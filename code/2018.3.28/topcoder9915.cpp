#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;

class RedIsGood
{
public:
	double F[maxN];
	double getProfit(int R, int B){
		for (int i=0;i<=R;i++) F[i]=i;
		for (int j=1;j<=B;j++)
			for (int i=0;i<=R;i++)
				F[i]=max(0.0,(1.0*i/(i+j)*(F[i-1]+1)+1.0*j/(i+j)*(F[i]-1)));
		return F[R];
	}
};
