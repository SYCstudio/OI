#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

class Task
{
public:
	int t1;//交代任务的时间
	int t2;//执行任务的时间
};

bool operator < (Task a,Task b)
{
	return a.t2>b.t2;
}

const int maxsize=1001;
const int inf=2147483647;

int n;
Task A[maxsize];

int main()
{
	int T=0;
	while (cin>>n) {
		if (n==0)
			break;
		T++;
		for (int i=1; i<=n; i++)
			cin>>A[i].t1>>A[i].t2;
		int Time=0;
		int Ans=0;
		sort(&A[1],&A[n+1]);
		for (int i=1; i<=n; i++) {
			Time+=A[i].t1;
			Ans=max(Ans,Time+A[i].t2);
		}
		cout<<"Case "<<T<<": "<<Ans<<endl;
	}
}
