#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=500010;
const int maxP=20;
const int inf=2147483647;

int n,m,P,Q;
ll Mu[maxNum];
ll Fact[maxNum];//每一个数分解后有多少个质因子
ll pricnt=0,Prime[maxNum];
bool notprime[maxNum];
ll F[maxNum][maxP];

void GetMu();

int main()
{
    GetMu();
    for (int i=1;i<maxNum;i++)
	for (int j=i;j<maxNum;j+=i)
	    F[j][Fact[i]]+=Mu[j/i];
    for (int i=0;i<maxNum;i++)
	for (int j=1;j<maxP;j++)
	    F[i][j]+=F[i][j-1];
    for (int i=1;i<maxNum;i++)
	for (int j=0;j<maxP;j++)
	    F[i][j]+=F[i-1][j];
    /*
    for (int i=1;i<maxNum;i++)
	for (int j=1;j<maxP;j++)
	    F[i][j]+=F[i-1][j]+F[i][j-1]-F[i-1][j-1];
    //*/
    /*
    for (int i=1;i<100;i++)
    {
	for (int j=1;j<maxP;j++)
	    cout<<F[i][j]<<" ";
	cout<<endl;
    }
    //*/
    scanf("%d",&Q);
    while (Q--)
    {
	scanf("%d%d%d",&n,&m,&P);
	if (P>=maxP)
	{
	    printf("%lld\n",(ll)n*(ll)m);
	    continue;
	}
	ll ans=0;
	if (m<n) swap(n,m);
	for (int i=1,last;i<=n;i=last+1)
	{
	    last=min(n/(int)(n/i),m/(int)(m/i));
	    ans=ans+(F[last][P]-F[i-1][P])*(ll)(n/i)*(ll)(m/i);
	}
	printf("%lld\n",ans);
    }
    return 0;
}

void GetMu()
{
    notprime[1]=1;Mu[1]=1;Fact[1]=0;
    for (int i=2;i<maxNum;i++)
    {
	if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1,Fact[i]=1;
	for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
	{
	    notprime[i*Prime[j]]=1;
	    Fact[i*Prime[j]]=Fact[i]+1;
	    if (i%Prime[j]==0) break;
	    Mu[i*Prime[j]]=-Mu[i];
	}
    }
    //for (int i=1;i<=20;i++) cout<<Mu[i]<<" ";cout<<endl;
    //for (int i=1;i<=20;i++) cout<<Fact[i]<<" ";cout<<endl;
    return;
}
