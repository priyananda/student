#include <server/Server.h>

#include <utils/Exception.h>
#include <utils/ConfigManager.h>

#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <iostream>
using std::cout;
using std::endl;

extern "C" {

static void child_dead(int signum){
	while(waitpid(-1,NULL,WNOHANG) > 0);
}

static void sig_int(int signum){
	cout<<"SIGINT recieved shutdown server"<<endl;
	Server::terminate();
}

static void sig_usr1(int signum){
	cout<<"SIGUSR1 recieved reloading config"<<endl;
	try{
		ConfigManager::reset();
		ConfigManager::load();
		Server::restart();
	}catch(Exception& e){
		cout<<e.toString()<<endl;
		exit(1);
	}
}

}

int main(int argc, char ** argv){
	try{
		ConfigManager::init(argc, argv);
		ConfigManager::load();
		signal(SIGCHLD, child_dead);
		signal(SIGINT, sig_int);
		signal(SIGUSR1, sig_usr1);
		Server::start();
	}catch(Exception& e){
		cout<<e.toString()<<endl;
	}
}
