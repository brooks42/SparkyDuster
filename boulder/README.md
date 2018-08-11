# Boulder

## Installation

run 

```cd boulder``` (if you're in root)
```sudo npm install express --save```

I had to install nvm, see this link:

https://davidwalsh.name/nvm
https://github.com/creationix/nvm/blob/master/README.md

to update NodeJS and be able to switch between them because my dev machine uses the Windows 10 Linux Subsystem and... it's just _great_.

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion