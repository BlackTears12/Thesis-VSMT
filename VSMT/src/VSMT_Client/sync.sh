rm ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-client-linux/files/src/* -r

cp vsmt-client-linux.bb ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-client-linux/
cp CMakeLists.txt ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-client-linux/files
cp src/* ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-client-linux/files/src/
cp ../common/* ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-client-linux/files/src/ -r