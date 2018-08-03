const express = require('express');
const bodyParser = require('body-parser');

const app = express();

app.use(bodyParser.json()); // for parsing application/json

const port = 2414;

// hey guys please don't make me regret having this in the repo haha
const githubSignature = "f4NHb86nALZyZoEsATuR";

// in the future this might send information like build # etc
app.get('/', (req, res) => res.send('I am listening'));

// on a post we'll want to use the CLI to compile and upload the posted code to an arduino on the robot
app.post('/', (req, res) => { 
    console.log(`request: ${JSON.stringify(req.headers)} ${JSON.stringify(req.body.cool)}`);
    res.send() 
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`));
