#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

/*
	Plan: Word Sort
	1. Take in character array of words
	2. Loop over argc (length of character array)
	3. push back each word at index i into vector v
	4. use std::sort to sort vector
	5. loop over vector and console output words
	*/

int main(int argc, char* argv[]) {
	std::vector<std::string> words;
	for (int i = 1; i < argc; i++) {
		words.push_back((argv[i]);
	}
	std::sort(words.begin(), words.end());
	std::cout << "sorted strings: ";
	for (int i = 0; i < argc; i++) {
		std::cout << words[i] << ' ';
	}
	
	/*int product = 1;
	for(int i = 1;i < argc; i++){
		int foo = std::stoi(argv[i]);
		product *= foo;
	*/
	}
	std::cout << "product of integers : " << product << std::endl; */
}