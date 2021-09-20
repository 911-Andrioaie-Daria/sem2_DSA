#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->current = this->map.head;
}
/// theta(1)

void MapIterator::first() {
	this->current = this->map.head;
}
/// theta(1)

void MapIterator::next() {
    if(!this->valid())
        throw exception();
	this->current = this->map.DLLANodes[current].next;
}
/// theta(1)


TElem MapIterator::getCurrent(){
    if(!this->valid())
        throw exception();

    return this->map.DLLANodes[current].info;
}
/// theta(1)


bool MapIterator::valid() const {
	if(this->current == -1)
	    return false;
    return true;
}
/// theta(1)


void MapIterator::jumpForward(int k) {
    if(k <= 0)
        throw exception();
    if(!valid())
        throw exception();

    int steps = 0;
    /// take k steps or stop when we reach the end of the list
    while(this->current != -1 && steps < k){
        steps = steps + 1;
        this->current = this->map.DLLANodes[current].next;
    }
    /// if the iterator didn't take k steps, it means that the loop stopped because it reached the end
    if(steps < k)
        this->current = -1;
}
/// best case: theta(1) : the iterator is invalid or k is zero or negative
/// worst: theta(k): move k steps
/// total: O(k).




