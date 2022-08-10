#pragma once
#include "../FixedCapBiMap/FixedCapBiMap.h"
class FixedCapBiMapIterator
{
	//DO NOT CHANGE THIS PART
	friend class FixedCapBiMap;
private:
	const FixedCapBiMap& map;
	int current; // the position of the current element from the elements array from the map


	FixedCapBiMapIterator(const FixedCapBiMap& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


