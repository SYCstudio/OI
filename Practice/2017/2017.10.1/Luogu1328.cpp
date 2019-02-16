#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=300;
const int inf=2147483647;
const int Mat[5][5]={{0,-1,1,1,-1},
					 {1,0,-1,1,-1},
					 {-1,1,0,-1,1},
					 {-1,-1,1,0,1},
					 {1,1,-1,-1,0}};

int n,na,nb;
int A1[maxN];
int A2[maxN];

int main()
{
	scanf("%d%d%d",&n,&na,&nb);
	for (int i=1;i<=na;i++)
		scanf("%d",&A1[i]);
	for (int i=1;i<=nb;i++)
		scanf("%d",&A2[i]);
	int p1=0,p2=0;
	for (int i=1,j1=1,j2=1;i<=n;i++,j1=j1%na+1,j2=j2%nb+1)
		if (Mat[A1[j1]][A2[j2]]==1)
			p1++;
		else
			if (Mat[A1[j1]][A2[j2]]==-1)
				p2++;
	printf("%d %d\n",p1,p2);
	return 0;
}
