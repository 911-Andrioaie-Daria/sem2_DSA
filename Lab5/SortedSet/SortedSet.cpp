#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->sorting_relation = r;
	this->root = nullptr;
	this->count = 0;
}
/// theta(1)

BSTNode *SortedSet::init_node(TElem info) {
    auto* new_node = new BSTNode{};
    new_node->info = info;
    new_node->left_child = nullptr;
    new_node->right_child = nullptr;

    return new_node;
}
/// theta(1)

TElem SortedSet::get_maximum(BSTNode *root_of_tree) {
    BSTNode* current = root_of_tree;

    if(current == nullptr){
        return NULL_TELEM;  /// the tree is empty.
    }

    while(current->right_child != nullptr)
        current = current->right_child;

    return current->info;
}
/// best case: theta(1), when the root of the tree does not have a right child, so the root is actually the maximum
/// worst case: theta(n), when the tree is degenerate, with each node having only a right child, so end up parsing the
/// whole tree.

/// total: BC != WC => O(n).

bool SortedSet::add(TComp elem) {

	/// insert it at the right position
	BSTNode* new_node = init_node(elem);

    BSTNode* previous = nullptr;
    BSTNode* current = this->root;
    while(current != nullptr){
        previous = current;

        if(current->info == elem) /// if on the path to the right position we found the element, we return false and don't continue adding it
            return false;

        if(sorting_relation(new_node->info, current->info)){
            current = current->left_child;
        }
        else {
            current = current->right_child;
        }
    }

    /// previous now contains a pointer to the node to which we have to add the new node as a child.

    if(previous == nullptr){
        /// case 1: the tree is empty and we add the root.
        this->root = new_node;
    }
    else {
        /// case 2: we have to set the new node as the appropriate child of its parent, so as to preserve the relation
        /// between elements
        if (sorting_relation(new_node->info, previous->info))
            previous->left_child = new_node;
        else
            previous->right_child = new_node;
    }
    this->count++;
	return true;
}
/// best case: theta(1): the tree is empty, so the while loop is not executed, and we only update the root
/// worst case: theta(n): the tree is degenerate and all nodes have their child on the same side, either left or right,
/// and the node is added as the new leaf => all nodes are parsed.
/// BC != WC => O(n)


bool SortedSet::remove(TComp elem) {
    bool found = false;
    BSTNode* previous = nullptr;
    BSTNode* current = this->root;

    /// parse the path to the node and stop when the node was found or nullptr is reached
    while(current != nullptr && !found){

        if(current->info == elem)
            found = true;

        else if(sorting_relation(elem, current->info)){
            previous = current;
            current = current->left_child;
        }
        else {
            previous = current;
            current = current->right_child;
        }
    }

    /// we parsed the whole path to the right position of the element and didn't find it
    if(current == nullptr)
        return false;

    /// remove the node
    this->count--;

    /// count the number of descendants, because this number will split the algorithm into 3 cases
    int number_of_descendants = 0;
    if(current->left_child != nullptr)
        number_of_descendants++;
    if(current->right_child != nullptr)
        number_of_descendants++;

    if(number_of_descendants == 0){
        /// case 1: the node has no descendants. we simply make the child if it's parent to be null and delete the node.

        /// case 1.1: the current node is the root, and it is the only left node in the tree
        if(current == this->root){
            delete current;
            this->root = nullptr;
        }
        else{
            /// case 1.2: the current node is a leaf
            if(previous->left_child == current){
                previous->left_child = nullptr;
            }
            else{
                previous->right_child = nullptr;
            }
            delete current;
        }
        return true;
    }
    else if(number_of_descendants == 1){
        /// case 2: the node has one descendant

        /// case 2.1: the node is the root and has one child.
        if(current == this->root){
            if(current->left_child != nullptr){
                this->root = this->root->left_child;
            }
            else{
                this->root = this->root->right_child;
            }
            delete current;
        }

        /// case 2.2: the node is not the root, meaning that it has a parent and a child,
        /// and we need to make the child of the parent to be the descendant.
        else{
            if(current->left_child != nullptr){
                if(previous->left_child == current){
                    previous->left_child = current->left_child;
                }
                else{
                    previous->right_child = current->left_child;
                }
            }
            else{
                if(previous->left_child == current){
                    previous->left_child = current->right_child;
                }
                else{
                    previous->right_child = current->right_child;
                }
            }
            delete current;
        }
        return true;
    }
    else{
        /// the current node has 2 descendants. We replace it with the value of the maximum node in its left subtree
        /// and remove the maximum;

        TElem maximum = get_maximum(current->left_child);
        remove(maximum);
        this->count++;
        current->info = maximum;

        return true;
    }
}


bool SortedSet::search(TComp elem) const {
    BSTNode* current = this->root;
    while(current != nullptr){

        if(current->info == elem)
            return true;

        if(sorting_relation(elem, current->info)){
            current = current->left_child;
        }
        else {
            current = current->right_child;
        }
    }
    return false;
}
/// theta(1): when the tree is empty or the element that is searched is the root.
/// worst case: theta(n): the tree is degenerate and all nodes have their child on the same side, either left or right,
/// and the node that is searched is the leaf of the tree (or should be the leaf of the tree, but does not exist)
/// => all nodes are parsed
/// BC != WC => O(n)


int SortedSet::size() const {
	return this->count;
}
/// theta(1)

bool SortedSet::isEmpty() const {
	if(this->count == 0)
        return true;
	return false;
}
/// theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
/// theta(1)

SortedSet::~SortedSet() {
    /// do a post order traversal, since for each node we must delete its children and then the actual node.


	BSTNode** stack = new BSTNode*[this->count];
	int index_of_top = -1;

    BSTNode* node = this->root;

    while(node != nullptr){
        if(node->right_child != nullptr){
            /// push to the stack
            stack[index_of_top+1] = node->right_child;
            index_of_top++;
        }

        /// push to the stack
        stack[index_of_top+1] = node;
        index_of_top++;
        node = node->left_child;
    }

    while(index_of_top >= 0){
        /// pop from the stack
        node = stack[index_of_top];
        index_of_top--;
        if(node->right_child != nullptr && index_of_top >= 0 && node->right_child == stack[index_of_top]){
            /// pop from the stack
            index_of_top--;

            /// push to the stack
            stack[index_of_top+1] = node;
            index_of_top++;
            node = node->right_child;
        }
        else{
            delete node;
            node = nullptr;
        }

        while(node != nullptr){
            if(node->right_child != nullptr){
                /// push to the stack
                stack[index_of_top+1] = node->right_child;
                index_of_top++;
            }
            stack[index_of_top+1] = node;
            index_of_top++;
            node = node->left_child;
        }
    }
}
/// Theta(n), O(n) extra space complexity for the stack