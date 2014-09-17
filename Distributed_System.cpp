#include<iostream>
#include<stdlib.h>
#include<fstream>

#include "Distributed_System.h"

using namespace std;

Node nd;


/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/	
Distributed_System * Distributed_System :: createGraph( int num_Nodes)
{
	
	Distributed_System *graph = new Distributed_System;   // graph is objct of Distributed_System
	
	graph->array = new Node_Adj_List [ num_Nodes ];   // allocate memory for Head Nodes Of Adjecency List
	graph->NUM_NODES = num_Nodes;			  
	
	for( int i = 0; i < graph->NUM_NODES; i++ )
	{
		graph->array[i].Head = NULL;		// Initially setting all Head NOde pointer to NULL
	}
	
	return graph;
}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/	

Node * Distributed_System :: Add_Node( int Node_Id )
{
	Node *newNode = new Node;
	
	newNode->node_id = Node_Id;
	newNode->next	= NULL;
	
	return newNode;
}
		


/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/
void Distributed_System :: Add_Connection( Distributed_System *graph, int source, int destination )    // Adding Edges
{

	Node *newNode = Add_Node( source );
	
	newNode->next = graph->array[destination].Head;
	graph->array[destination].Head = newNode;

	newNode = Add_Node( destination );
	newNode->next = graph->array[source].Head;
	graph->array[source].Head = newNode;	

}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*******************************************************************************************************/


void Distributed_System :: Remove_Node( int Node_Id )
{




}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/	

int Distributed_System :: Update_Graph()
{

	int error = 0 ;

	return error;

}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

void Distributed_System :: displayGraph( Distributed_System *graph)
{
	
	
	ofstream outStrm;
		
	// cout << "Adjecency List Representation Of Distributed System ( Graph ) " << endl;
	
	outStrm.open("graph_In_Adj_List_Format.txt", ios::out );
	
	for( int i = 0; i < graph->NUM_NODES; i++ )
	{
		Node *current = graph->array[i].Head; 
	
		if( i == 0 )
		{
			outStrm <<" <Source Node> ----> <Adjacency List Nodes> " << endl;
		}
		outStrm << i << "    " ;
		
		while( current )
		{
			outStrm <<  current->node_id << "    ";
			current = current->next;
		}			
	
		outStrm << "\n";


	/*	cout << "Adj_List [" << i << "] == > ";
		
		while( current )
		{
			cout <<  current->node_id << "->";
			current = current->next;
		}			
	
		cout << "\n";

	*/



	}
	
	outStrm.close();	





}
 
/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

int Distributed_System :: Find_Node( int Node_Id )
{
	int error = 0 ;


	return error;
}




/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

int Distributed_System :: get_Node_Count( char *inputfile)
{
	int error = 0, N =1024 ;
	int Node_Count = 0;
	char line[N];
	
	ifstream inpStrm;
	inpStrm.open( inputfile , ios::in );  
	
	while( inpStrm )
	{
		string str;
		
		inpStrm.getline( line, 1023, '\n');
		str = line;
		
		if( str.compare("// edges") == 0 )
		{
			return Node_Count-2;
		}
	
		Node_Count++;
	}	
	inpStrm.close();	

	return error;
}






/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

void Distributed_System :: Monitor_graph()
{




}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/		
	
void Distributed_System :: List_Nodes()
{





}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

int Distributed_System :: Search_Node_Id( int Node_Id )
{

	int error =0 ;

	
	return error;
}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

int Distributed_System :: Get_Transmitted_Num_Message()
{
	int error=0;



	return error;
}

/*********************************************************************************************************
Function Name            : 
 
Inputs                   : 

Returns                  : 

Description              : 
*********************************************************************************************************/

int Distributed_System :: Get_Num_Inserted_Connection()

{
	int error = 0 ;


	
	return error;
}
