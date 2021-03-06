//Programmer: Bryan K Clark
//Email: bryan.clark@email.wsu.edu
//Phone: (509)294-4161

#include "TriTree.h"


using namespace std;

int myatoi(char* str)
{
	int output = 0;
	int i=0;
	while( 48 <= str[i] && str[i] <=57 ){
		
		output = output*10 + (str[i] - 48) ;
		i++;
	}
	
	return output;
}

int main(void)
{
	TriTree tree;

	while (true)
	{
		// Display a menu with options
		cout << "-------------------------------------------------" << endl;
		cout << "--------------- Trinary Tree Menu ---------------" << endl;
		cout << "  1 = Add a number to the trinary tree" << endl;
		cout << "  2 = Remove a number from the trinary tree" << endl;
		cout << "  3 = Display the trinary tree as a list" << endl;
		cout << "      built using in-order traversal" << endl;
		cout << "  4 = Add sample numbers to tree:" << endl;
		cout << "                      add 5, 4, 9, 5, 7, 2, 2" << endl; 
		cout << "  5 = Quit" << endl;
		cout << "  6 = Programmer info" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;

		char input[10];
		cin >> input;
		int number = myatoi(input);
		switch(number) {
			//add a number
			case 1:
				//number = -1;
				while (number < 0 || number > 999) {
					cout << "Enter an integer in the range [0,999]: ";
					cin >> number;
					cout << endl;
				}
				//add number to tree
				if (tree.add(number)) {
					cout << "Added " << number << endl;
				}
				else{
					cout << "Failed to add " << number << endl;
				}
				break;
			//remove the number
			case 2:
				//number = -1;
				cout << "Enter a number to remove from the tree: ";
				cin >> number;
				cout << endl;
				//remove the number from tree
				if (tree.remove(number)) {
					cout << number << " was removed" << endl;
				}
				else {
					cout << "Value was NOT removed because it was not found in the tree" << endl;
				}
				break;
			//display contents
			case 3:
				tree.displayContents(cout);
				break;
			//add sample numbers to tree
			case 4:
				tree.add(5);
				tree.add(4);
				tree.add(9);
				tree.add(5);
				tree.add(7);
				tree.add(2);
				tree.add(2);
				cout << "List added successfully to tree!" << endl;
				break;
			//quit
			case 5:
				break;
			//display my personal info
			case 6:
				cout << endl;
				cout << "=================================================" << endl;
				cout << "============== My Contact Info ==================" << endl;
				cout << "Programmer:			Bryan Kieth Clark" << endl;
				cout << "Email:			bryan.clark@email.wsu.edu" << endl;
				cout << "Phone:			            (509)294-4161" << endl;
				cout << "=================================================" << endl;
				cout << "=================================================" << endl;
				cout << endl;
				break;
			default:
				cout << "Invalid option!" << endl << endl;
				break;
		}
	}
	return 0;
}
