project(vtkSlicer${MODULE_NAME}ModuleMRML)

find_package(RapidJSON REQUIRED)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_MRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${RapidJSON_INCLUDE_DIR}
  ${Slicer_Base_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  vtkMRML${MODULE_NAME}DisplayNode.cxx
  vtkMRML${MODULE_NAME}FiducialDisplayNode.cxx
  vtkMRML${MODULE_NAME}FiducialNode.cxx
  vtkMRML${MODULE_NAME}LineNode.cxx
  vtkMRML${MODULE_NAME}AngleNode.cxx
  vtkMRML${MODULE_NAME}CurveNode.cxx
  vtkMRML${MODULE_NAME}ClosedCurveNode.cxx
  vtkMRML${MODULE_NAME}PlaneNode.cxx
  vtkMRML${MODULE_NAME}Node.cxx
  vtkMRML${MODULE_NAME}FiducialStorageNode.cxx
  vtkMRML${MODULE_NAME}JsonStorageNode.cxx
  vtkCurveGenerator.cxx
  vtkCurveGenerator.h
  vtkLinearSpline.cxx
  vtkLinearSpline.h
  vtkParametricPolynomialApproximation.cxx
  vtkParametricPolynomialApproximation.h
  vtkSlicerDijkstraGraphGeodesicPath.cxx
  vtkSlicerDijkstraGraphGeodesicPath.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${MRML_LIBRARIES}
  ${VTK_LIBRARIES}
  ${ITK_LIBRARIES}
  vtkAddon
  )

link_directories(${Slicer_HOME}/${Slicer_INSTALL_LIB_DIR})

if(NOT Slicer_USE_PYTHONQT)
  set(DISABLE_PYTHON DISABLE_WRAP_PYTHON)
endif()


#-----------------------------------------------------------------------------
SlicerMacroBuildModuleMRML(
  ${DISABLE_PYTHON}
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
