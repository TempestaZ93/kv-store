CMAKE_MINIMUM_REQUIRED ( VERSION 3.15 )
PROJECT ( kvstore )

SET ( SRC "src/Main.c"
          "src/KVStore.c" )
SET ( HDR "include/KVStore.h" )

ADD_EXECUTABLE ( kvstore ${SRC} ${HDR} )
TARGET_LINK_LIBRARIES ( kvstore m )
TARGET_INCLUDE_DIRECTORIES ( kvstore PRIVATE "include" )
