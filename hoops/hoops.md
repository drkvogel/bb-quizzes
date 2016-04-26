# Hoops quiz

bb-quizzes/jonathanpr/BioBankQuizGames/TowerOfLondonGame.cpp

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

