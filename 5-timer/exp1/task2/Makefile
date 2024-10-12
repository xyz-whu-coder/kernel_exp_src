ifneq ($(KERNELRELEASE),)
	obj-m := task2_timer.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
install:
	insmod task2_timer.ko
uninstall:
	rmmod task2_timer
.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
