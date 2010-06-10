#!/bin/bash
# Small script to convert eps plots in a given dir/eps directory to pdf plots in dir/pdf
# Written by O. Bondu (June 2010)

syntax="Syntax ${0} {directory}"

if [[ -z ${1} ]]
then
  echo ${syntax}
	exit 1
fi

directory=${1}

for epsfiles in `'ls' ${directory}/eps`
do
	basename=`echo ${epsfiles} | cut -d . -f -1`
	echo "Converting ${epsfiles}"
	convert ${directory}/eps/${epsfiles} ${directory}/pdf/${basename}.pdf
done

exit 0

