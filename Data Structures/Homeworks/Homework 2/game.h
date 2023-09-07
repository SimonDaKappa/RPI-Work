#ifndef __game_h_
#define __game_h_
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "word.h"
#include "date.h"

class Game {
public:
	//Constructor
	Game(
		std::vector<Word>& words_, 
		const Date& d, 
		char& cntr_ltr,
		const std::string& game_l);


	//ACCESSORS
	const std::vector<Word> getWords() const { return words; };
	Date getDate() const { return date; };
	std::string getLongest() const { return longest_word; };
	std::string getGameLetters() const { return game_letters; };
	unsigned int getMaxScore() const { return maxscore; };
	int getPangramCount() const { return pangram_count; };
	std::string getLongestWord() const { return longest_word; };
	char getCenter() const { return center_letter; };

	//MODIFIERS
	void calcMaxScore();
	void longestWord();
	void pangramCount();

private:
	std::vector<Word> words;
	Date date;
	char center_letter;
	unsigned int maxscore; //Cannot be negative
	std::string game_letters;
	std::string longest_word;
	int pangram_count;
};

bool operator<(const Game& game1,const Game& game2);

#endif