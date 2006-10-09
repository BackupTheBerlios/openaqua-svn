<?php
  class View{
    protected $data;
    public function __construct(){
    }
    public function DrawArrayTable($array ){
        if(is_array($array))
    	    $this->data = $array;
        
        if(!is_array($this->data)) return "\n<!-- no array to draw -->";
	$html.="\n<table>";
	$html.="\n\t<tr>";
        foreach($this->data[0] as $key=>$value){
	  $html.="<th>$key</th>";
	}
	$html.="</tr>";
	foreach($this->data as $item){
    	    $html.="\n\t<tr>";
    	    foreach($item as $value){
		$html.="<td>$value</td>";
	    }
	    $html.="</tr>";
        }
	$html.="\n</table>";
	return $html;
    }
  }

?>
