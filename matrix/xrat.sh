#!/bin/bash

# 2016-04-14 q108-vlubuntu ssh to xrat no longer works

if [ -d "dist" ]; then          # we're on a machine where dist has been built, i.e. q108-vlubuntu or yoga3-vlubuntu
    echo "'dist' exists"
    echo "creating zip"
    tar czf dist.tgz dist       # zip it good
    scp dist.tgz drkvogel@web456.webfaction.com:/home/drkvogel/webapps/main/matrix/
else                            # on another machine e.g. q108
    echo "no 'dist' exists"
    echo "getting dist.tgz from remote"
    scp drkvogel@web456.webfaction.com:/home/drkvogel/webapps/main/matrix/dist.tgz .
    echo "unzipping"
    tar xzf dist.tgz distlocal  # unzip it to a folder named something else
    scp -r ./distlocal/* webman@xrat:/user/webman/www/matrix/
fi

# add -v for verbose debugging

# can use ssh config file, e.g ~/.ssh/config, to automate somethings, but not the password
# http://serverfault.com/questions/535028/adding-password-to-ssh-config/535031
# $ man ssh_config

# problems with this - doesn't seem to update files
#gulp --gulpfile gulp-ssh.js sftp-push-xrat
