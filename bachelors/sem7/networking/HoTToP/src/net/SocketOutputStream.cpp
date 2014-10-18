#include <net/SocketOutputStream.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

SocketOutputStream::SocketOutputStream():sd(-1){}

SocketOutputStream::SocketOutputStream(socket_t _sd):sd(_sd){}

int SocketOutputStream::write(const void * buff,int siz){
    int ret;
    if ( (ret = ::write(sd,buff,siz)) < 0)
        throw Exception("IOException : Socket write failed ");
    return ret;
}

void SocketOutputStream::close(){
    ::close(sd);
}

SocketOutputStream::~SocketOutputStream(){
}
