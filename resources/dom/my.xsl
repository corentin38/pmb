<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">

    <xsl:variable name="configuration-file" select="document( 'config.xml' )"/>
    <xsl:variable name="conf" select="$configuration-file/config"/>
    
    <xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>
    <html lang="fr">
      <head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
	<meta name="description" content="{$conf/meta-desc}" />
	<meta name="author" content="{$conf/meta-author}" />
	<link rel="icon" href="{$conf/meta-icon}" />
	
	<title><xsl:value-of select="$conf/meta-title"/></title>
	
	<!-- Bootstrap core CSS -->
	<link href="dist/css/bootstrap.min.css" rel="stylesheet" />
	
	<!-- Custom styles for this template -->
	<link href="{$conf/meta-conf-css}" rel="stylesheet" />
      </head>
      
      <body>
	<!-- Tout ce bordel viendra du putain de xml de config <<<<<<<<    -->
	<div class="blog-masthead">
	  <div class="container">
	    <nav class="blog-nav">
	      <a class="blog-nav-item" href="{$conf/nav-home/@href}"><xsl:value-of select="$conf/nav-home"/></a>
	      <a class="blog-nav-item active" href="#">Blog</a>
	      <xsl:for-each select="$conf/nav-items/item">
		<a class="blog-nav-item" href="{@href}"><xsl:value-of select="."/></a>
	      </xsl:for-each>
	    </nav>
	  </div>
	</div>
	
	<div class="container">
	  
	  <div class="blog-header">
	    <h1 class="blog-title"><xsl:value-of select="$conf/title"/></h1>
	    <p class="lead blog-description"><xsl:value-of select="$conf/subtitle"/></p>
	  </div>

	  <div class="row">

            <div class="col-sm-8 blog-main">

              <xsl:for-each select="posts/post">
		<xsl:sort select="@date" order="descending"/>

		
		<div class="blog-post">
		  <h2 class="blog-post-title"><xsl:value-of select="title"/></h2>
		  <p class="blog-post-meta"><xsl:value-of select="@date"/> par <a href="#"><xsl:value-of select="@author"/></a></p>

		  <p><xsl:copy-of select="mylife"/></p>
		</div><!-- /.blog-post -->
              </xsl:for-each>

	      
	      <nav>
		<ul class="pager">
		  <li><a href="{posts/@prev}">Previous</a></li>
		  <li><a href="{posts/@next}">Next</a></li>
		</ul>
	      </nav>
	      
	    </div><!-- /.blog-main -->
	    
	    <div class="col-sm-3 col-sm-offset-1 blog-sidebar">
	      <div class="sidebar-module sidebar-module-inset">
		<h4><xsl:value-of select="$conf/about/@line"/></h4>
		<p><xsl:copy-of select="$conf/about"/></p>
	      </div>
	      
	      <!-- Candy -->
	      <div class="sidebar-module">
		<h4><xsl:value-of select="$conf/links/@line"/></h4>
		<ol class="list-unstyled">
		  <xsl:for-each select="$conf/links/item">
		    <li><a href="{@href}"><xsl:value-of select="."/></a></li>
		  </xsl:for-each>
		</ol>
	      </div>
	    </div><!-- /.blog-sidebar -->
	  </div>
	</div>
	
	<footer class="blog-footer">
	  <p>
	    <xsl:copy-of select="$conf/footer/philosophy"/><br/>
	    <a href="#"><xsl:value-of select="$conf/footer/backtotop"/></a>
	  </p>
	</footer>
	
	
	<!-- Bootstrap core JavaScript
	     ================================================== -->
	<!-- Placed at the end of the document so the pages load faster -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
	<script src="dist/js/bootstrap.min.js"></script>
      </body>
    </html>
    
  </xsl:template>
  
</xsl:stylesheet> 
