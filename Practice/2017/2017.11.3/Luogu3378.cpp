#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000010;
const int inf=2147483647;

class Heap
{
public:
	int size;
	int H[maxN];
	Heap()
		{
			size=0;
		}
	void Insert(int x)
		{
			size++;
			H[size]=x;
			int now=size;
			int fa=now/2;
			while (fa)
			{
				if (H[fa]>H[now])
				{
					swap(H[fa],H[now]);
					now=fa;
					fa=now/2;
				}
				else break;
			}
			return;
		}
	int Top()
		{
			return H[1];
		}
	void Pop()
		{
			if (Empty())
				return;
			H[1]=H[size];
			size--;
			int now=1;
			int lson,rson,mnson;
			while (now<=size)
			{
				lson=now*2;
				rson=now*2+1;
				if (lson>size)
					break;
				if ((rson<=size)&&(H[lson]>H[rson]))
					mnson=rson;
				else mnson=lson;
				if (H[mnson]<H[now])
				{
					swap(H[mnson],H[now]);
					now=mnson;
				}
				else break;
			}
		}
	bool Empty()
		{
			return size==0;
		}
};

Heap H;

int main()
{
	int Q;
	scanf("%d",&Q);
	while (Q--)
	{
		int opt;
		scanf("%d",&opt);
		if (opt==1)
		{
			int x;
			scanf("%d",&x);
			H.Insert(x);
		}
		if (opt==2)
			printf("%d\n",H.Top());
		if (opt==3)
			H.Pop();
	}
	return 0;
}
