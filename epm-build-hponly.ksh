#!/bin/ksh

scriptName=${0##*/}

# Packaging
if [ `uname -s` = "Linux" ]
then 
  if [ -f /usr/bin/dpkg ]
  then
    TARGET_FORMAT="deb"
  else
    TARGET_FORMAT="rpm"
  fi
else
  TARGET_FORMAT="depot"
fi

NAME_LIST="core diameter-protocol radius-protocol octcap-protocol synchro-protocol library-java-synchro xcap-protocol h248-protocol msrp-protocol sip-protocol  trans-tls crypto trans-sctp external-lib-sctp mbi-protocol binary-body-not-interp-protocol orga-protocol dcc-protocol h323-registration-protocol tcap-ip-protocol"

BUILD_VERSION_FILE=build.conf
LIST_DIRECTORY=epm-list

. ./${BUILD_VERSION_FILE}

cd work-${PROJECT_VERSION}

echo "****** ${TARGET_FORMAT}"
echo "****** ${PROJECT_NAME}"
echo "****** ${PROJECT_VERSION}"


case ${TARGET_FORMAT} in 
   deb | rpm )
     TOOL_FORMAT=${TARGET_FORMAT}
     TOOL_SYSTEM=linux
   ;;

   depot)
     TOOL_FORMAT=swinstall
     TOOL_SYSTEM=hpux
   ;;

   *)
     echo "Unknown [${TARGET_FORMAT}]"
     exit 1
     ;;

esac


for target_name in ${NAME_LIST}
do

  if test ! -f ${PROJECT_NAME}-${target_name}.list
  then
     cat ../${LIST_DIRECTORY}/${PROJECT_NAME}-${target_name}.list | \
	  sed -e 's/tool-version/'${PROJECT_VERSION}'/' | \
	  sed -e 's/tool-format/'${TOOL_FORMAT}'/' | \
	  sed -e 's/tool-system/'${TOOL_SYSTEM}'/' | \
	  sed -e 's/build-version/build-'${PROJECT_VERSION}'/g' > ${PROJECT_NAME}-${target_name}.list
  fi

  epm -vv -f ${TOOL_FORMAT} ${PROJECT_NAME}-${target_name}

done

