#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int inf=2147483647;

int n;
int UFS[maxN];
bool mark[maxN];

int Find(int x);

int main(){
	for (int i=1;i<maxN;i++) UFS[i]=i;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int u,v;scanf("%d%d",&u,&v);
		int fu=Find(u),fv=Find(v);
		if (fu==fv){
			mark[fu]=1;continue;
		}
		if (fu>fv) swap(fu,fv);
		if ((mark[fu])||(mark[fv])) mark[fu]=mark[fv]=1;
		else mark[fu]=1,UFS[fu]=fv;
	}

	int ans=0;
	while (mark[ans+1]) ans++;
	printf("%d\n",ans);
	return 0;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
