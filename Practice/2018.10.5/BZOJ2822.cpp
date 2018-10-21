#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int B=1000;
const int inf=2147483647;

class Bigint
{
public:
	int num[6000],high;
	int bp[6000];
	
	void MainTain(){
		for (int i=1;i<high;i++)
			num[i+1]+=num[i]/B,num[i]%=B;
		while (num[high]>=B) num[high+1]+=num[high]/B,num[high]%=B,high++;
		return;
	}
	
	Bigint(int a){
		mem(num,0);mem(bp,0);
		num[high=1]=a;MainTain();return;
	}

	Bigint operator * (int a){
		for (int i=1;i<=high;i++) num[i]=num[i]*a;
		MainTain();return *this;
	}

	Bigint operator / (int a){
		int bcnt=0,ret=0;
		for (int i=high;i>=1;i--){
			ret=ret*B+num[i];
			bp[i]=ret/a;ret%=a;
		}
		for (int i=1;i<=high;i++) num[i]=bp[i];
		while (num[high]==0) high--;
		return *this;
	}
};

int n;
Bigint Ans(1);
ostream & operator << (ostream &os,Bigint B);

int main(){
	scanf("%d",&n);
	if (n<=2){
		printf("1\n");return 0;
	}

	for (int i=2;i<=n;i++) Ans=Ans*(4*i-2)/(i+1);
	printf("%d",Ans.num[Ans.high]);
	for (int i=Ans.high-1;i>=1;i--) printf("%03d",Ans.num[i]);
	return 0;
}

ostream & operator << (ostream &os,Bigint B){
	os<<B.num[B.high];
	for (int i=B.high-1;i>=1;i--) os<<setfill('0')<<setw(3)<<B.num[i];
	return os;
}
