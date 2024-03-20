#!/usr/bin/bash
podman run -it --rm -p 5000:5000 -v waterlevel:/app localhost/waterlevel:latest /bin/bash
