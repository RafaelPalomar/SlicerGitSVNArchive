/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Oslo University Hospital

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __vtkMRMLMarkupsBezierSurfaceNode_h
#define __vtkMRMLMarkupsBezierSurfaceNode_h

// MRML includes
#include "vtkMRMLDisplayableNode.h"

// Markups includes
#include "vtkSlicerMarkupsModuleMRMLExport.h"
#include "vtkMRMLMarkupsDisplayNode.h"
#include "vtkMRMLMarkupsNode.h"

/// \brief MRML node to represent a line markup
/// BezierSurface Markups nodes contain two control points.
/// Visualization parameters are set in the vtkMRMLMarkupsDisplayNode class.
///
/// Markups is intended to be used for manual marking/editing of point positions.
///
/// \ingroup Slicer_QtModules_Markups
class  VTK_SLICER_MARKUPS_MODULE_MRML_EXPORT vtkMRMLMarkupsBezierSurfaceNode : public vtkMRMLMarkupsNode
{
public:
  static vtkMRMLMarkupsBezierSurfaceNode *New();
  vtkTypeMacro(vtkMRMLMarkupsBezierSurfaceNode,vtkMRMLMarkupsNode);
  /// Print out the node information to the output stream
  void PrintSelf(ostream& os, vtkIndent indent) override;

  const char* GetIcon() override {return ":/Icons/MarkupsLineMouseModePlace.png";}

  //--------------------------------------------------------------------------
  // MRMLNode methods
  //--------------------------------------------------------------------------

  vtkMRMLNode* CreateNodeInstance() override;
  /// Get node XML tag name (like Volume, Model)
  const char* GetNodeTagName() override {return "MarkupsBezierSurface";}

  /// Read node attributes from XML file
  void ReadXMLAttributes( const char** atts) override;

  /// Write this node's information to a MRML file in XML format.
  void WriteXML(ostream& of, int indent) override;

  /// Copy the node's attributes to this object
  void Copy(vtkMRMLNode *node) override;

protected:
  vtkMRMLMarkupsBezierSurfaceNode();
  ~vtkMRMLMarkupsBezierSurfaceNode() override;
  vtkMRMLMarkupsBezierSurfaceNode(const vtkMRMLMarkupsBezierSurfaceNode&);
  void operator=(const vtkMRMLMarkupsBezierSurfaceNode&);

  void UpdateMeasurements() override;
};

#endif
