<?php
  /**
    \brief  Einspeichern eines WS requests in die KUVERT Datenbank
   */
   
  require_once("odaba.inc.php"); //< class opiI
    
  class ohelp extends opiI{
    public $odaba;
    protected $connected;
    public function __construct(){
	parent::__construct();
	
    }
    public function Extent($path){
	   $ph = $this->objectfactory->GetPropertyHandle();
	   if($ph->OpenExtent($this->database,$path,($readonly?OPI_PIACC::piaREAD:OPI_PIACC::piaWRITE)
	   	,false //transient
		,""))  //keyname
		echo "Failure to open $path";
	   return $ph;
    }
    public function Attributes($ph,$with_value=false){
	$indx0 = 0;
	if(!is_object($ph)) return NULL;
	while( $name = $ph->GetAttribute($indx0, false, false)){
	    $item[name] = $name;
	    if( is_numeric($name) ) $item[meta]="number";
	    else $item[meta] = "string";
	    $pha = $ph->GetPropertyHandle($name);
	    $item[type] = $pha->GetType();
	    if($with_value)
    		$item[value] = $ph->GetString( $name );
	    $data[] = $item;
	    $indx0++;
	}
	return $data;
    }
    public function Data($ph,$attlist){
      if(!is_array($attlist))
    	$attlist = $this->Attributes($ph,false);
      if(!is_array($attlist))
        return NULL;
      foreach($attlist as $att){
        $data[$att[name]] = $ph->GetString($att[name]);
      }
      return $data;
    }
    public function Collection($ph,$columns){
	$indx0 = 0;
	while($ph->GetAtPosition($indx0)){
	    unset($item);
	    foreach($columns as $name=>$datasource){
		$item[$name] = $ph->GetString($datasource);
	    }
	    $data[] = $item;
	    $indx0++;
	}
	return $data;
    }
    public function Path(){
    }
  }
  
?>
