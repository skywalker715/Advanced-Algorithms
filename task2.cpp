#include <iostream>
using namespace std;

// Node class representing a single node in the doubly linked list
class Node {
public:
    int data; // Data value stored in the node
    Node* prev; // Pointer to the previous node
    Node* next; // Pointer to the next node

    // Constructor for the Node class
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// DoublyLinkedList class representing a doubly linked list
class DoublyLinkedList {
private:
    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list

public:
    // Constructor for the DoublyLinkedList class
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor for the DoublyLinkedList class
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Method to insert a new node at the end of the list
    void insertEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Method to display the contents of the list
    void display() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Method to swap the data values of two nodes
    void swapNodes(Node* node1, Node* node2) {
        if (node1 == node2) return;

        int temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    // Method to partition the list around a pivot value
    Node* partition(Node* low, Node* high) {
        int pivot = high->data;
        Node* i = low->prev;

        for (Node* j = low; j!= high; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr)? low : i->next;
                swapNodes(i, j);
            }
        }

        i = (i == nullptr)? low : i->next;
        swapNodes(i, high);
        return i;
    }

    // Method to perform quicksort on the list
    void quickSort(Node* low, Node* high) {
        if (high!= nullptr && low!= high && low!= high->next) {
            Node* partitionNode = partition(low, high);
            quickSort(low, partitionNode->prev);
            quickSort(partitionNode->next, high);
        }
    }

    // Method to sort the list using quicksort
    void sort() {
        if (head == nullptr || head == tail) return;
        quickSort(head, tail);
    }
};

int main() {
    DoublyLinkedList list;
    list.insertEnd(5);
    list.insertEnd(3);
    list.insertEnd(8);
    list.insertEnd(2);
    list.insertEnd(7);

    cout << "Unsorted list: ";
    list.display();
    list.sort();

    cout << "Final list after sorting: ";
    list.display();

    return 0;
}