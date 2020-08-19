///////////////////////////////////////////////////////////////////////////////
// NAME:            main.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Main for the SPA
//
// CREATED:         08/19/2020
//
// LAST EDITED:     08/19/2020
////

const url = 'ws://localhost:8080/ws';
const connection = new WebSocket(url);

connection.onopen = () => {
    connection.send('Hello, server!');
};

connection.onmessage = message => {
    document.getElementById('response').innerHTML = message.data;
};

///////////////////////////////////////////////////////////////////////////////
