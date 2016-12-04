# AVA API

# Usage

```bash
  git clone --recursive https://github.com/ava-project/ava-api
```


# Choice of technologies


# Serialization:

- Google Protocol Buffer:

Google Protocol Buffer are Google's language-neutral, platform-neutral,
extensible mechanism for serializing structured data.


# Communication:

A c++11 network library is currently under development. This library will have
no dependencies and will work only with c++11 features.
The library will provide:

- TCP server (endpoint for the API)
- Thread Pool
- Events listener to dispatch correctly and effectively incoming connections
