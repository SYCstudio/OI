#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ls S[x].ch[0]
#define rs S[x].ch[1]

const int maxN=101000;
const int inf=2147483647;

class SplayData
{
public:
	int fa,ch[2],sz;
	int cov,rev,nega;
	int key;
	int premax,premin,sufmax,sufmin,sum;
};

int n,m,root;
char Input[maxN];
SplayData S[maxN];

void Update(int x);
void Cover(int x,int key);
void Reverse(int x);
void Nega(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x,int goal);
int Kth(int kth);
void Outp();

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",Input+1);
	for (int i=1;i<=n;i++)
	{
		if (Input[i]==')') S[i].key=S[i].sum=S[i].premax=S[i].sufmax=1;
		else S[i].key=S[i].sum=S[i].premin=S[i].sufmin=-1;
	}
	for (int i=2;i<=n;i++) S[i].fa=i-1,S[i-1].ch[1]=i;
	S[1].fa=n+1;S[n+2].fa=n;S[n].ch[1]=n+2;S[n+1].ch[1]=1;
	root=n+1;Splay(n+2,0);

	//Outp();

	//cout<<"Init"<<endl;
	Splay(n+2,0);
	//cout<<"finish"<<endl;

	while (m--)
	{
		int opt;scanf("%d",&opt);
		if (opt==2){
			int l,r;scanf("%d%d",&l,&r);
			int pl=Kth(l),pr=Kth(r+2);
			Splay(pl,0);PushDown(pl);Splay(pr,pl);PushDown(pr);
			Reverse(S[pr].ch[0]);
		}
		if (opt==1){
			int l,r;scanf("%d%d",&l,&r);
			int pl=Kth(l),pr=Kth(r+2);
			Splay(pl,0);PushDown(pl);Splay(pr,pl);PushDown(pr);
			Nega(S[pr].ch[0]);
		}
		if (opt==0){
			int l,r;scanf("%d%d",&l,&r);
			int pl=Kth(l),pr=Kth(r+2);
			Splay(pl,0);PushDown(pl);Splay(pr,pl);PushDown(pr);
			int c=S[pr].ch[0];
			printf("%d\n",(S[c].premax+1)/2+(abs(S[c].sufmin)+1)/2);
		}
		//Outp();
	}

	return 0;
}

void Update(int x)
{
	S[x].sum=S[ls].sum+S[x].key+S[rs].sum;S[x].sz=S[ls].sz+S[rs].sz+1;
	S[x].premax=max(max(S[ls].premax,S[ls].sum+S[x].key),S[ls].sum+S[x].key+S[rs].premax);
	S[x].premin=min(min(S[ls].premin,S[ls].sum+S[x].key),S[ls].sum+S[x].key+S[rs].premin);
	S[x].sufmax=max(max(S[ls].sufmax+S[x].key+S[rs].sum,S[x].key+S[rs].sum),S[rs].sufmax);
	S[x].sufmin=min(min(S[ls].sufmin+S[x].key+S[rs].sum,S[x].key+S[rs].sum),S[rs].sufmin);
	return;
}

void Cover(int x,int key)
{
	S[x].rev=S[x].nega=0;
	S[x].key=S[x].cov=key;S[x].sum=S[x].sz*key;
	if (key==1){
		S[x].premax=S[x].sufmax=S[x].sz;S[x].premin=S[x].sufmin=0;
	}
	else{
		S[x].premin=S[x].sufmin=-S[x].sz;S[x].premax=S[x].sufmax=0;
	}
	return;
}

void Reverse(int x)
{
	swap(S[x].ch[0],S[x].ch[1]);
	S[x].rev^=1;
	swap(S[x].premax,S[x].sufmax);swap(S[x].premin,S[x].sufmin);
	return;
}

void Nega(int x)
{
	S[x].key*=-1;S[x].sum*=-1;
	S[x].nega^=1;
	S[x].premax*=-1;S[x].premin*=-1;S[x].sufmin*=-1;S[x].sufmax*=-1;
	swap(S[x].premax,S[x].premin);swap(S[x].sufmin,S[x].sufmax);
	return;
}

void PushDown(int x)
{
	if (S[x].cov!=0){
		if (ls) Cover(ls,S[x].cov);
		if (rs) Cover(rs,S[x].cov);
		S[x].cov=0;
	}
	if (S[x].rev){
		if (ls) Reverse(ls);
		if (rs) Reverse(rs);
		S[x].rev=0;
	}
	if (S[x].nega){
		if (ls) Nega(ls);
		if (rs) Nega(rs);
		S[x].nega=0;
	}
	return;
}

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

int St[maxN];

void Splay(int x,int goal)
{
	int now=x,top=1;St[top]=x;
	while (now!=root) now=S[now].fa,St[++top]=now;
	while (top) PushDown(St[top--]);

	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		if (S[y].fa!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	if (goal==0) root=x;
	return;
}

int Kth(int kth)
{
	int now=root;
	while (1)
	{
		PushDown(now);
		if (S[S[now].ch[0]].sz>=kth) now=S[now].ch[0];
		else if (kth==S[S[now].ch[0]].sz+1) return now;
		else kth-=(S[S[now].ch[0]].sz+1),now=S[now].ch[1];
	}
}

void Outp()
{
	for (int i=1;i<=n+2;i++) for (int j=1;j<=n+2;j++) PushDown(j);
	cout<<"root:"<<root<<endl;
	printf("id ls rs fa sz key pmx pmn smx smn sum cov rev nega\n");
	for (int i=1;i<=n+2;i++)
		printf("%2d%3d%3d%3d%3d%4d%4d%4d%4d%4d%4d%4d%4d%5d\n",i,S[i].ch[0],S[i].ch[1],S[i].fa,S[i].sz,S[i].key,S[i].premax,S[i].premin,S[i].sufmax,S[i].sufmin,S[i].sum,S[i].cov,S[i].rev,S[i].nega);
	return;
}
/*
9 11
(())(()))
Q 1 4
Q 1 6
Q 4 9
I 2 6
Q 1 4
Q 3 8
S 3 6
Q 1 4
Q 2 5
R 2 5 (
Q 2 9
//*/
