#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const ull Base=37;
const int inf=2147483647;

int L1,L2;
char str1[maxN],str2[maxN];
ull H1[maxN],H2[maxN];
ull R[maxN];

void InitHash(char *str,ull *H);
ull GetHash(ull *H,int l,int r);

int main()
{
	int T;scanf("%d",&T);
	R[0]=1;
	for (int i=1;i<maxN;i++) R[i]=R[i-1]*Base;
	while (T--)
	{
		scanf("%s",str1+1);scanf("%s",str2+1);
		L1=strlen(str1+1);L2=strlen(str2+1);
		if (L1<L2)
		{
			printf("0\n");
			continue;
		}
		InitHash(str1,H1);InitHash(str2,H2);
		int Ans=0;
		for (int i=1;i+L2-1<=L1;i++)
		{
			int l1=i,l2=1;
			//cout<<"["<<l1<<","<<l1+L2-1<<"]"<<endl;
			for (int tim=1;tim<=4;tim++)
			{
				int L=l1,R=i+L2-1;
				int pos=l1-1;
				do
				{
					int mid=(L+R)>>1;int sz=mid-l1+1;
					//cout<<l1<<" "<<mid<<":"<<GetHash(H1,l1,mid)<<endl;
					//cout<<l2<<" "<<l2+sz-1<<":"<<GetHash(H2,l2,l2+sz-1)<<endl;
					if (GetHash(H1,l1,mid)==GetHash(H2,l2,l2+sz-1)){
						L=mid+1;pos=mid;
					}
					else R=mid-1;
				}
				while (L<=R);
				l1=pos+2;l2=pos-i+3;
				if (tim==4) l1--,l2--;
				//cout<<"now l1:"<<l1<<" l2:"<<l2<<endl;
				if (l1>i+L2-1) break;
			}
			if (l1>i+L2-1) Ans++;
		}
		printf("%d\n",Ans);
	}
	return 0;
}

void InitHash(char *str,ull *H)
{
	int len=strlen(str+1);
	H[0]=0;
	for (int i=1;i<=len;i++) H[i]=H[i-1]*Base+str[i];
	return;
}

ull GetHash(ull *H,int l,int r)
{
	return H[r]-H[l-1]*R[r-l+1];
}

