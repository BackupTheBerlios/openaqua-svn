<?php
  /**
    \brief einfaches beispiel zur kuvert datenbank
    
	    Die *Liste Funktionen aus der PHP Klasse Kuvert
	    werden zur darstellung an eine View Funktion uebergeben
	    dies ist ein sehr einfaches beispiel die erhaltenen daten zu nutzen
   */
   
  require_once("kuvert.inc.php"); //< class Kuvert
  require_once("helper.inc.php"); //< class View
    
  $k = new Kuvert();
  $v = new View();
  
  echo $v->DrawArrayTable($k->VertragListe());
  echo $v->DrawArrayTable($k->GesellschaftListe());
  echo $v->DrawArrayTable($k->BerufsgruppeListe());

?>
