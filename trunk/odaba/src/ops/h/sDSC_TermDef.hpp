/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_TermDef

\brief    Definition for term or concept
          Terms  are used to refer to concepts or phenomena of the real world by
          means  of  names.  Those  names  can  be  considered  as references to
          complex concepts or phenomena described in the term definition.

\date     $Date: 2006/03/13 21:30:07,14 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_TermDef_HPP
#define   DSC_TermDef_HPP

class     DSC_TermDef;

#include  <cLanguage.h>
#include  <sDSC_Description.hpp>
#pragma pack(8)

class  DSC_TermDef
{
protected  :         Language                                     language;                                                  // Language for Names and Labels
protected  :         char                                         name[40];                                                  // String Defining the Name
protected  :         char                                         abbreviation[10];                                          // Abbreviation for the Name
protected  :         DSC_Description                              definition;                                                // Term definition

public     :
                     Language                                     get_language() { return(language); }
                     char                                        *get_name() { return(name); }
                     char                                        *get_abbreviation() { return(abbreviation); }
                     DSC_Description                             &get_definition() { return(definition); }
};

#pragma pack()
#endif
