#!/bin/sh

echo -n File?
read filename
scp "$filename" team@wlan-robot15.private:"$filename"


