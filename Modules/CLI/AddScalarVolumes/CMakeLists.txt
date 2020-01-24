cmake_minimum_required(VERSION 3.0.2)

#-----------------------------------------------------------------------------
set(MODULE_NAME AddScalarVolumes)

#-----------------------------------------------------------------------------

#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#
# Slicer
#
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#
# ITK
#
set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  ITKImageFunction
  ITKImageGrid
  ITKImageIntensity
  )
find_package(ITK 4.6 COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED)
set(ITK_NO_IO_FACTORY_REGISTER_MANAGER 1) # See Libs/ITKFactoryRegistration/CMakeLists.txt
include(${ITK_USE_FILE})

find_package(Eigen3 REQUIRED)


link_directories(${Slicer_Base_LIBRARY_DIRS})

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/ITKLogo.h
  INSTALL_RUNTIME_DESTINATION ${Slicer_INSTALL_CLIMODULES_BIN_DIR}
  INSTALL_LIBRARY_DESTINATION ${Slicer_INSTALL_CLIMODULES_LIB_DIR}
  INSTALL_ARCHIVE_DESTINATION ${Slicer_INSTALL_CLIMODULES_SHARE_DIR}
  INCLUDE_DIRECTORIES
  ${Slicer_Base_INCLUDE_DIRS}
  ${Slicer_Libs_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  TARGET_LIBRARIES ${ITK_LIBRARIES} ITKFactoryRegistration
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

