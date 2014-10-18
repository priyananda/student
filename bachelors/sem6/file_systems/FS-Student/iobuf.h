//Base class which contains the virtual functions
class IOBuffer{
  protected:
	char *buf; // Buffer
  public:
	virtual int write(ostream &,student & s)=0;
	virtual int read(istream &)=0;
};

//Variable lengthe delimited buffer class derived from iobuffer
class vlbuff : public IOBuffer{
  private:
	char fdlim; // Field delimiter
	char rdlim; // Record delimiter
	fstream stream; // Logical name of the file stream
  public:
	vlbuff(char fd='|',char rd='\n');
	~vlbuff();
	int add(const char *,student &);
	int del(int ch,char *value,student &);
	int read(istream &);
	int dread(const int addr,char *b);
	int write(ostream & ,student &);
	int recover(const char *,student &);
	int search(int ,const char *,student &);
	int displayall(student &);
	int update();
	friend class interface;
};

//Constructor
vlbuff :: vlbuff(char fd,char rd){
  fdlim=fd;
  rdlim=rd;
  buf=new char[100]; // Dynamic allocation
  buf[0]='\0';
}

//Destructor
vlbuff :: ~vlbuff(){
  delete [] buf;
}

int vlbuff :: dread(const int addr,char *b){
  int flag=0;
  stream.open("db.txt",ios::in);
  stream.seekg(addr,ios::beg);
  if(!stream.fail()){ // if the file is seeked successfully
	stream.getline(b,100,'\n'); // extract a record into b
	int n=strlen(b);
	if(n!=0){
	  b[n]='\0';
	  flag=1; // Successfully read
	}
  }
  stream.close();
  return flag;
}

//Function to display all the records
int vlbuff :: displayall(student & s){
  int flag=0;
  stream.open("db.txt",ios::in);
  if(stream.fail()) return 0;
  while(!(stream.eof())){  // Till the end of file is encountered
	if(read(stream)){
	  if(buf[0]=='1'){
        flag=1;
        s.unpack(buf); // unpack the contents of buffer into student object
        s.show(); // Display the student details
        getch();
	  }
	}
  }
  stream.close();
  return flag;
}

//Function to recover temporarily deleted record
int vlbuff :: recover(const char *value,student & s){
  int flag=0,point=0;
  char r[20];
  stream.open("db.txt",ios::in|ios::out);
  stream.seekg(0,ios::beg);
  while(!stream.eof()){ // Until the end of file
	if(read(stream)){
	  if(buf[0]=='0'){ // If the record is temporarily deleted
	int count=0;
	for(int i=0;count!=2;i++)
	  if(buf[i]=='|') count++;
	for(int j=0;buf[i]!='|';j++)
	  r[j]=buf[i++];
	r[j]='\0';
	if(strcmp(r,value)==0){ // If the match is found
	  flag=1;
	  break;
	}
	  }
	}
	point+=strlen(buf)+2;
  }
  stream.clear();
  if(flag){
	stream.seekp(point,ios::beg);
	stream << '1'; // To make the record valid or to mark that the record is recovered
	if(!stream.fail()){
	  s.unpack(buf); // Unpack the buffer into student object
	  s.show(); // Display student details
	}
  }
  stream.close();
  return(flag);
}

//Function to remove all temporarily deleted records permanently
int vlbuff :: update(){
  int nor=0;
  stream.open("db.txt",ios::in|ios::out);
  if(stream.fail())
	return 0;
  fstream io("temp.txt",ios::out|ios::in|ios::trunc);
  while(!stream.eof()){
	if(read(stream)){
	  if(buf[0]=='1'){  // If the record is valid write it to the intermediate file
	io << buf;
	io << '\n';
	  }
	}
  }
  stream.close();
  stream.open("db.txt",ios::out|ios::trunc);
  io.seekg(0,ios::beg);
  while(!io.eof()){ // To copy back the contents to the original file
	if(read(io)){
	stream << buf;
	stream << '\n';
	nor++;
	}
  }
  stream.close();
  io.close();
  return nor;
}

//Function to read a record into the buffer
int vlbuff :: read(istream & stream){
  strcpy(buf,"");
  stream.getline(buf,75,'\n');
  buf[strlen(buf)]='\0';
  if(stream.fail())
	return 0; // Unsuccessful read
  else
	return 1; // Successful
}

//Function to delete record(s)
int vlbuff :: del(int ch,char *value,student & s){
  int flag=0,point=0,status=ch;
  char res;
  stream.open("db.txt",ios::in|ios::out);
  if(stream.fail())
	return 0;
  if(status==3)
	ch=2;
  switch(ch){
	// To delete based on name
	case 1: char na[20];
		// If desired all records with the same name are deleted
		while(!stream.eof()){
		  stream.seekg(point,ios::beg);
		  if(!read(stream))
			  break;
		  if(buf[0]=='1'){ // If the record is valid
			int j,count=0;
			for(int i=0;count!=3;i++)
			  if(buf[i]=='|') count++;
			  for(j=0;buf[i]!='|';j++)
				  na[j]=buf[i++];
			  na[j]='\0';
			  if((strcmp(na,value))==0){ // if there is a match
				  flag=1;
				  s.unpack(buf);
				  s.show();
				  setcolor(RED);
				  //Confirmation of deletion
				  outtextxy(120,380,"Would you like to delete the above shown record");
                  gotoxy(20,50);
				  cin >> res;
				  setcolor(BLACK);
				  outtextxy(120,380,"Would you like to delete the above shown record");
				  if(res=='y'){
					stream.seekp(0,ios::beg);        // Deletion confirmed
					stream.seekp(point);
					if(!stream.fail()){ // After successful seek
					  setcolor(RED);
					  cout << stream.tellp()<<endl;
					  stream.put((char)'0'); // Make the record invalid
					  outtextxy(120,380,"The record shown above is deleted");
					  getch();
					  setcolor(BLACK);
					  outtextxy(120,380,"The record shown above is deleted");
					}
				  }
			   }
		  }
		  point+=strlen(buf)+2;
		}
		break;
	// Deletion based on reg.no
	case 2: char re[20];
		while(!stream.eof()){         // Till the end of file is encountered
		  if(read(stream)){
		if(buf[0]=='1'){
		  int j,count=0;
		  for(int i=0;count!=2;i++)
			if(buf[i]=='|') count++;
		  for(j=0;buf[i]!='|';j++)
			re[j]=buf[i++];
		  re[j]='\0';
		  if((strcmp(re,value))==0){ // If the desired record is found
			flag=1;
			break;
		  }
		}
		  }
		  point+=strlen(buf)+2;
		}
		stream.clear();
		if(flag){
		  s.unpack(buf);
          stream.seekp(0,ios::beg);
		  stream.seekp(point);
		  if(!stream.fail()){
                stream << '0'; // Make the record invalid
                if (status != 3)s.show();
                if(status==3){
                    stream.close();
                    return flag;
                }
                setcolor(RED);
                outtextxy(120,380,"The record shown above is deleted");
		  }
		}
		break;
  };
  stream.flush();
  stream.close();
  return flag;
}

//Function to search record(s)
int vlbuff :: search(int ch,const char *value,student & s){
  int flag=0;
  stream.open("db.txt",ios::in);
  stream.seekg(0,ios::beg);
  if(stream.fail()){
	cout << "\nThe file is empty!!!\n";
	return 0;
  }
  switch(ch){
	// Search based on name
	case 1: char na[20],c;
		int i=0;
		while(!stream.eof()){
		  if(!read(stream))
		break;
		  if(buf[0]=='1'){
		int j,count=0;
		for(int i=0;count!=3;i++)
		  if(buf[i]=='|') count++;
		for(j=0;buf[i]!='|';j++)
		  na[j]=buf[i++];
		na[j]='\0';
		if((strcmp(na,value))==0){ // If the desired record is found
		  flag=1;
		  s.unpack(buf);
		  s.show();
		  getch();
		}
		  }
		}
		break;
	//Search based on reg.no
	case 2: char re[20];
		while(!stream.eof()){
		  if(read(stream)){
		if(buf[0]=='1'){
		  int j,count=0;
		  for(int i=0;count!=2;i++)
			if(buf[i]=='|') count++;
		  for(j=0;buf[i]!='|';j++)
			re[j]=buf[i++];
		  re[j]='\0';
		  if((strcmp(re,value))==0){ // If the desired record is found
			flag=1;
			break;
		  }
		}
		  }
		}
		stream.clear();
		if(flag){
		  s.unpack(buf);
		  setcolor(BLACK);
		  setfillstyle(1,BLACK);
		  rectangle(0,0,getmaxx(),getmaxy());
		  floodfill(1,1,BLACK);
		  for(int i=10;i<80;i+=10)
		  { setcolor(i+4);
		circle(getmaxx()/2,getmaxy()/2,i);
		sound(5*i);
		delay(300);
		nosound();
		  }
		  int x,d,y,x1,p,q,r,t,l,m,n,o;
		  d=getmaxx()/2;
		  y=getmaxy()/2;
		  x=100;
		  x1=0;
		  setlinestyle(0,1,2);
		  while(x<=d) {
		x+=5;
		x1+=5;
		p=x-10;
		q=y-10;
		r=x;
		t=y;
		l=x-10;
		m=y+10;
		n=x;
		o=y;
		setcolor(WHITE);
		line(x,y,x1,y);
		line(p,q,r,t);
		line(l,m,n,o);
		delay(50);
		setcolor(BLACK);
		line(x,y,x1,y);
		line(p,q,r,t);
		line(l,m,n,o);
		  }
		  setcolor(WHITE);
		  line(x,y,x1,y);
		  line(p,q,r,t);
		  line(l,m,n,o);
		  getch();
		  s.show();
		}
		break;
  };
  stream.close();
  update();
  return flag;
}

//Function to append a new record
int vlbuff :: add(const char *reg,student & s){
  if(!((s.sem[0]=='1'||s.sem[0]=='2'||s.sem[0]=='3'||s.sem[0]=='4'||s.sem[0]=='5'||s.sem[0]=='6'||s.sem[0]=='7'||s.sem[0]=='8')&&s.sem[1]=='\0'))
	return -1;
  stream.open("db.txt",ios::in|ios::out);
  int flag=0,addr=-1;
  char len[4],cno[20],dbuf[75],fbit[3];
  stream.seekg(0,ios::beg);
  while(!stream.eof()){ // Search if any record by the same reg.no is already present
	 stream.getline(fbit,3,'|');
	 if((strcmp(fbit,"0"))!=0){
	   stream.getline(len,4,'|');
	   if(!stream.good())
	 break;
	   stream.getline(cno,20,'|');
	   if((strcmp(cno,reg))==0){
	 flag=1;
	 break;
	   }
	   stream.getline(dbuf,75,'\n');
	 }
	 else
	   stream.getline(dbuf,75,'\n');
  }
  stream.clear();
  if(!flag){ // Duplicate record is not found
	stream.seekp(0,ios::end);
	addr=stream.tellp();
	if(!write(stream,s)) // Append the valid record
	  addr=-1;
  }
  stream.close();
  return addr;
}

//Function to write a record in to the file
int vlbuff :: write(ostream & stream,student & s){
  s.pack(buf); // Pack the student details into the buffer
  stream << buf;
  if(stream.fail())
	return 0;
  return 1;
}