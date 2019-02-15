#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;
const int inf=2147483647;

int n;
char Input[maxN];
int Cnt[30];

int main(){
	cin>>n;cin>>Input;
	for (int i=0;i<n;i++) Cnt[Input[i]-'a']++;
	for (int i=0;i<26;i++) while (Cnt[i]--) cout<<(char)(i+'a');
	cout<<endl;
	return 0;
}
