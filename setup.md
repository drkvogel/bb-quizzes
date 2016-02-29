# setup



    cbird@q108-vlubuntu:~/Projects/bb-quizzes/matrix$ 
    mkdir www
    sudo npm install -g yo
    sudo npm install -g gulp
    sudo npm install -g bower
    sudo npm install -g generator-webapp
    vi ~/.gitignore
    git config core.excludesfile ~/.gitignore

    yo webapp --help
    npm home generator-webapp   # show module homepage

    # http://stackoverflow.com/questions/21789683/how-to-fix-bower-ecmderr
    # if connection to github times out with ECMDERR - because git port not allowed through firewall? Use HTTP instead
    git config --global url."https://".insteadOf git://

    $ python -m SimpleHTTPServer


---

    graceful-fs version 3 and before will fail on newer node releases. Please update to graceful-fs