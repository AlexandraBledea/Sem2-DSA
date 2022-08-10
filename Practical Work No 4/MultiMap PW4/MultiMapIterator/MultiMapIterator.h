#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	MultiMap& col;
	int currentPositionInHashTable;
	Node* currentNodeInLinkedList;
	Node* previousNodeInLinkedList;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
    TElem remove();

};
