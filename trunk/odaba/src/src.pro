TEMPLATE=subdirs
CONFIG=ordered

SUBDIRS= zlib \
         linktest/zlib \
         greta \
         linktest/greta \
         sos \
         linktest/sos \
         libserver \
         linktest/libserver \
         if_structure \
         linktest/if_structure \
         if_dbbase \
         if_systemclass \
         ctxinterface \
         linktest/ctxinterface \
         adkctxi \
         linktest/adkctxi \
         libtool \
         linktest/libtool \
         linktest \
         binaries \
         


#the client lib is not supported
SUBDIRSA=     libclient \
         linktest/libclient \
