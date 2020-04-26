#### LibTorch

## Download LibTorch
function(install_liborch_mac version)
    get_filename_component(PYTORCH_ARCHIVE_VAR
            ${CMAKE_CURRENT_SOURCE_DIR}/libtorch-macos-${version}.zip
            ABSOLUTE)
    message(PYTORCH_ARCHIVE_VAR: ${PYTORCH_ARCHIVE_VAR})
    get_filename_component(LIBTORCH_DIR_VAR
            ${CMAKE_CURRENT_SOURCE_DIR}/libtorch
            ABSOLUTE)
    message(LIBTORCH_DIR_VAR: ${LIBTORCH_DIR_VAR})
    set(ENV{TORCH_INSTALL_PREFIX} ${LIBTORCH_DIR_VAR})
    download_file(https://download.pytorch.org/libtorch/cpu/libtorch-macos-${version}.zip
            ${PYTORCH_ARCHIVE_VAR})
    unzip_file(${PYTORCH_ARCHIVE_VAR} libtorch ${CMAKE_CURRENT_SOURCE_DIR})
#    list(APPEND CMAKE_PREFIX_PATH ${LIBTORCH_DIR_VAR}/share/cmake/Torch)
endfunction(install_liborch_mac)
