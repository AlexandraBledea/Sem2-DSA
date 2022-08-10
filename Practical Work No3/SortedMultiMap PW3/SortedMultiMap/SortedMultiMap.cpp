#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->relation = r;
    this->capacity = 10;
    this->DLLANodes = new Node[this->capacity];
    this->length = 0;
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->DLLANodes[firstEmpty].prev = -1;
    this->DLLANodes[firstEmpty].next = 1;
    this->DLLANodes[firstEmpty].info = NULL_TELEM;
    ///We set the previous and the next for the first empty position
    ///After that we set the links between the other nodes from the array, starting from the second node until the last but one
    for (int i = 1; i < this->capacity - 1; i++)
    {
        ///We establish the position path for the rest of the nodes
        this->DLLANodes[i].next = i + 1;
        this->DLLANodes[i].prev = i - 1;
        this->DLLANodes[i].info = NULL_TELEM;
    }
    this->DLLANodes[this->capacity - 1].next = -1;
    this->DLLANodes[this->capacity - 1].prev = this->capacity - 2;
    this->DLLANodes[this->capacity - 1].info = NULL_TELEM;
}
/// Theta(this->capacity)


vector<TValue> SortedMultiMap::removeKey(TKey key) {
    vector<TValue> values;
    int CurrentElement = this->head;
    int SecondCurrentElement;
    while(CurrentElement != -1){
        if(this->relation(this->DLLANodes[CurrentElement].info.first, key))
        {
                if (this->DLLANodes[CurrentElement].info.first == key) {
                    values.push_back(this->DLLANodes[CurrentElement].info.second);
                    SecondCurrentElement = this->DLLANodes[CurrentElement].next;
                    this->remove(key, this->DLLANodes[CurrentElement].info.second);
                    CurrentElement = SecondCurrentElement;
                }
                else
                    CurrentElement = this->DLLANodes[CurrentElement].next;
        }
        else
            break;
    }
    return values;
}
///Best Case: Theta(1)
///Worst Case: Theta((this->length)^2)
///Total Complexity: O((this->length)^2)

void SortedMultiMap::add(TKey c, TValue v) {
    ///We check first if we reached the maximum capacity, and in this case we do a resize
    if(this->length == this->capacity)
        this->resize();

    ///Case 1: The list is empty!
    if(this->length == 0 && this->head == -1)
    {
        this->length++;
        this->head=this->firstEmpty;

        this->firstEmpty=this->DLLANodes[this->firstEmpty].next;
        if(this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;

        this->DLLANodes[this->head].info.first = c;
        this->DLLANodes[this->head].info.second = v;

        this->DLLANodes[this->head].next = -1;
        this->tail = this->head;
    }
    else
    ///Case 2: the element has to be placed in front of the head
    if(this->relation(c, this->DLLANodes[this->head].info.first))
    {
        this->length++;
        int new_head = this->firstEmpty;

        this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
        if(this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;

        this->DLLANodes[new_head].next = this->head; ///We make the new node become the head, the next node from the new node will be the head
        this->DLLANodes[new_head].prev = -1;

        this->DLLANodes[new_head].info.first = c;
        this->DLLANodes[new_head].info.second = v;

        this->DLLANodes[this->head].prev = new_head; /// The previous node from the initial head will become the new node we just added, which became the head
        this->head = new_head;
    }
    else
    {
        int CurrentElement = this->head;
        while(this->DLLANodes[CurrentElement].next != -1 && !this->relation(c, this->DLLANodes[this->DLLANodes[CurrentElement].next].info.first))
        {
            CurrentElement = this->DLLANodes[CurrentElement].next;
        }
        /// Case 3: the element has to be placed after the tail
        if(this->DLLANodes[CurrentElement].next == -1)
        {
            this->length++;
            int new_element = this->firstEmpty;

            this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
            if(this->firstEmpty != -1)
                this->DLLANodes[this->firstEmpty].prev = -1;

            this->DLLANodes[this->tail].next = new_element;
            int old_tail = this->tail;
            this->tail = new_element;
            this->DLLANodes[this->tail].next = -1;
            this->DLLANodes[this->tail].prev = old_tail;

            this->DLLANodes[this->tail].info.first = c;
            this->DLLANodes[this->tail].info.second = v;
        }
        else
        /// Case 4: this means the element has to be placed somewhere between two nodes
        if(this->DLLANodes[CurrentElement].next != -1 && this->relation(c, this->DLLANodes[this->DLLANodes[CurrentElement].next].info.first))
        {
            this->length++;
            int new_element = this->firstEmpty;

            this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
            if(this->firstEmpty != -1)
                this->DLLANodes[this->firstEmpty].prev = -1;

            int NextElement = this->DLLANodes[CurrentElement].next;
            int PreviousElement = CurrentElement;
            DLLANodes[PreviousElement].next = new_element;

            DLLANodes[new_element].next = NextElement;
            DLLANodes[new_element].prev = PreviousElement;

            DLLANodes[new_element].info.first = c;
            DLLANodes[new_element].info.second = v;

            DLLANodes[NextElement].prev = new_element;

        }
    }
}
///Best case: Theta(1)
///Worst case: Theta(this->length)
///Average Case: O(this->length) => Total complexity: O(this->length)

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
	int CurrentElement = this->head;
	while(CurrentElement != -1){
	    if(this->relation(this->DLLANodes[CurrentElement].info.first, c))
        {
	        if(this->DLLANodes[CurrentElement].info.first == c)
            {
                values.push_back(this->DLLANodes[CurrentElement].info.second);
            }
            CurrentElement = this->DLLANodes[CurrentElement].next;
	    }
	    else
	        break;
	}
	return values;
}
///Best case: Theta(1)
///Worst case: Theta(this->length)
///Average Case: O(this->length) => Total complexity: O(this->length)

bool SortedMultiMap::remove(TKey c, TValue v) {
	int CurrentElement = this->head;
	while(CurrentElement != -1)
    {
	    /// We found the element
	    if(this->DLLANodes[CurrentElement].info.first == c and this->DLLANodes[CurrentElement].info.second == v)
        {
	        this->DLLANodes[CurrentElement].info = NULL_TELEM;
	        this->length--;

	        ///Now we have to remove the element from the list
	        ///Case 1: It means the list have only one element
	        if(CurrentElement == this->head && CurrentElement == this->tail)
            {
	            this->head = -1;
	            this->tail = -1;
            }
	        ///Case 2: It means the element we have to remove is the head
	        else if(CurrentElement == this->head)
            {
	            this->head = this->DLLANodes[this->head].next;
	            this->DLLANodes[this->head].prev = -1;
            }
	        ///Case 3: It means the element we have to remove is the tail
	        else if(CurrentElement == this->tail)
            {
	            this->tail = this->DLLANodes[this->tail].prev;
	            this->DLLANodes[this->tail].next = -1;
            }
	        ///Case 4: It means the element we have to remove is somewhere between the head and the tail
	        else
            {

                int PreviousElement = this->DLLANodes[CurrentElement].prev;
                int NextElement = this->DLLANodes[CurrentElement].next;
                this->DLLANodes[PreviousElement].next = NextElement;
                this->DLLANodes[NextElement].prev = PreviousElement;

            }
	        ///We free the position of the deleted node
	        free(CurrentElement);
	        return true;
        }
	    else
	        CurrentElement = this->DLLANodes[CurrentElement].next;

    }
    return false;
}
///Best case: Theta(1)
///Worst case: Theta(this->length)
///Average Case: O(this->length) => Total complexity: O(this->length)


int SortedMultiMap::size() const {
    return this->length;
}
///Theta(1)

bool SortedMultiMap::isEmpty() const {
	if(this->length == 0)
	    return true;
	return false;
}
///Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
///Theta(1)

SortedMultiMap::~SortedMultiMap() {
	delete[] this->DLLANodes;
}
///Theta(1)

void SortedMultiMap::resize() {

    this->capacity = 2*this->capacity;
    Node* NewArray = new Node[this->capacity];
    for(int i=0; i<this->length; i++)
        NewArray[i] = this->DLLANodes[i];

    this->firstEmpty = this->length;
    NewArray[firstEmpty].prev = -1;
    NewArray[firstEmpty].next = this->length + 1;
    NewArray[firstEmpty].info = NULL_TELEM;

    for(int i=this->length + 1; i<this->capacity -1; i++)
    {
        NewArray[i].prev = i - 1;
        NewArray[i].next = i + 1;
        NewArray[i].info = NULL_TELEM;
    }
    NewArray[this->capacity - 1].prev = this->capacity - 2;
    NewArray[this->capacity - 1].next = -1;
    NewArray[this->capacity - 1].info = NULL_TELEM;

    delete[] this->DLLANodes;
    this->DLLANodes = NewArray;
}
///Theta(this->capacity) We have two loops, one which go from 0 to capacity/2 and the other one which goes from capacity/2 until capacity

int SortedMultiMap::allocate() {
    int newElem = this->firstEmpty;
    if (newElem != -1) {
        this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
        if(this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;
        this->DLLANodes[newElem].next = -1;
        this->DLLANodes[newElem].prev = -1;
    }
    return newElem;
}
///Theta(1)

void SortedMultiMap::free(int position) {
    this->DLLANodes[position].next = this->firstEmpty;
    this->DLLANodes[position].prev = -1;
    this->DLLANodes[this->firstEmpty].prev = position;
    this->firstEmpty = position;
}
///Theta(1)




//void SortedMultiMap::add(TKey c, TValue v) {
//    int Current = this->head;
//    int CurrentPosition = 0;
//    while (Current != -1 && CurrentPosition < this->length && this->relation(this->DLLANodes[Current].info.first, c)) {
//        Current = this->DLLANodes[Current].next;
//        CurrentPosition = CurrentPosition + 1;
//    }
//    ///We allocate the new position
//    int NewPosition = this->allocate();
//    if (NewPosition == -1 && this->length == this->capacity) {
//        this->resize();
//        ///We alloc again the new position because we made a resize!
//        NewPosition = this->allocate();
//    }
//    bool Head = false;
//    this->DLLANodes[NewPosition].info.first = c;
//    this->DLLANodes[NewPosition].info.second = v;
//    if (Current == this->head) {
//        Head = true;
//        ///Case 1: It means the list is empty!
//        if (this->head == -1) {
//            this->head = NewPosition;
//            this->tail = this->head;
//        }
//            ///Case 2: It means we have to insert the new node in front of the initial head
//        else
//        {
//            this->DLLANodes[NewPosition].next = this->head;
//            this->DLLANodes[this->head].prev = NewPosition;
//            this->head = NewPosition;
//        }
//    }
//    if(!Head)
//    {
//        ///Case 3: It means we have to insert the new node at the end, which means it will become the tail
//        if(Current == -1)
//        {
//            this->DLLANodes[NewPosition].prev = this->tail;
//            this->DLLANodes[this->tail].next = NewPosition;
//            this->tail = NewPosition;
//        }
//            ///Case 4: It means we have to insert the new node somewhere between two other Nodes
//        else
//        {
//            int Next = Current;
//            int Previous = this->DLLANodes[Current].prev;
//            this->DLLANodes[NewPosition].next = Next;
//            this->DLLANodes[NewPosition].prev = Previous;
//            this->DLLANodes[Next].prev = NewPosition;
//            this->DLLANodes[Previous].next = NewPosition;
//        }
//
//    }
//    this->length++;
//}


//
//void SortedMultiMap::add(TKey c, TValue v) {
//    //TODO - Implementation
//    ///We check first if we reached the maximum capacity, and in this case we do a resize
//    int NewPosition = allocate();
//    if(this->length == this->capacity)
//    {
//        this->resize();
//        NewPosition = allocate();
//    }
//    this->DLLANodes[NewPosition].info.first = c;
//    this->DLLANodes[NewPosition].info.second = v;
//
//    ///Case 1: The list is empty!
//    if(this->length == 0 && this->head == -1)
//    {
//        this->length++;
//        this->head=NewPosition;
//        this->tail = this->head;
//    }
//    else
//        ///Case 2: the element has to be placed in front of the head
//    if(this->relation(c, this->DLLANodes[this->head].info.first))
//    {
//        this->length++;
//        this->DLLANodes[NewPosition].next = this->head; ///We make the new node become the head, the next node from the new node will be the head
//        this->DLLANodes[this->head].prev = NewPosition; /// The previous node from the initial head will become the new node we just added, which became the head
//        this->head = NewPosition;
//    }
//    else
//    {
//        int CurrentElement = this->head;
//        while(this->DLLANodes[CurrentElement].next != -1 && !this->relation(c, this->DLLANodes[this->DLLANodes[CurrentElement].next].info.first))
//        {
//            CurrentElement = this->DLLANodes[CurrentElement].next;
//        }
//        /// Case 3: the element has to be placed after the tail
//        if(this->DLLANodes[CurrentElement].next != -1)
//        {
//            this->length++;
//            this->DLLANodes[NewPosition].prev = this->tail;
//            this->DLLANodes[this->tail].next = NewPosition;
//            this->tail = NewPosition;
//        }
//        else
//            /// Case 4: this means the element has to be placed somewhere between two nodes
//        if(this->relation(c, this->DLLANodes[this->DLLANodes[CurrentElement].next].info.first))
//        {
//            this->length++;
//            int NextElement = this->DLLANodes[CurrentElement].next;
//            int PreviousElement = CurrentElement;
//            DLLANodes[PreviousElement].next = NewPosition;
//            DLLANodes[NewPosition].next = NextElement;
//            DLLANodes[NewPosition].prev = PreviousElement;
//            DLLANodes[NextElement].prev = NewPosition;
//        }
//    }
//
//}