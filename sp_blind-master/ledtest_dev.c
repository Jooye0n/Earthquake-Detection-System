#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>

#define GPIO1 16 //BCM
#define DEV_NAME "ledtest_dev"
#define DEV_NUM 240


MODULE_LICENSE("GPL");



int ledtest_open(struct inode *pinode, struct file *pfile){

 printk(KERN_ALERT "OPEN ledtest_dev\n");
 gpio_request(GPIO1,"GPIO1");
 gpio_direction_output(GPIO1,0); //when opening, reset to 0
 return 0;
}

int ledtest_close(struct inode *pinode, struct file *pfile){
 printk(KERN_ALERT "RELEASE ledtest_dev\n");
 gpio_set_value(GPIO1,0); //turn off led when closing
 return 0;
}

ssize_t ledtest_write(struct file *pfile,const char __user *buffer, size_t length, loff_t *offset)
{
 printk("Write led drv");

 gpio_set_value(GPIO1,1); //turning on the led

 return 0;
}


struct file_operations fop={
 .owner = THIS_MODULE,
 .open = ledtest_open,
 .release = ledtest_close,
 .write = ledtest_write,
};

int __init ledtest_init(void){
 printk(KERN_ALERT "INIT ledtest\n");
 register_chrdev(DEV_NUM, DEV_NAME, &fop);
 return 0;
}

void __exit ledtest_exit(void){
 printk(KERN_ALERT "EXIT ledtest_dev\n");
 unregister_chrdev(DEV_NUM,DEV_NAME);
}

module_init(ledtest_init);
module_exit(ledtest_exit);




