set(INSTRUMENT_SRC 
    instrumentFactory.cpp
    instrument.cpp
    singleClef.cpp
    multiClef.cpp
    instrumentDefinitions.cpp
    pianoharp.cpp)

set (SERIALISM_SRC
    serialismGenerator.cpp
    analysisMatrix.cpp
    timeSignature.cpp
    note.cpp
    )

set (PARALLELISM_SRC
    joinThreads.cpp
    threadPool.cpp)


add_library(serialism ${INSTRUMENT_SRC} ${SERIALISM_SRC})
target_include_directories(serialism PUBLIC ${PROJECT_SOURCE_DIR}/inc)

add_library(parallelism ${PARALLELISM_SRC})
target_include_directories(parallelism PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# see if we can keep these libraries separate. 

# Production executable
add_executable( TotalSerialism totalSerialism.cpp)
target_link_libraries(TotalSerialism serialism parallelism)