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

## Download CIFAR10
function(install_cifar10)
    get_filename_component(CIFAR10_ARCHIVE_VAR
            ${CMAKE_CURRENT_SOURCE_DIR}/cifar-10-binary.tar.gz
            ABSOLUTE)
    message(CIFAR10_ARCHIVE_VAR: ${CIFAR10_ARCHIVE_VAR})
    get_filename_component(CIFAR10_DIR_VAR
            ${CMAKE_CURRENT_SOURCE_DIR}/cifar-10-batches-bin
            ABSOLUTE)
    message(CIFAR10_DIR_VAR: ${CIFAR10_DIR_VAR})
    download_file(https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz
            ${CIFAR10_ARCHIVE_VAR})
    extract_tar_gz_file(${CIFAR10_ARCHIVE_VAR} cifar-10-batches-bin ${CMAKE_CURRENT_SOURCE_DIR})
endfunction(install_cifar10)
