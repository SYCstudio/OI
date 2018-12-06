#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int inf=2147483647;

int n;
char Input[maxN];
ld F[maxN];

int main(){
	//freopen("in","r",stdin);
	scanf("%d",&n);scanf("%s",Input+1);Input[0]=Input[++n]='x';
	/*
	for (int i=1;i<=n;i++)
		if (Input[i]!='o'){
			ld w=1;ld s1=0,s2=0,s3=0,s4=0;
			for (int j=i-1;j>=0;j--)
				if (Input[j]=='x'){
					F[i]=F[i]+w*(F[j]+(i-j-1)*(i-j-1));//break;
					s1+=F[j]*w;s2+=w;
					s3+=w*2.0*j;s4+=w*j*j;
					break;
				}
				else if (Input[j]=='?'){
					w*=0.5;
					F[i]=F[i]+w*(F[j]+(i-j-1)*(i-j-1));
					s1+=F[j]*w;s2+=w;
					s3+=w*2.0*j;s4+=w*j*j;
					//w*=0.5;
				}
			//cout<<i<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
		}
	for (int i=1;i<=n;i++) printf("%.4LF\n",F[i]);
	printf("%.4LF\n",F[n]);//return 0;
	//*/
	mem(F,0);ld s1=0,s2=1,s3=0,s4=0;
	for (int i=1;i<=n;i++){
		//cout<<i<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
		if (Input[i]=='?'){
			F[i]=s1+s2*(ld)(i-1)*(ld)(i-1)-(ld)2.0*(ld)(i-1)*s3+s4;
			//cout<<i<<" "<<F[i]<<endl;
			s1=(s1+F[i])*0.5;s2=(s2+(ld)1.0)*0.5;s3=(s3+(ld)i)*0.5;s4=(s4+(ld)i*(ld)i)*0.5;
			//cout<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
		}
		else if (Input[i]=='x'){
			F[i]=s1+s2*(ld)(i-1)*(ld)(i-1)-(ld)2.0*(i-1)*s3+s4;
			s1=F[i];s2=1;s3=i;s4=(ld)i*(ld)i;
		}
		//cout<<i<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
	}
	//for (int i=1;i<=n;i++) printf("%.4LF\n",F[i]);
	printf("%.4LF\n",F[n]);return 0;
}
