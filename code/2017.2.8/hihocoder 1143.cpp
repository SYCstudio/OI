#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;

int main()
{
    int F[3];
    int n;
    int i,j;
    F[0]=1;
    F[1]=2;
    cin>>n;
    if (n<=2)
    {
        cout<<F[n-1]<<endl;
        return 0;
	}
	j=0;
	for (i=3;i<=n;i++,j=!j)
	{
	    F[j]=(F[j]+F[!j])%19999997;
	    //cout<<F[j]<<endl;
	}
	cout<<F[!(n%2)]<<endl;
	
	return 0;
}