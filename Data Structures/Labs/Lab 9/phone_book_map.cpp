#include <iostream> 
#include <string>
#include <map>

void add(std::map<int,std::string>& phonebook, 
         int num, const std::string& name){
    phonebook[num] = name;
}

void identify(std::map<int,std::string>& phonebook,
              int number){
    if (phonebook.find(number) == phonebook.end())
        std::cout << "unknown caller!" << std::endl;
    else
        std::cout << phonebook[number] << " is calling!" << std::endl;
}

int main(){

    std::map<int, std::string> phonebook;

    // add several names to the phonebook
    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");

    // test the phonebook
    identify(phonebook, 2222);
    identify(phonebook, 4444);
}