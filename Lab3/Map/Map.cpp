#include "Map.h"
#include "MapIterator.h"

Map::Map() {
    this->capacity = 100;
    this->DLLANodes = new Node[this->capacity];
	this->length = 0;
	this->head = -1;
	this->tail = -1;

	/// initialise the list with empty positions
	this->firstEmpty = 0;
	for(int i=0; i<this->capacity-1; i++){
        this->DLLANodes[i].prev = i - 1;
        this->DLLANodes[i].next = i + 1;
        this->DLLANodes[i].info = NULL_TELEM;
	}

	this->DLLANodes[this->capacity - 1].prev = this->capacity - 2;
	this->DLLANodes[this->capacity - 1].next = -1;
	this->DLLANodes[this->capacity-1].info = NULL_TELEM;

}
/// theta(capacity), since I need to set the links of the empty positions, which now occupy the whole array

Map::~Map() {
	delete[] this->DLLANodes;
}
/// theta(1)

TValue Map::add(TKey c, TValue v){
	/// first search for the key and replace its value if it is found
	int parser = this->head;
	while(parser != -1){
	    if(this->DLLANodes[parser].info.first == c){
	        TValue old = this->DLLANodes[parser].info.second;
	        this->DLLANodes[parser].info.second = v;
            return old;
	    }
	    parser = this->DLLANodes[parser].next;
	}
	/// if this line is reached, the key is not in the list;

	/// resize in case it's needed
	if(this->length == this->capacity)
	    this->resize();

	/// case 1: list is empty
	if(this->head == -1){
	    this->head = this->firstEmpty;

	    /// move to the next empty position
	    this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
	    if(this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;

	    this->DLLANodes[head].info.first = c;
	    this->DLLANodes[head].info.second = v;
	    this->DLLANodes[head].next = -1;
	    this->tail = this->head;

	} else{
        /// case 2: the list is not empty -> we append at the end.
        int new_elem = this->firstEmpty;
        this->firstEmpty = this->DLLANodes[firstEmpty].next;
        if(this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;

        /// add one more element and update the tail
        this->DLLANodes[this->tail].next = new_elem;
        this->DLLANodes[new_elem].prev = this->tail;
        this->tail = new_elem;
        this->DLLANodes[this->tail].next = -1;
        this->DLLANodes[this->tail].info.first = c;
        this->DLLANodes[this->tail].info.second = v;
    }

	this->length++;
    return NULL_TVALUE;
}
/// best case: theta(1) -> the  list is empty or the head has the given key, so we only replace the value and return the old value of the head
/// worst case: theta(length) -> the list is full, the elem is not in the list and we append it to the end. The complexity comes from parsing the
/// whole list searching for the element.
/// TOTAL: O(length) amortized (because the resize function is called rarely).


TValue Map::search(TKey c) const{
    int parser = this->head;
    while(parser != -1){
        if(this->DLLANodes[parser].info.first == c)
            return this->DLLANodes[parser].info.second;
        parser = DLLANodes[parser].next;
    }
    return NULL_TVALUE;
}
/// best case: theta(1): the head has the given key or the list is empty.
/// worst case: theta(length): the list is full and all of it is parsed, but the key is not found.
/// TOTAL: O(length).

TValue Map::remove(TKey c){
	int parser;
	parser = this->head;
	while(parser != -1){
        if(this->DLLANodes[parser].info.first == c)
        {
            /// the key was found
            TValue value = this->DLLANodes[parser].info.second;
            this->DLLANodes[parser].info = NULL_TELEM;
            this->length--;

            /// detach it from the list

            /// 1. remove the one and only element from the list
            if(parser == this->head && parser == this->tail){
                  this->head = -1;
                  this->tail = -1;
            }

            /// 2. remove the head
            else if(parser == this->head){
                this->head = this->DLLANodes[this->head].next;
                this->DLLANodes[this->head].prev = -1;
            }

            /// 3. remove the tail
            else if(parser == this->tail){
                this->tail = this->DLLANodes[this->tail].prev;
                this->DLLANodes[this->tail].next = -1;
            }
            else{
                /// 4. remove something between the head and the tail
                int previous = this->DLLANodes[parser].prev;
                int next = this->DLLANodes[parser].next;
                this->DLLANodes[previous].next = next;
                this->DLLANodes[next].prev = previous;
            }

            /// add the position to the beginning of the empty list
            this->DLLANodes[parser].next = this->firstEmpty;
            this->DLLANodes[parser].prev = -1;
            this->DLLANodes[this->firstEmpty].prev = parser;
            this->firstEmpty = parser;
            return value;
        }
        else
            parser = this->DLLANodes[parser].next;
	}
	/// we reached the end of the list and the key was not found
	return NULL_TVALUE;
}
/// best case: theta(1), the list is empty or the element is the head.
/// worst case: theta(length), the list is full and the key is not found in the list.
/// TOTAL: O(length).


int Map::size() const {
    return this->length;
}
/// TOTAL: theta(1)

bool Map::isEmpty() const{
	if(this->size() == 0) // or this->head == -1
        return true;
	return false;
}
/// TOTAL: theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
/// TOTAL: theta(1)

void Map::resize() {
    this->capacity = 2* this->capacity;
    Node* new_array = new Node[this->capacity];

    /// copy the elements from the old to the new array
    for(int i=0; i<this->length; i++)
        new_array[i] = this->DLLANodes[i];

    /// the left capacity - length positions are empty
    this->firstEmpty = this->length;
    new_array[firstEmpty].prev = -1;
    new_array[firstEmpty].next = this->length + 1;
    new_array[firstEmpty].info = NULL_TELEM;

    for(int i=this->length+1; i<this->capacity-1; i++){
        new_array[i].prev = i-1;
        new_array[i].next = i+1;
        new_array[i].info = NULL_TELEM;
    }
    new_array[this->capacity-1].prev = this->capacity-2;
    new_array[this->capacity-1].next = -1;
    new_array[this->capacity-1].info = NULL_TELEM;

    delete[] this->DLLANodes;
    this->DLLANodes = new_array;
}
///TOTAL: theta(capacity), because there are 2 for loops of (capacity/2) each.



