#include "Matrix.h"
#include <exception>
using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {
    this->capacity = 5;
    this->nrElements = 0;
    this->nrLine = nrLines;
    this->nrCol = nrCols;
    this->root = -1;
    this->firstEmpty = 0;
    this->SLLANodes = new Node[this->capacity];
    this->SLLANodes[firstEmpty].left = 1;
    this->SLLANodes[firstEmpty].right = -1;
    this->SLLANodes[firstEmpty].parent = -1;
    get<2>(this->SLLANodes[firstEmpty].info) = NULL_TELEM;
    for(int i = 1; i < this->capacity - 1; i++)
    {
        this->SLLANodes[i].left = i + 1;
        this->SLLANodes[i].right = -1;
        this->SLLANodes[i].parent = -1;
        get<2>(this->SLLANodes[i].info) = NULL_TELEM;
    }
    this->SLLANodes[this->capacity - 1].right = -1;
    this->SLLANodes[this->capacity - 1].left = -1;
    this->SLLANodes[this->capacity - 1].parent = -1;
    get<2>(this->SLLANodes[this->capacity - 1].info) = NULL_TELEM;
}
///Theta(this->capacity)


int Matrix::nrLines() const {
	return this->nrLine;
}
///Theta(1)

int Matrix::nrColumns() const {
    return this->nrCol;
}
///Theta(1)

TElem Matrix::element(int i, int j) const {
	if(i < 0 || i >= this->nrLine)
	    throw exception();
	if(j < 0 || j >= this->nrCol)
	    throw exception();

	int currentNode = this->root;
//	if(currentNode != -1 && get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j) {
//        return get<2>(this->SLLANodes[currentNode].info);
//    }
	while(currentNode != -1)
    {
        if( get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j) {
            return get<2>(this->SLLANodes[currentNode].info);
        }
        if(get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j){
            currentNode = this->SLLANodes[currentNode].right;
        }
        else if(get<0>(this->SLLANodes[currentNode].info) < i){
            currentNode = this->SLLANodes[currentNode].right;
        }
        else if(get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j){
            currentNode = this->SLLANodes[currentNode].left;
        }
        else if(get<0>(this->SLLANodes[currentNode].info) > i){
            currentNode = this->SLLANodes[currentNode].left;
        }
    }

	return NULL_TELEM;
}
///Best case: Theta(1) -> if the element we search is exactly the root
///Worst case: Theta(this->nrElements) -> if the element we searched is not in the tree
///Total complexity: O(this->nrElements)


TElem Matrix::modify(int i, int j, TElem e) {
    ///Case 1: currentValue = 0 and newValue = 0 -> do nothing
    ///Case 2: currentValue = 0 and newValue != 0 -> insert in the data structure
    ///Case 3: currentValue != 0 and newValue = 0 -> remove from the data structure
    ///Case 4: currentValue !=0 and newValue != 0 -> just change the value in the data structure

    if(i < 0 || i >= this->nrLine)
        throw exception();
    if(j < 0 || j >= this->nrCol)
        throw exception();

    MCell newCell = MCell(i, j, e);
    if(e != 0) ///We have to modify the value or insert a new one
    {
        int currentNode = this->root;
        int previousNode = 0;
        while(currentNode != -1) {
            ///The first if refers to the following case:
            ///We have to modify the value of the cell
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j)
            {
                TElem oldValue = get<2>(this->SLLANodes[currentNode].info);
                this->SLLANodes[currentNode].info = newCell;
                return oldValue;
            }
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].right;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) < i)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].right;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].left;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) > i)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].left;
            }
        }

        ///Here we add a new element
        ///Case 1: The binary search tree is empty so the first added node will become the root
        if(this->root == -1){
            int position = this->allocate();
            if(position == -1 && this->nrElements == this->capacity)
            {
                this->resize();
                position = this->allocate();
            }
            this->SLLANodes[position].info = newCell;
            this->root = position;
            this->nrElements++;
            return 0;
        }

        ///Case 2: In this case we found the node for which we add a new "child"
        int position = this->allocate();
        if(position == -1 && this->nrElements == this->capacity)
        {
            this->resize();
            position = this->allocate();
        }
        /// It means we have to add the new node as the right child
        if((get<0>(this->SLLANodes[previousNode].info) == i and get<1>(this->SLLANodes[previousNode].info) < j) || get<0>(this->SLLANodes[previousNode].info) < i)
        {
            this->SLLANodes[previousNode].right = position;
            this->SLLANodes[position].info = newCell;
            this->SLLANodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }
        /// It means we have to add the new node as the left child
        else
        {   this->SLLANodes[previousNode].left = position;
            this->SLLANodes[position].info = newCell;
            this->SLLANodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }

    }
    else///We have to remove the value or do nothing
    {
        int currentNodeToBeRemoved = 0;

        int currentNode = this->root;

        bool stop = false;

//        ///Case 1: We have only one node in the three and this is the root
//        if(get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j and this->nrElements == 1){
//            this->root = -1;
//            TElem oldValue = get<2>(this->SLLANodes[currentNode].info);
//            free(currentNode);
//            return oldValue;
//        }

        while (currentNode != -1 and !stop) {
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j)
            {
                currentNodeToBeRemoved = currentNode;
                stop = true;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j) {
                currentNode = this->SLLANodes[currentNode].right;
            } else if (get<0>(this->SLLANodes[currentNode].info) < i) {
                currentNode = this->SLLANodes[currentNode].right;
            } else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j) {
                currentNode = this->SLLANodes[currentNode].left;
            } else if (get<0>(this->SLLANodes[currentNode].info) > i) {
                currentNode = this->SLLANodes[currentNode].left;
            }
        }

        ///It means the currentValue from that position is 0 and the new value we want to add is also 0, so we do nothing
        if(currentNode == -1)
            return 0;

        int numberOfDescendants = 0;

        if(this->SLLANodes[currentNodeToBeRemoved].left != -1)
            numberOfDescendants++;

        if(this->SLLANodes[currentNodeToBeRemoved].right != -1)
            numberOfDescendants++;

        ///In this case, the node we are about to delete doesn't have a descendent.
        if(numberOfDescendants == 0)
        {
            ///Case 1: we have only one node in the tree which is the root
            if(currentNodeToBeRemoved == this->root){
                this->root = -1;
                TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                free(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
            ///Case 2: the node we are about to delete is a leaf
            else
            {
                int parent = this->SLLANodes[currentNodeToBeRemoved].parent;
                ///We check if it was the left child of the parent
                if(this->SLLANodes[parent].left == currentNodeToBeRemoved){
                    this->SLLANodes[parent].left = -1;
                }
                ///We check if it was the right child of the parent
                else if(this->SLLANodes[parent].right == currentNodeToBeRemoved){
                    this->SLLANodes[parent].right = -1;
                }
                TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                free(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
        }
        ///In this case, the node we are about to delete has one descendent
        else if(numberOfDescendants == 1){
            ///Case 1: the node is the root
            if(currentNodeToBeRemoved == this->root){
                ///We check if the root had a left child
                if(this->SLLANodes[currentNodeToBeRemoved].left != -1){
                    TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                    ///We set the new root as being the left child of the root we are about to delete
                    this->root = this->SLLANodes[currentNodeToBeRemoved].left;
                    ///We set the parent of the new root with -1
                    this->SLLANodes[this->root].parent = -1;
                    free(currentNodeToBeRemoved);
                    this->nrElements--;
                    return oldValue;
                }
                ///We check if the root had a right child
                else if(this->SLLANodes[currentNodeToBeRemoved].right != -1){
                    TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                    ///We set the new root as being the right child of the root we are about to delete
                    this->root = this->SLLANodes[currentNodeToBeRemoved].right;
                    ///We set the parent of the new root with -1
                    this->SLLANodes[this->root].parent = -1;
                    free(currentNodeToBeRemoved);
                    this->nrElements--;
                    return oldValue;
                }
            }
            ///Case 2: the node is inside the three
            else{
                ///We check if the node had a left child
                if(this->SLLANodes[currentNodeToBeRemoved].left != -1) {

                    ///We keep the parent of the node we want to delete
                    int parent = this->SLLANodes[currentNodeToBeRemoved].parent;

                    ///We check if the node we want to delete was a left child of its parent
                    if (this->SLLANodes[parent].left == currentNodeToBeRemoved) {

                        ///We set the parent for the left child of the node we want to delete with the parent of the node we want to delete
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].left].parent = parent;

                        ///We set the left child of the parent of the node we want to delete with the left child of the node we want to delete
                        this->SLLANodes[parent].left = this->SLLANodes[currentNodeToBeRemoved].left;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                    ///We check if the node we want to delete was a right child of its parent
                    else if(this->SLLANodes[parent].right == currentNodeToBeRemoved){

                        ///We set the parent for the left child of the node we want to delete with the parent of the node we want to delete
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].left].parent = parent;

                        ///We set the right child of the parent of the node we want to delete with the left child of the node we want to delete
                        this->SLLANodes[parent].right = this->SLLANodes[currentNodeToBeRemoved].left;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                }
                ///We check if the node had a right child
                else if(this->SLLANodes[currentNodeToBeRemoved].right != -1){

                    ///We keep the parent of the node we want to delete
                    int parent = this->SLLANodes[currentNodeToBeRemoved].parent;

                    ///We check if the node we want to delete was a left child of its parent
                    if(this->SLLANodes[parent].left == currentNodeToBeRemoved){

                        ///We set the parent for the right child of the node we want to delete with the parent of the node we want to delete
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].right].parent = parent;

                        ///We set the left child of the parent of the node we want to delete with the right child of the node we want to delete
                        this->SLLANodes[parent].left = this->SLLANodes[currentNodeToBeRemoved].right;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                    ///We check if the node we want to delete was a right child of its parent
                    else if(this->SLLANodes[parent].right == currentNodeToBeRemoved){

                        ///We set the parent for the right child of the node we want to delete with the parent of the node we want to delete
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].right].parent = parent;

                        ///We set the right child of the parent of the node we want to delete with the right child of the node we want to delete
                        this->SLLANodes[parent].right = this->SLLANodes[currentNodeToBeRemoved].right;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }

                }
            }

        }
        ///It means the node we want to remove has 2 descendents
        ///We take the right child of the node we want to delete, in order to start the search for the minimum from there
        int rightChild = this->SLLANodes[currentNodeToBeRemoved].right;
        int replacedNode = this->findMinimum(rightChild);

        ///In this part we only detach the minimum from the tree

        ///Case 1: The minimum is a leaf
        ///We check only the right part because, being the minimum, it will always have a child only in the right, if it also had a child in the left, then it wouldn't be the minimum
        if(this->SLLANodes[replacedNode].right == -1){
            ///We keep the parent of the minimum
            int parent = this->SLLANodes[replacedNode].parent;

            ///We mark the parent of the minimum with -1 for now
            this->SLLANodes[replacedNode].parent = -1;

            ///We check if the minimum was a left child or a right child for its parent
            if(this->SLLANodes[parent].left == replacedNode) {
                this->SLLANodes[parent].left = -1;
            }
            else if(this->SLLANodes[parent].right == replacedNode){
                this->SLLANodes[parent].right = -1;
            }

        }

        ///Case 2: The minimum has a right child
        ///We check only the right part because, being the minimum, it will always have a child only in the right, if it also had a child in the left, then it wouldn't be the minimum
        else if(this->SLLANodes[replacedNode].right != -1){
            ///We keep the parent of the minimum
            int parent = this->SLLANodes[replacedNode].parent;

            ///We check if the minimum was a left child or a right child of its parent and we place there its own right child
            if(this->SLLANodes[parent].left == replacedNode) {
                this->SLLANodes[parent].left = this->SLLANodes[replacedNode].right;
            }
            else if(this->SLLANodes[parent].right == replacedNode){
                this->SLLANodes[parent].right = this->SLLANodes[replacedNode].right;
            }
            ///We keep the child of the minimum
            int child = this->SLLANodes[replacedNode].right;

            ///We mark the parent of the child's minimum
            this->SLLANodes[child].parent = parent;

            ///We mark the parent of the minimum with -1 for now
            this->SLLANodes[replacedNode].parent = -1;

        }
        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
        ///We change the value of the node we wanted to delete with the value of the minimum
        this->SLLANodes[currentNodeToBeRemoved].info = this->SLLANodes[replacedNode].info;
        ///We delete the minimum from the tree
        free(replacedNode);
        this->nrElements--;
        return oldValue;


//        ///Case 1: the node with the two descendents is the root
//        if(currentNodeToBeRemoved == this->root){
//
//            ///We set for the minimum the child's of the old root
//            this->SLLANodes[replacedNode].left = this->SLLANodes[this->root].left;
//            this->SLLANodes[replacedNode].right = this->SLLANodes[this->root].right;
//
//            MCell rootNodeInfo = this->SLLANodes[this->root].info;
//            free(this->root);
//            this->nrElements--;
//            this->root = replacedNode;
//            TElem oldValue = get<2>(rootNodeInfo);
//            return oldValue;
//        }
//        ///Case 2: the child we want to remove is inside the tree and has two descendents
//        else{
//
//            ///We connect the node with the new parent
//            int parent = this->SLLANodes[currentNodeToBeRemoved].parent;
//            this->SLLANodes[replacedNode].parent = parent;
//
//            ///We set for the minimum the child's of the old parent
//            this->SLLANodes[replacedNode].left = this->SLLANodes[currentNodeToBeRemoved].left;
//            this->SLLANodes[replacedNode].right = this->SLLANodes[currentNodeToBeRemoved].right;
//
//            TElem  oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
//            free(currentNodeToBeRemoved);
//            this->nrElements--;
//            return oldValue;
//        }


    }
}
///Best case: Theta(1)
///Worst case: Theta(this->nrElements)
///Total complexity: O(this->nrElements)

int Matrix::findMinimum(int position) {
    while(this->SLLANodes[position].left != -1){
        position = this->SLLANodes[position].left;
    }
    return position;
}
///Best case: Theta(1)
///Worst case: Theta(this->nrElements)
///Total complexity: O(this->nrElements)

void Matrix::resize() {
    this->capacity = 2*this->capacity;
    Node* NewArray = new Node[this->capacity];
    for(int i = 0; i < this->nrElements; i++)
    {
        NewArray[i] = this->SLLANodes[i];
    }

    this->firstEmpty = this->nrElements;
    NewArray[firstEmpty].left = this->nrElements + 1;
    NewArray[firstEmpty].right = -1;
    NewArray[firstEmpty].parent = -1;
    get<2>(NewArray[firstEmpty].info) = NULL_TELEM;
    for(int i = this->nrElements + 1; i < this->capacity - 1; i++){
        NewArray[i].left= i + 1;
        NewArray[i].right = -1;
        NewArray[i].parent = -1;
        get<2>(NewArray[i].info) = NULL_TELEM;
    }
    NewArray[this->capacity - 1].right = -1;
    NewArray[this->capacity - 1].left = -1;
    NewArray[this->capacity - 1].parent = -1;
    get<2>(NewArray[this->capacity - 1].info) = NULL_TELEM;

    delete[] this->SLLANodes;
    this->SLLANodes = NewArray;
}
///Theta(this->capacity)

int Matrix::allocate() {
    int newElement = this->firstEmpty;
    if(newElement != -1){
        this->firstEmpty = this->SLLANodes[this->firstEmpty].left;
        this->SLLANodes[newElement].left = -1;
        this->SLLANodes[newElement].right = -1;
        this->SLLANodes[newElement].parent = -1;
    }
    return newElement;
}
///Theta(1)

void Matrix::free(int position) {
    this->SLLANodes[position].left = this->firstEmpty;
    get<2>(this->SLLANodes[position].info) = NULL_TELEM;
    this->SLLANodes[position].right = -1;
    this->SLLANodes[position].parent = -1;
    this->firstEmpty = position;
}
///Theta(1)


int Matrix::recursiveSearch(int position, TElem value) const{
    if(position == -1 || get<2>(this->SLLANodes[position].info) == value)
        return position;

    int rightPosition = this->recursiveSearch(this->SLLANodes[position].right, value);
    if(rightPosition != -1)
        return rightPosition;

    int leftPosition = this->recursiveSearch(this->SLLANodes[position].left, value);
    if(leftPosition != -1)
        return leftPosition;

    return -1;
}

std::pair<int, int> Matrix::positionOf(TElem elem) const {
    int position = this->recursiveSearch(this->root, elem);
    if(position == -1){
        return std::make_pair(-1,-1);
    }
    int line = get<0>(this->SLLANodes[position].info);
    int column = get<1>(this->SLLANodes[position].info);
    return std::make_pair(line,column);
}


///Best case: Theta(1) -> if the element we searched is exactly the root
///Worst case: Theta(this->nrOfElements) ->if the element we searched for is not in the tree
///Total complexity: O(this->nrOfElements)

