#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxsize=20000;

int n;
int A[maxsize];

int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>A[i];
    sort(&A[1],&A[n+1]);
    cout<<A[n/2+1]<<endl;
    return 0;
}
