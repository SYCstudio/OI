#include<bits/stdc++.h>
using namespace std;

const int maxN=505;
const int inf=2147483647;

class Outp
{
public:
	int x1,y1,x2,y2;
};

int n,m;
int Mt[maxN][maxN];
int scnt=0;
Outp O[maxN*maxN];

int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) cin>>Mt[i][j];
	for (int i=1;i<=n;i++)
		if (i&1){
			for (int j=1;j<m;j++)
				if (Mt[i][j]&1)
					O[++scnt]=((Outp){i,j,i,j+1}),Mt[i][j+1]++;
			if ((Mt[i][m]&1)&&(i!=n)) O[++scnt]=((Outp){i,m,i+1,m}),Mt[i+1][m]++;
		}
		else{
			for (int j=m;j>1;j--)
				if (Mt[i][j]&1)
					O[++scnt]=((Outp){i,j,i,j-1}),Mt[i][j-1]++;
			if ((Mt[i][1]&1)&&(i!=n)) O[++scnt]=((Outp){i,1,i+1,1}),Mt[i+1][1]++;
		}
	cout<<scnt<<endl;
	for (int i=1;i<=scnt;i++) cout<<O[i].x1<<" "<<O[i].y1<<" "<<O[i].x2<<" "<<O[i].y2<<endl;
	return 0;
}
