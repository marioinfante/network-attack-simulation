#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include "Event.h"

class BinaryHeap {
private:
	Event* heap;
	int arraySize;
	int heapSize;
	int left(int);
	int right(int);
	int parent(int);
	void heapifyup(int);
	void heapifydown(int);
public:
	BinaryHeap();
	void Insert(Event);
	void DeleteMin();
	Event ExtractMin();
	int Size();
	bool isEmpty();
	~BinaryHeap() {
		delete[] heap;
	};
};

#endif