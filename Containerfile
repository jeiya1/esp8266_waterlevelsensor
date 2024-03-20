FROM quay.io/toolbx-images/debian-toolbox:latest

WORKDIR /app

RUN apt update

RUN apt install -y python3.11 python3-flask python3-flask-cors curl

RUN apt install -y libgirepository1.0-dev gcc libcairo2-dev pkg-config python3.11-dev

EXPOSE 5000
