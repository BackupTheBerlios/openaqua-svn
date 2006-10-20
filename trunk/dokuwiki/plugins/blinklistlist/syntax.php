<?php
/**
 * Allow storing of blinklist clouds
 * <blinklist whichone>
 *
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Claudia.Behrens (at) openaqua.de>
 *
 */
if (!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if (!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');
include_once("class_rss_parser/class_rss_parser.php");




// -----------------------------------------------------------------

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blinklistlist extends DokuWiki_Syntax_Plugin
{
    var $stack = array ();

    /**
     * return some info
     */
    function getInfo ()
    {
        return array ('author' =>'Claudia Behrens',
                      'email' =>'info@openaqua.de',
                      'date' =>'2006-10-20',
                      'name' =>'Blinklist List Plugin',
                      'desc' =>'Shows a blinklist list on to a wiki page', 
                      'url' =>'http://wiki.durga-online',
                      );
    }


    function getType ()
    {
        return 'container';
    }


    function getSort ()
    {
        return 10;
    }


    /**
     * Connect pattern to lexer
     */

    function connectTo ($mode)
    {
        $this->Lexer->addEntryPattern ('\n {2,}<blinklistlist', $mode, 'plugin_blinklistlist');
    }

    function postConnect ()
    {
        // we end the definition list when we encounter a blank line
        $this->Lexer->addExitPattern ('>', 'plugin_blinklistlist');
    }



    /**
     * Handle the match
     */
    function handle ($match, $state, $pos, &$handler)
    {
        if ($state == DOKU_LEXER_UNMATCHED) {
            return array ($state, $match);
        } else {
            return array ($state, '');
        }
    }



    /**
     * Create output
     */
    function render ($mode, &$renderer, $data)
    {
        list ($state, $param) = $data;
        if ($mode == 'xhtml') {
            switch ($state) {
            case DOKU_LEXER_ENTER:
            case DOKU_LEXER_MATCHED:
            case DOKU_LEXER_EXIT:
                break;
            case DOKU_LEXER_UNMATCHED:
               {
                  $renderer->doc .= "<p>davor</p>";
                  $rss=new RSS_parser();
                  $rss->rss_parse("http://www.blinklist.com/Tukaram/rss.xml");
                  $ch=$rss->get_channel_data();
                  $ch_im=$rss->get_channel_image_data();
                  $ch_ti=$rss->get_channel_textinput_data();
                  $items=$rss->get_items_data();
                  foreach($items as $item) {
                      $renderer->doc .= "----<br/>\n";
                      foreach($item as $key=>$val) {
                          $renderer->doc .= "<b>$key:</b> $val\n";
                      }
                  }
                
                $renderer->doc .= "<p>danach</p>";
                break;
               }
            }
            return true;
        }
        return false;
    }




}
