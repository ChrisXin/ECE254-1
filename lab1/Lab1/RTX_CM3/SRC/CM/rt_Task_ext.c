/**
* @file: rt_Task_ext.c
*/
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"



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
/* end of file */