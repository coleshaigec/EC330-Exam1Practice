#include "DoublyLinkedList.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>  // For potential use of std::swap if needed, though not required here

using namespace std;

//////////////////////////////////////////////////////////
//   Merge Sort for Doubly Linked Lists (Standalone)     //
//////////////////////////////////////////////////////////
//
// This file implements merge sort using the DoublyLinkedList
// structure previously defined. It does NOT live inside the
// DoublyLinkedList class itself, but rather operates *on top*
// of it. The algorithm is entirely pointer-based and does not
// convert the list into an array at any point.
//
// Merge sort is the ideal sorting algorithm for linked lists
// because it does not require random access (unlike quicksort
// or heapsort) and can be implemented entirely through pointer
// manipulation. The list is divided into halves using the
// "fast/slow pointer" technique, sorted recursively, and then
// merged in ascending order.
//

//////////////////////////////////////////////////////////
//              FAST/SLOW POINTER SPLIT                 //
//////////////////////////////////////////////////////////
//
// Purpose: Split a linked list into two halves.
// Arguments:
//    head: pointer to the head node of the list to split.
//
// How it works:
//    - The "slow" pointer advances one node at a time.
//    - The "fast" pointer advances two nodes at a time.
//    - When "fast" reaches the end of the list, "slow" is at
//      the midpoint.
//    - The list is then split into two halves by cutting the
//      connection between them.
// Returns:
//    - Pointer to the head of the second (right) half.
//
Node* split(Node* head) {
  if (head == nullptr || head->next == nullptr)
    return nullptr;  // Edge case: empty or single-element list

  Node* slow = head;
  Node* fast = head;

  // Advance fast by 2, slow by 1, until fast reaches end
  while (fast->next != nullptr && fast->next->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // 'slow' now points to the midpoint of the list
  Node* second = slow->next;  // Head of second half
  slow->next = nullptr;       // Break the list into two halves
  if (second != nullptr)
    second->prev = nullptr;   // Prevent backward linkage across halves

  return second;
}


//////////////////////////////////////////////////////////
//              MERGE TWO SORTED LISTS                  //
//////////////////////////////////////////////////////////
//
// Purpose: Merge two sorted sublists into one sorted list.
//
// Arguments:
//    first:  pointer to the head of the first sorted sublist.
//    second: pointer to the head of the second sorted sublist.
//
// How it works:
//    - Compares data at the current nodes of both lists.
//    - The smaller value becomes the new head of the merged list.
//    - The function then recursively merges the remaining nodes.
//    - 'prev' and 'next' pointers are updated to preserve
//      doubly-linked list integrity.
//
// Returns:
//    - Pointer to the head of the merged sorted list.
//
Node* merge(Node* first, Node* second) {
  // Base cases
  if (first == nullptr) return second;
  if (second == nullptr) return first;

  // Compare head data of both lists and pick the smaller one
  if (first->data <= second->data) {
    // first node remains at head; merge its tail recursively
    first->next = merge(first->next, second);
    if (first->next != nullptr)
      first->next->prev = first;
    first->prev = nullptr;
    return first;
  } else {
    // second node becomes new head; merge recursively
    second->next = merge(first, second->next);
    if (second->next != nullptr)
      second->next->prev = second;
    second->prev = nullptr;
    return second;
  }
}


//////////////////////////////////////////////////////////
//                 RECURSIVE MERGE SORT                 //
//////////////////////////////////////////////////////////
//
// Purpose:
//    Perform merge sort on a doubly linked list.
//
// Arguments:
//    head: pointer to the head node of the list (or sublist).
//
// How it works:
//    - Base case: if the list is empty or contains only one node,
//      it is already sorted.
//    - Otherwise, split the list into two halves using the
//      fast/slow pointer approach.
//    - Recursively call mergeSort on both halves to sort them.
//    - Merge the two sorted halves back together.
//
// Returns:
//    - Pointer to the new head of the sorted list.
//
Node* mergeSort(Node* head) {
  // Base case: 0 or 1 element -> already sorted
  if (head == nullptr || head->next == nullptr)
    return head;

  // Step 1: split into two halves
  Node* second = split(head);

  // Step 2: recursively sort each half
  head = mergeSort(head);
  second = mergeSort(second);

  // Step 3: merge the two sorted halves
  return merge(head, second);
}


//////////////////////////////////////////////////////////
//                   TEST SUITE (main)                  //
//////////////////////////////////////////////////////////
//
// This test suite creates several doubly linked lists with
// different configurations (empty, single, sorted, reversed,
// random, and mixed sign) and sorts them using merge sort.
//
// The goal is to confirm correctness and demonstrate how
// merge sort operates entirely via pointer manipulation.
//
int main() {
  vector<vector<int>> testCases = {
    {},                                   // empty list
    {5},                                  // single element
    {1, 2, 3, 4, 5},                      // already sorted
    {5, 4, 3, 2, 1},                      // reverse order
    {10, -3, 7, 2, 5, 0, -1},             // mixed positive/negative
    {4, 2, 2, 8, 3, 3, 1},                // duplicates
    {9, 1, 8, 2, 7, 3, 6, 4, 5}           // random
  };

  int testNum = 1;

  for (auto& data : testCases) {
    cout << "==================== Test " << testNum++ << " ====================" << endl;

    DoublyLinkedList list;

    // Populate the list
    for (int val : data)
      list.insertToTail(val);

    cout << "Before sort (forward): ";
    list.printForward();
    cout << "Before sort (backward): ";
    list.printBackward();

    // Perform merge sort externally
    list.head = mergeSort(list.head);

    // Post-sort fix: ensure all prev pointers are consistent
    Node* curr = list.head;
    Node* prev = nullptr;
    while (curr != nullptr) {
      curr->prev = prev;
      prev = curr;
      curr = curr->next;
    }

    cout << "After sort (forward): ";
    list.printForward();
    cout << "After sort (backward): ";
    list.printBackward();
    cout << "List size: " << list.getSize() << endl;

    cout << "-------------------------------------------------------------" << endl << endl;
  }

  return 0;
}
