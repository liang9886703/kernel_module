#ifndef DriverMain_H
#define DriverMain_H

#include <linux/init.h>
#include <linux/module.h>
#include <asm/mtrr.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define DEVICE_NAME "calculate_list"
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
static struct listnode *add_temp;
static int b;
struct SLDriverParameters
{
	struct class *pslDriverClass;
	dev_t uiDeviceNumber;
	struct cdev slCharDevice;
};

extern struct SLDriverParameters gslDriverParameters;

#endif
