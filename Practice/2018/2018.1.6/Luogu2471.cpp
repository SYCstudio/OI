#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxST=18;
const int inf=1000000001;

int n;
int Year[maxN],Rain[maxN];
int Log2[maxN];
int ST[maxN][maxST];

int GetOpt(int y1,int y2);
int Find(int key);
int GetMax(int l,int r);

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d%d",&Year[i],&Rain[i]);
    Log2[0]=-1;for (int i=1;i<=n;i++) Log2[i]=Log2[i>>1]+1;
    for (int i=1;i<=n;i++) ST[i][0]=Rain[i];
    for (int j=1;j<maxST;j++) for (int i=1;i+(1<<(j-1))<=n;i++) ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
    int m;scanf("%d",&m);
    while (m--)
    {
	int y1,y2;scanf("%d%d",&y1,&y2);
	int opt=GetOpt(y1,y2);
	if (opt==0) printf("false\n");
	if (opt==1) printf("true\n");
	if (opt==-1) printf("maybe\n");
    }
    return 0;
}

int Find(int key)
{
    int l=1,r=n,Ans;
    do
    {
	int mid=(l+r)/2;
	if (Year[mid]>=key)
	{
	    Ans=mid;
	    r=mid-1;
	}
	else l=mid+1;
    }
    while (l<=r);
    return Ans;
}

int GetOpt(int y1,int y2)
{
    //int id1=Find(y1),id2=Find(y2);//二分写错了什么鬼？？？
    int id1=lower_bound(&Year[1],&Year[n+1],y1)-Year;
    int id2=lower_bound(&Year[1],&Year[n+1],y2)-Year;
    int s1=(y1==Year[id1]);
    int s2=(y2==Year[id2]);
    //cout<<y1<<" "<<y2<<" "<<id1<<"["<<Year[id1]<<"] "<<id2<<"["<<Year[id2]<<"]"<<endl;
    if (s1)//左端存在
    {
	if (s2)//右端存在
	{
	    if (Rain[id1]<Rain[id2]) return 0;//当左端小于右端，则不满足
	    int mx=GetMax(id1+1,id2-1);
	    if (mx>=Rain[id2]) return 0;//中间的有大于等于右端点的，则不满足
	    else if (y2-y1==id2-id1) return 1;//中间的都严格小于，且没有不确定的
	    else return -1;//中间的都严格小于但存在不确定的
	}
	else//右端不存在
	{
	    int mx=GetMax(id1+1,id2-1);
	    if (mx>=Rain[id1]) return 0;//中间的大于等于左端，则不满足
	    else return -1;//中间的都严格小于左端，则不确定
	}
    }
    else//左端不存在
    {
	if (s2)//右端存在
	{
	    int mx=GetMax(id1,id2-1);
	    if (mx>=Rain[id2]) return 0;//中间的大于等于右端，则不满足
	    else return -1;//中间的都严格小于右端，则不确定
	}
	else return -1;//右端不存在，则一定不确定
    }
}

int GetMax(int l,int r)
{
    if (l>r) return -inf;
    int length=r-l+1;
    int lg=Log2[length];
    //cout<<"GetMax:"<<l<<" "<<r<<" ["<<Year[l]<<","<<Year[r]<<"] "<<max(ST[l][lg],ST[r-(1<<lg)+1][lg])<<endl;
    return max(ST[l][lg],ST[r-(1<<lg)+1][lg]);
}
