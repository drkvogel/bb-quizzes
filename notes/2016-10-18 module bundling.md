

early notes in bb-quizzes, hoops, have lots of stuff I should read and understand

### js module bundling / [Splitting JS across files](http://stackoverflow.com/questions/16749870/splitting-javascript-into-several-files)

Several methods:

* [Namespace Objects](https://addyosmani.com/blog/essential-js-namespacing/)
* [RequireJS](http://requirejs.org/) ([AMD](https://en.wikipedia.org/wiki/Asynchronous_module_definition))
* [Browserify](http://browserify.org/) ([CommonJS](http://requirejs.org/docs/commonjs.html))

e.g.

    // file 1
    (function(){
        cog = cog || {};
        cog.myvar = ...;
        cog.myfunc = function(){...};
    })();
    
    // file 2
    (function(){
        cog = cog || {};
        myaapp.myothervar = ...
        cog.myotherfunc = function(){...};
        cog.start = function(){...};
        }
    })();
    
    // last file
    $(cog.start);

[webpack](https://webpack.github.io/docs/commonjs.html)?
IIFE means "use strict" only has to be declared once per file, but now can't access funcs across files... http://gregfranko.com/blog/i-love-my-iife/