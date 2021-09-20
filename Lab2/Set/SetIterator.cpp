#include "SetIterator.h"
#include "Set.h"
using namespace std;
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
    this->current = this->set.head;
}
/// theta(1)

void SetIterator::first() {
    this->current = set.head;
}
/// theta(1)

void SetIterator::next() {
    if(!this->valid())
        throw exception();
    else
        this->current = this->current->next;
}
/// theta(1)

TElem SetIterator::getCurrent()
{
    if(!this->valid())
        throw exception();
    return this->current->info;
}
/// theta(1)

bool SetIterator::valid() const {
	if(this->current == nullptr)
        return false;
	else
        return true;
}

void SetIterator::previous() {
    if(!this->valid())
        throw exception();

    if(this->current == this->set.head)
        this->current = nullptr;

    /// parse the set until the current
    node* parser;
    parser = this->set.head;
    while(parser->next != this->current)
        parser = parser->next;

    this->current = parser;
}

/// best theta(1)
///worst theta(n)
///total O(n)




