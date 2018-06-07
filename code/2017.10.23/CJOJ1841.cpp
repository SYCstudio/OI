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

const int maxN=14;
const int Mod=100000000;
const int inf=2147483647;

int m,n;
int Binarycnt=0;
int Binary[1<<maxN];
int Erea[maxN];
int F[maxN][1<<maxN];

int read();
void Two(int i);

int main()
{
	n=read();
	m=read();
	Binarycnt=1;
	Binary[1]=0;
	for (int i=1;i<(1<<(m+1));i++)
	{
		bool is_true=1;
		if (i&1)
			continue;
		for (int j=1;j<=m;j++)
			if ((i&(1<<j))&&(i&(1<<(j+1))))
			{
				is_true=0;
				break;
			}
		if (is_true==1)
		{
			Binarycnt++;
			Binary[Binarycnt]=i;
		}
	}
	/*
	for (int i=1;i<=Binarycnt;i++)
	{
		Two(Binary[i]);
		cout<<endl;
	}
	//*/
	for (int i=1;i<=n;i++)
	{
		Erea[i]=0;
		for (int j=1;j<=m;j++)
			Erea[i]=Erea[i]|((read()^1)<<j);
	}
	for (int i=1;i<=Binarycnt;i++)
		if (!(Erea[1]&Binary[i]))
		{
			//Two(Erea[1]);
			//Two(Binary[i]);
			//cout<<endl;
		    F[1][Binary[i]]=1;
		}
	//cout<<endl;
	for (int i=2;i<=n;i++)
	{
		for (int j=1;j<=Binarycnt;j++)
			if (!(Erea[i-1]&Binary[j]))
				for (int k=1;k<=Binarycnt;k++)
					if ((!(Erea[i]&Binary[k]))&&(!(Binary[j]&Binary[k])))
						F[i][Binary[k]]=(F[i][Binary[k]]+F[i-1][Binary[j]])%Mod;
	}
	ll Ans=0;
	for (int i=1;i<=Binarycnt;i++)
		Ans=(Ans+F[n][Binary[i]])%Mod;
	printf("%lld\n",Ans);
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

void Two(int x)
{
	if (x==0)
		return;
	Two(x>>1);
	printf("%d",x&1);
	return;
}
