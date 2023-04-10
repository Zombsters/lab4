#pragma once
#pragma once
#include <iostream>
using namespace std;

class Node {
public:
    int row; int col;
    bool visited;
    bool visitedTwice; 
    bool visitedThrice;
    Node* left; Node* right;
    Node* up; Node* down;
    Node(int row,int col) {
        this->row = row;
        this->col = col;
        visited = false; visitedTwice = false; visitedThrice = false;
        left = NULL; right = NULL; up = NULL; down = NULL;
    }
    void Print() {
        cout << "(" << this->row << "," << this->col << ")";
    }

};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = NULL;
        rear = NULL;
    }

    void Print();
    void Dequeue();
    void Enqueue(Node* temp);
    Node* Front() {
        return front;
    }
    bool IsEmpty() {
        return front == NULL;
    }
};

void Queue::Print() {
    Node* traverse = front;
    while (traverse != NULL) {
        cout << "(" << traverse->row << "," << traverse->col << ")" << endl;
        traverse = traverse->right;
    }
}
void Queue::Dequeue() {
    Node* temp = front;
    if (front == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    else if (front == rear) {
        front = rear = NULL;
    }
    else {
        front = front->right;
    }
    delete temp;
}

void Queue::Enqueue(Node* temp) {
    cout << "enqueing: (" << temp->row << "," << temp->col << ")" << endl;
    if (front == NULL && rear == NULL) {
        front = rear = temp;
        return;
    }
    rear->right = temp;
    rear = temp;
}

