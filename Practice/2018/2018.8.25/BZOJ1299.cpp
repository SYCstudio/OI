#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxBit=32;

int n;
int Base[maxBit];

bool Insert(int key);

int main(){
	int T=10;
	while (T--){
		mem(Base,0);
		int n;scanf("%d",&n);
		bool flag=0;
		for (int i=1;i<=n;i++)
		{
			int key;scanf("%d",&key);
			if (Insert(key)==0){
				flag=1;
			}
		}
		if (flag==0) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}

bool Insert(int key){
	for (int i=maxBit-1;i>=0;i--)
		if (key&(1<<i)){
			if (Base[i]==0){
				Base[i]=key;return 1;
			}
			key^=Base[i];
		}
	return 0;
}
/*
3
11 10 15 
5
13 6 7 15 3 
2
15 12 
3
9 7 4 
2
15 12 
4
15 12 11 15 
3
2 14 15 
3
3 16 6 
4
1 4 10 3 
5
8 7 7 5 12
//*/
