set(TEMP ${PROJECT_BINARY_DIR}/Testing/Temporary)

add_executable(ContourToSurfaceRegistrationTest1
  ContourToSurfaceRegistrationTest1.cxx
  )

target_link_libraries(ContourToSurfaceRegistrationTest1 ContourToSurfaceRegistration)

ExternalData_Add_Test(WHSData Test1 ${EXECUTABLE_OUTPUT_PATH}/BinaryThresholdImageFilter
  DATA{canon_hist.nii.gz}
  ${TEMP}/canon_hist_mask.mha
  2500 # Threshold value
  )

ExternalData_Add_Test(WHSData Test2 ${EXECUTABLE_OUTPUT_PATH}/BinaryThresholdImageFilter
  DATA{E80_23109_00040.bmp}
  ${TEMP}/E80_23109_00040_mask.mha
  127 # Threshold value
  )


ExternalData_Add_Test(WHSData Test3 ${EXECUTABLE_OUTPUT_PATH}/DistanceMapImageFilter
  ${TEMP}/canon_hist_mask.mha
  ${TEMP}/canon_hist_distance_map.mha
  )

ExternalData_Add_Test(WHSData Test4 ${EXECUTABLE_OUTPUT_PATH}/ContourToSurfaceRegistrationTest1
  ${TEMP}/E80_23109_00040_mask.mha
  ${TEMP}/canon_hist_distance_map.mha
  )


