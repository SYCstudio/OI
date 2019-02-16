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

const int maxN=400000;
const int inf=2147483647;

class MonotoneQueue_Data
{
public:
	ll pos,key;
};

ll n,Mod;
MonotoneQueue_Data Q[maxN];

ll read();
char readchar();

int main()
{
	n=read();
	Mod=read();
	ll h=0,t=0;
	ll cnt=0;
	ll last=0;
	while (n--)
	{
		char ch;
		ch=readchar();
		ll x=read();
		if (ch=='A')
		{
			cnt++;
			x=(x+last)%Mod;
			while ((t<h)&&(Q[h].key<x))
				h--;
			h++;
			Q[h]=((MonotoneQueue_Data){cnt,x});
		}
		else
		{
			ll l=t,r=h;
			ll Ans;
			while (l<=r)
			{
				ll mid=(l+r)/2;
				if (Q[mid].pos>=cnt-x+1)
				{
					Ans=mid;
					r=mid-1;
				}
				else
					l=mid+1;
			}
			last=Q[Ans].key;
			printf("%lld\n",last);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

ll read()
{
	ll x=0,k=1;
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

char readchar()
{
	char ch=getchar();
	while ((ch!='A')&&(ch!='Q'))
		ch=getchar();
	return ch;
}
