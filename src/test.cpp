#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    list<int> liste = {1, 2, 3};
    int nb = 2;
    auto iter = find(liste.begin(), liste.end(), 2);
    liste.erase(iter);
    for(auto it : liste) cout<<it<<endl;

    return 0;
}