#find Threads, prefer pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)

message("Boost found: ${Boost_FOUND}")

add_subdirectory(deepNeuronalFilter)
add_subdirectory(cvui)
include_directories(deepNeuronalFilter cvui)
link_directories(deepNeuronalFilter)


add_executable(AudiClean main.cpp SoxReader.cpp FirLMS.cpp LinkDNF.cpp NoiseFilter.cpp FilterInputNoise.cpp FilterInputSignal.cpp FilterInputNoise.cpp Fir1.cpp SoxEndpoint.cpp Plotter.cpp SampleLink.cpp )
target_link_libraries(AudiClean dnf Threads::Threads ${OpenCV_LIBS})
target_include_directories(AudiClean PRIVATE deepNeuronalFilter)



