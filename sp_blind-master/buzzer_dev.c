#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define GPIO3 4 //BCM
#define DEV_NAME "buzzer_dev"
#define DEV_NUM 242

#define ON 0
#define OFF 1

MODULE_LICENSE("GPL");

static int status;

int buzzer_open(struct inode *pinode, struct file *pfile){
        printk(KERN_ALERT "open buzzer_dev\n");
        gpio_request(GPIO3,"buzzer");
        gpio_direction_output(GPIO3,OFF); // open with "OFF" state
        return 0;
}

int buzzer_close(struct inode *pinode, struct file *pfile){
        printk(KERN_ALERT "release buzzer_dev\n");
	gpio_set_value(GPIO3,OFF);
        return 0;
}

ssize_t buzzer_read(struct file *pfile, char __user  *buffer, size_t length, loff_t *offset){
        printk("read buzzer driver");
        return 0;
}
ssize_t buzzer_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
        
	printk("write buzzer driver");
        status = gpio_get_value(GPIO3);

        if(status ==1){ //when it's OFF
                gpio_set_value(GPIO3,ON);
		gpio_direction_output(GPIO3,ON);
                printk("buzzer on!!!!");
        }
        else if(status==0){ // when it's ON
                gpio_set_value(GPIO3,OFF);
		gpio_direction_output(GPIO3,OFF);
                printk("buzzer off!!!!");
        }// toggling

        return 0;
}

struct file_operations fop = {
        .owner = THIS_MODULE,
        .open = buzzer_open,
        .read = buzzer_read,
        .write = buzzer_write,
        .release = buzzer_close,

};

int __init buzzer_init(void){
        printk(KERN_ALERT "INIT buzzer\n");
        register_chrdev(DEV_NUM, DEV_NAME, &fop);
        return 0;
}

void __exit buzzer_exit(void){
        printk(KERN_ALERT "EXIT buzzer_dev\n");
        unregister_chrdev(DEV_NUM,DEV_NAME);
}

module_init(buzzer_init);
module_exit(buzzer_exit);
