<!DOCTYPE html>
<html>
<head>
  <title>Matrix Puzzle Complete</title>
</head>
<body>
  <h3>Matrix Puzzle Complete</h3>
  <p>Thanks.</p>
<?php 
    // show some fields that we're interested in
    echo "<p>Time started:</p><blockquote>".$_POST["timeStarted"]."</blockquote>";
    echo "<p>Results:</p><blockquote>".$_POST["responses"]."</blockquote>";

    // show whole POST contents
    $post = print_r($_POST, true);
    echo "<hr /><pre>POST contents:\n$post</pre>";

    // append to log file
    file_put_contents("comments.txt", $feedback, FILE_APPEND);
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

