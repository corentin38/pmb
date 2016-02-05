<!doctype html>
<html lang="fr">
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="##meta-desc##" />
    <meta name="author" content="##meta-author##" />
    <!--    <link rel="icon" href="meta-icon" /> -->
    <title>##meta-title##</title>
    <!-- Bootstrap core CSS -->
    <link href="##meta-conf-bootstrap##" rel="stylesheet" />
    <!-- Custom styles for this template -->
    <link href="##meta-conf-css##" rel="stylesheet" />
  </head>
  
  <body>
    <div class="blog-masthead">
      <div class="container">
    	<nav class="blog-nav">
    	  <a class="blog-nav-item active" href="#">Blog</a>
          <!-- #BEGINTABLE nav-items -->
    	  <a class="blog-nav-item" href="##nav-href##">##nav-item##</a>
          <!-- #ENDTABLE nav-items -->
    	</nav>
      </div>
    </div>
    
    <div class="container">
      
      <div class="blog-header">
    	<h1 class="blog-title">##title##</h1>
    	<p class="lead blog-description">##subtitle##</p>
      </div>
      
      <div class="row">
        <div class="col-sm-8 blog-main">
          
          <!-- #BEGINTABLE posts -->      	  
    	  <div class="blog-post">
    		<h2 class="blog-post-title">##post-title##</h2>
    		<p class="blog-post-meta">##post-date## par <a href="##post-author-link##">##post-author##</a></p>
    		##post-life##
    	  </div>
          <!-- #ENDTABLE posts -->
    	  
    	  <nav>
    		<ul class="pager">
    		  <li><a href="##prev-page-link##">Previous</a></li>
    		  <li><a href="##next-page-link##">Next</a></li>
    		</ul>
    	  </nav>
    	  
    	</div>
    	
    	<div class="col-sm-3 col-sm-offset-1 blog-sidebar">
    	  <div class="sidebar-module sidebar-module-inset">
    		<h4>##about-line##</h4>
    		<p>##about##</p>
    	  </div>
    	  
    	  <!-- Candy -->
    	  <div class="sidebar-module">
    		<h4>##links-line##</h4>
    		<ol class="list-unstyled">
              <!-- #BEGINTABLE links -->
    		  <li><a href="##link-href##">##link-item##</a></li>
              <!-- #ENDTABLE links -->
    		</ol>
    	  </div>
    	</div>
      </div>
    </div>
    
    <footer class="blog-footer">
      <p>
    	##philosophy##<br/>
    	<a href="#">##backtotop##</a>
      </p>
    </footer>
    
    <!-- Bootstrap core JavaScript
    	 ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <script src="dist/js/bootstrap.min.js"></script>
  </body>
</html>
