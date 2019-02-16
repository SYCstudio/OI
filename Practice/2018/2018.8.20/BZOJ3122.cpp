#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

map<int,int> M;

int QPow(int x,int cnt,int P);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int p,a,b,x,t;scanf("%d%d%d%d%d",&p,&a,&b,&x,&t);
		if (x==t){
			printf("1\n");continue;
		}
		if (a==0){
			if (b==t) printf("2\n");
			else printf("-1\n");
			continue;
		}
		if (a==1){
			if (b==0){
				if (((t-x)%p+p)%p==0) printf("1\n");
				else printf("-1\n");
				continue;
			}
			int ans=(1ll*(t-x+p)%p*QPow(b,p-2,p)%p+1)%p;
			if (ans==0) ans=p;
			printf("%d\n",ans);continue;
		}
		int k=1ll*b*QPow(a-1,p-2,p)%p;
		
		int w=1ll*(t+k)%p*QPow((x+k)%p,p-2,p)%p;
		
		M.clear();
		int m=ceil(sqrt(p));
		int now=w;M[now]=0;
		for (int i=1;i<=m;i++){
			now=1ll*now*a%p;
			if (M.count(now)==0) M[now]=i;
		}
		int bs=QPow(a,m,p);
		now=1;bool getans=0;
		for (int i=1;i<=m;i++){
			now=1ll*now*bs%p;
			if (M.count(now)){
				int ans=((i*m%p-M[now]+1)%p+p)%p;if (ans==0) ans=p;
				printf("%d\n",ans);getans=1;break;
			}
		}
		if (getans==0) printf("-1\n");
	}

	return 0;
}

int QPow(int x,int cnt,int P){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%P;
		x=1ll*x*x%P;cnt>>=1;
	}
	return ret;
}
