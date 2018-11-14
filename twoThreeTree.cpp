// 2-3 tree class implementations

#include "twoThreeTree.h"
#include "time.h"
#include <iomanip>
#include <sstream>

// Constructor
twoThreeTree::twoThreeTree() {
	root = NULL;
}

// Returns true if there are no nodes in the tree
bool twoThreeTree::isEmpty() {
	return root == NULL;
}

//Used to implement the search function in the main
//program.
void twoThreeTree::contains() const {
	string input;
	node *foundNode = NULL;
	cout << "Search word: ";
	cin >> input;
	if (containsHelper(input, root, foundNode)) {
		//word is the left key
		if (!foundNode->getlkey().empty() && input == foundNode->getlkey())
		{
			cout << "Line Numbers: " << foundNode->leftLines[0];
			for (unsigned i = 1; i < foundNode->leftLines.size(); i++)
				cout << ", " << foundNode->leftLines[i];
			cout << '\n';
		}
		//word is the right key
		else if (!foundNode->getrkey().empty())
		{
			cout << "Line Numbers: " << foundNode->rightLines[0];
			for (unsigned i = 1; i < foundNode->rightLines.size(); i++)
				cout << ", " << foundNode->rightLines[i];
			cout << '\n';
		}
	}
	else
		cout << '\"' << input << "\" is not in the document\n";
}

//Prints the index to the supplied receiver, either
//cout or the output file
void twoThreeTree::printTree(ostream & out) const {
	out << "Two-Three Tree Index:\n-------------------------\n";
	printTreeHelper(root, out);
}

double twoThreeTree::TotalTime(ifstream & input) {
	int line = 1, distWords = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	node * treeRoot = NULL;
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (unsigned i = 0; i < tempLine.length(); i++) {
			//Insert valid chars into tempWord until a delimiter( newline or space) is found
			while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length()) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			//Trim any punctuation off end of word. Will leave things like apostrophes
			//and decimal points
			while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() - 1);

			if (tempWord.length() > 0)
			{
				//Once word is formatted,call insert with the word, the line of the input
				//file it came from, the root of our tree, and the distinct word counter
				treeRoot = insertHelper(tempWord, line, treeRoot, distWords);
				//Increment our total number of words inserted
				//Clear out tempWord so we can use it again
				tempWord.clear();
			}

		}
		line++;
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;

	return totalTime;
}

//Receives the specified input file and constructs 
//the actual tree. Prints a message when finished.
void twoThreeTree::buildTree(ifstream & input) {
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	node * treeRoot = NULL;
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (unsigned i = 0; i < tempLine.length(); i++) {
			//Insert valid chars into tempWord until a delimiter( newline or space) is found
			while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length()) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			//Trim any punctuation off end of word. Will leave things like apostrophes
			//and decimal points
			while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() - 1);

			if (tempWord.length() > 0)
			{
				//Once word is formatted,call insert with the word, the line of the input
				//file it came from, the root of our tree, and the distinct word counter
				treeRoot = insertHelper(tempWord, line, treeRoot, distWords);
				//Increment our total number of words inserted
				numWords++;
				//Clear out tempWord so we can use it again
				tempWord.clear();
			}

		}
		line++;
	}
	root = treeRoot;
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	treeHeight = findHeight(treeRoot);

	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords << endl;

	cout << setw(40) << std::left
		<< "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left
		<< "Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
		<< "Height of 2-3 Tree is : " << treeHeight << endl;

}


//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
twoThreeTree::node * twoThreeTree::insertHelper(const string &x, int line, node * t, int &distWord) {
	//Empty tree: create a leaf node for root
	node * retval;
	if (t == NULL) {
		node * temp = new node(x, "", NULL, NULL, NULL);
		temp->leftLines.push_back(line);
		distWord++;
		return temp;
	}
	//At leaf node: insert here
	if (t->isLeaf())
	{
		if (!t->getlkey().empty() && x == t->getlkey())
		{
			t->leftLines.push_back(line);
			return t;
		}
		else if (!t->getrkey().empty() && x == t->getrkey())
		{
			t->rightLines.push_back(line);
			return t;
		}
		else
		{
			node * temp = new node(x, "", NULL, NULL, NULL);
			temp->leftLines.push_back(line);
			distWord++;
			return t->add(temp);
		}
	}
	//Add to internal node
	//Insert left
	if (x.compare(t->getlkey()) < 0) {
		if (x != t->getlkey())
		{
			retval = insertHelper(x, line, t->lchild(), distWord);
			if (retval == t->lchild())
				return t;
			else
			{
				//retval->leftLines.push_back(line);
				//distWord++;
				return t->add(retval);
			}
		}
	}
	else if ((t->getrkey().empty()) || (x.compare(t->getrkey()) < 0)) {
		if (x != t->getrkey())
		{
			retval = insertHelper(x, line, t->cchild(), distWord);
			if (retval == t->cchild())
				return t;
			else
			{
				//retval->leftLines.push_back(line);
				//distWord++;
				return t->add(retval);
			}
		}
	}
	//Insert right
	else {
		if (x != t->getlkey() && x != t->getrkey())
		{
			retval = insertHelper(x, line, t->rchild(), distWord);
			if (retval == t->rchild())
				return t;
			else
			{
				//retval->leftLines.push_back(line);
				//distWord++;
				return t->add(retval);
			}
		}
	}
}



// Add a new key/value pair to the node. There might be a subtree
// associated with the record being added. This information comes
// in the form of a 2-3 tree node with one key and a (possibly null)
// subtree through the center pointer field.
twoThreeTree::node * twoThreeTree::node::add(node * it) {
	//Only one key, add here
	if (this->rkey.empty()) {
		if (this->lkey.compare(it->getlkey()) < 0) {
			this->rkey = it->getlkey();
			this->rightLines = it->getleftLines();
			this->center = it->lchild();
			this->right = it->cchild();
		}
		else {
			this->rkey = this->lkey;
			this->rightLines = this->leftLines;
			this->right = this->center;
			this->lkey = it->getlkey();
			this->leftLines = it->getleftLines();
			this->center = it->cchild();
		}
		return this;
	}
	// Add left
	else if (this->lkey.compare(it->getlkey()) >= 0) {
		node * N1 = new node(this->lkey, "", it, this, NULL);
		N1->leftLines = this->leftLines;
		N1->rightLines.clear();
		it->setLeftChild(this->left);
		this->left = this->center;
		this->center = this->right;
		this->right = NULL;
		this->lkey = this->rkey;
		this->leftLines = this->rightLines;
		this->rkey = "";
		this->rightLines.clear();
		return N1;
	}
	// Add center
	else if (this->rkey.compare(it->getlkey()) >= 0) {
		node * N1 = new node(this->rkey, "", it->cchild(), this->right, NULL);
		N1->leftLines = this->rightLines;
		N1->rightLines.clear();
		it->setCenterChild(N1);
		it->setLeftChild(this);
		this->rkey = "";
		this->rightLines.clear();
		this->right = NULL;
		return it;
	}
	// Add right
	else {
		node * N1 = new node(this->rkey, "", this, it, NULL);
		N1->leftLines = this->rightLines;
		N1->rightLines.clear();
		it->setLeftChild(this->right);
		this->right = NULL;
		this->rkey = "";
		this->rightLines.clear();
		return N1;
	}
}


//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool twoThreeTree::containsHelper(const string & x, node * t, node* &result) const {
	if (t == NULL)                            // val not found
		return false;
	if (x.compare(t->getlkey()) == 0) {
		result = t;
		return true;
	}
	if ((!t->getrkey().empty()) && (x.compare(t->getrkey()) == 0)) {
		result = t;
		return true;
	}
	if (x.compare(t->getlkey()) < 0) // Search left
		return containsHelper(x, t->lchild(), result);
	else if (t->getrkey().empty()) // Search center
		return containsHelper(x, t->cchild(), result);
	else if (x.compare(t->getrkey()) < 0) // Search center
		return containsHelper(x, t->cchild(), result);
	else return containsHelper(x, t->rchild(), result); // Search right
}

//Called by printTree(), does the actual formatted printing
void twoThreeTree::printTreeHelper(node *t, ostream & out) const {
	if (t == NULL)
		return;
	else {
		printTreeHelper(t->lchild(), out);
		
		//print left key and lines if it exists
		if (!t->lkey.empty())
		{
			out << setw(30) << std::left;
			out << t->getlkey() << " " << t->leftLines[0];
			for (unsigned i = 1; i < t->leftLines.size(); i++)
				out << ", " << t->leftLines[i];
			out << endl;
		}
		//print right key and lines if it exists
		if (!t->rkey.empty())
		{
			out << setw(30) << std::left;
			out << t->getrkey() << " " << t->rightLines[0];
			for (unsigned i = 1; i < t->rightLines.size(); i++)
				out << ", " << t->rightLines[i];
			out << endl;
		}
		printTreeHelper(t->rchild(), out);
	}
}

//Returns height of tree. If tree has only one node, height is 1    
int twoThreeTree::findHeight(node *t) {
	if (t == NULL)
		return 0;
	else {
		int leftHeight = findHeight(t->left), centerHeight = findHeight(t->center), rightHeight = findHeight(t->right);
		if (leftHeight > rightHeight && leftHeight > centerHeight)
			return(leftHeight + 1);
		else if (rightHeight > leftHeight && rightHeight > centerHeight)
			return(rightHeight + 1);
		else
			return(centerHeight + 1);
	}
}
