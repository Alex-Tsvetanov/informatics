#include <iostream>

using namespace std;

#include "binary_search_tree.h"

int main ()
{
	binary_search_tree <int> BST;
	cout << BST.add (1) << "\n";
	cout << BST.add (34531) << "\n";
	cout << BST.add (31) << "\n";
	cout << BST.add (321) << "\n";
	cout << BST.add (11) << "\n";
	cout << BST.add (31) << "\n";
	cout << BST.add (31) << "\n";
	cout << BST.add (0) << "\n";
	cout << "-----------------------\n";
	cout << BST.find (1) << "\n";
	cout << BST.find (34531) << "\n";
	cout << BST.find (0) << "\n";
	cout << BST.find (9) << "\n";
}