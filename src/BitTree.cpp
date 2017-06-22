#include "BitTree.h"
#include "Logger.h"
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

/**********
* PRIVATE *
***********/

std::string BitTree::print(const std::string& prefix, unsigned int key) const
{
	if ( this->isEmpty() ) return prefix + "{}";

	std::string toPrint(prefix + std::to_string(key));
	std::string out;

	if ( this->hasKey(key) )
		{
			// Print current key and action
			toPrint += ": " + std::to_string(this->getValue(key));
			out += toPrint + "\n";

			std::string toAdd;
			for (unsigned int j(0); j<(toPrint.size()/2 - 3); j++) toAdd += " ";
			toAdd += "|   ";

			// Print left child
			out += this->print(prefix + toAdd, BitTree::getLeftChildKey(key));
			
			// Print right child
			out += this->print(prefix + toAdd, BitTree::getRightChildKey(key));

			return out;
		}


	// Print current key without action
	out += toPrint + "\n";
	return out;
}

/* Private iterators */
std::map<unsigned int, unsigned int>::const_iterator BitTree::nodes_cbegin() const { return this->nodes.cbegin(); }
std::map<unsigned int, unsigned int>::const_iterator BitTree::nodes_cend()	 const { return this->nodes.cend(); }

/*********
* PUBLIC *
**********/
BitTree::BitTree(const BitTree& bitTree) { this->nodes.insert(bitTree.nodes_cbegin(), bitTree.nodes_cend()); }

/* Setters */
void BitTree::addRoot(unsigned int value){ this->nodes[1] = value; }
void BitTree::addLeftChild(unsigned int parentKey,	unsigned int value)
{
	if ( this->hasKey(parentKey) )
		{
			this->nodes.insert(std::make_pair(parentKey << 1, value));
			return;
		}
}
void BitTree::addRightChild(unsigned int parentKey,	unsigned int value)
{
	if ( this->hasKey(parentKey) )
		{
			this->nodes.insert(std::make_pair((parentKey << 1) | 1, value));
			return;
		}
}

/* Getters */
bool BitTree::hasKey(unsigned int key) const { return this->nodes.find(key) != this->nodes.cend(); }
unsigned int BitTree::getValue(unsigned int key) const
{
	if ( this->hasKey(key) )
		return this->nodes.find(key)->second;
	return 0;
}
unsigned int BitTree::getNumberNodes() const { return this->nodes.size(); }
unsigned int BitTree::getMaxLevel() const
{
	if (this->getNumberNodes() == 0)
		return -1;
	return log2(this->nodes.rbegin()->first);
}
bool BitTree::isEmpty() const { return this->getNumberNodes() == 0; }

/* Static */
unsigned int BitTree::getLevel(unsigned int key)
{
	if ( key < 1 ) return -1;
	else return log2(key);
}
unsigned int BitTree::getParentKey(unsigned int key) { return (key >> 1); }
unsigned int BitTree::getChildKey(unsigned int key, unsigned int childIndex)
{
	if ( !(childIndex>>1) ) return (key<<1) | childIndex;
	Logger::error("Invalid input childIndex at BitTree::getChildKey(). Should be either 0 or 1.");
	throw("Invalid input childIndex at BitTree::getChildKey(). Should be either 0 or 1.");
}

unsigned int BitTree::isRoot(unsigned int key)		{ return (key == 1); }
unsigned int BitTree::isLeftChild(unsigned int key)	{ return  (key & 1); }
unsigned int BitTree::isRightChild(unsigned int key)	{ return !(key & 1); }

unsigned int BitTree::getLeftChildKey(unsigned int key) { return (key << 1); }
unsigned int BitTree::getRightChildKey(unsigned int key) { return (key << 1) | 1; }

std::string BitTree::toDot(const std::string& filename) const
{
	std::ofstream file;
	file.open(filename);
	file << "digraph Tree {\n";

	unsigned int leftChildKey, rightChildKey;

	for ( std::map<unsigned int, unsigned int>::const_iterator it(this->nodes.cbegin()); it != this->nodes.cend(); it++ )
	{
		if ( this->hasKey(it->first) )
			{
				file << "node [shape=oval];\n";
				file << it->first;
				file << " [colorscheme=rdylgn8, fontsize=9, label=\" ";
				file << it->second;
				file << "\", color=lightblue,style=filled ];\n";

				leftChildKey  = BitTree::getLeftChildKey(it->first);
				rightChildKey = BitTree::getRightChildKey(it->first);

				if ( this->hasKey(leftChildKey) )
				{
					file << (it->first);
					file << " -> ";
					file << leftChildKey;
					file << ";\n";
					//"[fontsize=8, labeldistance=2.5, labelangle=20];\n";
				}
				if ( this->hasKey(rightChildKey) )
				{
					file << (it->first);
					file << " -> ";
					file << rightChildKey;
					file << ";\n";
					//"[fontsize=8, labeldistance=2.5, labelangle=20];\n";
				}
			}
	}
	file << "}";
	file.close();
	return filename;
}

std::string BitTree::print(const std::string& prefix) const { return "\n" + this->print(prefix, 1); }
std::ostream& operator<< (std::ostream& out, const BitTree& bt)
{
	out << bt.print("", 1);
	return out;
}