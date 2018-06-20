#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxP=30000;
const int maxN=150;
const int inf=2147483647;

int n,m;
int Price[maxN];
int F[maxP];

int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        cin>>Price[i];
    memset(F,0,sizeof(F));
    F[0]=1;
    for (int i=1;i<=n;i++)
        for (int j=m;j>=Price[i];j--)
                F[j]=F[j]+F[j-Price[i]];
    cout<<F[m]<<endl;
    return 0;
}
