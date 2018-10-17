#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int inf=2147483647;
const ll INF=1e18;

class Point
{
public:
	ll x,y;
};

int n;
ll S,F[maxN],T[maxN];
ll DP[maxN],Path[maxN];
Point P[maxN],Q[maxN];

void Divide(int l,int r);
Point operator - (Point A,Point B);
ll Cross(Point A,Point B);

int main(){
	scanf("%d%lld",&n,&S);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&T[i],&F[i]),T[i]+=T[i-1],F[i]+=F[i-1];
	DP[0]=0;for (int i=1;i<=n;i++) DP[i]=INF;
	//for (int i=1;i<=n;i++) for (int j=0;j<i;j++) if (DP[i]>DP[j]+T[i]*(F[i]-F[j])+S*(F[n]-F[j])) DP[i]=DP[j]+T[i]*(F[i]-F[j])+S*(F[n]-F[j]),Path[i]=j;

	//cout<<DP[n]<<endl;
	Divide(1,n);

	//for (int i=1;i<=n;i++) cout<<DP[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Path[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<"("<<P[i].x<<","<<P[i].y<<")"<<" ";cout<<endl;
	
	printf("%lld\n",DP[n]);return 0;
}

void Divide(int L,int R){
	if (L>R) return;
	if (L==R){
		DP[L]=min(DP[L-1]+T[L]*(F[L]-F[L-1])+S*(F[n]-F[L-1]),DP[L]);
		//cout<<"GetKey:"<<L<<":"<<DP[L]<<endl;
		P[L]=((Point){F[L],DP[L]-S*F[L]});
		return;
	}
	int mid=(L+R)>>1;
	Divide(L,mid);

	int top=1;Q[1]=((Point){0,0});
	for (int i=L;i<=mid;i++){
		while ((top>=2)&&(Cross(P[i]-Q[top-1],Q[top]-Q[top-1])>=0)) top--;
		Q[++top]=P[i];
	}
	Q[++top]=((Point){Q[top-1].x+1,INF});

	//cout<<"Divide:["<<L<<"-"<<R<<"]"<<mid<<endl;
	//for (int i=1;i<=top;i++) cout<<"("<<Q[i].x<<","<<Q[i].y<<")"<<endl;
	//for (int i=L;i<=mid;i++) cout<<i<<":("<<P[i].x<<","<<P[i].y<<")"<<endl;
	for (int i=mid+1;i<=R;i++){
		int l=1,r=top-1,pos=1;
		while (l<=r){
			int mid=(l+r)>>1;
			Point d=Q[mid+1]-Q[mid];
			if (d.y>=T[i]*d.x) pos=mid,r=mid-1;
			else l=mid+1;
		}
		//cout<<pos<<" -> "<<i<<" "<<T[i]<<" "<<Q[pos].y-Q[pos].x+S*F[n]+T[i]*F[i]<<" "<<endl;
		//*/
		for (int j=max(1,pos-3);j<=min(pos+3,top);j++){
			//cout<<"("<<Q[j].x<<","<<Q[j].y<<") -> "<<i<<" "<<Q[j].y-Q[j].x+S*F[n]+T[i]*F[i]<<endl;
			DP[i]=min(DP[i],Q[j].y-T[i]*Q[j].x+S*F[n]+T[i]*F[i]);
		}
	}

	Divide(mid+1,R);
	return;
}

Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}

ll Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

/*
5 1
1 3
3 2
4 3
2 3
1 4
//*/
