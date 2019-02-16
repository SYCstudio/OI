#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=55;
const int inf=2147483647;

int n;
char str[maxN];
char s[maxN];
int pcnt,Pos[maxN];

bool Cmp(char *s1,char *s2,int l1,int r1,int l2,int r2);

int main()
{
	scanf("%s",str+1);
	int L;L=strlen(str+1);
	scanf("%d",&n);
	while (n--)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		pcnt=0;
		for (int i=1;i+len-1<=L;i++)
			if (Cmp(str,s,i,i+len-1,1,len)) Pos[++pcnt]=i+len-1;
		bool flag=1;
		for (int i=1;i<=len;i++)
		{
			int cnt=0;
			for (int j=1;j+(len-i+1)-1<=L;j++)
			{
				//cout<<j<<" "<<j+(len-i+1)-1<<" "<<i<<" "<<len<<endl;
				if (Cmp(str,s,j,j+(len-i+1)-1,i,len)) cnt++;
			}
			//cout<<i<<" "<<cnt<<endl;
			if (cnt!=pcnt)
			{
				flag=0;
				for (int j=i-1;j<=len;j++) printf("%c",s[j]);
				printf(" ");break;
			}
		}
		if (flag==1) printf("%c ",s[len]);
		for (int i=Pos[1]-len+1;i>=1;i--)
		{
			flag=1;
			for (int j=2;j<=pcnt;j++)
				if (Cmp(str,str,i,Pos[i],Pos[j]-(Pos[1]-i+1)+1,Pos[j])==0){
					flag=0;break;
				}
			if (flag==0)
			{
				for (int j=i+1;j<=Pos[1];j++) printf("%c",str[j]);
				printf(" ");break;
			}
		}
		if (flag==1)
		{
			for (int i=1;i<=Pos[1];i++) printf("%c",str[i]);
			printf(" ");
		}
		for (int i=1;i<=pcnt;i++) printf("%d ",Pos[i]);
		printf("\n");
	}
	return 0;
}

bool Cmp(char *s1,char *s2,int l1,int r1,int l2,int r2)
{
	for (int i=l1,j=l2;i<=r1,j<=r2;i++,j++)
		if (s1[i]!=s2[j]) return 0;
	return 1;
}
