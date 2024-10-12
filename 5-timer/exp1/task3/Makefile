ifneq ($(KERNELRELEASE),)
	obj-m := task3_timer.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
install:
	insmod task3_timer.ko
uninstall:
	rmmod task3_timer
.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
