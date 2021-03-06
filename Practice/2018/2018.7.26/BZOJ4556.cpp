#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=101000;
const int maxBit=20;
const int inf=2147483647;

class SegmentData{
public:
	int key;
	int ls,rs;
};

int n,m;
int Log2[maxN];
char str[maxN];
int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN];
int root[maxN],nodecnt;
SegmentData S[maxN*50];

int Input();
void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos);
bool Check(RG int a,RG int b,RG int c,RG int d,RG int limit);
bool Query(RG int r1,RG int r2,RG int l,RG int r,RG int ql,RG int qr);

int main()
{
	for (int i=1;i<maxN;i++) Log2[i]=log2(i);
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	RG int i,j,a,b,c,d,l,r,ans,mid;
	for (i=1;i<=n;i++) CntA[str[i]-'a']++;
	for (i=1;i<=26;i++) CntA[i]+=CntA[i-1];
	for (i=n;i>=1;i--) SA[CntA[str[i]-'a']--]=i;
	Rank[SA[1]]=1;
	for (i=2;i<=n;i++){
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}

	for (i=1;Rank[SA[n]]!=n;i<<=1){
		mem(CntA,0);mem(CntB,0);
		for (int j=1;j<=n;j++){
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=(i+j<=n)?(Rank[i+j]):(0)]++;
		}
		for (j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];
		for (j=n;j>=1;j--) SSA[CntB[B[j]]--]=j;
		for (j=n;j>=1;j--) SA[CntA[A[SSA[j]]]--]=SSA[j];
		Rank[SA[1]]=1;
		for (j=2;j<=n;j++){
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}
	}

	for (i=1,j=0;i<=n;i++){
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[0][Rank[i]]=j;
		if (j) j--;
	}

	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Height[0][i]<<" ";cout<<endl;

	for (i=1;i<maxBit;i++)
		for (j=1;j+(1<<(i-1))<=n;j++)
			Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))]);

	Build(root[0],1,n);
	for (i=1;i<=n;i++){
		root[i]=root[i-1];
		Modify(root[i],1,n,SA[i]);
	}

	while (m--){
		a=Input();b=Input();c=Input();d=Input();//scanf("%d%d%d%d",&a,&b,&c,&d);
		l=1;r=min(d-c+1,b-a+1);ans=0;
		do{
			mid=(l+r)>>1;
			if (Check(a,b-mid+1,c,d,mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		while (l<=r);
		printf("%d\n",ans);
	}
	return 0;
}

int Input(){
	RG int x=0;RG char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=(x<<3)+(x<<1)+ch-48,ch=getchar();
	return x;
}

void Build(int &now,int l,int r){
	now=++nodecnt;
	if (l==r) return;
	RG int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos){
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].key++;
	if (l==r) return;
	RG int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos);
	else Modify(S[now].rs,mid+1,r,pos);
	return;
}

bool Check(RG int a,RG int b,RG int c,RG int d,RG int limit){
	//cout<<"check:"<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<limit<<endl;
	RG int up=Rank[c],down=Rank[c];
	if (Height[0][down+1]>=limit) down=min(n,down+1);
	for (RG int i=Log2[up];i>=0;i--)
		if ((up-(1<<i)>=1)&&(Height[i][up-(1<<i)+1]>=limit)) up=up-(1<<i);
	for (RG int i=Log2[n-down+1];i>=0;i--)
		if ((down+(1<<i)<=n)&&(Height[i][down+1]>=limit)) down=down+(1<<i);
	//cout<<"up:"<<up<<" down:"<<down<<endl;
	return Query(root[up-1],root[down],1,n,a,b);
}

bool Query(RG int r1,RG int r2,RG int l,RG int r,RG int ql,RG int qr){
	//cout<<"Query:"<<r1<<" "<<r2<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if (r2==0) return 0;
	if ((l==ql)&&(r==qr)) return (S[r2].key-S[r1].key)>=1;
	RG int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[r1].ls,S[r2].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[r1].rs,S[r2].rs,mid+1,r,ql,qr);
	else return (Query(S[r1].ls,S[r2].ls,l,mid,ql,mid))||(Query(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr));
}
/*
8 5
aababbaa
1 3 7 8
1 5 5 8
1 2 5 6
3 6 2 4
1 5 2 5
//*/

