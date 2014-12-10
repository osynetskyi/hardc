#!/bin/bash

set -e
./devpkg -L NULL
./devpkg -I https://dist.torproject.org/tor-0.2.4.23.tar.gz
./devpkg -S NULL
./devpkg -F https://dist.torproject.org/tor-0.2.4.23.tar.gz
set +e
