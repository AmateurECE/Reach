///////////////////////////////////////////////////////////////////////////////
// NAME:            main.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Main for the SPA
//
// CREATED:         08/19/2020
//
// LAST EDITED:     08/29/2020
////

const url = 'ws://localhost:8080/ws';
const connection = new WebSocket(url);

connection.onopen = () => {
    document.getElementById('response').addEventListener('click', () => {
        connection.send(JSON.stringify({position: 0}));
        // try {
        //     window.AudioContext = window.AudioContext
            // || window.webkitAudioContext;
        //     context = new AudioContext();
        // } catch (error) {
        //     alert('Web Audio API is not supported in this browser');
        // }

        // const arrayBuffer =
        // context.createBuffer(message.data.arrayBuffer());
        // const source = context.createBufferSource();
        // source.buffer = arrayBuffer;
        // source.connect(context.destination);
        // source.start(0);
    }, false);
};

connection.onmessage = message => {
    console.log(message);
};

///////////////////////////////////////////////////////////////////////////////
