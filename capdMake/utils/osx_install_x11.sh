wget "http://xquartz.macosforge.org/downloads/SL/XQuartz-2.7.7.dmg" -O /tmp/XQuartz-2.7.7.dmg
hdiutil attach /tmp/XQuartz-2.7.7.dmg
sudo installer -pkg /Volumes/XQuartz-2.7.7/XQuartz.pkg -target /
ln -s /opt/X11/include/X11 /usr/local/include/X11
ln -s /opt/X11/lib/libX11.dylib /usr/local/lib/libX11.dylib
ln -s /opt/X11/lib/pkgconfig/{x11,xproto,kbproto,xcb,pthread-stubs,xau,xdmcp}.pc /usr/local/lib/pkgconfig/
