#include <iostream>
#include "SinglyLinkedList.h"

using namespace std;

int main() {
    cout << "=== LINKED LIST TEST SUITE START ===" << endl;

    // Create empty list
    SinglyLinkedList* myList = new SinglyLinkedList();
    cout << "\nInitial empty list: ";
    myList->print();
    cout << "Size: " << myList->getSize() << endl;

    // Insert to head
    cout << "\nInserting 10, 20, 30 to head (in that order):" << endl;
    myList->insertToHead(10);
    myList->insertToHead(20);
    myList->insertToHead(30);
    myList->print();
    cout << "Expected order: 30 -> 20 -> 10" << endl;

    // Insert to tail
    cout << "\nInserting 40 and 50 to tail:" << endl;
    myList->insertToTail(40);
    myList->insertToTail(50);
    myList->print();
    cout << "Expected order: 30 -> 20 -> 10 -> 40 -> 50" << endl;

    // Size check
    cout << "\nList size should be 5: " << myList->getSize() << endl;

    // Find tail
    Node* tail = myList->findTail();
    if (tail != nullptr)
        cout << "Tail node value: " << tail->data << " (expected 50)" << endl;
    else
        cout << "Tail not found!" << endl;

    // Remove from head
    cout << "\nRemoving from head:" << endl;
    int removedHead = myList->removeFromHead();
    cout << "Removed value: " << removedHead << endl;
    myList->print();
    cout << "Expected order: 20 -> 10 -> 40 -> 50" << endl;

    // Remove from tail
    cout << "\nRemoving from tail:" << endl;
    int removedTail = myList->removeFromTail();
    cout << "Removed value: " << removedTail << endl;
    myList->print();
    cout << "Expected order: 20 -> 10 -> 40" << endl;

    // Swap test
    cout << "\nTesting node swap:" << endl;
    Node* first = myList->head;           // should be 20
    Node* third = first->next->next;      // should be 40
    cout << "Before swap: ";
    myList->print();
    myList->swap(first, third);
    cout << "After swap: ";
    myList->print();
    cout << "Expected order: 40 -> 10 -> 20" << endl;

    // Remove all nodes to test destructor safety
    cout << "\nRemoving all remaining nodes:" << endl;
    while (myList->getSize() > 0) {
        cout << "Removed: " << myList->removeFromHead() << endl;
        myList->print();
    }

    cout << "Size after clearing: " << myList->getSize() << endl;

    // Attempt removal from empty list
    cout << "\nAttempting remove on empty list (should handle gracefully):" << endl;
    myList->removeFromHead();
    myList->removeFromTail();

    // Final cleanup
    delete myList;
    cout << "\n=== LINKED LIST TEST SUITE COMPLETE ===" << endl;

    return 0;
}
