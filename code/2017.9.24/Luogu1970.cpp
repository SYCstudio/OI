#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

int n;

int main()
{
	scanf("%d",&n);
	int Ans=1;
	int op=-1;
	int lasth,nowh;
	scanf("%d",&lasth);
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&nowh);
		if ((nowh>lasth)&&((op==-1)||(op==0)))
		{
			Ans++;
			op=1;
		}
		if ((nowh<lasth)&&((op==-1)||(op==1)))
		{
			Ans++;
			op=0;
		}
		lasth=nowh;
	}
	printf("%d\n",Ans);
	return 0;
}
