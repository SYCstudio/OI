#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int inf=2147483647;

class InSegData{
public:
	ld key;int ls,rs;
	void init(){
		key=ls=rs=0;return;
	}
};

class OutSegData{
public:
	int rt,ls,rs;
	void init(){
		rt=ls=rs=0;return;
	}
};

int n,Height[maxN],Speed[maxN];
int numcnt,Num[maxN],hcnt,spdcnt;
int innodecnt,outnodecnt,Rt[maxN],root;
ll F[maxN];
ld Cnt[maxN];
InSegData In[maxN*400];
OutSegData Out[maxN*400];

void Modify_Out(int &now,int l,int r,int x,int y,ld key,int opt);
void Modify_In(int &now,int l,int r,int y,ld key,int opt);
ld Query_Out(int &now,int l,int r,int ql,int qr,int nl,int nr,int opt);
ld Query_In(int &now,int l,int r,int ql,int qr,int opt);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&Height[i],&Speed[i]);
	
	for (int i=1;i<=n;i++) Num[i]=Height[i];
	sort(&Num[1],&Num[n+1]);hcnt=numcnt=unique(&Num[1],&Num[n+1])-Num-1;
	for (int i=1;i<=n;i++) Height[i]=lower_bound(&Num[1],&Num[numcnt+1],Height[i])-Num;

	for (int i=1;i<=n;i++) Num[i]=Speed[i];
	sort(&Num[1],&Num[n+1]);spdcnt=numcnt=unique(&Num[1],&Num[n+1])-Num-1;
	for (int i=1;i<=n;i++) Speed[i]=lower_bound(&Num[1],&Num[numcnt+1],Speed[i])-Num;

	int mx=0;
	for (int i=1;i<=n;i++){
		int f=0;ld cnt=0;
		f=Query_Out(root,1,hcnt,Height[i],hcnt,Speed[i],spdcnt,1);
		cnt=Query_Out(Rt[f],1,hcnt,Height[i],hcnt,Speed[i],spdcnt,2);
		
		F[i]=++f;Cnt[i]=(f==1)?(1):(cnt);mx=max(mx,f);
		Modify_Out(root,1,hcnt,Height[i],Speed[i],F[i],1);
		Modify_Out(Rt[F[i]],1,hcnt,Height[i],Speed[i],Cnt[i],2);
	}

	//for (int i=1;i<=n;i++) cout<<F[i]<<" "<<Cnt[i]<<endl;

	mem(Rt,0);outnodecnt=0;innodecnt=0;
	ld sum=0;
	for (int i=n;i>=1;i--){
		ld cnt=Query_Out(Rt[F[i]+1],1,hcnt,1,Height[i],1,Speed[i],2);
		if (F[i]==mx) cnt=1,sum=sum+Cnt[i];
		Cnt[i]=1ll*Cnt[i]*cnt;
		Modify_Out(Rt[F[i]],1,hcnt,Height[i],Speed[i],cnt,2);
	}

	//for (int i=1;i<=n;i++) cout<<(ll)Cnt[i]<<endl;cout<<endl;

	//cerr<<sum<<endl;

	printf("%d\n",mx);
	for (int i=1;i<=n;i++) printf("%.6lf ",(ld)Cnt[i]/(ld)sum);
	printf("\n");

	return 0;
}

void Modify_Out(int &now,int l,int r,int x,int y,ld key,int opt){
	if (now==0) now=++outnodecnt,Out[now].init();
	Modify_In(Out[now].rt,1,spdcnt,y,key,opt);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) Modify_Out(Out[now].ls,l,mid,x,y,key,opt);
	else Modify_Out(Out[now].rs,mid+1,r,x,y,key,opt);
	return;
}

void Modify_In(int &now,int l,int r,int y,ld key,int opt){
	if (now==0) now=++innodecnt,In[now].init();
	if (l==r){
		if (opt==1) In[now].key=max(In[now].key,key);
		if (opt==2) In[now].key+=key;
		return;
	}
	int mid=(l+r)>>1;
	if (y<=mid) Modify_In(In[now].ls,l,mid,y,key,opt);
	else Modify_In(In[now].rs,mid+1,r,y,key,opt);
	if (opt==1) In[now].key=max(In[In[now].ls].key,In[In[now].rs].key);
	if (opt==2) In[now].key=In[In[now].ls].key+In[In[now].rs].key;
	return;
}

ld Query_Out(int &now,int l,int r,int ql,int qr,int nl,int nr,int opt){
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return Query_In(Out[now].rt,1,spdcnt,nl,nr,opt);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_Out(Out[now].ls,l,mid,ql,qr,nl,nr,opt);
	else if (ql>=mid+1) return Query_Out(Out[now].rs,mid+1,r,ql,qr,nl,nr,opt);
	else{
		if (opt==1) return max(Query_Out(Out[now].ls,l,mid,ql,mid,nl,nr,opt),Query_Out(Out[now].rs,mid+1,r,mid+1,qr,nl,nr,opt));
		if (opt==2) return Query_Out(Out[now].ls,l,mid,ql,mid,nl,nr,opt)+Query_Out(Out[now].rs,mid+1,r,mid+1,qr,nl,nr,opt);
	}
}

ld Query_In(int &now,int l,int r,int ql,int qr,int opt){
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return In[now].key;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_In(In[now].ls,l,mid,ql,qr,opt);
	else if (ql>=mid+1) return Query_In(In[now].rs,mid+1,r,ql,qr,opt);
	else{
		if (opt==1) return max(Query_In(In[now].ls,l,mid,ql,mid,opt),Query_In(In[now].rs,mid+1,r,mid+1,qr,opt));
		if (opt==2) return Query_In(In[now].ls,l,mid,ql,mid,opt)+Query_In(In[now].rs,mid+1,r,mid+1,qr,opt);
	}
}

