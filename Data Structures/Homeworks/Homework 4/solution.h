#ifndef __solution_h
#define __solution_h

#include "diff.h"
#include "input_output.h"
#include "render.h"
#include <list>
#include <string>

//Uses Diff File to modify text to desired output
void apply_diff(std::list<std::string> & input_text,const std::list<Diff> & diff);

//Uses Diff file and original text to find inverse of provided Diff file
//MAIN.CPP VERS
std::list<Diff> invert_diff(std::list<std::string> & input ,std::list<Diff> &  diff);
//RENDER.CPP VERS
std::list<Diff> invert_diff(const std::list<std::string>& input,const std::list<Diff>& diff);


//Creates a Diff file of changes needed to modify list1 into list2
std::list<Diff> compute_diff(const std::string& command, std::list<std::string> & list1, std::list<std::string> & list2);

//Returns when the two lists of string are identical
bool assert_same(std::list<std::string> & list1 , std::list<std::string>& list2);

//Returns when two lists of Diff are the same
bool assert_same_diff(std::list<Diff>& list1, std::list<Diff>& list2);
#endif