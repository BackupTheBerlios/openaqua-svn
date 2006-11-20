<?php
/**
 * functions for mmKaizen DokuWiki Template
 *
 * License: GPL 2 (http://www.gnu.org/licenses/gpl.html)
 *
 * @author:   Marcin Mierzejewski <marcin@mierzejewski.net>
 * @homepage: http://www.mierzejewski.net
 */

require_once('conf.php');
 
/**
 * Displays the bottombar
 *
 * @author: Marcin Mierzejewski <marcin@mierzejewski.net>
 */
function tpl_bottombar() 
{
    global $INFO,$ID,$lang;
    $perm = $INFO['perm'];
 
 
    echo '<a href="?do=recent" class="interwiki" title="'.$lang['btn_rec'].'">'.$lang['btn_recent'].'</a>'
        .'&nbsp;&middot;&nbsp;';
    
		if( $perm > AUTH_READ ) 
		{
        echo '<a href="?do=revisions" class="interwiki" title="'.$lang['btn_revs'].'">'.$lang['btn_revs'].'</a>'
            .'&nbsp;&middot;&nbsp;';
        if(file_exists(wikiFN($ID))) {
            echo '<a href="?id='.$ID.'&amp;do=edit" class="interwiki" title="'.$lang['btn_edit'].'">'.$lang['btn_edit'].'</a>';
        } else {
            echo '<a href="?id='.$ID.'&amp;do=edit" class="interwiki" title="'.$lang['btn_create'].'">'.$lang['btn_create'].'</a>';
        }
        echo '&nbsp;&middot;&nbsp;';
		} 
		else 
		{
        echo '<a href="?id='.$ID.'&amp;do=edit" class="interwiki" title="'.$lang['btn_source'].'">'.$lang['btn_source'].'</a>'
            .'&nbsp;&middot;&nbsp;';
    }

		if($perm > AUTH_WRITE) 
		{
        echo '<a href="?do=admin" class="interwiki" title="'.$lang['btn_admin'].'">'.$lang['btn_admin'].'</a>'
            .'&nbsp;&middot;&nbsp;';
    }

		if(isset($INFO['userinfo']['name'])) 
		{
        echo '<a href="?do=logout" class="interwiki" title="'.$lang['btn_logout'].'">'.$lang['btn_logout'].'</a>';
		} 
		else 
		{
        echo '<a href="?do=login" class="interwiki" title="'.$lang['btn_login'].'">'.$lang['btn_login'].'</a>';
    }
}

/**
 * Displays the sidebar
 *
 * @author: Marcin Mierzejewski <marcin@mierzejewski.net>
 */
function tpl_renderMenu() 
{
		// Menu1
		$menu1Output = _getMenu( "menu1", false );
		if ( $menu1Output != "" )
		{
			print '<div class="Menu" id="level1">';
			print $menu1Output;
			print '</div>';
		}		
		
		// Menu1
		$menu2Output = _getMenu( "menu2", false );
		if ( $menu2Output != "" )
		{
			print '<div class="Menu" id="level2">';
			print $menu2Output;
			print '</div>';
		}		
}

function _getMenu( $menu, $edit )
{
	global $conf, $ID, $REV, $INFO, $lang;
	$currID = false;
 
	// Remember $ID and $REV
	$svID = $ID;
	$svREV = $REV;
	
	// Parent side ID
	$sub = substr($ID, 0, strpos($ID, ":"));
	
	$menuOutput = "";
	if ( file_exists(wikiFN($ID."/".$menu)) )
	{
		$menuOutput = p_wiki_xhtml($ID."/".$menu, '', false);
		$currID = $ID;
		$menuID = $currID.":".$menu;
	}
	else if ( file_exists(wikiFN($sub."/".$menu)) )
	{
		$menuOutput = p_wiki_xhtml($sub."/".$menu, '', false);
		$currID = $sub;
		$menuID = $currID.":".$menu;
	}
	
	if ( $INFO['perm'] > AUTH_READ && true == $edit )
  {
		$menuOutput = '<ul><li><a href="?id='.$menuID.'&amp;do=edit" class="wikilink1" title="Edit Menu"><b>Edit Menu</b></a></li></ul>';
  }
		
	$ID = $svID;
	$REV = $svREV;
 
	return $menuOutput;
}

function tpl_isEditMenu()
{
	global $INFO;
	$perm = $INFO['perm'];
	
	// Edit Menus
	if ( $perm > AUTH_READ )
	{
		return true;
	}
	return false;
}

function tpl_editMenu()
{
	if ( true == tpl_isEditMenu() )
	{
		// Menu1
		$menu1Output = _getMenu( "menu1", true );
		if ( $menu1Output != "" )
		{
			print '<div class="Menu" id="level1">';
			print $menu1Output;
			print '</div>';
		}		

		$menu2Output = _getMenu( "menu2", true);
		if ( $menu2Output != "" )
		{
			print '<div class="Menu" id="level2">';
			print $menu2Output;
			print '</div>';
		}		
	}
}
?>
