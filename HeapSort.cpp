#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Swaps two elements at specified indices in an array
void swap(vector<int>& A, int a, int b) {
  int temp = A[b];
  A[b] = A[a];
  A[a] = temp;
}

// Used to maintain adherence to the maxheap property
// Arguments:
// A: array storing the heap
// i: index of node to be heapified
// n: number of heap elements currently under consideration (not necessarily equal to A.size() -- it will shrink as HeapSort runs)
void heapify(vector<int>& A, int i, int n)
{
  // Check if any node has an illegal child
  // If they do, swap them and bubble up/down
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  // Left child larger than root -- swap!
  if (left < n && A[left] > A[largest]) {
    largest = left;
  }

  // Right child is larger than largest element found thus far
  if (right < n && A[right] > A[largest]){
    largest = right;
  }

  // After checking children, see if root is still largest
  // If it isn't, swap the node to be heapified with the largest one found
  if (largest != i) {
    // Swap
    swap(A[i], A[largest]);
    // Recursively heapify affected subtree
    heapify(A, largest, n);
  }
  
}

void heapSort(vector<int>& A){
  int n = A.size();

  // Stage 1: build maxheap
  for (int i = n/2 - 1; i>= 0; i--) {
    heapify(A, i, n);
  }

  // Stage 2: extract elements from heap sequentially, moving backward from sorted region
  // For each element, swap the max with the last child, extract the max into the sorted region, and heapify the result
  for (int i = n -1; i > 0; i--){
    swap(A[0], A[i]);
    heapify(A, 0, i);
  }

}
int main() {
  vector<vector<int>> testCases = {
    {3, 9, 2, 1, 4, 5},                  // simple unsorted
    {10, 15, 20, 17, 25},                // already mostly heapified
    {1, 2, 3, 4, 5, 6, 7},               // ascending
    {7, 6, 5, 4, 3, 2, 1},               // descending
    {5, 5, 5, 5, 5},                     // all equal
    {50},                                // single element
    {},                                  // empty
    {10, 3, 8, 2, 1, 4, 7, 6, 9, 5},     // complex mix
    {-5, -1, -3, -2, -4},                // negative numbers
    {0, -1, 2, -3, 4, -5, 6}             // mixed sign
  };

  for (int t = 0; t < (int)testCases.size(); t++) {
    vector<int> A = testCases[t];
    cout << "================== Test " << t + 1 << " ==================\n";
    cout << "Before: ";
    for (int x : A) cout << x << " ";
    cout << "\n";

    heapSort(A);

    cout << "After:  ";
    for (int x : A) cout << x << " ";
    cout << "\n";

    bool sorted = is_sorted(A.begin(), A.end());
    cout << "Result: " << (sorted ? "PASS ✅" : "FAIL ❌") << "\n";
    cout << "--------------------------------------------------\n\n";
  }

  return 0;
}
