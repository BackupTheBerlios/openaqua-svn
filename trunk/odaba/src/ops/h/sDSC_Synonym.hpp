/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_Synonym

\brief    Synonym
          A  synonym is a term that can be  defined as another word with more or
          less  the same meaning as the related concept. Each synonym is related
          to  exactly one  concept. As  a term  a synonym may have a description
          describing  the meaning of  the synonym and  the slight differences to
          the referenced concept.

\date     $Date: 2006/03/13 21:30:07,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_Synonym_HPP
#define   DSC_Synonym_HPP

class     DSC_Synonym;

#ifndef   P_DSC_Concept_HPP
#define   P_DSC_Concept_HPP
#include  <sPI.hpp>
class       DSC_Concept;
PI_dcl     (DSC_Concept)
#endif
#include  <sDSC_Term.hpp>
#pragma pack(8)

class  DSC_Synonym :public DSC_Term
{
protected  :         PI(DSC_Concept)                              term;                                                      // Concept the synonym is referring to

public     :
                     PI(DSC_Concept)                             &get_term() { return(term); }
};

#pragma pack()
#endif
