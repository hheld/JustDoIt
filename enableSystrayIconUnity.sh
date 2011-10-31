#!/bin/bash

# Note that is is not necessary any more in Ubuntu 11.10. However, without whitelisting this application, there will be no system
# tray icon in Ubuntu 11.04 using Unity.

currentSettings=`gsettings get com.canonical.Unity.Panel systray-whitelist`
newSettings=`echo $currentSettings | sed -e "s/\]$/, 'JustDoIt']/g"`

gsettings set com.canonical.Unity.Panel systray-whitelist "$newSettings"

