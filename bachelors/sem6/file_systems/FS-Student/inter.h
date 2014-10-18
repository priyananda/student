// Class to handle the graphical interface of both part1 and part2
class interface{
  private:
	student s;
	vlbuff v;
	char mesg[100];
	int mx,my;
  public:
	interface();
	int acceptchoice(char *value);
	void animate();
	student getstudent();
	int add();
	void accept();
	int del();
	void search();
	int update();
	void recover();
	void assign();
	int modify();
	void displayall();
};

// Constructor
interface :: interface(){
  mx=getmaxx();
  my=getmaxy();
}

// Function to return the student object
student interface :: getstudent(){
  return s;
}

// Function to remove the temporarily deleted records and update the new data file
int interface :: update(){
  return v.update();
}

// Function to display all the records in the data file
void interface :: displayall(){
  setcolor(BLACK);
  cleardevice();
  setcolor(2);
  settextstyle(1,0,2);
  outtextxy(mx/2-120,20,"Displaying  All the records");
  settextstyle(0,0,0);
  if(!v.displayall(s)){
    strcpy(mesg,"The file is Empty!!!");
    animate();
	getch();
  }
}

// Function to modify an existing record
int interface :: modify(){
    int flag=1;
    int i,coy=52;
    char value[20];
    student d , s;;

    setcolor(BLACK);
    cleardevice();
    setcolor(2);
    settextstyle(1,0,2);
    outtextxy(0,10,"+---------------------------------------------------------------------------------+");
    outtextxy(0,20,"|                          Modify an existing record                              |" );
    outtextxy(0,30,"+---------------------------------------------------------------------------------+");
    settextstyle(0,0,0);
    gotoxy(1,5);
    setcolor(LIGHTCYAN);

    cout << "Enter the Register Number of the Record : ";
    cin >> value;
    int ok=v.del(3,value,d);
    v.update();
    if(!ok){
        strcpy(mesg,"No such record exists");
        animate();
        mesg[0] = 0;
        getch();
        return 0;
    }
    strcpy(s.reg,d.reg);
    setcolor(WHITE);
    cout << "Old value of name : " << d.name << endl;
    cout << "New value of name : "; 
    gets(s.name);
    if(!strlen(s.name)) strcpy(s.name,d.name);
    cout << "---------------------------------------------------------------------------"<<endl;
    cout << "Old value of Address : " << d.addr << endl;
    cout << "New value of Address : "; 
    gets(s.addr);
    if(!strlen(s.addr)) strcpy(s.addr,d.addr);
    cout << "---------------------------------------------------------------------------"<<endl;
    cout << "Old value of Sem  : " << d.sem << endl;
    cout << "New value of name : "; 
    gets(s.sem);
    if(!strlen(s.sem)) strcpy(s.sem,d.sem);
    cout << "---------------------------------------------------------------------------"<<endl;
    cout << "Old value of Branch : " << d.branch << endl;
    cout << "New value of Branch : "; 
    gets(s.branch);
    if(!strlen(s.branch)) strcpy(s.branch,d.branch);
    cout << "---------------------------------------------------------------------------"<<endl;
    if(v.add(s.reg,s)==-1){
        strcpy(mesg,"Duplicate Record! Hence not modified");
        v.recover(d.reg,s);
        flag=0;
    }
    else
        strcpy(mesg,"The Record has been Modified");
    v.update();
    animate();
    getch();
    return flag;
}

// Function to assign a new record from an existing record
void interface :: assign(){
  clrscr();
  setcolor(BLACK);
  setfillstyle(1,BLACK);
  rectangle(0,0,mx,my);
  floodfill(1,1,BLACK);
  setcolor(2);
  settextstyle(0,0,2);
  outtextxy(mx/2-70,20,"ASSIGNMENT");
  settextstyle(0,0,0);
  cout << endl << endl << endl;
  int i,coy=52;
  char value[20];
  for(i=0;i<60;i++)
	 cout << ' ';
  setcolor(LIGHTCYAN);
  outtextxy(10,coy,"Enter the Reg.No from which new record is to be assigned ");
  cin >> value;
  coy+=32;
  student d;
  int ok=v.search(2,value,d);
  if(!ok){
	strcpy(mesg,"No such record exists");
	animate();
	return;
  }
  getch();
  setcolor(WHITE);
  setfillstyle(1,BLACK);
  rectangle(50,90,mx-50,my-90);
  floodfill(mx/2,my/2,WHITE);
  setcolor(BLACK);
  rectangle(50,90,mx-50,my-90);
  setcolor(LIGHTGREEN);
  char ch,c;
  cout << '\n';
  for(i=0;i<60;i++)
	cout << ' ';
  outtextxy(50,coy,"Would you like to assign Name ? ");
  coy+=32;
  cin >> ch;
  if(ch=='n'){
	cout << endl;
	for(i=0;i<20;i++)
	  cout << ' ';
	outtextxy(50,coy,"Name    : ");
	coy+=32;
	i=0;
	c=getchar();
	while(c!='\n'){
	  s.name[i++]=c;
	  c=getchar();
	}
	s.name[i]='\0';
  }
  else
	strcpy(s.name,d.name);
  cout << endl;
  for(i=0;i<20;i++)
	cout << ' ';
  outtextxy(50,coy,"Reg.No   :");
  cin >> s.reg;
  coy+=32;
  cout << endl;
  for(i=0;i<60;i++)
	cout << ' ';
  outtextxy(50,coy,"Would you like to assign Address ? ");
  cin >> ch;
  coy+=32;
  if(ch=='n'){
	cout << endl;
	for(i=0;i<20;i++)
	  cout << ' ';
	outtextxy(50,coy,"Address    : ");
	coy+=32;
	i=0;
	c=getchar();
	while(c!='\n'){
	  s.addr[i++]=c;
	  c=getchar();
	}
	s.addr[i]='\0';
  }
  else
	strcpy(s.addr,d.addr);
  cout << endl;
  for(i=0;i<60;i++)
	cout << ' ';
  outtextxy(50,coy,"Would you like to assign Semester ? ");
  cin >> ch;
  coy+=32;
  if(ch=='n'){
	cout << endl;
	for(i=0;i<20;i++)
	  cout << ' ';
	outtextxy(50,coy,"Semester   : ");
	coy+=32;
	cin >> s.sem;
  }
  else
	strcpy(s.sem,d.sem);
  cout << endl;
  for(i=0;i<60;i++)
	cout << ' ';
  outtextxy(50,coy,"Would you like to assign Branch ? ");
  cin >> ch;
  coy+=32;
  if(ch=='n'){
	cout << endl;
	for(i=0;i<20;i++)
	  cout << ' ';
	outtextxy(50,coy,"Branch    : ");
	coy+=32;
	i=0;
	c=getchar();
	while(c!='\n'){
	  s.branch[i++]=c;
	  c=getchar();
	}
	s.branch[i]='\0';
  }
  else
	strcpy(s.branch,d.branch);
  if(v.add(s.reg,s)==-1)
	strcpy(mesg,"Duplicate Record");
  else
	strcpy(mesg,"The Record has been assigned");
  animate();
  getch();
}

// Function to recover the temporarily deleted record
void interface :: recover(){
  clrscr();
  setcolor(BLACK);
  setfillstyle(1,BLACK);
  rectangle(0,0,mx,my);
  floodfill(1,1,BLACK);
  setcolor(2);
  settextstyle(0,0,2);
  outtextxy(mx/2-40,20,"RECOVERY");
  settextstyle(0,0,0);
  for(int i=0;i<6;i++)
	cout << '\n';
  setcolor(LIGHTCYAN);
  cout << endl;
  for(i=0;i<25;i++)
	cout << ' ';
  outtextxy(50,115,"Enter the Reg.No : ");
  char value[20];
  cin >> value;
  int ok=v.recover(value,s);
  if(ok){
	getch();
	strcpy(mesg,"The record shown has been recovered");
  }
  else
	strcpy(mesg,"No such record exists or No such record is deleted");
  animate();
  getch();
}

// Function to accept one of two choices
int interface :: acceptchoice(char *value){
    char c;
    int ch,i=0;
    setcolor(WHITE);
    gotoxy(1,4);
    cout << "Please choose the manner for finding the record :" << endl;
    cout << "1. By Name"<<endl;
    cout << "2. By Reg.No"<<endl;
    cout <<"Enter your choice : ";
    cin >> ch;
    switch(ch){
        case 1: 
            cout <<"Enter Name : ";
            gets(value);
            break;
        case 2:
            cout <<"Enter the Reg.No : ";
            gets( value );
            break;
        default:
            strcpy(mesg,"OOPS. WRONG ENTRY!!!");
    };
    if(ch==1)
        return 1;
    if(ch==2)
        return 2;
    return 0;
}

// Function to delete records based on key or name
int interface :: del(){
    setcolor(BLACK);
    cleardevice();
    setcolor(2);
    settextstyle(1,0,2);
    outtextxy(0,10,"+---------------------------------------------------------------------------------+");
    outtextxy(0,20,"|                          Delete an existing record                              |" );
    outtextxy(0,30,"+---------------------------------------------------------------------------------+");
    settextstyle(0,0,0);
    char value[20];
    int flag=0,ok=acceptchoice(value);
    if(ok){
        if(!(v.del(ok,value,s))){
          strcpy(mesg,"No such record exists");
          flag=1;
        }
    }
    if(flag||!ok)
        animate();
    getch();
    return !flag;
}

// Linear searching of records based on key or name
void interface :: search(){
  clrscr();
  setcolor(BLACK);
  setfillstyle(1,BLACK);
  rectangle(0,0,mx,my);
  floodfill(1,1,BLACK);
  setcolor(2);
  settextstyle(0,0,2);
  outtextxy(mx/2-40,20,"SEARCH");
  settextstyle(0,0,0);
  char value[20];
  int flag=0,ok=acceptchoice(value);
  if(ok){
	if(!(v.search(ok,value,s))){
	  strcpy(mesg,"The search is unsuccessful");
	  flag=1;
	}
  }
  if(flag||!ok)
	animate();
  getch();
}

// Function to show the animated message
void interface :: animate(){
  int len=strlen(mesg);
  mesg[len]='\0';
  setcolor(BLACK);
  cleardevice();
  setcolor(WHITE);
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  rectangle(148,148,452,302);
  bar(150,150,450,300);
  setfillstyle(SOLID_FILL,BLUE);
  rectangle(168,138,432,162);
  bar(170,140,430,160);
  settextstyle(1,0,2);
  setcolor(BLACK);
  outtextxy(290-8*len/2,my/2 - 20 ,mesg);
}

// Function to handle the insertion of new record
int interface :: add(){
  accept();
  int flag=0,addr;
  if((addr=v.add(s.getreg(),s))!=-1)
	flag=1;
  if(flag)
	strcpy(mesg,"The record has been added");
  else
	strcpy(mesg,"Record discarded");
  animate();
  getch();
  return addr;
}

// Function to accept the student details
void interface :: accept(){
  setcolor(BLACK);
  cleardevice();
  int x=mx/2-150;
  setcolor(WHITE);
  rectangle(x-30,50,x + 300 , 250);
  rectangle(x-10,40,x + 280 , 60);
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(x-8,42,x + 278 , 58);
  settextstyle(1,0,2);
  setcolor(BLACK);
  outtextxy(x+100 ,45,"ADDITION");
  settextstyle(0,0,0);
  setcolor(YELLOW);
  outtextxy(x,84 ,"Name         : ");
  outtextxy(x,116,"Reg.         : ");
  outtextxy(x,148,"Address      : ");
  outtextxy(x,180,"Semester     : ");
  outtextxy(x,212,"Branch       : ");
  double cox=ceil(x/8)+17,coy=4+1;
  gotoxy(40,6);
  char c;
  int i=0;
  gets(s.name);
  gotoxy(40,8);
  gets(s.reg);
  gotoxy(40,10);
  gets(s.addr);
  gotoxy(40,12);
  gets(s.sem);
  gotoxy(40,14);
  gets(s.branch);
}
