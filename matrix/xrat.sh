#!/bin/bash

# add -v for verbose debugging
scp -r ./dist/* webman@xrat:/user/webman/www/matrix/

# can use ssh config file, e.g ~/.ssh/config, to automate somethings, but not the password
# http://serverfault.com/questions/535028/adding-password-to-ssh-config/535031
# $ man ssh_config

# problems with this - doesn't seem to update files
#gulp --gulpfile gulp-ssh.js sftp-push-xrat
