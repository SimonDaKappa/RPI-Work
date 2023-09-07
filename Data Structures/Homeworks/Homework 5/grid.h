#ifndef _grid_h_
#define _grid_h_

#include <iostream>
#include <iomanip>

enum Direction {RIGHT, DOWN , LEFT, UP, NUM_DIR};

Direction operator++(Direction &dir, int){
	//++ operator for enum type, gotten from Stackoverflow
	dir = static_cast<Direction>((dir + 1) % NUM_DIR);
	return dir;
}

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node
{
public:
	Node() : left(NULL), right(NULL), up(NULL), down(NULL) {}
	Node(const T &v) : left(NULL), right(NULL), up(NULL), down(NULL), value(v) {}

	//REPRESENTATION

	//4 Pointers (UP,DOWN,LEFT, RIGHT)
	Node<T>* left;
	Node<T>* right;
	Node<T>* up;
	Node<T>* down;

	//Value
	T value;
};

template <class T>
class Grid;
// -----------------------------------------------------------------
// GRID ITERATOR
template <class T>
class GridIterator
{
public:
	GridIterator(Node<T> *p = NULL, Grid<T>* grid = NULL) 
	: ptr(p), grid_ptr(grid) 
	{ snake = spiral = snake_right = false;};

	//dereference operator
	T &operator*() { return ptr->value; };

	//MOVEMENT FUNCTIONS
	GridIterator<T> &left(){ 
		//move left
		ptr = ptr->left;
		return *this;
	}
	GridIterator<T> &right(){
		 //move right
		ptr = ptr->right;
		return *this;
	}
	GridIterator<T> &up(){ 
		//move up
		ptr = ptr->up;
		return *this;
	}
	GridIterator<T> &down(){
		//move down
		ptr = ptr->down;
		return *this;
	}

	//Snake/Spiral Movement
	GridIterator<T> &operator++(int); //postfix

	bool operator!=(const GridIterator<T> &right) { return !(ptr == right.ptr); }
	bool operator==(const GridIterator<T> &right) { return  ptr == right.ptr; }

	// the dslist class needs access to the private ptr member variable
	friend class Grid<T>;

private:
	//REPRESENTATION
	Node<T> *ptr; //ptr to node in grid
	Grid<T> *grid_ptr;
	//MORE MEMBER VARIABLES HERE FOR SNAKE AND SPIRAL
	bool snake;
	bool snake_right;
	bool spiral;
	unsigned int spiral_count;
	Node<T> *u_l;
	Node<T> *u_r;
	Node<T> *l_l;
	Node<T> *l_r;
	Direction dir;
};

// -----------------------------------------------------------------
// GRID CLASS DECLERATION
template <class T>
class Grid
{
public:
	//CONSTRUCTORS

	//Default
	Grid();
	// Main
	Grid(int w, int height, T v = 0);

	//COPY
	Grid(const Grid<T> &old);

	//ASSIGNMENT
	Grid<T> &operator=(const Grid<T> &old);
	~Grid() { destroy_grid(); }
	void copyGrid(const Grid<T> &old);

	//typedef
	typedef GridIterator<T> iterator;

	//Accessors
	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
	unsigned int getSize() const { return width * height; }
	Node<T> *get_upper_left() const { return upper_left; }
	Node<T> *get_upper_right() const { return upper_right; }
	Node<T> *get_lower_left() const { return lower_left; }
	Node<T> *get_lower_right() const { return lower_right; }

	T get(int i, int j) { return getAtLoc(i, j)->value; }

	//Indexing function
	Node<T> *getAtLoc(int i, int j);

	//MODIFIERS
	void set(int i, int j, T v);
	void reset(T v);

	// modify the structure (NON CONST REF NEEDED)
	void join(Grid<T> &inserted);
	void stack(Grid<T> &inserted);
	void lift(const iterator &itr, Grid<T> &top);
	void chop(const iterator &itr, Grid<T> &side);

	// Clear Functions
	void clear() { destroy_grid(); }
	
	// Iterators
	iterator begin_upper_left() { return iterator(upper_left); }
	iterator begin_upper_right() { return iterator(upper_right); }
	iterator begin_lower_left() { return iterator(lower_left); }
	iterator begin_lower_right() { return iterator(lower_right); }
	iterator end() { return iterator(NULL); }

	iterator begin_snake();
	iterator end_snake();
	iterator begin_spiral();
	iterator end_spiral();

	// Print
	void print();

private:
	//helper functions
	void copy_grid(const Grid<T> &old);
	void destroy_grid();
	void assign_corners();
	//REPRESENTATION

	// Size
	int width;
	int height;

	// Useful pointers
	Node<T> *upper_left;
	Node<T> *upper_right;
	Node<T> *lower_left;
	Node<T> *lower_right;
	
};

// -----------------------------------------------------------------
// GridIterator CLASS IMPLEMENTATION

template <class T>
GridIterator<T> Grid<T>::begin_snake()
{
	GridIterator<T> begin(upper_left);
	begin.snake = begin.snake_right = true;
	return begin;
}

template <class T>
GridIterator<T> &GridIterator<T>::operator++(int)
{ //postfix
	if(snake){

		if(snake_right && ptr->right != NULL){ // [] -> [][]
			ptr = ptr->right;
			return *this;
		}
		else if(snake_right && ptr->right == NULL){ //[]->
			ptr = ptr->down;
			snake_right = false;
			return *this;
		}
		else if(!snake_right && ptr->left != NULL){ //[]<-[]
			ptr = ptr->left;
			return *this;
		}
		else if(!snake_right && ptr->left == NULL){ //<-[]
			ptr = ptr->down;
			snake_right = true;
			return *this;
		}
		else //end
			return *this;
	}
	else if (spiral){
		//Move status
		bool can_move = (spiral_count < grid_ptr->getSize() - 1);
		//Moving in a spiral fashion
		if(can_move){
			spiral_count++;
			//Going Right
			if(dir == RIGHT){
				if(ptr == u_r){
					//Turn corner to go down
					dir++;
					down();
					u_r = u_r->down->left;
				}
				else{
					right();
				}
			}
			//Going Down
			else if(dir == DOWN){
				if(ptr == l_r){
					//Turn corner to go left
					dir++;
					left();
					l_r = l_r->left->up;
				}
				else{
					down();
				}
			}
			//Going Left
			else if (dir == LEFT){
				if(ptr == l_l){
					//Turn corner to go up
					dir++;
					up();
					l_l = l_l->up->right;
				}
				else{
					left();
				}
			}
			else if(dir == UP){
				if(ptr == u_l->down){
					//Turn corner to go right
					dir++;
					right();
					u_l = u_l->down->right;
				}
				else{
					up();
				}
			}
		}
		if(!can_move){
			ptr = NULL;
		}
	}
	return *this;
}

template <class T>
GridIterator<T> Grid<T>::end_snake()
{
	if(height % 2 == 0){
		GridIterator<T> temp(lower_left->left);
		//temp.grid_ptr = lower_left;
		return temp;
	}
	if(height % 2 != 0){
		GridIterator<T> temp(lower_right->right);
		//temp.grid_ptr = lower_right;
		return temp;
	}
	return GridIterator<T>(NULL);
}

template <class T>
GridIterator<T> Grid<T>::begin_spiral()
{
	GridIterator<T> begin(upper_left, this);
	begin.spiral = true;
	begin.u_l = upper_left;
	begin.u_r = upper_right;
	begin.l_l = lower_left;
	begin.l_r = lower_right;
	begin.dir = RIGHT;
	begin.spiral_count = 0;

	return begin;
}

template <class T>
GridIterator<T> Grid<T>::end_spiral(){	
	return Grid<T>::iterator(NULL);
}

// -----------------------------------------------------------------
// GRID CLASS IMPLEMENTATION

template <class T>
Grid<T>::Grid(int w, int h, T v) : width(w), height(h){	

	Node<T> *head_r1 = new Node<T>(v);
	upper_left = head_r1;

	//If more than one row
	for (int r = 0; r < height - 1; r++){

		Node<T> *current = head_r1;
		Node<T> *next = new Node<T>(v);
		
		//linking first row horizontally
		if(r == 0){ //If first row, need to create it
			for (int c = 0; c < width - 1; c++){
				//std::cout << current->value;
				current->right = next;
				next->left = current;
				current = next;
				next = new Node<T>(v);
			}
		}

		

		Node<T> *head_r2 = new Node<T>(v);
		Node<T> *current_r2 = head_r2;
		Node<T> *next_r2 = new Node<T>(v);
		
		//Linking Row Two horizontally
		for (int c = 0; c < width - 1; c++){
			current_r2->right = next_r2;
			next_r2->left = current_r2;
			current_r2 = next_r2;
			next_r2 = new Node<T>(v);
		}
		
		//TWO ROWS (Individually linked)
		current = head_r1;
		current_r2 = head_r2;
		
		//Linking The Two Rows
		while(current && current_r2){
			current->down = current_r2;
			current_r2->up = current;
			current = current->right;
			current_r2 = current_r2->right;
		}

		//memory cleanup of temp variables
		delete next;
		delete next_r2;
		
		//"iterating" head down the grid
		head_r1 = head_r2;
	}

	//If only 1 row
	if(height == 1){
		//Current node
		Node<T> *current = head_r1;
		Node<T> *next;
		for (int i = 0; i < width - 1; i++){
			//Creating new next node
			next = new Node<T>(v);
			
			//Testing
			//std::cout << current->value << "  ";
			
			//Iterating over 1row grid
			current->right = next;
			next->left = current;
			current = next;
		}
		//std::cout << '\n';
	}
	
	/*DIAGRAM
	1st iteration	

	Create Row     : [][][][][][][] <- link left/right wise
	Create New Row : [][][][][][][] <- link left/right wise

	Link Row/New Row UP/DOWN wise

	2nd+ iteration

	Current Row already created, so create only 1 row
	Existing Row   : [][][][][] <- already linked
	Create New Row : [][][][][] <- link left/right wise

	Link Row/New Row UP/DOWN wise*/

	//SETTING u_left,u_right,l_left,l_right
	assign_corners();
}

template <class T>
Grid<T>::Grid(){
	width = 0;
	height = 0;
	upper_left = upper_right = NULL;
	lower_left = lower_right = NULL;
}

template <class T>
Grid<T>::Grid(const Grid<T> &old){
	copyGrid(old);
	assign_corners();
}

template <class T>
Grid<T>& Grid<T>::operator=(const Grid<T>& old){
	if(&old != this){
		destroy_grid();
	 	copyGrid(old);
	}
	return *this;
}

template <class T>
void Grid<T>::copyGrid(const Grid<T>& old){
	width = old.width;
	height = old.height;
	upper_left = new Node<T>(old.upper_left->value);
	Node<T> *old_head = old.upper_left;
	
	Node<T> *head = upper_left;
	while(head && old_head){
		Node<T> *current = head;
		Node<T> *old_p = old_head->right;
		while(old_p){
			current->right = new Node<T>(old_p->value);
			current->right->left = current;
			old_p = old_p->right;
			current = current->right;
		}
		if(old_head->down)
			head->down = new Node<T>(old_head->value);
		head = head->down;
		old_head = old_head->down;
	}
}

template <class T>
void Grid<T>::set(int w, int h, T v){
	Node<T>* node = getAtLoc(w, h);
	node->value = v;
}

template <class T>
void Grid<T>::reset(T v){
	Node<T> *head = upper_left;
	while(head){
		Node<T> *current = head;
		while(current){
			current->value = v;
			current = current->right;
		}
		head = head->down;
	}
}

template <class T>
Node<T>* Grid<T>::getAtLoc(int y, int x){
	Node<T> *pos = upper_left;
	//Move y times down
	for (int i = 0; i < y; i++){
		pos = pos->right;
	}
	//Move x times right
	for (int j = 0; j < x; j++){
		pos = pos->down;
	}
	return pos;
}

template <class T>
void Grid<T>::join(Grid<T> &inserted){
	//Variables
	Node<T> *head_1 = upper_right;
	Node<T> *head_2 = inserted.upper_left;
	
	while(head_1 && head_2){
		//Assignment
		head_1->right = head_2;
		head_2->left = head_1;
		//Iterate
		head_1 = head_1->down;
		head_2 = head_2->down;
	}
	width += inserted.width;
	assign_corners();
	
	//Def janky asf - resetting inserteds old member variables.
	inserted.width = inserted.height = 0;
	inserted.upper_left = inserted.upper_right = NULL;
	inserted.lower_left = inserted.lower_right = NULL;
}

template <class T>
void Grid<T>::stack(Grid<T> &inserted){
	Node<T> *head_1 = upper_left;
	Node<T> *head_2 = inserted.lower_left;

	upper_left = inserted.upper_left;
	upper_right = inserted.upper_right;

	while(head_1 && head_2){
		head_1->up = head_2;
		head_2->down = head_1;

		head_1 = head_1->right;
		head_2 = head_2->right;
	}

	height += inserted.height;
	assign_corners();

	inserted.width = inserted.height = 0;
	inserted.upper_left = inserted.upper_right = NULL;
	inserted.lower_left = inserted.lower_right = NULL;
}

template <class T>
void Grid<T>::lift(const iterator& itr, Grid<T>& top){
	Grid<T>::iterator temp = itr;
	//move temp left
	while(temp.ptr->left){
		temp.left();
	}

	//Fixing top Corners
	upper_left = temp.ptr;
	top.lower_left = upper_left->up;
	//Moving right and cutting links
	
	//1 Column
	if(width == 1){
		temp.ptr->up->down = NULL;
		temp.ptr->up = NULL;
	}
	else{ //Multiple Column
		while(temp.ptr->right){
			temp.ptr->up->down = NULL;
			temp.ptr->up = NULL;
			temp.right();
		}
	}
	//Finding height of top
	temp = iterator(top.lower_left);
	int delta_h = 1;
	while(temp.ptr->up){
		delta_h++;
		temp.up();
	}
	top.upper_left = temp.ptr;

	//Setting member variables
	top.width = width;
	top.height = delta_h;
	height -= delta_h;

	//Fixing bottom corners
	top.assign_corners();
	assign_corners();
}

template <class T>
void Grid<T>::chop(const iterator& itr, Grid<T>& side){
	// Creation of temp iterator and moving left 1
	Grid<T>::iterator temp = itr;
	temp.left();

	//Move to top
	while(temp.ptr->up){
		temp.up();
	}
	//Fixing side upper left pointer
	side.upper_left = temp.ptr->right;
	//Cutting links and moving down
	if (height == 1){
		temp.ptr->right->left = NULL;
		temp.ptr->right = NULL;
	}
	else{
		while (temp.ptr){
			temp.ptr->right->left = NULL;
			temp.ptr->right = NULL;
			temp.down();
		}
	}
	//Finding width of side
	temp = iterator(side.upper_left);
	int delta_w = 1;
	while(temp.ptr->right){
		delta_w++;
		temp.right();
	}
	
	//Fixing side member variables
	side.width = delta_w;
	side.height = height;

	//Reassigning corner pointers;
	side.assign_corners();
	assign_corners();
}

template <class T>
void Grid<T>::print()
{

	Node<T> *head = upper_left;
	while(head)
	{
		Node<T> *current = head;
		//Iterating rightwise
		while (current)
		{
			std::cout << std::setw(4) << current->value;
			current = current->right;
		}
		std::cout << '\n';
		//Iterating head downwise
		head = head->down;
	}
	
}

template <class T>
void Grid<T>::destroy_grid(){
	Node<T> *head = upper_left;
	Node<T> *current;
	//Can go down
	while(head){
		//Set current to head of current row
		current = head;
		head = head->down;
		//Can go right
		while(current){
			//Iterate current and remove current(old)
			Node<T> *p = current;
			current = current->right;
			delete p;
		}
	}
	//Reset Member Variables
	upper_left = upper_right = NULL;
	lower_left = lower_right = NULL;
	height = width = 0;
}

template <class T>
void Grid<T>::assign_corners(){
	
	//1 row case
	if(height == 1){
		// 1 <-> 1
		lower_left = upper_left;
		Node<T> *current = upper_left;
		while(current->right){
			//iterate right until end of row
			current = current->right;
		}
		// 1 <-> 1
		lower_right = upper_right = current;
	}
	else{
		//Multi Row Case
		Node<T> *head = upper_left;
		Node<T>* current;
		int r = 0;
		//Next row exists
		while(head){
			current = head;
			//If at bottom
			if (r == height - 1){
				lower_left = current;
			}
			//Next col exists
			while (current->right){
				current = current->right;
			}
			//If at top and farthest col
			if(r == 0){
				upper_right = current;
			}
			//Row count
			r++;
			//Iterate down
			head = head->down;
		}
		lower_right = current;
	}
}


#endif