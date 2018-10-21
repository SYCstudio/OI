#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxR=55;
const int inf=2147483647;

class Function
{
public:
	ld a,b;
};

int n,T,Ring[maxR];
ld P;

Function dfs(int lst,int sum);
Function operator + (Function A,Function B);

int main(){
	while (scanf("%LF%d%d",&P,&T,&n)!=EOF){
		for (int i=1;i<=n;i++) scanf("%d",&Ring[i]);
		sort(&Ring[1],&Ring[n+1]);reverse(&Ring[1],&Ring[n+1]);
		printf("%.3LF\n",dfs(1,0).b);
	}

	return 0;
}

Function dfs(int lst,int sum){
	if (sum>T) return ((Function){0,0});
	ld a=0,b=0,c=(ld)(1.0-((sum==0)?(0):(P)))/(ld)(n-lst+1);
	for (int i=lst;i<=n;i++)
	{
		Function rt=dfs(i,sum+Ring[i]);
		a+=rt.a;b+=rt.b;
	}
	//cout<<"lst:"<<lst<<" sum:"<<sum<<" : "<<a<<" "<<b<<" "<<c<<" "<<c*a<<endl;
	return ((Function){((sum==0)?(0):(P))/(1.0-c*a),(c*b+1)/(1.0-c*a)});
}

Function operator + (Function A,Function B){
	return ((Function){A.a+B.a,A.b+B.b});
}
