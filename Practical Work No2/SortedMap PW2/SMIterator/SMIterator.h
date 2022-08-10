#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
    Node* CurrentNode;
	SMIterator(const SortedMap& mapionar);
	int CurrentPosition;

public:
	void first();
	void next();
	bool valid() const;
	void previous();
    TElem getCurrent() const;
};

