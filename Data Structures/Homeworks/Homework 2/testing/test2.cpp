#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
	const int row = 3;
	const int col = 4;
	int count = 0;
	std::vector<std::string> input(row, std::string(col, '1'));

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			input[r][c] = char(r + c + count + 97);
			std::cout << input[r][c] << ' ';
		}
		std::cout << '\n';
		count += 3;
	}

	int rows = 4;
	int cols = 3;
	char** p = new char* [rows];
	for (int r = 0; r < rows; r++) {
		p[r] = new char[cols];
	}

	for (int p_c = input.size() - 1; p_c >= 0; p_c--) {
		std::cout << "new row " << p_c << '\n';
		for (int p_r = 0; p_r < input[p_c].size(); p_r++) {
			std::cout << "new col " << p_r << " ";
			p[p_r][input.size() - p_c] = input[p_c][p_r];
		}
		std::cout << "\n";
	}

	std::cout << "passed rotation\n";

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c <= cols; c++) {
			std::cout << p[r][c] << " ";
		}
		std::cout << '\n';
	}





}