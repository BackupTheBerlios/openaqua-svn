/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_Concept

\brief    Concept
          Concepts  are  terms  that  refer  to  a  ‘concepts’  or  a  ‘relevant
          phenomena’  in  a  certain  context.  Each  concept is associated with
          exactly  one term; however, synonyms can also  be used to refer to the
          concept.

\date     $Date: 2006/03/13 21:30:06,85 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_Concept_HPP
#define   DSC_Concept_HPP

class     DSC_Concept;

#ifndef   P_DSC_Concept_HPP
#define   P_DSC_Concept_HPP
#include  <sPI.hpp>
class       DSC_Concept;
PI_dcl     (DSC_Concept)
#endif
#ifndef   P_DSC_Synonym_HPP
#define   P_DSC_Synonym_HPP
#include  <sPI.hpp>
class       DSC_Synonym;
PI_dcl     (DSC_Synonym)
#endif
#ifndef   P_DSC_Topic_HPP
#define   P_DSC_Topic_HPP
#include  <sPI.hpp>
class       DSC_Topic;
PI_dcl     (DSC_Topic)
#endif
#include  <sDSC_Term.hpp>
#pragma pack(8)

class  DSC_Concept :public DSC_Term
{
protected  :         PI(DSC_Synonym)                              synonyms;                                                  // Synonyms for the concept
protected  :         PI(DSC_Concept)                              references;                                                // References to other Terms
protected  :         PI(DSC_Concept)                              referenced_in;                                             // Terms Referring to the Term
protected  :         PI(DSC_Concept)                              generalisations;                                           // Generalizations of the Term
protected  :         PI(DSC_Concept)                              specialisations;                                           // Specializations of the Term
protected  :         PI(DSC_Topic)                                topics;                                                    // Topics associated with the concept (term)

public     :
                     PI(DSC_Synonym)                             &get_synonyms() { return(synonyms); }
                     PI(DSC_Concept)                             &get_references() { return(references); }
                     PI(DSC_Concept)                             &get_referenced_in() { return(referenced_in); }
                     PI(DSC_Concept)                             &get_generalisations() { return(generalisations); }
                     PI(DSC_Concept)                             &get_specialisations() { return(specialisations); }
                     PI(DSC_Topic)                               &get_topics() { return(topics); }
};

#pragma pack()
#endif
