<h1 align="center">Jellyfin Pi</h1>
<h3 align="center" style="font-weight: bold">Jellyfin Pi is not an Official Jellyfin Client! Yet?</h3>
<!-- <h3 align="center"><span style="font-weight: bold; color: red;">NOT</span> Part of the <a href="https://jellyfin.org">Jellyfin Project</a></h3> -->

---

Jellyfin Pi is my attempt at making a standalone Jellyfin client available for
the Raspberry Pi 4, or later.

Currently the only ways to use Jellyfin on a Raspberry Pi is to use the
Kodi add-on, or to run the Raspberry Pi with a desktop browser in order
to use the web client.

## DISCLAIMER

This Project is in it's infancy and is not currently in a functional state. If
you came here looking for a turnkey Jellyfin client for your Raspberry Pi, I
apologize for disappointing you. Check back in the future, as the project matures.

## Goals

I'm sure I'll make compromises, especially early on, but the overarching
goal is to have a Jellyfin client that renders with Linux DRM/KMS and
provides functionality on par with that provided by the Jellyfin Web client.

## Build Process

### Dependencies

   * build-essential
   * git
   * cmake
   * libmpv-dev
   * libcurl4-openssl-dev
   * libgbm-dev
   * libdrm-dev
   * libegl-dev

### Getting Started

1. Clone or download this repository.

   ```sh
   git clone https://github.com/Moros1138/jellyfin-pi.git
   cd jellyfin-pi
   ```

2. Install build dependencies.

   ```sh
   sudo apt install build-essential git cmake libmpv-dev libcurl4-openssl-dev libgbm-dev libdrm-dev libegl-dev
   ```

3. Generate CMake Configuration/Build files.
   ```sh
   cmake -S . -B build
   ```

4. Build the client.

   ```sh
   cmake --build build
   ```

## Directory Structure

```
.
├── src                         # C/C++ source files
└── assets                      # Static assets
```

<!-- - ❌ &mdash; Deprecated, do **not** create new files here
- 🧹 &mdash; Needs cleanup
- 🐉 &mdash; Serious mess (Here be dragons) -->

