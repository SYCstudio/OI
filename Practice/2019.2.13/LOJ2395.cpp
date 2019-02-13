#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int maxB=18;

int n,K,Q,Seq[maxN],St[maxN];
int L[maxB][maxN],R[maxB][maxN];

int main(){
    scanf("%d%d%d",&n,&K,&Q);
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    int top=1;St[1]=1;
    for (int i=2;i<=n;i++){
        while (top&&Seq[St[top]]<Seq[i]) --top;
        L[0][i]=St[top];St[++top]=i;
    }
    top=1;St[1]=n;
    for (int i=n-1;i>=1;i--){
        while (top&&Seq[St[top]]<Seq[i]) --top;
        R[0][i]=St[top];St[++top]=i;
    }
    L[0][1]=1;R[0][n]=n;
    for (int b=1;b<maxB;b++)
        for (int i=1;i<=n;i++){
            L[b][i]=min(L[b-1][L[b-1][i]],L[b-1][R[b-1][i]]);
            R[b][i]=max(R[b-1][R[b-1][i]],R[b-1][L[b-1][i]]);
        }
    while (Q--){
        int s,t,Ans=0;scanf("%d%d",&s,&t);if (s>t) swap(s,t);
        int l=s,r=s;
        for (int i=maxB-1;i>=0;i--){
            int lft=min(L[i][l],L[i][r]),rht=max(R[i][l],R[i][r]);
            if (rht<t){
                l=lft;r=rht;Ans+=(1<<i);
            }
        }
        s=r;l=r=t;
        for (int i=maxB-1;i>=0;i--){
            int lft=min(L[i][l],L[i][r]),rht=max(R[i][l],R[i][r]);
            if (lft>s){
                l=lft;r=rht;Ans+=(1<<i);
            }
        }
        printf("%d\n",Ans);
    }
    return 0;
}