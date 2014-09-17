/*********************************************************************************************************

Project           :  Build Simulator For Synchronous Distributed System

File name         :  main.CPP

Description       :  

Programmers       :  (1) Sachin Balchim    (CS13M010)
                     (2) Bibekananda Raul  (CS13M011)
		     (3) Pradip Hatwar     (CS13M022)

Compiler name     :  

Date created      :  

List of functions : (1)  int 	main(int argc, char *argv[])
		    (2)  int	ValidateCmdline();
		    (3)	 int	ValidateFile();	
		    (4)  int 	ValidateInput();
		    (5)  void	ReadInputs();	
		    (6)  int	WriteOutput();	
                    
History           :  

*********************************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<malloc.h>
#include<fstream>
#include<string.h>

#include "Graph.h"

int 	ValidateCmdline();
int 	ValidateFile();
int 	ValidateInput();
void	ReadInputs();
int 	WriteOutput();


int main()
{
	
	Distributed_System DS;
	
	ValidateCmdline();
 	
	ValidateFile();
 	
	ValidateInput();
	
	ReadInputs();
 	
		
	WriteOutput();
	
	return 0;
}



/*********************************************************************************************************
Function Name            : WriteOutput

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/
int ValidateCmdline()
{
	int 	error=0;
	
	return error;        
}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/	

int ValidateFile()
{




}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/

int ValidateInput()
{
	int error =0 ;

	
	return error;
}


/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/

void ReadInputs()
{


	

}

/*********************************************************************************************************
Function Name            : WriteOutput

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/

int WriteOutput()
{
	int error =0 ;

	
	return error;

}
