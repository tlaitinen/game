#!/bin/bash
emcc test.cpp -o test.html -I../protobuf-emscripten/src -L../protobuf-emscripten/src/.libs -lprotobuf
