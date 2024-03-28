#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init test_init(void)
{
    printk("<1>Hello, World! from the kernel space...\n");
    return 0;
}

static void __exit test_exit(void)
{
    printk("<1>Good Bye, World! leaving kernel space...\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
