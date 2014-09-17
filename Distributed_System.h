#include "Node.h"


/*********************************************************************************************************/
/*********************************************************************************************************/

class Node_Adj_List
{

	public :
		Node *Head;     // This is Head Node which points to Adjecency List of node 		
		
		

};

/*********************************************************************************************************/
/*********************************************************************************************************/

class Distributed_System
{							


		int 		NUM_NODES;
		Node_Adj_List 	*array;

	public : 
		

 Distributed_System 	*createGraph( int V );
		int 	Find_Node( int Node_Id );
		int 	Update_Graph();
		int 	get_Node_Count( char *);



		Node 	*Add_Node( int Node_Id );
		
		void 	Add_Connection( Distributed_System *graph, int Node_Id1, int Node_Id2 );
		
		void 	displayGraph( Distributed_System *graph);		
				
		void 	Remove_Node( int Node_Id );

		void 	Monitor_graph();
		
		void 	List_Nodes();

		int 	Search_Node_Id( int Node_Id );

		int 	Get_Transmitted_Num_Message();

		int 	Get_Num_Inserted_Connection();


};



