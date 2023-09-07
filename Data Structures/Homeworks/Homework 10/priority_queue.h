#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include "image.h"

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {

    if(values.size() > 0){
      for (int i = 0; i < int(values.size()); ++i){
        push(values[i]);
      }
    }
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(/*int i*/) { return true; } // return (2*i)+1 < size();
  bool has_right_child(/*int i*/) { return true; } // return (2*i)+2 < size();
  int get_left_child(int i) { assert (i >= 0 && has_left_child(/*i*/)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(/*i*/)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::cout << "Adding element : (" << element->getX() << ',' << element->getY() << ") : " << element->getValue() << "\t";
    std::map<DistancePixel *, int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    std::cout << "Size (post add) " << size() << '\n';
    if (size() == 1)
      return;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }

 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;

  // private helper functions
  void percolate_up(int i) {
    while(get_parent(i) > 0){
      int parent = get_parent(i);
      // if smaller than parent
      if(m_heap[i] < m_heap[parent]){
        DistancePixel *tmp = m_heap[parent];
        m_heap[parent] = m_heap[i];
        m_heap[i] = tmp;
        i = parent;
      } else{
        // otherwise we can break since in right place
        break;
      }
    }
  }
  
  void percolate_down(int i) {
    // if the element has at least one child, we must consider a swap
    while(get_left_child(i) < size()){
      int child = get_left_child(i);
      int rchild = get_right_child(i);
      // find the smaller of the two children (if both exist)
      if(rchild < size() && m_heap[rchild] < m_heap[child]){
        child = rchild;
      }
      // if the child is smaller, swap and keep looping
      if(m_heap[child] < m_heap[i]){
        DistancePixel *tmp = m_heap[child];
        m_heap[child] = m_heap[i];
        m_heap[i] = tmp;
        i = child;
      } else{
        // otherwise we can break
        break;
      }
    }
  }



};

#endif
