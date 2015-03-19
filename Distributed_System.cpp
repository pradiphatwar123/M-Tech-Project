#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<queue>
#include "Distributed_System.h"
using namespace std;

/*********************************************************************************************************
Function Name            : Create_graph

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/

void Distributed_System::Create_graph(int n, vector<int> A)
{
	Array = new Node[n];
	size=n;
	for(int i = 0; i < n; i++)
	{
		Array[i].Node_ID = A[i];
		Array[i].Broadcast_Msg =  false;
		Array[i].Broadcast_Msg_Received = false;
		Array[i].head = NULL;
	}
}

/*********************************************************************************************************
Function Name            : addEdge

Inputs                   : source Node_ID, destination Node_ID, Edge weight

Outputs                  : 

Description              :
*********************************************************************************************************/

void Distributed_System::addEdge(int from, int to, int weight)
{
	int f = find_node(from), t = find_node(to);
	AdjListNode *p=new AdjListNode, *q=new AdjListNode;
	
	p->dest = t;
	p->weight = weight;
	p->next = Array[f].head;
	Array[f].head = p;
	
	q->dest = f;
	q->weight = weight;
	q->next = Array[t].head;
	Array[t].head = q;
}

/*********************************************************************************************************
Function Name            : Send_message

Inputs                   : souce Node_ID, Dest Node_ID, Message 

Outputs                  : -1 If Error
							1 If successful send_message
Description              :  Sending a message from source node to destination node 
*********************************************************************************************************/

int Distributed_System::Send_message(int from, int to,std::string msg_type, std::string msg)
{
	int f = find_node(from), t = find_node(to);
	
	if(f==-1 || t==-1) 
	{	
		cout << " Error : Either Source Node OR Destination Node NOT FOUND " << endl;
		return  -1;
	
	}
	if( Receive_message( f, t, msg_type, msg) == -1)
	{
		cout << " Error : in Message Type" << endl;
		return -1;
	}
			
	return 1;
}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/
int Distributed_System::Receive_message(int f, int t, std::string msg_type, std::string msg)  // f = index of "from" Node  t = index of "to" Node
{
	
	if( msg_type == "Broadcast_Message")
	{
		Array[t].bm.message.push_back(msg);
		//cout<< Array[t].bm.message.front() << endl;
		//cout<< t;
		Array[t].bm.node_number.push_back(f);
		//cout<< " hello";
	}
	else if( msg_type == "Temperature_Read")
	{
		Array[t].tr.message.push_back(msg);
		Array[t].tr.node_number.push_back(f);
	}
	else if( msg_type == "Node_Id")
	{
		Array[t].nid.message.push_back(msg);
		Array[t].nid.node_number.push_back(f);
	}
	else if( msg_type == "Node_Count")
	{
		Array[t].nc.message.push_back(msg);
		Array[t].nc.node_number.push_back(f);
	}
	else
	{
		cout<< "INVALID MESSAGE TYPE" << endl;
		return -1;
	}

	return 1;
}
/*********************************************************************************************************
Function Name            : Display_msg

Inputs                   : Node_ID

Outputs                  : 
								
Description              :  Displaying messages of Node_ID
*********************************************************************************************************/

int Distributed_System::Broadcast_msg( int from, std::string msg_type, std::string msg)
{
	int f = find_node( from );
	
	if( f == -1)
	{
		cout<< " Error : Node Not Found " << endl; 
		return -1;
	}
	// queue for storing adjacency node ID's
	std::queue<int> q1, q2;      
	q1.push( from );
	
	while( !q1.empty() || !q2.empty())
	{

		while( !q1.empty() )
		{
			int ID;
			ID = q1.front();
			q1.pop();

			for( int i = 0; i < size; i++ )
			{
				if( Array[i].Node_ID == ID )                                   // search for node ID
				{																// and then
 					AdjListNode *p = Array[i].head;								// traverse that adjacency list
					
					while( p != NULL )
					{
						// Broadcasted Message receives ONLY ONCE
						if( Array[p->dest].Broadcast_Msg_Received == false )     
						{
							Send_message( ID, Array[p->dest].Node_ID, msg_type, msg);
							Array[p->dest].Broadcast_Msg_Received = true;
							q2.push( Array[p->dest].Node_ID);
						}
						p = p->next;
					}

					Array[i].Broadcast_Msg = true;
				}

			}

		}
		// swapping queue objects
		swap(q1, q2);    
	}

	for( int i = 0; i < size ; i++)
	{
		// Reset Broadcast_Msg for all nodes
		Array[i].Broadcast_Msg = false;     
		
		// Reset Broadcast_Msg for all nodes
		Array[i].Broadcast_Msg_Received = false;
	}
	
	return 1;
}

/*********************************************************************************************************
Function Name            : find_node

Inputs                   : Node_ID

Outputs                  : 

Description              :  Checking whether node is present in the network or not
*********************************************************************************************************/

int Distributed_System::find_node(int Node_ID)
{
	for( int i = 0; i < size; i++)
	{
		if( Array[i].Node_ID == Node_ID ) return i;
	}
	return -1;
}

/*********************************************************************************************************
Function Name            : Display

Inputs                   : 

Outputs                  : 

Description              : Ajacency list of nodes 
*********************************************************************************************************/

void Distributed_System::Display()
{
	cout << endl << endl;
	cout<< " *** GRAPH IN ADJACENCY LIST FORMAT ***" << endl;
	for(int i=0; i<size; i++)
	{
		cout<<Array[i].Node_ID;
		AdjListNode *p = Array[i].head;
		while(p != NULL)
		{
			cout<<" -> "<<Array[p->dest].Node_ID;
			p = p->next;
		}
		cout<<endl;
	}
	cout << endl <<endl; 
}

/*********************************************************************************************************
Function Name            : Display_msg

Inputs                   : Node_ID

Outputs                  : 
								
Description              :  Displaying messages of Node_ID
*********************************************************************************************************/

void Distributed_System::Display_msg(int ID)
{
	int n = find_node(ID);
	
	if(n == -1) 
	{
		cout<<"Error.....Node does not EXIST!!!!\n";
	}
	else if(Array[n].bm.message.size() == 0  && Array[n].nid.message.size() == 0 && Array[n].tr.message.size() == 0 && Array[n].nc.message.size() == 0)
	{
		cout<<"********* NO MESSAGE *********** " << endl;
	}
	else
	{
		cout<< " Node ID        :" << Array[n].Node_ID<<endl;
		
		if( Array[n].bm.message.size() > 0)
		{
			cout << " Message Type   : Broadcast_Message "<<endl;
			cout << " Received From  : Message" << endl;
			for(int i = 0; i < Array[n].bm.message.size(); i++)
			{
				cout<<"\t"<<Array[Array[n].bm.node_number[i]].Node_ID<<"\t:";
				cout<<Array[n].bm.message[i]<<endl;
			}
			cout << endl;
		}
			
		if( Array[n].tr.message.size() > 0)
		{
		
			cout << " Message Type   : Temperature_Read "<<endl;
			cout << " Received From  : Message" << endl;
					
			for(int i = 0; i < Array[n].tr.message.size(); i++)
			{
				cout<<"\t"<<Array[Array[n].tr.node_number[i]].Node_ID<<"\t:";
				cout<<Array[n].tr.message[i]<<endl;
			}
			cout << endl;
		}
		
		if( Array[n].nid.message.size() > 0)
		{
			cout << " Message Type   : Node_Id "<<endl;
			cout << " Received From  : Message" << endl;
	
			for(int i = 0; i < Array[n].nid.message.size(); i++)
			{
				cout<<"\t"<<Array[Array[n].nid.node_number[i]].Node_ID<<"\t:";
				cout<<Array[n].nid.message[i]<<endl;
			}
			cout << endl;
		}
		
		if( Array[n].nc.message.size() > 0)
		{
			cout << " Message Type   : Node_Count "<<endl;
			cout << " Received From  : Message" << endl;
			
			for(int i = 0; i < Array[n].nc.message.size(); i++)
			{
				cout<<"\t"<<Array[Array[n].nc.node_number[i]].Node_ID<<"\t:";
				cout<<Array[n].nc.message[i]<<endl;
			}
		}
	}
	
	cout<< endl <<endl;
}
