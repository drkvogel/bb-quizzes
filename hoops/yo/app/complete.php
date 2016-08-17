<!DOCTYPE html>
<html>
<head>
  <title>Hoops Puzzle Complete</title>
  <style type="text/css">
    body {
      cursor: default;
    }
  </style>
</head>
<body>
  <h3>Hoops Puzzle Complete</h3>
  <p>Thank you.</p>
<?php 
    $responses = $_POST["responses"];

    // show some fields that we're interested in
    echo "<hr /><p>Time started:</p><blockquote>".$_POST["timeStarted"]."</blockquote>";
    echo "<p>Answers:</p><blockquote>".$responses."</blockquote>";

    // show whole POST contents
    $post = print_r($_POST, true);
    echo "<hr /><pre>POST contents:\n$post</pre>";

    // append to log file
    file_put_contents("comments.txt", $responses, FILE_APPEND);
?>
  <hr />
</body>
</html>
