#!/usr/bin/env bash
for file in *.doc *.png *.jpg *.jpeg
do
  mv -- "$file" "${file// /_}"
done