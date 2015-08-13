#!/bin/bash
emcc test.cpp -Wall --preload-file  img -o test2.html -I../protobuf-emscripten/src -L../protobuf-emscripten/src/.libs -lprotobuf
