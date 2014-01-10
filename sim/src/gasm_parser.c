/* 
 * 
 * _GASM_PARSER_C_ 
 * 
 * GASM ASM PARSERS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "goblin_sim.h"
#include "goblin_sim_optable.h"

/* -------------------------------------------------- GASM_PARSER_REMOVE_NEWLINE */
/* 
 * GASM_PARSER_REMOVE_NEWLINE
 * 
 */
static void gasm_parser_remove_newline( char *buf )
{
	char *ptr = NULL;
	
	if ((ptr=strchr( buf, '\n')) != NULL ){ 
		*ptr = '\0';
	}
}

/* -------------------------------------------------- GASM_PARSER */
/* 
 * GASM_PARSER
 * 
 */
extern uint64_t gasm_parser( char *afile, uint64_t *inter, uint64_t nrows, int *error )
{
	/* vars */
	FILE *ifile	= NULL;
	char *buf	= NULL;
	char *tokbuf	= NULL;
	char tokstr[]	= " ,";
	uint64_t insts	= 0x00ll;
	uint64_t tmp	= 0x00ll;
	int imm		= 0;
	uint64_t line	= 0;
	int i		= 0;
	char inst[16];
	char arg1[16]; 
	char arg2[16]; 
	char arg3[16]; 
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * open the file 
	 */
	ifile	= fopen( afile, "r" );	
	if( ifile == NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : Could not open assembly file" );
		return 0x00ll;
	}

	/* 
	 * rewind the file 
	 */
	rewind( ifile );

	buf = gsim_malloc( sizeof( char ) * 2048 );
	memset( buf, 0, sizeof( char ) * 2048 );

	/* 
	 * Parse the file
	 */
	while( !feof( ifile ) ){
	
		fgets( buf, 2048, ifile );

		if( (strlen( buf ) > 2 ) && (buf[0] != '#') ){ 

			/* remove newline */
			gasm_parser_remove_newline( buf );		

			/* 
			 * this buffer is an instruction 
			 * 
			 * - tokenize the buffer 
			 * - examine the instruction
			 * - determine the arg types 
			 * - assemble the payload
			 */
	
			tokbuf	= strtok( buf, tokstr );	
			while( tokbuf != NULL ){ 

				switch( i )
				{
					case 0:
						/* instruction mneumonic */
						sprintf( inst, "%s", tokbuf );
						break;
					case 1:
						/* arg1 */
						sprintf( arg1, "%s", tokbuf );
						break;
					case 2:
						/* arg2 */
						sprintf( arg2, "%s", tokbuf );
						break;
					case 3:
						/* arg3 */
						sprintf( arg3, "%s", tokbuf );
						break;
					default:
						printf( "gasm: Error parsing assembly file at line %" PRIu64 "\n",
								line );
						printf( "\t>%s\n", buf );
						fflush( stdout );
						free( buf );
						fclose( ifile );
						*error = -1;
						return 0x01;
						break;
				}	

				i++;
				tokbuf = strtok( NULL, tokstr );	
			}
		}

		memset( buf,  0, sizeof( char ) * 2048 );
		memset( inst, 0, sizeof( char ) * 16 );
		memset( arg1, 0, sizeof( char ) * 16 );
		memset( arg2, 0, sizeof( char ) * 16 );
		memset( arg3, 0, sizeof( char ) * 16 );
		tokbuf	= NULL;

		imm 	= 0;
		i 	= 0;
		tmp 	= 0x00ll;
		line++;
		insts++;
	}

	/* 
	 * close the file
	 */
	fclose( ifile );	

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return insts;	
}


/* EOF */