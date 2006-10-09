/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_MBHeader

\brief    


\date     $Date: 2006/03/12 19:13:16,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_MBHeader_HPP
#define   EB_MBHeader_HPP

class     EB_MBHeader;

class     EBI;
class     acb;
class     eb_SubBase;
#include  <sEB_Number.hpp>
#include  <sEB_SBHeader.hpp>
#pragma pack(8)

class  EB_MBHeader :public EB_SBHeader
{
public     :         uint64                                      *ebi_buffer[5] ATTR_ALIGN(4);                               
protected  :         bit                                          ebi_buffer_mod: 3;                                         
protected  :         bit                                          lebi_buffer_mod: 1;                                        
protected  :         EBI                                         *low_ebi_buffer;                                            

public     :
                     bit                                          get_ebi_buffer_mod() { return(ebi_buffer_mod); }
                     bit                                          get_lebi_buffer_mod() { return(lebi_buffer_mod); }
                     EBI                                         *get_low_ebi_buffer() { return(low_ebi_buffer); }
public     :                                     void Close (eb_SubBase *odbptr );
public     :                                                             EB_MBHeader (uint16 len, logical netopt );
public     :                                     int64 GetEBIPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number entnum, logical provide );
public     :                                     int64 GetEBIoPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number entnum, logical provide );
public     :                                     int64 GetNextEBIPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number &entnr_ref );
public     :                                     int64 GetNextEBNumber (eb_SubBase *odbptr, EB_Number &entnr_ref );
public     :                                     logical Open ( );
public     :                                     int64 PutEBI (eb_SubBase *odbptr, int16 lev, EB_Number entnum );
public     :                                     uint64 ReadBuffer (eb_SubBase *odbptr, uint64 position64, uint64 *pos_buffer, int32 count );
public     : virtual                             logical Reset ( );
public     :                                     logical SaveBuffer (eb_SubBase *odbptr, int16 lev );
public     :                                     logical UpdateBuffer (eb_SubBase *odbptr, uint64 position64, uint64 *pos_buffer, int32 count );
public     :                                     logical Version1 (eb_SubBase *odbptr );
public     :                                     logical Version2 (eb_SubBase *odbptr );
public     :                                     logical Version3 (eb_SubBase *odbptr );
public     :                                     logical ebshigt (eb_SubBase *odbptr, acb *acbptr );
public     :                                     logical ebshilk (eb_SubBase *odbptr, acb *acbptr, logical wait );
public     :                                     uint64 ebshipg (int16 lev );
public     :                                     logical ebshipp (eb_SubBase *odbptr, acb *acbptr, logical provide );
public     :                                     void ebships (uint64 idxptr, int16 lev );
public     :                                     logical ebshipt (eb_SubBase *odbptr, acb *acbptr );
public     :                                     logical ebshiul (eb_SubBase *odbptr, acb *acbptr );
public     :                                     EB_Number ebshngt (eb_SubBase *odbptr );
public     :                                     void SetLastNum (int64 lastnr ){

  set_last_EBS_num(MAX(lastnr,get_last_EBS_num().get_ebsnum()));

}

};

#pragma pack()
#endif
