#include "SortedBagIterator.h"
#include "../SortedBag/SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
	this->frequency = bag.elements[this->current].second;
}
/// Theta(1)

TComp SortedBagIterator::getCurrent() {
	if(this->current >= this->bag.nrPairs)
	{
		throw exception();
	}
	return this->bag.elements[this->current].first;
}
/// Theta(1)

bool SortedBagIterator::valid() const{
    //if(this->current < this->bag.nrPairs)
	if(this->current < this->bag.nrPairs && this->current >=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// Theta(1)

//void SortedBagIterator::previous_2() {
//    if(!this->valid())
//        throw exception();
//    if(this->frequency > 1)
//        this->frequency--;
//    else
//        if(this->frequency == 1)
//        {
//            this->current--;
//            this->frequency = bag.elements[this->current].second;
//        }
//}
///// Theta(1)
//
//void SortedBagIterator::previous() {
//    if(!this->valid())
//    {
//        throw exception();
//    }
//    else
//    {
//        if(this->current == 0)
//            throw exception();
//        else
//        {
//            this->current--;
//            this->frequency = bag.elements[this->current].second;
//        }
//    }
//}
///// Theta(1)

void SortedBagIterator::next() {
	if(this->current >= this->bag.nrPairs)
	{
		throw exception();
	}
	else
	{
		this->frequency--;
		if(this->frequency == 0)
		{
			this->current++;
			if(valid())
			    this->frequency = bag.elements[this->current].second;
		}
	}
}
/// Theta(1)

void SortedBagIterator::first() {
	this->current = 0;
	this->frequency = bag.elements[this->current].second;
}


