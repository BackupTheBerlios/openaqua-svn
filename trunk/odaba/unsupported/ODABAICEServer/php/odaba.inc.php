<?php
    /*
    \brief ICE ODABA Interface Base Class
	
	creates the basic handles to the ODABAICEServer
    \lang{de} erstellt die grundsaetzliche verbindung zum ODABAICEServer
    */
    
    class iceT {
//    private $host = "192.168.0.17";
    private $host = "0xn0.de";
    private $port = "10000";
    public $sessionp;
    public $sessionfactory;
    public $session;
    public $objectfactory;
    public function __construct($name){
	    global $ICE;
    	    Ice_loadProfile($name);
	    try{
		$sessionp = $ICE->stringToProxy("session:tcp -h $this->host -p $this->port:udp -h $this->host -p $this->port -h $this->host");
    		$sessionp = $sessionp->ice_twoway();
        	$sessionfactory  = $sessionp->ice_uncheckedCast("::OPI::SessionFactory");
		$session = $sessionfactory->CreateProxy("php".time());
		$this->objectfactory = $session->CreateSession();
	    } catch(Ice_LocalException $ex) {
	        echo "warning impossible to continue: ".$ex->unknown."\n";
		if($debug>3)
		    var_dump($ex);
		exit(0);
	    }
	}
    };
    
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
	    $this->dictionary->OpenDictionary($this->odabaclient,$this->basepath.$dbname.".dev",($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
		,false   //net
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC //resourcetype
		,false); // sysenv
	    $this->database->OpenDatabase($this->dictionary,$this->basepath.$dbname.".dat",($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
		,false  //net
		,false  //online
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC
		,false);  //sysenv
	   
	}
    /**
    \brief Open a Extent
	this wraps the access to a extent (someting comparable to a table) to a single call
	the returned propertyhandle can be used for operation
    \lang{de} Oeffnet einen Extent
	Die erstellung auf eines extents (etwas vergleichbar mit einer tabelle) zu einem funktionsaufruf zusammengefasst.
	das zurueckgegebene propertyhandle kann fuer alle weiteren datenbankoperationen benutzt werden
    */
    public function Extent($path,$readonly=0){
	   $ph = $this->objectfactory->GetPropertyHandle();
	   $ph->OpenExtent($this->database,$path,($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
	   	,false //transient
		,"");  //keyname
	   return $ph;
	}
    };
?>