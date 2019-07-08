#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

const int maxsize=500;
const int inf=2147483647;

int main()
{
	int n;
	int Ans=0;
	int Y;
	string S;
	cin>>n>>S;
	S=S+S;
	for (int i=0; i<S.size(); i++) {
		int cnt=0;
		char c=S[i];
		int j=i;
		while ( ((S[j-1]==c)||(S[j-1]=='w')) &&(j>0)) {
			j--;
			cnt++;
		}
		c=S[i+1];
		j=i+1;
		while ( ((S[j+1]==c)||(S[j+1]=='w')) &&(j<S.size())) {
			j++;
			cnt++;
		}
		cnt=cnt+2;
		if (cnt>Ans) {
			Ans=cnt;
			Y=i;
		}
		if (Ans>=n) {
			Ans=n;
			break;
		}
	}
	cout<<Ans<<endl;
	//cout<<Y<<endl;
	return 0;
}
