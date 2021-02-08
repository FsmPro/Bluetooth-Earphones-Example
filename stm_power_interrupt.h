/** 
 * @file: stm_power_interrupt.h 
 * @project:  
 * @version: 1.02 
 
 * @author: John Doe 
 * @organization: Google LLC 
 * @date: Sun Feb 7 2021 
 * @description: Automatic codification of state machine stm_power_interrupt 
 * 
 * Number of States: 5
 * Number of Transitions: 6 
 * Input variables: 0 
 * Output variables: 0 
 * local variables : 1 
 * 
 *  
 */
 
#ifndef _STM_POWER_INTERRUPT_H
#define _STM_POWER_INTERRUPT_H
 
/*--------------------------------- user includes ---------------------------------*/ 
#include "ble_interface.h"
 
/*------------------------------ global declarations ------------------------------*/ 

typedef enum { 
 	STATE_STM_POWER_INTERRUPT_INIT_POWER_INTERRUPT = 0,
	STATE_STM_POWER_INTERRUPT_PLAY_PAUSE_TRIGGERRED = 1,
	STATE_STM_POWER_INTERRUPT_SHUTDOWN_EVENT = 2,
	STATE_STM_POWER_INTERRUPT_OPEN_TO_PAIR = 3,
	STATE_STM_POWER_INTERRUPT_CONNECTED = 4,
	STATE_0_STM_POWER_INTERRUPT = 5,
	}t_state_stm_power_interrupt;
 
/*----------------------------- function declarations -----------------------------*/ 

/** 
 * @function description  States diagram initialization stm_power_interrupt 
 */ 
 void stm_power_interruptInitialize(void);
 
/** 
 * @function description  Main routine of the states diagram stm_power_interrupt 
 Calls theCorresponding function state. 
 */ 
 void stm_power_interrupt(void);
 
/** 
 * @function description  Function that returns the current state of the FSM stm_power_interrupt 
 */ 
t_state_stm_power_interrupt stm_power_interruptGetState(void);
 
#endif /* _STM_POWER_INTERRUPT_H */