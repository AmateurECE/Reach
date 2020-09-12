# The Motivation Behind Reach

I currently use a popular open-source media server to stream my music over the
Internet. The issue, however, is that as I'm collecting more and more
high-quality tracks in lossless codecs such as FLAC, my media server is no
longer able to stream over my 5Mb/s residential upload connection.

The solution is not to sacrifice the quality of the audio, nor to shell out
more money to my ISP for an upgrade. The solution is _Reach_, a tool that
utilizes the existing network bandwidth more efficiently to deliver low-latency
music streaming over any connection.

# Developing

Reach is composed of two different components, as with any web application:
the _server_, and the _client_. Reach follows the thick-client philosophy, so
if you feel the need to do any development, it will probably be on the client.

The Client is an SPA using React.js and a custom WebAssembly script generated
using Emscripten. Like with any react application, the Reach SPA has a
development environment that supports hot-reloading. Docker is required to use
the development server. To start the development environment, simply run
`npm run start` from the `reach-spa` directory.

To build the SPA for production, run `npm run build`.

Dependencies for the SPA are currently managed using the Conan package manager.
The dependencies are hosted on a private Conan server owned by Ethan Twardy,
and any developers may need to reach out to him in order to obtain credentials
for this server in order to install the dependencies. To install dependencies,
first create a profile for cross-compiling with Emscripten:

```
conan profile new --detect emscripten
```

Next, manually edit this profile (stored at `~/.conan/profiles/emscripten`) to
look like the following, replacing `<YourOS>` and `<YourArchitecture>` with
your operating system and architecture, specifically. If you're not sure, copy
them from your default profile (stored at `~/.conan/profiles/default`).

```
[settings]
os=Emscripten
os_build=<YourOS>
arch=wasm
arch_build=<YourArchitecture>
compiler=emcc
compiler.version=2.0
compiler.libcxx=emsdk
build_type=Release
[options]
[build_requires]
[env]
```

Finally, install the dependencies and generate the build info:

```
conan install -pr=emscripten .
```

These steps only need to be performed when building for the first time, or when
updating the `conanfile.txt`.

To build the server application, run `npx webpack` from the `reach` directory.
You may then test the server by running it with node:

```
node build/reach.js
```
