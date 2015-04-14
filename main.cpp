//Programmer: Bryan K Clark
//Email: bryan.clark@email.wsu.edu
//Phone: (509)294-4161

#include "TriTree.h"


using namespace std;

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
		cout << "  4 = Add sample numbers: 5, 4, 9, 5, 7, 2, 2" << endl; 
		cout << "  5 = Quit" << endl;
		cout << "  6 = Programmer info" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;

		int number = -1;
		cin >> number;
		switch(number){
			//add a number
			case 1:
				number = -1;
				while (number < 0 || number > 999) {
					cout << "Enter an integer in the range [0,999]: ";
					cin >> number;
					cout << endl;
				}
				//add number to tree
				if (tree.Add(number)) {
					cout << "Added " << number << endl;
				}
				else{
					cout << "Failed to add " << number << endl;
				}
				break;
			//remove the number
			case 2:
				number = -1;
				cout << "Enter a number to remove from the tree: ";
				cin >> number;
				cout << endl;
				//remove the number from tree
				if (tree.Remove(number)) {
					cout << number << " was removed" << endl;
				}
				else {
					cout << "Value was NOT removed because it was not found in the tree" << endl;
				}
				break;
			//display contents
			case 3:
				tree.DisplayContents(cout);
				break;
			//add sample numbers to tree
			case 4:
				tree.Add(5);
				tree.Add(4);
				tree.Add(9);
				tree.Add(5);
				tree.Add(7);
				tree.Add(2);
				tree.Add(2);
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
