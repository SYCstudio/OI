#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000;
const int maxQ=maxN<<1;
const int inf=2147483647;

class QData
{
public:
	int l,r,id;
};

int n,m,qcnt;
int Sum[maxN],Id[maxN],Zero[maxN];
QData QD[maxQ];

class Queue
{
	int fst,lst,len;
public:
	void pop_back(){
		lst=QD[lst].l;len--;
		if (len==0) lst=fst=0;
	}
	void pop_front(){
		fst=QD[fst].r;len--;
		if (len==0) lst=fst=0;
	}
	bool empty(){
		return len==0;
	}
	int front(){
		return QD[fst].id;
	}
	int back(){
		return QD[lst].id;
	}
	void push_nopop(int id){
		QD[++qcnt]=((QData){lst,0,id});
		if (len) QD[lst].r=qcnt,lst=qcnt;
		else fst=lst=qcnt;
		++len;return;
	}
	void push(int id){
		while ((len)&&(Id[back()]>Id[id])) pop_back();
		push_nopop(id);
		return;
	}
};
Queue _Q1[maxQ],_Q2[maxQ],*q1=_Q1+maxN,*q2=_Q2+maxN;

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%d%d",&Id[i],&Sum[i]);
		if (Sum[i]==0) Sum[i]=-1;
	}
	for (int i=n;i>=1;i--) Sum[i]+=Sum[i+1],Zero[i]=Zero[i+1]+(Sum[i]==0);
	int ans=(Sum[1])?(ceil((ld)Sum[1]/(ld)m)):(Zero[1]<m);
	Zero[n+1]=-1;Id[n+1]=n+1;
	if (ans==0){
		for (int i=1,j=2;i<m;i++){
			while (Zero[j+1]>=m-i){
				if (Sum[j+1]==0) q1[0].push(j);
				j++;
			}
			printf("%d ",Id[q1[0].front()]);q1[0].pop_front();
		}
	}
	else{
		int last=0;
		for (int i=2;i<=n;i++) q1[Sum[i]].push_nopop(i-1);
		for (int i=1;i<m;i++){
			int nowans=n+1;
			for (int j=Sum[last+1]-ans;j<=Sum[last+1]+ans;j++){
				if (ceil((ld)abs(j)/(ld)(m-i))>ans) continue;
				while ((!q1[j].empty())&&((n-q1[j].front()>=m-i))){
					if (q1[j].front()>last) q2[j].push(q1[j].front());
					q1[j].pop_front();
				}
				while ((!q2[j].empty())&&(q2[j].front()<=last)) q2[j].pop_front();
				if (!q2[j].empty()){
					if (Id[q2[j].front()]<Id[nowans]) nowans=q2[j].front();
				}
			}
			printf("%d ",Id[nowans]);last=nowans;
		}
	}
	printf("%d\n",Id[n]);return 0;
}
