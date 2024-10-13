ifneq ($(KERNELRELEASE),)
	obj-m := kmalloc.o
else
	KERNELDIR ?= /usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
.PHONY:clean
clean:
	rm -rf *.mod.c *.o *.order *.symvers *.ko .*.ko.cmd .*.mod.o.cmd .*.o.cmd .tmp_versions/

