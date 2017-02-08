/*************************************************************************
    > File Name: sighub_test.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Tue 07 Feb 2017 05:08:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

char **args;
void myhandle(int sig){
	printf("%s: sighup received",args[1]);
}

int main(int argc, char **argv){
	args = argv;
	signal(SIGHUP, myhandle);
	pause();
	return 0;
}

