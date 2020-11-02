/** 
 * @file: stm_power_on.h 
 * @project:  
 * @version: 1.01 
 
 * @author: John Doe 
 * @organization: Google LLC 
 * @date: Mon Nov 2 2020 
 * @description: Automatic codification of state machine stm_power_on 
 * 
 * Number of States: 4
 * Number of Transitions: 5 
 * Input variables: 0 
 * Output variables: 0 
 * local variables : 2 
 * 
 *  
 */
 
#ifndef _STM_POWER_ON_H
#define _STM_POWER_ON_H
 
/*--------------------------------- user includes ---------------------------------*/ 
#include "ble_interface.h"
 
/*------------------------------ global declarations ------------------------------*/ 

typedef enum { 
 	STATE_STM_POWER_ON_ATTEMPT_CONNECTION = 0,
	STATE_STM_POWER_ON_POWER_ON = 1,
	STATE_STM_POWER_ON_OPEN_TO_CONNECT = 2,
	STATE_STM_POWER_ON_CONNECTED = 3,
	STATE_0_STM_POWER_ON = 4,
	}t_state_stm_power_on;
 
/*----------------------------- function declarations -----------------------------*/ 

/** 
 * @function description  States diagram initialization stm_power_on 
 */ 
 void stm_power_onInitialize(void);
 
/** 
 * @function description  Main routine of the states diagram stm_power_on 
 Calls theCorresponding function state. 
 */ 
 void stm_power_on(void);
 
/** 
 * @function description  Function that returns the current state of the FSM stm_power_on 
 */ 
t_state_stm_power_on stm_power_onGetState(void);
 
#endif /* _STM_POWER_ON_H */