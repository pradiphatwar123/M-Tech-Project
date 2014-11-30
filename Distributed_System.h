


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
		std::vector<std::string> message;     // Dynamic array to store message onto the node
		std::vector<int> node_number; 		  // Dynamic array to store node_number onto the node from which message has come
};

class Distributed_System
{
	public:
		Node 	*Array;
		int 	size;
		void 	Create_graph(int n, std::vector<int> A);
		void 	addEdge(int from, int to, int weight);
		int 	Send_message(int from, int to, std::string msg);
		int		find_node(int Node_ID);
		void 	Display();
		void 	Display_msg(int ID);
};
