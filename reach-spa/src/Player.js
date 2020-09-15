///////////////////////////////////////////////////////////////////////////////
// NAME:            Player.js
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements the player
//
// CREATED:         08/29/2020
//
// LAST EDITED:     09/14/2020
////

import React from 'react';
import PATH from './ReachCodecGlue';
import BufferedStreamReader from './BufferedStreamReader';
let reachCodec;

class Player extends React.Component {
    constructor(properties) {
        super(properties);
        this.state = {ready: false, playing: false, filename: ""};
        this.play = this.play.bind(this);

        this.playCallback = () => {};
        this.pauseCallback = () => {};
    }

    bindCallbacksAndData() {
        // TODO: this.decoder = new reachCodec.AudioStreamDecoder();
        this.filePlaying = "";

        // Bind callbacks
        this.playCallback = this.play.bind(this);
        this.pauseCallback = this.pause.bind(this);
    }

    componentDidMount() {
        const script = document.createElement('script');
        // Load the script...
        script.onload = () => {
            // Perform async initialization...
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

        // Have to create the AudioContext here because in Chrome, AudioContext
        // cannot be instantiated before a user gesture.
        if (!this.hasOwnProperty("audioContext")) {
            this.audioContext = new AudioContext();
            this.oscillator = this.audioContext.createOscillator();
            this.oscillator.type = 'square';
            this.oscillator.frequency.setValueAtTime(
                440, this.audioContext.currentTime);
            this.oscillator.connect(this.audioContext.destination);
            // this.oscillator.start();
        } else {
            // this.audioContext.resume();
        }

        if (this.filePlaying !== this.state.filename) {
            // The selected file has changed. Load the new file.
            this.filePlaying = this.state.filename;
            this.reader = new BufferedStreamReader(
                this.filePlaying, 65536);
            this.reader.onRead = message => console.log(message);
            this.reader.onBufferFull = message => console.log('Full buffer!');
            this.reader.read();
        }
    }

    //
    // Pause the audio stream
    //
    pause() {
        this.setState(state => ({playing: false}));
        this.audioContext.suspend();
    }

    render() {
        const playing = this.state.playing;
        return (
            <div className="Player">
              <label>Filename:
                <input name="filename" type="text" value={this.state.filename}
                       onChange={event => this.setState({
                           filename: event.target.value})}/>
              </label>
              <input type="button" value={(playing && "Pause") || "Play"}
                     onClick={(playing && this.pauseCallback)
                              || this.playCallback}/>
            </div>
        );
    }
}

export default Player;

///////////////////////////////////////////////////////////////////////////////
