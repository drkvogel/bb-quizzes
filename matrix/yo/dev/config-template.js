
// config for gulp-ssh

var fs = require('fs');
var config = {};

config.myhost = {
    ssh: { // for gulp-ssh
        host: 'myhost.com',
        port: 22,
        username: 'user',
        password: 'pass'
        privateKey: fs.readFileSync('/home/user/.ssh/id_rsa')        
    },
    dest: "/dest/dir"
  };

// etc...

module.exports = config;