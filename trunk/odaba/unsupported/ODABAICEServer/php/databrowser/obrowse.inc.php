<?php
  /**
    \brief  Einspeichern eines WS requests in die KUVERT Datenbank
   */
   
  require_once("ohelp.inc.php"); //< class opiI
  
  class obrowse extends ohelp{
    public function __construct(){
	parent::__construct();
    }
    public function CreateHandles(){
	if($this->OpenFile("adk.sys","adk.dev")){
	  var_dump($this->errors);
	  return;
	}
    }
    public function ExtentList(){
	$db = $this->database;
	$this->database = $this->dictionary;
	$extents = $this->Extent("SDB_Extend");
	$this->database = $db;
	$edata = $this->Collection($extents,array("name"=>"sys_ident"));
	return $edata;
    }
    public function ExtentData($path,$index){
	$extent = $this->Extent($path);
	if($index!="*"){
	    $index+=1;
	    $index-=1;
	    $extent->GetAtPosition($index);
	    return $this->Attributes($extent,true);
	}
	$index = 0;
	$attributes = $this->Attributes($extent);
	while($extent->GetAtPosition($index)){
	    $attributedata[] = $this->Data($extent,$attributes);
	    $index++;
	}
	return $attributedata;
    
    }
    public function AttributeList($path){
	$extent = $this->Extent($path);
	return $this->Attributes($extent);
    }
    public function TypeInfo($name){
	$db = $this->database;
	$this->database = $this->dictionary;
	$attributes = $this->Extent("SDB_Type");
	$this->database = $db;
	$found = false;
	$indx = 0;
	while(!$found && $attributes->GetAtPosition($indx)){
	  if($attributes->GetString("sys_ident") == $name)
	    $found = true;
	  $indx++;
	}
	
	$edata = $this->Attributes($attributes);
	return $edata;
    }
  }
?>
