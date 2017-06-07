#include <fstream>
#include <iostream>
#include <string>

#include "BitTree.h"

using namespace std;

int main() {

	BitTree bt;
	bt.addRoot(10);
	bt.addLeftChild(1, 20);
	bt.addRightChild(1, 30);

	bt.addLeftChild(2,40);
	bt.addRightChild(2,50);

	bt.addLeftChild(3,60);
	bt.addRightChild(3,70);

	bt.addLeftChild(4,80);
	bt.addRightChild(4,90);
	

	bt.addRightChild(6,130);
	bt.addRightChild(7,150);


	bt.addLeftChild(8, 160);
	bt.addRightChild(8, 170);

	bt.addLeftChild(13, 1000);


	cout << "level of node with key 0: " << bt.getLevel(0) << endl;
	cout << "level of node with key 1: " << bt.getLevel(1) << endl;
	cout << "level of node with key 8: " << bt.getLevel(8) << endl;
	cout << "level of node with key 838: " << bt.getLevel(838) << endl << endl;
	cout << "max level if tree: " << bt.getMaxLevel() << endl;

	cout << bt;

	bt.toDot("/home/cecilia/bittrees/tree.dot");

	return 0;
}