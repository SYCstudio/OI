#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxBit=32;
const int inf=2147483647;

class Trie
{
public:
	int size;
	int son[2];
};

int n;
int Arr[maxN],L[maxN],R[maxN];
int nodecnt,root[maxN];
Trie T[maxN*30];

void Insert(int &rt,int key);
int Query(int r1,int r2,int key);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	for (int i=1;i<=n;i++)
	{
		int p=i,cnt=0;
		while ((p>=1)&&(cnt<=1))
			if (Arr[--p]>Arr[i]) cnt++;
		//cout<<i<<" "<<p<<" "<<cnt<<endl;
		L[i]=min(p+1,i);
		p=i;cnt=0;
		while ((p<=n)&&(cnt<=1))
			if (Arr[++p]>Arr[i]) cnt++;
		R[i]=max(p-1,i);
	}
	//for (int i=1;i<=n;i++) cout<<L[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<R[i]<<" ";cout<<endl;
	
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		Insert(root[i],Arr[i]);
	}

	int Ans=0;
	for (int i=1;i<=n;i++) Ans=max(Ans,Query(root[L[i]-1],root[R[i]],Arr[i]));

	printf("%d\n",Ans);
	return 0;
}

void Insert(int &rt,int key)
{
	T[++nodecnt]=T[rt];rt=nodecnt;
	T[rt].size++;
	int now=rt;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		T[++nodecnt]=T[T[now].son[bit]];T[now].son[bit]=nodecnt;
		now=T[now].son[bit];T[now].size++;
	}
	return;
}

int Query(int r1,int r2,int key)
{
	int Ret=0;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		if (T[T[r2].son[bit^1]].size-T[T[r1].son[bit^1]].size>0){
			Ret|=(1<<i);r1=T[r1].son[bit^1];r2=T[r2].son[bit^1];
		}
		else{
			r1=T[r1].son[bit];r2=T[r2].son[bit];
		}
	}
	return Ret;
}
