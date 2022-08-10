#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
//    if(this->map.size() == 0)
//        throw exception();
	this->CurrentNode=this->map.head;
	this->CurrentPosition = 0;
}
/// Theta(1)

void SMIterator::first(){
//    if(this->map.size() == 0)
//        throw exception();
	this->CurrentNode=this->map.head;
    this->CurrentPosition = 0;
}
///Theta(1)

void SMIterator::previous() {
    if(!this->valid())
        throw exception();
    int PreviousPosition = this->CurrentPosition - 1;
    if( PreviousPosition < 0 )
    {
        this->CurrentNode = nullptr;
    }
    else
    {
        this->first();
        while(this->CurrentPosition < PreviousPosition)
        {
            this->next();
        }
    }
}
/// BestCase: Theta(1)
/// WorstCase: Theta(n)
/// Total Complexity: O(number_of_nodes)

void SMIterator::next(){
    if(this->map.size() == 0)
        throw exception();
    if(this->valid())
    {
        this->CurrentNode=this->CurrentNode->next;
        this->CurrentPosition++;
    }
    else
        throw exception();
}
/// Theta(1)

bool SMIterator::valid() const{
	if(this->CurrentNode != nullptr)
	    return true;
	return false;
}
/// Theta(1)

TElem SMIterator::getCurrent() const{
	if(this->valid())
	    return this->CurrentNode->info;
	else
	    throw exception();
//	return NULL_TPAIR;
}
/// Theta(1)

