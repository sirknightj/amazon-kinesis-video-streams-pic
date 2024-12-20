#!/usr/bin/env bash

if [[ -z $CLANG_FORMAT ]] ; then
    CLANG_FORMAT=clang-format
fi

if NOT type $CLANG_FORMAT 2> /dev/null ; then
    echo "No appropriate clang-format found."
    exit 1
fi

FAIL=0
SOURCE_FILES=`find src -type f \( -name '*.h' -o -name '*.c' \) -not -path "*/external/*"`
echo "Performing clang format compliance check...."
for i in $SOURCE_FILES
do
    $CLANG_FORMAT --dry-run --Werror $i
    if [ $? -ne 1 ]
    then
        FAIL=1
    fi
done

if [ $FAIL -eq 1 ]; then
    echo "Clang check failed for the project"
else
    echo "Clang check passed for the project"
fi

exit $FAIL
