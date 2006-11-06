<?php
/**
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Esther Brunner <wikidesign@gmail.com>
 */

// must be run within Dokuwiki
if(!defined('DOKU_INC')) die();

if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'action.php');

class action_plugin_oazen extends DokuWiki_Action_Plugin {

  /**
   * return some info
   */
  function getInfo(){
    return array(
      'author' => 'Esther Brunner',
      'email'  => 'wikidesign@gmail.com',
      'date'   => '2006-09-05',
      'name'   => 'oazen Plugin',
      'desc'   => 'Brings oazen functionality to DokuWiki',
      'url'    => 'http://wiki:splitbrain.org/plugin:oazen',
    );
  }

  /**
   * register the eventhandlers
   */
  function register(&$contr){
    $contr->register_hook('ZenShow',
                          'BEFORE',
                          $this,
                          'handle_act_preprocess',
                           array());
                              

  }

  
  /**
   * Checks if 'newentry' was given as action, if so we
   * do handle the event our self and no further checking takes place
   */
  function handle_act_preprocess(&$event, $param){
    //if ($event->data != 'newentry') return; // nothing to do for us
    
    global $ACT;
    global $ID;
    
    echo "param=$param";
    return;

    // we can handle it -> prevent others
    $event->stopPropagation();
    $event->preventDefault();
    
    
    $ns    = $_REQUEST['ns'];
    $title = str_replace(':', '', $_REQUEST['title']);
    $id    = ($ns ? $ns.':' : '').cleanID($title);
    
    // check if we are allowed to create this file
    if (auth_quickaclcheck($id) >= AUTH_CREATE){
      $back = $ID;
      $ID   = $id;
      $file = wikiFN($ID);
      
      //check if locked by anyone - if not lock for my self      
      if (checklock($ID)){
        $ACT = 'locked';
      } else {
        lock($ID);
      }

      // prepare the new thread file with default stuff
      if (!@file_exists($file)){
        global $TEXT;
        global $INFO;
        global $conf;
        
        $TEXT = pageTemplate($ns.':'.$title);
        if (!$TEXT) $TEXT = "====== $title ======\n\n\n\n".
                            "~~DISCUSSION~~\n";
        $ACT = 'preview';
      } else {
        $ACT = 'edit';
      }
    } else {
      $ACT = 'show';
    }
  }

}

//Setup VIM: ex: et ts=4 enc=utf-8 :
