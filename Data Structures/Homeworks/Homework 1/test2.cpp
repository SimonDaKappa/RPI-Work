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

int main(int argc, char* argv[]) {
    
    //Carryover from ascii_font_art.cpp
    std::string font_file;
    std::vector<std::vector<std::string> > bitmap_letters;
    int height, width;
    ReadFont(argv[2], width, height, bitmap_letters);
    std::cout << bitmap_letters.size() << std::endl;
    
    //1. Getting Vector<String> from string read to file. WORKS AS INTENDED
    std::string current_line;
    std::vector<std::string> file_input;
    std::ifstream read_file;
    std::cout << "file name: " << argv[3] << std::endl;
    read_file.open(argv[3]);
    std::cout << "file opened" << std::endl;
    //Checking that the file was opened
    if (!read_file) {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }
    std::cout << "File opened: " << argv[3] << std::endl;

    while (getline(read_file, current_line)) {
        std::cout << "current line: " << current_line << std::endl;
        file_input.push_back(current_line);
    }
    read_file.close();
    std::cout << "Finished read_file" << std::endl;


    //1.5 Determining Background vs. Foreground - WORKS AS INTENDED 
    std::cout << "Height: " << height << std::endl;
    std::cout << "file_input length: " << file_input.size() << std::endl;
    char background = file_input[height - 1][0];
    std::cout << "created background : " << background << std::endl;
    //Takes advantage of the fact that bottom row is always empty
    char foreground;
    //flag to preserve processing power
    bool stop = false;
    for (int row = 0; row < height; height++) {
        for (int col = 0; col < width; col++) {
            //Finding the first occurence of non-background character
            std::cout << "row,col = " << row << ',' << col << std::endl;
            if (file_input[row][col] != background) {
                foreground = file_input[row][col];
                std::cout << "created foreground : " << foreground << std::endl;
                stop = true;
                break;
            }
        }
        //Flag
        if (stop == true) {
            break;
        }

    }

    std::cout << "Passed Checkpoint 1" << std::endl;
    //2. Chunking the ASCII Art - WORKS AS INTENDED

    std::vector<std::vector<std::string>> chunked_bitmap;

    for (int i = 0; i < height; i++) {
        //This loop takes the starting index of each "character" according to the user given width
        //and iterates to the next characters start_index, additionally, it removes the column of 
        //background characters that are implemented between each bitmap.
        for (long unsigned int start_index = 0; start_index < file_input[i].size(); start_index += (width + 1)) {
            //Creating the necessary amount of blank 'characters' on the first runthrough
            if (i == 0) {
                chunked_bitmap.push_back(std::vector<std::string>(height, std::string(width, '?')));
            }
            //Assigns to the current character at current row the substring gotten from file_input
            // start_index / (width + 1) gives the "index" of where the character would be in output string
            chunked_bitmap[start_index / (width + 1)][i] = file_input[i].substr(start_index, width);
            std::cout << chunked_bitmap[start_index / (width + 1)][i];
        }
        std::cout << std::endl;
    }
 


    //Testing Character recognition for first chunk only
    int chunk = 0;
    int current_ASCII = 0;
    bool flag = false;
    
    
    
    
    
    for (int i = 0; i < 2; i++) {
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                std::cout << bitmap_letters[i][x][y];
            }
            std::cout << std::endl;
        }
    }
    
    
    
    
    
    
    for (long unsigned int ASCII_count = 0; ASCII_count < 1; ASCII_count++) {
        std::cout << "current ASCII: " << ASCII_count << std::endl;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                std::cout << "current char chunked: "<< chunked_bitmap[chunk][row][col] <<std::endl;
                std::cout << "current char bitmap_l: " << bitmap_letters[ASCII_count][row][col] <<std::endl;
                if (chunked_bitmap[chunk][row][col] != bitmap_letters[ASCII_count][row][col]) { //If ij comparison wrong
                    flag = true;
                    break;
                }
                else {
                    current_ASCII = ASCII_count;
                    std::cout << current_ASCII << "\t";
                }
            }
            if (flag == true) {
                break;
            }

        }
        flag == false;
    }
    std::cout << current_ASCII << "\t";

}