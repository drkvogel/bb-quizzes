# setup

    cbird@q108-vlubuntu:~/Projects/bb-quizzes/matrix$ 
    $ sudo npm install -g yo
    $ sudo npm install -g gulp
    $ sudo npm install -g bower
    $ sudo npm install -g generator-webapp
    $ vi ~/.gitignore
    $ git config core.excludesfile ~/.gitignore

    $ yo webapp --help
    $ npm home generator-webapp   # show module homepage

    # http://stackoverflow.com/questions/21789683/how-to-fix-bower-ecmderr
    # if connection to github times out with ECMDERR - because git port not allowed through firewall? Use HTTP instead
    $ git config --global url."https://".insteadOf git://

    $ python -m SimpleHTTPServer # 404s
    $ gulp serve

https://github.com/yeoman/generator-webapp#readme

    Install dependencies: npm install --global yo gulp-cli bower
    Install the generator: npm install --global generator-webapp
    Run yo webapp to scaffold your webapp
    Run gulp serve to preview and watch for changes
    Run bower install --save <package> to install frontend dependencies
    Run gulp serve:test to run the tests in the browser
    Run gulp to build your webapp for production
    Run gulp serve:dist to preview the production build



---

    graceful-fs version 3 and before will fail on newer node releases. Please update to graceful-fs
    Not compatible with your operating system or architecture: fsevents@1.0.8