// Matt Schafer, Chris Tran

//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST and a 2-3 Tree

#include <iostream>
#include <fstream>
#include "bst.h"
#include "twoThreeTree.h"
using namespace std;

int main(int argc, char* argv[]) {
	char option;
	int choice;
	if (argc != 2) {
		cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
		return 1;
	}

	cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree" << endl;
	cin >> option;
	if (option == 'a') {
		ifstream input(argv[1]);
		BST myTree;

		if (input.is_open()) {
			myTree.buildTree(input);
			input.close();
			while (1) {
				choice = 0;
				cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
				cin >> choice;

				//Print index
				if (choice == 1)
					myTree.printTree(cout);

				//Search index for a word
				else if (choice == 2)
					myTree.contains();

				//Save index
				else if (choice == 3) {
					string outputFile;
					cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
					cin >> outputFile;
					ofstream output(outputFile.c_str());
					myTree.printTree(output);
					output.close();
					cout << "Saved\n";
				}

				//Quit	
				else
					break;
			}
		}
		else {
			cout << "Invalid File Name. Restart Program.\n";
			return 2;
		}
	}
	else if (option == 'b') {
		ifstream input(argv[1]);
		twoThreeTree myTree;

		if (input.is_open()) {
			myTree.buildTree(input);
			input.close();
			while (1) {
				choice = 0;
				cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
				cin >> choice;

				//Print index
				if (choice == 1)
					myTree.printTree(cout);

				//Search index for a word
				else if (choice == 2)
					myTree.contains();

				//Save index
				else if (choice == 3) {
					string outputFile;
					cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
					cin >> outputFile;
					ofstream output(outputFile.c_str());
					myTree.printTree(output);
					output.close();
					cout << "Saved\n";
				}

				//Quit
				else
					break;
			}
		}
	}
	else if (option == 'c') {
		ifstream input(argv[1]);
		BST myTree1;
		twoThreeTree myTree2;

		if (input.is_open()) {
			cout << "Total time taken by BST: " << myTree1.TotalTime(input) << endl;
			cout << "Total time taken by 2-3 Tree: " << myTree2.TotalTime(input) << endl;
			input.close();
		}
	}
	return 0;
}
