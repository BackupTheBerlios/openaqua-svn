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




// -----------------------------------------------------------------

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_rssreader extends DokuWiki_Syntax_Plugin
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
                      'name' =>'RSS Reader for DokuWiki',
                      'desc' =>'Shows a RSS Newsfeed within a wiki page', 
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
        $this->Lexer->addEntryPattern ('\n {2,}<rssreader', $mode, 'plugin_rssreader');
    }

    function postConnect ()
    {
        // we end the definition list when we encounter a blank line
        $this->Lexer->addExitPattern ('>', 'plugin_rssreader');
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
$loadfeedcmd = 
<<< ENDOFSTRING
<script type="text/javascript" src="../adobespry/xpath.js"></script>
<script type="text/javascript" src="../adobespry/SpryData.js"></script>

<script type="text/javascript">
var theFeed = "http://weblogs.macromedia.com/mxna/xml/rss.cfm?query=byMostRecent&amp;languages=1";
var mydata = new Spry.Data.XMLDataSet("xmlproxy.cfm?xmlfeed="+theFeed,"//item", { useCache:  false, loadInterval: 10000 }); 
</script>
<style>
.pod {
        font-family: Arial;
        font-size: 10px;
        border: 1px solid black;
        width: 400px;
        padding: 5px;
}

.SpryHiddenRegion {
        visibility: true;
}
</style>


ENDOFSTRING;
//var rssFeed = new Spry.Data.XMLDataSet("http://www.blinklist.com/Tukaram/rss.xml","//item", { });
 
                $renderer->doc  .=  "\n\n" . $loadfeedcmd . "\n\n";
                break;
            
            case DOKU_LEXER_MATCHED:
            case DOKU_LEXER_EXIT:
                break;
            case DOKU_LEXER_UNMATCHED:


$divstring = 
<<< ENDOFSTRING
<div spry:region="mydata" class="SpryHiddenRegion">
        
        <div class="pod">

        <span spry:repeat="mydata">
        <a href="{link}"><span spry:content="{title}"></span></a><br>
        </span>
        
        </div>
        
</div>
ENDOFSTRING;
                $renderer->doc   .=  $divstring;
               //Load AdobeSpry
               break;
            }
            return true;
        }
        return false;
    }
}
