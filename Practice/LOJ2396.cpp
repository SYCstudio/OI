#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int maxN=202000;

int n,m;
ll X,W,T,Pos[maxN],F[maxN];
pair<ll,ll> Ref[maxN],Pag[maxN];
vector<pair<ll,ll> > Seg[maxN<<2];

bool cmpp(ll A,ll B);
bool cmpr(pair<ll,ll> A,pair<ll,ll> B);
void Modify(int x,int l,int r,int k,ll key);
ll Query(int x,int l,int r,ll k);

int main(){
    scanf("%lld%d%d%lld%lld",&X,&n,&m,&W,&T);
    for (int i=1;i<=n;i++) scanf("%lld",&Pos[i]);Pos[++n]=X;sort(&Pos[1],&Pos[n+1],cmpp);
    for (int i=1;i<=n;i++) Ref[i]=make_pair(Pos[i],Pos[i-1]);sort(&Ref[1],&Ref[n+1],cmpr);
    for (int i=1;i<=m;i++) scanf("%lld%lld",&Pag[i].first,&Pag[i].second);
    sort(&Pag[1],&Pag[m+1]);
    for (int i=1;i<=m;i++) Pag[i].second+=Pag[i-1].second;
    F[0]=(X/T+(X%T!=0))*W;Modify(1,0,m,0,F[0]);
    for (int i=1,j=1;i<=m;i++){
        F[i]=F[i-1]+(X/T+(X-1)%T+1
    }
}
bool cmpp(ll A,ll B){
    return (A-1)%T<(B-1)%T;
}
bool cmpr(pair<ll,ll> A,pair<ll,ll> B){
    return (A.first-1)%T<(B.first-1)%T;
}