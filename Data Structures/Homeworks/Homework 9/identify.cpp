#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cmath>

#define EPSILON .05
#define distEPSILON .05

bool doubleEquals(double f1, double f2, double epsilon){
  return std::abs(f1 - f2) < epsilon;
}

class Star {
public:
  friend std::ostream& operator<<(std::ostream &os, const Star &st);
  friend bool operator==(const Star &l, const Star &r);

  bool nameChanged;
  double x;
  double y;
  double apparent_magnitude;
  std::string which_constellation;
  std::string name;
};

// Output formatting for stars
std::ostream& operator<<(std::ostream& os, const Star& st){
  os 
    << "Star" << std::setw(10) << std::right
    << st.x << std::setw(9) << std::right
    << st.y << std::setw(9) << std::right << std::fixed << std::setprecision(2)
    << st.apparent_magnitude << "  " 
    << std::setw(21) << std::left
    << st.which_constellation << std::setw(10) << std::left
    << st.name;
  return os;
}

// Equals operator for stars
bool operator==(const Star& l, const Star& r){
  return (doubleEquals(l.x,  r.x, EPSILON) && doubleEquals(l.y, r.y, EPSILON));
}

class Line {
public:
  friend std::ostream& operator<<(std::ostream& os, const Line& l);
  friend bool operator<(const Line &l, const Line &r);

  std::string which_constellation;
  std::string name_a;
  std::string name_b;
};

std::ostream& operator<<(std::ostream& os, const Line& l){
    os
      << "line   " << std::setw(21) << std::left
      << l.which_constellation << l.name_a << "   "
      << l.name_b;
    return os;
}

bool operator<(const Line &l, const Line &r){
  if (l.name_a > r.name_a)
    return false;
  else if (l.name_a < r.name_a)
    return true;
  else{
    if(l.name_b > r.name_b)
      return false;
    else if(l.name_b < r.name_b)
      return true;
  }
  return false;
}

// Typedef for screen space
typedef std::unordered_map<double, std::pair<Star, Star> > starHash;

// Simple helper function for euclidean distance in R2
double distance(double x1, double y1, double x2, double y2){
  return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Helper function that reads in all constellations 
// and hashes their star combinations by distance
void hashByDist(starHash & star_distances, 
                const std::vector<std::string> & constellations, 
                std::vector<Line> & line_data){

  for (int i = 0; i < int(constellations.size()); ++i){
    std::vector<Star> star_data;
    std::unordered_map<std::string, Star> stars;
    std::ifstream istr(constellations[i]);
    assert(istr.good());

    // Load input constellation data for current file
    std::string token;
    while(istr >> token){
      // read in stars
      if(token == "star"){
        Star st;
        istr >> st.x >> st.y >> st.apparent_magnitude >> st.which_constellation >> st.name;
        star_data.push_back(st);
        stars.insert(std::make_pair(st.name, st));
      }
      // read in lines
      else if (token  == "line"){
        Line ln;
        istr >> ln.which_constellation >> ln.name_a >> ln.name_b;
        line_data.push_back(ln);
      }
      // formatting check
      else{
        assert(0);
      }
    }

    std::cout << "Constellation Size =" << star_data.size() << '\n';
    for (int i = 0; i < int(line_data.size()); ++i){
      Star star1 = stars[line_data[i].name_a];
      Star star2 = stars[line_data[i].name_b];

      double dist = distance(star1.x, star1.y, star2.x, star2.y);
      star_distances.insert(std::make_pair(dist, std::make_pair(star1, star2)));
    }

    starHash::const_iterator itr = star_distances.begin();
    while(itr != star_distances.end()){
      std::cout << "Hashed Pair: " << itr->first << "\nStar1: " << itr->second.first << "\nStar2: " << itr->second.second << '\n';
      itr++;
    }
    std::cout << '\n';

    // // Create combinations of stars for current constellation, and hash by their distances
    // for (unsigned int j = 0; j < star_data.size(); ++j){
    //   for (unsigned int k = 0; k < star_data.size(); ++k){
    //     if(k == j)
    //       continue;
    //     // k ranges from j+1-end, since all pairwise combinations results in a  
    //     // duplicate for every pair if (a,b) gives same distance as (b,a). Range 
    //     // leads to upper right triangle of matrix of combinations. Also no (j,j). 
        
    //     double dist = distance(star_data[j].x, star_data[j].y, star_data[k].x, star_data[k].y);
    //     // hash by euclidean distance
    //     star_distances.insert(std::make_pair(dist, std::make_pair(star_data[j], star_data[k])));
    //   }
    // }
  }
}

// Helper function to print pairs hased by distance
void printPairs(const starHash & star_distances){
  starHash::const_iterator itr = star_distances.begin();
  while(itr != star_distances.end()){
    std::cout 
      << "Pair : " << itr->first << '\n'
      << itr->second.first << '\n' 
      << itr->second.second << '\n';
    itr++;
  }
}

// Helper function to read input stars
void readStars(std::vector<Star> & inStars, const std::string& in){
  std::ifstream istr(in);
  assert(istr.good());

  std::string token;
  while(istr >> token){
    if(token == "star"){
      Star st;
      istr >> st.x >> st.y >> st.apparent_magnitude >> st.which_constellation >> st.name;
      st.nameChanged = false;
      inStars.push_back(st);
    }
    else
      assert(0);
  }
}

void assignLine(const Star& star1, const Star& star2, 
                const std::vector<Line>& line_data, std::vector<Line> &new_lines){
  for (int i = 0; i < int(line_data.size()); ++i){
    if (star1.name == line_data[i].name_a && star2.name == line_data[i].name_b)
      new_lines.push_back(line_data[i]);
  }
}

bool equalRotationPoint(const Star& stara, const Star& starb, const Star& star1, const Star& star2){
  
  std::cout << "Testing (" << stara.name << ":" << star1.name << "," << starb.name << ',' << star2.name << ")\n";
  // Midpoints between pairs
  std::pair<double, double> M_a1 = std::make_pair((stara.x + star1.x) / 2, (stara.y + star1.y) / 2);
  std::pair<double, double> M_b2 = std::make_pair((starb.x + star2.x) / 2, (starb.y + star2.y) / 2);

  // Slope of perpendicular bisectors (opposite reciprocal of slope of pairs)
  double S_a1 = (stara.y - star1.y) / (stara.x - star1.x);
  S_a1 = -1 / S_a1;
  double S_b2 = (starb.y - star2.y) / (starb.x - star2.x);
  S_b2 = -1 / S_b2;
  // M.y = S*M.x + b so b = M.y - S*M.x
  double b_a1 = M_a1.second - S_a1 * M_a1.first;
  double b_b2 = M_b2.second - S_b2 * M_b2.first;
  
  // y = m1x + b1 = m2x + b2 so x = (b2-b1)/(m1-m2)

  // Coordinates of intersection of perdendicular bisectors
  double x = (b_b2 - b_a1) / (S_a1 - S_b2);
  double y = S_a1 * x + b_a1;
  std::cout << "Intersection = (" << x << "," << y << ")\n";

  // Compare distance of a and 1 from intersection
  double dist1 = distance(stara.x, stara.y, x, y);
  double dist2 = distance(star1.x, star1.y, x, y);
  std::cout << "dist(" << stara.name << ",I) = " << dist1 << ", dist(" << star1.name << ",I) = " << dist2 << '\n';

  if(!doubleEquals(dist1,dist2, distEPSILON))
    return false;

  dist1 = distance(starb.x, starb.y, x, y);
  dist2 = distance(star2.x, star2.y, x, y);
  std::cout << "dist(" << starb.name << ",I) = " << dist1 << ", dist(" << star2.name << ",I) = " << dist2 << '\n';

  if(!doubleEquals(dist1,dist2, distEPSILON))
    return false;

  // Correct Pair
  return true;
}

void matchConstellations(std::vector<Star>& inStars, const starHash& star_distances ,
                         const std::vector<Line> & line_data, std::vector<Line> & new_lines){
  
  for (int i = 0; i < int(inStars.size()); ++i){
    for (int j = i+1; j < int(inStars.size()); ++j){

      Star star1 = inStars[i];
      Star star2 = inStars[j];
      double dist = distance(star1.x, star1.y, star2.x, star2.y);
      starHash::const_iterator itr = star_distances.begin();
      while(itr != star_distances.end()){
        if(doubleEquals(dist, itr->first, EPSILON))
          break;
        else
          itr++;
      }

      // Star combination not in given constellation
      if(itr == star_distances.end())
        continue;   

      std::cout << "Map Pair: Dist " << itr->first << '\n'
                << "Stara : " << itr->second.first << '\n'
                << "Starb : " << itr->second.second << '\n';
      std::cout << "dist = " << dist << '\n';
      std::cout << "star1 : " << star1 << '\n'
                << "star2 : " << star2 << "\n\n";

      Star stara = itr->second.first;
      Star starb = itr->second.second;

      // Updating member variables of star1 and star2
      // Two possible orders in pair so check both

      // Find point of rotation (creates third point)
      // Two possible points (two permutations of stara,starb,star1,star2)
      // Uses third point to calculate distance, and matching if distance
      // to rotation point is equal between pairs. 

      // First permutation a:1 and b:2 
      // Second permutation a:2 and b:1

      if(equalRotationPoint(stara,starb,star1,star2)) {
        std::cout << "PAIR FOUND A1 B2 \n\n";
        star1.name = stara.name;
        star1.which_constellation = stara.which_constellation;
        star1.apparent_magnitude = stara.apparent_magnitude;

        star2.name = starb.name;
        star2.which_constellation = starb.which_constellation;
        star2.apparent_magnitude = starb.apparent_magnitude;
        star1.nameChanged = star2.nameChanged = true;

        assignLine(star1, star2, line_data, new_lines);
      } 
      else if(equalRotationPoint(stara,starb,star2,star1)){
        // Pair found so update variables
        std::cout << "PAIR FOUND A2 B1 TEST\n\n";
        star1.name = starb.name;
        star1.which_constellation = starb.which_constellation;
        star1.apparent_magnitude = starb.apparent_magnitude;

        star2.name = stara.name;
        star2.which_constellation = stara.which_constellation;
        star2.apparent_magnitude = stara.apparent_magnitude;
        star1.nameChanged = star2.nameChanged = true;
        
        assignLine(star2, star1, line_data, new_lines);
      } 

      inStars[i] = star1;
      inStars[j] = star2;
    }
  }

} 

void fileOutput(const std::vector<Star> inStars, std::vector<Line>& lines,
                const std::string& out){
  std::ofstream ostr(out);
  assert(ostr.good());

  for (int i = 0; i < int(inStars.size()); ++i){
    ostr << "Star" << std::setw(10) << std::right
         << inStars[i].x << std::setw(9) << std::right
         << inStars[i].y << std::setw(9) << std::right << std::fixed << std::setprecision(2)
         << inStars[i].apparent_magnitude << "  "
         << std::setw(21) << std::left
         << inStars[i].which_constellation << std::setw(10) << std::left
         << inStars[i].name << '\n';
  }

  std::sort(lines.begin(), lines.end());

  for (int i = 0; i < int(lines.size()); ++i) {
    ostr << lines[i] << '\n';
  }
}

int main(int argc, char *argv[]){

  // Set Up 
  // ------------------------------------------------------------------
  assert(argc >= 3);
  std::string in, out;
  std::vector<std::string> constellations;
  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string("-i") && i < argc) {
      in = argv[i + 1];
    } else if (argv[i] == std::string("-o") && i < argc) {
      out = argv[i + 1];
    } else if (argv[i] == std::string("-l") && i < argc) {
      constellations.push_back(std::string(argv[i + 1]));
    }
  }

  // Creating the hashmap of star distances
  // ------------------------------------------------------------------
  starHash star_distances;
  std::vector<Line> line_data;
  hashByDist(star_distances, constellations, line_data);

  // Reading in input file stars
  // ------------------------------------------------------------------
  std::vector<Star> inStars;
  readStars(inStars, in);

  // Main heavy lifting code
  // ------------------------------------------------------------------

  // Consetllation Match
  std::vector<Line> new_lines;
  matchConstellations(inStars, star_distances, line_data, new_lines);

  // File Output
  fileOutput(inStars, new_lines, out);
}