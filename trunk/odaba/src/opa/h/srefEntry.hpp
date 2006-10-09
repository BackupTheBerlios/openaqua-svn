/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refEntry

\brief    


\date     $Date: 2006/03/12 19:15:02,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   refEntry_HPP
#define   refEntry_HPP

class     refEntry;

class     ref;
#pragma pack(8)

class  refEntry
{
protected  :         char                                         ref_name[40];                                              //
protected  :         ref                                         *ref_pointer;                                               //

public     :
                     char                                        *get_ref_name() { return(ref_name); }
                     ref                                         *get_ref_pointer() { return(ref_pointer); }
public     :                                                             refEntry (char *indxnam, ref *refptr );
public     :                                                             refEntry (ref *refptr );
};

#pragma pack()
#endif
