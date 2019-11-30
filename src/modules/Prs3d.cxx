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
#include <Prs3d_VertexDrawMode.hxx>
#include <Prs3d_TypeOfHLR.hxx>
#include <Prs3d_DimensionArrowOrientation.hxx>
#include <Prs3d_DimensionTextHorizontalPosition.hxx>
#include <Prs3d_DimensionTextVerticalPosition.hxx>
#include <Prs3d_TypeOfHighlight.hxx>
#include <Prs3d_DatumAttribute.hxx>
#include <Prs3d_DatumAxes.hxx>
#include <Prs3d_DatumMode.hxx>
#include <Prs3d_DatumParts.hxx>
#include <Prs3d_TypeOfLinePicking.hxx>
#include <Prs3d_DimensionUnits.hxx>
#include <TCollection_AsciiString.hxx>
#include <Graphic3d_PresentationAttributes.hxx>
#include <Standard_Std.hxx>
#include <Prs3d_Drawer.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Type.hxx>
#include <Aspect_TypeOfDeflection.hxx>
#include <Standard_TypeDef.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_PointAspect.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Prs3d_PlaneAspect.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_DatumAspect.hxx>
#include <GeomAbs_Shape.hxx>
#include <Prs3d_DimensionAspect.hxx>
#include <Graphic3d_ShaderProgram.hxx>
#include <Graphic3d_GroupAspect.hxx>
#include <Graphic3d_TypeOfShadingModel.hxx>
#include <Standard_OStream.hxx>
#include <Graphic3d_Structure.hxx>
#include <Prs3d_Presentation.hxx>
#include <Standard_Transient.hxx>
#include <Prs3d_BasicAspect.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Quantity_Color.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Graphic3d_HorizontalTextAlignment.hxx>
#include <Graphic3d_VerticalTextAlignment.hxx>
#include <Graphic3d_TextPath.hxx>
#include <HLRAlgo_Projector.hxx>
#include <Prs3d_Projector.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Aspect_TypeOfFacingModel.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Aspect_TypeOfMarker.hxx>
#include <TColStd_HArray1OfByte.hxx>
#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_MarkerImage.hxx>
#include <NCollection_DataMap.hxx>
#include <Standard.hxx>
#include <Graphic3d_Group.hxx>
#include <PrsMgr_PresentationManager.hxx>
#include <Prs3d_Root.hxx>
#include <NCollection_List.hxx>
#include <TColgp_HSequenceOfPnt.hxx>
#include <Prs3d_NListOfSequenceOfPnt.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Shape.hxx>
#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Prs3d.hxx>
#include <Graphic3d_ArrayOfTriangles.hxx>
#include <gp_Ax1.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <gp_Dir.hxx>
#include <Prs3d_Arrow.hxx>
#include <Standard_RangeError.hxx>
#include <Prs3d_InvalidAngle.hxx>
#include <Standard_SStream.hxx>
#include <Prs3d_NListIteratorOfListOfSequenceOfPnt.hxx>
#include <Prs3d_PresentationShadow.hxx>
#include <Graphic3d_StructureManager.hxx>
#include <Graphic3d_ViewAffinity.hxx>
#include <TopoDS_Face.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS_Vertex.hxx>
#include <Poly_Triangulation.hxx>
#include <TopLoc_Location.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Polygon3D.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <Prs3d_ShapeTool.hxx>
#include <TCollection_ExtendedString.hxx>
#include <gp_Ax2.hxx>
#include <Prs3d_Text.hxx>
#include <gp_Trsf.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <NCollection_Array1.hxx>
#include <Prs3d_ToolQuadric.hxx>
#include <Prs3d_ToolCylinder.hxx>
#include <Prs3d_ToolDisk.hxx>
#include <Prs3d_ToolSector.hxx>
#include <Prs3d_ToolSphere.hxx>
#include <bind_NCollection_List.hxx>
#include <bind_NCollection_TListIterator.hxx>

PYBIND11_MODULE(Prs3d, mod) {

py::module::import("OCCT.TCollection");
py::module::import("OCCT.Graphic3d");
py::module::import("OCCT.Standard");
py::module::import("OCCT.Aspect");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.Quantity");
py::module::import("OCCT.HLRAlgo");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.gp");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.Bnd");
py::module::import("OCCT.TopTools");
py::module::import("OCCT.Poly");
py::module::import("OCCT.TopLoc");
py::module::import("OCCT.TopExp");

// ENUM: PRS3D_VERTEXDRAWMODE
py::enum_<Prs3d_VertexDrawMode>(mod, "Prs3d_VertexDrawMode", "Describes supported modes of visualization of the shape's vertices: VDM_Isolated - only isolated vertices (not belonging to a face) are displayed. VDM_All - all vertices of the shape are displayed. VDM_Inherited - the global settings are inherited and applied to the shape's presentation.")
	.value("Prs3d_VDM_Isolated", Prs3d_VertexDrawMode::Prs3d_VDM_Isolated)
	.value("Prs3d_VDM_All", Prs3d_VertexDrawMode::Prs3d_VDM_All)
	.value("Prs3d_VDM_Inherited", Prs3d_VertexDrawMode::Prs3d_VDM_Inherited)
	.export_values();


// ENUM: PRS3D_TYPEOFHLR
py::enum_<Prs3d_TypeOfHLR>(mod, "Prs3d_TypeOfHLR", "Declares types of hidden line removal algorithm. TOH_Algo enables using of exact HLR algorithm. TOH_PolyAlgo enables using of polygonal HLR algorithm. TOH_NotSet is used by Prs3d_Drawer class, it means that the drawer should return the global value. For more details see Prs3d_Drawer class, AIS_Shape::Compute() method and HLRAlgo package from TKHLR toolkit.")
	.value("Prs3d_TOH_NotSet", Prs3d_TypeOfHLR::Prs3d_TOH_NotSet)
	.value("Prs3d_TOH_PolyAlgo", Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo)
	.value("Prs3d_TOH_Algo", Prs3d_TypeOfHLR::Prs3d_TOH_Algo)
	.export_values();


// ENUM: PRS3D_DIMENSIONARROWORIENTATION
py::enum_<Prs3d_DimensionArrowOrientation>(mod, "Prs3d_DimensionArrowOrientation", "Specifies dimension arrow location and orientation. DAO_Internal - arrows 'inside', pointing outwards. DAO_External - arrows 'outside', pointing inwards. DAO_Fit - arrows oriented inside if value label with arrowtips fit the dimension line, otherwise - externally")
	.value("Prs3d_DAO_Internal", Prs3d_DimensionArrowOrientation::Prs3d_DAO_Internal)
	.value("Prs3d_DAO_External", Prs3d_DimensionArrowOrientation::Prs3d_DAO_External)
	.value("Prs3d_DAO_Fit", Prs3d_DimensionArrowOrientation::Prs3d_DAO_Fit)
	.export_values();


// ENUM: PRS3D_DIMENSIONTEXTHORIZONTALPOSITION
py::enum_<Prs3d_DimensionTextHorizontalPosition>(mod, "Prs3d_DimensionTextHorizontalPosition", "Specifies options for positioning dimension value label in horizontal direction. DTHP_Left - value label located at left side on dimension extension. DTHP_Right - value label located at right side on dimension extension. DTHP_Center - value label located at center of dimension line. DTHP_Fit - value label located automatically at left side if does not fits the dimension space, otherwise the value label is placed at center.")
	.value("Prs3d_DTHP_Left", Prs3d_DimensionTextHorizontalPosition::Prs3d_DTHP_Left)
	.value("Prs3d_DTHP_Right", Prs3d_DimensionTextHorizontalPosition::Prs3d_DTHP_Right)
	.value("Prs3d_DTHP_Center", Prs3d_DimensionTextHorizontalPosition::Prs3d_DTHP_Center)
	.value("Prs3d_DTHP_Fit", Prs3d_DimensionTextHorizontalPosition::Prs3d_DTHP_Fit)
	.export_values();


// ENUM: PRS3D_DIMENSIONTEXTVERTICALPOSITION
py::enum_<Prs3d_DimensionTextVerticalPosition>(mod, "Prs3d_DimensionTextVerticalPosition", "Specifies options for positioning dimension value label in vertical direction with respect to dimension (extension) line. DTVP_Above - text label is located above the dimension or extension line. DTVP_Below - text label is located below the dimension or extension line. DTVP_Center - the text label middle-point is in line with dimension or extension line.")
	.value("Prs3d_DTVP_Above", Prs3d_DimensionTextVerticalPosition::Prs3d_DTVP_Above)
	.value("Prs3d_DTVP_Below", Prs3d_DimensionTextVerticalPosition::Prs3d_DTVP_Below)
	.value("Prs3d_DTVP_Center", Prs3d_DimensionTextVerticalPosition::Prs3d_DTVP_Center)
	.export_values();


// ENUM: PRS3D_TYPEOFHIGHLIGHT
py::enum_<Prs3d_TypeOfHighlight>(mod, "Prs3d_TypeOfHighlight", "Type of highlighting to apply specific style.")
	.value("Prs3d_TypeOfHighlight_None", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_None)
	.value("Prs3d_TypeOfHighlight_Selected", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Selected)
	.value("Prs3d_TypeOfHighlight_Dynamic", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Dynamic)
	.value("Prs3d_TypeOfHighlight_LocalSelected", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalSelected)
	.value("Prs3d_TypeOfHighlight_LocalDynamic", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalDynamic)
	.value("Prs3d_TypeOfHighlight_SubIntensity", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_SubIntensity)
	.value("Prs3d_TypeOfHighlight_NB", Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_NB)
	.export_values();


// ENUM: PRS3D_DATUMATTRIBUTE
py::enum_<Prs3d_DatumAttribute>(mod, "Prs3d_DatumAttribute", "Enumeration defining a part of datum aspect, see Prs3d_Datum.")
	.value("Prs3d_DA_XAxisLength", Prs3d_DatumAttribute::Prs3d_DA_XAxisLength)
	.value("Prs3d_DA_YAxisLength", Prs3d_DatumAttribute::Prs3d_DA_YAxisLength)
	.value("Prs3d_DA_ZAxisLength", Prs3d_DatumAttribute::Prs3d_DA_ZAxisLength)
	.value("Prs3d_DP_ShadingTubeRadiusPercent", Prs3d_DatumAttribute::Prs3d_DP_ShadingTubeRadiusPercent)
	.value("Prs3d_DP_ShadingConeRadiusPercent", Prs3d_DatumAttribute::Prs3d_DP_ShadingConeRadiusPercent)
	.value("Prs3d_DP_ShadingConeLengthPercent", Prs3d_DatumAttribute::Prs3d_DP_ShadingConeLengthPercent)
	.value("Prs3d_DP_ShadingOriginRadiusPercent", Prs3d_DatumAttribute::Prs3d_DP_ShadingOriginRadiusPercent)
	.value("Prs3d_DP_ShadingNumberOfFacettes", Prs3d_DatumAttribute::Prs3d_DP_ShadingNumberOfFacettes)
	.export_values();


// ENUM: PRS3D_DATUMAXES
py::enum_<Prs3d_DatumAxes>(mod, "Prs3d_DatumAxes", "Enumeration defining an axes used in datum aspect, see Prs3d_Datum.")
	.value("Prs3d_DA_XAxis", Prs3d_DatumAxes::Prs3d_DA_XAxis)
	.value("Prs3d_DA_YAxis", Prs3d_DatumAxes::Prs3d_DA_YAxis)
	.value("Prs3d_DA_ZAxis", Prs3d_DatumAxes::Prs3d_DA_ZAxis)
	.value("Prs3d_DA_XYAxis", Prs3d_DatumAxes::Prs3d_DA_XYAxis)
	.value("Prs3d_DA_YZAxis", Prs3d_DatumAxes::Prs3d_DA_YZAxis)
	.value("Prs3d_DA_XZAxis", Prs3d_DatumAxes::Prs3d_DA_XZAxis)
	.value("Prs3d_DA_XYZAxis", Prs3d_DatumAxes::Prs3d_DA_XYZAxis)
	.export_values();


// ENUM: PRS3D_DATUMMODE
py::enum_<Prs3d_DatumMode>(mod, "Prs3d_DatumMode", "Enumeration defining a mode of datum graphic presentation, see Prs3d_Datum.")
	.value("Prs3d_DM_WireFrame", Prs3d_DatumMode::Prs3d_DM_WireFrame)
	.value("Prs3d_DM_Shaded", Prs3d_DatumMode::Prs3d_DM_Shaded)
	.export_values();


// ENUM: PRS3D_DATUMPARTS
py::enum_<Prs3d_DatumParts>(mod, "Prs3d_DatumParts", "Enumeration defining a part of datum aspect, see Prs3d_Datum.")
	.value("Prs3d_DP_Origin", Prs3d_DatumParts::Prs3d_DP_Origin)
	.value("Prs3d_DP_XAxis", Prs3d_DatumParts::Prs3d_DP_XAxis)
	.value("Prs3d_DP_YAxis", Prs3d_DatumParts::Prs3d_DP_YAxis)
	.value("Prs3d_DP_ZAxis", Prs3d_DatumParts::Prs3d_DP_ZAxis)
	.value("Prs3d_DP_XArrow", Prs3d_DatumParts::Prs3d_DP_XArrow)
	.value("Prs3d_DP_YArrow", Prs3d_DatumParts::Prs3d_DP_YArrow)
	.value("Prs3d_DP_ZArrow", Prs3d_DatumParts::Prs3d_DP_ZArrow)
	.value("Prs3d_DP_XOYAxis", Prs3d_DatumParts::Prs3d_DP_XOYAxis)
	.value("Prs3d_DP_YOZAxis", Prs3d_DatumParts::Prs3d_DP_YOZAxis)
	.value("Prs3d_DP_XOZAxis", Prs3d_DatumParts::Prs3d_DP_XOZAxis)
	.value("Prs3d_DP_None", Prs3d_DatumParts::Prs3d_DP_None)
	.export_values();


// ENUM: PRS3D_TYPEOFLINEPICKING
py::enum_<Prs3d_TypeOfLinePicking>(mod, "Prs3d_TypeOfLinePicking", "None")
	.value("Prs3d_TOLP_Point", Prs3d_TypeOfLinePicking::Prs3d_TOLP_Point)
	.value("Prs3d_TOLP_Segment", Prs3d_TypeOfLinePicking::Prs3d_TOLP_Segment)
	.export_values();


// CLASS: PRS3D_DIMENSIONUNITS
py::class_<Prs3d_DimensionUnits> cls_Prs3d_DimensionUnits(mod, "Prs3d_DimensionUnits", "This class provides units for two dimension groups: - lengthes (length, radius, diameter) - angles");

// Constructors
cls_Prs3d_DimensionUnits.def(py::init<>());
cls_Prs3d_DimensionUnits.def(py::init<const Prs3d_DimensionUnits &>(), py::arg("theUnits"));

// Methods
cls_Prs3d_DimensionUnits.def("SetAngleUnits", (void (Prs3d_DimensionUnits::*)(const TCollection_AsciiString &)) &Prs3d_DimensionUnits::SetAngleUnits, "Sets angle units", py::arg("theUnits"));
cls_Prs3d_DimensionUnits.def("GetAngleUnits", (const TCollection_AsciiString & (Prs3d_DimensionUnits::*)() const) &Prs3d_DimensionUnits::GetAngleUnits, "Returns angle units");
cls_Prs3d_DimensionUnits.def("SetLengthUnits", (void (Prs3d_DimensionUnits::*)(const TCollection_AsciiString &)) &Prs3d_DimensionUnits::SetLengthUnits, "Sets length units", py::arg("theUnits"));
cls_Prs3d_DimensionUnits.def("GetLengthUnits", (const TCollection_AsciiString & (Prs3d_DimensionUnits::*)() const) &Prs3d_DimensionUnits::GetLengthUnits, "Returns length units");

// CLASS: PRS3D_DRAWER
py::class_<Prs3d_Drawer, opencascade::handle<Prs3d_Drawer>, Graphic3d_PresentationAttributes> cls_Prs3d_Drawer(mod, "Prs3d_Drawer", "A graphic attribute manager which governs how objects such as color, width, line thickness and deflection are displayed. A drawer includes an instance of the Aspect classes with particular default values.");

// Constructors
cls_Prs3d_Drawer.def(py::init<>());

// Methods
cls_Prs3d_Drawer.def_static("get_type_name_", (const char * (*)()) &Prs3d_Drawer::get_type_name, "None");
cls_Prs3d_Drawer.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_Drawer::get_type_descriptor, "None");
cls_Prs3d_Drawer.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DynamicType, "None");
cls_Prs3d_Drawer.def("SetTypeOfDeflection", (void (Prs3d_Drawer::*)(const Aspect_TypeOfDeflection)) &Prs3d_Drawer::SetTypeOfDeflection, "Sets the type of chordal deflection. This indicates whether the deflection value is absolute or relative to the size of the object.", py::arg("theTypeOfDeflection"));
cls_Prs3d_Drawer.def("TypeOfDeflection", (Aspect_TypeOfDeflection (Prs3d_Drawer::*)() const) &Prs3d_Drawer::TypeOfDeflection, "Returns the type of chordal deflection. This indicates whether the deflection value is absolute or relative to the size of the object.");
cls_Prs3d_Drawer.def("HasOwnTypeOfDeflection", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnTypeOfDeflection, "Returns true if the drawer has a type of deflection setting active.");
cls_Prs3d_Drawer.def("SetMaximalChordialDeviation", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetMaximalChordialDeviation, "Defines the maximal chordial deviation when drawing any curve. Even if the type of deviation is set to TOD_Relative, this value is used by: Prs3d_DeflectionCurve Prs3d_WFDeflectionSurface Prs3d_WFDeflectionRestrictedFace", py::arg("theChordialDeviation"));
cls_Prs3d_Drawer.def("MaximalChordialDeviation", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::MaximalChordialDeviation, "Returns the maximal chordal deviation. The default value is 0.1. Drawings of curves or patches are made with respect to an absolute maximal chordal deviation.");
cls_Prs3d_Drawer.def("HasOwnMaximalChordialDeviation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnMaximalChordialDeviation, "Returns true if the drawer has a maximal chordial deviation setting active.");
cls_Prs3d_Drawer.def("SetTypeOfHLR", (void (Prs3d_Drawer::*)(const Prs3d_TypeOfHLR)) &Prs3d_Drawer::SetTypeOfHLR, "Sets the type of HLR algorithm used by drawer's interactive objects", py::arg("theTypeOfHLR"));
cls_Prs3d_Drawer.def("TypeOfHLR", (Prs3d_TypeOfHLR (Prs3d_Drawer::*)()) &Prs3d_Drawer::TypeOfHLR, "Returns the type of HLR algorithm currently in use.");
cls_Prs3d_Drawer.def("HasOwnTypeOfHLR", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnTypeOfHLR, "Returns true if the type of HLR is not equal to Prs3d_TOH_NotSet.");
cls_Prs3d_Drawer.def("SetMaximalParameterValue", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetMaximalParameterValue, "Defines the maximum value allowed for the first and last parameters of an infinite curve.", py::arg("theValue"));
cls_Prs3d_Drawer.def("MaximalParameterValue", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::MaximalParameterValue, "Sets the maximum value allowed for the first and last parameters of an infinite curve. By default, this value is 500000.");
cls_Prs3d_Drawer.def("HasOwnMaximalParameterValue", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnMaximalParameterValue, "Returns true if the drawer has a maximum value allowed for the first and last parameters of an infinite curve setting active.");
cls_Prs3d_Drawer.def("SetIsoOnPlane", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetIsoOnPlane, "Sets IsoOnPlane on or off by setting the parameter theIsEnabled to true or false.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("IsoOnPlane", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::IsoOnPlane, "Returns True if the drawing of isos on planes is enabled.");
cls_Prs3d_Drawer.def("HasOwnIsoOnPlane", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnIsoOnPlane, "Returns true if the drawer has IsoOnPlane setting active.");
cls_Prs3d_Drawer.def("IsoOnTriangulation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::IsoOnTriangulation, "Returns True if the drawing of isos on triangulation is enabled.");
cls_Prs3d_Drawer.def("HasOwnIsoOnTriangulation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnIsoOnTriangulation, "Returns true if the drawer has IsoOnTriangulation setting active.");
cls_Prs3d_Drawer.def("SetIsoOnTriangulation", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetIsoOnTriangulation, "Enables or disables isolines on triangulation by setting the parameter theIsEnabled to true or false.", py::arg("theToEnable"));
cls_Prs3d_Drawer.def("SetDiscretisation", (void (Prs3d_Drawer::*)(const Standard_Integer)) &Prs3d_Drawer::SetDiscretisation, "Sets the discretisation parameter theValue.", py::arg("theValue"));
cls_Prs3d_Drawer.def("Discretisation", (Standard_Integer (Prs3d_Drawer::*)() const) &Prs3d_Drawer::Discretisation, "Returns the discretisation setting.");
cls_Prs3d_Drawer.def("HasOwnDiscretisation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDiscretisation, "Returns true if the drawer has discretisation setting active.");
cls_Prs3d_Drawer.def("SetDeviationCoefficient", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetDeviationCoefficient, "Sets the deviation coefficient theCoefficient. Also sets the hasOwnDeviationCoefficient flag to Standard_True and myPreviousDeviationCoefficient", py::arg("theCoefficient"));
cls_Prs3d_Drawer.def("DeviationCoefficient", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DeviationCoefficient, "Returns the deviation coefficient. Drawings of curves or patches are made with respect to a maximal chordal deviation. A Deviation coefficient is used in the shading display mode. The shape is seen decomposed into triangles. These are used to calculate reflection of light from the surface of the object. The triangles are formed from chords of the curves in the shape. The deviation coefficient gives the highest value of the angle with which a chord can deviate from a tangent to a curve. If this limit is reached, a new triangle is begun. This deviation is absolute and is set through the method: SetMaximalChordialDeviation. The default value is 0.001. In drawing shapes, however, you are allowed to ask for a relative deviation. This deviation will be: SizeOfObject * DeviationCoefficient.");
cls_Prs3d_Drawer.def("SetDeviationCoefficient", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::SetDeviationCoefficient, "Sets the hasOwnDeviationCoefficient flag to Standard_False");
cls_Prs3d_Drawer.def("HasOwnDeviationCoefficient", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDeviationCoefficient, "Returns true if there is a local setting for deviation coefficient in this framework for a specific interactive object.");
cls_Prs3d_Drawer.def("PreviousDeviationCoefficient", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::PreviousDeviationCoefficient, "Saves the previous value used for the chordal deviation coefficient.");
cls_Prs3d_Drawer.def("UpdatePreviousDeviationCoefficient", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::UpdatePreviousDeviationCoefficient, "Updates the previous value used for the chordal deviation coefficient to the current state.");
cls_Prs3d_Drawer.def("SetHLRDeviationCoefficient", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetHLRDeviationCoefficient, "Sets the deviation coefficient aCoefficient for removal of hidden lines created by different viewpoints in different presentations. The Default value is 0.02. Also sets the hasOwnHLRDeviationCoefficient flag to Standard_True and myPreviousHLRDeviationCoefficient", py::arg("theCoefficient"));
cls_Prs3d_Drawer.def("HLRDeviationCoefficient", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HLRDeviationCoefficient, "Returns the real number value of the hidden line removal deviation coefficient in this framework, if the flag hasOwnHLRDeviationCoefficient is true or there is no Link. Else the shape's HLR deviation coefficient is used. A Deviation coefficient is used in the shading display mode. The shape is seen decomposed into triangles. These are used to calculate reflection of light from the surface of the object. The triangles are formed from chords of the curves in the shape. The deviation coefficient give the highest value of the angle with which a chord can deviate from a tangent to a curve. If this limit is reached, a new triangle is begun. To find the hidden lines, hidden line display mode entails recalculation of the view at each different projector perspective. Since hidden lines entail calculations of more than usual complexity to decompose them into these triangles, a deviation coefficient allowing greater tolerance is used. This increases efficiency in calculation. The Default value is 0.02.");
cls_Prs3d_Drawer.def("SetHLRDeviationCoefficient", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::SetHLRDeviationCoefficient, "Sets the hasOwnHLRDeviationCoefficient flag to Standard_False");
cls_Prs3d_Drawer.def("HasOwnHLRDeviationCoefficient", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnHLRDeviationCoefficient, "Returns true if the there is a setting for HLR deviation coefficient in this framework for a specific interactive object.");
cls_Prs3d_Drawer.def("PreviousHLRDeviationCoefficient", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::PreviousHLRDeviationCoefficient, "Returns the previous value of the hidden line removal deviation coefficient.");
cls_Prs3d_Drawer.def("SetDeviationAngle", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetDeviationAngle, "Sets the deviation angle theAngle. Also sets the hasOwnDeviationAngle flag to Standard_True, and myPreviousDeviationAngle.", py::arg("theAngle"));
cls_Prs3d_Drawer.def("DeviationAngle", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DeviationAngle, "Returns the value for deviation angle.");
cls_Prs3d_Drawer.def("SetDeviationAngle", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::SetDeviationAngle, "Sets the hasOwnDeviationAngle flag to Standard_False");
cls_Prs3d_Drawer.def("HasOwnDeviationAngle", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDeviationAngle, "Returns true if the there is a local setting for deviation angle in this framework for a specific interactive object.");
cls_Prs3d_Drawer.def("PreviousDeviationAngle", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::PreviousDeviationAngle, "Returns the previous deviation angle");
cls_Prs3d_Drawer.def("UpdatePreviousDeviationAngle", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::UpdatePreviousDeviationAngle, "Updates the previous deviation angle to the current value");
cls_Prs3d_Drawer.def("SetHLRAngle", (void (Prs3d_Drawer::*)(const Standard_Real)) &Prs3d_Drawer::SetHLRAngle, "Sets anAngle, the angle of maximum chordal deviation for removal of hidden lines created by different viewpoints in different presentations. The default value is 20 * M_PI / 180. Also sets the hasOwnHLRDeviationAngle flag to Standard_True and myPreviousHLRDeviationAngle.", py::arg("theAngle"));
cls_Prs3d_Drawer.def("HLRAngle", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HLRAngle, "Returns the real number value of the deviation angle in hidden line removal views. The default value is 20 * M_PI / 180.");
cls_Prs3d_Drawer.def("SetHLRAngle", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::SetHLRAngle, "Sets the hasOwnHLRDeviationAngle flag to Standard_False");
cls_Prs3d_Drawer.def("HasOwnHLRDeviationAngle", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnHLRDeviationAngle, "Returns true if the there is a setting for HLR deviation angle in this framework for a specific interactive object.");
cls_Prs3d_Drawer.def("PreviousHLRDeviationAngle", (Standard_Real (Prs3d_Drawer::*)() const) &Prs3d_Drawer::PreviousHLRDeviationAngle, "Returns the previous value of the HLR deviation angle.");
cls_Prs3d_Drawer.def("SetAutoTriangulation", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetAutoTriangulation, "Sets IsAutoTriangulated on or off by setting the parameter theIsEnabled to true or false. If this flag is True automatic re-triangulation with deflection-check logic will be applied. Else this feature will be disable and triangulation is expected to be computed by application itself and no shading presentation at all if unavailable.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("IsAutoTriangulation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::IsAutoTriangulation, "Returns True if automatic triangulation is enabled.");
cls_Prs3d_Drawer.def("HasOwnIsAutoTriangulation", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnIsAutoTriangulation, "Returns true if the drawer has IsoOnPlane setting active.");
cls_Prs3d_Drawer.def("UIsoAspect", (const opencascade::handle<Prs3d_IsoAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::UIsoAspect, "Defines the attributes which are used when drawing an U isoparametric curve of a face. Defines the number of U isoparametric curves to be drawn for a single face. The LineAspect for U isoparametric lines can be edited (methods SetColor, SetTypeOfLine, SetWidth, SetNumber) The default values are: COLOR : Quantity_NOC_GRAY75 TYPE OF LINE: Aspect_TOL_SOLID WIDTH : 0.5");
cls_Prs3d_Drawer.def("SetUIsoAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_IsoAspect> &)) &Prs3d_Drawer::SetUIsoAspect, "None", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnUIsoAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnUIsoAspect, "Returns true if the drawer has its own attribute for UIso aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("VIsoAspect", (const opencascade::handle<Prs3d_IsoAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::VIsoAspect, "Defines the attributes which are used when drawing an V isoparametric curve of a face. Defines the number of V isoparametric curves to be drawn for a single face. The LineAspect for V isoparametric lines can be edited (methods SetColor, SetTypeOfLine, SetWidth, SetNumber) The default values are: COLOR : Quantity_NOC_GRAY82 TYPE OF LINE: Aspect_TOL_SOLID WIDTH : 0.5");
cls_Prs3d_Drawer.def("SetVIsoAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_IsoAspect> &)) &Prs3d_Drawer::SetVIsoAspect, "Sets the appearance of V isoparameters - theAspect.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnVIsoAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnVIsoAspect, "Returns true if the drawer has its own attribute for VIso aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("WireAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::WireAspect, "Returns wire aspect settings. The LineAspect for the free boundaries can be edited. The default values are: Color: Quantity_NOC_GREEN Type of line: Aspect_TOL_SOLID Width: 1.0 These attributes are used by the algorithm Prs3d_WFShape.");
cls_Prs3d_Drawer.def("SetWireAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetWireAspect, "Sets the parameter theAspect for display of wires.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnWireAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnWireAspect, "Returns true if the drawer has its own attribute for wire aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetWireDraw", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetWireDraw, "Sets WireDraw on or off by setting the parameter theIsEnabled to true or false.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("WireDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::WireDraw, "Returns True if the drawing of the wire is enabled.");
cls_Prs3d_Drawer.def("HasOwnWireDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnWireDraw, "Returns true if the drawer has its own attribute for 'draw wires' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("PointAspect", (const opencascade::handle<Prs3d_PointAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::PointAspect, "Returns the point aspect setting. The default values are Color: Quantity_NOC_YELLOW Type of marker: Aspect_TOM_PLUS Scale: 1.0 These attributes are used by the algorithms Prs3d_Point.");
cls_Prs3d_Drawer.def("SetPointAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_PointAspect> &)) &Prs3d_Drawer::SetPointAspect, "Sets the parameter theAspect for display attributes of points", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnPointAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnPointAspect, "Returns true if the drawer has its own attribute for point aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetupOwnPointAspect", [](Prs3d_Drawer &self) -> Standard_Boolean { return self.SetupOwnPointAspect(); });
cls_Prs3d_Drawer.def("SetupOwnPointAspect", (Standard_Boolean (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetupOwnPointAspect, "Sets own point aspect. Returns FALSE if the drawer already has its own attribute for point aspect.", py::arg("theDefaults"));
cls_Prs3d_Drawer.def("LineAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::LineAspect, "Returns settings for line aspects. These settings can be edited. The default values are: Color: Quantity_NOC_YELLOW Type of line: Aspect_TOL_SOLID Width: 1.0 These attributes are used by the following algorithms: Prs3d_Curve Prs3d_Line Prs3d_HLRShape");
cls_Prs3d_Drawer.def("SetLineAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetLineAspect, "Sets the parameter theAspect for display attributes of lines.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnLineAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnLineAspect, "Returns true if the drawer has its own attribute for line aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetOwnLineAspects", [](Prs3d_Drawer &self) -> Standard_Boolean { return self.SetOwnLineAspects(); });
cls_Prs3d_Drawer.def("SetOwnLineAspects", (Standard_Boolean (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetOwnLineAspects, "Sets own line aspects. Returns FALSE if own line aspect are already set.", py::arg("theDefaults"));
cls_Prs3d_Drawer.def("SetOwnDatumAspects", [](Prs3d_Drawer &self) -> Standard_Boolean { return self.SetOwnDatumAspects(); });
cls_Prs3d_Drawer.def("SetOwnDatumAspects", (Standard_Boolean (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetOwnDatumAspects, "Sets own line aspects for datums. Returns FALSE if own line for datums are already set.", py::arg("theDefaults"));
cls_Prs3d_Drawer.def("TextAspect", (const opencascade::handle<Prs3d_TextAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::TextAspect, "Returns settings for text aspect. These settings can be edited. The default value is: - Color: Quantity_NOC_YELLOW");
cls_Prs3d_Drawer.def("SetTextAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_TextAspect> &)) &Prs3d_Drawer::SetTextAspect, "Sets the parameter theAspect for display attributes of text.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnTextAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnTextAspect, "Returns true if the drawer has its own attribute for text aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("ShadingAspect", (const opencascade::handle<Prs3d_ShadingAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::ShadingAspect, "Returns settings for shading aspects. These settings can be edited. The default values are: - Color: Quantity_NOC_YELLOW - Material: Graphic3d_NOM_BRASS Shading aspect is obtained through decomposition of 3d faces into triangles, each side of each triangle being a chord of the corresponding curved edge in the face. Reflection of light in each projector perspective is then calculated for each of the resultant triangular planes.");
cls_Prs3d_Drawer.def("SetShadingAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_ShadingAspect> &)) &Prs3d_Drawer::SetShadingAspect, "Sets the parameter theAspect for display attributes of shading.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnShadingAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnShadingAspect, "Returns true if the drawer has its own attribute for shading aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetupOwnShadingAspect", [](Prs3d_Drawer &self) -> Standard_Boolean { return self.SetupOwnShadingAspect(); });
cls_Prs3d_Drawer.def("SetupOwnShadingAspect", (Standard_Boolean (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetupOwnShadingAspect, "Sets own shading aspect. Returns FALSE if the drawer already has its own attribute for shading aspect.", py::arg("theDefaults"));
cls_Prs3d_Drawer.def("SeenLineAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::SeenLineAspect, "Returns settings for seen line aspects. These settings can be edited. The default values are: Color: Quantity_NOC_YELLOW Type of line: Aspect_TOL_SOLID Width: 1.0");
cls_Prs3d_Drawer.def("SetSeenLineAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetSeenLineAspect, "Sets the parameter theAspect for the display of seen lines in hidden line removal mode.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnSeenLineAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnSeenLineAspect, "Returns true if the drawer has its own attribute for seen line aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("PlaneAspect", (const opencascade::handle<Prs3d_PlaneAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::PlaneAspect, "Returns settings for the appearance of planes.");
cls_Prs3d_Drawer.def("SetPlaneAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_PlaneAspect> &)) &Prs3d_Drawer::SetPlaneAspect, "Sets the parameter theAspect for the display of planes.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnPlaneAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnPlaneAspect, "Returns true if the drawer has its own attribute for plane aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("ArrowAspect", (const opencascade::handle<Prs3d_ArrowAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::ArrowAspect, "Returns the attributes for display of arrows.");
cls_Prs3d_Drawer.def("SetArrowAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_ArrowAspect> &)) &Prs3d_Drawer::SetArrowAspect, "Sets the parameter theAspect for display attributes of arrows.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnArrowAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnArrowAspect, "Returns true if the drawer has its own attribute for arrow aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetLineArrowDraw", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetLineArrowDraw, "Enables the drawing of an arrow at the end of each line. By default the arrows are not drawn.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("LineArrowDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::LineArrowDraw, "Returns True if drawing an arrow at the end of each edge is enabled and False otherwise (the default).");
cls_Prs3d_Drawer.def("HasOwnLineArrowDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnLineArrowDraw, "Returns true if the drawer has its own attribute for 'draw arrow' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("HiddenLineAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::HiddenLineAspect, "Returns settings for hidden line aspects. These settings can be edited. The default values are: Color: Quantity_NOC_YELLOW Type of line: Aspect_TOL_DASH Width: 1.0");
cls_Prs3d_Drawer.def("SetHiddenLineAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetHiddenLineAspect, "Sets the parameter theAspect for the display of hidden lines in hidden line removal mode.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnHiddenLineAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnHiddenLineAspect, "Returns true if the drawer has its own attribute for hidden lines aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("DrawHiddenLine", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DrawHiddenLine, "Returns Standard_True if the hidden lines are to be drawn. By default the hidden lines are not drawn.");
cls_Prs3d_Drawer.def("EnableDrawHiddenLine", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::EnableDrawHiddenLine, "Enables the DrawHiddenLine function.");
cls_Prs3d_Drawer.def("DisableDrawHiddenLine", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::DisableDrawHiddenLine, "Disables the DrawHiddenLine function.");
cls_Prs3d_Drawer.def("HasOwnDrawHiddenLine", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDrawHiddenLine, "Returns true if the drawer has its own attribute for 'draw hidden lines' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("VectorAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::VectorAspect, "Returns settings for the appearance of vectors. These settings can be edited. The default values are: Color: Quantity_NOC_SKYBLUE Type of line: Aspect_TOL_SOLID Width: 1.0");
cls_Prs3d_Drawer.def("SetVectorAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetVectorAspect, "Sets the modality theAspect for the display of vectors.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnVectorAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnVectorAspect, "Returns true if the drawer has its own attribute for vector aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetVertexDrawMode", (void (Prs3d_Drawer::*)(const Prs3d_VertexDrawMode)) &Prs3d_Drawer::SetVertexDrawMode, "Sets the mode of visualization of vertices of a TopoDS_Shape instance. By default, only stand-alone vertices (not belonging topologically to an edge) are drawn, that corresponds to Prs3d_VDM_Standalone mode. Switching to Prs3d_VDM_Standalone mode makes all shape's vertices visible. To inherit this parameter from the global drawer instance ('the link') when it is present, Prs3d_VDM_Inherited value should be used.", py::arg("theMode"));
cls_Prs3d_Drawer.def("VertexDrawMode", (Prs3d_VertexDrawMode (Prs3d_Drawer::*)()) &Prs3d_Drawer::VertexDrawMode, "Returns the current mode of visualization of vertices of a TopoDS_Shape instance.");
cls_Prs3d_Drawer.def("HasOwnVertexDrawMode", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnVertexDrawMode, "Returns true if the vertex draw mode is not equal to Prs3d_VDM_Inherited. This means that individual vertex draw mode value (i.e. not inherited from the global drawer) is used for a specific interactive object.");
cls_Prs3d_Drawer.def("DatumAspect", (const opencascade::handle<Prs3d_DatumAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::DatumAspect, "Returns settings for the appearance of datums. These settings can be edited. The default values for the three axes are: Color: Quantity_NOC_PEACHPUFF Type of line: Aspect_TOL_SOLID Width: 1.0");
cls_Prs3d_Drawer.def("SetDatumAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_DatumAspect> &)) &Prs3d_Drawer::SetDatumAspect, "Sets the modality theAspect for the display of datums.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnDatumAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDatumAspect, "Returns true if the drawer has its own attribute for datum aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SectionAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::SectionAspect, "The LineAspect for the wire can be edited. The default values are: Color: Quantity_NOC_ORANGE Type of line: Aspect_TOL_SOLID Width: 1.0 These attributes are used by the algorithm Prs3d_WFShape.");
cls_Prs3d_Drawer.def("SetSectionAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetSectionAspect, "Sets the parameter theAspect for display attributes of sections.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnSectionAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnSectionAspect, "Returns true if the drawer has its own attribute for section aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetFreeBoundaryAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetFreeBoundaryAspect, "Sets the parameter theAspect for the display of free boundaries. The method sets aspect owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("FreeBoundaryAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::FreeBoundaryAspect, "Returns the values for presentation of free boundaries, in other words, boundaries which are not shared. The LineAspect for the free boundaries can be edited. The default values are: Color: Quantity_NOC_GREEN Type of line: Aspect_TOL_SOLID Width: 1.0 These attributes are used by the algorithm Prs3d_WFShape");
cls_Prs3d_Drawer.def("HasOwnFreeBoundaryAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnFreeBoundaryAspect, "Returns true if the drawer has its own attribute for free boundaries aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetFreeBoundaryDraw", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetFreeBoundaryDraw, "Enables or disables drawing of free boundaries for shading presentations. The method sets drawing flag owned by the drawer that will be used during visualization instead of the one set in link. theIsEnabled is a boolean flag indicating whether the free boundaries should be drawn or not.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("FreeBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::FreeBoundaryDraw, "Returns True if the drawing of the free boundaries is enabled True is the default setting.");
cls_Prs3d_Drawer.def("HasOwnFreeBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnFreeBoundaryDraw, "Returns true if the drawer has its own attribute for 'draw free boundaries' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetUnFreeBoundaryAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetUnFreeBoundaryAspect, "Sets the parameter theAspect for the display of shared boundaries. The method sets aspect owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("UnFreeBoundaryAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::UnFreeBoundaryAspect, "Returns settings for shared boundary line aspects. The LineAspect for the unfree boundaries can be edited. The default values are: Color: Quantity_NOC_YELLOW Type of line: Aspect_TOL_SOLID Width: 1. These attributes are used by the algorithm Prs3d_WFShape");
cls_Prs3d_Drawer.def("HasOwnUnFreeBoundaryAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnUnFreeBoundaryAspect, "Returns true if the drawer has its own attribute for unfree boundaries aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetUnFreeBoundaryDraw", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetUnFreeBoundaryDraw, "Enables or disables drawing of shared boundaries for shading presentations. The method sets drawing flag owned by the drawer that will be used during visualization instead of the one set in link. theIsEnabled is a boolean flag indicating whether the shared boundaries should be drawn or not.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("UnFreeBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::UnFreeBoundaryDraw, "Returns True if the drawing of the shared boundaries is enabled. True is the default setting.");
cls_Prs3d_Drawer.def("HasOwnUnFreeBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnUnFreeBoundaryDraw, "Returns true if the drawer has its own attribute for 'draw shared boundaries' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetFaceBoundaryAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_Drawer::SetFaceBoundaryAspect, "Sets line aspect for face boundaries. The method sets line aspect owned by the drawer that will be used during visualization instead of the one set in link. theAspect is the line aspect that determines the look of the face boundaries.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("FaceBoundaryAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::FaceBoundaryAspect, "Returns line aspect of face boundaries.");
cls_Prs3d_Drawer.def("HasOwnFaceBoundaryAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnFaceBoundaryAspect, "Returns true if the drawer has its own attribute for face boundaries aspect that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetupOwnFaceBoundaryAspect", [](Prs3d_Drawer &self) -> Standard_Boolean { return self.SetupOwnFaceBoundaryAspect(); });
cls_Prs3d_Drawer.def("SetupOwnFaceBoundaryAspect", (Standard_Boolean (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetupOwnFaceBoundaryAspect, "Sets own face boundary aspect. Returns FALSE if the drawer already has its own attribute for face boundary aspect.", py::arg("theDefaults"));
cls_Prs3d_Drawer.def("SetFaceBoundaryDraw", (void (Prs3d_Drawer::*)(const Standard_Boolean)) &Prs3d_Drawer::SetFaceBoundaryDraw, "Enables or disables face boundary drawing for shading presentations. The method sets drawing flag owned by the drawer that will be used during visualization instead of the one set in link. theIsEnabled is a boolean flag indicating whether the face boundaries should be drawn or not.", py::arg("theIsEnabled"));
cls_Prs3d_Drawer.def("FaceBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::FaceBoundaryDraw, "Checks whether the face boundary drawing is enabled or not.");
cls_Prs3d_Drawer.def("HasOwnFaceBoundaryDraw", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnFaceBoundaryDraw, "Returns true if the drawer has its own attribute for 'draw face boundaries' flag that overrides the one in the link.");
cls_Prs3d_Drawer.def("HasOwnFaceBoundaryUpperContinuity", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnFaceBoundaryUpperContinuity, "Returns true if the drawer has its own attribute for face boundaries upper edge continuity class that overrides the one in the link.");
cls_Prs3d_Drawer.def("FaceBoundaryUpperContinuity", (GeomAbs_Shape (Prs3d_Drawer::*)() const) &Prs3d_Drawer::FaceBoundaryUpperContinuity, "Get the most edge continuity class; GeomAbs_CN by default (all edges).");
cls_Prs3d_Drawer.def("SetFaceBoundaryUpperContinuity", (void (Prs3d_Drawer::*)(GeomAbs_Shape)) &Prs3d_Drawer::SetFaceBoundaryUpperContinuity, "Set the most edge continuity class for face boundaries.", py::arg("theMostAllowedEdgeClass"));
cls_Prs3d_Drawer.def("UnsetFaceBoundaryUpperContinuity", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::UnsetFaceBoundaryUpperContinuity, "Unset the most edge continuity class for face boundaries.");
cls_Prs3d_Drawer.def("DimensionAspect", (const opencascade::handle<Prs3d_DimensionAspect> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::DimensionAspect, "Returns settings for the appearance of dimensions.");
cls_Prs3d_Drawer.def("SetDimensionAspect", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_DimensionAspect> &)) &Prs3d_Drawer::SetDimensionAspect, "Sets the settings for the appearance of dimensions. The method sets aspect owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theAspect"));
cls_Prs3d_Drawer.def("HasOwnDimensionAspect", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDimensionAspect, "Returns true if the drawer has its own attribute for the appearance of dimensions that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetDimLengthModelUnits", (void (Prs3d_Drawer::*)(const TCollection_AsciiString &)) &Prs3d_Drawer::SetDimLengthModelUnits, "Sets dimension length model units for computing of dimension presentation. The method sets value owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theUnits"));
cls_Prs3d_Drawer.def("SetDimAngleModelUnits", (void (Prs3d_Drawer::*)(const TCollection_AsciiString &)) &Prs3d_Drawer::SetDimAngleModelUnits, "Sets dimension angle model units for computing of dimension presentation. The method sets value owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theUnits"));
cls_Prs3d_Drawer.def("DimLengthModelUnits", (const TCollection_AsciiString & (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DimLengthModelUnits, "Returns length model units for the dimension presentation.");
cls_Prs3d_Drawer.def("DimAngleModelUnits", (const TCollection_AsciiString & (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DimAngleModelUnits, "Returns angle model units for the dimension presentation.");
cls_Prs3d_Drawer.def("HasOwnDimLengthModelUnits", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDimLengthModelUnits, "Returns true if the drawer has its own attribute for dimension length model units that overrides the one in the link.");
cls_Prs3d_Drawer.def("HasOwnDimAngleModelUnits", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDimAngleModelUnits, "Returns true if the drawer has its own attribute for dimension angle model units that overrides the one in the link.");
cls_Prs3d_Drawer.def("SetDimLengthDisplayUnits", (void (Prs3d_Drawer::*)(const TCollection_AsciiString &)) &Prs3d_Drawer::SetDimLengthDisplayUnits, "Sets length units in which value for dimension presentation is displayed. The method sets value owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theUnits"));
cls_Prs3d_Drawer.def("SetDimAngleDisplayUnits", (void (Prs3d_Drawer::*)(const TCollection_AsciiString &)) &Prs3d_Drawer::SetDimAngleDisplayUnits, "Sets angle units in which value for dimension presentation is displayed. The method sets value owned by the drawer that will be used during visualization instead of the one set in link.", py::arg("theUnits"));
cls_Prs3d_Drawer.def("DimLengthDisplayUnits", (const TCollection_AsciiString & (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DimLengthDisplayUnits, "Returns length units in which dimension presentation is displayed.");
cls_Prs3d_Drawer.def("DimAngleDisplayUnits", (const TCollection_AsciiString & (Prs3d_Drawer::*)() const) &Prs3d_Drawer::DimAngleDisplayUnits, "Returns angle units in which dimension presentation is displayed.");
cls_Prs3d_Drawer.def("HasOwnDimLengthDisplayUnits", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDimLengthDisplayUnits, "Returns true if the drawer has its own attribute for length units in which dimension presentation is displayed that overrides the one in the link.");
cls_Prs3d_Drawer.def("HasOwnDimAngleDisplayUnits", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasOwnDimAngleDisplayUnits, "Returns true if the drawer has its own attribute for angle units in which dimension presentation is displayed that overrides the one in the link.");
cls_Prs3d_Drawer.def("Link", (const opencascade::handle<Prs3d_Drawer> & (Prs3d_Drawer::*)()) &Prs3d_Drawer::Link, "Returns the drawer to which the current object references.");
cls_Prs3d_Drawer.def("HasLink", (Standard_Boolean (Prs3d_Drawer::*)() const) &Prs3d_Drawer::HasLink, "Returns true if the current object has a link on the other drawer.");
cls_Prs3d_Drawer.def("Link", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::Link, "Sets theDrawer as a link to which the current object references.", py::arg("theDrawer"));
cls_Prs3d_Drawer.def("SetLink", (void (Prs3d_Drawer::*)(const opencascade::handle<Prs3d_Drawer> &)) &Prs3d_Drawer::SetLink, "Sets theDrawer as a link to which the current object references.", py::arg("theDrawer"));
cls_Prs3d_Drawer.def("ClearLocalAttributes", (void (Prs3d_Drawer::*)()) &Prs3d_Drawer::ClearLocalAttributes, "Removes local attributes.");
cls_Prs3d_Drawer.def("SetShaderProgram", [](Prs3d_Drawer &self, const opencascade::handle<Graphic3d_ShaderProgram> & a0, const Graphic3d_GroupAspect a1) -> bool { return self.SetShaderProgram(a0, a1); });
cls_Prs3d_Drawer.def("SetShaderProgram", (bool (Prs3d_Drawer::*)(const opencascade::handle<Graphic3d_ShaderProgram> &, const Graphic3d_GroupAspect, const bool)) &Prs3d_Drawer::SetShaderProgram, "Assign shader program for specified type of primitives.", py::arg("theProgram"), py::arg("theAspect"), py::arg("theToOverrideDefaults"));
cls_Prs3d_Drawer.def("SetShadingModel", [](Prs3d_Drawer &self, Graphic3d_TypeOfShadingModel a0) -> bool { return self.SetShadingModel(a0); });
cls_Prs3d_Drawer.def("SetShadingModel", (bool (Prs3d_Drawer::*)(Graphic3d_TypeOfShadingModel, bool)) &Prs3d_Drawer::SetShadingModel, "Sets Shading Model type for the shading aspect.", py::arg("theModel"), py::arg("theToOverrideDefaults"));
cls_Prs3d_Drawer.def("DumpJson", [](Prs3d_Drawer &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_Drawer.def("DumpJson", (void (Prs3d_Drawer::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_Drawer::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// TYPEDEF: GRAPHIC3D_HIGHLIGHTSTYLE
/*
if (py::hasattr(mod, "Prs3d_Drawer")) {
	mod.attr("Graphic3d_HighlightStyle") = mod.attr("Prs3d_Drawer");
}
*/

// TYPEDEF: PRS3D_PRESENTATION
py::class_<Graphic3d_Structure, opencascade::handle<Graphic3d_Structure>, Standard_Transient> cls_Prs3d_Presentation(mod, "Prs3d_Presentation", "This class allows the definition a graphic object. This graphic structure can be displayed, erased, or highlighted. This graphic structure can be connected with another graphic structure.", py::module_local());

// Constructors
cls_Prs3d_Presentation.def(py::init<const opencascade::handle<Graphic3d_StructureManager> &>(), py::arg("theManager"));
cls_Prs3d_Presentation.def(py::init<const opencascade::handle<Graphic3d_StructureManager> &, const opencascade::handle<Graphic3d_Structure> &>(), py::arg("theManager"), py::arg("theLinkPrs"));

// Methods
cls_Prs3d_Presentation.def_static("get_type_name_", (const char * (*)()) &Graphic3d_Structure::get_type_name, "None");
cls_Prs3d_Presentation.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Graphic3d_Structure::get_type_descriptor, "None");
cls_Prs3d_Presentation.def("DynamicType", (const opencascade::handle<Standard_Type> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::DynamicType, "None");
cls_Prs3d_Presentation.def("Clear", [](Graphic3d_Structure &self) -> void { return self.Clear(); });
cls_Prs3d_Presentation.def("Clear", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::Clear, "if WithDestruction == Standard_True then suppress all the groups of primitives in the structure. and it is mandatory to create a new group in <me>. if WithDestruction == Standard_False then clears all the groups of primitives in the structure. and all the groups are conserved and empty. They will be erased at the next screen update. The structure itself is conserved. The transformation and the attributes of <me> are conserved. The childs of <me> are conserved.", py::arg("WithDestruction"));
cls_Prs3d_Presentation.def("Display", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::Display, "Displays the structure <me> in all the views of the visualiser.");
cls_Prs3d_Presentation.def("DisplayPriority", (Standard_Integer (Graphic3d_Structure::*)() const) &Graphic3d_Structure::DisplayPriority, "Returns the current display priority for this structure.");
cls_Prs3d_Presentation.def("Erase", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::Erase, "Erases the structure <me> in all the views of the visualiser.");
cls_Prs3d_Presentation.def("Highlight", [](Graphic3d_Structure &self, const opencascade::handle<Graphic3d_PresentationAttributes> & a0) -> void { return self.Highlight(a0); });
cls_Prs3d_Presentation.def("Highlight", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_PresentationAttributes> &, const Standard_Boolean)) &Graphic3d_Structure::Highlight, "Highlights the structure in all the views with the given style", py::arg("theStyle"), py::arg("theToUpdateMgr"));
cls_Prs3d_Presentation.def("Remove", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::Remove, "Suppress the structure <me>. It will be erased at the next screen update. Warning: No more graphic operations in <me> after this call. Category: Methods to modify the class definition");
cls_Prs3d_Presentation.def("CalculateBoundBox", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::CalculateBoundBox, "Computes axis-aligned bounding box of a structure.");
cls_Prs3d_Presentation.def("SetInfiniteState", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::SetInfiniteState, "Sets infinite flag. When TRUE, the MinMaxValues method returns: theXMin = theYMin = theZMin = RealFirst(). theXMax = theYMax = theZMax = RealLast(). By default, structure is created not infinite but empty.", py::arg("theToSet"));
cls_Prs3d_Presentation.def("SetDisplayPriority", (void (Graphic3d_Structure::*)(const Standard_Integer)) &Graphic3d_Structure::SetDisplayPriority, "Modifies the order of displaying the structure. Values are between 0 and 10. Structures are drawn according to their display priorities in ascending order. A structure of priority 10 is displayed the last and appears over the others. The default value is 5. Category: Methods to modify the class definition Warning: If <me> is displayed then the SetDisplayPriority method erase <me> and display <me> with the new priority. Raises PriorityDefinitionError if <Priority> is greater than 10 or a negative value.", py::arg("Priority"));
cls_Prs3d_Presentation.def("ResetDisplayPriority", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::ResetDisplayPriority, "Reset the current priority of the structure to the previous priority. Category: Methods to modify the class definition Warning: If <me> is displayed then the SetDisplayPriority method erase <me> and display <me> with the previous priority.");
cls_Prs3d_Presentation.def("SetZLayer", (void (Graphic3d_Structure::*)(const Graphic3d_ZLayerId)) &Graphic3d_Structure::SetZLayer, "Set Z layer ID for the structure. The Z layer mechanism allows to display structures presented in higher layers in overlay of structures in lower layers by switching off z buffer depth test between layers", py::arg("theLayerId"));
cls_Prs3d_Presentation.def("GetZLayer", (Graphic3d_ZLayerId (Graphic3d_Structure::*)() const) &Graphic3d_Structure::GetZLayer, "Get Z layer ID of displayed structure. The method returns -1 if the structure has no ID (deleted from graphic driver).");
cls_Prs3d_Presentation.def("SetClipPlanes", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_SequenceOfHClipPlane> &)) &Graphic3d_Structure::SetClipPlanes, "Changes a sequence of clip planes slicing the structure on rendering.", py::arg("thePlanes"));
cls_Prs3d_Presentation.def("ClipPlanes", (const opencascade::handle<Graphic3d_SequenceOfHClipPlane> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::ClipPlanes, "Get clip planes slicing the structure on rendering.");
cls_Prs3d_Presentation.def("SetVisible", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::SetVisible, "Modifies the visibility indicator to Standard_True or Standard_False for the structure <me>. The default value at the definition of <me> is Standard_True.", py::arg("AValue"));
cls_Prs3d_Presentation.def("SetVisual", (void (Graphic3d_Structure::*)(const Graphic3d_TypeOfStructure)) &Graphic3d_Structure::SetVisual, "Modifies the visualisation mode for the structure <me>.", py::arg("AVisual"));
cls_Prs3d_Presentation.def("SetZoomLimit", (void (Graphic3d_Structure::*)(const Standard_Real, const Standard_Real)) &Graphic3d_Structure::SetZoomLimit, "Modifies the minimum and maximum zoom coefficients for the structure <me>. The default value at the definition of <me> is unlimited. Category: Methods to modify the class definition Warning: Raises StructureDefinitionError if <LimitInf> is greater than <LimitSup> or if <LimitInf> or <LimitSup> is a negative value.", py::arg("LimitInf"), py::arg("LimitSup"));
cls_Prs3d_Presentation.def("SetIsForHighlight", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::SetIsForHighlight, "Marks the structure <me> representing wired structure needed for highlight only so it won't be added to BVH tree.", py::arg("isForHighlight"));
cls_Prs3d_Presentation.def("UnHighlight", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::UnHighlight, "Suppresses the highlight for the structure <me> in all the views of the visualiser.");
cls_Prs3d_Presentation.def("Compute", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::Compute, "None");
cls_Prs3d_Presentation.def("Compute", (opencascade::handle<Graphic3d_Structure> (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_DataStructureManager> &)) &Graphic3d_Structure::Compute, "Returns the new Structure defined for the new visualization", py::arg("theProjector"));
cls_Prs3d_Presentation.def("Compute", (opencascade::handle<Graphic3d_Structure> (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_DataStructureManager> &, const opencascade::handle<Geom_Transformation> &)) &Graphic3d_Structure::Compute, "Returns the new Structure defined for the new visualization", py::arg("theProjector"), py::arg("theTrsf"));
cls_Prs3d_Presentation.def("Compute", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_DataStructureManager> &, opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::Compute, "Returns the new Structure defined for the new visualization", py::arg("theProjector"), py::arg("theStructure"));
cls_Prs3d_Presentation.def("Compute", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_DataStructureManager> &, const opencascade::handle<Geom_Transformation> &, opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::Compute, "Returns the new Structure defined for the new visualization", py::arg("theProjector"), py::arg("theTrsf"), py::arg("theStructure"));
cls_Prs3d_Presentation.def("ReCompute", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::ReCompute, "Forces a new construction of the structure <me> if <me> is displayed and TOS_COMPUTED.");
cls_Prs3d_Presentation.def("ReCompute", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_DataStructureManager> &)) &Graphic3d_Structure::ReCompute, "Forces a new construction of the structure <me> if <me> is displayed in <aProjetor> and TOS_COMPUTED.", py::arg("aProjector"));
cls_Prs3d_Presentation.def("ContainsFacet", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::ContainsFacet, "Returns Standard_True if the structure <me> contains Polygons, Triangles or Quadrangles.");
cls_Prs3d_Presentation.def("Groups", (const Graphic3d_SequenceOfGroup & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::Groups, "Returns the groups sequence included in this structure.");
cls_Prs3d_Presentation.def("NumberOfGroups", (Standard_Integer (Graphic3d_Structure::*)() const) &Graphic3d_Structure::NumberOfGroups, "Returns the current number of groups in this structure.");
cls_Prs3d_Presentation.def("NewGroup", (opencascade::handle<Graphic3d_Group> (Graphic3d_Structure::*)()) &Graphic3d_Structure::NewGroup, "Append new group to this structure.");
cls_Prs3d_Presentation.def("CurrentGroup", (opencascade::handle<Graphic3d_Group> (Graphic3d_Structure::*)()) &Graphic3d_Structure::CurrentGroup, "Returns the last created group or creates new one if list is empty.");
cls_Prs3d_Presentation.def("HighlightStyle", (const opencascade::handle<Graphic3d_PresentationAttributes> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::HighlightStyle, "Returns the highlight attributes.");
cls_Prs3d_Presentation.def("IsDeleted", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsDeleted, "Returns TRUE if this structure is deleted (after Remove() call).");
cls_Prs3d_Presentation.def("IsDisplayed", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsDisplayed, "Returns the display indicator for this structure.");
cls_Prs3d_Presentation.def("IsEmpty", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsEmpty, "Returns Standard_True if the structure <me> is empty. Warning: A structure is empty if : it do not have group or all the groups are empties and it do not have descendant or all the descendants are empties.");
cls_Prs3d_Presentation.def("IsInfinite", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsInfinite, "Returns Standard_True if the structure <me> is infinite.");
cls_Prs3d_Presentation.def("IsHighlighted", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsHighlighted, "Returns the highlight indicator for this structure.");
cls_Prs3d_Presentation.def("IsTransformed", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsTransformed, "Returns TRUE if the structure is transformed.");
cls_Prs3d_Presentation.def("IsVisible", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsVisible, "Returns the visibility indicator for this structure.");
cls_Prs3d_Presentation.def("MinMaxValues", [](Graphic3d_Structure &self) -> Bnd_Box { return self.MinMaxValues(); });
cls_Prs3d_Presentation.def("MinMaxValues", (Bnd_Box (Graphic3d_Structure::*)(const Standard_Boolean) const) &Graphic3d_Structure::MinMaxValues, "Returns the coordinates of the boundary box of the structure <me>. If <theToIgnoreInfiniteFlag> is TRUE, the method returns actual graphical boundaries of the Graphic3d_Group components. Otherwise, the method returns boundaries taking into account infinite state of the structure. This approach generally used for application specific fit operation (e.g. fitting the model into screen, not taking into accout infinite helper elements). Warning: If the structure <me> is empty then the empty box is returned, If the structure <me> is infinite then the whole box is returned.", py::arg("theToIgnoreInfiniteFlag"));
cls_Prs3d_Presentation.def("Visual", (Graphic3d_TypeOfStructure (Graphic3d_Structure::*)() const) &Graphic3d_Structure::Visual, "Returns the visualisation mode for the structure <me>.");
cls_Prs3d_Presentation.def_static("AcceptConnection_", (Standard_Boolean (*)(Graphic3d_Structure *, Graphic3d_Structure *, Graphic3d_TypeOfConnection)) &Graphic3d_Structure::AcceptConnection, "Returns Standard_True if the connection is possible between <AStructure1> and <AStructure2> without a creation of a cycle.", py::arg("theStructure1"), py::arg("theStructure2"), py::arg("theType"));
cls_Prs3d_Presentation.def("Ancestors", (void (Graphic3d_Structure::*)(Graphic3d_MapOfStructure &) const) &Graphic3d_Structure::Ancestors, "Returns the group of structures to which <me> is connected.", py::arg("SG"));
cls_Prs3d_Presentation.def("Connect", [](Graphic3d_Structure &self, Graphic3d_Structure * a0, Graphic3d_TypeOfConnection a1) -> void { return self.Connect(a0, a1); });
cls_Prs3d_Presentation.def("Connect", (void (Graphic3d_Structure::*)(Graphic3d_Structure *, Graphic3d_TypeOfConnection, Standard_Boolean)) &Graphic3d_Structure::Connect, "If Atype is TOC_DESCENDANT then add <AStructure> as a child structure of <me>. If Atype is TOC_ANCESTOR then add <AStructure> as a parent structure of <me>. The connection propagates Display, Highlight, Erase, Remove, and stacks the transformations. No connection if the graph of the structures contains a cycle and <WithCheck> is Standard_True;", py::arg("theStructure"), py::arg("theType"), py::arg("theWithCheck"));
cls_Prs3d_Presentation.def("Connect", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::Connect, "None", py::arg("thePrs"));
cls_Prs3d_Presentation.def("Descendants", (void (Graphic3d_Structure::*)(Graphic3d_MapOfStructure &) const) &Graphic3d_Structure::Descendants, "Returns the group of structures connected to <me>.", py::arg("SG"));
cls_Prs3d_Presentation.def("Disconnect", (void (Graphic3d_Structure::*)(Graphic3d_Structure *)) &Graphic3d_Structure::Disconnect, "Suppress the connection between <AStructure> and <me>.", py::arg("theStructure"));
cls_Prs3d_Presentation.def("Remove", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::Remove, "None", py::arg("thePrs"));
cls_Prs3d_Presentation.def("DisconnectAll", (void (Graphic3d_Structure::*)(const Graphic3d_TypeOfConnection)) &Graphic3d_Structure::DisconnectAll, "If Atype is TOC_DESCENDANT then suppress all the connections with the child structures of <me>. If Atype is TOC_ANCESTOR then suppress all the connections with the parent structures of <me>.", py::arg("AType"));
cls_Prs3d_Presentation.def("RemoveAll", (void (Graphic3d_Structure::*)()) &Graphic3d_Structure::RemoveAll, "None");
cls_Prs3d_Presentation.def_static("Network_", (void (*)(Graphic3d_Structure *, const Graphic3d_TypeOfConnection, NCollection_Map<Graphic3d_Structure *> &)) &Graphic3d_Structure::Network, "Returns <ASet> the group of structures : - directly or indirectly connected to <AStructure> if the TypeOfConnection == TOC_DESCENDANT - to which <AStructure> is directly or indirectly connected if the TypeOfConnection == TOC_ANCESTOR", py::arg("theStructure"), py::arg("theType"), py::arg("theSet"));
cls_Prs3d_Presentation.def("SetOwner", (void (Graphic3d_Structure::*)(const Standard_Address)) &Graphic3d_Structure::SetOwner, "None", py::arg("theOwner"));
cls_Prs3d_Presentation.def("Owner", (Standard_Address (Graphic3d_Structure::*)() const) &Graphic3d_Structure::Owner, "None");
cls_Prs3d_Presentation.def("SetHLRValidation", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::SetHLRValidation, "None", py::arg("theFlag"));
cls_Prs3d_Presentation.def("HLRValidation", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::HLRValidation, "Hidden parts stored in this structure are valid if: 1) the owner is defined. 2) they are not invalid.");
cls_Prs3d_Presentation.def("Transformation", (const opencascade::handle<Geom_Transformation> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::Transformation, "Return local transformation.");
cls_Prs3d_Presentation.def("SetTransformation", (void (Graphic3d_Structure::*)(const opencascade::handle<Geom_Transformation> &)) &Graphic3d_Structure::SetTransformation, "Modifies the current local transformation", py::arg("theTrsf"));
cls_Prs3d_Presentation.def("Transform", (void (Graphic3d_Structure::*)(const opencascade::handle<Geom_Transformation> &)) &Graphic3d_Structure::Transform, "None", py::arg("theTrsf"));
cls_Prs3d_Presentation.def("SetTransformPersistence", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_TransformPers> &)) &Graphic3d_Structure::SetTransformPersistence, "Modifies the current transform persistence (pan, zoom or rotate)", py::arg("theTrsfPers"));
cls_Prs3d_Presentation.def("TransformPersistence", (const opencascade::handle<Graphic3d_TransformPers> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::TransformPersistence, "Returns transform persistence of the presentable object.");
cls_Prs3d_Presentation.def("SetMutable", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::SetMutable, "Sets if the structure location has mutable nature (content or location will be changed regularly).", py::arg("theIsMutable"));
cls_Prs3d_Presentation.def("IsMutable", (Standard_Boolean (Graphic3d_Structure::*)() const) &Graphic3d_Structure::IsMutable, "Returns true if structure has mutable nature (content or location are be changed regularly). Mutable structure will be managed in different way than static onces.");
cls_Prs3d_Presentation.def("ComputeVisual", (Graphic3d_TypeOfStructure (Graphic3d_Structure::*)() const) &Graphic3d_Structure::ComputeVisual, "None");
cls_Prs3d_Presentation.def("GraphicClear", (void (Graphic3d_Structure::*)(const Standard_Boolean)) &Graphic3d_Structure::GraphicClear, "Clears the structure <me>.", py::arg("WithDestruction"));
cls_Prs3d_Presentation.def("GraphicConnect", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::GraphicConnect, "None", py::arg("theDaughter"));
cls_Prs3d_Presentation.def("GraphicDisconnect", (void (Graphic3d_Structure::*)(const opencascade::handle<Graphic3d_Structure> &)) &Graphic3d_Structure::GraphicDisconnect, "None", py::arg("theDaughter"));
cls_Prs3d_Presentation.def("GraphicTransform", (void (Graphic3d_Structure::*)(const opencascade::handle<Geom_Transformation> &)) &Graphic3d_Structure::GraphicTransform, "Internal method which sets new transformation without calling graphic manager callbacks.", py::arg("theTrsf"));
cls_Prs3d_Presentation.def("Identification", (Standard_Integer (Graphic3d_Structure::*)() const) &Graphic3d_Structure::Identification, "Returns the identification number of this structure.");
cls_Prs3d_Presentation.def_static("PrintNetwork_", (void (*)(const opencascade::handle<Graphic3d_Structure> &, const Graphic3d_TypeOfConnection)) &Graphic3d_Structure::PrintNetwork, "Prints informations about the network associated with the structure <AStructure>.", py::arg("AStructure"), py::arg("AType"));
cls_Prs3d_Presentation.def("Remove", (void (Graphic3d_Structure::*)(Graphic3d_Structure *, const Graphic3d_TypeOfConnection)) &Graphic3d_Structure::Remove, "Suppress the structure in the list of descendants or in the list of ancestors.", py::arg("thePtr"), py::arg("theType"));
cls_Prs3d_Presentation.def("SetComputeVisual", (void (Graphic3d_Structure::*)(const Graphic3d_TypeOfStructure)) &Graphic3d_Structure::SetComputeVisual, "None", py::arg("theVisual"));
cls_Prs3d_Presentation.def_static("Transforms_", [](const gp_Trsf & theTrsf, const Standard_Real theX, const Standard_Real theY, const Standard_Real theZ, Standard_Real & theNewX, Standard_Real & theNewY, Standard_Real & theNewZ){ Graphic3d_Structure::Transforms(theTrsf, theX, theY, theZ, theNewX, theNewY, theNewZ); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &>(theNewX, theNewY, theNewZ); }, "Transforms theX, theY, theZ with the transformation theTrsf.", py::arg("theTrsf"), py::arg("theX"), py::arg("theY"), py::arg("theZ"), py::arg("theNewX"), py::arg("theNewY"), py::arg("theNewZ"));
cls_Prs3d_Presentation.def("CStructure", (const opencascade::handle<Graphic3d_CStructure> & (Graphic3d_Structure::*)() const) &Graphic3d_Structure::CStructure, "Returns the low-level structure");

// CLASS: PRS3D_BASICASPECT
py::class_<Prs3d_BasicAspect, opencascade::handle<Prs3d_BasicAspect>, Standard_Transient> cls_Prs3d_BasicAspect(mod, "Prs3d_BasicAspect", "All basic Prs3d_xxxAspect must inherits from this class The aspect classes qualifies how to represent a given kind of object.");

// Methods
cls_Prs3d_BasicAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_BasicAspect::get_type_name, "None");
cls_Prs3d_BasicAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_BasicAspect::get_type_descriptor, "None");
cls_Prs3d_BasicAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_BasicAspect::*)() const) &Prs3d_BasicAspect::DynamicType, "None");
cls_Prs3d_BasicAspect.def("DumpJson", [](Prs3d_BasicAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_BasicAspect.def("DumpJson", (void (Prs3d_BasicAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_BasicAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_ARROWASPECT
py::class_<Prs3d_ArrowAspect, opencascade::handle<Prs3d_ArrowAspect>, Prs3d_BasicAspect> cls_Prs3d_ArrowAspect(mod, "Prs3d_ArrowAspect", "A framework for displaying arrows in representations of dimensions and relations.");

// Constructors
cls_Prs3d_ArrowAspect.def(py::init<>());
cls_Prs3d_ArrowAspect.def(py::init<const Standard_Real, const Standard_Real>(), py::arg("anAngle"), py::arg("aLength"));
cls_Prs3d_ArrowAspect.def(py::init<const opencascade::handle<Graphic3d_AspectLine3d> &>(), py::arg("theAspect"));

// Methods
cls_Prs3d_ArrowAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_ArrowAspect::get_type_name, "None");
cls_Prs3d_ArrowAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_ArrowAspect::get_type_descriptor, "None");
cls_Prs3d_ArrowAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_ArrowAspect::*)() const) &Prs3d_ArrowAspect::DynamicType, "None");
cls_Prs3d_ArrowAspect.def("SetAngle", (void (Prs3d_ArrowAspect::*)(const Standard_Real)) &Prs3d_ArrowAspect::SetAngle, "defines the angle of the arrows.", py::arg("anAngle"));
cls_Prs3d_ArrowAspect.def("Angle", (Standard_Real (Prs3d_ArrowAspect::*)() const) &Prs3d_ArrowAspect::Angle, "returns the current value of the angle used when drawing an arrow.");
cls_Prs3d_ArrowAspect.def("SetLength", (void (Prs3d_ArrowAspect::*)(const Standard_Real)) &Prs3d_ArrowAspect::SetLength, "Defines the length of the arrows.", py::arg("theLength"));
cls_Prs3d_ArrowAspect.def("Length", (Standard_Real (Prs3d_ArrowAspect::*)() const) &Prs3d_ArrowAspect::Length, "Returns the current value of the length used when drawing an arrow.");
cls_Prs3d_ArrowAspect.def("SetColor", (void (Prs3d_ArrowAspect::*)(const Quantity_Color &)) &Prs3d_ArrowAspect::SetColor, "None", py::arg("theColor"));
cls_Prs3d_ArrowAspect.def("Aspect", (const opencascade::handle<Graphic3d_AspectLine3d> & (Prs3d_ArrowAspect::*)() const) &Prs3d_ArrowAspect::Aspect, "None");
cls_Prs3d_ArrowAspect.def("SetAspect", (void (Prs3d_ArrowAspect::*)(const opencascade::handle<Graphic3d_AspectLine3d> &)) &Prs3d_ArrowAspect::SetAspect, "None", py::arg("theAspect"));
cls_Prs3d_ArrowAspect.def("DumpJson", [](Prs3d_ArrowAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_ArrowAspect.def("DumpJson", (void (Prs3d_ArrowAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_ArrowAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_LINEASPECT
py::class_<Prs3d_LineAspect, opencascade::handle<Prs3d_LineAspect>, Prs3d_BasicAspect> cls_Prs3d_LineAspect(mod, "Prs3d_LineAspect", "A framework for defining how a line will be displayed in a presentation. Aspects of line display include width, color and type of line. The definition set by this class is then passed to the attribute manager Prs3d_Drawer. Any object which requires a value for line aspect as an argument may then be given the attribute manager as a substitute argument in the form of a field such as myDrawer for example.");

// Constructors
cls_Prs3d_LineAspect.def(py::init<const Quantity_Color &, const Aspect_TypeOfLine, const Standard_Real>(), py::arg("theColor"), py::arg("theType"), py::arg("theWidth"));
cls_Prs3d_LineAspect.def(py::init<const opencascade::handle<Graphic3d_AspectLine3d> &>(), py::arg("theAspect"));

// Methods
cls_Prs3d_LineAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_LineAspect::get_type_name, "None");
cls_Prs3d_LineAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_LineAspect::get_type_descriptor, "None");
cls_Prs3d_LineAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_LineAspect::*)() const) &Prs3d_LineAspect::DynamicType, "None");
cls_Prs3d_LineAspect.def("SetColor", (void (Prs3d_LineAspect::*)(const Quantity_Color &)) &Prs3d_LineAspect::SetColor, "Sets the line color defined at the time of construction. Default value: Quantity_NOC_YELLOW", py::arg("theColor"));
cls_Prs3d_LineAspect.def("SetTypeOfLine", (void (Prs3d_LineAspect::*)(const Aspect_TypeOfLine)) &Prs3d_LineAspect::SetTypeOfLine, "Sets the type of line defined at the time of construction. This could, for example, be solid, dotted or made up of dashes. Default value: Aspect_TOL_SOLID", py::arg("theType"));
cls_Prs3d_LineAspect.def("SetWidth", (void (Prs3d_LineAspect::*)(const Standard_Real)) &Prs3d_LineAspect::SetWidth, "Sets the line width defined at the time of construction. Default value: 1.", py::arg("theWidth"));
cls_Prs3d_LineAspect.def("Aspect", (const opencascade::handle<Graphic3d_AspectLine3d> & (Prs3d_LineAspect::*)() const) &Prs3d_LineAspect::Aspect, "Returns the line aspect. This is defined as the set of color, type and thickness attributes.");
cls_Prs3d_LineAspect.def("SetAspect", (void (Prs3d_LineAspect::*)(const opencascade::handle<Graphic3d_AspectLine3d> &)) &Prs3d_LineAspect::SetAspect, "None", py::arg("theAspect"));
cls_Prs3d_LineAspect.def("DumpJson", [](Prs3d_LineAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_LineAspect.def("DumpJson", (void (Prs3d_LineAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_LineAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_TEXTASPECT
py::class_<Prs3d_TextAspect, opencascade::handle<Prs3d_TextAspect>, Prs3d_BasicAspect> cls_Prs3d_TextAspect(mod, "Prs3d_TextAspect", "Defines the attributes when displaying a text.");

// Constructors
cls_Prs3d_TextAspect.def(py::init<>());
cls_Prs3d_TextAspect.def(py::init<const opencascade::handle<Graphic3d_AspectText3d> &>(), py::arg("theAspect"));

// Methods
cls_Prs3d_TextAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_TextAspect::get_type_name, "None");
cls_Prs3d_TextAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_TextAspect::get_type_descriptor, "None");
cls_Prs3d_TextAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::DynamicType, "None");
cls_Prs3d_TextAspect.def("SetColor", (void (Prs3d_TextAspect::*)(const Quantity_Color &)) &Prs3d_TextAspect::SetColor, "Sets the color of the type used in text display.", py::arg("theColor"));
cls_Prs3d_TextAspect.def("SetFont", (void (Prs3d_TextAspect::*)(const Standard_CString)) &Prs3d_TextAspect::SetFont, "Sets the font used in text display.", py::arg("theFont"));
cls_Prs3d_TextAspect.def("SetHeight", (void (Prs3d_TextAspect::*)(const Standard_Real)) &Prs3d_TextAspect::SetHeight, "Sets the height of the text.", py::arg("theHeight"));
cls_Prs3d_TextAspect.def("SetAngle", (void (Prs3d_TextAspect::*)(const Standard_Real)) &Prs3d_TextAspect::SetAngle, "Sets the angle", py::arg("theAngle"));
cls_Prs3d_TextAspect.def("Height", (Standard_Real (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::Height, "Returns the height of the text box.");
cls_Prs3d_TextAspect.def("Angle", (Standard_Real (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::Angle, "Returns the angle");
cls_Prs3d_TextAspect.def("SetHorizontalJustification", (void (Prs3d_TextAspect::*)(const Graphic3d_HorizontalTextAlignment)) &Prs3d_TextAspect::SetHorizontalJustification, "Sets horizontal alignment of text.", py::arg("theJustification"));
cls_Prs3d_TextAspect.def("SetVerticalJustification", (void (Prs3d_TextAspect::*)(const Graphic3d_VerticalTextAlignment)) &Prs3d_TextAspect::SetVerticalJustification, "Sets the vertical alignment of text.", py::arg("theJustification"));
cls_Prs3d_TextAspect.def("SetOrientation", (void (Prs3d_TextAspect::*)(const Graphic3d_TextPath)) &Prs3d_TextAspect::SetOrientation, "Sets the orientation of text.", py::arg("theOrientation"));
cls_Prs3d_TextAspect.def("HorizontalJustification", (Graphic3d_HorizontalTextAlignment (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::HorizontalJustification, "Returns the horizontal alignment of the text. The range of values includes: - left - center - right, and - normal (justified).");
cls_Prs3d_TextAspect.def("VerticalJustification", (Graphic3d_VerticalTextAlignment (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::VerticalJustification, "Returns the vertical alignment of the text. The range of values includes: - normal - top - cap - half - base - bottom");
cls_Prs3d_TextAspect.def("Orientation", (Graphic3d_TextPath (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::Orientation, "Returns the orientation of the text. Text can be displayed in the following directions: - up - down - left, or - right");
cls_Prs3d_TextAspect.def("Aspect", (const opencascade::handle<Graphic3d_AspectText3d> & (Prs3d_TextAspect::*)() const) &Prs3d_TextAspect::Aspect, "Returns the purely textual attributes used in the display of text. These include: - color - font - height/width ratio, that is, the expansion factor, and - space between characters.");
cls_Prs3d_TextAspect.def("SetAspect", (void (Prs3d_TextAspect::*)(const opencascade::handle<Graphic3d_AspectText3d> &)) &Prs3d_TextAspect::SetAspect, "None", py::arg("theAspect"));
cls_Prs3d_TextAspect.def("DumpJson", [](Prs3d_TextAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_TextAspect.def("DumpJson", (void (Prs3d_TextAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_TextAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_DIMENSIONASPECT
py::class_<Prs3d_DimensionAspect, opencascade::handle<Prs3d_DimensionAspect>, Prs3d_BasicAspect> cls_Prs3d_DimensionAspect(mod, "Prs3d_DimensionAspect", "defines the attributes when drawing a Length Presentation.");

// Constructors
cls_Prs3d_DimensionAspect.def(py::init<>());

// Methods
cls_Prs3d_DimensionAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_DimensionAspect::get_type_name, "None");
cls_Prs3d_DimensionAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_DimensionAspect::get_type_descriptor, "None");
cls_Prs3d_DimensionAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::DynamicType, "None");
cls_Prs3d_DimensionAspect.def("LineAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::LineAspect, "Returns the settings for the display of lines used in presentation of dimensions.");
cls_Prs3d_DimensionAspect.def("SetLineAspect", (void (Prs3d_DimensionAspect::*)(const opencascade::handle<Prs3d_LineAspect> &)) &Prs3d_DimensionAspect::SetLineAspect, "Sets the display attributes of lines used in presentation of dimensions.", py::arg("theAspect"));
cls_Prs3d_DimensionAspect.def("TextAspect", (const opencascade::handle<Prs3d_TextAspect> & (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::TextAspect, "Returns the settings for the display of text used in presentation of dimensions.");
cls_Prs3d_DimensionAspect.def("SetTextAspect", (void (Prs3d_DimensionAspect::*)(const opencascade::handle<Prs3d_TextAspect> &)) &Prs3d_DimensionAspect::SetTextAspect, "Sets the display attributes of text used in presentation of dimensions.", py::arg("theAspect"));
cls_Prs3d_DimensionAspect.def("IsText3d", (Standard_Boolean (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::IsText3d, "Check if text for dimension label is 3d.");
cls_Prs3d_DimensionAspect.def("MakeText3d", (void (Prs3d_DimensionAspect::*)(const Standard_Boolean)) &Prs3d_DimensionAspect::MakeText3d, "Sets type of text.", py::arg("isText3d"));
cls_Prs3d_DimensionAspect.def("IsTextShaded", (Standard_Boolean (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::IsTextShaded, "Check if 3d text for dimension label is shaded.");
cls_Prs3d_DimensionAspect.def("MakeTextShaded", (void (Prs3d_DimensionAspect::*)(const Standard_Boolean)) &Prs3d_DimensionAspect::MakeTextShaded, "Turns on/off text shading for 3d text.", py::arg("theIsTextShaded"));
cls_Prs3d_DimensionAspect.def("IsArrows3d", (Standard_Boolean (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::IsArrows3d, "Gets type of arrows.");
cls_Prs3d_DimensionAspect.def("MakeArrows3d", (void (Prs3d_DimensionAspect::*)(const Standard_Boolean)) &Prs3d_DimensionAspect::MakeArrows3d, "Sets type of arrows.", py::arg("theIsArrows3d"));
cls_Prs3d_DimensionAspect.def("IsUnitsDisplayed", (Standard_Boolean (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::IsUnitsDisplayed, "Shows if Units are to be displayed along with dimension value.");
cls_Prs3d_DimensionAspect.def("MakeUnitsDisplayed", (void (Prs3d_DimensionAspect::*)(const Standard_Boolean)) &Prs3d_DimensionAspect::MakeUnitsDisplayed, "Specifies whether the units string should be displayed along with value label or not.", py::arg("theIsDisplayed"));
cls_Prs3d_DimensionAspect.def("SetArrowOrientation", (void (Prs3d_DimensionAspect::*)(const Prs3d_DimensionArrowOrientation)) &Prs3d_DimensionAspect::SetArrowOrientation, "Sets orientation of arrows (external or internal). By default orientation is chosen automatically according to situation and text label size.", py::arg("theArrowOrient"));
cls_Prs3d_DimensionAspect.def("ArrowOrientation", (Prs3d_DimensionArrowOrientation (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::ArrowOrientation, "Gets orientation of arrows (external or internal).");
cls_Prs3d_DimensionAspect.def("SetTextVerticalPosition", (void (Prs3d_DimensionAspect::*)(const Prs3d_DimensionTextVerticalPosition)) &Prs3d_DimensionAspect::SetTextVerticalPosition, "Sets vertical text alignment for text label.", py::arg("thePosition"));
cls_Prs3d_DimensionAspect.def("TextVerticalPosition", (Prs3d_DimensionTextVerticalPosition (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::TextVerticalPosition, "Gets vertical text alignment for text label.");
cls_Prs3d_DimensionAspect.def("SetTextHorizontalPosition", (void (Prs3d_DimensionAspect::*)(const Prs3d_DimensionTextHorizontalPosition)) &Prs3d_DimensionAspect::SetTextHorizontalPosition, "Sets horizontal text alignment for text label.", py::arg("thePosition"));
cls_Prs3d_DimensionAspect.def("TextHorizontalPosition", (Prs3d_DimensionTextHorizontalPosition (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::TextHorizontalPosition, "Gets horizontal text alignment for text label.");
cls_Prs3d_DimensionAspect.def("ArrowAspect", (const opencascade::handle<Prs3d_ArrowAspect> & (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::ArrowAspect, "Returns the settings for displaying arrows.");
cls_Prs3d_DimensionAspect.def("SetArrowAspect", (void (Prs3d_DimensionAspect::*)(const opencascade::handle<Prs3d_ArrowAspect> &)) &Prs3d_DimensionAspect::SetArrowAspect, "Sets the display attributes of arrows used in presentation of dimensions.", py::arg("theAspect"));
cls_Prs3d_DimensionAspect.def("SetCommonColor", (void (Prs3d_DimensionAspect::*)(const Quantity_Color &)) &Prs3d_DimensionAspect::SetCommonColor, "Sets the same color for all parts of dimension: lines, arrows and text.", py::arg("theColor"));
cls_Prs3d_DimensionAspect.def("SetExtensionSize", (void (Prs3d_DimensionAspect::*)(const Standard_Real)) &Prs3d_DimensionAspect::SetExtensionSize, "Sets extension size.", py::arg("theSize"));
cls_Prs3d_DimensionAspect.def("ExtensionSize", (Standard_Real (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::ExtensionSize, "Returns extension size.");
cls_Prs3d_DimensionAspect.def("SetArrowTailSize", (void (Prs3d_DimensionAspect::*)(const Standard_Real)) &Prs3d_DimensionAspect::SetArrowTailSize, "Set size for arrow tail (extension without text).", py::arg("theSize"));
cls_Prs3d_DimensionAspect.def("ArrowTailSize", (Standard_Real (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::ArrowTailSize, "Returns arrow tail size.");
cls_Prs3d_DimensionAspect.def("SetValueStringFormat", (void (Prs3d_DimensionAspect::*)(const TCollection_AsciiString &)) &Prs3d_DimensionAspect::SetValueStringFormat, "Sets 'sprintf'-syntax format for formatting dimension value labels.", py::arg("theFormat"));
cls_Prs3d_DimensionAspect.def("ValueStringFormat", (const TCollection_AsciiString & (Prs3d_DimensionAspect::*)() const) &Prs3d_DimensionAspect::ValueStringFormat, "Returns format.");
cls_Prs3d_DimensionAspect.def("DumpJson", [](Prs3d_DimensionAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_DimensionAspect.def("DumpJson", (void (Prs3d_DimensionAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_DimensionAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_PROJECTOR
py::class_<Prs3d_Projector, opencascade::handle<Prs3d_Projector>, Standard_Transient> cls_Prs3d_Projector(mod, "Prs3d_Projector", "A projector object. This object defines the parameters of a view for a visualization algorithm. It is, for example, used by the hidden line removal algorithms.");

// Constructors
cls_Prs3d_Projector.def(py::init<const HLRAlgo_Projector &>(), py::arg("Pr"));
cls_Prs3d_Projector.def(py::init<const Standard_Boolean, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pers"), py::arg("Focus"), py::arg("DX"), py::arg("DY"), py::arg("DZ"), py::arg("XAt"), py::arg("YAt"), py::arg("ZAt"), py::arg("XUp"), py::arg("YUp"), py::arg("ZUp"));

// Methods
cls_Prs3d_Projector.def("Projector", (HLRAlgo_Projector (Prs3d_Projector::*)() const) &Prs3d_Projector::Projector, "Returns a projector object for use in a hidden line removal algorithm.");
cls_Prs3d_Projector.def_static("get_type_name_", (const char * (*)()) &Prs3d_Projector::get_type_name, "None");
cls_Prs3d_Projector.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_Projector::get_type_descriptor, "None");
cls_Prs3d_Projector.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_Projector::*)() const) &Prs3d_Projector::DynamicType, "None");

// CLASS: PRS3D_SHADINGASPECT
py::class_<Prs3d_ShadingAspect, opencascade::handle<Prs3d_ShadingAspect>, Prs3d_BasicAspect> cls_Prs3d_ShadingAspect(mod, "Prs3d_ShadingAspect", "A framework to define the display of shading. The attributes which make up this definition include: - fill aspect - color, and - material");

// Constructors
cls_Prs3d_ShadingAspect.def(py::init<>());
cls_Prs3d_ShadingAspect.def(py::init<const opencascade::handle<Graphic3d_AspectFillArea3d> &>(), py::arg("theAspect"));

// Methods
cls_Prs3d_ShadingAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_ShadingAspect::get_type_name, "None");
cls_Prs3d_ShadingAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_ShadingAspect::get_type_descriptor, "None");
cls_Prs3d_ShadingAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_ShadingAspect::*)() const) &Prs3d_ShadingAspect::DynamicType, "None");
cls_Prs3d_ShadingAspect.def("SetColor", [](Prs3d_ShadingAspect &self, const Quantity_Color & a0) -> void { return self.SetColor(a0); });
cls_Prs3d_ShadingAspect.def("SetColor", (void (Prs3d_ShadingAspect::*)(const Quantity_Color &, const Aspect_TypeOfFacingModel)) &Prs3d_ShadingAspect::SetColor, "Change the polygons interior color and material ambient color.", py::arg("aColor"), py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("SetMaterial", [](Prs3d_ShadingAspect &self, const Graphic3d_MaterialAspect & a0) -> void { return self.SetMaterial(a0); });
cls_Prs3d_ShadingAspect.def("SetMaterial", (void (Prs3d_ShadingAspect::*)(const Graphic3d_MaterialAspect &, const Aspect_TypeOfFacingModel)) &Prs3d_ShadingAspect::SetMaterial, "Change the polygons material aspect.", py::arg("aMaterial"), py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("SetTransparency", [](Prs3d_ShadingAspect &self, const Standard_Real a0) -> void { return self.SetTransparency(a0); });
cls_Prs3d_ShadingAspect.def("SetTransparency", (void (Prs3d_ShadingAspect::*)(const Standard_Real, const Aspect_TypeOfFacingModel)) &Prs3d_ShadingAspect::SetTransparency, "Change the polygons transparency value. Warning : aValue must be in the range 0,1. 0 is the default (NO transparent)", py::arg("aValue"), py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("Color", [](Prs3d_ShadingAspect &self) -> const Quantity_Color & { return self.Color(); });
cls_Prs3d_ShadingAspect.def("Color", (const Quantity_Color & (Prs3d_ShadingAspect::*)(const Aspect_TypeOfFacingModel) const) &Prs3d_ShadingAspect::Color, "Returns the polygons color.", py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("Material", [](Prs3d_ShadingAspect &self) -> const Graphic3d_MaterialAspect & { return self.Material(); });
cls_Prs3d_ShadingAspect.def("Material", (const Graphic3d_MaterialAspect & (Prs3d_ShadingAspect::*)(const Aspect_TypeOfFacingModel) const) &Prs3d_ShadingAspect::Material, "Returns the polygons material aspect.", py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("Transparency", [](Prs3d_ShadingAspect &self) -> Standard_Real { return self.Transparency(); });
cls_Prs3d_ShadingAspect.def("Transparency", (Standard_Real (Prs3d_ShadingAspect::*)(const Aspect_TypeOfFacingModel) const) &Prs3d_ShadingAspect::Transparency, "Returns the polygons transparency value.", py::arg("aModel"));
cls_Prs3d_ShadingAspect.def("Aspect", (const opencascade::handle<Graphic3d_AspectFillArea3d> & (Prs3d_ShadingAspect::*)() const) &Prs3d_ShadingAspect::Aspect, "Returns the polygons aspect properties.");
cls_Prs3d_ShadingAspect.def("SetAspect", (void (Prs3d_ShadingAspect::*)(const opencascade::handle<Graphic3d_AspectFillArea3d> &)) &Prs3d_ShadingAspect::SetAspect, "None", py::arg("theAspect"));
cls_Prs3d_ShadingAspect.def("DumpJson", [](Prs3d_ShadingAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_ShadingAspect.def("DumpJson", (void (Prs3d_ShadingAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_ShadingAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_POINTASPECT
py::class_<Prs3d_PointAspect, opencascade::handle<Prs3d_PointAspect>, Prs3d_BasicAspect> cls_Prs3d_PointAspect(mod, "Prs3d_PointAspect", "This class defines attributes for the points The points are drawn using markers, whose size does not depend on the zoom value of the views.");

// Constructors
cls_Prs3d_PointAspect.def(py::init<const Aspect_TypeOfMarker, const Quantity_Color &, const Standard_Real>(), py::arg("theType"), py::arg("theColor"), py::arg("theScale"));
cls_Prs3d_PointAspect.def(py::init<const Quantity_Color &, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfByte> &>(), py::arg("theColor"), py::arg("theWidth"), py::arg("theHeight"), py::arg("theTexture"));
cls_Prs3d_PointAspect.def(py::init<const opencascade::handle<Graphic3d_AspectMarker3d> &>(), py::arg("theAspect"));

// Methods
cls_Prs3d_PointAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_PointAspect::get_type_name, "None");
cls_Prs3d_PointAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_PointAspect::get_type_descriptor, "None");
cls_Prs3d_PointAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_PointAspect::*)() const) &Prs3d_PointAspect::DynamicType, "None");
cls_Prs3d_PointAspect.def("SetColor", (void (Prs3d_PointAspect::*)(const Quantity_Color &)) &Prs3d_PointAspect::SetColor, "defines the color to be used when drawing a point. Default value: Quantity_NOC_YELLOW", py::arg("theColor"));
cls_Prs3d_PointAspect.def("SetTypeOfMarker", (void (Prs3d_PointAspect::*)(const Aspect_TypeOfMarker)) &Prs3d_PointAspect::SetTypeOfMarker, "defines the type of representation to be used when drawing a point. Default value: Aspect_TOM_PLUS", py::arg("theType"));
cls_Prs3d_PointAspect.def("SetScale", (void (Prs3d_PointAspect::*)(const Standard_Real)) &Prs3d_PointAspect::SetScale, "defines the size of the marker used when drawing a point. Default value: 1.", py::arg("theScale"));
cls_Prs3d_PointAspect.def("Aspect", (const opencascade::handle<Graphic3d_AspectMarker3d> & (Prs3d_PointAspect::*)() const) &Prs3d_PointAspect::Aspect, "None");
cls_Prs3d_PointAspect.def("SetAspect", (void (Prs3d_PointAspect::*)(const opencascade::handle<Graphic3d_AspectMarker3d> &)) &Prs3d_PointAspect::SetAspect, "None", py::arg("theAspect"));
cls_Prs3d_PointAspect.def("GetTextureSize", [](Prs3d_PointAspect &self, Standard_Integer & theWidth, Standard_Integer & theHeight){ self.GetTextureSize(theWidth, theHeight); return std::tuple<Standard_Integer &, Standard_Integer &>(theWidth, theHeight); }, "Returns marker's texture size.", py::arg("theWidth"), py::arg("theHeight"));
cls_Prs3d_PointAspect.def("GetTexture", (const opencascade::handle<Graphic3d_MarkerImage> & (Prs3d_PointAspect::*)() const) &Prs3d_PointAspect::GetTexture, "Returns marker's texture.");
cls_Prs3d_PointAspect.def("DumpJson", [](Prs3d_PointAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_PointAspect.def("DumpJson", (void (Prs3d_PointAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_PointAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_DATUMASPECT
py::class_<Prs3d_DatumAspect, opencascade::handle<Prs3d_DatumAspect>, Prs3d_BasicAspect> cls_Prs3d_DatumAspect(mod, "Prs3d_DatumAspect", "A framework to define the display of datums.");

// Constructors
cls_Prs3d_DatumAspect.def(py::init<>());

// Methods
cls_Prs3d_DatumAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_DatumAspect::get_type_name, "None");
cls_Prs3d_DatumAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_DatumAspect::get_type_descriptor, "None");
cls_Prs3d_DatumAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::DynamicType, "None");
cls_Prs3d_DatumAspect.def("LineAspect", (opencascade::handle<Prs3d_LineAspect> (Prs3d_DatumAspect::*)(Prs3d_DatumParts) const) &Prs3d_DatumAspect::LineAspect, "Returns the right-handed coordinate system set in SetComponent.", py::arg("thePart"));
cls_Prs3d_DatumAspect.def("ShadingAspect", (opencascade::handle<Prs3d_ShadingAspect> (Prs3d_DatumAspect::*)(Prs3d_DatumParts) const) &Prs3d_DatumAspect::ShadingAspect, "Returns the right-handed coordinate system set in SetComponent.", py::arg("thePart"));
cls_Prs3d_DatumAspect.def("TextAspect", (const opencascade::handle<Prs3d_TextAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::TextAspect, "Returns the text attributes for rendering labels.");
cls_Prs3d_DatumAspect.def("SetTextAspect", (void (Prs3d_DatumAspect::*)(const opencascade::handle<Prs3d_TextAspect> &)) &Prs3d_DatumAspect::SetTextAspect, "Sets text attributes for rendering labels.", py::arg("theTextAspect"));
cls_Prs3d_DatumAspect.def("PointAspect", (const opencascade::handle<Prs3d_PointAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::PointAspect, "Returns the point aspect of origin wireframe presentation");
cls_Prs3d_DatumAspect.def("SetPointAspect", (void (Prs3d_DatumAspect::*)(const opencascade::handle<Prs3d_PointAspect> &)) &Prs3d_DatumAspect::SetPointAspect, "Returns the point aspect of origin wireframe presentation", py::arg("theAspect"));
cls_Prs3d_DatumAspect.def("ArrowAspect", (const opencascade::handle<Prs3d_ArrowAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::ArrowAspect, "Returns the arrow aspect of presentation");
cls_Prs3d_DatumAspect.def("SetArrowAspect", (void (Prs3d_DatumAspect::*)(const opencascade::handle<Prs3d_ArrowAspect> &)) &Prs3d_DatumAspect::SetArrowAspect, "Sets the arrow aspect of presentation", py::arg("theAspect"));
cls_Prs3d_DatumAspect.def("FirstAxisAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::FirstAxisAspect, "Returns the attributes for display of the first axis.");
cls_Prs3d_DatumAspect.def("SecondAxisAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::SecondAxisAspect, "Returns the attributes for display of the second axis.");
cls_Prs3d_DatumAspect.def("ThirdAxisAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::ThirdAxisAspect, "Returns the attributes for display of the third axis.");
cls_Prs3d_DatumAspect.def("SetDrawFirstAndSecondAxis", (void (Prs3d_DatumAspect::*)(Standard_Boolean)) &Prs3d_DatumAspect::SetDrawFirstAndSecondAxis, "Sets the DrawFirstAndSecondAxis attributes to active.", py::arg("theToDraw"));
cls_Prs3d_DatumAspect.def("DrawFirstAndSecondAxis", (Standard_Boolean (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::DrawFirstAndSecondAxis, "Returns true if the first and second axes can be drawn.");
cls_Prs3d_DatumAspect.def("SetDrawThirdAxis", (void (Prs3d_DatumAspect::*)(Standard_Boolean)) &Prs3d_DatumAspect::SetDrawThirdAxis, "Sets the DrawThirdAxis attributes to active.", py::arg("theToDraw"));
cls_Prs3d_DatumAspect.def("DrawThirdAxis", (Standard_Boolean (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::DrawThirdAxis, "Returns true if the third axis can be drawn.");
cls_Prs3d_DatumAspect.def("DrawDatumPart", (Standard_Boolean (Prs3d_DatumAspect::*)(Prs3d_DatumParts) const) &Prs3d_DatumAspect::DrawDatumPart, "Returns true if the given part is used in axes of aspect", py::arg("thePart"));
cls_Prs3d_DatumAspect.def("SetDrawDatumAxes", (void (Prs3d_DatumAspect::*)(Prs3d_DatumAxes)) &Prs3d_DatumAspect::SetDrawDatumAxes, "Sets the axes used in the datum aspect", py::arg("theType"));
cls_Prs3d_DatumAspect.def("DatumAxes", (Prs3d_DatumAxes (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::DatumAxes, "Returns axes used in the datum aspect");
cls_Prs3d_DatumAspect.def("SetAttribute", (void (Prs3d_DatumAspect::*)(Prs3d_DatumAttribute, const Standard_Real &)) &Prs3d_DatumAspect::SetAttribute, "Sets the attribute of the datum type", py::arg("theType"), py::arg("theValue"));
cls_Prs3d_DatumAspect.def("Attribute", (Standard_Real (Prs3d_DatumAspect::*)(Prs3d_DatumAttribute) const) &Prs3d_DatumAspect::Attribute, "Returns the attribute of the datum type", py::arg("theType"));
cls_Prs3d_DatumAspect.def("SetAxisLength", (void (Prs3d_DatumAspect::*)(Standard_Real, Standard_Real, Standard_Real)) &Prs3d_DatumAspect::SetAxisLength, "Sets the lengths of the three axes.", py::arg("theL1"), py::arg("theL2"), py::arg("theL3"));
cls_Prs3d_DatumAspect.def("AxisLength", (Standard_Real (Prs3d_DatumAspect::*)(Prs3d_DatumParts) const) &Prs3d_DatumAspect::AxisLength, "Returns the length of the displayed first axis.", py::arg("thePart"));
cls_Prs3d_DatumAspect.def("FirstAxisLength", (Standard_Real (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::FirstAxisLength, "Returns the length of the displayed first axis.");
cls_Prs3d_DatumAspect.def("SecondAxisLength", (Standard_Real (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::SecondAxisLength, "Returns the length of the displayed second axis.");
cls_Prs3d_DatumAspect.def("ThirdAxisLength", (Standard_Real (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::ThirdAxisLength, "Returns the length of the displayed third axis.");
cls_Prs3d_DatumAspect.def("ToDrawLabels", (Standard_Boolean (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::ToDrawLabels, "Returns true if axes labels are drawn; TRUE by default.");
cls_Prs3d_DatumAspect.def("SetDrawLabels", (void (Prs3d_DatumAspect::*)(Standard_Boolean)) &Prs3d_DatumAspect::SetDrawLabels, "Sets option to draw or not to draw text labels for axes", py::arg("theToDraw"));
cls_Prs3d_DatumAspect.def("SetToDrawLabels", (void (Prs3d_DatumAspect::*)(Standard_Boolean)) &Prs3d_DatumAspect::SetToDrawLabels, "None", py::arg("theToDraw"));
cls_Prs3d_DatumAspect.def("ToDrawArrows", (Standard_Boolean (Prs3d_DatumAspect::*)() const) &Prs3d_DatumAspect::ToDrawArrows, "Returns true if axes arrows are drawn; TRUE by default.");
cls_Prs3d_DatumAspect.def("SetDrawArrows", (void (Prs3d_DatumAspect::*)(Standard_Boolean)) &Prs3d_DatumAspect::SetDrawArrows, "Sets option to draw or not arrows for axes", py::arg("theToDraw"));
cls_Prs3d_DatumAspect.def("ArrowPartForAxis", (Prs3d_DatumParts (Prs3d_DatumAspect::*)(Prs3d_DatumParts) const) &Prs3d_DatumAspect::ArrowPartForAxis, "Returns type of arrow for a type of axis", py::arg("thePart"));
cls_Prs3d_DatumAspect.def("DumpJson", [](Prs3d_DatumAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_DatumAspect.def("DumpJson", (void (Prs3d_DatumAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_DatumAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_ROOT
py::class_<Prs3d_Root> cls_Prs3d_Root(mod, "Prs3d_Root", "A root class for the standard presentation algorithms of the StdPrs package.");

// Constructors
cls_Prs3d_Root.def(py::init<>());

// Methods
// cls_Prs3d_Root.def_static("operator new_", (void * (*)(size_t)) &Prs3d_Root::operator new, "None", py::arg("theSize"));
// cls_Prs3d_Root.def_static("operator delete_", (void (*)(void *)) &Prs3d_Root::operator delete, "None", py::arg("theAddress"));
// cls_Prs3d_Root.def_static("operator new[]_", (void * (*)(size_t)) &Prs3d_Root::operator new[], "None", py::arg("theSize"));
// cls_Prs3d_Root.def_static("operator delete[]_", (void (*)(void *)) &Prs3d_Root::operator delete[], "None", py::arg("theAddress"));
// cls_Prs3d_Root.def_static("operator new_", (void * (*)(size_t, void *)) &Prs3d_Root::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Prs3d_Root.def_static("operator delete_", (void (*)(void *, void *)) &Prs3d_Root::operator delete, "None", py::arg(""), py::arg(""));
cls_Prs3d_Root.def_static("CurrentGroup_", (opencascade::handle<Graphic3d_Group> (*)(const opencascade::handle<Prs3d_Presentation> &)) &Prs3d_Root::CurrentGroup, "Returns the current (last created) group of primititves inside graphic objects in the display. A group also contains the attributes whose ranges are limited to the primitives in it.", py::arg("thePrs3d"));
cls_Prs3d_Root.def_static("NewGroup_", (opencascade::handle<Graphic3d_Group> (*)(const opencascade::handle<Prs3d_Presentation> &)) &Prs3d_Root::NewGroup, "Returns the new group of primitives inside graphic objects in the display. A group also contains the attributes whose ranges are limited to the primitives in it.", py::arg("thePrs3d"));

// TYPEDEF: PRS3D_NLISTOFSEQUENCEOFPNT
bind_NCollection_List<opencascade::handle<TColgp_HSequenceOfPnt> >(mod, "Prs3d_NListOfSequenceOfPnt", py::module_local(false));

// CLASS: PRS3D
py::class_<Prs3d> cls_Prs3d(mod, "Prs3d", "The Prs3d package provides the following services - a presentation object (the context for all modifications to the display, its presentation will be displayed in every view of an active viewer) - an attribute manager governing how objects such as color, width, and type of line are displayed; these are generic objects, whereas those in StdPrs are specific geometries and topologies. - generic algorithms providing default settings for objects such as points, curves, surfaces and shapes - a root object which provides the abstract framework for the DsgPrs definitions at work in display of dimensions, relations and trihedra.");

// Constructors
cls_Prs3d.def(py::init<>());

// Methods
// cls_Prs3d.def_static("operator new_", (void * (*)(size_t)) &Prs3d::operator new, "None", py::arg("theSize"));
// cls_Prs3d.def_static("operator delete_", (void (*)(void *)) &Prs3d::operator delete, "None", py::arg("theAddress"));
// cls_Prs3d.def_static("operator new[]_", (void * (*)(size_t)) &Prs3d::operator new[], "None", py::arg("theSize"));
// cls_Prs3d.def_static("operator delete[]_", (void (*)(void *)) &Prs3d::operator delete[], "None", py::arg("theAddress"));
// cls_Prs3d.def_static("operator new_", (void * (*)(size_t, void *)) &Prs3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Prs3d.def_static("operator delete_", (void (*)(void *, void *)) &Prs3d::operator delete, "None", py::arg(""), py::arg(""));
cls_Prs3d.def_static("MatchSegment_", [](const Standard_Real X, const Standard_Real Y, const Standard_Real Z, const Standard_Real aDistance, const gp_Pnt & p1, const gp_Pnt & p2, Standard_Real & dist){ Standard_Boolean rv = Prs3d::MatchSegment(X, Y, Z, aDistance, p1, p2, dist); return std::tuple<Standard_Boolean, Standard_Real &>(rv, dist); }, "draws an arrow at a given location, with respect to a given direction.", py::arg("X"), py::arg("Y"), py::arg("Z"), py::arg("aDistance"), py::arg("p1"), py::arg("p2"), py::arg("dist"));
cls_Prs3d.def_static("GetDeflection_", (Standard_Real (*)(const TopoDS_Shape &, const opencascade::handle<Prs3d_Drawer> &)) &Prs3d::GetDeflection, "Computes the absolute deflection value depending on the type of deflection in theDrawer: Aspect_TOD_RELATIVE: the absolute deflection is computed using the relative deviation coefficient from theDrawer and the shape's bounding box; Aspect_TOD_ABSOLUTE: the maximal chordial deviation from theDrawer is returned. In case of the type of deflection in theDrawer computed relative deflection for shape is stored as absolute deflection. It is necessary to use it later on for sub-shapes. This function should always be used to compute the deflection value for building discrete representations of the shape (triangualtion, wireframe) to avoid incosistencies between different representations of the shape and undesirable visual artifacts.", py::arg("theShape"), py::arg("theDrawer"));
cls_Prs3d.def_static("PrimitivesFromPolylines_", (opencascade::handle<Graphic3d_ArrayOfPrimitives> (*)(const Prs3d_NListOfSequenceOfPnt &)) &Prs3d::PrimitivesFromPolylines, "Assembles array of primitives for sequence of polylines.", py::arg("thePoints"));
cls_Prs3d.def_static("AddPrimitivesGroup_", (void (*)(const opencascade::handle<Prs3d_Presentation> &, const opencascade::handle<Prs3d_LineAspect> &, Prs3d_NListOfSequenceOfPnt &)) &Prs3d::AddPrimitivesGroup, "Add primitives into new group in presentation and clear the list of polylines.", py::arg("thePrs"), py::arg("theAspect"), py::arg("thePolylines"));

// CLASS: PRS3D_ARROW
py::class_<Prs3d_Arrow, Prs3d_Root> cls_Prs3d_Arrow(mod, "Prs3d_Arrow", "Provides class methods to draw an arrow at a given location, along a given direction and using a given angle.");

// Constructors
cls_Prs3d_Arrow.def(py::init<>());

// Methods
cls_Prs3d_Arrow.def_static("DrawShaded_", (opencascade::handle<Graphic3d_ArrayOfTriangles> (*)(const gp_Ax1 &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer)) &Prs3d_Arrow::DrawShaded, "Defines the representation of the arrow as shaded triangulation.", py::arg("theAxis"), py::arg("theTubeRadius"), py::arg("theAxisLength"), py::arg("theConeRadius"), py::arg("theConeLength"), py::arg("theNbFacettes"));
cls_Prs3d_Arrow.def_static("DrawSegments_", (opencascade::handle<Graphic3d_ArrayOfSegments> (*)(const gp_Pnt &, const gp_Dir &, const Standard_Real, const Standard_Real, const Standard_Integer)) &Prs3d_Arrow::DrawSegments, "Defines the representation of the arrow as a container of segments.", py::arg("theLocation"), py::arg("theDir"), py::arg("theAngle"), py::arg("theLength"), py::arg("theNbSegments"));
cls_Prs3d_Arrow.def_static("Draw_", (void (*)(const opencascade::handle<Graphic3d_Group> &, const gp_Pnt &, const gp_Dir &, const Standard_Real, const Standard_Real)) &Prs3d_Arrow::Draw, "Defines the representation of the arrow. Note that this method does NOT assign any presentation aspects to the primitives group!", py::arg("theGroup"), py::arg("theLocation"), py::arg("theDirection"), py::arg("theAngle"), py::arg("theLength"));
cls_Prs3d_Arrow.def_static("Draw_", (void (*)(const opencascade::handle<Prs3d_Presentation> &, const gp_Pnt &, const gp_Dir &, const Standard_Real, const Standard_Real)) &Prs3d_Arrow::Draw, "Alias to another method Draw() for backward compatibility.", py::arg("thePrs"), py::arg("theLocation"), py::arg("theDirection"), py::arg("theAngle"), py::arg("theLength"));

// CLASS: PRS3D_INVALIDANGLE
py::class_<Prs3d_InvalidAngle, opencascade::handle<Prs3d_InvalidAngle>, Standard_RangeError> cls_Prs3d_InvalidAngle(mod, "Prs3d_InvalidAngle", "None");

// Constructors
cls_Prs3d_InvalidAngle.def(py::init<>());
cls_Prs3d_InvalidAngle.def(py::init<const Standard_CString>(), py::arg("theMessage"));

// Methods
cls_Prs3d_InvalidAngle.def_static("Raise_", (void (*)(const Standard_CString)) &Prs3d_InvalidAngle::Raise, "None", py::arg("theMessage"));
cls_Prs3d_InvalidAngle.def_static("Raise_", (void (*)(Standard_SStream &)) &Prs3d_InvalidAngle::Raise, "None", py::arg("theMessage"));
cls_Prs3d_InvalidAngle.def_static("NewInstance_", (opencascade::handle<Prs3d_InvalidAngle> (*)(const Standard_CString)) &Prs3d_InvalidAngle::NewInstance, "None", py::arg("theMessage"));
cls_Prs3d_InvalidAngle.def_static("get_type_name_", (const char * (*)()) &Prs3d_InvalidAngle::get_type_name, "None");
cls_Prs3d_InvalidAngle.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_InvalidAngle::get_type_descriptor, "None");
cls_Prs3d_InvalidAngle.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_InvalidAngle::*)() const) &Prs3d_InvalidAngle::DynamicType, "None");

// CLASS: PRS3D_ISOASPECT
py::class_<Prs3d_IsoAspect, opencascade::handle<Prs3d_IsoAspect>, Prs3d_LineAspect> cls_Prs3d_IsoAspect(mod, "Prs3d_IsoAspect", "A framework to define the display attributes of isoparameters. This framework can be used to modify the default setting for isoparameters in Prs3d_Drawer.");

// Constructors
cls_Prs3d_IsoAspect.def(py::init<const Quantity_Color &, const Aspect_TypeOfLine, const Standard_Real, const Standard_Integer>(), py::arg("theColor"), py::arg("theType"), py::arg("theWidth"), py::arg("theNumber"));

// Methods
cls_Prs3d_IsoAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_IsoAspect::get_type_name, "None");
cls_Prs3d_IsoAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_IsoAspect::get_type_descriptor, "None");
cls_Prs3d_IsoAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_IsoAspect::*)() const) &Prs3d_IsoAspect::DynamicType, "None");
cls_Prs3d_IsoAspect.def("SetNumber", (void (Prs3d_IsoAspect::*)(const Standard_Integer)) &Prs3d_IsoAspect::SetNumber, "defines the number of U or V isoparametric curves to be drawn for a single face. Default value: 10", py::arg("theNumber"));
cls_Prs3d_IsoAspect.def("Number", (Standard_Integer (Prs3d_IsoAspect::*)() const) &Prs3d_IsoAspect::Number, "returns the number of U or V isoparametric curves drawn for a single face.");

// TYPEDEF: PRS3D_NLISTITERATOROFLISTOFSEQUENCEOFPNT
bind_NCollection_TListIterator<opencascade::handle<TColgp_HSequenceOfPnt> >(mod, "Prs3d_NListIteratorOfListOfSequenceOfPnt", py::module_local(false));

// CLASS: PRS3D_PLANEASPECT
py::class_<Prs3d_PlaneAspect, opencascade::handle<Prs3d_PlaneAspect>, Prs3d_BasicAspect> cls_Prs3d_PlaneAspect(mod, "Prs3d_PlaneAspect", "A framework to define the display of planes.");

// Constructors
cls_Prs3d_PlaneAspect.def(py::init<>());

// Methods
cls_Prs3d_PlaneAspect.def_static("get_type_name_", (const char * (*)()) &Prs3d_PlaneAspect::get_type_name, "None");
cls_Prs3d_PlaneAspect.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_PlaneAspect::get_type_descriptor, "None");
cls_Prs3d_PlaneAspect.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::DynamicType, "None");
cls_Prs3d_PlaneAspect.def("EdgesAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::EdgesAspect, "Returns the attributes of displayed edges involved in the presentation of planes.");
cls_Prs3d_PlaneAspect.def("IsoAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::IsoAspect, "Returns the attributes of displayed isoparameters involved in the presentation of planes.");
cls_Prs3d_PlaneAspect.def("ArrowAspect", (const opencascade::handle<Prs3d_LineAspect> & (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::ArrowAspect, "Returns the settings for displaying an arrow.");
cls_Prs3d_PlaneAspect.def("SetArrowsLength", (void (Prs3d_PlaneAspect::*)(const Standard_Real)) &Prs3d_PlaneAspect::SetArrowsLength, "None", py::arg("theLength"));
cls_Prs3d_PlaneAspect.def("ArrowsLength", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::ArrowsLength, "Returns the length of the arrow shaft used in the display of arrows.");
cls_Prs3d_PlaneAspect.def("SetArrowsSize", (void (Prs3d_PlaneAspect::*)(const Standard_Real)) &Prs3d_PlaneAspect::SetArrowsSize, "Sets the angle of the arrowhead used in the display of planes.", py::arg("theSize"));
cls_Prs3d_PlaneAspect.def("ArrowsSize", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::ArrowsSize, "Returns the size of arrows used in the display of planes.");
cls_Prs3d_PlaneAspect.def("SetArrowsAngle", (void (Prs3d_PlaneAspect::*)(const Standard_Real)) &Prs3d_PlaneAspect::SetArrowsAngle, "Sets the angle of the arrowhead used in the display of arrows involved in the presentation of planes.", py::arg("theAngle"));
cls_Prs3d_PlaneAspect.def("ArrowsAngle", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::ArrowsAngle, "Returns the angle of the arrowhead used in the display of arrows involved in the presentation of planes.");
cls_Prs3d_PlaneAspect.def("SetDisplayCenterArrow", (void (Prs3d_PlaneAspect::*)(const Standard_Boolean)) &Prs3d_PlaneAspect::SetDisplayCenterArrow, "Sets the display attributes defined in DisplayCenterArrow to active.", py::arg("theToDraw"));
cls_Prs3d_PlaneAspect.def("DisplayCenterArrow", (Standard_Boolean (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::DisplayCenterArrow, "Returns true if the display of center arrows is allowed.");
cls_Prs3d_PlaneAspect.def("SetDisplayEdgesArrows", (void (Prs3d_PlaneAspect::*)(const Standard_Boolean)) &Prs3d_PlaneAspect::SetDisplayEdgesArrows, "Sets the display attributes defined in DisplayEdgesArrows to active.", py::arg("theToDraw"));
cls_Prs3d_PlaneAspect.def("DisplayEdgesArrows", (Standard_Boolean (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::DisplayEdgesArrows, "Returns true if the display of edge arrows is allowed.");
cls_Prs3d_PlaneAspect.def("SetDisplayEdges", (void (Prs3d_PlaneAspect::*)(const Standard_Boolean)) &Prs3d_PlaneAspect::SetDisplayEdges, "None", py::arg("theToDraw"));
cls_Prs3d_PlaneAspect.def("DisplayEdges", (Standard_Boolean (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::DisplayEdges, "None");
cls_Prs3d_PlaneAspect.def("SetDisplayIso", (void (Prs3d_PlaneAspect::*)(const Standard_Boolean)) &Prs3d_PlaneAspect::SetDisplayIso, "Sets the display attributes defined in DisplayIso to active.", py::arg("theToDraw"));
cls_Prs3d_PlaneAspect.def("DisplayIso", (Standard_Boolean (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::DisplayIso, "Returns true if the display of isoparameters is allowed.");
cls_Prs3d_PlaneAspect.def("SetPlaneLength", (void (Prs3d_PlaneAspect::*)(const Standard_Real, const Standard_Real)) &Prs3d_PlaneAspect::SetPlaneLength, "None", py::arg("theLX"), py::arg("theLY"));
cls_Prs3d_PlaneAspect.def("PlaneXLength", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::PlaneXLength, "Returns the length of the x axis used in the display of planes.");
cls_Prs3d_PlaneAspect.def("PlaneYLength", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::PlaneYLength, "Returns the length of the y axis used in the display of planes.");
cls_Prs3d_PlaneAspect.def("SetIsoDistance", (void (Prs3d_PlaneAspect::*)(const Standard_Real)) &Prs3d_PlaneAspect::SetIsoDistance, "Sets the distance L between isoparameters used in the display of planes.", py::arg("theL"));
cls_Prs3d_PlaneAspect.def("IsoDistance", (Standard_Real (Prs3d_PlaneAspect::*)() const) &Prs3d_PlaneAspect::IsoDistance, "Returns the distance between isoparameters used in the display of planes.");
cls_Prs3d_PlaneAspect.def("DumpJson", [](Prs3d_PlaneAspect &self, Standard_OStream & a0) -> void { return self.DumpJson(a0); });
cls_Prs3d_PlaneAspect.def("DumpJson", (void (Prs3d_PlaneAspect::*)(Standard_OStream &, const Standard_Integer) const) &Prs3d_PlaneAspect::DumpJson, "Dumps the content of me into the stream", py::arg("theOStream"), py::arg("theDepth"));

// CLASS: PRS3D_PRESENTATIONSHADOW
py::class_<Prs3d_PresentationShadow, opencascade::handle<Prs3d_PresentationShadow>, Graphic3d_Structure> cls_Prs3d_PresentationShadow(mod, "Prs3d_PresentationShadow", "Defines a 'shadow' of existing presentation object with custom aspects.");

// Constructors
cls_Prs3d_PresentationShadow.def(py::init<const opencascade::handle<Graphic3d_StructureManager> &, const opencascade::handle<Graphic3d_Structure> &>(), py::arg("theViewer"), py::arg("thePrs"));

// Methods
cls_Prs3d_PresentationShadow.def_static("get_type_name_", (const char * (*)()) &Prs3d_PresentationShadow::get_type_name, "None");
cls_Prs3d_PresentationShadow.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_PresentationShadow::get_type_descriptor, "None");
cls_Prs3d_PresentationShadow.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_PresentationShadow::*)() const) &Prs3d_PresentationShadow::DynamicType, "None");
cls_Prs3d_PresentationShadow.def("ParentId", (Standard_Integer (Prs3d_PresentationShadow::*)() const) &Prs3d_PresentationShadow::ParentId, "Returns the id of the parent presentation");
cls_Prs3d_PresentationShadow.def("ParentAffinity", (const opencascade::handle<Graphic3d_ViewAffinity> & (Prs3d_PresentationShadow::*)() const) &Prs3d_PresentationShadow::ParentAffinity, "Returns view affinity of the parent presentation");
cls_Prs3d_PresentationShadow.def("CalculateBoundBox", (void (Prs3d_PresentationShadow::*)()) &Prs3d_PresentationShadow::CalculateBoundBox, "Do nothing - axis-aligned bounding box should be initialized from parent structure.");

// CLASS: PRS3D_SHAPETOOL
py::class_<Prs3d_ShapeTool> cls_Prs3d_ShapeTool(mod, "Prs3d_ShapeTool", "describes the behaviour requested for a wireframe shape presentation.");

// Constructors
cls_Prs3d_ShapeTool.def(py::init<const TopoDS_Shape &>(), py::arg("theShape"));
cls_Prs3d_ShapeTool.def(py::init<const TopoDS_Shape &, const Standard_Boolean>(), py::arg("theShape"), py::arg("theAllVertices"));

// Methods
// cls_Prs3d_ShapeTool.def_static("operator new_", (void * (*)(size_t)) &Prs3d_ShapeTool::operator new, "None", py::arg("theSize"));
// cls_Prs3d_ShapeTool.def_static("operator delete_", (void (*)(void *)) &Prs3d_ShapeTool::operator delete, "None", py::arg("theAddress"));
// cls_Prs3d_ShapeTool.def_static("operator new[]_", (void * (*)(size_t)) &Prs3d_ShapeTool::operator new[], "None", py::arg("theSize"));
// cls_Prs3d_ShapeTool.def_static("operator delete[]_", (void (*)(void *)) &Prs3d_ShapeTool::operator delete[], "None", py::arg("theAddress"));
// cls_Prs3d_ShapeTool.def_static("operator new_", (void * (*)(size_t, void *)) &Prs3d_ShapeTool::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Prs3d_ShapeTool.def_static("operator delete_", (void (*)(void *, void *)) &Prs3d_ShapeTool::operator delete, "None", py::arg(""), py::arg(""));
cls_Prs3d_ShapeTool.def("InitFace", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::InitFace, "None");
cls_Prs3d_ShapeTool.def("MoreFace", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::MoreFace, "None");
cls_Prs3d_ShapeTool.def("NextFace", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::NextFace, "None");
cls_Prs3d_ShapeTool.def("GetFace", (const TopoDS_Face & (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::GetFace, "None");
cls_Prs3d_ShapeTool.def("FaceBound", (Bnd_Box (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::FaceBound, "None");
cls_Prs3d_ShapeTool.def("IsPlanarFace", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::IsPlanarFace, "None");
cls_Prs3d_ShapeTool.def("InitCurve", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::InitCurve, "None");
cls_Prs3d_ShapeTool.def("MoreCurve", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::MoreCurve, "None");
cls_Prs3d_ShapeTool.def("NextCurve", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::NextCurve, "None");
cls_Prs3d_ShapeTool.def("GetCurve", (const TopoDS_Edge & (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::GetCurve, "None");
cls_Prs3d_ShapeTool.def("CurveBound", (Bnd_Box (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::CurveBound, "None");
cls_Prs3d_ShapeTool.def("Neighbours", (Standard_Integer (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::Neighbours, "None");
cls_Prs3d_ShapeTool.def("FacesOfEdge", (opencascade::handle<TopTools_HSequenceOfShape> (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::FacesOfEdge, "None");
cls_Prs3d_ShapeTool.def("InitVertex", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::InitVertex, "None");
cls_Prs3d_ShapeTool.def("MoreVertex", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::MoreVertex, "None");
cls_Prs3d_ShapeTool.def("NextVertex", (void (Prs3d_ShapeTool::*)()) &Prs3d_ShapeTool::NextVertex, "None");
cls_Prs3d_ShapeTool.def("GetVertex", (const TopoDS_Vertex & (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::GetVertex, "None");
cls_Prs3d_ShapeTool.def("HasSurface", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::HasSurface, "None");
cls_Prs3d_ShapeTool.def("CurrentTriangulation", (opencascade::handle<Poly_Triangulation> (Prs3d_ShapeTool::*)(TopLoc_Location &) const) &Prs3d_ShapeTool::CurrentTriangulation, "None", py::arg("l"));
cls_Prs3d_ShapeTool.def("HasCurve", (Standard_Boolean (Prs3d_ShapeTool::*)() const) &Prs3d_ShapeTool::HasCurve, "None");
cls_Prs3d_ShapeTool.def("PolygonOnTriangulation", (void (Prs3d_ShapeTool::*)(opencascade::handle<Poly_PolygonOnTriangulation> &, opencascade::handle<Poly_Triangulation> &, TopLoc_Location &) const) &Prs3d_ShapeTool::PolygonOnTriangulation, "None", py::arg("Indices"), py::arg("T"), py::arg("l"));
cls_Prs3d_ShapeTool.def("Polygon3D", (opencascade::handle<Poly_Polygon3D> (Prs3d_ShapeTool::*)(TopLoc_Location &) const) &Prs3d_ShapeTool::Polygon3D, "None", py::arg("l"));
cls_Prs3d_ShapeTool.def_static("IsPlanarFace_", (Standard_Boolean (*)(const TopoDS_Face &)) &Prs3d_ShapeTool::IsPlanarFace, "None", py::arg("theFace"));

// CLASS: PRS3D_TEXT
py::class_<Prs3d_Text, Prs3d_Root> cls_Prs3d_Text(mod, "Prs3d_Text", "A framework to define the display of texts.");

// Constructors
cls_Prs3d_Text.def(py::init<>());

// Methods
// cls_Prs3d_Text.def_static("operator new_", (void * (*)(size_t)) &Prs3d_Text::operator new, "None", py::arg("theSize"));
// cls_Prs3d_Text.def_static("operator delete_", (void (*)(void *)) &Prs3d_Text::operator delete, "None", py::arg("theAddress"));
// cls_Prs3d_Text.def_static("operator new[]_", (void * (*)(size_t)) &Prs3d_Text::operator new[], "None", py::arg("theSize"));
// cls_Prs3d_Text.def_static("operator delete[]_", (void (*)(void *)) &Prs3d_Text::operator delete[], "None", py::arg("theAddress"));
// cls_Prs3d_Text.def_static("operator new_", (void * (*)(size_t, void *)) &Prs3d_Text::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Prs3d_Text.def_static("operator delete_", (void (*)(void *, void *)) &Prs3d_Text::operator delete, "None", py::arg(""), py::arg(""));
cls_Prs3d_Text.def_static("Draw_", (void (*)(const opencascade::handle<Graphic3d_Group> &, const opencascade::handle<Prs3d_TextAspect> &, const TCollection_ExtendedString &, const gp_Pnt &)) &Prs3d_Text::Draw, "Defines the display of the text.", py::arg("theGroup"), py::arg("theAspect"), py::arg("theText"), py::arg("theAttachmentPoint"));
cls_Prs3d_Text.def_static("Draw_", [](const opencascade::handle<Graphic3d_Group> & a0, const opencascade::handle<Prs3d_TextAspect> & a1, const TCollection_ExtendedString & a2, const gp_Ax2 & a3) -> void { return Prs3d_Text::Draw(a0, a1, a2, a3); });
cls_Prs3d_Text.def_static("Draw_", (void (*)(const opencascade::handle<Graphic3d_Group> &, const opencascade::handle<Prs3d_TextAspect> &, const TCollection_ExtendedString &, const gp_Ax2 &, const Standard_Boolean)) &Prs3d_Text::Draw, "Draws the text label.", py::arg("theGroup"), py::arg("theAspect"), py::arg("theText"), py::arg("theOrientation"), py::arg("theHasOwnAnchor"));
cls_Prs3d_Text.def_static("Draw_", (void (*)(const opencascade::handle<Prs3d_Presentation> &, const opencascade::handle<Prs3d_Drawer> &, const TCollection_ExtendedString &, const gp_Pnt &)) &Prs3d_Text::Draw, "Alias to another method Draw() for backward compatibility.", py::arg("thePrs"), py::arg("theDrawer"), py::arg("theText"), py::arg("theAttachmentPoint"));
cls_Prs3d_Text.def_static("Draw_", [](const opencascade::handle<Prs3d_Presentation> & a0, const opencascade::handle<Prs3d_TextAspect> & a1, const TCollection_ExtendedString & a2, const gp_Ax2 & a3) -> void { return Prs3d_Text::Draw(a0, a1, a2, a3); });
cls_Prs3d_Text.def_static("Draw_", (void (*)(const opencascade::handle<Prs3d_Presentation> &, const opencascade::handle<Prs3d_TextAspect> &, const TCollection_ExtendedString &, const gp_Ax2 &, const Standard_Boolean)) &Prs3d_Text::Draw, "Alias to another method Draw() for backward compatibility.", py::arg("thePrs"), py::arg("theAspect"), py::arg("theText"), py::arg("theOrientation"), py::arg("theHasOwnAnchor"));
cls_Prs3d_Text.def_static("Draw_", (void (*)(const opencascade::handle<Prs3d_Presentation> &, const opencascade::handle<Prs3d_TextAspect> &, const TCollection_ExtendedString &, const gp_Pnt &)) &Prs3d_Text::Draw, "Alias to another method Draw() for backward compatibility.", py::arg("thePrs"), py::arg("theAspect"), py::arg("theText"), py::arg("theAttachmentPoint"));

// CLASS: PRS3D_TOOLQUADRIC
py::class_<Prs3d_ToolQuadric> cls_Prs3d_ToolQuadric(mod, "Prs3d_ToolQuadric", "Base class to build 3D surfaces presentation of quadric surfaces.");

// Methods
// cls_Prs3d_ToolQuadric.def_static("operator new_", (void * (*)(size_t)) &Prs3d_ToolQuadric::operator new, "None", py::arg("theSize"));
// cls_Prs3d_ToolQuadric.def_static("operator delete_", (void (*)(void *)) &Prs3d_ToolQuadric::operator delete, "None", py::arg("theAddress"));
// cls_Prs3d_ToolQuadric.def_static("operator new[]_", (void * (*)(size_t)) &Prs3d_ToolQuadric::operator new[], "None", py::arg("theSize"));
// cls_Prs3d_ToolQuadric.def_static("operator delete[]_", (void (*)(void *)) &Prs3d_ToolQuadric::operator delete[], "None", py::arg("theAddress"));
// cls_Prs3d_ToolQuadric.def_static("operator new_", (void * (*)(size_t, void *)) &Prs3d_ToolQuadric::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Prs3d_ToolQuadric.def_static("operator delete_", (void (*)(void *, void *)) &Prs3d_ToolQuadric::operator delete, "None", py::arg(""), py::arg(""));
cls_Prs3d_ToolQuadric.def("FillArray", (void (Prs3d_ToolQuadric::*)(opencascade::handle<Graphic3d_ArrayOfTriangles> &, const gp_Trsf &)) &Prs3d_ToolQuadric::FillArray, "Generate primitives for 3D quadric surface and fill the given array. Optional transformation is applied.", py::arg("theArray"), py::arg("theTrsf"));
cls_Prs3d_ToolQuadric.def("FillArray", (void (Prs3d_ToolQuadric::*)(opencascade::handle<Graphic3d_ArrayOfTriangles> &, opencascade::handle<Poly_Triangulation> &, const gp_Trsf &)) &Prs3d_ToolQuadric::FillArray, "Generate primitives for 3D quadric surface presentation and fill the given array and poly triangulation structure. Optional transformation is applied.", py::arg("theArray"), py::arg("theTriangulation"), py::arg("theTrsf"));
cls_Prs3d_ToolQuadric.def_static("TrianglesNb_", (Standard_Integer (*)(const Standard_Integer, const Standard_Integer)) &Prs3d_ToolQuadric::TrianglesNb, "Number of triangles for presentation with the given params.", py::arg("theSlicesNb"), py::arg("theStacksNb"));

// CLASS: PRS3D_TOOLCYLINDER
py::class_<Prs3d_ToolCylinder, Prs3d_ToolQuadric> cls_Prs3d_ToolCylinder(mod, "Prs3d_ToolCylinder", "Standard presentation algorithm that outputs graphical primitives for cylindrical surface.");

// Constructors
cls_Prs3d_ToolCylinder.def(py::init<const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer>(), py::arg("theBottomRad"), py::arg("theTopRad"), py::arg("theHeight"), py::arg("theNbSlices"), py::arg("theNbStacks"));

// Methods
cls_Prs3d_ToolCylinder.def_static("Create_", (opencascade::handle<Graphic3d_ArrayOfTriangles> (*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const gp_Trsf &)) &Prs3d_ToolCylinder::Create, "Generate primitives for 3D quadric surface and return a filled array.", py::arg("theBottomRad"), py::arg("theTopRad"), py::arg("theHeight"), py::arg("theNbSlices"), py::arg("theNbStacks"), py::arg("theTrsf"));

// CLASS: PRS3D_TOOLDISK
py::class_<Prs3d_ToolDisk, Prs3d_ToolQuadric> cls_Prs3d_ToolDisk(mod, "Prs3d_ToolDisk", "Standard presentation algorithm that outputs graphical primitives for disk surface.");

// Constructors
cls_Prs3d_ToolDisk.def(py::init<const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer>(), py::arg("theInnerRadius"), py::arg("theOuterRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"));

// Methods
cls_Prs3d_ToolDisk.def_static("Create_", (opencascade::handle<Graphic3d_ArrayOfTriangles> (*)(const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const gp_Trsf &)) &Prs3d_ToolDisk::Create, "Generate primitives for 3D quadric surface and return a filled array.", py::arg("theInnerRadius"), py::arg("theOuterRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"), py::arg("theTrsf"));
cls_Prs3d_ToolDisk.def("SetAngleRange", (void (Prs3d_ToolDisk::*)(Standard_Real, Standard_Real)) &Prs3d_ToolDisk::SetAngleRange, "Set angle range in radians [0, 2*PI] by default.", py::arg("theStartAngle"), py::arg("theEndAngle"));

// CLASS: PRS3D_TOOLSECTOR
py::class_<Prs3d_ToolSector, Prs3d_ToolQuadric> cls_Prs3d_ToolSector(mod, "Prs3d_ToolSector", "Standard presentation algorithm that outputs graphical primitives for disk surface.");

// Constructors
cls_Prs3d_ToolSector.def(py::init<const Standard_Real, const Standard_Integer, const Standard_Integer>(), py::arg("theRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"));

// Methods
cls_Prs3d_ToolSector.def_static("Create_", (opencascade::handle<Graphic3d_ArrayOfTriangles> (*)(const Standard_Real, const Standard_Integer, const Standard_Integer, const gp_Trsf &)) &Prs3d_ToolSector::Create, "Generate primitives for 3D quadric surface and return a filled array.", py::arg("theRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"), py::arg("theTrsf"));

// CLASS: PRS3D_TOOLSPHERE
py::class_<Prs3d_ToolSphere, Prs3d_ToolQuadric> cls_Prs3d_ToolSphere(mod, "Prs3d_ToolSphere", "Standard presentation algorithm that outputs graphical primitives for spherical surface.");

// Constructors
cls_Prs3d_ToolSphere.def(py::init<const Standard_Real, const Standard_Integer, const Standard_Integer>(), py::arg("theRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"));

// Methods
cls_Prs3d_ToolSphere.def_static("Create_", (opencascade::handle<Graphic3d_ArrayOfTriangles> (*)(const Standard_Real, const Standard_Integer, const Standard_Integer, const gp_Trsf &)) &Prs3d_ToolSphere::Create, "Generate primitives for 3D quadric surface and return a filled array.", py::arg("theRadius"), py::arg("theNbSlices"), py::arg("theNbStacks"), py::arg("theTrsf"));


}
