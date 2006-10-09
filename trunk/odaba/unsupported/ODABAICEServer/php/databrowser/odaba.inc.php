<?php
    /**
    \author joerg@run-software.com
    \license gpl-2
    
    \brief odaba access for php scripts
    */
    require "opiice.inc.php";
      
    /**
    \brief OPI basic wrapping of essential odaba functions
    
	this makes it easier to learn how to use the objects without having the trouble with long parameter lists
	the 3 basic handles are requested from the object factory and Open attempts to fill them with live 

    \lang{de} OPI einfaches verpacken der wichtigsten ODABA funktionen
    
	fuer simple anwendungen, die objekte benutzen wollen stellen die funktienen eine einfachen einstiegspunkt bereit,
	ohne dass gelernt werden muss, was all die parameter bedeuten
	die 3 grundlegenden objekte werden von der ObjektFabrik erfragt und Open fuellt sie mit leben
    */
    class opiI extends iceT{
    protected $odabaclient;
    protected $dictionary;
    protected $database;
    /**
    \brief path of databases
	a location that can be accessed with the opiice user on the machine the opiiceserver is running
    \lang{de} pfad zu den datenbanken
	ein dateisystempfad den der opiice nutzer auf dem computer wo der opiiceserver laeuft lesen und schreiben darf
    */
    protected $basepath = "/data/data/";   
    /**
    \brief Konstruktor
	opens the profile "opi" /etc/ice/profile.ini
	creates empty handles from the objectfactory
    */
    public function __construct(){
    	    parent::__construct("opi");
	    $this->odabaclient = $this->objectfactory->GetODABAClient();
	    // the dictionary is in short the structure information
	    // you need it to know what is where in the database
	    // technical it is just a database and can be used like it
	    $this->dictionary  = $this->objectfactory->GetDictionaryHandle();
	    // the database is the storage for the data
	    $this->database    = $this->objectfactory->GetDatabaseHandle();	  
	}
    /**
    \brief Open Data
	opens the database and the dictionary from the $this->basepath with a
	naming convention (*.dev: dictionary, *.dat: database)
    */	
    public function Open($dbname,$readonly=0){
	    return $this->OpenFile($this->basepath.$dbname.".dev",$this->basepath.$dbname.".dat",$readonly);
	}
    /**
    \brief Open Data
	opens the database and the dictionary by file - more generic function to
	enable access to different named datasources
    */
    public function OpenFile($dict,$dat,$readonly=0){
	    $dict = $this->basepath.$dict;
	    $dat = $this->basepath.$dat;
	    $term = 
	    $this->dictionary->OpenDictionary($this->odabaclient,$dict,($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
		,false   //net
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC //resourcetype
		,false); // sysenv
	    if($term) $this->errors[] = "Open of Dictionary ($dict) failed";
	    $term = $term |
	    $this->database->OpenDatabase($this->dictionary,$dat,($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
		,false  //net
		,false  //online
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC
		,false);  //sysenv
	    if($term) $this->errors[] = "Open of Database ($dat) failed";
	    return $term;
    }
    /**
    \brief Connect to a ODABAServer
	connects to a odabaserver and opens the exported datasources.
	read the /etc/odaba/odabaserver.ini to find out what is exported
	the export names are expected to be gerneric *_DAT and *_DICT
    */
    public function Connect($server,$dbname,$readonly = 0){
            $term =  
	    $this->odabaclient->Connect($server,6123,"");
	    if($term) $this->errors[] =  "Failed to Connect to ODABAServer [$server:6123]\n";
	    
	    $term = $term |
	    $this->dictionary->OpenDictionary($this->odabaclient,"%${dbname}_DICT%", OPI_PIACC::piaREAD // dont, just dont write!
		,true   //net
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC//resourcetype
		,false); // sysenv
	    if($term) $this->errors[] = "Open of Dictionary (%${dbname}_DICT%) failed in CS Mode";
	    $term = $term |
	    $this->database->OpenDatabase($this->dictionary,"%${dbname}_DAT%",($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
		,true  //net
		,false  //online
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC
		,false);  //sysenv
	    if($term) $this->errors[] = "Open of Database (%${dbname}_DAT%) failed in CS Mode";
	    return $term;
	}
    /**
    \brief disconnect the odabaclient
	you have to disconnect the odabaclient when the connection was successfull
	call Close in every case you used opiice
    */
    public function Close(){
	if($this->odabaclient->IsConnected())
	  $this->odabaclient->Disconnect();
    }
    };
?>