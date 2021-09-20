#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->capacity = INITIAL_CAPACITY;
	this->hashTable = new Node*[this->capacity];

	for(int i=0; i < this->capacity; i++){
	    this->hashTable[i] = nullptr;
	}
	this->unique_count = 0;
	this->total_count = 0;
	this->relation = r;
}
/// theta(initial_capacity), because all positions in the hashtable must be initialised with a null pointer

int SortedBag::hashFunction(TElem e) const {
    int position = e % this->capacity;
    if(position < 0)
        position = -position;
    return position;
}
/// theta(1)

void SortedBag::insertInSortedLinkedList(Node *newNode, Node* head) {
    /// we search for the optimal position in the list, such that it remains sorted
    Node* current = head;

    /// 1. Must insert before the head
    if(!this->relation(current->value, newNode->value)){
        Node* copy = new Node;
        *copy = *head;
        newNode->next = copy;
        *head = *newNode;
        delete newNode;
        this->unique_count++;
        this->total_count += head->frequency;
        return;
    }

    ///2. Must insert after the head
    while(current->next != nullptr && this->relation(current->next->value, newNode->value))
        current = current->next;

    /// now current is the node after which we want to insert, or whose frequency will be incremented
    if(current->value == newNode->value){
        current->frequency++;
        this->total_count++;
        delete newNode;
        return;
    } else{
        newNode->next = current->next;
        current->next = newNode;
        this->total_count += newNode->frequency;
        this->unique_count++;
        return;
    }
}
///best case: theta(1), when the element is added before the head
/// worst case: theta(unique_count), when all the elements in the array are in the same linked list and the element must
///             be inserted on the last position
/// => total: O(unique_count)

void SortedBag::resize() {
    this->capacity *= 2;
    Node** newHashTable = new Node*[this->capacity];

    for(int i=0; i < this->capacity; i++){
        newHashTable[i] = nullptr;
    }

    this->unique_count = 0;
    this->total_count = 0;

    /// rehash the already existing elements
    for(int i=0; i<this->capacity/2; i++){  /// take the elements of each linked list and rehash
        Node* current = this->hashTable[i];
        while(current != nullptr){
            TComp e = current->value;
            int position = this->hashFunction(e);

            Node* newNode = new Node;
            newNode->value = e;
            newNode->frequency = current->frequency;
            newNode->next = nullptr;

            if(newHashTable[position] == nullptr){
                /// insert as the head
                newHashTable[position] = newNode;
                this->total_count += newNode->frequency;
                this->unique_count++;
            }
            else {
                /// insert somewhere in the list
                this->insertInSortedLinkedList(newNode, newHashTable[position]);
            }
            Node* old_node = current;
            current = current->next;
            delete old_node;
        }
    }
    delete[] this->hashTable;
    this->hashTable = newHashTable;
}
/// average: theta(capacity), because each existing element has to be rehashed

void SortedBag::add(TComp e) {
    double load = (double)this->unique_count/ this->capacity;
    if(load > LOAD_FACTOR)
        this->resize();

    int position = this->hashFunction(e);

    Node* newNode = new Node;
    newNode->value = e;
    newNode->frequency = 1;
    newNode->next = nullptr;

    if(this->hashTable[position] == nullptr){

        this->hashTable[position] = newNode;
        this->total_count++;
        this->unique_count++;

        return;
    }
    else
        insertInSortedLinkedList(newNode, this->hashTable[position]);
}
/// best case: theta(1), when the corresponding linked list is empty, and we simply add the element as the head
/// worst case: theta(capacity), when the array has to be resized and the element is inserted as the last in its
/// corresponding linked list
/// => total: O(capacity).



bool SortedBag::remove(TComp e) {
    int position = this->hashFunction(e);

    Node* current = this->hashTable[position];

    if(current == nullptr)
        return false;

    /// case 1: it s the head of the list
    if(current->value == e) {
        /// case 1.1: just decrease the frequency
        if (current->frequency > 1){
            current->frequency--;
        }

        /// case 1.2: need to remove if entirely
        else {
            Node *old_node = current;
            this->hashTable[position] = this->hashTable[position]->next;
            delete old_node;
            this->unique_count--;
        }
        this->total_count--;
        return true;
    }

    /// case 2: it s after the head
    Node* previous = current;
    current = current->next;

    while(current != nullptr){
        if(current->value == e){
            /// case 2.1: just decrease the frequency
            if(current->frequency > 1)
                current->frequency--;

            /// case 2.2: need to remove if entirely
            else{
                Node* old_node = current;
                previous->next = current->next;
                delete old_node;
                this->unique_count--;
            }

            this->total_count--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}
/// best case: theta(1), when the linked list of the corresponding position is empty, meaning that we know from the start
///            that the element is not in the list
/// worst case: theta(unique_count), when all the elements in the array are in the same linked list and the element is
///             the last or it does not exit at all in that list
/// => total: O(unique_count)




bool SortedBag::search(TComp elem) const {
	int position = this->hashFunction(elem);
	Node* current = this->hashTable[position];
    while (current != nullptr){
        if(current->value == elem)
            return true;
        current = current->next;
    }
    return false;
}
/// best case: theta(1), when the element is the head of the linked list at the corresponding position
/// worst case: theta(unique_count), when all of the elements in the array are at the same position and the given element
///             is not in its corresponding linked list
/// => total: O(unique_count)


int SortedBag::nrOccurrences(TComp elem) const {
    int position = this->hashFunction(elem);
    Node* current = this->hashTable[position];
    while (current != nullptr){
        if(current->value == elem)
            return current->frequency;
        current = current->next;
    }
	return 0;
}
/// best case: theta(1), when the element is the head of the linked list at the corresponding position
/// worst case: theta(unique_count), when all of the elements in the array are at the same position and the given element
///             is not in its corresponding linked list
/// => total: O(unique_count)

int SortedBag::size() const {
	return this->total_count;
}
/// theta(1)

bool SortedBag::isEmpty() const {
	if(this->unique_count == 0)
        return true;
    return false;
}
/// theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
/// theta(1)

SortedBag::~SortedBag() {
    /// delete each linked list
    for(int i = 0; i<this->capacity; i++){
        Node* current = this->hashTable[i];
        while(current != nullptr){
            Node* old_node = current;
            current = current->next;
            delete old_node;
        }
    }
    /// delete the array itself
	delete this->hashTable;
}
/// theta(unique_count), because we have to delete each node in the array

void SortedBag::filter(Condition cond) {
    /// Obs: in this case, the iterator is not used because we don't necessarily need the elements in the sorted order,
    /// and it would raise the time complexity

    for(int position = 0; position < this->capacity; position++){
        /// parse each linked list
        Node* current = this->hashTable[position];
        Node* previous = nullptr;

        while(current != nullptr){
            if(!cond(current->value)){
                /// in this case we remove it
                /// case 1: it's the head
                if(current == this->hashTable[position]){
                    Node *old_node = current;
                    current = current->next;
                    this->hashTable[position] = this->hashTable[position]->next;
                    this->unique_count--;
                    this->total_count -= old_node->frequency;
                    delete old_node;
                }

                    /// case 2: it's after the head
                else{
                    Node* old_node = current;
                    previous->next = current->next;
                    current = current->next;
                    this->unique_count--;
                    this->total_count -= old_node->frequency;
                    delete old_node;
                }
            } else{ /// continue parsing the list
                previous = current;
                current = current->next;
            }
        }
    }
}
/// Total complexity: Theta(capacity), since we have to parse each linked list and each element in that list
