
[Dollar Object vs function: $ vs $()](http://learn.jquery.com/using-jquery-core/dollar-object-vs-function/)

[jQuery Selectors](http://www.w3schools.com/jquery/jquery_ref_selectors.asp)

attr() http://api.jquery.com/attr/


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
