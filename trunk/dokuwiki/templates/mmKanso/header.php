<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<?php
/**
 * DokuWiki Default Template
 *
 * This is the template you need to change for the overall look
 * of DokuWiki.
 *
 * You should leave the doctype at the very top - It should
 * always be the very first line of a document.
 *
 * @link   http://wiki.splitbrain.org/wiki:tpl:templates
 * @author Andreas Gohr <andi@splitbrain.org>
 * @author Michael Klier <chi@chimeric.de>
 * additional editing by
 * @author Marcin Mierzejewski <marcin@mierzejewski.net>
 */
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>"
 lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
<head>
  <title> <?php echo hsc($conf['title'])?> :: <?php tpl_pagetitle()?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="Keywords" content="<?php if ( $conf['tpl_mmKanso']['keywords'] ) echo $conf['tpl_mmKanso']['keywords'].","; ?><?php tpl_pagetitle()?>"/>
  <meta name="Description" content="<?php if ( $conf['tpl_mmKanso']['description'] ) echo $conf['tpl_mmKanso']['description']; ?><?php tpl_pagetitle()?>"/>
  <?php tpl_metaheaders()?>
  <link rel="stylesheet" media="screen" type="text/css" href="<?php echo DOKU_TPL?>css/design.css" />
  <link rel="stylesheet" media="screen" type="text/css" href="<?php echo DOKU_TPL?>css/menu.css" />
  <link rel="stylesheet" media="screen" type="text/css" href="<?php echo DOKU_TPL?>css/gallery.css" />

  <style type="text/css">
   body { behavior: url("<?php echo DOKU_TPL?>csshover.htc"); }
  </style>

  <?php /*old includehook*/ @include(dirname(__FILE__).'/meta.html')?>
</head>
