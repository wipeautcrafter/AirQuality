const express = require("express");
const path = require("path");
const fs = require("fs");

const names = require("./names.json");
const app = express();

const clients = {};

// verify function
function parse(query) {
    if(!query.id) return false;
    if(!query.ppm) return false;
    if(!query.temp) return false;
    
    if(!names[query.id]) {
        console.log(`No name: ${query.id}`);
        return false;
    }

    if(!query.ppm.match(/[0-9\.]+/)) return false;
    if(!query.temp.match(/[0-9\.]+/)) return false;

    return {
        id: query.id,
        name: names[query.id],
        ppm: query.ppm,
        temp: query.temp,
        time: Date.now()
    };
}

// update function
function update(data) {
    if(!data) return false;
    const name = names[data.id];

    clients[data.id] = data;

    // append to log file
    const contents = "\n" + [
        new Date().toISOString(),
        data.ppm, data.temp
    ].join(" ");

    fs.appendFile(`log/${data.id}.log`, contents, () => {});
    
    return true;
}

// check if within sleep time
function shouldSleep() {
    const h = new Date().getHours();
    return h < 8 || h > 17;
}

// express event listeners
app.get("/update", (req, res) => {
    if(shouldSleep()) {
        res.status(503);
        res.send();
        return;
    }

    const data = parse(req.query);

    if(!update(data)) {
        res.status(400);
    }

    res.send();
});

// raw report page
app.get("/raw", (req, res) => {
    res.contentType("application/json");
    res.send(JSON.stringify(clients));
});

// get sensor names
app.get("/names", (req, res) => {
    res.contentType("application/json");
    res.send(JSON.stringify(names));
});

// get log
app.get("/log/:id", (req, res) => {
    const file = req.params.id.replace(/\./, "") + ".log";
    const dir = path.join(__dirname, "log", file);
    res.sendFile(dir);
});

// "clean" view
app.use(express.static("html"));

// interval
setInterval(() => {
    // remove "old" clients
    Object.keys(clients).forEach(c => {
        if(Date.now() - clients[c].time > 15000) {
            delete clients[c];
        }
    });

    // console.clear();
    // console.dir(clients);
}, 1000);

app.listen(8808);