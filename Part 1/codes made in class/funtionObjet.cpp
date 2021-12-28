#include <iostream>

using namespace std; 
//funtion objet es una operacion simple almaacenada dentro de un objeto 
/*
struct CLess{
	bool menor(int a, int b){
		return a<b; 
	}

};

struct CGreater{
	bool mayor(int a, int b){
		return a>b; 
	}

};*/

template<class T>
struct CLess{
	inline bool operator()(T a, T b){
		return a < b;
	}
};

template<class T>
struct CGreater{
	inline bool operator()(T a, T b){ //con el inline se va a comportar como una macro 
		return a > b;
	}
};

int main(){

	CLess<int> l; 
	int x = 3, y = 7; 
	if(l(x,y)) // llamamos a la funcion de comparacion con sus parametros 
		cout << x << endl; 
	else 
		cout << y << endl; 

	/*
	int x = 3, y = 7; 
	if(l.menor(x,y)) // llamamos a la funcion de comparacion con sus parametros 
		cout << x << endl; 
	else 
		cout << y << endl; 	*/
	/*
	if(x<y)
		cout << x << endl; 
	else 
		cout << y << endl;*/	
}