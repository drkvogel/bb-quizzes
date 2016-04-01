<!DOCTYPE html>
<html>
<head>
  <title>Matrix Puzzle Complete</title>
</head>
<body>
  <h3>Matrix Puzzle Complete</h3>
  <p>Thanks.</p>
<?php 
    $firstName = $_POST["firstname"];
    $comments = $_POST["comments"];    
    //$firstName = "test";
    //$comments = "this is a test";
    echo "<p>You said your name is:</p><blockquote>".$firstName."</blockquote>";
    echo "<p>And you said:</p><blockquote>$comments</blockquote>";
    echo "<p>here are the POST contents:</p>";
    echo "<pre>".print_r($_POST)."</pre>"?>
  <hr />
</body>
</html>
