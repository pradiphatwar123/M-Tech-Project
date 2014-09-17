
#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<malloc.h>
#include<fstream>
#include<string.h>
#include<math.h>
#include<cstdlib>

class Node
{

	public :

		unsigned int time;
		unsigned int node_id;
		
		struct Connection_Queue
		{
			Node *from;
			Node *to;
			unsigned int time;
		};

		
		struct Message_Queue
		{
			Node 	 *from;
			char 	 *message;
			unsigned int time;
		};

		void 	Send_Message( Node *target, int Message_Type, char *Message);

		void 	Receive_Message( Node *from, int Message_Type, char *Message );

		void 	Process_Received_Message( Node *origin , int Message_Type, char *Message );

		void 	Broadcast_Message_To_Neighbours( char *Message, int Message_Type );		
	
		void 	Broadcast_Message_To_All_Nodes( char *Message, int Message_Type );	

		void 	Find_Neighbours( int Node_Id);

		int 	IsNeighbour( Node *xyzNode);

		struct Remove_Message_From_Queue
		{
			Node *to;
			unsigned int time;
		};
		
};


class Distributed_System
{

	public : 
		
		int Add_Connection( int Node_Id1, int Node_Id2 );
	
		void Remove_Node( int Node_Id );

		int Add_Node( Node *newNode);
		
		void Monitor_graph();
		
		void List_Nodes();

		int Search_Node_Id( int Node_Id );

		int Get_Transmitted_Num_Message();

		int Get_Num_Inserted_Connection();


};






int 	AddNode( Node *newNode );
int 	Find_Node( int Node_Id );
int 	Delete_Node( int Node_Id);
int 	Update_Graph();


int 	ValidateCmdline();
int 	ValidateFile();
int 	ValidateInput();
void	ReadInputs();
int 	WriteOutput();

