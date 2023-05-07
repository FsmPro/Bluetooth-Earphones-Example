/** 
 * @file: stm_power_interrupt.c 
 * @project:  
 * @version: 0.01 
 
 * @author: John Doe 
 * @organization: Google 
 * @date: Sun May 7 2023 
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
 
/*----------------------------------- includes -----------------------------------*/ 

#include "stm_power_interrupt.h"
 
/*--------------------------------- user defines ---------------------------------*/ 

#define MIN_DEBOUNCE_PERIOD	500
#define PLAY_PAUSE_DELAY	1000
#define SHUTDOWN_DELAY	2000#define MAX_CONN_ERROR_RETRY	60
 
/*---------------------------------- variables -----------------------------------*/ 

static bool _global_conn_status;

static t_state_stm_power_interrupt state_stm_power_interrupt = STATE_0_STM_POWER_INTERRUPT;

/*---------------------------------- user code -----------------------------------*/ 

/*---------------------------------- headers -------------------------------------*/ 

static void stm_power_interrupt0(void);
static void init_power_interrupt(void);
static void play_pause_triggerred(void);
static void shutdown_event(void);
static void open_to_pair(void);
static void connected(void);


/*--------------------------- function definitions -------------------------------*/ 


/** 
 * @function description  States diagram initialization stm_power_interrupt 
 */ 
void stm_power_interruptInitialize(void) 
{	 
 	/* -- state variable initialization -- */ 
	state_stm_power_interrupt = STATE_0_STM_POWER_INTERRUPT; 
 	/* -- states machine initial cycle execution -- */ 
	stm_power_interrupt(); 
}
 
/** 
 * @function description  Main routine of the states diagram stm_power_interrupt 
   Calls theCorresponding function state. 
 */ 
void stm_power_interrupt(void) 
{
	switch(state_stm_power_interrupt){
 
		case STATE_0_STM_POWER_INTERRUPT: 
			stm_power_interrupt0();
			break;

		case STATE_STM_POWER_INTERRUPT_INIT_POWER_INTERRUPT:
			init_power_interrupt(); 
			break; 

		case STATE_STM_POWER_INTERRUPT_PLAY_PAUSE_TRIGGERRED:
			play_pause_triggerred(); 
			break; 

		case STATE_STM_POWER_INTERRUPT_SHUTDOWN_EVENT:
			shutdown_event(); 
			break; 

		case STATE_STM_POWER_INTERRUPT_OPEN_TO_PAIR:
			open_to_pair(); 
			break; 

		case STATE_STM_POWER_INTERRUPT_CONNECTED:
			connected(); 
			break; 

		default: 
			state_stm_power_interrupt = STATE_0_STM_POWER_INTERRUPT;
			break; 
	} 
}
 
/** 
 * @function description  Function that returns the current state of the FSM stm_power_interrupt 
 */ 
t_state_stm_power_interrupt stm_power_interruptGetState(void) 
{ 
	return state_stm_power_interrupt; 
}
 

/** 
 * @function description:  function corresponding to the initial state of stm_power_interrupt 
 */ 
static void stm_power_interrupt0(void) 
{
	state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_INIT_POWER_INTERRUPT;
}

/** 
 * @function description   
 */ 
static void init_power_interrupt(void) 
{
	/* -- code of the current state -- */ 
	if((true == powerButtonStatus) && (getPressInterval() > MIN_DEBOUNCE_PERIOD)) 
	{ 
	    int btn_press_duration = getPressInterval();
	}

	/* -- case where transition Play Pause event triggered by the user is executed  -- */
	if (btn_press_duration <= PLAY_PAUSE_DELAY)
	{
		
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_PLAY_PAUSE_TRIGGERRED;
	}

	/* -- case where transition Shutdown event triggered by the user is executed  -- */
	else if (btn_press_duration <= SHUTDOWN_DELAY)
	{
		
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_SHUTDOWN_EVENT;
	}

	/* -- case where transition Transition to pair a new device is executed  -- */
	else if (btn_press_duration > SHUTDOWN_DELAY)
	{
		
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_OPEN_TO_PAIR;
	}

}

/** 
 * @function description   
 */ 
static void play_pause_triggerred(void) 
{
	/* -- code of the current state -- */ 
	/* Call Bluetooth interface function for play/pause button 
	pressed to perform respective funtion on the hardware level */
	
	ble_play_trigger();

	/* -- case where transition Default transition back to the initial state is executed  -- */
	if(true)
	{
		
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_INIT_POWER_INTERRUPT;
	}

}

/** 
 * @function description   
 */ 
static void shutdown_event(void) 
{
	/* -- code of the current state -- */ 
	/* Call bluetooth interface functions to shutdown 
	the device */
	
	enable_playback(false);
	clearCache();
	reset_connection();
	ble_shutdown();

}

/** 
 * @function description   
 */ 
static void open_to_pair(void) 
{
	/* -- code of the current state -- */ 
	bool local_conn_status = false;
	
	/* Let other devices know that earphones is available for pairing */
	broadcast_as_available();
	
	if (true == request_rx()){
	    unsigned long long int req_addr = getReqDevAddress();
	    local_conn_status = attempt_conn(req_addr);
	}

	/* -- case where transition Case when connection with the requestor device is successful is executed  -- */
	if (true == local_conn_status)
	{
		add_new_device(req_addr);
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_CONNECTED;
	}

}

/** 
 * @function description   
 */ 
static void connected(void) 
{
	/* -- code of the current state -- */ 
	static int err_counter = 0;
	if(false == _global_conn_status)
	{
	    _global_conn_status = true;
	    enable_playback(true);
	}
	
	/* Checking for error in connection here */
	if(true == error_occurred()){
	    err_counter++;
	}
	

	/* -- case where transition Connection error confirmed is executed  -- */
	if (err_counter > MAX_CONN_ERROR_RETRY)
	{
		_global_conn_status = false;
		enable_playback(false);
		/* -- state is changed -- */ 
		state_stm_power_interrupt = STATE_STM_POWER_INTERRUPT_INIT_POWER_INTERRUPT;
	}

}

