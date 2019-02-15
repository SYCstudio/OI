#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000*50;
const int inf=2147483647;

class Treap
{
public:
	int key,size,ch[2];
};

int nodecnt;
Treap T[maxN];
int root[maxN];

int random(int l,int r);
int Newnode(int key);
int Copynode(int id);
void Init();
void Update(int x);
void Split(int now,int k,int &x,int &y);
int Merge(int x,int y);

int main(){
	freopen("td.in","r",stdin);
	srand(20010622);
	int TTT;scanf("%d",&TTT);
	Init();
	for (int ti=1;ti<=TTT;ti++){
		int vi,opt,key;scanf("%d%d%d",&vi,&opt,&key);
		if (opt==1){
			int x,y;Split(root[vi],key,x,y);
			int z=Newnode(key);
			root[ti]=Merge(Merge(x,z),y);
		}
		if (opt==2){
			int x,y,z;Split(root[vi],key,x,z);
			Split(x,key-1,x,y);
			root[ti]=Merge(Merge(x,Merge(T[y].ch[0],T[y].ch[1])),z);
		}
		if (opt==3){
			int x,y;Split(root[vi],key-1,x,y);
			printf("%d\n",T[x].size);
			root[ti]=Merge(x,y);
		}
		if (opt==4){
			int now=root[vi];++key;
			do{
				if (T[T[now].ch[0]].size>=key) now=T[now].ch[0];
				else if (T[T[now].ch[0]].size+1==key) break;
				else key-=T[T[now].ch[0]].size+1,now=T[now].ch[1];
			}
			while (1);
			printf("%d\n",T[now].key);
			root[ti]=root[vi];
		}
		if (opt==5){
			int x,y;Split(root[vi],key-1,x,y);
			int now=x;while (T[now].ch[1]) now=T[now].ch[1];
			printf("%d\n",T[now].key);root[ti]=Merge(x,y);
		}
		if (opt==6){
			int x,y;Split(root[vi],key,x,y);
			int now=y;while (T[now].ch[0]) now=T[now].ch[0];
			printf("%d\n",T[now].key);root[ti]=Merge(x,y);
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
	T[id].ch[0]=T[id].ch[1]=0;T[id].size=1;
	T[id].key=key;return id;
}

int Copynode(int id){
	T[++nodecnt]=T[id];return nodecnt;
}

void Init(){
	int x=Newnode(-2147483647),y=Newnode(2147483647);
	root[0]=x;T[x].ch[1]=y;Update(x);return;
}

void Update(int x){
	T[x].size=T[T[x].ch[0]].size+T[T[x].ch[1]].size+1;
	return;
}

void Split(int now,int k,int &x,int &y){
	if (now==0){
		x=y=0;return;
	}
	if (T[now].key<=k){
		x=Copynode(now);Split(T[now].ch[1],k,T[x].ch[1],y);Update(x);
	}
	else{
		y=Copynode(now);Split(T[now].ch[0],k,x,T[y].ch[0]);Update(y);
	}
	return;
}

int Merge(int x,int y){
	if ((x==0)||(y==0)) return x+y;
	int z;
	if (random(1,T[x].size+T[y].size)<=T[x].size){
		z=x;T[z].ch[1]=Merge(T[x].ch[1],y);
	}
	else{
		z=y;T[z].ch[0]=Merge(x,T[y].ch[0]);
	}
	Update(z);return z;
}
