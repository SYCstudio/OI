#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
const int maxN=202000;
const ll INF=1e18;

int n,m;
ll X,W,T,Pos[maxN],F[maxN];
pair<ll,ll> Ref[maxN],Pag[maxN];
vector<pair<ll,ll> > Seg[maxN<<2];

bool cmpp(ll A,ll B);
bool cmpr(pair<ll,ll> A,pair<ll,ll> B);
pair<ll,ll> operator - (pair<ll,ll> A,pair<ll,ll> B);
ostream & operator << (ostream &os,pair<ll,ll> P);
double Slope(pair<ll,ll> A,pair<ll,ll> B);
void Modify(int x,int l,int r,int k,ll key);
ll Query(int x,int l,int r,int ql,int qr,ll k);

int main()
{
	//freopen("04-12.in","r",stdin);freopen("out","w",stdout);
	scanf("%lld%d%d%lld%lld",&X,&n,&m,&W,&T);
	for (int i=1; i<=n; i++) scanf("%lld",&Pos[i]);
	Pos[++n]=X;
	sort(&Pos[1],&Pos[n+1]);
	for (int i=1; i<=n; i++) Ref[i]=make_pair(Pos[i],Pos[i-1]);
	sort(&Ref[1],&Ref[n+1],cmpr);
	//for (int i=1;i<=n;i++) cout<<Ref[i].first<<" "<<Ref[i].second<<endl;
	for (int i=1; i<=m; i++) scanf("%lld%lld",&Pag[i].first,&Pag[i].second);
	sort(&Pag[1],&Pag[m+1]);
	for (int i=1; i<=m; i++) Pag[i].second+=Pag[i-1].second;
	F[0]=(X/T-(X%T==0)+(X%T!=0))*W;
	Modify(1,0,m,0,F[0]);
	for (int i=1,j=1; i<=m; i++) {
		//cerr<<"running on "<<i<<" ";
		F[i]=F[i-1]+(X/T-(X%T==0)+(Pag[i].first%T<X%T))*W;
		//cout<<X/T-(X%T==0)+(Pag[i].first%T<X%T)<<" "<<Pag[i].first%T<<" "<<X%T<<" "<<F[i]<<endl;
		while (j<=n&&(i==m||Pag[i+1].first>Ref[j].first%T)) {
			if (Pag[i].first>Ref[j].first%T) {
				++j;
				continue;
			}
			//int lower=lower_bound(&Pag[1],&Pag[m+1],make_pair(Ref[j].first-Ref[j].second>=Pag[i].first?1:(Ref[j].second-1)/T+1,-INF))-Pag-1;
			int lower=lower_bound(&Pag[1],&Pag[m+1],make_pair(Ref[i].first/T!=Ref[i].second?0:Ref[i].second%T,-INF))-Pag-1;
			//cout<<make_pair(Ref[j].first/T!=Ref[j].second/T?0:Ref[j].second,-INF)<<endl;
			//cout<<i<<" "<<j<<" lower:"<<lower<<endl;
			if (lower>i-1) {
				++j;
				continue;
			}
			F[i]=min(F[i],Query(1,0,m,lower,i-1,(Ref[j].first-1)/T*W)+Pag[i].second+(Ref[j].first-1)/T*W*i);
			/*
			ll cnt=(Ref[j].first-1)/T;
			cout<<"cnt:"<<cnt<<endl;
			for (int k=lower;k<i;k++){
			    cout<<k<<"->"<<i<<" "<<F[k]+cnt*W*(i-k)+Pag[i].second-Pag[k].second<<endl;
			    F[i]=min(F[i],F[k]+cnt*W*(i-k)+Pag[i].second-Pag[k].second);
			}
			//*/
			++j;
		}
		Modify(1,0,m,i,F[i]-Pag[i].second);
		//cerr<<"mergecnt:"<<mergecnt<<endl;
	}
	//for (int i=0;i<=m;i++) cout<<F[i]<<" ";cout<<endl;
	printf("%lld\n",F[m]);
	return 0;
}
bool cmpp(ll A,ll B)
{
	return A%T<B%T;
}
bool cmpr(pair<ll,ll> A,pair<ll,ll> B)
{
	return A.first%T<B.first%T;
}
double Slope(pair<ll,ll> A,pair<ll,ll> B)
{
	return (double)(A.second-B.second)/(double)(A.first-B.first);
}
pair<ll,ll> operator - (pair<ll,ll> A,pair<ll,ll> B)
{
	return make_pair(A.first-B.first,A.second-B.second);
}
ostream & operator << (ostream &os,pair<ll,ll> P)
{
	os<<"("<<P.first<<","<<P.second<<")";
	return os;
}
void Modify(int x,int l,int r,int k,ll key)
{
	if (l==r) {
		Seg[x].push_back(make_pair(k,key));
		return;
	}
	int mid=(l+r)>>1;
	if (k<=mid) Modify(ls,l,mid,k,key);
	else Modify(rs,mid+1,r,k,key);
	int top=Seg[x].size()-1;
	while (top>=1&&Slope(make_pair(k,key),Seg[x][top-1])<=Slope(Seg[x][top],Seg[x][top-1])) --top,Seg[x].pop_back();
	Seg[x].push_back(make_pair(k,key));
	return;
}
ll Query(int x,int l,int r,int ql,int qr,ll k)
{
	//cout<<"Query:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<k<<endl;
	if (l==ql&&r==qr) {
		int l=0,r=Seg[x].size()-1;
		//for (int i=l;i<=r;i++) cout<<Seg[x][i]<<" ";cout<<endl;
		while (l<r) {
			int mid=(l+r)>>1;
			if (k>Slope(Seg[x][mid],Seg[x][mid+1])) l=mid+1;
			else r=mid;
		}
		//cout<<"chose:"<<l<<endl;
		//ll mn=INF;for (int i=0;i<Seg[x].size();i++) mn=min(mn,Seg[x][i].second-k*Seg[x][i].first);
		//return mn;
		return Seg[x][l].second-k*Seg[x][l].first;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr,k);
	return min(Query(ls,l,mid,ql,mid,k),Query(rs,mid+1,r,mid+1,qr,k));
}