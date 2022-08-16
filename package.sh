#!/usr/bin/env bash
# Package the library into a .zip file

source library.properties 2>/dev/null

if [ -f "client_config.h" ]; then
    cp server_options_client_conf.h server_options.h
else
    cp server_options_default.h server_options.h
fi

zip -r ${name}.zip . 2>&1 > /dev/null
echo ${name}.zip