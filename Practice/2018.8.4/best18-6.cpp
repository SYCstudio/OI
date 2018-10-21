#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=110;
const int inf=1000000000;

class Edge
{
public:
	int u,v,w,c;
};

int n,m;
Edge E[maxM],T[maxM];
int ecnt,pcnt;
int Ans[maxM],W[maxM],UFS[maxN];

int Find(int x);
int Mst();
bool cmp(Edge A,Edge B);

int main(){
	int TTT;scanf("%d",&TTT);
	for (int ti=1;ti<=TTT;ti++){
		scanf("%d%d",&n,&m);
		for (int i=1;i<=m;i++){
			char ch;
			scanf("%d%d%d %c",&E[i].u,&E[i].v,&E[i].w,&ch);
			if (ch=='R') E[i].c=1;
			if (ch=='G') E[i].c=2;
			if (ch=='B') E[i].c=3;
		}
		
		for (int i=1;i<=m;i++) Ans[i]=inf;

		ecnt=0;pcnt=0;
		for (int i=1;i<=m;i++)
			if (E[i].c!=3) T[++ecnt]=E[i];
			else W[++pcnt]=E[i].w;

		int mst=Mst();

		if (pcnt) sort(&W[1],&W[pcnt+1]);
		for (int i=0;i<=pcnt;i++){
			mst+=W[i];
			Ans[i+n-1]=min(Ans[i+n-1],mst);
		}

		ecnt=0;pcnt=0;
		for (int i=1;i<=m;i++)
			if (E[i].c!=1) T[++ecnt]=E[i];
			else W[++pcnt]=E[i].w;

		mst=Mst();
		if (pcnt) sort(&W[1],&W[pcnt+1]);
		for (int i=0;i<=pcnt;i++){
			mst+=W[i];
			Ans[i+n-1]=min(Ans[i+n-1],mst);
		}

		printf("Case #%d:\n",ti);
		for (int i=1;i<=m;i++)
			if (Ans[i]==inf) printf("-1\n");
			else printf("%d\n",Ans[i]);
	}
	return 0;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

bool cmp(Edge A,Edge B){
	return A.w<B.w;
}

int Mst(){
	int ret=0,tot=0;
	for (int i=1;i<=n;i++) UFS[i]=i;
	sort(&T[1],&T[ecnt+1],cmp);
	for (int i=1;i<=ecnt;i++){
		int u=T[i].u,v=T[i].v;
		if (Find(u)!=Find(v)){
			ret+=T[i].w;tot++;
			UFS[Find(u)]=Find(v);
		}
		else W[++pcnt]=T[i].w;
	}
	if (tot<n-1) return inf;
	return ret;
}
