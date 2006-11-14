<?php if (isset($DOKU_TPL)==FALSE) $DOKU_TPL = DOKU_TPL; if (isset($DOKU_TPLINC)==FALSE) $DOKU_TPLINC = DOKU_TPLINC; ?>
<?php if (file_exists(DOKU_PLUGIN.'displaywikipage/code.php')) include_once(DOKU_PLUGIN.'displaywikipage/code.php'); ?>
<?php if (file_exists(DOKU_PLUGIN.'referrers/code.php')) include_once(DOKU_PLUGIN.'referrers/code.php'); ?>
<?php
@include (dirname(__FILE__).'/string_fn.php');
if (beginsWith(getenv("REMOTE_ADDR"), 'xxx')) {
 echo "<html><body><h3>You have been blocked from this server.</h3></body></html>";
} else { ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>"
 lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
   <head>
      <?php if (function_exists('re_log_referrers')) re_log_referrers(); ?>
      <?php @include(dirname(__FILE__).'/user/pref.php'); ?>
      <?php
         @include(dirname(__FILE__).'/lang/en/lang.php');
         if ( $conf['lang'] && $conf['lang'] != 'en' )
            @include(dirname(__FILE__).'/lang/'.$conf['lang'].'/lang.php');
               @include(dirname(__FILE__).'/context.php');
         //@include(dirname(__FILE__).'/other.php');
      ?>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
      <?php tpl_metaheaders()?>
      <title><?php tpl_pagetitle()?> - <?php echo hsc($conf['title'])?></title>
      <?php if (file_exists(dirname(__FILE__).'/user/favicon.ico')) { ?>
         <link rel="shortcut icon" href="<?php echo $DOKU_TPL?>user/favicon.ico" />
      <?php } ?>
      <style type="text/css" media="screen,projection">/*<![CDATA[*/ @import "<?php echo $DOKU_TPL?>monobook/main.css"; /*]]>*/</style>

      <link rel="stylesheet" type="text/css" <?php if ($_REQUEST['mbdo'] != 'print') { echo 'media="print"'; } ?> href="<?php echo $DOKU_TPL?>common/commonPrint.css" />
      <link rel="stylesheet" type="text/css" <?php if ($_REQUEST['mbdo'] != 'print') { echo 'media="print"'; } ?> href="<?php echo $DOKU_TPL?>dokuwiki/print.css" />

      <script type="text/javascript" src="<?php echo $DOKU_TPL?>common/wikibits.js"></script>
      <style type="text/css" media="screen,projection">/*<![CDATA[*/
      @import "<?php echo $DOKU_TPL?>wikipedia/Common.css";
      @import "<?php echo $DOKU_TPL?>wikipedia/Monobook.css";
      @import "<?php echo $DOKU_TPL?>dokuwiki/doku.css";
      @import "<?php echo $DOKU_TPL?>lang/<?php echo $conf['lang'];?>/lang.css";
      @import "<?php echo $DOKU_TPL?>user/Common.css";
      @import "<?php echo $DOKU_TPL?>user/Monobook.css";
      /*]]>*/</style>
    <!--[if lt IE 5.5000]><style type="text/css">@import "<?php echo $DOKU_TPL?>monobook/IE50Fixes.css";</style><![endif]-->
    <!--[if IE 5.5000]><style type="text/css">@import "<?php echo $DOKU_TPL?>monobook/IE55Fixes.css";</style><![endif]-->
    <!--[if IE 6]><style type="text/css">@import "<?php echo $DOKU_TPL?>monobook/IE60Fixes.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css">@import "<?php echo $DOKU_TPL?>monobook/IE70Fixes.css";</style><![endif]-->
    <!--[if lt IE 7]><script type="text/javascript" src="<?php echo $DOKU_TPL?>common/IEFixes.js"></script>

    <meta http-equiv="imagetoolbar" content="no" /><![endif]-->
<?php
if (file_exists(DOKU_PLUGIN.'googleanalytics/code.php')) include_once(DOKU_PLUGIN.'googleanalytics/code.php');
if (function_exists('ga_google_analytics_code')) ga_google_analytics_code();
?>
   </head>
   <body ondblclick="<?php echo $monobook['body_ondblclick']; ?>" class="<?php echo $monobook['nsclass']; ?>">
      <div id="globalWrapper">
         <div id="column-content">
            <div id="content">
               <a name="top" id="top"></a>
               <?php if ($monobook['sitenotice']) { ?><div id="siteNotice"><?php ?></div>
               <?php } ?>
               <div id="bodyContent">
                  <div class="dokuwiki">
                     <!-- start content -->
                     <?php html_msgarea()?>
                     <?php if ($conf['breadcrumbs']) { ?><div id="catlinks"><p class="catlinks"><?php tpl_breadcrumbs(); ?></p></div><?php } ?>
<div id="qsearch__out" class="ajax_qsearch JSpopup"></div>
<?php if ($_REQUEST['mbdo'] == 'cite')
      @include(dirname(__FILE__).'/do_cite.php');
   else if ($_REQUEST['mbdo'] == 'detail')
      @include(dirname(__FILE__).'/do_detail.php');
   else if ($_REQUEST['mbdo'] == 'media')
      @include(dirname(__FILE__).'/do_media.php');
   else
      tpl_content();
?>
<br/>
                     <?php if ($conf['youarehere']) { ?><div id="catlinks"><p class="catlinks"><?php tpl_youarehere(); ?></p></div><?php } ?>
                     <!-- end content -->
                     <div class="visualClear"></div>
                  </div>
               </div>
            </div>
         </div>

         <div id="column-one">
            <div class="portlet" id="p-logo">
               <a 
                  <?php if (file_exists(dirname(__FILE__).'/user/logo.png')) { ?>
                  style="background-image: url(<?php echo $DOKU_TPL?>user/logo.png);"
                  <?php } else if (file_exists(dirname(__FILE__).'/user/logo.gif')) {?>
                  style="background-image: url(<?php echo $DOKU_TPL?>user/logo.gif);"
                  <?php } else if (file_exists(dirname(__FILE__).'/user/logo.jpg')) {?>
                  style="background-image: url(<?php echo $DOKU_TPL?>user/logo.jpg);"
                  <?php } ?>
                  href="<?php echo DOKU_BASE?>" accesskey="h" title="[ALT+H]">
               </a>
            </div>

            <?php writeMBPortlet($monobook['content_actions'], 'p-cactions', '', 'ca', '1'); ?>
            <?php writeMBPortlet($monobook['navigation'], 'p-x-navigation', '', 'n'); ?>
            <?php writeMBPortlet($monobook['personal'], 'p-personal', '', 'pt'); ?>

<div id="p-search" class="portlet">
    <div class="pBody">
        <form action="<?php echo DOKU_BASE.DOKU_SCRIPT;?>" accept-charset="utf-8" id="dw__search" name="search">
            <input type="hidden" name="do" value="search" />
            <input id="qsearch__in" name="id" type="text" accesskey="f" value="" />
            <input type='button' class="searchButton" id="searchGoButton" value="<?php echo $lang['monobook_btn_go']?>" onclick="document.location.href='<?php echo DOKU_BASE.DOKU_SCRIPT;?>?id=' + document.search.qsearch__in.value;" />&nbsp;
            <input type='submit' name="fulltext" class="searchButton" value="<?php echo $lang['monobook_btn_search']?>" />
        </form>
    </div>
</div>

            <?php writeMBPortlet($monobook['toolbox'], 'p-tb','', 'tb'); ?>

         </div>
         <!-- end of the left (by default at least) column -->
         <div class="visualClear"></div>
<div id="footer">
    <a target="_blank" href="<?php echo DOKU_BASE?>feed.php" title="Recent changes RSS feed">
        <img src="<?php echo $DOKU_TPL?>dokuwiki/button-rss.png" width="80" height="15" alt="Recent changes RSS feed"
            border="0" />
     </a>
     <li id="lastmod"><?php tpl_pageinfo()?><br />
</div>
      </div>
<a href="<?php echo DOKU_BASE.DOKU_SCRIPT;?>?do=recent" accesskey="r" style="visibility:hidden;" rel="nofollow">&nbsp;</a>
      <?php tpl_indexerWebBug(); ?>
   </body>
</html>
<?php } ?>