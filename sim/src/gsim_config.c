/* 
 * 
 * _GSIM_CONFIG_C_ 
 * 
 * GOBLIN-SIM CONFIG FILE INTERFACES
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- FUNCTION PROTOTYPES */
extern int gsim_config_func_parser(	uint32_t *vector, uint32_t *global_addr, 
					uint32_t *task_groups, uint32_t *task_procs, 
					uint32_t *tasks, char *cfile );

/* -------------------------------------------------- GSIM_CONFIG_READ */
/* 
 * GSIM_CONFIG_READ
 * 
 */
extern int gsim_config_read( struct gsim_t *sim )
{
#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* vars */
	uint32_t vector		= 0;
	uint32_t global_addr	= 0;
	uint32_t task_groups	= 0;
	uint32_t task_procs	= 0;
	uint32_t tasks		= 0;
	/* ---- */

	/* sanity check */
	if( sim == NULL ){ 
		return -1;
	}

	/* 
	 * call the parser generated by flex
	 * 
	 */
	if( gsim_config_func_parser(  	&vector, &global_addr, &task_groups, 
					&task_procs, &tasks, sim->config_file ) != 0 ) {
		return -1;
	}

	/* 
	 * global addressing option
	 *
	 */
	if( global_addr == 1 ){
		sim->options |= GSIM_OPT_GLOBAL_ADDR;
	}else if( (sim->options & GSIM_OPT_GLOBAL_ADDR) > 0 ){
		sim->options &= ~GSIM_OPT_GLOBAL_ADDR;
	}

	/* 
	 * vector
	 *
	 */
	if( vector == 1 ){
		sim->options |= GSIM_OPT_VECTOR;
	}else if( (sim->options & GSIM_OPT_VECTOR) > 0 ){ 
		sim->options &= ~GSIM_OPT_VECTOR;
	}

	sim->task_groups 	= task_groups;
	sim->task_procs		= task_procs;
	sim->tasks		= tasks;

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
