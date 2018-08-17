#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int inf=2147483647;

int n;
char Outp[maxN*2];
char Input[10];

int main(){
	scanf("%d",&n);
	bool flag=1;
	int x=1,y=1;
	int scnt=0;
	while ((x!=n)||(y!=n)){
		bool cas=0;
		if (x!=n){
			printf("? %d %d %d %d\n",x+1,y,n,n);fflush(stdout);
			scanf("%s",Input);
			if (Input[0]=='Y'){
				cas=1;x++;Outp[++scnt]='D';
			}
		}
		if ((y!=n)&&(cas==0)){
			printf("? %d %d %d %d\n",x,y+1,n,n);fflush(stdout);
			scanf("%s",Input);
			if (Input[0]=='Y'){
				cas=1;y++;Outp[++scnt]='R';
			}
		}
		//cout<<n-x+n-y<<flush<<endl;
		if ((n-x+n-y<=n-1)) break;
	}
	int x1=x,y1=y,stop=scnt;
	x=n;y=n;
	while ((x!=1)&&(y!=1)){
		if ((x==x1)&&(y==y1)) break;
		bool cas=0;
		if (y!=1){
			printf("? %d %d %d %d\n",1,1,x,y-1);fflush(stdout);
			scanf("%s",Input);
			if (Input[0]=='Y'){
				cas=1;y--;Outp[++scnt]='R';
			}
		}
		if ((x!=1)&&(cas==0)){
			printf("? %d %d %d %d\n",1,1,x-1,y);fflush(stdout);
			scanf("%s",Input);
			if (Input[0]=='Y'){
				cas=1;x--;Outp[++scnt]='D';
			}
		}
	}
	printf("! ");
	for (int i=1;i<=stop;i++) printf("%c",Outp[i]);
	for (int i=scnt;i>stop;i--) printf("%c",Outp[i]);
	printf("\n");
	return 0;
}
