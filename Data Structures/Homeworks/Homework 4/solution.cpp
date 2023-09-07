#include "solution.h"
#include <list>
#include <string>
#include <iostream>

void apply_diff(
	std::list<std::string>& input_text, 
	const std::list<Diff> & diff){ 
	//Iterators 
	std::list<std::string>::iterator input_iter = input_text.begin();
	std::list<Diff>::const_iterator diff_iter = diff.begin();
	
	//Used to calculate positions after edits, positive amount is shortened
	//Negative amount is lengthened
	int length_lost = 0;
	
	//looping over all edits
	while(diff_iter != diff.end()) {
		
		//Go to position of edit in input_text
		std::advance(input_iter, diff_iter->getPosition() - length_lost);
		
		//Performing EDITS
		if (diff_iter->getType() == EDIT::INSERT) {
			//insert at the position of input_iter
			input_text.insert(input_iter, diff_iter->getValue());
			length_lost--; //Decrement bc length + 1
		}
		
		else if (diff_iter->getType() == EDIT::ERASE) {
			//Erase at the position of input_iter
			input_text.erase(input_iter);
			length_lost++; //Increment bc length - 1
		}
		
		else if (diff_iter->getType() == EDIT::REPLACE) {
			//Delete current element and insert new in same place
			
			//Erase called within insert so that no temporary iterator is needed
			//To capture return value.
			input_text.insert( (input_text.erase(input_iter)) , diff_iter->getValue());
		}
		
		//Increment Diff list Iterator and reset input_iter
		input_iter = input_text.begin();
		diff_iter++;
	}
}

//MAIN.CPP VERSION - REFERENCE
std::list<Diff> invert_diff(
	std::list<std::string> & input,
	std::list<Diff> & diff) {
	//Inverts all inserts, erases, and replaces
	//Outputs the inverted of provided diff( to go back from output to input)

	//Iterators
	std::list<std::string>::iterator input_iter = input.begin();
	std::list<Diff>::iterator diff_iter = diff.begin();
	std::list<Diff> output;
	
	int times_erased = 0;
	int times_inserted = 0;

	while (diff_iter != diff.end()) {
		//Going to position of edit in input
		// if > 0, more inserts in reversed diff than erases,
		// if < 0, more erases in reversed diff than inserts
		int length_change = times_inserted - times_erased;
		int current_pos = diff_iter->getPosition() - length_change;

		/*std::cout
			<< diff_iter->getPosition() << ' '
			<< diff_iter->getType() << ' '
			<< diff_iter->getValue() << '\n';*/ //REMOVE LATER, FOR TESTING


			//INSERT A -> B = ERASE B -> A
		if (diff_iter->getType() == EDIT::INSERT) {
			//pushes_back new Dif object of the word that you erase from input
			output.push_back(Diff(current_pos, ERASE, ""));
			times_erased++;
		}

		//ERASE A -> B = INSERT B -> A
		else if (diff_iter->getType() == EDIT::ERASE) {
			std::advance(input_iter, diff_iter->getPosition());
			output.push_back(Diff(current_pos, INSERT, *input_iter));
			times_inserted++;
		}

		//REPLACE A -> B = REPLACE B -> A
		else if (diff_iter->getType() == EDIT::REPLACE) {
			std::advance(input_iter, diff_iter->getPosition());
			output.push_back(Diff(current_pos, REPLACE, *input_iter));
		}


		//std::cout << "Operation performed\n"; //REMOVE LATER

		//iterate over diff and reset input_iter
		diff_iter++;
		input_iter = input.begin();
	}
	return output;
}

//RENDER.CPP VERSION - CONST REFERENCE
std::list<Diff> invert_diff(
	const std::list<std::string>& input,
	const std::list<Diff>& diff) {
	//Inverts all inserts, erases, and replaces
	//Outputs the inverted of provided diff( to go back from output to input)

	//Iterators
	std::list<std::string>::const_iterator input_iter = input.begin();
	std::list<Diff>::const_iterator diff_iter = diff.begin();
	std::list<Diff> output;

	int times_erased = 0;
	int times_inserted = 0;

	while (diff_iter != diff.end()) {
		//Going to position of edit in input
		// if > 0, more inserts in reversed diff than erases,
		// if < 0, more erases in reversed diff than inserts
		int length_change = times_inserted - times_erased;
		int current_pos = diff_iter->getPosition() - length_change;

		/*std::cout
			<< diff_iter->getPosition() << ' '
			<< diff_iter->getType() << ' '
			<< diff_iter->getValue() << '\n';*/ //REMOVE LATER, FOR TESTING


			//INSERT A -> B = ERASE B -> A
		if (diff_iter->getType() == EDIT::INSERT) {
			//pushes_back new Dif object of the word that you erase from input
			output.push_back(Diff(current_pos, ERASE, ""));
			times_erased++;
		}

		//ERASE A -> B = INSERT B -> A
		else if (diff_iter->getType() == EDIT::ERASE) {
			std::advance(input_iter, diff_iter->getPosition());
			output.push_back(Diff(current_pos, INSERT, *input_iter));
			times_inserted++;
		}

		//REPLACE A -> B = REPLACE B -> A
		else if (diff_iter->getType() == EDIT::REPLACE) {
			std::advance(input_iter, diff_iter->getPosition());
			output.push_back(Diff(current_pos, REPLACE, *input_iter));
		}


		//std::cout << "Operation performed\n"; //REMOVE LATER

		//iterate over diff and reset input_iter
		diff_iter++;
		input_iter = input.begin();
	}
	return output;
}
	
std::list<Diff> compute_diff(
	const std::string& command,
	std::list<std::string>& list1,
	std::list<std::string>& list2) {

	// List of Diff objects
	std::list<Diff> output;

	// Creating Iterators for
	std::list<std::string>::iterator itr1 = list1.begin();
	std::list<std::string>::iterator itr2 = list2.begin();
	std::list<std::string>::iterator itr1_next = ++list1.begin();
	std::list<std::string>::iterator itr2_next = ++list2.begin();


	// Used for positioning of modifications
	int i1 = 0;
	int insert_c = 0; int erase_c = 0;

	while (itr1 != list1.end() || itr2 != list2.end()) {
		if (*itr1 != *itr2) {
			
			// Used for positioning also
			int current_pos = i1 - (insert_c - erase_c);
			if (*itr1_next == *itr2 || itr2 == list2.end()) {
				// Two cases for Erasure
				// 1. Next element of list1  == current element of list2
				// 2. List 2 at the end

				// Creating new Diff ERASE object
				output.push_back(Diff(current_pos, ERASE, ""));
			
				// Deleting *itr1 and reassignment
				itr1 = list1.erase(itr1);
				
				// Only increment next element list1 b/c length - 1
				itr1_next++;
				erase_c++;
			}
			else if (*itr1_next != *itr2_next || itr1 == list1.end() || *itr1 == *itr2_next) {
				// Multiple Cases for Insertion
				// 1. Next elements are unequal
				// 2. list1 at the end
				// 3. current element of list1 == next element of list 2

				// Creating new Diff INSERT object and
				// insertion into list1 of *itr2
				output.push_back(Diff(current_pos, INSERT, *itr2));
				list1.insert(itr1, *itr2);
				
				//Since length+1, increment itr2 and itr2_next, but not list1
				itr2++; itr2_next++;
				i1++;
				insert_c++;
			}
			else if (*itr1_next == *itr2_next) {
				// Case for Replacement
				// 1. The next two elements are equal
				
				// Creating new Diff REPLACE object and reassignment
				output.push_back(Diff(current_pos, REPLACE, *itr2));
				*itr1 = *itr2;
				
				//Increment all iterators and "index" since length unchanged
				itr1++; itr2++;
				itr1_next++; itr2_next++;
				i1++;
			}

		}
		else {
			//Increment all iterators and 'index' when elements equal
			itr1++; itr2++;
			itr1_next++;
			itr2_next++;
			i1++;
		}
	}
	
	//For compilation sakes, command used for extra credit
	if (command == "I didn't do the extra credit") {
		int extracredit = 0;
		extracredit += 0;
	}
	//Output
	return output;
}

bool assert_same(std::list<std::string> & list1,std::list<std::string>& list2) {
	// Compares lists of strings
	if (list1.size() == list2.size()) {
		std::list<std::string>::iterator itr1 = list1.begin();
		std::list<std::string>::iterator itr2 = list2.begin();
		while (itr1 != list1.end() && itr2 != list2.end()) {
			//loop over each item in list and compare
			if (*itr1 == *itr2) {
				//If strings identical
				itr1++; itr2++;
				continue;
			}
			return false;
		}
	}
	return list1.size() == list2.size();
	//Works bc will only get to here if uneven size or identical elements
}

bool assert_same_diff(std::list<Diff> & list1, std::list<Diff> & list2){
	//Compares lists of Diff objects by member variables.
	if (list1.size() == list2.size()) {
		std::list<Diff>::iterator itr1 = list1.begin();
		std::list<Diff>::iterator itr2 = list2.begin();

		while (itr1 != list1.end() && itr2 != list2.end()) {
			//loop over each item in list and compare
			if (
				itr1->getType() == itr2->getType() &&
				itr1->getPosition() == itr2->getPosition() &&
				itr1->getValue() == itr2->getValue()){
				//If all member variables are equal
				itr1++; itr2++;
				continue;
			}
			return false;
		}
	}
	return list1.size() == list2.size();
	//Works bc will only get to here if uneven size or identical elements
}