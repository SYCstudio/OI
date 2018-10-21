#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

class HeapData
{
public:
	int key;
	int ch[2],dis;
	void init()
		{
			ch[0]=ch[1]=dis=0;
			return;
		}
};

int n,m;
int UFS[maxN];
HeapData H[maxN];

int Merge(int x,int y);
void Div(int x);
int Find(int x);

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		for (int i=1;i<=n;i++) scanf("%d",&H[i].key),H[i].init(),UFS[i]=i;
		int m;scanf("%d",&m);
		while (m--)
		{
			int x,y;scanf("%d%d",&x,&y);
			if (Find(x)==Find(y))
			{
				printf("-1\n");
				continue;
			}
			x=Find(x);y=Find(y);
			if (H[x].key<H[y].key) swap(x,y);
			//printf("%d\n",H[x].key/2);
			Div(x);Div(y);x=Find(x);y=Find(y);
			int nrt=Merge(x,y);
			UFS[x]=UFS[y]=nrt;
			printf("%d\n",H[nrt].key);
		}
	}
}

int Merge(int x,int y)
{
	if (x==0) return y;
	if (y==0) return x;
	if (H[x].key<H[y].key) swap(x,y);
	H[x].ch[1]=Merge(H[x].ch[1],y);
	if (H[H[x].ch[0]].dis<H[H[x].ch[1]].dis) swap(H[x].ch[0],H[x].ch[1]);
	if (H[x].ch[1]) H[x].dis=H[H[x].ch[1]].dis+1;
	else H[x].dis=0;
	return x;
}

void Div(int x)
{
	if ((H[x].ch[0]==0)&&(H[x].ch[1]==0))
	{
		//cout<<"_Div:"<<x<<endl;
		H[x].key/=2;
		return;
	}
	//cout<<"Div:"<<x<<" "<<H[x].key<<" "<<H[x].ch[0]<<" "<<H[x].ch[1]<<endl;
	int nrt=Merge(H[x].ch[0],H[x].ch[1]);//cout<<"nrt:"<<nrt<<endl;
	UFS[nrt]=nrt;UFS[x]=x;
	if (nrt==H[x].ch[0]) if (H[x].ch[1]) UFS[H[x].ch[1]]=nrt;
	if (nrt==H[x].ch[1]) if (H[x].ch[0]) UFS[H[x].ch[0]]=nrt;
	H[x].init();H[x].key/=2;
	int nnrt=Merge(x,nrt);//cout<<"nnrt:"<<nnrt<<endl;
	UFS[nrt]=UFS[x]=nnrt;
	return;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
