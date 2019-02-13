#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=101000;
const int maxB=17;
const int inf=2000000000;
int n,K,T;
int lft[maxN],rht[maxN],St[maxN],Lg[maxN];
ll X[maxN],Y[maxN];
pair<ll,int> Mx[maxB][maxN],Mn[maxB][maxN];

bool check(ll v);
pair<ll,int> GetMx(int l,int r);
pair<ll,int> GetMn(int l,int r);

int main(){
    //freopen("in","r",stdin);
    for (int i=2;i<maxN;i++) Lg[i]=Lg[i>>1]+1;
    scanf("%d%d%d",&n,&K,&T);for (int i=1;i<=n;i++) scanf("%lld",&X[i]);
    ll l=0,r=1e9,Ans,mid;
    while (l<=r) if (check(mid=(l+r)>>1)) Ans=mid,r=mid-1;else l=mid+1;
    printf("%lld\n",Ans);return 0;
}
bool check(ll v){
    for (int i=1;i<=n;i++) Mn[0][i]=Mx[0][i]=make_pair(Y[i]=X[i]-2ll*v*T*i,i);
    for (int i=1;i<maxB;i++) 
        for (int j=1;j+(1<<i)-1<=n;j++){
            Mn[i][j]=min(Mn[i-1][j],Mn[i-1][j+(1<<(i-1))]);
            Mx[i][j]=max(Mx[i-1][j],Mx[i-1][j+(1<<(i-1))]);
        }
    for (int i=1,top=0;i<=n;i++){
        while (top&&Y[St[top]]<=Y[i]) --top;
        lft[i]=St[top];St[++top]=i;
    }
    for (int i=n,top=0;i>=1;i--){
        while (top&&Y[St[top]]>=Y[i]) --top;
        rht[i]=St[top];St[++top]=i;
    }
    //cout<<"check:"<<v<<endl;
    //for (int i=1;i<=n;i++) cout<<Y[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<lft[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<rht[i]<<" ";cout<<endl;
    for (int l=K,r=K;l>1||r<n;){
        int u=lft[l],v=rht[r];
        if (u&&GetMn(u+1,l-1).first>=Y[r]) l=u;
        else if (v&&GetMx(r+1,v-1).first<=Y[l]) r=v;
        else{
            //cout<<"Case3"<<endl;
            if (l==1) return GetMx(r+1,n).first<=Y[l];
            if (r==n) return GetMn(1,l-1).first>=Y[r];
            u=GetMn(1,l-1).second;v=GetMx(r+1,n).second;
            //cout<<"u:"<<u<<" v:"<<v<<endl;
            if (Y[u]<Y[r]||Y[v]>Y[l]) return 0;
            int i=GetMx(1,u).second,j=GetMn(v,n).second;
            //cout<<"i:"<<i<<" j:"<<j<<endl;
            if (Y[i]>=Y[v]) l=i;
            else if (Y[j]<=Y[u]) r=j;
            else return 0;
        }
    }
    return 1;
}
pair<ll,int> GetMx(int l,int r){
    if (l>r) return make_pair(-inf,l);
    int lg=Lg[r-l+1];
    return max(Mx[lg][l],Mx[lg][r-(1<<lg)+1]);
}
pair<ll,int> GetMn(int l,int r){
    if (l>r) return make_pair(inf,l);
    int lg=Lg[r-l+1];
    return min(Mn[lg][l],Mn[lg][r-(1<<lg)+1]);
}