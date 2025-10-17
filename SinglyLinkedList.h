// Class declaration for singly linked list comprised of nodes

#ifndef SinglyLinkedList_h
#define SinglyLinkedList_h

using namespace std;

class Node{
 public:
  Node(int data);   // Constructor
  int data;         // Data field/key
  Node* next;       // Pointer to next node
  void print();     // Function to print the content of the node
};


class SinglyLinkedList{
 public:
  SinglyLinkedList();              // Constructor
  ~SinglyLinkedList();             // Destructor
  void insertToHead(int data);     // Insert data to head of linked list
  void insertToTail(int data);     // Insert data to tail of linked list
  int removeFromHead();            // Pop node from head of linked list
  int removeFromTail();            // Pop node from tail of linked list
  int getSize();                   // Returns size of list
  Node* findTail();                // Finds tail node of list
  void print();                    // Prints list contents to console in sequence from head to tail
  void swap(Node* n1, Node* n2);   // Swaps two nodes in the list
  Node* head;                      // Pointer to first element in list
};



#endif
