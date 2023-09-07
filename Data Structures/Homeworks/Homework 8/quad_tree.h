// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>


// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

template <class number_type, class label_type>
class QuadTree{

public:
  // -------------------------------------------------------------------
  // QUADTREE NODE CLASS
  class Node{
  public:
    Node() : pt(NULL, NULL), label(NULL), children(NULL), parent(NULL) {}
    Node(const Point<number_type>& point, const label_type& lbl) :
      pt(point), label(lbl), parent(NULL) {
      children[0] = NULL;
      children[1] = NULL;
      children[2] = NULL;
      children[3] = NULL;
    }

    Point<number_type> pt;
    label_type label;
    Node *children[4];
    Node *parent;
  };

  // -------------------------------------------------------------------
  // DEPTHITERATOR CLASS
  class DepthIterator{
  public:
    DepthIterator() : ptr(NULL) {}
    DepthIterator(Node* p) : ptr(p) {}
    DepthIterator(const DepthIterator& old) : ptr(old.ptr) {}
    ~DepthIterator() {}
    DepthIterator &operator=(const DepthIterator &old) 
      { ptr = old.ptr; return *this;}
    const Point<number_type> &operator*() const { return ptr->pt; }

    friend bool operator==(const DepthIterator &l, const DepthIterator& r)
      {return (l.ptr == r.ptr);}
    friend bool operator!=(const DepthIterator& l, const DepthIterator& r)
      {return (l.ptr != r.ptr);}

    // ACCESSORS
    label_type getLabel() const { return ptr->label; }
    int getDepth(){
      int depth = 0;
      Node *tmp = ptr;
      while(tmp->parent != NULL){
        depth++;
        tmp = tmp->parent;
      }
      return depth;
    }

    // Increment and Decrement
    DepthIterator &operator++(){
      // Try Children
      for (int i = 0; i < 4; i++){
        if (ptr->children[i] != NULL){
          ptr = ptr->children[i];
          return *this;
        }
      }
      // Try Nodes at level same as ptr, move up level if fail
      Node *prnt = ptr->parent;
      Node *tmp = ptr;
      while (prnt != NULL){
        bool after = false;
        for (int i = 0; i < 4; i++){
          if (!after && prnt->children[i] != NULL){
            if (prnt->children[i]->pt.x == tmp->pt.x &&
                prnt->children[i]->pt.y == tmp->pt.y){
              after = true;
              continue;
            }
          }
          if (after){
            if (prnt->children[i] != NULL){
              ptr = prnt->children[i];
              return *this;
            }
          }
        }
        // Move Up a level ( None )
        tmp = prnt;
        prnt = prnt->parent;
      }
      // Could not move forward ( at end)
      ptr = NULL;
      return *this;
  }
    DepthIterator operator++(int){
      DepthIterator temp(*this);
      ++(*this);
      return temp;
    }

  private : 
    Node *ptr;
  };

  // -------------------------------------------------------------------
  // BREADTHITERATOR CLASS
  class BreadthIterator{
  public:
    BreadthIterator() : ptr(NULL) {}
    BreadthIterator(Node *p) : ptr(p) {
      // Add p's row to current
      if(p != NULL && p->parent != NULL){
        for (int i = 0; i < 4; i++){
          if(p->parent->children[i] != NULL){
            current.push_back(p->parent->children[i]);
          }
        }
      }
      else if (p != NULL){
        current.push_back(p);
      }
      // Add currents children to next
      for (unsigned int i = 0; i < current.size(); i++){
        for (int c = 0; c < 4; c++){
          if(current[i]->children[c] != NULL){
            next.push_back(current[i]->children[c]);
          }
        }
      }
    }
    BreadthIterator(const BreadthIterator &old)
      : ptr(old.ptr), current(old.current), next(old.next) {}
    ~BreadthIterator() {}
    BreadthIterator &operator=(const BreadthIterator &old)
      { ptr = old.ptr; current = old.current, next = old.next; return *this;}
    const Point<number_type> &operator*() const { return ptr->pt; }

    friend bool operator==(const BreadthIterator &l, const BreadthIterator &r)
      {return (l.ptr == r.ptr);}
    friend bool operator!=(const BreadthIterator &l, const BreadthIterator &r)
      {return (l.ptr != r.ptr);}

    int getDepth(){
      int depth = 0;
      Node *tmp = ptr;
      while(tmp->parent != NULL){
        depth++;
        tmp = tmp->parent;
      }
      return depth;
    }
    label_type getLabel() const { return ptr->label;}

    // Increment
    BreadthIterator &operator++()
      {
        // Try to move sideways on current
        bool after = false;
        for (unsigned int i = 0; i < current.size(); i++){
          if (!after &&
              current[i]->pt.x == ptr->pt.x &&
              current[i]->pt.y == ptr->pt.y) {
            after = true;
            continue;
          }
          if (after){
            ptr = current[i];
            return *this;
          }
        }
        // Current Level has no possible sideways move
        // Updating Current and Next
        current = next;
        next.clear();
        // Loop over current
        for (unsigned int i = 0; i < current.size(); i++){
          // Loop over current[i]'s children, add nonNULL to next
          for (int c = 0; c < 4; c++){
            if (current[i]->children[c] != NULL){
              next.push_back(current[i]->children[c]);
            }
          }
        }
        // Moving onto next layer, so place ptr at first of the layer
        if(current.size() > 0){
          ptr = current[0];
          return *this;
        }
        // Current row is empty
        ptr = NULL;
        return *this;
    }
    BreadthIterator operator++(int){
      BreadthIterator temp(*this);
      ++(*this);
      return temp;
    }

  private:
    Node *ptr;
    std::vector<Node *> current;
    std::vector<Node*> next;
  };

  // QUADTREE
  // -------------------------------------------------------------------

  typedef DepthIterator iterator;
  typedef BreadthIterator bf_iterator;

  // CONSTRUCTORS< ASSIGNMENT OPERATOR, DESTRUCTOR
  QuadTree() : root_(NULL), size_(0), height_(-1) {}
  QuadTree(const QuadTree<number_type, label_type>& old) 
    : size_(old.size_), height_(old.height_) 
    { root_ = this->copy_tree(old.root_, NULL); }
  ~QuadTree() {
    this->destroy_tree(root_);
    root_ = NULL;
  }
  QuadTree& operator=(const QuadTree<number_type, label_type>& old){
    if(&old != this){
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_, NULL);
      size_ = old.size_;
      height_ = old.height_;
    }
    return *this;
  }

  unsigned int size() const { return size_; }
  int height() const { return height_; }
  bool operator==(const QuadTree<number_type, label_type> &old) const 
    { return (old.root_ == this->root_); }

  // FIND, INSERT
  std::pair<iterator, bool> insert(const Point<number_type>& point,const label_type& lbl) { 
    std::pair<iterator, bool> tmp = insert(point, lbl, root_, NULL);
    height_ = updateHeight(root_);
    return tmp;
  }
  iterator find(const number_type& x, const number_type& y)
  { return find(x, y, root_); }

  // PLOT
  void plot(int max_x, int max_y, bool draw_lines = true) const;
  void print_sideways() const;

  // ITERATORS
  iterator begin() const{
    if(!root_) return iterator(NULL);
    // pre-order traversal so root
    return iterator(root_);
  }
  iterator end() const { return iterator(NULL); }
  bf_iterator bf_begin() const{
    if(!root_)
      return bf_iterator(NULL);
    return bf_iterator(root_);
  }
  bf_iterator bf_end() const { return bf_iterator(NULL); }

private :
  // -------------------------------------------------------------------
  // QUADTREE PRIVATE REPRESENTATION
  Node *root_;
  unsigned int size_;
  int height_;

  // -------------------------------------------------------------------
  // QUADTREE PRIVATE MEMBER FUNCTIONS
  void plot(Node *p, std::vector<std::string> &board,
           int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
    // base case, draw nothing if this node is NULL
    if (p == NULL)
      return;
    // check that the dimensions range of this node make sense
    assert(x_min >= 0 && x_min <= x_max);
    assert(y_min >= 0 && y_min <= y_max);
    assert(int(board.size()) >= y_max);
    assert(int(board[0].size()) >= x_max);
    // verify that the point stored at this node fits on the board
    assert(p->pt.y >= 0 && p->pt.y < int(board.size()));
    assert(p->pt.x >= 0 && p->pt.x < int(board[0].size()));
    // draw the vertical and horizontal bars extending across the
    // range of this node
    if (draw_lines)
    {
      for (int x = x_min; x <= x_max; x++)
      {
        board[p->pt.y][x] = '-';
      }
      for (int y = y_min; y <= y_max; y++)
      {
        board[y][p->pt.x] = '|';
      }
    }
    // draw this label
    board[p->pt.y][p->pt.x] = p->label;
    // recurse on the 4 children
    plot(p->children[0], board, x_min, p->pt.x - 1, y_min, p->pt.y - 1, draw_lines);
    plot(p->children[1], board, p->pt.x + 1, x_max, y_min, p->pt.y - 1, draw_lines);
    plot(p->children[2], board, x_min, p->pt.x - 1, p->pt.y + 1, y_max, draw_lines);
    plot(p->children[3], board, p->pt.x + 1, x_max, p->pt.y + 1, y_max, draw_lines);
  }

  void print_sideways(Node *p, const std::string &indent) const{
    // base case
    if (p == NULL)
      return;
    // print out this node
    std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
    // recurse on each of the children trees
    // increasing the indentation
    print_sideways(p->children[0], indent + "  ");
    print_sideways(p->children[1], indent + "  ");
    print_sideways(p->children[2], indent + "  ");
    print_sideways(p->children[3], indent + "  ");
  }

  std::pair<iterator, bool> insert(const Point<number_type>& point, const label_type& lbl, Node*& p, Node* the_parent){
    if(!p){
      p = new Node(point, lbl);
      p->parent = the_parent;
      this->size_++;
      return std::pair<iterator, bool>(iterator(p), true);
    }
    else if(point.x < p->pt.x && point.y < p->pt.y){
      return insert(point, lbl, p->children[0], p);
    }
    else if(point.x > p->pt.x && point.y < p->pt.y){
      return insert(point, lbl, p->children[1], p);
    }
    else if(point.x < p->pt.x && point.y > p->pt.y){
      return insert(point, lbl, p->children[2], p);
    }
    else if(point.x > p->pt.x && point.y > p->pt.y){
      return insert(point, lbl, p->children[3], p);
    }
    else{
      return std::pair<iterator, bool>(iterator(p), false);
    }
  }

  iterator find(const number_type& x, const number_type& y, Node* p){
    if(!p) return end();
    else if(x < p->pt.x && y < p->pt.y){ // first quadrant
      return find(x, y, p->children[0]);
    }
    else if(x > p->pt.x && y < p->pt.y){ // second quadrant
      return find(x, y, p->children[1]);
    }
    else if(x < p->pt.x && y > p->pt.y){ // third quadrant
      return find(x, y, p->children[2]);
    }
    else if(x > p->pt.x && y > p->pt.y){ // fourth quadrant
      return find(x, y, p->children[3]);
    }
    else if(x == p->pt.x && y == p->pt.y) // exact point
      return iterator(p);
    else // on one of the lines created by p
      return iterator(NULL); 
  }

  int updateHeight(Node* p){
    if(!p) return -1;
    else{
      int h1 = updateHeight(p->children[0]);
      int h2 = updateHeight(p->children[1]);
      int h3 = updateHeight(p->children[2]);
      int h4 = updateHeight(p->children[3]);

      int max = std::max(std::max(h1, h2), std::max(h3, h4));
      return max + 1;
    }
  }

  void destroy_tree(Node* p){
    if (!p) return;
    destroy_tree(p->children[0]);
    destroy_tree(p->children[1]);
    destroy_tree(p->children[2]);
    destroy_tree(p->children[3]);
    delete p;
  }

  Node* copy_tree(Node* old_root, Node* prnt){
    if(old_root == NULL) return NULL;
    Node *answer = new Node(old_root->pt, old_root->label);
    answer->children[0] = copy_tree(old_root->children[0], answer);
    answer->children[1] = copy_tree(old_root->children[1], answer);
    answer->children[2] = copy_tree(old_root->children[2], answer);
    answer->children[3] = copy_tree(old_root->children[3], answer);
    answer->parent = prnt;
    return answer;
  }
};

// ==============================================================
// PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
// ==============================================================

// Adjust the function prototypes below as necessary to add them as 
// member functions of your QuadTree class.

// NOTE: the plot function only works for quad trees with non negative
// integer coordinates and char labels

// NOTE2: the plot function assumes that no two points have the same x
// coordinate or the same y coordinate.

// plot driver function
// takes in the maximum x and y coordinates for these data points
// the optional argument draw_lines defaults to true
template <class number_type, class label_type>
void QuadTree<number_type, label_type>::plot(int max_x, int max_y, bool draw_lines) const {
  // allocate blank space for the center of the board
  std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
  // edit the board to add the point labels and draw vertical and
  // horizontal subdivisions
  plot(root_,board,0,max_x,0,max_y,draw_lines);
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  for (int i = 0; i <= max_y; i++) {
    // print each row of the board between vertical border bars
    std::cout << "|" << board[i] << "|" << std::endl;
  }
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
}

// ==============================================================

// prints all of the tree data with a pre-order (node first, then
// children) traversal of the tree structure

// driver function

template<class number_type, class label_type> 
void QuadTree<number_type, label_type>::print_sideways() const { print_sideways(root_,""); }

// ==============================================================
// ==============================================================

#endif
