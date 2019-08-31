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
#include <IGESData_IGESEntity.hxx>
#include <gp_XYZ.hxx>
#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <TCollection_HAsciiString.hxx>
#include <IGESGraph_TextDisplayTemplate.hxx>
#include <gp_Pnt.hxx>
#include <IGESDraw_ConnectPoint.hxx>
#include <Standard_Type.hxx>
#include <NCollection_Array1.hxx>
#include <IGESDraw_Array1OfConnectPoint.hxx>
#include <Standard_Transient.hxx>
#include <Standard.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <IGESDraw_HArray1OfConnectPoint.hxx>
#include <IGESDraw_Protocol.hxx>
#include <IGESDraw_NetworkSubfigureDef.hxx>
#include <IGESDraw_ViewsVisible.hxx>
#include <IGESDraw_ViewsVisibleWithAttr.hxx>
#include <IGESDraw_LabelDisplay.hxx>
#include <IGESDraw_Planar.hxx>
#include <IGESDraw_SegmentedViewsVisible.hxx>
#include <IGESDraw_Drawing.hxx>
#include <IGESDraw_DrawingWithRotation.hxx>
#include <IGESDraw_View.hxx>
#include <IGESDraw_RectArraySubfigure.hxx>
#include <IGESDraw_CircArraySubfigure.hxx>
#include <IGESDraw_NetworkSubfigure.hxx>
#include <IGESDraw_PerspectiveView.hxx>
#include <IGESDraw_ToolConnectPoint.hxx>
#include <IGESDraw_ToolNetworkSubfigureDef.hxx>
#include <IGESDraw_ToolViewsVisible.hxx>
#include <IGESDraw_ToolViewsVisibleWithAttr.hxx>
#include <IGESDraw_ToolLabelDisplay.hxx>
#include <IGESDraw_ToolPlanar.hxx>
#include <IGESDraw_ToolSegmentedViewsVisible.hxx>
#include <IGESDraw_ToolDrawing.hxx>
#include <IGESDraw_ToolDrawingWithRotation.hxx>
#include <IGESDraw_ToolView.hxx>
#include <IGESDraw_ToolRectArraySubfigure.hxx>
#include <IGESDraw_ToolCircArraySubfigure.hxx>
#include <IGESDraw_ToolNetworkSubfigure.hxx>
#include <IGESDraw_ToolPerspectiveView.hxx>
#include <IGESDraw_ReadWriteModule.hxx>
#include <IGESDraw_GeneralModule.hxx>
#include <IGESDraw_SpecificModule.hxx>
#include <IGESDraw.hxx>
#include <IGESData_ViewKindEntity.hxx>
#include <IGESDraw_Array1OfViewKindEntity.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESDraw_HArray1OfViewKindEntity.hxx>
#include <TColgp_HArray1OfXY.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_XY.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <IGESData_GeneralModule.hxx>
#include <Interface_EntityIterator.hxx>
#include <IGESData_DirChecker.hxx>
#include <Interface_ShareTool.hxx>
#include <Interface_Check.hxx>
#include <Interface_CopyTool.hxx>
#include <IGESData_LabelDisplayEntity.hxx>
#include <TColgp_HArray1OfXYZ.hxx>
#include <IGESDimen_HArray1OfLeaderArrow.hxx>
#include <IGESDimen_LeaderArrow.hxx>
#include <gp_Vec.hxx>
#include <IGESData_TransfEntity.hxx>
#include <IGESGeom_TransformationMatrix.hxx>
#include <IGESData_Protocol.hxx>
#include <Interface_Protocol.hxx>
#include <IGESData_ReadWriteModule.hxx>
#include <IGESData_IGESReaderData.hxx>
#include <IGESData_ParamReader.hxx>
#include <IGESData_IGESWriter.hxx>
#include <IGESGraph_HArray1OfColor.hxx>
#include <IGESBasic_HArray1OfLineFontEntity.hxx>
#include <IGESGraph_Color.hxx>
#include <IGESData_LineFontEntity.hxx>
#include <IGESData_SpecificModule.hxx>
#include <IGESData_IGESDumper.hxx>
#include <Message_Messenger.hxx>
#include <IGESGeom_Plane.hxx>
#include <bind_NCollection_Array1.hxx>

PYBIND11_MODULE(IGESDraw, mod) {

py::module::import("OCCT.IGESData");
py::module::import("OCCT.gp");
py::module::import("OCCT.Standard");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.IGESGraph");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.Interface");
py::module::import("OCCT.IGESDimen");
py::module::import("OCCT.IGESGeom");
py::module::import("OCCT.IGESBasic");
py::module::import("OCCT.Message");

// CLASS: IGESDRAW_CONNECTPOINT
py::class_<IGESDraw_ConnectPoint, opencascade::handle<IGESDraw_ConnectPoint>, IGESData_IGESEntity> cls_IGESDraw_ConnectPoint(mod, "IGESDraw_ConnectPoint", "defines IGESConnectPoint, Type <132> Form Number <0> in package IGESDraw");

// Constructors
cls_IGESDraw_ConnectPoint.def(py::init<>());

// Methods
cls_IGESDraw_ConnectPoint.def("Init", (void (IGESDraw_ConnectPoint::*)(const gp_XYZ &, const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<IGESGraph_TextDisplayTemplate> &, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<IGESGraph_TextDisplayTemplate> &, const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &)) &IGESDraw_ConnectPoint::Init, "This method is used to set the fields of the class ConnectPoint - aPoint : A Coordinate point - aDisplaySymbol : Display symbol Geometry - aTypeFlag : Type of the connection - aFunctionFlag : Function flag for the connection - aFunctionIdentifier : Connection Point Function Identifier - anIdentifierTemplate : Connection Point Function Template - aFunctionName : Connection Point Function Name - aFunctionTemplate : Connection Point Function Template - aPointIdentifier : Unique Connect Point Identifier - aFunctionCode : Connect Point Function Code - aSwapFlag : Connect Point Swap Flag - anOwnerSubfigure : Pointer to the 'Owner' Entity", py::arg("aPoint"), py::arg("aDisplaySymbol"), py::arg("aTypeFlag"), py::arg("aFunctionFlag"), py::arg("aFunctionIdentifier"), py::arg("anIdentifierTemplate"), py::arg("aFunctionName"), py::arg("aFunctionTemplate"), py::arg("aPointIdentifier"), py::arg("aFunctionCode"), py::arg("aSwapFlag"), py::arg("anOwnerSubfigure"));
cls_IGESDraw_ConnectPoint.def("Point", (gp_Pnt (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::Point, "returns the coordinate of the connection point");
cls_IGESDraw_ConnectPoint.def("TransformedPoint", (gp_Pnt (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::TransformedPoint, "returns the Transformed coordinate of the connection point");
cls_IGESDraw_ConnectPoint.def("HasDisplaySymbol", (Standard_Boolean (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::HasDisplaySymbol, "returns True if Display symbol is specified else returns False");
cls_IGESDraw_ConnectPoint.def("DisplaySymbol", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::DisplaySymbol, "if display symbol specified returns display symbol geometric entity else returns NULL Handle");
cls_IGESDraw_ConnectPoint.def("TypeFlag", (Standard_Integer (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::TypeFlag, "return value specifies a particular type of connection : Type Flag = 0 : Not Specified(default) 1 : Nonspecific logical point of connection 2 : Nonspecific physical point of connection 101 : Logical component pin 102 : Logical part connector 103 : Logical offpage connector 104 : Logical global signal connector 201 : Physical PWA surface mount pin 202 : Physical PWA blind pin 203 : Physical PWA thru-pin 5001-9999 : Implementor defined.");
cls_IGESDraw_ConnectPoint.def("FunctionFlag", (Standard_Integer (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::FunctionFlag, "returns Function Code that specifies a particular function for the ECO576 connection : e.g., Function Flag = 0 : Unspecified(default) = 1 : Electrical Signal = 2 : Fluid flow Signal");
cls_IGESDraw_ConnectPoint.def("FunctionIdentifier", (opencascade::handle<TCollection_HAsciiString> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::FunctionIdentifier, "return HAsciiString identifying Pin Number or Nozzle Label etc.");
cls_IGESDraw_ConnectPoint.def("HasIdentifierTemplate", (Standard_Boolean (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::HasIdentifierTemplate, "returns True if Text Display Template is specified for Identifier else returns False");
cls_IGESDraw_ConnectPoint.def("IdentifierTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::IdentifierTemplate, "if Text Display Template for the Function Identifier is defined, returns TestDisplayTemplate else returns NULL Handle");
cls_IGESDraw_ConnectPoint.def("FunctionName", (opencascade::handle<TCollection_HAsciiString> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::FunctionName, "returns Connection Point Function Name");
cls_IGESDraw_ConnectPoint.def("HasFunctionTemplate", (Standard_Boolean (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::HasFunctionTemplate, "returns True if Text Display Template is specified for Function Name else returns False");
cls_IGESDraw_ConnectPoint.def("FunctionTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::FunctionTemplate, "if Text Display Template for the Function Name is defined, returns TestDisplayTemplate else returns NULL Handle");
cls_IGESDraw_ConnectPoint.def("PointIdentifier", (Standard_Integer (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::PointIdentifier, "returns the Unique Connect Point Identifier");
cls_IGESDraw_ConnectPoint.def("FunctionCode", (Standard_Integer (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::FunctionCode, "returns the Connect Point Function Code");
cls_IGESDraw_ConnectPoint.def("SwapFlag", (Standard_Boolean (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::SwapFlag, "return value = 0 : Connect point may be swapped(default) = 1 : Connect point may not be swapped");
cls_IGESDraw_ConnectPoint.def("HasOwnerSubfigure", (Standard_Boolean (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::HasOwnerSubfigure, "returns True if Network Subfigure Instance/Definition Entity is specified else returns False");
cls_IGESDraw_ConnectPoint.def("OwnerSubfigure", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::OwnerSubfigure, "returns 'owner' Network Subfigure Instance Entity, or Network Subfigure Definition Entity, or NULL Handle.");
cls_IGESDraw_ConnectPoint.def_static("get_type_name_", (const char * (*)()) &IGESDraw_ConnectPoint::get_type_name, "None");
cls_IGESDraw_ConnectPoint.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_ConnectPoint::get_type_descriptor, "None");
cls_IGESDraw_ConnectPoint.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_ConnectPoint::*)() const) &IGESDraw_ConnectPoint::DynamicType, "None");

// TYPEDEF: IGESDRAW_ARRAY1OFCONNECTPOINT
bind_NCollection_Array1<opencascade::handle<IGESDraw_ConnectPoint> >(mod, "IGESDraw_Array1OfConnectPoint", py::module_local(false));

// CLASS: IGESDRAW_HARRAY1OFCONNECTPOINT
py::class_<IGESDraw_HArray1OfConnectPoint, opencascade::handle<IGESDraw_HArray1OfConnectPoint>, Standard_Transient> cls_IGESDraw_HArray1OfConnectPoint(mod, "IGESDraw_HArray1OfConnectPoint", "None", py::multiple_inheritance());

// Constructors
cls_IGESDraw_HArray1OfConnectPoint.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESDraw_HArray1OfConnectPoint.def(py::init<const Standard_Integer, const Standard_Integer, const IGESDraw_Array1OfConnectPoint::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESDraw_HArray1OfConnectPoint.def(py::init<const IGESDraw_Array1OfConnectPoint &>(), py::arg("theOther"));

// Methods
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_HArray1OfConnectPoint::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator delete_", (void (*)(void *)) &IGESDraw_HArray1OfConnectPoint::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_HArray1OfConnectPoint::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_HArray1OfConnectPoint::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_HArray1OfConnectPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_HArray1OfConnectPoint::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESDraw_HArray1OfConnectPoint::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESDraw_HArray1OfConnectPoint.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESDraw_HArray1OfConnectPoint::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESDraw_HArray1OfConnectPoint.def("Array1", (const IGESDraw_Array1OfConnectPoint & (IGESDraw_HArray1OfConnectPoint::*)() const) &IGESDraw_HArray1OfConnectPoint::Array1, "None");
cls_IGESDraw_HArray1OfConnectPoint.def("ChangeArray1", (IGESDraw_Array1OfConnectPoint & (IGESDraw_HArray1OfConnectPoint::*)()) &IGESDraw_HArray1OfConnectPoint::ChangeArray1, "None");
cls_IGESDraw_HArray1OfConnectPoint.def_static("get_type_name_", (const char * (*)()) &IGESDraw_HArray1OfConnectPoint::get_type_name, "None");
cls_IGESDraw_HArray1OfConnectPoint.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_HArray1OfConnectPoint::get_type_descriptor, "None");
cls_IGESDraw_HArray1OfConnectPoint.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_HArray1OfConnectPoint::*)() const) &IGESDraw_HArray1OfConnectPoint::DynamicType, "None");

// CLASS: IGESDRAW
py::class_<IGESDraw> cls_IGESDraw(mod, "IGESDraw", "This package contains the group of classes necessary for Structure Entities implied in Drawings and Structured Graphics (Sets for drawing, Drawings and Views).");

// Methods
// cls_IGESDraw.def_static("operator new_", (void * (*)(size_t)) &IGESDraw::operator new, "None", py::arg("theSize"));
// cls_IGESDraw.def_static("operator delete_", (void (*)(void *)) &IGESDraw::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw.def_static("Init_", (void (*)()) &IGESDraw::Init, "Prepares dynamic data (Protocol, Modules) for this package");
cls_IGESDraw.def_static("Protocol_", (opencascade::handle<IGESDraw_Protocol> (*)()) &IGESDraw::Protocol, "Returns the Protocol for this Package");

// TYPEDEF: IGESDRAW_ARRAY1OFVIEWKINDENTITY
bind_NCollection_Array1<opencascade::handle<IGESData_ViewKindEntity> >(mod, "IGESDraw_Array1OfViewKindEntity", py::module_local(false));

// CLASS: IGESDRAW_CIRCARRAYSUBFIGURE
py::class_<IGESDraw_CircArraySubfigure, opencascade::handle<IGESDraw_CircArraySubfigure>, IGESData_IGESEntity> cls_IGESDraw_CircArraySubfigure(mod, "IGESDraw_CircArraySubfigure", "Defines IGES Circular Array Subfigure Instance Entity, Type <414> Form Number <0> in package IGESDraw");

// Constructors
cls_IGESDraw_CircArraySubfigure.def(py::init<>());

// Methods
cls_IGESDraw_CircArraySubfigure.def("Init", (void (IGESDraw_CircArraySubfigure::*)(const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const gp_XYZ &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &)) &IGESDraw_CircArraySubfigure::Init, "This method is used to set the fields of the class CircArraySubfigure - aBase : Base entity - aNumLocs : Total number of possible instance locations - aCenter : Coordinates of Center of imaginary circle - aRadius : Radius of imaginary circle - aStAngle : Start angle in radians - aDelAngle : Delta angle in radians - aFlag : DO-DON'T flag to control which portion to display - allNumPos : All position to be or not to be processed", py::arg("aBase"), py::arg("aNumLocs"), py::arg("aCenter"), py::arg("aRadius"), py::arg("aStAngle"), py::arg("aDelAngle"), py::arg("aFlag"), py::arg("allNumPos"));
cls_IGESDraw_CircArraySubfigure.def("BaseEntity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::BaseEntity, "returns the base entity, copies of which are produced");
cls_IGESDraw_CircArraySubfigure.def("NbLocations", (Standard_Integer (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::NbLocations, "returns total number of possible instance locations");
cls_IGESDraw_CircArraySubfigure.def("CenterPoint", (gp_Pnt (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::CenterPoint, "returns the center of the imaginary circle");
cls_IGESDraw_CircArraySubfigure.def("TransformedCenterPoint", (gp_Pnt (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::TransformedCenterPoint, "returns the Transformed center of the imaginary circle");
cls_IGESDraw_CircArraySubfigure.def("CircleRadius", (Standard_Real (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::CircleRadius, "returns the radius of the imaginary circle");
cls_IGESDraw_CircArraySubfigure.def("StartAngle", (Standard_Real (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::StartAngle, "returns the start angle in radians");
cls_IGESDraw_CircArraySubfigure.def("DeltaAngle", (Standard_Real (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::DeltaAngle, "returns the delta angle in radians");
cls_IGESDraw_CircArraySubfigure.def("ListCount", (Standard_Integer (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::ListCount, "returns 0 if all elements to be displayed");
cls_IGESDraw_CircArraySubfigure.def("DisplayFlag", (Standard_Boolean (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::DisplayFlag, "returns True if (ListCount = 0) all elements are to be displayed");
cls_IGESDraw_CircArraySubfigure.def("DoDontFlag", (Standard_Boolean (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::DoDontFlag, "returns 0 if half or fewer of the elements of the array are defined 1 if half or more of the elements are defined");
cls_IGESDraw_CircArraySubfigure.def("PositionNum", (Standard_Boolean (IGESDraw_CircArraySubfigure::*)(const Standard_Integer) const) &IGESDraw_CircArraySubfigure::PositionNum, "returns whether Index is to be processed (DO) or not to be processed(DON'T) if (ListCount = 0) return theDoDontFlag raises exception if Index <= 0 or Index > ListCount().", py::arg("Index"));
cls_IGESDraw_CircArraySubfigure.def("ListPosition", (Standard_Integer (IGESDraw_CircArraySubfigure::*)(const Standard_Integer) const) &IGESDraw_CircArraySubfigure::ListPosition, "returns the Index'th value position raises exception if Index <= 0 or Index > ListCount().", py::arg("Index"));
cls_IGESDraw_CircArraySubfigure.def_static("get_type_name_", (const char * (*)()) &IGESDraw_CircArraySubfigure::get_type_name, "None");
cls_IGESDraw_CircArraySubfigure.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_CircArraySubfigure::get_type_descriptor, "None");
cls_IGESDraw_CircArraySubfigure.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_CircArraySubfigure::*)() const) &IGESDraw_CircArraySubfigure::DynamicType, "None");

// CLASS: IGESDRAW_HARRAY1OFVIEWKINDENTITY
py::class_<IGESDraw_HArray1OfViewKindEntity, opencascade::handle<IGESDraw_HArray1OfViewKindEntity>, Standard_Transient> cls_IGESDraw_HArray1OfViewKindEntity(mod, "IGESDraw_HArray1OfViewKindEntity", "None", py::multiple_inheritance());

// Constructors
cls_IGESDraw_HArray1OfViewKindEntity.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESDraw_HArray1OfViewKindEntity.def(py::init<const Standard_Integer, const Standard_Integer, const IGESDraw_Array1OfViewKindEntity::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESDraw_HArray1OfViewKindEntity.def(py::init<const IGESDraw_Array1OfViewKindEntity &>(), py::arg("theOther"));

// Methods
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_HArray1OfViewKindEntity::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator delete_", (void (*)(void *)) &IGESDraw_HArray1OfViewKindEntity::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_HArray1OfViewKindEntity::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_HArray1OfViewKindEntity::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_HArray1OfViewKindEntity::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_HArray1OfViewKindEntity::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESDraw_HArray1OfViewKindEntity::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESDraw_HArray1OfViewKindEntity.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESDraw_HArray1OfViewKindEntity::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESDraw_HArray1OfViewKindEntity.def("Array1", (const IGESDraw_Array1OfViewKindEntity & (IGESDraw_HArray1OfViewKindEntity::*)() const) &IGESDraw_HArray1OfViewKindEntity::Array1, "None");
cls_IGESDraw_HArray1OfViewKindEntity.def("ChangeArray1", (IGESDraw_Array1OfViewKindEntity & (IGESDraw_HArray1OfViewKindEntity::*)()) &IGESDraw_HArray1OfViewKindEntity::ChangeArray1, "None");
cls_IGESDraw_HArray1OfViewKindEntity.def_static("get_type_name_", (const char * (*)()) &IGESDraw_HArray1OfViewKindEntity::get_type_name, "None");
cls_IGESDraw_HArray1OfViewKindEntity.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_HArray1OfViewKindEntity::get_type_descriptor, "None");
cls_IGESDraw_HArray1OfViewKindEntity.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_HArray1OfViewKindEntity::*)() const) &IGESDraw_HArray1OfViewKindEntity::DynamicType, "None");

// CLASS: IGESDRAW_DRAWING
py::class_<IGESDraw_Drawing, opencascade::handle<IGESDraw_Drawing>, IGESData_IGESEntity> cls_IGESDraw_Drawing(mod, "IGESDraw_Drawing", "defines IGESDrawing, Type <404> Form <0> in package IGESDraw");

// Constructors
cls_IGESDraw_Drawing.def(py::init<>());

// Methods
cls_IGESDraw_Drawing.def("Init", (void (IGESDraw_Drawing::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<TColgp_HArray1OfXY> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_Drawing::Init, "This method is used to set the fields of the class Drawing - allViews : Pointers to DEs of View entities - allViewOrigins : Origin coordinates of transformed Views - allAnnotations : Pointers to DEs of Annotation entities raises exception if Lengths of allViews and allViewOrigins are not same.", py::arg("allViews"), py::arg("allViewOrigins"), py::arg("allAnnotations"));
cls_IGESDraw_Drawing.def("NbViews", (Standard_Integer (IGESDraw_Drawing::*)() const) &IGESDraw_Drawing::NbViews, "returns the number of view pointers in <me>");
cls_IGESDraw_Drawing.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_Drawing::*)(const Standard_Integer) const) &IGESDraw_Drawing::ViewItem, "returns the ViewKindEntity indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbViews().", py::arg("ViewIndex"));
cls_IGESDraw_Drawing.def("ViewOrigin", (gp_Pnt2d (IGESDraw_Drawing::*)(const Standard_Integer) const) &IGESDraw_Drawing::ViewOrigin, "returns the Drawing space coordinates of the origin of the Transformed view indicated by TViewIndex raises an exception if TViewIndex <= 0 or TViewIndex > NbViews().", py::arg("TViewIndex"));
cls_IGESDraw_Drawing.def("NbAnnotations", (Standard_Integer (IGESDraw_Drawing::*)() const) &IGESDraw_Drawing::NbAnnotations, "returns the number of Annotation entities in <me>");
cls_IGESDraw_Drawing.def("Annotation", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_Drawing::*)(const Standard_Integer) const) &IGESDraw_Drawing::Annotation, "returns the Annotation entity in this Drawing, indicated by the AnnotationIndex raises an exception if AnnotationIndex <= 0 or AnnotationIndex > NbAnnotations().", py::arg("AnnotationIndex"));
cls_IGESDraw_Drawing.def("ViewToDrawing", (gp_XY (IGESDraw_Drawing::*)(const Standard_Integer, const gp_XYZ &) const) &IGESDraw_Drawing::ViewToDrawing, "None", py::arg("NumView"), py::arg("ViewCoords"));
cls_IGESDraw_Drawing.def("DrawingUnit", [](IGESDraw_Drawing &self, Standard_Real & value){ Standard_Boolean rv = self.DrawingUnit(value); return std::tuple<Standard_Boolean, Standard_Real &>(rv, value); }, "Returns the Drawing Unit Value if it is specified (by a specific property entity) If not specified, returns False, and val as zero : unit to consider is then the model unit in GlobalSection", py::arg("value"));
cls_IGESDraw_Drawing.def("DrawingSize", [](IGESDraw_Drawing &self, Standard_Real & X, Standard_Real & Y){ Standard_Boolean rv = self.DrawingSize(X, Y); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, X, Y); }, "Returns the Drawing Size if it is specified (by a specific property entity) If not specified, returns False, and X,Y as zero : unit to consider is then the model unit in GlobalSection", py::arg("X"), py::arg("Y"));
cls_IGESDraw_Drawing.def_static("get_type_name_", (const char * (*)()) &IGESDraw_Drawing::get_type_name, "None");
cls_IGESDraw_Drawing.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_Drawing::get_type_descriptor, "None");
cls_IGESDraw_Drawing.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_Drawing::*)() const) &IGESDraw_Drawing::DynamicType, "None");

// CLASS: IGESDRAW_DRAWINGWITHROTATION
py::class_<IGESDraw_DrawingWithRotation, opencascade::handle<IGESDraw_DrawingWithRotation>, IGESData_IGESEntity> cls_IGESDraw_DrawingWithRotation(mod, "IGESDraw_DrawingWithRotation", "defines IGESDrawingWithRotation, Type <404> Form <1> in package IGESDraw");

// Constructors
cls_IGESDraw_DrawingWithRotation.def(py::init<>());

// Methods
cls_IGESDraw_DrawingWithRotation.def("Init", (void (IGESDraw_DrawingWithRotation::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<TColgp_HArray1OfXY> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_DrawingWithRotation::Init, "This method is used to set the fields of the class DrawingWithRotation - allViews : Pointers to View entities - allViewOrigins : Origin coords of transformed views - allOrientationAngles : Orientation angles of transformed views - allAnnotations : Pointers to Annotation entities raises exception if Lengths of allViews, allViewOrigins and allOrientationAngles are not same.", py::arg("allViews"), py::arg("allViewOrigins"), py::arg("allOrientationAngles"), py::arg("allAnnotations"));
cls_IGESDraw_DrawingWithRotation.def("NbViews", (Standard_Integer (IGESDraw_DrawingWithRotation::*)() const) &IGESDraw_DrawingWithRotation::NbViews, "returns the number of view pointers in <me>");
cls_IGESDraw_DrawingWithRotation.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_DrawingWithRotation::*)(const Standard_Integer) const) &IGESDraw_DrawingWithRotation::ViewItem, "returns the View entity indicated by Index raises an exception if Index <= 0 or Index > NbViews().", py::arg("Index"));
cls_IGESDraw_DrawingWithRotation.def("ViewOrigin", (gp_Pnt2d (IGESDraw_DrawingWithRotation::*)(const Standard_Integer) const) &IGESDraw_DrawingWithRotation::ViewOrigin, "returns the Drawing space coordinates of the origin of the Transformed view indicated by Index raises an exception if Index <= 0 or Index > NbViews().", py::arg("Index"));
cls_IGESDraw_DrawingWithRotation.def("OrientationAngle", (Standard_Real (IGESDraw_DrawingWithRotation::*)(const Standard_Integer) const) &IGESDraw_DrawingWithRotation::OrientationAngle, "returns the Orientation angle for the Transformed view indicated by Index raises an exception if Index <= 0 or Index > NbViews().", py::arg("Index"));
cls_IGESDraw_DrawingWithRotation.def("NbAnnotations", (Standard_Integer (IGESDraw_DrawingWithRotation::*)() const) &IGESDraw_DrawingWithRotation::NbAnnotations, "returns the number of Annotation entities in <me>");
cls_IGESDraw_DrawingWithRotation.def("Annotation", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_DrawingWithRotation::*)(const Standard_Integer) const) &IGESDraw_DrawingWithRotation::Annotation, "returns the Annotation entity in this Drawing, indicated by Index raises an exception if Index <= 0 or Index > NbAnnotations().", py::arg("Index"));
cls_IGESDraw_DrawingWithRotation.def("ViewToDrawing", (gp_XY (IGESDraw_DrawingWithRotation::*)(const Standard_Integer, const gp_XYZ &) const) &IGESDraw_DrawingWithRotation::ViewToDrawing, "None", py::arg("NumView"), py::arg("ViewCoords"));
cls_IGESDraw_DrawingWithRotation.def("DrawingUnit", [](IGESDraw_DrawingWithRotation &self, Standard_Real & value){ Standard_Boolean rv = self.DrawingUnit(value); return std::tuple<Standard_Boolean, Standard_Real &>(rv, value); }, "Returns the Drawing Unit Value if it is specified (by a specific property entity) If not specified, returns False, and val as zero : unit to consider is then the model unit in GlobalSection", py::arg("value"));
cls_IGESDraw_DrawingWithRotation.def("DrawingSize", [](IGESDraw_DrawingWithRotation &self, Standard_Real & X, Standard_Real & Y){ Standard_Boolean rv = self.DrawingSize(X, Y); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, X, Y); }, "Returns the Drawing Size if it is specified (by a specific property entity) If not specified, returns False, and X,Y as zero : unit to consider is then the model unit in GlobalSection", py::arg("X"), py::arg("Y"));
cls_IGESDraw_DrawingWithRotation.def_static("get_type_name_", (const char * (*)()) &IGESDraw_DrawingWithRotation::get_type_name, "None");
cls_IGESDraw_DrawingWithRotation.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_DrawingWithRotation::get_type_descriptor, "None");
cls_IGESDraw_DrawingWithRotation.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_DrawingWithRotation::*)() const) &IGESDraw_DrawingWithRotation::DynamicType, "None");

// CLASS: IGESDRAW_GENERALMODULE
py::class_<IGESDraw_GeneralModule, opencascade::handle<IGESDraw_GeneralModule>, IGESData_GeneralModule> cls_IGESDraw_GeneralModule(mod, "IGESDraw_GeneralModule", "Definition of General Services for IGESDraw (specific part) This Services comprise : Shared & Implied Lists, Copy, Check");

// Constructors
cls_IGESDraw_GeneralModule.def(py::init<>());

// Methods
cls_IGESDraw_GeneralModule.def("OwnSharedCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, Interface_EntityIterator &) const) &IGESDraw_GeneralModule::OwnSharedCase, "Lists the Entities shared by a given IGESEntity <ent>, from its specific parameters : specific for each type", py::arg("CN"), py::arg("ent"), py::arg("iter"));
cls_IGESDraw_GeneralModule.def("OwnImpliedCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, Interface_EntityIterator &) const) &IGESDraw_GeneralModule::OwnImpliedCase, "Specific list of Entities implied by an IGESEntity <ent> (in addition to Associativities). Redefined for ViewsVisible ...", py::arg("CN"), py::arg("ent"), py::arg("iter"));
cls_IGESDraw_GeneralModule.def("DirChecker", (IGESData_DirChecker (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESDraw_GeneralModule::DirChecker, "Returns a DirChecker, specific for each type of Entity (identified by its Case Number) : this DirChecker defines constraints which must be respected by the DirectoryPart", py::arg("CN"), py::arg("ent"));
cls_IGESDraw_GeneralModule.def("OwnCheckCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_GeneralModule::OwnCheckCase, "Performs Specific Semantic Check for each type of Entity", py::arg("CN"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_GeneralModule.def("NewVoid", (Standard_Boolean (IGESDraw_GeneralModule::*)(const Standard_Integer, opencascade::handle<Standard_Transient> &) const) &IGESDraw_GeneralModule::NewVoid, "Specific creation of a new void entity", py::arg("CN"), py::arg("entto"));
cls_IGESDraw_GeneralModule.def("OwnCopyCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, Interface_CopyTool &) const) &IGESDraw_GeneralModule::OwnCopyCase, "Copies parameters which are specific of each Type of Entity", py::arg("CN"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_GeneralModule.def("OwnRenewCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, const Interface_CopyTool &) const) &IGESDraw_GeneralModule::OwnRenewCase, "Renews parameters which are specific of each Type of Entity : redefined for ViewsVisible ... (takes only the implied ref.s which have also been copied)", py::arg("CN"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_GeneralModule.def("OwnDeleteCase", (void (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESDraw_GeneralModule::OwnDeleteCase, "Clears parameters with can cause looping structures : redefined for ViewsVisible ... (clears the implied ref.s)", py::arg("CN"), py::arg("ent"));
cls_IGESDraw_GeneralModule.def("CategoryNumber", (Standard_Integer (IGESDraw_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &) const) &IGESDraw_GeneralModule::CategoryNumber, "Returns a category number which characterizes an entity Planar : Auxiliary Subfigures and ConnectPoint : Structure others : Drawing", py::arg("CN"), py::arg("ent"), py::arg("shares"));
cls_IGESDraw_GeneralModule.def_static("get_type_name_", (const char * (*)()) &IGESDraw_GeneralModule::get_type_name, "None");
cls_IGESDraw_GeneralModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_GeneralModule::get_type_descriptor, "None");
cls_IGESDraw_GeneralModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_GeneralModule::*)() const) &IGESDraw_GeneralModule::DynamicType, "None");

// CLASS: IGESDRAW_LABELDISPLAY
py::class_<IGESDraw_LabelDisplay, opencascade::handle<IGESDraw_LabelDisplay>, IGESData_LabelDisplayEntity> cls_IGESDraw_LabelDisplay(mod, "IGESDraw_LabelDisplay", "defines IGESLabelDisplay, Type <402> Form <5> in package IGESDraw");

// Constructors
cls_IGESDraw_LabelDisplay.def(py::init<>());

// Methods
cls_IGESDraw_LabelDisplay.def("Init", (void (IGESDraw_LabelDisplay::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<TColgp_HArray1OfXYZ> &, const opencascade::handle<IGESDimen_HArray1OfLeaderArrow> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_LabelDisplay::Init, "This method is used to set the fields of the class LabelDisplay - allViews : Pointers to View Entities - allTextLocations : Coordinates of text locations in the views - allLeaderEntities : Pointers to Leader Entities in the views - allLabelLevels : Entity label level numbers in the views - allDisplayedEntities : Pointers to the entities being displayed raises exception if Lengths of allViews, allTextLocations, allLeaderEntities, allLabelLevels and allDisplayedEntities are not same.", py::arg("allViews"), py::arg("allTextLocations"), py::arg("allLeaderEntities"), py::arg("allLabelLevels"), py::arg("allDisplayedEntities"));
cls_IGESDraw_LabelDisplay.def("NbLabels", (Standard_Integer (IGESDraw_LabelDisplay::*)() const) &IGESDraw_LabelDisplay::NbLabels, "returns the number of label placements in <me>");
cls_IGESDraw_LabelDisplay.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::ViewItem, "returns the View entity indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbLabels().", py::arg("ViewIndex"));
cls_IGESDraw_LabelDisplay.def("TextLocation", (gp_Pnt (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::TextLocation, "returns the 3d-Point coordinates of the text location, in the view indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbLabels().", py::arg("ViewIndex"));
cls_IGESDraw_LabelDisplay.def("LeaderEntity", (opencascade::handle<IGESDimen_LeaderArrow> (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::LeaderEntity, "returns the Leader entity in the view indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbLabels().", py::arg("ViewIndex"));
cls_IGESDraw_LabelDisplay.def("LabelLevel", (Standard_Integer (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::LabelLevel, "returns the Entity label level number in the view indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbLabels().", py::arg("ViewIndex"));
cls_IGESDraw_LabelDisplay.def("DisplayedEntity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::DisplayedEntity, "returns the entity indicated by EntityIndex raises an exception if EntityIndex <= 0 or EntityIndex > NbLabels().", py::arg("EntityIndex"));
cls_IGESDraw_LabelDisplay.def("TransformedTextLocation", (gp_Pnt (IGESDraw_LabelDisplay::*)(const Standard_Integer) const) &IGESDraw_LabelDisplay::TransformedTextLocation, "returns the transformed 3d-Point coordinates of the text location, in the view indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbLabels().", py::arg("ViewIndex"));
cls_IGESDraw_LabelDisplay.def_static("get_type_name_", (const char * (*)()) &IGESDraw_LabelDisplay::get_type_name, "None");
cls_IGESDraw_LabelDisplay.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_LabelDisplay::get_type_descriptor, "None");
cls_IGESDraw_LabelDisplay.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_LabelDisplay::*)() const) &IGESDraw_LabelDisplay::DynamicType, "None");

// CLASS: IGESDRAW_NETWORKSUBFIGURE
py::class_<IGESDraw_NetworkSubfigure, opencascade::handle<IGESDraw_NetworkSubfigure>, IGESData_IGESEntity> cls_IGESDraw_NetworkSubfigure(mod, "IGESDraw_NetworkSubfigure", "defines IGES Network Subfigure Instance Entity, Type <420> Form Number <0> in package IGESDraw");

// Constructors
cls_IGESDraw_NetworkSubfigure.def(py::init<>());

// Methods
cls_IGESDraw_NetworkSubfigure.def("Init", (void (IGESDraw_NetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, const gp_XYZ &, const gp_XYZ &, const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<IGESGraph_TextDisplayTemplate> &, const opencascade::handle<IGESDraw_HArray1OfConnectPoint> &)) &IGESDraw_NetworkSubfigure::Init, "This method is used to set the fields of the class NetworkSubfigure - aDefinition : Network Subfigure Definition Entity - aTranslation : Translation data relative to the model space or the definition space - aScaleFactor : Scale factors in the definition space - aTypeFlag : Type flag - aDesignator : Primary reference designator - aTemplate : Primary reference designator Text display Template Entity - allConnectPoints : Associated Connect Point Entities", py::arg("aDefinition"), py::arg("aTranslation"), py::arg("aScaleFactor"), py::arg("aTypeFlag"), py::arg("aDesignator"), py::arg("aTemplate"), py::arg("allConnectPoints"));
cls_IGESDraw_NetworkSubfigure.def("SubfigureDefinition", (opencascade::handle<IGESDraw_NetworkSubfigureDef> (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::SubfigureDefinition, "returns Network Subfigure Definition Entity specified by this entity");
cls_IGESDraw_NetworkSubfigure.def("Translation", (gp_XYZ (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::Translation, "returns Translation Data relative to either model space or to the definition space of a referring entity");
cls_IGESDraw_NetworkSubfigure.def("TransformedTranslation", (gp_XYZ (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::TransformedTranslation, "returns the Transformed Translation Data relative to either model space or to the definition space of a referring entity");
cls_IGESDraw_NetworkSubfigure.def("ScaleFactors", (gp_XYZ (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::ScaleFactors, "returns Scale factor in definition space(x, y, z axes)");
cls_IGESDraw_NetworkSubfigure.def("TypeFlag", (Standard_Integer (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::TypeFlag, "returns Type Flag which implements the distinction between Logical design and Physical design data,and is required if both are present. Type Flag = 0 : Not specified (default) = 1 : Logical = 2 : Physical");
cls_IGESDraw_NetworkSubfigure.def("ReferenceDesignator", (opencascade::handle<TCollection_HAsciiString> (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::ReferenceDesignator, "returns the primary reference designator");
cls_IGESDraw_NetworkSubfigure.def("HasDesignatorTemplate", (Standard_Boolean (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::HasDesignatorTemplate, "returns True if Text Display Template Entity is specified, else False");
cls_IGESDraw_NetworkSubfigure.def("DesignatorTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::DesignatorTemplate, "returns primary reference designator Text Display Template Entity, or null. If null, no Text Display Template Entity specified");
cls_IGESDraw_NetworkSubfigure.def("NbConnectPoints", (Standard_Integer (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::NbConnectPoints, "returns the number of associated Connect Point Entities");
cls_IGESDraw_NetworkSubfigure.def("ConnectPoint", (opencascade::handle<IGESDraw_ConnectPoint> (IGESDraw_NetworkSubfigure::*)(const Standard_Integer) const) &IGESDraw_NetworkSubfigure::ConnectPoint, "returns the Index'th associated Connect point Entity raises exception if Index <= 0 or Index > NbConnectPoints()", py::arg("Index"));
cls_IGESDraw_NetworkSubfigure.def_static("get_type_name_", (const char * (*)()) &IGESDraw_NetworkSubfigure::get_type_name, "None");
cls_IGESDraw_NetworkSubfigure.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_NetworkSubfigure::get_type_descriptor, "None");
cls_IGESDraw_NetworkSubfigure.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_NetworkSubfigure::*)() const) &IGESDraw_NetworkSubfigure::DynamicType, "None");

// CLASS: IGESDRAW_NETWORKSUBFIGUREDEF
py::class_<IGESDraw_NetworkSubfigureDef, opencascade::handle<IGESDraw_NetworkSubfigureDef>, IGESData_IGESEntity> cls_IGESDraw_NetworkSubfigureDef(mod, "IGESDraw_NetworkSubfigureDef", "defines IGESNetworkSubfigureDef, Type <320> Form Number <0> in package IGESDraw");

// Constructors
cls_IGESDraw_NetworkSubfigureDef.def(py::init<>());

// Methods
cls_IGESDraw_NetworkSubfigureDef.def("Init", (void (IGESDraw_NetworkSubfigureDef::*)(const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const Standard_Integer, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<IGESGraph_TextDisplayTemplate> &, const opencascade::handle<IGESDraw_HArray1OfConnectPoint> &)) &IGESDraw_NetworkSubfigureDef::Init, "This method is used to set fields of the class NetworkSubfigureDef - aDepth : Depth of Subfigure (indicating the amount of nesting) - aName : Subfigure Name - allEntities : Associated subfigures Entities exclusive of primary reference designator and Control Points. - aTypeFlag : Type flag determines which Entity belongs in which design (Logical design or Physical design) - aDesignator : Designator HAsciiString and its Template - allPointEntities : Associated Connect Point Entities", py::arg("aDepth"), py::arg("aName"), py::arg("allEntities"), py::arg("aTypeFlag"), py::arg("aDesignator"), py::arg("aTemplate"), py::arg("allPointEntities"));
cls_IGESDraw_NetworkSubfigureDef.def("Depth", (Standard_Integer (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::Depth, "returns Depth of Subfigure(indication the amount of nesting) Note : The Depth is inclusive of both Network Subfigure Definition Entity and the Ordinary Subfigure Definition Entity. Thus, the two may be nested.");
cls_IGESDraw_NetworkSubfigureDef.def("Name", (opencascade::handle<TCollection_HAsciiString> (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::Name, "returns the Subfigure Name");
cls_IGESDraw_NetworkSubfigureDef.def("NbEntities", (Standard_Integer (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::NbEntities, "returns Number of Associated(child) entries in subfigure exclusive of primary reference designator and Control Points");
cls_IGESDraw_NetworkSubfigureDef.def("Entity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_NetworkSubfigureDef::*)(const Standard_Integer) const) &IGESDraw_NetworkSubfigureDef::Entity, "returns the Index'th IGESEntity in subfigure exclusive of primary reference designator and Control Points raises exception if Index <=0 or Index > NbEntities()", py::arg("Index"));
cls_IGESDraw_NetworkSubfigureDef.def("TypeFlag", (Standard_Integer (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::TypeFlag, "return value = 0 : Not Specified = 1 : Logical design = 2 : Physical design");
cls_IGESDraw_NetworkSubfigureDef.def("Designator", (opencascade::handle<TCollection_HAsciiString> (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::Designator, "returns Primary Reference Designator");
cls_IGESDraw_NetworkSubfigureDef.def("HasDesignatorTemplate", (Standard_Boolean (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::HasDesignatorTemplate, "returns True if Text Display Template is specified for primary designator else returns False");
cls_IGESDraw_NetworkSubfigureDef.def("DesignatorTemplate", (opencascade::handle<IGESGraph_TextDisplayTemplate> (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::DesignatorTemplate, "if Text Display Template specified then return TextDisplayTemplate else return NULL Handle");
cls_IGESDraw_NetworkSubfigureDef.def("NbPointEntities", (Standard_Integer (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::NbPointEntities, "returns the Number Of Associated(child) Connect Point Entities");
cls_IGESDraw_NetworkSubfigureDef.def("HasPointEntity", (Standard_Boolean (IGESDraw_NetworkSubfigureDef::*)(const Standard_Integer) const) &IGESDraw_NetworkSubfigureDef::HasPointEntity, "returns True is Index'th Associated Connect Point Entity is present else returns False raises exception if Index is out of bound", py::arg("Index"));
cls_IGESDraw_NetworkSubfigureDef.def("PointEntity", (opencascade::handle<IGESDraw_ConnectPoint> (IGESDraw_NetworkSubfigureDef::*)(const Standard_Integer) const) &IGESDraw_NetworkSubfigureDef::PointEntity, "returns the Index'th Associated Connect Point Entity raises exception if Index <= 0 or Index > NbPointEntities()", py::arg("Index"));
cls_IGESDraw_NetworkSubfigureDef.def_static("get_type_name_", (const char * (*)()) &IGESDraw_NetworkSubfigureDef::get_type_name, "None");
cls_IGESDraw_NetworkSubfigureDef.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_NetworkSubfigureDef::get_type_descriptor, "None");
cls_IGESDraw_NetworkSubfigureDef.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_NetworkSubfigureDef::*)() const) &IGESDraw_NetworkSubfigureDef::DynamicType, "None");

// CLASS: IGESDRAW_PERSPECTIVEVIEW
py::class_<IGESDraw_PerspectiveView, opencascade::handle<IGESDraw_PerspectiveView>, IGESData_ViewKindEntity> cls_IGESDraw_PerspectiveView(mod, "IGESDraw_PerspectiveView", "defines IGESPerspectiveView, Type <410> Form <1> in package IGESDraw");

// Constructors
cls_IGESDraw_PerspectiveView.def(py::init<>());

// Methods
cls_IGESDraw_PerspectiveView.def("Init", (void (IGESDraw_PerspectiveView::*)(const Standard_Integer, const Standard_Real, const gp_XYZ &, const gp_XYZ &, const gp_XYZ &, const gp_XYZ &, const Standard_Real, const gp_XY &, const gp_XY &, const Standard_Integer, const Standard_Real, const Standard_Real)) &IGESDraw_PerspectiveView::Init, "This method is used to set the fields of the class PerspectiveView - aViewNumber : The desired view - aScaleFactor : Scale factor - aViewNormalVector : View plane normal vector (model space) - aViewReferencePoint : View reference point (model space) - aCenterOfProjection : Center Of Projection (model space) - aViewUpVector : View up vector (model space) - aViewPlaneDistance : View plane distance (model space) - aTopLeft : Top-left point of clipping window - aBottomRight : Bottom-right point of clipping window - aDepthClip : Depth clipping indicator - aBackPlaneDistance : Distance of back clipping plane - aFrontPlaneDistance : Distance of front clipping plane", py::arg("aViewNumber"), py::arg("aScaleFactor"), py::arg("aViewNormalVector"), py::arg("aViewReferencePoint"), py::arg("aCenterOfProjection"), py::arg("aViewUpVector"), py::arg("aViewPlaneDistance"), py::arg("aTopLeft"), py::arg("aBottomRight"), py::arg("aDepthClip"), py::arg("aBackPlaneDistance"), py::arg("aFrontPlaneDistance"));
cls_IGESDraw_PerspectiveView.def("IsSingle", (Standard_Boolean (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::IsSingle, "Returns True (for a single view)");
cls_IGESDraw_PerspectiveView.def("NbViews", (Standard_Integer (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::NbViews, "Returns 1 (single view)");
cls_IGESDraw_PerspectiveView.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_PerspectiveView::*)(const Standard_Integer) const) &IGESDraw_PerspectiveView::ViewItem, "For a single view, returns <me> whatever <num>", py::arg("num"));
cls_IGESDraw_PerspectiveView.def("ViewNumber", (Standard_Integer (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewNumber, "returns the view number associated with <me>");
cls_IGESDraw_PerspectiveView.def("ScaleFactor", (Standard_Real (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ScaleFactor, "returns the scale factor associated with <me>");
cls_IGESDraw_PerspectiveView.def("ViewNormalVector", (gp_Vec (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewNormalVector, "returns the View plane normal vector (model space)");
cls_IGESDraw_PerspectiveView.def("ViewReferencePoint", (gp_Pnt (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewReferencePoint, "returns the View reference point (model space)");
cls_IGESDraw_PerspectiveView.def("CenterOfProjection", (gp_Pnt (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::CenterOfProjection, "returns the Center Of Projection (model space)");
cls_IGESDraw_PerspectiveView.def("ViewUpVector", (gp_Vec (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewUpVector, "returns the View up vector (model space)");
cls_IGESDraw_PerspectiveView.def("ViewPlaneDistance", (Standard_Real (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewPlaneDistance, "returns the View plane distance (model space)");
cls_IGESDraw_PerspectiveView.def("TopLeft", (gp_Pnt2d (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::TopLeft, "returns the top left point of the clipping window");
cls_IGESDraw_PerspectiveView.def("BottomRight", (gp_Pnt2d (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::BottomRight, "returns the bottom right point of the clipping window");
cls_IGESDraw_PerspectiveView.def("DepthClip", (Standard_Integer (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::DepthClip, "returns the Depth clipping indicator 0 = No depth clipping 1 = Back clipping plane ON 2 = Front clipping plane ON 3 = Back and front clipping planes ON");
cls_IGESDraw_PerspectiveView.def("BackPlaneDistance", (Standard_Real (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::BackPlaneDistance, "returns the View coordinate denoting the location of the back clipping plane");
cls_IGESDraw_PerspectiveView.def("FrontPlaneDistance", (Standard_Real (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::FrontPlaneDistance, "returns the View coordinate denoting the location of the front clipping plane");
cls_IGESDraw_PerspectiveView.def("ViewMatrix", (opencascade::handle<IGESData_TransfEntity> (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::ViewMatrix, "returns the Transformation Matrix");
cls_IGESDraw_PerspectiveView.def("ModelToView", (gp_XYZ (IGESDraw_PerspectiveView::*)(const gp_XYZ &) const) &IGESDraw_PerspectiveView::ModelToView, "returns XYX from the Model space to the View space by applying the View Matrix", py::arg("coords"));
cls_IGESDraw_PerspectiveView.def_static("get_type_name_", (const char * (*)()) &IGESDraw_PerspectiveView::get_type_name, "None");
cls_IGESDraw_PerspectiveView.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_PerspectiveView::get_type_descriptor, "None");
cls_IGESDraw_PerspectiveView.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_PerspectiveView::*)() const) &IGESDraw_PerspectiveView::DynamicType, "None");

// CLASS: IGESDRAW_PLANAR
py::class_<IGESDraw_Planar, opencascade::handle<IGESDraw_Planar>, IGESData_IGESEntity> cls_IGESDraw_Planar(mod, "IGESDraw_Planar", "defines IGESPlanar, Type <402> Form <16> in package IGESDraw");

// Constructors
cls_IGESDraw_Planar.def(py::init<>());

// Methods
cls_IGESDraw_Planar.def("Init", (void (IGESDraw_Planar::*)(const Standard_Integer, const opencascade::handle<IGESGeom_TransformationMatrix> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_Planar::Init, "This method is used to set the fields of the class Planar - nbMats : Number of Transformation matrices - aTransformationMatrix : Pointer to the Transformation matrix - allEntities : Pointers to the entities specified", py::arg("nbMats"), py::arg("aTransformationMatrix"), py::arg("allEntities"));
cls_IGESDraw_Planar.def("NbMatrices", (Standard_Integer (IGESDraw_Planar::*)() const) &IGESDraw_Planar::NbMatrices, "returns the number of Transformation matrices in <me>");
cls_IGESDraw_Planar.def("NbEntities", (Standard_Integer (IGESDraw_Planar::*)() const) &IGESDraw_Planar::NbEntities, "returns the number of Entities in the plane pointed to by this associativity");
cls_IGESDraw_Planar.def("IsIdentityMatrix", (Standard_Boolean (IGESDraw_Planar::*)() const) &IGESDraw_Planar::IsIdentityMatrix, "returns True if TransformationMatrix is Identity Matrix, i.e:- No Matrix defined.");
cls_IGESDraw_Planar.def("TransformMatrix", (opencascade::handle<IGESGeom_TransformationMatrix> (IGESDraw_Planar::*)() const) &IGESDraw_Planar::TransformMatrix, "returns the Transformation matrix moving data from the XY plane into space or zero");
cls_IGESDraw_Planar.def("Entity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_Planar::*)(const Standard_Integer) const) &IGESDraw_Planar::Entity, "returns the Entity on the specified plane, indicated by EntityIndex raises an exception if EntityIndex <= 0 or EntityIndex > NbEntities()", py::arg("EntityIndex"));
cls_IGESDraw_Planar.def_static("get_type_name_", (const char * (*)()) &IGESDraw_Planar::get_type_name, "None");
cls_IGESDraw_Planar.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_Planar::get_type_descriptor, "None");
cls_IGESDraw_Planar.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_Planar::*)() const) &IGESDraw_Planar::DynamicType, "None");

// CLASS: IGESDRAW_PROTOCOL
py::class_<IGESDraw_Protocol, opencascade::handle<IGESDraw_Protocol>, IGESData_Protocol> cls_IGESDraw_Protocol(mod, "IGESDraw_Protocol", "Description of Protocol for IGESDraw");

// Constructors
cls_IGESDraw_Protocol.def(py::init<>());

// Methods
cls_IGESDraw_Protocol.def("NbResources", (Standard_Integer (IGESDraw_Protocol::*)() const) &IGESDraw_Protocol::NbResources, "Gives the count of Resource Protocol. Here, one (Protocol from IGESDimen)");
cls_IGESDraw_Protocol.def("Resource", (opencascade::handle<Interface_Protocol> (IGESDraw_Protocol::*)(const Standard_Integer) const) &IGESDraw_Protocol::Resource, "Returns a Resource, given a rank.", py::arg("num"));
cls_IGESDraw_Protocol.def("TypeNumber", (Standard_Integer (IGESDraw_Protocol::*)(const opencascade::handle<Standard_Type> &) const) &IGESDraw_Protocol::TypeNumber, "Returns a Case Number, specific of each recognized Type This Case Number is then used in Libraries : the various Modules attached to this class of Protocol must use them in accordance (for a given value of TypeNumber, they must consider the same Type as the Protocol defines)", py::arg("atype"));
cls_IGESDraw_Protocol.def_static("get_type_name_", (const char * (*)()) &IGESDraw_Protocol::get_type_name, "None");
cls_IGESDraw_Protocol.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_Protocol::get_type_descriptor, "None");
cls_IGESDraw_Protocol.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_Protocol::*)() const) &IGESDraw_Protocol::DynamicType, "None");

// CLASS: IGESDRAW_READWRITEMODULE
py::class_<IGESDraw_ReadWriteModule, opencascade::handle<IGESDraw_ReadWriteModule>, IGESData_ReadWriteModule> cls_IGESDraw_ReadWriteModule(mod, "IGESDraw_ReadWriteModule", "Defines Draw File Access Module for IGESDraw (specific parts) Specific actions concern : Read and Write Own Parameters of an IGESEntity.");

// Constructors
cls_IGESDraw_ReadWriteModule.def(py::init<>());

// Methods
cls_IGESDraw_ReadWriteModule.def("CaseIGES", (Standard_Integer (IGESDraw_ReadWriteModule::*)(const Standard_Integer, const Standard_Integer) const) &IGESDraw_ReadWriteModule::CaseIGES, "Defines Case Numbers for Entities of IGESDraw", py::arg("typenum"), py::arg("formnum"));
cls_IGESDraw_ReadWriteModule.def("ReadOwnParams", (void (IGESDraw_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ReadWriteModule::ReadOwnParams, "Reads own parameters from file for an Entity of IGESDraw", py::arg("CN"), py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ReadWriteModule.def("WriteOwnParams", (void (IGESDraw_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, IGESData_IGESWriter &) const) &IGESDraw_ReadWriteModule::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("CN"), py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ReadWriteModule.def_static("get_type_name_", (const char * (*)()) &IGESDraw_ReadWriteModule::get_type_name, "None");
cls_IGESDraw_ReadWriteModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_ReadWriteModule::get_type_descriptor, "None");
cls_IGESDraw_ReadWriteModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_ReadWriteModule::*)() const) &IGESDraw_ReadWriteModule::DynamicType, "None");

// CLASS: IGESDRAW_RECTARRAYSUBFIGURE
py::class_<IGESDraw_RectArraySubfigure, opencascade::handle<IGESDraw_RectArraySubfigure>, IGESData_IGESEntity> cls_IGESDraw_RectArraySubfigure(mod, "IGESDraw_RectArraySubfigure", "Defines IGES Rectangular Array Subfigure Instance Entity, Type <412> Form Number <0> in package IGESDraw Used to produce copies of object called the base entity, arranging them in equally spaced rows and columns");

// Constructors
cls_IGESDraw_RectArraySubfigure.def(py::init<>());

// Methods
cls_IGESDraw_RectArraySubfigure.def("Init", (void (IGESDraw_RectArraySubfigure::*)(const opencascade::handle<IGESData_IGESEntity> &, const Standard_Real, const gp_XYZ &, const Standard_Integer, const Standard_Integer, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &)) &IGESDraw_RectArraySubfigure::Init, "This method is used to set the fields of the class RectArraySubfigure - aBase : a base entity which is replicated - aScale : Scale Factor - aCorner : lower left hand corner for the entire array - nbCols : Number of columns of the array - nbRows : Number of rows of the array - hDisp : Column separations - vtDisp : Row separation - rotationAngle : Rotation angle specified in radians - allDont : DO-DON'T flag to control which portion to display - allNumPos : List of positions to be or not to be displayed", py::arg("aBase"), py::arg("aScale"), py::arg("aCorner"), py::arg("nbCols"), py::arg("nbRows"), py::arg("hDisp"), py::arg("vtDisp"), py::arg("rotationAngle"), py::arg("doDont"), py::arg("allNumPos"));
cls_IGESDraw_RectArraySubfigure.def("BaseEntity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::BaseEntity, "returns the base entity, copies of which are produced");
cls_IGESDraw_RectArraySubfigure.def("ScaleFactor", (Standard_Real (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::ScaleFactor, "returns the scale factor");
cls_IGESDraw_RectArraySubfigure.def("LowerLeftCorner", (gp_Pnt (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::LowerLeftCorner, "returns coordinates of lower left hand corner for the entire array");
cls_IGESDraw_RectArraySubfigure.def("TransformedLowerLeftCorner", (gp_Pnt (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::TransformedLowerLeftCorner, "returns Transformed coordinates of lower left corner for the array");
cls_IGESDraw_RectArraySubfigure.def("NbColumns", (Standard_Integer (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::NbColumns, "returns number of columns in the array");
cls_IGESDraw_RectArraySubfigure.def("NbRows", (Standard_Integer (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::NbRows, "returns number of rows in the array");
cls_IGESDraw_RectArraySubfigure.def("ColumnSeparation", (Standard_Real (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::ColumnSeparation, "returns horizontal distance between columns");
cls_IGESDraw_RectArraySubfigure.def("RowSeparation", (Standard_Real (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::RowSeparation, "returns vertical distance between rows");
cls_IGESDraw_RectArraySubfigure.def("RotationAngle", (Standard_Real (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::RotationAngle, "returns rotation angle in radians");
cls_IGESDraw_RectArraySubfigure.def("DisplayFlag", (Standard_Boolean (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::DisplayFlag, "returns True if (ListCount = 0) i.e., all elements to be displayed");
cls_IGESDraw_RectArraySubfigure.def("ListCount", (Standard_Integer (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::ListCount, "returns 0 if all replicated entities to be displayed");
cls_IGESDraw_RectArraySubfigure.def("DoDontFlag", (Standard_Boolean (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::DoDontFlag, "returns 0 if half or fewer of the elements of the array are defined 1 if half or more of the elements are defined");
cls_IGESDraw_RectArraySubfigure.def("PositionNum", (Standard_Boolean (IGESDraw_RectArraySubfigure::*)(const Standard_Integer) const) &IGESDraw_RectArraySubfigure::PositionNum, "returns whether Index is to be processed (DO) or not to be processed(DON'T) if (ListCount = 0) return theDoDontFlag", py::arg("Index"));
cls_IGESDraw_RectArraySubfigure.def("ListPosition", (Standard_Integer (IGESDraw_RectArraySubfigure::*)(const Standard_Integer) const) &IGESDraw_RectArraySubfigure::ListPosition, "returns the Index'th value position raises exception if Index <= 0 or Index > ListCount()", py::arg("Index"));
cls_IGESDraw_RectArraySubfigure.def_static("get_type_name_", (const char * (*)()) &IGESDraw_RectArraySubfigure::get_type_name, "None");
cls_IGESDraw_RectArraySubfigure.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_RectArraySubfigure::get_type_descriptor, "None");
cls_IGESDraw_RectArraySubfigure.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_RectArraySubfigure::*)() const) &IGESDraw_RectArraySubfigure::DynamicType, "None");

// CLASS: IGESDRAW_SEGMENTEDVIEWSVISIBLE
py::class_<IGESDraw_SegmentedViewsVisible, opencascade::handle<IGESDraw_SegmentedViewsVisible>, IGESData_ViewKindEntity> cls_IGESDraw_SegmentedViewsVisible(mod, "IGESDraw_SegmentedViewsVisible", "defines IGESSegmentedViewsVisible, Type <402> Form <19> in package IGESDraw");

// Constructors
cls_IGESDraw_SegmentedViewsVisible.def(py::init<>());

// Methods
cls_IGESDraw_SegmentedViewsVisible.def("Init", (void (IGESDraw_SegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESGraph_HArray1OfColor> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESBasic_HArray1OfLineFontEntity> &, const opencascade::handle<TColStd_HArray1OfInteger> &)) &IGESDraw_SegmentedViewsVisible::Init, "This method is used to set the fields of the class SegmentedViewsVisible - allViews : Pointers to View Entities - allBreakpointParameters : Parameters of breakpoints - allDisplayFlags : Display flags - allColorValues : Color Values - allColorDefinitions : Color Definitions - allLineFontValues : LineFont values - allLineFontDefinitions : LineFont Definitions - allLineWeights : Line weights raises exception if Lengths of allViews, allBreakpointParameters, allDisplayFlags, allColorValues, allColorDefinitions, allLineFontValues, allLineFontDefinitions and allLineWeights are not same.", py::arg("allViews"), py::arg("allBreakpointParameters"), py::arg("allDisplayFlags"), py::arg("allColorValues"), py::arg("allColorDefinitions"), py::arg("allLineFontValues"), py::arg("allLineFontDefinitions"), py::arg("allLineWeights"));
cls_IGESDraw_SegmentedViewsVisible.def("IsSingle", (Standard_Boolean (IGESDraw_SegmentedViewsVisible::*)() const) &IGESDraw_SegmentedViewsVisible::IsSingle, "Returns False (for a complex view)");
cls_IGESDraw_SegmentedViewsVisible.def("NbViews", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)() const) &IGESDraw_SegmentedViewsVisible::NbViews, "Returns the count of Views referenced by <me> (inherited)");
cls_IGESDraw_SegmentedViewsVisible.def("NbSegmentBlocks", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)() const) &IGESDraw_SegmentedViewsVisible::NbSegmentBlocks, "returns the number of view/segment blocks in <me> Similar to NbViews but has a more general significance");
cls_IGESDraw_SegmentedViewsVisible.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::ViewItem, "returns the View entity indicated by ViewIndex raises an exception if ViewIndex <= 0 or ViewIndex > NbSegmentBlocks()", py::arg("ViewIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("BreakpointParameter", (Standard_Real (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::BreakpointParameter, "returns the parameter of the breakpoint indicated by BreakpointIndex raises an exception if BreakpointIndex <= 0 or BreakpointIndex > NbSegmentBlocks().", py::arg("BreakpointIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("DisplayFlag", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::DisplayFlag, "returns the Display flag indicated by FlagIndex raises an exception if FlagIndex <= 0 or FlagIndex > NbSegmentBlocks().", py::arg("FlagIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("IsColorDefinition", (Standard_Boolean (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::IsColorDefinition, "returns True if the ColorIndex'th value of the 'theColorDefinitions' field of <me> is a pointer raises an exception if ColorIndex <= 0 or ColorIndex > NbSegmentBlocks().", py::arg("ColorIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("ColorValue", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::ColorValue, "returns the Color value indicated by ColorIndex raises an exception if ColorIndex <= 0 or ColorIndex > NbSegmentBlocks().", py::arg("ColorIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("ColorDefinition", (opencascade::handle<IGESGraph_Color> (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::ColorDefinition, "returns the Color definition entity indicated by ColorIndex raises an exception if ColorIndex <= 0 or ColorIndex > NbSegmentBlocks().", py::arg("ColorIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("IsFontDefinition", (Standard_Boolean (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::IsFontDefinition, "returns True if the FontIndex'th value of the 'theLineFontDefinitions' field of <me> is a pointer raises an exception if FontIndex <= 0 or FontIndex > NbSegmentBlocks().", py::arg("FontIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("LineFontValue", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::LineFontValue, "returns the LineFont value indicated by FontIndex raises an exception if FontIndex <= 0 or FontIndex > NbSegmentBlocks().", py::arg("FontIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("LineFontDefinition", (opencascade::handle<IGESData_LineFontEntity> (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::LineFontDefinition, "returns the LineFont definition entity indicated by FontIndex raises an exception if FontIndex <= 0 or FontIndex > NbSegmentBlocks().", py::arg("FontIndex"));
cls_IGESDraw_SegmentedViewsVisible.def("LineWeightItem", (Standard_Integer (IGESDraw_SegmentedViewsVisible::*)(const Standard_Integer) const) &IGESDraw_SegmentedViewsVisible::LineWeightItem, "returns the LineWeight value indicated by WeightIndex raises an exception if WeightIndex <= 0 or WeightIndex > NbSegmentBlocks().", py::arg("WeightIndex"));
cls_IGESDraw_SegmentedViewsVisible.def_static("get_type_name_", (const char * (*)()) &IGESDraw_SegmentedViewsVisible::get_type_name, "None");
cls_IGESDraw_SegmentedViewsVisible.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_SegmentedViewsVisible::get_type_descriptor, "None");
cls_IGESDraw_SegmentedViewsVisible.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_SegmentedViewsVisible::*)() const) &IGESDraw_SegmentedViewsVisible::DynamicType, "None");

// CLASS: IGESDRAW_SPECIFICMODULE
py::class_<IGESDraw_SpecificModule, opencascade::handle<IGESDraw_SpecificModule>, IGESData_SpecificModule> cls_IGESDraw_SpecificModule(mod, "IGESDraw_SpecificModule", "Defines Services attached to IGES Entities : Dump & OwnCorrect, for IGESDraw");

// Constructors
cls_IGESDraw_SpecificModule.def(py::init<>());

// Methods
cls_IGESDraw_SpecificModule.def("OwnDump", (void (IGESDraw_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_SpecificModule::OwnDump, "Specific Dump (own parameters) for IGESDraw", py::arg("CN"), py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));
cls_IGESDraw_SpecificModule.def("OwnCorrect", (Standard_Boolean (IGESDraw_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESDraw_SpecificModule::OwnCorrect, "Performs non-ambiguous Corrections on Entities which support them (Planar)", py::arg("CN"), py::arg("ent"));
cls_IGESDraw_SpecificModule.def_static("get_type_name_", (const char * (*)()) &IGESDraw_SpecificModule::get_type_name, "None");
cls_IGESDraw_SpecificModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_SpecificModule::get_type_descriptor, "None");
cls_IGESDraw_SpecificModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_SpecificModule::*)() const) &IGESDraw_SpecificModule::DynamicType, "None");

// CLASS: IGESDRAW_TOOLCIRCARRAYSUBFIGURE
py::class_<IGESDraw_ToolCircArraySubfigure> cls_IGESDraw_ToolCircArraySubfigure(mod, "IGESDraw_ToolCircArraySubfigure", "Tool to work on a CircArraySubfigure. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolCircArraySubfigure.def(py::init<>());

// Methods
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolCircArraySubfigure::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolCircArraySubfigure::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolCircArraySubfigure::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolCircArraySubfigure::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolCircArraySubfigure::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolCircArraySubfigure.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolCircArraySubfigure::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolCircArraySubfigure.def("ReadOwnParams", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolCircArraySubfigure::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolCircArraySubfigure.def("WriteOwnParams", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, IGESData_IGESWriter &) const) &IGESDraw_ToolCircArraySubfigure::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolCircArraySubfigure.def("OwnShared", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, Interface_EntityIterator &) const) &IGESDraw_ToolCircArraySubfigure::OwnShared, "Lists the Entities shared by a CircArraySubfigure <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolCircArraySubfigure.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &) const) &IGESDraw_ToolCircArraySubfigure::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolCircArraySubfigure.def("OwnCheck", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolCircArraySubfigure::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolCircArraySubfigure.def("OwnCopy", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, const opencascade::handle<IGESDraw_CircArraySubfigure> &, Interface_CopyTool &) const) &IGESDraw_ToolCircArraySubfigure::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolCircArraySubfigure.def("OwnDump", (void (IGESDraw_ToolCircArraySubfigure::*)(const opencascade::handle<IGESDraw_CircArraySubfigure> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolCircArraySubfigure::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLCONNECTPOINT
py::class_<IGESDraw_ToolConnectPoint> cls_IGESDraw_ToolConnectPoint(mod, "IGESDraw_ToolConnectPoint", "Tool to work on a ConnectPoint. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolConnectPoint.def(py::init<>());

// Methods
// cls_IGESDraw_ToolConnectPoint.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolConnectPoint::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolConnectPoint.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolConnectPoint::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolConnectPoint.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolConnectPoint::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolConnectPoint.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolConnectPoint::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolConnectPoint.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolConnectPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolConnectPoint.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolConnectPoint::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolConnectPoint.def("ReadOwnParams", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolConnectPoint::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolConnectPoint.def("WriteOwnParams", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, IGESData_IGESWriter &) const) &IGESDraw_ToolConnectPoint::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolConnectPoint.def("OwnShared", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, Interface_EntityIterator &) const) &IGESDraw_ToolConnectPoint::OwnShared, "Lists the Entities shared by a ConnectPoint <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolConnectPoint.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &) const) &IGESDraw_ToolConnectPoint::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolConnectPoint.def("OwnCheck", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolConnectPoint::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolConnectPoint.def("OwnCopy", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, const opencascade::handle<IGESDraw_ConnectPoint> &, Interface_CopyTool &) const) &IGESDraw_ToolConnectPoint::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolConnectPoint.def("OwnDump", (void (IGESDraw_ToolConnectPoint::*)(const opencascade::handle<IGESDraw_ConnectPoint> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolConnectPoint::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLDRAWING
py::class_<IGESDraw_ToolDrawing> cls_IGESDraw_ToolDrawing(mod, "IGESDraw_ToolDrawing", "Tool to work on a Drawing. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolDrawing.def(py::init<>());

// Methods
// cls_IGESDraw_ToolDrawing.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolDrawing::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolDrawing.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolDrawing::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolDrawing.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolDrawing::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolDrawing.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolDrawing::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolDrawing.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolDrawing::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolDrawing.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolDrawing::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolDrawing.def("ReadOwnParams", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolDrawing::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolDrawing.def("WriteOwnParams", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, IGESData_IGESWriter &) const) &IGESDraw_ToolDrawing::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolDrawing.def("OwnShared", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, Interface_EntityIterator &) const) &IGESDraw_ToolDrawing::OwnShared, "Lists the Entities shared by a Drawing <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolDrawing.def("OwnCorrect", (Standard_Boolean (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &) const) &IGESDraw_ToolDrawing::OwnCorrect, "Sets automatic unambiguous Correction on a Drawing (Null Views are removed from list)", py::arg("ent"));
cls_IGESDraw_ToolDrawing.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &) const) &IGESDraw_ToolDrawing::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolDrawing.def("OwnCheck", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolDrawing::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolDrawing.def("OwnCopy", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, const opencascade::handle<IGESDraw_Drawing> &, Interface_CopyTool &) const) &IGESDraw_ToolDrawing::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolDrawing.def("OwnDump", (void (IGESDraw_ToolDrawing::*)(const opencascade::handle<IGESDraw_Drawing> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolDrawing::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLDRAWINGWITHROTATION
py::class_<IGESDraw_ToolDrawingWithRotation> cls_IGESDraw_ToolDrawingWithRotation(mod, "IGESDraw_ToolDrawingWithRotation", "Tool to work on a DrawingWithRotation. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolDrawingWithRotation.def(py::init<>());

// Methods
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolDrawingWithRotation::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolDrawingWithRotation::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolDrawingWithRotation::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolDrawingWithRotation::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolDrawingWithRotation::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolDrawingWithRotation.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolDrawingWithRotation::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolDrawingWithRotation.def("ReadOwnParams", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolDrawingWithRotation::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolDrawingWithRotation.def("WriteOwnParams", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, IGESData_IGESWriter &) const) &IGESDraw_ToolDrawingWithRotation::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolDrawingWithRotation.def("OwnShared", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, Interface_EntityIterator &) const) &IGESDraw_ToolDrawingWithRotation::OwnShared, "Lists the Entities shared by a DrawingWithRotation <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolDrawingWithRotation.def("OwnCorrect", (Standard_Boolean (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &) const) &IGESDraw_ToolDrawingWithRotation::OwnCorrect, "Sets automatic unambiguous Correction on a DrawingWithRotation (Null Views are removed from list)", py::arg("ent"));
cls_IGESDraw_ToolDrawingWithRotation.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &) const) &IGESDraw_ToolDrawingWithRotation::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolDrawingWithRotation.def("OwnCheck", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolDrawingWithRotation::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolDrawingWithRotation.def("OwnCopy", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, const opencascade::handle<IGESDraw_DrawingWithRotation> &, Interface_CopyTool &) const) &IGESDraw_ToolDrawingWithRotation::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolDrawingWithRotation.def("OwnDump", (void (IGESDraw_ToolDrawingWithRotation::*)(const opencascade::handle<IGESDraw_DrawingWithRotation> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolDrawingWithRotation::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLLABELDISPLAY
py::class_<IGESDraw_ToolLabelDisplay> cls_IGESDraw_ToolLabelDisplay(mod, "IGESDraw_ToolLabelDisplay", "Tool to work on a LabelDisplay. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolLabelDisplay.def(py::init<>());

// Methods
// cls_IGESDraw_ToolLabelDisplay.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolLabelDisplay::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolLabelDisplay.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolLabelDisplay::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolLabelDisplay.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolLabelDisplay::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolLabelDisplay.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolLabelDisplay::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolLabelDisplay.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolLabelDisplay::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolLabelDisplay.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolLabelDisplay::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolLabelDisplay.def("ReadOwnParams", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolLabelDisplay::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolLabelDisplay.def("WriteOwnParams", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, IGESData_IGESWriter &) const) &IGESDraw_ToolLabelDisplay::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolLabelDisplay.def("OwnShared", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, Interface_EntityIterator &) const) &IGESDraw_ToolLabelDisplay::OwnShared, "Lists the Entities shared by a LabelDisplay <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolLabelDisplay.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &) const) &IGESDraw_ToolLabelDisplay::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolLabelDisplay.def("OwnCheck", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolLabelDisplay::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolLabelDisplay.def("OwnCopy", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, const opencascade::handle<IGESDraw_LabelDisplay> &, Interface_CopyTool &) const) &IGESDraw_ToolLabelDisplay::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolLabelDisplay.def("OwnDump", (void (IGESDraw_ToolLabelDisplay::*)(const opencascade::handle<IGESDraw_LabelDisplay> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolLabelDisplay::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLNETWORKSUBFIGURE
py::class_<IGESDraw_ToolNetworkSubfigure> cls_IGESDraw_ToolNetworkSubfigure(mod, "IGESDraw_ToolNetworkSubfigure", "Tool to work on a NetworkSubfigure. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolNetworkSubfigure.def(py::init<>());

// Methods
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolNetworkSubfigure::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolNetworkSubfigure::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolNetworkSubfigure::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolNetworkSubfigure::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolNetworkSubfigure::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigure.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolNetworkSubfigure::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolNetworkSubfigure.def("ReadOwnParams", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolNetworkSubfigure::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolNetworkSubfigure.def("WriteOwnParams", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, IGESData_IGESWriter &) const) &IGESDraw_ToolNetworkSubfigure::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolNetworkSubfigure.def("OwnShared", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, Interface_EntityIterator &) const) &IGESDraw_ToolNetworkSubfigure::OwnShared, "Lists the Entities shared by a NetworkSubfigure <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolNetworkSubfigure.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &) const) &IGESDraw_ToolNetworkSubfigure::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolNetworkSubfigure.def("OwnCheck", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolNetworkSubfigure::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolNetworkSubfigure.def("OwnCopy", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, const opencascade::handle<IGESDraw_NetworkSubfigure> &, Interface_CopyTool &) const) &IGESDraw_ToolNetworkSubfigure::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolNetworkSubfigure.def("OwnDump", (void (IGESDraw_ToolNetworkSubfigure::*)(const opencascade::handle<IGESDraw_NetworkSubfigure> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolNetworkSubfigure::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLNETWORKSUBFIGUREDEF
py::class_<IGESDraw_ToolNetworkSubfigureDef> cls_IGESDraw_ToolNetworkSubfigureDef(mod, "IGESDraw_ToolNetworkSubfigureDef", "Tool to work on a NetworkSubfigureDef. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolNetworkSubfigureDef.def(py::init<>());

// Methods
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolNetworkSubfigureDef::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolNetworkSubfigureDef::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolNetworkSubfigureDef::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolNetworkSubfigureDef::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolNetworkSubfigureDef::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolNetworkSubfigureDef.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolNetworkSubfigureDef::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolNetworkSubfigureDef.def("ReadOwnParams", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolNetworkSubfigureDef::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("WriteOwnParams", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, IGESData_IGESWriter &) const) &IGESDraw_ToolNetworkSubfigureDef::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("OwnShared", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, Interface_EntityIterator &) const) &IGESDraw_ToolNetworkSubfigureDef::OwnShared, "Lists the Entities shared by a NetworkSubfigureDef <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &) const) &IGESDraw_ToolNetworkSubfigureDef::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("OwnCheck", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolNetworkSubfigureDef::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("OwnCopy", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, Interface_CopyTool &) const) &IGESDraw_ToolNetworkSubfigureDef::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolNetworkSubfigureDef.def("OwnDump", (void (IGESDraw_ToolNetworkSubfigureDef::*)(const opencascade::handle<IGESDraw_NetworkSubfigureDef> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolNetworkSubfigureDef::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLPERSPECTIVEVIEW
py::class_<IGESDraw_ToolPerspectiveView> cls_IGESDraw_ToolPerspectiveView(mod, "IGESDraw_ToolPerspectiveView", "Tool to work on a PerspectiveView. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolPerspectiveView.def(py::init<>());

// Methods
// cls_IGESDraw_ToolPerspectiveView.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolPerspectiveView::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolPerspectiveView.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolPerspectiveView::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolPerspectiveView.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolPerspectiveView::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolPerspectiveView.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolPerspectiveView::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolPerspectiveView.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolPerspectiveView::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolPerspectiveView.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolPerspectiveView::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolPerspectiveView.def("ReadOwnParams", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolPerspectiveView::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolPerspectiveView.def("WriteOwnParams", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, IGESData_IGESWriter &) const) &IGESDraw_ToolPerspectiveView::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolPerspectiveView.def("OwnShared", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, Interface_EntityIterator &) const) &IGESDraw_ToolPerspectiveView::OwnShared, "Lists the Entities shared by a PerspectiveView <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolPerspectiveView.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &) const) &IGESDraw_ToolPerspectiveView::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolPerspectiveView.def("OwnCheck", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolPerspectiveView::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolPerspectiveView.def("OwnCopy", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, const opencascade::handle<IGESDraw_PerspectiveView> &, Interface_CopyTool &) const) &IGESDraw_ToolPerspectiveView::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolPerspectiveView.def("OwnDump", (void (IGESDraw_ToolPerspectiveView::*)(const opencascade::handle<IGESDraw_PerspectiveView> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolPerspectiveView::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLPLANAR
py::class_<IGESDraw_ToolPlanar> cls_IGESDraw_ToolPlanar(mod, "IGESDraw_ToolPlanar", "Tool to work on a Planar. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolPlanar.def(py::init<>());

// Methods
// cls_IGESDraw_ToolPlanar.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolPlanar::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolPlanar.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolPlanar::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolPlanar.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolPlanar::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolPlanar.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolPlanar::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolPlanar.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolPlanar::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolPlanar.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolPlanar::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolPlanar.def("ReadOwnParams", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolPlanar::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolPlanar.def("WriteOwnParams", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, IGESData_IGESWriter &) const) &IGESDraw_ToolPlanar::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolPlanar.def("OwnShared", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, Interface_EntityIterator &) const) &IGESDraw_ToolPlanar::OwnShared, "Lists the Entities shared by a Planar <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolPlanar.def("OwnCorrect", (Standard_Boolean (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &) const) &IGESDraw_ToolPlanar::OwnCorrect, "Sets automatic unambiguous Correction on a Planar (NbMatrices forced to 1)", py::arg("ent"));
cls_IGESDraw_ToolPlanar.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &) const) &IGESDraw_ToolPlanar::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolPlanar.def("OwnCheck", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolPlanar::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolPlanar.def("OwnCopy", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, const opencascade::handle<IGESDraw_Planar> &, Interface_CopyTool &) const) &IGESDraw_ToolPlanar::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolPlanar.def("OwnDump", (void (IGESDraw_ToolPlanar::*)(const opencascade::handle<IGESDraw_Planar> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolPlanar::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLRECTARRAYSUBFIGURE
py::class_<IGESDraw_ToolRectArraySubfigure> cls_IGESDraw_ToolRectArraySubfigure(mod, "IGESDraw_ToolRectArraySubfigure", "Tool to work on a RectArraySubfigure. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolRectArraySubfigure.def(py::init<>());

// Methods
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolRectArraySubfigure::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolRectArraySubfigure::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolRectArraySubfigure::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolRectArraySubfigure::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolRectArraySubfigure::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolRectArraySubfigure.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolRectArraySubfigure::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolRectArraySubfigure.def("ReadOwnParams", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolRectArraySubfigure::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolRectArraySubfigure.def("WriteOwnParams", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, IGESData_IGESWriter &) const) &IGESDraw_ToolRectArraySubfigure::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolRectArraySubfigure.def("OwnShared", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, Interface_EntityIterator &) const) &IGESDraw_ToolRectArraySubfigure::OwnShared, "Lists the Entities shared by a RectArraySubfigure <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolRectArraySubfigure.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &) const) &IGESDraw_ToolRectArraySubfigure::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolRectArraySubfigure.def("OwnCheck", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolRectArraySubfigure::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolRectArraySubfigure.def("OwnCopy", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, const opencascade::handle<IGESDraw_RectArraySubfigure> &, Interface_CopyTool &) const) &IGESDraw_ToolRectArraySubfigure::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolRectArraySubfigure.def("OwnDump", (void (IGESDraw_ToolRectArraySubfigure::*)(const opencascade::handle<IGESDraw_RectArraySubfigure> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolRectArraySubfigure::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLSEGMENTEDVIEWSVISIBLE
py::class_<IGESDraw_ToolSegmentedViewsVisible> cls_IGESDraw_ToolSegmentedViewsVisible(mod, "IGESDraw_ToolSegmentedViewsVisible", "Tool to work on a SegmentedViewsVisible. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolSegmentedViewsVisible.def(py::init<>());

// Methods
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolSegmentedViewsVisible::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolSegmentedViewsVisible::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolSegmentedViewsVisible::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolSegmentedViewsVisible::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolSegmentedViewsVisible::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolSegmentedViewsVisible.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolSegmentedViewsVisible::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolSegmentedViewsVisible.def("ReadOwnParams", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolSegmentedViewsVisible::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("WriteOwnParams", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, IGESData_IGESWriter &) const) &IGESDraw_ToolSegmentedViewsVisible::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("OwnShared", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, Interface_EntityIterator &) const) &IGESDraw_ToolSegmentedViewsVisible::OwnShared, "Lists the Entities shared by a SegmentedViewsVisible <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &) const) &IGESDraw_ToolSegmentedViewsVisible::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("OwnCheck", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolSegmentedViewsVisible::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("OwnCopy", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, Interface_CopyTool &) const) &IGESDraw_ToolSegmentedViewsVisible::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolSegmentedViewsVisible.def("OwnDump", (void (IGESDraw_ToolSegmentedViewsVisible::*)(const opencascade::handle<IGESDraw_SegmentedViewsVisible> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolSegmentedViewsVisible::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLVIEW
py::class_<IGESDraw_ToolView> cls_IGESDraw_ToolView(mod, "IGESDraw_ToolView", "Tool to work on a View. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolView.def(py::init<>());

// Methods
// cls_IGESDraw_ToolView.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolView::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolView.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolView::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolView.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolView::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolView.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolView::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolView.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolView::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolView.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolView::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolView.def("ReadOwnParams", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolView::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolView.def("WriteOwnParams", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, IGESData_IGESWriter &) const) &IGESDraw_ToolView::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolView.def("OwnShared", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, Interface_EntityIterator &) const) &IGESDraw_ToolView::OwnShared, "Lists the Entities shared by a View <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolView.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &) const) &IGESDraw_ToolView::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolView.def("OwnCheck", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolView::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolView.def("OwnCopy", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, const opencascade::handle<IGESDraw_View> &, Interface_CopyTool &) const) &IGESDraw_ToolView::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolView.def("OwnDump", (void (IGESDraw_ToolView::*)(const opencascade::handle<IGESDraw_View> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolView::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESDRAW_TOOLVIEWSVISIBLE
py::class_<IGESDraw_ToolViewsVisible> cls_IGESDraw_ToolViewsVisible(mod, "IGESDraw_ToolViewsVisible", "Tool to work on a ViewsVisible. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolViewsVisible.def(py::init<>());

// Methods
// cls_IGESDraw_ToolViewsVisible.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolViewsVisible::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolViewsVisible.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolViewsVisible::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisible.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolViewsVisible::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolViewsVisible.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolViewsVisible::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisible.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolViewsVisible::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisible.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolViewsVisible::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolViewsVisible.def("ReadOwnParams", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolViewsVisible::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolViewsVisible.def("WriteOwnParams", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, IGESData_IGESWriter &) const) &IGESDraw_ToolViewsVisible::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolViewsVisible.def("OwnShared", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, Interface_EntityIterator &) const) &IGESDraw_ToolViewsVisible::OwnShared, "Lists the Entities shared by a ViewsVisible <ent>, from its specific (own) parameters shared not implied (the Views)", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolViewsVisible.def("OwnImplied", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, Interface_EntityIterator &) const) &IGESDraw_ToolViewsVisible::OwnImplied, "Lists the Entities shared by a ViewsVisible <ent>, from its specific (own) implied parameters : the Displayed Entities", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolViewsVisible.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &) const) &IGESDraw_ToolViewsVisible::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolViewsVisible.def("OwnCheck", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolViewsVisible::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolViewsVisible.def("OwnCopy", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, const opencascade::handle<IGESDraw_ViewsVisible> &, Interface_CopyTool &) const) &IGESDraw_ToolViewsVisible::OwnCopy, "Copies Specific Parameters shared not implied, i.e. all but the Displayed Entities", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolViewsVisible.def("OwnRenew", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, const opencascade::handle<IGESDraw_ViewsVisible> &, const Interface_CopyTool &) const) &IGESDraw_ToolViewsVisible::OwnRenew, "Copies Specific implied Parameters : the Displayed Entities which have already been copied", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolViewsVisible.def("OwnWhenDelete", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &) const) &IGESDraw_ToolViewsVisible::OwnWhenDelete, "Clears specific implied parameters, which cause looping structures; required for deletion", py::arg("ent"));
cls_IGESDraw_ToolViewsVisible.def("OwnDump", (void (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolViewsVisible::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));
cls_IGESDraw_ToolViewsVisible.def("OwnCorrect", (Standard_Boolean (IGESDraw_ToolViewsVisible::*)(const opencascade::handle<IGESDraw_ViewsVisible> &) const) &IGESDraw_ToolViewsVisible::OwnCorrect, "Sets automatic unambiguous Correction on a ViewsVisible (all displayed entities must refer to <ent> in directory part, else the list is cleared)", py::arg("ent"));

// CLASS: IGESDRAW_TOOLVIEWSVISIBLEWITHATTR
py::class_<IGESDraw_ToolViewsVisibleWithAttr> cls_IGESDraw_ToolViewsVisibleWithAttr(mod, "IGESDraw_ToolViewsVisibleWithAttr", "Tool to work on a ViewsVisibleWithAttr. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESDraw_ToolViewsVisibleWithAttr.def(py::init<>());

// Methods
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator new_", (void * (*)(size_t)) &IGESDraw_ToolViewsVisibleWithAttr::operator new, "None", py::arg("theSize"));
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator delete_", (void (*)(void *)) &IGESDraw_ToolViewsVisibleWithAttr::operator delete, "None", py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator new[]_", (void * (*)(size_t)) &IGESDraw_ToolViewsVisibleWithAttr::operator new[], "None", py::arg("theSize"));
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator delete[]_", (void (*)(void *)) &IGESDraw_ToolViewsVisibleWithAttr::operator delete[], "None", py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator new_", (void * (*)(size_t, void *)) &IGESDraw_ToolViewsVisibleWithAttr::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESDraw_ToolViewsVisibleWithAttr.def_static("operator delete_", (void (*)(void *, void *)) &IGESDraw_ToolViewsVisibleWithAttr::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("ReadOwnParams", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESDraw_ToolViewsVisibleWithAttr::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("WriteOwnParams", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, IGESData_IGESWriter &) const) &IGESDraw_ToolViewsVisibleWithAttr::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnShared", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, Interface_EntityIterator &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnShared, "Lists the Entities shared by a ViewsVisibleWithAttr <ent>, from its specific (own) parameters shared not implied, i.e. all but the Displayed Entities", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnImplied", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, Interface_EntityIterator &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnImplied, "Lists the Entities shared by a ViewsVisible <ent>, from its specific (own) implied parameters : the Displayed Entities", py::arg("ent"), py::arg("iter"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("DirChecker", (IGESData_DirChecker (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &) const) &IGESDraw_ToolViewsVisibleWithAttr::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnCheck", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnCopy", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, Interface_CopyTool &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnCopy, "Copies Specific Parameters shared not implied, i.e. all but the Displayed Entities", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnRenew", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const Interface_CopyTool &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnRenew, "Copies Specific implied Parameters : the Displayed Entities which have already been copied", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnWhenDelete", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnWhenDelete, "Clears specific implied parameters, which cause looping structures; required for deletion", py::arg("ent"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnDump", (void (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));
cls_IGESDraw_ToolViewsVisibleWithAttr.def("OwnCorrect", (Standard_Boolean (IGESDraw_ToolViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_ViewsVisibleWithAttr> &) const) &IGESDraw_ToolViewsVisibleWithAttr::OwnCorrect, "Sets automatic unambiguous Correction on a ViewsVisibleWithAttr (all displayed entities must refer to <ent> in directory part, else the list is cleared)", py::arg("ent"));

// CLASS: IGESDRAW_VIEW
py::class_<IGESDraw_View, opencascade::handle<IGESDraw_View>, IGESData_ViewKindEntity> cls_IGESDraw_View(mod, "IGESDraw_View", "defines IGES View Entity, Type <410> Form <0> in package IGESDraw");

// Constructors
cls_IGESDraw_View.def(py::init<>());

// Methods
cls_IGESDraw_View.def("Init", (void (IGESDraw_View::*)(const Standard_Integer, const Standard_Real, const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &)) &IGESDraw_View::Init, "This method is used to set fields of the class View - aViewNum : View number - aScale : Scale factor - aLeftPlane : Left plane of view volume - aTopPlane : Top plane of view volume - aRightPlane : Right plane of view volume - aBottomPlane : Bottom plane of view volume - aBackPlane : Back plane of view volume - aFrontPlane : Front plane of view volume", py::arg("aViewNum"), py::arg("aScale"), py::arg("aLeftPlane"), py::arg("aTopPlane"), py::arg("aRightPlane"), py::arg("aBottomPlane"), py::arg("aBackPlane"), py::arg("aFrontPlane"));
cls_IGESDraw_View.def("IsSingle", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::IsSingle, "Returns True (for a single view)");
cls_IGESDraw_View.def("NbViews", (Standard_Integer (IGESDraw_View::*)() const) &IGESDraw_View::NbViews, "Returns 1 (single view)");
cls_IGESDraw_View.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_View::*)(const Standard_Integer) const) &IGESDraw_View::ViewItem, "For a single view, returns <me> whatever <num>", py::arg("num"));
cls_IGESDraw_View.def("ViewNumber", (Standard_Integer (IGESDraw_View::*)() const) &IGESDraw_View::ViewNumber, "returns integer number identifying view orientation");
cls_IGESDraw_View.def("ScaleFactor", (Standard_Real (IGESDraw_View::*)() const) &IGESDraw_View::ScaleFactor, "returns the scale factor(Default = 1.0)");
cls_IGESDraw_View.def("HasLeftPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasLeftPlane, "returns False if left side of view volume is not present");
cls_IGESDraw_View.def("LeftPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::LeftPlane, "returns the left side of view volume, or null handle");
cls_IGESDraw_View.def("HasTopPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasTopPlane, "returns False if top of view volume is not present");
cls_IGESDraw_View.def("TopPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::TopPlane, "returns the top of view volume, or null handle");
cls_IGESDraw_View.def("HasRightPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasRightPlane, "returns False if right side of view volume is not present");
cls_IGESDraw_View.def("RightPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::RightPlane, "returns the right side of view volume, or null handle");
cls_IGESDraw_View.def("HasBottomPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasBottomPlane, "returns False if bottom of view volume is not present");
cls_IGESDraw_View.def("BottomPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::BottomPlane, "returns the bottom of view volume, or null handle");
cls_IGESDraw_View.def("HasBackPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasBackPlane, "returns False if back of view volume is not present");
cls_IGESDraw_View.def("BackPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::BackPlane, "returns the back of view volume, or null handle");
cls_IGESDraw_View.def("HasFrontPlane", (Standard_Boolean (IGESDraw_View::*)() const) &IGESDraw_View::HasFrontPlane, "returns False if front of view volume is not present");
cls_IGESDraw_View.def("FrontPlane", (opencascade::handle<IGESGeom_Plane> (IGESDraw_View::*)() const) &IGESDraw_View::FrontPlane, "returns the front of view volume, or null handle");
cls_IGESDraw_View.def("ViewMatrix", (opencascade::handle<IGESData_TransfEntity> (IGESDraw_View::*)() const) &IGESDraw_View::ViewMatrix, "returns the Transformation Matrix");
cls_IGESDraw_View.def("ModelToView", (gp_XYZ (IGESDraw_View::*)(const gp_XYZ &) const) &IGESDraw_View::ModelToView, "returns XYZ from the Model space to the View space by applying the View Matrix", py::arg("coords"));
cls_IGESDraw_View.def_static("get_type_name_", (const char * (*)()) &IGESDraw_View::get_type_name, "None");
cls_IGESDraw_View.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_View::get_type_descriptor, "None");
cls_IGESDraw_View.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_View::*)() const) &IGESDraw_View::DynamicType, "None");

// CLASS: IGESDRAW_VIEWSVISIBLE
py::class_<IGESDraw_ViewsVisible, opencascade::handle<IGESDraw_ViewsVisible>, IGESData_ViewKindEntity> cls_IGESDraw_ViewsVisible(mod, "IGESDraw_ViewsVisible", "Defines IGESViewsVisible, Type <402>, Form <3> in package IGESDraw");

// Constructors
cls_IGESDraw_ViewsVisible.def(py::init<>());

// Methods
cls_IGESDraw_ViewsVisible.def("Init", (void (IGESDraw_ViewsVisible::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_ViewsVisible::Init, "This method is used to set the fields of the class ViewsVisible - allViewEntities : All View kind entities - allDisplayEntity : All entities whose display is specified", py::arg("allViewEntities"), py::arg("allDisplayEntity"));
cls_IGESDraw_ViewsVisible.def("InitImplied", (void (IGESDraw_ViewsVisible::*)(const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_ViewsVisible::InitImplied, "Changes only the list of Displayed Entities (Null allowed)", py::arg("allDisplayEntity"));
cls_IGESDraw_ViewsVisible.def("IsSingle", (Standard_Boolean (IGESDraw_ViewsVisible::*)() const) &IGESDraw_ViewsVisible::IsSingle, "Returns False (for a complex view)");
cls_IGESDraw_ViewsVisible.def("NbViews", (Standard_Integer (IGESDraw_ViewsVisible::*)() const) &IGESDraw_ViewsVisible::NbViews, "returns the Number of views visible");
cls_IGESDraw_ViewsVisible.def("NbDisplayedEntities", (Standard_Integer (IGESDraw_ViewsVisible::*)() const) &IGESDraw_ViewsVisible::NbDisplayedEntities, "returns the number of entities displayed in the Views or zero if no Entities specified in these Views");
cls_IGESDraw_ViewsVisible.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_ViewsVisible::*)(const Standard_Integer) const) &IGESDraw_ViewsVisible::ViewItem, "returns the Index'th ViewKindEntity Entity raises exception if Index <= 0 or Index > NbViewsVisible()", py::arg("Index"));
cls_IGESDraw_ViewsVisible.def("DisplayedEntity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_ViewsVisible::*)(const Standard_Integer) const) &IGESDraw_ViewsVisible::DisplayedEntity, "returns the Index'th entity whose display is being specified by this associativity instance raises exception if Index <= 0 or Index > NbEntityDisplayed()", py::arg("Index"));
cls_IGESDraw_ViewsVisible.def_static("get_type_name_", (const char * (*)()) &IGESDraw_ViewsVisible::get_type_name, "None");
cls_IGESDraw_ViewsVisible.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_ViewsVisible::get_type_descriptor, "None");
cls_IGESDraw_ViewsVisible.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_ViewsVisible::*)() const) &IGESDraw_ViewsVisible::DynamicType, "None");

// CLASS: IGESDRAW_VIEWSVISIBLEWITHATTR
py::class_<IGESDraw_ViewsVisibleWithAttr, opencascade::handle<IGESDraw_ViewsVisibleWithAttr>, IGESData_ViewKindEntity> cls_IGESDraw_ViewsVisibleWithAttr(mod, "IGESDraw_ViewsVisibleWithAttr", "defines IGESViewsVisibleWithAttr, Type <402>, Form <4> in package IGESDraw");

// Constructors
cls_IGESDraw_ViewsVisibleWithAttr.def(py::init<>());

// Methods
cls_IGESDraw_ViewsVisibleWithAttr.def("Init", (void (IGESDraw_ViewsVisibleWithAttr::*)(const opencascade::handle<IGESDraw_HArray1OfViewKindEntity> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESBasic_HArray1OfLineFontEntity> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESGraph_HArray1OfColor> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_ViewsVisibleWithAttr::Init, "This method is used to set fields of the class ViewsVisibleWithAttr - allViewEntities : All View kind entities - allLineFonts : All Line Font values or zero(0) - allLineDefinitions : Line Font Definition (if Line Font value = 0) - allColorValues : All Color values - allColorDefinitions : All Color Definition Entities - allLineWeights : All Line Weight values - allDisplayEntities : Entities which are member of this associativity raises exception if Lengths of allViewEntities, allLineFonts, allColorValues,allColorDefinitions, allLineWeights are not same", py::arg("allViewEntities"), py::arg("allLineFonts"), py::arg("allLineDefinitions"), py::arg("allColorValues"), py::arg("allColorDefinitions"), py::arg("allLineWeights"), py::arg("allDisplayEntities"));
cls_IGESDraw_ViewsVisibleWithAttr.def("InitImplied", (void (IGESDraw_ViewsVisibleWithAttr::*)(const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESDraw_ViewsVisibleWithAttr::InitImplied, "Changes only the list of Displayed Entities (Null allowed)", py::arg("allDisplayEntity"));
cls_IGESDraw_ViewsVisibleWithAttr.def("IsSingle", (Standard_Boolean (IGESDraw_ViewsVisibleWithAttr::*)() const) &IGESDraw_ViewsVisibleWithAttr::IsSingle, "Returns False (for a complex view)");
cls_IGESDraw_ViewsVisibleWithAttr.def("NbViews", (Standard_Integer (IGESDraw_ViewsVisibleWithAttr::*)() const) &IGESDraw_ViewsVisibleWithAttr::NbViews, "returns the number of Views containing the view visible, line font, color number, and line weight information");
cls_IGESDraw_ViewsVisibleWithAttr.def("NbDisplayedEntities", (Standard_Integer (IGESDraw_ViewsVisibleWithAttr::*)() const) &IGESDraw_ViewsVisibleWithAttr::NbDisplayedEntities, "returns the number of entities which have this particular set of display characteristic, or zero if no Entities specified");
cls_IGESDraw_ViewsVisibleWithAttr.def("ViewItem", (opencascade::handle<IGESData_ViewKindEntity> (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::ViewItem, "returns the Index'th ViewKindEntity entity raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("LineFontValue", (Standard_Integer (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::LineFontValue, "returns the Index'th Line font value or zero raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("IsFontDefinition", (Standard_Boolean (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::IsFontDefinition, "returns True if the Index'th Line Font Definition is specified else returns False raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("FontDefinition", (opencascade::handle<IGESData_LineFontEntity> (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::FontDefinition, "returns the Index'th Line Font Definition Entity or NULL(0) raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("ColorValue", (Standard_Integer (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::ColorValue, "returns the Index'th Color number value raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("IsColorDefinition", (Standard_Boolean (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::IsColorDefinition, "returns True if Index'th Color Definition is specified else returns False raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("ColorDefinition", (opencascade::handle<IGESGraph_Color> (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::ColorDefinition, "returns the Index'th Color Definition Entity raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("LineWeightItem", (Standard_Integer (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::LineWeightItem, "returns the Index'th Color Line Weight raises exception if Index <= 0 or Index > NbViews()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def("DisplayedEntity", (opencascade::handle<IGESData_IGESEntity> (IGESDraw_ViewsVisibleWithAttr::*)(const Standard_Integer) const) &IGESDraw_ViewsVisibleWithAttr::DisplayedEntity, "returns Index'th Display entity with this particular characteristics raises exception if Index <= 0 or Index > NbEntities()", py::arg("Index"));
cls_IGESDraw_ViewsVisibleWithAttr.def_static("get_type_name_", (const char * (*)()) &IGESDraw_ViewsVisibleWithAttr::get_type_name, "None");
cls_IGESDraw_ViewsVisibleWithAttr.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESDraw_ViewsVisibleWithAttr::get_type_descriptor, "None");
cls_IGESDraw_ViewsVisibleWithAttr.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESDraw_ViewsVisibleWithAttr::*)() const) &IGESDraw_ViewsVisibleWithAttr::DynamicType, "None");


}
