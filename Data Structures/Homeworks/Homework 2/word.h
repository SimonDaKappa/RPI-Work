#ifndef __word_h_
#define __word_h_
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>


class Word {
public:
	//CONSTRUCTOR
	Word(
		int len = 4, 
		std::string ltrs = "", 
		std::string game_letters = "");
	
	//ACCESSORS
	int getScore() const { return score; };
	unsigned int getLength() const { return length; };
	const std::string getLetters() const { return letters; };
	bool getPangram() const { return pangram; };
	int foundCount() const { return timesfound; };
	std::string getCenter() const { return center_letters; };

	//MODIFIERS
	void setScore(const int& scr){ score = scr; };
	void calcScore();
	bool calcPangram(std::string game_letters);
	void wordFound(int i){timesfound+= i;};
	void addCenter(char cntr) { center_letters += cntr; };

private:
	//REPRESENTATION
	unsigned int length;
	unsigned int score; //cannot be negative
	std::string letters;
	bool pangram;
	int timesfound;
	bool alreadyfound;
	std::string center_letters;
};

// operator< to allow sorting
bool operator< (const Word& left, const Word& right);

bool operator==(const Word& left, const Word& right);

// operator<< to allow output
std::ostream& operator<< (std::ostream& ostr, const Word& w);

#endif
