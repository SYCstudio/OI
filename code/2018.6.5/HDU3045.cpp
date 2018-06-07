#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=401000;
const int inf=147483647;
const ll INF=1e17;

int n,K;
ll V[maxN],F[maxN],S[maxN],Q[maxN];

//ld Slope(ll x1,ll x2);
ll X(ll x1,ll x2);
ll Y(ll x1,ll x2);

int main()
{
	while (scanf("%d%d",&n,&K)!=EOF)
	{
		for (int i=1;i<=n;i++) scanf("%lld",&V[i]);
		sort(&V[1],&V[n+1]);
		mem(F,63);mem(S,0);
		for (int i=1;i<=n;i++) S[i]=S[i-1]+V[i];

		/*
		F[0]=0;
		for (int i=1;i<=n;i++)
		{
			F[i]=inf;
			for (int j=0;j+K<=i;j++)
				F[i]=min(F[i],F[j]+S[i]-S[j]-V[j+1]*(i-j));
			for (int j=0;j+K<=i;j++)
				if (F[i]==F[j]+S[i]-S[j]-V[j+1]*(i-j)){
					cout<<j<<" -> "<<i<<endl;break;
				}
		}
		for (int i=1;i<=n;i++)
			if (F[i]==inf) cout<<"inf ";
			else cout<<F[i]<<" ";
		cout<<endl;
		cout<<F[n]<<endl;
        //*/
		for (int i=K;(i<2*K)&&(i<=n);i++) F[i]=S[i]-V[1]*(ll)i;
		int L=1,R=0;
		for (int i=K+K,j=K;i<=n;i++,j++)
		{
			while ((L<R)&&(Y(Q[R-1],Q[R])*X(Q[R],j)>=Y(Q[R],j)*X(Q[R-1],Q[R]))) R--;
			Q[++R]=j;
			while ((L<R)&&(Y(Q[L],Q[L+1])>=1ll*i*X(Q[L],Q[L+1]))) L++;
			//cout<<Q[L]<<" -> "<<i<<endl;
			F[i]=F[Q[L]]+S[i]-S[Q[L]]-V[Q[L]+1]*((ll)i-Q[L]);
		}
		//*/
		//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
		printf("%lld\n",F[n]);
	}
	return 0;
}

/*
ld Slope(ll x1,ll x2)
{
	//cout<<"slope:"<<x1<<" "<<x2<<endl;
	if (V[x1+1]==V[x2+1]) return INF;
	return ((ld)1.0*((ld)(F[x1]-S[x1]+x1*V[x1+1])-(ld)(F[x2]-S[x2]+x2*V[x2+1])))/((ld)1.0*(V[x1+1]-V[x2+1]));
}
//*/

ll X(ll x1,ll x2)
{
	return V[x1+1]-V[x2+1];
}

ll Y(ll x1,ll x2)
{
	return (F[x1]-S[x1]+x1*V[x1+1])-(F[x2]-S[x2]+x2*V[x2+1]);
}
