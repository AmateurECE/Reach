///////////////////////////////////////////////////////////////////////////////
// NAME:            Player.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements the player
//
// CREATED:         08/29/2020
//
// LAST EDITED:     09/09/2020
////

import React from 'react';
import Module from './flac-decoder/StreamDecoder';

const url = 'ws://localhost:5000';
class Player extends React.Component {
    static flac = undefined;

    constructor(properties) {
        super(properties);
        this.state = {
            message: ""
        };

        this.initializeDecoder();
        this.obtainMessage = () => {};
    }

    initializeDecoder() {
        if (Player.flac === undefined) {
            Player.flac = null;
            Module().then(flac => {
                Player.flac = flac;
                this.obtainMessage = this.obtainMessage.bind(this);
            });
        }
    }

    obtainMessage() {
        const decoder = Player.flac.StreamDecoder();
        this.setState(state => ({message: decoder.getMessage()}));
    }

    render() {
        const connected = this.state.connected;
        return (
            <div className="Player">
              {connected &&
               <button onClick={this.obtainMessage}>
                 {this.state.message || "Get Segment"}
               </button>
              }
            </div>
        );
    }
}

export default Player;

///////////////////////////////////////////////////////////////////////////////
