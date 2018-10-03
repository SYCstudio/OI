#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=601000;
const int inf=2147483647;

class Heap
{
public:
	int ls,rs,key;
	int dis,fa;
};

int n,m,K,Rt[maxN];
Heap H[maxN];

int Merge(int u,int v);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	while (K--){
		char opt[10];scanf(" %s",opt);
		if (opt[0]=='A'){
			int p,k,w;scanf("%d%d%d",&p,&k,&w);
			H[k].key=w;Rt[p]=Merge(Rt[p],k);
		}
		if (opt[0]=='D'){
			int p,k,w;scanf("%d%d%d",&p,&k,&w);
			int ls=H[k].ls,rs=H[k].rs,fa=H[k].fa;
			H[ls].fa=H[rs].fa=H[k].fa=H[k].ls=H[k].rs=0;
			int rt=Merge(ls,rs);
			if (fa==0) Rt[p]=rt;
			else{
				if (H[fa].ls==k) H[fa].ls=rt;
				else H[fa].rs=rt;
				H[rt].fa=fa;
			}
			H[k].key-=w;Rt[p]=Merge(Rt[p],k);
		}
		if (opt[0]=='T'){
			int n1,n2;scanf("%d%d",&n1,&n2);
			Rt[n2]=Merge(Rt[n1],Rt[n2]);Rt[n1]=0;
		}
		if (opt[0]=='M'){
			int p;scanf("%d",&p);
			printf("%d\n",H[Rt[p]].key);
		}
		if (opt[0]=='W'){
			int p,w;scanf("%d%d",&p,&w);
			int id=Rt[p];
			bool flag=1;
			if ((H[id].ls)&&(H[H[id].ls].key==H[id].key)) flag=0;
			if ((H[id].rs)&&(H[H[id].rs].key==H[id].key)) flag=0;
			if (flag==0){
				printf("ERROR\n");continue;
			}
			Rt[p]=Merge(H[id].ls,H[id].rs);
			H[id].ls=H[id].rs=0;H[id].key+=w;
			Rt[p]=Merge(Rt[p],id);
		}
	}
	return 0;
}

int Merge(int u,int v){
	if (u==0) return v;
	if (v==0) return u;
	if (H[u].key>H[v].key) swap(u,v);H[u].fa=0;
	H[u].rs=Merge(H[u].rs,v);if (H[u].rs) H[H[u].rs].fa=u;
	if (H[H[u].ls].dis<H[H[u].rs].dis) swap(H[u].ls,H[u].rs);
	if (H[u].rs) H[u].dis=H[H[u].rs].dis+1;
	else H[u].dis=0;
	return u;
}
/*
2 3 13
ADD 1 2 100
ADD 1 1 90
MIN 1
WORK 1 20
TRANS 1 2
MIN 2
ADD 1 3 105
TRANS 2 1
MIN 1
DEC 1 3 200
MIN 1
DEC 1 1 205
WORK 1 15
//*/
