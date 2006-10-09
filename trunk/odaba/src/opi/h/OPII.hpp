#ifndef OPI_I_H
#define OPI_I_H
#include <OPI.h>
#include <codaba2.h>
#include <enumconv.h>
#include <list>
#include <Ice/Ice.h>
#include <OPIFactoryI.hpp>

class CheckOptionsI;
typedef IceUtil::Handle<CheckOptionsI> CheckOptionsIPtr; //<cast&convert
typedef std::list< ::OPI::CheckOptionsPrx > CheckOptionsPrxList;
/**
 * \brief ICE Interface Class for CheckOptions
 */
class CheckOptionsI : virtual public OPI::CheckOptions, virtual public ::CheckOptions

{

	private:

	OPIFactoryIPtr factory;
	public:
	CheckOptionsI(::CheckOptions &refobj):
		OPI::CheckOptions()
		,::CheckOptions(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool Initialize(
		  const ::std::string& parmstring			//<STRING|parmstring
		, const ::Ice::Current& current //< ice default

	);

};//class CheckOptionsI

class DBObjectHandleI;
typedef IceUtil::Handle<DBObjectHandleI> DBObjectHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DBObjectHandlePrx > DBObjectHandlePrxList;
/**
 * \brief ICE Interface Class for DBObjectHandle
 */
class DBObjectHandleI : virtual public OPI::DBObjectHandle, virtual public ::DBObjectHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DBObjectHandleI(::DBObjectHandle &refobj):
		OPI::DBObjectHandle()
		,::DBObjectHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual ::Ice::Int BeginTransaction(
		  bool extTA			//<LOGICAL|ext_TA
		, ::Ice::Int wmaxnum			//<INT|w_maxnum
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ChangeTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CommitTransaction(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteExtent(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteExtentRef(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual void DisableEventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual void EnableEventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool EventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ExecuteDBObjectAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx ExecuteExpression(
		  const ::OPI::DBObjectHandlePrx& resobhandle			//<DBObjectHandle|res_obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExtentExist(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PIACC GetAccess(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetActionResult(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx GetDBHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DataSourceHandlePrx GetDataSource(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DictionaryHandlePrx GetDictionary(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetExtent(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx GetHighObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetObject(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSystemVersion(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Long GetTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetTransactionLevel(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsClient(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsEmpty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsOpened(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsServer(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsValid(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool NewVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenObject(
		  const ::OPI::DBObjectHandlePrx& dbobject			//<DBObjectHandle|dbobject
		, const ::std::string& objname			//<CHAR|objname
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RollBack(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	);
	virtual void SetActionResult(
		  const ::std::string& resultstring			//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int SetOverload(
		  bool overloadopt			//<LOGICAL|overload_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::std::string& varstring			//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetUserDefinedIdentity(
		  bool identityopt			//<LOGICAL|identity_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersion(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersioni1(
		  ::Ice::Long date			//<dbdt|date
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersioni2(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int VersionCount(
		  const ::Ice::Current& current //< ice default

	);

};//class DBObjectHandleI

class DataSourceHandleI;
typedef IceUtil::Handle<DataSourceHandleI> DataSourceHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DataSourceHandlePrx > DataSourceHandlePrxList;
/**
 * \brief ICE Interface Class for DataSourceHandle
 */
class DataSourceHandleI : virtual public OPI::DataSourceHandle, virtual public ::DataSourceHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DataSourceHandleI(::DataSourceHandle &refobj):
		OPI::DataSourceHandle()
		,::DataSourceHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool BeginTransaction(
		  bool extta			//<LOGICAL|ext_ta
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Close(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDBObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDatabase(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDictionary(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseResourceDB(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CommitTransaction(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Connect(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Disconnect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Open(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, ::OPI::PIACC accmod			//<PIACC|acc_mod
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Openi02(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Openi1(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx OpenDBObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx OpenDatabase(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DictionaryHandlePrx OpenDictionary(
		  ::OPI::PIACC accopt			//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx OpenProperty(
		  const ::std::string& extname			//<CHAR|extname
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx OpenResourceDB(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool RollBack(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SetDBObject(
		  const ::OPI::DBObjectHandlePrx& ohandle			//<DBObjectHandle|ohandle
		, const ::std::string& wobjname			//<STRING|w_objname
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDataSource(
		  const ::OPI::DataSourceHandlePrx& dbdefptr			//<DataSourceHandle|dbdefptr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDatabase(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDictionary(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::std::string& wdictpath			//<STRING|w_dictpath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetResourceDB(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Setup(
		  const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetupVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);

};//class DataSourceHandleI

#endif
