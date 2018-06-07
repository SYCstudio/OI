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

const int maxN=1000100;
const int inf=2147483647;

#define Y(i,j) (F[i]+Sum[i]-F[j]-Sum[j])
#define X(i,j) (SumP[i]-SumP[j])

int n;
ll P[maxN];
ll C[maxN];
ll X[maxN];
ll Sum[maxN];//P[i]*X[i]前缀和
ll SumP[maxN];//P[i]前缀和
ll F[maxN];
int Q[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&X[i],&P[i],&C[i]);
		SumP[i]=SumP[i-1]+P[i];
		Sum[i]=Sum[i-1]+P[i]*X[i];
	}
	int h=0,t=0;
	Q[0]=0;
	for (int i=1;i<=n;i++)
	{
		while ((t<h)&&((ll)Y(Q[t+1],Q[t])<(ll)X[i]*X(Q[t+1],Q[t])))
			t++;
		F[i]=F[Q[t]]+(ll)X[i]*(SumP[i]-SumP[Q[t]])-Sum[i]+Sum[Q[t]]+C[i];
		while ((t<h)&&((ll)Y(i,Q[h])*X(Q[h],Q[h-1])<Y(Q[h],Q[h-1])*X(i,Q[h])))
			h--;
		h++;
		Q[h]=i;
		//cout<<F[i]<<endl;
	}
	printf("%lld\n",F[n]);
	return 0;
}
