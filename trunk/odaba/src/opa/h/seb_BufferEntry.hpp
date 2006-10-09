/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_BufferEntry

\brief    


\date     $Date: 2006/03/12 19:14:14,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_BufferEntry_HPP
#define   eb_BufferEntry_HPP

class     eb_BufferEntry;

#define  BUFKEY_LEN                                sizeof(void *)
#define  BUFKEY_POS                                17
#define  BUFKEY_TYP                                'P'
#define  EBKEY_LEN                                 sizeof(EB_Number)
#define  EBKEY_POS                                 9
#define  EBKEY_TYP                                 'C'
#define  TEMPKEY_LEN                               2
#define  TEMPKEY_POS                               5
#define  TEMPKEY_TYP                               'I'
#pragma pack(8)

class  eb_BufferEntry
{
protected  :         int32                                        length;                                                    //
protected  :         int32                                        temp_index;                                                //
protected  :         uint64                                       eb_position;                                               //
protected  :         void                                        *buffer_pointer;                                            //

public     :
                     int32                                        get_length() { return(length); }
                     uint64                                       get_eb_position() { return(eb_position); }
                     void                                        *get_buffer_pointer() { return(buffer_pointer); }
public     :                                     logical IsModified ( ){

  return ( temp_index ? YES : NO );

}

public     :                                     void ResetModified ( ){

  temp_index = NO;

}

public     :                                     void SetAreaPointer (void *area ){

  buffer_pointer = area;

}

public     :                                     void SetIndex (int16 short_indx0 ){

  temp_index = short_indx0;

}

public     :                                     void SetLength (int32 odblen ){

  length = odblen;

}

public     :                                     void SetModified ( ){

  temp_index = YES;

}

public     :                                     void SetPosition (EB_Number entnr ){

  eb_position = entnr.get_ebsnum();

}

};

#pragma pack()
#endif
