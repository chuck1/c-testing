#!/bin/bash
here=$PWD

docs=$(find ../../ -path ../../external -prune -o -name doc -print)

echo "here: $here"
echo "docs: $docs"

regex=".*/(\w+)$"

for d in $docs
do
	home=${d/\/doc/}
	doc=$here/$d
	src=$here/$home/src
	
	name=unknown
	if [[ $home =~ $regex ]]; then
		n=${#BASH_REMATCH[*]}
			
		if [[ $n -eq 2 ]]; then
			name=${BASH_REMATCH[1]}
		fi
	fi
	
	tagfile=$here/$name.tag
	touch $tagfile	
	
	here_manged=${here//\//\\\@}
	doc_manged=${doc//\//\\\@}
	src_manged=${src//\//\\\@}	
	home_manged=${home//\//\\\@}
	tagfile_manged=${tagfile//\//\\\@}
	
	echo "home:           $home"
	echo "doc:            $doc"
	echo "src:            $src"
	echo "doc_manged:     $doc_manged"
	echo "src_manged:     $src_manged"
	echo "tagfile_manged: $tagfile_manged"
	
	
	doxygen -s -g $d/D1 > doxygen_log
	
	
	
	perl -pe "s/^PROJECT_NAME    .*/PROJECT_NAME           = $name/"                     $d/D1 > $d/D2
	perl -pe "s/^OUTPUT_DIRECTORY.*/OUTPUT_DIRECTORY       = $doc_manged/"               $d/D2 > $d/D3
	perl -pe "s/^CREATE_SUBDIRS  .*/CREATE_SUBDIRS         = YES/"                       $d/D3 > $d/D4
	perl -pe "s/^RECURSIVE       .*/RECURSIVE              = YES/"                       $d/D4 > $d/D5
	perl -pe "s/^INPUT           .*/INPUT                  = $src_manged/"               $d/D5 > $d/D6
	perl -pe "s/^EXCLUDE_PATTERNS.*/EXCLUDE_PATTERNS       = *\/old\/* *\/doc\/*/"       $d/D6 > $d/D7
	perl -pe "s/^GENERATE_TAGFILE.*/GENERATE_TAGFILE       = $tagfile_manged/"           $d/D7 > $d/D8
	perl -pe "s/^OUTPUT_DIRECTORY.*/OUTPUT_DIRECTORY       = $doc_manged/"               $d/D8 > $d/D9
	perl -pe "s/^OUTPUT_DIRECTORY.*/OUTPUT_DIRECTORY       = $doc_manged/"               $d/D9 > $d/D10
	





	
	
	perl -pe "s/\@/\//g" $d/D10 > $d/Doxyfile

	
done


tagfiles_all=$(find . -name '*.tag' -print)

echo tagfiles: $tagfiles_all

for d in $docs
do
	home=${d/\/doc/}
	
	name="unknown"
	if [[ $home =~ $regex ]]; then
		n=${#BASH_REMATCH[*]}
			
		if [[ $n -eq 2 ]]; then
			name=${BASH_REMATCH[1]}
		fi
	fi	

	echo "name: $name"

	tagfiles=""

	for t in $tagfiles_all
	do	
		t_file=${t/.\//}
		t_name=${t_file/.tag/}
		
		
		
		echo "t_name: $t_name"

		if [ $t_name != $name ]; then
			echo "found: $t"
			tagfiles="$tagfiles $here/$t_file"
		fi
		
		
	done
	
	echo "tagfiles: $tagfiles"
done














