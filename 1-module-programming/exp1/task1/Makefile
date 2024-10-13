obj-m := module1.o module2.o module3.o module4.o
KDIR := /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	sudo rm -rf *.o *.ko *.mod *.mod.c .*.ko.cmd .*.mod.o.cmd .*.o.cmd Module.symvers modules.order ./.tmp_versions 
