# include<iostream.h>                                                           
# include<math.h>                                                               
 class octal                                                                    
{                                                                               
                                                                                
private :                                                                       
                                                                                
int ono;                                                                        
                                                                                
public :                                                                        
                                                                                
octal(int m=0)                                                                  
{                                                                               
int flag=0,i=0;                                                                 
if(m<=7&&m>=-7)                                                                 
ono=m;                                                                          
                                                                                
else                                                                            
{                                                                               
if(m<0)                                                                         
{                                                                               
m=-m;                                                                           
flag=1;                                                                         
-- INSERT --                                                                    