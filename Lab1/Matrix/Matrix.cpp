#include "Matrix.h"
#include <exception>
using namespace std;

///constructor
Matrix::Matrix(int nrLines, int nrCols) {
	this->nonzero_elements = new TElem[2 * nrCols];
	this->row_indices = new int[2 * nrCols];
	this->column_pointers = new int[nrCols+1];
	for(int index=0;index<= nrCols;index++)
	    this->column_pointers[index] = 0;
	this->number_of_lines = nrLines;
	this->number_of_columns = nrCols;
	this->current_capacity = 2 * nrCols;
}
//// theta(1)


int Matrix::nrLines() const {
	return this->number_of_lines;
}
/// theta(1)

int Matrix::nrColumns() const {
    return this->number_of_columns;

}
/// theta(1)

TElem Matrix::element(int i, int j) const {
	if(i<0 || i>=this->nrLines())
	    throw exception();
    if(j<0 || j>=this->nrColumns())
        throw exception();

    int column_start = this->column_pointers[j];
    int column_end = this->column_pointers[j+1];
    /// parse the elements on column j
    for(int value_index = column_start; value_index < column_end; value_index++)
        if(this->row_indices[value_index] == i)
            return this->nonzero_elements[value_index];

    return NULL_TELEM;
}
/// best case: the element is the first one in its column -> theta(1)
/// worst case: the element is the last one in its column and the column is full of non-zero elements or it does
/// not exist at all in the arrays (= 0) -> theta(nrRows)
/// average case: theta(nrRows)
/// total complexity: O(nrRows)


void Matrix::resize(int new_capacity){
    TElem* new_array_of_non_zero_elements = new TElem[new_capacity];
    int* new_array_of_row_indices = new int[new_capacity];

    /// if the array shrinks, we only copy the elements up until the new capacity
    if(new_capacity < this->current_capacity)
        for(int i=0; i<new_capacity;i++){
            new_array_of_non_zero_elements[i] = this->nonzero_elements[i];
            new_array_of_row_indices[i] = this->row_indices[i];
        }

    /// if the array expands, we copy all its old elements
    else
        for(int i=0; i<this->current_capacity;i++){
            new_array_of_non_zero_elements[i] = this->nonzero_elements[i];
            new_array_of_row_indices[i] = this->row_indices[i];
        }

    /// get rid of the old array
    delete[] this->nonzero_elements;
    delete[] this->row_indices;

    /// update the new array
    this->nonzero_elements = new_array_of_non_zero_elements;
    this->row_indices = new_array_of_row_indices;
    this->current_capacity = new_capacity;
}
/// case 1: the new capacity is less than the old capacity: theta(new_capacity)
/// case 2: the new capacity is greater than the old capacity: theta(old_capacity)
/// total complexity: the minimum between old_capacity and new_capacity.
/// I honestly don't know how to write the final complexity mathematically.


TElem Matrix::modify(int i, int j, TElem e) {
    if(i<0 || i>=this->nrLines())
        throw exception();
    if(j<0 || j>=this->nrColumns())
        throw exception();

    int column_start = this->column_pointers[j];
    int column_end = this->column_pointers[j+1];

    /// if at the given position is a non-zero element, we replace it
    /// parse the elements on column j
    for(int value_index = column_start; value_index < column_end; value_index++)
        if(this->row_indices[value_index] == i) {
            /// we found a non-zero element on the position (i, j)
            TElem old_value = this->nonzero_elements[value_index];
            if (e != NULL_TELEM) {
                /// e <- e case, we simply change the value
                this->nonzero_elements[value_index] = e;
            }
            else{
               /// e <- 0 case, we have to remove the element by overwriting it
               /// we move all the elements after the value_index one position to the left in the arrays of
               /// row indices and values
               int number_of_non_zero_elements = this->column_pointers[this->nrColumns()];
               for(int index = value_index; index < number_of_non_zero_elements - 1; index++){
                   this->nonzero_elements[index] = this->nonzero_elements[index+1];
                   this->row_indices[index] = this->row_indices[index+1];
               }
               /// in column pointers, all elements after the column index are decremented
               for(int index = j+1; index<=this->nrColumns(); index++)
                   this->column_pointers[index]--;

               /// check for the need to resize after deletion (contract the matrix to save up memory).
               if(number_of_non_zero_elements-1 < this->current_capacity/4)
                   this->resize(this->current_capacity/2);

            }
            return old_value;
        }

    /// if this line is reached, the element at the given position is zero.

    /// If the new element is 0, no modifications take place
    if(e==NULL_TELEM){
        /// 0 <- 0 case, nothing happens
        return NULL_TELEM;
    }
    else{
        /// 0 <- e case

        /// If the new element is non-zero, it is must be added to the representation
        /// by updating the 3 arrays.

        /// in column pointers, all elements after the column j are incremented
        for(int index = j+1; index<=this->nrColumns(); index++)
            this->column_pointers[index]++;

        int new_element_index;
        int current_index = column_start;
        bool found_insertion_position = false;

        /// find the right position where to insert the new element
        while(!found_insertion_position && current_index < column_end){
            if(this->row_indices[current_index] > i){
                found_insertion_position = true;
            }
            else current_index++;
        }

        new_element_index = current_index;

        /// check for the need to resize (expand).
        int number_of_non_zero_elements = this->column_pointers[this->nrColumns()];
        if(number_of_non_zero_elements == this->current_capacity)
            this->resize(2*this->current_capacity);

        /// move the elements that come after the insertion index, one position to the right, in order to make room
        /// for the new element

        for(int index = number_of_non_zero_elements; index > new_element_index; index--){
            this->nonzero_elements[index] = this->nonzero_elements[index-1];
            this->row_indices[index] = this->row_indices[index - 1];
        }

        /// insert the element in the array of elements and its row index in the array of indices.
        this->nonzero_elements[new_element_index] = e;
        this->row_indices[new_element_index] = i;

        return NULL_TELEM;
    }

}
/// best case: on the given position is a non-zero element, it's the first on its column and is replaced by another non-zero
/// element -> theta(1)
/// worst case: on the given position is a 0 which has to be replaced with a non-zero element, after performing a resize
/// theta(new_capacity)
/// total: O(current_capacity)

pair<int, int> Matrix::positionOf(TElem elem) const{
    pair<int, int> element_position;
    element_position.first = -1;
    element_position.second = -1;

    if(elem == NULL_TELEM){
        /// search for the first 0

        /// parse each column
        for(int column = 0; column < this->number_of_columns; column ++){
            int column_start = this->column_pointers[column];
            int column_end = this->column_pointers[column + 1];

            /// case in which the column is empty
            if(column_start == column_end){
                element_position.first = 0;
                element_position.second = column;
                return element_position;
            }

            /// check if the column is not full of non-zero elements, so that it makes sense to search for a 0
            if(column_end - column_start < this->nrLines()){
                int index_of_zero = 0;
                for(int index = column_start; index < column_end; index++)
                    if(this->row_indices[index] != index_of_zero){
                        element_position.first = index_of_zero;
                        element_position.second = column;
                        return element_position;
                    }
                    else
                        index_of_zero++;
            }
        }
        }
    else{
        ///search for the first occurrence of the non-zero element

        /// parse each column
        for(int column = 0; column < this->number_of_columns; column ++){
            int column_start = this->column_pointers[column];
            int column_end = this->column_pointers[column + 1];

            /// parse the elements on each column
            for(int index = column_start; index < column_end; index++)
                if(this->nonzero_elements[index] == elem){
                    element_position.first = this->row_indices[index];
                    element_position.second = column;
                    return element_position;
                }
        }
    }

    return element_position;
}
/// best case: the element, either a 0 or non-zero, is on position (0, 0) in the matrix => theta(1)
/// worst case: a non zero element is on the bottom right corner position in the matrix (nrlines-1, nrcols-1) or it does not exist at all  => theta(number of non-zero elements)
/// Total complexity: O(number of non-zero elements)

/// destructor
Matrix::~Matrix() {
    delete[] this->nonzero_elements;
    delete[] this->row_indices;
    delete[] this->column_pointers;
}
/// theta(1) or theta(nrLines*nrCols)