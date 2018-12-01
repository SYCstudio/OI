#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100;
const int inf=2147483647;

class Splay
{
public:
	ll key,ans,lz;
	int ch[2],fa,size;
};

int n;
Splay S[maxN];
int X[maxN],Y[maxN];
map<pair<int,int>,int> Rt;

void Insert(int id);
void Erase(int id);
void Update(int x);
void PushDown(int x);
void GM(int x,ll key);
void Rotate(int x);
void Splay(int &rt,int x,int goal);
int Prev(int &rt,int x);
int Next(int &rt,int x);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%lld%d%d",&S[i].key,&X[i],&Y[i]);
		Insert(i);
	}
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int v,x,y;scanf("%d%d%d",&v,&x,&y);
		Erase(v);X[v]=x;Y[v]=y;Insert(v);
	}
}

void Insert(int id){
	pair p=make_pair(X[id],Y[id]);
	if (Rt.cound(p)==0) Rt[p]=id;
	else{
		int now=Rt[p];
		do{
			if (cmp(now,id)){
				if (S[now].ch[1]) now=S[now].ch[1];
				else{
					S[now].ch[1]=id;S[id].fa=now;Splay(Rt[p],id,0);
				}
			}
			else{
				if (S[now].ch[0]) now=S[now].ch[0];
				else{
					S[now].ch[0]=id;S[id].fa=now;Splay(Rt[p],id,0);
				}
			}
		}
		while (1);
		now=Rt[p];
		while (S[now].ch[1]) now=S[now].ch[1];
		Splay(Rt[p],now,0);GM(S[now].ch[0],(S[now].size-1)*S[now].key);
		int pre=Prev(now);Splay(Rt[p],pre,0);
		GM(S[pre].ch[1],(S[pre].size-1)*S[pre].key);
	}
	return;
}

void Erase(int id){
	pair p=make_pair(X[id],Y[id]);
	if (S[Rt[p]].size==1) Rt.erase(p);
	else{
		if (Prev(Rt[p],id)==-1){
			Splay(Rt[p],id,0);Rt[p]=S[id].ch[1];
			S[S[id].ch[1]].fa=0;S[id].ch[1]=0;
		}
		else if (Next(Rt[p],id)==-1){
			Splay(Rt[p],id,0);Rt[p]=S[id].ch[0];
			S[S[id].ch[0]].fa=0;S[id].ch[0]=0;
		}
		else{
			int pre=Prev(Rt[p],id),nxt=Next(Rt[p],id);
			Splay(Rt[p],pre,0);Splay(Rt[p].nxt,pre);
			S[id].fa=0;S[nxt].ch[1]=0;Update(nxt);Update(pre);
		}
	}
	return;
}

void Update(int x){
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size;
	return;
}

void PushDown(int x){
	if (S[x].lz!=0){
		if (S[x].ch[0]) GM(S[x].ch[0],S[x].lz);
		if (S[x].ch[1]) GM(S[x].ch[1],S[x].lz);
		S[x].lz=0;
	}
	return;
}

void GM(int x,ll key){
	S[x].ans=max(S[x].ans,key);S[x].lz=max(S[x].lz,key);
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

void Splay(int &rt,int x,int goal){
	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	if (goal==0) rt=x;return;
}

int Prev(int &rt,int x){
	Splay(rt,x,0);if (S[x].ch[0]==0) return -1;
	int now=S[x].ch[0];while (S[now].ch[1]) now=S[now].ch[1];
	return now;
}

int Next(int &rt,int x){
	Splay(rt,x,0);if (S[x].ch[1]==0) return -1;
	int now=S[x].ch[1];while (S[now].ch[0]) now=S[now].ch[0];
	return now;
}
