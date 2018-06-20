#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxV=20001;
const int maxN=40;
const int inf=2147483647;

int V,N;
int weight[maxN];
int F[maxV];

int main()
{
    cin>>V>>N;
    for (int i=1;i<=N;i++)
        cin>>weight[i];
    memset(F,0,sizeof(F));
    for (int i=1;i<=N;i++)
        for (int j=V;j>=weight[i];j--)
            F[j]=max(F[j],F[j-weight[i]]+weight[i]);
    cout<<V-F[V]<<endl;
    return 0;
}
