#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int Mod=1000000000;
const int inf=2147483647;

int n;
ll Ans=0;
int Seq[maxN],Sum[maxN];
int Tq[maxN],T[maxN],Mnq[maxN],Mn[maxN],Mxq[maxN],Mx[maxN];

void Solve(int l,int r);

int main(){
	for (int i=1;i<maxN;i++) Sum[i]=(Sum[i-1]+i)%Mod;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i])/*,S1[i]=(S1[i-1]+Seq[i])%Mod,S2[i]=(S2[i-1]+1ll*i*Seq[i]%Mod)%Mod*/;

	Solve(1,n);

	printf("%lld\n",Ans);

	/*
	Ans=0;
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++){
			int mn=Seq[i],mx=Seq[i];
			for (int k=i;k<=j;k++) mn=min(mn,Seq[k]),mx=max(mx,Seq[k]);
			Ans=Ans+(j-i+1)*mn*mx;
		}
	printf("%lld\n",Ans);
	//*/

	return 0;
}

void Solve(int l,int r){
	if (l>r) return;
	if (l==r){
		Ans=(Ans+1ll*Seq[l]*Seq[l]%Mod)%Mod;
		return;
	}
	int mid=(l+r)>>1;
	int mn=inf,mx=0;
	Tq[mid]=T[mid]=Mn[mid]=Mx[mid]=Mnq[mid]=Mxq[mid]=0;
	for (int i=mid+1;i<=r;i++){
		mn=min(mn,Seq[i]);mx=max(mx,Seq[i]);
		Tq[i]=1ll*mn*mx%Mod*i%Mod;T[i]=1ll*mx*mn%Mod;
		Mnq[i]=1ll*mn*i%Mod;Mn[i]=mn;
		Mxq[i]=1ll*mx*i%Mod;Mx[i]=mx;
	}
	
	for (int i=r-1;i>=mid+1;i--) Tq[i]=(Tq[i]+Tq[i+1])%Mod,T[i]=(T[i]+T[i+1])%Mod;
	for (int i=mid+1;i<=r;i++) Mnq[i]=(Mnq[i]+Mnq[i-1])%Mod,Mn[i]=(Mn[i]+Mn[i-1])%Mod,Mxq[i]=(Mxq[i-1]+Mxq[i])%Mod,Mx[i]=(Mx[i]+Mx[i-1])%Mod;

	//cout<<"Tq:";for (int i=mid+1;i<=r;i++) cout<<Tq[i]<<" ";cout<<endl;
	//cout<<"T:";for (int i=mid+1;i<=r;i++) cout<<T[i]<<" ";cout<<endl;
	
	mn=inf;mx=0;
	int mxr=mid,mnr=mid;
	int lastans=Ans;
	for (int p=mid;p>=l;p--){
		mn=min(mn,Seq[p]);mx=max(mx,Seq[p]);
		while ((mxr<r)&&(Seq[mxr+1]<=mx)) mxr++;
		while ((mnr<r)&&(Seq[mnr+1]>=mn)) mnr++;
		int rps=min(mxr,mnr),rmp=max(mxr,mnr);
		//cout<<"p:"<<p<<" mxr:"<<mxr<<" mnr:"<<mnr<<endl;
		//cout<<"PartA:"<<1ll*mn*mx%Mod*(Sum[rps-p+1]-Sum[mid-p+1]+Mod)%Mod<<endl;
		Ans=(Ans+1ll*mn*mx%Mod*(Sum[rps-p+1]-Sum[mid-p+1]+Mod)%Mod)%Mod;
		//cout<<"PartB:"<<Tq[rmp+1]-T[rmp+1]*(p-1)<<endl;
		if (rmp<r) Ans=((Ans+Tq[rmp+1])%Mod-1ll*T[rmp+1]*(p-1)%Mod+Mod)%Mod;
		if (mxr!=mnr){
			if (rps==mnr){
				//cout<<"C1:"<<mx<<" "<<Mnq[mxr]-Mnq[rps]<<" "<<Mn[mxr]-Mn[rps]<<endl;
				Ans=(Ans+1ll*mx*(Mnq[mxr]-Mnq[rps]+Mod-1ll*(Mn[mxr]-Mn[rps])*(p-1)%Mod+Mod)%Mod)%Mod;
			}
			else{
				//cout<<"C2:"<<mn<<" "<<Mxq[mnr]-Mxq[rps]<<" "<<Mx[mnr]-Mx[rps]<<" "<<mnr<<" "<<rps<<endl;
				Ans=(Ans+1ll*mn*(Mxq[mnr]-Mxq[rps]+Mod-1ll*(Mx[mnr]-Mx[rps])*(p-1)%Mod+Mod)%Mod)%Mod;
			}
		}
		//cout<<"this ans:"<<Ans-lastans<<endl;
	}

	//cout<<"["<<l<<","<<r<<"] lastans:"<<Ans-lastans<<" "<<mid<<endl<<endl;

	Solve(l,mid);Solve(mid+1,r);return;
}
/*
4
2 4 1 4
//*/
