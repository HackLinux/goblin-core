/*
 * _GOBLIN_SIM_MACROS_H_
 * 
 * GOBLIN-SIM MACROS HEADER FILE 
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS USE THE TOP-LEVEL HEADER: 
 *          GOBLIN_SIM.H
 * 
 */


#ifndef	_GOBLIN_SIM_MACROS_H_
#define _GOBLIN_SIM_MACROS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* --------------------------------------------- VERSION MACROS */
#ifndef GSIM_MAJOR_VERSION
#define GSIM_MAJOR_VERSION	0
#endif

#ifndef GSIM_MINOR_VERSION
#define GSIM_MINOR_VERSION	1
#endif

#ifndef GSIM_SVN_VERSION
#define GSIM_SVN_VERSION	0000
#endif


/* --------------------------------------------- SIMULATION OPTION MACROS */
#define	GSIM_OPT_TRACING	0x0000000000000001	/*! RUNTIME OPTIONS: ENABLE TRACING */
#define GSIM_OPT_EXCEPTIONS	0x0000000000000002	/*! RUNTIME OPTIONS: ENABLE EXCEPTIONS */
#define GSIM_OPT_TASKING	0x0000000000000004	/*! RUNTIME OPTIONS: ENABLE TASKING */

#define	GSIM_OPT_CYCLE_FUNC	0x0000000000000008	/*! RUNTIME OPTIONS: ENABLE FUNCTIONAL SIM */
#define	GSIM_OPT_CYCLE_ACCUR	0x000000000000000F	/*! RUNTIME OPTIONS: ENABLE CYCLE ACCURATE CXX SIM */
#define	GSIM_OPT_CYCLE_HDL	0x0000000000000010	/*! RUNTIME OPTIONS: ENABLE VERILOG SIM */

#define GSIM_OPT_VALIDATE	0x0000000000000020	/*! RUNTIME OPTIONS: VALIDATE THE OBJECT */

#define GSIM_OPT_DEFAULT	(GSIM_OPT_EXCEPTIONS|GSIM_OPT_TASKING|GSIM_OPT_CYCLE_FUNC)

/* --------------------------------------------- PRINT MACROS */
#define	GSIM_PRINT_ERROR( s )		( fprintf( stderr, "GSIM_ERROR: %s:%d : %s\n", __FUNCTION__, __LINE__, s ) )
#define	GSIM_PRINT_MSG( s )		( fprintf( stdout, "GSIM_MSG: %s:%d : %s\n", __FUNCTION__, __LINE__, s ) )
#define	GSIM_PRINT_FUNC_ENTRY( )	( fprintf( stdout, "GSIM_FUNC_ENTRY: %s:%s\n", __FILE__, __FUNCTION__ ) )
#define	GSIM_PRINT_FUNC_EXIT( )		( fprintf( stdout, "GSIM_FUNC_EXIT : %s:%s\n", __FILE__, __FUNCTION__ ) )

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_MACROS_H_ */

/* EOF */