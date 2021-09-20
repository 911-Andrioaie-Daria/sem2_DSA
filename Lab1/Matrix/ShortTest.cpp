#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
    pair<int, int> position = m.positionOf(5);
    assert(position.first == 1);
    assert(position.second == 1);

	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

	m.modify(0, 2, 10);
	position = m.positionOf(10);
	assert(position.first == 0);
	assert(position.second == 2);

	position = m.positionOf(NULL_TELEM);
	assert(position.first == 0);
	assert(position.second == 0);

	/// does not exist in the matrix
	position = m.positionOf(49);
    assert(position.first == -1);
    assert(position.second ==-1);
}