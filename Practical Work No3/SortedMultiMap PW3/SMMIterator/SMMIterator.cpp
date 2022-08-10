#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->currentElement = this->map.head;
}

void SMMIterator::first(){
	this->currentElement = this->map.head;
}
///Theta(1)

void SMMIterator::next(){
	if(!this->valid())
	    throw exception();
	this->currentElement = this->map.DLLANodes[this->currentElement].next;
}
///Theta(1)

bool SMMIterator::valid() const{
	if(this->currentElement == -1)
	    return false;
	return true;
}
///Theta(1)

TElem SMMIterator::getCurrent() const{
    if(!this->valid())
            throw exception();
    return this->map.DLLANodes[this->currentElement].info;
}
///Theta(1)


