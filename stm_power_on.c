/** 
 * @file: stm_power_on.c 
 * @project:  
 * @version: 0.01 
 
 * @author: John Doe 
 * @organization: Google 
 * @date: Sun May 7 2023 
 * @description: Automatic codification of state machine stm_power_on 
 * 
 * Number of States: 4
 * Number of Transitions: 6 
 * Input variables: 0 
 * Output variables: 0 
 * local variables : 2 
 * 
 *  
 */
 
/*----------------------------------- includes -----------------------------------*/ 

#include "stm_power_on.h"
 
/*--------------------------------- user defines ---------------------------------*/ 

#define MAX_CONN_ERROR_RETRY	60 
 
/*---------------------------------- variables -----------------------------------*/ 

static unsigned_long_long_int _prev_addr;
static bool _global_conn_status;

static t_state_stm_power_on state_stm_power_on = STATE_0_STM_POWER_ON;

/*---------------------------------- user code -----------------------------------*/ 

/*---------------------------------- headers -------------------------------------*/ 

static void stm_power_on0(void);
static void attempt_connection(void);
static void power_on(void);
static void open_to_connect(void);
static void connected(void);


/*--------------------------- function definitions -------------------------------*/ 


/** 
 * @function description  States diagram initialization stm_power_on 
 */ 
void stm_power_onInitialize(void) 
{	 
 	/* -- state variable initialization -- */ 
	state_stm_power_on = STATE_0_STM_POWER_ON; 
 	/* -- states machine initial cycle execution -- */ 
	stm_power_on(); 
}
 
/** 
 * @function description  Main routine of the states diagram stm_power_on 
   Calls theCorresponding function state. 
 */ 
void stm_power_on(void) 
{
	switch(state_stm_power_on){
 
		case STATE_0_STM_POWER_ON: 
			stm_power_on0();
			break;

		case STATE_STM_POWER_ON_ATTEMPT_CONNECTION:
			attempt_connection(); 
			break; 

		case STATE_STM_POWER_ON_POWER_ON:
			power_on(); 
			break; 

		case STATE_STM_POWER_ON_OPEN_TO_CONNECT:
			open_to_connect(); 
			break; 

		case STATE_STM_POWER_ON_CONNECTED:
			connected(); 
			break; 

		default: 
			state_stm_power_on = STATE_0_STM_POWER_ON;
			break; 
	} 
}
 
/** 
 * @function description  Function that returns the current state of the FSM stm_power_on 
 */ 
t_state_stm_power_on stm_power_onGetState(void) 
{ 
	return state_stm_power_on; 
}
 

/** 
 * @function description:  function corresponding to the initial state of stm_power_on 
 */ 
static void stm_power_on0(void) 
{
	state_stm_power_on = STATE_STM_POWER_ON_POWER_ON;
}

/** 
 * @function description   
 */ 
static void attempt_connection(void) 
{
	/* -- code of the current state -- */ 
	/* Try to connect with the previously paired device */
	bool connect_status = attempt_conn(prev_addr);
	

	/* -- case where transition Case when the connection fails is executed  -- */
	if false == connect_status
	{
		
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_OPEN_TO_CONNECT;
	}

	/* -- case where transition Case when the connection succeeds is executed  -- */
	else if true == connect_status
	{
		
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_CONNECTED;
	}

}

/** 
 * @function description   
 */ 
static void power_on(void) 
{
	/* -- code of the current state -- */ 
	/* Attempt to connect to a previously paired device */
	
	prev_addr = getPrevDevAddress();

	/* -- case where transition Case when the previously connected device is available for connection is executed  -- */
	if (prev_addr != 0) && (true == isDeviceAvailable(prev_addr))
	{
		
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_ATTEMPT_CONNECTION;
	}

	/* -- case where transition Case when no previously paired device was found is executed  -- */
	else if (prev_addr == 0) || (false == isDeviceAvailable(prev_addr))
	{
		
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_OPEN_TO_CONNECT;
	}

}

/** 
 * @function description   
 */ 
static void open_to_connect(void) 
{
	/* -- code of the current state -- */ 
	bool local_conn_status = false;
	
	/* Let other paired devices know that earphones is available for pairing */
	broadcast_as_available();
	
	if (true == request_rx()){
	    unsigned long long int req_addr = getReqDevAddress();
	    local_conn_status = attempt_conn(req_addr);
	}

	/* -- case where transition Case when connection with the requestor device is successful is executed  -- */
	if (true == local_conn_status)
	{
		
		
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_CONNECTED;
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
	

	/* -- case where transition Connection error confirmed  is executed  -- */
	if (err_counter > MAX_CONN_ERROR_RETRY)
	{
		_global_conn_status = false;
		enable_playback(false);
		/* -- state is changed -- */ 
		state_stm_power_on = STATE_STM_POWER_ON_OPEN_TO_CONNECT;
	}

}

