#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");


int (*ASMD_cal)(int add1, char act, int add2, int *ans);

static int ASMD_cal_function(int add1, char act, int add2, int *ans){
    static int i = 0;
    switch(act){
        case '+':
            *ans = add1 + add2;
            break;
        case '-':
            *ans = add1 - add2;
            break;
        case '*':
            *ans = add1 * add2;
            break;
        case '/':
            if(add2 == 0){
                *ans = -65536;
                i++;
            }
            else    
                *ans = add1 / add2;
            break;
        default:
            break;
    }
    return  i;
}
//程序中必须有下列两个函数
static int hello_init(void)
{
   printk(KERN_ALERT "hello ASMD_cal\n");
    ASMD_cal = ASMD_cal_function;
    return 0;
}
static void hello_exit(void)
{
   printk(KERN_ALERT "goodbye,kernel\n");
}
EXPORT_SYMBOL(ASMD_cal);
//加载or卸载模块
module_init(hello_init);
module_exit(hello_exit);
// 可选 
MODULE_AUTHOR("LiangZisonog");
MODULE_DESCRIPTION("calculate arithmetic function!\n");
MODULE_VERSION("v1.0");
MODULE_ALIAS("A simplest example");
