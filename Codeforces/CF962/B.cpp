#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

int n,A,B;
char Seat[maxN];
priority_queue<int> Heap;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>A>>B;
	cin>>(Seat+1);Seat[n+1]='*';n++;
	int lastpos=-1;
	for (int i=1;i<=n;i++)
	{
		if ((Seat[i]=='.')&&(lastpos==-1)) lastpos=i;
		if ((Seat[i]=='*')&&(lastpos!=-1))
		{
			Heap.push(i-lastpos);
			lastpos=-1;
		}
	}
	int Ans=0;
	if (A<B) swap(A,B);
	while ((!Heap.empty())&&(A+B!=0))
	{
		int u=Heap.top();Heap.pop();
		//cout<<"u:"<<u<<endl;
		if ((u&1)==0)
		{
			u=u/2;
			Ans+=min(A,u);Ans+=min(B,u);
			A=max(0,A-u);B=max(0,B-u);
		}
		else
		{
			int u1=u/2+1;int u2=u-u1;
			//cout<<u1<<" "<<u2<<" "<<A<<" "<<B<<endl;
			Ans+=min(A,u1);Ans+=min(B,u2);
			A=max(0,A-u1);B=max(0,B-u2);
		}
		if (A<B) swap(A,B);
	}
	cout<<Ans<<endl;
	return 0;
}
