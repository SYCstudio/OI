#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=400020;
const int inf=2147483647;

ll n;
ll A[maxN];
char str[maxN];

int main()
{
    int TT;
    cin>>TT;
    for (int ti=1;ti<=TT;ti++)
    {
        scanf("%s",str);
        n=strlen(str);
        for (int i=0;i<n;i++)
            if (str[i]=='R')
                A[i+1]=1;
            else
                A[i+1]=0;
        ll invcnt=0;//逆序对数
        ll tmp1=0;//左边R的个数，右边B的个数（方便求逆序对）
        ll tmp2=0;
        ll mid=n>>1;//中间的位置，同时也是元素个数的一半
        //求出在初始mid左边的数右移和右边的数左移的初值tmp
        for (int i=1;i<=mid;i++)
            if (A[i]==1)
                tmp1++;
            else
                invcnt+=tmp1;
        for (int i=mid+1;i<=n;i++)
            if (A[i]==0)
                tmp2++;
            else
                invcnt+=tmp2;
        ll Ans=invcnt;//Ans的初值就是上面我们求出的逆序对数，因为全部向中间靠也是一种方案
        //这里规定R为1，B为1
        for (int i=1;i<=n;i++)//相当于在向右滑动一个窗口
        {
            int i2=(i+mid-1)%n+1;//i代表原左边最左边的一个数要加入右边，i2代表原右边最左边的一个数要加入左边
            if (A[i]==1)
            {
                if (A[i2]==0)//首先让invcnt加上放到后面去后新产生的正序对数，这里就要判断一下右边滑到左边去的那个数是否会产生一个正序对，若是，则要减去一
                {
                    invcnt+=tmp2-1;
                }
                else
                    invcnt+=tmp2;
                //再减去从左边移走后消失的逆序对数
                invcnt-=mid-tmp1;//tmp1是左边的R数，那么mid-tmp1就是左边的B数
            }
            if (A[i2]==0)
            {
                if (A[i]==1)//和上面一样，首先要invcnt加上把一个B放到前面去后的在左边形成的新逆序对数
                            //此时就要判断左边移出去的是否是R了
                {
                    invcnt+=tmp1-1;
                }
                else
                    invcnt+=tmp1;
                //再减去右边消失的正序对数
                invcnt-=(n-mid-tmp2);//注意这里是n-mid，因为n有奇偶数的情况，当奇数时，两边不一样
            }
            if (A[i]==1)
                tmp1--;
            else
                tmp2++;
            if (A[i2]==0)
                tmp2--;
            else
                tmp1++;
            Ans=min(Ans,invcnt);
        }
        //printf("Case #%d: %d\n",ti,Ans);
        cout<<Ans<<endl;
    }
    return 0;
}
