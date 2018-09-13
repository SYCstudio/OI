#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxN=5010;
const int inf=2147483647;

char str[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>(str+1);
	int len=strlen(str+1);
	bool flag=1;
	for (int i=1,cnt='a';i<=len;i++)
	{
		if (str[i]<cnt){
			flag=0;break;
		}
		if (str[i]!=cnt) cnt++;
		if (str[i]!=cnt){
			flag=0;break;
		}
	}
	if (flag==0)
	{
		printf("NO\n");
		return 0;
	}
	int a=0,b=0,c=0;
	for (int i=1;i<=len;i++)
	{
		if (str[i]=='a') a++;
		else if (str[i]=='b') b++;
		else if (str[i]=='c') c++;
	}
	if ((a==0)||(b==0)||(c==0)) printf("NO\n");
	else if ((a==c)||(b==c)) printf("YES\n");
	else printf("NO\n");
	return 0;
}
