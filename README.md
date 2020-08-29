# The WebSocket Communication Protocol

There are two kinds of messages in this simple protocol: control and data
messages. The server is the only entity who ever has any reason to send a data
message. The type of a message is inferred from the context in which it is
held. Control messages are sent as JSON. Data messages are sent as raw binary
data.

The client requests frames from the server. Servers do not send data to the
client automatically or gratuitously. In this way, the protocol can maintain
some semblance of statelessness. Frames are zero-indexed.

1. Client requests a frame by index.
2. Server responds with a control message, telling the client the index of the
frame it is sending, the number of frames in the target, and the format of the
frame (e.g. `"flac"`).
3. Server sends the frame in binary format.
