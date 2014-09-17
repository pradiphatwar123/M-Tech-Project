
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
