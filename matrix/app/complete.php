<!DOCTYPE html>
<html>
<head>
  <title>Matrix Puzzle Complete</title>
</head>
<body>
  <h3>Matrix Puzzle Complete</h3>
  <p>Thanks.</p>
<?php 
    $fullname = $_POST["fullname"];
    $email = $_POST["email"];
    $comments = $_POST["comments"];    
    //$firstName = "test";
    //$comments = "this is a test";
    echo "<p>Name:</p><blockquote>$fullname</blockquote>";
    echo "<p>Email:</p><blockquote>$email</blockquote>";
    echo "<p>Comments:</p><blockquote>$comments</blockquote>";
    // echo "<hr /><p>POST contents:</p>";
    // echo "<pre>".print_r($_POST, true)."</pre>"
    echo "\n<!-- POST contents:\n".print_r($_POST, true)."-->";
?>
  <hr />
</body>
</html>
