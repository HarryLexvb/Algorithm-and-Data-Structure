#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex m;
long sum = 0;

void F1(int x, int n)
{
    for ( int i = 0; i < n; i++ )
    {
        m.lock(); ///sera como el semanaforo para que tenga coherencia el resultado 
        sum += x;
        //cout<<sum <<endl; 
        m.unlock();
    }
}

int main()
{

    int i = 0, nt = thread::hardware_concurrency();
    vector<thread> ths(nt);
    cout<<"\n n-threads: "<<nt;
    
    for ( i = 0; i < nt; i++ )
        ths[i] = thread(F1, i, 1000);

    for ( i = 0; i < nt; i++ )
        ths[i].join();
    
    cout<<"\n sum: "<<sum;

    getchar();
    return 0;
}

