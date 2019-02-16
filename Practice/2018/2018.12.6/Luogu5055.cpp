#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int inf=2147483647;

class Treap
{
public:
	int key,size,rev;
	int ch[2];
};

int n;
ll Sum[maxN*80];
Treap T[maxN*80];
int root[maxN],nodecnt;

int random(int l,int r);
int Newnode(int key);
int Copynode(int x);
void Reverse(int x);
void Update(int x);
void PushDown(int x);
void Init();
void Split(int now,int key,int &x,int &y);
int Merge(int x,int y);

int main(){
	srand(20010622);Init();
	int TTT;scanf("%d",&TTT);
	ll lastans=0;
	for (int ti=1;ti<=TTT;ti++){
		int opt,vi;scanf("%d%d",&vi,&opt);
		if (opt==1){
			ll p,key;scanf("%lld%lld",&p,&key);p^=lastans;key^=lastans;++p;
			int x,y;Split(root[vi],p,x,y);
			root[ti]=Merge(Merge(x,Newnode(key)),y);
		}
		if (opt==2){
			ll p;scanf("%lld",&p);p^=lastans;++p;
			int x,y,z;Split(root[vi],p,x,z);Split(x,p-1,x,y);
			root[ti]=Merge(x,z);
		}
		if (opt==3){
			ll l,r;scanf("%lld%lld",&l,&r);l^=lastans;r^=lastans;++l;++r;
			int x,y,z;Split(root[vi],r,x,z);Split(x,l-1,x,y);
			Reverse(y);
			root[ti]=Merge(Merge(x,y),z);
		}
		if (opt==4){
			ll l,r;scanf("%lld%lld",&l,&r);l^=lastans;r^=lastans;++l;++r;
			int x,y,z;Split(root[vi],r,x,z);Split(x,l-1,x,y);
			printf("%lld\n",lastans=Sum[y]);
			root[ti]=Merge(Merge(x,y),z);
		}
	}
	return 0;
}

int random(int l,int r){
	double dou=1.0*rand()/RAND_MAX;
	return min(r,(int)(dou*(r-l+1))+l);
}

int Newnode(int key){
	int id=++nodecnt;
	T[id].ch[0]=T[id].ch[1]=T[id].rev=0;T[id].size=1;T[id].key=key;
	Sum[id]=key;return id;
}

int Copynode(int x){
	T[++nodecnt]=T[x];Sum[nodecnt]=Sum[x];
	return nodecnt;
}

void Reverse(int x){
	T[x].rev^=1;swap(T[x].ch[0],T[x].ch[1]);
	return;
}

void Update(int x){
	T[x].size=T[T[x].ch[0]].size+T[T[x].ch[1]].size+1;
	Sum[x]=Sum[T[x].ch[0]]+Sum[T[x].ch[1]]+T[x].key;
	return;
}

void PushDown(int x){
	if (T[x].rev==0) return;
	if (T[x].ch[0]){
		T[x].ch[0]=Copynode(T[x].ch[0]);
		Reverse(T[x].ch[0]);
	}
	if (T[x].ch[1]){
		T[x].ch[1]=Copynode(T[x].ch[1]);
		Reverse(T[x].ch[1]);
	}
	T[x].rev=0;return;
}

void Init(){
	int x=Newnode(0),y=Newnode(0);
	root[0]=x;T[x].ch[1]=y;Update(x);return;
}

void Split(int now,int key,int &x,int &y){
	if (now==0){
		x=y=0;return;
	}
	PushDown(now);
	if (T[T[now].ch[0]].size>=key){
		y=Copynode(now);Split(T[now].ch[0],key,x,T[y].ch[0]);Update(y);
	}
	else{
		x=Copynode(now);Split(T[now].ch[1],key-T[T[now].ch[0]].size-1,T[x].ch[1],y);Update(x);
	}
	return;
}

int Merge(int x,int y){
	if ((x==0)||(y==0)) return x+y;
	PushDown(x);PushDown(y);int z;
	if (random(1,T[x].size+T[y].size)<=T[x].size) T[z=x].ch[1]=Merge(T[x].ch[1],y);
	else T[z=y].ch[0]=Merge(x,T[y].ch[0]);
	Update(z);return z;
}
