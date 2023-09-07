#include <map>
#include <set>
#include <vector>
#include <iostream>

int main(){
    std::map<int, int> count;
    std::vector<int> sequence;
    sequence.push_back(1);
    sequence.push_back(1);
    sequence.push_back(1);
    sequence.push_back(4);
    sequence.push_back(3);
    sequence.push_back(3);
    sequence.push_back(6);
    sequence.push_back(3);

    for (int i = 0; i < sequence.size();i++){
        bool inserted = count.insert(std::pair<int, int>(sequence[i], 1)).second;
        if(!inserted){
            std::map<int, int>::iterator itr_m = count.find(sequence[i]);
            itr_m->second += 1;
        }
    }

    std::cout << "Mode(s): ";
    std::map<int, int>::iterator itr = count.begin();
    int max = itr->second;
    int current = itr->second;
    while(itr != count.end()){
        current = itr->second;
        if(current == max)
            std::cout << "(" << itr->first << "," << itr->second << ") ";
        itr++;
    }

    return 0;
}