KERNELDIR = /lib/modules/4.19.42-v7+/build

obj-m := led_mod.o ultra_dev.o 

PWD := $(shell pwd)

all :
		make -C $(KERNELDIR) M=$(PWD) modules

clean :
		make -C $(KERNELDIR) M=$(PWD) clean

in :
		sudo insmod led_mod.ko
		sudo mknod -m 777 /dev/led_mod c 241 0
		sudo insmod ultra_dev.ko
		sudo mknod -m 777 /dev/ultra_dev c 240 0

out :
		sudo rmmod led_mod
		sudo rmmod ultra_dev


