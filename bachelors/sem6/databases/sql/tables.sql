-- @document : tables.sql
-- @author   : shenoy + Naveen
-- @date     : 27 May 2003
-- @comments : create s all the tables
-- @todo     : make all primary keys auto-generating

drop table Subject CASCADE CONSTRAINTS;
drop table Course CASCADE CONSTRAINTS;
drop table CourseSubject CASCADE CONSTRAINTS;
drop table Student CASCADE CONSTRAINTS;
drop table Lecturer CASCADE CONSTRAINTS;
drop table Test CASCADE CONSTRAINTS;
drop table Question CASCADE CONSTRAINTS;
drop table ScheduledLecture CASCADE CONSTRAINTS;
drop table OnlineLecture CASCADE CONSTRAINTS;
drop table SampleQuestion CASCADE CONSTRAINTS;
drop table SampleQuestionPaper CASCADE CONSTRAINTS;
drop table SampleQuestionSamplePaper CASCADE CONSTRAINTS;
drop table SampleTest CASCADE CONSTRAINTS;
drop table admin_pass CASCADE CONSTRAINTS;

create  table Subject (
	cSubjectId	char(6) NOT NULL ,
	vName		varchar2(30) NOT NULL ,
	vDescription varchar2(50) NOT NULL ,
    constraint pk_Subject PRIMARY KEY ( cSubjectId )
);

create  table Course (
	cCourseId	char(6) NOT NULL ,
	vName		varchar2(30) NOT NULL ,
	vDescription varchar2(50) NOT NULL ,
	bUsed 		number(10) DEFAULT (1),
    constraint pk_Course PRIMARY KEY ( cCourseId )
);

create  table CourseSubject (
	cCourseId	char(6) NOT NULL,
	cSubjectId	char(6) NOT NULL,
	constraint fk_CSSub	FOREIGN KEY ( cCourseId ) REFERENCES Course(cCourseId),
	constraint fk_CSCou	FOREIGN KEY ( cSubjectId ) REFERENCES Subject(cSubjectId)
);

create  table Student (
	cStudentId	char(6)			NOT NULL,
	vName		varchar2(30)	NOT NULL,
	dDob		Date			NOT NULL,
	cCourseId	char(6)			NOT NULL,
	vAddress	varchar2(50)	NOT NULL,
	vEmailId	varchar2(30)	NOT NULL,
	bCompleted	number			NOT NULL,
	vPassword	varchar2(20)	NOT NULL,
	vOtherSkills varchar2(100)	NULL,
	cCCNumber	char(30)		NOT NULL,
    constraint pk_Student PRIMARY KEY ( cStudentId ),
    constraint fk_Student FOREIGN KEY ( cCourseId ) REFERENCES Course( cCourseId )
);

create  table Lecturer (
	cLecturerId char(6) NOT NULL ,
	vName		varchar2(30) NOT NULL ,
	nDob		Date NOT NULL ,
	cSubjectId	char(6) NOT NULL ,
	vAddress	varchar2(50) NOT NULL ,
	vEmailId	varchar2(30) NOT NULL ,
	vPassword	varchar2(20) NOT NULL ,
	cCCNumber	char(30) NOT NULL,
    constraint pk_Lecturer PRIMARY KEY ( cLecturerId),
    constraint fk_Lecturer FOREIGN KEY ( cSubjectId ) REFERENCES Subject( cSubjectId )
);

-- nWeightage is betweeen 1 and 1
create  table Question (
    cSubjectId  char(6) NOT NULL ,
	vQuestion	varchar2(100) NOT NULL ,
	vOption1	varchar2(50) NOT NULL ,
	vOption2	varchar2(50) NOT NULL ,
	vOption3	varchar2(50) NOT NULL ,
	vOption4	varchar2(50) NOT NULL ,
	nWeightage	number NOT NULL ,
	nAnswer		number NOT NULL ,
    constraint fk_Question FOREIGN KEY ( cSubjectId ) REFERENCES Subject(cSubjectId)
) ;
-- all tests have 10 questions
create  table Test (
    cTestId     char(6) NOT NULL ,
    cSubjectId  char(6) NOT NULL ,
    cStudentId  char(6) NOT NULL ,
    nMarks      number NOT NULL ,
    constraint pk_Test PRIMARY KEY ( cTestId ),
    constraint fk_TestSub   FOREIGN KEY ( cSubjectId ) REFERENCES Subject ( cSubjectId ),
    constraint fk_TestStud  FOREIGN KEY ( cStudentId ) REFERENCES Student ( cStudentId )
);

create  table OnlineLecture (
	cOLectureId char(6) NOT  NULL, 
    cLecturerId char(6) NOT NULL ,
    vDescription varchar2(30) NOT NULL ,
    cType       char(20) NOT NULL ,
    vPath       char(30) NOT NULL ,
    vKeyword    varchar2(30) NOT NULL ,
    constraint pk_OLLec PRIMARY KEY ( cOLectureId ),
    constraint fk_OLLec FOREIGN KEY ( cLecturerId ) REFERENCES Lecturer( cLecturerId )
);

create  table ScheduledLecture (
    cSLectureId  char(6) NOT NULL ,
    cLecturerId  char(6) NOT NULL ,
    vDescription varchar2(30) NOT NULL ,
    vPlace      varchar2(30) NOT NULL ,
    dDate       varchar2(10) NOT NULL ,
    tTime       varchar2(10) NOT NULL,
    constraint pk_SLLec PRIMARY KEY ( cSLectureId ),
    constraint fk_SLLec FOREIGN KEY ( cLecturerId ) REFERENCES Lecturer( cLecturerId )
);

create  table SampleQuestionPaper (
    cSampleQuestionPaperId char(6) NOT NULL ,
    nQuestions  number NOT NULL ,
    constraint pk_SampleQuestionPaper PRIMARY KEY ( cSampleQuestionPaperId )
) ;

create  table SampleQuestion (
	cSampleQuestionId char(6) NOT NULL ,
	vQuestion	varchar2(30) NOT NULL ,
	vOption1	varchar2(20) NOT NULL ,
	vOption2	varchar2(20) NOT NULL ,
	vOption3	varchar2(20) NOT NULL ,
	vOption4	varchar2(20) NOT NULL ,
	nWeight		number NOT NULL ,
	nAnswer		number NOT NULL,
    constraint pk_SamQ PRIMARY KEY ( cSampleQuestionId )
);

create  table SampleQuestionSamplePaper (
	cSampleQuestionId char(6) NOT NULL ,
	cSampleQuestionPaperId char(6) NOT NULL ,
    constraint fk_SQSPSQID FOREIGN KEY ( cSampleQuestionId ) REFERENCES SampleQuestion( cSampleQuestionId),
    constraint fk_SQSPSQPID FOREIGN KEY ( cSampleQuestionPaperId ) REFERENCES SampleQuestionPaper( cSampleQuestionPaperId )
);  

create table SampleTest(
	cSampleTestId char(6) NOT  NULL,
	cSubjectId    char(6) NOT NULL,
	cSampleQuestionPaperId char(6)  NOT NULL,
    constraint fk_STSub FOREIGN KEY ( cSubjectId ) REFERENCES Subject( cSubjectId ),
    constraint fk_ST FOREIGN KEY ( cSampleQuestionPaperId ) REFERENCES SampleQuestionPaper( cSampleQuestionPaperId),
	constraint pk_STId PRIMARY KEY ( cSampleTestId )
);

create table admin_pass (
	vPassword varchar2(20)
);

create or replace view Student_Course
as
select s.vName Studentname , c.vName CourseName , s.cStudentid StudentId , 
       s.vEmailId EmailId , s.vOtherSkills OtherSkills
from Student s,Course c
where s.cCourseId = c.cCourseId
;

create or replace view Lecturer_Course
as
select  l.vName LecturerName , sb.vName SubjectName , l.cLecturerid LecturerId ,
		l.vemailId EmailId   
from Lecturer l, Subject sb
where l.cSubjectId = sb.cSubjectId
;
