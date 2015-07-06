#!/bin/bash
emcc test.cpp -Wall --preload-file  img -o test.html -I../protobuf-emscripten/src -L../protobuf-emscripten/src/.libs -lprotobuf
