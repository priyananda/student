-- @document : tables.sql
-- @author   : shenoy
-- @date     : 7 May 2003
-- @comments : All the queries . They are not to be executed here but 
		in the application
-- only a reference

--Student Login 
select vPassword from Student where cStudentId = 'name';

--Lecturer Login
select vPassword from Lecturer where cStudentId = 'name';

--Course details during student regn 
select cCourseId , vName , vDescription from Course;
select vName , vDescription from Subject where cSubjectId in (
	select cSubjectId from CourseStudent where cCourseId='$courseid'
);

--Student Registration
insert into Student values ( '$name' , '$age' , '$courseId' ,
 '$Address' , '$email' , 0, '$pass' , '$others' , '$ccno');

 --Lecturer Registration
 insert into Lecturer values ( '$name' , '$age' , '$SubjectId' ,
 '$Address' , '$email' ,  '$pass' , '$ccno');

 --Subject details during Lecturer regn 
select vName  from Subject ;

--Admin : add a subject
insert into Subject values ( '$name' , '$desc' );

--Admin : delete a subject
delete Subject where cSubjectId = '$subj'
