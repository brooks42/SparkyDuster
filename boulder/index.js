const express = require('express');
const app = express();

const port = 2414;

// in the future this might send information like build # etc
app.get('/', (req, res) => res.send('I am listening'));

// on a post we'll want to use the CLI to compile and upload the posted code to an arduino on the robot
app.post('/', (req, res) => { 
    console.log(`request: ${req}`);
    res.send() 
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`));

//f4NHb86nALZyZoEsATuR