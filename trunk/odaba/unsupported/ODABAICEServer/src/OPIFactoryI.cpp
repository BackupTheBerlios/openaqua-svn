
#include <OPIFactoryI.hpp>
#include <Ice/Ice.h>
#include <OPII.hpp>
::OPI::CheckOptionsPrx
OPIFactoryI::GetCheckOptions(const Ice::Current& current){
	::CheckOptions hdl;
	CheckOptionsIPtr ret = new CheckOptionsI(hdl);
	ret->SetObjectFactory(this);
	::OPI::CheckOptionsPrx prx =OPI::CheckOptionsPrx::uncheckedCast(current.adapter->addWithUUID(ret));
	CheckOptionsItems.push_back(prx);
	return prx;
}
::OPI::DBObjectHandlePrx
OPIFactoryI::GetDBObjectHandle(const Ice::Current& current){
	::DBObjectHandle hdl;
	DBObjectHandleIPtr ret = new DBObjectHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::DBObjectHandlePrx prx =OPI::DBObjectHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	DBObjectHandleItems.push_back(prx);
	return prx;
}
::OPI::DataSourceHandlePrx
OPIFactoryI::GetDataSourceHandle(const Ice::Current& current){
	::DataSourceHandle hdl;
	DataSourceHandleIPtr ret = new DataSourceHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::DataSourceHandlePrx prx =OPI::DataSourceHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	DataSourceHandleItems.push_back(prx);
	return prx;
}
::OPI::DatabaseHandlePrx
OPIFactoryI::GetDatabaseHandle(const Ice::Current& current){
	::DatabaseHandle hdl;
	DatabaseHandleIPtr ret = new DatabaseHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::DatabaseHandlePrx prx =OPI::DatabaseHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	DatabaseHandleItems.push_back(prx);
	return prx;
}
::OPI::DictionaryHandlePrx
OPIFactoryI::GetDictionaryHandle(const Ice::Current& current){
	::DictionaryHandle hdl;
	DictionaryHandleIPtr ret = new DictionaryHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::DictionaryHandlePrx prx =OPI::DictionaryHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	DictionaryHandleItems.push_back(prx);
	return prx;
}
::OPI::ODABAClientPrx
OPIFactoryI::GetODABAClient(const Ice::Current& current){
	::ODABAClient hdl;
	ODABAClientIPtr ret = new ODABAClientI(hdl);
	ret->SetObjectFactory(this);
	::OPI::ODABAClientPrx prx =OPI::ODABAClientPrx::uncheckedCast(current.adapter->addWithUUID(ret));
	ODABAClientItems.push_back(prx);
	return prx;
}
::OPI::OperationHandlePrx
OPIFactoryI::GetOperationHandle(const Ice::Current& current){
	::OperationHandle hdl;
	OperationHandleIPtr ret = new OperationHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::OperationHandlePrx prx =OPI::OperationHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	OperationHandleItems.push_back(prx);
	return prx;
}
::OPI::PropertyHandlePrx
OPIFactoryI::GetPropertyHandle(const Ice::Current& current){
	::PropertyHandle hdl;
	PropertyHandleIPtr ret = new PropertyHandleI(hdl);
	ret->SetObjectFactory(this);
	::OPI::PropertyHandlePrx prx =OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	PropertyHandleItems.push_back(prx);
	return prx;
}
void
OPIFactoryI::Destroy(const Ice::Current& current){
	for(CheckOptionsList::iterator CheckOptionsit = CheckOptionsItems.begin();
		CheckOptionsit !=CheckOptionsItems.end();
		CheckOptionsit++){
		current.adapter->remove((*CheckOptionsit)->ice_getIdentity());
	}
	CheckOptionsItems.clear();
	for(DBObjectHandleList::iterator DBObjectHandleit = DBObjectHandleItems.begin();
		DBObjectHandleit !=DBObjectHandleItems.end();
		DBObjectHandleit++){
		current.adapter->remove((*DBObjectHandleit)->ice_getIdentity());
	}
	DBObjectHandleItems.clear();
	for(DataSourceHandleList::iterator DataSourceHandleit = DataSourceHandleItems.begin();
		DataSourceHandleit !=DataSourceHandleItems.end();
		DataSourceHandleit++){
		current.adapter->remove((*DataSourceHandleit)->ice_getIdentity());
	}
	DataSourceHandleItems.clear();
	for(DatabaseHandleList::iterator DatabaseHandleit = DatabaseHandleItems.begin();
		DatabaseHandleit !=DatabaseHandleItems.end();
		DatabaseHandleit++){
		current.adapter->remove((*DatabaseHandleit)->ice_getIdentity());
	}
	DatabaseHandleItems.clear();
	for(DictionaryHandleList::iterator DictionaryHandleit = DictionaryHandleItems.begin();
		DictionaryHandleit !=DictionaryHandleItems.end();
		DictionaryHandleit++){
		current.adapter->remove((*DictionaryHandleit)->ice_getIdentity());
	}
	DictionaryHandleItems.clear();
	for(ODABAClientList::iterator ODABAClientit = ODABAClientItems.begin();
		ODABAClientit !=ODABAClientItems.end();
		ODABAClientit++){
		current.adapter->remove((*ODABAClientit)->ice_getIdentity());
	}
	ODABAClientItems.clear();
	for(OperationHandleList::iterator OperationHandleit = OperationHandleItems.begin();
		OperationHandleit !=OperationHandleItems.end();
		OperationHandleit++){
		current.adapter->remove((*OperationHandleit)->ice_getIdentity());
	}
	OperationHandleItems.clear();
	for(PropertyHandleList::iterator PropertyHandleit = PropertyHandleItems.begin();
		PropertyHandleit !=PropertyHandleItems.end();
		PropertyHandleit++){
		current.adapter->remove((*PropertyHandleit)->ice_getIdentity());
	}
	PropertyHandleItems.clear();
}
