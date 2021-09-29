let names;
let ids;

$(function() {
    $.getJSON("/names", data => {
        names = data;
        ids = Object.keys(data);
    
        update();
        setInterval(update, 5000);
    });
});

function sensor(id, v) {
    let name = names[id];
    let ppm = "-";
    let temp = "-";
    let body = "<div><b>OFFLINE</b></div>";

    if(v) {
        off = false;
        ppm = v.ppm;
        temp = v.temp;

        body = `
            <div><b>PPM: </b>${ppm}</div>
            <div><b>TMP: </b>${temp}</div>
        `;
    }

    return `
        <div class="sensor">
            <div class="lead mb-2">Lokaal ${name}</div>
            ${body}
            <div class="small">${id}</div>
        </div>
    `;
}

function update() {
    $.getJSON("/raw", data => {
        $("body").html(ids.map(i => {
            return sensor(i, data[i]);
        }).join(""));
    });
}