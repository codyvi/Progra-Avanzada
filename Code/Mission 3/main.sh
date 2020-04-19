#!/bin/bash

#grep to get the hashtags
grep -o "hashtag\/[A-Za-z0-9_]\+" $1 | sort -n | uniq -ic > $"html_hashtags.txt"
#remove the hashtag and \ from the txt
cat $"html_hashtags.txt" | sed "s/hashtag//" |  sed "s/\///g" > $"text_hashtags.txt"
#print in screen the hashtags
cat text_hashtags.txt