#!/bin/bash
sort -n $1 > tmp1
sort -n $2 > tmp2
sort -m tmp1 tmp2
rm tmp1 tmp2

