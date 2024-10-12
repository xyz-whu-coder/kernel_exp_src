ifneq ($(KERNELRELEASE),)
	obj-m := task4_timer.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
install:
	insmod task4_timer.ko
uninstall:
	rmmod task4_timer
.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
