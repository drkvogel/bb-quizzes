#!/bin/bash

# pushd .
# cd dist
scp -rv ./dist/* drkvogel@web456.webfaction.com:/home/drkvogel/webapps/main/matrix/
# popd


# problems with this - doesn't seem to update files
#gulp --gulpfile gulp-ssh.js sftp-push-webfaction
