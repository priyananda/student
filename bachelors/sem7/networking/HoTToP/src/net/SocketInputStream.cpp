#include <net/SocketInputStream.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

SocketInputStream::SocketInputStream():sd(-1){}

SocketInputStream::SocketInputStream(socket_t _sd):sd(_sd){}

int SocketInputStream::read(void * buff,int siz){
    int ret;
    if ( (ret = ::read(sd,buff,siz)) < 0)
        throw Exception("IOException : Socket write failed");
    return ret;
}

void SocketInputStream::close(){
    ::close(sd);
}

SocketInputStream::~SocketInputStream(){
}
