#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
//#include <asm/atomic.h>
#include <linux/rwsem.h>
//#include <asm/uaccess.h>
#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/poll.h>
struct listnode *Linknode_req = NULL;
extern int (*ASMD_cal)(int add1, char act, int add2, int *ans);

int insert(int val){
    struct listnode *temp = NULL;
    temp = (struct listnode*)kmalloc(sizeof(struct listnode), GFP_KERNEL);
    if(temp == NULL )return -1;
    temp->val = add_temp->val;
    temp->add1 = add_temp->add1;
    temp->add2 = add_temp->add2;
    temp->act = add_temp->act;
    temp -> next = Linknode_req -> next;
    Linknode_req -> next = temp;
    DEBUG_PRINT(DEVICE_NAME ": insert %d %c %d success\n", temp->add1, temp->act, temp->add2);
    return 1;
} //成功返回1，失败返回-1

int delete(int val){
    if(Linknode_req -> next == NULL)return -1;
    struct listnode *temp = Linknode_req -> next ->next;
    kfree(Linknode_req -> next);
    Linknode_req -> next = temp;
    return 1;
}//成功返回1，失败返回-1

int lookup(int val){
    if(Linknode_req -> next == NULL)return -1;
    struct listnode* temp = Linknode_req -> next;
    while(temp){
        if(temp->val == val){
            return 1;
        }
        temp = temp -> next;
    }
    return -1;
}//找到返回1，没有返回-1
//输出并删除结果
void print(int val){
    struct listnode* temp = Linknode_req -> next;
    int err_count = 0, count = 0;
    while(temp){
        err_count = ASMD_cal(temp->add1, temp->act, temp->add2, &(temp->val));
        Linknode_req -> next = temp -> next;
        DEBUG_PRINT(DEVICE_NAME ": %d %c %d = %d\n",temp->add1, temp->act, temp->add2, temp->val);
        kfree(temp);
        temp = Linknode_req -> next;
        count++;
    }
	DEBUG_PRINT(DEVICE_NAME ": calculate success, all:%d, error data:%d\n", count, err_count);
}


int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");
	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked \n");
    int ret = 0;

    switch (uiCmd) {
    case NODE_IOCTL_INSERT: // 
        add_temp= kmalloc(sizeof(struct listnode),GFP_KERNEL);
        if (copy_from_user(add_temp, (struct listnode __user *)ulArg, sizeof(struct listnode))) { // 从用户空间程序中复制被加数到内核空间
            //__user是一个标记，它告诉编译器，这个指针所指向的内存空间是用户空间的。这个标记可以作为指针类型的修饰符
	        DEBUG_PRINT(DEVICE_NAME "copy from user fail\n");
            ret = -EFAULT; // 复制失败
            break;
        }
        insert(1);
        break;
    case NODE_IOCTL_DELETE: 
        delete(1);
        break;
    case NODE_IOCTL_LOOKUP: 
        if (copy_from_user(&b, (int __user *)ulArg, sizeof(int))) { // 从用户空间程序中复制被加数到内核空间
            //__user是一个标记，它告诉编译器，这个指针所指向的内存空间是用户空间的。这个标记可以作为指针类型的修饰符
	        DEBUG_PRINT(DEVICE_NAME "copy from user fail\n");
            ret = -EFAULT; // 复制失败
            break;
        }    
        if(1 == lookup(b)){
	        DEBUG_PRINT(DEVICE_NAME ": find %d!\n", b);
        }else{
	        DEBUG_PRINT(DEVICE_NAME ": no find %d !\n", b);    
            ret = -EFAULT; // 复制失败
        }
        break;
    case NODE_IOCTL_PRINT: 
        print(1);
        break;
    default:
        ret = -EINVAL; // 无效的命令
        break;
    }

    return ret;

}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}

