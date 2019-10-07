project(qSlicer${MODULE_NAME}SubjectHierarchyPlugins)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "Q_SLICER_${MODULE_NAME_UPPER}_SUBJECT_HIERARCHY_PLUGINS_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/qSlicerSubjectHierarchyModuleWidgets
  ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/vtkSlicerSubjectHierarchyModuleLogic
  ${Slicer_Libs_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/qSlicerTerminologiesModuleWidgets
  ${Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR}/vtkSlicerTerminologiesModuleLogic
  ${VTK_INCLUDE_DIRS}
  ${Slicer_Base_INCLUDE_DIRS}
  ${vtkSlicer${MODULE_NAME}ModuleMRML_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  qSlicerSubjectHierarchyMarkupsPlugin.cxx
  qSlicerSubjectHierarchyMarkupsPlugin.h
  )

set(${KIT}_MOC_SRCS
  qSlicerSubjectHierarchyMarkupsPlugin.h
  )

set(${KIT}_UI_SRCS
  )

set(${KIT}_RESOURCES
  Resources/${KIT}.qrc
  )

#-----------------------------------------------------------------------------
set(${KIT}_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleMRML
  qSlicerSubjectHierarchyModuleWidgets
  vtkSlicerSubjectHierarchyModuleLogic
  qSlicerTerminologiesModuleWidgets
  qMRMLWidgets
  MRMLLogic
  MRMLCore
  vtkSegmentationCore
  Qt5::Widgets
  ${VTK_LIBRARIES}
  ${CTK_LIBRARIES})

link_directories(
  ${Slicer_HOME}/${Slicer_INSTALL_LIB_DIR}
  ${Slicer_INSTALL_QTLOADABLEMODULES_LIB_DIR}
  ${Slicer_Libs_LIBRARY_DIRS}
  )

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleQtLibrary(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  FOLDER "Module-${MODULE_NAME}"
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  MOC_SRCS ${${KIT}_MOC_SRCS}
  UI_SRCS ${${KIT}_UI_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  RESOURCES ${${KIT}_RESOURCES}
  WRAP_PYTHONQT
  )
