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

    $feedback = print_r($_POST, true);
    echo "\n<!-- POST contents:\n$feedback-->";

    file_put_contents("comments.txt", $feedback, FILE_APPEND);
?>
  <hr />
</body>
</html>
