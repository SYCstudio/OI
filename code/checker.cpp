#include <algorithm>
#include <cstdio>
int arr[50005];
int main()
{
	FILE *fin = fopen("sort.in", "r"), *fout = fopen("sort.out", "r");
	if (!fin)
	{
		puts("INVALID : File sort.in not found.");
		return -1;
	}
	if (!fout)
	{
		puts("INVALID : File sort.out not found.");
		return -1;
	}
	int n;
	fscanf(fin, "%d", &n);
	for (int i = 0; i < n; i++)
		fscanf(fin, "%d", arr + i);
	int l, r, sum = 0;
	while (~fscanf(fout, "%d%d", &l, &r))
	{
		if (l == -1 && r == -1)
			break;
		sum += r - l + 1;
		if (l <= 0 || l > n)
		{
			printf("INVALID : l = %d is not in range [1, %d].\n", l, n);
			return -1;
		}
		if (r <= 0 || r > n)
		{
			printf("INVALID : r = %d is not in range [1, %d].\n", r, n);
			return -1;
		}
		if (l > r)
		{
			printf("INVALID : %d = l > r = %d.\n", l, r);
			return -1;
		}
		if (sum > 20000000)
		{
			puts("INVALID : Too much cost.");
			return -1;
		}
		std::reverse(arr + --l, arr + r);
	}
	bool f = true;
	for (int i = 1; i < n; i++)
		f &= arr[i] >= arr[i - 1];
	if (!f)
	{
		puts("INVALID : Not sorted.");
		return -1;
	}
	printf("VALID : Total cost is %d.\n", sum);
	return 0;
}
