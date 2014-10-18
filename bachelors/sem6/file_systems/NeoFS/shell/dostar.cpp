#include "shell.h"
#include "cmdparse.h"
#include "fileio.h"
#include "fnode.h"
#include <global.h>
#include "dir_str.h"
#include <conio.h>
#include <stdio.h>

#define vd_puts(x)      (printf((char *)x))
#define vd_putint(x)    (printf("  %u  ",x))
#define vd_putchar(x)   (printf("%c",x))
#define IS_CTRLED(ch)   ( (ch) & 0x10000  )
#define gets(__x)       gets((char*)__x)
#define SEEK_BEG                0
#define SEEK_CUR                1
#define SEEK_END                2
/////////////Uncomment this for colored output ( slow )///////////////////

//#define COLOR_LIST  

///////////////////////////////////////////////////////////////////////////
u8 CommandParser::command[100];
u8 CommandParser::curr_dir[100];
u8 CommandParser::first_arg[132];
u8 CommandParser::second_arg[132];
u8 is_loaded;

int atoi(char *);
int is_dir(u8 * path);

void CommandParser::init(){
	clrscr();
	strcpy(curr_dir,"|");
	command[0] = 0;
	first_arg[0] = 0;
	second_arg[0] = 0;
	is_loaded =0;
}

void CommandParser::getCommand(){
	vd_puts("[ ");
	vd_puts(curr_dir);
	vd_puts(" ]+>");
	command[0] = 0;
	first_arg[0] = 0;
	second_arg[0] = 0;
	gets((char *)command);
}

int CommandParser::parseCommand(){
	int cmd = BAD_CMD ,i ,  j;
	u8 temp[100];
		int x;
	first_arg[0] = 0;
	second_arg[0] = 0;
	for( i = 0 ; command[i] != 0 && command[i] == (u8)' ' ; ++i);//skip spaces
	for( j = 0; command[i] != 0 && command[i] != (u8)' ' ; ++i , ++j )//get the command
		temp[j] = command[i];
	temp[j] = 0;
	for (  x = 0 ; x < NUM_CMD ; ++x)
		if(!strcmp(temp,cmd_str[x])){
			cmd = x;
			break;
		}
	if ( i == BAD_CMD ) return BAD_CMD;
	for( ; command[i] != 0 && command[i] == (u8)(' ')   ; ++i);//skip spaces
	for( j = 0 ; command[i] != 0 && command[i] != (u8)(' ') ;   ++i , ++j)
		first_arg[j] = command[i];// get first argument
	first_arg[j] = 0;
	for( ; command[i] != 0 && command[i] == (u8)(' ')   ; ++i);//skip spaces
	if ( command[i] == 0 )
		return cmd;
	for( j = 0 ; command[i] != 0 && command[i] != (u8)(' ') ;   ++i , ++j)
		second_arg[j] = command[i];// get second argument
	second_arg[j] = 0;
	return cmd;
}

void CommandParser::executeCommand(int cmd){
	switch(cmd){
		case WRI  :  toAbsolute(first_arg);
					 do_wri(first_arg);     break;
		case LIST :  toAbsolute(first_arg);
					 do_list(first_arg);        break;
		case SHOW :  toAbsolute(first_arg);
					 do_show(first_arg);    break;
		case APP  :  toAbsolute(first_arg);
					 do_app(first_arg);        break;
		case CD   :  do_cd();               break;
		case HELP :  if (strlen(first_arg) == 0)
						do_helpd();
					 else
						do_help(first_arg);
					 break;
		case MKFS :  do_mkfs();             break;
		case REN  :  toAbsolute(first_arg);
					 do_ren(first_arg , second_arg);
					 break;
		case FINFO:  toAbsolute(first_arg);
					 do_info(first_arg);
					 break;
		case LINK :  toAbsolute(first_arg);
					 toAbsolute(second_arg);
					 do_link(first_arg , second_arg);
					 break;
		case QUIT :  do_quit();break;
		case CP   :  toAbsolute(first_arg);
					 toAbsolute(second_arg);
					 do_cp(first_arg , second_arg);
					 break;
		case LOAD :  do_load();
					 break;
		case ULOAD:     do_uload();
					 break;
		case RF   :  toAbsolute(first_arg);
					 do_rf(first_arg);
					 break;
		case RMD  :  toAbsolute(first_arg);
					 do_rmd(first_arg);
					 break;
		case MKD  :  toAbsolute(first_arg);
					 do_mkd(first_arg);
					 break;
		case CHOWN : toAbsolute(first_arg);
					 do_chown(first_arg,second_arg);
					 break ;
		case CHPERM : toAbsolute(first_arg);
					  do_chperm(first_arg,second_arg);
					  break;
		case ADDUSER :
					  do_adduser() ;
					  break;
		case CLS     :
					  clrscr();
					  break;
		case REBOOT  :
					 //
					  break;
		default:
					 if ( strlen(command) )
						 vd_puts("Invalid Command\n");
	}
}

void CommandParser::do_cd(){
	int len;
	if (!is_loaded){
		vd_puts("FILE SYSTEM NOT LOADED\n");
		return ;
	}
	if(flpchange){
		uloadfs();
	}
	if ( strlen(first_arg) == 0){
		vd_puts("Current Dir:");
		vd_puts(curr_dir);
		return;
	}
    toAbsolute(first_arg);
	if ( ispresent(first_arg) == -1  ){
	   vd_puts( "THE DIRECTORY SEEMS TO BE ON A HOLIDAY !!\n" );
	   errormessage(geterror());
	   return;
	}
    if ( !is_dir(first_arg) ){
       vd_puts( "The Specified File is not a directory\n" );
	   return;
    }
    strcpy(curr_dir,first_arg);
}

int CommandParser::do_quit(){
		if (is_loaded){
			   vd_puts ( "Please UNLOAD FILE SYSTEM BEFORE QUITING\n");
			   return 1;
		}
        exit(0);
		return 0;
}

void CommandParser::toAbsolute(u8 * file){
	u8 temp[135];
	int len = strlen(file);
	if (len == 0)return;
	if (file[0] != '|' ){
        strcpy(temp,curr_dir);
        strcat(temp,"|");
        strcat(temp,file);
	}else
        strcpy(temp,file);
    normalize(temp);
    strcpy(file , temp);

}

int do_wri(u8 * file){
	s8 ret,fd;
	u32 retlba ;
	u8 i=0;
	u32 ch;
	u8 buff[256] = {0};
	if (!check_for_args(WRI,1))return 1;
	fd = openf(file,O_RW);
	if ( fd == -1){
		retlba=NO_LBA;
		if (ERROR_NO == NO_DIR_FILE)
			retlba  = creatf(file , 064);
		if (retlba  == NO_LBA){
			vd_puts ( "COULD NOT OPEN OR CREATE THE DESTINATION FILE\n" );
				errormessage(geterror());
			closef(fd);
			fl_clean();
			return 0;
		}
		fd = openf(file,O_RW);
	}
	if(fd == -1){
		vd_puts("CANNOT OPEN THE FILE\n");
		errormessage(geterror());
		fl_clean();
		return 1;
	}
	while(1){
		ch=getche();
		if(ch == 1)
			break;
        if( ch == 13 || ch == 10){printf("\n"); ch = '\n';}
		if (i == 255){
			i=0;
			ret = writef(fd,buff,256);
			if(ret == -1){
				vd_puts("SORRY SORRY CANNOT WRITE TO FILE SO REMOVING IT\n");
				errormessage(geterror());
				unlinkf(file);
				fl_clean();
				return 1;
			}
		}
		buff[i++] = ch;
	}
	ret = writef(fd,buff,i);
	if(ret == -1){
		vd_puts("SORRY SORRY CANNOT WRITE TO FILE SO REMOVING IT\n");
		errormessage(geterror());
		unlinkf(file);
		fl_clean();
		return 1;
	}
	closef(fd);
	vd_puts(" \n");
	fl_clean();
	return 0;
}
int do_list(u8 * dir){
	s8 fd,ret;
	struct fnode fn;
	int i;
	u8 size;
	struct dir_str dira[256];
    u8 full_name[132];// fullpath name  of child
	if (!check_for_args(LIST,1)) return 1;
	fd = opend(dir);
	if (fd == -1){
		vd_puts("CANNOT OPEN DIRECTORY:: ");vd_puts(dir);vd_puts("\n");
				errormessage(geterror());
				fl_clean();
		return 1;
	}
	ret = finfo(fd,&fn);
	if (ret == -1){
		vd_puts(" CANNOT OPEN DIRECTORY::");vd_puts(dir);vd_puts("\n");
		errormessage(geterror());
		fl_clean();
		return 1;
	}
	size = fn.ct_links;
	ret=readd(fd,size+2,dira);
	if (! ret){
		vd_puts(" CANNOT READ THE DIRECTORY\n");
				errormessage(geterror());
				fl_clean();
		return 2;
	}
	for(i=0; i < size+2 ; i++){
#ifdef COLOR_LIST 
        strcpy(full_name,dir);
        strcat(full_name,"|");
        strcat(full_name,dira[i].name);
        if ( !strcmp(dira[i].name,".") || ! strcmp(dira[i].name,"..") ){
            textcolor(YELLOW);
            cprintf("%s\n\r",dira[i].name);
            textcolor(WHITE);
            continue;
        }
        if ( is_dir(full_name) ){
            textcolor(YELLOW);
            cprintf("%s\n\r",dira[i].name);
            continue;
        }
        textcolor(BLUE);
        cprintf("%s\n\r",dira[i].name);
#else
        printf("%s\n",dira[i].name);
#endif
    }
    textcolor(WHITE);
    fl_clean();
	return 0;
}

int do_show(u8 * file){
	s8 fd, ret ; u32 i ;
	struct fnode fn;
	u32 size;
	u8 buff[1025];

	if (!check_for_args(SHOW,1)) return 1;
	fd=openf(file,O_READ);
	if ( fd == -1){
		vd_puts("CANNOT OPEN THE FILE\n");
				errormessage(geterror());
				fl_clean();
		return 1;
	}

	ret = finfo(fd,&fn);
	if ( ret == -1){
		vd_puts("CANNOT OPEN THE FILE\n");
				errormessage(geterror());
				fl_clean();
		return 1;
	}
	size=fn.size;
	while(size){
		ret = readf(fd,buff,(size < 1024 ? size : 1024));
		if ( ret == -1){
			vd_puts("CANNOT  READ THE FILE\n");
					errormessage(geterror());
					fl_clean();
			return 1;
		}
		buff[(size < 1024 ? size : 1024)]=0 ;
		for(i = 0 ; i < (size < 1024 ? size : 1024) ; ++i )
			if ( buff[i] == 10 || buff[i] == 13) buff[i] = '\n';
		vd_puts( buff);
		vd_puts("\n");
		if (size >= 1024)
		    size-=1024 ;
		else
			size=0;
	}
	closef(fd);
	fl_clean();
	return 0;
}

int do_app(u8 * file){
	s8 ret,fd;
	u8 i=0;
	u32 ch;
	u8 buff[256];
	struct fnode fn;
	u32 size;
	if (!check_for_args(APP,1)) return 1;
	fd = openf(file,O_RW);
	if(fd == -1){
		vd_puts( "CANNOT OPEN THE FILE\n");
				errormessage(geterror());
				fl_clean();
		return 1;
	}
	finfo(fd, & fn);
	size = fn.size;
	ret= seekf(fd,  size,SEEK_BEG);
	while(1){
		ch=getche();
		if(ch == 1)
			break;
        if (ch == 13 || ch == 10 ){
            printf("\n");ch='\n';
        }
		if (i == 255){
			i=0;
			ret = writef(fd,buff,256);
			if(ret == -1){
				vd_puts("SORRY SORRY CANNOT WRITE TO FILE SO REMOVING IT\n");
                errormessage(geterror());
				unlinkf(file);
                fl_clean();
				return 1;
			}
		}
		buff[i++] = (u8)ch;
	}
	ret = writef(fd,buff,i);
	if(ret == -1){
		vd_puts("SORRY SORRY CANNOT WRITE TO FILE SO REMOVING IT\n");
				errormessage(geterror());
		unlinkf(file);
				fl_clean();
		return 1;
	}
    puts(" ");
	closef(fd);
		fl_clean();
	return 0;

}

int do_mkfs(){
	s8 ret,i=0;
    u8 ch;
	u8 password[PASSWORD_LENGTH];
	vd_puts("enter the new admin password you want to set  ::");
	while (i <= PASSWORD_LENGTH && ( ch = password[i++] = getch()) != (u8)('\n') && ch != (u8)('\r') )vd_putchar('#');
	password[--i] = 0;
	vd_puts("\n");
	ret=makefs(password);
	flpchange=0;
	if(ret == -1){
		ERROR_NO=0;
		ret=makefs(password);
		flpchange=0;
		if (ret == -1){
			vd_puts("CANNOT CREATE FILE SYSTEM\n") ;
			errormessage(geterror());
			return 1;
		}
	}
	fl_clean();
	return 0;
}
int do_ren(u8 * _old , u8 * _new){
	s8 ret;
	if (!check_for_args(REN,2)) return 1;
	ret =ren(_old, _new);
	if(ret == -1){
		vd_puts("CANNOT RENAME THIS FILE\n");
		errormessage(geterror());
	}
	fl_clean();
	return 0;
}

int do_info(u8 * file){
	struct fnode fn;
	s8 ret;
	if (!check_for_args(FINFO,1)) return 1;
   ret = info(file, &fn);
   if(ret == -1){
		vd_puts("CANNOT GET INFO\n");
		errormessage(geterror());
		fl_clean();
		return 1;
   }

   vd_puts("File :"); vd_puts(file);vd_puts("\n");
   vd_puts("Size :"); vd_putint((unsigned int)fn.size);vd_puts("\n");
   vd_puts("Links :"); vd_putint((unsigned int)fn.ct_links);vd_puts("\n");
   vd_puts("m_time :");vd_putint((unsigned int)fn.m_time);vd_puts("\n");
   vd_puts("User id :" );vd_putint( (unsigned int)fn.uid );vd_puts("\n");
   vd_puts("mode :" ); vd_putint( (unsigned int)fn.mode );vd_puts("\n");
   (fn.mode & 0x80 )? vd_puts("DIRECTORY") : vd_puts("ORDINARY FILE" ) ;vd_puts("\n");
    vd_puts("PERMISSIONS :: \n" );
   (fn.mode & OWNER_READ)? vd_puts("r"):vd_puts("-") ;
   (fn.mode & OWNER_WRITE)?vd_puts("w"):vd_puts("-") ;
   (fn.mode & OWNER_EXECUTE)?vd_puts("x"):vd_puts("-");
   (fn.mode & OTHER_READ)?vd_puts("r"):vd_puts("-") ;
   (fn.mode & OTHER_WRITE)?vd_puts("w"):vd_puts("-") ;
   (fn.mode & OTHER_EXECUTE)?vd_puts("x"):vd_puts("-") ;vd_puts("\n");
   fl_clean();
   return 0;
}

int do_link(u8 * file , u8 * link){
	s8 ret;
	if (!check_for_args(LINK,2)) return 1;
	ret = linkf(file,link);
	if(ret == -1){
		vd_puts("CANNOT CREATE LINK\n");
				errormessage(geterror());
		}
		fl_clean();
	return 0;
}

int do_cp(u8 * src , u8 * dst){
	s8 sfd,dfd,ret ;
		u32 retlba;
	struct fnode fn;
	u32 size;
	u8 buff[1024];
	if (!check_for_args(CP,2)) return 1;
	sfd=openf(src,O_READ);
	if ( sfd == -1){
		vd_puts("COULD NOT OPEN SOURCE FILE\n");
				errormessage(geterror());
				fl_clean();
		return 1;
	}
	dfd = openf(dst, O_RW);
	if ( dfd == -1){
		retlba  = creatf(dst , 064);
		if (retlba  == NO_LBA){
			vd_puts("COULD NOT OPEN  OR CREATE THE DESTINATION FILE\n");
						errormessage(geterror());
						fl_clean();
					return 0;
			   }
		   dfd = openf(dst,O_RW);
	}

	ret = finfo(sfd, &fn);
	if (ret == -1){
		vd_puts("HAD PROBLEMS WITH GETTING INFO  OF SOURCE FILE\n");
				 errormessage(geterror());
		closef(sfd);
		closef(dfd);
				fl_clean();
		return 1;
	}
	size = fn.size;
		while (size ){
			ret = readf(sfd  , buff,  (size < 1024  ?  size  :  1024));
			if ( ret == -1){
				vd_puts("ERRROR OCCURED IN READING SOURCE FILE\n");
						errormessage(geterror());
				closef(sfd);
				closef(dfd);
						fl_clean();
				return 1;
			}
			ret = writef(dfd, buff , (size < 1024  ?  size  :  1024));
			if (ret == -1){
				vd_puts("ERROR IN WRITE  DELETING THE FILE\n");
					   errormessage(geterror());
				closef(sfd);
				closef(dfd);
				unlinkf(dst);
						 fl_clean();
				return 1;
			}
				if (size >= 1024){
						size-=1024;
				}else
						size=0;

		}
		fl_clean();
	return 0;
}



int do_load(){
	s8 ret;
    u8 ch;
	u32 i=0;
	u8 id;
	u8 password[PASSWORD_LENGTH];
	u8 username[MAX_NAME];

	if (is_loaded){
		vd_puts("FILE SYSTEM ALREADY LOADED\n");
		return 0;
	}
	vd_puts("ENTER USER NAME ::") ;
	gets(username);
	username[--i] = 0;
	i=0;
	vd_puts("\nENTER PASSWORD ::");
	while (i <= PASSWORD_LENGTH && ( ch = password[i++] = getch() ) != (u8)('\n') && ch != (u8)('\r'))vd_putchar('#');
	password[--i] = 0;
	vd_puts("\n");
	ret = loadfs(username,password);
	flpchange=0;
	if(ret == -1){
		ERROR_NO=0;
		ret = loadfs(username,password);
		flpchange=0;
		if (ret == -1){
			 vd_puts( "CANNOT LOAD FILESYSTEM\n" );
			 errormessage(geterror());
			 return 1;
		}
	}
  is_loaded  = 1;
  fl_clean();
  return 0;
}

int do_uload(){
		s8 ret;
	if ( ! is_loaded){
		vd_puts("FILE SYSTEM NOT  LOADED TO UNLOAD\n");
		return 0;
	}
	is_loaded  = 0;
	ret =  uloadfs();
		if (ret == -1) {
				vd_puts(" CANNOT UNLOAD FILE SYSTEM");
				return 0;
		}
		return 1;
}

int do_rf(u8 * file){
	s8 ret;
	if (!check_for_args(RF,1)) return 1;
	ret = unlinkf(file);
	if(ret == -1){
		vd_puts("CANNOT REMOVE THE FILE\n");
				errormessage(geterror());
		}
	fl_clean();
	return 0;
}

int do_rmd(u8 * dir){
	s8 ret;
	if (!check_for_args(RMD,1)) return 1;
	ret= removed(dir);
	if(ret == -1){
		vd_puts("CANNOT REMOVE THIS  DIRECTORY\n");
				errormessage(geterror());
		}
		fl_clean();
	return 0;
}


int do_mkd(u8 * dir){
	s8 ret;
	u32 retlba;
	if (!check_for_args(MKD,1)) return 1;
	vd_puts(dir);
	vd_puts("\n");
	retlba  = maked(dir);
	if(retlba == NO_LBA){
		vd_puts( "CANNOT MAKE DIRECTORY\n"  );
				errormessage(geterror());
		}
		 fl_clean();
	return 0;
}

int do_chown(u8 * path , u8 * newown){
		s8 ret;
		if (! is_loaded){
				vd_puts( "FILE SYSTEM NOT LOADED\n" );
				return 0;
		}
		ret = chown(path,newown);
		if (ret == -1){
				vd_puts("COULD NOT CHANGO OWNERSHIP\n") ;
				errormessage(geterror());
		}
		fl_clean();
		return 0;
}

int do_chperm(u8 * path , u8 * newperm){
		s8 ret;
		u8 own;
    if (!check_for_args(CHPERM,1)) return 1;
		own = (u8)atoi((char *)newperm);
		ret = chperm(path,own);
		if (ret == -1){
				vd_puts ( "COULD NOT CHANGE PERMISSION\n");
				errormessage(geterror());
		}
		fl_clean();
		return 0;
}

int do_adduser(){
    s8 ret;
	u32 i=0;
	u8 id;
	u8 password[PASSWORD_LENGTH] , ch;
	u8 username[MAX_NAME];
	if (!check_for_args(ADDUSER,0)) return 1;
	vd_puts("ENTER USER NAME ::" );
	gets(username);
	username[--i] = 0;
	i=0;
	vd_puts("\nENTER PASSWORD ::" );
	while (i <= PASSWORD_LENGTH && (ch = password[i++] = getch()) != (u8)('\n') && ch != (u8)('\r'))vd_putchar('#');
	password[--i] = 0;
	vd_puts("\n");
	ret=useradd(username,password);
	if (ret == -1) {
	   vd_puts("COULD NOT ADD USER\n");
	   errormessage(geterror());
	   fl_clean();
	   return 1;
	}
	fl_clean();
	return 0;
}

int check_for_args(int cmd,int nargs ){
	int al = strlen(CommandParser::first_arg), bl = strlen(CommandParser::second_arg);
	ERROR_NO=0;
	if (!is_loaded){
		vd_puts("FILE SYSTEM NOT LOADED\n");
		return 0;
	}
	if (   ( nargs == 0 && al == 0  && bl == 0 )
		 ||( nargs == 1 && al != 0  && bl == 0 )
		 ||( nargs == 2 && al != 0  && bl != 0 ) )return 1;
	vd_puts("Invalid Arguments to ");
	vd_puts(cmd_str[cmd]);
	vd_puts("\n");
	vd_puts("Usage ::\n");
	vd_puts(cmd_help_str[cmd]);
	vd_puts("\n");
	return 0;

}
// Sorry , very bad implementation . Later (??) we can replace this with proper one
int is_dir(u8 * file){
    struct fnode fn;
    s8 ret;
    ret = info(file, &fn);
    if(ret == -1){
		fl_clean();
		return 0;
   }
   fl_clean();
   return fn.mode & (0x80);
}
