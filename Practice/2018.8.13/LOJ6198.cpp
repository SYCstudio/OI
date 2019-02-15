#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxBit=18;
const int inf=2147483647;

class Trie
{
public:
	int cnt,ch[2];
};

int n;
char str[maxN];
int Val[maxN],Log[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN];
int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN],MinId[maxBit][maxN];
int nodecnt=0,root[maxN];
Trie T[maxN*100];
int Ans=0;

void GetSA();
void Insert(int &rt,int key);
int Query(int l,int r,int key);
void Solve(int l,int r);
int GetMin(int l,int r);

int main(){
	for (int i=1;i<maxN;i++) Log[i]=log2(i);
	scanf("%d",&n);
	scanf("%s",str+1);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);

	GetSA();

	for (int i=1;i<=n;i++) Insert(root[i]=root[i-1],Val[SA[i]]);

	Solve(1,n);

	printf("%d\n",Ans);

	return 0;
}

void GetSA(){
	for (int i=1;i<=n;i++) CntA[str[i]-'a']++;
	for (int i=1;i<=26;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[str[i]-'a']--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++){
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}

	for (int i=1;Rank[SA[n]]!=n;i<<=1){
		mem(CntA,0);mem(CntB,0);
		for (int j=1;j<=n;j++){
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=((j+i<=n)?(Rank[j+i]):(0))]++;
		}
		for (int j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];
		for (int j=n;j>=1;j--) SSA[CntB[B[j]]--]=j;
		for (int j=n;j>=1;j--) SA[CntA[A[SSA[j]]]--]=SSA[j];
		Rank[SA[1]]=1;
		for (int j=2;j<=n;j++){
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}
	}

	for (int i=1,j=0;i<=n;i++){
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[0][Rank[i]]=j;MinId[0][i]=i;
		if (j) j--;
	}

	for (int i=1;i<maxBit;i++)
		for (int j=1;j+(1<<(i-1))<=n;j++){
			if (Height[i-1][j]<Height[i-1][j+(1<<(i-1))]) MinId[i][j]=MinId[i-1][j];
			else MinId[i][j]=MinId[i-1][j+(1<<(i-1))];
			Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))]);
		}

	/*
	for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Height[0][i]<<" ";cout<<endl;
	//*/
	
	return;
}

void Insert(int &rt,int key){
	T[++nodecnt]=T[rt];rt=nodecnt;
	T[rt].cnt++;
	for (int i=maxBit-1,now=rt;i>=0;i--){
		int c=(key&(1<<i))!=0;
		T[++nodecnt]=T[T[now].ch[c]];
		T[now].ch[c]=nodecnt;
		now=nodecnt;T[nodecnt].cnt++;
	}
	return;
}

int Query(int l,int r,int key){
	int r1=root[l-1],r2=root[r];
	int ret=0;
	for (int i=maxBit-1;i>=0;i--){
		int c=(key&(1<<i))!=0;
		if (T[T[r2].ch[c^1]].cnt-T[T[r1].ch[c^1]].cnt){
			ret|=(1<<i);
			r1=T[r1].ch[c^1];r2=T[r2].ch[c^1];
		}
		else r1=T[r1].ch[c],r2=T[r2].ch[c];
	}
	return ret;
}

void Solve(int l,int r){
	if (l==r) return;
	int id=GetMin(l+1,r);
	//cout<<"Solve: ("<<l<<","<<r<<") "<<id<<" "<<Height[0][id]<<endl;
	//cout<<id<<endl;
	int lcp=Height[0][id];
	if (id-l<=r-id+1) for (int i=l;i<id;i++) Ans=max(Ans,lcp+Query(id,r,Val[SA[i]]));
	else for (int i=id;i<=r;i++) Ans=max(Ans,lcp+Query(l,id-1,Val[SA[i]]));

	//cout<<Ans<<endl;

	Solve(l,id-1);Solve(id,r);
	return;
}

int GetMin(int l,int r){
	int lg=Log[r-l+1];
	//cout<<"Q:"<<l<<" "<<r<<" "<<lg<<" "<<Height[lg][l]<<" "<<Height[lg][r-(1<<lg)+1]<<endl;
	if (Height[lg][l]<Height[lg][r-(1<<lg)+1]) return MinId[lg][l];
	else return MinId[lg][r-(1<<lg)+1];
}
