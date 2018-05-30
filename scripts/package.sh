#!/usr/bin/env bash

set -e

BUILD_DIR=build
APP_NAME=Q2Pro
APP_DIR=${BUILD_DIR}/${APP_NAME}.app
CONTENT_DIR=${APP_DIR}/Contents
BIN_DIR=${CONTENT_DIR}/MacOS
RESOURCE_DIR=${CONTENT_DIR}/Resources
LIB_DIR=${CONTENT_DIR}/Library
DMG_IMAGE=${BUILD_DIR}/${APP_NAME}.dmg
VOLUME_NAME=${APP_NAME}

rm -rf ${BUILD_DIR}

mkdir -p ${APP_DIR}
mkdir -p ${CONTENT_DIR}
mkdir -p ${BIN_DIR}
mkdir -p ${RESOURCE_DIR}
mkdir -p ${LIB_DIR}
mkdir -p ${BIN_DIR}/baseq2

cp scripts/apple/Info.plist ${CONTENT_DIR}
cp q2pro ${BIN_DIR}
cp q2proded ${BIN_DIR}
cp gamex86_64.so ${BIN_DIR}/baseq2

cp scripts/apple/q2pro.icns ${RESOURCE_DIR}
cp -r scripts/baseq2 ${RESOURCE_DIR}
cp -r src/client/ui/q2pro.menu ${RESOURCE_DIR}/baseq2

dylibbundler -b \
    -x "${BIN_DIR}/q2pro" \
    -x "${BIN_DIR}/q2proded" \
    -d "${LIB_DIR}" -of -p @executable_path/Library

ln -f -s /Applications ${BUILD_DIR}/Applications
hdiutil create ${DMG_IMAGE} -srcfolder ${BUILD_DIR} -volname ${VOLUME_NAME}
