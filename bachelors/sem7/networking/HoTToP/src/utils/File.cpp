#include <utils/File.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

bool File::exists(const string& path){
	int fd;
	fd = open(path.c_str(), O_RDONLY);
	if(fd == -1 )return false;
	close(fd);
	return true;
}

bool File::isDir(const string& path){
	DIR * d;
	d = opendir(path.c_str());
	if(d == 0)return false;
	closedir(d);
	return true;
}
