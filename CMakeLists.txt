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



