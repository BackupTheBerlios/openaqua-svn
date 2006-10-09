/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_Description

\brief    Language Depending Section of a Description
          This  structure contains  all the  language depending information of a
          description.  It  does  not  contain  information  about  the document
          structure (because this is not language depending).

\date     $Date: 2006/03/13 21:30:06,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_Description_HPP
#define   DSC_Description_HPP

class     DSC_Description;

#pragma pack(8)

class  DSC_Description
{
protected  :         PI(mem)                                      characteristic;                                            // Characteristic of the Described Object
protected  :         PI(mem)                                      example;                                                   // Example for the Described Fact or Concept
protected  :         PI(mem)                                      notes;                                                     // Notes for definition
protected  :         PI(mem)                                      others;                                                    // Other information

public     :
                     PI(mem)                                     &get_characteristic() { return(characteristic); }
                     PI(mem)                                     &get_example() { return(example); }
                     PI(mem)                                     &get_notes() { return(notes); }
                     PI(mem)                                     &get_others() { return(others); }
};

#pragma pack()
#endif
