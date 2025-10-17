#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main(){
  cout << "=== DOUBLY LINKED LIST TEST SUITE START ===" << endl;

  DoublyLinkedList* myList = new DoublyLinkedList();

  cout << "\nInitial empty list:" << endl;
  myList->printForward();
  cout << "Size: " << myList->getSize() << endl;

  cout << "\nInserting 10, 20, 30 to head:" << endl;
  myList->insertToHead(10);
  myList->insertToHead(20);
  myList->insertToHead(30);
  myList->printForward();
  cout << "Expected: 30 20 10" << endl;

  cout << "\nInserting 40 and 50 to tail:" << endl;
  myList->insertToTail(40);
  myList->insertToTail(50);
  myList->printForward();
  cout << "Expected: 30 20 10 40 50" << endl;

  cout << "\nPrinting backward (tail to head):" << endl;
  myList->printBackward();
  cout << "Expected: 50 40 10 20 30" << endl;

  cout << "\nList size: " << myList->getSize() << endl;

  cout << "\nRemoving from head:" << endl;
  int headVal = myList->removeFromHead();
  cout << "Removed: " << headVal << endl;
  myList->printForward();

  cout << "\nRemoving from tail:" << endl;
  int tailVal = myList->removeFromTail();
  cout << "Removed: " << tailVal << endl;
  myList->printForward();

  cout << "\nTesting swap function:" << endl;
  Node* first = myList->head;              // likely 20
  Node* third = first->next->next;         // likely 40
  cout << "Before swap: ";
  myList->printForward();
  myList->swap(first, third);
  cout << "After swap: ";
  myList->printForward();

  cout << "\nPrinting backward after swap:" << endl;
  myList->printBackward();

  cout << "\nRemoving all elements:" << endl;
  while (myList->getSize() > 0){
    cout << "Removed: " << myList->removeFromHead() << endl;
    myList->printForward();
  }

  cout << "\nAttempting remove on empty list (expect exception):" << endl;
  try {
    myList->removeFromTail();
  } catch (exception& e){
    cout << "Caught exception: " << e.what() << endl;
  }

  delete myList;
  cout << "\n=== DOUBLY LINKED LIST TEST SUITE COMPLETE ===" << endl;
  return 0;
}
