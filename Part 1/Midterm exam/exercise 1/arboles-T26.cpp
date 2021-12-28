#include<iostream>
#include<new>
#include<unistd.h>
#include<sstream>
#include<string>

#ifdef __WIN23
#define clear "cls"
#elif defined(unix) or defined(__unix) or defined(__unix__) or defined(__APPLE__) or defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado"
#endif

using namespace std;

struct Nodo{
     int dato;
     Nodo *izq;
     Nodo *der;
};

Nodo *crearArbol(int dato){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;
    return nuevo_nodo;
}

void agregarArbol(Nodo *&arbol,int dato){
    if(arbol == NULL){
       Nodo *nuevo_nodo = new Nodo();
       nuevo_nodo = arbol;
    }
    else{
       int valor_raiz = arbol->dato;
       if(dato < valor_raiz){
          agregarArbol(arbol->izq,dato);
       }else{
          agregarArbol(arbol->der,dato);
       }
    }
    cout<<"\n\n el elemento "<<dato<<" se ha agregado correctamente en el arbol ...\n\n";

}

void mostrarArbol(Nodo *arbol,int contador){
    if(arbol == NULL){
       return;
    }
    else{
        mostrarArbol(arbol->der,contador+1);
        for(int i=0;i<contador;i++){
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq,contador+1);
    }
}

void menu(){
    Nodo *arbol = nullptr;
    int dato;
    int opciones;
    int contador = 0;
    string aux;

    do{  

        cout<<"\n\n\n                                     ..::MENU::..\n\n\n";  
        cout<<"1. agregar elementos a arbol .\n\n";
        cout<<"2. mostrar arbol .\n\n";
        cout<<"3. salir . \n\n";
        cout<<"\n                                                  :: ";getline(cin,aux);
        stringstream(aux)>>opciones;
        system(CLEAR);
        switch(opciones){
              case 1:
                     cout<<"\n\n\n\n-----------------------------------------\n\n\n\n";
                     cout<<"elemento : ";cin>>dato;
                     agregarArbol(arbol,dato);
                     sleep(2);
                     break;

              case 2:
                     cout<<"\n\n---------------------------------------------------------\n\n";
                     mostrarArbol(arbol,contador);
                     cout<<"\n\n---------------------------------------------------------\n\n";
                     sleep(5);
                     break;                 
              default : break;
        }
        system(CLEAR);
    }while(opciones not_eq 3);
    
}

int main(){
    
    Nodo *arbol = nullptr;
    int dato;
    int opciones;
    int contador = 0;
    string aux;
    do{  
         
        inicio:
        cout<<"\n\n\n                                     ..::MENU::..\n\n\n";  
        cout<<"1. agregar elementos a arbol .\n\n";
        cout<<"2. mostrar arbol .\n\n";
        cout<<"3. salir . \n\n";
        cout<<"\n                                                  :: ";opciones;//getline(cin,aux);
        //stringstream(aux)>>opciones;
        system(CLEAR);
        switch(opciones){
              case 1:
                     cout<<"\n\n\n\n-----------------------------------------\n\n\n\n";
                     cout<<"elemento : ";cin>>dato;
                     goto inicio;
                     agregarArbol(arbol,dato);
                     sleep(2);
                     break;

              case 2:
                     cout<<"\n\n---------------------------------------------------------\n\n";
                     mostrarArbol(arbol,contador);
                     cout<<"\n\n---------------------------------------------------------\n\n";
                     sleep(5);
                     break;                 
              default : break;
        }
        system(CLEAR);
    }while(opciones not_eq 3);
    


    return 0;
}