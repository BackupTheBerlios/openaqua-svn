#ifndef __OPIFactory__
#define __OPIFactory__
#include <OPI.h>
#include <list>
typedef std::list< ::OPI::CheckOptionsPrx > CheckOptionsList;
typedef std::list< ::OPI::DBObjectHandlePrx > DBObjectHandleList;
typedef std::list< ::OPI::DataSourceHandlePrx > DataSourceHandleList;
typedef std::list< ::OPI::DatabaseHandlePrx > DatabaseHandleList;
typedef std::list< ::OPI::DictionaryHandlePrx > DictionaryHandleList;
typedef std::list< ::OPI::ODABAClientPrx > ODABAClientList;
typedef std::list< ::OPI::OperationHandlePrx > OperationHandleList;
typedef std::list< ::OPI::PropertyHandlePrx > PropertyHandleList;
class OPIFactoryI: virtual public ::OPI::OPIFactory{
	public:
	CheckOptionsList CheckOptionsItems;
	DBObjectHandleList DBObjectHandleItems;
	DataSourceHandleList DataSourceHandleItems;
	DatabaseHandleList DatabaseHandleItems;
	DictionaryHandleList DictionaryHandleItems;
	ODABAClientList ODABAClientItems;
	OperationHandleList OperationHandleItems;
	PropertyHandleList PropertyHandleItems;
	 void Destroy(const Ice::Current&);
	virtual ::OPI::CheckOptionsPrx GetCheckOptions(const Ice::Current&);
	virtual ::OPI::DBObjectHandlePrx GetDBObjectHandle(const Ice::Current&);
	virtual ::OPI::DataSourceHandlePrx GetDataSourceHandle(const Ice::Current&);
	virtual ::OPI::DatabaseHandlePrx GetDatabaseHandle(const Ice::Current&);
	virtual ::OPI::DictionaryHandlePrx GetDictionaryHandle(const Ice::Current&);
	virtual ::OPI::ODABAClientPrx GetODABAClient(const Ice::Current&);
	virtual ::OPI::OperationHandlePrx GetOperationHandle(const Ice::Current&);
	virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const Ice::Current&);
};
typedef IceUtil::Handle<OPIFactoryI> OPIFactoryIPtr; //<cast&convert
#endif
