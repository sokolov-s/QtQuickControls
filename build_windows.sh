#!/bin/bash - 
#===============================================================================
#
#          FILE:  build_windows.sh
# 
#         USAGE:  ./build_windows.sh 
# 
#   DESCRIPTION:  
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR: Sergey Sokolov, 
#       COMPANY: 
#       CREATED: 17.07.2015 17:38:49 EEST
#      REVISION:  ---
#===============================================================================

if [ -z "$READER_SDK_CFG" ]
then
	toolchain_path=`realpath $HOME/PBReader/mxe`
	source ${toolchain_path}/update_path.sh -p ${toolchain_path}
	toolchaiin_config="${CMAKE_CONFIG_FILE}"
	toolchain_config_path==${CMAKE_TOOLCHAIN_PATH}
	echo -en "\033[0;31m Environment variable READER_SDK_CFG is not set\n Try to assume with - ${toolchain_config_path}/${toolchain_config} \n \033[0m"
else
	toolchain_config=$(basename ${READER_SDK_CFG})
	toolchain_config_path="${READER_SDK_CFG%/*}"
	toolchain_path="${TOOLCHAIN_PATH}"
	echo -en "Use toolchain ${toolchain_config_path}"
fi

src_dir="`pwd`"
build_type="Debug"
system_name="Windows"
build_dir="${src_dir}/build/${system_name}/${build_type}"

cpu_cnt=`nproc`; cpu_cnt=`expr $cpu_cnt`;

CMAKE_BUILD_TYPE="${build_type}"
SRC_DIR=${src_dir}
BUILD_DIR=${build_dir}

CMAKE_INSTALL_PREFIX="${src_dir}/${system_name}"
if [ -z ${CMAKE_TOOLCHAIN_FILE} ]
then
	CMAKE_TOOLCHAIN_PATH="${toolchain_config_path}/${toolchain_config}"
else
	CMAKE_TOOLCHAIN_PATH=${CMAKE_TOOLCHAIN_FILE}
fi


#CMAKE_GEN="MinGW Makefiles"
CMAKE_GEN="Unix Makefiles"
CMAKE="cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_PATH}"
CMAKE_PROJECT="${CMAKE} "

export PB_SDK_CFG=${CMAKE_TOOLCHAIN_PATH}
export TOOLCHAIN_PATH=${toolchain_path}
export TOOLCHAIN_BIN_DIR=${TOOLCHAIN_BIN_PATH}

MAKE="make"
MAKE_PROJECT="${MAKE} -j${cpu_cnt}"

mkdir -p ${build_dir}
cd ${build_dir}


${CMAKE} ${src_dir}
${MAKE_PROJECT}
${MAKE} install
