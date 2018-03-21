#!/bin/bash
# This script is for git add, commit, push

echo "Commit message?"

read msg

git add .
git commit -m "$msg"
git push
