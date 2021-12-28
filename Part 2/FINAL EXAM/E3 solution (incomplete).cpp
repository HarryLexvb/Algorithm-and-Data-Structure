#include <iostream>
#include <mutex>
#include <cmath>
#include <thread>
#include <vector>

using namespace std;
mutex m;
void PrintMatrix(int (*pm)[7], int y, int x)
{
    for ( int j = 0; j < y; j++ )
    {
        for ( int i = 0; i < x; i++ )
            std::cout<<pm[j][i]<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void PrintVector(int *v, int s)
{
    for ( int i = 0; i < s; i ++ )
        std::cout<<v[i]<<" ";
    std::cout<<"\n\n";
}

void subsum(int (*ans)[7], int *mat, int size, int offset){
    for(int i = 0; i < size; ++i){
        /*m.lock();
        float h_v = float(mat[i])/100.f;
        ans[ceil(float(mat[i])/100)-1] += mat[i];
        m.unlock(); //*/
        for (int j = 0; j < size; ++j) {
        
            mat[ans[i][j]/100-0] += ans[i][j];

        }
    }

}
int main()
{
    int m[10][7]
            {
                    {142,950,227,771,907,827,159},
                    {932,51,99,117,306,909,885},
                    {471,208,985,202,42,85,364},
                    {248,860,82,154,236,429,756},
                    {120,989,344,638,77,522,911},
                    {985,842,170,491,904,736,854},
                    {114,431,657,864,604,580,766},
                    {120,352,321,668,917,88,898},
                    {768,190,955,757,422,915,658},
                    {5,622,355,675,150,557,126}
            };
    int sum[10] = {0};
    PrintMatrix(m, 10, 7);
//**************************************************
    int i = 0, nt = 4; //thread::hardware_concurrency();
    vector<thread> ths(nt);
    cout<<"\n cantidad threads: "<<nt;

    for ( i = 0; i < nt; ++i )
        ths.at(i) = thread(subsum, m, sum, 10, i);

    for ( i = 0; i < nt; i++ )
        ths.at(i).join();
//**************************************************
    ///suma de la matriz
    PrintVector(sum, 10);
}