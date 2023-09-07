#ifndef __tetris_h__
#define __tetris_h__
#include <string>


class Tetris {
public:
	//Default Constructor
	Tetris(const int& w) : width(w) { newData(); }
	//Copy Constructor
	Tetris(const Tetris& t);
	// Assignment
	void operator=(const Tetris& t);		
	
	//Destructor
	~Tetris() { destroy(); }

	//Modifiers
	void print() const;
	void add_piece(char p, int rot, int lpos);
	int remove_full_rows();
	void clear();
	void downshift(int r);
	void add_left_column();
	void add_right_column();
	void remove_left_column();
	void remove_right_column();
	void copy(const Tetris& t);

	//Accessors
	int get_width() const { return width; }
	int get_max_height() const;
	int count_squares() const;

private:
	//Representation
	int width;
	char** data;
	int* heights;

	//Private member functions
	//Creates the 2-D dynamically allocated array of width size
	void newData();
	//Destroying all data stored by data, columns, etc/
	void destroy();
	//Finding the data column that gives a piece max height
	int find_base_block(char** piece, int lpos, int indl, int indr, int& shift);
	//resizing a column of data
	void resize_column(int index, int colsize, int height);
};

//HELPER FUNCTIONS

//Rotates 4x4 piece 90 degree clockwise
void rotate90(char** piece);
//Hardcoded 4x4's for the tetris pieces
void construct_letter(char p, char** piece);

#endif