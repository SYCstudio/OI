#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=310;
const int Mod=1e9+7;
const int inf=2000000000;

int n,m;
vector<pair<int,int> > Vp[maxN];
int F[maxN][maxN][maxN];

void Plus(int &x,int y);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        int l,r,x;scanf("%d%d%d",&l,&r,&x);Vp[r].push_back(make_pair(l,x));
        if (x>r-l+1){
            puts("0");return 0;
        }
    }
    F[1][0][0]=3;int Ans=0;
    for (int i=1;i<=n;i++){
        int mn1=inf,mn2=inf,mn3=inf,mx1=0,mx2=0,mx3=0;
        for (int j=0,sz=Vp[i].size();j<sz;j++){
            if (Vp[i][j].second==1) mn1=min(mn1,Vp[i][j].first),mx1=max(mx1,Vp[i][j].first);
            if (Vp[i][j].second==2) mn2=min(mn2,Vp[i][j].first),mx2=max(mx2,Vp[i][j].first);
            if (Vp[i][j].second==3) mn3=min(mn3,Vp[i][j].first),mx3=max(mx3,Vp[i][j].first);
        }
        for (int j=0;j<i;j++)
            for (int k=0;k<=j;k++){
                if (k&&j==k) continue;
                if (j>=mn1) continue;
                if (j<mx2||k>=mn2) continue;
                if (k<mx3) continue;
                if (!F[i][j][k]) continue;
                if (i==n) Plus(Ans,F[i][j][k]);
                Plus(F[i+1][j][k],F[i][j][k]);
                Plus(F[i+1][i][k],F[i][j][k]);
                Plus(F[i+1][i][j],F[i][j][k]);
            }
    }
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}