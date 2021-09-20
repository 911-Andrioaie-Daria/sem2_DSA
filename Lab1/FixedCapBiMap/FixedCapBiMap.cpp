#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

// constructor
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0){
	   throw exception();
	}
	this->capacity = capacity;
	this->number_of_pairs = 0;
	this->elements = new TElem[capacity];
}
// theta(1)

// destructor
FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
// theta(1) or theta(capacity)

bool FixedCapBiMap::add(TKey c, TValue v){
	if( this->number_of_pairs == this->capacity)
	    throw exception();
	int index = 0;
	int count = 0;
	while(count < 2 && index < this->number_of_pairs){
	    if(this->elements[index].first == c)
	        count++;
	    index++;
	}
	if(count == 2)
        return false;
	else {
	    this->elements[this->number_of_pairs].first = c;
        this->elements[this->number_of_pairs].second = v;
	}
    this->number_of_pairs ++;
	return true;
}
/* BC = theta(1)
WC = theta(number_of_pairs
=> total complexity is O(number_of_pairs)
 */

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair return_value;
    return_value.first = NULL_TVALUE;
    return_value.second = NULL_TVALUE;
    int count = 0;
    int index = 0;
    while(count < 2 && index < this->number_of_pairs){
        if(this->elements[index].first == c){
            if (count == 0){
                return_value.first = this->elements[index].second;
            }
            else {
                return_value.second = this->elements[index].second;
            }
            count++;
        }
        index++;
    }

	return return_value;
}
/* BC = theta(1)
 * WC = theta(number_of_pairs)
 * => total complexity = O(number_of_pairs)
 */

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
	bool pair_is_found = false;
	while (index < this->number_of_pairs && !pair_is_found){
	    if(this->elements[index].first == c && this->elements[index].second == v)
	        pair_is_found = true;
	    else index++;
	}

	if(!pair_is_found)
	    return false;
	else{
        this->elements[index] = this->elements[this->number_of_pairs-1];
        this->number_of_pairs--;
        return true;
	}
}
/* best case: theta(1) - the pair is the first in the list
 * worst case: theta(number_of_pairs) - the pair does not exist at all
 * total complexity: O(number_of_pairs)
 */

ValuePair FixedCapBiMap::removeKey(TKey k){
    ValuePair return_value;
    return_value.first = NULL_TVALUE;
    return_value.second = NULL_TVALUE;
    int count = 0;
    int index = 0;
    while( count < 2 && index < this->number_of_pairs)
    {
        if(this->elements[index].first == k)
        {
            if(return_value.first == NULL_TVALUE)
                return_value.first = this->elements[index].second;
            else
                return_value.second = this->elements[index].second;

            this->elements[index] = this->elements[this->number_of_pairs-1];
            this->number_of_pairs-- ;

            count++;
        }
        else
            index++;
    }

    return return_value;
}


int FixedCapBiMap::size() const {
	return this->number_of_pairs;
}
// theta(1)

bool FixedCapBiMap::isEmpty() const{
	if(this->size() == 0)
	    return true;
    return false;
}
// theta(1)

bool FixedCapBiMap::isFull() const {
	if(this->size() == this->capacity)
        return true;
	return false;
}
// theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
// theta(1)



