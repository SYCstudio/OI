#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class PEOPLE//定义人的结构体
{
public:
    int point,w,num;
};

bool operator < (PEOPLE a,PEOPLE b)//重载小于运算符，因为要使用STL中的sort
{
    if (a.point==b.point)
        return a.num<b.num;
    else
        return a.point>b.point;
}

const int maxN=1000001;
const int inf=2147483647;

int n,R,Q;
PEOPLE A[maxN*2];//存放所有人
PEOPLE K1[maxN*2];//每轮后临时存放胜者
PEOPLE K2[maxN*2];//临时存放败者

int main()
{
    cin>>n>>R>>Q;
    for (int i=1;i<=n*2;i++)
        cin>>A[i].point;
    for (int i=1;i<=n*2;i++)
        cin>>A[i].w;
    for (int i=1;i<=n*2;i++)
        A[i].num=i;
    sort(&A[1],&A[2*n+1]);//第一轮前用一边快排
    for (int i=1;i<=R;i++)
    {
        for (int j=1;j<=2*n;j=j+2)
        {
            if (A[j].w>A[j+1].w)
            {
                K1[j/2+1]=A[j];//分别放入两个数组
                K2[j/2+1]=A[j+1];
                K1[j/2+1].point++;
            }
            else
            {
                K1[j/2+1]=A[j+1];
                K2[j/2+1]=A[j];
                K1[j/2+1].point++;
            }
        }
        int j1=1,j2=1;
        for (int j=1;j<=2*n;j++)//归并排序
            if ((j2>n)|| ((j1<=n)&&((K1[j1].point>K2[j2].point)||((K1[j1].point==K2[j2].point)&&(K1[j1].num<K2[j2].num))) )     )
            {
                A[j]=K1[j1];
                j1++;
            }
            else
            {
                A[j]=K2[j2];
                j2++;
            }
    }
    cout<<A[Q].num<<endl;
    return 0;
}
