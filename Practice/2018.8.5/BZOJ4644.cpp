#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=510;
const int maxM=1010;
const int maxL=1000;
const int maxBit=10;
const int inf=2147483647;

int n,m;
int EU[maxM],EV[maxM];
bitset<maxL> Num[maxM],W[maxN],Base[maxL],Tmp;
char Input[maxN];
vector<int> S[maxM<<2];

void Modify(int now,int l,int r,int ql,int qr,int id);
void Query(int now,int l,int r);

int main(){
	int id;scanf("%d",&id);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d %s",&EU[i],&EV[i],Input+1);
		int len=strlen(Input+1);
		for (int j=1;j<=len;j++)
			if (Input[j]=='1') Num[i].set(len-j);
		Modify(1,1,m,i,m,i);
	}

	Query(1,1,m);
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

void Query(int now,int l,int r){
	for (int sz=S[now].size(),i=0;i<sz;i++){
		int id=S[now][i];
		W[EU[id]]^=Num[id];W[EV[id]]^=Num[id];
	}
	if (l==r){
		for (int i=maxL-1;i>=0;i--) Base[i].reset();
		for (int i=1;i<=n;i++){
			Tmp=W[i];
			for (int j=maxL-1;j>=0;j--)
				if (Tmp[j]){
					if (Base[j].any()==0){
						Base[j]=Tmp;break;
					}
					Tmp^=Base[j];
				}
		}
		Tmp.reset();
		for (int i=maxL-1;i>=0;i--) if ((Base[i][i])&&(Tmp[i]==0)) Tmp^=Base[i];
		int opt=0;
		for (int i=maxL-1;i>=0;i--)
			if ((opt==1)||(Tmp[i])){
				printf("%d",(int)Tmp[i]);
				opt=1;
			}
		if (opt==0) printf("0");
		printf("\n");
	}
	else{
		int mid=(l+r)>>1;
		Query(lson,l,mid);Query(rson,mid+1,r);
	}
	for (int sz=S[now].size(),i=0;i<sz;i++){
		int id=S[now][i];
		W[EU[id]]^=Num[id];W[EV[id]]^=Num[id];
	}
	return;
}
/*
0
3 6
1 2 1
1 2 1
3 3 111
1 3 101101
1 2 1011
2 3 111011
//*/
