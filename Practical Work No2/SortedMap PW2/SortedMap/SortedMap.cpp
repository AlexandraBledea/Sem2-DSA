#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->relation = r;
	this->head = nullptr;
	this->length = 0;
}
/// Theta(1)

TValue SortedMap::add(TKey k, TValue v) {
    Node* NewNode = new Node;
    NewNode->info.first = k;
    NewNode->info.second = v;
    NewNode->next = nullptr;

    TValue OldValue;
	/// In this case we check if we don't have any node yet, and if we don't then it means the NewNode will become the head
    if(this->length == 0 && this->head == nullptr)
    {
        this->length++;
        this->head = NewNode;
        return NULL_TVALUE;
    }
    else
    ///In this case we check if the key of the NewNode is the same as the head, and if it is we change the value from the head
    if(this->head->info.first == k)
    {
        OldValue = this->head->info.second;
        this->head->info.second = NewNode->info.second;
        delete NewNode;
        return OldValue;
    }
    else
    ///In this case we check if the NewNode has to be placed in front of the head
    if(this->relation(NewNode->info.first, this->head->info.first) and this->head->info.first != k)
    {
        this->length++;
        NewNode->next = this->head;
        this->head = NewNode;
        return NULL_TVALUE;
    }
    else
        {
        Node* CurrentNode = this->head;
        while(CurrentNode->next != nullptr && CurrentNode->next->info.first != NewNode->info.first &&
        !this->relation(NewNode->info.first, CurrentNode->next->info.first))
        {
            CurrentNode = CurrentNode->next;
        }
        /// In this case we found the key of the NewNode so we just change the second value of the CurrentNode->next
        if(CurrentNode->next != nullptr && CurrentNode->next->info.first == NewNode->info.first)
        {
            OldValue = CurrentNode->next->info.second;
            CurrentNode->next->info.second = NewNode->info.second;
            delete NewNode;
            return OldValue;
        }
        else
        /// M am gandit la acest caz ca si cum am ajunge la ultimul Nod si relatia inca nu e indeplinita, iar astfel
        /// Elementul ar fi plasat exact la final (Nu stiu daca e corect)
        if(CurrentNode->next == nullptr)
        {
            this->length++;
            NewNode->next = CurrentNode->next;
            CurrentNode->next = NewNode;
            return NULL_TVALUE;
        }
        else
        /// In this case we didn't find the key of the NewNode so it means we have to add a new Node with the given
        /// information
//        if(this->relation(NewNode->info.first, CurrentNode->next->info.first))
        {
            this->length++;
            NewNode->next = CurrentNode->next;
            CurrentNode->next = NewNode;
            return NULL_TVALUE;
        }
    }
}
/// BestCase: Theta(1)
/// WorstCase: Theta(length)
/// Total Complexity: O(length)

TValue SortedMap::search(TKey k) const {
	Node* CurrentNode = this->head;
	while(CurrentNode != nullptr && CurrentNode->info.first != k)
    {
        CurrentNode = CurrentNode->next;
    }
    if(CurrentNode == nullptr)
        return NULL_TVALUE;
    else
        return CurrentNode->info.second;
}
/// BestCase: Theta(1)
/// WorstCase: Theta(length)
/// Total Complexity: O(length)

TValue SortedMap::remove(TKey k) {
	Node* CurrentNode = this->head;
	Node* Previous;
	TValue Deleted;
	/// In this case we check if the key we are looking for belongs to the head
	if(CurrentNode != nullptr && CurrentNode->info.first == k)
    {
	    Deleted = CurrentNode->info.second;
	    this->head = CurrentNode->next;
	    CurrentNode = nullptr;
	    delete CurrentNode;
	    this->length--;
	    return Deleted;
    }
	/// If we reach this case it means we have to look for the key through all the keys
	while(CurrentNode != nullptr && CurrentNode->info.first != k)
    {
	    Previous = CurrentNode;
	    CurrentNode = CurrentNode->next;
    }
	/// If we reach this case it means we didn't find the key through the elements
    if(CurrentNode == nullptr)
    {
        return NULL_TVALUE;
    }
    else
    /// If we reach this case it means we found the key
    if(CurrentNode->info.first == k)
    {
        Deleted = CurrentNode->info.second;
        Previous->next = CurrentNode->next;
        CurrentNode = nullptr;
        delete CurrentNode;
        this->length--;
        return Deleted;
    }
}
/// BestCase: Theta(1)
/// WorstCase: Theta(length) -> where the length represents the number of nodes
/// Total Complexity: O(length)

int SortedMap::size() const {
	return this->length;
}
/// Theta(1)

bool SortedMap::isEmpty() const {
	if(this->length == 0)
	    return true;
	return false;
}
/// Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
/// Theta(1)

SortedMap::~SortedMap() {
	Node* NewNode;
	while(this->head != nullptr)
    {
	    NewNode = this->head->next;
	    delete this->head;
	    this->head = NewNode;
    }
}
/// Theta(length)

//            if(CurrentNode->info.first == k) {
//                OldValue = CurrentNode->info.second;
//                CurrentNode->info.second = v;
//                return OldValue;
//            }
//            else
//            if(this->relation(NewNode->info.first, CurrentNode->info.first))
//            {
//
//            }