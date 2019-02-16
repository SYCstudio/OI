#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000100;
const ld eps=1e-5;
const int inf=2147483647;

int n;
ll Arr[maxN];
ll Queue[maxN];
ll F[maxN];

ld Slope(int i,int j);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>Arr[i];
	int l=1,r=1;
	Queue[1]=0;
	for (int i=1;i<=n;i++)
	{
		//cout<<"Slope:"<<Queue[l]<<" "<<Queue[l+1]<<" "<<Slope(Queue[l],Queue[l+1])<<endl;
		while ((l<r)&&(Slope(Queue[l],Queue[l+1])<2.0*i+eps)) l++;
		//cout<<i<<" "<<Queue[l]<<" ["<<l<<","<<r<<"]"<<endl;
		F[i]=Arr[i]+F[Queue[l]]+(i-Queue[l]-1)*(i-Queue[l])/2;
		while ((l<r)&&(Slope(Queue[r-1],Queue[r])+eps>Slope(Queue[r],i))) r--;
		Queue[++r]=i;
	}
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	cout<<F[n]<<endl;
	return 0;
}

ld Slope(int i,int j)
{
	//if (i==0) return -inf;
	//if (j==0) return inf;
	return (ld)((2.0*F[i]+1.0*i*i+1.0*i)-(2.0*F[j]+1.0*j*j+1.0*j))/(ld)(1.0*i-1.0*j);
}

