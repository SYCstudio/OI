#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
const int maxNum=10000100;
const int Mod=998244353;
const int sqr=sqrt(10000000);
const int maxM=7000;
const int maxB=450;

int notp[maxNum],pcnt,P[maxNum],Mx[maxNum],Id[maxNum];
pair<int,int> Sorter[maxM];
bitset<maxB> B[maxB];

void Init();
int QPow(int x,int cnt);
bitset<maxB> Get(int key);
bool Insert(bitset<maxB> R);
int main()
{
	Init();
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		int L,R;
		scanf("%d%d",&L,&R);
		if (R-L+1>=sqr*2) {
			int s=R-L+1;
			for (int i=1; P[i]<=R; i++) if ((L-1)/P[i]!=R/P[i]) --s;
			printf("%d\n",QPow(2,s));
			continue;
		}
		int sz=R-L+1;
		for (int i=1; i<=sz; i++) Sorter[i]=mp(Mx[i+L-1],i+L-1);
		for (int i=0; i<maxB; i++) B[i].reset();
		sort(&Sorter[1],&Sorter[sz+1]);
		int bsz=0,cnt=0;
		//for (int i=1;i<=sz;i++) cout<<"("<<Sorter[i].ft<<" "<<Sorter[i].sd<<") ";cout<<endl;
		for (int l=1,r; l<=sz; l=r+1) {
			r=l;
			while (r<sz&&Sorter[r+1].ft==Sorter[l].ft) ++r;
			if (Sorter[l].ft<=sqr) for (int i=l; i<=r; i++) if (bsz<maxB&&Insert(Get(Sorter[i].sd))) ++bsz,++cnt;
					else;
			else {
				++cnt;
				bitset<maxB> F=Get(Sorter[l].sd);
				for (int i=l+1; i<=r; i++) if (bsz<maxB&&Insert(F^Get(Sorter[i].sd))) ++bsz,++cnt;
			}
		}
		printf("%d\n",QPow(2,R-L+1-cnt));
	}
	return 0;
}
void Init()
{
	notp[1]=1;
	Mx[1]=1;
	for (int i=2; i<maxNum; i++) {
		if (!notp[i]) P[++pcnt]=i,Id[i]=pcnt,Mx[i]=i;
		for (int j=1; j<=pcnt&&1ll*i*P[j]<maxNum; j++) {
			notp[i*P[j]]=1;
			Mx[i*P[j]]=Mx[i];
			if (i%P[j]==0) break;
		}
	}
	//for (int i=1;i<=100;i++) cout<<Mx[i]<<" ";cout<<endl;
	return;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		cnt>>=1;
		x=1ll*x*x%Mod;
	}
	return ret;
}
bitset<maxB> Get(int key)
{
	bitset<maxB> R;
	if (Mx[key]>sqr) key/=Mx[key];
	while (key>1) R[Id[Mx[key]]-1]=R[Id[Mx[key]]-1]^1,key/=Mx[key];
	return R;
}
bool Insert(bitset<maxB> R)
{
	for (int i=0; i<maxB; i++)
		if (R[i]&&!B[i].any()) {
			B[i]=R;
			return 1;
		} else if (R[i]) R^=B[i];
	return 0;
}
