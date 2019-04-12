#include<bits/stdc++.h>
using namespace std;

typedef double ld;
const int maxN=202000;
const ld eps=1e-11;

int n,Q;
ld Sy,A,B;
ld L[maxN],R[maxN],Sm[maxN];

ld GetX(ld x1,ld y1,ld x2,ld y2,ld y);
int main(){
    scanf("%lf%lf%lf",&Sy,&A,&B);scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lf%lf",&L[i],&R[i]),Sm[i]=Sm[i-1]+R[i]-L[i];
    scanf("%d",&Q);
    while (Q--){
	ld tx,ty;scanf("%lf%lf",&tx,&ty);
	ld lx=GetX(tx,ty,A,Sy,0),rx=GetX(tx,ty,B,Sy,0);
	if (lx>R[n]||rx<L[1]){
	    puts("0");continue;
	}
	lx=max(lx,L[1]);rx=min(rx,R[n]);
	int l,r,p1=0,p2=n+1;
	l=1;r=n;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (lx<=R[mid]) p1=mid,r=mid-1;
	    else l=mid+1;
	}
	l=1;r=n;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (rx>=L[mid]) p2=mid,l=mid+1;
	    else r=mid-1;
	}
	//cout<<p1<<" "<<p2<<" "<<lx<<" "<<rx<<endl;
	if (p1>p2){
	    puts("0");continue;
	}
	ld Ans=0;lx=max(lx,L[p1]);rx=min(rx,R[p2]);
	if (p1==p2) Ans=(rx-lx)*(ty-Sy)/ty;
	else{
	    Ans=Sm[p2-1]-Sm[p1];
	    if (p1>=1) Ans+=R[p1]-lx;
	    if (p2<=n) Ans+=rx-L[p2];
	    Ans*=(ty-Sy)/ty;
	}
	printf("%.11lf\n",Ans);
    }
    return 0;
}
ld GetX(ld x1,ld y1,ld x2,ld y2,ld y){
    if (fabs(x1-x2)<eps) return x1;
    ld k=(y1-y2)/(x1-x2),b=y1-k*x1;
    //cout<<"Get:"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<y<<" "<<(y-b)/k<<" "<<k<<"x+"<<b<<endl;
    return (y-b)/k;
}
