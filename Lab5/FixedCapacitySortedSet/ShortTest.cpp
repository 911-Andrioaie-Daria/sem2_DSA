#include "ShortTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <assert.h>

bool r2(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}


void testAll() { 
	int vverif[5];
	int iverif;
	TComp e;

	SortedSet s1(r2, 5);
	assert(s1.add(5) == true);
	assert(s1.add(1) == true);
	assert(s1.add(10) == true);
	SortedSetIterator it1 = s1.iterator();
	it1.first();
	e = it1.getCurrent();
	iverif = 0;
	vverif[iverif++] = e;
	it1.next();
	while (it1.valid()) {
		assert(e < it1.getCurrent());
		e = it1.getCurrent();
		vverif[iverif++] = e;
		it1.next();
	}
	assert((vverif[0] == 1) && (vverif[1] == 5) && (vverif[2] == 10));


	SortedSet s(r2, 7);
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.add(1) == false);
	assert(s.add(10) == false);
	assert(s.add(-3) == true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


    SortedSet s2(r2, 8);
    assert(s2.isEmpty() == true);
    assert(s2.size() == 0);
    assert(s2.add(13) == true);
    assert(s2.add(8) == true);
    assert(s2.add(25) == true);
    assert(s2.add(1) == true);
    assert(s2.add(10) == true);
    assert(s2.add(0) == true);
    assert(s2.add(5) == true);
    assert(s2.add(4) == true);
    assert(s2.size() == 8);
    assert(s2.remove(13) == true);
    assert(s2.size() == 7);

	SortedSetIterator it = s.iterator();
	iverif = 0;
	it.first();
	e = it.getCurrent();
	vverif[iverif++] = e;
	it.next();
	while (it.valid()) {
		assert(r2(e, it.getCurrent()));
		e = it.getCurrent();
		vverif[iverif++] = e;
		it.next();
	}
	assert((vverif[0] == -3) && (vverif[1] == 5) && (vverif[2] == 7) && (vverif[3] == 10));

    SortedSet s3(r2, 1);
    for(int i=0; i<100; i++){
        if(i==0){
            assert(s3.add(i)== true);
        }
        else
            assert(s3.add(i)== false);
    }
    assert(s3.size() == 1);
}

