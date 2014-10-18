//Student class declaration and definition

class student{
  private:
    // All the fields of the file
    char name[20],reg[15],addr[45],sem[2],branch[30];
  public:
    student(const char *n=NULL,const char *r=NULL,const char *a=NULL,const char *s=NULL,const char *b=NULL);
    char *getreg();
    void show();
    void pack(char *buf);
    void unpack(const char *buf);
    friend class interface;
    friend class sequence_set;
    friend class bplus;
    friend class vlbuff;
};

//Default constructor
student :: student(const char *n,const char *r,const char *a,const char *s,const char *b){
  strcpy(name,n);
  strcpy(reg,r);
  strcpy(addr,a);
  strcpy(sem,s);
  strcpy(branch,b);
}

//Function to return the register number
char * student :: getreg(){
  char *rno;
  strcpy(rno,reg);
  rno[strlen(reg)]='\0';
  return rno;
}

//Function to pack all the fields with required delimiters into the buffer
void student :: pack(char *buf){
  int dum,noc=strlen(name)+strlen(reg)+strlen(addr)+strlen(sem)+strlen(branch)+4;
  int j=2;
  dum=noc;
  buf[0]='1';
  buf[1]='|';
  // To store integer noc as character
  while(noc>0){
    int i=noc/10;
    if(i!=0){
      noc-=i*10;
      buf[j++]=i+'0';
    }
    else{
      buf[j++]=noc+'0';
      noc=0;
    }
  }
  if(j==3 && dum>=10) buf[j++]='0';
  buf[j++]='|'; // field delimiter
  for(int i=0;reg[i]!='\0';i++) buf[j++]=reg[i];
  buf[j++]='|';
  for(i=0;name[i]!='\0';i++) buf[j++]=name[i];
  buf[j++]='|';
  for(i=0;addr[i]!='\0';i++) buf[j++]=addr[i];
  buf[j++]='|';
  for(i=0;sem[i]!='\0';i++) buf[j++]=sem[i];
  buf[j++]='|';
  for(i=0;branch[i]!='\0';i++) buf[j++]=branch[i];
  buf[j++]='\n';//record delimiter
  buf[j]='\0';
}

//Function to extract fields from the buffer
void student :: unpack(const char *buf){
  int count=0;
  for(int j=0;count!=2;j++)
    if(buf[j]=='|') count++;
  for(int i=0;buf[j]!='|';i++)
    reg[i]=buf[j++];
  j++;
  reg[i]='\0';
  for(i=0;buf[j]!='|';i++)
    name[i]=buf[j++];
  j++;
  name[i]='\0';
  for(i=0;buf[j]!='|';i++)
    addr[i]=buf[j++];
  addr[i]='\0';
  j++;
  for(i=0;buf[j]!='|';i++)
    sem[i]=buf[j++];
  sem[i]='\0';
  j++;
  for(i=0;buf[j]!='\0';i++)
    branch[i]=buf[j++];
  branch[i]='\0';
}

//Function to display all the details pertaining to a student graphically
void student :: show(){
  int p=0,q=0,r=getmaxx(),s=getmaxy();
  setcolor(RED);
  int mx=getmaxx();
  rectangle(mx/2-200,140,mx/2+180,340);
  setfillstyle(0,3);
  floodfill(mx/2,200,RED);
  setcolor(YELLOW);
  outtextxy(mx/2-180,160,"Name     : ");
  outtextxy(mx/2-180,200,"Reg.No   : ");
  outtextxy(mx/2-180,240,"Address  : ");
  outtextxy(mx/2-180,280,"Semester : ");
  outtextxy(mx/2-180,320,"Branch   : ");
  setcolor(WHITE);
  rectangle(mx/2-80,155,mx/2 + 50 ,170);
  rectangle(mx/2-80,195,mx/2 + 50 ,210);
  rectangle(mx/2-80,235,mx/2 + 50 ,250);
  rectangle(mx/2-80,275,mx/2 + 50 ,290);
  rectangle(mx/2-80,315,mx/2 + 50 ,330);
  setcolor(LIGHTCYAN);
  outtextxy(mx/2-75,160,name);
  outtextxy(mx/2-75,200,reg);
  outtextxy(mx/2-75,240,addr);
  outtextxy(mx/2-75,280,sem);
  outtextxy(mx/2-75,320,branch);
}