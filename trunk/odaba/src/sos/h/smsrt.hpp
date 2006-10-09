/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    msrt



\date     $Date: 2006/03/12 19:20:53,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   msrt_HPP
#define   msrt_HPP

class     msrt;

class     acc;
class     kcb;
#include  <sksrt.hpp>
#pragma pack(8)

class  msrt :public ksrt
{
protected  :         char                                        *key1 ATTR_ALIGN(4);                                        
protected  :         char                                        *key2;                                                      
protected  :         logical                                      fill_opt1;                                                 
protected  :         logical                                      fill_opt2;                                                 
protected  :         int16                                        key_size;                                                  
protected  :         acc                                         *access;                                                    

public     :
                     char                                        *get_key1() { return(key1); }
                     char                                        *get_key2() { return(key2); }
                     logical                                      get_fill_opt1() { return(fill_opt1); }
                     logical                                      get_fill_opt2() { return(fill_opt2); }
                     int16                                        get_key_size() { return(key_size); }
                     acc                                         *get_access() { return(access); }
public     :         SOS7ImpExp                  int Compare (const void *entry1, const void *entry2 );
public     :         SOS7ImpExp                  logical FillKey (const void *entry1, int16 keynum );
public     :         SOS7ImpExp                                          msrt (kcb *kcbptr, int32 maxe, int16 elen, int16 klen, int16 kpos, logical expand );
public     :         SOS7ImpExp                                          ~msrt ( );
};

#pragma pack()
#endif
