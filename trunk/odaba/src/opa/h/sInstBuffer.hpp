/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstBuffer

\brief    


\date     $Date: 2006/03/12 19:13:24,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InstBuffer_HPP
#define   InstBuffer_HPP

class     InstBuffer;

#ifndef   DPA_inti_HPP
#define   DPA_inti_HPP
#include  <sinti.hpp>
#include  <sDPA.h>
#endif
class     bnode;
class     inti;
class     node;
#include  <sStatistic.hpp>
#pragma pack(8)

class  InstBuffer
{
protected  :         int32                                        buf_count;                                                 
protected  :         DPA(inti)                                    inti_array;                                                
protected  :         bnode                                       *node_ref;                                                  
protected  :         int32                                        startpos;                                                  
protected  :         int32                                        lastpos;                                                   
protected  :         int32                                        curpos;                                                    
protected  :         int32                                        last_abspos;                                               
protected  :         Statistic                                    stats;                                                     
protected  :         int32                                        count;                                                     
protected  :         logical                                      backward;                                                  
protected  :         logical                                      eof;                                                       

public     :
                     int32                                        get_buf_count() { return(buf_count); }
                     DPA(inti)                                   &get_inti_array() { return(inti_array); }
                     bnode                                       *get_node_ref() { return(node_ref); }
                     int32                                        get_startpos() { return(startpos); }
                     int32                                        get_lastpos() { return(lastpos); }
                     int32                                        get_curpos() { return(curpos); }
                     int32                                        get_last_abspos() { return(last_abspos); }
                     Statistic                                   &get_stats() { return(stats); }
                     logical                                      get_backward() { return(backward); }
                     logical                                      get_eof() { return(eof); }
public     :                                     logical Cancel ( );
public     :                                     logical Fill (int32 indx0 );
public     :                                     void *Get (int32 lindx0, int16 direction );
public     :                                     void *Get (char *skey, int16 direction );
public     :                                     int32 GetBackward (int32 lindx0, int16 direction );
public     :                                     int32 GetForeward (int32 lindx0, int16 direction );
public     :                                     int32 GetLastPos ( );
public     :                                                             InstBuffer (int32 max_inst, bnode *bnode_ptr );
public     :                                     logical Locate (int32 indx0 );
public     :                                     int32 Read (int32 lindx0, int16 direction );
public     :                                     int32 ReadBackward ( );
public     :                                     int32 ReadForeward ( );
public     :                                     logical SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                                             ~InstBuffer ( );
};

#pragma pack()
#endif
