<?php
  /**
    \brief  Einspeichern eines WS requests in die KUVERT Datenbank
   */
   
  class oview {
    public function Table($data,$border=false){
	if(!is_array($data))
	    return "oview::Table::NO ARRAY";
	if($border)
	$v.="\n<table border=\"1\">";
	else
	$v.="\n<table>";
	foreach($data as $row){
	    $v.="\n<tr>";
	    foreach($row as $col){
		$v.="<td>$col</td>";
	    }
	    $v.="</tr>";
	}
	$v.="\n</table>";
	return $v;
    }
    public function AjaxDataNavigation($extent,$index){
	$prev = $index-1;
	$next = $index+1;
	$nav = "<table><tr>";
	$nav.="<td>";
	if($prev>=0) 
	    $nav.="<a href=\"Javascript:ajgetdata('$extent','$prev')\">Previous</a>";
	$nav.="</td>";
	$nav.="<td>";
	$nav.="<a href=\"Javascript:ajgetdata('$extent','*')\">All</a>";
	$nav.="</td>";
	$nav.="<td>";
	$nav.="<a href=\"Javascript:ajgetdata('$extent','$next')\">Next</a>";
	$nav.="</td>";
	$nav.="</tr></table>";
	return $nav;
    }
    public function AjaxExecuteLink($linkref,$target,$label){
	return "<a href=\"Javascript:ajget('$linkref','$target')\">$label</a>";
    }
    public function AjaxExecuteLinks($linkref,$def,$data){
	foreach($data as $row){
	    $link[href] = oview::AjaxExecuteLink($linkref,$row[$def[target]],$row[$def[label]]);
	    $links[] = $link;
	}
	return $links;
    }
    public function AjaxReply($data){
	return '<div>'.$data.'</div>';
    }
    public function Head($title,$opthead=""){
	return '<title>'.$title.'</title>'.$opthead.'';
    }
    public function HTML($head,$body){
	return "<html><head>$head</head><body><h1>Ajax OPIICE Odaba Demo</h1>$body</body></html>";
    }
    public function AjaxView($content){
	return '
	<div id="items"><h1>Extents</h1>'.$content.'</div>
	<div id="attributes"></div>
	';
    }
    public function AjaxInit(){
	global $_SERVER;
	$self = $_SERVER['PHP_SELF'];
	return '
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="ajax/prototype.js" language="JavaScript" type="text/javascript"></script>
<script type="text/javascript" language="JavaScript">
function ajgetdata(extent,index){
    var url = "'.$self.'" ;
    var params =  "extent=" + extent + "&index=" + index;
    var ajax = new Ajax.Updater({success: "attributes"},url,{method: "get", parameters: params, onFailure: reportError});
}
function ajget(type,extent) {
    var url = "'.$self.'" ;
    var params = type + "=" + extent;
    var ajax = new Ajax.Updater({success: "attributes"},url,{method: "get", parameters: params, onFailure: reportError});
}
function reportError(request) {
    $F("attributes") = "Error";
}
</script>';
    }
  }
  
?>
