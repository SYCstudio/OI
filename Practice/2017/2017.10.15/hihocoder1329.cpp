#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=10000101;
const int inf=2147483647;

class SplayData
{
public:
	int fa,ch[2],key,cnt,size;
	SplayData()
		{
			ch[0]=ch[1]=0;
			cnt=0;
			size=0;
		}
};

class SplayTree
{
public:
	int cnt;
	int root;
	SplayData S[maxN];
	SplayTree()
		{
			root=0;
			cnt=0;
			Insert(-inf);
			Insert(inf);
		}
	void Insert(int x)
		{
			int now=root;
			int nowf=0;
			while ((now!=0)&&(S[now].key!=x))
			{
				nowf=now;
				now=S[now].ch[x>S[now].key];
			}
			if (now==0)
			{
				cnt++;
				now=cnt;
				S[cnt].fa=nowf;
				S[cnt].cnt=S[cnt].size=1;
				S[cnt].key=x;
				if (nowf!=0)
					S[nowf].ch[x>S[nowf].key]=cnt;
				if (root==0)
					root=1;
			}
			else
				S[now].cnt++;
			Splay(now,0);
			return;
		}
	bool Find(int x)
		{
			int now=root;
			if (root==0)
				return 0;
			while ((S[now].ch[x>S[now].key]!=0)&&(x!=S[now].key))
			{
				//cout<<now<<endl;
				now=S[now].ch[x>S[now].key];
			}
			//cout<<now<<endl;
			Splay(now,0);
			if (x!=S[now].key)
				return 0;
			return 1;
		}
	void Rotate(int x)
		{
			int y=S[x].fa;
			int z=S[y].fa;
			int k1=S[y].ch[1]==x;
			int k2=S[z].ch[1]==y;
			S[z].ch[k2]=x;
			S[x].fa=z;
			S[y].ch[k1]=S[x].ch[k1^1];
			S[S[x].ch[k1^1]].fa=y;
			S[x].ch[k1^1]=y;
			S[y].fa=x;
			return;
		}
	void Splay(const int x,int goal)
		{
			while (S[x].fa!=goal)
			{
				int y=S[x].fa;
				int z=S[y].fa;
				if (z!=goal)
					((S[z].ch[0]==y)^(S[y].ch[0]==x))?Rotate(x):Rotate(y);
				Rotate(x);
			}
			if (goal==0)
				root=x;
			return;
		}
	int Next(int x,int opt)
		{
			Find(x);
			int now=root;
			if ((S[now].key<x)&&(opt==0))
				return now;
			if ((S[now].key>x)&&(opt==1))
				return now;
			now=S[now].ch[opt];
			while (S[now].ch[opt^1]!=0)
				now=S[now].ch[opt^1];
			return now;
		}
	void DeleteRange(int l,int r)
		{
			Insert(l);
			Insert(r);
			int prep=Next(l,0);
			int nex=Next(r,1);
			Splay(prep,0);
			Splay(nex,prep);
			S[nex].ch[0]=0;
			return;
		}
	void Outp()
		{
			cout<<"SplaySize:"<<cnt<<endl;
			cout<<"Root:"<<root<<endl;
			for (int o=1;o<=cnt;o++)
				cout<<o<<" "<<S[o].key<<" "<<S[o].ch[0]<<" "<<S[o].ch[1]<<" "<<S[o].fa<<endl;
			return;
		}
};

int n;
SplayTree SP;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char opt;
		opt=getchar();
		while ((opt!='I')&&(opt!='Q')&&(opt!='D'))
			opt=getchar();
		if (opt=='I')
		{
			int k;
			scanf("%d",&k);
			SP.Insert(k);
		}
		if (opt=='Q')
		{
			int k;
			scanf("%d",&k);
			if (SP.Find(k))
			{
				printf("%d\n",k);
				continue;
			}
			int prep=SP.Next(k,0);
			printf("%d\n",SP.S[prep].key);
		}
		if (opt=='D')
		{
			int l,r;
			scanf("%d%d",&l,&r);
			SP.DeleteRange(l,r);
		}
		//SP.Outp();
	}
	return 0;
}
