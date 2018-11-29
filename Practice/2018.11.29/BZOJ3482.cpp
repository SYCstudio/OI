#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxM=10100;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Dist[maxN][maxN],W[maxM];
bool inq[maxN][maxN];
queue<pair<int,int> > Qu;
pair<ll,ll> St1[maxN],St2[maxN];

void Add_Edge(int u,int v,int w);
ll Cross(ll k1,ll b1,ll k2,ll x2);

int main(){
	//freopen("in","r",stdin);//freopen("out","w",stdout);
	mem(Head,-1);int xcnt=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		char Input[10];scanf(" %s",Input);
		if (Input[0]=='x') Add_Edge(u,v,-1),++xcnt;
		else{
			int key=0,l=strlen(Input);for (int i=0;i<l;i++) key=key*10+Input[i]-'0';
			Add_Edge(u,v,key);
		}
	}
	xcnt=min(xcnt,n);
	int Case;scanf("%d",&Case);
	while (Case--){
		int S,T;scanf("%d%d",&S,&T);mem(Dist,63);mem(inq,0);
		Dist[S][0]=0;inq[S][0]=1;Qu.push(make_pair(S,0));
		do{
			int u=Qu.front().first,d=Qu.front().second;Qu.pop();
			//if (u==T) cout<<"D:"<<u<<" "<<d<<" "<<Dist[T][d]<<endl;
			for (int i=Head[u];i!=-1;i=Next[i])
				if (W[i]==-1){
					if ((d<xcnt)&&(Dist[V[i]][d+1]>Dist[u][d])){
						Dist[V[i]][d+1]=Dist[u][d];
						if (inq[V[i]][d+1]==0){
							Qu.push(make_pair(V[i],d+1));inq[V[i]][d+1]=1;
						}
					}
				}
				else{
					if (Dist[V[i]][d]>Dist[u][d]+W[i]){
						Dist[V[i]][d]=Dist[u][d]+W[i];
						if (inq[V[i]][d]==0){
							Qu.push(make_pair(V[i],d));inq[V[i]][d]=1;
						}
					}
				}
			inq[u][d]=0;
		}
		while (!Qu.empty());

		int mx=n;
		while ((mx>=0)&&(Dist[T][mx]==Dist[0][0])) --mx;
		//cout<<mx<<endl;
		//for (int i=0;i<=mx;i++) cout<<Dist[T][i]<<" ";cout<<endl;
		if (mx==-1) {printf("0 0\n");continue;}
		if (Dist[T][0]==Dist[0][0]) {printf("inf\n");continue;}
		int top=1;St1[1]=make_pair(mx,Dist[T][mx]);St2[1]=make_pair(1,mx+Dist[T][mx]);
		for (int i=mx-1;i>=0;i--)
			if (Dist[T][i]!=Dist[0][0]){
				while ((top)&&(Cross(St1[top].first,St1[top].second,i,Dist[T][i])<=St2[top].first)) --top;
				St1[++top]=make_pair(i,Dist[T][i]);
				if (top==1) St2[top]=make_pair(1,i+Dist[T][i]);
				else{
					ll x=Cross(St1[top-1].first,St1[top-1].second,i,Dist[T][i]);
					St2[top]=make_pair(x,i*x+Dist[T][i]);
				}
			}
		//cout<<"top:"<<top<<endl;
		//for (int i=1;i<=top;i++) cout<<"("<<St1[i].first<<" "<<St1[i].second<<") ";cout<<endl;
		//for (int i=1;i<=top;i++) cout<<"("<<St2[i].first<<" "<<St2[i].second<<") ";cout<<endl;
		ll cnt=1,sum=St2[top].second;
		//ll cnt=0,sum=0;
		for (int i=1;i<top;i++){
			ll k=St2[i+1].first-St2[i].first,lt=St2[i].second+(k-1)*St1[i].first;
			//cout<<i<<" "<<k<<" "<<lt<<endl;
			cnt+=k;sum+=(St2[i].second+lt)*k/2ll;
		}
		printf("%lld %lld\n",cnt,sum);
	}
	return 0;
}

void Add_Edge(int u,int v,int w){
	//cout<<u<<" "<<v<<" "<<w<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

ll Cross(ll k1,ll b1,ll k2,ll b2){
	return (b2-b1)/(k1-k2)+((b2-b1)%(k1-k2)!=0);
}
/*
4 4
1 2 x
2 3 x
3 4 x
1 4 8
3
2 1
1 3
1 4
//*/
