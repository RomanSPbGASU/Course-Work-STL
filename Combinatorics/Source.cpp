//#include <windows.h>
//#include <iostream>
//#include <stdlib.h>
//using namespace std;
//
//const int n = 4;
//
//long total = 1;
//int used[n], a[n];
//
//void generate(int x)
//{
//	int i;
//	if (x == n)
//	{
//		cout << (total++) << ":\t";
//		for (i = 0; i < n; ++i)
//			cout << a[i];
//		cout << endl;
//	}
//	else
//		for (i = 0; i < n; ++i)
//			if (!used[i])
//			{
//				used[i] = 1;
//				a[x] = i + 1;
//
//				generate(x + 1);
//				used[i] = 0;
//			}
//}
//
//void main()
//{
//
//	for (int i = 0; i < n; ++i)
//		used[i] = 0;
//
//	generate(0);
//	system("pause");
//}