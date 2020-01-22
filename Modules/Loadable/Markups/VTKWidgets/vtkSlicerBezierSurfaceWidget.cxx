#include "vtkSlicerBezierSurfaceWidget.h"

#include "vtkMRMLSliceNode.h"
#include "vtkSlicerBezierSurfaceRepresentation2D.h"
#include "vtkSlicerBezierSurfaceRepresentation3D.h"
#include "vtkCommand.h"
#include "vtkEvent.h"

vtkStandardNewMacro(vtkSlicerBezierSurfaceWidget);

//----------------------------------------------------------------------
vtkSlicerBezierSurfaceWidget::vtkSlicerBezierSurfaceWidget()
{
  this->SetEventTranslationClickAndDrag(WidgetStateOnWidget, vtkCommand::LeftButtonPressEvent, vtkEvent::AltModifier,
    WidgetStateRotate, WidgetEventRotateStart, WidgetEventRotateEnd);
  this->SetEventTranslationClickAndDrag(WidgetStateOnWidget, vtkCommand::RightButtonPressEvent, vtkEvent::AltModifier,
    WidgetStateScale, WidgetEventScaleStart, WidgetEventScaleEnd);

  this->SetEventTranslation(WidgetStateOnWidget, vtkCommand::LeftButtonPressEvent, vtkEvent::ControlModifier, WidgetEventControlPointInsert);
}

//----------------------------------------------------------------------
vtkSlicerBezierSurfaceWidget::~vtkSlicerBezierSurfaceWidget()
= default;

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceWidget::CreateDefaultRepresentation(
  vtkMRMLMarkupsDisplayNode* markupsDisplayNode, vtkMRMLAbstractViewNode* viewNode, vtkRenderer* renderer)
{
  vtkSmartPointer<vtkSlicerMarkupsWidgetRepresentation> rep = nullptr;
  if (vtkMRMLSliceNode::SafeDownCast(viewNode))
    {
    rep = vtkSmartPointer<vtkSlicerBezierSurfaceRepresentation2D>::New();
    }
  else
    {
    rep = vtkSmartPointer<vtkSlicerBezierSurfaceRepresentation3D>::New();
    }
  this->SetRenderer(renderer);
  this->SetRepresentation(rep);
  rep->SetViewNode(viewNode);
  rep->SetMarkupsDisplayNode(markupsDisplayNode);
  rep->UpdateFromMRML(nullptr, 0); // full update
}
