const express = require("express");
const app = express();

const _clients = require("./clients.json");
const clients = {};

function parseData(query) {
    if(!query.id) return false;
    if(!query.ppm) return false;
    if(!query.temp) return false;

    if(!query.ppm.match(/[0-9\.]+/)) return false;
    if(!query.temp.match(/[0-9\.]+/)) return false;

    if(!_clients[query.id]) return false;
    const id = _clients[query.id];

    clients[id] = {
        "ppm": parseFloat(query.ppm),
        "temp": parseFloat(query.temp),
        "time": Date.now()
    };

    return true;
}

app.get("/update", (req, res) => {
    if(!parseData(req.query)) {
        res.status(400);
    }

    res.send();
});

function update() {
    Object.keys(clients).forEach(id => {
        if(clients[id].time + 15000 < Date.now()) delete clients[id];
    });

    console.clear();
    console.dir(clients);
}

app.listen(8808);

setInterval(update, 1000);
update();
