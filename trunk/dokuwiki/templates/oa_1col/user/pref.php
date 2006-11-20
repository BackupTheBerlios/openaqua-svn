<?php

/** Individual Preferences
 * for Monobook for DokuWiki
 * By Terence J. Grant
 * tjgrant [at] tatewake [dot] com
 * License: GPL v2
 *
 * Updated : 23/04/2006, Etienne Gauthier (etiennegauthier [at] free [dot] com)
 *   Add of the local_pref.php file, to easily keep configuration when switching to a newer configuration of monobook.
 */


/*
 *  Default configuration file.
 *
 * This file contains all default value for the monobook configuration template for DokuWiki. It loads the local_pref.php (if it exists).
 * Then, it fills in all non set configuration variable.
 *
 * Thus : 
 * 1) This file should not be modified any more by monobook's users.
 * 2) All needed configuration should be put into the local_pref.php file (to be created in the same directory as the pref.php file).
 * 3) When upgrading monobook : the file will remain intact, as it is not 'given' in the monobook distibution. A backup is still always useful.
 *
 */


@include(dirname(__FILE__).'/local_pref.php');

/*
@include (dirname(__FILE__).'/../lang/en/lang.php');
         if ( $conf['lang'] && $conf['lang'] != 'en' )
            @include (dirname(__FILE__).'/../lang/'.$conf['lang'].'/lang.php');
*/
 
/* Change Edit to [Edit] */
$lang['btn_secedit'] = '['.$lang['btn_secedit'].']';

/* Usage of certain features... */
if (!isset($monobook['discussion']))
    $monobook['discussion'] = 1;

if (!isset($monobook['footer']))
    $monobook['footer']['page']['wiki_page'] = ':wiki:footer';
    
if (!isset($monobook['discussion-location']))
    $monobook['discussion-location'] = "talk";

/* Site notice */
if (!isset($monobook['sitenotice']))
    $monobook['sitenotice'] = ':wiki:site_notice';

/* Copyright */
if (!isset($monobook['copyright']))
    $monobook['copyright'] = ":wiki:copyright";

/* Navigation : link to a wiki page called 'navigation', in the 'wiki' namespace */
if (!isset($monobook['navigation']))
    $monobook['navigation']['page']['wiki_page'] = ':wiki:navigation';

/* Toolbox */
if (!isset($monobook['toolbox'])) {
    $monobook['toolbox']['whatlinkshere']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;do=backlink";
    $monobook['toolbox']['whatlinkshere']['text'] = $lang['monobook_whatlinkshere'];
    $monobook['toolbox']['whatlinkshere']['rel'] = "nofollow";
    
    $monobook['toolbox']['upload']['href'] = DOKU_BASE."lib/exe/mediamanager.php?ns=".getNS($ID);
    $monobook['toolbox']['upload']['text'] = $lang['monobook_upload'];
    $monobook['toolbox']['upload']['rel'] = "nofollow";
    
    $monobook['toolbox']['special']['href'] = DOKU_BASE."doku.php?idx=wiki";
    $monobook['toolbox']['special']['text'] = $lang['monobook_specialpage'];
    $monobook['toolbox']['special']['rel'] = "nofollow";
    
if (isset($_REQUEST['rev']))
    $monobook['toolbox']['print']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$_REQUEST['rev']."&amp;mbdo=print";
else
    $monobook['toolbox']['print']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$INFO['lastmod']."&amp;mbdo=print";

    $monobook['toolbox']['print']['text'] = $lang['monobook_print'];
    $monobook['toolbox']['print']['rel'] = "nofollow";

if (isset($_REQUEST['rev']))
    $monobook['toolbox']['permanent']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$_REQUEST['rev'];
else
    $monobook['toolbox']['permanent']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$INFO['lastmod'];

    $monobook['toolbox']['permanent']['text'] = $lang['monobook_permanent'] ;

//"Permanent Link";
    $monobook['toolbox']['permanent']['rel'] = "nofollow";
    
if (isset($_REQUEST['rev']))
    $monobook['toolbox']['cite']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$_REQUEST['rev']."&amp;mbdo=cite";
else
    $monobook['toolbox']['cite']['href'] = DOKU_BASE."doku.php?id=".$ID."&amp;rev=".$INFO['lastmod']."&amp;mbdo=cite";

    $monobook['toolbox']['cite']['text'] = $lang['monobook_cite'];
    $monobook['toolbox']['cite']['rel'] = "nofollow";
}


?>
