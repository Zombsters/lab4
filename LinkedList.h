#pragma once
#include "Queue.h"

class LinkedList {
public:
	int rows; int cols; int size;
	Node* start; 
	LinkedList(int rows,int cols);
	void AddNode(int row, int col);
	void Print(); void PrintTraversal(int count,Node* traverse);
};

LinkedList::LinkedList(int rows, int cols) {
	this->rows = rows; this->cols = cols;
	size = rows * cols; 
	start = new Node(0, 0);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			AddNode(i, j);
		}
	}
}

void LinkedList::AddNode(int row, int col) {
	Node* traverse = start;
	Node* temp = new Node(row, col);

	if (row == 0 && col != 0){
		while (traverse->col != (col - 1)){
			traverse = traverse->right;
		}
		traverse->right = temp;
		temp->left = traverse;
	}
	else if (row != 0 && col == 0){
		while (traverse->row != (row - 1)){
			traverse = traverse->down;
		}
		traverse->down = temp;
		temp->up = traverse;
	}
	else {
		while (traverse->col < col){
			traverse = traverse->right;
		}
		while (traverse->down != NULL){
			traverse = traverse->down;
		}
		traverse->down = temp; temp->up = traverse;

		//set node (1,0)->right = temp
		traverse = start;
		while (traverse->row < row){
			traverse = traverse->down;
		}
		while (traverse->right != NULL){
			traverse = traverse->right;
		}
		traverse->right = temp; temp->left = traverse;
	}
}

void LinkedList::Print() {
	int count = 0; Node* traverse = start;
	while (traverse != NULL) {
		traverse->Print(); cout << traverse->visited << " ";
		traverse = traverse->right;
	}
	cout << endl; count++;
	if (count < rows) {
		traverse = start;
		for (int i = 0; i < count; i++) {
			traverse = traverse->down;
		}
		PrintTraversal(count,traverse);
	}
}

void LinkedList::PrintTraversal(int count, Node* traverse) {
	while (traverse != NULL) {
		traverse->Print(); cout << traverse->visited << " ";
		traverse = traverse->right;
	}
	cout << endl; count++;
	if (count < rows) {
		traverse = start;
		for (int i = 0; i < count; i++) {
			traverse = traverse->down;
		}
		PrintTraversal(count, traverse);
	}
}