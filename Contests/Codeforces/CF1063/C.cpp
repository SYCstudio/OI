#include<bits/stdc++.h>
using namespace std;

int n;
char Input[10];

int main(){
	cin>>n;int nn=max(n>>1,1);
	int xl=1,xr=1000000000;
	int yl=1,yr=1000000000;
	char bcolor;
	cout<<0<<" "<<0<<endl;
	cin>>Input;
	bcolor=Input[0];
	for (int i=2;i<=nn;i++){
		int mid=(xl+xr)>>1;
		cout<<mid<<" "<<0<<endl;
		cin>>Input;
		if (Input[0]==bcolor) xl=mid+1;
		else xr=mid-1;
	}
	for (int i=nn+1;i<=n;i++){
		int mid=(yl+yr)>>1;
		cout<<0<<" "<<mid<<endl;
		cin>>Input;
		if (Input[0]==bcolor) yl=mid+1;
		else yr=mid-1;
	}
	cout<<xl<<" "<<0<<" "<<0<<" "<<yl<<endl;
	return 0;
}
