#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int inf=2147483647;

int n;
char Input[maxN];
ld F[maxN];

int main(){
	scanf("%d",&n);scanf("%s",Input+1);Input[0]=Input[++n]='x';
	ld ans=0,s1=0,s2=0,s3=0,s4=0;
	for (int i=1;i<=n;i++)
		if (Input[i]!='o'){
			ld w=1;//if (Input[i]=='?') w=0.5;
			for (int j=i-1;j>=0;j--)
				if (Input[j]=='x'){
					F[i]=F[i]+w*(F[j]+(i-j-1)*(i-j-1));break;
				}
				else if (Input[j]=='?'){
					w*=0.5;
					F[i]=F[i]+w*(F[j]+(i-j-1)*(i-j-1));
					//w*=0.5;
				}
		}
	for (int i=1;i<=n;i++) printf("%.4LF\n",F[i]);
	printf("%.4LF\n",F[n]);return 0;
	/*
	for (int i=1;i<=n;i++)
		if (Input[i]=='x'){
			ans=ans+s1+s2*i*i-2.0*i*s3+s4;
			s1=s2=s3=s4=0;
		}
		else if (Input[i]=='?'){
			//ans=ans+
		}
	//*/
}
