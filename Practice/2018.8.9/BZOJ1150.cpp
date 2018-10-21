#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;
const ll INF=1e18;

class QueueData
{
public:
	ll key;int id;
};

int n,K;
int Dist[maxN],Next[maxN],Pre[maxN];
ll Val[maxN];
priority_queue<QueueData> Q,Del;

bool operator < (QueueData A,QueueData B);
bool operator == (QueueData A,QueueData B);
void Push(QueueData u);
void Delete(QueueData u);
QueueData Top();
void Pop();

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&Dist[i]);
	for (int i=1;i<n;i++) Val[i]=Dist[i+1]-Dist[i];
	Val[0]=INF;Val[n]=INF;
	for (int i=1;i<n;i++) Next[i]=i+1,Pre[i]=i-1;
	Next[0]=1;Pre[n]=n-1;Pre[0]=-1;Next[n]=-1;

	for (int i=0;i<=n;i++) Push((QueueData){Val[i],i});

	ll Ans=0;
	while (K--){
		QueueData u=Top();Pop();
		Ans=Ans+u.key;
		int pre=Pre[u.id],nxt=Next[u.id];
		Delete((QueueData){Val[pre],pre});Delete((QueueData){Val[nxt],nxt});
		Val[u.id]=Val[pre]+Val[nxt]-Val[u.id];
		Pre[u.id]=Pre[pre];Next[u.id]=Next[nxt];
		if (Pre[pre]!=-1) Next[Pre[pre]]=u.id;
		if (Next[nxt]!=-1) Pre[Next[nxt]]=u.id;
		Push((QueueData){Val[u.id],u.id});
	}

	printf("%lld\n",Ans);
	return 0;
}

bool operator < (QueueData A,QueueData B){
	if (A.key!=B.key) return A.key>B.key;
	else return A.id<B.id;
}

bool operator == (QueueData A,QueueData B){
	return ((A.key==B.key)&&(A.id==B.id));
}

void Push(QueueData u){
	Q.push(u);return;
}

void Delete(QueueData u){
	Del.push(u);return;
}

QueueData Top(){
	while ((!Q.empty())&&(!Del.empty())&&(Q.top()==Del.top())) Q.pop(),Del.pop();
	return Q.top();
}

void Pop(){
	while ((!Q.empty())&&(!Del.empty())&&(Q.top()==Del.top())) Q.pop(),Del.pop();
	Q.pop();return;
}
