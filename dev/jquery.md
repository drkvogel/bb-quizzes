
### Dollar Object vs function

[Dollar Object vs function: $ vs $()](http://learn.jquery.com/using-jquery-core/dollar-object-vs-function/)

In jQuery, by convention, variables that are assigned jQuery objects are named with a '$' prefix, e.g.:

    var $button = $(".btn");

### get attribute

attr() http://api.jquery.com/attr/

### replaceWith() vs html()

replaceWith() will replace the current element, whereas html() simply replaces the contents.
Note that the replaceWith() will not actually delete the element but simply remove it from the DOM and return it to you in the collection.
http://stackoverflow.com/questions/730916/whats-the-difference-between-jquerys-replacewith-and-html

### Selectors

[jQuery Selectors](http://www.w3schools.com/jquery/jquery_ref_selectors.asp)
http://code.tutsplus.com/tutorials/the-30-css-selectors-you-must-memorize--net-16048

>jQuery selectors are based on the existing CSS Selectors, and in addition, has some own custom selectors.

    *                   all elements
    x *                 all children of x
    #x                  first id="x"
    .x                  all class="x"
    x                   all x
    x y                 all descendants y of x
    x + y               all y immediately following x
    x > y               all y is direct child of x
    x ~ y               all y following x, immediately or not
    x[attr]             all x with attribute attr
    x[attr="val"]       all x with attr="val"
    X[href*="nettuts"]  glob attribute value
    X[href^="http"]     begins with
    X[href$=".jpg"]     ends with
    X[data-*="foo"]     ?
    X[foo~="bar"]       attribute which has a spaced-separated list of values
    X:not(selector)     negation

    x:visited
    x:link
    x:hover
    x:checked
    x:after              Insert content before, or after, the content
    x:before
    :empty
    :target
    :focus

    Pseudo Elements:
    p::first-line
    p::first-letter
    x:first-child
    x:last-child
    x:nth-child(n)
    x:nth-last-child(n)
    x:nth-of-type(n)
    x:nth-last-of-type(n)
    x:only-child
    x:only-of-type
    x:first-of-type


### load() and get()

load() is roughly equivalent to $.get(url, data, success) except that it is a method rather than global function and it has an implicit callback function. When a successful response is detected (i.e. when textStatus is "success" or "notmodified"), .load() sets the HTML contents of the matched element to the returned data. This means that most uses of the method can be quite simple:

### [Using jQuery to include files](http://www.attackofdesign.com/using-jquery-to-include-files/)

```html
    <div class="js-include" title="nav.html"></div>
```

`js-include` is simply a class name that we'll assign to every element that should trigger the include. And nav.html is the relative URL of the file that we're including. Now, let’s take a look at the jQuery code:

```js
    $(".js-include").each(function(){
        var inc=$(this);
        $.get(inc.attr("title"), function(data){ // HTTP GET
            inc.replaceWith(data);
        });
    });
```

The first line just tells the script to execute the function once of each element that has the class `js-include`. We then store the current element inside a variable
We use jQuery's get function with the following arguments: the div's title as the URL of the file to load, and a callback function The callback function replaces the current DIV with the content that we just loaded.


### jquery on legacy browsers

TL;DR: "IE 6/7/8 will be supported" by jQuery 1.9. Use conditional comments to include it for lt IE 9.

https://blog.jquery.com/2012/06/28/jquery-core-version-1-9-and-beyond/
>jQuery 1.9 (early 2013): We’ll remove many of the interfaces already deprecated in version 1.8; some of them will be available as plugins or alternative APIs supported by the jQuery project. IE 6/7/8 will be supported as today.
jQuery 1.9.x (ongoing in 2013 and beyond): This version will continue to get fixes for any regressions, new browser bugs, etc.
jQuery 2.0 (early 2013, not long after 1.9): This version will support the same APIs as jQuery 1.9 does, but removes support for IE 6/7/8 oddities such as borked event model, IE7 “attroperties”, HTML5 shims, etc.

>Q: My site still has many IE7/8 visitors but I want to use jQuery 2.0. Can I do that? If your web site needs oldIE support, and we expect most sites will need it for at least another year or two, you can use IE conditional comments to include version 1.9 only when visitors are using oldIE:

    <!--[if lt IE 9]>
        <script src="jquery-1.9.0.js"></script>
    <![endif]-->
    <!--[if gte IE 9]><!-->
        <script src="jquery-2.0.0.js"></script>
    <!--<![endif]-->
