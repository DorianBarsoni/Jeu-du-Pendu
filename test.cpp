#include <iostream>

using namespace std;

int recurs(int i);

int main()
{
    int nb = recurs(7);
    cout<<nb<<endl;

    return 0;
}

int recurs(int i)
{
    if(i<5) return recurs(i+1);
    else return i;
}