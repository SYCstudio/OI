#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300100;
const int inf=2147483647;

class Splay_Data
{
public:
	int key;
	int fa,ch[2];
	int xorsum;
	int rev;
	Splay_Data()
	{
		xorsum=0;rev=0;fa=ch[0]=ch[1]=0;
		return;
	}
	void clear()
	{
		key=fa=ch[0]=ch[1]=xorsum=rev=0;
		return;
	}
};

int n,m;

class Link_Cut_Tree
{
public:
	int cnt,root;
	Splay_Data S[maxN];
	int Stack[maxN];
	Link_Cut_Tree()
	{
		cnt=root=0;
		return;
	}
	bool Is_root(int x)
	{
		if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
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
		S[x].xorsum=S[S[x].ch[0]].xorsum^S[S[x].ch[1]].xorsum^S[x].key;
		return;
	}
	void Rotate(int x)
	{
		int y=S[x].fa,z=S[y].fa;
		//cout<<"Rotate:"<<x<<" "<<y<<" "<<z<<" ";
		//cout<<S[z].ch[0]<<" "<<S[z].ch[1]<<" "<<Is_root(y)<<endl;
		//cout<<"Rotate:"<<x<<"["<<S[x].ch[0]<<","<<S[x].ch[1]<<","<<S[x].fa<<"] "<<y<<"["<<S[y].ch[0]<<","<<S[y].ch[1]<<","<<S[y].fa<<"] "<<z<<"["<<S[z].ch[0]<<","<<S[z].ch[1]<<","<<S[z].fa<<"]"<<endl;
		int sx=(x==S[y].ch[1]);
		int sy=(y==S[z].ch[1]);
		//cout<<"sx:"<<sx<<" sy:"<<sy<<endl;
		if (Is_root(y)==0)//注意这里要判断y是否为根，同时注意顺序
			S[z].ch[sy]=x;
		S[x].fa=z;
		if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
		S[y].ch[sx]=S[x].ch[sx^1];
		S[y].fa=x;S[x].ch[sx^1]=y;
		Update(y);Update(x);
		//cout<<"Totate:"<<x<<"["<<S[x].ch[0]<<","<<S[x].ch[1]<<","<<S[x].fa<<"] "<<y<<"["<<S[y].ch[0]<<","<<S[y].ch[1]<<","<<S[y].fa<<"] "<<z<<"["<<S[z].ch[0]<<","<<S[z].ch[1]<<","<<S[z].fa<<"]"<<endl;
		return;
	}
	void Splay(int x)
	{
		int stacktop=0;//首先要把所有的标记放下来
		int now=x;
		//cout<<"BeforePushDown:"<<endl;
		//Outp();
		stacktop++;Stack[stacktop]=now;//注意这里要提前就把x放进去，因为x是一定要更新的。。
		while (Is_root(now)==0)
		{
			stacktop++;Stack[stacktop]=S[now].fa;
			now=S[now].fa;
		}
		for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
		//cout<<"AfterPushDown:"<<endl;
		//Outp();
		while (Is_root(x)==0)
		{
			int y=S[x].fa;int z=S[y].fa;
			//cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<"[sxfa:"<<S[x].fa<<" sxfals:"<<S[S[x].fa].ch[0]<<" sxfars:"<<S[S[x].fa].ch[1]<<"]"<<endl;
			if (Is_root(y)==0)
				((S[y].ch[0]==x)^(S[z].ch[0]==y))?(Rotate(x)):(Rotate(y));
			Rotate(x);
			//Outp();
		}
		return;
	}
	void Access(int x)
	{
		//cout<<"Access begin!"<<endl;
		int lastx=0;
		while (x)
		{
			Splay(x);
			S[x].ch[1]=lastx;
			Update(x);lastx=x;
			x=S[x].fa;
		}
		//cout<<"Access end!"<<endl;
		return;
	}
	void Makeroot(int x)
	{
		//cout<<"Makeroot begin!"<<endl;
		Access(x);Splay(x);
		S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
		//cout<<"Makeroot end!"<<endl;
		return;
	}
	int Findroot(int x)
	{
		//cout<<"Findroot begin!"<<endl;
		Access(x);Splay(x);
		int now=x;
		while (S[now].ch[0]) now=S[now].ch[0];
		//cout<<"Findroot end!"<<endl;
		return now;
	}
	void Split(int x,int y)//找出x到y的路径，执行结束后，x与y在同一Splay内，x在Splay的最左边（即原树的根），y为Splay的根
	{
		//cout<<"Split begin!"<<endl;
		Makeroot(x);Access(y);Splay(y);
		//cout<<"Split end!"<<endl;
		return;
	}
	void Cut(int x,int y)
	{
		//cout<<"Cut begin!"<<endl;
		Split(x,y);S[x].fa=S[y].ch[0]=0;
		//cout<<"Cut end!"<<endl;
		return;
	}
	void Link(int x,int y)
	{
		//cout<<"Link begin!"<<endl;
		Makeroot(x);S[x].fa=y;
		//cout<<"Link end!"<<endl;
		return;
	}
	void Outp()
	{
		printf("id key fa ls rs sum \n");
		for (int i=0;i<=n;i++)
			printf("%2d%4d%3d%3d%3d%4d\n",i,S[i].key,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].xorsum);
		cout<<endl;
		return;
	}
};

Link_Cut_Tree LCT;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&LCT.S[i].key),LCT.Update(i);
	int mi=1;
	while (m--)
	{
		//LCT.S[0].fa=LCT.S[0].ch[0]=LCT.S[0].ch[1]=0;
		//LCT.Outp();
		LCT.S[0].clear();
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		//cout<<opt<<" "<<x<<" "<<y<<endl;
		if (opt==0)
		{
			//cout<<"F"<<endl;
			//cout<<mi<<" ";
			LCT.Split(x,y);printf("%d\n",LCT.S[y].xorsum);
		}
		//else cout<<mi<<endl;
		if (opt==1)
			if (LCT.Findroot(x)!=LCT.Findroot(y))
				LCT.Link(x,y);
		if (opt==2)
			if (LCT.Findroot(x)==LCT.Findroot(y))
				LCT.Cut(x,y);
		if (opt==3)
		{
			LCT.Access(x);LCT.Splay(x);
			LCT.S[x].key=y;
			LCT.Update(x);
		}
		mi++;
	}
	return 0;
}
