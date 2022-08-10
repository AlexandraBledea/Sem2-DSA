#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(MultiMap& c): col(c) {
	this->currentPositionInHashTable = 0;
    while(this->currentPositionInHashTable < this->col.m && this->col.hashTable[this->currentPositionInHashTable] == nullptr)
    {
        this->currentPositionInHashTable++;
    } /// We look for the first linked list which has elements

    if(this->currentPositionInHashTable < this->col.m)
    {
        this->previousNodeInLinkedList = nullptr;
        this->currentNodeInLinkedList = this->col.hashTable[this->currentPositionInHashTable];
    }
    else
    {
        this->previousNodeInLinkedList= nullptr;
        this->currentNodeInLinkedList = nullptr;
    } /// If there are no such lists then the iterator will become invalid

}
///Best case: Theta(1)
///Worst case: Theta(m), where m represents the capacity of the hashTable
///Total complexity: O(m)

TElem MultiMapIterator::getCurrent() const{
	if(this->valid() && this->col.size() > 0)
	    return this->currentNodeInLinkedList->info;
	else
	    throw exception();
}
///Theta(1)

bool MultiMapIterator::valid() const {
	if(this->currentNodeInLinkedList == nullptr || this->currentPositionInHashTable > this->col.m)
	    return false;
	return true;
}
///Theta(1)

void MultiMapIterator::next() {
	if(this->col.size() == 0)
	    throw exception();
    if(this->valid()) {
        ///In this case it means i still have elements in my linked list so i have to move to the next one
        if (this->currentNodeInLinkedList->next != nullptr) {
            this->previousNodeInLinkedList = this->currentNodeInLinkedList;
            this->currentNodeInLinkedList = this->currentNodeInLinkedList->next;
        }
        else
        {
            ///In this case it means i reached the end of the linked list so i have to search for another one
            this->currentPositionInHashTable++;
            while(this->currentPositionInHashTable < this->col.m && this->col.hashTable[this->currentPositionInHashTable] == nullptr){
                this->currentPositionInHashTable++;
            }

            if(this->currentPositionInHashTable < this->col.m){
                this->previousNodeInLinkedList = nullptr;
                this->currentNodeInLinkedList = this->col.hashTable[this->currentPositionInHashTable];}
            else{
                this->previousNodeInLinkedList = nullptr;
                this->currentNodeInLinkedList = nullptr;
            }
        }
    }
    else
        throw exception();
}
///Best case: Theta(1)
///Worst case: Theta(m), where m represents the capacity of the hashTable
///Total complexity: O(m)

void MultiMapIterator::first() {
    this->currentPositionInHashTable = 0;
    while(this->currentPositionInHashTable < this->col.m && this->col.hashTable[this->currentPositionInHashTable] == nullptr)
    {
        this->currentPositionInHashTable++;
    } /// We look for the first linked list which has elements

    if(this->currentPositionInHashTable < this->col.m)
    {
        this->previousNodeInLinkedList = nullptr;
        this->currentNodeInLinkedList = this->col.hashTable[this->currentPositionInHashTable];
    }
    else
    {
        this->previousNodeInLinkedList = nullptr;
        this->currentNodeInLinkedList = nullptr;
    } /// If there are no such lists then the iterator will become invalid
}
///Best case: Theta(1)
///Worst case: Theta(m), where m represents the capacity of the hashTable
///Total complexity: O(m)

TElem MultiMapIterator::remove() {
    if(this->valid() && this->col.size() > 0)
    {
//        if(this->previousNodeInLinkedList == nullptr && this->currentNodeInLinkedList == nullptr)
//            throw exception();

        TElem element = this->getCurrent();
        int position = this->col.hashFunction(element.first);

        ///In this case we check if the element we have to remove is exactly the first one
        if(this->previousNodeInLinkedList == nullptr){
            ///Mark the element which came after the one we just deleted
            Node* nextNode = this->currentNodeInLinkedList->next;
            ///Dealloc the memory for that node
            delete this->currentNodeInLinkedList;
            ///Set the corresponding position for the element in the hashtable
            this->currentNodeInLinkedList = nextNode;
            this->col.hashTable[position] = nextNode;
            this->col.numberOfElements--;
            return element;
        }

        ///In this case it means the element is found somewhere between two other elements
        ///We connect the previousNode with the Next node of the current node we just deleted
        this->previousNodeInLinkedList->next = this->currentNodeInLinkedList->next;
        delete this->currentNodeInLinkedList;
        this->currentNodeInLinkedList = this->previousNodeInLinkedList->next;
        this->col.numberOfElements--;
        return element;

    }
    else throw exception();
}
///Theta(1)

