add_library(ContourToSurfaceRegistration
  ContourToSurfaceRegistration.cxx
  )

target_link_libraries(ContourToSurfaceRegistration ${ITK_LIBRARIES})

add_executable(DistanceMapImageFilter DistanceMapImageFilter.cxx)
target_link_libraries(DistanceMapImageFilter ${ITK_LIBRARIES})

add_executable(BinaryThresholdImageFilter BinaryThresholdImageFilter.cxx)
target_link_libraries(BinaryThresholdImageFilter ${ITK_LIBRARIES})
