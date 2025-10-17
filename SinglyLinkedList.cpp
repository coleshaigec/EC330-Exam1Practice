#include "SinglyLinkedList.h"
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
}

void Node::print(){
  cout << data << " ";
}

///////////////////////////////////////////////////////
//     Implementation of SINGLY LINKED LIST class    //
///////////////////////////////////////////////////////

// Constructor
SinglyLinkedList::SinglyLinkedList(){
  this->head = nullptr;
}

// Destructor
SinglyLinkedList::~SinglyLinkedList(){
  Node* curr = head;
  while (curr != nullptr){
    Node* nxt = curr->next;
    delete curr;
    curr = nxt;
  }
  head = nullptr;
}

// Get size
int SinglyLinkedList::getSize(){
  Node* curr = head;
  int size = 0;
  while (curr != nullptr){
    curr = curr->next;
    size++;
  }
  return size;
}

// Find tail
Node* SinglyLinkedList::findTail(){
  // If list is empty, return head (nullptr)
  if (this->head == nullptr){
    return head;
  }

  // If the list is nonempty, traverse it to find the final element
  else {
    Node* curr = head;
    while (curr->next != nullptr){
      curr = curr->next;
    }
    return curr;
  }
}

// Insert to head
void SinglyLinkedList::insertToHead(int data){
  Node* newNode = new Node(data);
  newNode->next = head;
  head = newNode;
}

// Insert to tail
void SinglyLinkedList::insertToTail(int data){
  Node* newNode = new Node(data);
  // If list is empty, the node to be inserted will become the head
  if (head == nullptr) {          // FIXED: comparison, not assignment
    head = newNode;
  }
  // If list is nonempty, find tail and tack new node onto it
  else {
    Node* currTail = this->findTail();
    currTail->next = newNode;
  }
}

// Remove from head
int SinglyLinkedList::removeFromHead(){
  // If the list is empty, you cannot remove from head
  // Throw an exception
  if (head == nullptr) {
    throw runtime_error("Cannot remove from empty list");
  }
  // If list is non-empty, do the following:
  // 1: Extract data from head node and delete that node
  // 2: Repoint the head of the list to the old head's successor (if it exists; if not, head will be nullptr)
  // 3: Return extracted data
  else {
    int data = head->data;
    Node* newHead = head->next;
    delete head;
    head = newHead;
    return data;
  }
}

// Remove from tail
int SinglyLinkedList::removeFromTail(){
  // If the list is empty, you cannot remove from tail
  // Throw an exception
  if (head == nullptr){
    throw runtime_error("Cannot remove from empty list.");
  }

  // If the head is the tail, remove from head
  else if (head->next == nullptr){
    return this->removeFromHead();
  }

  // If list has two or more elements, do the following:
  // 1: Find the tail and its predecessor
  // 2: Extract data from the tail and delete it
  // 3: Remove the dangling pointer from the old tail's predecessor
  else {
    Node* curr = head;
    while (curr->next->next != nullptr){   // FIXED traversal logic
      curr = curr->next;
    }
    int data = curr->next->data;
    delete curr->next;
    curr->next = nullptr;
    return data;
  }
}

// Print
void SinglyLinkedList::print(){
  Node* curr = head;
  while (curr != nullptr){
    cout << curr->data << " ";
    curr = curr->next;
  }
  cout << endl;   // Added newline for clean output
}

// Swap
void SinglyLinkedList::swap(Node* n1, Node* n2){
  // Simple implementation: swap node data fields
  // This preserves structure but interchanges stored values
  if (n1 == nullptr || n2 == nullptr){
    cout << "Swap failed: one or both nodes are null." << endl;
    return;
  }
  int temp = n1->data;
  n1->data = n2->data;
  n2->data = temp;
}
