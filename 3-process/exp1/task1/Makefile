ifneq ($(KERNELRELEASE),)
	obj-m := kthread.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
.PHONY:clean
install:
	insmod kthread.ko
uninstall:
	rmmod kthread
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
