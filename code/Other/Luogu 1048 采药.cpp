#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxT=1001;
const int maxM=101;
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
        for (int j=T;j>=Time[i];j--)
            F[j]=max(F[j],F[j-Time[i]]+Value[i]);
    int Ans=0;
    for (int i=0;i<=T;i++)
        Ans=max(Ans,F[i]);
    cout<<Ans<<endl;
    return 0;
}
