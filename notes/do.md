## todo

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops

* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

>determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.

determine the scaling in each of the horizontal and vertical directions required to fit the window
  scaling of what? 
  height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

### scaleImagesCBnew()

get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)
// missing some widths and heights?

### scaleImagesAY()

get the unscaled dimensions of the content:
  fullHeight
    get the various heights of fixed elements - hardcoded, or with jquery
    and the full-size heights of the images added together, including padding
  fullWidth
    get the various widths of fixed elements - hardcoded, or with jquery
    and the full-size widths of the wider image (bottom 3x2 or 4x2) added together, including padding
and then work out what ratio fullHeight to viewport height is
and then work out what ratio fullWidth to viewport width is
get the greater/lesser of these # resize using the smaller of these factors as a parameter

fullWidth = widthExtra + $('.bot').width()
fullHeight = heightExtra + $('.top').height() + $('bot').height()


central images are the only thing we can usefully scale
and the only way do that is to set the left and right margins to cause the width to alter - the height will follow to keep the aspect ratio.
so, we need to find out what height the central images would need to be in order for everything to fit height-wise.


i.e. get the height of the window
subtract the heights of everything we cannot change



ay calcs:

```
    get natural width/height (naturalFullWidth/Height)
    get window width/height ($(window).width()/height)
    allow 200px for text at bottom
    window - 200px height needs to fit natural width/height

    vertical shrink = (window height - 200px) / naturalFullHeight
    horizontal shrink = window width / naturalFullWidth

    scale = vShrink < hShrink ? vShrink : hShrink

    targetHeight = naturalFullHeight * scale
    targetWidth = naturalFullWidth * scale # forget about width... (?) can't change

    targetMiddleHeight = targetHeight - heightExtras

    need h/w ratio of .gridContainer
    Typical dimensions: 162 x 144
    162 / 144 == 1.125
    middleHWRatio = 1.125
    # what innerWidth of .gridcontainer would create targetMiddleHeight?

    targetMiddleWidth = targetMiddleHeight * middleHWRatio [1.125] # h/w ratio of .gridContainer

    margins = (window.width - widthExtra) / 2
```

innerWidth
.gridcontainer 


```js
        var topWidth, topHeight, botWidth, botHeight;
        if (currentPage().templateId == 'quiz2x2') {
            topWidth = 420;
            topHeight = 340;
            botWidth = 680;
            botHeight = 365;
        } else if (page.templateId == 'quiz3x3') {
            topWidth = 510;
            topHeight = 405;
            botWidth = 755;
            botHeight = 295;
        }
        // 2x2, 3x2: img.top natural: 420 x 340, img.bot natural: 680 x 365
        // 3x3, 4x2: img.top natural: 510 x 405, img.bot natural: 755 x 295

        var widthExtra =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());

        var heightExtra =
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0);

        var naturalFullWidth = widthExtra + botWidth; // bottom image is widest
        var naturalFullHeight = heightExtra + topHeight + botHeight; // combined height of both images

        var scaleH = naturalFullWidth / $(window).width();
        var scaleV = naturalFullHeight / $(window).height();

        var scale = scaleH <= scaleV ? scaleH : scaleV;

        // make whole thing smaller by scale?
        var newWidth = naturalFullWidth * scale;
        var newHeight = naturalFullHeight * scale;
```



get code to print worked examples
hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()
fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start


