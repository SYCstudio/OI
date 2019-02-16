#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mcp(Arr,Brr) memcpy(Arr,Brr,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

class Splay_Data
{
public:
	int key;
	int ch[2];
	int cnt;
	int size;
	int fa;
	Splay_Data()
		{
			cnt=0;
			ch[0]=ch[1]=0;
			size=0;
		}
};

class SplayTree
{
public:
	int cnt;
	int root;
	Splay_Data S[maxN*50];
	SplayTree()
		{
			cnt=0;
			root=0;
			Insert(-inf);
			Insert(inf);
			return;
		}
	void Insert(int x)//插入数x
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
					root=cnt;
			}
			else
				S[now].cnt++;
			Splay(now,0);
			return;
		}
	void Find(int x)//找出数x并使之到根
		{
			int now=root;
			while ((S[now].key!=x)&&(S[now].ch[x>S[now].key]!=0))
			    now=S[now].ch[x>S[now].key];
			Splay(now,0);
			return;
		}
	void Splay(int x,int goal)//将点x旋转到goal
		{
			while (S[x].fa!=goal)
			{
				int y=S[x].fa;
				int z=S[y].fa;
				if (z!=goal)
					((S[z].ch[0]==y)^(S[y].ch[0]==x))?Ratate(x):Ratate(y);
				Ratate(x);
			}
			if (goal==0)
				root=x;
			return;
		}
	void Ratate(int x)//旋转点x
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
			Update(y);
			Update(x);
			return;
		}
	void Update(int x)//更新点x
		{
			S[x].size=S[x].cnt;
			if (S[x].ch[0]!=0)
				S[x].size+=S[S[x].ch[0]].size;
			if (S[x].ch[1]!=0)
				S[x].size+=S[S[x].ch[1]].size;
			return;
		}
	int Next(int x,int opt)//查询数x的前驱
		{
			Find(x);
			//cout<<S[root].key<<endl;
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
	int Size(int x)//查询x数的排名
		{
			Find(x);
			return S[S[root].ch[0]].size;//注意这里不再+1因为最前面有一个-inf
		}
	int Rank(int x)//查询排名为x的数
		{
			//cout<<"Rank:"<<x<<endl;
			int now=root;
			if (S[now].size<x)
				return 0;
			while (x!=0)
			{
				//cout<<now<<" "<<x<<endl;
				int lson=S[now].ch[0];
				if (S[lson].size+S[now].cnt<x)
				{
					x=x-S[lson].size-S[now].cnt;
					now=S[now].ch[1];
				}
				else if (x<=S[lson].size)
					now=lson;
				else
					return S[now].key;
			}
		}
	void Delete(int x)//删除数x
		{
			int pre=Next(x,0);
			int nex=Next(x,1);
			Splay(pre,0);
			Splay(nex,pre);
			int lson=S[nex].ch[0];
			if (S[lson].cnt>1)
			{
				S[lson].cnt--;
				Splay(lson,0);
			}
			else
				S[nex].ch[0]=0;
			return;
		}
	void Outp()
		{
			cout<<"SplayTree Size:"<<cnt<<endl;
			cout<<"Root:"<<root<<endl;
		    cout<<" key lson rson   fa  cnt size"<<endl;
			for (int i=1;i<=cnt;i++)
			{
				if (S[i].key==inf)
					printf(" inf ");
				else if (S[i].key==-inf)
					printf("-inf ");
				else printf ("%4d ",S[i].key);
				printf("%4d %4d %4d %4d %4d\n",S[i].ch[0],S[i].ch[1],S[i].fa,S[i].cnt,S[i].size);
			}
			return;
		}
};

SplayTree S;

int read();

int main()
{
	int n;
	n=read();
	while (n--)
	{
		int opt=read();
		if (opt==1)
		{
			int x=read();
			S.Insert(x);
		}
		if (opt==2)
		{
			int x=read();
			S.Delete(x);
		}
		if (opt==3)
		{
			int x=read();
			printf("%d\n",S.Size(x));
		}
		if (opt==4)
		{
			int x=read();
			printf("%d\n",S.Rank(x+1));//注意到因为多插入了-inf所以排名都+1
		}
		if (opt==5)
		{
			int x=read();
			printf("%d\n",S.S[S.Next(x,0)].key);
		}
		if (opt==6)
		{
			int x=read();
			printf("%d\n",S.S[S.Next(x,1)].key);
		}
		//S.Outp();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int read()
{
	int x=0,k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}
