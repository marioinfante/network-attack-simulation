#include "Event.h"
#include "BinaryHeap.h"
#include <iostream>

using namespace std;

//intialize array with starting memory of 5
BinaryHeap::BinaryHeap() {
	heap = new Event[5];
	heapSize = 0;
	arraySize = 5;
}

//return size
int BinaryHeap::Size() {
	return heapSize;
}

//Insert Event object
void BinaryHeap::Insert(Event e) {
	if (heapSize == arraySize) {
		arraySize *= 2;
		Event* newHeap = new Event [arraySize];
		for (int i = 0; i < heapSize; i++) {
			newHeap[i] = heap[i];
		}
		delete[] heap;
		heap = newHeap;
	}
	heapSize++;
	heap[heapSize - 1] = e;
	heapifyup(heapSize - 1);
}

//Delete minimum Event
void BinaryHeap::DeleteMin() {
	if (heapSize == 0) {
		cout << "Heap is Empty" << endl;
		return;
	}
	heap[0] = heap[heapSize - 1];
	heapSize--;
	if (heapSize > 0)
		heapifydown(0);
}

//Extract minimum Event
Event BinaryHeap::ExtractMin() {
	if (heapSize == 0) {
		cout << "Heap is empty" << endl;
		Event e(0, 0, 0);
		return e;
	}
	return heap[0];
}

//return left node
int BinaryHeap::left(int parent) {
	int left = 2 * parent + 1;
	if (left < heapSize)
		return left;
	else
		return -1;
}

//return right node
int BinaryHeap::right(int parent) {
	int right = 2 * parent + 2;
	if (right < heapSize)
		return right;
	else
		return -1;
}

//return parent node
int BinaryHeap::parent(int child) {
	int parent = (child - 1) / 2;
	if (child == 0)
		return -1;
	else
		return parent;
}

//Heapify up to maintain heap structure
void BinaryHeap::heapifyup(int in) {
	Event parentNode = heap[parent(in)];
	Event thisNode = heap[in];
	if (in >= 0 && parent(in) >= 0 && parentNode.getTime() > thisNode.getTime()) {
		Event temp = heap[in];
		heap[in] = heap[parent(in)];
		heap[parent(in)] = temp;
		heapifyup(parent(in));
	}
}

//Heapify down to maintain heap structure
void BinaryHeap::heapifydown(int in)
{
	int child = left(in);
	int child1 = right(in);
	Event childNode = heap[child];
	Event child1Node = heap[child1];
	if (child >= 0 && child1 >= 0 && childNode.getTime() > child1Node.getTime()) {
		child = child1;
	}
	if (child > 0 && heap[in].getTime() > heap[child].getTime()) {
		Event temp = heap[in];
		heap[in] = heap[child];
		heap[child] = temp;
		heapifydown(child);
	}
}

//check if heap is empty
bool BinaryHeap::isEmpty() {
	return heapSize == 0;
}

