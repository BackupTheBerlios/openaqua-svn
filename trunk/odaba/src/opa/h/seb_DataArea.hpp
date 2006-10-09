/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    eb_DataArea

\brief    


\date     $Date: 2006/06/25 16:17:33,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_DataArea_HPP
#define   eb_DataArea_HPP

class     eb_DataArea;

class     EBDataArea;
class     EB_DAHeader;
class     EB_Header;
#pragma pack(8)

class  eb_DataArea
{
protected  :         EB_DAHeader                                 *da_header;                                                 // 
protected  :         int16                                        file_handle;                                               // 
protected  :         int16                                        da_number;                                                 // 
protected  :         logical                                      access_opt;                                                // 
protected  :         logical                                      net_opt;                                                   // 

public     :
                     EB_DAHeader                                 *get_da_header() { return(da_header); }
                     int16                                        get_file_handle() { return(file_handle); }
                     int16                                        get_da_number() { return(da_number); }
                     logical                                      get_access_opt() { return(access_opt); }
                     logical                                      get_net_opt() { return(net_opt); }
public     :                                        int64 Append (int32 instlen, int32 length, void *area );
public     :                                        logical Check (uint64 position64, int32 length );
public     :                                        logical Close ( );
public     : static                                 logical __cdecl Exist (char *path, logical netopt, char chkopt=AUTO );
public     :                                        logical Flush ( );
public     : static                                 logical __cdecl InitFile (EB_Header *pheader, EBDataArea *defentry, uint16 len );
public     :                                        logical Lock (uint64 position64, int32 length, logical wait );
public     :                                        logical Open (EB_DAHeader *pdaheader, char *path, logical outopt, logical netopt );
public     :                                        logical Read (uint64 position64, int32 length, void *area );
public     : static                                 logical __cdecl ReadCheck (int16 filehandle, int32 length, void *area );
public     :                                        logical ResetSize ( );
public     :                                        void SetDynamic ( );
public     :                                        logical SetNetOpt (logical netopt );
public     :                                        logical TraceLock (uint64 position64, logical lock_opt );
public     :                                        logical Unlock (uint64 position64, int32 length );
public     :                                        logical Write (uint64 position64, int32 length, void *area );
public     :                                        logical WriteNull (uint64 position64, int32 length );
public     :                                             eb_DataArea ( );
public     :                                             ~eb_DataArea ( );
};

#pragma pack()
#endif
