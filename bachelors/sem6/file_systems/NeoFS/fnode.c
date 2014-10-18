/*
 * @file : fnode.c
 * @date : 23 4 2003 
 * @author : naveen
 * @comments : FNode maintainance operations
 * @exports : get_fnode , put_fnode , knock_out , alloc_node ,free_node
 */
#include "proto.h"
#include "global.h"
#define OPEN_START 0 
/* represents starting fd , 2 because 0 and 1 
 * for stdin and stdout respectively currently 
 * set to 0, if changed remember that the vlue 
 * of NO_OPEN has to be changed */

/** 
 * fuction get_fnode(lba,dev)  
 * return the file descriptor.This also reads the required inode to memory 
 * table and uses buffer for this purpose
 **/
u8 get_fnode(u32 lba,u8 dev){
	u8 buf_no,i,dirty=CT_OPEN_FILE;
	for(i=0; i < CT_OPEN_FILE; i++){  
		/*it starts from 2 because fd 0 and fd 1 are always used for stdin
		 * and stdout respectively, if used*/
		if(open[i].dev == dev && open[i].lba == lba){
				if(open[i].used == NOT_IN_USE){
					open[i].used=IN_USE;
					open[i].file_pos=0;/*we do not call it clean , because
										if it was dirty earlier then it should
										remain so*/
                                        open[i].pid=get_pid();
					return i+OPEN_START;
				}else{
					ERROR_NO = ALREADY_OPEN;
					handle_error();
					return NO_OPEN;     /*never executed because u never exit
										  from handle_error() function*/
				}
		}
	}
	for(i=0; i < CT_OPEN_FILE; i++){
		if(open[i].used==NOT_IN_USE ){
			if (open[i].f_status==CLEAN)
				break;
			else
				dirty=i;
		}
	}
	if(i == CT_OPEN_FILE){  /* means no clean page ,not in use*/
		if(dirty != CT_OPEN_FILE){  /*a dirty page is available,
									  write it and use it*/
			buf_no = get_block(open[dirty].dev,open[dirty].lba,ONLY_SEARCH);
			/*since dirty we put it to buffer to write to disk*/
			buf[buf_no].data.fadt=open[dirty].block.fadt;
			/*even if it is a directory , since we have same 
			 * type_in_blk union and it is bit by bit copy, 
			 * should work fine, same at 2 occations later, 
			 * line 50 and 65*/
			buf[buf_no].status=DIRTY;
			put_block(buf_no,NOT_FRONT);
			/*getting the required fnode*/
			buf_no =  get_block(dev,lba,NOT_ONLY_SEARCH);
			open[dirty].block.fadt=buf[buf_no].data.fadt;
			put_block(buf_no,NOT_FRONT);
			open[dirty].lba =lba;
			open[dirty].dev=dev;
			open[dirty].f_status=CLEAN;  /*only the mode attribute of 
										   file table not set, because it 
										   depends on the operation 
										   specified in open call, R or W*/
			open[dirty].used=IN_USE;
			open[dirty].file_pos=0;
                        open[dirty].pid=get_pid();
			return dirty+OPEN_START;

		}else{          /*whole array already in uuse*/
			ERROR_NO= NO_EMPTY_OPEN;
			handle_error();
			return NO_OPEN;
		}
	}else{ 				/*free clean page available*/
		buf_no=get_block(dev,lba,NOT_ONLY_SEARCH);
		open[i].block.fadt=buf[buf_no].data.fadt;
		put_block(buf_no,NOT_FRONT);
		open[i].lba =lba;
		open[i].dev=dev;
		open[i].used=IN_USE;
		open[i].f_status=CLEAN;
		open[i].file_pos=0;
                open[i].pid=get_pid();
		return i+OPEN_START;
	}

}

/**
 * This makes the file descriptor free to be used by other file
 **/
void put_fnode(u8 fd){
		open[fd-OPEN_START].used=NOT_IN_USE;
		/*fd varies from 2 to end , 0 and 1 left spare*/
}

void clean_fnode(u32 lba){
    u8 i;
    for(i=0; i < CT_OPEN_FILE ; i++)
        if( open[i].lba == lba){
            open[i].lba = NO_LBA;
            open[i].dev = NO_DEV;
            open[i].f_status = CLEAN;
            open[i].used = NOT_IN_USE ;
        }
}

u8 knock_out(u8 dev){
	u8 i,buf_no;
	for(i=0; i < CT_OPEN_FILE; i++){
		if(open[i].f_status ==  DIRTY  &&  open[i].dev ==  dev){
			buf_no=get_block(dev,open[i].lba,ONLY_SEARCH);
			buf[buf_no].data.fadt=open[i].block.fadt;
			buf[buf_no].status=DIRTY;
			put_block(buf_no,FRONT);
            open[i].f_status=CLEAN; 
			/*we do not say it is not in use, because a perticular 
			 * file ay be, we say not in use only at put_fnode */
        }
	}
	return 1;
}

/**
 * 	This function allocates fnode. since we do not know whether it is done 
 * 	for ordinary file or directory fields like mode and size are in complete
 *  the function mkdir and create are expected complete them 
 **/
 u32 alloc_node(u8 dev){
	u32 lba;
	lba = alloc_bit(dev);
 	return lba;
}

void free_node(u32 lba,u8 dev){
	u8 i;
	free_bit(lba,dev);
	for(i=0; i < CT_OPEN_FILE; i++){
		if(open[i].dev == dev &&  open[i].lba == lba){
			open[i].used=NOT_IN_USE; 
			/* These 2 are 2 prevent waste of buffer caused due to some 
			 * inconsistency*/
			open[i].f_status=CLEAN;  
			/* Before we free node we need to explicitly clean buffers, 
			 * for writing them back*/
			open[i].lba=NO_LBA;     
			/* These 2 are 2 see to it that a new file ,if that has same 
			 * lba does not use remains in buffer*/
			open[i].dev=NO_DEV;
			/* We need not write back here because the remove operation 
			 * looks after it*/
		}
	}
	for(i=0; i < CT_BUFS; i++){
		if(buf[i].dev == dev &&  buf[i].lba == lba){
			buf[i].used=NOT_IN_USE; 
			/* These 2 are 2 prevent waste of buffer caused due to some 
			 * inconsistency*/
			buf[i].status=CLEAN;
			buf[i].lba=NO_LBA;     
			/* These 2 are 2 see to it that a new file ,if that has same 
			 * lba does not use remains in buffer*/
			buf[i].dev=NO_DEV;
			/* We need not write back here because the remove operation 
			 * looks after it*/
		}
	}
}

