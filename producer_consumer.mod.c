#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_MITIGATION_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x6bd0e573, "down_interruptible" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x122c3a7e, "_printk" },
	{ 0xcf2a6966, "up" },
	{ 0x246e77b3, "init_task" },
	{ 0x64ab2ee9, "kthread_stop" },
	{ 0x37a0cba, "kfree" },
	{ 0x52c5c991, "__kmalloc_noprof" },
	{ 0x80e6e7d6, "kthread_create_on_node" },
	{ 0x32710744, "wake_up_process" },
	{ 0x3efc6d60, "param_ops_int" },
	{ 0x7d439289, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "54BAC3F1C6CFD5ABDF2413A");
