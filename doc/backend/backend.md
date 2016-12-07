
# oqs backend


### oqsweb.ndph.ox.ac.uk

`oqsweb` hosts the public-facing web applications
https://oqs.ndph.ox.ac.uk/~cp/bbquiz/

### oqshub.ndph.ox.ac.uk

Behind firewall - for building the backend
with make
and yopush to push the front end

### yopush

in bb-quizzes.git:/bin
rsync


---

## done

edit files via sublime-sftp on oqshub from q108, make on oqshub, push to oqsweb...
but, changes files on both q108 and oqshub, no need to add to git on server....
why not sftp direct to oqsweb from q108-vlubuntu?
or sftp direct to oqsweb from q108-vlubuntu, and make via ssh? works for now...

### xrat2red

sftps everything.... lots of jpgs e.g. in dccs. rsync better

    rsync -r --info=progress2 -e ssh . $REMOTEUSER@$REMOTEHOST:$REMOTEPATH

## todo

put bak.sh in general.git and on red ~cp/bin
docs in jekyll?
    git hooks
cp@oqshub:/user/cp/proj/.cbrc
    
    # .vimrc 
    set background=dark
