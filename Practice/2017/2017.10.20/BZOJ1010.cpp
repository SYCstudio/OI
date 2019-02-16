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
#define sqr(x) (((ll)x)*((ll)x))
#define X(i,j) ((ll)2*(S[i]-S[j]))
#define Y(i,j) ((ll)F[i]-(ll)F[j]+(ll)sqr(S[i]+L+1)-(ll)sqr(S[j]+L+1))

const int maxN=50010;
const int inf=2147483647;

int n,L;
int Q[maxN*2];//单调队列
ll Sum[maxN];//长度前缀和
ll F[maxN];//DP,F[i]表示到第i个物品时的最小费用
ll S[maxN];//S[i]=Sum[i]+i;
ll G[maxN];//G[i]=F[i]+Si^2

int main()
{
	scanf("%d%d",&n,&L);
	for (int i=1;i<=n;i++)
	{
		int length;
		scanf("%d",&length);
		Sum[i]=Sum[i-1]+(ll)length;
		S[i]=Sum[i]+(ll)i;
	}
	int h=0,t=0;
	Q[h]=0;
	for (int i=1;i<=n;i++)
	{
		while ((t<h)&&(Y(Q[t+1],Q[t])<=(ll)S[i]*X(Q[t+1],Q[t])))
			t++;
		F[i]=(ll)F[Q[t]]+(ll)sqr(S[i]-S[Q[t]]-L-1);
		while ((t<h)&&(Y(i,Q[h])*X(Q[h],Q[h-1])<=Y(Q[h],Q[h-1])*X(i,Q[h])))
			h--;
		h++;
		Q[h]=i;
	}
	printf("%lld\n",F[n]);
	return 0;
}
