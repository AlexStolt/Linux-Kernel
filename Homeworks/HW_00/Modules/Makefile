obj-m := project1-kyber.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules


clean:
	rm -f *.o *.ko *.mod.c *.mod *.order *.symvers