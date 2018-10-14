#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020000;
const int inf=2147483647;

int n,c,m;
int Seq[maxN],Lst[maxN],LLst[maxN];
vector<pair<int,int> > Qn[maxN];
int Ans[maxN];
int Cnt[maxN];

void Modify(int pos,int key);
int Sum(int pos);
int Query(int l,int r);

int main(){
	scanf("%d%d%d",&n,&c,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	for (int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		Qn[r].push_back(make_pair(l,i));
	}
	for (int i=1;i<=n;i++){
		if (Lst[Seq[i]]==0) Lst[Seq[i]]=i;
		else{
			if (LLst[Seq[i]]!=0) Modify(LLst[Seq[i]],-1);
			Modify(Lst[Seq[i]],1);
			LLst[Seq[i]]=Lst[Seq[i]];Lst[Seq[i]]=i;
		}
		for (int j=0,sz=Qn[i].size();j<sz;j++)
			Ans[Qn[i][j].second]=Query(Qn[i][j].first,i);
	}
	for (int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}

void Modify(int pos,int key){
	while (pos<=n){
		Cnt[pos]+=key;pos+=(pos)&(-pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=Cnt[pos];pos-=(pos)&(-pos);
	}
	return ret;
}

int Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
