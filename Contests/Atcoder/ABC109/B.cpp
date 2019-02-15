#include<bits/stdc++.h>
using namespace std;

const int maxN=100;
const int maxL=12;
const int inf=2147483647;

int n;
set<string> St;
string str;

int main(){
	cin>>n;
	cin>>str;St.insert(str);
	for (int i=2;i<=n;i++){
		char lst=str[str.size()-1];
		cin>>str;
		if ((St.count(str))||(str[0]!=lst)){
			printf("No\n");return 0;
		}
		St.insert(str);
	}
	printf("Yes\n");
	return 0;
}
