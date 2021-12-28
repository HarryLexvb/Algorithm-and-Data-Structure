
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(char c, int n)
{
    for ( int i = 0; i < n; i++ )
        cout<<c<<endl;
}

int main()
{
    int i = 0, nThreads = thread::hardware_concurrency(); 
    ///thread::hardware_concurrency(); ---> retorna el numero de nucleos que  tengo en mi maquina 
    vector<thread> ths(nThreads); ///array de threads   

    for ( i = 0; i < nThreads; i++ )
        ths[i] = thread(F1, char('a'+i), 100);

    for ( i = 0; i < nThreads; i++ )
        ths[i].join();

    cout<<"\n";
}


