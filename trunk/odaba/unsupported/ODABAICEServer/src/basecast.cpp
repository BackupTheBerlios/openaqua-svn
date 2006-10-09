#include <basecast.h>
#include <Ice/Ice.h>
// handwritten - not able to generate from database yet
// generic casts

// in: dbobjecthandle prx
// out: ::dbobjecthandle

::DBObjectHandle* dbocast(const ::OPI::DBObjectHandlePrx& objecthandle,const ::Ice::Current& c){
    ::DBObjectHandle *TCobjecthandle = NULL;
    
	if((*objecthandle).ice_isA("::OPI::DictionaryHandle")){
    	    DictionaryHandleIPtr dicth = DictionaryHandleIPtr::dynamicCast(c.adapter->find((*objecthandle).ice_getIdentity())); //0x*10
	    TCobjecthandle= (::DBObjectHandle*)(::DatabaseHandle*)(::DictionaryHandle*)(&(*dicth));
	}else if((*objecthandle).ice_isA("::OPI::DatabaseHandle")){
    	    DatabaseHandleIPtr dbh = DatabaseHandleIPtr::dynamicCast(c.adapter->find((*objecthandle).ice_getIdentity())); //0x*10
	    TCobjecthandle= (::DBObjectHandle*) (::DatabaseHandle*)(&(*dbh));
	}else if((*objecthandle).ice_isA("::OPI::DBObjectHandle")){
	    DBObjectHandleIPtr TCPobjecthandle = DBObjectHandleIPtr::dynamicCast(c.adapter->find((*objecthandle).ice_getIdentity()));  //0x*40
	    TCobjecthandle= &(*TCPobjecthandle);
	}
    return TCobjecthandle;
}

::DatabaseHandle* dbhcast(const ::OPI::DatabaseHandlePrx& dbhandle,const ::Ice::Current& c){
    ::DatabaseHandle *TCdbhandle = NULL;
    
	if((*dbhandle).ice_isA("::OPI::DictionaryHandle")){
    	    DictionaryHandleIPtr dicth = DictionaryHandleIPtr::dynamicCast(c.adapter->find((*dbhandle).ice_getIdentity())); //0x*10
	    TCdbhandle= (::DatabaseHandle*)(::DictionaryHandle*)(&(*dicth));
	}else if((*dbhandle).ice_isA("::OPI::DatabaseHandle")){
    	    DatabaseHandleIPtr dbh = DatabaseHandleIPtr::dynamicCast(c.adapter->find((*dbhandle).ice_getIdentity())); //0x*10
	    TCdbhandle= (::DatabaseHandle*)(&(*dbh));
	}
    return TCdbhandle;
}

