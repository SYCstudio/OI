#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int P=100000;
const int inf=2147483647;

class Data
{
public:
	ll key;int id;
};

int n,m,K;
ll Val[maxN],Ft[maxN],Dc[maxN],Num[maxN];
ll Use[maxN],Ans[maxN];
priority_queue<Data,vector<Data>,less<Data> > H1;
priority_queue<Data,vector<Data>,greater<Data> > H2;
vector<int> Id[maxN];
queue<Data> Tmp;

bool operator < (Data A,Data B);
bool operator > (Data A,Data B);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&Val[i],&Ft[i],&Num[i],&Dc[i]);
		if (Dc[i]!=0) Id[min((ll)P,(Num[i]+Dc[i]-1)/Dc[i])].push_back(i);
		else Id[P].push_back(i);
	}
	for (int i=P;i>=1;i--){
		for (int j=0,sz=Id[i].size();j<sz;j++) H1.push((Data){Val[Id[i][j]]+Ft[Id[i][j]],Id[i][j]});
		int res=m;
		while ((res!=0)&&(!H1.empty())){
			int id=H1.top().id;H1.pop();
			if (Use[id]==0){
				Ans[P]=Ans[P]+Val[id]+Ft[id];res--;Use[id]++;
				if (Use[id]<Num[id]) H1.push((Data){Val[id],id});
			}
			else{
				int nowuse=min((ll)res,Num[id]-Use[id]-Dc[id]*(i-1));
				Ans[P]=Ans[P]+Val[id]*nowuse;Use[id]+=nowuse;res-=nowuse;
				if (Use[id]<Num[id]) Tmp.push((Data){Val[id],id});
			}
		}
		while (!Tmp.empty()){
			H1.push(Tmp.front());Tmp.pop();
		}
	}
	int used=0;
	for (int i=1;i<=n;i++){
		if (Use[i]==1) H2.push((Data){Val[i]+Ft[i],i});
		else if (Use[i]) H2.push((Data){Val[i],i});
		used+=Use[i];
	}
	for (int i=P-1;i>=1;i--){
		Ans[i]=Ans[i+1];
		if (m*i>=used) continue;
		int res=used-m*i;
		while ((res!=0)&&(!H2.empty())){
			int id=H2.top().id;H2.pop();
			if (Use[id]!=1){
				int nowuse=min((ll)res,Use[id]-1);
				Ans[i]=Ans[i]-nowuse*Val[id];Use[id]-=nowuse;res-=nowuse;
				if (Use[id]==1) H2.push((Data){Ft[id]+Val[id],id});
				else if (Use[id]) H2.push((Data){Val[id],id});
			}
			else{
				Ans[i]=Ans[i]-Val[id]-Ft[id];Use[id]=0;res--;
			}
		}
		used=m*i;
	}
	while (K--){
		int day;scanf("%d",&day);
		printf("%lld\n",Ans[day]);
	}
	return 0;
}

bool operator < (Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.id<B.id;
}

bool operator > (Data A,Data B){
	if (A.key!=B.key) return A.key>B.key;
	return A.id>B.id;
}
