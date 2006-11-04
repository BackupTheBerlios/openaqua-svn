<?php
/**
 */

// must be run from within DokuWiki
if (!defined('DOKU_INC')) die();
if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');

$myNamespacePrefix          = 'openaqua';
$myPAGENAVIGATION           = ':wiki:navigation';
$myPAGEHEADERNAVIGATION     = ':wiki:headernavigation';
$myDefaultPageContact       = $myNamespacePrefix . ':contact';
$myDefaultPageAbout         = $myNamespacePrefix . ':about';
$myDefaultPagePrivacyPolice = $myNamespacePrefix . ':privacypolicy';
$myDefaultPageCopyRight     = $myNamespacePrefix . ':copyright';
$myLogo                     = '<B><FONT COLOR="#ff0000">#</FONT><FONT COLOR="#666666">define</FONT>
<FONT COLOR="#333333">OpenAqua</FONT></B>';
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
 
<!--##################################################HTML HEADER-->
<head>
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      
      /*make page title*/
      echo '<title>';  tpl_pagetitle(); echo ' - ' . strip_tags($conf['title']) . "</title>\n";
      
      //Add meta headers
      echo '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
      tpl_metaheaders();
      @include(dirname(__FILE__).'/meta.html');
    
   ?>
   
   <!-- to correct the unsightly Flash of Unstyled Content. http://www.bluerobot.com/web/css/fouc.asp -->
	<script type="text/javascript"></script>


   <!--
		@import "http://www.csszengarden.com/184/184.css";
   -->
      

	<style type="text/css" media="all">
	
		@import "http://www.zeuscms.gr/zengarden/sample.css";
	</style>
	
</head>


<!--##################################################HTML BODY-->

   <!--

   	This xhtml document is marked up to provide the designer with the maximum possible flexibility.
   	There are more classes and extraneous tags than needed, and in a real world situation, it's more
   	likely that it would be much leaner.

   	However, I think we can all agree that even given that, we're still better off than if this had been
   	built with tables.


   -->

   <body onload="window.defaultStatus='css Zen Garden: The Beauty in CSS Design';" id="css-zen-garden">

   <div id="container">
   
   	<div id="intro">
         <!--Logo!!-->
   		<div id="pageHeader">
   		   <h1><span><?php tpl_link(wl(),$conf['title'],'accesskey="h" title="[ALT+H]"')?></span></h1>
   			<h2><span>The Beauty of <acronym title="Cascading Style Sheets">CSS</acronym> Design</span></h2>
   		</div>

         <!--subtitle for the website-->
   		<div id="quickSummary">

   			<p class="p1"><span>A demonstration of what can be accomplished visually through <acronym title="Cascading Style Sheets">CSS</acronym>-based design. Select any style sheet from the list to load it into this page.</span></p>
   			<p class="p2"><span>Download the sample <a href="zengarden-sample.html" title="This page's source HTML code, not to be modified.">html file</a> and <a href="zengarden-sample.css" title="This page's sample CSS, the file you may modify.">css file</a></span></p>
   		</div>

         <!--????-->
   		<div id="preamble">

   			<h3><span>The Road to Enlightenment</span></h3>
   			<p class="p1"><span>Littering a dark and dreary road lay the past relics of browser-specific tags, incompatible <acronym title="Document Object Model">DOM</acronym>s, and broken <acronym title="Cascading Style Sheets">CSS</acronym> support.</span></p>
   			<p class="p2"><span>Today, we must clear the mind of past practices. Web enlightenment has been achieved thanks to the tireless efforts of folk like the <acronym title="World Wide Web Consortium">W3C</acronym>, <acronym title="Web Standards Project">WaSP</acronym> and the major browser creators.</span></p>

   			<p class="p3"><span>The css Zen Garden invites you to relax and meditate on the important lessons of the masters. Begin to see with clarity. Learn to use the (yet to be) time-honored techniques in new and invigorating fashion. Become one with the web.</span></p>
   		</div>
   	</div>
      
      
      <div id="supportingText">
         <?php tpl_content();?>
      </div>
      
      <div id="linkList">
   		<!--extra div for flexibility - this list will probably be the trickiest spot you'll deal with -->

   		<div id="linkList2">

   		<!-- If you're wondering about the extra &nbsp; at the end of the link, it's a hack to meet WCAG 1 Accessibility. -->
   		<!-- I don't like having to do it, but this is a visual exercise. It's a compromise. -->
   			<div id="lselect">
	            <?php if ($conf['useacl'] ) {if(! $_SERVER['REMOTE_USER']) {    echo '<!--';   }} ?>
   				<h3 class="select"><span>Select a Design:</span></h3>
   				<!-- list of links begins here. There will be no more than 8 links per page -->
   				<ul>
                  <li ><?php tpl_actionlink('edit');   ?> </li>
                  <li ><?php tpl_actionlink('history');   ?> </li>
                  <li ><?php tpl_actionlink('recent');   ?> </li>
      			</ul>
               <?php if ($conf['useacl'] ) {if(! $_SERVER['REMOTE_USER']) {    echo '-->';   }} ?>
   			</div>

   			<div id="larchives">
   				<h3 class="archives"><span>Archives:</span></h3>
   				<ul>

   					<li><a href="/" title="View next set of designs. AccessKey: n" accesskey="n"><span class="accesskey">n</span>ext designs &raquo;</a>&nbsp;</li>
   					<li><a href="/" title="View previous set of designs. AccessKey: p" accesskey="p">&laquo; <span class="accesskey">p</span>revious designs</a></li>
   					<li><a href="http://www.mezzoblue.com/zengarden/alldesigns/" title="View every submission to the Zen Garden. AccessKey: w" accesskey="w">Vie<span class="accesskey">w</span> All Designs</a></li>
   				</ul>

   			</div>

   			<div id="lresources">
   				<h3 class="resources"><span>Resources:</span></h3>
   				<ul>
   					<li><a href="http://www.csszengarden.com/001/001.css" title="View the source CSS file for the currently-viewed design, AccessKey: v" accesskey="v"><span class="accesskey">V</span>iew This Design&#8217;s <acronym title="Cascading Style Sheets">CSS</acronym></a></li>
   					<li><a href="http://www.mezzoblue.com/zengarden/resources/" title="Links to great sites with information on using CSS. AccessKey: r" accesskey="r"><acronym title="Cascading Style Sheets">CSS</acronym> <span class="accesskey">R</span>esources</a></li>

   					<li><a href="http://www.mezzoblue.com/zengarden/faq/" title="A list of Frequently Asked Questions about the Zen Garden. AccessKey: q" accesskey="q"><acronym title="Frequently Asked Questions">FA<span class="accesskey">Q</span></acronym></a>&nbsp;</li>
   					<li><a href="http://www.mezzoblue.com/zengarden/submit/" title="Send in your own CSS file. AccessKey: s" accesskey="s"><span class="accesskey">S</span>ubmit a Design</a></li>
   					<li><a href="http://www.mezzoblue.com/zengarden/translations/" title="View translated versions of this page. AccessKey: t" accesskey="t"><span class="accesskey">T</span>ranslations</a></li>
   				</ul>
   			</div>
   		</div>

   	</div>
   	
   	
   </div>

   <!-- These extra divs/spans may be used as catch-alls to add extra imagery. -->
   <!-- Add a background image to each and use width and height to control sizing, place with absolute positioning -->
   <div id="extraDiv1"><span></span></div><div id="extraDiv2"><span></span></div><div id="extraDiv3"><span></span></div>
   <div id="extraDiv4"><span></span></div><div id="extraDiv5"><span></span></div><div id="extraDiv6"><span></span></div>

</body>
</html>


