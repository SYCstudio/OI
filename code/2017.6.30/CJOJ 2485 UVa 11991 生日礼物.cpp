#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

int n,m;
map<int , vector<int> > Map;

int main()
{
    while (cin>>n>>m)
    {
        int x;
        int k,v;
        Map.clear();
        for (int i=1;i<=n;i++)
        {
            cin>>x;
            Map[x].push_back(i);
        }
        for (int i=1;i<=m;i++)
        {
            cin>>k>>v;
            //cout<<Map[v].size()<<' ';
            if (Map[v].size()<k)
            {
                cout<<0<<endl;
            }
            else
                cout<<Map[v][k-1]<<endl;
        }
    }
    return 0;
}
