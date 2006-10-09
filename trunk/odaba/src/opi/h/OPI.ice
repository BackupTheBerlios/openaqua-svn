module OPI{
enum PIACC            { piaREAD, piaWRITE, piaUPDATE,piaUNDEFINED };
enum PIREPL           { piaREPLGUID, piaREPLDIRECT, piaREPLNONE, piaREPLLOCAL, piaREPLALL, piaREPLINSTANCE, piaREPLRELATIONSHIPS, piaREPLNOCREATE};
enum PIADEF           { piaUNKNOWN, piaEXCLUSIVE, piaSHARE }; 
enum ResourceTypes    { resAUTOMATIC, resSERVER, resLOCAL, resSERVERINTERN };
enum ApplicationTypes { aptWINDOWS, aptCONSOLE };

// class declaration
	class CheckOptions;
	class DBObjectHandle;
	class DataSourceHandle;
	class DatabaseHandle;
	class DictionaryHandle;
	class ODABAClient;
	class OperationHandle;
	class PropertyHandle;
class CheckOptions
{
	// not documented
	bool* Initialize(
		  string parmstring		//<STRING|parmstring

	);

};// end of CheckOptions slice

class DBObjectHandle
{
	// not documented
	int BeginTransaction(
		  bool extTA		//<LOGICAL|ext_TA
		, int wmaxnum		//<INT|w_maxnum

	);

	// not documented
	bool ChangeTimeStamp(
		  int versionnr		//<UINT|version_nr
		, long timestamp		//<dttm|timestamp

	);

	// not documented
	bool CommitTransaction(
		  int talevel		//<INT|talevel

	);

	// not documented
	PropertyHandle* CreateTempPropertyHandle(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref

	);

	// not documented
	bool DeleteExtent(
		  string extnames		//<STRING|extnames

	);

	// not documented
	bool DeleteExtentRef(
		  string extnames		//<STRING|extnames

	);

	// not documented
	void DisableEventHandling();

	// not documented
	void EnableEventHandling();

	// not documented
	bool EventHandling();

	// not documented
	bool ExecuteDBObjectAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);

	// not documented
	PropertyHandle* ExecuteExpression(
		  DBObjectHandle* resobhandle		//<DBObjectHandle|res_obhandle
		, string expression		//<STRING|expression

	);

	// not documented
	bool ExtentExist(
		  string extnames		//<STRING|extnames

	);

	// not documented
	PIACC GetAccess();

	// not documented
	string GetActionResult();

	// not documented
	DatabaseHandle* GetDBHandle();

	// not documented
	DataSourceHandle* GetDataSource();

	// not documented
	DictionaryHandle* GetDictionary();

	// not documented
	string GetExtent(
		  int indx0		//<INT|indx0

	);

	// not documented
	DBObjectHandle* GetHighObject();

	// not documented
	string GetObject(
		  int indx0		//<INT|indx0

	);

	// not documented
	string GetServerVariable(
		  string varname		//<STRING|var_name

	);

	// not documented
	int GetSystemVersion();

	// not documented
	long GetTimeStamp(
		  int versionnr		//<UINT|version_nr

	);

	// not documented
	int GetTransactionLevel();

	// not documented
	int GetVersion(
		  long timestamp		//<dttm|timestamp

	);

	// not documented
	bool IsClient();

	// not documented
	bool IsEmpty();

	// not documented
	bool IsOpened();

	// not documented
	bool IsServer();

	// not documented
	bool IsValid();

	// not documented
	bool NewVersion(
		  long timestamp		//<dttm|timestamp
		, int versionnr		//<UINT|version_nr

	);

	// not documented
	bool OpenObject(
		  DBObjectHandle* dbobject		//<DBObjectHandle|dbobject
		, string objname		//<CHAR|objname
		, PIACC accopt		//<PIACC|accopt
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources

	);

	// not documented
	bool RollBack(
		  int talevel		//<INT|talevel

	);

	// not documented
	void SetActionResult(
		  string resultstring		//<STRING|result_string

	);

	// not documented
	int SetOverload(
		  bool overloadopt		//<LOGICAL|overload_opt

	);

	// not documented
	bool SetServerVariable(
		  string varname		//<STRING|var_name
		, string varstring		//<STRING|var_string

	);

	// not documented
	bool SetUserDefinedIdentity(
		  bool identityopt		//<LOGICAL|identity_opt

	);

/**
	\brief Set verion according to number

	The current database version is set according to the passed version number. The version number must be less or equal to the last version number created for the database object.
*/
	bool SetVersion(
		  int versionnr		//<UINT|version_nr

	);

/**
	\brief Set verion according to date

	The current database version is set according to the passed date, i.e. to the version slice (version number) that includes the passed date. The date should be the current date or a darte in the passed.
*/
	bool SetVersioni1(
		  long date		//<dbdt|date

	);

/**
	\brief Set verion according to timestamp

	The current database version is set according to the passed timepoint, i.e. to the version slice (version number) that includes the passed timepoint. The date should be the current date or a darte in the passed.
*/
	bool SetVersioni2(
		  long timestamp		//<dttm|timestamp

	);

	// not documented
	int VersionCount();

};// end of DBObjectHandle slice

class DataSourceHandle
{
	// not documented
	bool BeginTransaction(
		  bool extta		//<LOGICAL|ext_ta

	);

	// not documented
	bool Close();

	// not documented
	bool CloseDBObject();

	// not documented
	bool CloseDatabase();

	// not documented
	bool CloseDictionary();

	// not documented
	bool CloseProperty();

	// not documented
	bool CloseResourceDB();

	// not documented
	bool CommitTransaction();

	// not documented
	bool Connect(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client

	);

	// not documented
	bool Disconnect();

/**
	\brief Open empty data source

	A data source can be opened when the application has filled the external specifications for the data source. At least the dict_path should be set in the data source before openeing. 
The data source should be opened only, when all external resources to be accessed are defined in the data source. When the client is not connected the server specifications (server_name and port_number) shuold be set as well. This is not necessary when running a local application.
*/
	bool Open(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, PIACC accmod		//<PIACC|acc_mod

	);

/**
	\brief Opening datasource based on ini-file section

	The function opens the data source based on external resource definitions passsed in the ini-file. The inifile section name containing the resource definitions is passed as datasource_name to the function. The resource definitions in the data source are filled from the corresponding resource definitions in the ini-file.
*/
	bool Openi02(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string inifile		//<STRING|ini_file
		, string datasourcename		//<STRING|datasource_name

	);

/**
	\brief Opening data source from catalogue

	The function opens the data source based on external resource definitions passsed stored in the data source catalogue. In this case the external resource defitions are read from the catalogue where an entry with the passed datasource_name must exist. 
Using the catalogue feature the catalogue data source must be provided in a catalogue [DATA-CATALOGUE] section of the ini-file (local application) or in a corresponding section of the server. The resource definitions in the data source are filled from the corresponding resource definitions in the catalogue entry before opening the data source.
*/
	bool Openi1(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string datasourcename		//<STRING|datasource_name

	);

	// not documented
	DBObjectHandle* OpenDBObject();

	// not documented
	DatabaseHandle* OpenDatabase();

	// not documented
	DictionaryHandle* OpenDictionary(
		  PIACC accopt		//<PIACC|accopt

	);

	// not documented
	PropertyHandle* OpenProperty(
		  string extname		//<CHAR|extname

	);

	// not documented
	DatabaseHandle* OpenResourceDB();

	// not documented
	bool RollBack();

	// not documented
	bool SetDBObject(
		  DBObjectHandle* ohandle		//<DBObjectHandle|ohandle
		, string wobjname		//<STRING|w_objname

	);

	// not documented
	bool SetDataSource(
		  DataSourceHandle* dbdefptr		//<DataSourceHandle|dbdefptr

	);

	// not documented
	bool SetDatabase(
		  DatabaseHandle* dbhandle		//<DatabaseHandle|db_handle
		, string wbasepath		//<STRING|w_basepath

	);

	// not documented
	bool SetDictionary(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, string wdictpath		//<STRING|w_dictpath

	);

	// not documented
	bool SetResourceDB(
		  DatabaseHandle* dbhandle		//<DatabaseHandle|db_handle
		, string wbasepath		//<STRING|w_basepath

	);

	// not documented
	bool SetVariables(
		  string datasourcename		//<STRING|datasource_name

	);

	// not documented
	bool Setup(
		  string inifile		//<STRING|ini_file
		, string datasourcename		//<STRING|datasource_name

	);

	// not documented
	bool SetupVariables(
		  string datasourcename		//<STRING|datasource_name

	);

};// end of DataSourceHandle slice

class DatabaseHandle extends DBObjectHandle
{
	// not documented
	bool ActivateShadowBase();

	// not documented
	bool BackupDB(
		  string target		//<STRING|target

	);

	// not documented
	bool CheckDB(
		  CheckOptions* checkopts		//<CheckOptions|check_opts
		, string source		//<STRING|source

	);

/**
	\brief Register costumer

	The function checks the user name and license number and registers the license information in the database. When licensing is requested the license information is checked whenever the database is opened.
*/
	bool CheckLicence(
		  string licowner		//<STRING|lic_owner
		, string licnumber		//<CHAR|lic_number

	);

	// not documented
	bool CloseWorkspace();

	// not documented
	bool ConsolidateWorkspace();

	// not documented
	bool DeactivateShadowBase();

	// not documented
	bool DeleteWorkspace(
		  string wsnames		//<STRING|ws_names
		, string username		//<STRING|user_name

	);

	// not documented
	bool DisableWorkspace();

	// not documented
	bool DiscardWorkspace();

	// not documented
	bool EnableWorkspace(
		  string sdwpath		//<CHAR|sdw_path

	);

	// not documented
	bool ExecuteDatabaseAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);

	// not documented
	bool ExistWorkspace(
		  string wsnames		//<STRING|ws_names

	);

	// not documented
	int GetDatabaseID();

	// not documented
	string GetPath();

	// not documented
	int GetSchemaVersion();

	// not documented
	string GetVersionString();

	// not documented
	string GetWorkspace(
		  string wsroot		//<STRING|ws_root
		, int wsindex		//<INT|ws_index
		, string username		//<STRING|user_name
		, string wsname		//<STRING|ws_name
		, bool refreshopt		//<LOGICAL|refresh_opt
		, string wsinfo		//<CHAR|ws_info

	);

	// not documented
	bool IgnoreWriteProtect();

	// not documented
	bool InitDataArea(
		  int mbnumber		//<INT|mbnumber
		, int sbnumber		//<INT|sbnumber
		, int danumber		//<UINT|danumber
		, string filename		//<STRING|filename
		, int dasize		//<INT|dasize

	);

	// not documented
	bool InitMainBase(
		  int mbnumber		//<INT|mbnumber
		, string filename		//<STRING|filename
		, int lowEBN		//<INT|lowEBN
		, int highEBN		//<INT|highEBN
		, int dasize		//<INT|dasize
		, bool largedb		//<LOGICAL|largedb
		, bool pindep		//<LOGICAL|pindep

	);

	// not documented
	bool InitSubBase(
		  int mbnumber		//<INT|mbnumber
		, int sbnumber		//<INT|sbnumber
		, string filename		//<STRING|filename
		, int dasize		//<INT|dasize

	);

	// not documented
	bool IsLicenced();

	// not documented
	bool IsShared();

	// not documented
	bool LocateWorkspace(
		  string wsnames		//<STRING|ws_names

	);

	// not documented
	bool OpenDatabase(
		  DictionaryHandle* dicthandle		//<DictionaryHandle|dict_handle
		, string cpath		//<STRING|cpath
		, PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, bool onlineversion		//<LOGICAL|online_version
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv

	);

	// not documented
	bool OpenWorkspace(
		  string wsnames		//<STRING|ws_names
		, string username		//<STRING|user_name
		, bool exclusive		//<LOGICAL|exclusive
		, string wspath		//<STRING|ws_path

	);

	// not documented
	bool RecreateExtent(
		  string extnames		//<STRING|extnames

	);

	// not documented
	bool RestoreDB(
		  string source		//<STRING|source

	);

	// not documented
	bool SetupTypeID(
		  int sid		//<INT|sid

	);

};// end of DatabaseHandle slice

class DictionaryHandle extends DatabaseHandle
{
	// not documented
	int BaseType(
		  string strnames		//<STRING|strnames

	);

	// not documented
	bool CheckExpression(
		  string expression		//<STRING|expression
		, DBObjectHandle* dbobjhandle		//<DBObjectHandle|dbobj_handle
		, string clsnames		//<STRING|clsnames

	);

	// not documented
	bool CheckExpressionInClass(
		  DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, string clsnames		//<STRING|clsnames
		, string exprnames		//<STRING|exprnames
		, string implnames		//<STRING|implnames

	);

	// not documented
	bool CheckExtentDef(
		  string scopedname		//<STRING|scoped_name

	);

	// not documented
	bool CheckValueSet(
		  string scopedname		//<STRING|scoped_name

	);

	// not documented
	bool CopyCodeset(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strname		//<CHAR|strname
		, int namespaceid		//<INT|namespace_id
		, string newnames		//<STRING|newnames
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav

	);

	// not documented
	bool CopyExtentDef(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string extentname		//<STRING|extentname
		, string newnames		//<STRING|newnames
		, string targstruct		//<STRING|targ_struct
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav

	);

	// not documented
	bool CopyStructure(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strname		//<CHAR|strname
		, int namespaceid		//<INT|namespace_id
		, string newnames		//<STRING|newnames
		, string topname		//<CHAR|topname
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav

	);

	// not documented
	bool CopyType(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strnames		//<STRING|strnames
		, string newnames		//<STRING|newnames
		, string topname		//<CHAR|topname
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav

	);

	// not documented
	bool CreateEnum(
		  string enumname		//<STRING|enum_name
		, string basetype		//<STRING|basetype

	);

	// not documented
	string CreateTempExtent(
		  string strnames		//<STRING|strnames
		, string extnamesw		//<STRING|extnames_w
		, string keynamew		//<CHAR|key_name_w
		, string baseextsw		//<STRING|baseexts_w
		, bool weakoptw		//<LOGICAL|weak_opt_w
		, bool ownoptw		//<LOGICAL|own_opt_w

	);

	// not documented
	bool DeleteEnum(
		  string enumname		//<STRING|enum_name

	);

	// not documented
	string EnumToString(
		  string enumeration		//<STRING|enumeration
		, int enumval		//<INT|enum_val
		, string pstring		//<STRING|string
		, int len		//<INT|len

	);

	// not documented
	int GetLastSchemaVersion();

	// not documented
	string GetTempName(
		  string extnames		//<STRING|extnames

	);

	// not documented
	bool IsBasicType(
		  string typenames		//<STRING|typenames

	);

	// not documented
	bool OpenDictionary(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string cpath		//<STRING|cpath
		, PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv

	);

	// not documented
	int StringToEnum(
		  string enumeration		//<STRING|enumeration
		, string enumstring		//<STRING|enum_string

	);

	// not documented
	bool UpdateVersion();

};// end of DictionaryHandle slice

class ODABAClient
{
	// not documented
	void ActivateGUIMessages();

	// not documented
	bool BackupDB(
		  string cpath		//<STRING|cpath
		, string target		//<STRING|target
		, int waitsec		//<INT|wait_sec

	);

	// not documented
	bool CheckDB(
		  string dictpath		//<STRING|dict_path
		, string cpath		//<STRING|cpath
		, CheckOptions* checkopts		//<CheckOptions|check_opts
		, string source		//<STRING|source
		, int waitsec		//<INT|wait_sec

	);

	// not documented
	bool Close();

	// not documented
	bool Connect(
		  string servername		//<STRING|server_name
		, int hostport		//<UINT|host_port
		, string cachestring		//<STRING|cache_string

	);

	// not documented
	bool DictDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);

	// not documented
	void Disconnect();

	// not documented
	bool Exist(
		  string cpath		//<STRING|cpath

	);

	// not documented
	string GetDataSource(
		  int indx0		//<INT|indx0

	);

	// not documented
	string GetHost();

	// not documented
	int GetPort();

	// not documented
	string GetServerVariable(
		  string varname		//<STRING|var_name

	);

	// not documented
	void Initialize(
		  string inipath		//<STRING|inipath
		, string applicationname		//<STRING|application_name
		, string progpath		//<STRING|progpath
		, ApplicationTypes applicationtype		//<ApplicationTypes|application_type
		, bool initservices		//<LOGICAL|init_services

	);

	// not documented
	bool IsConnected();

	// not documented
	bool KillClient(
		  int clientid		//<INT|client_id
		, int waitsec		//<INT|wait_sec
		, bool sendmessage		//<LOGICAL|send_message

	);

	// not documented
	bool Open(
		  string inipath		//<STRING|inipath
		, string applicationname		//<STRING|application_name
		, string progpath		//<STRING|progpath
		, ApplicationTypes applicationtype		//<ApplicationTypes|application_type

	);

	// not documented
	DBObjectHandle* OpenDataSource(
		  string datasourcename		//<STRING|datasource_name
		, PIACC accopt		//<PIACC|accopt

	);

	// not documented
	bool PackDatabase(
		  string cpath		//<STRING|cpath
		, string temppath		//<STRING|temp_path

	);

	// not documented
	bool RestoreDB(
		  string cpath		//<STRING|cpath
		, string source		//<STRING|source
		, int waitsec		//<INT|wait_sec

	);

	// not documented
	bool SendClientMessage(
		  int clientid		//<INT|client_id
		, string mtext		//<STRING|mtext
		, string mtitle		//<STRING|mtitle
		, string mtype		//<CHAR|mtype

	);

	// not documented
	bool SetServerVariable(
		  string varname		//<STRING|var_name
		, string varstring		//<STRING|var_string

	);

	// not documented
	bool ShutDown(
		  string closesystem		//<CHAR|close_system

	);

	// not documented
	bool StartPause(
		  int waitsec		//<INT|wait_sec

	);

	// not documented
	bool StatDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);

	// not documented
	void StopPause();

	// not documented
	bool SysInfoDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);

};// end of ODABAClient slice

class OperationHandle
{
	// not documented
	bool CheckExpression(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, string expression		//<STRING|expression
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string clsnames		//<STRING|clsnames

	);

	// not documented
	bool CheckExpressionInClass(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, string clsnames		//<STRING|clsnames
		, string exprnames		//<STRING|exprnames
		, string impnames		//<STRING|impnames

	);

	// not documented
	bool Execute();

	// not documented
	PropertyHandle* GetResult();

	// not documented
	int GetSize();

	// not documented
	bool IsValid();

	// not documented
	bool Open(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref

	);

	// not documented
	bool ProvideExpression(
		  DictionaryHandle* pdictionary		//<DictionaryHandle|dictionary
		, DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string expression		//<STRING|expression

	);

};// end of OperationHandle slice

class PropertyHandle
{
	// not documented
	bool Add(
		  int setpos0		//<INT|set_pos0
		, string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w

	);

	// not documented
	bool AddByKey(
		  string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w

	);

/**
	\brief Add instance by property value

	The function checks whether the property handle passes a numerical value or not. When passing a numerical value the function creates an instance at the position according to the number passed in the property handle (-> "Create instance at position"). Otherwise the value in the property handle is interpreted as string key, which will be converted into key and adds an instance by key value to the collection (-> "Add instance by key value")..
*/
	bool AddInstance(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

/**
	\brief Create instance at position

	This function is used to create an instance at a certain position in an unordered collection. The function creates the instance at the passed position (set_pos_w). When AUTO is passed the instance is created infront of the selected instance. When no instance is selected the new instance is appended to the end of the collection. The instance in the property handle can be initialized before calling the Add function calling GetInitInstance() and setting initial property values. In this case the init_inst option must be set to YES when calling the function (otherwuise the initialized instance will be ignored) and the function operates similar to the "Add instance at position" function. The instance can be also initialized before adding to the collection using the DBInitialized event in the structure context.
When the collection is ordered the position passed will be ignored and the instance will be inserted in the collection according to the key passed within the initialized instance. When the instance is not initialized, the instance is created with the default values defined in the data model (structure definition).
*/
	bool AddOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst

	);

	// not documented
	bool AddGlobal(
		  int setpos0		//<INT|set_pos0
		, string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst

	);

	// not documented
	bool AddGlobalByKey(
		  string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst

	);

	// not documented
	bool AddGlobalOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst

	);

	// not documented
	bool AddReference(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	bool AllocDescription();

	// not documented
	bool AllocateArea();

	// not documented
	bool AppendString(
		  string pstring		//<STRING|string

	);

	// not documented
	bool AutoLocate(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool Cancel();

	// not documented
	bool CancelBuffer();

	// not documented
	int ChangeBuffer(
		  int buffnum		//<INT|buffnum

	);

	// not documented
	bool ChangeCache(
		  int buffnum		//<INT|buffnum

	);

	// not documented
	PIACC ChangeMode(
		  PIACC newmode		//<PIACC|newmode

	);

	// not documented
	bool Check(
		  bool iniopt		//<LOGICAL|ini_opt

	);

	// not documented
	bool CheckPosition();

	// not documented
	bool CheckUpdate(
		  bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	bool CheckWProtect();

	// not documented
	bool Close();

/**
	\brief Compare with other property handle

	This implementation compares the value in the property handle with the value in the passed property handle. Data conversion  is performed when required.
*/
	int Compare(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl

	);

/**
	\brief Compare with date value

	This implementation compares the value in the property handle with the passed date value. Data conversion is performed for the passed value when required. Converting date values to string values may result in different string values for the same date value depending on the national setting. Hence, string values should not be compared with date values. In this case it is more appropriate to compare the date values directly ( ph.GetDate() == date_val).
*/
	int CompareDate(
		  long dateval		//<dbdt|date_val

	);

/**
	\brief Compare with double value

	This implementation compares the value in the property handle with the passed double float value. Data conversion is performed for the passed value when required.
*/
	int CompareFloat(
		  float doubleval		//<REAL|double_val

	);

/**
	\brief Compare with 32-bit integer value

	This implementation compares the value in the property handle with the passed integer value. Data conversion is performed for the passed value when required.
*/
	int CompareInteger(
		  int longval		//<INT|long_val

	);

/**
	\brief Compare with string value

	This implementation compares the value in the property handle with the value in the passed string. Data conversion is performed for the string when required.
*/
	int CompareString(
		  string pstring		//<STRING|string

	);

/**
	\brief Compare with time value

	This implementation compares the value in the property handle with the passed time value. Data conversion is performed for the passed value when required. Converting time values to string values may result in different string values for the same time value depending on the national setting. Hence, string values should not be compared with time values. In this case it is more appropriate to compare the time values directly ( ph.GetTime() == time_val).
*/
	int CompareTime(
		  long timeval		//<dbtm|time_val

	);

	// not documented
	int CompareKey(
		  string identkey1		//<Key|ident_key1
		, string identkey2		//<Key|ident_key2

	);

	// not documented
	int CompareSortKey(
		  string sortkey1		//<Key|sort_key1
		, string sortkey2		//<Key|sort_key2

	);

	// not documented
	bool CompareType(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl
		, bool convert		//<LOGICAL|convert

	);

	// not documented
	bool Copy(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, string newkey		//<Key|new_key
		, int setpos0		//<INT|set_pos0
		, PIREPL replopt		//<PIREPL|replopt
		, PIREPL copytype		//<PIREPL|copy_type

	);

/**
	\brief Copy instance data from source instance

	The implementation copies the data from the source instance into the target instance. All direct properties (attributes and base structures) are copied by name. References and relationships are copied, when not yet existing or when replace opt REPL_local (for references) or REPL_all (for references and relationships) has been defined.
When the target is sorted, the sort key is not copied from the source. When the target is not sorted, but an ident-key is defined for the structure, the ident-key remains unchanged.
The target instance will not be initialized, i.e. fields not existing in the source instance are not changed.
*/
	bool CopyData(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, PIREPL replopt		//<PIREPL|replopt

	);

	// not documented
	bool CopyHandle(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

	// not documented
	bool CopyInstanceArea(
		  PropertyHandle* prophdl		//<PropertyHandle|prophdl

	);

	// not documented
	int CopySet(
		  PropertyHandle* csourcehandle		//<PropertyHandle|csource_handle
		, PIREPL replopt		//<PIREPL|replopt
		, PIREPL copytype		//<PIREPL|copy_type
		, bool inversecheck		//<LOGICAL|inverse_check

	);

	// not documented
	bool CreateTempExtent(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string extnamesw		//<STRING|extnames_w

	);

	// not documented
	bool Delete(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

/**
	\brief Delete instance by key

	The function deletes an instance by key. When no instance with the passed key can be located, the function terminates with error.
*/
	bool DeleteByKey(
		  string sortkey		//<Key|sort_key

	);

/**
	\brief Delete instance by position

	The function deletes the instance at the position passed to the function (set_pos0_w). When AUTO is passed the current instance is deleted. Dependent instances are usually deleted as well (del_dep=YES). 
When passing NO, depending instances are not deleted, as long as they are not owned by the current instance.
*/
	bool DeleteOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool deldep		//<LOGICAL|del_dep
		, bool delinst		//<LOGICAL|del_inst

	);

	// not documented
	bool DeleteIndexEntry(
		  int setpos0		//<INT|set_pos0

	);

	// not documented
	bool DeleteSet(
		  bool deldep		//<LOGICAL|del_dep

	);

	// not documented
	bool DisableKeyCheck();

	// not documented
	bool Duplicate(
		  int setpos0		//<INT|set_pos0
		, PIREPL replopt		//<PIREPL|replopt

	);

	// not documented
	bool DuplicateKey(
		  string identkey		//<Key|ident_key
		, PIREPL replopt		//<PIREPL|replopt

	);

	// not documented
	bool EnableKeyCheck();

	// not documented
	bool Execute();

	// not documented
	PropertyHandle* ExecuteExpression(
		  DBObjectHandle* resobhandle		//<DBObjectHandle|res_obhandle
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string expression		//<STRING|expression

	);

	// not documented
	bool ExecuteInstanceAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);

	// not documented
	bool ExecutePropertyAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);

	// not documented
	bool Exist();

	// not documented
	string ExtractKey(
		  string keyname		//<STRING|key_name

	);

	// not documented
	string ExtractSortKey(
		  string sortkeyw		//<Key|sort_key_w

	);

	// not documented
	string FirstKey();

/**
	\brief Get instance by value in the property handle

	When passing the value for locating an instance in a collection via property hanndle, Get() is called as get by key or index depending on the data type defined in the property handle. 
When the value property handle passes a structured instance of the same or a specialized type as the instance to be selected, the key value is extracted from the instance passed in the property handle and get by key is used.
When passing a text value (STRING, MEMO or CHAR), the text data is considered as string key where key komponents are separated by |. You cannot pass a structured key (Key) my means of property handles. 
If not the key or instant version is used the 'get by position' version is called. Non-integer numerical values are rounded to the next lower integer number.
*/
	bool Get(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

/**
	\brief Get Instance by index position

	Reading an instance by position is locating the instance on the given location in the selected index (sort order). Thus, the result will change usually when changing the selected index for the collection. Using index positions for reading is also a weak point when indexes are updated simultaneously, since the index position might change when other users insert or remove entries from the index. To avoid this you may use the LockSet() function, that locks the complete collection. Access by position, however, is a comfortable way browsing through a collection. Access by position cannot be used for LOID or GUID property handles. Passing a number to an LOID handle interpretes the number as local object identity. 
For a path property Get() by position automatically changes the selection for higher properties in the path when the end of collection is signaled an a level that is not the top level for the path property. 
Passing AUTO as position the function returns the instance currently selected in the property handle. When no instance is selected the function returns the first instance in the collection. When an instance is selected in the property handle and the current access mode does not correspond to the required access mode, the function will re-read the instance. Thus, the function can be used to update the access mode when the selected instance was write protected. Selections in subordinated property handles are canceled when re-reading the instance.
*/
	bool GetAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);

/**
	\brief Get instance by key value

	When reading an instance by key, this is considered as key in the currently selected index (SetOrder()). When the key cannor be found in the index the function returns an empty instance. It is also possible to locate an instance by key in an unordered collection, when it has been marked as unique (no duplicate instances). In this case the key must be passed according to the structure of the ident key. The key must be passed according to the internal key structure. 
The key can also be an LOID or a GUID string when the property handle has been opened for reading by local object identities (__LOID) or by global unique identifiers (__GUID).
When positioning the instance for a path property the key must consist of all sort keys along the path. 

*/
	bool GetByKey(
		  string sortkey		//<Key|sort_key

	);

	// not documented
	string GetActionResult();

/**
	\brief Provide area for current property handle

	The function returns the area for the current property handle.
*/
	string GetArea(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	string GetAttribute(
		  int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic

	);

	// not documented
	PropertyHandle* GetBaseProperty();

	// not documented
	int GetCollectionID();

	// not documented
	PropertyHandle* GetCollectionProperty();

	// not documented
	int GetCount();

	// not documented
	int GetCurrentIndex();

	// not documented
	int GetCurrentSize();

	// not documented
	string GetCurrentType();

	// not documented
	DatabaseHandle* GetDBHandle();

	// not documented
	long GetDate(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	long GetDateTime(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetDay(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	DictionaryHandle* GetDictionary();

	// not documented
	int GetDimension();

	// not documented
	float GetDouble(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetExtInstModCount();

	// not documented
	string GetExtentName();

	// not documented
	string GetGUID();

	// not documented
	int GetGenAttrType(
		  string wpropnames		//<STRING|w_propnames

	);

	// not documented
	int GetGenOrderType();

	// not documented
	int GetGlobalID();

	// not documented
	int GetHours(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetID(
		  int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	string GetIdentity(
		  string idstring		//<STRING|id_string

	);

	// not documented
	string GetIndexName(
		  int indx0		//<INT|indx0

	);

	// not documented
	bool GetInitInstance();

	// not documented
	int GetInstModCount();

	// not documented
	int GetInt(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetIntValue(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	string GetKey(
		  int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	int GetKeyLength();

	// not documented
	int GetLOID(
		  int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	int GetLOIDByKey(
		  string sortkey		//<Key|sort_key

	);

	// not documented
	int GetMinutes(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	PIACC GetMode();

	// not documented
	int GetMonth(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetNormalized();

	// not documented
	DBObjectHandle* GetObjectHandle();

	// not documented
	int GetOrigin();

	// not documented
	PropertyHandle* GetParentProperty();

	// not documented
	PropertyHandle* GetPropertyHandle(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	string GetPropertyPath();

	// not documented
	int GetRefModCount();

	// not documented
	string GetReference(
		  int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic

	);

	// not documented
	bool GetRelative(
		  int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	int GetRelativeCount();

	// not documented
	int GetRelativeIndex(
		  bool lastopt		//<LOGICAL|last_opt

	);

	// not documented
	int GetSeconds(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	string GetSelectedKey();

	// not documented
	int GetSize();

	// not documented
	int GetSizeOf();

	// not documented
	string GetSortKey();

	// not documented
	int GetSortKeyLength();

	// not documented
	string GetString(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	int GetStringLength();

	// not documented
	string GetStringValue(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	string GetSubString(
		  int startpos		//<INT|start_pos
		, int length		//<INT|length

	);

	// not documented
	string GetText(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	long GetTime(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	string GetType();

	// not documented
	bool GetValid();

	// not documented
	int GetVersion();

	// not documented
	int GetYear(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	PropertyHandle* Group(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string groupingrule		//<STRING|grouping_rule
		, bool distinct		//<LOGICAL|distinct

	);

	// not documented
	bool HasData();

	// not documented
	bool HasDescription();

	// not documented
	bool HasGenericAttributes();

	// not documented
	bool HasIndex();

	// not documented
	bool Inherits(
		  string strnames		//<STRING|strnames

	);

	// not documented
	bool InsertString(
		  string pstring		//<STRING|string
		, int position		//<INT|position

	);

	// not documented
	bool InsertTerminator(
		  string pstring		//<STRING|string

	);

	// not documented
	bool InstanceInserted();

	// not documented
	string InstanceToString(
		  string stringsep		//<STRING|string_sep
		, string fieldsep		//<STRING|field_sep
		, string blocksep		//<STRING|block_sep
		, string emptystring		//<STRING|empty_string
		, bool skiptrans		//<LOGICAL|skip_trans

	);

	// not documented
	PropertyHandle* Intersect(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt

	);

	// not documented
	bool Is(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

	// not documented
	bool IsA(
		  string strnames		//<STRING|strnames

	);

	// not documented
	bool IsActive();

	// not documented
	bool IsAttribute();

	// not documented
	bool IsAutoSelection();

	// not documented
	bool IsBasedOn(
		  string strnames		//<STRING|strnames

	);

	// not documented
	bool IsBasetypeProperty();

	// not documented
	bool IsBasicType();

	// not documented
	bool IsClient();

	// not documented
	bool IsCollection(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsCollectionUpdate();

	// not documented
	bool IsCopyHandle();

	// not documented
	bool IsDirty();

	// not documented
	bool IsEmpty();

	// not documented
	bool IsEnumeration();

	// not documented
	bool IsGenericAttribute();

	// not documented
	bool IsInitInstance();

	// not documented
	bool IsMemo(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsModified();

	// not documented
	bool IsNewInstance();

	// not documented
	bool IsNumeric();

	// not documented
	bool IsOldInstance();

	// not documented
	bool IsOwner();

	// not documented
	bool IsPositioned(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsReadOnly();

	// not documented
	bool IsSelected(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsSensitive(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	bool IsServer();

	// not documented
	bool IsShareBaseHandle(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsStructure();

	// not documented
	bool IsText(
		  string chkopt		//<CHAR|chkopt

	);

	// not documented
	bool IsTransient();

	// not documented
	bool IsTrue(
		  string proppath		//<STRING|prop_path

	);

	// not documented
	bool IsTyped();

	// not documented
	bool IsUserHandle();

	// not documented
	bool IsValid(
		  bool topt		//<LOGICAL|topt

	);

	// not documented
	bool IsValidText(
		  string pstring		//<STRING|string

	);

	// not documented
	bool IsVariableType();

	// not documented
	bool IsWeakTyped();

	// not documented
	bool IsWrite();

	// not documented
	bool Locate(
		  int obident		//<INT|obident
		, bool readopt		//<LOGICAL|read_opt

	);

	// not documented
	bool LocatePath();

	// not documented
	bool Lock();

	// not documented
	bool LockSet();

	// not documented
	void MarkUnused();

	// not documented
	void MarkUsed();

	// not documented
	PropertyHandle* Minus(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt

	);

	// not documented
	bool Modify();

/**
	\brief Move with rename

	The function allows renaming an instance while moving it to the target collection. When the new key does already exist in the target collection the instance is overwritten depending on the replace option.
*/
	bool Move(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, string newkey		//<Key|new_key
		, PIREPL replopt		//<PIREPL|replopt

	);

	// not documented
	bool MoveDown();

	// not documented
	bool MoveUp();

	// not documented
	string NextKey(
		  string sortkeyw		//<Key|sort_key_w
		, int switchlevel		//<INT|switch_level

	);

	// not documented
	bool NoWrite();

/**
	\brief Open an undefined property handle

	The function opens an undefined and unbound property handle. Before using the property handle definition and instance area must be set.
*/
	bool Open();

	// not documented
	bool OpenBigInt(
		  int int64val		//<INT|int64_val

	);

/**
	\brief Open property handle for a logical value

	The function opens an unbound property handle for a logical value (LOGICAL).
*/
	bool OpenBoolean(
		  bool logval		//<LOGICAL|logval

	);

/**
	\brief Open subordinated property handle

	The function openes a subordinated property handle of the instance. Since the property handlels for instance properties are part of the instance the function creates a copy handle with an own cursor. It behaves, however, like a normal subordinated property handle, that depends on the selection in the upper property handle (if there is any).
*/
	bool OpenChild(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl
		, string proppath		//<STRING|prop_path

	);

/**
	\brief Open subordinated property handle

	The constructor provides a subordinated property handle of the instance. Since property handlels for an instance are part of the instance the function provides a property handle that shares area and cursor with the property handle in the instance. As subordinated property handle it depends on the selection in the upper property handle (if there is any).
*/
	bool OpenChildReference(
		  PropertyHandle* ppropertyhandle		//<PropertyHandle|property_handle
		, string proppath		//<STRING|prop_path

	);

/**
	\brief Open non sharing copy for a property handle

	The function opens a copy of the passed property handle with an own cursor and an own instance area.
*/
	bool OpenCopy(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl

	);

/**
	\brief Open property handle for a date value

	The function opens an unbound property handle for a date value (DATE).
*/
	bool OpenDate(
		  long dateval		//<dbdt|date_val

	);

/**
	\brief Open extent property handle

	The function opens a property handle for a global collection (extent). The extent name passed may contain symbolic references to system variables (e.g. "%EXT_PREF%Pers") which are resolved according to the current setting of the referenced system variables. A key name can be passed to set the sort order for the property handle. If no key is passed the sort order is set to the default order. 
You may open a transient extent that stores data only in main storage by passing the transient_w option.
*/
	bool OpenExtent(
		  DBObjectHandle* objecthandle		//<DBObjectHandle|object_handle
		, string extnames		//<STRING|extnames
		, PIACC accopt		//<PIACC|accopt
		, bool transientw		//<LOGICAL|transient_w
		, string keynamew		//<CHAR|key_name_w

	);

/**
	\brief Open property handle for a double value

	The function opens an unbound property handle for a double value (REAL).
*/
	bool OpenFloat(
		  float dblvalue		//<REAL|dbl_value

	);

/**
	\brief Open property handle for a 32-bit integer value

	The function opens an unbound property handle for a platform independent 32-bit integer value (int32).
*/
	bool OpenInteger(
		  int intval		//<INT|int_val

	);

/**
	\brief Open a sharing copy for a property handle

	The function opens a copy of the passed property handle that shares the instance area and cursor with its origin.
*/
	bool OpenReference(
		  PropertyHandle* ppropertyhandle		//<PropertyHandle|property_handle

	);

/**
	\brief Open property handle for a string value

	The function opens an unbound property handle for a string value (STRING). The area is set to the string pointer passed to the function.
*/
	bool OpenSizedString(
		  string pstring		//<STRING|string
		, int stringlen		//<INT|string_len

	);

/**
	\brief Open property handle for a string value

	The function opens an unbound property handle for a string value (STRING). The area is allocated with the size of the string passed to the constructor. The string is copied into the instance area owned by the property handle. To enable dynamical resize featur for the property handle use the SetDynLength() function.
*/
	bool OpenString(
		  string pstring		//<STRING|string
		, bool convopt		//<LOGICAL|conv_opt

	);

/**
	\brief OPen property handle for a time value

	The function opens an unbound property handle for a time value (TIME).
*/
	bool OpenTime(
		  long timeval		//<dbtm|time_val

	);

/**
	\brief Open property handle for a date/time value

	The function opens an unbound property handle for a date/time value (DATETIME).
*/
	bool OpenTimestamp(
		  long datetimeval		//<dttm|datetime_val

	);

	// not documented
	bool OpenHierarchy(
		  PropertyHandle* bottomph		//<PropertyHandle|bottom_ph
		, PropertyHandle* topph		//<PropertyHandle|top_ph
		, bool pathopt		//<LOGICAL|path_opt
		, PIACC accmode		//<PIACC|accmode
		, bool copyselection		//<LOGICAL|copy_selection

	);

	// not documented
	bool OwnsData();

	// not documented
	bool Position(
		  int count		//<INT|count

	);

	// not documented
	bool PositionTop();

	// not documented
	PropertyHandle* Power(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

	// not documented
	bool ProvGenAttribute();

/**
	\brief Provide instance by property

	The function checks whether the property handle passes a numerical value or not. When passing a numerical value the function provides an instance at the position according to the number passed in the property handle (-> "Provide instance at position"). When the property handle contains text data, the value in the property handle is interpreted as string key, which will be converted into key and provides an instance by key value (-> "Provide instance by key value").
When the property handle refers to a complex instance of the same type or a base type of the current type in the property handle, the instance key in the passed property handle is used for locating the key.
*/
	bool Provide(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

/**
	\brief Provide instance at position

	The function tries to provide an instance at a certain position. When no instance exist at the location passed in set_pos_w, the function creates an instance by position (-> Add(): "Create Instance at position").
*/
	bool ProvideAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);

/**
	\brief Provide intsance by key value

	The function tries to provide an instance with the passed sort key (or ident-key for unordered collections). When no instance exist with the key passed in sort_key, the function creates an instance by key value (-> Add(): "Add Instance by key value").
*/
	bool ProvideByKey(
		  string sortkey		//<Key|sort_key

	);

	// not documented
	bool ProvideArea();

	// not documented
	string ProvideGUID();

	// not documented
	bool ProvideGlobal(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

	// not documented
	bool ProvideGlobalAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);

	// not documented
	bool ProvideGlobalByKey(
		  string sortkey		//<Key|sort_key

	);

	// not documented
	OperationHandle* ProvideOperation(
		  string expression		//<STRING|expression

	);

	// not documented
	bool Refresh();

	// not documented
	bool ReleaseBuffer();

	// not documented
	bool RemoveFromCollection();

	// not documented
	bool RemoveString(
		  string pstring		//<STRING|string
		, int position		//<INT|position
		, int len		//<INT|len

	);

	// not documented
	bool RemoveTerminator(
		  string pstring		//<STRING|string

	);

	// not documented
	bool Rename(
		  string newkey		//<Key|new_key

	);

	// not documented
	bool RepairIndex(
		  string keynamew		//<CHAR|key_name_w
		, string attrstrw		//<STRING|attrstr_w

	);

	// not documented
	bool ReplaceString(
		  string oldstr		//<STRING|old_str
		, string newstr		//<STRING|new_str

	);

	// not documented
	bool ReplaceSysVariables();

	// not documented
	bool Reset();

	// not documented
	void ResetDirty();

	// not documented
	bool ResetTransientProperty();

	// not documented
	bool ResetWProtect();

	// not documented
	bool Save(
		  string savopt		//<CHAR|savopt
		, bool switchopt		//<LOGICAL|switchopt

	);

	// not documented
	int SearchText(
		  string pstring		//<STRING|string
		, int curpos		//<INT|curpos
		, bool caseopt		//<LOGICAL|case_opt

	);

	// not documented
	PropertyHandle* Select(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string expression		//<STRING|expression

	);

	// not documented
	void SetActionResult(
		  string resultstring		//<STRING|result_string

	);

	// not documented
	bool SetContextVariables(
		  string contextstring		//<STRING|context_string

	);

	// not documented
	void SetDirty();

	// not documented
	bool SetDynLength();

	// not documented
	bool SetGenAttribute(
		  string attrstr		//<STRING|attrstr
		, string proppath		//<STRING|prop_path

	);

	// not documented
	bool SetKey(
		  string identkey		//<Key|ident_key

	);

	// not documented
	void SetModified();

	// not documented
	bool SetNormalized(
		  int longval		//<INT|long_val

	);

	// not documented
	bool SetOrder(
		  string keyname		//<STRING|key_name
		, string attrstr		//<STRING|attrstr

	);

	// not documented
	bool SetSelection(
		  string expression		//<STRING|expression

	);

	// not documented
	bool SetSortKey(
		  string sortkey		//<Key|sort_key

	);

	// not documented
	bool SetTransientProperty(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);

	// not documented
	bool SetType(
		  string strnames		//<STRING|strnames

	);

	// not documented
	bool SetUpdate(
		  bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValue(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueBigInt(
		  int int64val		//<INT|int64_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueBoolean(
		  bool logval		//<LOGICAL|logval
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueDate(
		  long dateval		//<dbdt|date_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueFloat(
		  float dblvalue		//<REAL|dbl_value
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueInteger(
		  int longval		//<INT|long_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueString(
		  string pstring		//<STRING|string
		, bool pcheckupdate		//<LOGICAL|check_update
		, bool convopt		//<LOGICAL|conv_opt

	);

	// not documented
	PropertyHandle* SetValueTime(
		  long timeval		//<dbtm|time_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	PropertyHandle* SetValueTimestamp(
		  long datetimeval		//<dttm|datetime_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);

	// not documented
	bool SetVersion(
		  int versionnr		//<UINT|version_nr

	);

	// not documented
	bool SetWProtect();

	// not documented
	bool ToTop();

/**
	\brief Binary union

	This implementation builds the union from the two collections passed to the operation. The result is stored in the collection referenced by the calling property handle. When the calling property handle refers to a non empty collection all instances are removed before performing the operation. When the calling property handle is empty the function creates a temporary extend for storing the result.
*/
	PropertyHandle* Union(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt
		, bool distinct		//<LOGICAL|distinct

	);

	// not documented
	bool Unlock();

	// not documented
	bool UnlockSet();

};// end of PropertyHandle slice

class OPIFactory{

	void Destroy();
	CheckOptions* GetCheckOptions();
	DBObjectHandle* GetDBObjectHandle();
	DataSourceHandle* GetDataSourceHandle();
	DatabaseHandle* GetDatabaseHandle();
	DictionaryHandle* GetDictionaryHandle();
	ODABAClient* GetODABAClient();
	OperationHandle* GetOperationHandle();
	PropertyHandle* GetPropertyHandle();
};
class Session{

	OPIFactory* CreateSession();
	void Destroy();
	void TimeOut(int seconds);
	string getName();
};
class SessionFactory{

	Session* CreateProxy(string name);
	void shutdown();
};
};//module
