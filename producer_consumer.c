#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#define EXIT_ZOMBIE 0x00000020

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Princess Mariah Taylor");
MODULE_DESCRIPTION("Zombie Hunter");

static int prod =0;
module_param(prod, int, 0);
static int cons =0;
module_param(cons, int, 0);
static int size =0;
module_param(size, int, 0);
static int uid =0;
module_param(uid, int, 0);
static int regular =0;
module_param(regular, int, 0);
static int zombies =0;
module_param(zombies, int, 0);

static struct task_struct **kthreadPro;
static struct task_struct **kthreadCon;
static struct task_struct **bounbuffer;
int count =0;
int prow =0;
int conr = 0;
struct semaphore empty;
struct semaphore full;

static int kthreadProd_func(void *arg){
	struct task_struct *p;
	size_t process_counter =0;
	size_t tempN =(size_t)arg;
	int n =(int)tempN;
	while(!kthread_should_stop()){
		for_each_process(p){
			if (p->cred->uid.val != uid){
			continue;
			}
		++process_counter;

		if(p->exit_state & EXIT_ZOMBIE){
			if(down_interruptible(&empty)){
				bounbuffer[prow] = p;
				prow++;
				count++;
				printk(KERN_INFO "[Producer-%d] has produced a zombie process with the pid %d and parent pid %d\n", n, p->pid, p->parent->pid);
				up(&full);
			}
		}
	}
}
return 0;
}

static int kthreadCon_func(void *arg){
	while(!kthread_should_stop()){
		if(down_interruptible(&full)){
			struct task_struct *p = bounbuffer[conr];
			size_t tempM =(size_t)arg;
			int m = (int)tempM;
			conr++;
			count--;
			printk(KERN_INFO "[Consumer-%d] has consumed a zombie process with the pid %d and parent pid %d\n", m, p->pid, p->parent->pid);
			up(&empty);
		}
	}
return 0;
}

static int __init prodCons_init(void){
	kthreadPro= kmalloc_array(prod, sizeof(struct task_struct *), GFP_KERNEL);
	kthreadCon= kmalloc_array(cons, sizeof(struct task_struct *), GFP_KERNEL);
	bounbuffer = kmalloc_array(size, sizeof(struct task_struct *), GFP_KERNEL);
	sema_init(&empty, size);
	sema_init(&full, 0);
	for(int n =0; n < prod; n++){ //i thought of these 2 arrays to do it at first before i saw the get_task_com at the end and i was in too deep to change it
		kthreadPro[n]= kthread_run(kthreadProd_func, (void *)(size_t)(n+1), "Producer-%d", (n+1));
		}
	for(int m =0; m < cons; m++){
		kthreadCon[m]=kthread_run(kthreadCon_func, (void *)(size_t)(m+1), "Consumer-%d", (m+1));
	}
return 0;
}

static void __exit prodCons_exit(void){
	for(int n=0; n< prod; n++){
		kthread_stop(kthreadPro[n]);
	}

	for(int m=0; m< cons; m++){
		kthread_stop(kthreadCon[m]);
	}
	kfree(kthreadPro);
	kfree(kthreadCon);
	kfree(bounbuffer);
}

module_init(prodCons_init);
module_exit(prodCons_exit); 
