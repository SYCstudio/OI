#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxBit=30;
const int inf=2147483647;

int n,Seq[maxN];
int lst[maxBit],L[maxN],R[maxN],Lm[maxN],Rm[maxN],St[maxN];

int main(){
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	mem(lst,0);
	for (int i=1;i<=n;i++){
		L[i]=0;
		for (int j=0;j<maxBit;j++)
			if (Seq[i]&(1<<j)) lst[j]=i;
			else L[i]=max(L[i],lst[j]);
	}
	for (int i=0;i<maxBit;i++) lst[i]=n+1;
	for (int i=n;i>=1;i--){
		R[i]=n+1;
		for (int j=0;j<maxBit;j++)
			if (Seq[i]&(1<<j)) lst[j]=i;
			else R[i]=min(R[i],lst[j]);
	}

	int top=0;St[0]=0;
	for (int i=1;i<=n;i++){
		if (Seq[i]>=Seq[St[1]]) Lm[i]=1;
		else if (Seq[i]<Seq[St[top]]) Lm[i]=i;
		else{
			int l=1,r=top,pos=0;
			do{
				int mid=(l+r)>>1;
				if (Seq[i]>=Seq[St[mid]]) pos=mid,r=mid-1;
				else l=mid+1;
			}
			while (l<=r);
			Lm[i]=St[pos];
		}
		while ((top)&&(Seq[i]>=Seq[St[top]])) top--;
		St[++top]=i;
	}
	top=0;St[0]=St[1]=0;
	for (int i=n;i>=1;i--){
		if (Seq[i]>=Seq[St[1]]) Rm[i]=n;
		else if (Seq[i]<=Seq[St[top]]) Rm[i]=i;
		else{
			int l=1,r=top,pos=0;
			do{
				int mid=(l+r)>>1;
				if (Seq[i]<Seq[St[mid]]) pos=mid,l=mid+1;
				else r=mid-1;
			}
			while (l<=r);
			Rm[i]=St[pos]-1;
		}
		while ((top)&&(Seq[i]>=Seq[St[top]])) top--;
		St[++top]=i;
	}
	
	for (int i=1;i<=n;i++) cout<<L[i]<<" "<<R[i]<<" "<<Lm[i]<<" "<<Rm[i]<<endl;

	ll Ans=0;
	for (int i=1;i<=n;i++){
		if (L[i]>=Lm[i]) Ans=Ans+1ll*(L[i]-Lm[i]+1)*(R[i]-i);
		if (R[i]<=Rm[i]) Ans=Ans+1ll*(Rm[i]-R[i]+1)*(i-L[i]);
	}
	printf("%lld\n",Ans);return 0;
}
