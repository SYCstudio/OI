#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "forest"
#define IL inline

const int maxN=101000;
const int inf=2147483647;

int n,Q;
ll A[maxN],B[maxN],C[maxN],D[maxN],E[maxN],Delta[maxN],S[maxN];
multiset<ll> MS[maxN];
multiset<ll> Min,Max;

IL void UpdateE(int u,ll key);
IL void UpdateC(int u,ll key);
IL void UpdateD(int u,ll key);
IL void Add(int u,ll key);
IL void Del(int u,ll key);
IL void Modify(int u,ll key);

int main(){
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%lld",&B[i]);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]);

	for (int i=1;i<=n;i++) D[i]+=2,D[A[i]]++;
	for (int i=1;i<=n;i++) E[i]=B[i]/D[i];
	for (int i=1;i<=n;i++) S[A[i]]+=E[i];
	for (int i=1;i<=n;i++) C[i]=B[i]-D[i]*E[i]+S[i]+E[i]+E[A[i]],MS[A[i]].insert(C[i]);
	for (int i=1;i<=n;i++) if (MS[i].empty()==0) Min.insert(*MS[i].begin()),Max.insert(*(--MS[i].end()));

	//cout<<"Init:"<<endl;
	//cout<<"C:";for (int i=1;i<=n;i++) cout<<C[i]<<" ";cout<<endl;
	//cout<<"D:";for (int i=1;i<=n;i++) cout<<D[i]<<" ";cout<<endl;
	//cout<<"E:";for (int i=1;i<=n;i++) cout<<E[i]<<" ";cout<<endl;

	while (Q--){
		int opt;scanf("%d",&opt);
		if (opt==1){
			int u,w;scanf("%d%d",&u,&w);
			int v=A[u];
			C[u]=C[u]+Delta[v];UpdateC(v,C[v]-E[u]);
			Del(v,C[u]);C[u]=C[u]-E[v];
			UpdateD(v,D[v]-1);UpdateE(v,B[v]/D[v]);

			UpdateD(w,D[w]+1);UpdateE(w,B[w]/D[w]);
			C[u]=C[u]+E[w];
			Add(w,C[u]);UpdateC(w,C[w]+E[u]);
			C[u]=C[u]-Delta[w];
			A[u]=w;

			//cout<<"A :";for (int i=1;i<=n;i++) cout<<A[i]<<" ";cout<<endl;
			//cout<<"C :";for (int i=1;i<=n;i++) cout<<C[i]<<" ";cout<<endl;
			//cout<<"D :";for (int i=1;i<=n;i++) cout<<D[i]<<" ";cout<<endl;
			//cout<<"E :";for (int i=1;i<=n;i++) cout<<E[i]<<" ";cout<<endl;
			//cout<<"Dt:";for (int i=1;i<=n;i++) cout<<Delta[i]<<" ";cout<<endl;
		}
		if (opt==2){
			int p;scanf("%d",&p);
			printf("%lld\n",C[p]+Delta[A[p]]);
		}
		if (opt==3) printf("%lld %lld\n",(*Min.begin()),(*(--Max.end())));
	}

	return 0;
}

IL void UpdateD(int u,ll key){
	UpdateE(u,B[u]/D[u]);
	UpdateC(u,C[u]+D[u]*E[u]);
	D[u]=key;
	UpdateC(u,C[u]-D[u]*E[u]);
	return;
}

IL void UpdateE(int u,ll key){
	//cout<<"UpdateE:"<<u<<" "<<E[u]<<"->"<<key<<endl;
	UpdateC(A[u],C[A[u]]-E[u]);UpdateC(u,C[u]-E[u]+D[u]*E[u]);
	Modify(u,key-E[u]);
	E[u]=key;
	UpdateC(A[u],C[A[u]]+E[u]);UpdateC(u,C[u]+E[u]-D[u]*E[u]);
	return;
}

IL void UpdateC(int u,ll key){
	//cout<<"UpdateC:"<<u<<" "<<C[u]<<"->"<<key<<endl;
	Del(A[u],C[u]+Delta[A[u]]);
	C[u]=key;
	Add(A[u],C[u]+Delta[A[u]]);
	return;
}

IL void Add(int u,ll key){
	if (MS[u].empty()==0){
		Min.erase(Min.find(Delta[u]+(*MS[u].begin())));Max.erase(Max.find(Delta[u]+(*(--MS[u].end()))));
	}
	key=key-Delta[u];
	MS[u].insert(key);
	Min.insert(Delta[u]+(*MS[u].begin()));Max.insert(Delta[u]+(*(--MS[u].end())));
	return;
}

void Del(int u,ll key){
	if (MS[u].empty()==0){
		Min.erase(Min.find(Delta[u]+(*MS[u].begin())));Max.erase(Max.find(Delta[u]+(*(--MS[u].end()))));
	}
	key-=Delta[u];
	MS[u].erase(MS[u].find(key));
	if (MS[u].empty()==0){
		Min.insert(Delta[u]+(*MS[u].begin()));Max.insert(Delta[u]+(*(--MS[u].end())));
	}
	return;
}

IL void Modify(int u,ll key){
	if (MS[u].empty()==0){
		Min.erase(Min.find(Delta[u]+(*MS[u].begin())));Max.erase(Max.find(Delta[u]+(*(--MS[u].end()))));
	}
	Delta[u]+=key;
	if (MS[u].empty()==0){
		Min.insert(Delta[u]+(*MS[u].begin()));Max.insert(Delta[u]+(*(--MS[u].end())));
	}
	return;
}

