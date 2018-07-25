#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;

int make(int l,int r);

int main()
{
	freopen("rand","r",stdin);int seed;cin>>seed;srand(seed^time(0));fclose(stdin);
	freopen("in.in","w",stdout);
	int cas=10;
	while (cas--){
		cout<<make(1,40)<<endl;
		int len=50;
		for (int i=1;i<=len;i++) cout<<(char)(make('a','c'));cout<<endl;
	}
	cout<<0<<endl;
	fclose(stdout);
	freopen("rand","w",stdout);cout<<make(1,1000000000)<<endl;fclose(stdout);
	return 0;
}

int make(int l,int r){
	double dou=1.0*rand()/RAND_MAX;
	return min(r,(int)(dou*(r-l+1)+l));
}
