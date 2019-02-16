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
#define sqr(x) ((x)*(x))
#define Y(i,j) (F[i]-F[j]+a*(sqr(Sum[i])-sqr(Sum[j]))-b*(Sum[i]-Sum[j]))
#define X(i,j) (Sum[i]-Sum[j])

const int maxN=1000100;
const int inf=2147483647;

int n;
ll a,b,c;
ll Arr[maxN];
ll Sum[maxN];
ll F[maxN];
int Q[maxN];

int main()
{
	scanf("%d",&n);
	scanf("%lld%lld%lld",&a,&b,&c);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&Arr[i]);
		Sum[i]=Sum[i-1]+Arr[i];
	}
	int h,t;
	h=t=0;
	Q[h]=0;
	for (int i=1;i<=n;i++)
	{
		while ((t<h)&&(Y(Q[t+1],Q[t])>(ll)2*a*Sum[i]*X(Q[t+1],Q[t])))
			t++;
		F[i]=F[Q[t]]+a*sqr(Sum[i]-Sum[Q[t]])+b*(Sum[i]-Sum[Q[t]])+c;
		//cout<<F[i]<<endl;
		while ((t<h)&&(Y(i,Q[h])*X(Q[h],Q[h-1])>Y(Q[h],Q[h-1])*X(i,Q[h])))
			h--;
		h++;
		Q[h]=i;
	}
	printf("%lld\n",F[n]);
	return 0;
}
