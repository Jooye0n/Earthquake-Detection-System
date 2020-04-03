#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#define GPIOOUT 12 //trig
#define GPIOIN 1 //echo
#define DEV_NAME "ultra_dev"
#define DEV_NUM 243


MODULE_LICENSE("GPL");

static int temp;
static int state;

int ultra_open(struct inode *pinode, struct file *pfile){

 printk(KERN_ALERT "OPEN ultra_dev\n");
 gpio_request(GPIOIN,"GPIOIN");
 gpio_direction_input(GPIOIN);
 gpio_request(GPIOOUT,"GPIOOUT");
 gpio_direction_output(GPIOOUT,0);
 return 0;
}

int ultra_close(struct inode *pinode, struct file *pfile){
 printk(KERN_ALERT "RELEASE ultra_dev\n");
 return 0;
}

ssize_t ultra_write(struct file *pfile,const char __user *buffer, size_t length, loff_t *offset)
{
 printk("Write ultra drv\n");
 
 gpio_set_value(GPIOOUT,0); 
 gpio_set_value(GPIOOUT,1);
 udelay(30);
 gpio_set_value(GPIOOUT,0);
 //shoots ultra-sonic to the object
 
 return 0;
}

ssize_t ultra_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){

 //printk("Read simple ultra drv\n");
 state=gpio_get_value(GPIOIN);
 if(state==0){
	temp=0;
	copy_to_user(buffer,&temp,4);
	
 }
 else if(state==1){
	temp=1;
	copy_to_user(buffer,&temp,4);
	
 }
 else
 	return -1;
 //implemented by polling manner. send stopflag to main app if state==1

 return 0;

}

 
struct file_operations fop={
 .owner = THIS_MODULE,
 .open = ultra_open,
 .release = ultra_close,
 .write = ultra_write,
 .read = ultra_read,
};

int __init ultra_init(void){
 printk(KERN_ALERT "INIT ultra\n");
 register_chrdev(DEV_NUM, DEV_NAME, &fop);
 return 0;

}

void __exit ultra_exit(void){
 printk(KERN_ALERT "EXIT ultra\n");
 unregister_chrdev(DEV_NUM,DEV_NAME);
}

module_init(ultra_init);
module_exit(ultra_exit);




