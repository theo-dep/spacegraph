include(FetchContent)

FetchContent_Declare(erased
    GIT_REPOSITORY https://github.com/qnope/Erased.git
    GIT_TAG 544529135a0daa0152c1957932b610d1ccfa6ba9
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(erased)
