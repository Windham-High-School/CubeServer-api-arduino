#!/usr/bin/env bash
# Package the library into a .zip file

source library.properties 2>/dev/null

if [ -f "client_config.h" ]; then
    cp server_options_client_conf.h server_options.h
else
    cp server_options_default.h server_options.h
fi

mkdir ${name}
cp README.md server.h server.cpp server_options.h server_options_client_conf.h server_options_default.h LICENSE library.properties keywords.txt compile_time.h ./${name}/
zip -r ${name}.zip ./${name} 2>&1 > /dev/null
echo ${name}.zip
