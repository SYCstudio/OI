#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=13;
const int Mod=1e9+7;
const int inf=2147483647;

class ConversionMachine
{
public:
	ll Ans[maxN*maxN][maxN*maxN],Ret[maxN*maxN][maxN*maxN];
	ll Bp[maxN*maxN][maxN*maxN];
	int idcnt,Id[maxN*maxN][maxN*maxN];
	
	void Mul1(){
		for (int i=0;i<=idcnt;i++) Bp[0][i]=Ans[0][i],Ans[0][i]=0;
		for (int i=0;i<=0;i++)
			for (int j=0;j<=idcnt;j++)
				for (int k=0;k<=idcnt;k++)
					Ans[i][j]=(Bp[i][k]*Ret[k][j]%Mod+Ans[i][j])%Mod;
		return;
	}
	
	void Mul2(){
		for (int i=0;i<=idcnt;i++) for (int j=0;j<=idcnt;j++) Bp[i][j]=Ret[i][j],Ret[i][j]=0;
		for (int i=0;i<=idcnt;i++)
			for (int j=0;j<=idcnt;j++)
				for (int k=0;k<=idcnt;k++)
					Ret[i][j]=(Bp[i][k]*Bp[k][j]%Mod+Ret[i][j])%Mod;
		return;
	}
	
	int countAll(string word1,string word2,vector<int> costs,int maxCost){
		mem(Ans,0);mem(Ret,0);
		int len=word1.size();
		int Change[3]={0};//记录开始时要变化的次数
		ll Cost=0;//记录初始需要的花费
		//cout<<word1<<endl<<word2<<endl;
		for (int i=0;i<len;i++)
		{
			if (word1[i]=='a')
			{
				if (word2[i]=='a') Change[0]++;
				else if (word2[i]=='b') Change[1]++,Cost+=costs[0];
				else Change[2]++,Cost+=costs[0]+costs[1];
			}
			else if (word1[i]=='b')
			{
				if (word2[i]=='b') Change[0]++;
				else if (word2[i]=='c') Change[1]++,Cost+=costs[1];
				else Change[2]++,Cost+=costs[1]+costs[2];
			}
			else
			{
				if (word2[i]=='c') Change[0]++;
				else if (word2[i]=='a') Change[1]++,Cost+=costs[2];
				else Change[2]++,Cost+=costs[2]+costs[0];
			}
		}
		if (maxCost<Cost) return 0;
		int Step=Change[1]+Change[2]*2+(maxCost-Cost)/(costs[0]+costs[1]+costs[2])*3+1;
		//cout<<Cost<<" "<<Step<<endl;
		idcnt=-1;
		for (int i=0;i<=len;i++) for (int j=0;j+i<=len;j++) Id[i][j]=++idcnt;

		idcnt++;
		for (int i=0;i<=len;i++)
			for (int j=0;j+i<=len;j++)
			{
				if (i!=0) Ret[Id[i][j]][Id[i-1][j]]+=i;
				if (j!=0) Ret[Id[i][j]][Id[i+1][j-1]]+=j;
				if (len-i-j!=0) Ret[Id[i][j]][Id[i][j+1]]+=(len-i-j);
			}

		Ret[idcnt][idcnt]=1;
		Ret[Id[0][0]][idcnt]=1;
		Ans[0][Id[Change[1]][Change[2]]]=1;
		
		while (Step)
		{
			if (Step&1) Mul1();
			Mul2();
			Step=Step>>1;
		}
		return Ans[0][idcnt];
	}
}Do;

string in1="aa";
string in2="cc";
int CC[]={1,10,100};
int W=1787;

int main()
{
	cout<<Do.countAll(in1,in2,CC,W)<<endl;
	return 0;
}
