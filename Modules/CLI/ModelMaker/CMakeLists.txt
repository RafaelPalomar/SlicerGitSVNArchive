cmake_minimum_required(VERSION 3.0.2)

#-----------------------------------------------------------------------------
set(MODULE_NAME ModelMaker)

#-----------------------------------------------------------------------------

find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})
#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include (${ITK_USE_FILE})

link_directories(
  ${Slicer_Libs_LIBRARY_DIRS}
  ${Slicer_Base_LIBRARY_DIRS}
  )

#-----------------------------------------------------------------------------
# TODO: Remove SlicerBaseLogic once pass in color node information
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  INSTALL_RUNTIME_DESTINATION ${Slicer_INSTALL_CLIMODULES_BIN_DIR}
  INSTALL_LIBRARY_DESTINATION ${Slicer_INSTALL_CLIMODULES_LIB_DIR}
  INSTALL_ARCHIVE_DESTINATION ${Slicer_INSTALL_CLIMODULES_SHARE_DIR}
  TARGET_LIBRARIES vtkITK ModuleDescriptionParser MRMLCore SlicerBaseLogic SlicerBaseCLI ${VTK_LIBRARIES} ${ITK_LIBRARIES} ITKFactoryRegistration
  INCLUDE_DIRECTORIES
  ${Slicer_Base_INCLUDE_DIRS}
  ${vtkITK_INCLUDE_DIRS}
  ${Slicer_Libs_INCLUDE_DIRS}
  ${SlicerBaseLogic_SOURCE_DIR} ${SlicerBaseLogic_BINARY_DIR}
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
