<?php
  /**
    \brief einfaches beispiel zur kuvert datenbank
    
	    Die *Liste Funktionen aus der PHP Klasse Kuvert
	    werden zur darstellung an eine View Funktion uebergeben
	    dies ist ein sehr einfaches beispiel die erhaltenen daten zu nutzen
   */
   
  require_once("odaba.inc.php"); //< class Kuvert
    
  class View extends opiI{
    public $odaba;
    public function __construct(){
	parent::__construct();
	$this->Open("transparent");
    }
    public function drawNotiz($notiz){
      $draw.= "\n".$notiz->GetString("typ")." ".$notiz->GetString("betreff");
      return $draw;
    }
    public function drawActor($actor){
      $draw.="\n  ".$actor->GetString("name");
      $draw.="\n  ".$actor->GetString("vorname");
      $draw.="\n  ".$actor->GetString("kennung");
    }
    public function test(){
       $action = $this->Extent("Action");
       $vertrag = $action->GetPropertyHandle("vertrag");
       $vn      = $action->GetPropertyHandle("versicherungsnehmer");
       $partner = $action->GetPropertyHandle("partner");
       $notiz   = $action->GetPropertyHandle("notizen");
       echo $action->GetCount();
       $indx = 0;
       while($action->GetAtPosition($indx)){
         echo "\n".$indx.":".$action->GetString("typ");
	 echo "\n Vertrag:".$this->drawNotiz($vertrag);
	 $vn->GetAtPosition(0);
	 $partner->GetAtPosition(0);
	 echo "\n VN:".$this->drawActor($vn);
	 echo "\n Partner:".$this->drawActor($partner);
	 if($notiz->GetCount()>0){
    	    echo "\n Notizen:";
	    while($notiz->GetAtPosition($notiz->GetCurrentIndex()+1)){
	      echo $this->drawNotiz($notiz);
	    }
	  }
         $indx++;
       }
       /*
       echo $action->ToTop();
       while($action->GetAtPosition($action->GetCurrentIndex()+1)){
         echo $action->GetString("typ");
       }*/
    }
  }
 
  $v = new View();
  $v->test();
  
?>
