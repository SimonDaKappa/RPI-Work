#include <iostream>
#include <string>
#include <algorithm>

int main(){

    std::string s = "uncopyrightable";
    std::sort(s.begin(),s.end());
    std::cout << s << std::endl;
}