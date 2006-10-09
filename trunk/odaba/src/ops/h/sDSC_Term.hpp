/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_Term

\brief    Term
          Terms  are  words  used  to  refer  to concepts or facts of importance
          within  a certain context. Different terms (synonyms) may refer to the
          same concept. Synonyms and concepts are special terms.

\date     $Date: 2006/03/13 21:30:07,04 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_Term_HPP
#define   DSC_Term_HPP

class     DSC_Term;

#ifndef   P_DSC_Concept_HPP
#define   P_DSC_Concept_HPP
#include  <sPI.hpp>
class       DSC_Concept;
PI_dcl     (DSC_Concept)
#endif
#ifndef   P_DSC_Term_HPP
#define   P_DSC_Term_HPP
#include  <sPI.hpp>
class       DSC_Term;
PI_dcl     (DSC_Term)
#endif
#include  <cTermTypes.h>
#include  <sDSC_TermDef.hpp>
#pragma pack(8)

class  DSC_Term :public __OBJECT
{
protected  :         int32                                        __AUTOIDENT ATTR_ALIGN(4);                                 // Unique term number
protected  :         DSC_TermDef                                  definition;                                                // Name of Term
protected  :         TermTypes                                    type;                                                      // Type the Term is referred as
protected  :         PI(DSC_Concept)                              concept;                                                   // Concept definition
protected  :         PI(DSC_Term)                                 details;                                                   // Details defining a term
protected  :         PI(DSC_Term)                                 type_ref;                                                  // Special Type the Term is used as

public     :
                     int32                                        get___AUTOIDENT() { return(__AUTOIDENT); }
                     DSC_TermDef                                 &get_definition() { return(definition); }
                     TermTypes                                    get_type() { return(type); }
                     PI(DSC_Concept)                             &get_concept() { return(concept); }
                     PI(DSC_Term)                                &get_details() { return(details); }
                     PI(DSC_Term)                                &get_type_ref() { return(type_ref); }
};

#pragma pack()
#endif
