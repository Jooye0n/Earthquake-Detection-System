#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#define GPIO2 22 //BCM
#define DEV_NAME "button_dev"
#define DEV_NUM 241

MODULE_LICENSE("GPL");

static int count=0;

int button_open(struct inode *pinode, struct file *pfile){

 printk(KERN_ALERT "OPEN button_dev\n");
 gpio_request(GPIO2,"GPIO2");
 
 gpio_direction_input(GPIO2);
 
 return 0;
}


int button_close(struct inode *pinode, struct file *pfile){
 printk(KERN_ALERT "RELEASE button_dev\n");
 count =0; 
 return 0;
}


ssize_t button_write (struct file *pfile, const char __user *buffer,size_t length, loff_t *offset)
{
 printk("Write button drv\n");
 
 return length;
}


ssize_t button_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
 //printk("Read button drv\n");

 if(gpio_get_value(GPIO2)==0){
 count++;
 
 if(count>200){
 	int a;
 	a=1;
	count=0; 
 	copy_to_user(buffer,&a,4);//button_flag=1
 	}
 }//recognize "pushed" when it should be pressed during specific time

 return 0;
}


struct file_operations fop={
 .owner = THIS_MODULE,
 .open = button_open,
 .release = button_close,
 .write = button_write,
 .read = button_read,
};

int __init button_init(void){
 printk(KERN_ALERT "INIT ledtest\n");
 register_chrdev(DEV_NUM, DEV_NAME, &fop);
 return 0;
}

void __exit button_exit(void){
 printk(KERN_ALERT "EXIT ledtest_dev\n");
 unregister_chrdev(DEV_NUM,DEV_NAME);
}

module_init(button_init);
module_exit(button_exit);




