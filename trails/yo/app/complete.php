<!DOCTYPE html>
<html>
<head>
  <title>Trails Puzzle Complete</title>
  <style type="text/css">
    body {
      cursor: default;
    }
  </style>
</head>
<body>
  <h3>Trails Puzzle Complete</h3>
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

<?php 
    // $fullname = $_POST["fullname"];
    // $email = $_POST["email"];
    // $comments = $_POST["comments"];
    // $results = $_POST["results"];

    // echo "<p>Name:</p><blockquote>$fullname</blockquote>";
    // echo "<p>Email:</p><blockquote>$email</blockquote>";
    // echo "<p>Comments:</p><blockquote>$comments</blockquote>";
?>

