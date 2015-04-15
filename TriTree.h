//Programmer: Bryan K Clark
//Email: bryan.clark@email.wsu.edu
//Phone: (509)294-4161

#include <iostream>
#include <queue>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>


//create a Trinary Tree class
class TriTree
{
private:
	struct Node
	{
		int Data;
		Node* Left;
		Node* Middle;
		Node* Right;

		Node(int dataValue);
	};

	//pointer to root node
	//if NULL the tree is empty
	Node* m_root;

	void deleteTree(Node* n);
	void displayContents(Node* node, std::ostream& outputStream);
	// Adds in a new node
	bool insertNode(Node* TempRoot, Node* NewNode );
	//returns true if the node is successfully removed
	bool removeNode(Node* parent, Node* grandparent);
public:
	//constructor and deconstructor
	 TriTree(void);
	~TriTree(void);


	//returns true if successfully added
	bool add(int dataValue);
	//returns true if  the value was found and removed, else false
	bool remove(int dataValue);
	//checks if tree is empty. True if empty
	bool isEmpty(void);

	void displayContents(std::ostream& outputStream);

};
