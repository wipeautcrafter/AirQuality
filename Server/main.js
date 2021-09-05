const express = require("express");
const fs = require("fs");

const names = require("./names.json");
const app = express();

const clients = {};

// verify function
function parse(query) {
    if(!query.id) return false;
    if(!query.ppm) return false;
    if(!query.temp) return false;

    if(!query.ppm.match(/[0-9\.]+/)) return false;
    if(!query.temp.match(/[0-9\.]+/)) return false;

    return {
        id: query.id,
        ppm: query.ppm,
        temp: query.temp,
        time: Date.now()
    };
}

// update function
function update(data) {
    if(!data) return false;
    const name = names[data.id];

    clients[data.id] = {
        name: name,
        ppm: data.ppm,
        temp: data.temp,
        time: Date.now()
    };

    // append to log file
    const contents = "\n" + [
        new Date().toISOString(),
        data.ppm, data.temp
    ].join(" ");

    fs.appendFile(`log/${data.id}.log`, contents, () => {});
    
    return true;
}

// express event listeners
app.get("/update", (req, res) => {
    const data = parse(req.query);

    if(!update(data)) {
        res.status(400);
    }

    res.send();
});

// interval
setInterval(() => {
    // remove "old" clients
    Object.keys(clients).forEach(c => {
        if(Date.now() - clients[c].time > 15000) {
            delete clients[c];
        }
    });

    console.clear();
    console.dir(clients);
}, 1000);

app.listen(8808);