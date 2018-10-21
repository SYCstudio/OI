#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100100;
const int inf=2147483647;

int n,m;
int Op[maxN];
char name[maxN][50];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d%s",&Op[i],name[i]);
	int pos=0;
	for (int i=1;i<=m;i++)
	{
		int op,num;
		scanf("%d%d",&op,&num);
		num=num%n;
		if (op==Op[pos])
			pos=(pos-num+n)%n;
		else
			pos=(pos+num)%n;
	}
	printf("%s\n",name[pos]);
	return 0;
}
