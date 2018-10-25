#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int maxM=6;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt,ufs[maxM*2];bool bd[maxM*2];
	SegmentData operator = (SegmentData A){
		for (int i=0;i<maxM*2;i++) ufs[i]=A.ufs[i],bd[i]=A.bd[i];
		cnt=A.cnt;
		return *this;
	}
	void clear(){
		cnt=0;mem(ufs,0);mem(bd,0);return;
	}
	int find(int u){
		return (ufs[u]!=u)?(ufs[u]=find(ufs[u])):ufs[u];
	}
	void merge(int u,int v){
		int fu=find(u),fv=find(v);
		if (fu!=fv){
			ufs[fv]=fu;bd[fu]|=bd[fv];
		}
		return;
	}
};

int n,m;
int UFS[maxM*4],BD[maxM*4],use[maxM*4],BBD[maxM*4];
char Mp[maxN][maxM];
SegmentData S[maxN<<2];

bool isclr(char ch);
bool iscud(char ch);
void UFSMerge(int u,int v);
int Find(int u);
SegmentData Init(int id);
SegmentData Merge(SegmentData A,SegmentData B,int mid);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int pos);
SegmentData Query(int now,int l,int r,int ql,int qr);
void Outp(int now,int l,int r);

int main(){
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]);
	Build(1,1,n);
	//Outp(1,1,n);cout<<endl;
	int Q;scanf("%d",&Q);
	while (Q--){
		char opt;scanf(" %c",&opt);
		if (opt=='C'){
			int x,y;char c;scanf("%d%d %c",&x,&y,&c);
			Mp[x][y-1]=c;
			Modify(1,1,n,x);
		}
		else{
			int l,r;scanf("%d%d",&l,&r);
			printf("%d\n",Query(1,1,n,l,r).cnt);
		}
		//Outp(1,1,n);cout<<endl;
	}
	return 0;
}

bool isclr(char ch){
	return (ch=='O')||(ch=='+')||(ch=='-');
}

bool iscud(char ch){
	return (ch=='O')||(ch=='+')||(ch=='|');
}

SegmentData Init(int id){
	//cout<<"Init:"<<id<<endl;
	SegmentData R;R.clear();
	for (int i=0;i<m;i++) R.ufs[i]=R.ufs[i+m]=i,R.bd[i]=R.bd[i+m]=(Mp[id][i]=='O');
	for (int i=1;i<m;i++) if (isclr(Mp[id][i-1])&&isclr(Mp[id][i])) R.merge(i-1,i);
	for (int i=0;i<m;i++) if ((R.find(i)==i)&&(R.bd[i])) ++R.cnt;
	//for (int i=0;i<m;i++) cout<<R.bd[i]<<" ";cout<<endl;
	//for (int i=0;i<m;i++) cout<<R.ufs[i]<<" ";cout<<endl;
	return R;
}

int Find(int u){
	return (UFS[u]!=u)?(UFS[u]=Find(UFS[u])):UFS[u];
}

void UFSMerge(int u,int v){
	int fu=Find(u),fv=Find(v);
	if (fu!=fv){
		UFS[fv]=fu;BD[fu]|=BD[fv];
	}
	return;
}

SegmentData Merge(SegmentData A,SegmentData B,int mid){
	//cout<<"Merge:"<<mid<<endl;
	//for (int i=0;i<m+m;i++) cout<<A.ufs[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m;i++) cout<<A.bd[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m;i++) cout<<B.ufs[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m;i++) cout<<B.bd[i]<<" ";cout<<endl;
	SegmentData R;R.clear();
	for (int i=0;i<m+m;i++){
		UFS[i]=A.ufs[i];UFS[i+m+m]=B.ufs[i]+m+m;
		BD[i]=A.bd[i];BD[i+m+m]=B.bd[i];
	}
	//cout<<"Copy"<<endl;
	//cout<<"Before"<<endl;
	//for (int i=0;i<m+m+m+m;i++) cout<<UFS[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m+m+m;i++) cout<<BD[i]<<" ";cout<<endl;
	R.cnt=A.cnt+B.cnt;
	for (int i=0;i<m;i++){
		//cout<<Mp[mid][i]<<" "<<Mp[mid+1][i]<<endl;
		if (iscud(Mp[mid][i])&&iscud(Mp[mid+1][i])){
			//cout<<i+m<<" "<<i+m+m<<" "<<Find(i+m)<<" "<<Find(i+m+m)<<endl;
			if (Find(i+m)!=Find(i+m+m)){
				//cout<<BD[Find(i+m)]<<" "<<BD[Find(i+m+m)]<<endl;
				if (BD[Find(i+m)]&&BD[Find(i+m+m)]) --R.cnt;
				UFSMerge(i+m,i+m+m);
			}
		}
	}
	//cout<<"After"<<endl;
	//for (int i=0;i<m+m+m+m;i++) cout<<UFS[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m+m+m;i++) cout<<BD[i]<<" ";cout<<endl;
	
	for (int i=0;i<m+m+m+m;i++) use[i]=-1,BBD[i]=0;
	for (int i=0;i<m;i++){
		if (use[Find(i)]==-1) use[Find(i)]=i;
		if (use[Find(i+m+m+m)]==-1) use[Find(i+m+m+m)]=i+m;
	}
	for (int i=0;i<m+m+m+m;i++) BBD[use[Find(i)]]|=BD[i];
	for (int i=0;i<m;i++){
		R.ufs[i]=use[Find(i)];R.bd[i]=BBD[R.ufs[i]];
		R.ufs[i+m]=use[Find(i+m+m+m)];R.bd[i+m]=BBD[R.ufs[i+m]];
	}
	//cout<<"After:"<<endl;
	//for (int i=0;i<m+m;i++) cout<<R.ufs[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m;i++) cout<<R.bd[i]<<" ";cout<<endl;
	return R;
}

void Build(int now,int l,int r){
	//cout<<"Build:"<<now<<" "<<l<<" "<<r<<endl;
	if (l==r){
		S[now]=Init(l);return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	//cout<<"Merge ["<<l<<","<<r<<"] "<<mid<<endl;
	S[now]=Merge(S[lson],S[rson],mid);
	return;
}

void Modify(int now,int l,int r,int pos){
	if (l==r){
		S[now]=Init(l);return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos);
	else Modify(rson,mid+1,r,pos);
	//cout<<"Modify merge:["<<l<<" "<<r<<"]"<<endl;
	S[now]=Merge(S[lson],S[rson],mid);
	return;
}

SegmentData Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Merge(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr),mid);
}

void Outp(int now,int l,int r){
	//cout<<"["<<l<<","<<r<<"] "<<S[now].cnt<<endl;
	//for (int i=0;i<m+m;i++) cout<<S[now].ufs[i]<<" ";cout<<endl;
	//for (int i=0;i<m+m;i++) cout<<S[now].bd[i]<<" ";cout<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}
