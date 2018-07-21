#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20;
const int inf=2147483647;

int make(int l,int r);

int main()
{
	int seed;freopen("rand","r",stdin);cin>>seed;srand(seed);fclose(stdin);
	freopen("in.in","w",stdout);
	int n=7;
	cout<<n<<endl;
	for (int i=1;i<=n;i++) cout<<(char)(make('A','C'));cout<<endl;
	for (int i=1;i<=n;i++) cout<<(char)(make('A','C'));cout<<endl;
	fclose(stdout);

	freopen("rand","w",stdout);cout<<make(1,10000000)<<endl;fclose(stdout);
	return 0;
}

int make(int l,int r){
	double dou=1.0*rand()/RAND_MAX;
	return min(r,(int)(dou*(r-l+1)+l));
}
