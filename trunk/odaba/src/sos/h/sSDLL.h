/*******************************************************************/
/*                         D L L                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          18.03.97 */
/*******************************************************************/

#ifndef   SDL_LIST_HPP
#define   SDL_LIST_HPP

#include  <list>

#define   SDLL(itp)     tc_sdll<itp>
#define   SDLL_dcl(itp)

template <class itp> class tc_sdll :
  public  std::list<itp*>
{
  protected:
    std::list<itp*>::iterator current;
    bool top;
    itp*                      pNULL;
  public:
    void         AddHead        (itp * entptr)
                                { push_front(entptr); }
    void         AddTail        (itp * entptr)
                                { push_back(entptr); }
    int          FindIndex      (int indx0)
                                { 
                                	if( indx0<0 ) 
                                		return NO;
                                	for( current = begin(); current != end() && indx0 ; current++ ){
	                                	indx0--;
	                                }
                                	return current!=end();
                                }
    int          Find           (itp * entptr)
                                {
                                	for( current = begin(); current != end(); current++ )
                                		if( *current == entptr )
                                	   		return YES;
                                	return NO;
				}
    itp       *& GetObjectInst  (int indx0)
                                {
                                	if( indx0 <0 ) return NULL;
					for( current = begin(); current != end() && indx0; current++ )
						indx0--;
					return GetAt();
                                }
    int          GetPosition    (itp *entptr)
                                {
                                	int indx0 = 0;
                                	for( current = begin(); current != end(); current++ ){
                                		if( *current == entptr )
                                	   		break;
                                		indx0++;
					}
                                	return indx0;
				}
    itp       *& Get            (int indx0)
                                {
                                	if(FindIndex(indx0))
	                                	return GetAt();
	                                return NULL;
                                }
    itp       *& GetAt          ()
                                { 
                                	if(!size()) return pNULL;
                                	if(current == end()) return pNULL;
                                	return (*current) ; 
				}
    int          GetCount       ()
                                { return size(); }
    itp       *& GetHead        ()
                                { 
                                	current = begin();
                                	return GetAt(); 
                                }
    itp       *& GetNext        ()
                                { 
                                	if(!top)
                                		current++;
                                	else
                                		top = false;
                                	return GetAt();
                                	
                                }
    itp       *& GetPrev        ()
                                {
                                	current--;
                                	return GetAt();
				}
    itp       *& GetTail        ()
                                {
                                	current = end();
                                	current--;
                                	return GetAt();
                                }
    void         GoBottom       ()
                                {
                                	current = end();
                                }
    void         GoTop          ()
                                {
                                	current = begin();
                                	top = true;
                                }
    void         InsertAfter    (itp *entptr)
                                { 
                                	current++;
                                	insert(current, *entptr);
                                }
    void         InsertBefore   (itp *entptr)
                                {
                                	insert(current, *entptr);
				}
    void         Insert         (itp *entptr,int indx0)
                                {
                                	Find(indx0);
                                	InsertBefore(entptr);
                                }
    itp       *  Remove         (int indx0)
                                {
                                	itp* value;
                                	Find(indx0);
                                	value = (*current);
                                	erase(current);
                                	return value;
                                }
    itp       *  Remove         (itp *entptr)
                                {
                                	itp* value;
                                	Find(entptr);
                                	value = (*current);
                                	erase(current);
                                	return value;
                                }
    itp       *  RemoveAt       ()
                                {
                                	itp* value = (*current);
                                	erase(current);
                                	return value;
                                }
    itp       *  RemoveHead     ()
                                { 
                                	GetHead();
                                	return RemoveAt();
                                }
    itp       *  RemoveTail     ()
                                {
                                	GetTail();
                                	return RemoveAt();
                                }
    void         Clear          () { clear(); }
    void         SetAt          (itp *entptr)
                                { *current = *entptr; }

    itp      *  operator()      (int indx0)
                                {
                                	Find(indx0);
                                	return &(*current);
                                }
/*    tc_sdll   &  operator=       (tc_sdll &rlist)
                                { return( (tc_dll &)QuList::operator=((QuList &)rlist) ); }*/

                 tc_sdll         () :
                                  std::list<itp*>()
                                 ,current()
                                 ,top(true)
                                 ,pNULL(NULL)
                                {}
                 tc_sdll         (tc_sdll &rlist) :
                                  std::list<itp*>(rlist)
                                 ,current()
                                 ,top(true)
                                 ,pNULL(NULL)
                                {}
                 tc_sdll         (int16 buffcount) :
                                  std::list<itp*>()
                                 ,current()
                                 ,top(true)
                                 ,pNULL(NULL)
                                {}
                ~tc_sdll         () {clear();}
};

#endif
