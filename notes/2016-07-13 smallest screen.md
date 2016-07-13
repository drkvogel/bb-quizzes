

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
