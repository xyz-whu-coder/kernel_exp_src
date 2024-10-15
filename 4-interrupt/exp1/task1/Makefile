ifneq ($(KERNELRELEASE),)
	obj-m := tasklet_interrupt.o
else
	KERNELDIR ?= /usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
.PHONY:clean
clean:
	sudo rm -rf *.mod.c *.o *.order *.symvers *.ko .tasklet_interrupt.ko.cmd .tasklet_interrupt.mod.o.cmd .tasklet_interrupt.o.cmd .tmp_versions
