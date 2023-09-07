#include <iostream>
#include <string>

void rotate(std::string &s1, std::string &s2, std::string &s3, std::string &s4){
    std::string temp = s1;
    std::string temp2;
    s1 = s4;
    
    temp2 = s2;
    s2 = temp;
    temp = s2;

    temp = s3;
    s3 = temp2;
    temp2 = s3;

    s4 = temp;
}
void rotateInverse(std::string &s1, std::string &s2, std::string &s3, std::string &s4)
{
    std::string temp = s1;
    std::string temp2;
    s1 = s2;

    temp2 = s4;
    s4 = temp;
    temp = s4;

    temp = s3;
    s3 = temp2;
    temp2 = s3;

    s2 = temp;
}

    int main()
{
    std::string s1, s2, s3, s4;
    s1 = "north";
    s2 = "east";
    s3 = "south";
    s4 = "west";

    std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << '\n';
    rotate(s1, s2, s3, s4);
    std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << '\n';
    rotateInverse(s1, s2, s3, s4);
    std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << '\n';
}
