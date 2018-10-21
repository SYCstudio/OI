#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100;

char str[maxN];

int main()
{
	scanf("%s",str);
	int l=strlen(str);
	int Ans=0;
	for (int i=0;i<l;i++)
		if ((str[i]=='a')||(str[i]=='e')||(str[i]=='i')||(str[i]=='o')||(str[i]=='u')||(str[i]=='1')||(str[i]=='3')||(str[i]=='5')||(str[i]=='7')||(str[i]=='9')) Ans++;
	printf("%d\n",Ans);
	return 0;
}
