#include "word.h"
#include <string>
#include <iostream>

Word::Word(
		int len, 
		std::string ltrs, 
		std::string game_letters)
		:
		length(len), 
		letters(ltrs)
		{
		timesfound = 0;
		alreadyfound = false;
		calcPangram(game_letters);
		center_letters = "";
		}

void Word::calcScore() {
	
	if (score == 32767) score = 0;
	if (length == 4) score = 1;
	else if (length > 4) {
		//checking for pangram
		if (pangram == true) {
			score = length + 7; 
		}
		//non pangram of length > 4
		else score = length;
	}
}

bool Word::calcPangram(std::string game_letters){
	pangram = false;
	//looping over all seven letters in spelling bee board
	for (long unsigned int i = 0; i < game_letters.size(); i++) {
		//if no index of substring is found, find() returns string::npos,
		//if any letter return npos, not a pangram
		if (letters.find(game_letters[i]) == std::string::npos) {
			//std::cout << "Calc Pangram called1\t" << letters << "\t" << pangram << std::endl;
			return pangram;
		}
	}
	//More likely than not for a word to not be a pangram, so default case is false
	pangram = true;
	//std::cout << "Calc Pangram called2\t" << letters << "\t" << pangram << std::endl;
	return pangram;
}

bool operator==(const Word& left, const Word& right) {
	if (left.getLetters() == right.getLetters()) return true;
	return false;
}

bool operator<(const Word& left, const Word& right) {
	if (left.foundCount() < right.foundCount()) {
		return true;
	}
	else if (left.foundCount() == right.foundCount()) {
		if (left.getLetters() > right.getLetters()) {
			// '>' because I need descending foundcount
			// and ascending alphabettically
			return true;
		}
	}
	return false;
}

std::ostream& operator<< (std::ostream & ostr, const Word & w) {
	ostr << w.getLetters();
	return ostr;
}