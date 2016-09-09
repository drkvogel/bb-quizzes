## defer

Matrix : structure, technology and algorithms
Hoops : structure, technology and algorithms

pandoc markdown \newpage and \pagebreak - neither seems to work
errors reported by ff
hoops - abandon seems to trigger of its own accord
cache image for next page
`bb-quizzes/matrix/main-jon.js`
uncomputable?
\newpage in pandoc worked!
.replace() e.g. `alert($("a").css("margin-top").replace("px", ""));`

scaling - thought I'd fixed my basic one on tuesday? What happened?
yes, the matrix on red scrolls, but the localhost one with scaleImagesCBsimple() doesn't so scaleImagesAY() is redundant, but...
2x2 still "larger" than 3x3 - tiles are bigger cause there's less of them to fill the same space
hoops images too small on large screen
preload
device-width initial
js script page height
make divs text-align, not margin-auto-?
take out float?
or... why not, instead of setting the margins, set max-width? (and margin: auto)

use flag instead of unbind to debounce
make modular
    libcog.js: commonjs, requirejs, amd, browserify, webpack...
    yeoman/gulp is providing modularity via bower/wiredep? 2016-08-23 modular js.md
https://lodash.com/docs
.done() - Promises?

pesticide stopped working in q108-vlubuntu ff
suppressAbandon -> showAbandon


matrix: get rid of blank images; unnecessary bandwidth
abandon POST var, etc


scale func left over in aborted gulp/browsersync-served window, that actually works...:

```js
function scaleImagesCBsimple() {
    console.log('scaleImagesCBsimple()');
    var widthExtra = $('.container').outerWidth(true) - $('.container').width() + ($('#pages').outerWidth(true) - $('#pages').width());
    var heightExtra = // required height of .gridContainer
    ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
     ($('.botText').is(':visible') ? $('.botText').height() : 0) + 75;
    var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;
    if (setMargins > 0) {
        $('.gridContainer').css('margin-left', setMargins);
        $('.gridContainer').css('margin-right', setMargins);
    } else {
        // don't set negative margins. content should shrink width-wise if needed
        $('.gridContainer').css('margin-left', 0);
        $('.gridContainer').css('margin-right', 0);
    }
}
```

matrix heightScrolled: 53 with text still at large size before media query breakpoint, and height squash
still more heights to add?

cap min image size at, say, 100px
    .middleImg {  min-width: 100px; } but left margin pushes it rightwards

hoops scaleImages() that kind of works (pretty printed in Chrome dev tools from minified version deployed on red)

```js
function r() {
    console.log("scaleImages()");
    var t = ($(window).width() - $(window).height()) / 2;
    i("$(window).width(): " + $(window).width() + ", $(window).height()" + $(window).height() + ", margins: " + t),
    $(".middleImg").css("margin-left", t),
    $(".middleImg").css("margin-right", t)
}
```



## fossilised

matrix: centre divs
matrix: space lower tiles
matrix: add text
hoops: abandon button doesn't do anything
hoops: answers in config - depends on order...
hoops: puzzles are hard coded and not in pseudo-random order
prev, next should be closer together, and not off the bottom

bower install imageMapResizer?
stose responsive test site?
range of normal aspect ratios
gulp desktop notification on error or via browsersync
http://stackoverflow.com/questions/4083351/what-does-jquery-fn-mean/4083362 jQuery.fn === jQuery.prototype
pandoc markdown \newpage (force) and \pagebreak (prefer)
pesticide.io - hold ctrl to see current div
/home/cbird/Projects/general/dev/web/responsive/responsive.md
IIFE to prevent hoisting - but maybe we want global vars to maintain state?
http://stackoverflow.com/questions/9741328/why-do-we-need-a-fieldset-tag
