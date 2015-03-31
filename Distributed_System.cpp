#include<iostream>
//#include<bits/stdc++.h>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
//#include<random>    // lib for random number
//#include<chrono>	// lib for random number
#include<sstream>
#include "Distributed_System.h"
using namespace std;

/*********************************************************************************************************
Function Name            : Create_graph

Inputs                   : n = Number of Nodes

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

void Distributed_System::Send_message(int from, int to,std::string msg_type, int Message_Id, std::string msg) // 'from' & 'to' index of node
{
	AdjListNode *p = Array[to].head;
	
	vector<int>::iterator it ;
	it = find( Array[to].msg.Message_Id.begin(), Array[to].msg.Message_Id.end(), Message_Id );
	if( it == Array[to].msg.Message_Id.end() )
	{
		Array[to].msg.node_number.push_back( from );
		Array[to].msg.msg_type.push_back( msg_type );
		Array[to].msg.Message_Id.push_back( Message_Id );
		Array[to].msg.message.push_back( msg );
	}
}

/*********************************************************************************************************
Function Name            : 

Inputs                   : 

Outputs                  : 

Description              :  
*********************************************************************************************************/
void Distributed_System::Receive_message(int k )  // k = index of Node in adjacency list e.g. Array[k]
{
	// check message vector is empty or not
	if( Array[k].msg.message.size()  == 0 )	
	{
			// Do Nothing
	}
	else  
	{
		for( int i = 0; i < Array[k].msg.message.size(); i++)
		{
			// computation as per msg_type
			if( Array[k].msg.msg_type[i].compare("Broadcast_Message") == 0)
			{
				// put a message in OUTBOX in order to broadcast to it's neighbours
				AdjListNode *p = Array[k].head;
				
				while( p  != NULL )
				{
					// do not push back a same message to an incoming edge ( node from where message had come)
					if( Array[k].msg.node_number[i] != p->dest )	
					{
						{
							
							Array[k].Outb.Message_Id.push_back( Array[k].msg.Message_Id[i]);
							Array[k].Outb.msg_type.push_back( Array[k].msg.msg_type[i]);
							Array[k].Outb.node_number.push_back( p->dest);				// Array[k] want to send message to Array[p->dest]
							Array[k].Outb.message.push_back( Array[k].msg.message[i]);
							
						}
						
					}
					p = p->next;
				}
				
			}
			else if( Array[k].msg.msg_type[i].compare("Random_Number") == 0)
			{
				
			// data type conversion of Array[k].msg.rand_num[i] from string to float
				stringstream ss;
				float rand_num;
				ss << Array[k].msg.message[i];
				ss >> rand_num;

				if ( Array[k].Mark )
				{
					// If Node is willing to be part of MIS..then check for rand_num
					if( Array[k].rand_num > rand_num )
					{
						// node can't become part of MIS since rand_num value is greater than at least one of the neighbour
						Array[k].Mark = false;    
						
					}
				}
			}
			else if( Array[k].msg.msg_type[i].compare("color") == 0)
			{
				Array[k].color = Array[k].msg.message[i];
			
			}
			else if( Array[k].msg.msg_type[i].compare("Node_Count") == 0)
			{

			
			}
			else
			{
				cout<< "INVALID MESSAGE TYPE" << endl;
			}
					// Deleting a message information from Inbox i.e.  message  vector, after pushing a message information in outbox
		}
		
	}
	
}
/*********************************************************************************************************
Function Name            : Display_msg

Inputs                   : Node_ID

Outputs                  : 
								
Description              :  Displaying messages of Node_ID
*********************************************************************************************************/

/*
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
*/

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

void Distributed_System::Display_msg(int k)   // k is a index of node Array[k]
{
	for( int i = 0; i < Array[k].msg.message.size(); i++)
	{
		cout << "  " << Array[k].Node_ID << "\t \t" << Array[k].msg.Message_Id[i] << " \t       " << Array[k].msg.msg_type[i] << "  \t" << Array[Array[k].msg.node_number[i]].Node_ID << " \t \t" << Array[k].msg.message[i] << endl;
		cout << endl;
	}
}

/*********************************************************************************************************
Function Name            : Simulation

Inputs                   : int Round

Outputs                  : 
								
Description              :  
*********************************************************************************************************/

void Distributed_System::Simulation( int R)
{
	// simulate for 'R' number of rounds
	for( int i = 0; i < R; i++ )         
	{
		// Receive message & process it 
		// k is the index of a Node in the Array e.g. Array[k]
		
		cout << " ROUND " << i << endl << endl;
		cout << "My ID   :     MESSAGE ID   :   MESSAGE TYPE  :     RECEIVED FROM    :   MESSAGE " << endl << endl; 
		
		// check message vector of node Array[k] and perform action as per 'msg_type'
		for( int k = 0; k < size; k++ )          
		{
			//Display_msg(k);
			Receive_message( k );			
		}

		// send Messages
		for( int k = 0; k < size; k++ )			 
		{
			for( int p = 0; p < Array[k].Outb.message.size(); p++)
			{
				Send_message( k, Array[k].Outb.node_number[p], Array[k].Outb.msg_type[p], Array[k].Outb.Message_Id[p], Array[k].Outb.message[p]);
			}
			Array[k].Outb.Message_Id.clear();
			Array[k].Outb.msg_type.clear();
			Array[k].Outb.node_number.clear();
			Array[k].Outb.message.clear();
		}
		
		// Initiate activity like broadcast, convergecast

		for( int k = 0; k < size; k++ )          
		{
			char choice;
			cout << " Would You Like To Initiate Something (y/n) " << endl;
			cin>>choice;
			
			cout << endl << endl;
			
			if( 'y' == choice )
			{
				int choice;
							
				cout << "************  CHOICES  ************" << endl;
				cout << "1. Broadcast " << endl;
				cout << "2. Maximal Independent Set " << endl << endl;
				cout << "Enter Your choice " << endl;
				cin>>choice;
							
				switch( choice )
				{
					case 1:
						{
							// Initiating Broadcast
							int Message_Id;
							string msg, msg_type;
										
							cout<< "enter msg( MESSAGE_TYPE( Broadcast_Message), Message_Id, MESSAGE )" << endl;
							cin>>msg_type>>Message_Id;
							getline(cin, msg);
							
							cout << endl;
							AdjListNode *p = Array[k].head;
							
							while( p  != NULL)
							{
								Send_message( k, p->dest, msg_type, Message_Id, msg );	// send index of source and destination node
								p = p->next;
							}
							
							break;
						}
					case 2:
						{	
						// **************Maximal Independent Set******************//
							int round = 3;
							// Uncolor all nodes
							for( int i = 0; i < size; i++)
							{
								Array[i].color = "white";
								Array[i].Mark = true;						// initially each node wanted to be a part of MIS 
							}

							// Generate random number and Send it to neighbours
							for( int j = 0; j < size; j++ )
							{
								// generating random number using rand() fuction
								float x = (j+1)*round*rand();
								Array[j].rand_num = x;
								string msg_type = "Random_Number";
									
								AdjListNode *p = Array[j].head;
								
								// Data type conversion of " Array[j].rand_num " from float to string
								stringstream ss;
								ss << Array[j].rand_num;
								std::string s( ss.str() );
								
								// "s" is message string of " Array[j].rand_num "  
								while( p != NULL )
								{
									int Message_Id = j*round;
						
									Send_message( j, p->dest, msg_type, Message_Id , s ); 
									p = p->next;
								}
							}

							// Receive Random  number from neighbours
							for( int m = 0 ; m < size; m++ )
							{
								Receive_message( m );
							}

							// Colour Marked node with "red" colour
							for( int k = 0; k < size; k++ )
							{
								if( Array[k].Mark )
								{
									Array[k].color = "red" ;
									
									AdjListNode *p = Array[k].head;
										
									while( p != NULL )
									{
										int Message_Id = rand()*(k+1);
										// informing to neighbours to color themselves with "blue" color 
										Send_message(k, p->dest, "color", Message_Id, "blue");
										p = p->next;
									}
								}
								else
								{
									if( Array[k].color.compare("white") == 0)
									{	
										Array[k].color = "red";
									}
									else 
									{
										Array[k].color = "blue";
									}
								}
							}

							// neighbours color themselves with "blue" color					
								
							for( int k = 0; k < size; k++ )
							{
								Receive_message(k);
							}
							
							// Display_graph after executing the above MIS algorithm
						
							cout << " NODE ID " << "   " << "NODE COLOR " << "   " << "Adjacent Node ID " << "   " << "Adjacent Node Colour "<<endl;

							for( int  l = 0; l < size; l++ )
							{
			
								AdjListNode *p;
								p = Array[l].head;
								if( p )
								{
								
									while( p != NULL )
									{
										cout << Array[l].Node_ID << "\t\t" << Array[l].color << "\t\t" << Array[p->dest].Node_ID << " \t \t" << Array[p->dest].color << endl;
										p = p->next;
									}
								}
								else
								{
									cout << Array[l].Node_ID << "\t\t" << Array[l].color  << endl;
								}
								 
							}
							
							break;
						}			
					default: 
						{
							cout << "**** WRONG CHOICE ****" << endl;
							break;
						}
				}
			}
		}
	}
}
