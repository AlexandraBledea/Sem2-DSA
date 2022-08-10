#include "SortedBag.h"
#include "../SortedBagIterator/SortedBagIterator.h"
#include <exception>
using namespace std;

SortedBag::SortedBag(Relation r) {
    this->capacity = 100;
    this->nrPairs = 0;
    this->elements = new TElem[this->capacity];
    this->relation = r;
}

void SortedBag::add(TComp e)
{
    int index = 0;  ///We use this in order to go through all the pairs
    int element_position = 0; /// We save the position on which we should insert the element
    bool the_same_element = false; /// We keep track whether the element already exists or not
    bool found = false; /// We keep track whether we found the fact that the element already exists or if not, the
    ///position on which it should be inserted
    bool first_found = false; /// We keep track whether we have to place the element on the first position of the array
    /// or not

    if(this->nrPairs >= capacity) /// This is the condition for a resize
    {
        resize();
    }

    if(this->nrPairs == 0) /// In this case, it means we have no elements so we place the fist one on position 0
    {
        elements[this->nrPairs].first = e;
        elements[this->nrPairs].second = 1;
        first_found = true;
        this->nrPairs++;
    }

//    if(this->elements[this->nrPairs - 1].first < e)
//    {
//        this->elements[this->nrPairs].first = e;
//        this->elements[this->nrPairs].second = 1;
//        last_element = true;
//        this->nrPairs++;
//    }

	while(index < this->nrPairs && !found && !first_found)
    {
	    if(this->elements[index].first == e && !the_same_element) /// We check whether the element already exists
	    {
            found = true;
            this->elements[index].second++;
            the_same_element = true;
        }
	    else
        if(relation(e, this->elements[index].first) && !the_same_element) /// If it doesn't then we check the relation
        {
            element_position = index;
            found = true;
        }
        index++;
    }

	index = this->nrPairs;
	bool final_case = false;

	while(index > element_position && !the_same_element && found && !first_found) /// In case the element doesn't exist
	/// We shift all the elements to the right once in order to make place for the element which will be inserted.
    {
        this->elements[index].first = this->elements[index - 1].first;
        this->elements[index].second = this->elements[index - 1].second;
        final_case = true;
        index--;
    }
	if(final_case)
    {
	    nrPairs++;
        this->elements[element_position].first = e;
        this->elements[element_position].second = 1;
    }
	if(!the_same_element && !found && !final_case && !first_found)
	/// If we reached this place it means that the element should be placed on the last position of the array
	{
        this->elements[nrPairs].first = e;
        this->elements[nrPairs].second = 1;
        nrPairs++;
	}
}
/// Best case: Theta(1)
/// Worst case: Theta(nrPairs)
/// Total Complexity : O(nrPairs)

bool SortedBag::remove(TComp e) {
	bool found = false; /// With this we keep track whether the element was found and removed or was not found
    int index = 0;
    int element_position = 0; /// Represents the position of the element we are about to remove
    bool one_occurrence = false; /// With this we keep track whether the element's frequency is 1 and if we remove it
    /// then we have to shift all the elements with one position to left

    while(index < this->nrPairs && !found && !one_occurrence)
    {
        if(elements[index].first == e)
        {
            elements[index].second--;
            element_position = index;
            found = true;
        }
        if(elements[index].second == 0)
        {
            one_occurrence = true;
            this->nrPairs--;
        }
        index++;
    }
    index = element_position;
    while(one_occurrence && index < this->nrPairs && found)
    {
        this->elements[index].first = this->elements[index + 1].first;
        this->elements[index].second = this->elements[index + 1].second;
        index++;
    }
    if(found)
        return true;
    else
	    return false;
}

/// Best case: Theta(1)
/// Worst case: Theta(nrPairs)
/// Total Complexity : O(nrPairs)

bool SortedBag::search(TComp elem) const {

    int index = 0;
    int found = false;
    while(index < this->nrPairs && !found)
    {
        if(this->elements[index].first == elem)
            found = true;
        index++;
    }
    if(found)
        return true;
    else
	    return false;
}
/// Best case: Theta(1)
/// Worst case: Theta(nrPairs)
/// Total Complexity : O(nrPairs)

int SortedBag::nrOccurrences(TComp elem) const {
    int index = 0;
    bool found = false; /// With this we keep track whether the element was found or not
    while(index < this->nrPairs && !found)
    {
        if(this->elements[index].first == elem)
            found = true;
        index++;
    }
    if(found)
	    return this->elements[index - 1].second;
    else
        return 0;
}
/// Best case: Theta(1)
/// Worst case: Theta(nrPairs)
/// Total Complexity : O(nrPairs)

int SortedBag::size() const {
	int index = 0;
	int size = 0;
	while(index < this->nrPairs)
    {
	    size = this->elements[index].second + size;
	    index++;
    }
	return size;
}
/// Best case: Theta(1)
/// Worst case: Theta(nrPairs)
/// Total Complexity : O(nrPairs)

bool SortedBag::isEmpty() const {
	if(this->nrPairs != 0)
	    return false;
	else
	    return true;
}
/// Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
/// Theta(1)

SortedBag::~SortedBag()
{
	    delete[] this->elements;
	    //delete this->elements;
}
/// Theta(1)

void SortedBag::resize() {
    TElem* NewElements;
    NewElements = new TElem[this->capacity*2];
    this->capacity = this->capacity * 2;
    for(int i = 0; i < this->nrPairs; i++)
    {
        NewElements[i].first = this->elements[i].first;
        NewElements[i].second = this->elements[i].second;
    }
    delete[] this->elements;
    //delete this->elements;
    this->elements = NewElements;
}
/// Total Complexity: Theta(nrPairs)