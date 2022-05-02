#find Threads, prefer pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_subdirectory(deepNeuronalFilter)

include_directories(deepNeuronalFilter)

add_executable(AudiClean main.cpp SampleLink.cpp WavReader.cpp FirLMS.cpp FirFilter.cpp FilterInputNoise.cpp FilterInputSignal.cpp FilterInputNoise.cpp Fir1.cpp  )
target_link_libraries(AudiClean Threads::Threads)

add_library(WavReader WavReader.cpp WavReader.h)
target_link_libraries(WavReader Threads::Threads)