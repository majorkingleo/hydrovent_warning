#!/usr/bin/env bash

git log > ChangeLog
touch NEWS
touch README

aclocal
automake --add-missing
automake -f
autoconf -f

# just skip this stepp when running from ebuild script
if ! [[ ${1} ]] ; then
	./configure
fi
