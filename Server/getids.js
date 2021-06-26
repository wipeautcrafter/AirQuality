const express = require("express");
const app = express();

const clients = [];

app.get("/update", (req, res) => {
    if(!req.query.id) {
        res.status(400);
        return;
    }

    res.send();

    const id = req.query.id;
    if(clients.indexOf(id) === -1) {
        clients.push(id);
    }

    console.clear();
    console.dir(clients);
});

app.listen(8808);