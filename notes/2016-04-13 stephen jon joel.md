OK, so as http://kvogel.net/responsive/tables has proved (?), there are really two problems:

1. The tiles do not stretch, and therefore:
2. The grids are a fixed size that fills most of the width and height - on my laptop, where the screen is 1920 x 1080, and therefore the aspect ratio is 16:9, the height cannot fit and scrolls off the screen

so:

1. The tile images should scale
2. the page height should fit in the viewport hight, and the width adjust as necessary

As I'm using sprites, I should perhaps use stretchy sprites, or 

Stretchy Sprites
doesn't use `background-size`

```css
/*
Stretchy Sprites by tobyj.net
Feel free to copy and reuse as you like
*/

/*Set the max-width to the width of your individual sprites:*/
.stretchy {display:block; float:left; position:relative; overflow:hidden; max-width:160px;}
.stretchy .spacer {width: 100%; height: auto;}
.stretchy .sprite {position:absolute; top:0; left:0; max-width:none; max-height:100%;}
.stretchy .sprite.s2 {left:-100%;}
.stretchy .sprite.s3 {left:-200%;}
.stretchy .sprite.s4 {left:-300%;}
.stretchy .sprite.s5 {left:-400%;}
.stretchy .sprite.s6 {left:-500%;}

.stretchy.no-limit {max-width: none;} /*you could also set this to a pixel size, for example 320px, to limit the maximum*/
.stretchy.no-limit .sprite {min-height: 100%;}

/*END stretchy sprites by tobyj.net*/
```



`background-size` doesn't work in IE8
http://www.w3schools.com/cssref/css3_pr_background-size.asp
http://caniuse.com/#feat=background-img-opts

>Not much, I’m afraid.  One obvious question, though: how have you specified the viewport?
>I’m never quite sure about device-width on PCs, unless the browser’s operating full screen, but I wonder if the problem is the different devices are interpreting it differently.  If it wasn’t there, my guess is that they’d all try to do the decent thing. Sorry; not much more I can offer Nick


### flexbox

already have from Bootstrap?

A Complete Guide to Flexbox
https://css-tricks.com/snippets/css/a-guide-to-flexbox/

CSS3 Flexible Box
http://www.w3schools.com/css/css3_flexbox.asp
>Flexible boxes, or flexbox, is a **new layout mode** in **CSS3**
>the flexible box model provides an improvement over the block model in that it **does not use floats**, nor do the flex container's margins collapse with the margins of its contents.

The Ultimate Flexbox Cheat Sheet
http://www.sketchingwithcss.com/samplechapter/cheatsheet.html

### Jon's tips

set height px with js
window.width|height
height auto body
body height
window.screenX|screenY

## defer

(hoops)

caniuse.com/svg
svg fallbacks

## done

top2 not displaying-

### via Joel

"for Explorer set a max 100% but not a min"
http://www.websitedimensions.com/
http://quirktools.com/screenfly/ view your website on a variety of device screens and resolutions
http://quirktools.com/wires/ build online wireframes right in your browser
http://quirktools.com/smaps/ build site maps in your browser
http://quirktools.com/retro/ screen size, viewport size, pixel ratio, user agent string, language, IP
