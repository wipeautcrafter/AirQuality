const rl = require("readline").createInterface(process.stdin, process.stdout);
const app = require("express")();
const {writeFile} = require("fs");

const names = require("./names.json");
let busy = false;

app.get("/update", (req, res) => {
    if(!req.query || !req.query.id || busy) {
        res.status(400).send();
        return;
    }

    const id = req.query.id;
    
    if(names[id]) {
        res.send();
        return;
    }

    busy = true;
    res.status(400).send();

    rl.question(`[${id}] `, name => {
        names[id] = name;

        writeFile("names.json", JSON.stringify(names), () => {
            busy = false;
        });
    });
});

app.listen(8808);