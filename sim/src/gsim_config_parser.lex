%{
/* 
 * _GSIM_CONFIG_PARSER_LEX_
 *
 * PARSER LEX DRIVER 
 *  
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "goblin_sim.h"

enum {
	LOOKUP = 0, 
	VECTOR = 1, 
	GLOBAL_ADDR = 2, 
	TASK_GROUPS = 3, 
	TASK_PROCS = 4, 
	TASKS = 64
};

int state;
int gsim_config_func( int type, char *word );
uint32_t *__vector;
uint32_t *__global_addr;
uint32_t *__task_groups;
uint32_t *__task_procs;
uint32_t *__tasks;
%}

%option nounput
%option noyywrap

%%
\n			{	state = LOOKUP;	}
^VECTOR			{ 	state = VECTOR; }
^GLOBAL_ADDR		{ 	state = GLOBAL_ADDR; }
^TASK_GROUPS		{ 	state = TASK_GROUPS; }
^TASK_PROCS		{ 	state = TASK_PROCS; }
^TASKS			{ 	state = TASKS; }
[a-zA-Z0-9\/.-_]+	{ if( state != LOOKUP ) gsim_config_func( state, yytext ); }
. ;
%%

extern int gsim_config_func_parser( 	uint32_t *vector, uint32_t *global_addr, 
					uint32_t *task_groups, uint32_t *task_procs, 
					uint32_t *tasks, char *cfile )
{
	__vector	= vector;
	__global_addr	= global_addr;
	__task_groups	= task_groups;
	__task_procs	= task_procs;
	__tasks		= tasks;

	yyin = fopen( cfile, "r" );
	
	yylex();

	fclose( yyin );
	yyin = NULL;

	return 0;
}

int gsim_config_func( int type, char *word )
{
	switch( type )
	{
		case VECTOR : 
			*__vector = (uint32_t)(atoi( word ));
			break;
		case GLOBAL_ADDR:
			*__global_addr = (uint32_t)(atoi( word ));
			break;
		case TASK_GROUPS:
			*__task_groups = (uint32_t)(atoi( word ));
			break;
		case TASK_PROCS:
			*__task_procs = (uint32_t)(atoi( word ));
			break;
		case TASKS:
			*__tasks = (uint32_t)(atoi( word ));
			break;
		default:
			break;
	}

	return 0;
}
