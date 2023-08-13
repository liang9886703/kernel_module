

ifneq ($(KERNELRELEASE),)
	obj-m := calculate_list.o
	calculate_list-objs := DriverMain.o DriverFileOperations.o
	KBUILD_EXTRA_SYMBOLS += ../cal/ASMD_cal.ko
	export KBUILD_EXTRA_SYMBOLS
EXTRA_CFLAGS := -DTEST_DEBUG -ggdb -O2

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm *.order *.symvers *.mod.c *.o .*.o.cmd .*.cmd .tmp_versions -rf
endif
