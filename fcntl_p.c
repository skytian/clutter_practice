/*************************************************************************
    > File Name: fcntl_p.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Wed 08 Feb 2017 09:50:08 AM CST
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<error.h>

void write_to_file(int fd, char *a, int size){
	int i;
	for( ; i < 100; i++){
		if(write(fd, a, size) == -1){
			printf("write error!");
		}
		sleep(1);
	}
}
void my_thread_func(void *arg){
	printf("enter my thread func\n");
	int *fd = (int *)arg;
	printf("thread fd:%d\n", *fd);
	write_to_file(*fd, "thread\n", sizeof("thread\n"));
}
int judge_block(int fd){
	int flags;
	if((flags = fcntl(fd, F_GETFL,0)) == -1)
		printf("fcntl F_GETFL failed!\n");
	if(flags&O_NONBLOCK)
		printf("fd is nonblcok!\n");
	else
		printf("fd is block!\n");
	return flags;
}
int main(){
	int ntowrite,nwrite;
	int fd;
	int flags;
	pthread_t pid;
	fd = open("test_block.txt", O_WRONLY|O_CREAT|O_APPEND);
	flags = judge_block(fd);

	flags &= ~O_NONBLOCK;
	if(fcntl(fd, F_SETFL, flags) == -1)
		printf("fcntl F_SETFL fail\n");

	flags = judge_block(fd);
	//write(fd, "test_block\n", sizeof("test_block\n"));
	if(pthread_create(&pid, NULL, my_thread_func, (void *)&fd) != 0){
		printf("create thread error!\n");
	}
	//printf("main fd:%d\n", fd);
	write_to_file(fd, "\nmain", sizeof("main\n"));
	close(fd);
}
