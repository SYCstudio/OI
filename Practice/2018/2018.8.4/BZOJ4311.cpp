#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=201000;
const int inf=2147483647;
const ld eps=1e-8;
const ll INF=1e17;

class Vector
{
public:
	ll x,y;
};

int n;
Vector Vn[maxN],Qn[maxN],St[maxN];
vector<int> S[maxN<<2];
int vcnt=0,qcnt=0,app[maxN],dip[maxN];
ll Ans[maxN];

void Modify(int now,int l,int r,int ql,int qr,int id);
void Query(int now,int l,int r);
bool cmp(int A,int B);
ld GetK(Vector A,Vector B);
ll GetAns(int id,int top);
ll Calc(Vector A,Vector B);

int main(){
	//freopen("8.in","r",stdin);freopen("out.out","w",stdout);
	mem(dip,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int opt;scanf("%d",&opt);
		if (opt==1){
			vcnt++;scanf("%lld%lld",&Vn[vcnt].x,&Vn[vcnt].y);app[vcnt]=qcnt;
		}
		if (opt==2){
			int id;scanf("%d",&id);dip[id]=qcnt;
		}
		if (opt==3){
			qcnt++;scanf("%lld%lld",&Qn[qcnt].x,&Qn[qcnt].y);Ans[qcnt]=0;
		}
	}
	for (int i=1;i<=vcnt;i++) if (dip[i]==-1) dip[i]=qcnt;

	for (int i=1;i<=vcnt;i++)
		if (app[i]!=dip[i]){
			//cout<<i<<" "<<app[i]+1<<" "<<dip[i]<<endl;
			Modify(1,1,qcnt,app[i]+1,dip[i],i);
		}
	Query(1,1,qcnt);

	for (int i=1;i<=qcnt;i++) printf("%lld\n",Ans[i]);

	return 0;
}
			
void Modify(int now,int l,int r,int ql,int qr,int id){
	if ((l==ql)&&(r==qr)){
		S[now].push_back(id);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,id);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,id);
	else{
		Modify(lson,l,mid,ql,mid,id);Modify(rson,mid+1,r,mid+1,qr,id);
	}
	return;
}

bool cmp(int A,int B){
	if (Vn[A].x==Vn[B].x) return Vn[A].y>Vn[B].y;
	return Vn[A].x<Vn[B].x;
}

void Query(int now,int l,int r){
	if (S[now].empty()==0){
		int top=0;
		sort(S[now].begin(),S[now].end(),cmp);
		for (int i=0,sz=S[now].size();i<sz;i++){
			//if ((i!=0)&&(Vn[S[now][i]].x==Vn[S[now][i-1]].x)) continue;
			while ((top>=2)&&(GetK(Vn[S[now][i]],St[top])>=GetK(St[top],St[top-1]))) top--;
			St[++top]=Vn[S[now][i]];
		}
		//cout<<"Query:"<<now<<" ["<<l<<","<<r<<"]"<<endl;
		//for (int i=1;i<=top;i++) cout<<"("<<St[i].x<<","<<St[i].y<<") ";cout<<endl;
		for (int i=l;i<=r;i++) Ans[i]=max(Ans[i],GetAns(i,top));
	}
	//for (int i=1;i<=qcnt;i++) cout<<Ans[i]<<" ";cout<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Query(lson,l,mid);Query(rson,mid+1,r);
	return;
}

ld GetK(Vector A,Vector B){
	return (ld)(A.y-B.y)/(ld)(A.x-B.x);
}

ll GetAns(int id,int top){
	if (top==1) return Calc(Qn[id],St[top]);
	int L=1,R=top-1,pos=-1;
	ld k=-(ld)Qn[id].x/(ld)Qn[id].y;
	
	do{
		int mid=(L+R)>>1;
		if (GetK(St[mid],St[mid+1])+eps>=k) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	if ((pos!=top)&&(GetK(St[pos+1],St[pos])+eps>=k)) pos++;
	//cout<<"Binary:"<<Qn[id].x<<" "<<Qn[id].y<<":"<<pos<<endl;
	ll mx=0;
	for (int j=max(1,pos-2);j<=min(top,pos+2);j++) mx=max(mx,Calc(Qn[id],St[j]));
	return mx;
}

ll Calc(Vector A,Vector B){
	return A.x*B.x+A.y*B.y;
}

/*
5
1 3 3
1 1 4
3 3 3
2 1
3 3 3

17
1 3 3
1 4 5
1 5 9
1 7 10
3 2 2
3 5 7
1 1 3
3 2 6
2 4
2 3
3 3 5
1 2 7
3 8 2
2 2
2 5
1 30 100
3 2 8
//*/

