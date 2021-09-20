#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	this->head = nullptr;
    this->length = 0;
}
/// theta(1)

bool Set::add(TElem elem) {
	/// we first search if elem is already in the set. If not, we add at the beginning

	if(this->search(elem))
	    return false;

	node* new_node = new node;
	new_node->info = elem;
	new_node->next = this->head;
	this->head = new_node;
	this->length++;

    return true;
}
/// best case: theta(1): when the element is first in the linked list, the algorithm stops
/// worst case: O(n): when we parse the whole list to check for the existence of the element

bool Set::remove(TElem elem) {
	/// first search for the element.

	if(this->length == 0)
        return false;

	/// the case in which we remove the head
	if(this->head->info == elem){
	    node* previous_head = this->head;
	    this->head = this->head->next;
	    delete previous_head;
        this->length--;
        return true;
	}

    /// parse the list until we reach the element
	node* previous_node;
	node* current_node;
    previous_node = this->head;
    current_node = previous_node->next;

    while(current_node != nullptr){
        if(current_node->info == elem){
            previous_node->next = current_node->next;
            delete current_node;
            this->length--;
            return true;
        }
        previous_node = previous_node->next;
        current_node = current_node->next;
    }

    return false;
}
/// best case: theta(1), the element is the first one in the list
/// worst case: theta(n), the element is the last or it does not exist.
/// total: O(n).

bool Set::search(TElem elem) const {

    node* current_node;
    current_node = this->head;

    while(current_node != nullptr){
        if(current_node->info == elem)
            return true;
        current_node = current_node->next;
    }

	return false;
}
/// best case: theta(1), when the element is the first in the list
/// worst case: theta(n), when the element is the last or it does not exist
/// total: O(n)

int Set::size() const {
    return this->length;
}
/// theta(1)

bool Set::isEmpty() const {
	if(this->head == nullptr)
        return true;
	return false;
}
/// theta(1)

Set::~Set() {
	while(this->length > 0){
	    node* previous_head = this->head;
	    this->head = this->head->next;
	    delete previous_head;
	    this->length--;
	}
}
/// theta(n)

SetIterator Set::iterator() const {
	return SetIterator(*this);
}
/// theta(1)