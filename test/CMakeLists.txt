
add_executable(ContourToSurfaceRegistrationTest1
  ContourToSurfaceRegistrationTest1.cxx
  )

target_link_libraries(ContourToSurfaceRegistrationTest1 ContourToSurfaceRegistration)

add_test(Test1 ${EXECUTABLE_OUTPUT_PATH}/BinaryThresholdImageFilter
  canon_hist.nii.gz
  canon_hist_mask.nii.gz
  2500 # Threshold value
  )

add_test(Test2 ${EXECUTABLE_OUTPUT_PATH}/DistanceMapImageFilter
  canon_hist_mask.nii.gz
  canon_hist_distance_map.nii.gz
  )

add_test(Test3 ${EXECUTABLE_OUTPUT_PATH}/ContourToSurfaceRegistrationTest1
  inputimage.jpg
  canon_hist_distance_map.nii.gz
  )


