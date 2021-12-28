#include <iostream>
#include <list>

struct CFd1{ // funcion de dispersion 1 

	inline unsigned long operator()(int x){
		return x+1; 
	}
};

template<class T, class S, class Fd, unsigned long Sz> 
class CHashTable{
public: 

	CHashTable();
	~CHashTable(); 
	bool Find(T v);  /// find function 
	bool Ins(T v);  /// insert function
	bool Rem(T v);  /// remove function 

	S *table; 
	Fd fd; 
};

template<class T, class S, class Fd, unsigned long Sz> 
CHashTable<T, S, Fd, Sz>::CHashTable(){

	table = new S[Sz]; 

}

template<class T, class S, class Fd, unsigned long Sz> 
CHashTable<T, S, Fd, Sz>::~CHashTable(){

	delete[] table; 
	
}

template<class T, class S, class Fd, unsigned long Sz> 
bool CHashTable<T, S, Fd, Sz>::Find(T v){
	 
	 
}

template<class T, class S, class Fd, unsigned long Sz> 
bool CHashTable<T, S, Fd, Sz>::Ins(T v){

	/*
	unsigned long id = fd(v)%Sz; 
	table[id].push_back(v); */
	table[fd(v)%Sz].push_back(v);

	return 1; 	
}

template<class T, class S, class Fd, unsigned long Sz> 
bool CHashTable<T, S, Fd, Sz>::Rem(T v){
	table[fd(v)%Sz].remove(v);
	return 0; 
}

int main(){

	/*
	Sz : tamaño 
	Fd: funcion de dispersion 
	*/
	CHashTable<int, std::list<int>, CFd1, 7> ht; 
	ht.ins(11);
	ht.ins(8);
	ht.ins(4);
	ht.ins(9);
	//ht.find(9);
}