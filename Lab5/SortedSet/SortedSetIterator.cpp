#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& set) : sortedSet(set)
{
	this->stack.array = new BSTNode*[this->sortedSet.count];
	this->stack.index_of_top = -1;

	BSTNode* current = this->sortedSet.root;
	while(current != nullptr){
	    /// push to the stack
	    this->stack.array[this->stack.index_of_top+1] = current;
	    this->stack.index_of_top++;
	    current = current->left_child;
	}

	if(this->stack.index_of_top >= 0){
	    /// access the top of the stack
	    this->currentNode = this->stack.array[this->stack.index_of_top];
	}
	else{
	    this->currentNode = nullptr;
	}
}
/// best case: theta(1): the tree is empty
/// worst case: theta(n) the tree is degenerate with all children being on the left side and all of them are parsed and
/// added to the stack
/// total complexity: O(n)

void SortedSetIterator::first() {
    /// empty the stack;
    this->stack.index_of_top = -1;

    BSTNode* current = this->sortedSet.root;
    while(current != nullptr){
        /// push to the stack
        this->stack.array[this->stack.index_of_top+1] = current;
        this->stack.index_of_top++;
        current = current->left_child;
    }

    if(this->stack.index_of_top >= 0){
        /// access the top of the stack
        this->currentNode = this->stack.array[this->stack.index_of_top];
    }
    else{
        this->currentNode = nullptr;
    }
}
/// best case: theta(1): the tree is empty
/// worst case: theta(n) the tree is degenerate with all children being on the left side and all of them are parsed and
/// added to the stack
/// total complexity: O(n)


void SortedSetIterator::next() {
    if(!this->valid())
        throw exception();

    /// pop from the stack
	BSTNode* node = this->stack.array[this->stack.index_of_top];
	this->stack.index_of_top--;

	if(node->right_child != nullptr){
        node = node->right_child;
	    while(node != nullptr){
	        /// push to the stack
	        this->stack.array[this->stack.index_of_top+1] = node;
	        this->stack.index_of_top++;
            node = node->left_child;
	    }
	}

	if(this->stack.index_of_top >=0)
	    /// access the top of the stack
	    this->currentNode = this->stack.array[this->stack.index_of_top];
	else
	    this->currentNode = nullptr;
}
/// best case: theta(1): when the iterator is invalid or the stack is empty and the iterator parsed all the elements
/// worst case: theta(n): when the current node is a root of a subtree and it has a right child and all the children
/// of the subtree starting from the right child are on the left side, so we have to push all of those children to the
/// stack
/// total: O(n)

TElem SortedSetIterator::getCurrent()
{
    if(!this->valid())
        throw exception();

    return this->currentNode->info;
}
/// theta(1)

bool SortedSetIterator::valid() const {
	if(this->currentNode == nullptr)
        return false;
	else
        return true;
}
/// theta(1)