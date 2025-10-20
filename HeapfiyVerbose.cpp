#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Used to maintain adherence to the maxheap property
// Arguments:
// A: array storing the heap
// i: index of node to be heapified
// n: number of heap elements currently under consideration (not necessarily equal to A.size() -- it will shrink as HeapSort runs)
// verbose: if true, prints detailed step-by-step mechanics of heapify
void heapify_impl(vector<int>& A, int i, int n, bool verbose, int depth) {
  auto indent = string(2 * depth, ' ');

  if (verbose) {
    cout << indent << "[enter] heapify(i=" << i << ", n=" << n << ")\n";
    cout << indent << "current array: ";
    for (int x : A) cout << x << " ";
    cout << "\n";
  }

  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (verbose) {
    cout << indent << "children: left=" << left << (left < n ? "" : " (OOB)")
         << ", right=" << right << (right < n ? "" : " (OOB)") << "\n";
  }

  // Left child larger than root -- swap!
  if (left < n) {
    if (verbose) {
      cout << indent << "compare left: A[left]=" << A[left]
           << " vs A[largest=" << largest << "]=" << A[largest] << " -> ";
    }
    if (A[left] > A[largest]) {
      largest = left;
      if (verbose) cout << "left is larger; largest := left (" << largest << ")\n";
    } else if (verbose) {
      cout << "no change\n";
    }
  }

  // Right child is larger than largest element found thus far
  if (right < n) {
    if (verbose) {
      cout << indent << "compare right: A[right]=" << A[right]
           << " vs A[largest=" << largest << "]=" << A[largest] << " -> ";
    }
    if (A[right] > A[largest]) {
      largest = right;
      if (verbose) cout << "right is larger; largest := right (" << largest << ")\n";
    } else if (verbose) {
      cout << "no change\n";
    }
  }

  // After checking children, see if root is still largest
  if (largest != i) {
    if (verbose) {
      cout << indent << "swap needed: i=" << i << " (A[i]=" << A[i]
           << ") with largest=" << largest << " (A[largest]=" << A[largest] << ")\n";
    }
    std::swap(A[i], A[largest]); // explicit std::swap to avoid any overload confusion

    if (verbose) {
      cout << indent << "after swap: ";
      for (int x : A) cout << x << " ";
      cout << "\n";
      cout << indent << "recurse on affected subtree at index " << largest << "\n";
    }

    heapify_impl(A, largest, n, verbose, depth + 1);
  } else {
    if (verbose) {
      cout << indent << "node i=" << i
           << " already satisfies max-heap relative to children; stop\n";
    }
  }

  if (verbose) {
    cout << indent << "[return] heapify(i=" << i << ", n=" << n << ")\n";
  }
}

void heapify(vector<int>& A, int i, int n, bool verbose) {
  heapify_impl(A, i, n, verbose, 0);
}


// Utility to print vectors
void printVec(const vector<int>& A, const string& label) {
  cout << label;
  for (int x : A) cout << x << " ";
  cout << "\n";
}

// Verifies max-heap property on first n elements
bool isMaxHeap(const vector<int>& A, int n) {
  for (int i = 0; i < n / 2; i++) {
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && A[i] < A[l]) return false;
    if (r < n && A[i] < A[r]) return false;
  }
  return true;
}

int main() {
  vector<vector<int>> testCases = {
    {3, 9, 2, 1, 4, 5},                 // simple unsorted
    {10, 15, 20, 17, 25},               // not a heap yet
    {1, 2, 3, 4, 5, 6, 7},              // ascending
    {7, 6, 5, 4, 3, 2, 1},              // descending
    {50},                               // single element
    {},                                 // empty
    {10, 3, 8, 2, 1, 4, 7, 6, 9, 5}     // mixed
  };

  for (int t = 0; t < (int)testCases.size(); t++) {
    vector<int> A = testCases[t];
    int n = (int)A.size();

    cout << "================= Test " << t + 1 << " =================\n";
    printVec(A, "before build-heap: ");

    // Build a max-heap bottom-up; pass verbose=true to illustrate each call
    for (int i = n / 2 - 1; i >= 0; i--) {
      cout << "---- heapify call on i=" << i << " (n=" << n << ") ----\n";
      heapify(A, i, n, /*verbose=*/true);
    }

    printVec(A, "after  build-heap: ");
    cout << "heap property: " << (isMaxHeap(A, n) ? "VALID" : "INVALID") << "\n";
    cout << "============================================\n\n";
  }

  // Optional: single-node-focused demo to show local repair
  {
    cout << "===== Local heapify demonstration =====\n";
    vector<int> B = {1, 14, 7, 8, 9, 3, 2};
    // Assume everything below root is already heapified, we repair at i=0
    printVec(B, "before local heapify at i=0: ");
    heapify(B, /*i=*/0, /*n=*/(int)B.size(), /*verbose=*/true);
    printVec(B, "after  local heapify at i=0: ");
    cout << "heap property: " << (isMaxHeap(B, (int)B.size()) ? "VALID" : "INVALID") << "\n";
    cout << "=======================================\n";
  }

  return 0;
}
