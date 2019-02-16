#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40010;
const int inf=2147483647;

class Heap
{
public:
    int cnt;
    int H[maxN];
    Heap()
		{
			cnt=0;
		}
    void Push(int x)
		{
			cnt++;
			H[cnt]=x;
			int now=cnt;
			int fa=now/2;
			while ((fa!=0)&&(H[fa]<H[now]))
			{
				swap(H[fa],H[now]);now=fa;fa=now/2;
			}
		}
    int Top()
		{
			if (Empty()) return 0;
			return H[1];
		}
    void Pop()
		{
			if (Empty()) return;
			swap(H[1],H[cnt]);
			cnt--;
			int now=1;
			int lson=now*2,rson=now*2+1;
			while (lson<=cnt)
			{
				int mxid=lson;
				if ((rson<=cnt)&&(H[rson]>H[lson])) mxid=rson;
				if (H[mxid]>H[now])
				{
					swap(H[now],H[mxid]);
					now=mxid;
					lson=now*2;rson=now*2+1;
				}
				else break;
			}
		}
    bool Empty()
		{
			return cnt==0;
		}
};

class Edge
{
public:
    int w,nex;
};

class Modefy
{
public:
    int a,b,h;
};

int n;
Heap H1,H2;
int cnt=0,Head[maxN*2];
Edge E[maxN*2];
int numcnt=0,Num[maxN*2];
map<int,int> M;
Modefy Mdf[maxN];

void Add_Edge(int u,int w);

int main()
{
    mem(Head,-1);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
		scanf("%d%d%d",&Mdf[i].a,&Mdf[i].b,&Mdf[i].h);
		if (M[Mdf[i].a]==0) Num[++numcnt]=Mdf[i].a;
		if (M[Mdf[i].b]==0) Num[++numcnt]=Mdf[i].b;
		M[Mdf[i].a]=1;M[Mdf[i].b]=1;
    }
    sort(&Num[1],&Num[numcnt+1]);
    for (int i=1;i<=numcnt;i++) M[Num[i]]=i;
    for (int i=1;i<=n;i++)
    {
		Add_Edge(M[Mdf[i].a],Mdf[i].h);
		Add_Edge(M[Mdf[i].b],-Mdf[i].h);
    }
    H1.Push(0);
    ll sum=0;
    //cout<<endl;
    for (int i=1;i<numcnt;i++)
    {
		for (int j=Head[i];j!=-1;j=E[j].nex)
			if (E[j].w>0) H1.Push(E[j].w);
			else H2.Push(-E[j].w);
		while ((!H1.Empty())&&(!H2.Empty())&&(H1.Top()==H2.Top()))
		{
			H1.Pop();H2.Pop();
		}
		//cout<<H1.Top()<<" "<<Num[i]<<" "<<Num[i+1]<<endl;
		sum=sum+(ll)H1.Top()*(Num[i+1]-Num[i]);
    }
    printf("%lld\n",sum);
    return 0;
}

void Add_Edge(int u,int w)
{
    cnt++;E[cnt].nex=Head[u];Head[u]=cnt;
    E[cnt].w=w;
    return;
}
