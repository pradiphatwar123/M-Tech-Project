#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
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

int Distributed_System::Send_message(int from, int to, string msg)
{
	int f = find_node(from), t = find_node(to);
	
	if(f==-1 || t==-1) 
		return  -1;
	Array[t].message.push_back(msg);
	Array[t].node_number.push_back(f);
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
	else if(Array[n].message.size() == 0)
	{
		cout<<"No message\n";
	}
	else
	{
		cout<<Array[n].Node_ID<<endl;
		for(int i = 0; i < Array[n].message.size(); i++)
		{
			
			cout<<"\t"<<Array[Array[n].node_number[i]].Node_ID<<":\t";
			cout<<Array[n].message[i]<<endl;
		}
	}
}
