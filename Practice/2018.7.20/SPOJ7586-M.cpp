#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010*2;
const int inf=2147483647;

char Input[maxN];
int P[maxN];

int main()
{
	scanf("%s",Input+1);
	int len=strlen(Input+1);

	for (int i=len;i>=1;i--) Input[2*i]=Input[i],Input[2*i-1]='#';
	Input[0]='@';Input[len+len+2]='%';Input[1]=Input[len+len+1]='#';

	int pos=0,mxR=0;
	for (int i=1;i<=len+len;i++)
	{
		if (i<mxR) P[i]=min(P[pos*2-i],mxR-i);
		else P[i]=1;
		while (Input[i-P[i]]==Input[i+P[i]]) P[i]++;
		if (i+P[i]>mxR){
			mxR=i+P[i];pos=i;
		}
	}

	//for (int i=1;i<=len+len+2;i++) cout<<Input[i]<<" ";cout<<endl;
	//for (int i=1;i<=len+len+2;i++) cout<<P[i]<<" ";cout<<endl;

	int Ans=0;
	for (int i=1;i<=len+len;i++)
		Ans=Ans+P[i]/2;
	printf("%d\n",Ans);
	return 0;
}
