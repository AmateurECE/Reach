///////////////////////////////////////////////////////////////////////////////
// NAME:            main.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Main logic for the Reach server.
//
// CREATED:         08/19/2020
//
// LAST EDITED:     08/29/2020
////

const { ServerProtocol } = require('protocol.js');

const fs = require('fs');
const WebSocket = require('ws');
const util = require('util');

const readFile = util.promisify(fs.read);
async function readChunk(fileDescriptor, request) {
    const chunk = await readFile(fileDescriptor, {position: request.position});
    return {
        message: {
            position: request.position, length: chunk.bytesRead
        },
        data: chunk.buffer
    };
}

const server = new WebSocket.Server({port: 5000});
const filePath = '../dreamland.flac';
server.on('connection', ws => {
    fs.open(filePath, 'r', (error, fd) => {
        const protocol = new ServerProtocol(ws, request => {
            return readChunk(fd, request);
        });
        protocol.startListening();
    });
});

///////////////////////////////////////////////////////////////////////////////
