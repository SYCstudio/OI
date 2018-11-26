#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int maxH=101000;
const int inf=2147483647;

int main(){
	int sum=0;
	for (int i=1;i<=maxN;i++) for (int j=1;j<=maxH;j++) sum+=i+j;
	return 0;
}
