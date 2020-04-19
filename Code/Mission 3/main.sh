#!/bin/bash

#grep to get the hashtags
grep -o "hashtag\/[A-Za-z0-9_]\+" smith.html | sort -n | uniq -ic $1 > html_hashtags.txt
#remove the hashtag and \ from the txt
cat $"html_hashtags.txt" | sed "s/hashtag/ /" |  sed "s/\// /g" > $"text_hashtags.txt"
#print in screen the hashtags
cat text_hashtags.txt