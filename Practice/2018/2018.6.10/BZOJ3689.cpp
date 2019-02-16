#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxBit=32;
const int inf=2147483647;

class Trie
{
public:
	int size;
	int son[2];
};

class HData
{
public:
	int key,id,kth;
};

int n,K;
int Val[maxN];
int nodecnt;
Trie T[maxN*20];
priority_queue<HData> H;

void Insert(int key);
int Query(int key,int kth);
bool operator < (HData A,HData B);

int main()
{
	nodecnt=1;
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	for (int i=1;i<=n;i++) Insert(Val[i]);

	for (int i=1;i<=n;i++) H.push((HData){Query(Val[i],2),i,2});
	//for (int i=1;i<=n;i++) cout<<Query(Val[i],1)<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Query(Val[i],2)<<" ";cout<<endl;

	K=K<<1;
	for (int i=1;i<=K;i++)
	{
		HData u=H.top();H.pop();
		if (i&1) printf("%d ",u.key);
		if (u.kth!=n) H.push((HData){Query(Val[u.id],u.kth+1),u.id,u.kth+1});
	}
	printf("\n");
	return 0;
}

void Insert(int key)
{
	int now=1;T[now].size++;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		if (T[now].son[bit]==0) T[now].son[bit]=++nodecnt;
		now=T[now].son[bit];T[now].size++;
	}
	return;
}

int Query(int key,int kth)
{
	int now=1,Ret=0;
	for (int i=maxBit-1;i>=0;i--)
	{
		int bit=((key&(1<<i))!=0);
		if (T[T[now].son[bit]].size>=kth){
			now=T[now].son[bit];
		}
		else{
			kth-=T[T[now].son[bit]].size;now=T[now].son[bit^1];Ret|=(1<<i);
			//cout<<i<<" ";
		}
	}
	//cout<<endl;
	return Ret;
}

bool operator < (HData A,HData B){
	return A.key>B.key;
}
