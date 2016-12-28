#!/bin/bash

convert_image_to_header () {
  local inflie="${1}.png"
  local ident=`echo ${1}|tr '-' '_'`
  local file_signature=${ident^^}
  local img_width=$2
  local img_height=$3
  local img_x=$4
  local img_y=$5
  local outfile="xbm_${ident}.h"

  echo "INFO: Input image \"$inflie\" need to be $img_width x $img_height"

  TMP_XBM_FILENAME="_tmp_.xbm"
  convert "artwork/$inflie" $TMP_XBM_FILENAME
  BUF=`cat $TMP_XBM_FILENAME | tail -n +4`
  rm $TMP_XBM_FILENAME

  echo "#ifndef XBM_${file_signature}_H
#define XBM_${file_signature}_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_${file_signature}_WIDTH $img_width
#define XBM_${file_signature}_HEIGHT $img_height
#define XBM_${file_signature}_X $img_x
#define XBM_${file_signature}_Y $img_y

static const uint8_t xbm_${ident}[] PROGMEM = {
$BUF
#endif" > $outfile

  echo "INFO: Successfully written $outfile"
}

sed 1d "artwork/dimension.csv" | while read LINE; do
  NAME=`echo ${LINE} | cut -d , -f 1`
  W=`echo ${LINE} | cut -d , -f 2`
  H=`echo ${LINE} | cut -d , -f 3`
  X=`echo ${LINE} | cut -d , -f 4`
  Y=`echo ${LINE} | cut -d , -f 5`

  convert_image_to_header $NAME $W $H $X $Y
done
