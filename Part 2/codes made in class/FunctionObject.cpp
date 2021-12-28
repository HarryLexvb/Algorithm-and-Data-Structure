#include <iostream>

using namespace std; 

/*
struct Cless{
    bool cmp(int a, int b){
      return a<b; 
    }
};
struct Cgreater{
    bool cmp(int a, int b){
      return a>b; 
    }
};*/

///sobre carga de operadores 
template <class T>
struct Cless{
    bool operator()(T a, T b){
      return a<b; 
    }
};
template <class T>
struct Cgreater{
    bool operator()(T a, T b){
      return a>b; 
    }
};

int main(){
/*  Cless l; 
  int x = 3, y = 7; 
  if(l.cmp(x, y))
    cout << x; 
  else 
  cout << y; */

  /*Cgreater g; 
  int x = 3, y = 7;
  if(g.cmp(x, y))
    cout << x; 
  else 
  cout << y; */

  //xobrecarga de operadores
  Cgreater<int> g; 
  int x = 3, y = 7;
  if(g(x, y))
    cout << x; 
  else 
  cout << y;
  
}