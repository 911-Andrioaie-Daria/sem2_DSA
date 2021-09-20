#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
//ADT  Matrix –represented  as  a  sparse  matrix,  compressed  sparse  column  representation using dynamic arrays.
using namespace std;


int main() {
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}