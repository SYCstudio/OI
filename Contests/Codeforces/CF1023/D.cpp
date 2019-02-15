#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

int n,Q;
int Seq[maxN],Ans[maxN];
int Left[maxN],Right[maxN];
vector<int> V[maxN];
set<int> S;

int main(){
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Ans[i]=Seq[i];
	for (int i=1;i<=n;i++)
		if (Seq[i]!=0){
			if (Left[Seq[i]]==0) Left[Seq[i]]=i;
			Right[Seq[i]]=i;
		}
	for (int i=1;i<=Q;i++)
		if (Left[i]!=0){
			V[Left[i]].push_back(i);
			V[Right[i]+1].push_back(-i);
		}
	/*
	for (int i=1;i<=n;i++){
		for (int sz=V[i].size(),j=0;j<sz;j++)
			cout<<V[i][j]<<" ";
		cout<<endl;
	}
	//*/
	bool flag=1;
	bool usemax=(Left[Q]==0);
	Ans[0]=1;
	for (int i=1;i<=n;i++){
		for (int sz=V[i].size(),j=0;j<sz;j++)
			if (V[i][j]>0) S.insert(V[i][j]);
			else S.erase(-V[i][j]);
		if (Seq[i]==0){
			if (usemax==1){
				Ans[i]=Q;usemax=0;
			}
			else if (S.size()) Ans[i]=(*--S.end());
			else Ans[i]=Ans[i-1];
			continue;
		}
		if (Seq[i]!=(*--S.end())){
			flag=0;break;
		}
	}
	int mx=0;
	for (int i=1;i<=n;i++) mx=max(mx,Ans[i]);
	if (mx!=Q) flag=0;
	if (flag==0) printf("NO\n");
	else{
		printf("YES\n");
		for (int i=1;i<=n;i++) printf("%d ",Ans[i]);
		printf("\n");
	}
	return 0;
}
