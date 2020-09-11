///////////////////////////////////////////////////////////////////////////////
// NAME:            Player.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements the player
//
// CREATED:         08/29/2020
//
// LAST EDITED:     09/11/2020
////

import React from 'react';
import PATH from './ReachCodecGlue';
let reachCodec;

class Player extends React.Component {
    constructor(properties) {
        super(properties);
        this.state = {ready: false};
        this.play = this.play.bind(this);
    }

    componentDidMount() {
        const script = document.createElement('script');
        script.onload = () => {
            window.ReachCodec().then(reachCodecModule => {
                reachCodec = reachCodecModule;
                this.setState(state => ({ready: true}));
            });
        };
        document.body.appendChild(script);
        script.src = PATH;
    }

    play() {}

    render() {
        const ready = this.state.ready;
        let message = "Play";
        if (ready) {
            const decoder = new reachCodec.StreamDecoder();
            message = decoder.getMessage();
        }
        return (
            <div className="Player">
              {ready && <button onClick={this.play}>{message}</button>}
            </div>
        );
    }
}

export default Player;

///////////////////////////////////////////////////////////////////////////////
