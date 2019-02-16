#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	while (cin>>n)
	{
		int cnt=0,Ans=0;
		for (int i=1;i<=n;i++)
		{
			int number;
			scanf("%d",&number);
			if (cnt==0)
			{
				cnt=1;
				Ans=number;
				continue;
			}
			if (number==Ans)
				cnt++;
			else
				cnt--;
		}
		printf("%d\n",Ans);
	}
	return 0;
}	
