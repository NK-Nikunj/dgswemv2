set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

list (APPEND RKDG_SWE_SOURCES
  ${PROJECT_SOURCE_DIR}/source/problem/SWE/problem_parser/swe_parser.cpp
  ${PROJECT_SOURCE_DIR}/source/problem/SWE/problem_input/swe_inputs.cpp

  ${PROJECT_SOURCE_DIR}/source/preprocessor/mesh_metadata.cpp
  ${PROJECT_SOURCE_DIR}/source/preprocessor/ADCIRC_reader/adcirc_format.cpp

  ${PROJECT_SOURCE_DIR}/source/simulation/stepper/rk_stepper.cpp

  ${PROJECT_SOURCE_DIR}/source/basis/polynomials/basis_polynomials.cpp
  ${PROJECT_SOURCE_DIR}/source/basis/bases_1D/basis_legendre_1D.cpp
  ${PROJECT_SOURCE_DIR}/source/basis/bases_2D/basis_dubiner_2D.cpp

  ${PROJECT_SOURCE_DIR}/source/shape/shapes_2D/shape_straighttriangle.cpp

  ${PROJECT_SOURCE_DIR}/source/integration/integrations_2D/integration_dunavant_2D.cpp
  ${PROJECT_SOURCE_DIR}/source/integration/integrations_1D/integration_gausslegendre_1D.cpp
)

add_executable(
  RKDG_MANUFACTURED_SOLUTION_SERIAL
  ${PROJECT_SOURCE_DIR}/examples/rkdg_swe_manufactured_solution/manufactured_main_swe.cpp
  ${RKDG_SWE_SOURCES}
)

target_include_directories(RKDG_MANUFACTURED_SOLUTION_SERIAL PRIVATE ${YAML_CPP_INCLUDE_DIR})  
target_link_libraries(RKDG_MANUFACTURED_SOLUTION_SERIAL ${YAML_CPP_LIBRARIES})

if(USE_OMPI)
  add_executable(
    RKDG_MANUFACTURED_SOLUTION_OMPI
    ${PROJECT_SOURCE_DIR}/examples/rkdg_swe_manufactured_solution/manufactured_ompi_main_swe.cpp
    ${RKDG_SWE_SOURCES}
    ${PROJECT_SOURCE_DIR}/source/communication/ompi_communicator.cpp
  )

  target_include_directories(RKDG_MANUFACTURED_SOLUTION_OMPI PRIVATE ${YAML_CPP_INCLUDE_DIR} ${MPI_CXX_INCLUDE_PATH})

  target_link_libraries(RKDG_MANUFACTURED_SOLUTION_OMPI ${YAML_CPP_LIBRARIES} ${MPI_CXX_LIBRARIES})

  install(TARGETS RKDG_MANUFACTURED_SOLUTION_OMPI DESTINATION bin)
endif()

if(USE_HPX)
  add_executable(
    RKDG_MANUFACTURED_SOLUTION_HPX
    ${PROJECT_SOURCE_DIR}/examples/rkdg_swe_manufactured_solution/manufactured_hpx_main_swe.cpp
    ${RKDG_SWE_SOURCES}
    ${PROJECT_SOURCE_DIR}/source/communication/hpx_communicator.cpp
  )

  set_target_properties(RKDG_MANUFACTURED_SOLUTION_HPX PROPERTIES COMPILE_FLAGS "-DHAS_HPX")

  hpx_setup_target(
    RKDG_MANUFACTURED_SOLUTION_HPX
    COMPONENT_DEPENDENCIES iostreams
  )

  target_include_directories(RKDG_MANUFACTURED_SOLUTION_HPX PRIVATE ${YAML_CPP_INCLUDE_DIR} ${HPX_INCLUDE_DIRS})
  target_link_libraries(RKDG_MANUFACTURED_SOLUTION_HPX ${YAML_CPP_LIBRARIES} ${HPX_LIBRARIES})

  install(TARGETS RKDG_MANUFACTURED_SOLUTION_HPX DESTINATION bin)
endif()

install(TARGETS RKDG_MANUFACTURED_SOLUTION_SERIAL DESTINATION bin)
