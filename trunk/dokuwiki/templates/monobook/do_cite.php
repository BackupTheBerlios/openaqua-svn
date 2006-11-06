<?php
	if (!isset($_REQUEST['rev']))
		$_REQUEST['rev'] = $INFO['lastmod'];

	$permanent = DOKU_URL.DOKU_SCRIPT."?id=".$ID."&amp;rev=".$_REQUEST['rev'];
?>
<h1><a name="bibliographic_details" id="bibliographic_details">Bibliographic details for &quot;<?php tpl_pagetitle()?>&quot;</a></h2>
<div class="level2">

<ul>
<li class="level1"><div class="li"> Page name: <?php tpl_pagetitle()?></div>
</li>
<li class="level1"><div class="li"> Author: <?php echo hsc($conf['title'])?> contributors</div>
</li>
<li class="level1"><div class="li"> Publisher: <?php echo hsc($conf['title'])?>.</div>
</li>
<li class="level1"><div class="li"> Date of this revision: <?php echo date('j F Y H:i T', $_REQUEST['rev']); ?></div>
</li>
<li class="level1"><div class="li"> Date retrieved: <?php echo date('j F Y H:i T'); ?></div>
</li>
<li class="level1"><div class="li"> Permanent link: <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a></div>
</li>
<li class="level1"><div class="li"> Page Version ID: <?php echo $_REQUEST['rev']; ?> </div>

</li>
</ul>

<p>
 Please remember to check with your standards guide or professor&rsquo;s guidelines for the exact syntax to suit your needs.
</p>

</div>
<h2><a name="citation_styles_for" id="citation_styles_for">Citation styles for &quot;<?php tpl_pagetitle()?>&quot;</a></h2>
<div class="level2">

</div>

<h3><a name="apa_style" id="apa_style">APA style</a></h3>
<div class="level3">

<p>
 <?php echo hsc($conf['title'])?> contributors (<?php echo date('Y', $_REQUEST['rev']); ?>). <?php tpl_pagetitle()?>. <?php echo hsc($conf['title'])?>. Retrieved <?php echo date('H:i, j F, Y'); ?> from <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a>.
</p>

</div>
<h3><a name="mla_style" id="mla_style">MLA style</a></h3>

<div class="level3">

<p>
 &ldquo;<?php tpl_pagetitle()?>.&rdquo; <u><?php echo hsc($conf['title'])?></u>. <?php echo date('j M Y, H:i T', $_REQUEST['rev']); ?>. <?php echo date('j M Y, H:i'); ?> &lt;<a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a>&gt;.
</p>

</div>
<h3><a name="mhra_style" id="mhra_style">MHRA style</a></h3>
<div class="level3">

<p>
 <?php echo hsc($conf['title'])?> contributors, &lsquo;<?php tpl_pagetitle()?>&rsquo;, <?php echo hsc($conf['title'])?>, <?php echo date('j F Y, H:i T', $_REQUEST['rev']); ?>, &lt;<a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a>&gt; [accessed <?php echo date('j F Y'); ?>]
</p>

</div>
<h3><a name="chicago_style" id="chicago_style">Chicago style</a></h3>
<div class="level3">

<p>
 <?php echo hsc($conf['title'])?> contributors, &ldquo;<?php tpl_pagetitle()?>,&rdquo; <?php echo hsc($conf['title'])?>, <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a> (accessed <?php echo date('F j, Y'); ?>).
</p>

</div>
<h3><a name="cbe_cse_style" id="cbe_cse_style">CBE/CSE style</a></h3>

<div class="level3">

<p>
 <?php echo hsc($conf['title'])?> contributors. <?php tpl_pagetitle()?> [Internet]. <?php echo hsc($conf['title'])?>; <?php echo date('Y M j, H:i T', $_REQUEST['rev']); ?> [cited <?php echo date('Y M j'); ?>]. Available from: <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a>.
</p>

</div>
<h3><a name="bluebook_style" id="bluebook_style">Bluebook style</a></h3>
<div class="level3">

<p>

 <?php tpl_pagetitle()?>, <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a> (last visited <?php echo date('F j, Y'); ?>).
</p>

</div>
<h3><a name="ama_style" id="ama_style">AMA style</a></h3>
<div class="level3">

<p>
 <?php echo hsc($conf['title'])?> contributors. <?php tpl_pagetitle()?>. <?php echo hsc($conf['title'])?>. <?php echo date('F j, Y, H:i T', $_REQUEST['rev']); ?>. Available at: <a href="<?php echo $permanent; ?>" title="<?php echo $permanent; ?>"><?php echo $permanent; ?></a>. Accessed <?php echo date('F j, Y'); ?>.

</p>

</div>
<h3><a name="bibtex_entry" id="bibtex_entry">BibTeX entry</a></h3>
<div class="level3">
<pre>
 @misc{ wiki:xxx,
   author = &quot;<?php echo hsc($conf['title'])?>&quot;,
   title = &quot;<?php tpl_pagetitle()?> --- <?php echo hsc($conf['title'])?>&quot;,
   year = &quot;<?php echo date('Y', $_REQUEST['rev']); ?>&quot;,
   url = &quot;<?php echo $permanent; ?>&quot;,
   note = &quot;[Online; accessed <?php echo date('j-F-Y'); ?>]&quot;
 }
</pre>

<p>
When using the LaTeX package url (\usepackage{url} somewhere in the preamble), which tends to give much more nicely formatted web addresses, the following may be preferred:
</p>
<pre>
 @misc{ wiki:xxx,
   author = &quot;<?php echo hsc($conf['title'])?>&quot;,
   title = &quot;<?php tpl_pagetitle()?> --- <?php echo hsc($conf['title'])?>&quot;,
   year = &quot;<?php echo date('Y', $_REQUEST['rev']); ?>&quot;,
   url = &quot;\url{<?php echo $permanent; ?>}&quot;,
   note = &quot;[Online; accessed <?php echo date('j-F-Y'); ?>]&quot;
 }
</pre>

</div>
