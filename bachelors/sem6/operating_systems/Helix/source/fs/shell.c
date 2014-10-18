#include "cmdparse.h"
#include "fileio.h"

const char  cmd_str[][10] =  {
 	"wri"  ,
 	"list" ,
 	"show" ,
 	"app"  ,
 	"cd"   ,
 	"help" ,
 	"mkfs" ,
 	"ren"  ,
 	"finfo",
 	"link" ,
    "quit" ,
    "cp"   ,
    "load" ,
    "uload",
    "rf"   ,
    "rmd"  ,
    "mkd"  ,
    "chown",
    "chperm",
    "adduser",
    "clr",
    "reboot"
};

const char  cmd_help_str[][100] =  {
	"wri FILE                    :        Writes a new file"  ,
	"list                        :        Lists directory contents" ,
	"show FILW                   :        Displays a file" ,
	"app FILE                    :        Appends to existing file"  ,
	"cd DIR                      :        Change directory"   ,
	"help [CMD]                  :        Displays a help message" ,
	"mkfs                        :        Create a new FileSystem" ,
	"ren OLD NEW                 :        Rename a file"  ,
	"finfo FILE                  :        File information",
	"link OLD NEW                :        Create a link" ,
	"quit                        :        Quits from shell",
	"cp OLD NEW                  :        Copies files"   ,
	"load                        :        Loads filesystem" ,
	"uload                       :        Unloads filesystem",
	"rf FILE                     :        Deletes a file"   ,
	"rmd DIR                     :        Deletes a directory"  ,
	"mkd DIR                     :        Creates a directory",
    "chown FILE NEW_OWNER        :        Changes the owner ",
    "chperm FILE NEW_PERM        :        Changes the permission ",
    "adduser                     :        Adds a user",
    "clr                         :        Clears the screen",
    "reboot                      :        Reboots System"
};

const struct man_message man_msg[]  = {
    {
        "wri" ,
        "FILENAME " ,
        "This command writes a new file or overwrites an existing file" ,
        "Terminate by CTRL-A"
    },
	{
        "list" ,
        "DIRNAME",
        "Lists directory contents.Shows all files and folders under the directory. ",
        "Use list . to get current directory contents"
     },
	{
        "show",
        "FILE",
        "Displays the contents of a file on the screen" ,
        "Donot use for binary ( non-ascii) files"
    },
	{
        "app",
        "FILE",
        "Appends to existing file. If file doesnot exist , it is not created." ,
        "Use wri for creating new files"
    } ,
    {
        "cd",
        "[DIR]",
        "Change directory to target directory . If no arguments are given , the "
            "current working directory is displayed"   ,
        ""
    },
    {
        "help",
        "[CMD]",
        "Displays a help message. If no arguments are given , a list of all commands"
            "are given. To get a more detailed help for a particular command , pass that "
            "as an argument",
        "Use help before trying out any commands"
    },
    {
        "mkfs",
        "",
        "Creates a new FileSystem.IMPORTANT : This will remove all data on your floppy ",
        "You need to give a password for the admin of the floppy  here "
    },
    {
        "ren",
        "OLDFILE NEWFILE",
        "Renames a file",
        "The second argument must be a filename, not a path"
    },
    {
        "finfo",
        "FILE",
        "File information : gives information about a file or a directory. ",
        "You need to have read permissions for the file / directory"
    },
    {
        "link",
        "OLDFILE NEWFILE",
        "Creates a link.The linked file points to the same file as the original.",
        "Changing a link will affect the original file"
    },
	{
        "quit",
        ""
        "Quits from shell",
        "You need to unload the file-system before quitting the shell"
    },
	{
        "cp",
        "OLDFILE NEWFILE",
        "Copies files.The newly created file is different from the original file",
        "The destination must be a file-name not a directory"
    },
	{
        "load",
        "",
        "Loads the filesystem.This must be done before any other operations" ,
        "Password is required for loading FS"
    },
	{
        "uload",
        "",
        "Unloads the filesystem.This must be done to flush all pending data to disk",
        ""
    },
	{
        "rf",
        "FILE",
        "Deletes a file.If the file is a link , the file is deleted only if there are "
            "no other links to that file",
        "Only one file can be deleted at a time"
    },
	{
        "rmd",
        "DIR",
        "Deletes a directory." ,
        "The directory must be empty"
    } ,
	{
        "mkd",
        "DIR",
        "Creates a directory",
        "No files are present in the directory when it is created"
    },
    {
        "chown",
        "FILE NEW_OWNER",
        "Changes the owner ",
        "You must be owner of file( or admin) for using this command"
    },
    {
        "chperm",
        "FILE NEW_PERM",
        "Changes the permission for the file",
        "File permissions are in octal"
    },
    {
        "adduser",
        "",
        "Adds a user",
        "Only admin can add users. Also users are for a paritcular floppy only"
    },
    {
        "clr",
        "",
        "Clears the screen",
        ""
    },
    {
        "reboot",
        "",
        "Reboots System",
        ""
    }
};

u8 NUM_CMD = ( sizeof(cmd_str) / sizeof(cmd_str[0]) );

int do_main(){
	int c = 1;
	initc();
	vd_puts("Type help for help\n");
	while(c){
		getCommand();
		c = parseCommand();
		c = executeCommand(c);
    }
    return 0;
}

