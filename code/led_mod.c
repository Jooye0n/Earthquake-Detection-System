#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/fs.h>

#define LW 20
#define LY 23
#define LR 24
#define LG 25

#define LOW 0
#define HIGH 1

MODULE_LICENSE("GPL");

#define IOCTL_MAGIC_NUMBER 'H'
#define IOCTL_LED_20	_IO( IOCTL_MAGIC_NUMBER, 0)
#define IOCTL_LED_23	_IO( IOCTL_MAGIC_NUMBER, 1)
#define IOCTL_LED_24	_IO( IOCTL_MAGIC_NUMBER, 2)
#define IOCTL_LED_25	_IO( IOCTL_MAGIC_NUMBER, 3)

long led_ioctl (struct file * filp, unsigned int cmd, unsigned long arg){
	switch(cmd) {
		case IOCTL_LED_20://white
			gpio_set_value(LW, HIGH);
			gpio_set_value(LG, LOW);
			gpio_set_value(LY, LOW);
			gpio_set_value(LR, LOW);
			printk(KERN_INFO "LED : TURNNING ON GREEN LED\n");
			break;
		case IOCTL_LED_23://yellow
			gpio_set_value(LY, HIGH);
			gpio_set_value(LW, LOW);
			gpio_set_value(LG, LOW);
			gpio_set_value(LR, LOW);
			printk(KERN_INFO "LED : TURNNING ON YELLOW LED\n");
			break;
		case IOCTL_LED_24://red
			gpio_set_value(LR, HIGH);
			gpio_set_value(LW, LOW);
			gpio_set_value(LG, LOW);
			gpio_set_value(LY, LOW);
			printk(KERN_INFO "LED : TURNNING ON RED LED\n");
			break;
		case IOCTL_LED_25://green
			gpio_set_value(LG, HIGH);
			gpio_set_value(LW, LOW);
			gpio_set_value(LY, LOW);
			gpio_set_value(LR, LOW);
			printk(KERN_INFO "LED : TURNNING ON GREEN LED\n");
			break;
		}

	return 0;
}

struct file_operations fops = {
	.unlocked_ioctl = led_ioctl
};

static int __init led_init(void){
	printk(KERN_INFO "LED : Starting ...\n");

	register_chrdev(241, "led_dev", &fops);
	gpio_request(LR, "LR");
	gpio_request(LW, "LW");
	gpio_request(LY, "LY");
	gpio_request(LG, "LG");
	gpio_direction_output(LR, HIGH);
	gpio_direction_output(LW, HIGH);
	gpio_direction_output(LY, LOW);
	gpio_direction_output(LG, LOW);
	printk(KERN_INFO "LED : Starting Complete\n");

	return 0;
}

static void __exit led_exit(void){
	gpio_free(LR);
	gpio_free(LW);
	gpio_free(LY);
	gpio_free(LG);
	unregister_chrdev(241, "led_dev");
	printk(KERN_INFO "LED : Exit Done");
}



module_init(led_init);
module_exit(led_exit);
