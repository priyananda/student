
/*
 * @document : path.c
 * @date : 9 5 2003
 * @author : Naveen
 * @exports :
       lba  last_dir(u8 * path , u8 string[MAX_NAME]);
       lba  eat_path(u8 * path);  returns lba of last entry
       u8   search_dir(lba,string , lba * , flag);
        flag is LOOK_UP,ENTER,DELETE,IS_EMPTY
 * @finalUpdate : line 45
*/
#include "proto.h"
#include "global.h"
 /**  given a pointer to a path name ,this function stores
     * in string  argument the next string to be considered
     * and returns pointer to the part which has not been parsed  **/
u8 * get_name(u8 * old_name,u8 string[MAX_NAME]){
    register u8 c,*np,*rnp;
    np=string;
    rnp=old_name;
    while((c=*rnp)==IFS) rnp++;
    /*we can have multiple IFS in place of a single one*/
    while(c != IFS && c!= '\0'){
        if(np < &string[MAX_NAME])
             *np++=c;
        c= * ( ++rnp );
    }
    if(np < &string[MAX_NAME])
            *np='\0';
    return(rnp);
}

/**
 * This function returns the lba of the last directory, and also the
 * name of last part ,file or dir stored in string  , ie in path
 * |a|b|c|d   return lba of c and also name d stored in string,
 * this can be used to open d which is present or to create d which
 * is so far not present
 **/
u32 last_dir(u8 * path, u8 string[MAX_NAME]){
        u32 prev_lba=super[get_super(FDD)].root_dir_lba;
        u32 new_lba;
        u8 * rem;
        if(*path == '\0'){
                ERROR_NO=NAME_MISSING;
                handle_error();
                return NO_LBA;
       }
        rem=get_name(path,string);  /*read at root | to get next part*/
        while(*rem == IFS){
                /* as long as there is an IFS | to follow in string ,
                 * get its lba and continue*/
                search_dir(prev_lba,string,&new_lba,LOOK_UP);
                if(new_lba == NO_LBA){
                		if(!ERROR_NO){
                			ERROR_NO=NO_DIR_FILE;
                			handle_error();
                		}
                        return NO_LBA;
                }
                prev_lba=new_lba;
                rem=get_name(rem,string);   /*get the next part*/
        }
        return prev_lba;
}

/** this is used places like open, returns the lba of last
  entry is if path is |a|b|c  , returns lba of c  **/
u32 eat_path(u8 * path){
        u8 string[MAX_NAME];
        u32 lba,dlba;
        dlba=last_dir(path,string);
        if (dlba == NO_LBA){
                return NO_LBA ;
        }
        search_dir(dlba,string,&lba,LOOK_UP);
        if(lba == NO_LBA){
        		if(!ERROR_NO){
                	ERROR_NO=NO_DIR_FILE;
                	handle_error();
                }
               return NO_LBA ;
        }
        return lba;
}

    /**
      In the directory given by dlba, search for name string,
      whose lba will be stored in slba operation performed is
      give by flag as LOOK_UP or DELETE or  ENTER  or IS_EMPTY
      non zero on success  and  zero on failure
     **/

u8 search_dir(u32 dlba  , u8 string[MAX_NAME]  , u32 * slba , u8 flag){
    u8 second_idx=0,i,hashid,ct_links,temp;
    u8 buf1,buf2,buf3;
    u32 idx_lba;
    if(dlba == NO_LBA){
        ERROR_NO=NOT_DIR;
        handle_error();
        if (flag == LOOK_UP)     /*because the way error is indicated for LOOK_UP is not by returning 0 but by slba being NO_LBA*/
                *slba=NO_LBA ;
        return 0;
    }
    if (flag  >  IS_EMPTY){ /*IS_EMPTY MACRO HAS HIGHEST VALUE*/
        ERROR_NO=SCRAP_CODE;
        handle_error();
        if (flag == LOOK_UP)
                *slba=NO_LBA ;
        return 0;
    }
    buf1=get_block(FDD,dlba,NOT_ONLY_SEARCH);
    if( ! (buf[buf1].data.fadr.hc_fnode.mode  &  DIRECTORY)  ){
        /*to check if it is a directory*/
        put_block(buf1,NOT_FRONT);
        if(!ERROR_NO){
        	ERROR_NO=NOT_DIR;
	        handle_error();
	    }
        if (flag == LOOK_UP)
                *slba=NO_LBA ;
        return 0;
    }

    if(flag == IS_EMPTY){
        put_block(buf1,NOT_FRONT);
        return !(buf[buf1].data.fadr.hc_fnode.ct_links);
    }

    /* well count of links is zero , when it contains nothing other
     * than . and .. directories, then it retunrs !0 ie success.
     * If some subdirectory or file is there, ct_links is not zero
     * so this program returns zero.This puts a constraint on number
     * of files a directory can have , which is 255 because ct_links
     * is u8.
     * This also means that we know that reference do not cross second
     * direct reference. there are CT_DIR_FNODE entries in fnode block
     * and CT_DIR_NO_FNODE entries in non fnode block*/

     /*privilege check*/
    if (buf[buf1].data.fadr.hc_fnode.uid == get_user()){ /*to qwner of directory*/
                if (! (buf[buf1].data.fadr.hc_fnode.mode & OWNER_WRITE)  && ( flag == ENTER  ||  flag == DELETE )) {
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        put_block(buf1,NOT_FRONT);
                        return 0;
                }
                if (! (buf[buf1].data.fadr.hc_fnode.mode & OWNER_READ)  && ( flag == LOOK_UP)  ) {
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        put_block(buf1,NOT_FRONT);
                        return 0;
                }

    }else{ /*to other user of directory*/
                if (! (buf[buf1].data.fadr.hc_fnode.mode & OTHER_WRITE)  && ( flag == ENTER  ||  flag == DELETE )) {
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        put_block(buf1,NOT_FRONT);
                        return 0;
                }
                if (! (buf[buf1].data.fadr.hc_fnode.mode & OTHER_READ)  && ( flag == LOOK_UP)  ) {
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        put_block(buf1,NOT_FRONT);
                        return 0;
                }
    }


     /*privilege check*/
     hashid = hash(string);
     ct_links=buf[buf1].data.fadr.hc_fnode.ct_links;
     /* number of entries marked in block marked by second index,
      * ~second_idx is max value stored in u8*/

     /* going for a look up required for all 3 remaining functions*/
    if(ct_links <= CT_DIR_FNODE  -2){
       for(i=0; i <=ct_links+1;i++)
       /*we start at 2 coz we have .and .. directory at 0 and 1*/
       /*I hav decided to search this as well*/
           if(buf[buf1].data.fadr.dir[i].hash == hashid)
               if( !strcmp((char *)string,(char *)buf[buf1].data.fadr.dir[i].name))
                    /*exact match found*/
                    break;
       if(flag == LOOK_UP ){
           if(i > ct_links+1){
                   put_block(buf1,NOT_FRONT);
                   *slba=NO_LBA;
                    return 0;
           }else{ /*entry found*/
                   *slba=buf[buf1].data.fadr.dir[i].lba;
                   put_block(buf1,NOT_FRONT);
                   return i;
           }
       }
       if(flag == DELETE){
           if(i > ct_links+1){ /*no entry found*/
                   ERROR_NO=NO_DIR_FILE;
                   put_block(buf1,NOT_FRONT);
                   handle_error();
                   return 0;
           }
           if(i != ct_links+1)
               buf[buf1].data.fadr.dir[i] =
               buf[buf1].data.fadr.dir[ct_links+1];
           buf[buf1].data.fadr.hc_fnode.ct_links--;
           buf[buf1].status=DIRTY;
           put_block(buf1,NOT_FRONT);
           return 1;
       }
       if(flag == ENTER){
            if(i <= ct_links+1) {
                /*already present, so cannot be added*/
                ERROR_NO = ALREADY_PRESENT;
                put_block(buf1,NOT_FRONT);
                handle_error();
                return 0;
            }
            if(i <  CT_DIR_FNODE){
                /* Remember i is ct_links+1, i can go upto
                 * CT_DIR_FNODE, index starts at 0*/
                strcpy((char *)buf[buf1].data.fadr.dir[i].name ,(char *) string);
                buf[buf1].data.fadr.dir[i].hash=hashid;
                buf[buf1].data.fadr.dir[i].lba=*slba;
                buf[buf1].status=DIRTY;
                buf[buf1].data.fadr.hc_fnode.ct_links++;
                put_block(buf1 , NOT_FRONT);
                   return 1;
            }else{
                /* is i is CT_DIR_FNODE , so needs a new block*/
                idx_lba=alloc_node(FDD);
                if (idx_lba ==  NO_LBA){
                        put_block(buf1 ,  NOT_FRONT);
                        return 0;
                }
                buf[buf1].data.fadr.hc_fnode.index[0] = idx_lba;
                buf[buf1].status=DIRTY;
                buf2=get_block(FDD,idx_lba,ONLY_SEARCH);
                buf[buf2].data.data.dir[0].lba=*slba;
                strcpy((char *)buf[buf2].data.data.dir[0].name  ,
                        (char *)string);
                buf[buf2].data.data.dir[0].hash=hashid;
                buf[buf1].data.fadr.hc_fnode.ct_links++;
                buf[buf1].status=DIRTY;
                buf[buf2].status=DIRTY;
                put_block(buf1,NOT_FRONT);
                put_block(buf2,NOT_FRONT);
                return 1;
            }
        }/* end of if ( flag == ENTER) */
    }/* end of  if(ct_links <= CT_DIR_FNODE   -2) */
    /*a situation where in the name to be processed may be  in block
     * indicated by direct index 0*/
    else if (ct_links > CT_DIR_FNODE  -2
                &&  ct_links <= (CT_DIR_FNODE+CT_DIR_NO_FNODE -2 ) ){
       for(i=0; i <=CT_DIR_FNODE -1 ;i++)
           if(buf[buf1].data.fadr.dir[i].hash == hashid)
              if( !strcmp((char *)string , (char *)buf[buf1].data.fadr.dir[i].name))
                  /*exact match found*/
                  break;
       if( i  <  CT_DIR_FNODE){
           if(flag ==  LOOK_UP){
                   *slba=buf[buf1].data.fadr.dir[i].lba;
                   put_block(buf1,NOT_FRONT);
                   return  i  ;
           }
           if(flag == ENTER){
                    ERROR_NO = ALREADY_PRESENT;
                   put_block(buf1,NOT_FRONT);
                   handle_error();
                   return 0;
           }
           if(flag ==  DELETE){
                   buf2=get_block(FDD, buf[buf1].data.fadr.hc_fnode.index[0],NOT_ONLY_SEARCH);
                   buf[buf1].data.fadr.dir[i]  = buf[buf2].data.data.dir[ct_links - CT_DIR_FNODE +1 ] ;
                   buf[buf1].data.fadr.hc_fnode.ct_links--;
                   if(buf[buf1].data.fadr.hc_fnode.ct_links  <=  CT_DIR_FNODE -2 ) { /*ie the last element from first index is removed*/
                           free_node( buf[buf1].data.fadr.hc_fnode.index[0] , FDD);
                           buf[buf1].data.fadr.hc_fnode.index[0] = NO_LBA ;
                   }
                   buf[buf1].status=DIRTY;
                   put_block(buf1 , NOT_FRONT);
                   put_block(buf2 , NOT_FRONT);
                   return 1;
           }
       }/* end if ( i < CT_DIR_FNODE */
        /* this part obviously when element was not found in fadr,
        so following first direct index*/
        buf2=get_block(FDD, buf[buf1].data.fadr.hc_fnode.index[0],NOT_ONLY_SEARCH);
        temp = ct_links  -  CT_DIR_FNODE  +1;  /*ther are 0 to temp elements in first index block, this is after considering  the directories .   and .. , and also that starting index is 0*/
        for(i=0 ;  i <=temp;  i++)
           if(buf[buf2].data.data.dir[i].hash == hashid)
               if( !strcmp((char *)string , (char *)buf[buf2].data.data.dir[i].name))  /*exact match found*/
                     break;
        if(i  <=  temp){
            if(flag  ==  LOOK_UP){
                *slba=buf[buf1].data.fadr.dir[i].lba;
                 put_block(buf1,NOT_FRONT);
                 put_block(buf2,NOT_FRONT);
                 return CT_DIR_FNODE+i;
            }
            if(flag  ==  ENTER){
                     ERROR_NO = ALREADY_PRESENT;
                    put_block(buf1 ,NOT_FRONT);
                    put_block(buf2 ,NOT_FRONT);
                    handle_error();
                    return 0;
            }
            if(flag  ==  DELETE){
                buf[buf1].data.fadr.hc_fnode.ct_links--;
                buf[buf1].status=DIRTY;
                if ( i  !=  temp){
                      buf[buf2].data.fadr.dir[i] = buf[buf2].data.data.dir[temp ] ;
                      buf[buf2].status=DIRTY;
                 }
                if ( buf[buf1].data.fadr.hc_fnode.ct_links  <=  CT_DIR_FNODE   -2 ){
                    free_node( buf[buf1].data.fadr.hc_fnode.index[0] , FDD);
                    buf[buf1].data.fadr.hc_fnode.index[0] = NO_LBA ;
                    buf[buf1].status=DIRTY;
                 }
                 put_block(buf1,NOT_FRONT);
                 put_block(buf2,NOT_FRONT);
                 return 1;
            }else  /* all three conditions are already checked */
                return 0;
        }else{
            if(flag  ==  LOOK_UP){
                *slba=NO_LBA;
                put_block(buf1,NOT_FRONT);
                put_block(buf2,NOT_FRONT);
                return 0;
            }
            if(flag  ==  DELETE){
                put_block(buf1,NOT_FRONT);
                put_block(buf2,NOT_FRONT);
                handle_error();
                ERROR_NO=NO_DIR_FILE;
                return 0;
            }
            if(flag  ==  ENTER){
                if(  i  ==  CT_DIR_NO_FNODE) {
                    /*it varies from 0 to  CT_DIR_NO_FNODE-1 , if i is this value it
                    means i can insert, but since the block is complete i need to open
                    and write to second direct index block*/
                     idx_lba=alloc_node(FDD);
                     buf[buf1].data.fadr.hc_fnode.index[1] = idx_lba;
                     buf[buf1].status=DIRTY;
                     buf3 = get_block(FDD ,  idx_lba , ONLY_SEARCH);
                     buf[buf3].data.data.dir[0].hash=hashid;
                     buf[buf3].data.data.dir[0].lba=*slba;
                     strcpy ((char *)buf[buf3].data.data.dir[0].name  ,(char *)  string );
                     buf[buf3].status=DIRTY;
                     buf[buf1].data.fadr.hc_fnode.ct_links ++;
                     put_block(buf1,NOT_FRONT);
                     put_block(buf2,NOT_FRONT);
                     put_block(buf3,NOT_FRONT);
                     return 1;
                }else{ /* not the last entry , can be added easily*/
                     buf[buf1].data.fadr.hc_fnode.ct_links++;
                     buf[buf1].status=DIRTY;
                     buf[buf2].data.data.dir[temp+1].hash  =  hashid;
                     buf[buf2].data.data.dir[temp+1].lba     =  *slba;
                     strcpy ((char *) buf[buf2].data.data.dir[temp+1].name  ,(char *) string  ) ;
                     buf[buf2].status=DIRTY;
                     put_block(buf1,NOT_FRONT);
                     put_block(buf2,NOT_FRONT);
                     return 1;
                 }/* end of CT_DIR_NO_FNODE */
            }/* end of flag == ENTER */
        }/* end of  i <= temp */
    }/* Third part in an extremely complex large if */
    else if ( (ct_links  >  CT_DIR_FNODE  +  CT_DIR_NO_FNODE  -2 )  &&
            (ct_links  <  2* CT_DIR_NO_FNODE + CT_DIR_FNODE - 2) )
        /* To make sure that we do not go beyond 2 direct references, we have <
          instead of <=, because I want the insertion possible for last element ,
          and not beyond that*/
        {
            for(i=0; i <=CT_DIR_FNODE -1 ;i++)
                if(buf[buf1].data.fadr.dir[i].hash == hashid)
                   if( !strcmp((char *)string ,(char *) buf[buf1].data.fadr.dir[i].name))  /*exact match found*/
                       break;
            if( i  <  CT_DIR_FNODE){
                 if(flag ==  LOOK_UP){
                     *slba=buf[buf1].data.fadr.dir[i].lba;
                      put_block(buf1,NOT_FRONT);
                      return i;
                 }
                 if(flag == ENTER){
                     ERROR_NO = ALREADY_PRESENT;
                     put_block(buf1,NOT_FRONT);
                     handle_error();
                     return 0;
                 }
                 if(flag ==  DELETE){
                      buf3=get_block(FDD, buf[buf1].data.fadr.hc_fnode.index[1],NOT_ONLY_SEARCH);
                      buf[buf1].data.fadr.dir[i]  = buf[buf3].data.data.dir[ct_links - CT_DIR_FNODE  -  CT_DIR_NO_FNODE  +1 ] ;
                      buf[buf1].data.fadr.hc_fnode.ct_links--;
                      if ( buf[buf1].data.fadr.hc_fnode.ct_links  <=  CT_DIR_FNODE + CT_DIR_NO_FNODE  -2 ){
                              free_node( buf[buf1].data.fadr.hc_fnode.index[1] , FDD);
                              buf[buf1].data.fadr.hc_fnode.index[1] = NO_LBA ;
                      }
                      buf[buf1].status=DIRTY;
                      put_block(buf1 , NOT_FRONT);
                      put_block(buf3 , NOT_FRONT);
                      return 1;
                 }else
                      return 0;
            }
            buf2 =  get_block(FDD, buf[buf1].data.fadr.hc_fnode.index[0],NOT_ONLY_SEARCH);
            for(i=0; i <=CT_DIR_NO_FNODE -1 ;i++)
               if(buf[buf2].data.fadr.dir[i].hash == hashid)
                   if( !strcmp((char *)string , (char *)buf[buf2].data.fadr.dir[i].name))  /*exact match found*/
                      break;
            if( i  <  CT_DIR_NO_FNODE){
                    if(flag ==  LOOK_UP){
                        *slba=buf[buf2].data.fadr.dir[i].lba;
                        put_block(buf1,NOT_FRONT);
                        put_block(buf2,NOT_FRONT);
                        return CT_DIR_FNODE+i;
                    }
                    if(flag == ENTER){
                        ERROR_NO = ALREADY_PRESENT;
                        put_block(buf1,NOT_FRONT);
                        put_block(buf2,NOT_FRONT);
                        handle_error();
                        return 0;
                    }
                    if(flag ==  DELETE){
                        buf3=get_block(FDD  ,  buf[buf1].data.fadr.hc_fnode.index[1]  ,  NOT_ONLY_SEARCH);
                        buf[buf2].data.fadr.dir[i]  = buf[buf3].data.data.dir[ct_links - CT_DIR_FNODE  -  CT_DIR_NO_FNODE  +1 ] ;
                        buf[buf1].data.fadr.hc_fnode.ct_links--;
                        if ( buf[buf1].data.fadr.hc_fnode.ct_links  <=  CT_DIR_FNODE + CT_DIR_NO_FNODE  -2 ){
                            free_node( buf[buf1].data.fadr.hc_fnode.index[1] , FDD);
                            buf[buf1].data.fadr.hc_fnode.index[1] = NO_LBA ;
                        }
                        buf[buf1].status=DIRTY;
                        buf[buf2].status=DIRTY;
                        put_block(buf1 , NOT_FRONT);
                        put_block(buf2 , NOT_FRONT);
                        put_block(buf3 , NOT_FRONT);
                        return 1;
                    }
            }else{
                put_block(buf2  ,  NOT_FRONT);
            }
            buf3=get_block(FDD, buf[buf1].data.fadr.hc_fnode.index[1],NOT_ONLY_SEARCH);
            temp =  ct_links - CT_DIR_FNODE -  CT_DIR_NO_FNODE  +1 ;   /*there are 0 to temp entries in second index*/
             for(i=0 ;  i <=temp;  i++)
                    if(buf[buf3].data.data.dir[i].hash == hashid)
                            if( !strcmp((char *)string , (char *)buf[buf3].data.data.dir[i].name))  /*exact match found*/
                                    break;
            if(i  <=  temp){
                    if(flag  ==  LOOK_UP){
                            *slba=buf[buf1].data.fadr.dir[i].lba;
                            put_block(buf1,NOT_FRONT);
                            put_block(buf3,NOT_FRONT);
                            return CT_DIR_FNODE + CT_DIR_NO_FNODE + i;
                    }
                    if(flag  ==  ENTER){
                             ERROR_NO = ALREADY_PRESENT;
                            put_block(buf1 ,NOT_FRONT);
                            put_block(buf3 ,NOT_FRONT);
                            handle_error();
                            return 0;
                    }
                    if(flag  ==  DELETE){
                            buf[buf1].data.fadr.hc_fnode.ct_links--;
                            buf[buf1].status=DIRTY;
                            if(i  !=  temp){
                                    buf[buf3].data.fadr.dir[i]  = buf[buf3].data.data.dir[temp ]  ;
                                    buf[buf3].status=DIRTY;
                            }
                            if ( buf[buf1].data.fadr.hc_fnode.ct_links  <=  CT_DIR_FNODE + CT_DIR_NO_FNODE  -2 ){
                                    free_node( buf[buf1].data.fadr.hc_fnode.index[1] , FDD);
                                    buf[buf1].data.fadr.hc_fnode.index[1] = NO_LBA ;
                                    buf[buf1].status=DIRTY;
                            }
                            put_block(buf1,NOT_FRONT);
                            put_block(buf3,NOT_FRONT);
                            return 1;
                    }else
                            return 0;
            }else{
                    if(flag  ==  LOOK_UP){
                        *slba=NO_LBA;
                        put_block(buf1,NOT_FRONT);
                        put_block(buf3,NOT_FRONT);
                        return 0;
                    }
                    if(flag  ==  DELETE){
                        put_block(buf1,NOT_FRONT);
                        put_block(buf3,NOT_FRONT);
                        ERROR_NO=NO_DIR_FILE;
                        handle_error();
                        return 0;
                    }
                    if(flag  ==  ENTER){
                         buf[buf1].data.fadr.hc_fnode.ct_links++;
                         buf[buf1].status=DIRTY;
                         buf[buf3].data.data.dir[temp+1].hash  =  hashid;
                         buf[buf3].data.data.dir[temp+1].lba     =  *slba;
                         strcpy ( (char *)buf[buf2].data.data.dir[temp+1].name  , (char *)string  ) ;
                         buf[buf3].status=DIRTY;
                         put_block(buf1,NOT_FRONT);
                         put_block(buf3,NOT_FRONT);
                         return 1;
                    }else
                         return 0;
            }
    }

}
