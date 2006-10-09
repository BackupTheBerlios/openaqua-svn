/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ieh

\brief    


\date     $Date: 2006/03/12 19:14:25,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ieh_HPP
#define   ieh_HPP

class     ieh;

#define  IEH                                       sizeof(ieh)
#include  <sieh.hpp>
#pragma pack(4)

class  ieh
{
protected  :         uint32                                       iehlen;                                                    
protected  :         int16                                        iehsid;                                                    
protected  :         int8                                         iehtyp;                                                    
protected  :         int8                                         iehver;                                                    //

public     :
                     uint32                                       get_iehlen() { return(iehlen); }
                     int16                                        get_iehsid() { return(iehsid); }
                     int8                                         get_iehtyp() { return(iehtyp); }
                     int8                                         get_iehver() { return(iehver); }
public     :                                     ieh *Copy (ieh *iehptr );
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                                             ieh (int16 strid, int16 orgtyp );
public     :                                                             ieh ( );
public     :                                                             ieh (ieh &iehref );
public     :                                     void set_iehsid (int16 sid );
public     :                                     void set_iehver (uint16 version );
public     :                                     void set_iehlen (int32 instlen ){

  iehlen = instlen;

}

public     :                                     void set_iehtyp (char otype ){

  iehtyp = otype;

}

};

#pragma pack()
#endif
