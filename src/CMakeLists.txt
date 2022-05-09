#find Threads, prefer pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

message("Boost found: ${Boost_FOUND}")

add_subdirectory(deepNeuronalFilter)
include_directories(deepNeuronalFilter)
link_directories(deepNeuronalFilter)


add_executable(AudiClean main.cpp SampleLink.cpp SoxReader.cpp FirLMS.cpp FirDNF.cpp NoiseFilter.cpp FilterInputNoise.cpp FilterInputSignal.cpp FilterInputNoise.cpp Fir1.cpp SoxEndpoint.cpp )
target_link_libraries(AudiClean dnf Threads::Threads)
target_include_directories(AudiClean PRIVATE deepNeuronalFilter)



