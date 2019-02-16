#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxL=35;
const int inf=2147483647;
const ll INF=1e18;

int n,L,P;
char str[maxN][maxL];
ld Len[maxN],Q[maxN],From[maxN];
ld F[maxN];

ld QPowa(ld key,ll cnt);
ll Lower(int u,int v);
ld calc(int u,int v);
void Outp(int id);

int main(){
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	int Case;scanf("%d",&Case);
	while (Case--){
		scanf("%d%d%d",&n,&L,&P);
		for (int i=1;i<=n;i++) scanf("%s",str[i]),Len[i]=Len[i-1]+strlen(str[i]);
		F[0]=Q[1]=0;int L=1,R=1;
		bool flag=0;
		for (int i=1;i<=n;i++){
			//cout<<"i:"<<i<<" ";for (int j=L;j<=R;j++) cout<<Q[j]<<" ";cout<<endl;
			
			while ((L<R)&&(Lower(Q[L],Q[L+1])<=i)) L++;
			F[i]=calc(Q[L],i);From[i]=Q[L];
			while ((L<R)&&(Lower(Q[R],i)<Lower(Q[R-1],Q[R]))) R--;
			Q[++R]=i;
			//*/
			/*
			F[i]=INF;
			for (int j=0;j<i;j++)
				if (calc(j,i)<=F[i]) From[i]=j,F[i]=calc(j,i);
			//*/
		}
		if (F[n]>1e18) printf("Too hard to arrange\n");
		else{
			//cout<<"From:"<<endl;for (int i=1;i<=n;i++) cout<<From[i]<<" ";cout<<endl;
			printf("%lld\n",(ll)F[n]);
			Outp(n);
		}
		printf("--------------------");
		if (Case) printf("\n");
	}

	return 0;
}

ld QPowa(ld key,ll cnt){
	if (key<0) key=-key;
	ld ret=1;
	while (cnt){
		if (cnt&1) ret*=key;
		key*=key;cnt>>=1;
	}
	return ret;
}

ll Lower(int u,int v){
	if (calc(u,n)<calc(v,n)) return n+1;
	int l=v+1,r=n,ret=n+1;
	do{
		int mid=(l+r)>>1;
		if (calc(u,mid)>=calc(v,mid)) ret=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	//cout<<"lower ["<<u<<" "<<v<<"]:"<<ret<<endl;
	return ret;
}

ld calc(int u,int v){
	return F[u]+QPowa(Len[v]-Len[u]+(v-u-1)-L,P);
}

void Outp(int id){
	if (id==0) return;
	Outp(From[id]);
	for (int i=From[id]+1;i<=id;i++) printf(((i==id)?("%s\n"):("%s ")),str[i]);
	return;
}
