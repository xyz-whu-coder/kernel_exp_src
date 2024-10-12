ifneq ($(KERNELRELEASE),)
	obj-m := task5_timer.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
install:
	insmod task5_timer.ko
uninstall:
	rmmod task5_timer
.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
