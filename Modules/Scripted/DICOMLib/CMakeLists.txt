cmake_minimum_required(VERSION 3.0)

project(DICOMLib)

find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

find_package(CTK REQUIRED)
include(${CTK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(CTK REQUIRED)
include(${CTK_USE_FILE})

#-----------------------------------------------------------------------------
set(MODULE_NAME DICOMLib)
string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)
add_subdirectory(Widgets)
add_subdirectory(SubjectHierarchyPlugins)

#-----------------------------------------------------------------------------
set(MODULE_PYTHON_SCRIPTS
  __init__
  DICOMBrowser
  DICOMExportScalarVolume
  DICOMExportScene
  DICOMPlugin
  DICOMPluginSelector
  DICOMProcesses
  DICOMRecentActivityWidget
  DICOMSendDialog
  DICOMUtils
  )

set(MODULE_PYTHON_RESOURCES
  )

#-----------------------------------------------------------------------------
slicerMacroBuildScriptedModule(
  NAME ${MODULE_NAME}
  SCRIPTS ${MODULE_PYTHON_SCRIPTS}
  RESOURCES ${MODULE_PYTHON_RESOURCES}
  WITH_SUBDIR
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
#  add_subdirectory(Testing)
endif()
