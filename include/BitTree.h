#ifndef BITTREE_H
#define BITTREE_H

#include <map>

class BitTree
{

private:

	/* The KEY is the node indentifier.
	* Left  child key = parent key * 2
	* Right child key = parent key * 2 + 1
	* The VALUE is the node content. It can be used an index to some other structure. */
	std::map<int,int> nodes;
	void print(std::ostream& out, const std::string& prefix, int key) const;

public:

	/* Setters */
	void addRoot(int value);
	void addLeftChild(int parentKey,	int value);
	void addRightChild(int parentKey,	int value);

	/* Getters */
	bool hasKey(int key) const;
	int  getValue(int key) const;
	int  getNumberNodes() const;
	int  getMaxLevel() const;

	static int getLevel(int key);
	static int getLeftChildKey(int key);
	static int getRightChildKey(int key);
	
	std::string toDot(const std::string& suffix) const;
	friend std::ostream& operator<< (std::ostream& out, const BitTree& bt);
};

#endif