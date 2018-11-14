// 2-3 tree class

#ifndef TWO_THREE_TREE
#define TWO_THREE_TREE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class twoThreeTree{
    public:
        twoThreeTree();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
        double TotalTime(ifstream & input);
    private:
    struct node{
            node(const string &lk, const string &rk, node *l, node *c, node *r)
                :lkey(lk), rkey(rk), left(l), center(c), right(r){
                leftLines.resize(0), leftLines.resize(0);
            }
            string lkey; //left word in node
            string rkey; //right word in node
            node * left;
            node * center;
            node * right;
            vector<int> leftLines; //left word's line numbers it appears in
			vector<int> rightLines; //right word's line numbers it appears in


			node * lchild() { return left; }
			node * rchild() { return right; }
			node * cchild() { return center; }
			string getlkey() { return lkey; }  // return left word
			vector<int> getleftLines() { return leftLines; }  // return left word's line numbers
			string getrkey() { return rkey; }  // return right word
			vector<int> getrightLines() { return rightLines; }  // return right word's line numbers
			void setLeft(string k, vector<int> l) { lkey = k; leftLines = l; }
			void setRight(string k, vector<int> l) { rkey = k; rightLines = l; }
			void setLeftChild(node * l) { left = l; }
			void setCenterChild(node * c) { center = c; }
			void setRightChild(node * r) { right = r; }
			bool isLeaf() { return left == NULL; }
			node * add(node * t);
			
        };
        node * root;
        node * insertHelper(const string &X, int line, node * t, int &distWords);
		bool containsHelper(const string & x, node * t, node* &result) const;
		void printTreeHelper(node *t, ostream & out) const;
		int findHeight(node *t);
		
        
};

#endif
