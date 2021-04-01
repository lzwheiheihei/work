#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <iostream>
#include <thread>
using namespace std;
int test(int num)
{
	cout << num << endl;
	sleep(1);
}
int main()
{
	/*
	#pragma omp parallel for num_threads(5)
		for (int i = 0; i < 10; i++)
		{
			test(i);
		}
	*/
	thread t[3];
	for(int i = 0; i < 3; i++)
	{
		t[i] = thread(test, i);
	}
	for(int i = 0; i < 3; i++)
	{
		t[i].join();
	}
	cout << "hello world" << endl;
	return 0;
}
