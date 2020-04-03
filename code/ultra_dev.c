#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3f584fcd, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x83601418, "__register_chrdev" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x1d855df9, "gpiod_get_raw_value" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xe27518da, "gpiod_set_raw_value" },
	{ 0x127f5033, "gpiod_direction_output_raw" },
	{ 0x8987853, "gpiod_direction_input" },
	{ 0x2a941df5, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x7c32d0f0, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "4BAEB1161A2E6C8E756E042");
