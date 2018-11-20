#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class SplayData
{
public:
	int ch[2],fa,mx,siz,key;
};

int n,root;
int Rank[maxN];
SplayData S[maxN];

void Update(int x);
void Rotate(int x);
void Splay(int x,int goal);
int Kth(int k);
int Next(int u);

int main(){
	scanf("%d",&n);
	root=1;S[1].mx=S[2].mx=0;S[1].ch[1]=2;S[2].fa=1;S[1].siz=S[2].siz=1;int Ans=0;
	for (int i=1;i<=n;i++){
		int kth;scanf("%d",&kth);++kth;
		int u=Kth(kth),v=Next(u);
		//cout<<"u:"<<u<<" "<<v<<endl;
		Splay(v,0);Splay(u,v);S[i+2].key=S[i+2].mx=S[u].mx+1;Ans=max(Ans,S[u].mx+1);
		Splay(u,0);Splay(v,u);
		S[v].ch[0]=i+2;S[i+2].fa=v;S[i+2].siz=1;
		printf("%d\n",Ans);
	}
	return 0;
}

void Update(int x){
	S[x].siz=S[S[x].ch[0]].siz+S[S[x].ch[1]].siz+1;
	S[x].mx=max(max(S[S[x].ch[0]].mx,S[S[x].ch[1]].mx),S[x].key);
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

void Splay(int x,int goal){
	//cout<<"Splay:"<<x<<" "<<goal<<endl;
	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		//cout<<x<<" "<<y<<" "<<z<<endl;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	if (goal==0) root=x;return;
}

int Kth(int k){
	int now=root;
	do{
		if (S[S[now].ch[0]].siz+1==k){
			Splay(now,0);
			return now;
		}
		if (S[S[now].ch[0]].siz>=k) now=S[now].ch[0];
		else k=k-S[S[now].ch[0]].siz-1,now=S[now].ch[1];
	}
	while (1);
}

int Next(int u){
	Splay(u,0);
	int now=S[now].ch[1];
	while (S[now].ch[0]) now=S[now].ch[0];
	Splay(now,0);
	return now;
}
