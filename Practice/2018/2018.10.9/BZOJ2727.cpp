#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
//#define Id(x,y) ((x)*m+(y))

const int maxN=2010000;
const int Mod=1000000009;
const int inf=2147483647;

int n,m,K;
bool Map[maxN];
int Up[maxN],Down[maxN],L[maxN],R[maxN],W[maxN];

class BIT
{
public:
	int B[maxN],timcnt,Tim[maxN];
	void Add(int pos,int key){
		while (pos<=m){
			if (Tim[pos]==timcnt) B[pos]=(B[pos]+key)%Mod;
			else B[pos]=key,Tim[pos]=timcnt;
			pos+=(pos)&(-pos);
		}
		return;
	}
	int Query(int pos){
		int ret=0;
		while (pos){
			if (Tim[pos]==timcnt) ret=(ret+B[pos])%Mod;
			pos-=(pos)&(-pos);
		}
		return ret;
	}
	void clear(){
		timcnt++;return;
	}
};

BIT B1,B2,B3;

int Id(int x,int y);
int QPow(int x,int cnt);
void Modify(int pos,int key);

int main(){
	int inv2=QPow(2,Mod-2);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Map[Id(i,j)]=1;
	for (int i=1;i<=K;i++){
		int x,y;scanf("%d%d",&x,&y);Map[Id(x,y)]=0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (Map[Id(i,j)]) Up[Id(i,j)]=Up[Id(i-1,j)]+1,L[Id(i,j)]=L[Id(i,j-1)]+1;
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--)
			if (Map[Id(i,j)]) Down[Id(i,j)]=Down[Id(i+1,j)]+1,R[Id(i,j)]=R[Id(i,j+1)]+1;
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (Map[Id(i,j)])
				W[Id(i,j)]=min(L[Id(i,j)],R[Id(i,j)])-1,Up[Id(i,j)]--,Down[Id(i,j)]--;

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) cout<<Map[Id(i,j)]<<" ";cout<<endl;
	}printf("\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) printf("%3d",Up[Id(i,j)]);printf("\n");
	}printf("\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) printf("%3d",Down[Id(i,j)]);printf("\n");
	}printf("\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) printf("%3d",W[Id(i,j)]);printf("\n");
	}
	//*/
	
	ll Ans=0;
	for (int i=1;i<=m;i++){
		B1.clear();B2.clear();B3.clear();
		for (int j=1;j<=n;j++){
			int id=Id(j,i);
			if (Map[id]==0){
				B1.clear();B2.clear();B3.clear();continue;
			}
			if (W[id]>1){
				ll w=W[id]-1;
				ll c1=B1.Query(w),c2=B2.Query(w),c3=B3.Query(w);
				ll s=(((1ll*w*w+3ll*w+2)%Mod*c1-(w+w+3)%Mod*c2%Mod+c3)%Mod+Mod)%Mod;
				//cout<<"("<<j<<","<<i<<") "<<w<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<s<<endl;
				Ans=(Ans+s*Down[id]%Mod*inv2%Mod)%Mod;
			}
			Modify(1,Up[id-m]);Modify(W[id-m]+1,-Up[id-m]);
			//cout<<"B1:";for (int k=1;k<=m;k++) cout<<B1.Query(k)<<" ";cout<<endl;
			//cout<<"B2:";for (int k=1;k<=m;k++) cout<<B2.Query(k)<<" ";cout<<endl;
			//cout<<"B3:";for (int k=1;k<=m;k++) cout<<B3.Query(k)<<" ";cout<<endl;
		}
	}
	printf("%lld\n",Ans);return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Modify(int pos,int key){
	key=(key%Mod+Mod)%Mod;
	//if (key) cout<<"M:"<<pos<<" "<<key<<endl;
	B1.Add(pos,key);B2.Add(pos,1ll*key*pos%Mod);B3.Add(pos,1ll*key*pos%Mod*pos%Mod);
	return;
}

int Id(int x,int y){
	//cout<<"Id:"<<x<<" "<<y<<endl;
	if ((x<=0)||(y<=0)||(x>n)||(y>m)) return 0;
	return (x*m+y);
}
