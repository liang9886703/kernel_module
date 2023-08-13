#include<errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
// 定义ioctl命令
#define NODE_IOCTL_MAGIC 'a'
#define NODE_IOCTL_INSERT _IOWR(NODE_IOCTL_MAGIC, 1, struct listnode)
#define NODE_IOCTL_DELETE _IOR(NODE_IOCTL_MAGIC, 2, int)
#define NODE_IOCTL_LOOKUP _IOR(NODE_IOCTL_MAGIC, 3, int)
#define NODE_IOCTL_PRINT _IOR(NODE_IOCTL_MAGIC, 4, int)
struct listnode{
    int val;//结果
	int add1;//数字1
	int add2;//数字2
	char act;//计算符号
	struct listnode* next;
};

int main(int argc, char *argv[])
{
    int fd;
    int res;
	if((fd = open("/dev/calculate_list", O_RDWR)) < 0)
	{
		printf("open /dev/calculate_list fail!\n");
		return -1;
	}
	int fd2;
  	if((fd2 = open(argv[1], O_RDONLY)) == -1){
      	printf("open path:'%s' fail ! error: %s\n", argv[1], strerror(errno));
     	 return 0;
 	}
 	dup2(fd2, STDIN_FILENO);
	int scanf_ans, a, b;
	char ch;
 	while((scanf_ans = scanf("%d %c %d", &a, &ch, &b)) != EOF){
      //如果输入数据不匹配则报错
      	if(scanf_ans == 0){
         	printf("get cur data fail!\n");
         	break;
      	}
		struct listnode add_temp = {0, a, b, ch, NULL};
		if (ioctl(fd, NODE_IOCTL_INSERT, &add_temp) < 0) {
			printf("add request failed\n");
			close(fd);
			return -1;
		}
   }

	//insert
	b = 3;
	//delete
	ioctl(fd, NODE_IOCTL_DELETE, &b);
	//lookup
	ioctl(fd, NODE_IOCTL_LOOKUP, &b);
	//print
	ioctl(fd, NODE_IOCTL_PRINT, &b);
	//close(fd);

	return 0;
}
