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
#define X(i,j) (E2[j+1].b-E2[i+1].b)
#define Y(i,j) (F[i]-F[j])

const int maxN=50010;
const int inf=2147483647;

class Erea
{
public:
	ll a,b;
};

bool operator < (Erea A,Erea B)
{
	if (A.a!=B.a)
		return A.a<B.a;
	return A.b<B.b;
}

int n;
Erea E1[maxN];//原来的n块土地
Erea E2[maxN];//去掉冗余的土地后的
ll F[maxN];//动态规划
int Q[maxN*2];//单调队列

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld%lld",&E1[i].a,&E1[i].b);
	sort(&E1[1],&E1[n+1]);
	int ecnt=1;
	E2[1]=E1[1];
	for (int i=2;i<=n;i++)
	{
		while ((ecnt!=0)&&(E2[ecnt].b<=E1[i].b))
			ecnt--;
		ecnt++;
		E2[ecnt]=E1[i];
	}
	/*
	for (int i=1;i<=ecnt;i++)
		cout<<E2[i].a<<" "<<E2[i].b<<endl;
	//*/
	int h=0,t=0;
	Q[h]=0;
	for (int i=1;i<=ecnt;i++)
	{
		while ((t<h)&&(Y(Q[t+1],Q[t])<E2[i].a*X(Q[t+1],Q[t])))
			t++;
		F[i]=F[Q[t]]+E2[i].a*E2[Q[t]+1].b;
		//cout<<t<<" "<<F[i]<<endl;
		while ((t<h)&&(Y((ll)i,Q[h])*(ll)X(Q[h],Q[h-1])<(ll)Y(Q[h],Q[h-1])*(ll)X(i,Q[h])))
			h--;
		h++;
		Q[h]=i;
		//cout<<h<<endl;
	}
	printf("%lld\n",F[ecnt]);
	return 0;
}
