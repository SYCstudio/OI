#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,limit;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],D[maxN],H[maxN],Seq[maxN];

void Add_Edge(int u,int v);
bool dfs(int u,int fa);
bool check(int pos,int sz);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	int sum=1;
	for (int i=1;i<=n;i++) sum=sum+(D[i]-1)/2;
	int L=0,R=n,ans=n;
	do{
		limit=(L+R)>>1;
		//cout<<"check:"<<limit<<endl;
		if (dfs(1,1)) ans=limit,R=limit-1;
		else L=limit+1;
	}
	while (L<=R);

	//for (int i=1;i<=n;i++) cout<<D[i]<<" ";cout<<endl;
	
	printf("%d %d\n",sum,ans);return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;D[u]++;
	return;
}

bool dfs(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) if (dfs(V[i],u)==0) return 0;
	int scnt=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) Seq[++scnt]=H[V[i]]+1;

	//cout<<"dfs:"<<u<<endl;
	if ((u==1)&&(scnt%2==0)){
		sort(&Seq[1],&Seq[scnt+1]);
		//for (int i=1;i<=scnt;i++) cout<<Seq[i]<<" ";cout<<endl;
		for (int l=1,r=scnt;l<r;l++,r--)
			if (Seq[l]+Seq[r]>limit) return 0;
		return 1;
	}
	if (scnt%2==0) Seq[++scnt]=0;
	sort(&Seq[1],&Seq[scnt+1]);
	//for (int i=1;i<=scnt;i++) cout<<Seq[i]<<" ";cout<<endl;
	int l=1,r=scnt,ret=-1;
	do{
		int mid=(l+r)>>1;
		if (check(mid,scnt)) ret=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	if (ret==-1) H[u]=inf;
	else H[u]=Seq[ret];
	return H[u]<=limit;
}

bool check(int pos,int sz){
	//cout<<"check:"<<pos<<" "<<sz<<" - ";for (int i=1;i<=sz;i++) cout<<Seq[i]<<" ";cout<<endl;
	int l=1,r=sz;
	while (l<r){
		if (l==pos) {l++;continue;}
		if (r==pos) {r--;continue;}
		if (Seq[l]+Seq[r]>limit) return 0;
		l++;r--;
	}
	return 1;
}

/*
9
7 8
4 5
5 6
1 2
3 2
9 8
2 5
5 8
//*/

