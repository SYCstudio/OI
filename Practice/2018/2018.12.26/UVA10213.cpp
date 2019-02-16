#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

__int128 Input();
void Print(__int128 x);

int main(){
	int Case=Input();
	while (Case--){
		__int128 n=Input();
		Print(n*(n-1)*(n-2)*(n-3)/24+n*(n-1)/2+1);
		putchar('\n');
	}
	return 0;
}

__int128 Input(){
	char ch=getchar();__int128 x=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x;
}

void Print(__int128 x){
	if (x==0) return;
	Print(x/10);
	putchar('0'+x%10);return;
}
