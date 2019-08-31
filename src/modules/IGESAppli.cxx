/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC
Copyright (C) 2019 Trevor Laughlin and the pyOCCT contributors

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <pyOCCT_Common.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <IGESAppli_Protocol.hxx>
#include <IGESAppli_Node.hxx>
#include <IGESAppli_FiniteElement.hxx>
#include <IGESAppli_NodalDisplAndRot.hxx>
#include <IGESAppli_NodalResults.hxx>
#include <IGESAppli_ElementResults.hxx>
#include <IGESAppli_Flow.hxx>
#include <IGESAppli_PipingFlow.hxx>
#include <IGESAppli_RegionRestriction.hxx>
#include <IGESAppli_LevelFunction.hxx>
#include <IGESAppli_LineWidening.hxx>
#include <IGESAppli_DrilledHole.hxx>
#include <IGESAppli_ReferenceDesignator.hxx>
#include <IGESAppli_PinNumber.hxx>
#include <IGESAppli_PartNumber.hxx>
#include <IGESAppli_FlowLineSpec.hxx>
#include <IGESAppli_LevelToPWBLayerMap.hxx>
#include <IGESAppli_PWBArtworkStackup.hxx>
#include <IGESAppli_PWBDrilledHole.hxx>
#include <IGESAppli_NodalConstraint.hxx>
#include <IGESAppli_ToolNode.hxx>
#include <IGESAppli_ToolFiniteElement.hxx>
#include <IGESAppli_ToolNodalDisplAndRot.hxx>
#include <IGESAppli_ToolNodalResults.hxx>
#include <IGESAppli_ToolElementResults.hxx>
#include <IGESAppli_ToolFlow.hxx>
#include <IGESAppli_ToolPipingFlow.hxx>
#include <IGESAppli_ToolRegionRestriction.hxx>
#include <IGESAppli_ToolLevelFunction.hxx>
#include <IGESAppli_ToolLineWidening.hxx>
#include <IGESAppli_ToolDrilledHole.hxx>
#include <IGESAppli_ToolReferenceDesignator.hxx>
#include <IGESAppli_ToolPinNumber.hxx>
#include <IGESAppli_ToolPartNumber.hxx>
#include <IGESAppli_ToolFlowLineSpec.hxx>
#include <IGESAppli_ToolLevelToPWBLayerMap.hxx>
#include <IGESAppli_ToolPWBArtworkStackup.hxx>
#include <IGESAppli_ToolPWBDrilledHole.hxx>
#include <IGESAppli_ToolNodalConstraint.hxx>
#include <IGESAppli_ReadWriteModule.hxx>
#include <IGESAppli_GeneralModule.hxx>
#include <IGESAppli_SpecificModule.hxx>
#include <IGESAppli.hxx>
#include <IGESData_IGESEntity.hxx>
#include <gp_XYZ.hxx>
#include <IGESGeom_TransformationMatrix.hxx>
#include <gp_Pnt.hxx>
#include <IGESData_TransfEntity.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Type.hxx>
#include <NCollection_Array1.hxx>
#include <IGESAppli_Array1OfNode.hxx>
#include <Standard_Transient.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <IGESAppli_HArray1OfNode.hxx>
#include <TCollection_HAsciiString.hxx>
#include <IGESAppli_Array1OfFiniteElement.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESDraw_HArray1OfConnectPoint.hxx>
#include <Interface_HArray1OfHAsciiString.hxx>
#include <IGESGraph_HArray1OfTextDisplayTemplate.hxx>
#include <IGESDraw_ConnectPoint.hxx>
#include <IGESGraph_TextDisplayTemplate.hxx>
#include <IGESAppli_Array1OfFlow.hxx>
#include <IGESAppli_HArray1OfFiniteElement.hxx>
#include <IGESDimen_GeneralNote.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESBasic_HArray1OfHArray1OfInteger.hxx>
#include <IGESBasic_HArray1OfHArray1OfReal.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <IGESData_GeneralModule.hxx>
#include <Interface_EntityIterator.hxx>
#include <IGESData_DirChecker.hxx>
#include <Interface_ShareTool.hxx>
#include <Interface_Check.hxx>
#include <Interface_CopyTool.hxx>
#include <IGESAppli_HArray1OfFlow.hxx>
#include <IGESDefs_HArray1OfTabularData.hxx>
#include <IGESDefs_TabularData.hxx>
#include <IGESDimen_HArray1OfGeneralNote.hxx>
#include <IGESBasic_HArray1OfHArray1OfXYZ.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <IGESData_Protocol.hxx>
#include <Interface_Protocol.hxx>
#include <IGESData_ReadWriteModule.hxx>
#include <IGESData_IGESReaderData.hxx>
#include <IGESData_ParamReader.hxx>
#include <IGESData_IGESWriter.hxx>
#include <IGESData_SpecificModule.hxx>
#include <IGESData_IGESDumper.hxx>
#include <Message_Messenger.hxx>
#include <bind_NCollection_Array1.hxx>

PYBIND11_MODULE(IGESAppli, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.IGESData");
py::module::import("OCCT.gp");
py::module::import("OCCT.IGESGeom");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.IGESDraw");
py::module::import("OCCT.Interface");
py::module::import("OCCT.IGESGraph");
py::module::import("OCCT.IGESDimen");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.IGESBasic");
py::module::import("OCCT.IGESDefs");
py::module::import("OCCT.Message");

// CLASS: IGESAPPLI
py::class_<IGESAppli> cls_IGESAppli(mod, "IGESAppli", "This package represents collection of miscellaneous entities from IGES");

// Methods
// cls_IGESAppli.def_static("operator new_", (void * (*)(size_t)) &IGESAppli::operator new, "None", py::arg("theSize"));
// cls_IGESAppli.def_static("operator delete_", (void (*)(void *)) &IGESAppli::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli.def_static("Init_", (void (*)()) &IGESAppli::Init, "Prepares dynamic data (Protocol, Modules) for this package");
cls_IGESAppli.def_static("Protocol_", (opencascade::handle<IGESAppli_Protocol> (*)()) &IGESAppli::Protocol, "Returns the Protocol for this Package");

// CLASS: IGESAPPLI_NODE
py::class_<IGESAppli_Node, opencascade::handle<IGESAppli_Node>, IGESData_IGESEntity> cls_IGESAppli_Node(mod, "IGESAppli_Node", "defines Node, Type <134> Form <0> in package IGESAppli Geometric point used in the definition of a finite element.");

// Constructors
cls_IGESAppli_Node.def(py::init<>());

// Methods
cls_IGESAppli_Node.def("Init", (void (IGESAppli_Node::*)(const gp_XYZ &, const opencascade::handle<IGESGeom_TransformationMatrix> &)) &IGESAppli_Node::Init, "This method is used to set the fields of the class Node - aCoord : Nodal Coordinates - aCoordSystem : the Nodal Displacement Coordinate System Entity (default 0 is Global Cartesian Coordinate system)", py::arg("aCoord"), py::arg("aCoordSystem"));
cls_IGESAppli_Node.def("Coord", (gp_Pnt (IGESAppli_Node::*)() const) &IGESAppli_Node::Coord, "returns the nodal coordinates");
cls_IGESAppli_Node.def("System", (opencascade::handle<IGESData_TransfEntity> (IGESAppli_Node::*)() const) &IGESAppli_Node::System, "returns TransfEntity if a Nodal Displacement Coordinate System Entity is defined else (for Global Cartesien) returns Null Handle");
cls_IGESAppli_Node.def("SystemType", (Standard_Integer (IGESAppli_Node::*)() const) &IGESAppli_Node::SystemType, "Computes & returns the Type of Coordinate System : 0 GlobalCartesian, 1 Cartesian, 2 Cylindrical, 3 Spherical");
cls_IGESAppli_Node.def("TransformedNodalCoord", (gp_Pnt (IGESAppli_Node::*)() const) &IGESAppli_Node::TransformedNodalCoord, "returns the Nodal coordinates after transformation");
cls_IGESAppli_Node.def_static("get_type_name_", (const char * (*)()) &IGESAppli_Node::get_type_name, "None");
cls_IGESAppli_Node.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_Node::get_type_descriptor, "None");
cls_IGESAppli_Node.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_Node::*)() const) &IGESAppli_Node::DynamicType, "None");

// TYPEDEF: IGESAPPLI_ARRAY1OFNODE
bind_NCollection_Array1<opencascade::handle<IGESAppli_Node> >(mod, "IGESAppli_Array1OfNode", py::module_local(false));

// CLASS: IGESAPPLI_HARRAY1OFNODE
py::class_<IGESAppli_HArray1OfNode, opencascade::handle<IGESAppli_HArray1OfNode>, Standard_Transient> cls_IGESAppli_HArray1OfNode(mod, "IGESAppli_HArray1OfNode", "None", py::multiple_inheritance());

// Constructors
cls_IGESAppli_HArray1OfNode.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESAppli_HArray1OfNode.def(py::init<const Standard_Integer, const Standard_Integer, const IGESAppli_Array1OfNode::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESAppli_HArray1OfNode.def(py::init<const IGESAppli_Array1OfNode &>(), py::arg("theOther"));

// Methods
// cls_IGESAppli_HArray1OfNode.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_HArray1OfNode::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfNode.def_static("operator delete_", (void (*)(void *)) &IGESAppli_HArray1OfNode::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfNode.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_HArray1OfNode::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfNode.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_HArray1OfNode::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfNode.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_HArray1OfNode::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_HArray1OfNode.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_HArray1OfNode::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESAppli_HArray1OfNode.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfNode::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESAppli_HArray1OfNode.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfNode::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESAppli_HArray1OfNode.def("Array1", (const IGESAppli_Array1OfNode & (IGESAppli_HArray1OfNode::*)() const) &IGESAppli_HArray1OfNode::Array1, "None");
cls_IGESAppli_HArray1OfNode.def("ChangeArray1", (IGESAppli_Array1OfNode & (IGESAppli_HArray1OfNode::*)()) &IGESAppli_HArray1OfNode::ChangeArray1, "None");
cls_IGESAppli_HArray1OfNode.def_static("get_type_name_", (const char * (*)()) &IGESAppli_HArray1OfNode::get_type_name, "None");
cls_IGESAppli_HArray1OfNode.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_HArray1OfNode::get_type_descriptor, "None");
cls_IGESAppli_HArray1OfNode.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_HArray1OfNode::*)() const) &IGESAppli_HArray1OfNode::DynamicType, "None");

// CLASS: IGESAPPLI_FINITEELEMENT
py::class_<IGESAppli_FiniteElement, opencascade::handle<IGESAppli_FiniteElement>, IGESData_IGESEntity> cls_IGESAppli_FiniteElement(mod, "IGESAppli_FiniteElement", "defines FiniteElement, Type <136> Form <0> in package IGESAppli Used to define a finite element with the help of an element topology.");

// Constructors
cls_IGESAppli_FiniteElement.def(py::init<>());

// Methods
cls_IGESAppli_FiniteElement.def("Init", (void (IGESAppli_FiniteElement::*)(const Standard_Integer, const opencascade::handle<IGESAppli_HArray1OfNode> &, const opencascade::handle<TCollection_HAsciiString> &)) &IGESAppli_FiniteElement::Init, "This method is used to set the fields of the class FiniteElement - aType : Indicates the topology type - allNodes : List of Nodes defining the element - aName : Element type name", py::arg("aType"), py::arg("allNodes"), py::arg("aName"));
cls_IGESAppli_FiniteElement.def("Topology", (Standard_Integer (IGESAppli_FiniteElement::*)() const) &IGESAppli_FiniteElement::Topology, "returns Topology type");
cls_IGESAppli_FiniteElement.def("NbNodes", (Standard_Integer (IGESAppli_FiniteElement::*)() const) &IGESAppli_FiniteElement::NbNodes, "returns the number of nodes defining the element");
cls_IGESAppli_FiniteElement.def("Node", (opencascade::handle<IGESAppli_Node> (IGESAppli_FiniteElement::*)(const Standard_Integer) const) &IGESAppli_FiniteElement::Node, "returns Node defining element entity raises exception if Index <= 0 or Index > NbNodes()", py::arg("Index"));
cls_IGESAppli_FiniteElement.def("Name", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_FiniteElement::*)() const) &IGESAppli_FiniteElement::Name, "returns Element Type Name");
cls_IGESAppli_FiniteElement.def_static("get_type_name_", (const char * (*)()) &IGESAppli_FiniteElement::get_type_name, "None");
cls_IGESAppli_FiniteElement.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_FiniteElement::get_type_descriptor, "None");
cls_IGESAppli_FiniteElement.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_FiniteElement::*)() const) &IGESAppli_FiniteElement::DynamicType, "None");

// TYPEDEF: IGESAPPLI_ARRAY1OFFINITEELEMENT
bind_NCollection_Array1<opencascade::handle<IGESAppli_FiniteElement> >(mod, "IGESAppli_Array1OfFiniteElement", py::module_local(false));

// CLASS: IGESAPPLI_FLOW
py::class_<IGESAppli_Flow, opencascade::handle<IGESAppli_Flow>, IGESData_IGESEntity> cls_IGESAppli_Flow(mod, "IGESAppli_Flow", "defines Flow, Type <402> Form <18> in package IGESAppli Represents a single signal or a single fluid flow path starting from a starting Connect Point Entity and including additional intermediate connect points.");

// Constructors
cls_IGESAppli_Flow.def(py::init<>());

// Methods
cls_IGESAppli_Flow.def("Init", (void (IGESAppli_Flow::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const opencascade::handle<IGESDraw_HArray1OfConnectPoint> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const opencascade::handle<Interface_HArray1OfHAsciiString> &, const opencascade::handle<IGESGraph_HArray1OfTextDisplayTemplate> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESAppli_Flow::Init, "This method is used to set the fields of the class Flow - nbContextFlags : Count of Context Flags, always = 2 - aFlowType : Type of Flow, default = 0 - aFuncFlag : Function Flag, default = 0 - allFlowAssocs : Flow Associativity Entities - allConnectPoints : Connect Point Entities - allJoins : Join Entities - allFlowNames : Flow Names - allTextDisps : Text Display Template Entities - allContFlowAssocs : Continuation Flow Associativity Entities", py::arg("nbContextFlags"), py::arg("aFlowType"), py::arg("aFuncFlag"), py::arg("allFlowAssocs"), py::arg("allConnectPoints"), py::arg("allJoins"), py::arg("allFlowNames"), py::arg("allTextDisps"), py::arg("allContFlowAssocs"));
cls_IGESAppli_Flow.def("OwnCorrect", (Standard_Boolean (IGESAppli_Flow::*)()) &IGESAppli_Flow::OwnCorrect, "forces NbContextFalgs to 2, returns True if changed");
cls_IGESAppli_Flow.def("NbContextFlags", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbContextFlags, "returns number of Count of Context Flags, always = 2");
cls_IGESAppli_Flow.def("NbFlowAssociativities", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbFlowAssociativities, "returns number of Flow Associativity Entities");
cls_IGESAppli_Flow.def("NbConnectPoints", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbConnectPoints, "returns number of Connect Point Entities");
cls_IGESAppli_Flow.def("NbJoins", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbJoins, "returns number of Join Entities");
cls_IGESAppli_Flow.def("NbFlowNames", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbFlowNames, "returns number of Flow Names");
cls_IGESAppli_Flow.def("NbTextDisplayTemplates", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbTextDisplayTemplates, "returns number of Text Display Template Entities");
cls_IGESAppli_Flow.def("NbContFlowAssociativities", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::NbContFlowAssociativities, "returns number of Continuation Flow Associativity Entities");
cls_IGESAppli_Flow.def("TypeOfFlow", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::TypeOfFlow, "returns Type of Flow = 0 : Not Specified (default) 1 : Logical 2 : Physical");
cls_IGESAppli_Flow.def("FunctionFlag", (Standard_Integer (IGESAppli_Flow::*)() const) &IGESAppli_Flow::FunctionFlag, "returns Function Flag = 0 : Not Specified (default) 1 : Electrical Signal 2 : Fluid Flow Path");
cls_IGESAppli_Flow.def("FlowAssociativity", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::FlowAssociativity, "returns Flow Associativity Entity raises exception if Index <= 0 or Index > NbFlowAssociativities()", py::arg("Index"));
cls_IGESAppli_Flow.def("ConnectPoint", (opencascade::handle<IGESDraw_ConnectPoint> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::ConnectPoint, "returns Connect Point Entity raises exception if Index <= 0 or Index > NbConnectPoints()", py::arg("Index"));
cls_IGESAppli_Flow.def("Join", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::Join, "returns Join Entity raises exception if Index <= 0 or Index > NbJoins()", py::arg("Index"));
cls_IGESAppli_Flow.def("FlowName", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::FlowName, "returns Flow Name raises exception if Index <= 0 or Index > NbFlowNames()", py::arg("Index"));
cls_IGESAppli_Flow.def("TextDisplayTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::TextDisplayTemplate, "returns Text Display Template Entity raises exception if Index <= 0 or Index > NbTextDisplayTemplates()", py::arg("Index"));
cls_IGESAppli_Flow.def("ContFlowAssociativity", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_Flow::*)(const Standard_Integer) const) &IGESAppli_Flow::ContFlowAssociativity, "returns Continuation Flow Associativity Entity raises exception if Index <= 0 or Index > NbContFlowAssociativities()", py::arg("Index"));
cls_IGESAppli_Flow.def_static("get_type_name_", (const char * (*)()) &IGESAppli_Flow::get_type_name, "None");
cls_IGESAppli_Flow.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_Flow::get_type_descriptor, "None");
cls_IGESAppli_Flow.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_Flow::*)() const) &IGESAppli_Flow::DynamicType, "None");

// TYPEDEF: IGESAPPLI_ARRAY1OFFLOW
bind_NCollection_Array1<opencascade::handle<IGESAppli_Flow> >(mod, "IGESAppli_Array1OfFlow", py::module_local(false));

// CLASS: IGESAPPLI_DRILLEDHOLE
py::class_<IGESAppli_DrilledHole, opencascade::handle<IGESAppli_DrilledHole>, IGESData_IGESEntity> cls_IGESAppli_DrilledHole(mod, "IGESAppli_DrilledHole", "defines DrilledHole, Type <406> Form <6> in package IGESAppli Identifies an entity representing a drilled hole through a printed circuit board.");

// Constructors
cls_IGESAppli_DrilledHole.def(py::init<>());

// Methods
cls_IGESAppli_DrilledHole.def("Init", (void (IGESAppli_DrilledHole::*)(const Standard_Integer, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const Standard_Integer)) &IGESAppli_DrilledHole::Init, "This method is used to set the fields of the class DrilledHole - nbPropVal : Number of property values = 5 - aSize : Drill diameter size - anotherSize : Finish diameter size - aPlating : Plating indication flag False = not plating True = is plating - aLayer : Lower numbered layer - anotherLayer : Higher numbered layer", py::arg("nbPropVal"), py::arg("aSize"), py::arg("anotherSize"), py::arg("aPlating"), py::arg("aLayer"), py::arg("anotherLayer"));
cls_IGESAppli_DrilledHole.def("NbPropertyValues", (Standard_Integer (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::NbPropertyValues, "is always 5");
cls_IGESAppli_DrilledHole.def("DrillDiaSize", (Standard_Real (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::DrillDiaSize, "returns the drill diameter size");
cls_IGESAppli_DrilledHole.def("FinishDiaSize", (Standard_Real (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::FinishDiaSize, "returns the finish diameter size");
cls_IGESAppli_DrilledHole.def("IsPlating", (Standard_Boolean (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::IsPlating, "Returns Plating Status : False = not plating / True = is plating");
cls_IGESAppli_DrilledHole.def("NbLowerLayer", (Standard_Integer (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::NbLowerLayer, "returns the lower numbered layer");
cls_IGESAppli_DrilledHole.def("NbHigherLayer", (Standard_Integer (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::NbHigherLayer, "returns the higher numbered layer");
cls_IGESAppli_DrilledHole.def_static("get_type_name_", (const char * (*)()) &IGESAppli_DrilledHole::get_type_name, "None");
cls_IGESAppli_DrilledHole.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_DrilledHole::get_type_descriptor, "None");
cls_IGESAppli_DrilledHole.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_DrilledHole::*)() const) &IGESAppli_DrilledHole::DynamicType, "None");

// CLASS: IGESAPPLI_HARRAY1OFFINITEELEMENT
py::class_<IGESAppli_HArray1OfFiniteElement, opencascade::handle<IGESAppli_HArray1OfFiniteElement>, Standard_Transient> cls_IGESAppli_HArray1OfFiniteElement(mod, "IGESAppli_HArray1OfFiniteElement", "None", py::multiple_inheritance());

// Constructors
cls_IGESAppli_HArray1OfFiniteElement.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESAppli_HArray1OfFiniteElement.def(py::init<const Standard_Integer, const Standard_Integer, const IGESAppli_Array1OfFiniteElement::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESAppli_HArray1OfFiniteElement.def(py::init<const IGESAppli_Array1OfFiniteElement &>(), py::arg("theOther"));

// Methods
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_HArray1OfFiniteElement::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator delete_", (void (*)(void *)) &IGESAppli_HArray1OfFiniteElement::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_HArray1OfFiniteElement::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_HArray1OfFiniteElement::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_HArray1OfFiniteElement::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_HArray1OfFiniteElement::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfFiniteElement::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESAppli_HArray1OfFiniteElement.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfFiniteElement::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESAppli_HArray1OfFiniteElement.def("Array1", (const IGESAppli_Array1OfFiniteElement & (IGESAppli_HArray1OfFiniteElement::*)() const) &IGESAppli_HArray1OfFiniteElement::Array1, "None");
cls_IGESAppli_HArray1OfFiniteElement.def("ChangeArray1", (IGESAppli_Array1OfFiniteElement & (IGESAppli_HArray1OfFiniteElement::*)()) &IGESAppli_HArray1OfFiniteElement::ChangeArray1, "None");
cls_IGESAppli_HArray1OfFiniteElement.def_static("get_type_name_", (const char * (*)()) &IGESAppli_HArray1OfFiniteElement::get_type_name, "None");
cls_IGESAppli_HArray1OfFiniteElement.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_HArray1OfFiniteElement::get_type_descriptor, "None");
cls_IGESAppli_HArray1OfFiniteElement.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_HArray1OfFiniteElement::*)() const) &IGESAppli_HArray1OfFiniteElement::DynamicType, "None");

// CLASS: IGESAPPLI_ELEMENTRESULTS
py::class_<IGESAppli_ElementResults, opencascade::handle<IGESAppli_ElementResults>, IGESData_IGESEntity> cls_IGESAppli_ElementResults(mod, "IGESAppli_ElementResults", "defines ElementResults, Type <148> in package IGESAppli Used to find the results of FEM analysis");

// Constructors
cls_IGESAppli_ElementResults.def(py::init<>());

// Methods
cls_IGESAppli_ElementResults.def("Init", (void (IGESAppli_ElementResults::*)(const opencascade::handle<IGESDimen_GeneralNote> &, const Standard_Integer, const Standard_Real, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESAppli_HArray1OfFiniteElement> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESBasic_HArray1OfHArray1OfInteger> &, const opencascade::handle<IGESBasic_HArray1OfHArray1OfReal> &)) &IGESAppli_ElementResults::Init, "This method is used to set the fields of the class ElementResults - aNote : GeneralNote Entity describing analysis - aSubCase : Analysis Subcase number - aTime : Analysis time value - nbResults : Number of result values per FEM - aResRepFlag : Results Reporting Flag - allElementIdents : FEM element number for elements - allFiniteElems : FEM element - allTopTypes : Element Topology Types - nbLayers : Number of layers per result data location - allDataLayerFlags : Data Layer Flags - allnbResDataLocs : Number of result data report locations - allResDataLocs : Result Data Report Locations - allResults : List of Result data values of FEM analysis", py::arg("aNote"), py::arg("aSubCase"), py::arg("aTime"), py::arg("nbResults"), py::arg("aResRepFlag"), py::arg("allElementIdents"), py::arg("allFiniteElems"), py::arg("allTopTypes"), py::arg("nbLayers"), py::arg("allDataLayerFlags"), py::arg("allnbResDataLocs"), py::arg("allResDataLocs"), py::arg("allResults"));
cls_IGESAppli_ElementResults.def("SetFormNumber", (void (IGESAppli_ElementResults::*)(const Standard_Integer)) &IGESAppli_ElementResults::SetFormNumber, "Changes the FormNumber (which indicates Type of Result) Error if not in range [0-34]", py::arg("form"));
cls_IGESAppli_ElementResults.def("Note", (opencascade::handle<IGESDimen_GeneralNote> (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::Note, "returns General Note Entity describing analysis case");
cls_IGESAppli_ElementResults.def("SubCaseNumber", (Standard_Integer (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::SubCaseNumber, "returns analysis Subcase number");
cls_IGESAppli_ElementResults.def("Time", (Standard_Real (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::Time, "returns analysis time value");
cls_IGESAppli_ElementResults.def("NbResultValues", (Standard_Integer (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::NbResultValues, "returns number of result values per FEM");
cls_IGESAppli_ElementResults.def("ResultReportFlag", (Standard_Integer (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::ResultReportFlag, "returns Results Reporting Flag");
cls_IGESAppli_ElementResults.def("NbElements", (Standard_Integer (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::NbElements, "returns number of FEM elements");
cls_IGESAppli_ElementResults.def("ElementIdentifier", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::ElementIdentifier, "returns FEM element number for elements", py::arg("Index"));
cls_IGESAppli_ElementResults.def("Element", (opencascade::handle<IGESAppli_FiniteElement> (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::Element, "returns FEM element", py::arg("Index"));
cls_IGESAppli_ElementResults.def("ElementTopologyType", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::ElementTopologyType, "returns element Topology Types", py::arg("Index"));
cls_IGESAppli_ElementResults.def("NbLayers", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::NbLayers, "returns number of layers per result data location", py::arg("Index"));
cls_IGESAppli_ElementResults.def("DataLayerFlag", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::DataLayerFlag, "returns Data Layer Flags", py::arg("Index"));
cls_IGESAppli_ElementResults.def("NbResultDataLocs", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::NbResultDataLocs, "returns number of result data report locations", py::arg("Index"));
cls_IGESAppli_ElementResults.def("ResultDataLoc", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_ElementResults::ResultDataLoc, "returns Result Data Report Locations UNFINISHED", py::arg("NElem"), py::arg("NLoc"));
cls_IGESAppli_ElementResults.def("NbResults", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::NbResults, "returns total number of results", py::arg("Index"));
cls_IGESAppli_ElementResults.def("ResultData", (Standard_Real (IGESAppli_ElementResults::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_ElementResults::ResultData, "returns Result data value for an Element, given its order between 1 and <NbResults(NElem)> (direct access) For a more comprehensive access, see below", py::arg("NElem"), py::arg("num"));
cls_IGESAppli_ElementResults.def("ResultRank", (Standard_Integer (IGESAppli_ElementResults::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer) const) &IGESAppli_ElementResults::ResultRank, "Computes, for a given Element <NElem>, the rank of a individual Result Data, given <NVal>,<NLay>,<NLoc>", py::arg("NElem"), py::arg("NVal"), py::arg("NLay"), py::arg("NLoc"));
cls_IGESAppli_ElementResults.def("ResultData", (Standard_Real (IGESAppli_ElementResults::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer) const) &IGESAppli_ElementResults::ResultData, "returns Result data values of FEM analysis, according this definition : - <NElem> : n0 of the Element to be considered - <NVal> : n0 of the Value between 1 and NbResultValues - <NLay> : n0 of the Layer for this Element - <NLoc> : n0 of the Data Location for this Element This gives for each Element, the corresponding rank computed by ResultRank, in which the leftmost subscript changes most rapidly", py::arg("NElem"), py::arg("NVal"), py::arg("NLay"), py::arg("NLoc"));
cls_IGESAppli_ElementResults.def("ResultList", (opencascade::handle<TColStd_HArray1OfReal> (IGESAppli_ElementResults::*)(const Standard_Integer) const) &IGESAppli_ElementResults::ResultList, "Returns in once the entire list of data for an Element, addressed as by ResultRank (See above)", py::arg("NElem"));
cls_IGESAppli_ElementResults.def_static("get_type_name_", (const char * (*)()) &IGESAppli_ElementResults::get_type_name, "None");
cls_IGESAppli_ElementResults.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_ElementResults::get_type_descriptor, "None");
cls_IGESAppli_ElementResults.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_ElementResults::*)() const) &IGESAppli_ElementResults::DynamicType, "None");

// CLASS: IGESAPPLI_FLOWLINESPEC
py::class_<IGESAppli_FlowLineSpec, opencascade::handle<IGESAppli_FlowLineSpec>, IGESData_IGESEntity> cls_IGESAppli_FlowLineSpec(mod, "IGESAppli_FlowLineSpec", "defines FlowLineSpec, Type <406> Form <14> in package IGESAppli Attaches one or more text strings to entities being used to represent a flow line");

// Constructors
cls_IGESAppli_FlowLineSpec.def(py::init<>());

// Methods
cls_IGESAppli_FlowLineSpec.def("Init", (void (IGESAppli_FlowLineSpec::*)(const opencascade::handle<Interface_HArray1OfHAsciiString> &)) &IGESAppli_FlowLineSpec::Init, "This method is used to set the fields of the class FlowLineSpec - allProperties : primary flow line specification and modifiers", py::arg("allProperties"));
cls_IGESAppli_FlowLineSpec.def("NbPropertyValues", (Standard_Integer (IGESAppli_FlowLineSpec::*)() const) &IGESAppli_FlowLineSpec::NbPropertyValues, "returns the number of property values");
cls_IGESAppli_FlowLineSpec.def("FlowLineName", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_FlowLineSpec::*)() const) &IGESAppli_FlowLineSpec::FlowLineName, "returns primary flow line specification name");
cls_IGESAppli_FlowLineSpec.def("Modifier", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_FlowLineSpec::*)(const Standard_Integer) const) &IGESAppli_FlowLineSpec::Modifier, "returns specified modifier element raises exception if Index <= 1 or Index > NbPropertyValues", py::arg("Index"));
cls_IGESAppli_FlowLineSpec.def_static("get_type_name_", (const char * (*)()) &IGESAppli_FlowLineSpec::get_type_name, "None");
cls_IGESAppli_FlowLineSpec.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_FlowLineSpec::get_type_descriptor, "None");
cls_IGESAppli_FlowLineSpec.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_FlowLineSpec::*)() const) &IGESAppli_FlowLineSpec::DynamicType, "None");

// CLASS: IGESAPPLI_GENERALMODULE
py::class_<IGESAppli_GeneralModule, opencascade::handle<IGESAppli_GeneralModule>, IGESData_GeneralModule> cls_IGESAppli_GeneralModule(mod, "IGESAppli_GeneralModule", "Definition of General Services for IGESAppli (specific part) This Services comprise : Shared & Implied Lists, Copy, Check");

// Constructors
cls_IGESAppli_GeneralModule.def(py::init<>());

// Methods
cls_IGESAppli_GeneralModule.def("OwnSharedCase", (void (IGESAppli_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, Interface_EntityIterator &) const) &IGESAppli_GeneralModule::OwnSharedCase, "Lists the Entities shared by a given IGESEntity <ent>, from its specific parameters : specific for each type", py::arg("CN"), py::arg("ent"), py::arg("iter"));
cls_IGESAppli_GeneralModule.def("DirChecker", (IGESData_DirChecker (IGESAppli_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESAppli_GeneralModule::DirChecker, "Returns a DirChecker, specific for each type of Entity (identified by its Case Number) : this DirChecker defines constraints which must be respected by the DirectoryPart", py::arg("CN"), py::arg("ent"));
cls_IGESAppli_GeneralModule.def("OwnCheckCase", (void (IGESAppli_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_GeneralModule::OwnCheckCase, "Performs Specific Semantic Check for each type of Entity", py::arg("CN"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_GeneralModule.def("NewVoid", (Standard_Boolean (IGESAppli_GeneralModule::*)(const Standard_Integer, opencascade::handle<Standard_Transient> &) const) &IGESAppli_GeneralModule::NewVoid, "Specific creation of a new void entity", py::arg("CN"), py::arg("entto"));
cls_IGESAppli_GeneralModule.def("OwnCopyCase", (void (IGESAppli_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, Interface_CopyTool &) const) &IGESAppli_GeneralModule::OwnCopyCase, "Copies parameters which are specific of each Type of Entity", py::arg("CN"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_GeneralModule.def("CategoryNumber", (Standard_Integer (IGESAppli_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &) const) &IGESAppli_GeneralModule::CategoryNumber, "Returns a category number which characterizes an entity FEA for : ElementResults,FiniteElement,Node&Co Piping for : Flow & Co Professional for : others (in fact Schematics)", py::arg("CN"), py::arg("ent"), py::arg("shares"));
cls_IGESAppli_GeneralModule.def_static("get_type_name_", (const char * (*)()) &IGESAppli_GeneralModule::get_type_name, "None");
cls_IGESAppli_GeneralModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_GeneralModule::get_type_descriptor, "None");
cls_IGESAppli_GeneralModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_GeneralModule::*)() const) &IGESAppli_GeneralModule::DynamicType, "None");

// CLASS: IGESAPPLI_HARRAY1OFFLOW
py::class_<IGESAppli_HArray1OfFlow, opencascade::handle<IGESAppli_HArray1OfFlow>, Standard_Transient> cls_IGESAppli_HArray1OfFlow(mod, "IGESAppli_HArray1OfFlow", "None", py::multiple_inheritance());

// Constructors
cls_IGESAppli_HArray1OfFlow.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESAppli_HArray1OfFlow.def(py::init<const Standard_Integer, const Standard_Integer, const IGESAppli_Array1OfFlow::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESAppli_HArray1OfFlow.def(py::init<const IGESAppli_Array1OfFlow &>(), py::arg("theOther"));

// Methods
// cls_IGESAppli_HArray1OfFlow.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_HArray1OfFlow::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator delete_", (void (*)(void *)) &IGESAppli_HArray1OfFlow::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_HArray1OfFlow::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_HArray1OfFlow::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_HArray1OfFlow::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_HArray1OfFlow::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESAppli_HArray1OfFlow.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfFlow::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESAppli_HArray1OfFlow.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESAppli_HArray1OfFlow::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESAppli_HArray1OfFlow.def("Array1", (const IGESAppli_Array1OfFlow & (IGESAppli_HArray1OfFlow::*)() const) &IGESAppli_HArray1OfFlow::Array1, "None");
cls_IGESAppli_HArray1OfFlow.def("ChangeArray1", (IGESAppli_Array1OfFlow & (IGESAppli_HArray1OfFlow::*)()) &IGESAppli_HArray1OfFlow::ChangeArray1, "None");
cls_IGESAppli_HArray1OfFlow.def_static("get_type_name_", (const char * (*)()) &IGESAppli_HArray1OfFlow::get_type_name, "None");
cls_IGESAppli_HArray1OfFlow.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_HArray1OfFlow::get_type_descriptor, "None");
cls_IGESAppli_HArray1OfFlow.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_HArray1OfFlow::*)() const) &IGESAppli_HArray1OfFlow::DynamicType, "None");

// CLASS: IGESAPPLI_LEVELFUNCTION
py::class_<IGESAppli_LevelFunction, opencascade::handle<IGESAppli_LevelFunction>, IGESData_IGESEntity> cls_IGESAppli_LevelFunction(mod, "IGESAppli_LevelFunction", "defines LevelFunction, Type <406> Form <3> in package IGESAppli Used to transfer the meaning or intended use of a level in the sending system");

// Constructors
cls_IGESAppli_LevelFunction.def(py::init<>());

// Methods
cls_IGESAppli_LevelFunction.def("Init", (void (IGESAppli_LevelFunction::*)(const Standard_Integer, const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &)) &IGESAppli_LevelFunction::Init, "This method is used to set the fields of the class LevelFunction - nbPropVal : Number of Properties, always = 2 - aCode : Function Description code default = 0 - aFuncDescrip : Function Description default = null string", py::arg("nbPropVal"), py::arg("aCode"), py::arg("aFuncDescrip"));
cls_IGESAppli_LevelFunction.def("NbPropertyValues", (Standard_Integer (IGESAppli_LevelFunction::*)() const) &IGESAppli_LevelFunction::NbPropertyValues, "is always 2");
cls_IGESAppli_LevelFunction.def("FuncDescriptionCode", (Standard_Integer (IGESAppli_LevelFunction::*)() const) &IGESAppli_LevelFunction::FuncDescriptionCode, "returns the function description code . Default = 0");
cls_IGESAppli_LevelFunction.def("FuncDescription", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_LevelFunction::*)() const) &IGESAppli_LevelFunction::FuncDescription, "returns the function description Default = null string");
cls_IGESAppli_LevelFunction.def_static("get_type_name_", (const char * (*)()) &IGESAppli_LevelFunction::get_type_name, "None");
cls_IGESAppli_LevelFunction.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_LevelFunction::get_type_descriptor, "None");
cls_IGESAppli_LevelFunction.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_LevelFunction::*)() const) &IGESAppli_LevelFunction::DynamicType, "None");

// CLASS: IGESAPPLI_LEVELTOPWBLAYERMAP
py::class_<IGESAppli_LevelToPWBLayerMap, opencascade::handle<IGESAppli_LevelToPWBLayerMap>, IGESData_IGESEntity> cls_IGESAppli_LevelToPWBLayerMap(mod, "IGESAppli_LevelToPWBLayerMap", "defines LevelToPWBLayerMap, Type <406> Form <24> in package IGESAppli Used to correlate an exchange file level number with its corresponding native level identifier, physical PWB layer number and predefined functional level identification");

// Constructors
cls_IGESAppli_LevelToPWBLayerMap.def(py::init<>());

// Methods
cls_IGESAppli_LevelToPWBLayerMap.def("Init", (void (IGESAppli_LevelToPWBLayerMap::*)(const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<Interface_HArray1OfHAsciiString> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<Interface_HArray1OfHAsciiString> &)) &IGESAppli_LevelToPWBLayerMap::Init, "This method is used to set the fields of the class LevelToPWBLayerMap - nbPropVal : Number of property values - allExchLevels : Exchange File Level Numbers - allNativeLevels : Native Level Identifications - allPhysLevels : Physical Layer Numbers - allExchIdents : Exchange File Level Identifications raises exception if allExchLevels, allNativeLevels, allPhysLevels and all ExchIdents are not of same dimensions", py::arg("nbPropVal"), py::arg("allExchLevels"), py::arg("allNativeLevels"), py::arg("allPhysLevels"), py::arg("allExchIdents"));
cls_IGESAppli_LevelToPWBLayerMap.def("NbPropertyValues", (Standard_Integer (IGESAppli_LevelToPWBLayerMap::*)() const) &IGESAppli_LevelToPWBLayerMap::NbPropertyValues, "returns number of property values");
cls_IGESAppli_LevelToPWBLayerMap.def("NbLevelToLayerDefs", (Standard_Integer (IGESAppli_LevelToPWBLayerMap::*)() const) &IGESAppli_LevelToPWBLayerMap::NbLevelToLayerDefs, "returns number of level to layer definitions");
cls_IGESAppli_LevelToPWBLayerMap.def("ExchangeFileLevelNumber", (Standard_Integer (IGESAppli_LevelToPWBLayerMap::*)(const Standard_Integer) const) &IGESAppli_LevelToPWBLayerMap::ExchangeFileLevelNumber, "returns Exchange File Level Number raises exception if Index <= 0 or Index > NbLevelToLayerDefs", py::arg("Index"));
cls_IGESAppli_LevelToPWBLayerMap.def("NativeLevel", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_LevelToPWBLayerMap::*)(const Standard_Integer) const) &IGESAppli_LevelToPWBLayerMap::NativeLevel, "returns Native Level Identification raises exception if Index <= 0 or Index > NbLevelToLayerDefs", py::arg("Index"));
cls_IGESAppli_LevelToPWBLayerMap.def("PhysicalLayerNumber", (Standard_Integer (IGESAppli_LevelToPWBLayerMap::*)(const Standard_Integer) const) &IGESAppli_LevelToPWBLayerMap::PhysicalLayerNumber, "returns Physical Layer Number raises exception if Index <= 0 or Index > NbLevelToLayerDefs", py::arg("Index"));
cls_IGESAppli_LevelToPWBLayerMap.def("ExchangeFileLevelIdent", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_LevelToPWBLayerMap::*)(const Standard_Integer) const) &IGESAppli_LevelToPWBLayerMap::ExchangeFileLevelIdent, "None", py::arg("Index"));
cls_IGESAppli_LevelToPWBLayerMap.def_static("get_type_name_", (const char * (*)()) &IGESAppli_LevelToPWBLayerMap::get_type_name, "None");
cls_IGESAppli_LevelToPWBLayerMap.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_LevelToPWBLayerMap::get_type_descriptor, "None");
cls_IGESAppli_LevelToPWBLayerMap.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_LevelToPWBLayerMap::*)() const) &IGESAppli_LevelToPWBLayerMap::DynamicType, "None");

// CLASS: IGESAPPLI_LINEWIDENING
py::class_<IGESAppli_LineWidening, opencascade::handle<IGESAppli_LineWidening>, IGESData_IGESEntity> cls_IGESAppli_LineWidening(mod, "IGESAppli_LineWidening", "defines LineWidening, Type <406> Form <5> in package IGESAppli Defines the characteristics of entities when they are used to define locations of items.");

// Constructors
cls_IGESAppli_LineWidening.def(py::init<>());

// Methods
cls_IGESAppli_LineWidening.def("Init", (void (IGESAppli_LineWidening::*)(const Standard_Integer, const Standard_Real, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Real)) &IGESAppli_LineWidening::Init, "This method is used to set the fields of the class LineWidening - nbPropVal : Number of property values = 5 - aWidth : Width of metalization - aCornering : Cornering codes 0 = rounded 1 = squared - aExtnFlag : Extension Flag 0 = No Extension 1 = One-half width extension 2 = Extn set by ExtnVal - aJustifFlag : Justification flag 0 = Center justified 1 = left justified 2 = right justified - aExtnVal : Extension value if aExtnFlag = 2", py::arg("nbPropVal"), py::arg("aWidth"), py::arg("aCornering"), py::arg("aExtnFlag"), py::arg("aJustifFlag"), py::arg("aExtnVal"));
cls_IGESAppli_LineWidening.def("NbPropertyValues", (Standard_Integer (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::NbPropertyValues, "returns the number of property values is always 5");
cls_IGESAppli_LineWidening.def("WidthOfMetalization", (Standard_Real (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::WidthOfMetalization, "returns the width of metallization");
cls_IGESAppli_LineWidening.def("CorneringCode", (Standard_Integer (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::CorneringCode, "returns the cornering code 0 = Rounded / 1 = Squared");
cls_IGESAppli_LineWidening.def("ExtensionFlag", (Standard_Integer (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::ExtensionFlag, "returns the extension flag 0 = No extension 1 = One-half width extension 2 = Extension set by theExtnVal");
cls_IGESAppli_LineWidening.def("JustificationFlag", (Standard_Integer (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::JustificationFlag, "returns the justification flag 0 = Centre justified 1 = Left justified 2 = Right justified");
cls_IGESAppli_LineWidening.def("ExtensionValue", (Standard_Real (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::ExtensionValue, "returns the Extension Value Present only if theExtnFlag = 2");
cls_IGESAppli_LineWidening.def_static("get_type_name_", (const char * (*)()) &IGESAppli_LineWidening::get_type_name, "None");
cls_IGESAppli_LineWidening.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_LineWidening::get_type_descriptor, "None");
cls_IGESAppli_LineWidening.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_LineWidening::*)() const) &IGESAppli_LineWidening::DynamicType, "None");

// CLASS: IGESAPPLI_NODALCONSTRAINT
py::class_<IGESAppli_NodalConstraint, opencascade::handle<IGESAppli_NodalConstraint>, IGESData_IGESEntity> cls_IGESAppli_NodalConstraint(mod, "IGESAppli_NodalConstraint", "defines NodalConstraint, Type <418> Form <0> in package IGESAppli Relates loads and/or constraints to specific nodes in the Finite Element Model by creating a relation between Node entities and Tabular Data Property that contains the load or constraint data");

// Constructors
cls_IGESAppli_NodalConstraint.def(py::init<>());

// Methods
cls_IGESAppli_NodalConstraint.def("Init", (void (IGESAppli_NodalConstraint::*)(const Standard_Integer, const opencascade::handle<IGESAppli_Node> &, const opencascade::handle<IGESDefs_HArray1OfTabularData> &)) &IGESAppli_NodalConstraint::Init, "This method is used to set the fields of the class NodalConstraint - aType : Loads / Constraints - aNode : the Node - allTabData : Tabular Data Property carrying the load or constraint vector", py::arg("aType"), py::arg("aNode"), py::arg("allTabData"));
cls_IGESAppli_NodalConstraint.def("NbCases", (Standard_Integer (IGESAppli_NodalConstraint::*)() const) &IGESAppli_NodalConstraint::NbCases, "returns total number of cases");
cls_IGESAppli_NodalConstraint.def("Type", (Standard_Integer (IGESAppli_NodalConstraint::*)() const) &IGESAppli_NodalConstraint::Type, "returns whether Loads (1) or Constraints (2)");
cls_IGESAppli_NodalConstraint.def("NodeEntity", (opencascade::handle<IGESAppli_Node> (IGESAppli_NodalConstraint::*)() const) &IGESAppli_NodalConstraint::NodeEntity, "returns the Node");
cls_IGESAppli_NodalConstraint.def("TabularData", (opencascade::handle<IGESDefs_TabularData> (IGESAppli_NodalConstraint::*)(const Standard_Integer) const) &IGESAppli_NodalConstraint::TabularData, "returns Tabular Data Property carrying load or constraint vector raises exception if Index <= 0 or Index > NbCases", py::arg("Index"));
cls_IGESAppli_NodalConstraint.def_static("get_type_name_", (const char * (*)()) &IGESAppli_NodalConstraint::get_type_name, "None");
cls_IGESAppli_NodalConstraint.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_NodalConstraint::get_type_descriptor, "None");
cls_IGESAppli_NodalConstraint.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_NodalConstraint::*)() const) &IGESAppli_NodalConstraint::DynamicType, "None");

// CLASS: IGESAPPLI_NODALDISPLANDROT
py::class_<IGESAppli_NodalDisplAndRot, opencascade::handle<IGESAppli_NodalDisplAndRot>, IGESData_IGESEntity> cls_IGESAppli_NodalDisplAndRot(mod, "IGESAppli_NodalDisplAndRot", "defines NodalDisplAndRot, Type <138> Form <0> in package IGESAppli Used to communicate finite element post processing data.");

// Constructors
cls_IGESAppli_NodalDisplAndRot.def(py::init<>());

// Methods
cls_IGESAppli_NodalDisplAndRot.def("Init", (void (IGESAppli_NodalDisplAndRot::*)(const opencascade::handle<IGESDimen_HArray1OfGeneralNote> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESAppli_HArray1OfNode> &, const opencascade::handle<IGESBasic_HArray1OfHArray1OfXYZ> &, const opencascade::handle<IGESBasic_HArray1OfHArray1OfXYZ> &)) &IGESAppli_NodalDisplAndRot::Init, "This method is used to set the fields of the class NodalDisplAndRot - allNotes : Used to store the general note describing the analysis cases - allIdentifiers : Used to store the node number identifier for the nodes - allNodes : Used to store the nodes - allRotParams : Used to store the rotation for the nodes - allTransParams : Used to store the incremental displacements for the nodes raises exception if Lengths of allIdentifiers, allNodes, allRotParams, and allTransParams are not same or if length of allNotes and size of each element of allRotParams and allTransParam are not same", py::arg("allNotes"), py::arg("allIdentifiers"), py::arg("allNodes"), py::arg("allRotParams"), py::arg("allTransParams"));
cls_IGESAppli_NodalDisplAndRot.def("NbCases", (Standard_Integer (IGESAppli_NodalDisplAndRot::*)() const) &IGESAppli_NodalDisplAndRot::NbCases, "returns the number of analysis cases");
cls_IGESAppli_NodalDisplAndRot.def("NbNodes", (Standard_Integer (IGESAppli_NodalDisplAndRot::*)() const) &IGESAppli_NodalDisplAndRot::NbNodes, "returns the number of nodes");
cls_IGESAppli_NodalDisplAndRot.def("Note", (opencascade::handle<IGESDimen_GeneralNote> (IGESAppli_NodalDisplAndRot::*)(const Standard_Integer) const) &IGESAppli_NodalDisplAndRot::Note, "returns the General Note that describes the Index analysis case raises exception if Index <= 0 or Index > NbCases", py::arg("Index"));
cls_IGESAppli_NodalDisplAndRot.def("NodeIdentifier", (Standard_Integer (IGESAppli_NodalDisplAndRot::*)(const Standard_Integer) const) &IGESAppli_NodalDisplAndRot::NodeIdentifier, "returns the node identifier as specified by the Index raises exception if Index <= 0 or Index > NbNodes", py::arg("Index"));
cls_IGESAppli_NodalDisplAndRot.def("Node", (opencascade::handle<IGESAppli_Node> (IGESAppli_NodalDisplAndRot::*)(const Standard_Integer) const) &IGESAppli_NodalDisplAndRot::Node, "returns the node as specified by the Index raises exception if Index <= 0 or Index > NbNodes", py::arg("Index"));
cls_IGESAppli_NodalDisplAndRot.def("TranslationParameter", (gp_XYZ (IGESAppli_NodalDisplAndRot::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_NodalDisplAndRot::TranslationParameter, "returns the Translational Parameters for the particular Index Exception raised if NodeNum <= 0 or NodeNum > NbNodes() or CaseNum <= 0 or CaseNum > NbCases()", py::arg("NodeNum"), py::arg("CaseNum"));
cls_IGESAppli_NodalDisplAndRot.def("RotationalParameter", (gp_XYZ (IGESAppli_NodalDisplAndRot::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_NodalDisplAndRot::RotationalParameter, "returns the Rotational Parameters for Index Exception raised if NodeNum <= 0 or NodeNum > NbNodes() or CaseNum <= 0 or CaseNum > NbCases()", py::arg("NodeNum"), py::arg("CaseNum"));
cls_IGESAppli_NodalDisplAndRot.def_static("get_type_name_", (const char * (*)()) &IGESAppli_NodalDisplAndRot::get_type_name, "None");
cls_IGESAppli_NodalDisplAndRot.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_NodalDisplAndRot::get_type_descriptor, "None");
cls_IGESAppli_NodalDisplAndRot.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_NodalDisplAndRot::*)() const) &IGESAppli_NodalDisplAndRot::DynamicType, "None");

// CLASS: IGESAPPLI_NODALRESULTS
py::class_<IGESAppli_NodalResults, opencascade::handle<IGESAppli_NodalResults>, IGESData_IGESEntity> cls_IGESAppli_NodalResults(mod, "IGESAppli_NodalResults", "defines NodalResults, Type <146> in package IGESAppli Used to store the Analysis Data results per FEM Node");

// Constructors
cls_IGESAppli_NodalResults.def(py::init<>());

// Methods
cls_IGESAppli_NodalResults.def("Init", (void (IGESAppli_NodalResults::*)(const opencascade::handle<IGESDimen_GeneralNote> &, const Standard_Integer, const Standard_Real, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESAppli_HArray1OfNode> &, const opencascade::handle<TColStd_HArray2OfReal> &)) &IGESAppli_NodalResults::Init, "This method is used to set the fields of the class NodalResults - aNote : General Note that describes the analysis case - aNumber : Analysis Subcase number - aTime : Analysis time - allNodeIdentifiers : Node identifiers for the nodes - allNodes : List of FEM Node Entities - allData : Values of the Finite Element analysis result data raises exception if Lengths of allNodeIdentifiers, allNodes and allData (Cols) are not same", py::arg("aNote"), py::arg("aNumber"), py::arg("aTime"), py::arg("allNodeIdentifiers"), py::arg("allNodes"), py::arg("allData"));
cls_IGESAppli_NodalResults.def("SetFormNumber", (void (IGESAppli_NodalResults::*)(const Standard_Integer)) &IGESAppli_NodalResults::SetFormNumber, "Changes the FormNumber (which indicates Type of Result) Error if not in range [0-34]", py::arg("form"));
cls_IGESAppli_NodalResults.def("Note", (opencascade::handle<IGESDimen_GeneralNote> (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::Note, "returns the General Note Entity that describes the analysis case");
cls_IGESAppli_NodalResults.def("SubCaseNumber", (Standard_Integer (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::SubCaseNumber, "returns zero if there is no subcase");
cls_IGESAppli_NodalResults.def("Time", (Standard_Real (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::Time, "returns the Analysis time value for this subcase. It is the time at which transient analysis results occur in the mathematical FEM model.");
cls_IGESAppli_NodalResults.def("NbData", (Standard_Integer (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::NbData, "returns number of real values in array V for a FEM node");
cls_IGESAppli_NodalResults.def("NbNodes", (Standard_Integer (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::NbNodes, "returns number of FEM nodes for which data is to be read.");
cls_IGESAppli_NodalResults.def("NodeIdentifier", (Standard_Integer (IGESAppli_NodalResults::*)(const Standard_Integer) const) &IGESAppli_NodalResults::NodeIdentifier, "returns FEM node number identifier for the (Index)th node raises exception if Index <= 0 or Index > NbNodes", py::arg("Index"));
cls_IGESAppli_NodalResults.def("Node", (opencascade::handle<IGESAppli_Node> (IGESAppli_NodalResults::*)(const Standard_Integer) const) &IGESAppli_NodalResults::Node, "returns the node as specified by the Index raises exception if Index <= 0 or Index > NbNodes", py::arg("Index"));
cls_IGESAppli_NodalResults.def("Data", (Standard_Real (IGESAppli_NodalResults::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_NodalResults::Data, "returns the finite element analysis result value raises exception if (NodeNum <= 0 or NodeNum > NbNodes()) or if (DataNum <=0 or DataNum > NbData())", py::arg("NodeNum"), py::arg("DataNum"));
cls_IGESAppli_NodalResults.def_static("get_type_name_", (const char * (*)()) &IGESAppli_NodalResults::get_type_name, "None");
cls_IGESAppli_NodalResults.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_NodalResults::get_type_descriptor, "None");
cls_IGESAppli_NodalResults.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_NodalResults::*)() const) &IGESAppli_NodalResults::DynamicType, "None");

// CLASS: IGESAPPLI_PARTNUMBER
py::class_<IGESAppli_PartNumber, opencascade::handle<IGESAppli_PartNumber>, IGESData_IGESEntity> cls_IGESAppli_PartNumber(mod, "IGESAppli_PartNumber", "defines PartNumber, Type <406> Form <9> in package IGESAppli Attaches a set of text strings that define the common part numbers to an entity being used to represent a physical component");

// Constructors
cls_IGESAppli_PartNumber.def(py::init<>());

// Methods
cls_IGESAppli_PartNumber.def("Init", (void (IGESAppli_PartNumber::*)(const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<TCollection_HAsciiString> &)) &IGESAppli_PartNumber::Init, "This method is used to set the fields of the class PartNumber - nbPropVal : number of property values, always = 4 - aGenName : Generic part number or name - aMilName : Military Standard (MIL-STD) part number - aVendName : Vendor part number or name - anIntName : Internal part number", py::arg("nbPropVal"), py::arg("aGenName"), py::arg("aMilName"), py::arg("aVendName"), py::arg("anIntName"));
cls_IGESAppli_PartNumber.def("NbPropertyValues", (Standard_Integer (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::NbPropertyValues, "returns number of property values, always = 4");
cls_IGESAppli_PartNumber.def("GenericNumber", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::GenericNumber, "returns Generic part number or name");
cls_IGESAppli_PartNumber.def("MilitaryNumber", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::MilitaryNumber, "returns Military Standard (MIL-STD) part number");
cls_IGESAppli_PartNumber.def("VendorNumber", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::VendorNumber, "returns Vendor part number or name");
cls_IGESAppli_PartNumber.def("InternalNumber", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::InternalNumber, "returns Internal part number");
cls_IGESAppli_PartNumber.def_static("get_type_name_", (const char * (*)()) &IGESAppli_PartNumber::get_type_name, "None");
cls_IGESAppli_PartNumber.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_PartNumber::get_type_descriptor, "None");
cls_IGESAppli_PartNumber.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_PartNumber::*)() const) &IGESAppli_PartNumber::DynamicType, "None");

// CLASS: IGESAPPLI_PINNUMBER
py::class_<IGESAppli_PinNumber, opencascade::handle<IGESAppli_PinNumber>, IGESData_IGESEntity> cls_IGESAppli_PinNumber(mod, "IGESAppli_PinNumber", "defines PinNumber, Type <406> Form <8> in package IGESAppli Used to attach a text string representing a component pin number to an entity being used to represent an electrical component's pin");

// Constructors
cls_IGESAppli_PinNumber.def(py::init<>());

// Methods
cls_IGESAppli_PinNumber.def("Init", (void (IGESAppli_PinNumber::*)(const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &)) &IGESAppli_PinNumber::Init, "This method is used to set the fields of the class PinNumber - nbPropVal : Number of property values (always = 1) - aValue : Pin Number value", py::arg("nbPropVal"), py::arg("aValue"));
cls_IGESAppli_PinNumber.def("NbPropertyValues", (Standard_Integer (IGESAppli_PinNumber::*)() const) &IGESAppli_PinNumber::NbPropertyValues, "returns the number of property values is always 1");
cls_IGESAppli_PinNumber.def("PinNumberVal", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PinNumber::*)() const) &IGESAppli_PinNumber::PinNumberVal, "returns the pin number value");
cls_IGESAppli_PinNumber.def_static("get_type_name_", (const char * (*)()) &IGESAppli_PinNumber::get_type_name, "None");
cls_IGESAppli_PinNumber.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_PinNumber::get_type_descriptor, "None");
cls_IGESAppli_PinNumber.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_PinNumber::*)() const) &IGESAppli_PinNumber::DynamicType, "None");

// CLASS: IGESAPPLI_PIPINGFLOW
py::class_<IGESAppli_PipingFlow, opencascade::handle<IGESAppli_PipingFlow>, IGESData_IGESEntity> cls_IGESAppli_PipingFlow(mod, "IGESAppli_PipingFlow", "defines PipingFlow, Type <402> Form <20> in package IGESAppli Represents a single fluid flow path");

// Constructors
cls_IGESAppli_PipingFlow.def(py::init<>());

// Methods
cls_IGESAppli_PipingFlow.def("Init", (void (IGESAppli_PipingFlow::*)(const Standard_Integer, const Standard_Integer, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const opencascade::handle<IGESDraw_HArray1OfConnectPoint> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const opencascade::handle<Interface_HArray1OfHAsciiString> &, const opencascade::handle<IGESGraph_HArray1OfTextDisplayTemplate> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESAppli_PipingFlow::Init, "This method is used to set the fields of the class PipingFlow - nbContextFlags : Count of Context Flags, always = 1 - aFlowType : Type of Flow, default = 0 - allFlowAssocs : PipingFlow Associativity Entities - allConnectPoints : Connect Point Entities - allJoins : Join Entities - allFlowNames : PipingFlow Names - allTextDispTs : Text Display Template Entities - allContFlowAssocs : Continuation Flow Associativity Entities", py::arg("nbContextFlags"), py::arg("aFlowType"), py::arg("allFlowAssocs"), py::arg("allConnectPoints"), py::arg("allJoins"), py::arg("allFlowNames"), py::arg("allTextDisps"), py::arg("allContFlowAssocs"));
cls_IGESAppli_PipingFlow.def("OwnCorrect", (Standard_Boolean (IGESAppli_PipingFlow::*)()) &IGESAppli_PipingFlow::OwnCorrect, "forces NbContextFalgs to 1, returns True if changed");
cls_IGESAppli_PipingFlow.def("NbContextFlags", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbContextFlags, "returns number of Count of Context Flags, always = 1");
cls_IGESAppli_PipingFlow.def("NbFlowAssociativities", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbFlowAssociativities, "returns number of Piping Flow Associativity Entities");
cls_IGESAppli_PipingFlow.def("NbConnectPoints", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbConnectPoints, "returns number of Connect Point Entities");
cls_IGESAppli_PipingFlow.def("NbJoins", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbJoins, "returns number of Join Entities");
cls_IGESAppli_PipingFlow.def("NbFlowNames", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbFlowNames, "returns number of Flow Names");
cls_IGESAppli_PipingFlow.def("NbTextDisplayTemplates", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbTextDisplayTemplates, "returns number of Text Display Template Entities");
cls_IGESAppli_PipingFlow.def("NbContFlowAssociativities", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::NbContFlowAssociativities, "returns number of Continuation Piping Flow Associativities");
cls_IGESAppli_PipingFlow.def("TypeOfFlow", (Standard_Integer (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::TypeOfFlow, "returns Type of Flow = 0 : Not specified, 1 : Logical, 2 : Physical");
cls_IGESAppli_PipingFlow.def("FlowAssociativity", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::FlowAssociativity, "returns Piping Flow Associativity Entity raises exception if Index <= 0 or Index > NbFlowAssociativities()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def("ConnectPoint", (opencascade::handle<IGESDraw_ConnectPoint> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::ConnectPoint, "returns Connect Point Entity raises exception if Index <= 0 or Index > NbConnectPoints()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def("Join", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::Join, "returns Join Entity raises exception if Index <= 0 or Index > NbJoins()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def("FlowName", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::FlowName, "returns Flow Name raises exception if Index <= 0 or Index > NbFlowNames()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def("TextDisplayTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::TextDisplayTemplate, "returns Text Display Template Entity raises exception if Index <= 0 or Index > NbTextDisplayTemplates()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def("ContFlowAssociativity", (opencascade::handle<IGESData_IGESEntity> (IGESAppli_PipingFlow::*)(const Standard_Integer) const) &IGESAppli_PipingFlow::ContFlowAssociativity, "returns Continuation Piping Flow Associativity Entity raises exception if Index <= 0 or Index > NbContFlowAssociativities()", py::arg("Index"));
cls_IGESAppli_PipingFlow.def_static("get_type_name_", (const char * (*)()) &IGESAppli_PipingFlow::get_type_name, "None");
cls_IGESAppli_PipingFlow.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_PipingFlow::get_type_descriptor, "None");
cls_IGESAppli_PipingFlow.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_PipingFlow::*)() const) &IGESAppli_PipingFlow::DynamicType, "None");

// CLASS: IGESAPPLI_PROTOCOL
py::class_<IGESAppli_Protocol, opencascade::handle<IGESAppli_Protocol>, IGESData_Protocol> cls_IGESAppli_Protocol(mod, "IGESAppli_Protocol", "Description of Protocol for IGESAppli");

// Constructors
cls_IGESAppli_Protocol.def(py::init<>());

// Methods
cls_IGESAppli_Protocol.def("NbResources", (Standard_Integer (IGESAppli_Protocol::*)() const) &IGESAppli_Protocol::NbResources, "Gives the count of direct Resource Protocol. Here, two (Protocols from IGESDefs and IGESDraw)");
cls_IGESAppli_Protocol.def("Resource", (opencascade::handle<Interface_Protocol> (IGESAppli_Protocol::*)(const Standard_Integer) const) &IGESAppli_Protocol::Resource, "Returns a Resource, given a rank.", py::arg("num"));
cls_IGESAppli_Protocol.def("TypeNumber", (Standard_Integer (IGESAppli_Protocol::*)(const opencascade::handle<Standard_Type> &) const) &IGESAppli_Protocol::TypeNumber, "Returns a Case Number, specific of each recognized Type This Case Number is then used in Libraries : the various Modules attached to this class of Protocol must use them in accordance (for a given value of TypeNumber, they must consider the same Type as the Protocol defines)", py::arg("atype"));
cls_IGESAppli_Protocol.def_static("get_type_name_", (const char * (*)()) &IGESAppli_Protocol::get_type_name, "None");
cls_IGESAppli_Protocol.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_Protocol::get_type_descriptor, "None");
cls_IGESAppli_Protocol.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_Protocol::*)() const) &IGESAppli_Protocol::DynamicType, "None");

// CLASS: IGESAPPLI_PWBARTWORKSTACKUP
py::class_<IGESAppli_PWBArtworkStackup, opencascade::handle<IGESAppli_PWBArtworkStackup>, IGESData_IGESEntity> cls_IGESAppli_PWBArtworkStackup(mod, "IGESAppli_PWBArtworkStackup", "defines PWBArtworkStackup, Type <406> Form <25> in package IGESAppli Used to communicate which exchange file levels are to be combined in order to create the artwork for a printed wire board (PWB). This property should be attached to the entity defining the printed wire assembly (PWA) or if no such entity exists, then the property should stand alone in the file.");

// Constructors
cls_IGESAppli_PWBArtworkStackup.def(py::init<>());

// Methods
cls_IGESAppli_PWBArtworkStackup.def("Init", (void (IGESAppli_PWBArtworkStackup::*)(const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<TColStd_HArray1OfInteger> &)) &IGESAppli_PWBArtworkStackup::Init, "This method is used to set the fields of the class PWBArtworkStackup - nbPropVal : number of property values - anArtIdent : Artwork Stackup Identification - allLevelNums : Level Numbers", py::arg("nbPropVal"), py::arg("anArtIdent"), py::arg("allLevelNums"));
cls_IGESAppli_PWBArtworkStackup.def("NbPropertyValues", (Standard_Integer (IGESAppli_PWBArtworkStackup::*)() const) &IGESAppli_PWBArtworkStackup::NbPropertyValues, "returns number of property values");
cls_IGESAppli_PWBArtworkStackup.def("Identification", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_PWBArtworkStackup::*)() const) &IGESAppli_PWBArtworkStackup::Identification, "returns Artwork Stackup Identification");
cls_IGESAppli_PWBArtworkStackup.def("NbLevelNumbers", (Standard_Integer (IGESAppli_PWBArtworkStackup::*)() const) &IGESAppli_PWBArtworkStackup::NbLevelNumbers, "returns total number of Level Numbers");
cls_IGESAppli_PWBArtworkStackup.def("LevelNumber", (Standard_Integer (IGESAppli_PWBArtworkStackup::*)(const Standard_Integer) const) &IGESAppli_PWBArtworkStackup::LevelNumber, "returns Level Number raises exception if Index <= 0 or Index > NbLevelNumbers", py::arg("Index"));
cls_IGESAppli_PWBArtworkStackup.def_static("get_type_name_", (const char * (*)()) &IGESAppli_PWBArtworkStackup::get_type_name, "None");
cls_IGESAppli_PWBArtworkStackup.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_PWBArtworkStackup::get_type_descriptor, "None");
cls_IGESAppli_PWBArtworkStackup.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_PWBArtworkStackup::*)() const) &IGESAppli_PWBArtworkStackup::DynamicType, "None");

// CLASS: IGESAPPLI_PWBDRILLEDHOLE
py::class_<IGESAppli_PWBDrilledHole, opencascade::handle<IGESAppli_PWBDrilledHole>, IGESData_IGESEntity> cls_IGESAppli_PWBDrilledHole(mod, "IGESAppli_PWBDrilledHole", "defines PWBDrilledHole, Type <406> Form <26> in package IGESAppli Used to identify an entity that locates a drilled hole and to specify the characteristics of the drilled hole");

// Constructors
cls_IGESAppli_PWBDrilledHole.def(py::init<>());

// Methods
cls_IGESAppli_PWBDrilledHole.def("Init", (void (IGESAppli_PWBDrilledHole::*)(const Standard_Integer, const Standard_Real, const Standard_Real, const Standard_Integer)) &IGESAppli_PWBDrilledHole::Init, "This method is used to set the fields of the class PWBDrilledHole - nbPropVal : number of property values, always = 3 - aDrillDia : Drill diameter size - aFinishDia : Finish diameter size - aCode : Function code for drilled hole", py::arg("nbPropVal"), py::arg("aDrillDia"), py::arg("aFinishDia"), py::arg("aCode"));
cls_IGESAppli_PWBDrilledHole.def("NbPropertyValues", (Standard_Integer (IGESAppli_PWBDrilledHole::*)() const) &IGESAppli_PWBDrilledHole::NbPropertyValues, "returns number of property values, always = 3");
cls_IGESAppli_PWBDrilledHole.def("DrillDiameterSize", (Standard_Real (IGESAppli_PWBDrilledHole::*)() const) &IGESAppli_PWBDrilledHole::DrillDiameterSize, "returns Drill diameter size");
cls_IGESAppli_PWBDrilledHole.def("FinishDiameterSize", (Standard_Real (IGESAppli_PWBDrilledHole::*)() const) &IGESAppli_PWBDrilledHole::FinishDiameterSize, "returns Finish diameter size");
cls_IGESAppli_PWBDrilledHole.def("FunctionCode", (Standard_Integer (IGESAppli_PWBDrilledHole::*)() const) &IGESAppli_PWBDrilledHole::FunctionCode, "returns Function code for drilled hole is 0, 1, 2, 3, 4, 5 or 5001-9999");
cls_IGESAppli_PWBDrilledHole.def_static("get_type_name_", (const char * (*)()) &IGESAppli_PWBDrilledHole::get_type_name, "None");
cls_IGESAppli_PWBDrilledHole.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_PWBDrilledHole::get_type_descriptor, "None");
cls_IGESAppli_PWBDrilledHole.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_PWBDrilledHole::*)() const) &IGESAppli_PWBDrilledHole::DynamicType, "None");

// CLASS: IGESAPPLI_READWRITEMODULE
py::class_<IGESAppli_ReadWriteModule, opencascade::handle<IGESAppli_ReadWriteModule>, IGESData_ReadWriteModule> cls_IGESAppli_ReadWriteModule(mod, "IGESAppli_ReadWriteModule", "Defines basic File Access Module for IGESAppli (specific parts) Specific actions concern : Read and Write Own Parameters of an IGESEntity.");

// Constructors
cls_IGESAppli_ReadWriteModule.def(py::init<>());

// Methods
cls_IGESAppli_ReadWriteModule.def("CaseIGES", (Standard_Integer (IGESAppli_ReadWriteModule::*)(const Standard_Integer, const Standard_Integer) const) &IGESAppli_ReadWriteModule::CaseIGES, "Defines Case Numbers for Entities of IGESAppli", py::arg("typenum"), py::arg("formnum"));
cls_IGESAppli_ReadWriteModule.def("ReadOwnParams", (void (IGESAppli_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ReadWriteModule::ReadOwnParams, "Reads own parameters from file for an Entity of IGESAppli", py::arg("CN"), py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ReadWriteModule.def("WriteOwnParams", (void (IGESAppli_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, IGESData_IGESWriter &) const) &IGESAppli_ReadWriteModule::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("CN"), py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ReadWriteModule.def_static("get_type_name_", (const char * (*)()) &IGESAppli_ReadWriteModule::get_type_name, "None");
cls_IGESAppli_ReadWriteModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_ReadWriteModule::get_type_descriptor, "None");
cls_IGESAppli_ReadWriteModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_ReadWriteModule::*)() const) &IGESAppli_ReadWriteModule::DynamicType, "None");

// CLASS: IGESAPPLI_REFERENCEDESIGNATOR
py::class_<IGESAppli_ReferenceDesignator, opencascade::handle<IGESAppli_ReferenceDesignator>, IGESData_IGESEntity> cls_IGESAppli_ReferenceDesignator(mod, "IGESAppli_ReferenceDesignator", "defines ReferenceDesignator, Type <406> Form <7> in package IGESAppli Used to attach a text string containing the value of a component reference designator to an entity being used to represent a component.");

// Constructors
cls_IGESAppli_ReferenceDesignator.def(py::init<>());

// Methods
cls_IGESAppli_ReferenceDesignator.def("Init", (void (IGESAppli_ReferenceDesignator::*)(const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &)) &IGESAppli_ReferenceDesignator::Init, "This method is used to set the fields of the class ReferenceDesignator - nbPropVal : Number of property values = 1 - aText : Reference designator text", py::arg("nbPropVal"), py::arg("aText"));
cls_IGESAppli_ReferenceDesignator.def("NbPropertyValues", (Standard_Integer (IGESAppli_ReferenceDesignator::*)() const) &IGESAppli_ReferenceDesignator::NbPropertyValues, "returns the number of property values is always 1");
cls_IGESAppli_ReferenceDesignator.def("RefDesignatorText", (opencascade::handle<TCollection_HAsciiString> (IGESAppli_ReferenceDesignator::*)() const) &IGESAppli_ReferenceDesignator::RefDesignatorText, "returns the Reference designator text");
cls_IGESAppli_ReferenceDesignator.def_static("get_type_name_", (const char * (*)()) &IGESAppli_ReferenceDesignator::get_type_name, "None");
cls_IGESAppli_ReferenceDesignator.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_ReferenceDesignator::get_type_descriptor, "None");
cls_IGESAppli_ReferenceDesignator.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_ReferenceDesignator::*)() const) &IGESAppli_ReferenceDesignator::DynamicType, "None");

// CLASS: IGESAPPLI_REGIONRESTRICTION
py::class_<IGESAppli_RegionRestriction, opencascade::handle<IGESAppli_RegionRestriction>, IGESData_IGESEntity> cls_IGESAppli_RegionRestriction(mod, "IGESAppli_RegionRestriction", "defines RegionRestriction, Type <406> Form <2> in package IGESAppli Defines regions to set an application's restriction over a region.");

// Constructors
cls_IGESAppli_RegionRestriction.def(py::init<>());

// Methods
cls_IGESAppli_RegionRestriction.def("Init", (void (IGESAppli_RegionRestriction::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer)) &IGESAppli_RegionRestriction::Init, "This method is used to set the fields of the class RegionRestriction - nbPropVal : Number of property values, always = 3 - aViasRest : Electrical Vias restriction - aCompoRest : Electrical components restriction - aCktRest : Electrical circuitry restriction", py::arg("nbPropVal"), py::arg("aViasRest"), py::arg("aCompoRest"), py::arg("aCktRest"));
cls_IGESAppli_RegionRestriction.def("NbPropertyValues", (Standard_Integer (IGESAppli_RegionRestriction::*)() const) &IGESAppli_RegionRestriction::NbPropertyValues, "is always 3");
cls_IGESAppli_RegionRestriction.def("ElectricalViasRestriction", (Standard_Integer (IGESAppli_RegionRestriction::*)() const) &IGESAppli_RegionRestriction::ElectricalViasRestriction, "returns the Electrical vias restriction is 0, 1 or 2");
cls_IGESAppli_RegionRestriction.def("ElectricalComponentRestriction", (Standard_Integer (IGESAppli_RegionRestriction::*)() const) &IGESAppli_RegionRestriction::ElectricalComponentRestriction, "returns the Electrical components restriction is 0, 1 or 2");
cls_IGESAppli_RegionRestriction.def("ElectricalCktRestriction", (Standard_Integer (IGESAppli_RegionRestriction::*)() const) &IGESAppli_RegionRestriction::ElectricalCktRestriction, "returns the Electrical circuitry restriction is 0, 1 or 2");
cls_IGESAppli_RegionRestriction.def_static("get_type_name_", (const char * (*)()) &IGESAppli_RegionRestriction::get_type_name, "None");
cls_IGESAppli_RegionRestriction.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_RegionRestriction::get_type_descriptor, "None");
cls_IGESAppli_RegionRestriction.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_RegionRestriction::*)() const) &IGESAppli_RegionRestriction::DynamicType, "None");

// CLASS: IGESAPPLI_SPECIFICMODULE
py::class_<IGESAppli_SpecificModule, opencascade::handle<IGESAppli_SpecificModule>, IGESData_SpecificModule> cls_IGESAppli_SpecificModule(mod, "IGESAppli_SpecificModule", "Defines Services attached to IGES Entities : Dump & OwnCorrect, for IGESAppli");

// Constructors
cls_IGESAppli_SpecificModule.def(py::init<>());

// Methods
cls_IGESAppli_SpecificModule.def("OwnDump", (void (IGESAppli_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_SpecificModule::OwnDump, "Specific Dump (own parameters) for IGESAppli", py::arg("CN"), py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));
cls_IGESAppli_SpecificModule.def("OwnCorrect", (Standard_Boolean (IGESAppli_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESAppli_SpecificModule::OwnCorrect, "---Purpose", py::arg("CN"), py::arg("ent"));
cls_IGESAppli_SpecificModule.def_static("get_type_name_", (const char * (*)()) &IGESAppli_SpecificModule::get_type_name, "None");
cls_IGESAppli_SpecificModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESAppli_SpecificModule::get_type_descriptor, "None");
cls_IGESAppli_SpecificModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESAppli_SpecificModule::*)() const) &IGESAppli_SpecificModule::DynamicType, "None");

// CLASS: IGESAPPLI_TOOLDRILLEDHOLE
py::class_<IGESAppli_ToolDrilledHole> cls_IGESAppli_ToolDrilledHole(mod, "IGESAppli_ToolDrilledHole", "Tool to work on a DrilledHole. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolDrilledHole.def(py::init<>());

// Methods
// cls_IGESAppli_ToolDrilledHole.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolDrilledHole::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolDrilledHole.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolDrilledHole::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolDrilledHole.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolDrilledHole::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolDrilledHole.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolDrilledHole::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolDrilledHole.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolDrilledHole::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolDrilledHole.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolDrilledHole::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolDrilledHole.def("ReadOwnParams", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolDrilledHole::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolDrilledHole.def("WriteOwnParams", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, IGESData_IGESWriter &) const) &IGESAppli_ToolDrilledHole::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolDrilledHole.def("OwnShared", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, Interface_EntityIterator &) const) &IGESAppli_ToolDrilledHole::OwnShared, "Lists the Entities shared by a DrilledHole <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolDrilledHole.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &) const) &IGESAppli_ToolDrilledHole::OwnCorrect, "Sets automatic unambiguous Correction on a DrilledHole (NbPropertyValues forced to 5, Level cleared if Subordinate != 0)", py::arg("ent"));
cls_IGESAppli_ToolDrilledHole.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &) const) &IGESAppli_ToolDrilledHole::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolDrilledHole.def("OwnCheck", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolDrilledHole::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolDrilledHole.def("OwnCopy", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, const opencascade::handle<IGESAppli_DrilledHole> &, Interface_CopyTool &) const) &IGESAppli_ToolDrilledHole::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolDrilledHole.def("OwnDump", (void (IGESAppli_ToolDrilledHole::*)(const opencascade::handle<IGESAppli_DrilledHole> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolDrilledHole::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLELEMENTRESULTS
py::class_<IGESAppli_ToolElementResults> cls_IGESAppli_ToolElementResults(mod, "IGESAppli_ToolElementResults", "Tool to work on a ElementResults. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolElementResults.def(py::init<>());

// Methods
// cls_IGESAppli_ToolElementResults.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolElementResults::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolElementResults.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolElementResults::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolElementResults.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolElementResults::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolElementResults.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolElementResults::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolElementResults.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolElementResults::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolElementResults.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolElementResults::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolElementResults.def("ReadOwnParams", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolElementResults::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolElementResults.def("WriteOwnParams", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, IGESData_IGESWriter &) const) &IGESAppli_ToolElementResults::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolElementResults.def("OwnShared", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, Interface_EntityIterator &) const) &IGESAppli_ToolElementResults::OwnShared, "Lists the Entities shared by a ElementResults <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolElementResults.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &) const) &IGESAppli_ToolElementResults::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolElementResults.def("OwnCheck", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolElementResults::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolElementResults.def("OwnCopy", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, const opencascade::handle<IGESAppli_ElementResults> &, Interface_CopyTool &) const) &IGESAppli_ToolElementResults::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolElementResults.def("OwnDump", (void (IGESAppli_ToolElementResults::*)(const opencascade::handle<IGESAppli_ElementResults> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolElementResults::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLFINITEELEMENT
py::class_<IGESAppli_ToolFiniteElement> cls_IGESAppli_ToolFiniteElement(mod, "IGESAppli_ToolFiniteElement", "Tool to work on a FiniteElement. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolFiniteElement.def(py::init<>());

// Methods
// cls_IGESAppli_ToolFiniteElement.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolFiniteElement::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolFiniteElement.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolFiniteElement::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFiniteElement.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolFiniteElement::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolFiniteElement.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolFiniteElement::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFiniteElement.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolFiniteElement::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolFiniteElement.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolFiniteElement::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolFiniteElement.def("ReadOwnParams", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolFiniteElement::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolFiniteElement.def("WriteOwnParams", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, IGESData_IGESWriter &) const) &IGESAppli_ToolFiniteElement::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolFiniteElement.def("OwnShared", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, Interface_EntityIterator &) const) &IGESAppli_ToolFiniteElement::OwnShared, "Lists the Entities shared by a FiniteElement <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolFiniteElement.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &) const) &IGESAppli_ToolFiniteElement::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolFiniteElement.def("OwnCheck", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolFiniteElement::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolFiniteElement.def("OwnCopy", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, const opencascade::handle<IGESAppli_FiniteElement> &, Interface_CopyTool &) const) &IGESAppli_ToolFiniteElement::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolFiniteElement.def("OwnDump", (void (IGESAppli_ToolFiniteElement::*)(const opencascade::handle<IGESAppli_FiniteElement> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolFiniteElement::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLFLOW
py::class_<IGESAppli_ToolFlow> cls_IGESAppli_ToolFlow(mod, "IGESAppli_ToolFlow", "Tool to work on a Flow. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolFlow.def(py::init<>());

// Methods
// cls_IGESAppli_ToolFlow.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolFlow::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolFlow.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolFlow::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFlow.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolFlow::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolFlow.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolFlow::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFlow.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolFlow::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolFlow.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolFlow::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolFlow.def("ReadOwnParams", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolFlow::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolFlow.def("WriteOwnParams", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, IGESData_IGESWriter &) const) &IGESAppli_ToolFlow::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolFlow.def("OwnShared", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, Interface_EntityIterator &) const) &IGESAppli_ToolFlow::OwnShared, "Lists the Entities shared by a Flow <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolFlow.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &) const) &IGESAppli_ToolFlow::OwnCorrect, "Sets automatic unambiguous Correction on a Flow (NbContextFlags forced to 2)", py::arg("ent"));
cls_IGESAppli_ToolFlow.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &) const) &IGESAppli_ToolFlow::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolFlow.def("OwnCheck", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolFlow::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolFlow.def("OwnCopy", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, const opencascade::handle<IGESAppli_Flow> &, Interface_CopyTool &) const) &IGESAppli_ToolFlow::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolFlow.def("OwnDump", (void (IGESAppli_ToolFlow::*)(const opencascade::handle<IGESAppli_Flow> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolFlow::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLFLOWLINESPEC
py::class_<IGESAppli_ToolFlowLineSpec> cls_IGESAppli_ToolFlowLineSpec(mod, "IGESAppli_ToolFlowLineSpec", "Tool to work on a FlowLineSpec. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolFlowLineSpec.def(py::init<>());

// Methods
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolFlowLineSpec::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolFlowLineSpec::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolFlowLineSpec::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolFlowLineSpec::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolFlowLineSpec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolFlowLineSpec.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolFlowLineSpec::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolFlowLineSpec.def("ReadOwnParams", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolFlowLineSpec::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolFlowLineSpec.def("WriteOwnParams", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, IGESData_IGESWriter &) const) &IGESAppli_ToolFlowLineSpec::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolFlowLineSpec.def("OwnShared", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, Interface_EntityIterator &) const) &IGESAppli_ToolFlowLineSpec::OwnShared, "Lists the Entities shared by a FlowLineSpec <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolFlowLineSpec.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &) const) &IGESAppli_ToolFlowLineSpec::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolFlowLineSpec.def("OwnCheck", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolFlowLineSpec::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolFlowLineSpec.def("OwnCopy", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, const opencascade::handle<IGESAppli_FlowLineSpec> &, Interface_CopyTool &) const) &IGESAppli_ToolFlowLineSpec::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolFlowLineSpec.def("OwnDump", (void (IGESAppli_ToolFlowLineSpec::*)(const opencascade::handle<IGESAppli_FlowLineSpec> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolFlowLineSpec::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLLEVELFUNCTION
py::class_<IGESAppli_ToolLevelFunction> cls_IGESAppli_ToolLevelFunction(mod, "IGESAppli_ToolLevelFunction", "Tool to work on a LevelFunction. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolLevelFunction.def(py::init<>());

// Methods
// cls_IGESAppli_ToolLevelFunction.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolLevelFunction::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolLevelFunction.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolLevelFunction::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLevelFunction.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolLevelFunction::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolLevelFunction.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolLevelFunction::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLevelFunction.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolLevelFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolLevelFunction.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolLevelFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolLevelFunction.def("ReadOwnParams", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolLevelFunction::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolLevelFunction.def("WriteOwnParams", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, IGESData_IGESWriter &) const) &IGESAppli_ToolLevelFunction::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolLevelFunction.def("OwnShared", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, Interface_EntityIterator &) const) &IGESAppli_ToolLevelFunction::OwnShared, "Lists the Entities shared by a LevelFunction <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolLevelFunction.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &) const) &IGESAppli_ToolLevelFunction::OwnCorrect, "Sets automatic unambiguous Correction on a LevelFunction (NbPropertyValues forced to 2)", py::arg("ent"));
cls_IGESAppli_ToolLevelFunction.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &) const) &IGESAppli_ToolLevelFunction::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolLevelFunction.def("OwnCheck", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolLevelFunction::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolLevelFunction.def("OwnCopy", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, const opencascade::handle<IGESAppli_LevelFunction> &, Interface_CopyTool &) const) &IGESAppli_ToolLevelFunction::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolLevelFunction.def("OwnDump", (void (IGESAppli_ToolLevelFunction::*)(const opencascade::handle<IGESAppli_LevelFunction> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolLevelFunction::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLLEVELTOPWBLAYERMAP
py::class_<IGESAppli_ToolLevelToPWBLayerMap> cls_IGESAppli_ToolLevelToPWBLayerMap(mod, "IGESAppli_ToolLevelToPWBLayerMap", "Tool to work on a LevelToPWBLayerMap. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolLevelToPWBLayerMap.def(py::init<>());

// Methods
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolLevelToPWBLayerMap::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolLevelToPWBLayerMap::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolLevelToPWBLayerMap::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolLevelToPWBLayerMap::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolLevelToPWBLayerMap::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolLevelToPWBLayerMap.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolLevelToPWBLayerMap::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("ReadOwnParams", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolLevelToPWBLayerMap::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("WriteOwnParams", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, IGESData_IGESWriter &) const) &IGESAppli_ToolLevelToPWBLayerMap::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("OwnShared", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, Interface_EntityIterator &) const) &IGESAppli_ToolLevelToPWBLayerMap::OwnShared, "Lists the Entities shared by a LevelToPWBLayerMap <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &) const) &IGESAppli_ToolLevelToPWBLayerMap::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("OwnCheck", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolLevelToPWBLayerMap::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("OwnCopy", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, Interface_CopyTool &) const) &IGESAppli_ToolLevelToPWBLayerMap::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolLevelToPWBLayerMap.def("OwnDump", (void (IGESAppli_ToolLevelToPWBLayerMap::*)(const opencascade::handle<IGESAppli_LevelToPWBLayerMap> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolLevelToPWBLayerMap::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLLINEWIDENING
py::class_<IGESAppli_ToolLineWidening> cls_IGESAppli_ToolLineWidening(mod, "IGESAppli_ToolLineWidening", "Tool to work on a LineWidening. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolLineWidening.def(py::init<>());

// Methods
// cls_IGESAppli_ToolLineWidening.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolLineWidening::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolLineWidening.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolLineWidening::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLineWidening.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolLineWidening::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolLineWidening.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolLineWidening::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolLineWidening.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolLineWidening::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolLineWidening.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolLineWidening::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolLineWidening.def("ReadOwnParams", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolLineWidening::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolLineWidening.def("WriteOwnParams", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, IGESData_IGESWriter &) const) &IGESAppli_ToolLineWidening::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolLineWidening.def("OwnShared", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, Interface_EntityIterator &) const) &IGESAppli_ToolLineWidening::OwnShared, "Lists the Entities shared by a LineWidening <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolLineWidening.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &) const) &IGESAppli_ToolLineWidening::OwnCorrect, "Sets automatic unambiguous Correction on a LineWidening (NbPropertyValues forced to 5, Level cleared if Subordinate != 0)", py::arg("ent"));
cls_IGESAppli_ToolLineWidening.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &) const) &IGESAppli_ToolLineWidening::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolLineWidening.def("OwnCheck", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolLineWidening::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolLineWidening.def("OwnCopy", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, const opencascade::handle<IGESAppli_LineWidening> &, Interface_CopyTool &) const) &IGESAppli_ToolLineWidening::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolLineWidening.def("OwnDump", (void (IGESAppli_ToolLineWidening::*)(const opencascade::handle<IGESAppli_LineWidening> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolLineWidening::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLNODALCONSTRAINT
py::class_<IGESAppli_ToolNodalConstraint> cls_IGESAppli_ToolNodalConstraint(mod, "IGESAppli_ToolNodalConstraint", "Tool to work on a NodalConstraint. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolNodalConstraint.def(py::init<>());

// Methods
// cls_IGESAppli_ToolNodalConstraint.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolNodalConstraint::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalConstraint.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolNodalConstraint::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalConstraint.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolNodalConstraint::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalConstraint.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolNodalConstraint::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalConstraint.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolNodalConstraint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolNodalConstraint.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolNodalConstraint::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolNodalConstraint.def("ReadOwnParams", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolNodalConstraint::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolNodalConstraint.def("WriteOwnParams", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, IGESData_IGESWriter &) const) &IGESAppli_ToolNodalConstraint::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolNodalConstraint.def("OwnShared", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, Interface_EntityIterator &) const) &IGESAppli_ToolNodalConstraint::OwnShared, "Lists the Entities shared by a NodalConstraint <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolNodalConstraint.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &) const) &IGESAppli_ToolNodalConstraint::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolNodalConstraint.def("OwnCheck", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolNodalConstraint::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolNodalConstraint.def("OwnCopy", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, const opencascade::handle<IGESAppli_NodalConstraint> &, Interface_CopyTool &) const) &IGESAppli_ToolNodalConstraint::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolNodalConstraint.def("OwnDump", (void (IGESAppli_ToolNodalConstraint::*)(const opencascade::handle<IGESAppli_NodalConstraint> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolNodalConstraint::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLNODALDISPLANDROT
py::class_<IGESAppli_ToolNodalDisplAndRot> cls_IGESAppli_ToolNodalDisplAndRot(mod, "IGESAppli_ToolNodalDisplAndRot", "Tool to work on a NodalDisplAndRot. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolNodalDisplAndRot.def(py::init<>());

// Methods
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolNodalDisplAndRot::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolNodalDisplAndRot::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolNodalDisplAndRot::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolNodalDisplAndRot::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolNodalDisplAndRot::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolNodalDisplAndRot.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolNodalDisplAndRot::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolNodalDisplAndRot.def("ReadOwnParams", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolNodalDisplAndRot::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolNodalDisplAndRot.def("WriteOwnParams", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, IGESData_IGESWriter &) const) &IGESAppli_ToolNodalDisplAndRot::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolNodalDisplAndRot.def("OwnShared", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, Interface_EntityIterator &) const) &IGESAppli_ToolNodalDisplAndRot::OwnShared, "Lists the Entities shared by a NodalDisplAndRot <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolNodalDisplAndRot.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &) const) &IGESAppli_ToolNodalDisplAndRot::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolNodalDisplAndRot.def("OwnCheck", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolNodalDisplAndRot::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolNodalDisplAndRot.def("OwnCopy", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, const opencascade::handle<IGESAppli_NodalDisplAndRot> &, Interface_CopyTool &) const) &IGESAppli_ToolNodalDisplAndRot::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolNodalDisplAndRot.def("OwnDump", (void (IGESAppli_ToolNodalDisplAndRot::*)(const opencascade::handle<IGESAppli_NodalDisplAndRot> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolNodalDisplAndRot::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLNODALRESULTS
py::class_<IGESAppli_ToolNodalResults> cls_IGESAppli_ToolNodalResults(mod, "IGESAppli_ToolNodalResults", "Tool to work on a NodalResults. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolNodalResults.def(py::init<>());

// Methods
// cls_IGESAppli_ToolNodalResults.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolNodalResults::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalResults.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolNodalResults::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalResults.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolNodalResults::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolNodalResults.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolNodalResults::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNodalResults.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolNodalResults::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolNodalResults.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolNodalResults::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolNodalResults.def("ReadOwnParams", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolNodalResults::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolNodalResults.def("WriteOwnParams", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, IGESData_IGESWriter &) const) &IGESAppli_ToolNodalResults::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolNodalResults.def("OwnShared", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, Interface_EntityIterator &) const) &IGESAppli_ToolNodalResults::OwnShared, "Lists the Entities shared by a NodalResults <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolNodalResults.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &) const) &IGESAppli_ToolNodalResults::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolNodalResults.def("OwnCheck", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolNodalResults::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolNodalResults.def("OwnCopy", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, const opencascade::handle<IGESAppli_NodalResults> &, Interface_CopyTool &) const) &IGESAppli_ToolNodalResults::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolNodalResults.def("OwnDump", (void (IGESAppli_ToolNodalResults::*)(const opencascade::handle<IGESAppli_NodalResults> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolNodalResults::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLNODE
py::class_<IGESAppli_ToolNode> cls_IGESAppli_ToolNode(mod, "IGESAppli_ToolNode", "Tool to work on a Node. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolNode.def(py::init<>());

// Methods
// cls_IGESAppli_ToolNode.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolNode::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolNode.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolNode::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNode.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolNode::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolNode.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolNode::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolNode.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolNode::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolNode.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolNode::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolNode.def("ReadOwnParams", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolNode::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolNode.def("WriteOwnParams", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, IGESData_IGESWriter &) const) &IGESAppli_ToolNode::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolNode.def("OwnShared", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, Interface_EntityIterator &) const) &IGESAppli_ToolNode::OwnShared, "Lists the Entities shared by a Node <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolNode.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &) const) &IGESAppli_ToolNode::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolNode.def("OwnCheck", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolNode::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolNode.def("OwnCopy", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, const opencascade::handle<IGESAppli_Node> &, Interface_CopyTool &) const) &IGESAppli_ToolNode::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolNode.def("OwnDump", (void (IGESAppli_ToolNode::*)(const opencascade::handle<IGESAppli_Node> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolNode::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLPARTNUMBER
py::class_<IGESAppli_ToolPartNumber> cls_IGESAppli_ToolPartNumber(mod, "IGESAppli_ToolPartNumber", "Tool to work on a PartNumber. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolPartNumber.def(py::init<>());

// Methods
// cls_IGESAppli_ToolPartNumber.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolPartNumber::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolPartNumber.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolPartNumber::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPartNumber.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolPartNumber::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolPartNumber.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolPartNumber::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPartNumber.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolPartNumber::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolPartNumber.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolPartNumber::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolPartNumber.def("ReadOwnParams", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolPartNumber::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolPartNumber.def("WriteOwnParams", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, IGESData_IGESWriter &) const) &IGESAppli_ToolPartNumber::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolPartNumber.def("OwnShared", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, Interface_EntityIterator &) const) &IGESAppli_ToolPartNumber::OwnShared, "Lists the Entities shared by a PartNumber <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolPartNumber.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &) const) &IGESAppli_ToolPartNumber::OwnCorrect, "Sets automatic unambiguous Correction on a PartNumber (NbPropertyValues forced to 4)", py::arg("ent"));
cls_IGESAppli_ToolPartNumber.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &) const) &IGESAppli_ToolPartNumber::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolPartNumber.def("OwnCheck", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolPartNumber::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolPartNumber.def("OwnCopy", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, const opencascade::handle<IGESAppli_PartNumber> &, Interface_CopyTool &) const) &IGESAppli_ToolPartNumber::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolPartNumber.def("OwnDump", (void (IGESAppli_ToolPartNumber::*)(const opencascade::handle<IGESAppli_PartNumber> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolPartNumber::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLPINNUMBER
py::class_<IGESAppli_ToolPinNumber> cls_IGESAppli_ToolPinNumber(mod, "IGESAppli_ToolPinNumber", "Tool to work on a PinNumber. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolPinNumber.def(py::init<>());

// Methods
// cls_IGESAppli_ToolPinNumber.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolPinNumber::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolPinNumber.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolPinNumber::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPinNumber.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolPinNumber::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolPinNumber.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolPinNumber::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPinNumber.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolPinNumber::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolPinNumber.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolPinNumber::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolPinNumber.def("ReadOwnParams", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolPinNumber::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolPinNumber.def("WriteOwnParams", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, IGESData_IGESWriter &) const) &IGESAppli_ToolPinNumber::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolPinNumber.def("OwnShared", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, Interface_EntityIterator &) const) &IGESAppli_ToolPinNumber::OwnShared, "Lists the Entities shared by a PinNumber <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolPinNumber.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &) const) &IGESAppli_ToolPinNumber::OwnCorrect, "Sets automatic unambiguous Correction on a PinNumber (Level cleared in D.E. if Subordinate != 0)", py::arg("ent"));
cls_IGESAppli_ToolPinNumber.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &) const) &IGESAppli_ToolPinNumber::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolPinNumber.def("OwnCheck", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolPinNumber::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolPinNumber.def("OwnCopy", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, const opencascade::handle<IGESAppli_PinNumber> &, Interface_CopyTool &) const) &IGESAppli_ToolPinNumber::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolPinNumber.def("OwnDump", (void (IGESAppli_ToolPinNumber::*)(const opencascade::handle<IGESAppli_PinNumber> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolPinNumber::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLPIPINGFLOW
py::class_<IGESAppli_ToolPipingFlow> cls_IGESAppli_ToolPipingFlow(mod, "IGESAppli_ToolPipingFlow", "Tool to work on a PipingFlow. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolPipingFlow.def(py::init<>());

// Methods
// cls_IGESAppli_ToolPipingFlow.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolPipingFlow::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolPipingFlow.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolPipingFlow::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPipingFlow.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolPipingFlow::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolPipingFlow.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolPipingFlow::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPipingFlow.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolPipingFlow::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolPipingFlow.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolPipingFlow::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolPipingFlow.def("ReadOwnParams", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolPipingFlow::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolPipingFlow.def("WriteOwnParams", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, IGESData_IGESWriter &) const) &IGESAppli_ToolPipingFlow::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolPipingFlow.def("OwnShared", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, Interface_EntityIterator &) const) &IGESAppli_ToolPipingFlow::OwnShared, "Lists the Entities shared by a PipingFlow <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolPipingFlow.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &) const) &IGESAppli_ToolPipingFlow::OwnCorrect, "Sets automatic unambiguous Correction on a PipingFlow (NbContextFlags forced to 1)", py::arg("ent"));
cls_IGESAppli_ToolPipingFlow.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &) const) &IGESAppli_ToolPipingFlow::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolPipingFlow.def("OwnCheck", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolPipingFlow::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolPipingFlow.def("OwnCopy", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, const opencascade::handle<IGESAppli_PipingFlow> &, Interface_CopyTool &) const) &IGESAppli_ToolPipingFlow::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolPipingFlow.def("OwnDump", (void (IGESAppli_ToolPipingFlow::*)(const opencascade::handle<IGESAppli_PipingFlow> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolPipingFlow::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLPWBARTWORKSTACKUP
py::class_<IGESAppli_ToolPWBArtworkStackup> cls_IGESAppli_ToolPWBArtworkStackup(mod, "IGESAppli_ToolPWBArtworkStackup", "Tool to work on a PWBArtworkStackup. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolPWBArtworkStackup.def(py::init<>());

// Methods
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolPWBArtworkStackup::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolPWBArtworkStackup::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolPWBArtworkStackup::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolPWBArtworkStackup::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolPWBArtworkStackup::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolPWBArtworkStackup.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolPWBArtworkStackup::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolPWBArtworkStackup.def("ReadOwnParams", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolPWBArtworkStackup::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolPWBArtworkStackup.def("WriteOwnParams", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, IGESData_IGESWriter &) const) &IGESAppli_ToolPWBArtworkStackup::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolPWBArtworkStackup.def("OwnShared", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, Interface_EntityIterator &) const) &IGESAppli_ToolPWBArtworkStackup::OwnShared, "Lists the Entities shared by a PWBArtworkStackup <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolPWBArtworkStackup.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &) const) &IGESAppli_ToolPWBArtworkStackup::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolPWBArtworkStackup.def("OwnCheck", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolPWBArtworkStackup::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolPWBArtworkStackup.def("OwnCopy", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, const opencascade::handle<IGESAppli_PWBArtworkStackup> &, Interface_CopyTool &) const) &IGESAppli_ToolPWBArtworkStackup::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolPWBArtworkStackup.def("OwnDump", (void (IGESAppli_ToolPWBArtworkStackup::*)(const opencascade::handle<IGESAppli_PWBArtworkStackup> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolPWBArtworkStackup::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLPWBDRILLEDHOLE
py::class_<IGESAppli_ToolPWBDrilledHole> cls_IGESAppli_ToolPWBDrilledHole(mod, "IGESAppli_ToolPWBDrilledHole", "Tool to work on a PWBDrilledHole. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolPWBDrilledHole.def(py::init<>());

// Methods
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolPWBDrilledHole::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolPWBDrilledHole::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolPWBDrilledHole::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolPWBDrilledHole::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolPWBDrilledHole::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolPWBDrilledHole.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolPWBDrilledHole::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolPWBDrilledHole.def("ReadOwnParams", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolPWBDrilledHole::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolPWBDrilledHole.def("WriteOwnParams", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, IGESData_IGESWriter &) const) &IGESAppli_ToolPWBDrilledHole::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolPWBDrilledHole.def("OwnShared", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, Interface_EntityIterator &) const) &IGESAppli_ToolPWBDrilledHole::OwnShared, "Lists the Entities shared by a PWBDrilledHole <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolPWBDrilledHole.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &) const) &IGESAppli_ToolPWBDrilledHole::OwnCorrect, "Sets automatic unambiguous Correction on a PWBDrilledHole (NbPropertyValues forced to 3)", py::arg("ent"));
cls_IGESAppli_ToolPWBDrilledHole.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &) const) &IGESAppli_ToolPWBDrilledHole::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolPWBDrilledHole.def("OwnCheck", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolPWBDrilledHole::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolPWBDrilledHole.def("OwnCopy", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, const opencascade::handle<IGESAppli_PWBDrilledHole> &, Interface_CopyTool &) const) &IGESAppli_ToolPWBDrilledHole::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolPWBDrilledHole.def("OwnDump", (void (IGESAppli_ToolPWBDrilledHole::*)(const opencascade::handle<IGESAppli_PWBDrilledHole> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolPWBDrilledHole::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLREFERENCEDESIGNATOR
py::class_<IGESAppli_ToolReferenceDesignator> cls_IGESAppli_ToolReferenceDesignator(mod, "IGESAppli_ToolReferenceDesignator", "Tool to work on a ReferenceDesignator. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolReferenceDesignator.def(py::init<>());

// Methods
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolReferenceDesignator::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolReferenceDesignator::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolReferenceDesignator::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolReferenceDesignator::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolReferenceDesignator::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolReferenceDesignator.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolReferenceDesignator::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolReferenceDesignator.def("ReadOwnParams", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolReferenceDesignator::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolReferenceDesignator.def("WriteOwnParams", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, IGESData_IGESWriter &) const) &IGESAppli_ToolReferenceDesignator::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolReferenceDesignator.def("OwnShared", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, Interface_EntityIterator &) const) &IGESAppli_ToolReferenceDesignator::OwnShared, "Lists the Entities shared by a ReferenceDesignator <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolReferenceDesignator.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &) const) &IGESAppli_ToolReferenceDesignator::OwnCorrect, "Sets automatic unambiguous Correction on a ReferenceDesignator (NbPropertyValues forced to 1, Level cleared if Subordinate != 0)", py::arg("ent"));
cls_IGESAppli_ToolReferenceDesignator.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &) const) &IGESAppli_ToolReferenceDesignator::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolReferenceDesignator.def("OwnCheck", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolReferenceDesignator::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolReferenceDesignator.def("OwnCopy", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, const opencascade::handle<IGESAppli_ReferenceDesignator> &, Interface_CopyTool &) const) &IGESAppli_ToolReferenceDesignator::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolReferenceDesignator.def("OwnDump", (void (IGESAppli_ToolReferenceDesignator::*)(const opencascade::handle<IGESAppli_ReferenceDesignator> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolReferenceDesignator::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESAPPLI_TOOLREGIONRESTRICTION
py::class_<IGESAppli_ToolRegionRestriction> cls_IGESAppli_ToolRegionRestriction(mod, "IGESAppli_ToolRegionRestriction", "Tool to work on a RegionRestriction. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESAppli_ToolRegionRestriction.def(py::init<>());

// Methods
// cls_IGESAppli_ToolRegionRestriction.def_static("operator new_", (void * (*)(size_t)) &IGESAppli_ToolRegionRestriction::operator new, "None", py::arg("theSize"));
// cls_IGESAppli_ToolRegionRestriction.def_static("operator delete_", (void (*)(void *)) &IGESAppli_ToolRegionRestriction::operator delete, "None", py::arg("theAddress"));
// cls_IGESAppli_ToolRegionRestriction.def_static("operator new[]_", (void * (*)(size_t)) &IGESAppli_ToolRegionRestriction::operator new[], "None", py::arg("theSize"));
// cls_IGESAppli_ToolRegionRestriction.def_static("operator delete[]_", (void (*)(void *)) &IGESAppli_ToolRegionRestriction::operator delete[], "None", py::arg("theAddress"));
// cls_IGESAppli_ToolRegionRestriction.def_static("operator new_", (void * (*)(size_t, void *)) &IGESAppli_ToolRegionRestriction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESAppli_ToolRegionRestriction.def_static("operator delete_", (void (*)(void *, void *)) &IGESAppli_ToolRegionRestriction::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESAppli_ToolRegionRestriction.def("ReadOwnParams", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESAppli_ToolRegionRestriction::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESAppli_ToolRegionRestriction.def("WriteOwnParams", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, IGESData_IGESWriter &) const) &IGESAppli_ToolRegionRestriction::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESAppli_ToolRegionRestriction.def("OwnShared", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, Interface_EntityIterator &) const) &IGESAppli_ToolRegionRestriction::OwnShared, "Lists the Entities shared by a RegionRestriction <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESAppli_ToolRegionRestriction.def("OwnCorrect", (Standard_Boolean (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &) const) &IGESAppli_ToolRegionRestriction::OwnCorrect, "Sets automatic unambiguous Correction on a RegionRestriction (NbPropertyValues forced to 3, Level cleared if Subordinate != 0)", py::arg("ent"));
cls_IGESAppli_ToolRegionRestriction.def("DirChecker", (IGESData_DirChecker (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &) const) &IGESAppli_ToolRegionRestriction::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESAppli_ToolRegionRestriction.def("OwnCheck", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESAppli_ToolRegionRestriction::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESAppli_ToolRegionRestriction.def("OwnCopy", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, const opencascade::handle<IGESAppli_RegionRestriction> &, Interface_CopyTool &) const) &IGESAppli_ToolRegionRestriction::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESAppli_ToolRegionRestriction.def("OwnDump", (void (IGESAppli_ToolRegionRestriction::*)(const opencascade::handle<IGESAppli_RegionRestriction> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESAppli_ToolRegionRestriction::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));


}
