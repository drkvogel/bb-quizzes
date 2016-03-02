# setup


Backticks have to be pressed twice: https://en.wikipedia.org/wiki/Dead_key
http://askubuntu.com/questions/252688/lubuntu-12-04-change-default-keyboard-layout-after-installation

install lxkeymap, then change layout to English (UK) (NOT Extended or anything else)

### yeoman (yo, gulp, bower)

    cbird@q108-vlubuntu:~/Projects/bb-quizzes/matrix$ 
    $ sudo npm install -g yo
    $ sudo npm install -g gulp
    $ sudo npm install -g bower
    $ sudo npm install -g generator-webapp
    $ yo webapp # scaffold 
    $ yo webapp --help
    $ npm home generator-webapp   # show module homepage
        # http://stackoverflow.com/questions/21789683/how-to-fix-bower-ecmderr
        # if connection to github times out with ECMDERR - because git port not allowed through firewall? Use HTTP
    $ git config --global url."https://".insteadOf git://
    $ python -m SimpleHTTPServer    # 404s for assets, but ok for testing
    $ serve                         # /usr/local/bin/serve
    $ gulp serve                    # proper yeoman/gulp way
    $ ngrok 9000                    # then submit to browsershots.org

Serving files from .tmp, app
scripts, e.g. main.js, are deployed to .tmp? They don't update on refresh, unlike .html pages
https://github.com/yeoman/generator-webapp#readme

HTML does update dynamically with `gulp serve`

### browser testing

[Browsersync](https://www.browsersync.io/)
[Utilu IE Collection](http://utilu.com/IECollection/) - bundle of old IE versions
http://browsershots.org - free

### gulp

    Install dependencies: npm install --global yo gulp-cli bower
    Install the generator: npm install --global generator-webapp
    Run yo webapp to scaffold your webapp
    Run gulp serve to preview and watch for changes
    Run bower install --save <package> to install frontend dependencies
    Run gulp serve:test to run the tests in the browser
    Run gulp to build your webapp for production
    Run gulp serve:dist to preview the production build

## done

    $ vi ~/.gitignore
    $ git config core.excludesfile ~/.gitignore

---

    graceful-fs version 3 and before will fail on newer node releases. Please update to graceful-fs
    Not compatible with your operating system or architecture: fsevents@1.0.8