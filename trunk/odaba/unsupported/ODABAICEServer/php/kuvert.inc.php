<?php
		
  require_once("odaba.inc.php");

  /**
  \brief Transparent Datenbank
	
	Oeffnet die Transparent Datenbank
  */  
  class Transparent extends opiI{
    public $odaba;
    public function __construct(){
	parent::__construct();
	$this->Open("transparent");
    }
  };
  
  /**
  \brief Kuvert Datenbehandlung
  
	Die Klasse Kuvert stellt fuer die
	Applikation funktionen bereit, die die
	daten aufbereitet in php-arrays zur verfuegung stellt.
  */
  class Kuvert extends Transparent{
    public function __construct(){
      parent::__construct();
    }
    /**
    \brief Liste der Vertraege
    
	    Erstellt ein mehrdimensionales Array mit ausgewaehlten
	    Vertragsinformationen
    */
    public function VertragListe(){
	$vertraege = $this->Extent("Action");
	$indx = 0;
	while($vertraege->GetAtPosition($indx)){
	    $item[name]     = $vertraege->GetString("typ");
	    $item[erstellt] = date("d.M.Y H:i",$vertraege->GetDate("created"));  //< datumskonvertierung, GetDate liefert Unix Timestamp

	    $liste[] = $item;
	    $indx++;
	}
	return $liste;
    }
    /**
    \brief Liste der Gesellschaften
    
	    Erstellt ein mehrdimensionales Array mit ausgewaehlten 
	    Gesellschaftsinformationen.
	    die Anzahl der Vertraege wird ueber die Beziehung zu 'actions'(Vertraege) ermittelt
    */
    public function GesellschaftListe(){
	$gesellschaften = $this->Extent("s_Gesellschaft");
	$vertraege = $gesellschaften->GetPropertyHandle("actions");
	$indx = 0;
	while($gesellschaften->GetAtPosition($indx)){
	  $item[name] = $gesellschaften->GetString("name");
	  $item[anz_vertrag] = $vertraege->GetCount();
	  
	  $liste[] = $item;
	  $indx++;
	}
	return $liste;
    }
    /**
    \brief Liste der Berufsgruppen
    
	    Erstellt ein mehrdimensionales Array mit ausgewaehlten 
	    Berufsgruppeninformationen.
    */
    public function BerufsgruppeListe(){
	$berufsgruppe = $this->Extent("s_Berufsgruppe");
	$indx = 0;
	while($berufsgruppe->GetAtPosition($indx)){
	  $item[name] = $berufsgruppe->GetString("name");
	  $item[extern] = $berufsgruppe->GetString("extern_id");
	  $item[oeffentlicherdienst] = $berufsgruppe->GetString("od");
	  $liste[] = $item;
	  $indx++;
	}
	return $liste;
	
    }
  };    
?>
