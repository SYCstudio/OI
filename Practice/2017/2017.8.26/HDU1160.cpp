#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100000;
const int inf=2147483647;

class DATA
{
public:
	int weight,speed;
	int num;
};

bool operator < (DATA A,DATA B)
{
	return A.weight<B.weight;
}

int n;
DATA Arr[maxN];
int Path[maxN];
int F[maxN];

void outp(int now);

int main()
{
	n=0;
	int w,s;
	while (scanf("%d%d",&w,&s)!=EOF)
	{
		//if ((w==0)&&(s==0))
		//	break;
		n++;
		Arr[n].weight=w;
		Arr[n].speed=s;
		Arr[n].num=n;
	}
	sort(&Arr[1],&Arr[n+1]);
	int Ans=0;
	for (int i=1;i<=n;i++)
	{
		F[i]=1;
		Path[i]=-1;
		for (int j=1;j<i;j++)
			if ((Arr[j].speed>Arr[i].speed)&&(Arr[j].weight<Arr[i].weight))
				if (F[j]+1>F[i])
				{
					F[i]=F[j]+1;
					Path[i]=j;
				}
		if (F[i]>F[Ans])
			Ans=i;
	}
	printf("%d\n",F[Ans]);
	outp(Ans);
	return 0;
}

void outp(int now)
{
	if (now==-1)
		return;
	outp(Path[now]);
	printf("%d\n",Arr[now].num);
	return;
}
