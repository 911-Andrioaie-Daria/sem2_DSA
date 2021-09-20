#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include "utility"

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
typedef bool (*Condition)(TElem);
//typedef std::pair<TElem, int> TPair;
#define NULL_TCOMP -11111;
const int INITIAL_CAPACITY = 100;
const double LOAD_FACTOR = 0.7;


class SortedBagIterator;

struct Node{
    TElem value;
    int frequency;
    Node* next;
};

class SortedBag {
	friend class SortedBagIterator;

private:
    int capacity;
	int unique_count;
	int total_count;
	Node** hashTable;
	Relation relation;

	/// Function that returns the position of the element e in the hashtable
	int hashFunction(TElem e) const;

	void insertInSortedLinkedList(Node *newNode, Node* head);

	void resize();

public:
	//constructor
	explicit SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

    //keeps in the SortedBag only those elements that respect the given condition, cond
    void filter(Condition cond);

    //destructor
	~SortedBag();
};