# Guide: https://www.kernel.org/doc/html/latest/kbuild/makefiles.html

MODULE_NAME = csi_dump_pdata
SRC_FILE = dump_pdata

PWD := $(shell pwd)
KVERSION := $(shell uname -r)
KERNEL_DIR = /lib/modules/$(shell uname -r)


obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-y := $(SRC_FILE).o
# you can put more source files in "$(MODULE_NAME)-y := ..." line.

all:
	make -C $(KERNEL_DIR)/build M=$(PWD) modules && echo "  OK: Module file $(MODULE_NAME).ko generated."
clean:
	make -C $(KERNEL_DIR)/build M=$(PWD) clean
