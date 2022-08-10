#pragma once
#include "../SortedBag/SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	int current;
	int frequency;

public:
	TComp getCurrent();
	bool valid() const;
//	void previous();
//	void previous_2();
	void next();
	void first();
};

