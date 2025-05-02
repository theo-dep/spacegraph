include(FetchContent)

FetchContent_Declare(erased
    GIT_REPOSITORY https://github.com/qnope/Erased.git
    GIT_TAG main
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(erased)
