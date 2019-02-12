#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
typedef long long ll;
#define Min(x,y) x=min(x,y)
#define Max(x,y) x=max(x,y)
const int maxN=310;
const int inf=1000000000;
const ll INF=1e18;
class Range{
    public:
    int l,r,a,b,c;
};
class MonotonusQueue{
    public:
    int l,r;pair<int,ll> Q[maxN*2];
    void Init(){
        l=1;r=0;return;
    }
    void Push(int x,ll y){
        while (l<=r&&Q[r].second<=y) --r;
        Q[++l]=make_pair(x,y);return;
    }
    ll Front(int x){
        while (l<=r&&Q[l].first<x) ++l;
        if (l>r) return INF;
        return Q[l].first;
    }
};
int n,cntx=0;
pair<ll,ll> P[maxN];
ll Ca[maxN],Cb[maxN],Cc[maxN];
ll W,H,Xn[maxN],Ans=1e18;
MonotonusQueue Qa,Qb,Qc;
Range R[maxN*2];
queue<int> Qx;

void Calc(ll len);

int main(){
    scanf("%lld%lld%d",&W,&H,&n);for (int i=1;i<=n;i++) scanf("%lld%lld",&P[i].first,&P[i].second);
    sort(&P[1],&P[n+1]);
    for (int i=1,j;i<=n;i=j+1){
        j=i;while (j<n&&P[j+1].first==P[i].first) ++j;
        ++cntx;Xn[cntx]=P[i].first;
        Ca[cntx]=Cb[cntx]=inf;Cc[cntx]=0;
        for (int k=i;k<=j;k++) Min(Ca[cntx],P[k].second-1),Min(Cb[cntx],W-P[k].second);
        for (int k=i;k<j;k++) Max(Cc[cntx],P[k+1].second-P[k].second-1);
    }
    Calc(Xn[1]);Calc(W-Xn[cntx]);
    for (int i=1;i<=cntx;i++) for (int j=i+1;j<=cntx;j++) Calc(Xn[j]-Xn[i]-1),Calc(Xn[j]-Xn[i]-1+W);
    printf("%lld\n",Ans);return 0;
}
void Calc(ll len){
    cout<<"Calc:"<<len<<endl;
    int rcnt=0,p=1,lst=1;
    Qa.Init();Qb.Init();Qc.Init();while (!Qx.empty()) Qx.pop();
    while (p<=cntx||!Qx.empty())
        if (p<=cntx&&(Qx.empty()||Xn[p]<=Qx.front())){
            if (lst<Xn[p]) R[++rcnt]=((Range){lst,Xn[p]-1,Qa.Front(lst),Qb.Front(lst),Qc.Front(lst)});
            Qx.push(Xn[p]+len);Qa.Push(Xn[p]+len,Ca[p]);Qb.Push(Xn[p]+len,Cb[p]);Qc.Push(Xn[p]+len,Cc[p]);
            lst=Xn[p];++p;
        }
        else{
            if (lst<=Qx.front()) R[++rcnt]=((Range){lst,Qx.front(),Qa.Front(lst),Qb.Front(lst),Qc.Front(lst)});
            lst=Qx.front()+1;Qx.pop();
        }
    if (lst<=W) R[++rcnt]=((Range){lst,W,Qa.Front(lst),Qb.Front(lst),Qc.Front(lst)});

    Qa.Init();Qb.Init();Qc.Init();
    int p1=1,p2=0;
    for (p1=1;p1<=rcnt;p1++){
        while (p2<rcnt&&R[p2].r<R[p1].l+W-1){
            ++p2;Qa.Push(R[p2].r,R[p2].a);Qb.Push(R[p2].r,R[p2].b);Qc.Push(R[p2].r,R[p2].c);
        }
        if (R[p2].r<R[p1].l+W-1) break;
        Ans=min(Ans,len+max(Qa.Front(R[p1].l)+Qb.Front(R[p1].l),Qc.Front(R[p1].l)));
    }
    return;
}