add_executable (assignment1
        main.cpp
        )

find_package(PythonLibs)

target_include_directories(assignment1
        PUBLIC
            ${USD_INC_DIR}
            ${PYTHON_INCLUDE_PATH}
        )

target_link_libraries(
        assignment1
                ${USD_LIB_DIR}/libgf.dylib
                ${USD_LIB_DIR}/libsdf.dylib
                ${USD_LIB_DIR}/libtf.dylib
                ${USD_LIB_DIR}/libusd.dylib
                ${USD_LIB_DIR}/libusdGeom.dylib
                ${USD_LIB_DIR}/libvt.dylib
                ${USD_LIB_DIR}/libboost_python.dylib # todo find library
                ${PYTHON_LIBRARY}
        )
