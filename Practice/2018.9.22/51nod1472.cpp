#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300030;
const int maxK=1010000;
const int maxBit=19;
const int inf=2147483647;

class Question{
public:
	int l,r;
};

int n,K;
int Seq[maxN],Mx[maxBit][maxN],Sum[maxN],Log[maxN];
ll Ans=0,Bit[maxK],qcnt;
vector<Question> Qs[maxK];
int Order[maxN];

int GetMx(int l,int r);
void Solve(int l,int r);
bool cmp(int a,int b);
void Add(int pos,int key);
int Pre(int pos);

int main(){
	for (int i=1;i<maxN;i++) Log[i]=log2(i);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++){
		scanf("%d",&Seq[i]);Mx[0][i]=i;
		Sum[i]=(Sum[i-1]+Seq[i])%K;
	}

	for (int i=1;i<maxBit;i++)
		for (int j=1;j+(1<<(i-1))<=n;j++)
			if (Seq[Mx[i-1][j]]>=Seq[Mx[i-1][j+(1<<(i-1))]]) Mx[i][j]=Mx[i-1][j];
			else Mx[i][j]=Mx[i-1][j+(1<<(i-1))];

	/*
	for (int i=0;i<maxBit;i++){
		for (int j=1;j+(1<<i)-1<=n;j++)
			cout<<Seq[i][j]<<" ";cout<<endl;
	}
	for (int i=0;i<maxBit;i++){
		for (int j=1;j+(1<<i)-1<=n;j++)
			cout<<Mx[i][j]<<" ";cout<<endl;
	}
	//*/

	Solve(1,n);

	/*
	for (int i=0;i<K;i++){
		cout<<i<<":"<<endl;
		for (int sz=Qs[i].size(),k=0;k<sz;k++) cout<<"["<<Qs[i][k].l<<","<<Qs[i][k].r<<"]"<<endl;
	}
    //*/

	for (int i=0;i<=n;i++) Order[i]=i;
	sort(&Order[0],&Order[n+1],cmp);

	//for (int i=1;i<=n;i++) cout<<Order[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Sum[Order[i]]<<" ";cout<<endl;

	for (int i=0,j=-1;i<K;i++){
		int lastj=j;
		while ((j<n)&&(Sum[Order[j+1]]<=i)) Add(Order[++j],1);
		//cout<<i<<" "<<j<<endl;
		for (int sz=Qs[i].size(),k=0;k<sz;k++)
			Ans=Ans+Pre(Qs[i][k].r)-Pre(Qs[i][k].l-1)/*,cout<<"["<<Qs[i][k].l<<","<<Qs[i][k].r<<"] "<<Pre(Qs[i][k].r)-Pre(Qs[i][k].l-1)<<endl*/;
		for (int k=lastj+1;k<=j;k++) Add(Order[k],-1);
	}

	printf("%lld\n",Ans);

	/*
	Ans=0;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			int sum=0,mx=0;
			for (int k=i;k<=j;k++) sum=sum+Seq[0][k],mx=max(mx,Seq[0][k]);
			if (((sum%K-mx%K)+K)%K==0) Ans++;
		}
	printf("%lld\n",Ans);
	//*/
	
	return 0;
}

int GetMx(int l,int r){
	int lg=Log[r-l+1];
	if (Seq[Mx[lg][l]]>=Seq[Mx[lg][r-(1<<lg)+1]]) return Mx[lg][l];
	else return Mx[lg][r-(1<<lg)+1];
}

void Solve(int l,int r){
	//cout<<"Solve:"<<l<<" "<<r<<endl;
	if (l==r) return;
	if (l>r) return;

	int mxp=GetMx(l,r),mx=Seq[mxp];
	//cout<<"mx:["<<mxp<<"] "<<mx<<endl;
	if (mxp-l+1<=r-mxp+1){
		for (int i=mxp;i>=l;i--)
			Qs[(mx+Sum[i-1])%K].push_back((Question){mxp+1,r});
		//Ans=Ans+Query(root[mxp],root[r],0,K-1,(mx+Sum[i-1])%K);
		Solve(l,mxp);Solve(mxp+1,r);
	}
	else{
		//cout<<"Case2:"<<endl;
		if (mxp-2>=0) 
			for (int i=mxp;i<=r;i++){
				//if (l-1<=0) cout<<"Q:"<<((Sum[i]-mx)%K+K)%K<<" "<<0<<" "<<mxp-2<<endl;
				//else cout<<"Q:"<<((Sum[i]-mx)%K+K)%K<<" "<<l-1<<" "<<mxp-2<<endl;
				if (l-1<=0) Qs[((Sum[i]-mx)%K+K)%K].push_back((Question){0,mxp-2});
				//Ans=Ans+Query(root[mxp-2],0,K-1,((Sum[i]-mx)%K+K)%K);
				else Qs[((Sum[i]-mx)%K+K)%K].push_back((Question){l-1,mxp-2});
				//Ans=Ans+Query(root[max(l-2,0)],root[mxp-2],0,K-1,((Sum[i]-mx)%K+K)%K);
			}
		//cout<<endl;
		Solve(l,mxp-1);Solve(mxp,r);
	}
	return;
}

bool cmp(int a,int b){
	return Sum[a]<Sum[b];
}

void Add(int pos,int key){
	pos++;
	while (pos<=n+1){
		Bit[pos]+=key;pos+=(pos)&(-pos);
	}
	return;
}

int Pre(int pos){
	int ret=0;
	pos++;
	while (pos){
		ret+=Bit[pos];pos-=((pos)&(-pos));
	}
	return ret;
}
