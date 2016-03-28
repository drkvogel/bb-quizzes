
// config for gulp-ssh

var fs = require('fs');
var config = {};

config.myhost = {
    host: 'myhost.com',
    port: 22,
    username: 'user',
    password: 'pass'
    privateKey: fs.readFileSync('/home/user/.ssh/id_rsa')
  };

// etc...

module.exports = config;