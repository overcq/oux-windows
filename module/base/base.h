//-*-C-*-
/*******************************************************************************
*   ___   publicplace
*  ¦OUX¦  C+
*  ¦/C+¦  component
*   ---   base
*         global defines
* ©overcq                on "Gentoo Linux 13.0” “x86_64”              2015-7-6 *
*******************************************************************************/
extern I _X_var( flow, call_req );
extern I _X_var( io, stream_write );
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern void E_flow_Q_process_call_I_func(P);
//==============================================================================
#define E_mem_Q_blk_S_allocated_S_mapped_id     ( E_base_S->E_mem_Q_blk_S_table_allocated_id - 3 )
#define E_mem_Q_blk_S_allocated_S_decommited_id ( E_base_S->E_mem_Q_blk_S_table_allocated_id - 2 )
#define E_mem_Q_blk_S_allocated_S_free_id       ( E_base_S->E_mem_Q_blk_S_table_allocated_id - 1 )
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct E_flow_Z_args
{ N argc;
  Pc *argv;
};
/******************************************************************************/
