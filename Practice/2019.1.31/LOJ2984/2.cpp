#include<bits/stdc++.h>
using namespace std;

int main(){
	freopen("oldcomputer2.out","w",stdout);
	cout<<"node 1"<<endl;
	cout<<"read 0 a"<<endl;
	cout<<"add a 4"<<endl;
	cout<<"jmp a"<<endl;
	int a=0,b=1;
	while (a<=1000000000){
		cout<<"write "<<a<<" 0"<<endl;
		swap(a,b);b+=a;
	}
	return 0;
}
