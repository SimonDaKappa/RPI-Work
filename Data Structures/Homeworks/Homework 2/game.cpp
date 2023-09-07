#include "game.h"
#include <iostream>

Game::Game(	
		std::vector<Word>& words_,
		const Date& d,
		char& cntr_ltr,
		const std::string& game_l)
		:
		words(words_), 
		date(d),
		center_letter(cntr_ltr),
		game_letters(game_l)
		{
	calcMaxScore();
	pangramCount();
	longestWord();
		}



void Game::calcMaxScore() {
	maxscore = 0; //Resetting due to a weird bug earlier today
	for (Word w : words) {
		w.calcScore();
		maxscore += w.getScore();
	}
}

void Game::longestWord() {
	longest_word = "";
	for (Word w : words) {
		if (w.getLength() > longest_word.size()) longest_word = w.getLetters();
	}

}

void Game::pangramCount() {
	pangram_count = 0; //Same bug as in calcMaxScore()
	for (Word w : words) {
		//std::cout << w.getLetters() << "\t" << w.getPangram() << '\n';
		if (w.getPangram() == true) pangram_count++;
	}
}

bool operator<(const Game& game1,const Game& game2) {
	//Helper Function that is true if less than, false if >=.
	//Checks first by pangramcount, then max score, and finally chronologically
	if (game1.getPangramCount() < game2.getPangramCount()) {
		return true;
	}
	else if (game1.getPangramCount() == game2.getPangramCount()) {
		if (game1.getMaxScore() < game2.getMaxScore()) {
			return true;
		}
		else if (game1.getMaxScore() == game2.getMaxScore()) {
			if (game1.getDate() < game2.getDate()) {
				return false;
			}
		}
	}
	return false;
}
