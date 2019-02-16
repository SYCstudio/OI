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
#define Y(j,k) (F1[j]+Sum[j]-F1[k]-Sum[k])
#define X(j,k) (SumW[j]-SumW[k])

const int maxN=200100;
const int inf=2147483647;
int n;
ll D[maxN];
ll W[maxN];
ll SumW[maxN];//W前缀和
ll Sum[maxN];//W[i]*SumD[i]前缀和
ll F1[maxN];
ll F2[maxN];
ll F[maxN];
ll Q[maxN];

int read();

int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		W[i]=read();
		int d=read();
		D[i+1]=d+D[i];
		SumW[i]=SumW[i-1]+W[i];
		Sum[i]=Sum[i-1]+W[i]*D[i];
		F1[i]=SumW[i-1]*(D[i]-D[i-1])+F1[i-1];
	}
	for (int i=n;i>=1;i--)
		F2[i]=F2[i+1]+W[i+1]*(D[n+1]-D[i+1]);
	/*
	printf("   D   W SumW Sum F1  F2\n");
	for (int i=1;i<=n;i++)
		printf("%4lld%4lld%4lld%4lld%4lld%4lld\n",D[i],W[i],SumW[i],Sum[i],F1[i],F2[i]);
	//cout<<D[i]<<" "<<W[i]<<" "<<SumW[i]<<" "<<Sum[i]<<" "<<F1[i]<<" "<<F2[i]<<endl;
	//*/
	int h=0,t=0;
	Q[h]=0;
	for (int i=1;i<=n;i++)
	{
		while ((t<h)&&(Y(Q[t+1],Q[t])<D[i]*X(Q[t+1],Q[t])))
			t++;
		F[i]=F1[Q[t]]+D[i]*(SumW[i]-SumW[Q[t]])-(Sum[i]-Sum[Q[t]])+F2[i];
		while ((t<h)&&(Y(i,Q[h])*X(Q[h],Q[h-1])<Y(Q[h],Q[h-1])*X(i,Q[h])))
			h--;
		h++;
		Q[h]=i;
		//cout<<F[i]<<endl;
	}
	ll Ans=inf;
	for (int i=1;i<=n;i++)
		Ans=min(Ans,F[i]);
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
