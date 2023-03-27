#include<linux/module.h>
#include<linux/kernel.h>


static int __init e1000_init_module(void)
{
    pr_info("Hello from e1000.c hello mod init\n");
    return 0;
}

static void __exit e1000_exit_module(void)
{
    pr_info("Hello from e1000.c hello mod init\n");
}

module_init(hello_mod_init);
module_exit(hello_mod_exit);