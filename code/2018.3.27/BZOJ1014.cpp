#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100*4;
const ull hashbase=233;
const int inf=2147483647;

class SplayData
{
public:
	int size;
	int fa,ch[2];
	ull hash,key;
};

int n,nodecnt,root;
ull Hash[maxN];
SplayData S[maxN];
char Input[maxN];

void Update(int now);
void Rotate(int x);
void Splay(int x,int goal);
int Find(int kth);
void Insert(int pos,int key);
void Outp(int now);
ull GetHash(int ql,int qr);

int main()
{
	ios::sync_with_stdio(false);
	Hash[0]=1;for (int i=1;i<maxN;i++) Hash[i]=Hash[i-1]*hashbase;

	cin>>(Input+1);
	int len=strlen(Input+1);
	
	S[1].key=0;S[1].ch[1]=1;
	for (int i=1;i<=len;i++)
	{
		S[i+1].key=Input[i];
		S[i+1].fa=i;
		S[i].ch[1]=i+1;
	}
	S[len+2].key=0;S[len+1].ch[1]=len+2;S[len+2].fa=len+1;
	Splay(len+2,0);nodecnt=len+2;

	//Outp(root);cout<<endl;
	
	int m;cin>>m;
	int L=strlen(Input+1);
	while (m--)
	{
		char opt;cin>>opt;
		if (opt=='Q')
		{
			int x,y;cin>>x>>y;
			if (x>y) swap(x,y);
			int l=1,r=L-y+1;
			int Ans=0;
			do
			{
				int mid=(l+r)>>1;
				if (GetHash(x,x+mid-1)==GetHash(y,y+mid-1)) Ans=mid,l=mid+1;
				else r=mid-1;
			}
			while (l<=r);
			cout<<Ans<<endl;
		}
		if (opt=='R')
		{
			int x;char ch;cin>>x>>ch;
			x=Find(x+1);
			Splay(x,0);
			S[x].key=ch;Update(x);
		}
		if (opt=='I')
		{
			int x;char ch;cin>>x>>ch;
			Insert(x,ch);L++;
		}
		//Outp(root);cout<<endl;
	}
	return 0;
}

void Update(int now)
{
	S[now].hash=S[S[now].ch[0]].hash*Hash[S[S[now].ch[1]].size+1]+S[now].key*Hash[S[S[now].ch[1]].size]+S[S[now].ch[1]].hash;
	S[now].size=S[S[now].ch[0]].size+S[S[now].ch[1]].size+1;
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

void Splay(int x,int goal)
{
	while (S[x].fa!=goal)
	{
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0])?(Rotate(x)):(Rotate(y)));
		Rotate(x);
	}
	Update(x);
	if (goal==0) root=x;
	return;
}

int Find(int kth)
{
	int now=root;
	while (1)
	{
		int l=S[now].ch[0];
		if (S[l].size>=kth) now=l;
		else if (S[l].size+1==kth) return now;
		else kth=kth-S[l].size-1,now=S[now].ch[1];
	}
}

void Insert(int pos,int key)
{
	int l=Find(pos+1),r=Find(pos+2);
	Splay(l,0);Splay(r,l);
	nodecnt++;
	S[nodecnt].key=key;S[nodecnt].fa=r;S[r].ch[0]=nodecnt;
	Splay(nodecnt,0);return;
}

ull GetHash(int ql,int qr)
{
	int l=Find(ql),r=Find(qr+2);
	Splay(l,0);Splay(r,l);
	return S[S[r].ch[0]].hash;
}

void Outp(int now)
{
	if (S[now].ch[0]) Outp(S[now].ch[0]);
	cout<<(char)(S[now].key);
	if (S[now].ch[1]) Outp(S[now].ch[1]);
	return;
}
