inherit cmake cmake_qt5

SUMMARY = "VSMT client"
LICENSE = "CLOSED"
SECTION = "devel"

SRC_URI += "file://src/"
SRC_URI += "file://CMakeLists.txt"

EXTRA_OECMAKE += "-Dyocto_deploy=true"

DEPENDS += "qtbase qttools "
RDEPENDS:${PN} += "qtwayland"

S = "${WORKDIR}"
B = "${S}/v2"

PACKAGES = "${PN} ${PN}-dbg"

FILES:${PN} += "/usr/lib/vsmt-client/* /usr/lib/vsmt-client/* "
