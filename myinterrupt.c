/*
 *  linux/mykernel/myinterrupt.c
 *
 *  Kernel internal my_timer_handler
 *  Change IA32 to x86-64 arch, 2020/4/26
 *
 *  Copyright (C) 2013, 2020  Mengning
 *
 */
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/tty.h>
#include <linux/vmalloc.h>

#include "mypcb.h"

extern tPCB task[MAX_TASK_NUM];
extern tPCB * my_current_task;
extern volatile int my_need_sched;
volatile int time_count = 0;

/*
 * Called by timer interrupt.
 * it runs in the name of current running process,
 * so it use kernel stack of current running process
 */
void my_timer_handler(void)
{
    if(time_count%1000 == 0 && my_need_sched != 1)
    {
        printk(KERN_NOTICE ">>>my_timer_handler here<<<\n");
        my_need_sched = 1;
    } 
    time_count ++ ;  
    return;  	
}

void my_schedule(void)
{
    tPCB * next;
    tPCB * prev;

    if(my_current_task == NULL 
        || my_current_task->next == NULL)
    {
    	return;
    }
    printk(KERN_NOTICE ">>>my_schedule<<<\n");
    /* schedule */
    next = my_current_task->next;
    prev = my_current_task;
    if(next->state == 0)/* -1 unrunnable, 0 runnable, >0 stopped */
    {        
    	my_current_task = next;
        unsigned long prev_sp = prev->thread.sp;
        unsigned long prev_ra = next->thread.ra;
    	unsigned long next_sp = next->thread.sp;
        unsigned long next_ra = next->thread.ra; 
    	printk(KERN_NOTICE ">>>switch %d to %d<<<\n",prev->pid,next->pid);  
    	/* switch to next process */
    	// __asm__ volatile(	
        //     "mv %0,sp \n"
        //     "mv %1,ra \n"
        //     "ld sp,%2 \n"
        //     "ld ra,%3 \n"
        //     "ret"
        // 	: "=r" (prev->thread.sp),"=r" (prev->thread.ra)
        // 	: "m" (next->thread.sp), "m" ( next->thread.ra)
    	// ); 
        __asm__ volatile (
            "mv %0,sp \n"
            "mv %1,ra \n"
            :"=r" (prev_sp) ,"=r" (prev_ra)
        );
        __asm__ volatile(	
 
            "mv sp,%0 \n"
            "mv ra,%1 \n"
            "ret"
        	:
            : "r" (next_sp), "r" ( next_ra)
    	); 
    }  
    return;	
}
