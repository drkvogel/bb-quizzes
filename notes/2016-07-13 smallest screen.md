
fossilize...


Tue Jul 12 11:54:56 2016 meeting
try matrix on smallest browserstack browser-
abandon still scrolls off in some dimensions
`#abandon-div` is outside `#page`

Implement AY re-sizing algorithm and update documentation
description of images - size of icons and spacings between them for the 2 layouts
Produce a similar document for the Hoops system

## smallest screen

Investigate (briefly!) what is the smallest mobile phone screen we are likely to encounter so some lower limit can be put on the 'shrinkability' of the interface.

Samsung Galaxy S - 480×800
v slow to respond
doesn't always get right tile... as if using image map for 2x2 on 3x3 and/or vice versa.
[BrowserStack](https://www.browserstack.com/start#os=android&os_version=2.2&device=Samsung+Galaxy+S&zoom_to_fit=true&full_screen=true&url=http%3A%2F%2Fred.ctsu.ox.ac.uk%2F~cp%2Fcjb%2F&speed=1)
intro 1, 2, 3
getReady - ok
games with Abandon - ok..
press Abandon - chooses tile instead!
"Please check" - buttons off screen
responds to 'd' key 
3x3 grid borders look a bit naff

Motorola Droid Razr with Android 2.3 - 960x540
Chrome? own browser - much faster, but then - crashed! after Start
wonder if css sprites version does...

Sony Xperia Tipo with Android 4 - 320x480 <---  smallest width so far
intro 1 just fits
3x3 borders look naff, and 2x2
abandon on screen
Please check buttons mostly off screen
don't need big textarea on Complete screen

Google Nexus 7 -  1920 x 1200 - all looks OK
HTC One X - 720 x 1280 - OK
Galaxy Core Prime - 800 x 480

### mobile browser resolution stats


[what is the smallest screen resolution that I should care when building a website?](http://stackoverflow.com/questions/10943342/what-is-the-smallest-screen-resolution-that-i-should-care-when-building-a-websit)

320 css?


[Browser Display Statistics](http://www.w3schools.com/browsers/browsers_display.asp) - but this is for desktops

    Date            Other high  1920x1080   1366x768    1280x1024   1280x800    1024x768    800x600 Lower
    January 2016    30.7%       18%         35%         6%          4%          3%          0.3%    3%


http://gs.statcounter.com/

I personally used a breakpoint of 768px screen width
For maximum optimisation you could use interim breakpoints at 640px, 600px, 480px, 360px, 320px and even 240px (low-low-end androids) but it's probably a good practice to make it totally %-based below 768px so it fits automatically.

one useful breakpoint I found is 810px - the width of an iframe in a Facebook tab. Helpful when you create FB apps and want to reuse your webapp code.

BrowserStack Local Testing
With the BrowserStack features extension, you can test local URLs, files, localhost, etc. https://www.browserstack.com/local-testing

---


imagemap does not match image on 10, 13, 14, 15, 16, 17, 18, 19 - change map or image
send result by ajax (don't use submit)
log IP?

css errors
abandon button vanishes
js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start
tidy up matrix, hoops

Dear Chris, just to record the outcomes from our meeting today. Firstly we noted you were either ill or on leave for most of the time since our last meeting so it's not unreasonable that most of the ToDos from then remain undone. The carry-over actions from last week are:
* Implement the re-sizing algorithm as described in last weeks email and annotated on the paper copy of your documentation.  Update the documentation to match.
* Add a generic description of the images used in the system - i.e. say how big the various "icons" are and the spacings between them for the 2 layouts.
* Produce a similar document for the Hoops system.
I think the above should all be achievable within a week.
New item:
* Investigate (briefly!) what is the smallest mobile phone screen we are likely to encounter so some lower limit can be put on the 'shrinkability' of the interface.
Also:
* I said that it's not necessary for all the instructional text on the training pages to be visible (it's fine for users to scroll at this point in the process) so you don't need to spend time calculating the size of the div box containing that text as the screen changes size.
* I noted that you arrived at 11ish and emailed then to say that you'd been late due to oversleeping.  I asked that, in future, you ring from home prior to coming in so we know as early as possible that you will be in.
Regards, Alan

text full width-
get ready text too small-
start button should be further from text-
time limit is now 3 mins-

remember (e.g.):
`#getReady.buttons` matches `<div id="getReady" class="buttons">`
`#getReady .buttons ` matches `<div id="getReady"><div class="buttons">` 

look at fossil bugs bb-quizzes.fossil

pointer doesn't change over clickable areas now?
dev prev button doesn't work now unless navbar fits on one line
shrink containing div - too big-
with `.top, .bot { width: 100%; }`, image map doesn't work-x

## done

comparing app-imagemap with app-aycalc, was missing recent tweaks - forgot about app-lessdivs

estimate or calculate height of text element - forget this
estimate or predict height of html element - Google Search (https://www.google.co.uk/search?q=estimate+or+predict+height+of+html+element)
Determining the dimensions of elements - Web APIs | MDN (https://developer.mozilla.org/en-US/docs/Web/API/CSS_Object_Model/Determining_the_dimensions_of_elements)
html determine height of text element - Google Search (https://www.google.co.uk/search?q=html+text+height)
javascript - How to get the real height of a text? - Stack Overflow (http://stackoverflow.com/questions/15161385/how-to-get-the-real-height-of-a-text)
JavaScript Window getComputedStyle() Method (http://www.w3schools.com/jsref/jsref_getcomputedstyle.asp)
Calculate text width and height with JavaScript (http://daipratt.co.uk/calculate-text-width-and-height-with-javascript/)
HTML / JavaScript calculate text dimensions - Ben Ripkens (bripkens) (http://blog.bripkens.de/2011/06/html-javascript-calculate-text-dimensions/)
javascript measure text - Google Search (https://www.google.co.uk/search?q=javascript+measure+text)
[HTML canvas measureText()](http://www.w3schools.com/tags/canvas_measuretext.asp) - nope