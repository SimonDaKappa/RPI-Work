#include <iostream>
#include <string>
#include <map>
#include <list>
#include <cassert>

      // std::map<costume_name, std::pair<total_stock, std::list<last,first> > >
      // size of list = amount rented
typedef std::map<std::string, std::pair<int, std::list<std::pair<std::string, std::string> > > > COSTUME_SHOP_TYPE;
      // std::map<std::pair<last_name, first_name>, costume_name>
typedef std::map<std::pair<std::string, std::string>, std::string > PEOPLE_TYPE;

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(PEOPLE_TYPE& people);

int main() {
  // two data structures store all of the information for efficiency
  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addCostume(costume_shop);
    } else if (c == 'r') {
      rentCostume(costume_shop,people);
    } else if (c == 'l') {
      lookup(costume_shop);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
  std::string costume_name;
  int num;
  std::cin >> costume_name >> num;
  // New addition to shop (initial stock)
  if(costume_shop.find(costume_name) == costume_shop.end()){
    std::list<std::pair<std::string,std::string> > customers;
    std::pair<int, std::list< std::pair<std::string, std::string> > > new_costume(num, customers);
    costume_shop[costume_name] = new_costume;
  } 
  // Costume already sold by store (add stock)
  else{
    costume_shop[costume_name].first += num;
  }

  std::cout << "Added " << num << " " << costume_name;
  if(num > 1 ) std::cout << " costumes.\n";
  else std::cout << " costume.\n";


}

void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
  std::string first_name;  
  std::string last_name;
  std::string costume_name;
  std::cin >> first_name >> last_name >> costume_name;

  // Used Numerous times to minimize size of lines
  std::pair<std::string, std::string> p(last_name, first_name);

  // Does Costume exist?
  if(costume_shop.find(costume_name) == costume_shop.end()){
    std::cout << "The shop doesn't carry " << costume_name << " costumes.\n";
    // If first time costumer
    if(people.find(p) == people.end()){
      // Register customer with empty purchase ("" string)
      people[p] = "";
    }
    // If not first time customer leave
    // current rented costume unchanged
    return;
  }
  // Does Shop have no stock? (stock - rented == 0)
  if(costume_shop[costume_name].first - costume_shop[costume_name].second.size() == 0  ){
    std::cout << "No " << costume_name << " costumes available.\n";
    // If first time costumer
    if(people.find(p) == people.end()){
      // Register customer with empty purchase ("" string)
      people[p] = "";
    }
    // If not first time customer leave
    // current rented costume unchanged
    return;
  }
  
  // First time customer
  if (people.find(p) == people.end()){
    // Register customer with purchase
    people[p] = costume_name;

    costume_shop[costume_name].second.push_back(p);
    std::cout << first_name << " " << last_name << " rents a "
              << costume_name << " costume.\n";
    return;
  }
  // Return Customer but already renting this costume
  if(people[p] == costume_name){
    std::cout << first_name << ' ' << last_name << " already has a "
              << costume_name << " costume.\n";
    return;
  }
  // Return Customer but currently renting a different costume
  if(people[p] != ""){
    std::cout << first_name << " " << last_name << " returns a "
              << people[p] << " costume before renting a "
              << costume_name << " costume.\n";
    // Iterator that points to first element of list of customers renting the old costume
    std::list<std::pair<std::string, std::string> >::iterator itr = costume_shop[people[p]].second.begin();
    // Looping until we find the current customer in old customer list
    while(itr != costume_shop[people[p]].second.end() && *itr != p){
      itr++;
    }
    // Erasing existing costume
    costume_shop[people[p]].second.erase(itr);
    // Adding new costume renting to stores side
    costume_shop[costume_name].second.push_back(p);
    people[p] = costume_name;
    return;
  }
  // Return Customer and not renting any costume currently
  else if(people[p] == ""){
    costume_shop[costume_name].second.push_back(p);
    people[p] = costume_name;
    std::cout << first_name << " " << last_name << " rents a "
              << costume_name << " costume.\n";
    return;
  }
}

void lookup(COSTUME_SHOP_TYPE& costume_shop) {
  std::string costume_name;
  std::cin >> costume_name;

  // Does not Carry costume
  if(costume_shop.find(costume_name) == costume_shop.end()){
    std::cout << "The shop doesn't carry " << costume_name << " costumes.\n";
    return;
  }

  // Helpful variables
  std::pair<int, std::list<std::pair<std::string, std::string> > > costume = costume_shop[costume_name];
  int total_inventory = costume.first;
  std::list<std::pair< std::string, std::string> > renters = costume.second;

  std::cout << "Shop info for " << costume_name << " costumes:\n";

  // Costumes Available
  if (total_inventory - renters.size() > 0){
    std::cout << "  " << total_inventory - renters.size();
    if(total_inventory - renters.size() == 1)
      std::cout << " copy";
    else
      std::cout << " copies";
    std::cout << " available\n";
  }
  // At least one renter
  if (renters.size() > 0){
    // Formatted output
    std::cout << "  " << renters.size();
    if(renters.size() == 1)
      std::cout << " copy";
    else
      std::cout << " copies";
    std::cout << " rented by:\n";

    // Print out current renters
    std::list<std::pair<std::string, std::string> >::iterator itr = renters.begin();
    while(itr != renters.end()){
      std::cout << "    " <<  itr->second << ' ' << itr->first << '\n';
      itr++;
    }
  }
}

void printPeople(PEOPLE_TYPE& people) {
  std::map<std::pair<std::string, std::string>, std::string>::iterator itr = people.begin();

  std::cout << "Costume info for the " << people.size() << " party ";
  if(people.size() == 1)
    std::cout << "attendee:\n";
  else
    std::cout << "attendees:\n";
  
  while(itr != people.end()){
    // Syntax is a little wonky. ->first is the pair<string,string> 
    // and .second is the first name,
    // similarly, .first is the last name
    std::cout << "  " << itr->first.second << " " << itr->first.first;

    if(itr->second == ""){
      std::cout << " does not have a costume.\n";
    }
    else{
      std::cout << " is wearing a " << itr->second << " costume.\n";
    }
    itr++;
  }
}
