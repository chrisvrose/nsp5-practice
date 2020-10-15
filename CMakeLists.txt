cmake_minimum_required(VERSION 3.0.0)
project(nsp VERSION 0.1.0)

# Add include directories to pull from
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)


# Standard tcp server
set(SRC_DEFC
    src/defserver.c
)
add_executable(defserver ${SRC_DEFC})

# Standard tcp client
set(SRC_DEFS
    src/defclient.c
)
add_executable(defclient ${SRC_DEFS})


# Echo client
set(SRC_EC
    src/ec.c
)
add_executable(ec ${SRC_EC})

# Echo server -> concurrent
set(SRC_ES
    src/es.c
)
add_executable(es ${SRC_ES})


# Timeclient
set(SRC_TC
    src/tc.c
)
add_executable(tc ${SRC_TC})

set(SRC_TS
    src/ts.c
)
add_executable(ts ${SRC_TS})


set(SRC_FS
    src/fs.c
)
add_executable(fs ${SRC_FS})



set(SRC_FC
    src/fc.c
)
add_executable(fc ${SRC_FC})