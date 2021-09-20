#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	int current;

	MapIterator(const Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

    //moves the current element from the iterator k steps forward,
    //or makes the iterator invalid if there are less than k elements left in the Map.
    //throws an exception if the iterator is invalid or k is zero or negative
    void jumpForward(int k);

};


