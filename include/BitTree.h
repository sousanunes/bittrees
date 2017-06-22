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
	std::map<unsigned int,unsigned int> nodes;
	std::string print(const std::string& prefix, unsigned int key) const;

	/* Private iterators */
	std::map<unsigned int, unsigned int>::const_iterator nodes_cbegin()	const;
	std::map<unsigned int, unsigned int>::const_iterator nodes_cend()	const;

public:
	BitTree(){};
	BitTree(const BitTree& bitTree);

	/* Setters */
	void addRoot(unsigned int value);
	void addLeftChild(unsigned int parentKey,	unsigned int value);
	void addRightChild(unsigned int parentKey,	unsigned int value);

	/* Getters */
	bool			hasKey(unsigned int key) const;
	unsigned int	getValue(unsigned int key) const;
	unsigned int	getNumberNodes() const;
	unsigned int	getMaxLevel() const;
	bool			isEmpty() const;

	static unsigned int getLevel(unsigned int key);
	static unsigned int getParentKey(unsigned int key);
	static unsigned int getChildKey(unsigned int key, unsigned int childIndex);
	
	static unsigned int isRoot(unsigned int key);
	static unsigned int isLeftChild(unsigned int key);
	static unsigned int isRightChild(unsigned int key);
	
	static unsigned int getLeftChildKey(unsigned int key);
	static unsigned int getRightChildKey(unsigned int key);
	
	std::string toDot(const std::string& suffix) const;
	std::string print(const std::string& prefix="") const;
	friend std::ostream& operator<< (std::ostream& out, const BitTree& bt);
};

#endif