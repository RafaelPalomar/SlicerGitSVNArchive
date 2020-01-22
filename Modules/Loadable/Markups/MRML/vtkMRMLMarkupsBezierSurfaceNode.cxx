/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Oslo University Hospital

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// MRML includes
#include "vtkMRMLMarkupsDisplayNode.h"
#include "vtkMRMLMarkupsBezierSurfaceNode.h"
#include "vtkMRMLMarkupsFiducialStorageNode.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLUnitNode.h"

// VTK includes
#include <vtkNew.h>
#include <vtkObjectFactory.h>

// STD includes
#include <sstream>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLMarkupsBezierSurfaceNode);


//----------------------------------------------------------------------------
vtkMRMLMarkupsBezierSurfaceNode::vtkMRMLMarkupsBezierSurfaceNode()
{
  this->MaximumNumberOfControlPoints = 2;
  this->RequiredNumberOfControlPoints = 2;
}

//----------------------------------------------------------------------------
vtkMRMLMarkupsBezierSurfaceNode::~vtkMRMLMarkupsBezierSurfaceNode()
= default;

//----------------------------------------------------------------------------
void vtkMRMLMarkupsBezierSurfaceNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of,nIndent);
}

//----------------------------------------------------------------------------
void vtkMRMLMarkupsBezierSurfaceNode::ReadXMLAttributes(const char** atts)
{
  Superclass::ReadXMLAttributes(atts);
}

//----------------------------------------------------------------------------
void vtkMRMLMarkupsBezierSurfaceNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
}

//----------------------------------------------------------------------------
void vtkMRMLMarkupsBezierSurfaceNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);
}

//---------------------------------------------------------------------------
void vtkMRMLMarkupsBezierSurfaceNode::UpdateMeasurements()
{
  this->RemoveAllMeasurements();
  if (this->GetNumberOfDefinedControlPoints() == 2)
    {
    double p1[3] = { 0.0 };
    double p2[3] = { 0.0 };
    this->GetNthControlPointPositionWorld(0, p1);
    this->GetNthControlPointPositionWorld(1, p2);
    double length = sqrt(vtkMath::Distance2BetweenPoints(p1, p2));
    std::string printFormat;
    std::string unit = "mm";
    vtkMRMLUnitNode* unitNode = GetUnitNode("length");
    if (unitNode)
      {
      if (unitNode->GetSuffix())
        {
        unit = unitNode->GetSuffix();
        }
      length = unitNode->GetDisplayValueFromValue(length);
      printFormat = unitNode->GetDisplayStringFormat();
      }
    this->SetNthMeasurement(0, "length", length, unit, printFormat);
    }
  this->WriteMeasurementsToDescription();
}
