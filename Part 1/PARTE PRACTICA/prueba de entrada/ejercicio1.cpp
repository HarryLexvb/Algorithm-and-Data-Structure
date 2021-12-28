#include <iostream>

using namespace std;

int menor(char *a, char *b){

    int lena = 0, lenb = 0; 
    while (*a++){
        lena++;      
    }
    while (*b++){
        lenb++;      
    }
    
    if(lena < lenb) return 1; 
    else if(lenb < lena) return 2;
    else if(lena == lenb) return 0; 
 
}

int main() {
  
  char A[3][100] = { "Anastasia","anastasia","anabel"};

  cout<<"frase 1: "<<A[0]<<endl;
  cout<<"frase 2: "<<A[1]<<endl;
  cout<<"La frase menor es "<<menor(A[0],A[1])<<endl<<endl;

  cout<<"frase 1: "<<A[1]<<endl;
  cout<<"frase 2: "<<A[2]<<endl;
  cout<<"La frase menor es "<<menor(A[1],A[2])<<endl<<endl;

  cout<<"frase 1: "<<A[0]<<endl;
  cout<<"frase 2: "<<A[1]<<endl;
  cout<<"La frase menor es "<<menor(A[0],A[1])<<endl<<endl;

  
  return 0;
    
}