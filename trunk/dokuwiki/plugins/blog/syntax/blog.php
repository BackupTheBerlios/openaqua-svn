<?php
/**
 * Blog Plugin: displays a number of recent entries from the blog subnamespace
 * 
 * @license  GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author   Esther Brunner <wikidesign@gmail.com>
 * @author   Robert Rackl <wiki [at] doogie [dot] de>
 */

if(!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blog_blog extends DokuWiki_Syntax_Plugin {

  /**
   * return some info
   */
  function getInfo(){
    return array(
      'author' => 'Esther Brunner',
      'email'  => 'esther@kaffeehaus.ch',
      'date'   => '2006-09-06',
      'name'   => 'Blog Plugin (blog component)',
      'desc'   => 'Displays a number of recent entries from a given namesspace',
      'url'    => 'http://wiki.splitbrain.org/plugin:blog',
    );
  }

  function getType(){ return 'substition'; }
  function getPType(){ return 'block'; }
  function getSort(){ return 307; }
  function connectTo($mode) { $this->Lexer->addSpecialPattern('\{\{blog>.+?\}\}',$mode,'plugin_blog_blog'); }

  /**
   * Handle the match
   */
  function handle($match, $state, $pos, &$handler){
    $match = substr($match, 7, -2); // strip {{blog> from start and }} from end
    list($ns, $num) = explode('?', $match, 2);
    if (!is_numeric($num)){
      if (is_numeric($ns)){
        $num = $ns;
        $ns  = '';
      } else {
        $num = 5;
      }
    }

    return array($ns, $num);
  }

  /**
   * Create output
   */
  function render($mode, &$renderer, $data){
    global $conf;
    global $ID;
    
    $ns = $data[0];
    if ($ns == '') $ns = cleanID($this->getConf('namespace'));
    elseif ($ns == '*') $ns = '';
    elseif ($ns == '.') $ns = getNS($ID);
    
    $num   = $data[1];
    $first = $_REQUEST['first'];
    if (!is_numeric($first)) $first = 0;
    $more  = false;
    
    // get recent pages from our blog namespace
    $recents = $this->_getRecents($first, $num, $ns, $more);
    $num = count($recents);
              
    if ($mode == 'xhtml'){
      define('IS_BLOG_MAINPAGE', 1);
            
      // prevent caching to ensure the included pages are always fresh
      $renderer->info['cache'] = false;

      // current section level
      $clevel = 0;
      preg_match_all('|<div class="level(\d)">|i', $renderer->doc, $matches, PREG_SET_ORDER);
      $n = count($matches)-1;
      if ($n > -1) $clevel = $matches[$n][1];
      
      // close current section
      if ($clevel) $renderer->doc .= '</div>';
      
      // now include the blog entries
      foreach ($recents as $recent){
        $this->_include($renderer, 'section', $recent, $clevel, $this->getConf('firstseconly'));
      }
      
      // resume the section
      if ($clevel) $renderer->doc .= '<div class="level'.$clevel.'">';
            
      // show older / newer entries links
      $renderer->doc .= $this->_browseEntriesLinks($more, $first, $data[1], $ID);
      
      // show new entry form
      if (auth_quickaclcheck($ns.':*') >= AUTH_CREATE)
        $renderer->doc .= $this->_newEntryForm($ns);
                  
      return true;
      
    // for metadata renderer
    } elseif ($mode == 'metadata'){
      foreach ($recents as $recent){
        $id = $recent['id'];
        $renderer->meta['relation']['haspart'][$id] = true;
      }
      
      return true;
    }
    return false;
  }
    
/* ---------- Recent Pages Functions ---------- */
  
  /**
   * Collect additional information about the wanted recent pages
   */
  function _getRecents($first, $num, $ns, &$more){
    global $conf;
    global $ID;
    
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
      
      // prevent include recursion 
      if ($id == $ID) continue;
      if ($this->_inFilechain($id)) continue;   
      
      // okay, add the page
      $cdate = substr($cdate_idx[$i], 0, -1);
      if (!$cdate) $cdate = $this->_getCdate($id, $i, $cdate_idx);
      $result[$cdate] = array(
        'id'     => $id,
        'date'   => $cdate,
        'exists' => true,
        'perm'   => $perm,
      );
    }
    
    // finally sort by creation time...
    krsort($result);
    
    // ... and slice the needed chunk of pages
    if (count($result) > ($first + $num)) $more = true;
    $result = array_slice($result, $first, $num);
        
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
  
/* ---------- (X)HTML Output Functions ---------- */
    
  /**
   * Displays links to older newer entries of the blog namespace
   */
  function _browseEntriesLinks($more, $first, $num, $id){
    $ret = '';
    $last = $first+$num;
    if ($first > 0){
      $first -= $num;
      if ($first < 0) $first = 0;
      $ret .= '<p class="centeralign"><a href="'.wl($id, 'first='.$first).'" class="wikilink1">&lt;&lt; '.$this->getLang('newer').'</a>';
      if ($more) $ret .= ' | ';
      else $ret .= '</p>';
    } else if ($more){
      $ret .= '<p class="centeralign">';
    }
    if ($more){
      $ret .= '<a href="'.wl($id, 'first='.$last).'" class="wikilink1">'.$this->getLang('older').' &gt;&gt;</a></p>';
    }
    return $ret;
  }
  
  /**
   * Displays a form to enter the title of a new entry in the blog namespace
   * and then open that page in the edit mode
   */
  function _newEntryForm($ns){
    global $lang;
    global $ID;
    
    return '<div class="newentry_form">'.
      '<form id="blog__newentry_form" method="post" action="'.script().'" accept-charset="'.$lang['encoding'].'">'.
      '<div class="no">'.
      '<input type="hidden" name="id" value="'.$ID.'" />'.
      '<input type="hidden" name="do" value="newentry" />'.
      '<input type="hidden" name="ns" value="'.$ns.'" />'.
      '<label class="block" for="blog__newentry_title">'.
      '<span>'.$this->getLang('newentry').'</span> '.
      '<input class="edit" type="text" name="title" id="blog__newentry_title" size="40" tabindex="1" /></label>'.
      '<input class="button" type="submit" value="'.$lang['btn_create'].'" tabindex="2" />'.
      '</div>'.
      '</form>'.
      '</div>';
  }
    
/* ---------- Inclusion Functions ---------- */
  
  /**
   * Builds the XHTML to embed the page to include
   */
  function _include(&$renderer, $type, $data, $clevel = 0, $firstseconly = false){ 
    global $filechain;
    
    $id      = $data['id'];
    $section = $data['section'];
    
    array_push($filechain, $id.'#'.$section);
     
    // get instructions and render them on the fly
    $file             = wikiFN($id);
    $data['filepath'] = $file;
    $instr = p_cached_instructions($file, false); 
    if (!empty($instr)){
      if ($section) $instr = $this->_getSection($section, $instr); 
      $instr   = $this->_convertInstructions($instr, $id, $renderer, $clevel, $h,$firstseconly);
      if ($firstseconly) $instr = $this->_readMore($instr, $id);
      $content = p_render('xhtml', $instr, $info);
      $content = $this->_cleanXHTML($content, $tags);
      $data['tags'] = $tags;

      // embed the included page
      $renderer->doc .= '<div class="include">';
      if (!$h && $clevel && ($type == 'section'))
        $renderer->doc .= '<div class="level'.$clevel.'">';
      $renderer->doc .= $content.$this->_editButton($data);
      if (!$h && $clevel && ($type == 'section'))
        $renderer->doc .= '</div>';
      $renderer->doc .= '</div>';
      $renderer->doc .= $this->_metaLine($data, $renderer);
    }
    
    array_pop($filechain);
    
    return true;
  }
  
  /**
   * Checks if the page to include is already included (prevent recursion)
   */
  function _inFilechain($id, $section = ''){
    global $filechain;
    if (!isset($filechain)) $filechain = array();
    
    $id = preg_quote($id,'/');
    $section = preg_quote($section,'/');
    
    $pattern = $section ? "/^($id#$section|$id#)$/" : "/^$id#/";
    $match = preg_grep($pattern, $filechain);
    return (!empty($match));
  }  
     
  /** 
   * Get a section including its subsections 
   */ 
  function _getSection($title, $instructions){ 
    foreach ($instructions as $instruction){ 
      if ($instruction[0] == 'header'){ 
 
        // found the right header 
        if (cleanID($instruction[1][0]) == $title){ 
          $level = $instruction[1][1]; 
          $i[] = $instruction; 
 
        // next header of the same or higher level -> exit 
        } elseif ($instruction[1][1] <= $level){ 
          return $i; 
        } elseif (isset($level)){ 
          $i[] = $instruction; 
        } 
 
      // add instructions from our section 
      } elseif (isset($level)){ 
        $i[] = $instruction; 
      } 
    } 
    return $i; 
  } 
 
  /** 
   * Corrects relative internal links and media and 
   * converts headers of included pages to subheaders of the current page 
   */ 
  function _convertInstructions($instr, $incl, &$renderer, $clevel, &$h, $firstseconly = false){ 
    global $ID; 
    global $conf; 
 
    // check if included page is in same namespace 
    $iNS = getNS($incl);
    if (getNS($ID) == $iNS) $convert = false; 
    else $convert = true; 
 
    $n = count($instr); 
    for ($i = 0; $i < $n; $i++){ 
 
      // convert internal links and media from relative to absolute 
      if ($convert && (substr($instr[$i][0], 0, 8) == 'internal')){ 
 
        // relative subnamespace 
        if ($instr[$i][1][0]{0} == '.'){
          // parent namespace
          if ($instr[$i][1][0]{1} == '.')
            $instr[$i][1][0] = getNS($iNS).':'.substr($instr[$i][1][0], 2);
          // current namespace
          else
            $instr[$i][1][0] = $iNS.':'.substr($instr[$i][1][0], 1);
 
        // relative link 
        } elseif (strpos($instr[$i][1][0], ':') === false){
          $instr[$i][1][0] = $iNS.':'.$instr[$i][1][0];
        }
 
      // set header level to current section level + header level 
      } elseif ($instr[$i][0] == 'header'){ 
        $level = $instr[$i][1][1]+$clevel; 
        if ($level > 5) $level = 5; 
        $instr[$i][1][1] = $level; 
 
        // add TOC items 
        if ($level >= $conf['toptoclevel'] && $level <= $conf['maxtoclevel']){ 
          $text = $instr[$i][1][0]; 
          $hid  = $renderer->_headerToLink($text, 'true'); 
          $renderer->toc[] = array( 
            'hid'   => $hid, 
            'title' => $text, 
            'type'  => 'ul', 
            'level' => $level-$conf['toptoclevel']+1 
          );
          
          $h = true;
        } 
 
      // the same for sections 
      } elseif ($instr[$i][0] == 'section_open'){ 
        $level = $instr[$i][1][0]+$clevel; 
        if ($level > 5) $level = 5; 
        $instr[$i][1][0] = $level; 
 
      // show only the first section? 
      } elseif ($firstseconly && ($instr[$i][0] == 'section_close') && ($instr[$i-1][0] != 'section_open')){ 
        if ($instr[0][0] == 'document_start') return array_slice($instr, 1, $i); 
        else return array_slice($instr, 0, $i); 
 
      } 
    } 
    if ($instr[0][0] == 'document_start') return array_slice($instr, 1, -1); 
    else return $instr; 
  } 
 
  /** 
   * Remove TOC, section edit buttons and tags 
   */ 
  function _cleanXHTML($xhtml, &$tags){
    preg_match('!<div class="tags">.*?</div>!s', $xhtml, $match);
    $tags    = $match[0];
    $replace = array( 
      '!<div class="toc">.*?(</div>\n</div>)!s'   => '', // remove toc 
      '#<!-- SECTION "(.*?)" \[(\d+-\d*)\] -->#e' => '', // remove section edit buttons 
      '!<div class="tags">.*?(</div>)!s'          => '', // remove category tags 
    );
    $xhtml  = preg_replace(array_keys($replace), array_values($replace), $xhtml); 
    return $xhtml; 
  } 
 
  /** 
   * Display an edit button for the included page 
   */ 
  function _editButton($data){ 
    $ret = ''; 
    if (!isset($data['perm'])) $data['perm'] = auth_quickaclcheck($data['id']);
    if ($data['exists']){ 
      if (($data['perm'] >= AUTH_EDIT) && (is_writable($data['filepath'])))
        $ret = '<div class="secedit">'.
          html_btn('edit', $data['id'], '', array('do' => 'edit'), 'post').
          '</div>'; 
    } elseif ($data['perm'] >= AUTH_CREATE){ 
      $ret = '<div class="secedit">'.
        html_btn('create', $data['id'], '', array('do' => 'edit'), 'post').
        '</div>'; 
    } 
    return $ret;
  } 
  
  /**
   * Adds a read more... link at the bottom of the first section
   */
  function _readMore($instr, $id){
    $last    = $instr[count($instr)-1];
    if ($last[0] == 'section_close') $instr = array_slice($instr, 0, -1);
    $instr[] = array('p_open', array(), $last[2]);
    $instr[] = array('internallink', array($id, $this->getLang('readmore')), $last[2]);
    $instr[] = array('p_close', array(), $last[2]);
    if ($last[0] == 'section_close') $instr[] = $last;
    return $instr;
  }
  
  /**
   * Returns the meta line below the included page
   */
  function _metaLine($data, &$renderer){
    global $conf;
    
    $id   = $data['id'];
    $meta = p_get_metadata($id);
    $ret  = array();
        
    // permalink
    if ($this->getConf('showlink')){
      $title = ($data['title'] ? $data['title'] : $meta['title']);
      if (!$title) $title = str_replace('_', ' ', noNS($id));
      $ret[] = $renderer->internallink($id, $title, '', true);
    }
    
    // author
    if ($this->getConf('showuser')){
      $author   = ($data['user'] ? $data['user'] : $meta['creator']);
      if ($author){
        $userpage = cleanID($this->getConf('user_namespace').':'.$author);
        $ret[]    = $renderer->internallink($userpage, $author, '', true);
      }
    }
    
    // date
    if ($this->getConf('showdate')){
      $date  = ($data['date'] ? $data['date'] : $meta['date']['created']);
      $ret[] = date($conf['dformat'], $date);
    }
           
    // comments
    $cfile = metaFN($id, '.comments');
    if (@file_exists($cfile) && !$data['section']){
      $comments = unserialize(io_readFile($cfile, false));
      if ($comments['status']){
        $discuss = $id.'#'.cleanID($this->getLang('discussion'));
        $noc     = $comments['number'];
        if ($noc == 0) $comment = '0 '.$this->getLang('comments');
        elseif ($noc == 1) $comment = '1 '.$this->getLang('comment');
        else $comment = $noc.' '.$this->getLang('comments');
        $ret[] = $renderer->internallink($discuss, $comment, '', true);
      }
    }
    
    $ret = $data['tags'].implode(' &middot; ', $ret);
    if (!$ret) $ret = '&nbsp;';
    return '<div class="inclmeta">'.$ret.'</div>';
  }
        
}

//Setup VIM: ex: et ts=4 enc=utf-8 :
