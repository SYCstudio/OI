#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000;
const int inf=2147483647;

char str1[maxN],str2[maxN];

int main()
{
	cin>>str1>>str2;
	int l1=strlen(str1),l2=strlen(str2);
	for (int i=0;i<l1;i++)
		if ((str1[i]>='a')&&(str1[i]<='z'))
			str1[i]-='a';
		else
			str1[i]-='A';
	for (int i=0,j=0;i<l2;i++,j=(j+1)%l1)
	{
		if ((str2[i]>='a')&&(str2[i]<='z'))
		{
			str2[i]-=str1[j];
			if (str2[i]<'a')
				str2[i]+=26;
		}
		else
		{
			str2[i]-=str1[j];
			if (str2[i]<'A')
				str2[i]+=26;
		}
	}
	cout<<str2<<endl;
	return 0;
}
