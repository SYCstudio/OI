#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
#define pb push_back

const int maxN=202000;
const int Mod=1e9+7;

int n;
pair<int,int> D[maxN];
int St[maxN],Sm[maxN<<2],L[maxN],R[maxN];
vector<int> Vr[maxN];

void Modify(int x,int l,int r,int p,int key);
int Query(int x,int l,int r,int ql,int qr);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d%d",&D[i].sd,&D[i].ft);
	sort(&D[1],&D[n+1]);

	for (int i=1,top=0; i<=n; i++) {
		int l=1,r=top,pos=i;
		while (l<=r) {
			int mid=(l+r)>>1;
			if (D[St[mid]].sd>D[i].sd) pos=St[mid],r=mid-1;
			else l=mid+1;
		}
		L[i]=pos;
		if (top==0||D[i].sd>D[St[top]].sd) St[++top]=i;
	}

	for (int i=n,top=0; i>=1; i--) {
		int l=1,r=top,pos=i;
		while (l<=r) {
			int mid=(l+r)>>1;
			if (D[St[mid]].sd<D[i].sd) pos=St[mid],r=mid-1;
			else l=mid+1;
		}
		R[i]=pos;
		if (top==0||D[i].sd<D[St[top]].sd) St[++top]=i;
	}

	for (int i=1; i<=n; i++) Vr[L[i]].pb(R[i]);
	Modify(1,0,n,0,1);

	for (int i=1; i<=n; i++) {
		sort(Vr[i].begin(),Vr[i].end());
		for (int j=0; j<Vr[i].size(); j++) {
			int r=Vr[i][j];
			Modify(1,0,n,r,Query(1,0,n,i-1,n));
		}
	}
	//for (int i=1;i<=n;i++) cout<<L[i]<<" "<<R[i]<<endl;

	printf("%d\n",Query(1,0,n,n,n));
	return 0;
}
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int p,int key)
{
	Sm[x]=(Sm[x]+key)%Mod;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(ls,l,mid,p,key);
	else Modify(rs,mid+1,r,p,key);
	return;
}
int Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return Sm[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return (Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr))%Mod;
}
