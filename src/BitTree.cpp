#include "BitTree.h"
#include <math.h>
#include <iostream>
#include <fstream>

/**********
* PRIVATE *
***********/

void BitTree::print(std::ostream& out, const std::string& prefix, int key) const
{
	std::string toAdd;
	if ( this->hasKey(key) )
		{
			out << prefix;
			std::string toPrint(std::to_string(key) + ": " + std::to_string(this->getValue(key)) + " ");
			out << toPrint << std::endl;

			for (unsigned int j(0); j<(toPrint.size()/2 - 1); j++) toAdd += " ";
			toAdd += "|    ";
		}

	if ( this->hasKey(BitTree::getLeftChildKey(key)) )
		this->print(out, prefix + toAdd, BitTree::getLeftChildKey(key));
	
	if ( this->hasKey(BitTree::getRightChildKey(key)) )
		this->print(out, prefix + toAdd, BitTree::getRightChildKey(key));
}

/*********
* PUBLIC *
**********/

/* Setters */
void BitTree::addRoot(int value){ this->nodes[1] = value; }
void BitTree::addLeftChild(int parentKey,	int value)
{
	if ( this->hasKey(parentKey) )
		{
			this->nodes.insert(std::make_pair(parentKey << 1, value));
			return;
		}
}
void BitTree::addRightChild(int parentKey,	int value)
{
	if ( this->hasKey(parentKey) )
		{
			this->nodes.insert(std::make_pair((parentKey << 1) | 1, value));
			return;
		}
}

/* Getters */
bool BitTree::hasKey(int key) const { return this->nodes.find(key) != this->nodes.cend(); }
int BitTree::getValue(int key) const
{
	if ( this->hasKey(key) )
		return this->nodes.find(key)->second;
	return -1;
}
int BitTree::getNumberNodes() const { return this->nodes.size(); }
int BitTree::getMaxLevel() const
{
	if (this->getNumberNodes() == 0)
		return -1;
	return log2(this->nodes.rbegin()->first);
}


/* Static */

int BitTree::getLevel(int key)
{
	if ( key < 1 ) return -1;
	else return log2(key);
}
int BitTree::getLeftChildKey(int key) { return (key << 1); }
int BitTree::getRightChildKey(int key) { return (key << 1) | 1; }

std::string BitTree::toDot(const std::string& filename) const
{
	std::ofstream file;
	file.open(filename);
	file << "digraph Tree {\n";

	int leftChildKey, rightChildKey;

	for ( std::map<int, int>::const_iterator it(this->nodes.cbegin()); it != this->nodes.cend(); it++ )
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

std::ostream& operator<< (std::ostream& out, const BitTree& bt)
{
	bt.print(out, "", 1);
	return out;
}