ifneq ($(KERNELRELEASE),)
	obj-m := ASMD_cal.o

EXTRA_CFLAGS := -DTEST_DEBUG -ggdb -O2
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm *.order *.symvers *.mod.c *.o .*.o.cmd .*.cmd .tmp_versions -rf
endif
