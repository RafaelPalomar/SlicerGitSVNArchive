project(vtkSlicer${MODULE_NAME}ModuleLogic)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_LOGIC_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/vtkSlicerMarkupsModuleMRML
  ${vtkSlicerMarkupsModuleMRML_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  vtkSlicerTransformLogic.cxx
  vtkSlicerTransformLogic.h
  )

set(${KIT}_TARGET_LIBRARIES
  MRMLCore
  MRMLLogic
  SlicerBaseLogic
  ${VTK_LIBRARIES}
  ${ITK_LIBRARIES}
  vtkAddon
  vtkSlicerMarkupsModuleMRML
  )

link_directories(
  ${Slicer_HOME}/${Slicer_INSTALL_LIB_DIR}
  ${Slicer_INSTALL_QTLOADABLEMODULES_LIB_DIR}
)

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleLogic(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )

if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
