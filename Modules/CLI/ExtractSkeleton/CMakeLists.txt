cmake_minimum_required(VERSION 3.0)

project(ExtractSkeleton)

#-----------------------------------------------------------------------------
set(MODULE_NAME ExtractSkeleton)

#-----------------------------------------------------------------------------

#
# Slicer
#
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})


#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#
# VTK
#
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


#
# ITK
#
set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  )
find_package(ITK 4.6 COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED)
set(ITK_NO_IO_FACTORY_REGISTER_MANAGER 1) # See Libs/ITKFactoryRegistration/CMakeLists.txt
include(${ITK_USE_FILE})

#-----------------------------------------------------------------------------
# Disable MSVC 8 warnings
if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

link_directories(${Slicer_INSTALL_QTLOADABLEMODULES_LIB_DIR})

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  #LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  ADDITIONAL_SRCS
    SkelGraph.h
    SkelGraph.cxx
    tilg_iso_3D.h
    tilg_iso_3D.cxx
    coordTypes.h
    misc.h
    misc.cxx
    
    TARGET_LIBRARIES
    ${VTK_LIBRARIES}
    ${ITK_LIBRARIES}
    MRMLCore
    vtkSlicerMarkupsModuleMRML
    ITKFactoryRegistration
    
    INCLUDE_DIRECTORIES
    ${Slicer_Libs_INCLUDE_DIRS}
    ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/vtkSlicerMarkupsModuleMRML

    INSTALL_RUNTIME_DESTINATION ${Slicer_INSTALL_CLIMODULES_BIN_DIR}
    INSTALL_LIBRARY_DESTINATION ${Slicer_INSTALL_CLIMODULES_LIB_DIR}
    INSTALL_ARCHIVE_DESTINATION ${Slicer_INSTALL_CLIMODULES_SHARE_DIR}
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
