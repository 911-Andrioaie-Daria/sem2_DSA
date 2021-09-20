#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART

struct stack{
    BSTNode** array;
    int index_of_top;
};

class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& sortedSet;
    stack stack;
    BSTNode* currentNode;
	SortedSetIterator(const SortedSet& set);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

