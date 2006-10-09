/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RegExp

\brief    


\date     $Date: 2006/03/12 19:21:56,78 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RegExp"

#include  <stdinc.h>
#include  <pdefault.h>
#include  <srpattern.hpp>
#include  <sRegExp.hpp>


/******************************************************************************/
/**
\brief  IsValid - 


\return

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical RegExp :: IsValid ( ) const
{

  return pat != NULL;

}

/******************************************************************************/
/**
\brief  Match - 


\return term - Success

\param  std_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Match"

logical RegExp :: Match (std::string &std_str ) const
{
  regex::match_results               results;
  regex::match_results::backref_type br;
  return ( pat ? pat->match(std_str,results).matched : NO );

}

/******************************************************************************/
/**
\brief  MatchExpression - 


\return term - Success

\param  reg_expr -
\param  std_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MatchExpression"

logical __cdecl RegExp :: MatchExpression (char *reg_expr, std::string &std_str )
{
  regex::match_results   r;
  logical                cond = NO;
BEGINSEQ
  try
  {
    cond = regex::rpattern(reg_expr,regex::NOFLAGS,regex::MODE_SAFE).match(std_str,r).matched;
  } 
  catch ( ... )
  {
    ERROR
  }
RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  RegExp - Constructor


-------------------------------------------------------------------------------
\brief i00


\param  reg_expr -
\param  repl_string -
\param  submatches -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegExp"

                        RegExp :: RegExp (char *reg_expr, char *repl_string, logical submatches )
                     : pat(NULL)
{

try {
	pat = new regex::rpattern (reg_expr, repl_string, regex::GLOBAL | (submatches ? regex::ALLBACKREFS : regex::FIRSTBACKREFS), regex::MODE_SAFE);
} catch ( ... )
{
	pat = NULL;
}


}

/******************************************************************************/
/**
\brief i01


\param  reg_expr -
\param  submatches -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegExp"

                        RegExp :: RegExp (char *reg_expr, logical submatches )
                     : pat(NULL)
{

try {
	pat = new regex::rpattern (reg_expr, regex::GLOBAL | (submatches ? regex::ALLBACKREFS : regex::FIRSTBACKREFS), regex::MODE_SAFE);
} catch ( ... )
{
	pat = NULL;
}


}

/******************************************************************************/
/**
\brief  Replace - Replace matched text with passed string
        The  function replaces the text, that matches the regular expression, by
        the replacement string passed to the function.

\return pos_vec -
-------------------------------------------------------------------------------
\brief i00 -


\param  std_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

VECTOR(intPair) RegExp :: Replace (std::string &std_str ) const
{
  VECTOR(intPair)                   pos_vec;
//  regex::subst_results              results;

BEGINSEQ
  if ( !pat )                                        ERROR
  //fixme: hier geht was maechtig schief, bis auf weiteres gibt's deshalb kein Replace
/*
  (*pat).substitute(std_str, results);
  br_count = results.cbackrefs();
  for ( int i = 0; i < br_count; i++ )
  {
    br = results.backref(i);
    if ( br.matched )
      pos_vec.push_back(intPair(std::distance((const std::string::iterator)std_str.begin(), (const std::string::iterator)br.first), std::distance(br.first, br.second)));
    else
      pos_vec.push_back(intPair(-1,-1));
  }
*/
RECOVER

ENDSEQ
  return(pos_vec);
}

/******************************************************************************/
/**
\brief i01


\param  repl_string -
\param  std_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

VECTOR(intPair) RegExp :: Replace (char *repl_string, std::string &std_str ) const
{
  VECTOR(intPair)         pos_vec;

  return(pos_vec);
}

/******************************************************************************/
/**
\brief  ReplaceExpression - Replace matched text with passed string
        The  function  replaces  the  text,  which  matches  the  passed regular
        expression, by the replacement string passed to the function.

\return pos_vec -

\param  reg_expr -
\param  repl_string -
\param  std_str -
\param  submatches -
\param  case_sensitive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceExpression"

VECTOR(intPair) __cdecl RegExp :: ReplaceExpression (char *reg_expr, char *repl_string, std::string &std_str, logical submatches, logical case_sensitive )
{
  VECTOR(intPair)                    pos_vec;
  regex::subst_results               results;
  size_t                             br_count;
  regex::subst_results::backref_type br;
BEGINSEQ
  try
  {
    regex::rpattern(reg_expr, regex::GLOBAL | (case_sensitive ? regex::NOFLAGS : regex::NOCASE) | (submatches ? regex::ALLBACKREFS : regex::FIRSTBACKREFS), regex::MODE_SAFE).substitute(std_str, results);
  } catch ( ... )
  {
    ERROR
  }

  br_count = results.cbackrefs();
  for ( int i = 0; i < br_count; i++ )
  {
    br = results.backref(i); 
    if ( br.matched )
      pos_vec.push_back(intPair(std::distance((std::string::const_iterator)std_str.begin(), (std::string::const_iterator)br.first), std::distance(br.first, br.second)));
    else
      pos_vec.push_back(intPair(-1,-1));
  }
RECOVER

ENDSEQ
  return(pos_vec);
}

/******************************************************************************/
/**
\brief  Search - Search expression in string
        The   function   checks,   whether   the   string   contains one or more
        sub-strings that match the regular expression or not.

\return

\param  std_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Search"

VECTOR(intPair) RegExp :: Search (std::string &std_str ) const
{
  VECTOR(intPair)                    pos_vec;
  regex::match_results               results;
  size_t                             br_count;
  regex::match_results::backref_type br;
BEGINSEQ
  if ( !pat )                                        ERROR
  pat->match( std_str, results );
    
  br_count = results.cbackrefs();
  for ( int i = 0; i < br_count; i++ )
  {
    br = results.backref(i);
    if ( br.matched )
      pos_vec.push_back(intPair(std::distance((std::string::const_iterator)std_str.begin(), (std::string::const_iterator)br.first), std::distance(br.first, br.second)));
    else
      pos_vec.push_back(intPair(-1,-1));
  }
RECOVER

ENDSEQ
  return pos_vec;
}

/******************************************************************************/
/**
\brief  SearchExpression - Serch expression in string
        The  static search function  checks, whether the  string contains one or
        more sub-strings that match the passed regular expression or not.

\return pos_vec -

\param  reg_expr -
\param  std_str -
\param  submatches -
\param  case_sensitive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchExpression"

VECTOR(intPair) __cdecl RegExp :: SearchExpression (char *reg_expr, std::string &std_str, logical submatches, logical case_sensitive )
{
  VECTOR(intPair)         pos_vec;
  regex::match_results    results;
  size_t                  br_count;
  regex::match_results::backref_type br;
BEGINSEQ
  try
  {
    regex::rpattern(reg_expr, regex::GLOBAL | (case_sensitive ? regex::NOFLAGS : regex::NOCASE) | (submatches ? regex::ALLBACKREFS : regex::FIRSTBACKREFS), regex::MODE_SAFE).match(std_str, results);
  } catch ( ... )
  {
    ERROR
  }
  
  br_count = results.cbackrefs();
  for ( int i = 0; i < br_count; i++ )
  {
    br = results.backref(i);
    if ( br.matched )
      pos_vec.push_back(intPair(std::distance((std::string::const_iterator)std_str.begin(), (std::string::const_iterator)br.first), std::distance(br.first, br.second)));
    else
      pos_vec.push_back(intPair(-1,-1));
  }
RECOVER

ENDSEQ
  return(pos_vec);
}

/******************************************************************************/
/**
\brief  TextPositionToPoint - Text Position as paragraph and index relative 1


\return text_point - Text point as paragraph and index relative 1

\param  std_str -
\param  posn - Position relative 0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TextPositionToPoint"

intPair __cdecl RegExp :: TextPositionToPoint (std::string &std_str, int32 posn )
{
  RegExp const     lines("[^\n]*(\n|$)");
  VECTOR(intPair)  matches;
  intPair          point(0,0);
  int              line_count = UNDEF;
BEGINSEQ
  matches    = lines.Search(std_str);
  line_count = matches.size();
  
  while ( point.first < line_count )
  {
    if ( posn >= matches[point.first].first + matches[point.first].second )
    {
      if ( matches[point.first].second )  // last, but no real line
        point.first++;
      else
      {
        if ( point.first )
        {
          point.first--;
          point.second = posn - matches[point.first].first;
        }
        LEAVESEQ
      }
    }
    else
    {
      point.second = posn - matches[point.first].first;
      LEAVESEQ
    }
  }
ENDSEQ
  point.first++;
  point.second++;  
  return(point);
}

/******************************************************************************/
/**
\brief  ~RegExp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RegExp"

                        RegExp :: ~RegExp ( )
{

 	delete pat;

}


