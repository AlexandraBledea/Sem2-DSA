#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->m = 30;
	this->loadFactor = 0.7;
	this->numberOfElements = 0;

	this->hashTable = new Node*[this->m];

	for(int i = 0; i < this->m; i++)
	    this->hashTable[i] = nullptr;
}
///Theta(m), where m represents the capacity of the hashTable

void MultiMap::add(TKey c, TValue v) {
    if((double)(this->numberOfElements/this->m) > this->loadFactor)
        this->resize();

	int position = this->hashFunction(c);
	Node* newNode = new Node;
	newNode->info.first = c;
	newNode->info.second = v;
	newNode->next = this->hashTable[position];
	this->hashTable[position] = newNode;
	this->numberOfElements++;
}
///Theta(1) amortized because sometimes we have to make a resize

bool MultiMap::remove(TKey c, TValue v) {
	int position = this->hashFunction(c);

    if(this->hashTable[position] == nullptr)
        return false;

    Node* currentNode = this->hashTable[position];
    Node* previousNode;

    /// In this case we check if the element we have to remove is exactly the first one from the linked list
    if(currentNode->info.first == c && currentNode->info.second == v)
    {
        Node* nextNode = currentNode->next;
        this->hashTable[position] = nextNode;
        delete currentNode;
        this->numberOfElements--;
        return true;
    }

    /// If we reach this case it means we have to look for the key and the corresponding value through all the nodes
    while(currentNode != nullptr && (currentNode->info.first !=c || currentNode->info.second !=v)){
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    /// If we reach this case it means the element we were looking for is not in the list
    if(currentNode == nullptr)
        return false;

    /// If we reach this case it means we found the element
    previousNode->next = currentNode->next;
    delete currentNode;
    this->numberOfElements--;
    return true;
}
///Best case: Theta(1)
///Worst case: Theta(nrOfElements)
///Average case: Theta(loadFactor)
///Total Complexity: O(nrOfElements)

vector<TValue> MultiMap::search(TKey c) const {
    int position = this->hashFunction(c);

    vector<TValue> values;

    if(this->hashTable[position] == nullptr)
        return values;

    Node* currentNode = this->hashTable[position];
    while(currentNode != nullptr)
    {
        if(currentNode->info.first == c)
            values.push_back(currentNode->info.second);
        currentNode = currentNode->next;
    }

    return values;
}
///Best case: Theta(1)
///Worst case: Theta(nrOfElements)
///Average case: Theta(loadFactor)
///Total Complexity: O(nrOfElements)

int MultiMap::size() const {
	return this->numberOfElements;
}
///Theta(1)

bool MultiMap::isEmpty() const {
	if(this->numberOfElements == 0)
	    return true;
	return false;
}
///Theta(1)

MultiMapIterator MultiMap::iterator() {
	return MultiMapIterator(*this);
}
///Theta(1)

MultiMap::~MultiMap() {
    for(int i = 0; i < this->m; i++)
    {
        Node* currentNode;
        while(this->hashTable[i] != nullptr) {
            currentNode = this->hashTable[i]->next;
            delete this->hashTable[i];
            this->hashTable[i] = currentNode;
        }
    }
    delete[] this->hashTable;
}
///Theta(m*nrOfElements), where m represents the capacity of the hashTable

int MultiMap::hashFunction(int element) const {
    if(element < 0)
        element = abs(element);
    return element % this->m;
}
///Theta(1)

void MultiMap::resize() {

    Node** newHashTable = new Node*[this->m*2];
    Node* currentNode;
    int newPosition;
    this->m = this->m*2;

    ///We initialize the positions of the new hashtable with null pointer;
    for(int i = 0; i < this->m; i++)
    {
        newHashTable[i] = nullptr;
    }

    for(int i = 0; i < this->m/2; i++){
        currentNode = this->hashTable[i];
        while(currentNode!= nullptr)
        {
            ///We compute the new position
            newPosition = this->hashFunction(currentNode->info.first);

            ///We create the new node
            Node* newNode = new Node;
            newNode->info.first = currentNode->info.first;
            newNode->info.second = currentNode->info.second;

            ///We add the new node to the its corresponding linked list on the first position
            newNode->next = newHashTable[newPosition];
            newHashTable[newPosition] = newNode;

            currentNode = currentNode->next;
        }
    }

    for(int i = 0; i < this->m/2; i++)
    {
        Node* currentNode;
        while(this->hashTable[i] != nullptr) {
            currentNode = this->hashTable[i]->next;
            delete this->hashTable[i];
            this->hashTable[i] = currentNode;
        }
    }

    this->hashTable = newHashTable;
}
///Theta(m + nrOfElements)
///By the fact that the loadFactor is = 0.7 it means that nrOfElements is always < m. Thus, the complexity will be Theta(m)
