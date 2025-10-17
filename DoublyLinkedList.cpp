#include "DoublyLinkedList.h"
#include <iostream>
#include <stdexcept>

using namespace std;

/////////////////////////////////////////
//     Implementation of NODE class    //
/////////////////////////////////////////

// Constructor
Node::Node(int data){
  this->data = data;
  this->next = nullptr;
  this->prev = nullptr;
}

void Node::print(){
  cout << data << " ";
}


//////////////////////////////////////////////////////////
//     Implementation of DOUBLY LINKED LIST class       //
//////////////////////////////////////////////////////////

// Constructor
DoublyLinkedList::DoublyLinkedList(){
  this->head = nullptr;
}

// Destructor
DoublyLinkedList::~DoublyLinkedList(){
  Node* curr = head;
  while (curr != nullptr){
    Node* nxt = curr->next;
    delete curr;
    curr = nxt;
  }
  head = nullptr;
}

// Get size
int DoublyLinkedList::getSize(){
  Node* curr = head;
  int size = 0;
  while (curr != nullptr){
    curr = curr->next;
    size++;
  }
  return size;
}

// Find tail
Node* DoublyLinkedList::findTail(){
  if (this->head == nullptr){
    return head;
  }
  Node* curr = head;
  while (curr->next != nullptr){
    curr = curr->next;
  }
  return curr;
}

// Insert to head
void DoublyLinkedList::insertToHead(int data){
  Node* newNode = new Node(data);
  if (head == nullptr){
    head = newNode;
  }
  else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
}

// Insert to tail
void DoublyLinkedList::insertToTail(int data){
  Node* newNode = new Node(data);
  if (head == nullptr){
    head = newNode;
  }
  else {
    Node* tail = this->findTail();
    tail->next = newNode;
    newNode->prev = tail;
  }
}

// Remove from head
int DoublyLinkedList::removeFromHead(){
  if (head == nullptr){
    throw runtime_error("Cannot remove from empty list.");
  }
  int data = head->data;
  Node* newHead = head->next;
  delete head;
  if (newHead != nullptr){
    newHead->prev = nullptr;
  }
  head = newHead;
  return data;
}

// Remove from tail
int DoublyLinkedList::removeFromTail(){
  if (head == nullptr){
    throw runtime_error("Cannot remove from empty list.");
  }
  if (head->next == nullptr){
    return this->removeFromHead();
  }

  Node* tail = this->findTail();
  int data = tail->data;
  Node* prevNode = tail->prev;
  prevNode->next = nullptr;
  delete tail;
  return data;
}

// Print forward
void DoublyLinkedList::printForward(){
  Node* curr = head;
  while (curr != nullptr){
    cout << curr->data << " ";
    curr = curr->next;
  }
  cout << endl;
}

// Print backward
void DoublyLinkedList::printBackward(){
  Node* tail = this->findTail();
  while (tail != nullptr){
    cout << tail->data << " ";
    tail = tail->prev;
  }
  cout << endl;
}

// Swap (pointer-based)
void DoublyLinkedList::swap(Node* n1, Node* n2){
  if (n1 == nullptr || n2 == nullptr || n1 == n2){
    cout << "Swap skipped: invalid or identical nodes." << endl;
    return;
  }

  // Ensure n1 comes before n2 for consistency
  Node* curr = head;
  bool n1First = false;
  while (curr != nullptr){
    if (curr == n1){ n1First = true; break; }
    if (curr == n2){ n1First = false; break; }
    curr = curr->next;
  }
  if (!n1First) swap(n1, n2);  // Ensure order (no pun intended)

  Node* prev1 = n1->prev;
  Node* next1 = n1->next;
  Node* prev2 = n2->prev;
  Node* next2 = n2->next;

  // Handle adjacency as a special case
  if (n1->next == n2){
    if (prev1) prev1->next = n2;
    if (next2) next2->prev = n1;
    n2->prev = prev1;
    n1->next = next2;
    n2->next = n1;
    n1->prev = n2;
  }
  else {
    // Swap links for non-adjacent nodes
    if (prev1) prev1->next = n2;
    if (next1) next1->prev = n2;
    if (prev2) prev2->next = n1;
    if (next2) next2->prev = n1;

    Node* tempPrev = n1->prev;
    Node* tempNext = n1->next;
    n1->prev = n2->prev;
    n1->next = n2->next;
    n2->prev = tempPrev;
    n2->next = tempNext;
  }

  // Adjust head pointer if needed
  if (n1 == head) head = n2;
  else if (n2 == head) head = n1;
}
