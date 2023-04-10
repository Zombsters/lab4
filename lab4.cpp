// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "ArgumentManager.h"
#include "Queue.h"
#include "LinkedList.h"
using namespace std;


Queue CreateQ(int rows, int cols, Node* traverse, Node* prev);
void Traverse(int rows, int cols,int row, int col, Node* curr, Node* prev);
Node* GoTo(int row, int col,Node* curr);

bool IsVisited(int row, int col, Node* curr);
bool AreAllVisited(int count,int rows,int cols,Node* curr);
void SetToStart(Node*& curr);

bool AllTraversed = false;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    int rows = 5; int cols = 5;
    LinkedList list(rows, cols);
    list.Print(); cout << endl;
 

    Node* traverse = list.start;
    Node* prev = NULL;
    Traverse(rows, cols, 0, 0, traverse, prev);

    cout << endl;list.Print(); cout << endl;
    cout << "Possible: " << AllTraversed << endl;
    return 0;
}

Queue CreateQ(int rows, int cols, Node* traverse, Node* prev) {
    cout << " start: "; traverse->Print(); 
    cout << " prev: "; prev->Print(); cout << endl;
    //down 1 right 2 // down 2 right 1
    Queue result;
    for (int i = 1, j = 2; (i <= 2 && j >= 1); i++, j--) {
        if ((traverse->row + i < rows) && (traverse->col + j < cols)) {
            if (IsVisited(traverse->row + i, traverse->col + j, traverse)) {
                continue;
            }
            Node* temp = new Node(traverse->row + i, traverse->col + j);
            result.Enqueue(temp);
        }
    }
    //up 1 left 2 // up 2 left 1
    for (int i = -1, j = -2; (i >= -2 && j <= -1); i--, j++) {
        if ((traverse->row + i >= 0) && (traverse->col + j >= 0)) {
            if (IsVisited(traverse->row + i, traverse->col + j, traverse)) {
                continue;
            }
            Node* temp = new Node(traverse->row + i, traverse->col + j);
            result.Enqueue(temp);
        }
    }
    //down 1 left 2 // down 2 left 1
    for (int i = 1, j = -2; (i <= 2 && j <= -1); i++, j++) {
        if ((traverse->row + i < rows) && (traverse->col + j >= 0)) {
            if (IsVisited(traverse->row + i, traverse->col + j, traverse)) {
                continue;
            }
            Node* temp = new Node(traverse->row + i, traverse->col + j);
            result.Enqueue(temp);
        }
    }
    //up 1 right 2 // up 2 right 1
    for (int i = -1, j = 2; (i >= -2 && j >= 1); i--, j--) {
        if ((traverse->row + i >= 0) && (traverse->col + j < cols)) {
            if (IsVisited(traverse->row + i, traverse->col + j, traverse)) {
                continue;
            }
            Node* temp = new Node(traverse->row + i, traverse->col + j);
            result.Enqueue(temp);
        }
    }
    cout << "In my Q: " << endl; result.Print();
    return result;
}

void Traverse(int rows, int cols, int row, int col, Node* curr, Node* prev) {
    prev = curr;
    curr = GoTo(row, col,curr);
    if (!(prev == curr)) {
        if (curr->row != 0 || curr->col != 0) {
            curr->visited = true;
        }
        else{
            cout << "REACHED (0,0)" << endl;
            curr->visited = true;
            int count = 0;
            if (AreAllVisited(count, rows, cols, curr)) {
                cout << "ALL TRUE " << endl;
                AllTraversed = true;
            }
            else {
                curr->visited = false;
            }
        }
    }
    Queue myQ = CreateQ(rows, cols, curr, prev);
    while (!(myQ.IsEmpty())) {
        int i = myQ.Front()->row; int j = myQ.Front()->col;
        myQ.Dequeue();
        if (!(IsVisited(i, j, curr))) {
            Traverse(rows, cols, i, j, curr, prev);
        }
    }
}

bool IsVisited(int row, int col, Node* curr) {
    while (curr->row < row) {
        curr = curr->down;
    }
    while (curr->col < col) {
        curr = curr->right;
    }
    while (curr->row > row) {
        curr = curr->up;
    }
    while (curr->col > col) {
        curr = curr->left;
    }
    return curr->visited;
}

void SetToStart(Node*& curr) {
    while (curr->row > 0) {
        curr = curr->up;
    }
    while (curr->col > 0) {
        curr = curr->left;
    }
}

bool AreAllVisited(int count,int rows, int cols, Node* curr) {
    //at start...
    Node* temp = curr;
    while (temp != NULL) {
        if (temp->visited == false) {
            return false;
        }
        temp = temp->right;
    }
    count++;
    if (count < rows) {
        SetToStart(curr);
        for (int i = 0; i < count; i++) {
            curr = curr->down;
        }
        AreAllVisited(count, rows, cols, curr);
    }
    return true;
}

Node* GoTo(int row, int col, Node* curr) {
    while (curr->row < row) {
        curr = curr->down;
    }
    while (curr->col < col) {
        curr = curr->right;
    }
    while (curr->row > row) {
        curr = curr->up;
    }
    while (curr->col > col) {
        curr = curr->left;
    }
    return curr;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
