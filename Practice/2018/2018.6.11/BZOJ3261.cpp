#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x)  memset(Arr,x,sizeof(Arr))

const int maxN=301000*2;
const int maxBit=32;
const int inf=2147483647;

class Trie
{
public:
	int size;
	int son[2];
};

int n,m;
int nodecnt,root[maxN];
Trie T[maxN*25];

void Insert(int &rt,int key);
int Query(int rt1,int rt2,int key);
void outp(int u);

int main()
{
	scanf("%d%d",&n,&m);
	int sum=0;Insert(root[1],0);
	for (int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		sum^=x;root[i+1]=root[i];Insert(root[i+1],sum);
	}

	/*
	for (int i=1;i<=n+1;i++)
	{
		cout<<i<<":"<<endl;
		outp(root[i]);
	}
	//*/

	for (int i=1;i<=m;i++)
	{
		char opt;cin>>opt;//scanf("\n%c",&opt);
		if (opt=='Q')
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",Query(root[l-1],root[r],x^sum));
		}
		else
		{
			int x;scanf("%d",&x);
			sum^=x;n++;root[n+1]=root[n];Insert(root[n+1],sum);
		}
	}

	return 0;
}

void Insert(int &rt,int key)
{
	T[++nodecnt]=T[rt];rt=nodecnt;T[rt].size++;
	int now=rt;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		T[++nodecnt]=T[T[now].son[bit]];T[now].son[bit]=nodecnt;
		now=T[now].son[bit];T[now].size++;
	}
	return;
}

int Query(int rt1,int rt2,int key)
{
	//cout<<"Query:"<<rt1<<" "<<rt2<<" "<<key<<endl;
	int Ret=0;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		//cout<<T[rt1].son[bit^1]<<" "<<T[rt2].son[bit^1]<<endl;
		if (T[T[rt2].son[bit^1]].size-T[T[rt1].son[bit^1]].size>0){
			rt1=T[rt1].son[bit^1];rt2=T[rt2].son[bit^1];Ret|=(1<<i);
		}
		else{
			rt1=T[rt1].son[bit];rt2=T[rt2].son[bit];
		}
	}
	return Ret;
}

void outp(int u)
{
	if (T[u].son[0]) cout<<u<<" -> "<<T[u].son[0]<<" ["<<0<<"]"<<endl;
	if (T[u].son[1]) cout<<u<<" -> "<<T[u].son[1]<<" ["<<1<<"]"<<endl;
	if (T[u].son[0]) outp(T[u].son[0]);
	if (T[u].son[1]) outp(T[u].son[1]);
	return;
}
