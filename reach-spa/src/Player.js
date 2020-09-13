///////////////////////////////////////////////////////////////////////////////
// NAME:            Player.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements the player
//
// CREATED:         08/29/2020
//
// LAST EDITED:     09/13/2020
////

import React from 'react';
import PATH from './ReachCodecGlue';
let reachCodec;

class Player extends React.Component {
    constructor(properties) {
        super(properties);
        this.state = {ready: false, playing: false};
        this.play = this.play.bind(this);

        this.playCallback = () => {};
        this.pauseCallback = () => {};
    }

    bindCallbacksAndData() {
        // TODO: this.decoder = new reachCodec.AudioStreamDecoder();
        // Bind callbacks
        this.playCallback = this.play.bind(this);
        this.pauseCallback = this.pause.bind(this);
    }

    componentDidMount() {
        const script = document.createElement('script');
        script.onload = () => {
            window.ReachCodec().then(reachCodecModule => {
                reachCodec = reachCodecModule;
                this.bindCallbacksAndData();

                // Must set the state after binding so the component is
                // re-rendered with the new callbacks.
                this.setState(state => ({ready: true}));
            });
        };
        document.body.appendChild(script);
        script.src = PATH;
    }

    //
    // Play the audio stream
    //
    play() {
        this.setState(state => ({playing: true}));
        if (!this.hasOwnProperty("audioContext")) {
            this.audioContext = new AudioContext();
            this.oscillator = this.audioContext.createOscillator();
            this.oscillator.type = 'square';
            this.oscillator.frequency.setValueAtTime(
                440, this.audioContext.currentTime);
            this.oscillator.connect(this.audioContext.destination);
        }

        this.oscillator.start();
    }

    //
    // Pause the audio stream
    //
    pause() {
        this.setState(state => ({playing: false}));
        this.oscillator.stop();
    }

    render() {
        const playing = this.state.playing;
        return (
            <div className="Player">
              {(playing && <button onClick={this.pauseCallback}>Pause</button>)
               || <button onClick={this.playCallback}>Play</button>}
            </div>
        );
    }
}

export default Player;

///////////////////////////////////////////////////////////////////////////////
