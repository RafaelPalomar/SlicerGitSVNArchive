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
 * @class   vtkSlicerBezierSurfaceRepresentation3D
 * @brief   Default representation for the curve widget
 *
  * This class provides the default concrete representation for the
 * vtkMRMLAbstractWidget. See vtkMRMLAbstractWidget
 * for details.
 * @sa
 * vtkSlicerMarkupsWidgetRepresentation3D vtkMRMLAbstractWidget

*/

#ifndef vtkSlicerBezierSurfaceRepresentation3D_h
#define vtkSlicerBezierSurfaceRepresentation3D_h

#include "vtkSlicerMarkupsModuleVTKWidgetsExport.h"
#include "vtkSlicerMarkupsWidgetRepresentation3D.h"

class vtkActor;
class vtkCellLocator;
class vtkPolyDataMapper;
class vtkPolyData;
class vtkTubeFilter;
class vtkBezierSurfaceSource;

class vtkMRMLInteractionEventData;

class VTK_SLICER_MARKUPS_MODULE_VTKWIDGETS_EXPORT vtkSlicerBezierSurfaceRepresentation3D : public vtkSlicerMarkupsWidgetRepresentation3D
{
public:
  /// Instantiate this class.
  static vtkSlicerBezierSurfaceRepresentation3D *New();

  /// Standard methods for instances of this class.
  vtkTypeMacro(vtkSlicerBezierSurfaceRepresentation3D,vtkSlicerMarkupsWidgetRepresentation3D);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /// Subclasses of vtkMRMLAbstractWidgetRepresentation must implement these methods. These
  /// are the methods that the widget and its representation use to
  /// communicate with each other.
  void UpdateFromMRML(vtkMRMLNode* caller, unsigned long event, void *callData = nullptr) override;

  /// Methods to make this class behave as a vtkProp.
  void GetActors(vtkPropCollection *) override;
  void ReleaseGraphicsResources(vtkWindow *) override;
  int RenderOverlay(vtkViewport *viewport) override;
  int RenderOpaqueGeometry(vtkViewport *viewport) override;
  int RenderTranslucentPolygonalGeometry(vtkViewport *viewport) override;
  vtkTypeBool HasTranslucentPolygonalGeometry() override;

  /// Return the bounds of the representation
  double *GetBounds() override;

  void CanInteract(vtkMRMLInteractionEventData* interactionEventData,
    int &foundComponentType, int &foundComponentIndex, double &closestDistance2) override;

  void CanInteractWithBezierSurface(vtkMRMLInteractionEventData* interactionEventData,
    int &foundComponentType, int &componentIndex, double &closestDistance2);

  // This overrides the BuildLine from the parent class, since the topology
  // is different
  void BuildControlPolygon(vtkPolyData* linePolyData, bool displayPosition);
  
protected:
  vtkSlicerBezierSurfaceRepresentation3D();
  ~vtkSlicerBezierSurfaceRepresentation3D() override;

  void SetMarkupsNode(vtkMRMLMarkupsNode *markupsNode) override;

  vtkSmartPointer<vtkBezierSurfaceSource> BezierSurfaceSource;
  vtkSmartPointer<vtkPolyData> ControlPolygon;
  vtkSmartPointer<vtkPolyDataMapper> ControlPolygonMapper;
  vtkSmartPointer<vtkPolyDataMapper> BezierSurfaceMapper;
  vtkSmartPointer<vtkActor> ControlPolygonActor;
  vtkSmartPointer<vtkActor> BezierSurfaceActor;

  vtkSmartPointer<vtkTubeFilter> TubeFilter;

  vtkSmartPointer<vtkCellLocator> BezierSurfacePointLocator;

private:
  vtkSlicerBezierSurfaceRepresentation3D(const vtkSlicerBezierSurfaceRepresentation3D&) = delete;
  void operator=(const vtkSlicerBezierSurfaceRepresentation3D&) = delete;
};

#endif
