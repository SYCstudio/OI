#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxT=100001;
const int maxM=10001;
const int inf=2147483647;

int T,M;
int Value[maxM];
int Time[maxM];
int F[maxT];

int main()
{
    cin>>T>>M;
    for (int i=1;i<=M;i++)
        cin>>Time[i]>>Value[i];
    memset(F,0,sizeof(F));
    for (int i=1;i<=M;i++)
        for (int j=Time[i];j<=T;j++)
            F[j]=max(F[j],F[j-Time[i]]+Value[i]);
    cout<<F[T]<<endl;
    return 0;
}
