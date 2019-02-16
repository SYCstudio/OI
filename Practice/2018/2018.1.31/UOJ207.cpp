#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=400100;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int rev;
	int key;
	int sum;
	int vsum;
};

int n,m;
Splay_Data S[maxN];
int Stack[maxN];
int scnt=0,S1[maxN],S2[maxN],Sxor[maxN];

bool Isroot(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
int make(int l,int r);
void Outp();

int main()
{
	srand(141936+141905);
	scanf("%d",&n);scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Link(u,v);
	}
	int xorsum=0;
	for (int i=1;i<=m;i++)
	{
		int type;
		scanf("%d",&type);
		if (type==1)
		{
			int x,y,u,v;scanf("%d%d%d%d",&x,&y,&u,&v);
			Cut(x,y);Link(u,v);
		}
		if (type==2)
		{
			int x,y;scanf("%d%d",&x,&y);
			scnt++;S1[scnt]=x;S2[scnt]=y;Sxor[scnt]=make(1,1000000000);
			Makeroot(x);Splay(x);S[x].key^=Sxor[scnt];Update(x);
			Makeroot(y);Splay(y);S[y].key^=Sxor[scnt];Update(y);
			xorsum^=Sxor[scnt];
			//cout<<"xor:"<<Sxor[scnt]<<endl;
		}
		if (type==3)
		{
			int id;scanf("%d",&id);
			int x=S1[id],y=S2[id];
			//cout<<"x y:"<<x<<" "<<y<<endl;
			Makeroot(x);Splay(x);S[x].key^=Sxor[id];Update(x);
			Makeroot(y);Splay(y);S[y].key^=Sxor[id];Update(y);
			//cout<<S[y].key<<" "<<S[y].sum<<endl;
			xorsum^=Sxor[id];
		}
		if (type==4)
		{
			int x,y;scanf("%d%d",&x,&y);
			Makeroot(x);Access(y);Splay(y);
			//cout<<"sum:"<<S[x].sum<<endl;
			if (S[x].sum==xorsum) printf("YES\n");
			else printf("NO\n");
		}
		//Outp();
		//cout<<"xorsum:"<<xorsum<<endl;
	}
	return 0;
}

bool Isroot(int x)
{
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		int lson=S[x].ch[0],rson=S[x].ch[1];
		swap(S[lson].ch[0],S[lson].ch[1]);
		swap(S[rson].ch[0],S[rson].ch[1]);
		if (lson) S[lson].rev^=1;
		if (rson) S[rson].rev^=1;
	}
	return;
}

void Update(int x)
{
	S[x].sum=S[S[x].ch[0]].sum^S[S[x].ch[1]].sum^S[x].key^S[x].vsum;
	return;
}

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);Update(x);return;
}

void Splay(int x)
{
	int now=x,stacktop=1;Stack[1]=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=S[now].fa;now=S[now].fa;
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):Rotate(y);
		Rotate(x);
	}
	Update(x);return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].vsum^=S[lastx].sum^S[S[x].ch[1]].sum;
		S[x].ch[1]=lastx;Update(x);
		lastx=x;x=S[x].fa;
	}
	return;
}

void Makeroot(int x)
{
	Access(x);Splay(x);S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	return;
}

int Findroot(int x)
{
	Access(x);Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Link(int x,int y)
{
	Makeroot(x);Makeroot(y);S[y].vsum^=S[x].sum;
	S[x].fa=y;
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[x].fa=S[y].ch[0]=0;Update(x);Update(y);
	return;
}

int make(int l,int r)
{
	double dou=1.0*rand()/RAND_MAX;
	return dou*(r-l+1)+l;
}

void Outp()
{
	printf("id fa ls rs       key        sum        vsum\n");
	for (int i=0;i<=n;i++) printf("%2d%3d%3d%3d%10d%11d%12d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].key,S[i].sum,S[i].vsum);
	cout<<endl;
	return;
}
