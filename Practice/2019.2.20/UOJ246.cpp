#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=201000;

int n,m,K,Seq[maxN],lst[maxN],pos[maxN];
int Mn[2][maxN];
ll Ans=0;

int main(){
    //freopen("in","r",stdin);
    scanf("%d%d%d",&n,&m,&K);int srt=sqrt(m)+1;
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    
    int now=1;
    for (int i=1;i<n;i++){
        Mn[now][i]=abs(Seq[i]-Seq[i+1]);
        if (K==2) Ans=max(Ans,1ll*Mn[now][i]);
    }
    for (int b=3;b<=srt;b++){
        now^=1;
        for (int i=1;i+b-1<=n;i++){
            Mn[now][i]=min(min(Mn[now^1][i],Mn[now^1][i+1]),abs(Seq[i]-Seq[i+b-1]));
            if (b>=K) Ans=max(Ans,1ll*(b-1)*Mn[now][i]);
        }
    }

    for (int i=1;i<=n;i++){
        for (int j=0,mxpos=0;j<=srt;j++){
            if (Seq[i]-j>=1&&pos[Seq[i]-j]) lst[j]=max(lst[j],pos[Seq[i]-j]);
            if (Seq[i]+j<maxN&&pos[Seq[i]+j]) lst[j]=max(lst[j],pos[Seq[i]+j]);
            if (lst[j]>mxpos&&i-mxpos>=K) Ans=max(Ans,1ll*j*(i-mxpos-1));
            mxpos=max(mxpos,lst[j]);
            //cout<<i<<" "<<j<<" "<<mxpos<<" "<<lst[j]<<" "<<Ans<<endl;
        }
        pos[Seq[i]]=i;
    }
    printf("%lld\n",Ans);return 0;
}