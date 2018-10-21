#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class HeapData
{
public:
	int key,pos;
};

bool operator < (HeapData A,HeapData B)
{
	return (A.key!=B.key)?(A.key<B.key):(A.pos<B.pos);
};

class Heap
{
public:
	HeapData H;
	int ch[2],dis;
};
const int maxN=100100;
const int inf=2147483647;

int n,m;
int UFS[maxN];
Heap H[maxN];
bool Del[maxN];

void Union(int x,int y);
int Merge(int rtx,int rty);
void TopDel(int x);
int Find(int x);
void Outp();

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&H[i].H.key),H[i].H.pos=i,UFS[i]=i;
	while (m--)
	{
		int opt;scanf("%d",&opt);
		if (opt==1)
		{
			int x,y;scanf("%d%d",&x,&y);
			Union(x,y);
		}
		if (opt==2)
		{
			int x;scanf("%d",&x);
			TopDel(x);
		}
		//Outp();
	}
	return 0;
}

void Union(int x,int y)
{
	if ((Del[x]==1)||(Del[y]==1)) return;
	x=Find(x);y=Find(y);
	if (x==y) return;
	int newrt=Merge(x,y);
	if (newrt==x) UFS[y]=x;
	else UFS[x]=y;
}

int Merge(int rtx,int rty)
{
	if (rtx==0) return rty;
	if (rty==0) return rtx;
	if (H[rty].H<H[rtx].H) swap(rtx,rty);
	H[rtx].ch[1]=Merge(H[rtx].ch[1],rty);
	if (H[H[rtx].ch[0]].dis<H[H[rtx].ch[1]].dis) swap(H[rtx].ch[0],H[rtx].ch[1]);
	if (H[rtx].ch[1]) H[rtx].dis=H[H[rtx].ch[1]].dis+1;
	else H[rtx].dis=0;
	return rtx;
}

void TopDel(int x)
{
	if (Del[x]==1)
	{
		printf("-1\n");
		return;
	}
	x=Find(x);
	printf("%d\n",H[x].H.key);
	Del[x]=1;
	int newrt=Merge(H[x].ch[0],H[x].ch[1]);
	if (newrt==H[x].ch[0])
	{
		if (H[x].ch[1]) UFS[H[x].ch[1]]=H[x].ch[0];
		UFS[H[x].ch[0]]=H[x].ch[0],UFS[x]=H[x].ch[0];
	}
	else
	{
		if (H[x].ch[0]) UFS[H[x].ch[0]]=H[x].ch[1];
		UFS[H[x].ch[1]]=H[x].ch[1],UFS[x]=H[x].ch[1];
	}
	return;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

void Outp()
{
	for (int i=1;i<=n;i++)
		cout<<i<<" "<<H[i].H.key<<" "<<H[i].ch[0]<<" "<<H[i].ch[1]<<" "<<H[i].dis<<" "<<Del[i]<<" "<<UFS[i]<<endl;
	cout<<endl;
}
