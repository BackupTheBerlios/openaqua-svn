/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_Buffer

\brief    


\date     $Date: 2006/03/12 19:14:14,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_Buffer_HPP
#define   eb_Buffer_HPP

class     eb_Buffer;

#define  OBUF_MAX                                  100
class     eb_BufferEntry;
#include  <ssrt.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  eb_Buffer :public sts
{
protected  :         void                                        *ms_pool ATTR_ALIGN(4);                                     //
protected  :         void                                        *buffer_area;                                               //
protected  :         srt                                         *entry_table;                                               //
protected  :         int32                                        buffer_size;                                               //
protected  :         int32                                        current_position;                                          //
protected  :         int32                                        next_position;                                             //

public     :
                     void                                        *get_ms_pool() { return(ms_pool); }
                     void                                        *get_buffer_area() { return(buffer_area); }
                     srt                                         *get_entry_table() { return(entry_table); }
                     int32                                        get_buffer_size() { return(buffer_size); }
                     int32                                        get_current_position() { return(current_position); }
                     int32                                        get_next_position() { return(next_position); }
public     :                                     logical Add (int32 odblen, EB_Number entnr, void *area );
public     :                                     void *ChangeEntrySize (int32 newsize, EB_Number entnr );
public     :                                     logical Clear ( );
public     :                                     logical Compress ( );
public     :                                     logical Delete (EB_Number entnr );
public     :                                     void *Get (EB_Number entnr );
public     :                                     int16 GetEntryCount ( );
public     :                                     eb_BufferEntry *GetTableEntry (EB_Number entnr );
public     :                                     void *Initialize (int32 odblen, EB_Number entnr );
public     :                                     void *Locate (EB_Number entnr );
public     :                                     logical LowPriorityDel ( );
public     :                                     void Remove (void *area );
public     :                                     logical Update (int32 odblen, EB_Number entnr, void *area );
public     :                                                             eb_Buffer (int32 maxbuf, logical expand=NO );
public     :                                                             ~eb_Buffer ( );
public     :                                     eb_BufferEntry *GetTableEntry (int16 indx ){


  return ( (eb_BufferEntry *)entry_table->srtigt(indx) );

}

};

#pragma pack()
#endif
