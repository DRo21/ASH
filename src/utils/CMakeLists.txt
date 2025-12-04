add_library(utils
    logging.c
    string_helpers.c
)
target_include_directories(utils PUBLIC ../../include)
