#!/bin/bash

trap "rm -f temp$$;exit 0" 2 3
touch temp$$
sleep 60
