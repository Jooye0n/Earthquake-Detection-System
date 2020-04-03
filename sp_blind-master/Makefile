KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := ledtest_dev.o button_dev.o buzzer_dev.o ultra_dev.o

PWD := $(shell pwd)

default: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

in: 
	sudo insmod ledtest_dev.ko
	sudo mknod -m 666 /dev/ledtest_dev c 240 0
	sudo insmod button_dev.ko
	sudo mknod -m 666 /dev/button_dev c 241 0
	sudo insmod buzzer_dev.ko
	sudo mknod -m 666 /dev/buzzer_dev c 242 0
	sudo insmod ultra_dev.ko
	sudo mknod -m 666 /dev/ultra_dev c 243 0

out:
	sudo rmmod ledtest_dev
	sudo rm -rf /dev/ledtest_dev
	sudo rmmod button_dev
	sudo rm -rf /dev/button_dev
	sudo rmmod buzzer_dev
	sudo rm -rf /dev/buzzer_dev
	sudo rmmod ultra_dev
	sudo rm -rf /dev/ultra_dev

usr:
	gcc -c main.c -lwiringPi -lwiringPiDev
	gcc -c motor.c -lwiringPi -lwiringPiDev
	gcc -o main motor.o main.o -lwiringPi -lwiringPiDev
