#include <iostream>
#include <math.h>
#include <random>
#include <utility>

using point = std::pair<float, float>; 

bool is_in_circle(point pt) {
  
  point temp( std::pow(pt.first, 2), std::pow(pt.second, 2) ); 
  return ( std::sqrt(temp.first) + std::sqrt(temp.second) ) < 1;
}

int main() {
  
  std::random_device rd;                     
  std::mt19937 gen(rd());                   
  std::uniform_int_distribution<> distrib(-100, 100);  

  point pt(distrib(gen),distrib(gen)); 
  std::cout << "point: " << pt.first << ' ' << pt.second << "is: " << is_in_circle(pt) << '\n';

}
