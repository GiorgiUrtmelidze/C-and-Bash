#!/bin/bash

# First argument of cp_files is always
# current directory -> $1

cp_files() {
	local curr_dir="$1"
	
	for file in "$curr_dir"/*;
	do
		if [[ -f "$file" && "$file" == *.c ]];
		then
			new_name="${file}.orig"
			cp "$file" "$new_name"
		elif [[ -d "$file" ]];
		then
			# If it is a directory then do
			# the same work...
			cp_files "$file"
		fi
	done
}

cp_files "$(pwd)"



