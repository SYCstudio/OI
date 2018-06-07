// Copyright (C) 2017 SYCstudio.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mcp(Arr,Brr) memcpy(Arr,Brr,sizeof(Arr))

const int maxN=80010;
const int Mod=1000000;
const int inf=2147483647;

class SplayData
{
public:
	int key;
	int size;
	int fa;
	int ch[2];
	SplayData()
		{
			ch[0]=ch[1]=0;
		}
};

class SplayTree
{
public:
	int cnt;
	int root;
	SplayData S[maxN*4];
	SplayTree()
		{
			cnt=root=0;
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
				S[cnt].key=x;
				S[cnt].size=1;
				S[cnt].fa=nowf;
				if (nowf!=0)
					S[nowf].ch[x>S[nowf].key]=cnt;
				if (root==0)
					root=cnt;
			}
			Splay(now,0);
			return;
		}
	void Ratate(int x)
		{
			int y=S[x].fa;
			int z=S[y].fa;
			int k1=S[y].ch[1]==x;
			int k2=S[z].ch[1]==y;
			S[z].ch[k2]=x;
			S[x].fa=z;
			S[y].ch[k1]=S[x].ch[k1^1];
			S[S[x].ch[k1^1]].fa=y;
			S[y].fa=x;
			S[x].ch[k1^1]=y;
			Update(y);
			Update(x);
			return;
		}
	void Update(int x)
		{
			S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
			return;
		}
	void Splay(int x,int goal)
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
		}
	void Find(int x)
		{
			int now=root;
			while ((S[now].ch[S[now].key<x]!=0)&&(S[now].key!=x))
				now=S[now].ch[S[now].key<x];
			Splay(now,0);
		}
	int Next(int x,int opt)
		{
			Find(x);
			if ((S[root].key<x)&&(opt==0))
				return root;
			if ((S[root].key>x)&&(opt==1))
				return root;
			int now=S[root].ch[opt];
			while (S[now].ch[opt^1]!=0)
				now=S[now].ch[opt^1];
			return now;
		}
	void Delete(int x)
		{
			int pre=Next(x,0);
			int nex=Next(x,1);
			Splay(pre,0);
			Splay(nex,pre);
			S[nex].ch[0]=0;
			Splay(nex,0);
			return;
		}
	bool empty()
		{
			return S[root].size<=2;
		}
};

int n;
SplayTree S;
int read();

int main()
{
	ll Ans=0;
	n=read();
	int opt=-1;
	{
		int a=read(),b=read();
		if (a==0)
			opt=0;
		else
			opt=1;
		S.Insert(b);
		n--;
	}
	while (n--)
	{
		int a=read(),b=read();
		if (a==opt)
			S.Insert(b);
		else
		{
			int pre=S.Next(b,0);
			int nex=S.Next(b,1);
			//cout<<b<<" "<<S.S[pre].key<<" "<<S.S[nex].key<<endl;
			if ((b-S.S[pre].key<=S.S[nex].key-b)&&(S.S[pre].key!=-inf))
			{
				Ans=(Ans+b-S.S[pre].key)%Mod;
				S.Delete(S.S[pre].key);
			}
			else
			{
				Ans=(Ans+S.S[nex].key-b)%Mod;
				S.Delete(S.S[nex].key);
			}
			if (S.empty())
				opt=opt^1;
		}
	}
	cout<<Ans<<endl;
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
