#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) (x)&(-x)

const int maxN=101000;
const int inf=2147483647;

class Question
{
public:
	int n,m,a,id;
};

class HSum
{
public:
	int d,h;
};

int Q;
bool notprime[maxN];
int pricnt,Prime[maxN],Mu[maxN],H[maxN],Low[maxN];
Question Qs[maxN];
HSum S[maxN];
int BIT[maxN],Outp[maxN];

void Init();
bool cmp1(Question A,Question B);
bool cmp2(HSum A,HSum B);
void Add(int pos,int key);
int Sum(int pos);
int Query(int l,int r);

int main()
{
	Init();
	scanf("%d",&Q);
	for (int i=1;i<=Q;i++) scanf("%d%d%d",&Qs[i].n,&Qs[i].m,&Qs[i].a),Qs[i].id=i;

	sort(&Qs[1],&Qs[Q+1],cmp1);

	int hcnt=1;
	for (int i=1;i<=Q;i++)
	{
		while ((hcnt<maxN)&&(S[hcnt].h<=Qs[i].a))
		{
			for (int j=S[hcnt].d;j<maxN;j+=S[hcnt].d)
				Add(j,Mu[j/S[hcnt].d]*S[hcnt].h);
			hcnt++;
		}
		int Ans=0;if (Qs[i].n>Qs[i].m) swap(Qs[i].n,Qs[i].m);
		
		for (int j=1,lastj;j<=Qs[i].n;j=lastj+1)
		{
			lastj=min(Qs[i].n/(Qs[i].n/j),Qs[i].m/(Qs[i].m/j));
			Ans+=(int)(Qs[i].n/j)*(int)(Qs[i].m/j)*Query(j,lastj);
		}
		if (Ans<0) Ans=Ans+inf+1;
		Outp[Qs[i].id]=Ans;
	}
	for (int i=1;i<=Q;i++) printf("%d\n",Outp[i]);
	return 0;
}

void Init()
{
	notprime[1]=0;Mu[1]=1;H[1]=1;Low[1]=1;
	for (int i=2;i<maxN;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1,H[i]=i+1,Low[i]=i;
		for (int j=1;(j<=pricnt)&&(1ll*i*Prime[j]<maxN);j++)
		{
			notprime[i*Prime[j]]=1;
			//cout<<i*Prime[j]<<"="<<i<<"*"<<Prime[j]<<endl;
			if (i%Prime[j]==0)
			{
				Mu[i*Prime[j]]=0;
				if (i==Low[i]) H[i*Prime[j]]=H[i]*Prime[j]+1;
				else H[i*Prime[j]]=H[i/Low[i]]*H[Low[i]*Prime[j]];
				Low[i*Prime[j]]=Low[i]*Prime[j];
				break;
			}
			Mu[i*Prime[j]]=-Mu[i];
			H[i*Prime[j]]=H[i]*H[Prime[j]];
			Low[i*Prime[j]]=Prime[j];
		}
	}
	for (int i=1;i<maxN;i++) S[i].d=i,S[i].h=H[i];
	sort(&S[1],&S[maxN],cmp2);

	//for (int i=1;i<=20;i++) cout<<Mu[i]<<" ";cout<<endl;
	//for (int i=1;i<=20;i++) cout<<H[i]<<" ";cout<<endl;
	//for (int i=1;i<=20;i++) cout<<Low[i]<<" ";cout<<endl;

	//for (int i=1;i<=20;i++) cout<<S[i].d<<" "<<S[i].h<<endl;
	
	return;
}

bool cmp1(Question A,Question B){
	return A.a<B.a;
}

bool cmp2(HSum A,HSum B){
	return A.h<B.h;
}

void Add(int pos,int key){
	while (pos<maxN){
		BIT[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=BIT[pos];pos-=lowbit(pos);
	}
	return ret;
}

int Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
