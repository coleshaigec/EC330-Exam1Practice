// Class declaration for doubly linked list comprised of nodes

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

using namespace std;

/////////////////////////////////////////
//     Declaration of NODE class       //
/////////////////////////////////////////

class Node{
 public:
  Node(int data);   // Constructor
  int data;         // Data field/key
  Node* next;       // Pointer to next node
  Node* prev;       // Pointer to previous node
  void print();     // Function to print the content of the node
};


///////////////////////////////////////////////////////
//     Declaration of DOUBLY LINKED LIST class       //
///////////////////////////////////////////////////////

class DoublyLinkedList{
 public:
  DoublyLinkedList();               // Constructor
  ~DoublyLinkedList();              // Destructor
  void insertToHead(int data);      // Insert data to head of linked list
  void insertToTail(int data);      // Insert data to tail of linked list
  int removeFromHead();             // Pop node from head of linked list
  int removeFromTail();             // Pop node from tail of linked list
  int getSize();                    // Returns size of list
  Node* findTail();                 // Finds tail node of list
  void printForward();              // Prints list contents head -> tail
  void printBackward();             // Prints list contents tail -> head
  void swap(Node* n1, Node* n2);    // Swaps two nodes in the list (pointer-based)
  Node* head;                       // Pointer to first element in list
};

#endif
