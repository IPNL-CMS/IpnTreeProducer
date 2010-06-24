#!/usr/local/bin/bash
# Small script to delete all jobs on batch
# Written by Olivier Bondu (January 2010)

#for file in `'qjob' -l | awk '{print $2}'`
for file in `'qjob' -l | awk '{print $2}' | tail -n +3`
do
	qdel "$file"
done

exit 0
