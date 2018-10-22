#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int inf=2147483647;

class Point
{
public:
	ld x,y;int id;
};

int n;
Point P[maxN],St[maxN];
ld Mn[maxN],Mx[maxN];
vector<int> Id[maxN],Ans;

bool cmp(Point A,Point B);
Point operator - (Point A,Point B);
ld Cross(Point A,Point B);

int main(){
	//freopen("in","r",stdin);
	scanf("%d",&n);int mxy=-inf;
	for (int i=1;i<=n;i++) scanf("%LF",&P[i].y),Id[i].push_back(i),mxy=max(mxy,(int)P[i].y);
	for (int i=1;i<=n;i++) scanf("%LF",&P[i].x),P[i].id=i;
	for (int i=1;i<=n;i++) if (P[i].y==mxy) Ans.push_back(i);
	sort(&P[1],&P[n+1],cmp);
	//Ans.push_back(P[1].id);
	//for (int i=2;(i<=n)&&(P[i].y==P[1].y);i++) Ans.push_back(i);
	int top=0;
	//cerr<<"A"<<endl;
	for (int i=1;i<=n;i++){
		if ((top)&&(P[i].x==St[top].x)){
			if (P[i].y==St[top].y) Id[St[top].id].push_back(P[i].id);
			continue;
		}
		while ((top)&&(St[top].y<=P[i].y)) top--;
		St[++top]=P[i];
	}
	n=top;for (int i=1;i<=n;i++) P[i]=St[i];

	//cerr<<"B"<<endl;
	top=0;
	for (int i=1;i<=n;i++){
		while ((top>=2)&&(Cross(St[top]-St[top-1],P[i]-St[top-1])>=0)) top--;
		Mn[i]=-(P[i].y-St[top].y)/(P[i].x-St[top].x);
		St[++top]=P[i];
	}
	//cerr<<"C"<<endl;
	top=0;
	for (int i=n;i>=1;i--){
		while ((top>=2)&&(Cross(P[i]-St[top-1],St[top]-St[top-1])>=0)) top--;
		Mx[i]=-(P[i].y-St[top].y)/(P[i].x-St[top].x);
		St[++top]=P[i];
	}
	for (int i=1;i<=n;i++)
		if ((i==1)||(i==n)||(Mn[i]<=Mx[i]))
			for (int j=0,sz=Id[P[i].id].size();j<sz;j++)
				Ans.push_back(Id[P[i].id][j]);
	sort(Ans.begin(),Ans.end());
	Ans.erase(unique(Ans.begin(),Ans.end()),Ans.end());
	printf("%d\n",(int)Ans.size());
	for (int i=0,sz=Ans.size();i<sz;i++){
		printf("%d",Ans[i]);
		if (i!=sz-1) printf(" ");
	}
	printf("\n");
	return 0;
}

bool cmp(Point A,Point B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y>B.y;
}

Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}

ld Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}
