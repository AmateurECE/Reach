///////////////////////////////////////////////////////////////////////////////
// NAME:            main.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Main logic for the Reach server.
//
// CREATED:         08/19/2020
//
// LAST EDITED:     08/19/2020
////

const WebSocket = require('ws');
const port = 5000;
const server = new WebSocket.Server({ port });

// TODO: Make call to django auth endpoint to verify user credentials.
server.on('connection', ws => {
    ws.on('message', message => {
        ws.send(`Echo: ${message}`);
    });
});

///////////////////////////////////////////////////////////////////////////////
