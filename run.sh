#!/bin/bash

if [ -z $1 ]
then
    export DYLD_LIBRARY_PATH=`pwd`"/" DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=`pwd`"/libft_malloc.so"
else
    unset DYLD_FORCE_FLAT_NAMESPACE DYLD_INSERT_LIBRARIES DYLD_LIBRARY_PATH
fi
