#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
class Edge{
    public:
    int u,v,id;
    ll w;
};

const int maxN=20200;
const int maxM=50500;
const int maxB=20;
const int inf=1000000000;
const ll INF=1e18;

int n,m,Q;
int ufs[maxN],uId[maxM];
ll Ew[maxM];
Edge Wk[maxB][maxM],Bp[maxM],tmp[maxM];
pair<int,int> Mfy[maxM];

int find(int x);
bool cmp(Edge A,Edge B);
void Divide(int d,int l,int r,ll sum,int size);

int main(){
    //freopen("1.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=m;i++) scanf("%d%d%lld",&Wk[0][i].u,&Wk[0][i].v,&Ew[i]),Wk[0][i].id=i;
    for (int i=1;i<=Q;i++) scanf("%d%d",&Mfy[i].first,&Mfy[i].second);
    for (int i=1;i<=n;i++) ufs[i]=i;
    Divide(0,1,Q,0,m);
    return 0;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
bool cmp(Edge A,Edge B){
    return A.w<B.w;
}
void Divide(int d,int l,int r,ll sum,int size){
    Ew[Mfy[l].first]=Mfy[l].second;
    for (int i=1;i<=size;i++) Bp[i]=Wk[d][i],Bp[i].w=Ew[Bp[i].id],uId[Bp[i].id]=i;
    if (l==r){
        for (int i=1;i<=size;i++) ufs[Bp[i].u]=Bp[i].u,ufs[Bp[i].v]=Bp[i].v;
        sort(&Bp[1],&Bp[size+1],cmp);
        for (int i=1;i<=size;i++) if (find(Bp[i].u)!=find(Bp[i].v)) sum+=Bp[i].w,ufs[find(Bp[i].u)]=find(Bp[i].v);
        printf("%lld\n",sum);return;
    }

    int top=0;
    for (int i=l;i<=r;i++) Bp[uId[Mfy[i].first]].w=-INF;
    for (int i=1;i<=size;i++) ufs[Bp[i].u]=Bp[i].u,ufs[Bp[i].v]=Bp[i].v;
    sort(&Bp[1],&Bp[size+1],cmp);
    for (int i=1;i<=size;i++)
        if (find(Bp[i].u)!=find(Bp[i].v)){
            ufs[find(Bp[i].u)]=find(Bp[i].v);
            if (Bp[i].w!=-INF) tmp[++top]=Bp[i];
        }
    for (int i=1;i<=size;i++) ufs[Bp[i].u]=Bp[i].u,ufs[Bp[i].v]=Bp[i].v;
    for (int i=1;i<=top;i++) sum+=tmp[i].w,ufs[find(tmp[i].u)]=find(tmp[i].v);
    top=0;
    for (int i=1;i<=size;i++)
        if (find(Bp[i].u)!=find(Bp[i].v)){
            tmp[++top]=Bp[i];tmp[top].u=find(tmp[top].u);tmp[top].v=find(tmp[top].v);uId[tmp[top].id]=top;
        }
    size=top;for (int i=1;i<=size;i++) Bp[i]=tmp[i];

    for (int i=1;i<=size;i++) ufs[Bp[i].u]=Bp[i].u,ufs[Bp[i].v]=Bp[i].v;
    for (int i=l;i<=r;i++) Bp[uId[Mfy[i].first]].w=INF;
    sort(&Bp[1],&Bp[size+1],cmp);top=0;
    for (int i=1;i<=size;i++)
        if (find(Bp[i].u)!=find(Bp[i].v)){
            ufs[find(Bp[i].u)]=find(Bp[i].v);tmp[++top]=Bp[i];
        }
        else if (Bp[i].w==INF) tmp[++top]=Bp[i];
    for (int i=1;i<=top;i++) Wk[d+1][i]=tmp[i];
    int mid=(l+r)>>1;Divide(d+1,l,mid,sum,top);Divide(d+1,mid+1,r,sum,top);
    return;
}