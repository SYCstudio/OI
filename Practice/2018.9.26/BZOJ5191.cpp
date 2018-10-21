#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(Arr,sz,x) (lower_bound(&Arr[1],&Arr[sz+1],x)-Arr)
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int inf=2000000000;
const int meminf=2139062143;

ll numx,X[maxN+maxN],numy,Y[maxN+maxN];

class Data
{
public:
	ll x,y,t;
};

int n,m;
Data D[maxN],Q[maxN];
ll Ans[maxN];
int Mn[maxN*8];

bool cmp(Data A,Data B);
void Modify(int now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);

int main(){
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld%lld%lld",&D[i].x,&D[i].y,&D[i].t),X[++numx]=D[i].x,Y[++numy]=D[i].y;
	for (int i=1;i<=m;i++) scanf("%lld%lld",&Q[i].x,&Q[i].y),X[++numx]=Q[i].x,Y[++numy]=Q[i].y,Ans[i]=abs(Q[i].x-Q[i].y),Q[i].t=i;
	sort(&X[1],&X[numx+1]);sort(&Y[1],&Y[numy+1]);numx=unique(&X[1],&X[numx+1])-X-1;numy=unique(&Y[1],&Y[numy+1])-Y-1;


	for (int i=1;i<=n;i++) D[i].x=Find(X,numx,D[i].x),D[i].y=Find(Y,numy,D[i].y);
	for (int i=1;i<=m;i++) Q[i].x=Find(X,numx,Q[i].x),Q[i].y=Find(Y,numy,Q[i].y);
	
	sort(&D[1],&D[n+1],cmp);sort(&Q[1],&Q[m+1],cmp);

	//for (int i=1;i<=numx;i++) cout<<X[i]<<" ";cout<<endl;
	//for (int i=1;i<=numy;i++) cout<<Y[i]<<" ";cout<<endl;
	
	mem(Mn,127);
	for (int i=m,j=n;i>=1;i--){
		while ((j)&&(D[j].x>=Q[i].x)) Modify(1,1,numy,D[j].y,D[j].t+X[D[j].x]+Y[D[j].y]),j--;
		//cerr<<"A "<<i<<" "<<j<<" "<<Q[i].y<<endl;
		if (Query(1,1,numy,Q[i].y,numy)!=meminf) Ans[Q[i].t]=min(Ans[Q[i].t],(ll)Query(1,1,numy,Q[i].y,numy)-X[Q[i].x]-Y[Q[i].y]);
		//if (i==n) cout<<Query(1,1,numy,Q[i].y,numy)<<endl;
	}

	mem(Mn,127);
	for (int i=1,j=1;i<=m;i++){
		while ((j<=n)&&(D[j].x<=Q[i].x)) Modify(1,1,numy,D[j].y,D[j].t-X[D[j].x]+Y[D[j].y]),j++;
		//cerr<<"B "<<i<<" "<<j<<endl;
		if (Query(1,1,numy,Q[i].y,numy)!=meminf) Ans[Q[i].t]=min(Ans[Q[i].t],(ll)Query(1,1,numy,Q[i].y,numy)+X[Q[i].x]-Y[Q[i].y]);
		//cout<<i<<" "<<j<<endl;
		//if (i==n) cout<<Query(1,1,numy,Q[i].y,numy)<<endl;
	}

	mem(Mn,127);
	for (int i=m,j=n;i>=1;i--){
		while ((j)&&(D[j].x>=Q[i].x)) Modify(1,1,numy,D[j].y,D[j].t+X[D[j].x]-Y[D[j].y]),j--;
		//cerr<<"C "<<i<<" "<<j<<endl;
		if (Query(1,1,numy,1,Q[i].y)!=meminf) Ans[Q[i].t]=min(Ans[Q[i].t],(ll)Query(1,1,numy,1,Q[i].y)-X[Q[i].x]+Y[Q[i].y]);
		//if (i==n) cout<<Query(1,1,numy,1,Q[i].y)<<endl;
	}

	mem(Mn,127);
	for (int i=1,j=1;i<=m;i++){
		while ((j<=n)&&(D[j].x<=Q[i].x)) Modify(1,1,numy,D[j].y,D[j].t-X[D[j].x]-Y[D[j].y]),j++;
		//cerr<<"D "<<i<<" "<<j<<endl;
		if (Query(1,1,numy,1,Q[i].y)!=meminf) Ans[Q[i].t]=min(Ans[Q[i].t],(ll)Query(1,1,numy,1,Q[i].y)+X[Q[i].x]+Y[Q[i].y]);
		//if (i==n) cout<<Query(1,1,numy,1,Q[i].y)<<endl;
	}
	
	for (int i=1;i<=m;i++) printf("%lld\n",Ans[i]);
	
	
	return 0;
}

bool cmp(Data A,Data B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

void Modify(int now,int l,int r,int pos,int key){
	//cerr<<"Modify:"<<now<<" "<<l<<" "<<r<<" "<<pos<<" "<<key<<endl;
	Mn[now]=min(Mn[now],key);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
}

int Query(int now,int l,int r,int ql,int qr){
	//cerr<<"Query:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if ((l==ql)&&(r==qr)) return Mn[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

/*
2 3
0 10 1
13 8 2
1 12
5 2
20 7
//*/
