#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1500100;
const int inf=2147483647;

class Building
{
public:
	int t1,t2;
};

int n;
Building B[maxN];
priority_queue<int> Q;

bool cmp(Building A,Building B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&B[i].t1,&B[i].t2);

	sort(&B[1],&B[n+1],cmp);

	int nowtim=0,Ans=0;
	for (int i=1;i<=n;i++){
		if (nowtim+B[i].t1<=B[i].t2){
			nowtim+=B[i].t1;Q.push(B[i].t1);Ans++;
		}
		else if ((!Q.empty())&&(Q.top()>B[i].t1)){
			nowtim=nowtim-Q.top()+B[i].t1;Q.pop();Q.push(B[i].t1);
		}
	}

	printf("%d\n",Ans);

	return 0;
}

bool cmp(Building A,Building B){
	return A.t2<B.t2;
}
