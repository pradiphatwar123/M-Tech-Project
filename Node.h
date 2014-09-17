class Node
{

	public :

		unsigned int node_id;
		Node *next;	
		unsigned int time;
				
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
