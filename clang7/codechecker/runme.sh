#!/bin/bash

export PATH=/home/dl9pf/codechecker/build/CodeChecker/bin/:$PATH

rm -rf build
mkdir build
cd build
cmake ../rba/

CodeChecker log -b "make -j8" -o compilation.json

CodeChecker analyze compilation.json -o ./report -j 8

mkdir report_html
CodeChecker parse ./report -e html -o report_html/

CodeChecker store ./report --name rba-run-$(date +%Y%m%d-%H%M) --url http://192.168.2.6:8001/Default

# CodeChecker store ./report --name rba-run-$(date +%Y%m%d-%H%M) --url <host with docker container running>
