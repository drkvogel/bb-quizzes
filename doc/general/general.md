What is the smallest screen resolution we should care about?

The general consensus on the following forum thread is 320 CSS pixels wide: http://stackoverflow.com/questions/10943342/what-is-the-smallest-screen-resolution-that-i-should-care-when-building-a-websit
On BrowserStack, the device with the smallest screen that I could find was the Sony Xperia Tipo with Android 4, which has a resolution of  320 x 480.
At this resolution the Matrix puzzle almost displays perfectly:
The intro screens with the explanatory text fit onscreen without the need for scrolling
The abandon button in the live test stays onscreen without scrolling
However, if you choose Abandon, in the “Please check” modal dialogue that appears, the “Yes” and “No” buttons are scrolled slightly offscreen left and right.
The thin borders around the tiles in the puzzles don’t display very well at such a low resolution, because there are not enough pixels to define them well. 
There are some CSS properties which can affect how scaled images are rendered:
img {
  image-rendering: auto;
  image-rendering: crisp-edges;
  image-rendering: pixelated;
}

But support is limited on Android particularly so it may be up to the individual device how it renders scaled images.
On other mobile devices, the quiz displays well – apart from the fact that the 2x2 live quizzes, the abandon button sometimes scrolls off the bottom of the screen.  I should be able to factor this into the scaling calculations to avoid this.
I have found Blisk Browser (https://blisk.io/ ) to be quite useful for quick responsiveness tests – it is a browser based on Chromium which has a main panel to display a web page on one side and a range of emulated mobile devices on the other. Unfortunately it does not currently display the dimensions of those devices, nor those of the main panel. I have sent a feature request about this to the developers.
