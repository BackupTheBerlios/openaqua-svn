<?php
  /**
    \brief  Einspeichern eines WS requests in die KUVERT Datenbank
   */
   
  require_once("obrowse.inc.php"); //< class opiI
  require_once("oview.inc.php"); //< class opiI
    
  $b = new obrowse();
  $b->OpenFile("adk.sys","transparent.dev");
  if(isset($_REQUEST[extent])){
    $content =  oview::AjaxDataNavigation($_REQUEST[extent],$_REQUEST[index]);
    if(isset($_REQUEST[index])){
	$attributeData = $b->ExtentData($_REQUEST[extent],$_REQUEST[index]);
	$content.=  "<h1>$_REQUEST[extent],$_REQUEST[index]</h1>";
	$content.=  oview::Table($attributeData,true);
    }else{
	$attributelist = $b->AttributeList($_REQUEST[extent]);
	if(is_array($attributelist))
	    foreach($attributelist as $key=>$attribute){
		$attributelist[$key][type] = oview::AjaxExecuteLink("type",$attributelist[$key][type],$attributelist[$key][type]);
	    }
	$content.=  oview::Table($attributelist);
    }
    echo oview::AjaxReply($content);
  }else if(isset($_REQUEST[type])){
    $content =  oview::Table($b->TypeInfo($_REQUEST[type]));
    echo oview::AjaxReply($content);
  }else{
    $content = oview::Table(oview::AjaxExecuteLinks("extent",array("target"=>"name","label"=>"name"),$b->ExtentList()));
    $content = oview::AjaxView($content);
     echo oview::HTML(oview::Head("obrowser",oview::AjaxInit()),$content);
  }
  
  
?>
