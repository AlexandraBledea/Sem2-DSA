#include "SortedBag/SortedBag.h"
#include "SortedBagIterator/SortedBagIterator.h"
#include <iostream>
#include "ShortTest/ShortTest.h"
#include "ExtendedTest/ExtendedTest.h"

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "Test over" << endl;
	system("pause");
}
