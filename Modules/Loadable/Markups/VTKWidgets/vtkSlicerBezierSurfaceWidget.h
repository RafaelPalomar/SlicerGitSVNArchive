/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Oslo University Hospital

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef vtkSlicerBezierSurfaceWidget_h
#define vtkSlicerBezierSurfaceWidget_h

#include "vtkSlicerMarkupsModuleVTKWidgetsExport.h"
#include "vtkSlicerMarkupsWidget.h"

class vtkPolyData;
class vtkIdList;

class VTK_SLICER_MARKUPS_MODULE_VTKWIDGETS_EXPORT vtkSlicerBezierSurfaceWidget : public vtkSlicerMarkupsWidget
{
public:
  /// Instantiate this class.
  static vtkSlicerBezierSurfaceWidget *New();

  /// Standard methods for a VTK class.
  vtkTypeMacro(vtkSlicerBezierSurfaceWidget, vtkSlicerMarkupsWidget);

  /// Create the default widget representation and initializes the widget and representation.
  void CreateDefaultRepresentation(vtkMRMLMarkupsDisplayNode* markupsDisplayNode, vtkMRMLAbstractViewNode* viewNode, vtkRenderer* renderer) override;

protected:
  vtkSlicerBezierSurfaceWidget();
  ~vtkSlicerBezierSurfaceWidget() override;

private:
  vtkSlicerBezierSurfaceWidget(const vtkSlicerBezierSurfaceWidget&) = delete;
  void operator=(const vtkSlicerBezierSurfaceWidget&) = delete;
};

#endif
