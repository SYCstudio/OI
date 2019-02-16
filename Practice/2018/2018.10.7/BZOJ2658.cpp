#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40100;
const int maxM=101000;

class TreapData
{
public:
	int ht,ch[2],size;
	ll pls,sum;
};

int n,m,K,root;
ll S[maxM],Ans=0;
vector<int> V[maxN];
TreapData T[maxN];

void Update(int x);
void Plus(int x,ll h);
void PushDown(int x);
void Rotate(int &x,int c);
void Modify(int &x,int kth);

int main(){
	for (int i=1;i<maxM;i++) S[i]=1ll*i*(i-1)/2;
	
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=K;i++){
		int x,y;scanf("%d%d",&x,&y);
		V[x].push_back(y);
	}
	for (int i=1;i<m;i++) T[i].ch[1]=i+1;
	for (int i=m;i>=1;i--) Update(i);
	root=1;
	
	ll Ans=S[n+1]*S[m+1];
	for (int i=1;i<=n;i++){
		Plus(root,1);
		for (int j=0,sz=V[i].size();j<sz;j++) Modify(root,V[i][j]);
		Ans=Ans-T[root].sum-S[T[root].size+1]*T[root].ht;
	}
	printf("%lld\n",Ans);return 0;
}

void Update(int x){
	T[x].size=1;T[x].sum=0;
	if (T[x].ch[0]){
		T[x].size+=T[T[x].ch[0]].size;
		T[x].sum+=T[T[x].ch[0]].sum+S[T[T[x].ch[0]].size+1]*(T[T[x].ch[0]].ht-T[x].ht);
	}
	if (T[x].ch[1]){
		T[x].size+=T[T[x].ch[1]].size;
		T[x].sum+=T[T[x].ch[1]].sum+S[T[T[x].ch[1]].size+1]*(T[T[x].ch[1]].ht-T[x].ht);
	}
	return;
}

void Plus(int x,ll h){
	T[x].ht+=h;T[x].pls+=h;return;
}

void PushDown(int x){
	if (T[x].pls==0) return;
	if (T[x].ch[0]) Plus(T[x].ch[0],T[x].pls);
	if (T[x].ch[1]) Plus(T[x].ch[1],T[x].pls);
	T[x].pls=0;
	return;
}

void Rotate(int &x,int c){
	int y=T[x].ch[c];
	T[x].ch[c]=T[y].ch[c^1];
	T[y].ch[c^1]=x;
	Update(x);Update(y);x=y;return;
}

void Modify(int &x,int kth){
	PushDown(x);
	if (T[T[x].ch[0]].size+1==kth){
		T[x].ht=0;Update(x);return;
	}
	else if (T[T[x].ch[0]].size+1>kth){
		Modify(T[x].ch[0],kth);
		Rotate(x,0);return;
	}
	else{
		Modify(T[x].ch[1],kth-T[T[x].ch[0]].size-1);
		Rotate(x,1);return;
	}
}
