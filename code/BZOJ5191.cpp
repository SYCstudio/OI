#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(Arr,sz,x) (lower_bound(&Arr[1],&Arr[sz+1],x)-Arr)

const int inf=147483647;

class SegmentData
{
public:
	int mn,lz,ls,rs;
	SegmentData(){mn=inf;lz=inf;return;}
};

class Data
{
public:
	int x,y,t;
};

const int maxN=101000;

int n,m;
SegmentData S[maxN*400];
int rt1[maxN],rt2[maxN],rt3[maxN],rt4[maxN],nodecnt;
Data D[maxN],Q[maxN];
int numx,X[maxN+maxN],numy,Y[maxN+maxN];

bool cmp(Data A,Data B);
void Modify(int &now,int l,int r,int ql,int qr,int mn);
int Query(int now,int l,int r,int pos);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&D[i].x,&D[i].y,&D[i].t),X[++numx]=D[i].x,Y[++numy]=D[i].y;
	for (int i=1;i<=m;i++) scanf("%d%d",&Q[i].x,&Q[i].y),X[++numx]=Q[i].x,Y[++numy]=Q[i].y;
	sort(&X[1],&X[numx+1]);sort(&Y[1],&Y[numy+1]);numx=unique(&X[1],&X[numx+1])-X-1;numy=unique(&Y[1],&Y[numy+1])-Y-1;

	for (int i=1;i<=n;i++) D[i].x=Find(X,numx,D[i].x),D[i].y=Find(Y,numy,D[i].y);
	for (int i=1;i<=m;i++) Q[i].x=Find(X,numx,Q[i].x),Q[i].y=Find(Y,numy,Q[i].y);

	sort(&D[1],&D[n+1],cmp);

	for (int i=1;i<=n;i++) cout<<D[i].x<<" "<<D[i].y<<" "<<D[i].t<<endl;
	for (int i=1;i<=m;i++) cout<<Q[i].x<<" "<<Q[i].y<<endl;

	for (int i=n,j=numx+1;i>=1;i--){
		while (j>D[i].x) rt1[j-1]=rt1[j],--j;
		Modify(rt1[j],1,numy,1,D[i].y,D[i].t+X[D[i].x]+Y[D[i].y]);
	}
	for (int i=1,j=0;i<=n;i++){
		while (j<D[i].x) rt2[j+1]=rt2[j],++j;
		Modify(rt2[j],1,numy,1,D[i].y,D[i].t-X[D[i].x]+Y[D[i].y]);
	}
	for (int i=n,j=numx+1;i>=1;i--){
		while (j>D[i].x) rt3[j-1]=rt3[j],--j;
		Modify(rt3[j],1,numy,D[i].y,numy,D[i].t+X[D[i].x]-Y[D[i].y]);
	}
	for (int i=1,j=0;i<=n;i++){
		while (j<D[i].x) rt4[j+1]=rt4[j],++j;
		Modify(rt4[j],1,numy,D[i].y,numy,D[i].t-X[D[i].x]-Y[D[i].y]);
	}
	cout<<Query(rt1[numx],1,numy,1)<<endl;

	for (int i=1;i<=m;i++) cout<<Query(rt1[Q[i].x],1,numy,Q[i].y)<<" "<<Query(rt2[Q[i].x],1,numy,Q[i].y)<<" "<<Query(rt3[Q[i].x],1,numy,Q[i].y)<<" "<<Query(rt4[Q[i].x],1,numy,Q[i].y)<<endl;

	for (int i=1;i<=m;i++) printf("%d\n",min(min(Query(rt1[Q[i].x],1,numy,Q[i].y)-X[Q[i].x]-Y[Q[i].y]
												 ,Query(rt2[Q[i].x],1,numy,Q[i].y)+X[Q[i].x]-Y[Q[i].y])
											 ,min(Query(rt3[Q[i].x],1,numy,Q[i].y)-X[Q[i].x]+Y[Q[i].y]
												  ,Query(rt4[Q[i].x],1,numy,Q[i].y)+X[Q[i].x]+Y[Q[i].y])));

	return 0;
}

bool cmp(Data A,Data B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

void Modify(int &now,int l,int r,int ql,int qr,int mn){
	S[++nodecnt]=S[now];now=nodecnt;S[now].mn=min(S[now].mn,mn);
	if ((l==ql)&&(r==qr)){
		S[now].lz=min(S[now].lz,mn);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,mn);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,mn);
	else{
		Modify(S[now].ls,l,mid,ql,mid,mn);
		Modify(S[now].rs,mid+1,r,mid+1,qr,mn);
	}
	return;
}

int Query(int now,int l,int r,int pos){
	if (l==r) return min(S[now].mn,S[now].lz);
	int mid=(l+r)>>1;
	if (pos<=mid) return min(S[now].lz,Query(S[now].ls,l,mid,pos));
	else return min(S[now].lz,Query(S[now].rs,mid+1,r,pos));
}
