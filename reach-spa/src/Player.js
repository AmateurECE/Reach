///////////////////////////////////////////////////////////////////////////////
// NAME:            Player.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements the player
//
// CREATED:         08/29/2020
//
// LAST EDITED:     08/29/2020
////

import React from 'react';

const url = 'ws://localhost:5000';
class Player extends React.Component {
    constructor(properties) {
        super(properties);
        this.webSocket = new WebSocket(url);
        this.state = {
            connected: false
        };

        this.webSocket.onopen = () => { this.setState(state => ({
            connected: true})); };
        this.webSocket.onmessage = message => { console.log(message); };

        try {
            window.AudioContext = window.AudioContext
                || window.webkitAudioContext;
            this.audioContext = new AudioContext();
        } catch (error) {
            alert('Web Audio API is not supported in this browser');
        }

        this.obtainSegment = this.obtainSegment.bind(this);
    }

    obtainSegment() {
        this.webSocket.send(JSON.stringify({position: 0}));
        // const arrayBuffer =
        // context.createBuffer(message.data.arrayBuffer());
        // const source = context.createBufferSource();
        // source.buffer = arrayBuffer;
        // source.connect(context.destination);
        // source.start(0);
    }

    render() {
        const connected = this.state.connected;
        return (
            <div className="Player">
              {connected &&
               <button onClick={this.obtainSegment}>
                 Get Segment
               </button>
              }
            </div>
        );
    }
}

export default Player;

///////////////////////////////////////////////////////////////////////////////
