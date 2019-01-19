#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;

int n,m,D;
int Mt[maxN],U[maxN],Ans[maxN],acnt;
vector<int> T1[maxN],T2[maxN];
int tim,Tim[maxN],Qu[maxN];

bool check(int S);

int main(){
    scanf("%d%d%d",&n,&m,&D);
    for (int i=1;i<=m;i++){
	int u,v;scanf("%d%d",&u,&v);
	T1[u].push_back(v);T2[v].push_back(u);
    }
    for (int i=1;i<=D;i++) scanf("%d",&Mt[i]),U[Mt[i]]=1;
    
    for (int i=1;i<=n;i++) if (U[i]||check(i)) Ans[++acnt]=i;
    for (int i=1;i<=acnt;i++){
	if (i!=1) printf(" ");
	printf("%d",Ans[i]);
    }
    printf("\n");return 0;
}
bool check(int S){
    ++tim;int ql=1,qr=1;Qu[1]=S;Tim[S]=tim;
    while (ql<=qr) for (int u=Qu[ql++],i=0,sz=T2[u].size();i<sz;i++) if (Tim[T2[u][i]]!=tim) Tim[T2[u][i]]=tim,Qu[++qr]=T2[u][i];
    for (int i=1;i<=D;i++) if (Tim[Mt[i]]==tim) return 1;
    ql=1;qr=0;for (int i=1;i<=n;i++) if (Tim[i]!=tim&&T2[i].size()==0) Tim[Qu[++qr]=i]=tim;
    while (ql<=qr) for (int u=Qu[ql++],i=0,sz=T1[u].size();i<sz;i++) if (Tim[T1[u][i]]!=tim) Tim[T1[u][i]]=tim,Qu[++qr]=T1[u][i];
    for (int i=1;i<=D;i++) if (Tim[Mt[i]]!=tim) return 1;
    return 0;
}
