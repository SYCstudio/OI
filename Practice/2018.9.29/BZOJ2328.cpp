#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const ld eps=1e-9;
const int inf=2147483647;

class HData
{
public:
	ld v,d;
};

int n;
ld a,b,vm,f;
priority_queue<HData> H;

bool operator < (HData A,HData B);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%lf%lf%lf%lf",&a,&b,&vm,&f);
		scanf("%d",&n);
		while (!H.empty()) H.pop();
		for (int i=1;i<=n;i++){
			ld x,y;scanf("%lf%lf",&x,&y);x/=1000.0;y/=1000.0;
			ld k=y/x,d=sqrt(x*x+y*y);
			if (k<0) H.push((HData){min(-b*k/a,vm),d});
			else{
				f-=b*k*d;
				H.push((HData){0,d});
			}
		}
		if (f<0){
			printf("IMPOSSIBLE\n");continue;
		}
		H.push((HData){vm,0});
		while ((!H.empty())&&(fabs(f)>eps)){
			ld v=H.top().v,d=H.top().d;H.pop();
			if (fabs(v-vm)<eps){
				H.push((HData){v,d});break;
			}
			if (fabs(v-H.top().v)<eps){
				d+=H.top().d;H.pop();
				H.push((HData){v,d});continue;
			}
			ld dv=f/(a*d);
			if (dv+v>H.top().v){
				dv=H.top().v-v;
				f-=dv*d*a;
				H.push((HData){v+dv,d});
			}
			else{
				f-=dv*a*d;
				H.push((HData){v+dv,d});
			}
		}
		ld Ans=0;
		while (!H.empty()){
			//cout<<"H:"<<H.top().d<<" "<<H.top().v<<endl;
			Ans+=H.top().d/H.top().v;H.pop();
		}
		printf("%.5lf\n",Ans);
	}
	return 0;
}

bool operator < (HData A,HData B){
	return A.v>B.v;
}
