
class Message
{
	public :
		std::vector<std::string> msg_type; 
		std::vector<std::string> message;   // Dynamic array to store message onto the node
		std::vector<int> node_number;		// Dynamic array to store node_number onto the node from which message has come
		std::vector<int> Message_Id;
};

class Outbox
{
	public :
		std::vector<std::string> msg_type; 
		std::vector<std::string> message;   // Dynamic array to store message onto the node
		std::vector<int> node_number;		// Dynamic array to store node_number_INDEX onto the node from which message has come
		std::vector<int> Message_Id;
};

class AdjListNode
{
	public :
			int	 	dest;
			int		weight;
	AdjListNode		*next;
};

class Node
{
	
	public:
		AdjListNode *head;
		int	 Node_ID;
	
		Message msg;
		Outbox Outb;
};

class Distributed_System
{
	public:
		Node 	*Array;
		int 	size;
		void 	Create_graph(int n, std::vector<int> A);
		void 	addEdge(int from, int to, int weight);
		void 	Send_message(int from, int to, std::string msg_type, int Message_Id, std::string msg);
		void 	Receive_message(int Node_Index);
		int		find_node(int Node_ID);
		void 	Display();
		void 	Display_msg(int ID);
		//int		Broadcast_msg( int from, std::string msg_type, std::string msg);
		void 	Simulation( int Round);
};
