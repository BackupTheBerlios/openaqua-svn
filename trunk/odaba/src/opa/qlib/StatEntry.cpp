/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    StatEntry

\brief    


\date     $Date: 2006/03/12 19:18:11,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "StatEntry"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sacb.hpp>
#include  <seb_MainBase.hpp>
#include  <sStatEntry.hpp>


/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical StatEntry :: IsEmpty ( )
{

  return(inst_count+index_count+del_count+del_index_count == 0);

}

/******************************************************************************/
/**
\brief  Print - 


\return term - Termination code

\param  statfile -
\param  line -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical StatEntry :: Print (FILE *statfile, char *line )
{
  logical                 term = NO;

  gvtxltp((char *)memcpy(line,"ZZZZZZZZ9",9),inst_count,9);
  gvtxltp((char *)memcpy(line+10,"ZZZZZZZZ9",9),inst_size,9);
  gvtxltp((char *)memcpy(line+20,"ZZZZZZZZ9",9),del_count,9);
  gvtxltp((char *)memcpy(line+30,"ZZZZZZZZ9",9),del_size,9);
  gvtxltp((char *)memcpy(line+40,"ZZZZZZZZ9",9),index_count,9);
  gvtxltp((char *)memcpy(line+50,"ZZZZZZZZ9",9),index_size,9);
  gvtxltp((char *)memcpy(line+60,"ZZZZZZZZ9",9),del_index_count,9);
  gvtxltp((char *)memcpy(line+70,"ZZZZZZZZ9",9),del_index_size,9);
  gvtxltp((char *)memcpy(line+80,"ZZZZZZZZ9",9),hist_count,9);
  gvtxltp((char *)memcpy(line+90,"ZZZZZZZZ9",9),hist_size,9);

  return(term);
}

/******************************************************************************/
/**
\brief  StatEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StatEntry"

                        StatEntry :: StatEntry ( )
                     : inst_count(0),
  inst_size(0),
  index_count(0),
  index_size(0),
  del_count(0),
  del_size(0),
  del_index_count(0),
  del_index_size(0),
  hist_count(0),
  hist_size(0)
{



}

/******************************************************************************/
/**
\brief  Update - 


\return term - Termination code

\param  acbptr -
\param  hcount
\param  hsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical StatEntry :: Update (acb *acbptr, uint32 hcount, uint32 hsize )
{
  logical                 term    = NO;
  switch ( 2*acbptr->stscdel() + (acbptr->get_acbieh().get_iehtyp() == IDB_INS) )
  {
    case  0 : index_count++;
              index_size += acbptr->get_entry_length();
              break;
    case  1 : inst_count++;
              inst_size += acbptr->get_entry_length();
              break;
    case  2 : del_index_count++;
              del_index_size += acbptr->get_entry_length();
              break;
    case  3 : del_count++;
              del_size += acbptr->get_entry_length();
              break;
    default : ;
  }
  hist_count += hcount;
  hist_size  += hsize;
  return(term);
}

/******************************************************************************/
/**
\brief  operator+=

\return st_entry

\param  st_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

StatEntry &StatEntry :: operator+= (StatEntry &st_entry )
{

  inst_count      += st_entry.get_inst_count();
  inst_size       += st_entry.get_inst_size();
  index_count     += st_entry.get_index_count();
  index_size      += st_entry.get_index_size();
  del_count       += st_entry.get_del_count();
  del_size        += st_entry.get_del_size();
  del_index_count += st_entry.get_del_index_count();
  del_index_size  += st_entry.get_del_index_size();
  hist_count      += st_entry.get_hist_count();
  hist_size       += st_entry.get_hist_size();

  return(*this);
}


