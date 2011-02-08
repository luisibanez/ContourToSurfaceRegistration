set(TEMP ${PROJECT_BINARY_DIR}/Testing/Temporary)

add_executable(ContourToSurfaceRegistrationTest1
  ContourToSurfaceRegistrationTest1.cxx
  )

target_link_libraries(ContourToSurfaceRegistrationTest1 ContourToSurfaceRegistration)

add_test(Test1 ${EXECUTABLE_OUTPUT_PATH}/BinaryThresholdImageFilter
  DATA{canon_hist.nii.gz}
  ${TEMP}/canon_hist_mask.nii.gz
  2500 # Threshold value
  )

add_test(Test2 ${EXECUTABLE_OUTPUT_PATH}/DistanceMapImageFilter
  ${TEMP}/canon_hist_mask.nii.gz
  ${TEMP}/canon_hist_distance_map.nii.gz
  )

add_test(Test3 ${EXECUTABLE_OUTPUT_PATH}/ContourToSurfaceRegistrationTest1
  inputimage.jpg
  ${TEMP}/canon_hist_distance_map.nii.gz
  )


