#include <iostream>

using namespace std; 

//macros 
#define pi 3.141592
#define x(y) y*2+1
int main(){

  float f = 3*pi; 
  float k; 
  k = x(10); 
  cout << "k: "<<k << endl;
  cout << "F: "<<f << endl;
}