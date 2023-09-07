#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <typeinfo>


// ======================================================================================

// Helper function to read the provided font from a file.  The format
// of the font file is described in comments below.  The width,
// height, and bitmap_letters variables are set by this function.
void ReadFont(const std::string& font_file,
    int& width,
    int& height,
    std::vector<std::vector<std::string> >& bitmap_letters) {

    // open the font file for reading
    std::ifstream istr(font_file.c_str());
    if (!istr) {
        std::cerr << "ERROR: cannot open font file " << font_file << std::endl;
        exit(0);
    }

    // read in the width & height for every character in the file
    istr >> width >> height;
    assert(width >= 1);
    assert(height >= 1);

    // Create a vector to store all 256 ASCII characters of the
    // characters.  Each character is represented as a vector of
    // <height> strings that are each <width> wide.  Initially the
    // characters are unknown (represented with the '?' character).
    bitmap_letters = std::vector<std::vector<std::string> >
        (256, std::vector<std::string>(height, std::string(width, '?')));

    // read in all the characters
    // first is the ascii integer representation of the character
    int ascii;
    while (istr >> ascii) {
        assert(ascii >= 0 && ascii < 256);
        // next the character is printed in single quotes
        char c;
        istr >> c;
        assert(c == '\'');
        // use std::noskipws to make sure we can read the space character correctly
        istr >> std::noskipws >> c;
        // verify that the ascii code matches the character
        assert(c == (char)ascii);
        // switch back to std::skipws mode
        istr >> std::skipws >> c;
        assert(c == '\'');
        // read in the letter
        std::vector<std::string> bitmap;
        std::string tmp;
        for (int i = 0; i < height; i++) {
            istr >> tmp;
            assert((int)tmp.size() == width);
            // make sure the letter uses only '#' and '.' characters
            for (unsigned int j = 0; j < tmp.size(); j++) {
                assert(tmp[j] == '.' || tmp[j] == '#');
            }
            bitmap.push_back(tmp);
        }
        // overwrite the initially unknown letter in the vector
        bitmap_letters[ascii] = bitmap;
    }
}

// ======================================================================================

void Display(char* arguments[], std::vector<std::vector<std::string>> bitmap_letters) {
    //Numbered comments refer back to my implementation of planning in README.txt
    //Constants (for code cleanliness ik it uses unnessary memory)
    const char foreground = std::string(arguments[4])[0];
    const char background = std::string(arguments[5])[0];
    // 1. Casting argv[3] to string for later use
    std::string input_phrase = std::string(arguments[3]);

    // 2. Converting bitmap to appropriate characters
    std::vector<std::vector<std::string> > converted_bitmap;

    //Looping over each character in input phrase and 
    //creating a tempory bitmap for the current character.
    for (long unsigned int i = 0; i < input_phrase.size(); i++) {
        std::vector<std::string> temp = bitmap_letters[int(input_phrase[i])];
        //replacing all the values in foreground and background line by 
        //line for each singular character bitmap
        for (long unsigned int j = 0; j < temp.size(); j++) {
            std::replace(temp[j].begin(), temp[j].end(), '.', background);
            std::replace(temp[j].begin(), temp[j].end(), '#', foreground);
        }

        //Adding the converted bitmap vector<string> to converted_bitmap.
        converted_bitmap.push_back(temp);
    }

    // 3. Printing out the phrase (Assuming the bitmap has constant height
    for (long unsigned int i = 0; i < converted_bitmap[0].size(); i++) {

        //Outputting all columns in each row
        for (long unsigned int j = 0; j < input_phrase.size(); j++) {
            std::cout << converted_bitmap[j][i] << background;
        }

        std::cout << std::endl;
    }
}

void Read(char* arguments[], int height, int width, std::vector<std::vector<std::string>> bitmap_letters) {
    
    //###########################################################################################
    //1. Getting Vector<String> from string read to file.
    std::string current_line;
    std::vector<std::string> file_input;
   
    std::ifstream read_file;
    read_file.open(arguments[3]);
    //Checking that the file was opened
    if (!read_file) {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }

    while (getline(read_file, current_line)) {
        file_input.push_back(current_line);
    }
    read_file.close();
    
    //1.5 Determining Background vs. Foreground
    
    //Takes advantage of the fact that bottom row is always empty
    char background = file_input[height - 1][0];
    char foreground;
    //flag to preserve processing power
    bool stop = false;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            //Finding the first occurence of non-background character
            if (file_input[row][col] != background) {
                foreground = file_input[row][col];
                stop = true;
                break;
            }
        }
        //Flag
        if (stop == true) {
            break;
        }   
    }
   
    //############################################################################################
    //2. Chunking the ASCII Art

    std::vector<std::vector<std::string>> chunked_bitmap;
    //looping over rows
    for (int i = 0; i < height; i++) {
        //This loop takes the starting index of each "chunk" according to the user given width
        //and iterates to the next chunk's start_index, additionally, it removes the column of 
        //background characters that are implemented between each bitmap.
        for (long unsigned int start_index = 0; start_index < file_input[i].size(); start_index += (width + 1)) {
            //Creating the necessary amount of blank 'characters' on the first runthrough
            if (i == 0) {
                chunked_bitmap.push_back(std::vector<std::string>(height, std::string(width, '?')));
            }
            //Assigns to the current character at current row the substring gotten from file_input
            //start_index / (width + 1) gives the "index" of where the character would be in output string
            chunked_bitmap[start_index / (width + 1)][i] = file_input[i].substr(start_index, width);
        }
    }
  
    //###########################################################################################
    //3. Standardizing Foreground and Background

    for (long unsigned int chunk = 0; chunk < chunked_bitmap.size(); chunk++) {
        for (int row = 0; row < height; row++) {
            std::replace(chunked_bitmap[chunk][row].begin(), chunked_bitmap[chunk][row].end(), foreground, '#');
            std::replace(chunked_bitmap[chunk][row].begin(), chunked_bitmap[chunk][row].end(), background, '.');
        }
    }
    //##########################################################################################
    //4. Character Recognition

    //Used to make my triple loop a little more efficient
    bool found_character = false; //true if all 6 rows were equal, flagging loop to skip to next chunk
    int current_character; //current ASCII in int value
    std::string output = "";

    //Looping over each "chunk": checking every valid ascii bitmap row by row to see
    //if it equals the current chunk
    for (long unsigned int chunk = 0; chunk < chunked_bitmap.size(); chunk++) {
        for (long unsigned int ascii = 32; ascii <= 126; ascii++) { //Bounds were established from simple_font.txt
            for (int row = 0; row < height; row++) {
                //Checking if the two rows are equal
                if (chunked_bitmap[chunk][row] == bitmap_letters[ascii][row]){
                    current_character = ascii;
                    if (row == height - 1) found_character = true;
                }
                else {
                    //skipping to next ASCII Bitmap if any row is wrong.
                    break;
                }
            }
            //Escaping if all 6 rows were correct
            if (found_character == true) break;
        }
        //Prep for next chunk
        found_character = false;
        output += char(current_character);
    }
    //Final Output
    std::cout << output << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 6) {
        std::cerr << "Invalid Argument Count";
        exit(0);
    }
    //Declaring Variables used by Readfont()
    std::string font_file;
    int width, height;
    std::vector<std::vector<std::string> > bitmap_letters;
    //Calling Readfont to create the bitmap of letters
    ReadFont(argv[2], width, height, bitmap_letters);
    //std::cout << "Finished ReadFont()" << std::endl;
    if (strcmp("display", argv[1]) == 0) {
        //Currently returns nothing, only outputs to console
        Display(argv, bitmap_letters);
    }
    else if (strcmp("read", argv[1]) == 0) {
        //Also currently returns nothing, only outputs to console
        //std::cout << "Called Read()" << std::endl;
        Read(argv, height, width, bitmap_letters);
    }
    else {
        std::cerr << "Incorrect command line arguments";
    }
    return 0;
}



