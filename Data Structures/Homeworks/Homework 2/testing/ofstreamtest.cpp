#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char* argv[]) {
	std::ifstream inFile("small_test.txt");
	if (!inFile) {
		std::cerr << "Couldnt open File\n";
		exit(0);
	}


	std::string instring, garbage, month_name, letters;
	int year, month, day;
	char center_letter, a, b, c, d, e, f;
	std::vector<std::string> words;
	bool game_end = false;
	while (inFile) {
		if (game_end == false) {
			inFile >> garbage;
		}
		
		inFile
			>> month_name
			>> day
			>> garbage //"," after the day
			>> year
			>> garbage //"[" before center character
			>> center_letter
			>> garbage //"]" after center character
			>> a //The six other letters from a game board.
			>> b
			>> c
			>> d
			>> e
			>> f
			>> garbage; //second horizontal bar
		letters = { center_letter, a, b, c, d, e, f };
		//std::cout << letters << std::endl; //Testing


		while (inFile >> instring) {
			if (instring[0] == '-') {
				game_end = true;
				break; //checking if next game
			}
			words.push_back(instring);
		}

	}
	for (std::string s : words) {
		std::cout << s << std::endl;
	}
}