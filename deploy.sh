#!/bin/bash -xe
git push
(cd build; make)
ssh -i ~/amazon.pem ubuntu@52.32.84.215 "killall ff1-online-server ff1-online-bot || true"
scp -i ~/amazon.pem build/ff1-online-server build/bot/ff1-online-bot bot-*.txt ubuntu@52.32.84.215:
ssh -i ~/amazon.pem ubuntu@52.32.84.215 "nohup ./ff1-online-server > /dev/null 2>&1 &"
ssh -i ~/amazon.pem ubuntu@52.32.84.215 "for i in bot-*.txt; do nohup ./ff1-online-bot \$i > /dev/null 2>&1 & done"
