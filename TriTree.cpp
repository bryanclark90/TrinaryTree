//Programmer: Bryan K Clark
//Email: bryan.clark@email.wsu.edu
//Phone: (509)294-4161

#include "TriTree.h"
using namespace std;

//Constructor
TriTree::TriTree(void){
	m_root = NULL;
}

//Deconstructor
TriTree::~TriTree(void)
{
	deleteTree(m_root);
	m_root = NULL;
}

/*
 * @function  Node(Int dataValue)
 *
 * @param     int dataValue
 *
 * @returns   a new node with no children
 */
TriTree::Node::Node(int dataValue)
{
	Data = dataValue;
	Left = Middle = Right = NULL;
}

/*
 * @function  DeleteTree(Node* root)
 *
 * @param     Node* root
 *
 * @returns   nothing, but removes the entire tree
 */
void TriTree::deleteTree(Node* root)
{
	//if exists
	if(root) {
		//remove left subtree
		deleteTree(root->Left);
		//remove middle subtree
		deleteTree(root->Middle);
		//remove right subtree
		deleteTree(root->Right);
		//remove the root
		delete root;
	}
}

/*
 * @function   IsEmpty(void)
 *
 * @param      none
 *
 * @returns    true if tree is empty
 *             false otherwise
 */
bool TriTree::isEmpty(void)
{
	return(NULL == m_root);
}

/*
 * @function   Add(int dataValue)
 *
 * @param      int dataValue
 *
 * @returns    true if tree is empty
 *             false otherwise
 *
 *             adds a node to the Trinary tree,
 *             smaller values go left, equal 
 *             values middle, greater values go 
 *             right              
 */
bool TriTree::add(int dataValue)
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
	if(tempRoot == NULL) {
		//set root to newNode
		m_root = newNode;
		//return successful addition
		return true;
	}
	else{
		successState = insertNode(tempRoot, newNode);
		return successState;
	}
}

/*
 * @function   insertNode(Node* tempRoot, Node* newNode)
 *
 * @param      Node* tempRoot    pointer to the parent node we
 *								 are adding to
 *
 * @param      Node* newNode     the node to be added to the tree
 *
 * @returns    true if successful addition; false otherwise
 *
 *             helper function that traverses the tree, find a free
 *             location to insert beyond root              
 */
bool TriTree::insertNode(Node* tempRoot, Node* newNode)
{
	bool result = false;
	//check if value of current node and new node are identical
	if(newNode->Data == tempRoot->Data) {
		//if middle attriubute is NULL add newNode
		if(tempRoot->Middle == NULL) {
			tempRoot->Middle = newNode;
			return true;
		}
		//go to next level 
		else {
			result = insertNode(tempRoot->Middle, newNode);
			return result;
		}
	}
	//if the value of new node < current node
	else if(newNode->Data < tempRoot->Data) {
		//if left attriubute is NULL add newNode
		if(tempRoot->Left == NULL){
			tempRoot->Left = newNode;
			return true;
		}
		//go to next level 
		else {
			result = insertNode(tempRoot->Left, newNode);
			return result;
		}
	}
	//if the value of new node > current node
	else if(newNode->Data > tempRoot->Data) {
		//if right attriubute is NULL add newNode
		if(tempRoot->Right == NULL) {
			tempRoot->Right = newNode;
			return true;
		}
		//go to next level 
		else {
			result = insertNode(tempRoot->Right, newNode);
			return result;
		}
	}
	//else return false
	else {
	 return result;
	}
}

/*
 * @function   Remove(int dataValue)
 *
 * @param      int dataValue     Value to be removed
 *
 * @returns    true if successful removal; false otherwise
 *
 *             function that finds the node to be found and removed              
 */
bool TriTree::remove(int dataValue)
{
	Node* parent = m_root;
	Node* current = m_root;
	bool removed;
	if(isEmpty()) {
		//throw flag
		cout << "Tree is empty, can not remove" << dataValue <<  " from a tree that doesn't exist" << endl;
		return false;
	}
	else {
		//recursively go through to locate it
		while(current->Data != dataValue) {
			//if not equal check if less than current data
			if(dataValue < current->Data) {
				//update parent to current position
				//will be redundant on first pass
				parent = current;
				//update current to LEFT value
				if(current->Left != NULL) {
					current = current->Left;
				}
				else{
					cout << dataValue << " is not in tree!" << endl;
					return false;
				}
			}
			//if not equal check if greater than current data
			else if(dataValue > current->Data) {
				//update parent to current position
				//will be redundant on first pass
				parent = current;
				//update current to RIGHT value
				if(current->Right != NULL) {
					current = current->Right;
				}
				else {
					cout << dataValue << " is not in tree!" << endl;
					return false;
				}
			}
		}
		//now we can remove it
		removed = removeNode(current, parent);
		return removed;
	}

}

/*
 * @function  removeNode(Node* tempRoot, Node* newNode)
 *
 * @param      Node* tempRoot    pointer to the parent node we
 *								 are adding to
 *
 * @param      Node* newNode     the node to be added to the tree
 *
 * @returns    true if successful addition; false otherwise
 *
 *             helper function that traverses the tree, find a free
 *             location to insert beyond root              
 */
//helper function that rearranges the tree
bool TriTree::removeNode(Node* current, Node* parent)
{
	Node* previous = parent;
	//if current is the middle node of the tree
	//find the "last one" and remove it
	if(current->Middle != NULL) {
		while(current->Middle) 	{
			previous = current;
			current = current->Middle;
		}
		previous->Middle = NULL;
		delete(current);
		return true;
	}
	// if both node left and right are empty you empty the node	
	else if((current->Left == NULL)&&(current->Right == NULL)) {
		//if root
		if(current == m_root) {
			m_root = NULL;
			return true;
		}
		//if the parent[grandparent] of the CURRENT NODE[parent] points from the left
		//then set left to null
		if(parent->Left == current) {
			parent->Left = NULL;
		}
		else {
			parent->Right = NULL;
		}
		delete(current);
		return true;
	}
	//current is node to remove
	// if left child of node for removal node is not null
	else if(current->Left != NULL) {
		
		Node* subtree = previous = current->Left;
		//if subtree has no right branch, just
		//move everything up and connect right branch
		if(subtree->Right == NULL) {
			current->Data = subtree->Data;
			current->Left = subtree->Left;
			current->Middle = subtree->Middle;
		}
		else {
			//find the largest of the left subtree
			while(subtree->Right != NULL) {
				previous = subtree;
				subtree = subtree->Right;
			}
			//move subtree data up, truncate it out
			current->Data = subtree->Data;
			previous->Right = subtree->Left;
		}
		return true;
	}
	// if right exists but left doesn't just move everything up
	else if(current->Right != NULL) {
		previous = current; 
		current = current->Right;
		previous->Data = current->Data;
		previous->Left = current->Left;
		previous->Right = current->Right;
		delete(current);
		return true;
	}
	return false;
}

//print displays out 
void TriTree::displayContents(ostream& outputStream)
{
	//print out contents
	outputStream << "trinary tree: ";
	//start at root
	displayContents(m_root, outputStream);
	if(m_root == NULL){
		outputStream << "The tree is empty!" << endl;
	}
	outputStream << endl;
}

//helper function to recursively build tree
void TriTree::displayContents(Node* node, ostream& outputStream)
{
	if (node){
		displayContents(node->Left, outputStream);
		
		// Display the numerical value for this node
		std::ostringstream out;
		out << node->Data << " ";
		std::cout << out.str();

		displayContents(node->Middle, outputStream);
		// Display the entire right subtree
		displayContents(node->Right, outputStream);
	}
	
}
