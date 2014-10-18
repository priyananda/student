-- @document : insert.sql
-- @author   : shenoy
-- @date     : 1 May 2003
-- @comments : Creates all the tables
-- @todo     : make all primary keys auto-generating


delete subject;
insert into subject values ( 'sb0001' , 'Java' ,'Introduction Java' );
insert into subject values ( 'sb0002' , 'vb' ,'Introduction to MS VB 6' );
insert into subject values ( 'sb0003' , 'C#' ,'The great language of the future' );
insert into subject values ( 'sb0004' , 'vb.net' ,'.NET VB development' );
insert into subject values ( 'sb0005' , 'Linux Admin' ,'Linux System Admin' );
insert into subject values ( 'sb0006' , 'PHP' ,'PHP language' );
insert into subject values ( 'sb0007' , 'Jini' ,'Java Jini Technology' );

delete Course;
insert into course values ( 'cr0001','RHCE','RedHa t Certification Examination',1
);

insert into course values ( 'cr0002','MCSE','Microsoft Certified Software Enginner',1
);

insert into course values ( 'cr0003','SCP','Sun Certified Programmer',1
);

delete CourseSubject;
insert into CourseSubject values('cr0001','sb0005');
insert into CourseSubject values('cr0001','sb0006');
insert into CourseSubject values('cr0002','sb0002');
insert into CourseSubject values('cr0002','sb0003');
insert into CourseSubject values('cr0002','sb0004');
insert into CourseSubject values('cr0003','sb0001');
insert into CourseSubject values('cr0003','sb0007');


delete Student;
insert into Student values('st0001' , 'Naveen Bean','11-may-90','cr0002','Hell', 'bean@ssit.org' ,0, 'bakra' , 'Nothing' , '0' 
);	

insert into Student values('st0002' , 'Frodo Baggins','12-may-90','cr0001','Hobiton' , 'frodo@lotr.org' ,0, 'ring' , 'likes elves' , '00-110' 
);

insert into Student values('st0003' , 'Baba Btree','12-may-82','cr0003','Lido' , 'baba@btree.org' , 0,'battery' , 'Rajanikanth Style' , 'ab' 
);

delete admin_pass;
insert into admin_pass values('admin');

delete Lecturer;
insert into Lecturer values('lc0001' , 'Ram Reddy' , '11-jun-1952' , 'sb0005','Faith Hill','a@b.com','abcd','00-10');
insert into Lecturer values('lc0002' , 'Krihna MKS' , '12-oct-1967' , 'sb0001','Bombay Hill','aca@bbv.com','hello','010-10');

delete Question;
insert into Question values( 'sb0002','Who invented VB  ','Microsoft','Sub','IBM','None of the above' ,1,1);
insert into Question values( 'sb0002','What is VB  ','Language','Game','Word Processor','Editor' ,1,1);
insert into Question values( 'sb0002','What are the base of VB delvelopment','ActiveX','COM','DOM','JVM' ,1,1);
insert into Question values( 'sb0002','Why Vb is powerfull','Cheap','RAD','Easy','Builtin classes' ,1,2);
insert into Question values( 'sb0002','Expand VB','Visual basic','Visual Builder','View Builder','None' ,1,1);
insert into Question values( 'sb0002','Where do you add VB controls','VC++ only','VB only','Both','None' ,1,3);
insert into Question values( 'sb0002','Looping in Vb is done using','While','Goto','if','None' ,1,1);
insert into Question values( 'sb0002','Current Version of VB','6','7','8','2' ,1,2);
insert into Question values( 'sb0002','Platform DLL for VB','MSVB60','MSVCRT','vb6','None' ,1,4);
insert into Question values( 'sb0002','what is ActiveX ','Language','Standard','IDE','Game Engine' ,1,2);
insert into Question values( 'sb0002','Extension of ActiveX file is','ocj','ocx','java','vbp' ,1,2);
insert into Question values( 'sb0002','ActiveX  parent is','COM','VB','OLE','DCOM' ,1,3);
insert into Question values( 'sb0002','how do you add ActiveX Controls in VB','Using Toolbar','Using Menu','Both','None' ,1,2);
insert into Question values( 'sb0002','The company which created COM','MS','Sun','IBM','None' ,1,1);
insert into Question values( 'sb0002','What is COM','Standard','Language','Model','None' ,1,3);
insert into Question values( 'sb0002','COM came from','ActiveX','OLE','OOP','None' ,1,2);
insert into Question values( 'sb0002','COM successor ','BCOM','DCOM','COM+','COM++' ,1,2);
insert into Question values( 'sb0002','WHo created IIS','MS','Sun','IBM','None' ,1,1);
insert into Question values( 'sb0002','IIS is a ','Portal','Web Server','App Server','None' ,1,2);
insert into Question values( 'sb0002','IIS Controls are','ActiveX','Java','VB','VC++' ,1,1);
insert into Question values( 'sb0002','IIS Container is','IISContainer','IUnknown','Both','None' ,1,2);

insert into Question values( 'sb0001','What is Java','Language','Standard','IDE','Game Engine',1,1);
insert into Question values( 'sb0001','Who created Java','MS','Sun','IBM','None' ,1,2);
insert into Question values( 'sb0001','CurrentVersion of JAVA','1','2','4','3' ,1,2);
insert into Question values( 'sb0001','What is JDK','Language','Standard','IDE','none' ,1,4);
insert into Question values( 'sb0001','CurrentVersion of JDK','1.4','1.3','9.0','1.1' ,1,2);

insert into Question values( 'sb0001','What is superclass of all classes','Object','Applet','Socket','None' ,1,1);
insert into Question values( 'sb0001','Serializable is a ','Interface','Class','variable','None' ,1,1);
insert into Question values( 'sb0001','Package containing String is','lang','net','io','None' ,1,1);
insert into Question values( 'sb0001','Swing is in __ package','java','javax','both','None' ,1,2);
insert into Question values( 'sb0001','AWT is a ','Interface','windowing kit','Class','None' ,1,2);

insert into Question values( 'sb0001','javax package contains','networking','Swing','I/O','AWT' ,1,2);
insert into Question values( 'sb0001','Exception are caught in __ block','catch','try','finally','None' ,1,2);
insert into Question values( 'sb0001','Java 2D is','Version of Java','Graphics Library','Both','None' ,1,2);
insert into Question values( 'sb0001','RMI is ','Class','Interface','variable','None' ,1,2);
insert into Question values( 'sb0001','Socket class is in __ package','lang','net','io','None' ,1,2);

insert into Question values( 'sb0001','JDBC deals with','I/O','databases','Networking','None' ,1,2);
insert into Question values( 'sb0001','JComponent is in','swing','awt','net','None' ,1,1);
insert into Question values( 'sb0001','paint() is in ','Component','JComponent','Container','None' ,1,1);
insert into Question values( 'sb0001','init() is start-up for','Applet','Frame','JFrame','None' ,1,1);
insert into Question values( 'sb0001','The applet tag in HTML is ','<applet>','<java>','<java-appplet>','None' ,1,2);

insert into Question values( 'sb0001','What is Java','Language','Standard','IDE','Game Engine',1,1);
insert into Question values( 'sb0001','Who created Java','MS','Sun','IBM','None' ,1,2);
insert into Question values( 'sb0001','CurrentVersion of JAVA','1','2','4','3' ,1,2);
insert into Question values( 'sb0001','What is JDK','Language','Standard','IDE','none' ,1,4);
insert into Question values( 'sb0001','CurrentVersion of JDK','1.4','1.3','9.0','1.1' ,1,2);

insert into Question values( 'sb0001','What is superclass of all classes','Object','Applet','Socket','None' ,1,1);
insert into Question values( 'sb0001','Serializable is a ','Interface','Class','variable','None' ,1,1);
insert into Question values( 'sb0001','Package containing String is','lang','net','io','None' ,1,1);
insert into Question values( 'sb0001','Swing is in __ package','java','javax','both','None' ,1,2);
insert into Question values( 'sb0001','AWT is a ','Interface','windowing kit','Class','None' ,1,2);

insert into Question values( 'sb0001','javax package contains','networking','Swing','I/O','AWT' ,1,2);
insert into Question values( 'sb0001','Exception are caught in __ block','catch','try','finally','None' ,1,2);
insert into Question values( 'sb0001','Java 2D is','Version of Java','Graphics Library','Both','None' ,1,2);
insert into Question values( 'sb0001','RMI is ','Class','Interface','variable','None' ,1,2);
insert into Question values( 'sb0001','Socket class is in __ package','lang','net','io','None' ,1,2);

insert into Question values( 'sb0001','JDBC deals with','I/O','databases','Networking','None' ,1,2);
insert into Question values( 'sb0001','JComponent is in','swing','awt','net','None' ,1,1);
insert into Question values( 'sb0001','paint() is in ','Component','JComponent','Container','None' ,1,1);
insert into Question values( 'sb0001','init() is start-up for','Applet','Frame','JFrame','None' ,1,1);
insert into Question values( 'sb0001','The applet tag in HTML is ','<applet>','<java>','<java-appplet>','None' ,1,2);