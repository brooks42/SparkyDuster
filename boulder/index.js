'use strict';
const express = require('express');
const bodyParser = require('body-parser');
const shell = require('shelljs');

const app = express();

app.use(bodyParser.json()); // for parsing application/json

const port = 2414;

// hey guys please don't make me regret having this in the repo haha
const githubSignature = "f4NHb86nALZyZoEsATuR";

// in the future this might send information like build # etc
app.get('/', (req, res) => res.send('I am listening'));

// when someone posts to /update we should do the git commands to pull etc, and restart the server
app.post('/update', (req, res) => {
    pullRepo();
    restartServer();
    res.send();
});

app.post('/pull', (req, res) => {
    pullRepo();
    res.send();
});

app.post('/restart', (req, res) => {
    restartServer();
    res.send();
});

// on a post we'll want to use the CLI to compile and upload the posted code to an arduino on the robot
app.post('/', (req, res) => { 
    console.log(`request: ${JSON.stringify(req.headers)} ${JSON.stringify(req.body, undefined, '\t')}`);
    res.send();

    // parse the github PN and decide whether we need to push or not
    var notification = new PushNotification(req.body);
    if (notification.shouldPullRepoAndRebuild()) {
        console.log("Should pull the repo and rebuild...");

        // do a bunch of stuff

    }
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`));

// pull the git repo (this should override this code :O )
function pullRepo() {
    console.log("pulling repo...");
    shell.exec('git pull');
}

// do the CLI to restart this server, might be a little gnarly at first
function restartServer() {
    console.log("restarting server...");
    
}

/**
 * PushNotification class for determining if we trust the PN and whether we should pull or not.
 */
class PushNotification {

    /**
     * 
     * @param {Object} obj a JSON object representing the body of the push notification
     */
    constructor(obj) {
        console.log(`New PushNotification created with body ${JSON.stringify(obj, undefined, '\t')}`);
        this.object = obj;
    }

    /**
     * 
     */
    isTrustedPN() {
        // TODO: returns true for now
        return true;
    }

    /**
     * 
     */
    shouldPullRepoAndRebuild() {
        // for now I just return true, maybe filter on releases or a commit message keyword or something?
        return true;
    }
}