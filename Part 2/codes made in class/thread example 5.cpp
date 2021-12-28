#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

void F1(int n)
{
    int sum = 0;
    for ( int i = 0; i < n; i++ )
    for ( int j = 0; j < n; j++ )
    {
        sum = += 1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1;
    }
}

int main()
{
    int i, nthreads = thread::hardware_concurrency();
    vector<thread> ths(nthreads);
    
    for ( i = 0; i < nt; i++ )
        ths[i] = thread(F1, 1000);

    for ( i = 0; i < nt; i++ )
        ths[i].join();
    
    cout<<"\n -- end --";

    getchar();
    return 0;
}

