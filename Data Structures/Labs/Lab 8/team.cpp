#include <cassert>
#include "superhero.h"
#include "team.h"

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

void Team::operator+=(const Superhero &a){
  superheroes.push_back(a);
}

void Team::operator-=(const Superhero &a){
  std::list<Superhero>::iterator itr = superheroes.begin();
  while (itr != superheroes.end()){
    if (itr->getName() == a.getName() &&
        itr->getPower() == a.getPower() &&
        itr->getTrueIdentity() == a.getTrueIdentity()){
      superheroes.erase(itr);
      return;
    }
    itr++;
  }
}

Team operator+(const Team& t1,const Team& t2){
  Team temp(t1);
  std::list<Superhero>::const_iterator itr = t2.getTeam().begin();
  while(itr != t2.getTeam().end()){
    temp + *itr;

  }
}

Team operator+(const Team& t, const Superhero& s){
  Team temp(t);
  temp.getTeam().push_back(s);
  std::string temps = temp.getName();
  temp.setName(s.getName());
  return temp;
}

void Team::setName(const std::string& s){
  if(s.length() >= 2){
    teamname += tolower(s[0]) + tolower(s[1]);
  }

}