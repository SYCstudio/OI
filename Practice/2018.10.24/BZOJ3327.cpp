//精度问题，未通过全部测试数据
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

const int maxN=101000;
const ld Pi=acos(-1);
const ld eps=1e-6;
const int inf=2147483647;
const ld INF=1e20;

class Point
{
public:
	ld x,y;int ls,rs,col;
	ld mnx,mxx,mny,mxy;
};

int n,nowD,root;
ld W,H;
Point P[maxN];
int UFS[maxN],Sz[maxN];
int del[maxN];

bool operator < (Point A,Point B);
int Build(int l,int r,int d);
void Query(int now,int id);
void Merge(int u,int v);
int Find(int x);
ld Cross(ld x1,ld y1,ld x2,ld y2);

int main(){
	//freopen("4.in","r",stdin);
	scanf("%LF%LF",&W,&H);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%LF%LF%d",&P[i].x,&P[i].y,&P[i].col),UFS[i]=i,Sz[i]=1;
	root=Build(1,n,0);
	for (int i=1;i<=n;i++) Query(root,i);
	//for (int i=1;i<=n;i++) cout<<"("<<P[i].x<<" "<<P[i].y<<") "<<P[i].col<<endl;
	//for (int i=1;i<=n;i++) cout<<Find(i)<<" ";cout<<endl;
	//cout<<Sz[2]<<" "<<Sz[5]<<endl;
	for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) if ((sqr(P[i].x-P[j].x)+sqr(P[i].y-P[j].y)<=2.0*2.0+eps)&&(P[i].col==P[j].col)) Merge(i,j);
	int Q;scanf("%d",&Q);ll Ans=0;
	while (Q--){
		//cout<<endl;
		//cout<<"nowQ:"<<Q<<endl;
		ld alpha;int col;scanf("%LF%d",&alpha,&col);alpha=alpha*Pi/180.0;
		ld x=cos(alpha),y=sin(alpha),d=1.0;
		ld mnid=-1,mindist=INF;
		//cout<<"("<<x<<" "<<y<<") "<<d<<endl;
		for (int i=1;i<=n;i++)
			if ((del[Find(i)]==0)&&(fabs(Cross(P[i].x,P[i].y,x,y))/d<=2.0+eps)){
				//ld cos=fabs((P[i].x*x+P[i].y*y)/(sqrt(P[i].x*P[i].x+P[i].y*P[i].y)*sqrt(x*x+y*y)));
				ld dist=fabs(Cross(P[i].x,P[i].y,x,y))/d;
				//ld dd=sqrt(P[i].x*P[i].x+P[i].y*P[i].y)*cos;
				ld dd=fabs((P[i].x*x+P[i].y*y)/sqrt(x*x+y*y));
				dd=dd-sqrt(sqr(2.0)-sqr(dist));
				if (dd<mindist) mnid=i,mindist=dd;
			}
		//cout<<"mnid:"<<mnid<<" "<<mindist<<endl;
		if (mnid!=-1){
			x*=mindist;y*=mindist;
			//cout<<"stop point:"<<x<<" "<<y<<endl;
			int cnt=0;
			for (int i=1;i<=n;i++)
				if ((del[Find(i)]==0)&&(sqr(x-P[i].x)+sqr(y-P[i].y)<=4.0+eps)&&(P[i].col==col)) cnt+=Sz[Find(i)],del[Find(i)]=-1/*,cout<<i<<" F:"<<Find(i)<<endl*/;
			//cout<<"cnt:"<<cnt<<endl;
			if (cnt>=2){
				for (int i=1;i<=n;i++) if (del[Find(i)]==-1) del[Find(i)]=1;
				cnt++;
				Ans=Ans+1ll*cnt*cnt;
			}
			else{
				int id=-1;
				for (int i=1;i<=n;i++) if ((del[Find(i)]==-1)&&(sqr(x-P[i].x)+sqr(y-P[i].y)<=4.0+eps)&&(P[i].col==col)) del[Find(i)]=0,id=i/*,cout<<i<<" G:"<<Find(i)<<endl*/;
				//cout<<"id:"<<id<<endl;
				++n;P[n].x=x;P[n].y=y;
				UFS[n]=n;P[n].col=col;Sz[n]=1;
				if (id!=-1) Merge(id,n);
			}
		}
		else{
			ld k=H/W;
			if (fabs(x)<eps){
				++n;P[n].x=0;P[n].y=H-1;
				UFS[n]=n;P[n].col=col;Sz[n]=1;
			}
			else if (fabs(y)<=k*fabs(x)){
				if (y/x>0){
					ld xx=W-1,yy=xx*y/x,d=sqrt(xx*xx+yy*yy);
					x*=d;y*=d;++n;P[n].x=x;P[n].y=y;UFS[n]=n;P[n].col=col;Sz[n]=1;
				}
				else{
					ld xx=-W+1,yy=xx*y/x,d=sqrt(xx*xx+yy*yy);
					x*=d;y*=d;++n;P[n].x=x;P[n].y=y;UFS[n]=n;P[n].col=col;Sz[n]=1;
				}
			}
			else{
				ld yy=H-1,xx=yy*x/y,d=sqrt(xx*xx+yy*yy);
				x*=d;y*=d;++n;P[n].x=x;P[n].y=y;UFS[n]=n;P[n].col=col;Sz[n]=1;
			}
			//cout<<"stop at:"<<P[n].x<<" "<<P[n].y<<" ["<<n<<"]"<<endl;
		}
		//cout<<"now ufs:";for (int i=1;i<=n;i++) cout<<UFS[i]<<" ";cout<<endl;
		//cout<<"now del:";for (int i=1;i<=n;i++) cout<<del[Find(i)]<<" ";cout<<endl;
		//cout<<"now siz:";for (int i=1;i<=n;i++) cout<<Sz[Find(i)]<<" ";cout<<endl;
	}
	printf("%lld\n",Ans);return 0;
}

bool operator < (Point A,Point B){
	if (nowD==0) return A.x<B.x;
	else return A.y<B.y;
}

int Build(int l,int r,int d){
	nowD=d;int mid=(l+r)>>1;
	nth_element(&P[l],&P[mid],&P[r+1]);
	P[mid].mnx=P[mid].x-1;P[mid].mxx=P[mid].x+1;
	P[mid].mny=P[mid].y-1;P[mid].mxy=P[mid].y+1;
	if (l<mid){
		P[mid].ls=Build(l,mid-1,d^1);
		P[mid].mnx=min(P[mid].mnx,P[P[mid].ls].mnx);
		P[mid].mxx=max(P[mid].mxx,P[P[mid].ls].mxx);
		P[mid].mny=min(P[mid].mny,P[P[mid].ls].mny);
		P[mid].mxy=max(P[mid].mxy,P[P[mid].ls].mxy);
	}
	if (mid<r){
		P[mid].rs=Build(mid+1,r,d^1);
		P[mid].mnx=min(P[mid].mnx,P[P[mid].rs].mnx);
		P[mid].mxx=max(P[mid].mxx,P[P[mid].rs].mxx);
		P[mid].mny=min(P[mid].mny,P[P[mid].rs].mny);
		P[mid].mxy=max(P[mid].mxy,P[P[mid].rs].mxy);
	}
	return mid;
}

void Query(int now,int id){
	if ((P[now].mnx-eps>P[id].x+1)||(P[now].mxx+eps<P[id].x-1)||(P[now].mny-eps>P[id].y+1)||(P[now].mxy+eps<P[id].y-1)) return;
	if ((sqr(P[id].x-P[now].x)+sqr(P[id].y-P[now].y)<=2.0*2.0+eps)&&(P[now].col==P[id].col)) Merge(now,id);
	if (P[now].ls) Query(P[now].ls,id);
	if (P[now].rs) Query(P[now].rs,id);
	return;
}

void Merge(int u,int v){
	u=Find(u);v=Find(v);
	if (u==v) return;
	Sz[u]+=Sz[v];UFS[v]=u;
	return;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

ld Cross(ld x1,ld y1,ld x2,ld y2){
	return x1*y2-x2*y1;
}
