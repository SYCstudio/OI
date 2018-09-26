#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class SplayData
{
public:
	int key,ch[2],fa,dp,rev;
	multiset<int> Ms;
};

int n,nodecnt;
SplayData S[maxN];
int St[maxN];

bool Isroot(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
void Outp();

int main(){
	int Q;scanf("%d",&Q);
	while (Q--){
		char opt;int key;scanf(" %c%d",&opt,&key);
		if (opt=='B'){
			n++;
			if (key!=-1){
				Makeroot(key);S[key].Ms.insert(0);
				S[n].fa=key;Update(key);
			}
		}
		if (opt=='Q'){
			Makeroot(key);
			printf("%d\n",S[key].dp);
		}
		//Outp();
	}
	return 0;
}

bool Isroot(int x){
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void PushDown(int x){
	if (S[x].rev){
		int ls=S[x].ch[0],rs=S[x].ch[1];
		if (ls) S[ls].rev^=1,swap(S[ls].ch[0],S[ls].ch[1]);
		if (rs) S[rs].rev^=1,swap(S[rs].ch[0],S[rs].ch[1]);
		S[x].rev=0;
	}
	return;
}

void Update(int x){
	S[x].dp=0;
	if (!S[x].Ms.empty()) S[x].dp=max(S[x].dp,(*(--S[x].Ms.end()))+1);
	if (S[x].ch[0]) S[x].dp=max(S[x].dp,S[S[x].ch[0]].dp+1);
	if (S[x].ch[1]) S[x].dp=max(S[x].dp,S[S[x].ch[1]].dp+1);
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

void Splay(int x){
	int now=x,top=1;St[1]=now;
	while (Isroot(now)==0) now=St[++top]=S[now].fa;
	while (top) PushDown(St[top--]);
	while (Isroot(x)==0){
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);return;
}
void Access(int x){
	int lastx=0;
	while (x){
		Splay(x);
		if (S[x].ch[1]) S[x].Ms.insert(S[S[x].ch[1]].dp);
		if (lastx) S[x].Ms.erase(S[x].Ms.find(S[lastx].dp));
		Update(S[x].ch[1]);S[x].ch[1]=lastx;Update(x);
		lastx=x;x=S[x].fa;
	}
	return;
}

void Makeroot(int x){
	Access(x);Splay(x);
	S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);return;
}

void Outp(){
	printf("fa ls rs dp MP:\n");
	for (int i=1;i<=n;i++){
		printf("%2d%3d%3d%3d ",S[i].fa,S[i].ch[0],S[i].ch[1],S[i].dp);
		for (multiset<int>::iterator it=S[i].Ms.begin();it!=S[i].Ms.end();it++)
			printf("%d ",(*it));
		printf("\n");
	}
	return;
}
/*
16
B -1
Q 1
B 1
Q 2
Q 1
B 2
Q 2
Q 3
Q 1
B 3
Q 1
Q 2
Q 3
B 3
Q 3
Q 5
//*/
