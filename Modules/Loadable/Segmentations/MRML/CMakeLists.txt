project(vtkSlicer${MODULE_NAME}ModuleMRML)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_MRML_EXPORT")

include_directories(BEFORE ${vtkTeem_INCLUDE_DIRS})

set(${KIT}_INCLUDE_DIRECTORIES
  ${vtkSegmentationCore_INCLUDE_DIRS}
  ${MRMLCore_INCLUDE_DIRS}
  ${vtkSlicerSubjectHierarchyModuleLogic_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  vtkMRMLSegmentEditorNode.cxx
  vtkMRMLSegmentEditorNode.h
  )

set(${KIT}_TARGET_LIBRARIES
  MRMLCore
  SlicerBaseLogic
  vtkSegmentationCore
  vtkSlicerSubjectHierarchyModuleLogic
  ${VTK_LIBRARIES}
  )

link_directories(
  ${Slicer_HOME}/${Slicer_INSTALL_LIB_DIR}
  ${Slicer_INSTALL_QTLOADABLEMODULES_LIB_DIR}
  )

if(NOT Slicer_USE_PYTHONQT)
  set(DISABLE_PYTHON DISABLE_WRAP_PYTHON)
endif()

# --------------------------------------------------------------------------
SlicerMacroBuildModuleMRML(
  ${DISABLE_PYTHON}
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
