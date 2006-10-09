/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    MemberInfo

\brief    Information about a group of properties
          The  properties of an internal data structure representation in ODABA2
          are grouped as follows:
          	ab BaseStructures
          	ab Attributes
          	ab References
          	ab Relationships
          The  class  MemberInfo  provides  information  about  such  a group as
          number  of properties in  the group and  offset of the data within the
          internal and external data area.

\date     $Date: 2006/06/05 13:22:43,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   MemberInfo_HPP
#define   MemberInfo_HPP

class     MemberInfo;

#pragma pack(8)

class  MemberInfo
{
protected  :         int16                                        count;                                                     // 
protected  :         uint32                                       int_position;                                              // 
protected  :         uint32                                       ext_position;                                              // 

public     :
                     uint32                                       get_ext_position() { return(ext_position); }
public     :                                             MemberInfo (int16 mcount );
public     :                                        void SetPosition (int32 &intpos, int32 &extpos );
public     :                  OPAImpExp             int32 get_count ( );
public     :                  OPAImpExp             uint32 get_int_position ( );
public     :                  OPAImpExp             int16 inc_count ( );
public     :                  OPAImpExp             int16 set_count (int16 memcnt );
};

#pragma pack()
#endif
