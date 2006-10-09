<?php
    /**
    \author joerg@run-software.com
    \license gpl-2
    
    \brief opiice access for php scripts
    */
    
    /*
    \brief ICE ODABA Interface Base Class
	
	creates the basic handles to the ODABAICEServer
    \lang{de} erstellt die grundsaetzliche verbindung zum ODABAICEServer
    */
    
    class iceT {
    // change this as configuration
    private $host = "192.168.0.17";
    private $port = "10000";
    
    
    private $valid;
    public $sessionp;
    public $sessionfactory;
    public $session;
    public $objectfactory;
    protected $errors;
    public function __construct($name){
	    global $ICE;
    	    Ice_loadProfile($name);
	    try{
		$sessionp = $ICE->stringToProxy("session:tcp -h $this->host -p $this->port:udp -h $this->host -p $this->port -h $this->host");
    		$sessionp = $sessionp->ice_twoway();
        	$sessionfactory  = $sessionp->ice_uncheckedCast("::OPI::SessionFactory");
		$session = $sessionfactory->CreateProxy("php".time());
		$session->TimeOut(10);
		$this->objectfactory = $session->CreateSession();
		$this->valid = true;
	    } catch(Ice_LocalException $ex) {
		Header("HTTP/1.0 500 Internal Server Error");
	        echo "fatal: impossible to continue: ".$ex->unknown."\n";
	        echo "check the ICE server!";
	        exit;
	    }
	}
    /**
    \brief makeup errors created by the classes
    
	if at any point you experience a error (take care of cond and term)
	you can ask this function to makeup the error{s} into something
	readable
	this makes it possible to have multiple errors occured and not poluting the
	output with echo's
    */
    public function errortext($ashtml=0){
      if(!is_array($this->errors))
        return "";
      $text = "";
      if($ashtml) $text.= "\n<h1 id=\"errors\">";
      $text.= "Following Errors occured:\n";
      if($ashtml) $text.= "</h1>\n<ul>";
      $text.="\n";
      foreach($this->errors as $error){
        if($ashtml) $text.= "<li>";
        $text.=$error;
        if($ashtml) $text.= "</li>"; 
        $text.="\n";
      }
      if($ashtml) $text.= "</ul>";
      unset($errors);
      return $text;
    }
    };
    
?>