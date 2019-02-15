#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN=1010000;
const int inf=2147483647;

int A,B,c1,c2,S1[maxN],S2[maxN];

bool check(ll limit);

int main(){
	cin>>A>>B;bool flag=0;
	if (A>B) swap(A,B),flag=1;
	ll n;
	for (n=0;n*(n+1)/2<=A+B;n++);n--;
	while (check(n)==0) n--;
	if (flag) swap(c1,c2),swap(S1,S2);
	cout<<c1<<endl;
	for (int i=1;i<=c1;i++) cout<<S1[i]<<" ";cout<<endl;
	cout<<c2<<endl;
	for (int i=1;i<=c2;i++) cout<<S2[i]<<" ";cout<<endl;
	return 0;
}

bool check(ll limit){
	ll a=A,b=B;c1=c2=0;
	for (int i=limit;i>=1;i--)
		if (a>=i) S1[++c1]=i,a-=i;
		else if (b>=i) S2[++c2]=i,b-=i;
		else return 0;
	return 1;
}
