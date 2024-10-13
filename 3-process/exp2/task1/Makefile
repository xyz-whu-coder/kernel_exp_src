ifneq ($(KERNELRELEASE),)
	obj-m := proc_parser.o
else
	KERNELDIR ?=/usr/lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
install:
	insmod proc_parser.ko
uninstall:
	rmmod proc_parser
.PHONY:clean
clean:
	sudo rm -rf *.mod.c *.o *.order *.symvers *.ko .proc_parser.mod.o.cmd .proc_parser.ko.cmd  .proc_parser.o.cmd .tmp_versions
