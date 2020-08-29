///////////////////////////////////////////////////////////////////////////////
// NAME:            ServerProtocol.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     The protocol that the server exposes to the client.
//
// CREATED:         08/27/2020
//
// LAST EDITED:     08/29/2020
////

class ServerProtocol {
    constructor(webSocket, responder) {
        this.webSocket = webSocket;
        this.responder = responder;
    }

    startListening() {
        this.webSocket.on('message', message => {
            // Client always makes requests using json
            // TODO: Can this be asynchronous?
            const data = JSON.parse(message);
            this.responder(data).then(response => {
                this.webSocket.send(JSON.stringify(response.message));
                if (response.hasOwnProperty('data')) {
                    this.webSocket.send(response.data);
                }
            }).catch(error => { console.log(error); });
        });
    }
}

module.exports.ServerProtocol = ServerProtocol;

///////////////////////////////////////////////////////////////////////////////
