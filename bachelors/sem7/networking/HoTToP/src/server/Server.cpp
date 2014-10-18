#include <server/Server.h>
#include <server/RequestDispatcher.h>

#include <utils/Exception.h>
#include <utils/ConfigManager.h>

#include <unistd.h>


volatile bool Server::terminated = true;
volatile bool Server::restarting = false;
ServerSocket Server::soc;

void Server::start(){
	soc.bind(ConfigManager::getPort());
	restarting = terminated = false;
	while(terminated == false){
		try{
			// Wait for a request.
			Socket s = soc.accept();
			switch(fork()){
				case -1: throw Exception("Fork error");
				case 0:{
					soc.close();
					terminated = true;
					// Dispatch the request.
					RequestDispatcher dispatcher(s);
					while(dispatcher.prepareRequest())
						dispatcher.dispatchRequest();
					break;
				}default:
					s.close();
			}
		}catch(Exception& e){
			if(errno == EAGAIN || restarting)continue;
			if(!terminated)throw;
		}
	}
	soc.close();
}

void Server::terminate(){
	terminated = true;
	soc.close();
}

void Server::restart(){
	if(!terminated)soc.close();
	soc.bind(ConfigManager::getPort());
	restarting = true;
}
