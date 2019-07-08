#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=101000;
const int maxNum=1010000;
int n;
class BIT
{
public:
	int B[maxN+maxN],sum;
	void Insert(int x)
	{
		//cout<<"Insert:"<<x<<endl;
		++sum;
		x+=maxN;
		while (x<maxN+maxN) {
			++B[x];
			x+=(x)&(-x);
		}
		return;
	}
	int Sum(int x)
	{
		int ret=0;
		x+=maxN;
		while (x) {
			ret+=B[x];
			x-=(x)&(-x);
		}
		return ret;
	}
	int Morethan(int x)
	{
		return sum-Sum(x);
	}
};
int C[maxN][3],Seq[maxNum];
char Input[maxN];
BIT B[3][3];

int main()
{
	scanf("%d",&n);
	scanf("%s",Input+1);
	reverse(&Input[1],&Input[n+1]);
	for (int i=1; i<=n; i++) {
		//cerr<<"running on :"<<i<<endl;
		int c=Input[i]-'0';
		C[i][0]=C[i-1][0];
		C[i][1]=C[i-1][1];
		C[i][2]=C[i-1][2];
		++C[i][c];
		if (2*C[i-1][0]<=i-1&&2*C[i-1][1]<=i-1&&2*C[i-1][2]<=i-1&&(i&1)) {
			B[c][0].Insert(i-2*C[i][0]);
			B[c][1].Insert(i-2*C[i][1]);
			B[c][2].Insert(i-2*C[i][2]);
		}
		if (C[i][0]*2>i||C[i][1]*2>i||C[i][2]*2>i) {
			if (C[i][1]*2>i) ++Seq[0],--Seq[C[i][1]-C[i][0]-C[i][2]];//,cerr<<"Case2-1:"<<endl;
			else if (C[i][2]*2>i) Seq[0]+=2,Seq[C[i][2]-C[i][0]-C[i][1]]-=2;//,cerr<<"Case2-2"<<endl;
		} else if (i&1) {
			/*
			int mn=2;
			for (int j=1;j<=i;j+=2){
			    if (C[j-1][0]*2<=j-1&&C[j-1][1]*2<=j-1&&C[j-1][2]*2<=j-1)
			        if (C[i][0]-C[j][0]<=(i-j)/2&&C[i][1]-C[j][1]<=(i-j)/2&&C[i][2]-C[j][2]<=(i-j)/2)
			            mn=min(mn,Input[j]-'0');
			}
			Seq[0]+=mn;Seq[1]-=mn;
			//*/

			for (int b=0; b<=2; b++)
				if (B[b][0].Morethan(i-2*C[i][0])+B[b][1].Morethan(i-2*C[i][1])+B[b][2].Morethan(i-2*C[i][2])<B[b][0].sum) {
					//cerr<<"Case3-"<<b<<endl;
					Seq[0]+=b;
					Seq[1]-=b;
					break;
				}
			//*/
		}
	}
	for (int i=1; i<maxNum; i++) Seq[i]+=Seq[i-1];
	for (int i=0; i+1<maxNum; i++) Seq[i+1]+=Seq[i]/10,Seq[i]%=10;
	int up=maxNum-1;
	while (up&&!Seq[up]) --up;
	for (int i=up; i>=0; i--) printf("%d",Seq[i]);
	printf("\n");
	return 0;
}