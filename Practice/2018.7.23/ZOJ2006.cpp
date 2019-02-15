#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int inf=2147483647;

char str[maxN];

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		mem(str,'\0');
		scanf("%s",str+1);
		int len=strlen(str+1);

		int i=1,j=2,k=0,d;
		while ((i<=len)&&(j<=len)&&(k<len)){
			d=str[(i+k-1)%len+1]-str[(j+k-1)%len+1];
			if (d==0) k++;
			else{
				if (d>0) i+=k+1;
				else j+=k+1;
				k=0;
				if (i==j) j++;
			}
		}

		printf("%d\n",min(i,j));
	}

	return 0;
}
