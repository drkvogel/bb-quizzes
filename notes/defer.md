## defer

errors reported by ff
.replace() e.g. `alert($("a").css("margin-top").replace("px", ""));`

hoops - abandon seems to trigger of its own accord


`bb-quizzes/matrix/main-jon.js`
I’d just do something like this to centre the tiles of the matrix:  

```html
<div style="width: 75%; margin: auto">
    ...
</div>
```

tidy up matrix, hoops
leave comments shows previous puzzle on resize

hourglass if wait on submit?
//$("body").css("cursor", "progress"); // $("body").css("cursor", "default");
or
$(window).on('beforeunload', function(){
   $('*').css("cursor", "progress");
});
* If possible a busy/hourglass cursor could be displayed while data is uploading [don't spend more than an hour on this - if it's not easy to do, then forget it].  


## fossilised

matrix: centre divs
matrix: space lower tiles
matrix: add text
hoops: abandon button doesn't do anything
hoops: answers in config - depends on order...
hoops: puzzles are hard coded and not in pseudo-random order
prev, next should be closer together, and not off the bottom

standardise text sizes

bower install imageMapResizer?
stose responsive test site?
range of normal aspect ratios
gulp desktop notification on error
or via browsersync

http://stackoverflow.com/questions/4083351/what-does-jquery-fn-mean/4083362 jQuery.fn === jQuery.prototype


IIFE to prevent hoisting - but maybe we want global vars to maintain state?

http://stackoverflow.com/questions/9741328/why-do-we-need-a-fieldset-tag
