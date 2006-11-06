<?php
/**
 * Archive Plugin: displays links to all wiki pages from a given month
 * 
 * @license  GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author   Esther Brunner <wikidesign@gmail.com>
 */

if(!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blog_archive extends DokuWiki_Syntax_Plugin {

  /**
   * return some info
   */
  function getInfo(){
    return array(
      'author' => 'Esther Brunner',
      'email'  => 'wikidesign@gmail.com',
      'date'   => '2006-09-06',
      'name'   => 'Blog Plugin (archive component)',
      'desc'   => 'Displays a list of wiki pages from a given month',
      'url'    => 'http://wiki.splitbrain.org/plugin:blog',
    );
  }

  function getType(){ return 'substition'; }
  function getPType(){ return 'block'; }
  function getSort(){ return 309; }
  function connectTo($mode) { $this->Lexer->addSpecialPattern('\{\{archive>.+?\}\}',$mode,'plugin_blog_archive'); }

  /**
   * Handle the match
   */
  function handle($match, $state, $pos, &$handler){
    $match = substr($match,10,-2); // strip {{archive> from start and }} from end
    list($ns, $rest) = explode("?", $match);
    if (!$rest){
      $rest = $ns;
      $ns   = '';
    }
    
    // monthly archive
    if (preg_match("/\d{4}-\d{2}/", $rest)){
      list($year, $month) = explode("-", $rest);
      return array($ns, $month, $year);
    }
    
    return false;
  }

  /**
   * Create output
   */
  function render($mode, &$renderer, $data) {
    global $ID;
    global $conf;
    
    $ns = $data[0];
    if ($ns == '') $ns = cleanID($this->getConf('namespace'));
    elseif ($ns == '*') $ns = '';
    elseif ($ns == '.') $ns = getNS($ID);
    
    $pages = $this->_monthArchive($ns, $data[1], $data[2]);
    
    if (!count($pages)) return true; // nothing to display
    
    if ($mode == 'xhtml'){
      
      // prevent caching to ensure content is always fresh
      $renderer->info['cache'] = false;
  
      $renderer->doc .= '<table class="archive">';
      foreach ($pages as $page){
        $renderer->doc .= '<tr><td class="page">';
        
        // page title
        $id    = $page['id'];
        $title = $page['title'];
        if (!$title) $title = str_replace('_', ' ', noNS($id));
        $renderer->doc .= $renderer->internallink(':'.$id, $title).'</td>';
        
        // author
        if ($this->getConf('archive_showuser')){
          if ($page['user']) $renderer->doc .= '<td class="user">'.$page['user'].'</td>';
          else $renderer->doc .= '<td class="user">&nbsp;</td>';
        }
        
        // creation date
        if ($this->getConf('archive_showdate')){
          $renderer->doc .= '<td class="date">'.date($conf['dformat'], $page['date']).
            '</td>';
        }
        $renderer->doc .= '</tr>';
      }
      $renderer->doc .= '</table>';
      
      return true;
      
    // for metadata renderer
    } elseif ($mode == 'metadata'){
      foreach ($pages as $page){
        $id  = $page['id'];
        $renderer->meta['relation']['references'][$id] = true;
      }
      
      return true;
    }
    return false;
  }
  
  /**
   * Return the monthly archive list
   */
  function _monthArchive($ns, $month, $year){
    global $conf;

    // calculate start and end times
    $nextmonth = $month + 1;
    $year2     = $year;
    if ($nextmonth > 12){
      $nextmonth = 1;
      $year2     = $year + 1;
    }
    
    $monthstart  = mktime(0, 0, 0, $month, 1, $year);
    $monthend    = mktime(0, 0, 0, $nextmonth, 1, $year2);
        
    // load page and creation date index
    $page_idx  = file($conf['cachedir'].'/page.idx');
    $cdate_idx = file($conf['cachedir'].'/cdate.idx');
    
    // add pages in given namespace
    $result = array();
    $c = count($page_idx);
    for ($i = 0; $i < $c; $i++){
      $id = substr($page_idx[$i], 0, -1);
      
      // do some checks first
      if (isHiddenPage($id)) continue;                     // skip excluded pages
      if (($ns) && (strpos($id, $ns.':') !== 0)) continue; // filter namespaces
      if (!@file_exists(wikiFN($id))) continue;            // skip deleted
      $perm = auth_quickaclcheck($id);
      if ($perm < AUTH_READ) continue;                     // check ACL
            
      // in right date range?
      $cdate = substr($cdate_idx[$i], 0, -1);
      if (!$cdate) $cdate = $this->_getCdate($id, $i, $cdate_idx);
      if (($monthstart > $cdate) || ($cdate >= $monthend)) continue;
      
      // okay, add the page
      $meta = p_get_metadata($id);
      $result[$cdate] = array(
        'id'     => $id,
        'title'  => $meta['title'],
        'user'   => $meta['creator'],
        'date'   => $cdate,
        'exists' => true,
        'perm'   => $perm,
      );
    }
    
    // finally sort by creation time
    krsort($result);
        
    return $result;
  }
  
  /**
   * Get the creation date of a page from metadata or filectime
   */
  function _getCdate($id, $pid, &$idx){
    global $conf;
    
    $cdate = p_get_metadata($id, 'date created');
    if (!$cdate) $cdate = filectime(wikiFN($id));
    
    // check lines and fill creation date in
    for ($i = 0; $i < $pid; $i++){
      if (empty($idx[$i])) $idx[$i] = "\n";
    }
    $idx[$pid] = "$cdate\n";
    
    // save creation date index
    $fh = fopen($conf['cachedir'].'/cdate.idx', 'w');
    if (!$fh) return false;
    fwrite($fh, join('', $idx));
    fclose($fh);
    
    return $cdate;
  }

}

//Setup VIM: ex: et ts=4 enc=utf-8 :
