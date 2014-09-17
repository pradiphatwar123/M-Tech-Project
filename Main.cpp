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
		    (3)  int	Check_Files();
		    (3)	 int	ValidateFile();	
		    (4)  int 	ValidateInput();
		    (5)  void	ReadInputs();	
		    (6)  int	WriteOutput();	
		    (7)  void Extract_EdgeN_Weights( char *, char *);  \\                   
History           :  

*********************************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<malloc.h>
#include<fstream>
#include<string.h>
#include<sstream>

#include "Distributed_System.h"
using namespace std;

int 	ValidateCmdline(int argc, char *argv[], char **inputfile, char **outputfile, char **program);
int 	Check_Files( char *inputfile, char *outputfile);
int 	ValidateFile( char * );
int 	ValidateInput( char *, int );
void	ReadInputs();
int 	WriteOutput();
void Extract_EdgeN_Weight( char *, char *);  //

int main( int argc, char *argv[] )
{
	
	Distributed_System DS;
			
	char *inputfile, *outputfile, *program;

	inputfile = (char *)" ";
	outputfile = (char *)" ";
	program  =(char *)" ";
		
	if( ValidateCmdline( argc, argv, &inputfile, &outputfile, &program) == -1)
	{
		cout << "!!...Exiting...!!" << endl;
		exit(1);	
	}
	
	else if( Check_Files( inputfile , outputfile ) == -1)
	{
		cout << " !!...Exiting...!! " << endl;
		exit(1);
	}
	else if(ValidateFile(inputfile) == -1) // Validating Input File 
	{
		cout << "Failed to validate file  " << inputfile  << ", Exiting....." << endl;
		exit(-1);
	}

	Extract_EdgeN_Weight( inputfile, outputfile);  //

	int Num_Nodes = DS.get_Node_Count(inputfile);
	
	
	Distributed_System *graph = DS.createGraph( Num_Nodes );
	DS.Add_Connection( graph, 0, 1	);
	DS.Add_Connection( graph, 2, 3	);
	DS.Add_Connection( graph, 4, 5	);
	DS.Add_Connection( graph, 6, 7	);	
	DS.Add_Connection( graph, 8, 9	);
	DS.Add_Connection( graph, 0, 2	);
	DS.Add_Connection( graph, 0, 3	);	

	DS.displayGraph( graph );
	 
	ReadInputs();
 	
		
	WriteOutput();
	
	return 0;
}



/*********************************************************************************************************
Function Name            : ValidateCmdline

Inputs                   : (1) Number of command line arguments passed
			   (2) List of Command Line arguments
			   (3) Reference to input file
			   (4) Reference to output file
Outputs                  : int
			    0 	If No Error
			   -1 	If Error

Description              :  This function validates the command line arguments
*******************************************************************************************************/
int ValidateCmdline( int argc, char *argv[], char **inputfile, char **outputfile, char **program)
{
	int 	error=0;
	string temp, temp1;

	if( argc < 4)
	{
		cout << " Error : Valid Command for Execution is " << endl;
		cout << "< exename> <Input_File_Name>.gv <Output_File_Name>.gv <program>.txt " << endl; 		
		error = -1;
	}	
	else
	{
		temp = argv[1];
		temp1 = temp.substr(( temp.length() - 3 ), 3 );

		if( temp1.compare( ".gv" ) != 0 )		
		{
			cout << " Error : Valid Command for Execution is " << endl;
			cout << "< exename> <Input_File_Name>.gv <Output_File_Name>.gv <program>.txt" << endl; 		
			error = -1;	
		}
		else
		{
			temp = argv[2];
			temp1 = temp.substr(  ( temp.length() - 3 ), 3 );
		
			if( temp1.compare( ".gv") != 0 )
			{
				cout << " Error : Valid Command for Execution is " << endl;
				cout << "< exename> <Input_File_Name>.gv <Output_File_Name>.gv <program>.txt" << endl; 		
				error = -1;
			}
			else
			{
				temp = argv[1];
				temp1 = temp.substr(( temp.length() - 3 ), 3 );

				if( temp1.compare( ".gv" ) != 0 )		
				{
					cout << " Error : Valid Command for Execution is " << endl;
					cout << "< exename> <Input_File_Name>.gv <Output_File_Name>.gv <program>.txt" << endl; 		
					error = -1;
				}
				else
				{
					*inputfile = argv[1];
					*outputfile = argv[2]; 
					*program    = argv[3];
				}
			}
		}		
	}
	
	return error;        
}

/*********************************************************************************************************
Function Name            : Check_Files

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/	

int Check_Files( char *inputfile, char *outputfile )
{
	
	int error = 0;
		
	ifstream inputStrm;
	ofstream outputStrm;
	
	inputStrm.open( inputfile , ios :: in );
	
	if( !inputStrm )
	{
		cout << " File "<< inputfile << " doesn't exist " << endl;
		error = -1;
	}
	else
	{
		inputStrm.close();
		
		inputStrm.open( outputfile , ios :: in );
		if( !inputStrm )
		{
			cout << " File " << outputfile << " doesn't exist" << endl;
			error = -1; 	
		}
		else 
		{
			
			inputStrm.close();
		}
	}

	
	return error;

}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/	

int ValidateFile(char *inpfile)
{

	int		retval = 0, count = 0, line_num = 1, temp;
	ifstream	inpstrm ;	
	char		buff1[1025],buff[100],ch;
	stringstream 	sis;	
	string		str;


	inpstrm.open(inpfile, ios::in);	// Opening Input file 

	if(!inpstrm){		
		cout << "Exiting...." << endl;
		retval = -1;
	}
	else
	{			
		while(inpstrm)		
		{		
			std::fill(buff1, buff1 + 1024, ' ');	//Filling entire buffer with blank space
			inpstrm.getline(buff1,1024, '\n');	// Reading Input file line wise		
			if(inpstrm)
			{	
												
				if((int)buff1[0] == 0) //For handling blank lines
				{					
					retval = ValidateInput(buff1, line_num);
					if(retval == -1)
					{		
						cout << "Invalid Entry in the input.gv at line num " << line_num << endl;					
						break;
					}
				}	 				
				/*
				sis << buff1;					
				while(getline(sis,str,'\n'))
				{					
					strncpy(buff, str.c_str(), sizeof(buff));
					retval = ValidateInput(buff, line_num); // Validating items read from Input file 					
					if(retval == -1)
					{ 	
						cout << "Invalid Entry in the input.gv at line num " << line_num << endl;					
						break;	
					}
				}
				sis.clear();
				*/
					
				retval = ValidateInput(buff1, line_num); // Validating items read from Input file 					
				if(retval == -1)
				{ 	
					cout << "Invalid Entry in the input.gv at line num " << line_num << endl;					
					break;	
				}				
			}
			else
			{
				if(inpstrm.eof())
				{
					//Reached end of the file
				}
				else
				{
					cout << "Failed to read data from file " << inpfile << "inside validate_file " << endl; 
					retval = -1;				
				}
			}	
			if(retval == -1)
				break;
			line_num++;
		}
		inpstrm.close(); // Closing the input file 
	}	
	return retval;
}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/

int ValidateInput(char *input, int line_num)
{

		int		retval =0, iter =0, iter1 = 0, iter3 =0;
	static 	int		nodes_start = 0, edges_start = 0, last_line = 0;
		int		nodes_line_num = 0, edges_line_num = 0;
		stringstream	sis,sis1;
		string		str,str1;	
		char		buff[50],buff1[50];
		
	//Verifying if blank space is received
	if(strlen(input) == 0)			//No line of Input File must be blank
	{
		retval = -1;
	} 	
	else
	{
		if(line_num == 1) 		//Line 1 must be "graph G {"
		{		
			if(strcmp(input, "graph G {") != 0 )
			{
				retval = -1;		
			}			
		}	
		else if(line_num == 2) 		//Line 2 must be "// nodes"
		{		
			if(strcmp(input, "// nodes") != 0 )
			{
				retval = -1;		
			}
			else			//Nodes information starts from next line
			{				
				nodes_start = 1;
				nodes_line_num = line_num;			
 			}	
		}	
		else if(strstr(input,"edges"))	//Edges information starts from next line
		{					
			edges_line_num = line_num;		
			nodes_start = 0;
			edges_start = 1;			
		}	
		else if(strstr(input,"}"))	//Last Line
		{
			if(last_line == 0)
			{	
				nodes_start = 0;
				edges_start = 0;	
				last_line = 1;	
			}
			else			//Invalid End of the file
			{
				cout << "Invalid End of the file " << endl;
				retval = -1;
			}
		}
		else if(nodes_start == 1)	//Verifiying Node Line Structure
		{			
			for(iter = 0; iter < strlen(input) - 1 ; iter++)
			{
				if(isdigit(input[iter]) == 0)	//Only Numeric characters
				{
					cout << "Not a valid node name "<< endl;
					retval = -1;
					break;
				} 
			}
			if(input[strlen(input) - 1] != ';') 	//Must End with semicolon
			{
				cout << "Not a valid node line " << endl;
				retval = -1;			
			}			
		}
		else if(edges_start == 1)	//Verifiying Edge Line Structure
		{		
			sis << input;	
			iter = 0;						
			while(getline(sis,str,' '))
			{	
				strncpy(buff, str.c_str(), sizeof(buff));			
				if(iter == 0)	//Edge 1st Vertex
				{	
					//Edge Endpoint1 extracted endl;											
					for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
					{
						if(isdigit(buff[iter1]) == 0) //Only Numeric characters
						{
							cout << "Not a valid edge endpoint "<< endl;							
							retval = -1;
							break;
						} 
					}
					if(retval == -1)
					break;	
				}			
				else if(iter == 1)	//Edge divider	
				{
					// Edge Divider extracted 
	
					if(strlen(buff) != 2)
					{
						cout << "Not a valid edge divider"<< endl;
						retval = -1;
						break;
					}
					else
					{						
						for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
						{
							if(buff[iter1] != '-') //Only -- is allowed
							{
								cout << "Not a valid edge divider"<< endl;								
								retval = -1;
								break;
							} 
						}
					}
					if(retval == -1)
					break;
				}
				else if(iter == 2)	//Edge 2nd Vertex
				{
					//Edge Endpoint2 extracted

					for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
					{
						if(isdigit(buff[iter1]) == 0) //Only Nuemeric
						{
							cout << "Not a valid edge endpoint"<< endl;
							retval = -1;
							break;
						} 
					}	
					if(retval == -1)
					break;
				}
				else if(iter == 3)	//Edge Attributes Structure	
				{
					sis1 << buff;	
					iter3 = 0;						
					while(getline(sis1,str1,'"')) //  " delimiter 
					{		
						strncpy(buff1, str1.c_str(), sizeof(buff1));
						if(iter3 == 0)	//Edge Attribute part1
						{
							if(strcmp(buff1,"[label=") != 0)
							{
								cout << "Not a valid edge label attribute"<< endl;
								retval = -1;
								break;

							}	
						}
						else if(iter3 == 1) 	//Edge Attribute part2 - weight
						{
							for(iter1 = 0; iter1 < strlen(buff1) ; iter1++)
							{
								if(isdigit(buff1[iter1]) == 0) //Only Digit
								{
									cout << "Not a valid edge weight"<< endl;
									retval = -1;
									break;
								}	 
							}
						}
						else if(iter3 == 2)	//Edge Attribute part3
						{
							if(strcmp(buff1,"];") != 0)
							{
								cout << "Not a valid edge label attribute"<< endl;	
								retval = -1;
								break;

							}
						}
						else			//Invalid Edge Attribute
						{
							cout << "Invalid Edge Label Attribute " << endl;
							retval  = -1;
							break;
						}
						iter3++;
						if(retval == -1)
						{	 	
							break;	
						}
					}
					sis1.clear();
				}
				else 				//Invalid Entry in input file
				{
					cout << "Inavlid Edge Line " << endl;
					retval = -1;
					break;
				}
				iter++;						
				if(retval == -1)
				{ 	
					break;	
				}
			}
			sis.clear();						
		}
		else						//Invalid End of the file
		{
			if(last_line == 1)
			{
				cout << "Invalid end of the file " << endl;
				retval = -1;
			}
		}	
	}	
				
	return retval;

}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/

void Extract_EdgeN_Weight( char *inputfile, char *outputfile )
{
	int N = 1024;
	char line[N];
	string str;
	stringstream ss;
	
	ifstream inpStrm;
	ofstream outStrm;
	
	inpStrm.open(inputfile, ios::in );
	outStrm.open("Extracted_EdgeN_Weight" , ios::in | ios::out | ios::trunc );
	while( inpStrm )
	{
		inpStrm.getline(line, 1023, '\n');
		str = line;                 
		       
		if( str.compare("// edges") == 0 )         // read the input lines till "// edges"
		{
			break;
		}
	}

	while(inpStrm)
	{
		inpStrm.getline( line, 1023, '\n');
	
		if( line[0] == '}')
			break;

		for( int i = 0; (i < 1024) && ( line[i] != ';' ) ; i++ )
		{
			while( isdigit(line[i]))
			{
				outStrm<< line[i];
				
				i++;
			}	
			outStrm << " ";
		}
		outStrm << "\n";
	}
	
}


/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/

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
