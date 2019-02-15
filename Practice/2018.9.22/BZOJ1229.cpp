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

int n,Nd[maxN],Res[maxN];
int n1,n2,c1,c2,cst;
deque<int> Q;

int Calc(int num);

int main(){
	//freopen("in.in","r",stdin);
	scanf("%d%d%d%d%d%d",&n,&n1,&n2,&c1,&c2,&cst);
	int sum=0;
	for (int i=1;i<=n;i++) scanf("%d",&Nd[i]),sum=sum+Nd[i];

	if (n1>n2) swap(n1,n2),swap(c1,c2);
	if (c1<c2) c2=c1;
	
	int L=0,R=sum;
	do{
		int sz=(R-L+1)/3;
		int md1=L+sz-1,md2=R-sz+1;
		if (Calc(md1)>=Calc(md2)) L=md1;
		else R=md2;
	}
	while (L+50<=R);
	
	int Ans=inf;
	for (int i=L;i<=R;i++) Ans=min(Ans,Calc(i));
	printf("%d\n",Ans);return 0;
}

int Calc(int num){
	Q.clear();
	int ret=0,key=num;
	for (int i=1;i<=n;i++){
		Res[i]=Nd[i];
		if (i-n1>=1) Q.push_back(i-n1);
		if (Nd[i]<=num) num-=Nd[i],ret+=Nd[i]*cst;
		else{
			int nd=Nd[i]-num;ret+=num*cst;num=0;
			while (nd){
				if (Q.empty()) return inf;
				if (Q.front()<=i-n2){
					int id=Q.front();Q.pop_front();
					int mn=min(nd,Res[id]);ret+=mn*c2;
					nd-=mn;Res[id]-=mn;
					if (Res[id]) Q.push_front(id);
				}
				else{
					int id=Q.back();Q.pop_back();
					int mn=min(nd,Res[id]);ret+=mn*c1;
					nd-=mn;Res[id]-=mn;
					if (Res[id]) Q.push_back(id);
				}
			}
		}
	}
	return ret;
}

/*
if (i-n1>=1){
			Q.push_back(i-n1);Res[i-n1]=Nd[i-n1];
		}
		if (Nd[i]<=num)	num-=Nd[i],ret+=Nd[i]*cst;
		else{
			int nd=Nd[i];
			while (nd){
				if (Q.empty()) return inf;
				if ((Q.front()<=i-n2)&&(c1>c2)){
					int id=Q.front();Q.pop_front();
					if (Res[id]>=nd){
						Res[id]-=nd;ret+=nd*c2;nd=0;Q.push_front(id);break;
					}
					else{
						nd-=Res[id];ret+=Res[id]*c2;Res[id]=0;
					}
				}
				else{
					int id=Q.back();Q.pop_back();
					if (Res[id]>=nd){
						Res[id]-=nd;ret+=nd*c1;nd=0;Q.push_back(id);break;
					}
					else{
						nd-=Res[id];ret+=Res[id]*c1;Res[id]=0;
					}
				}
			}
		}
//*/
