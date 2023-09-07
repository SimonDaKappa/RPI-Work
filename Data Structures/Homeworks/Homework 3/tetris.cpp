#include "tetris.h"
#include <iostream>
#include <iomanip>
#include <string>

Tetris::Tetris(const Tetris& t) {
	//Create blank slate and copy onto it
	copy(t);
}

void Tetris::newData() {
	//Sets up data 2d array and 1d column array
	//By default, each column will have size 0;
	//When new letters are added, will call resize_column();
	
	data = new char*[width];
	heights = new int[width];
	for (int i = 0; i < width; i++) {
		data[i] = nullptr;
		heights[i] = 0;
	}
}

int Tetris::get_max_height() const {
	//loops over heights and finds highest value
	int max = 0;
	for (int i = 0; i < width; i++) {
		if (heights[i] > max)
			max = heights[i];
	}
	return max;
}

int Tetris::count_squares() const {
	//loops over each column of data, and counts
	//the number of non ' ' characters, and sums the count up
	int count = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heights[i]; j++) {
			if (data[i][j] != ' ') {
				count++;
			}
		}
	}
	return count;
}

void Tetris::resize_column(int index, int colsize, int height) {
	//Creating new column of height and replacing the old one in data
	char* newcol = new char[height];
	
	//Manually initializing each element in new column
	for (int i = 0; i < height; i++) {
		newcol[i] = '\0';
	}

	//Copying from col in data
	for (int i = 0; i < height && i < colsize; ++i) { 
		newcol[i] = data[index][i];
	}
	//Deleting old column from heap
	delete[] data[index];
	//Reassignment of new values
	data[index] = newcol;
	heights[index] = height;
}

void Tetris::add_piece(char p, int rot, int lpos){
	//Creates 2D dynamic array of ' '
	char** piece = new char*[4];
	for (int r = 0; r < 4; ++r) {
		piece[r] = new char[4];
		for (int c = 0; c < 4; ++c)
			piece[r][c] = ' ';
	}
	
	//Constructs a 2D 4x4 Matrix of the letter
	construct_letter(p, piece);
	
	//Rotates the piece by rot/90 times
	for (int i = 0; i < rot / 90; ++i) {
		rotate90(piece);
	}

	//Finding the farthest left character in 4x4 matrix
	int indl = 4;
	bool flag = false;
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			if (piece[r][c] != ' ') {
				indl = c;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}

	//Finding the farthest right character in 4x4 matrix
	int indr = 0;
	flag = false;
	for (int c = 3; c >=0; c--) {
		for (int r = 0; r < 4; ++r) {
			if (piece[r][c] != ' ') { 
				indr = c;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}

	//Error Checking for piece in bounds
	if (lpos + indr >= width) {
		std::cerr << "Piece being placed out of bounds";
		exit(0);
	}

	//Finding Base Block
	//shift,mheight, and bb_index are height and col values that are used to place
	//the 4x4 piece in the proper place.
	int shift = 0;
	int bb_index = find_base_block(piece, lpos, indl, indr, shift); 
	int mheight = heights[bb_index];
	
	//Placing block at height relative to base block
	//(a) resizing each column by necessary amount
	for (int col = lpos; col <= indr + lpos; col++) {
		//new_height = mheight + (4-shift)- #empty space 
		//above highest non ' ' in col
		
		//Finding empty space
		int empty_count = 0;
		for (int row = 0; row < 4 && piece[row][col - lpos] == ' '; row++) {
			empty_count++;
		}

		//new_height
		int new_height = mheight + (4 - shift) - empty_count;
		//resizing each column with new found height
		resize_column(col, heights[col], new_height);
	}
	
	//(b) placing piece columns in data columns
	//Using shift, mheight to translate piece onto the board
	for (int col = lpos; col <= lpos + indr; col++) {
		for (int row = 3 - shift; row >= 0; row--) {
			//Essentially lines up corresponding col of board with piece col and corresponding
			//height of board with piece height. The 3 is harcoded b/c all pieces are 4x4.
			data[col][mheight + (3 - shift - row)] = piece[row][indl + col - lpos];
		}
	}

	//REPLACING '\0' with a ' ' (space character) in data
	//Each column is originally empty, so I replace them with ' ',
	//so that the provided print function works
	for (int col = 0; col < width; col++) {
		for (int row = 0; row < heights[col]; row++) {
			if (data[col][row] == '\0')
				data[col][row] = ' ';
		}
	}
	//Destroying piece
	for (int i = 0; i < 4; i++) {
		delete[] piece[i];
	}
	delete[] piece;
}

void construct_letter(char p, char** piece){
	// piece passed by pointer
	// I piece
	if (p == 'I') {
		piece[0][0] = 'I';
		piece[1][0] = 'I';
		piece[2][0] = 'I';
		piece[3][0] = 'I';
	}
	// O piece
	if (p == 'O') {
		piece[0][0] = 'O';
		piece[0][1] = 'O';
		piece[1][0] = 'O';
		piece[1][1] = 'O';
	}
	// T piece
	if (p == 'T') {
		piece[0][0] = 'T';
		piece[0][1] = 'T';
		piece[0][2] = 'T';
		piece[1][1] = 'T';
	}
	// Z piece
	if (p == 'Z') {
		piece[0][0] = 'Z';
		piece[0][1] = 'Z';
		piece[1][1] = 'Z';
		piece[1][2] = 'Z';
	}
	// S Piece
	if (p == 'S') {
		piece[1][0] = 'S';
		piece[1][1] = 'S';
		piece[0][1] = 'S';
		piece[0][2] = 'S';
	}
	// L piece
	if (p == 'L') {
		piece[0][0] = 'L';
		piece[1][0] = 'L';
		piece[2][0] = 'L';
		piece[2][1] = 'L';
	}
	// J piece
	if (p == 'J') {
		piece[0][1] = 'J';
		piece[1][1] = 'J';
		piece[2][1] = 'J';
		piece[2][0] = 'J';
	}
}

void rotate90(char** piece){
	//This function is only used for 4x4 piece
	//matrix, thus it is hardecoded to N = 4
	//Source found in README.TXT
	for (int i = 0; i < 4 / 2; ++i) {
		for (int j = 0; j < 4 / 2; ++j) {
			//Swap elements of each each cycle clockwise
			char temp = piece[i][j];
			piece[i][j] = piece[4 - 1 - j][i];
			piece[4 - 1 - j][i] = piece[4 - 1 - i][4 - 1 - j];
			piece[4 - 1 - i][4 - 1 - j] = piece[j][4 - 1 - i];
			piece[j][4 - 1 - i] = temp;
		}
	}
}

int Tetris::find_base_block(char** piece, int lpos, int indl, int indr, int& shift){
	//This function finds the square on data that will result in
	//the placed piece having the highest height. "The resting/base block"
	
	//looping over each column in piece,
	//and corresponding column on data
	//NOTE: boardcol = col + lpos
	
	//Variables for comparison
	int mheight = 0;
	int bb_index = lpos;
	//Looping first over columns of 4x4 and then rows

	for (int col = indl; col <= indr; col++) {
		int boardcol = col + lpos;
		//looping over rows backwards
		for (int row = 3; row >= 0; row--) {
			if (piece[row][col] != ' ') {
				int temp = heights[boardcol] + (row + 1); //height value
				//if this combination of boardcol and matrix results in 
				//higher max height
				if (temp > mheight) {
					//assigning new mheight, and corresponding variables
					mheight = temp;
					bb_index = boardcol;
					shift = 3 - row;
					//If the lowest part of 4x4 results in higher mheight
					//A higher part of 4x4 in same column wont change anything
					//So you can automatically move on to new col.
					break;
				}
			}
		}
	}
	return bb_index;
}

int Tetris::remove_full_rows() {
	//Loops row than col to find all full rows
	//and then downshift every row above the full one
	//returns total number of full rows
	int score = 0;
	for (int row = 0; row < get_max_height(); ++row) {
		bool fullrow = true;
		for (int col = 0; col < width; ++col) {
			if (row < heights[col]) {
				//Check for first case of non piece
				if (data[col][row] == ' ') {
					fullrow = false;
					break;
				}
			}
			//If no empty spaces
			else {
				fullrow = false;
				break;
			}
		}
		if (fullrow) {
			downshift(row);
			//iterate down to accomodate downshift
			//Used for case of back to back full rows.
			row--;
			score++;
		}
	}
	return score;
}

void Tetris::downshift(int r) {
	//Given a row (must be in (0,heights[col]), shift each element above r
	//down by 1, and then resize each column to be 1 smaller
	
	//Shifting Down
	for (int col = 0; col < width; col++) {
		for (int row = r; row < heights[col] - 1; row++) {
			data[col][row] = data[col][row + 1];
		}
		//Resizing down by 1
		resize_column(col, heights[col], heights[col] - 1);
		//checking if the entire column is ' ', if yes, resize,
		//row to height 0
		bool empty = true;
		for (int row = 0; row < heights[col]; row++) {
			if (data[col][row] != ' ') {
				empty = false;
				break;
			}
		}
		if(empty)
			resize_column(col, heights[col], 0);
	}
}

void Tetris::add_left_column() {
	width++; //INCREMENT
	//DATA REPLACEMENT
	char** newData = new char*[width];
	newData[0] = nullptr;
	//copying from old data
	for (int i = 1; i < width; i++) {
		newData[i] = data[i - 1];
	}
	//reassignment
	delete[] data;
	data = newData;

	//HEIGHTS REPLACEMENT
	int* newHeights = new int[width];
	newHeights[0] = 0;
	//copying
	for (int i = 1; i < width; i++) {
		newHeights[i] = heights[i - 1];
	}
	//reassignment
	delete[] heights;
	heights = newHeights;


}

void Tetris::add_right_column() {
	width++;
	//DATA REPLACEMENT
	char** newData = new char*[width];
	newData[width - 1] = nullptr;
	//copying from old data
	for (int i = 0; i < width-1; i++) {
		newData[i] = new char[heights[i]];
		for (int j = 0; j < heights[i]; j++) {
			newData[i][j] = data[i][j];
		}
		//memory cleanup
		delete[] data[i];
	}
	//reassignment
	delete[] data;
	data = newData;

	//HEIGHTS REPLACEMENT
	int* newHeights = new int[width];
	newHeights[width-1] = 0;
	//copying
	for (int i = 0; i < width-1; i++) {
		newHeights[i] = heights[i];
	}
	//reassignment
	delete[] heights;
	heights = newHeights;
}

void Tetris::remove_left_column() {
	//DATA REPLACEMENT
	char** newData = new char* [width - 1];
	//memory cleanup
	delete[] data[0];
	//copying from old data
	for (int i = 1; i < width; i++) {
		newData[i - 1] = new char[heights[i]];
		for (int j = 0; j < heights[i]; j++) {
			newData[i - 1][j] = data[i][j];
		}
		//memory cleanup
		delete[] data[i];
	}
	//reassignment
	delete[] data;
	data = newData;

	//HEIGHTS REPLACEMENT
	int* newHeights = new int[width - 1];
	//copying
	for (int i = 1; i < width; i++) {
		newHeights[i - 1] = heights[i];
	}
	//reassignment
	delete[] heights;
	heights = newHeights;
	//decrement
	width--;
}

void Tetris::remove_right_column() {
	//DATA REPLACEMENT
	width--;
	char** newData = new char* [width];
	//Memory cleanup
	delete[] data[width];
	//Copying elements form old data
	for (int i = 0; i < width; i++) {
		newData[i] = new char[heights[i]];
		for (int j = 0; j < heights[i]; j++) {
			newData[i][j] = data[i][j];
		}
		delete[] data[i];
	}
	delete[] data;
	//reassignment
	data = newData;

	//HEIGHTS REPLACEMENT
	int* newHeights = new int[width];
	//copying
	for (int i = 0; i < width; i++) {
		newHeights[i] = heights[i];
	}
	//reassignment
	delete[] heights;
	heights = newHeights;
}

void Tetris::operator=(const Tetris& t) { 
	//Self Assignment Check
	if(this != &t) {
		//Copy from fresh slate
		destroy();
		copy(t);
	}	
}

void Tetris::copy(const Tetris& t) {
	
	//Reassign width
	width = t.width;
	//Re initialize heights after destroy()
	heights = new int[width];
	//Copying values of t.heights
	for (int i = 0; i < width; i++) {
		heights[i] = t.heights[i];
	}
	data = new char* [width];
	//Copying Values of t.data
	for (int i = 0; i < width; i++) {
		data[i] = new char[heights[i]];
		for (int j = 0; j < heights[i]; j++) {
			data[i][j] = t.data[i][j];
		}
	}
}

void Tetris::clear() {
	//loop over [0,width], deleting cols and setting height to 0
	for (int i = 0; i < width; i++) {
		char* new_col = new char[0];
		heights[i] = 0;
		delete[] data[i];
		data[i] = new_col;
	}
}

void Tetris::destroy() {
	//Destroys any and all dynamic memory used
	//By Tetris class
	//So destroys 2D dynamic array data
	//and 1D Dynamic array columns.
	delete[] heights;
	for (int i = 0; i < width; i++) {
		delete[] data[i];
	}
	delete[] data;
}	