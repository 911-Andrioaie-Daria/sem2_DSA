#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->current = 0;
}
// theta(1)

void FixedCapBiMapIterator::first() {
	this->current = 0;
}
// theta(1)

void FixedCapBiMapIterator::next() {
	if(!this->valid()){
	   throw exception();
	}
	else this->current++;
}
// theta(1)

TElem FixedCapBiMapIterator::getCurrent(){
	if(!this->valid())
    {
        throw exception();
    }
	else
        return this->map.elements[this->current];
}
// theta(1)

bool FixedCapBiMapIterator::valid() const {
	if (this->current < this->map.number_of_pairs)
        return true;
	return false;
}
// theta(1)



