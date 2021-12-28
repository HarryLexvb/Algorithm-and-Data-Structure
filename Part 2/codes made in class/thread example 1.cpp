
#include <iostream>
#include <thread>

using namespace std;

void F1(char c, int n)
{
    for ( int i = 0; i < n; i++ )
        cout<<c;
}

int main()
{
    thread t(F1,'c',50); ///pasamos por parametro la funcion, dato 1, dato 2
    
    t.join(); /// se pone al finalizar la thread 
    
    cout<<"\n";
}
