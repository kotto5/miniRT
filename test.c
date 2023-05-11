
#include <sys/time.h>
#include <stdio.h>

unsigned int	func(unsigned int a, unsigned int b)
{
	if (a)
		return func(a - 1, a + b);
	else
		return (b);
}

unsigned int	func2(unsigned int a)
{
	if (a)
		return (func2(a - 1) + a);
	else
		return (0);
}


unsigned long	func3(unsigned long sum, unsigned long add, unsigned long times)
{
	if (times)
		return (func3(sum + add, add, times - 1));
	else
		return (sum);
}

unsigned long	func4(unsigned long add, unsigned long times)
{
	unsigned long ret;
	if (times)
	{
		ret = func4(add, times - 1);

		return (add + ret);
	}
	else
		return (0);
}

// int	main()
// {
// 	struct timeval	tp;

// 	gettimeofday(&tp, NULL);
// 	printf("time %ld %d\n", tp.tv_sec, tp.tv_usec);

// 	// func(100000, 0);
// 	// func2(100000);

// 	unsigned long ret;
// 	// ret = func3(0, 1, 200 0000 0000 0000 0000);
// 	ret = func3(0, 1, 2000000000000000000);
// 	// func4(1, 1000000);
// 	gettimeofday(&tp, NULL);
// 	printf("time %ld %d  ret:%ld\n", tp.tv_sec, tp.tv_usec, ret);

// 	return (0);
// }

