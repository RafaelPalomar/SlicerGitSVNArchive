/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Oslo University Hospital

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// VTK includes
#include "vtkActor2D.h"
#include "vtkCellLocator.h"
#include "vtkCleanPolyData.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkPointData.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkSlicerBezierSurfaceRepresentation3D.h"
#include "vtkTubeFilter.h"
#include "vtkCellArray.h"

// MRML includes
#include "vtkMRMLInteractionEventData.h"
#include "vtkMRMLMarkupsDisplayNode.h"

vtkStandardNewMacro(vtkSlicerBezierSurfaceRepresentation3D);

//----------------------------------------------------------------------
vtkSlicerBezierSurfaceRepresentation3D::vtkSlicerBezierSurfaceRepresentation3D()
{
  this->ControlPolygon = vtkSmartPointer<vtkPolyData>::New();
  this->BezierSurface = vtkSmartPointer<vtkPolyData>::New();

  this->TubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
  this->TubeFilter->SetInputData(this->ControlPolygon);
  this->TubeFilter->SetNumberOfSides(20);
  this->TubeFilter->SetRadius(1);

  this->ControlPolygonMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  //  this->ControlPolygonMapper->SetInputConnection(this->TubeFilter->GetOutputPort());
  this->ControlPolygonMapper->SetInputData(this->ControlPolygon);
  this->BezierSurfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

  this->ControlPolygonActor = vtkSmartPointer<vtkActor>::New();
  this->ControlPolygonActor->SetMapper(this->ControlPolygonMapper);
  this->ControlPolygonActor->SetProperty(this->GetControlPointsPipeline(Unselected)->Property);
  this->BezierSurfaceActor = vtkSmartPointer<vtkActor>::New();
  this->BezierSurfaceActor->SetMapper(this->BezierSurfaceMapper);  

  this->BezierSurfacePointLocator = vtkSmartPointer<vtkCellLocator>::New();
}

//----------------------------------------------------------------------
vtkSlicerBezierSurfaceRepresentation3D::~vtkSlicerBezierSurfaceRepresentation3D()
= default;

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::UpdateFromMRML(vtkMRMLNode* caller, unsigned long event, void *callData /*=nullptr*/)
{
  Superclass::UpdateFromMRML(caller, event, callData);

  this->NeedToRenderOn();

  vtkMRMLMarkupsNode* markupsNode = this->GetMarkupsNode();
  if (!markupsNode || !this->MarkupsDisplayNode
    || !this->MarkupsDisplayNode->GetVisibility()
    || !this->MarkupsDisplayNode->IsDisplayableInView(this->ViewNode->GetID()))
    {
    this->VisibilityOff();
    return;
    }

  this->VisibilityOn();

  this->BuildControlPolygon(this->ControlPolygon, false);

}

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::GetActors(vtkPropCollection *pc)
{
  this->Superclass::GetActors(pc);
  this->ControlPolygonActor->GetActors(pc);
}

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::ReleaseGraphicsResources(
  vtkWindow *win)
{
  this->Superclass::ReleaseGraphicsResources(win);
  this->ControlPolygonActor->ReleaseGraphicsResources(win);
}

//----------------------------------------------------------------------
int vtkSlicerBezierSurfaceRepresentation3D::RenderOverlay(vtkViewport *viewport)
{
  int count=0;
  count = this->Superclass::RenderOverlay(viewport);
  if (this->ControlPolygonActor->GetVisibility())
    {
    count +=  this->ControlPolygonActor->RenderOverlay(viewport);
    }
  return count;
}

//-----------------------------------------------------------------------------
int vtkSlicerBezierSurfaceRepresentation3D::RenderOpaqueGeometry(
  vtkViewport *viewport)
{
  int count=0;
  count = this->Superclass::RenderOpaqueGeometry(viewport);
  if (this->ControlPolygonActor->GetVisibility())
    {
    this->TubeFilter->SetRadius(this->ControlPointSize * this->MarkupsDisplayNode->GetLineThickness() * 0.5);
    count += this->ControlPolygonActor->RenderOpaqueGeometry(viewport);
    }
  return count;
}

//-----------------------------------------------------------------------------
int vtkSlicerBezierSurfaceRepresentation3D::RenderTranslucentPolygonalGeometry(
  vtkViewport *viewport)
{
  int count=0;
  count = this->Superclass::RenderTranslucentPolygonalGeometry(viewport);
  if (this->ControlPolygonActor->GetVisibility())
    {
    count += this->ControlPolygonActor->RenderTranslucentPolygonalGeometry(viewport);
    }
  return count;
}

//-----------------------------------------------------------------------------
vtkTypeBool vtkSlicerBezierSurfaceRepresentation3D::HasTranslucentPolygonalGeometry()
{
  if (this->Superclass::HasTranslucentPolygonalGeometry())
    {
    return true;
    }
  if (this->ControlPolygonActor->GetVisibility() && this->ControlPolygonActor->HasTranslucentPolygonalGeometry())
    {
    return true;
    }
  return false;
}

//----------------------------------------------------------------------
double *vtkSlicerBezierSurfaceRepresentation3D::GetBounds()
{
  vtkBoundingBox boundingBox;
  const std::vector<vtkProp*> actors({ this->ControlPolygonActor });
  this->AddActorsBounds(boundingBox, actors, Superclass::GetBounds());
  boundingBox.GetBounds(this->Bounds);
  return this->Bounds;
}

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::CanInteract(
  vtkMRMLInteractionEventData* interactionEventData,
  int &foundComponentType, int &foundComponentIndex, double &closestDistance2)
{
  foundComponentType = vtkMRMLMarkupsDisplayNode::ComponentNone;
  vtkMRMLMarkupsNode* markupsNode = this->GetMarkupsNode();
  if ( !markupsNode || markupsNode->GetLocked() || markupsNode->GetNumberOfControlPoints() < 1
    || !interactionEventData )
    {
    return;
    }
  Superclass::CanInteract(interactionEventData, foundComponentType, foundComponentIndex, closestDistance2);
  if (foundComponentType != vtkMRMLMarkupsDisplayNode::ComponentNone)
    {
    return;
    }

  this->CanInteractWithBezierSurface(interactionEventData, foundComponentType, foundComponentIndex, closestDistance2);
}

//-----------------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::PrintSelf(ostream& os, vtkIndent indent)
{
  //Superclass typedef defined in vtkTypeMacro() found in vtkSetGet.h
  this->Superclass::PrintSelf(os, indent);

  if (this->ControlPolygonActor)
    {
    os << indent << "ControlPolygon Visibility: " << this->ControlPolygonActor->GetVisibility() << "\n";
    }
  else
    {
    os << indent << "ControlPolygon Visibility: (none)\n";
    }
}

//-----------------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::SetMarkupsNode(vtkMRMLMarkupsNode *markupsNode)
{
  if (this->MarkupsNode != markupsNode)
  {
    if (markupsNode)
      {
      vtkNew<vtkCleanPolyData> cleaner;
      cleaner->PointMergingOn();
      cleaner->SetInputConnection(markupsNode->GetCurveWorldConnection());
      this->TubeFilter->SetInputConnection(cleaner->GetOutputPort());
      }
    else
      {
      this->TubeFilter->SetInputData(this->ControlPolygon);
      }
  }
  this->Superclass::SetMarkupsNode(markupsNode);
ppp}

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::CanInteractWithBezierSurface(
  vtkMRMLInteractionEventData* interactionEventData,
  int &foundComponentType, int &componentIndex, double &closestDistance2)
{
  if (!this->MarkupsNode || this->MarkupsNode->GetLocked()
    || this->MarkupsNode->GetNumberOfControlPoints() < 16
    || !this->GetVisibility() || !interactionEventData)
    {
    return;
    }

  vtkPolyData* curveWorld = this->MarkupsNode->GetCurveWorld();
  if (!curveWorld || curveWorld->GetNumberOfCells()<1)
    {
    return;
    }

  this->BezierSurfacePointLocator->SetDataSet(curveWorld);
  this->BezierSurfacePointLocator->Update();

  double closestPointDisplay[3] = { 0.0 };
  vtkIdType cellId = -1;
  int subId = -1;
  double dist2 = VTK_DOUBLE_MAX;
  if (interactionEventData->IsWorldPositionValid())
    {
    const double* worldPosition = interactionEventData->GetWorldPosition();
    this->BezierSurfacePointLocator->FindClosestPoint(worldPosition, closestPointDisplay, cellId, subId, dist2);
    }

  if (dist2 < this->ControlPointSize + this->PickingTolerance * this->ScreenScaleFactor * this->ViewScaleFactorMmPerPixel)
    {
    closestDistance2 = dist2 / this->ViewScaleFactorMmPerPixel / this->ViewScaleFactorMmPerPixel;
    foundComponentType = vtkMRMLMarkupsDisplayNode::ComponentLine;
    componentIndex = this->MarkupsNode->GetControlPointIndexFromInterpolatedPointIndex(subId);
    }
}

//----------------------------------------------------------------------
void vtkSlicerBezierSurfaceRepresentation3D::BuildControlPolygon(vtkPolyData* controlPolygonPolyData, bool displayPosition)
{
  vtkNew<vtkPoints> points;
  vtkNew<vtkCellArray> controlPolygon;

  vtkMRMLMarkupsNode* markupsNode = this->GetMarkupsNode();
  if (!markupsNode)
    {
    controlPolygonPolyData->SetPoints(points);
    controlPolygonPolyData->SetLines(controlPolygon);
    return;
    }
  int numberOfControlPoints = markupsNode->GetNumberOfControlPoints();
  vtkIdType numberOfLines = 24;

  //TODO: make this more elegant
  if (numberOfControlPoints < 6)
    numberOfLines = numberOfControlPoints -1;
  else if (numberOfControlPoints > 5 and numberOfControlPoints < 9)
    numberOfLines = 4 + 2 * (numberOfControlPoints - 5);
  else if (numberOfControlPoints == 9)
    numberOfLines = 11;
  else if (numberOfControlPoints > 9 and numberOfControlPoints < 13)
    numberOfLines = 11 + 2 * (numberOfControlPoints - 9);
  else if (numberOfControlPoints == 13)
    numberOfLines = 18;
  else
    numberOfLines = 18 + 2 * (numberOfControlPoints - 13);
      
  if (numberOfLines <= 0)
    {
    return;
    }

  double pos[3] = { 0.0 };
  vtkIdType line[2] = {0,0};
  for (int i = 0; i < numberOfControlPoints; i++)
    {
    // Add the node
    if (displayPosition)
      {
      this->GetNthControlPointDisplayPosition(i, pos);
      }
    else
      {
      markupsNode->GetNthControlPointPositionWorld(i, pos);
      }
    points->InsertNextPoint(pos);

    // TODO: make this more elegant
    switch(i)
      {
      case 4:
      case 8:
      case 12:
	line[0] = i;
	line[1] = i-4;
	controlPolygon->InsertNextCell(2, line);
	break;
      case 5:
      case 6:
      case 7:
      case 9:
      case 10:
      case 11:
      case 13:
      case 14:
      case 15:
	line[0] = i -4;
	line[1] = i;
	controlPolygon->InsertNextCell(2, line);
      case 1:
      case 2:
      case 3:
	line[0] = i -1;
	line[1] = i;
	controlPolygon->InsertNextCell(2, line);
	break;	
      }
    
    }    

  controlPolygonPolyData->SetPoints(points);
  controlPolygonPolyData->SetLines(controlPolygon);
}

