/*----------------------------------------------------------------------------
 *      ECE254 Lab3
 *----------------------------------------------------------------------------
 *      Name:    RT_TASK_ext.C
 *      Purpose: Interface functions for extended task management  
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/

#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *      Local Functions
 *---------------------------------------------------------------------------*/
/*--------------------------- rt_tsk_count_get ------------------------------*/
/* added in ECE254 lab2 keil_rtx */

int rt_tsk_count_get (void) {
	int activeNum;
	int count;
	activeNum = 0;

	for (count = 1; count <= os_maxtaskrun; count++) {
    if (os_active_TCB[count-1] != NULL) {
      activeNum++;
    }
  }

	if(os_idle_TCB.state != INACTIVE){
		activeNum++;
	}
	
	return activeNum;
}




/*--------------------------- rt_tsk_get ------------------------------------*/
/* added in ECE254 lab3 keil_proc */
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	
	/* sanity check */
    if( ((task_id < 1 || task_id > os_maxtaskrun) && task_id != 0xFF)||
		((P_TCB)os_active_TCB[task_id - 1] == NULL)||
		(p_task_info == NULL || t == NULL))
		return OS_R_NOK;

	/*	Get TCB of this task id info  */
    P_TCB p_task;
    p_task = os_active_TCB[task_id-1];

	
    /*	task_id  */
	p_task_info->task_id     = p_task->task_id;
	
	/*	task_state  */
	p_task_info->state       = p_task->state;

	/*	execution priority  */
	p_task_info->prio        = p_task->prio;
    
	/*  ptask   */
	p_task_info->ptask       = p_task->ptask;


    /*  stack usage   */
	U32 stackSize, currAddr, endAddr;
	U32 *sEnd;

    // stack size
	stackSize = p_task->priv_stack >> 2;
    if(stackSize == 0)
		stackSize = (U16)os_stackinfo >> 2;

    // end address
	sEnd = &p_task->stack[stackSize];
	endAddr = (U32)sEnd;

    // current address  
	// to do if not running)
	currAddr = p_task->tsk_stack;

    p_task_info->stack_usage = (U32)(endAddr - currAddr)*100/(U16)osstackinfo;
	return OS_R_OK;



}


