#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
    int utmostPosition;
    Node** representatives;
    int current_frequency;

	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

public:
	TComp getCurrent();
	bool valid() const;
	void next();
	void first();
};

