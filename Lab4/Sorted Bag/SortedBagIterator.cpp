#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->utmostPosition = -1;

    /// create a copy of the first nodes in each linked list
    this->representatives = new Node*[this->bag.capacity];

	for(int i=0; i<this->bag.capacity; i++){
        this->representatives[i] = this->bag.hashTable[i];

        /// we also try to find the position of the utmost element as we copy the elements
        if(this->representatives[i] != nullptr){
            if(this->utmostPosition == -1 || this->bag.relation(this->representatives[i]->value, this->representatives[utmostPosition]->value))
                this->utmostPosition = i;
        }
	}

	if(utmostPosition != -1)
	    current_frequency = this->representatives[utmostPosition]->frequency;
}
/// theta(capacity), because we have to parse the whole hashTable in order to copy the first nodes in each linked list

TComp SortedBagIterator::getCurrent() {
    if(!this->valid())
        throw exception();

    return this->representatives[utmostPosition]->value;

}
/// theta(1)

bool SortedBagIterator::valid() const {
	if(this->utmostPosition == -1)
	    return false;
    return true;
}
/// theta(1)

void SortedBagIterator::next() {
    if(!this->valid())
        throw exception();

    current_frequency--;
    if(current_frequency == 0){
        this->representatives[utmostPosition] = this->representatives[utmostPosition]->next;

        this->utmostPosition = -1;
        for(int i=0; i<this->bag.capacity; i++)
            if(this->representatives[i] != nullptr){
                if(this->utmostPosition == -1 || this->bag.relation(this->representatives[i]->value, this->representatives[this->utmostPosition]->value))
                    this->utmostPosition = i;
            }
        if(utmostPosition!= -1 )
            this->current_frequency = this->representatives[utmostPosition]->frequency;
    }
}
/// best case: theta(1), when we have more of the same element, and just decrease its frequency
/// worst case: theta(capacity), when we need to find the position of the next element in the array of representatives and thus parse the whole array
/// => total: O(capacity)

void SortedBagIterator::first() {
    this->utmostPosition = -1;

    for(int i=0; i<this->bag.capacity; i++){
        this->representatives[i] = this->bag.hashTable[i];
        if(this->representatives[i] != nullptr){
            if(this->utmostPosition == -1 || this->bag.relation(this->representatives[i]->value, this->representatives[utmostPosition]->value))
                this->utmostPosition = i;
        }

    }
    if(utmostPosition!= -1 )
        this->current_frequency = this->representatives[utmostPosition]->frequency;
}
/// theta(capacity), because we have to parse the whole hashTable in order to copy the first nodes in each linked list

