#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include "ioctl_test.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sean");
MODULE_DESCRIPTION("test ioctl");

static int driver_open(struct inode *device_file, struct file *instance) {
  printk("driver open");
  return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
  printk("driver close");
  return 0;
}

int32_t answer = 42;

static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg) {
  struct mystruct test;
  switch(cmd) {
    case WR_VALUE:
      if(copy_from_user(&answer, (int32_t *) arg, sizeof(answer))) {
         printk("error \n");
      } else {
      	printk("success \n");
      }
      break;
    case RD_VALUE:
      if(copy_to_user((int32_t *) arg, &answer, sizeof(answer))) {
        printk("error copy date to user\n");
      } else {
        printk("answer copied\n");
      }
      break;
    case GREETER:
      if (copy_from_user(&test, (struct mystruct *) arg, sizeof(test))) {
        printk("error copy from user\n");
      } else {
        printk("error copy from user %d %s\n", test.repeat, test.name);
      }
      break;
  }
  return 0;
}

static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = driver_open,
  .release = driver_close,
  .unlocked_ioctl = my_ioctl
};

#define MYMAJOR 64

static int __init ModuleInit(void) {
  int retval;
  printk("hello kernel\n");
  
  retval = register_chrdev(MYMAJOR, "my_ioctl_example", &fops);
  if (retval == 0) {
    printk("register device number major %d, minor: %d \n", MYMAJOR, 0);
  } else if(retval > 0) {
    printk("register device number major %d, minor: %d \n", retval >> 20, retval&0xfffff);
  } else {
    printk("could not register device number\n");
    return -1;
  }
  return 0;
}

static void __exit ModuleExit(void) {
  unregister_chrdev(MYMAJOR, "my_ioctl_example");
  printk("Goodbye, kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
