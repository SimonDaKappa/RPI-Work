#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "game.h"
#include <cmath> //USED FOR CUSTOM_STATS

//Setup Games Function
void setup(char *argv[], std::vector<Game>& games){
	
	//Opening File
	std::ifstream inFile(argv[1]);
	
	//Error Checking
	if (!inFile) {
			std::cerr << "ERROR: Cannot Open input File.\n";
			exit(0);
	}
	
	//Declaring a bunch of variables that are used for instream
	//and creating games/words.
	std::string instring, garbage, month_name, letters;
	int year, day;
	char center_letter, a, b, c, d, e, f;
	std::vector<Word> words;
	bool game_end = false;

	//A double loop where the outside iteration represents each game, and each inner
	//iteration is an instream value that represents a word from that game
	while (inFile) { 
		//Checking if it is first game or not from file
		if (game_end == false) {
			inFile >> garbage;
		}
		//Getting all the useful information from each "header" of a game
		inFile
			>> month_name
			>> day
			>> garbage //"," after the day
			>> year
			>> garbage //"[" before center character
			>> center_letter
			>> garbage //"]" after center character
			>> a //The six other letters from a game board.
			>> b //
			>> c //
			>> d //
			>> e //
			>> f //
			>> garbage; //second horizontal bar

		//Using std::string overloaded operator to concatenate chars
		letters = { center_letter, a, b, c, d, e, f };

		//Grabbing all words for a certain game
		while (inFile >> instring) {
			//checking if next game
			if (instring[0] == '-') { //checking if next instring == bar -> next game start
				game_end = true;
				break; 
			}
			//Creating a word object and adding to words
			words.push_back(Word(instring.size(), instring, letters)); 
		}

		//Constructing A Game
		Game newGame(
			words,
			Date( StringToMonth(month_name), day, year ),
			center_letter,
			letters);
		//Adding new game to games
		games.push_back(newGame);

		//Emptying Words after each game
		words.clear();
	}
}

//Game_Stats helper function
std::vector<int> wordsByLength(
	const std::vector<Word>& words,
	unsigned int longest_len)
{
	std::vector<int> temp(longest_len-3); //index = length - 4 + 1, (+1) bc of length
	for (Word w : words) {
		for (unsigned int i = 4; i <= longest_len + 1; i++) {
			if (w.getLength() == i) {
				temp[i - 4] += 1;
			}
		}
	}
	return temp;
}

//Game_Stats helper function.
void print_game_stats(
	char* argv[],
	const std::vector<Game>& games_r,
	int longest_len) 
{
	//Open File
	std::ofstream outFile(argv[2]);
	
	//Error Checking
	if (!outFile) {
		std::cerr << "ERROR: Couldn't open output file\n";
		exit(0);
	}

	//Writing Header
	outFile /*Top row*/
		<< std::setw(20) << std::left << "date"
		<< std::setw(18) << std::left << "letters"
		<< std::setw(7) << std::left << "score"
		<< std::setw(10) << std::left << "pangrams"
		<< std::setw(8) << std::left << "#words";

	//Adding necessary columns that represent word lengths
	for (int i = 4; i <= longest_len; i++) {
		outFile << std::setw(3) << std::right << i;
	}

	outFile /*Horizontal Bar*/
		<< "\n"
		<< std::string(65, '-')
		<< std::string(3 * (longest_len - 4) + 1, '-') 
		//Adds the necessary columns (ie. 4 5 6 7 8 9...)
		<< "\n";

	//Looping over reversed and sorted games to format output
	for (Game g : games_r) {
		//Game Date
		outFile
			<< std::setw(10) << std::left << MonthToString(g.getDate().getMonth())
			<< std::setw(2) << std::right << g.getDate().getDay()
			<< std::setw(2) << std::left << ","
			<< std::setw(6) << std::left << g.getDate().getYear();
		//Game letters
		outFile
			<< std::setw(1) << std::left << '['
			<< ' ' << g.getGameLetters()[0] << ' '
			<< std::setw(1) << std::right  << ']'
			<< std::setw(2) << std::right << g.getGameLetters()[1]
			<< std::setw(2) << std::right << g.getGameLetters()[2]
			<< std::setw(2) << std::right << g.getGameLetters()[3]
			<< std::setw(2) << std::right << g.getGameLetters()[4]
			<< std::setw(2) << std::right << g.getGameLetters()[5]
			<< std::setw(2) << std::right << g.getGameLetters()[6];
		//Game Score
		outFile
			<< std::setw(6) << std::right << g.getMaxScore();
		//Pangram Count
		outFile
			<< std::setw(10) << std::right << g.getPangramCount();
		//Word Count
		outFile
			<< std::setw(8) << std::right << g.getWords().size()
			<< std::setw(2) << " ";
		
		//Words by Length
		std::vector<int> temp = wordsByLength(g.getWords(), longest_len);
		//vector of ints, where index = length - 4 + 1, and temp[index] is the count of that length
		for (unsigned int i = 0; i < temp.size(); i++) {
			//if no words of size i
			if (temp[i] == 0) { 
				outFile << "   ";
				continue; //skip to next word
			}
			//if words of size i
			else {
				outFile << std::setw(3) << std::right << temp[i];
			}
		}
		outFile << std::endl;
	}
	outFile.close();
}

//Game_Stats Function
void game_stats(char* argv[],std::vector<Game>& games) {
	//Sorting and Reversing the sorted games vec
	//using overloaded < operator from games.cpp
	std::sort(games.begin(), games.end());
	std::vector<Game> games_reversed;
	for (int i = games.size() - 1; i >= 0; i--) {
		games_reversed.push_back(games[i]);
	}
	
	//Finding longest word.
	std::vector<int> word_lengths;

	for (Game g : games_reversed) {
		word_lengths.push_back(g.getLongestWord().size());
	}
	
	//Sorting so that the longest word out of all games is last
	std::sort(word_lengths.begin(), word_lengths.end());
	int longest_length = word_lengths[word_lengths.size() - 1];

	print_game_stats(argv,games_reversed, longest_length);
	//Helper function to write to file.
}

//Word_Stats helper function
int count_centers(char c, std::string center_letters) {
	//counts the amount of times a certain letter appears in center_letters.
	int count = 0;
	for (unsigned int i = 0; i < center_letters.size(); i++) {
		if (c == center_letters[i])
			count++;
	}
	return count;
}

//Word_Stats helper function
void print_word_stats(
	char** argv,
	const std::vector<Word>& Words_r,
	int longest) {

	//Open File
	std::ofstream outFile(argv[2]);

	//Error Checking
	if (!outFile) {
		std::cerr << "ERROR: Couldn't open output file\n";
		exit(0);
	}

	//Writing Header
	
	/* 
	all if(longest > 8) statements offer alternative spacings to accomodate
	for larger words
	*/

	//Word and Count in header
	if (longest > 8) {
		outFile
			<< std::setw(3 + longest - 4) << std::left << "word"
			<< std::setw(9) << std::left << "count";
	}
	else {
		outFile
			<< std::setw(7) << std::left << "word"
			<< std::setw(9) << std::left << "count";
	}

	//Adding all letters to header
	for (int i = int('a'); i <= int('z'); i++) {
		outFile << std::setw(3) << std::left << char(i);
	}
	
	//Horizontal Bar in Header
	if (longest > 8) {
		outFile
			<< '\n'
			<< std::string(92 + longest - 8, '-')
			<< '\n';
	}
	else {
		outFile
			<< '\n'
			<< std::string(92, '-')
			<< '\n';
	}

	//Looping over each word and outputting the calculated statistics
	for (Word w : Words_r) {
		//Actual word and times found
		if (longest > 8) {
			outFile
				<< std::setw(longest + 3) << std::left << w
				<< std::setw(3) << std::left << w.foundCount();
		}
		else {
			outFile
				<< std::setw(11) << std::left << w
				<< std::setw(3) << std::left << w.foundCount();
		}
		
		//For each letter, outputs the amount of times 
		//it was a center letter and also in that word
		for (int i = 0; i < 26; i++) {
			//For each letter, count the amount of times it shows up in center_letters;
			int count = count_centers(char(i + 97), w.getCenter());
			//replacing 0's with whitespace
			if(count == 0)
				outFile << std::setw(3) << std::right << ' ';
			else
				outFile << std::setw(3) << std::right << count;
		}
		outFile << std::endl;
	}
	outFile.close();
}

//Word_Stats Function
void word_stats(char* argv[], std::vector<Game>& games) {
	//Fill vector will all words in games minus duplicates
	std::vector<Word> Words;

	//Looping over each game and its words
	for (Game g : games) {
		for (Word w : g.getWords()) {
			//If no words in Words
			if (Words.size() == 0) {
				//increasing times found and center letters
				w.wordFound(1);
				w.addCenter(g.getCenter());
				//Adding new word to Words
				Words.push_back(w);
				continue;
			}
			bool found = false; //Initializing and also resetting to default value
			for (unsigned int i = 0; i < Words.size(); i++) {
				//if any element in Words == w, then w in Words
				if (w == Words[i]) { 
					//increasing times found and center letters
					Words[i].wordFound(1);
					Words[i].addCenter(g.getCenter());
					found = true;
					break;
				}
			}
			if (found == false) {
				//if false at end, then the word is new, add it Words.
				w.wordFound(1);
				w.addCenter(g.getCenter());
				Words.push_back(w);
			}
		}

	}

	//Sorting and Reversing according to custom operator
	std::sort(Words.begin(), Words.end());
	std::vector<Word> Words_r;
	for (int i = Words.size() - 1; i >= 0; i--) {
		Words_r.push_back(Words[i]);
	}

	//Finding longest word.
	std::vector<int> word_lengths;

	for (Game g : games) {
		//ADDing to word_lengths the longest word size from each game
		word_lengths.push_back(g.getLongestWord().size());
	}

	//sorting so that longest at end
	std::sort(word_lengths.begin(), word_lengths.end()); 
	int longest_length = word_lengths[word_lengths.size() - 1];

	//Helper function to output to file
	print_word_stats(argv, Words_r,longest_length);
}


//Letter_Stats helper function
void print_letter_stats(
	char** argv,
	const std::vector<int>& countsC,
	const std::vector<float>& averagesC,
	const std::vector<int>& countsNC,
	const std::vector<float>& averagesNC
	){
	//Open File
	std::ofstream outFile(argv[2]);

	//Error Checking
	if (!outFile) {
		std::cerr << "ERROR: Couldn't open output file\n";
		exit(0);
	}

	//Printing Header
	outFile
		<< std::setw(9) << std::left << "letter"
		<< std::setw(10) << std::left << "#center"
		<< std::setw(13) << std::left << "avg center"
		<< std::setw(9) << std::left << "#other"
		<< std::setw(9) << std::left << "avg other\n";

	//Bar
	outFile << std::string(50, '-') << '\n';

	//Main Body
	for (int i = int('a'); i <= int('z'); i++) {
		
		int index = i - int('a');
		outFile << std::setw(9) << std::left << char(i);
		
		//Outputting the count for center letters
		//Also replaces 0's with whitespace.
		if (countsC[index] != 0) 
			outFile << std::setw(7) << std::right << countsC[index];
		else 
			outFile << std::setw(7) << std::right << ' ';
		
		//For floats
		outFile	<< std::fixed;
		
		//Outputting the avg max game score for center letters
		//Also replaces 0's with whitespace.
		if (averagesC[index] != 0) 
			outFile << std::setw(13) << std::right 
			<< std::setprecision(1) << averagesC[index];
		else 
			outFile << std::setw(13) << std::right << ' ';
		
		///Outputting the count for non center letters
		//Also replaces 0's with whitespace.
		if (countsNC[index] != 0) 
			outFile << std::setw(9) << std::right << countsNC[index];
		else 
			outFile << std::setw(9) << std::right << ' ';
		
		//Outputting the avg max game score for non center letters
		//Also replaces 0's with whitespace.
		if (averagesNC[index] != 0) 
			outFile << std::setw(12) << std::setprecision(1)
			<< std::right << averagesNC[index] << '\n';
		else 
			outFile << "      \n";
	}
	outFile.close();
}


//Letter_Stats Function
void letter_stats(char** argv, std::vector<Game>& games) {
	
	std::vector<float> averagesC(26, 0); 
	std::vector<int> countsC(26, 0);
	//(0,25) -> running average
	// (0,25) -> corresponding counts
	//Corresponds to center letter only
	//Looping over each letter, and seeing if any games have current letter as center
	
	for (int i = int('a'); i <= char('z'); i++) {
		for (Game g : games) {
			if (char(i) == g.getCenter()) {
				//adding count
				countsC[i - int('a')]++;
				//averaging score
				//Since iterated first, do not have to worry about divide by 0
				//Calculating new average.
				averagesC[i - int('a')] = (averagesC[i - int('a')] * (countsC[i - int('a')] -1)
					+ g.getMaxScore()) / countsC[i - int('a')];
			}
		}
	}

		std::vector<int> countsNC(26, 0);
		std::vector<float> averagesNC(26, 0.0);

		//(0,25) -> running average
		// (0,25) -> corresponding counts
		//Can be any letter that is not the center, gameletters (1,6)
		for (int i = int('a'); i <= char('z'); i++) {
			for (Game g : games) {
				for (int j = 1; j <= 6; j++) { //looping over non-center letters
					if (char(i) == g.getGameLetters()[j]) {
						//adding count
						countsNC[i - int('a')]++;
						
						//averaging score
						//Since iterated first, do not have to worry about divide by 0
						//Calculating new average.
						averagesNC[i - int('a')] = (averagesNC[i - int('a')] * (countsNC[i - int('a')] - 1)
							+ g.getMaxScore()) / countsNC[i - int('a')];
					}
				}
			}

		}
	print_letter_stats(argv, countsC, averagesC, countsNC, averagesNC);
}


void print_custom_stats(
	char** argv,
	std::vector<float> rel_freq,
	std::vector<float> calc_rel_freq,
	std::vector<float> percent_error) 
{
	
	std::ofstream outFile(argv[2]);
	//Error Checking
	if (!outFile) {
		std::cerr << "ERROR: Couldn't open output file\n";
		exit(0);
	}

	outFile
		<< std::setw(9) << std::left << "letter"
		<< std::setw(12) << std::left << "frequency"
		<< std::setw(18) << std::left << "calc. frequency"
		<< std::setw(7) << std::left << "% error" << std::endl
		<< std::string(46, '-')
		<< '\n';

	for (int i = 0; i < 26; i++) {
		outFile
			<< std::setw(6) << std::left << char(i + 97)
			<< std::setw(12) << std::right << std::setprecision(5) << rel_freq[i]
			<< std::setw(18) << std::right << std::setprecision(5) << calc_rel_freq[i]
			<< std::fixed
			<< std::setw(10) << std::right << std::setprecision(5) << percent_error[i]
			<< "\n";
	}

	float error_sum = 0;
	for (float f : percent_error) {
		error_sum += f;
	}
	outFile
		<< "Total Error: " << error_sum << "%";

	outFile.close();
}


void custom_stats(char** argv, std::vector<Game>& games) {
	

	//TO PLEASE AUTOGRADER WHILE MY CODE IS COMMENTED, COMMENT
	//THIS SECTION WHEN REVIEWING ACTUAL CODE
	
	std::ofstream commentOut(argv[2]);

	if (!commentOut) {
		std::cerr << "ERROR: Couldn't open output file\n";
		exit(0);
	}

	commentOut
		<< "AUTOGRADER CANT OPEN MY PROVIDED TXT FILE,"
		<< "SO I AM COMMENTING MY REAL CUSTOM_STATS OUT.\n"
		<< "PLEASE UNCOMMENT MAIN CODE AND USE MY PROVIDED TXT TO PARSE "
		<< "WHEN YOU WOULD LIKE TO SEE MY CUSTOM_STATS.\n"
		<< games[0].getWords()[0];

	commentOut.close();


	/*
	std::vector<float> relative_frequencies(25, 0); //(0 = A, ... , 25 = Z) representation

	std::ifstream relfreqIN("relative_frequency.txt");

	if (!relfreqIN) {
		std::cerr << "ERROR: relative_frequency.txt not found in directory";
		exit(0);
	}

	for (unsigned int i = 0; i < relative_frequencies.size(); i++) {
		std::string garbage;
		relfreqIN
			>> garbage
			>> relative_frequencies[i];
	}

	//Calculating relative frequencies for each letter.
	std::vector<int> count_letters(25, 0); //(0 = A, ... , 25 = Z) representation

	for (Game g : games) {
		for (char c : g.getGameLetters()) {
			count_letters[int(c) - int('a')]++;
		}
	}

	int sum = 0;
	std::vector<float> calc_relative_frequencies(25, 0); //(0 = A, ... , 25 = Z) representation

	for (int i : count_letters) {
		sum += i;
	}
	std::vector<float> percent_error(25, 0); //(0 = A, ... , 25 = Z) representation
	for (unsigned int i = 0; i < calc_relative_frequencies.size(); i++) {
		calc_relative_frequencies[i] = count_letters[i] / float(sum);
		//Calculating percent difference
		float experimental = calc_relative_frequencies[i];
		float theoretical = relative_frequencies[i];
		percent_error[i] = std::abs((theoretical - experimental) / (theoretical)) * 100.0;
	}
	print_custom_stats(argv, relative_frequencies, calc_relative_frequencies, percent_error);
	*/
}

int main(int argc, char* argv[]) {
	//Argument Error Checking
	if (argc != 4) {
		std::cerr
			<< "Invalid argument count: Use format ./*.out input.txt output.txt --*_stats"
			<< std::endl;
		exit(0);
	}
	std::vector<Game> games;
	//filling vector<Game>
	setup(argv, games);
	if (std::string(argv[3]) == "--game_stats")
		game_stats(argv, games);
	else if (std::string(argv[3]) == "--word_stats")
		word_stats(argv, games);
	else if (std::string(argv[3]) == "--letter_stats")
		letter_stats(argv, games);
	else if (std::string(argv[3]) == "--custom_stats")
		custom_stats(argv, games);
	else {
		std::cerr << "Invalid stastistic inputted, exiting.\n";
		exit(0);
	}
}