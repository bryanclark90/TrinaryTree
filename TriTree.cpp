//Programmer: Bryan K Clark
//Email: bryan.clark@email.wsu.edu
//Phone: (509)294-4161

#include "TriTree.h"
using namespace std;

//Constructor
TriTree::TriTree(void)
{
	m_root = NULL;
}
//Deconstructor
TriTree::~TriTree(void)
{
	DeleteTree(m_root);
	m_root = NULL;
}
//Node Initialization
TriTree::Node::Node(int dataValue)
{
	Data = dataValue;
	Left = Middle = Right = NULL;
}
//Delete Tree shall remove all branches of the tree recursively
void TriTree::DeleteTree(Node* root)
{
	//if exists
	if(root)
	{
		//remove left subtree
		DeleteTree(root->Left);
		//remove middle subtree
		DeleteTree(root->Middle);
		//remove right subtree
		DeleteTree(root->Right);
		//remove the root
		delete root;
	}
}
//checks if tree is empty
bool TriTree::IsEmpty(void)
{
	return(NULL == m_root);
}
//adds a node to the Trinary Tree
//values smaller than current node go left
//values equal go middle
//values greater than go right
bool TriTree::Add(int dataValue)
{
	//initialize success state to false
	bool successState = false;

	//initialize a new node
	Node* newNode = new Node(dataValue);
	newNode->Left = NULL;
	newNode->Middle = NULL;
	newNode->Right = NULL;
	
	//start at root, use a pointer to preserve root
	Node* tempRoot = m_root;

	//if root is empty
	if(tempRoot == NULL)
	{
		//set root to newNode
		m_root = newNode;
		//return successful addition
		return true;
	}
	//if root is not empty
	else
	{
		successState = insertNode(tempRoot, newNode);
		return successState;
	}
}
//helper function that traverses the tree
//finds free location to insert beyond root
bool TriTree::insertNode(Node* tempRoot, Node* newNode)
{
	bool result = false;
	//check if value of current node and new node are identical
	if(newNode->Data == tempRoot->Data)
	{
		//if middle attriubute is NULL add newNode
		if(tempRoot->Middle == NULL)
		{
			tempRoot->Middle = newNode;
			return true;
		}
		//find next available free location 
		else
		{
			result = insertNode(tempRoot->Middle, newNode);
			return result;
		}
	}
	//if the value of new node < current node
	else if(newNode->Data < tempRoot->Data)
	{
		//if left attriubute is NULL add newNode
		if(tempRoot->Left == NULL)
		{
			tempRoot->Left = newNode;
			return true;
		}
		//find next available free location 
		else
		{
			result = insertNode(tempRoot->Left, newNode);
			return result;
		}
	}
	//if the value of new node > current node
	else if(newNode->Data > tempRoot->Data)
	{
		//if right attriubute is NULL add newNode
		if(tempRoot->Right == NULL)
		{
			tempRoot->Right = newNode;
			return true;
		}
		//find next available free location 
		else
		{
			result = insertNode(tempRoot->Right, newNode);
			return result;
		}
	}
	//else return false
	else
	{
	 return result;
	}
}
//returns true if the value was found and removed, false if it was not removed or found
bool TriTree::Remove(int dataValue)
{
	Node* parent = m_root;
	Node* current = NULL;
	Node* removalNode = NULL;
	bool removed;
	if(IsEmpty() == true)
	{
		//throw flag
		printf("Tree is empty, can not remove %d from a tree that doesn't exist.\n", dataValue);
		return false;
	}
	else
	{
		//if data is at root
		if(m_root->Data == dataValue)
		{
			//in removeNode function current[here] = parent[there], and parent[here] = grandparent[there].
			//confusing i know but based on two trains of though.
			current = parent;
			removed = removeNode(current, parent, dataValue);
			return removed;
		}
		else
		{
			//check if data to be removed AND is not at root is less than or greater than root data
			if(dataValue < parent->Data)
			{
				//set the next check point to the left
				current = parent->Left;
			}
			else if(dataValue > parent->Data)
			{
				//set the next check point to the right
				current = parent->Right;
			}
			//recursively go through to locate it
			bool keepGoing = true;
			while(keepGoing)
			{
				//if equal(meaning data is at the node)
				if(current->Data == dataValue)
				{
					//we found the location we wanted
					keepGoing = false;
				}
				//if not equal check if less than current data
				else if(dataValue < current->Data)
				{
					//update parent to current position
					parent = current;
					//update current to LEFT value
					current = current->Left;
					//don't break while loop, we haven't found the correct node
					keepGoing = true;
				}
				//if not equal check if greater than current data
				else if(dataValue > current->Data)
				{
					//update parent to current position
					parent = current;
					//update current to RIGHT value
					current = current->Right;
					//don't break while loop, we haven't found the correct node
					keepGoing = true;
				}
			}
			//now we can remove it
			//in removeNode function current[here] = parent[there], and parent[here] = grandparent[there].
			//confusing i know but based on two trains of though.
			removed = removeNode(current, parent, dataValue);
			return removed;
		}
	}

}
//helper function that rearranges the tree
bool TriTree::removeNode(Node* parent, Node* grandparent,  int dataValue)
{
	Node* previous;
	Node* current;
		//if current is middle
		if(parent->Middle != NULL)
		{
			current = previous = parent;
			while(current->Middle)
			{
				previous = current;
				current = current->Middle;
			}
			previous->Middle = NULL;
		//	DeleteTree(current);
			return true;
		}
		// if both node left and right are empty you empty the node
		else if((parent->Left == NULL)&&(parent->Right == NULL)) 
		{
			//throw flag if only one item in tree
			if(parent == m_root)
			{
				m_root = NULL;
				return true;
			}
			//if the parent[grandparent] of the CURRENT NODE[parent] points from the left
			//then set left to null
			if(grandparent->Left->Data == parent->Data)
			{
				grandparent->Left = NULL;
			}
			//if the parent[grandparent] of the CURRENT NODE[parent] points from the left
			//then set left to null
			else if(grandparent->Right->Data == parent->Data)
			{
				grandparent->Right = NULL;
			}
			parent->Data = NULL;
			return true;
		}
		// if left is not null
		else if((parent->Left != NULL)) 
		{
			
			current = previous = parent->Left; // temp and temp prev = root temp
			// find largest value on the left side and make new root
			//if doesn't exist
			if(current->Right == NULL)
			{
				parent->Data = current->Data;
				parent->Left = current->Left;
				parent->Middle = current->Middle;
			//	DeleteTree(current);
				return true;
			}
			else
			{
				//if does
				while( current->Right != NULL) 
				{
					previous = current;
					current = current->Right;
				}
				// second largest value on left side is now largest
				parent->Data = current->Data;
				// where that value was is now null
				previous->Right = NULL;
				// delete node that value was found in
				//DeleteTree(current); 
				return true;
			}

		}
		// if right and not left
		else if((parent->Left == NULL)&&(parent->Right != NULL)) 
		{
			
			current = parent->Right;
			// replace with right value, delete the old one.
			parent->Data = current->Data; 
			parent->Left = current->Left;
			parent->Middle = current->Middle;
			parent->Right = current->Right;
			//DeleteTree(current);
			return true;
		}
		//check if more middle values
		//if not remove current node
}
//print displays out 
void TriTree::DisplayContents(ostream& outputStream)
{
	//print out contents
	outputStream << "trinary tree: ";
	//start at root
	DisplayContents(m_root, outputStream);
	if(m_root == NULL){
		outputStream << "The tree is empty!" << endl;
	}
	outputStream << endl;
}
//helper function to recursively build tree
void TriTree::DisplayContents(Node* node, ostream& outputStream)
{
	if (node){
		DisplayContents(node->Left, outputStream);
		
		// Display the numerical value for this node
		std::ostringstream out;
		out << node->Data << " ";
		std::cout << out.str();

		DisplayContents(node->Middle, outputStream);
		// Display the entire right subtree
		DisplayContents(node->Right, outputStream);
	}
	
}
