#!/bin/bash

currentSettings=`gsettings get com.canonical.Unity.Panel systray-whitelist`
newSettings=`echo $currentSettings | sed -e "s/\]$/, 'JustDoIt']/g"`

gsettings set com.canonical.Unity.Panel systray-whitelist "$newSettings"

