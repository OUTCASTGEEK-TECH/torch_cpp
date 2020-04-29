#### Utilities

## Download Function
function(download_file resource_url output_file)
    if (NOT EXISTS ${output_file})
        file(DOWNLOAD ${resource_url} ${output_file}
                SHOW_PROGRESS
                TLS_VERIFY ON)
    endif ()
endfunction(download_file)

## Unzip File
function(unzip_file zip_file_path target_directory output_directory)
    if (EXISTS ${zip_file_path})
        if (NOT EXISTS ${output_directory}/${target_directory})
            execute_process(COMMAND unzip ${zip_file_path}
                    WORKING_DIRECTORY ${output_directory})
        endif ()
    endif ()
endfunction(unzip_file)

## Extract File
function(extract_tar_gz_file tar_gz_file_path target_directory output_directory)
    if (EXISTS ${tar_gz_file_path})
        if (NOT EXISTS ${output_directory}/${target_directory})
            execute_process(COMMAND tar xzvf ${tar_gz_file_path}
                    WORKING_DIRECTORY ${output_directory})
        endif ()
    endif ()
endfunction(extract_tar_gz_file)
