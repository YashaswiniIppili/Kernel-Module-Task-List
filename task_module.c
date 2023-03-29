#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/init.h>

#include <linux/sched/signal.h>

#include <linux/slab.h>



MODULE_LICENSE("GPL");

MODULE_AUTHOR("Your Name");

MODULE_DESCRIPTION("A kernel module to list all current tasks in a Linux system beginning from the init task.");



struct process_info {

    struct task_struct *task;

    int depth;

    struct list_head list;

};



void print_tree(void) {

    struct process_info *pi;

    struct list_head *pos, *tmp;

    struct list_head queue;



    INIT_LIST_HEAD(&queue);

    pi = kmalloc(sizeof(*pi), GFP_KERNEL);

    if (!pi) {

        printk(KERN_ERR "Failed to allocate memory for process_info struct.\n");

        return;

    }

    pi->task = &init_task;

    pi->depth = 0;

    list_add_tail(&pi->list, &queue);



    while (!list_empty(&queue)) {

        pi = list_first_entry(&queue, struct process_info, list);

        list_del(&pi->list);



        printk(KERN_INFO "%*s|-%s [%d]\n", pi->depth*2, "", pi->task->comm, pi->task->pid);



        struct task_struct *child;

        struct list_head *list;

        list_for_each(list, &pi->task->children) {

            child = list_entry(list, struct task_struct, sibling);

            struct process_info *child_pi = kmalloc(sizeof(*child_pi), GFP_KERNEL);

            if (!child_pi) {

                printk(KERN_ERR "Failed to allocate memory for process_info struct.\n");

                continue;

            }

            child_pi->task = child;

            child_pi->depth = pi->depth + 1;

            list_add_tail(&child_pi->list, &queue);

        }



        kfree(pi);

    }

}



static int __init init_task_init(void) {

    printk(KERN_INFO "Initiating task module...\n");

    print_tree();

    return 0;

}



static void __exit init_task_exit(void) {

    printk(KERN_INFO "Exiting task module...\n");

}



module_init(init_task_init);

module_exit(init_task_exit);

