#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>
#include <utility>

#include "image.h"
#include "priority_queue.h"

#define infinity 1e10

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double distance(double x1, double y1, double x2, double y2){
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++) {
        for (int j2 = 0; j2 < h; j2++){
          const Color &c = input.GetPixel(i2, j2);
          // skip all pixels that are not black
          if (!c.isBlack())
            continue;
          // calculate the distance between the two pixels
          double distance = sqrt((i - i2) * (i - i2) + (j - j2) * (j - j2));
          // store the closest distance to a black pixel
          if (closest < 0 || distance < closest) {
            closest = distance;
          }
        }
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setX(i);
      p.setY(j);
      p.setValue(closest);
    }
  }
  return answer;
}

double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  //
  // IMPLEMENT THIS FUNCTION
  //
  // a small improvement on the NaiveDistanceFieldMethod
  //

  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;

  // First grab all black pixels and put in list, so o(1) push_back
  std::list<std::pair<int, int>> black_pixels;
  for (int i = 0; i < w;++i){
    for (int j = 0; j < h; ++j){
      const Color &c = input.GetPixel(i, j);
      if(c.isBlack()){
        black_pixels.push_back(std::make_pair(i, j));
        DistancePixel &p = distance_image.GetPixel(i, j);
        p.setValue(-1);
      }
    }
  }
  // Now loop over image again
  for (int i = 0; i < w; ++i){
    for (int j = 0; j < h; ++j){
      double closest = -1;
      const Color &c = input.GetPixel(i, j);
      if (c.isBlack())
        continue;
      else{
        std::list<std::pair<int, int>>::iterator itr = black_pixels.begin();
        for (; itr != black_pixels.end(); itr++) {
          double distance = sqrt((i - itr->first) * (i - itr->first) + (j - itr->second) * (j - itr->second));
          if (closest < 0 || distance < closest){
            closest = distance;
          }
        }
        assert(closest >= 0);
        answer = std::max(answer, closest);
        // save the data to the distance image
        DistancePixel &p = distance_image.GetPixel(i, j);
        p.setX(i);
        p.setY(j);
        p.setValue(closest);
      }
    }
  }
  return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  // ----------------------------------------------------------------------------------

  double max_dist = -1;
  // First Step - Collect all black pixels and initialize distance field
  // to 0 for them and initialize distance value of nonblack to infinity (1e10)
  int w = input.Width();
  int h = input.Height();
  DistancePixel_PriorityQueue queue;
  for (int i = 0; i < w; ++i){
    for (int j = 0; j < h; ++j){
      DistancePixel &dp = distance_image.GetPixel(j, i);
      dp.setX(i);
      dp.setY(j);
      dp = distance_image.GetPixel(j, i);
      std::cout << "dp (x,y) =(" << dp.getX() << ',' << dp.getY() << ")\n";
      const Color &c = input.GetPixel(j, i);
      // set values of black pixels to known and 0, add to list
      if (c.isBlack()){
        std::cout << "is black\n";
        dp.setValue(0);
        dp.setKnown(true);
        queue.push(&dp);
      } else{
        dp.setValue(infinity);
      }
    }
  }
  std::cout << "\nBlack pixels found\n\n";

  // ----------------------------------------------------------------------------------
  while(queue.size() > 0){
    const DistancePixel *p = queue.top();
    std::cout << "\n\np (x,y) = (" << p->getX() << ',' << p->getY() << ")\t";
    std::cout << "P value = " << p->getValue() << "\n";
    for (int j = -1; j <= 1; j++) {
      for (int i = -1; i <= 1; i++) {
        // out of bounds and self check
        if (i == 0 && j == 0){
           std::cout << "skipped 00\n";
          continue;
        }
        if (p->getX() + i < 0 || p->getX() + i > h){
           std::cout << "skipped Xi\n";
          continue;
        }
        if (p->getY() + j < 0 || p->getY() + j > w){
           std::cout << "skipped Yj\n";
          continue;
        }
        DistancePixel &dp = distance_image.GetPixel(p->getY() + j, p->getX() + i);
        if(dp.isKnown())
          continue;
        
        // else propogate distance
        // two cases: value = infinity or value < infinity
        double propagation_distance = p->getValue() + distance(p->getX(), p->getY(), p->getX() + i, p->getY() + j);
        std::cout << "(" << p->getX() << ',' << p->getY() << "), (" << p->getX() + i << ',' << p->getY() + j << ")\n";
        if (dp.getValue() < infinity / 10) { // already in queue
          if(dp.getValue() > p->getValue() + propagation_distance){
            dp.setValue(p->getValue() + propagation_distance);
            queue.update_position(&dp);
          }
        }
        else {
          std::cout << "Adding new pixel : " << dp << '\n';
          if(dp.getValue() > p->getValue() + propagation_distance){
            dp.setValue(p->getValue() + propagation_distance);
            std::cout << "Adding pixel above ( value updated )): " << dp << '\n';
            queue.push(&dp);
            std::cout << "Top of queue after push :" << *(queue.top()) << '\n';
          }
        }
        

        std::cout << "dp (x,y) = (" << dp.getX() << ',' << dp.getY() << ")\t";
        std::cout << "dP value = " << dp.getValue() << "\n\n";
      }
    }
    DistancePixel &p_2 = distance_image.GetPixel(p->getX(), p->getY());
    std::cout << "p_2 (x,y) = (" << p_2.getX() << ',' << p_2.getY() << ")\t"; 
    p_2.setKnown(true);
    queue.pop();
    std::cout << "Top of queue after pop :" << *(queue.top()) << '\n';

  }
  return max_dist;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
