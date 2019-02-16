#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10010;
const int maxM=100100*2;
const int inf=2147483647;

class Splay_Data
{
public:
    int key,mx;
    int fa,ch[2],rev;
    Splay_Data()
	{
	    fa=ch[0]=ch[1]=rev=0;
	    return;
	}
};

int n,m,C,K;
int Stack[maxN];

class Link_Cut_Tree
{
public:
    int cnt,root;
    Splay_Data S[maxN];
    Link_Cut_Tree()
	{
	    cnt=root=0;
	}
    int Is_root(int x)
	{
	    if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
	    return 1;
	}
    void Update(int x)
	{
	    int lson=S[x].ch[0],rson=S[x].ch[1];
	    S[x].mx=max(max(S[lson].mx,S[rson].mx),S[x].key);
	    return;
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
    void Rotate(int x)
	{
	    int y=S[x].fa;int z=S[y].fa;
	    int sx=(x==S[y].ch[1]);
	    int sy=(y==S[z].ch[1]);
	    S[x].fa=z;if (Is_root(y)==0) S[z].ch[sy]=x;
	    if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;S[y].ch[sx]=S[x].ch[sx^1];
	    S[y].fa=x;S[x].ch[sx^1]=y;
	    Update(y);Update(x);
	    return;
	}
    void Splay(int x)
	{
	    int stacktop=1;Stack[stacktop]=x;
	    int now=x;
	    while (Is_root(now)==0)
	    {
			stacktop++;Stack[stacktop]=S[now].fa;
			now=S[now].fa;
	    }
	    for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	    while (Is_root(x)==0)
	    {
			int y=S[x].fa;int z=S[y].fa;
			if (Is_root(y)==0)
				((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
			Rotate(x);
	    }
	    return;
	}
    void Access(int x)
	{
	    int lastx=0;
	    while (x)
	    {
			Splay(x);
			S[x].ch[1]=lastx;
			Update(x);lastx=x;
			x=S[x].fa;
	    }
	    return;
	}
    void Makeroot(int x)
	{
	    Access(x);Splay(x);
	    S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	    return;
	}
    int Findroot(int x)
	{
	    Access(x);Splay(x);
	    //Outp();cout<<endl;
	    int now=x;
	    //cout<<now<<" "<<S[now].ch[0]<<endl;
	    while (S[now].ch[0]) now=S[now].ch[0];
	    return now;
	}
    void Split(int x,int y)
	{
	    Makeroot(x);Access(y);Splay(y);
	    return;
	}
    void Link(int x,int y)
	{
	    //cout<<"Link:"<<x<<" "<<y<<endl;
	    Makeroot(x);S[x].fa=y;Update(y);
	    return;
	}
    void Cut(int x,int y)
	{
	    Split(x,y);S[x].fa=S[y].ch[0]=0;Update(x);Update(y);
	    return;
	}
    void Outp()
	{
	    printf("id key fa ls rs mx\n");
	    //for (int i=1;i<=n;i++)
	    //printf("%2d%4d%3d%3d%3d%3d\n",i,S[i].key,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].mx);
	    for (int i=1;i<=n;i++)
			if (Is_root(i))
			{
				cout<<"root:"<<i<<endl;
				_outp(i);
			}
	    return;
	}
    void _outp(int x)
	{
	    if (S[x].ch[0]) _outp(S[x].ch[0]);
	    printf("%2d%4d%3d%3d%3d%3d\n",x,S[x].key,S[x].fa,S[x].ch[0],S[x].ch[1],S[x].mx);
	    if (S[x].ch[1]) _outp(S[x].ch[1]);
	}
};

Link_Cut_Tree LCT[11];
int Color[maxN][11];//统计每一个点出来的边的颜色的个数
int cnt=-1,Head[maxN],Next[maxM],V[maxM],Cedge[maxM];

void Add_Edge(int u,int v,int color);

int main()
{
    //freopen("networkzj.in","r",stdin);
    //freopen("networkzj.out","w",stdout);
    mem(Head,-1);
    scanf("%d%d%d%d",&n,&m,&C,&K);
    for (int i=1;i<=n;i++)
    {
		//cout<<"A "<<i<<endl;
		int key;scanf("%d",&key);
		for (int j=0;j<C;j++) LCT[j].S[i].key=key;
    }
    //LCT[0].Outp();
    mem(Color,0);
    for (int i=1;i<=m;i++)
    {
		//cout<<"B "<<i<<endl;
		int u,v,c;scanf("%d%d%d",&u,&v,&c);
		Color[u][c]++;Color[v][c]++;
		//cout<<"Color:"<<c<<endl;
		//cout<<"Before Link:"<<endl;
		//LCT[c].Outp();
		LCT[c].Link(u,v);
		//cout<<"After Link:"<<endl;
		//LCT[c].Outp();
		Add_Edge(u,v,c);
		Add_Edge(v,u,c);
    }
    //LCT[0].Outp();
    while (K--)
    {
		//cout<<"C "<<K<<endl;
		int opt;scanf("%d",&opt);
		if (opt==0)
		{
			int pos,key;scanf("%d%d",&pos,&key);
			for (int i=0;i<C;i++)
			{
				LCT[i].Makeroot(pos);
				LCT[i].S[pos].key=key;
				LCT[i].Update(pos);
			}
		}
		if (opt==1)
		{
			int u,v,c;scanf("%d%d%d",&u,&v,&c);
			int id=-1;
			for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]==v){id=i;break;}
			if (id==-1) printf("No such edge.\n");//不存在这样的边
			else if (c==Cedge[id]) printf("Success.\n");//特判颜色一样的情况
			else if ((Color[u][c]>=2)||(Color[v][c]>=2)) printf("Error 1.\n");//加上这条边后，u或v出发的同种颜色数量大于2
			else if (LCT[c].Findroot(u)==LCT[c].Findroot(v)) printf("Error 2.\n");//已经连通
			else
			{
				LCT[Cedge[id]].Cut(u,v);
				LCT[c].Link(u,v);
				Color[u][Cedge[id]]--;Color[v][Cedge[id]]--;
				Color[u][c]++;Color[v][c]++;
				Cedge[id]=Cedge[id^1]=c;
				printf("Success.\n");
			}
		}
		if (opt==2)
		{
			int c,u,v;scanf("%d%d%d",&c,&u,&v);
			//cout<<c<<" "<<u<<" "<<v<<endl;
			//LCT[c].Outp();
			//cout<<LCT[c].Findroot(u)<<endl;
			//cout<<LCT[c].Findroot(v)<<endl;
			if (LCT[c].Findroot(u)!=LCT[c].Findroot(v)) printf("-1\n");
			else
			{
				LCT[c].Split(u,v);
				printf("%d\n",LCT[c].S[v].mx);
			}
		}
    }
    return 0;
}

void Add_Edge(int u,int v,int color)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;Cedge[cnt]=color;
    return;
}
