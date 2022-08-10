#pragma once

#include <tuple>
//DO NOT CHANGE THIS PART
typedef int TElem;
typedef std::tuple <int, int, TElem> MCell;
#define NULL_TELEM 0


struct Node{
    MCell info;
    int left;
    int right;
    int parent;
};

class Matrix {

private:
    Node* SLLANodes;
    int root;
    int firstEmpty;
    int nrCol;
    int nrLine;
    int capacity;
    int nrElements;


    int findMinimum(int position);
    int allocate();
    void free(int position);
    void resize();
    int recursiveSearch(int position, TElem value) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	TElem findClosest(TElem e);

	std::pair<int,int> positionOf(TElem elem) const;

};
