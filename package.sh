#!/usr/bin/env bash
# Package the library into a .zip file

source library.properties

if [ -f "client_config.h" ]; then
    echo "Building in specified client config..."
    cp server_options_client_conf.h server_options.h
else
    cp server_options_default.h server_options.h
fi

zip -r ${name}.zip .
