#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int n,Seq[maxN],B[maxN],W[maxN];
int Ans=0;

void Work();
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    Work();reverse(&Seq[1],&Seq[n+1]);Work();
    printf("%d\n",Ans);return 0;
}
void Work(){
    memset(B,0,sizeof(B));memset(W,0,sizeof(W));
    for (int i=1;i<=n;i++) if (Seq[i]==1) B[i]=B[i-1]+1;
    for (int i=n;i>=1;i--) if (Seq[i]==2) W[i]=W[i+1]+1;
    for (int i=1,mn;i<n;i++) if (Seq[i]==1&&Seq[i+1]==2) mn=min(B[i],W[i+1]),Ans=max(Ans,mn+mn);
    return;
}