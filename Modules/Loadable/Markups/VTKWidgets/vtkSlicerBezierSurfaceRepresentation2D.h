/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Oslo University Hospital

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

/**
 * @class   vtkSlicerBezierSurfaceRepresentation2D
 * @brief   Default representation for the line widget
 *
 * This class provides the default concrete representation for the
 * vtkMRMLAbstractWidget. See vtkMRMLAbstractWidget
 * for details.
 * @sa
 * vtkSlicerMarkupsWidgetRepresentation2D vtkMRMLAbstractWidget
*/

#ifndef vtkSlicerBezierSurfaceRepresentation2D_h
#define vtkSlicerBezierSurfaceRepresentation2D_h

#include "vtkSlicerMarkupsModuleVTKWidgetsExport.h"
#include "vtkSlicerMarkupsWidgetRepresentation2D.h"

class vtkCellLocator;
class vtkDiscretizableColorTransferFunction;
class vtkSampleImplicitFunctionFilter;
class vtkTubeFilter;

class vtkMRMLInteractionEventData;

class VTK_SLICER_MARKUPS_MODULE_VTKWIDGETS_EXPORT vtkSlicerBezierSurfaceRepresentation2D : public vtkSlicerMarkupsWidgetRepresentation2D
{
public:
  /// Instantiate this class.
  static vtkSlicerBezierSurfaceRepresentation2D *New();

  /// Standard methods for instances of this class.
  vtkTypeMacro(vtkSlicerBezierSurfaceRepresentation2D,vtkSlicerMarkupsWidgetRepresentation2D);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /// Subclasses of vtkContourBezierSurfaceRepresentation must implement these methods. These
  /// are the methods that the widget and its representation use to
  /// communicate with each other.
  void UpdateFromMRML(vtkMRMLNode* caller, unsigned long event, void *callData = nullptr) override;
  void CanInteract(vtkMRMLInteractionEventData* interactionEventData,
    int &foundComponentType, int &foundComponentIndex, double &closestDistance2) override;

  /// Methods to make this class behave as a vtkProp.
  void GetActors(vtkPropCollection *) override;
  void ReleaseGraphicsResources(vtkWindow *) override;
  int RenderOverlay(vtkViewport *viewport) override;
  int RenderOpaqueGeometry(vtkViewport *viewport) override;
  int RenderTranslucentPolygonalGeometry(vtkViewport *viewport) override;
  vtkTypeBool HasTranslucentPolygonalGeometry() override;

  /// Return the bounds of the representation
  double *GetBounds() override;

  void CanInteractWithBezierSurface(vtkMRMLInteractionEventData* interactionEventData,
    int &foundComponentType, int &componentIndex, double &closestDistance2);

protected:
  vtkSlicerBezierSurfaceRepresentation2D();
  ~vtkSlicerBezierSurfaceRepresentation2D() override;

  void SetMarkupsNode(vtkMRMLMarkupsNode *markupsNode) override;

  void UpdateLineColorMap();

  vtkSmartPointer<vtkPolyData> Line;
  vtkSmartPointer<vtkPolyDataMapper2D> LineMapper;
  vtkSmartPointer<vtkActor2D> LineActor;
  vtkSmartPointer<vtkDiscretizableColorTransferFunction> LineColorMap;

  vtkSmartPointer<vtkTubeFilter> TubeFilter;

  vtkSmartPointer<vtkTransformPolyDataFilter> WorldToSliceTransformer;
  vtkSmartPointer<vtkCellLocator> SliceBezierSurfacePointLocator;

  vtkSmartPointer<vtkSampleImplicitFunctionFilter> SliceDistance;

private:
  vtkSlicerBezierSurfaceRepresentation2D(const vtkSlicerBezierSurfaceRepresentation2D&) = delete;
  void operator=(const vtkSlicerBezierSurfaceRepresentation2D&) = delete;
};

#endif
