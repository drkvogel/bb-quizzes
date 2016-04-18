# Hoops quiz



    $ yo webapp
    ? What more would you like? (Press <space> to select)
    ❯◉ Sass
     ◉ Bootstrap
     ◉ Modernizr



    2016-04-18 16:13:07 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/app
    $ gulp
    [16:13:20] Failed to load external module babel-register
    [16:13:20] Failed to load external module babel-core/register
    [16:13:20] Failed to load external module babel/register
    /home/kvogel/Projects/bb-quizzes/hoops/app/gulpfile.babel.js:2
    import gulp from 'gulp';
    SyntaxError: Unexpected reserved word
    $ npm install --save-dev babel-core
    # git diff package.json
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

>the babel-runtime version and the version of babel that compiled the files needs to be the same. See babel/babel#965.


npm list babel-loader
@ /home/kvogel/Projects/bb-quizzes/hoops/app
└── (empty)
npm ERR! code 1




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