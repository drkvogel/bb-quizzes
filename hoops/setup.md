
## Hoops setup

    $ yo webapp
    ? What more would you like? (Press <space> to select)
    ❯◉ Sass
     ◉ Bootstrap
     ◉ Modernizr



### Setup problems

when will I learn? yeoman setup always seems to break, or maybe seem unresponsive and I kill it, and the node packages will be broken. 
Delete everything with `rm -rf node_modules` and run `npm install`. /home/kvogel/Projects/bb-quizzes/hoops/setup.md
and don't forget to do `bower install` as well.

then "jQuery is not defined", and all styles are missing from page.

    $ gulp wiredep

now looks OK. What was going on there? 

https://github.com/taptapship/wiredep
>A Bower package may not properly list its dependencies in its bower.json file.
>A Bower package may not specify a main property in its bower.json file. ?

why was this necessary? Anyway, works for now....

### Semantic Versioning 2.0.0

Given a version number `MAJOR.MINOR.PATCH`, increment the:

1. `MAJOR` version when you make incompatible API changes,
2. `MINOR` version when you add functionality in a backwards-compatible manner, and
3. `PATCH` version when you make backwards-compatible bug fixes.

---



    2016-04-18 16:13:07 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/app
    $ gulp
    [16:13:20] Failed to load external module babel-register
    [16:13:20] Failed to load external module babel-core/register
    [16:13:20] Failed to load external module babel/register
    /home/kvogel/Projects/bb-quizzes/hoops/app/gulpfile.babel.js:2
    import gulp from 'gulp';
    SyntaxError: Unexpected reserved word
    $ npm install --save-dev babel-core     # devDependencies, not dependencies

    $ git diff package.json
        "devDependencies": {
    -        "babel-core": "^6.4.0",
        "devDependencies": {
    +        "babel-core": "^6.7.6",

    $ npm help update
    $ npm help upgrade  # synonym for update
    $ npm install --save-dev babel-core
    $ sudo npm upgrade
    $ npm --version
    $ sudo npm update yo
    $ yo --version
    $ npm install babel-runtime
    $ npm install core-js
    $ npm install babel-loader
    $ npm install webpack@1 || ^2.1.0-beta
    $ npm install babel-register

    Error: Cannot find module 'babel-runtime/helpers/interop-export-wildcard'
    $ npm install --save-dev babel-runtime
    babel-runtime@6.6.1 node_modules/babel-runtime
    └── core-js@2.2.2


    2016-04-18 18:12:27 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/app
    $ npm install --save babel-runtime
    babel-runtime@6.6.1 node_modules/babel-runtime


    $ npm install --save babel-runtime
    babel-runtime@6.6.1 node_modules/babel-runtime


    Error: Cannot find module 'core-js/library/fn/get-iterator'
    $ npm install --save core-js

    $ npm install babel-loader
    npm WARN peerDependencies The peer dependency webpack@1 || ^2.1.0-beta included from babel-loader will no
    npm WARN peerDependencies longer be automatically installed to fulfill the peerDependency 
    npm WARN peerDependencies in npm 3+. Your application will need to depend on it explicitly.
    npm WARN optional dep failed, continuing fsevents@1.0.11
    $ npm install webpack@1 || ^2.1.0-beta

    Failed to load external module babel-core/register
    $ npm install babel-register
    babel-register@6.7.2 node_modules/babel-register
    ├── path-exists@1.0.0
    ├── home-or-tmp@1.0.0 (os-tmpdir@1.0.1, user-home@1.1.1)
    ├── mkdirp@0.5.1 (minimist@0.0.8)
    ├── source-map-support@0.2.10 (source-map@0.1.32)
    ├── lodash@3.10.1
    └── babel-runtime@5.8.38 (core-js@1.2.6)
    # gets rid of 'Failed to load external module babel-register' warning
    # but doesn't solve Error: Cannot find module 'babel-runtime/helpers/interop-export-wildcard'

    $ npm list babel-register
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    ├─┬ babel-core@6.7.6
    │ └── babel-register@6.7.2 
    └── babel-register@6.7.2  extraneous
    npm ERR! extraneous: babel-register@6.7.2 /home/kvogel/Projects/bb-quizzes/hoops/app/node_modules/babel-register

    npm ERR! extraneous: babel-register 
    2016-04-18 17:33:37 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/app
    $ rm -rf node_modules/*
    $ npm install


https://github.com/krakenjs/confit/issues/39

>the babel deps are inverted. babel should be a devDependency, while babel-runtime should be a regular dependency.

>Babel doesn't play well with semver ranges (e.g. ^ and ~). We need to pin the deps to exact, specific versions.

>the babel-runtime version and the version of babel that compiled the files needs to be the same. See **babel/babel#965**.

"babel/babel#965"? https://github.com/babel/babel/issues/965 is a 404. But:

>Bugs and feature requests should be posted at phabricator.babeljs.io.
You can directly translate a github issue to phabricator; just add a T to the beginning of the issue.
https://phabricator.babeljs.io/T2168 corresponds to https://github.com/babel/babel/issues/2168

So `babel/babel#965` => https://phabricator.babeljs.io/T965

    $ npm install --save babel
    babel@6.5.2 node_modules/babel

no dice. I created `interop-export-wildcard.js` in `~/Projects/bb-quizzes/hoops/app/node_modules/babel-runtime/helpers/` from here: http://pocketlingo.merson.stevemckeogh.co.uk/react-isomorphic-starterkit/node_modules/babel-core/node_modules/babel-runtime/helpers/interop-export-wildcard.js:

```js
"use strict";
exports["default"] = function (obj, defaults) {
  var newObj = defaults({}, obj);
  delete newObj["default"];
  return newObj;
};
exports.__esModule = true;
```

and *that* problem went away... but next:

    Error: Cannot find module 'lodash/array/compact'

btw these errors are thrown by `babel-types` (`/home/kvogel/Projects/bb-quizzes/hoops/app/node_modules/babel-preset-es2015/node_modules/babel-plugin-transform-es2015-function-name/node_modules/babel-types/lib/index.js:13:30`)

    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    ├─┬ babel-core@6.7.6
    │ └── babel-types@6.7.2 
    ...

    $ npm list -s lodash    # -s: silent - hide WARN messages
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    ├─┬ babel-core@6.7.6
    │ └── lodash@3.10.1 
    ...

it's true, `~/Projects/bb-quizzes/hoops/app/node_modules/babel-preset-es2015/node_modules/babel-plugin-transform-es2015-function-name/node_modules/babel-types/node_modules/lodash` doesn't have an `array` subdirectory, `lodash` in other locations does... out of disk space? 

    2016-04-19 00:34:30 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/app
    $ rm -rf node_modules/
    $ npm install
    $ gulp          # great success




    $ npm list babel-loader
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    └── (empty)
    npm ERR! code 1
    $ npm install --save babel-loader
    npm WARN peerDependencies The peer dependency webpack@1 || ^2.1.0-beta included from babel-loader will no
    npm WARN peerDependencies longer be automatically installed to fulfill the peerDependency 
    npm WARN peerDependencies in npm 3+. Your application will need to depend on it explicitly.
    webpack@1.13.0 node_modules/webpack
    ├── interpret@0.6.6
    ├── tapable@0.1.10
    ├── clone@1.0.2
    ├── async@1.5.2
    ├── supports-color@3.1.2 (has-flag@1.0.0)
    ├── loader-utils@0.2.14 (object-assign@4.0.1, big.js@3.1.3, json5@0.5.0, emojis-list@1.0.1)
    ├── enhanced-resolve@0.9.1 (graceful-fs@4.1.3, memory-fs@0.2.0)
    ├── acorn@3.1.0
    ├── mkdirp@0.5.1 (minimist@0.0.8)
    ├── optimist@0.6.1 (wordwrap@0.0.3, minimist@0.0.10)
    ├── webpack-core@0.6.8 (source-map@0.4.4, source-list-map@0.1.6)
    ├── uglify-js@2.6.2 (async@0.2.10, uglify-to-browserify@1.0.2, source-map@0.5.3, yargs@3.10.0)
    ├── memory-fs@0.3.0 (errno@0.1.4, readable-stream@2.1.0)
    ├── watchpack@0.2.9 (graceful-fs@4.1.3, async@0.9.2, chokidar@1.4.3)
    └── node-libs-browser@0.5.3 (https-browserify@0.0.0, punycode@1.4.1, path-browserify@0.0.0, string_decoder@0.10.31, tty-browserify@0.0.0, os-browserify@0.1.2, constants-browserify@0.0.1, process@0.11.2, assert@1.3.0, domain-browser@1.1.7, querystring-es3@0.2.1, timers-browserify@1.4.2, stream-browserify@1.0.0, events@1.1.0, vm-browserify@0.0.4, readable-stream@1.1.14, util@0.10.3, console-browserify@1.1.0, url@0.10.3, http-browserify@1.7.0, buffer@3.6.0, browserify-zlib@0.1.4, crypto-browserify@3.2.8)
    babel-loader@6.2.4 node_modules/babel-loader
    ├── object-assign@4.0.1
    ├── loader-utils@0.2.14 (big.js@3.1.3, json5@0.5.0, emojis-list@1.0.1)
    └── mkdirp@0.5.1 (minimist@0.0.8)
    $ npm --version
    2.14.20




    npm list webpack@1 || ^2.1.0-beta

    $ npm list babel-register
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    └─┬ babel-core@6.7.6
      └── babel-register@6.7.2 

    $ npm list core-js
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    └─┬ babel-core@6.7.6
      └─┬ babel-register@6.7.2
        └── core-js@2.2.2 

    $ npm list babel-runtime
    @ /home/kvogel/Projects/bb-quizzes/hoops/app
    ├─┬ babel-core@6.7.6
    │ └── babel-runtime@5.8.38 
    └─┬ babel-preset-es2015@6.6.0
      ├─┬ babel-plugin-check-es2015-constants@6.7.2
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-arrow-functions@6.5.2
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-block-scoped-functions@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-block-scoping@6.7.1
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-classes@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-computed-properties@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-destructuring@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-duplicate-keys@6.6.4
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-for-of@6.6.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-function-name@6.5.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-literals@6.5.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-modules-commonjs@6.7.4
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-object-super@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-parameters@6.7.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-shorthand-properties@6.5.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-spread@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-sticky-regex@6.5.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-template-literals@6.6.5
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-typeof-symbol@6.6.0
      │ └── babel-runtime@5.8.38 
      ├─┬ babel-plugin-transform-es2015-unicode-regex@6.5.0
      │ └── babel-runtime@5.8.38 
      └─┬ babel-plugin-transform-regenerator@6.6.5
        └── babel-runtime@5.8.38 