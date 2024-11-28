rm ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/files/src/* -r

cp vsmt-hyp-gateway.bb ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/
cp CMakeLists.txt ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/files
cp src/* ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/files/src/
cp ../common/* ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/files/src/ -r
cp ../VSMT_Hyp_Shared/* ~/AGL/needlefish/meta-vsmt/recipes-core/vsmt-hyp-gateway/files/src/ -r