<?php
   /**
    * Theme Sandy 2
    * @author neolao <neo@neolao.com>
    * @author Claudia Behrens < Claudia.Behrens@openaqua.de>
    * @link   http://resources.neolao.com/php/dokuwiki/templates
    */
   
   //secure the php file from direct access
   if (!defined('DOKU_INC')) die(); 
   
   
   //set up a couple of variables
   if (isset($DOKU_TPL)==FALSE) $DOKU_TPL = DOKU_TPL; 
   if (isset($DOKU_TPLINC)==FALSE) $DOKU_TPLINC = DOKU_TPLINC;
   if (!empty($INFO['userinfo'])) $user = true;

   //use displaywikipage for the menu (if exists)
   if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php');
   //use the referrers plugin (if exists)      
   if (file_exists(DOKU_PLUGIN.'referrers/code.php')) include_once(DOKU_PLUGIN.'referrers/code.php');
   
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>" lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">

<!--##################################################HTML HEADER-->
<head>
   <?php 
      if (function_exists('re_log_referrers')) re_log_referrers();
      @include (dirname(__FILE__).'/string_fn.php');
      @include(dirname(__FILE__).'/user/pref.php');
      @include(dirname(__FILE__).'/context.php');

      
      /*make page title*/
      echo '<title>';  tpl_pagetitle(); echo ' - ' . strip_tags($conf['title']) . "</title>\n";
      
      //Add meta headers
      echo '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
      tpl_metaheaders();
      
      //add a page icon
      echo '<link rel="shortcut icon" href="<' . DOKU_TPL . '/favicon.ico" />' . "\n";
      
      //add googleanalytics support
      if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
      if (file_exists(DOKU_PLUGIN.'googleanalytics/code.php')) include_once(DOKU_PLUGIN.'googleanalytics/code.php');
      if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
    
    
      //don't show edit buttons if user is not logged in
      if ($conf['useacl'] ) {
         if(! $_SERVER['REMOTE_USER']) {
            echo '<style type="text/css">';
            echo '<!--';
            echo '.secedit {display:none;}';
            echo '-->';
            echo '</style>';
         }
      }
   ?>
</head>


   
    
    
<!--##################################################HTML BODY-->
    <body>
        <div id="header"><?php tpl_link(wl(),'<img src="'.DOKU_TPL.'images/banner.png" alt="'.hsc($conf['title']).'"/>','name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[ALT+H]"')?></div>
        <div id="menu">
            <ul>
                <?php include('menu.php'); ?>
            </ul>
        </div>
      <div id="body">
            <div id="body_top"></div>
            <p><?php tpl_youarehere(); ?></p>
         <?php flush(); ?>
            <?php tpl_content(); ?>
            <?php flush(); ?>
            <div id="body_bottom"></div>
      </div>
        <div id="footer">
            <?php tpl_searchform()?>
            <ul>
                <li><?php tpl_actionlink('edit'); ?></li>
                <li><?php tpl_actionlink('login'); ?></li>
            </ul>
            <ul>
                <li><a href="http://dokuwiki.org/wiki:dokuwiki">DokuWiki</a></li>
            <?php if ($user) { ?>
                <li><?php tpl_actionlink('profile')?></li>
                <li><?php tpl_actionlink('admin'); ?>&nbsp;</li>
            <?php } ?>
            </ul>
        </div>
    </body>
</html>
