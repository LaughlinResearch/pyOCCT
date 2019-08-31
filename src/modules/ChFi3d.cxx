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
#include <ChFi3d_FilletShape.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <GeomAbs_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <Standard_Handle.hxx>
#include <ChFiDS_Spine.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Shape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <Geom_Surface.hxx>
#include <ChFiDS_ErrorStatus.hxx>
#include <TopOpeBRepBuild_HBuilder.hxx>
#include <ChFiDS_SurfData.hxx>
#include <ChFiDS_SequenceOfSurfData.hxx>
#include <Adaptor3d_HSurface.hxx>
#include <Adaptor3d_TopolTool.hxx>
#include <ChFiDS_HElSpine.hxx>
#include <BRepAdaptor_HSurface.hxx>
#include <math_Vector.hxx>
#include <BRepAdaptor_HCurve2d.hxx>
#include <TopAbs_Orientation.hxx>
#include <BRepBlend_Line.hxx>
#include <Blend_Function.hxx>
#include <Blend_FuncInv.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <Blend_SurfRstFunction.hxx>
#include <Blend_SurfPointFuncInv.hxx>
#include <Blend_SurfCurvFuncInv.hxx>
#include <Blend_RstRstFunction.hxx>
#include <Blend_CurvPointFuncInv.hxx>
#include <ChFiDS_Stripe.hxx>
#include <gp_Pnt2d.hxx>
#include <ChFiDS_ListOfStripe.hxx>
#include <TopAbs_State.hxx>
#include <ChFiDS_CommonPoint.hxx>
#include <TopoDS_Face.hxx>
#include <AppBlend_Approx.hxx>
#include <Geom2d_Curve.hxx>
#include <ChFiDS_Map.hxx>
#include <TopOpeBRepDS_HDataStructure.hxx>
#include <ChFiDS_StripeMap.hxx>
#include <ChFiDS_Regularities.hxx>
#include <TopTools_DataMapOfShapeListOfInteger.hxx>
#include <BRepTopAdaptor_TopolTool.hxx>
#include <ChFi3d_Builder.hxx>
#include <ChFiDS_ChamfMethod.hxx>
#include <ChFiDS_SecHArray1.hxx>
#include <ChFi3d_ChBuilder.hxx>
#include <Law_Function.hxx>
#include <gp_XY.hxx>
#include <BlendFunc_SectionShape.hxx>
#include <ChFi3d_FilBuilder.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <ChFi3d_SearchSing.hxx>
#include <ChFi3d.hxx>
#include <math_FunctionWithDerivative.hxx>
#include <Geom_Curve.hxx>

PYBIND11_MODULE(ChFi3d, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.ChFiDS");
py::module::import("OCCT.TopTools");
py::module::import("OCCT.Geom");
py::module::import("OCCT.TopOpeBRepBuild");
py::module::import("OCCT.Adaptor3d");
py::module::import("OCCT.BRepAdaptor");
py::module::import("OCCT.math");
py::module::import("OCCT.TopAbs");
py::module::import("OCCT.BRepBlend");
py::module::import("OCCT.Blend");
py::module::import("OCCT.Adaptor2d");
py::module::import("OCCT.gp");
py::module::import("OCCT.AppBlend");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.TopOpeBRepDS");
py::module::import("OCCT.BRepTopAdaptor");
py::module::import("OCCT.Law");
py::module::import("OCCT.BlendFunc");

// ENUM: CHFI3D_FILLETSHAPE
py::enum_<ChFi3d_FilletShape>(mod, "ChFi3d_FilletShape", "Lists the types of fillet shapes. These include the following: - ChFi3d_Rational (default value), which is the standard NURBS representation of circles, - ChFi3d_QuasiAngular, which is a NURBS representation of circles where the parameters match those of the circle, - ChFi3d_Polynomial, which corresponds to a polynomial approximation of circles. This type facilitates the implementation of the construction algorithm.")
	.value("ChFi3d_Rational", ChFi3d_FilletShape::ChFi3d_Rational)
	.value("ChFi3d_QuasiAngular", ChFi3d_FilletShape::ChFi3d_QuasiAngular)
	.value("ChFi3d_Polynomial", ChFi3d_FilletShape::ChFi3d_Polynomial)
	.export_values();


// CLASS: CHFI3D_BUILDER
py::class_<ChFi3d_Builder> cls_ChFi3d_Builder(mod, "ChFi3d_Builder", "Root class for calculation of surfaces (fillets, chamfers) destined to smooth edges of a gap on a Shape and the reconstruction of the Shape.");

// Methods
// cls_ChFi3d_Builder.def_static("operator new_", (void * (*)(size_t)) &ChFi3d_Builder::operator new, "None", py::arg("theSize"));
// cls_ChFi3d_Builder.def_static("operator delete_", (void (*)(void *)) &ChFi3d_Builder::operator delete, "None", py::arg("theAddress"));
// cls_ChFi3d_Builder.def_static("operator new[]_", (void * (*)(size_t)) &ChFi3d_Builder::operator new[], "None", py::arg("theSize"));
// cls_ChFi3d_Builder.def_static("operator delete[]_", (void (*)(void *)) &ChFi3d_Builder::operator delete[], "None", py::arg("theAddress"));
// cls_ChFi3d_Builder.def_static("operator new_", (void * (*)(size_t, void *)) &ChFi3d_Builder::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ChFi3d_Builder.def_static("operator delete_", (void (*)(void *, void *)) &ChFi3d_Builder::operator delete, "None", py::arg(""), py::arg(""));
cls_ChFi3d_Builder.def("SetParams", (void (ChFi3d_Builder::*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &ChFi3d_Builder::SetParams, "None", py::arg("Tang"), py::arg("Tesp"), py::arg("T2d"), py::arg("TApp3d"), py::arg("TolApp2d"), py::arg("Fleche"));
cls_ChFi3d_Builder.def("SetContinuity", (void (ChFi3d_Builder::*)(const GeomAbs_Shape, const Standard_Real)) &ChFi3d_Builder::SetContinuity, "None", py::arg("InternalContinuity"), py::arg("AngularTolerance"));
cls_ChFi3d_Builder.def("Remove", (void (ChFi3d_Builder::*)(const TopoDS_Edge &)) &ChFi3d_Builder::Remove, "extracts from the list the contour containing edge E.", py::arg("E"));
cls_ChFi3d_Builder.def("Contains", (Standard_Integer (ChFi3d_Builder::*)(const TopoDS_Edge &) const) &ChFi3d_Builder::Contains, "gives the number of the contour containing E or 0 if E does not belong to any contour.", py::arg("E"));
cls_ChFi3d_Builder.def("Contains", [](ChFi3d_Builder &self, const TopoDS_Edge & E, Standard_Integer & IndexInSpine){ Standard_Integer rv = self.Contains(E, IndexInSpine); return std::tuple<Standard_Integer, Standard_Integer &>(rv, IndexInSpine); }, "gives the number of the contour containing E or 0 if E does not belong to any contour. Sets in IndexInSpine the index of E in the contour if it's found", py::arg("E"), py::arg("IndexInSpine"));
cls_ChFi3d_Builder.def("NbElements", (Standard_Integer (ChFi3d_Builder::*)() const) &ChFi3d_Builder::NbElements, "gives the number of disjoint contours on which the fillets are calculated");
cls_ChFi3d_Builder.def("Value", (opencascade::handle<ChFiDS_Spine> (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::Value, "gives the n'th set of edges (contour) if I >NbElements()", py::arg("I"));
cls_ChFi3d_Builder.def("Length", (Standard_Real (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::Length, "returns the length of the contour of index IC.", py::arg("IC"));
cls_ChFi3d_Builder.def("FirstVertex", (TopoDS_Vertex (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::FirstVertex, "returns the First vertex V of the contour of index IC.", py::arg("IC"));
cls_ChFi3d_Builder.def("LastVertex", (TopoDS_Vertex (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::LastVertex, "returns the Last vertex V of the contour of index IC.", py::arg("IC"));
cls_ChFi3d_Builder.def("Abscissa", (Standard_Real (ChFi3d_Builder::*)(const Standard_Integer, const TopoDS_Vertex &) const) &ChFi3d_Builder::Abscissa, "returns the abscissa of the vertex V on the contour of index IC.", py::arg("IC"), py::arg("V"));
cls_ChFi3d_Builder.def("RelativeAbscissa", (Standard_Real (ChFi3d_Builder::*)(const Standard_Integer, const TopoDS_Vertex &) const) &ChFi3d_Builder::RelativeAbscissa, "returns the relative abscissa([0.,1.]) of the vertex V on the contour of index IC.", py::arg("IC"), py::arg("V"));
cls_ChFi3d_Builder.def("ClosedAndTangent", (Standard_Boolean (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::ClosedAndTangent, "returns true if the contour of index IC is closed an tangent.", py::arg("IC"));
cls_ChFi3d_Builder.def("Closed", (Standard_Boolean (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::Closed, "returns true if the contour of index IC is closed", py::arg("IC"));
cls_ChFi3d_Builder.def("Compute", (void (ChFi3d_Builder::*)()) &ChFi3d_Builder::Compute, "general calculation of geometry on all edges, topologic reconstruction.");
cls_ChFi3d_Builder.def("IsDone", (Standard_Boolean (ChFi3d_Builder::*)() const) &ChFi3d_Builder::IsDone, "returns True if the computation is success");
cls_ChFi3d_Builder.def("Shape", (TopoDS_Shape (ChFi3d_Builder::*)() const) &ChFi3d_Builder::Shape, "if (Isdone()) makes the result. if (!Isdone())");
cls_ChFi3d_Builder.def("Generated", (const TopTools_ListOfShape & (ChFi3d_Builder::*)(const TopoDS_Shape &)) &ChFi3d_Builder::Generated, "Advanced function for the history", py::arg("EouV"));
cls_ChFi3d_Builder.def("NbFaultyContours", (Standard_Integer (ChFi3d_Builder::*)() const) &ChFi3d_Builder::NbFaultyContours, "Returns the number of contours on which the calculation has failed.");
cls_ChFi3d_Builder.def("FaultyContour", (Standard_Integer (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::FaultyContour, "Returns the number of I'th contour on which the calculation has failed.", py::arg("I"));
cls_ChFi3d_Builder.def("NbComputedSurfaces", (Standard_Integer (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::NbComputedSurfaces, "Returns the number of surfaces calculated on the contour IC.", py::arg("IC"));
cls_ChFi3d_Builder.def("ComputedSurface", (opencascade::handle<Geom_Surface> (ChFi3d_Builder::*)(const Standard_Integer, const Standard_Integer) const) &ChFi3d_Builder::ComputedSurface, "Returns the IS'th surface calculated on the contour IC.", py::arg("IC"), py::arg("IS"));
cls_ChFi3d_Builder.def("NbFaultyVertices", (Standard_Integer (ChFi3d_Builder::*)() const) &ChFi3d_Builder::NbFaultyVertices, "Returns the number of vertices on which the calculation has failed.");
cls_ChFi3d_Builder.def("FaultyVertex", (TopoDS_Vertex (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::FaultyVertex, "Returns the IV'th vertex on which the calculation has failed.", py::arg("IV"));
cls_ChFi3d_Builder.def("HasResult", (Standard_Boolean (ChFi3d_Builder::*)() const) &ChFi3d_Builder::HasResult, "returns True if a partial result has been calculated");
cls_ChFi3d_Builder.def("BadShape", (TopoDS_Shape (ChFi3d_Builder::*)() const) &ChFi3d_Builder::BadShape, "if (HasResult()) returns partial result if (!HasResult())");
cls_ChFi3d_Builder.def("StripeStatus", (ChFiDS_ErrorStatus (ChFi3d_Builder::*)(const Standard_Integer) const) &ChFi3d_Builder::StripeStatus, "for the stripe IC ,indication on the cause of failure WalkingFailure,TwistedSurface,Error, Ok", py::arg("IC"));
cls_ChFi3d_Builder.def("Reset", (void (ChFi3d_Builder::*)()) &ChFi3d_Builder::Reset, "Reset all results of compute and returns the algorythm in the state of the last acquisition to enable modification of contours or areas.");
cls_ChFi3d_Builder.def("Builder", (opencascade::handle<TopOpeBRepBuild_HBuilder> (ChFi3d_Builder::*)() const) &ChFi3d_Builder::Builder, "Returns the Builder of topologic operations.");
cls_ChFi3d_Builder.def("SplitKPart", [](ChFi3d_Builder &self, const opencascade::handle<ChFiDS_SurfData> & Data, ChFiDS_SequenceOfSurfData & SetData, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Iedge, const opencascade::handle<Adaptor3d_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<Adaptor3d_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, Standard_Boolean & Intf, Standard_Boolean & Intl){ Standard_Boolean rv = self.SplitKPart(Data, SetData, Spine, Iedge, S1, I1, S2, I2, Intf, Intl); return std::tuple<Standard_Boolean, Standard_Boolean &, Standard_Boolean &>(rv, Intf, Intl); }, "Method, implemented in the inheritants, calculates the elements of construction of the surface (fillet or chamfer).", py::arg("Data"), py::arg("SetData"), py::arg("Spine"), py::arg("Iedge"), py::arg("S1"), py::arg("I1"), py::arg("S2"), py::arg("I2"), py::arg("Intf"), py::arg("Intl"));
cls_ChFi3d_Builder.def("PerformTwoCornerbyInter", (Standard_Boolean (ChFi3d_Builder::*)(const Standard_Integer)) &ChFi3d_Builder::PerformTwoCornerbyInter, "None", py::arg("Index"));

// CLASS: CHFI3D_CHBUILDER
py::class_<ChFi3d_ChBuilder, ChFi3d_Builder> cls_ChFi3d_ChBuilder(mod, "ChFi3d_ChBuilder", "construction tool for 3D chamfers on edges (on a solid).");

// Constructors
cls_ChFi3d_ChBuilder.def(py::init<const TopoDS_Shape &>(), py::arg("S"));
cls_ChFi3d_ChBuilder.def(py::init<const TopoDS_Shape &, const Standard_Real>(), py::arg("S"), py::arg("Ta"));

// Methods
// cls_ChFi3d_ChBuilder.def_static("operator new_", (void * (*)(size_t)) &ChFi3d_ChBuilder::operator new, "None", py::arg("theSize"));
// cls_ChFi3d_ChBuilder.def_static("operator delete_", (void (*)(void *)) &ChFi3d_ChBuilder::operator delete, "None", py::arg("theAddress"));
// cls_ChFi3d_ChBuilder.def_static("operator new[]_", (void * (*)(size_t)) &ChFi3d_ChBuilder::operator new[], "None", py::arg("theSize"));
// cls_ChFi3d_ChBuilder.def_static("operator delete[]_", (void (*)(void *)) &ChFi3d_ChBuilder::operator delete[], "None", py::arg("theAddress"));
// cls_ChFi3d_ChBuilder.def_static("operator new_", (void * (*)(size_t, void *)) &ChFi3d_ChBuilder::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ChFi3d_ChBuilder.def_static("operator delete_", (void (*)(void *, void *)) &ChFi3d_ChBuilder::operator delete, "None", py::arg(""), py::arg(""));
cls_ChFi3d_ChBuilder.def("Add", (void (ChFi3d_ChBuilder::*)(const TopoDS_Edge &)) &ChFi3d_ChBuilder::Add, "initializes a contour with the edge <E> as first (the next are found by propagation ). The two distances (parameters of the chamfer) must be set after. if the edge <E> has more than 2 adjacent faces", py::arg("E"));
cls_ChFi3d_ChBuilder.def("Add", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const TopoDS_Edge &, const TopoDS_Face &)) &ChFi3d_ChBuilder::Add, "initializes a new contour with the edge <E> as first (the next are found by propagation ), and the distance <Dis> if the edge <E> has more than 2 adjacent faces", py::arg("Dis"), py::arg("E"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("SetDist", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const Standard_Integer, const TopoDS_Face &)) &ChFi3d_ChBuilder::SetDist, "set the distance <Dis> of the fillet contour of index <IC> in the DS with <Dis> on <F>. if the face <F> is not one of common faces of an edge of the contour <IC>", py::arg("Dis"), py::arg("IC"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("GetDist", [](ChFi3d_ChBuilder &self, const Standard_Integer IC, Standard_Real & Dis){ self.GetDist(IC, Dis); return Dis; }, "gives the distances <Dis> of the fillet contour of index <IC> in the DS", py::arg("IC"), py::arg("Dis"));
cls_ChFi3d_ChBuilder.def("Add", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const Standard_Real, const TopoDS_Edge &, const TopoDS_Face &)) &ChFi3d_ChBuilder::Add, "initializes a new contour with the edge <E> as first (the next are found by propagation ), and the distance <Dis1> and <Dis2> if the edge <E> has more than 2 adjacent faces", py::arg("Dis1"), py::arg("Dis2"), py::arg("E"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("SetDists", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const Standard_Real, const Standard_Integer, const TopoDS_Face &)) &ChFi3d_ChBuilder::SetDists, "set the distances <Dis1> and <Dis2> of the fillet contour of index <IC> in the DS with <Dis1> on <F>. if the face <F> is not one of common faces of an edge of the contour <IC>", py::arg("Dis1"), py::arg("Dis2"), py::arg("IC"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("Dists", [](ChFi3d_ChBuilder &self, const Standard_Integer IC, Standard_Real & Dis1, Standard_Real & Dis2){ self.Dists(IC, Dis1, Dis2); return std::tuple<Standard_Real &, Standard_Real &>(Dis1, Dis2); }, "gives the distances <Dis1> and <Dis2> of the fillet contour of index <IC> in the DS", py::arg("IC"), py::arg("Dis1"), py::arg("Dis2"));
cls_ChFi3d_ChBuilder.def("AddDA", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const Standard_Real, const TopoDS_Edge &, const TopoDS_Face &)) &ChFi3d_ChBuilder::AddDA, "initializes a new contour with the edge <E> as first (the next are found by propagation ), and the distance <Dis1> and <Angle> if the edge <E> has more than 2 adjacent faces", py::arg("Dis"), py::arg("Angle"), py::arg("E"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("SetDistAngle", (void (ChFi3d_ChBuilder::*)(const Standard_Real, const Standard_Real, const Standard_Integer, const TopoDS_Face &)) &ChFi3d_ChBuilder::SetDistAngle, "set the distance <Dis> and <Angle> of the fillet contour of index <IC> in the DS with <Dis> on <F>. if the face <F> is not one of common faces of an edge of the contour <IC>", py::arg("Dis"), py::arg("Angle"), py::arg("IC"), py::arg("F"));
cls_ChFi3d_ChBuilder.def("GetDistAngle", [](ChFi3d_ChBuilder &self, const Standard_Integer IC, Standard_Real & Dis, Standard_Real & Angle, Standard_Boolean & DisOnFace1){ self.GetDistAngle(IC, Dis, Angle, DisOnFace1); return std::tuple<Standard_Real &, Standard_Real &, Standard_Boolean &>(Dis, Angle, DisOnFace1); }, "gives the distances <Dis> and <Angle> of the fillet contour of index <IC> in the DS", py::arg("IC"), py::arg("Dis"), py::arg("Angle"), py::arg("DisOnFace1"));
cls_ChFi3d_ChBuilder.def("IsChamfer", (ChFiDS_ChamfMethod (ChFi3d_ChBuilder::*)(const Standard_Integer) const) &ChFi3d_ChBuilder::IsChamfer, "renvoi la methode des chanfreins utilisee", py::arg("IC"));
cls_ChFi3d_ChBuilder.def("ResetContour", (void (ChFi3d_ChBuilder::*)(const Standard_Integer)) &ChFi3d_ChBuilder::ResetContour, "Reset tous rayons du contour IC.", py::arg("IC"));
cls_ChFi3d_ChBuilder.def("Simulate", (void (ChFi3d_ChBuilder::*)(const Standard_Integer)) &ChFi3d_ChBuilder::Simulate, "None", py::arg("IC"));
cls_ChFi3d_ChBuilder.def("NbSurf", (Standard_Integer (ChFi3d_ChBuilder::*)(const Standard_Integer) const) &ChFi3d_ChBuilder::NbSurf, "None", py::arg("IC"));
cls_ChFi3d_ChBuilder.def("Sect", (opencascade::handle<ChFiDS_SecHArray1> (ChFi3d_ChBuilder::*)(const Standard_Integer, const Standard_Integer) const) &ChFi3d_ChBuilder::Sect, "None", py::arg("IC"), py::arg("IS"));
cls_ChFi3d_ChBuilder.def("SimulSurf", [](ChFi3d_ChBuilder &self, opencascade::handle<ChFiDS_SurfData> & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<BRepAdaptor_HCurve2d> & PC1, const opencascade::handle<BRepAdaptor_HSurface> & Sref1, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref1, Standard_Boolean & Decroch1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const TopAbs_Orientation Or2, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP, const Standard_Boolean RecS, const Standard_Boolean RecRst, const math_Vector & Soldep){ self.SimulSurf(Data, Guide, Spine, Choix, S1, I1, PC1, Sref1, PCref1, Decroch1, S2, I2, Or2, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP, RecS, RecRst, Soldep); return std::tuple<Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch1, First, Last); }, "None", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("PC1"), py::arg("Sref1"), py::arg("PCref1"), py::arg("Decroch1"), py::arg("S2"), py::arg("I2"), py::arg("Or2"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP"), py::arg("RecS"), py::arg("RecRst"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("SimulSurf", [](ChFi3d_ChBuilder &self, opencascade::handle<ChFiDS_SurfData> & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const TopAbs_Orientation Or1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const opencascade::handle<BRepAdaptor_HCurve2d> & PC2, const opencascade::handle<BRepAdaptor_HSurface> & Sref2, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref2, Standard_Boolean & Decroch2, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP, const Standard_Boolean RecS, const Standard_Boolean RecRst, const math_Vector & Soldep){ self.SimulSurf(Data, Guide, Spine, Choix, S1, I1, Or1, S2, I2, PC2, Sref2, PCref2, Decroch2, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP, RecS, RecRst, Soldep); return std::tuple<Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch2, First, Last); }, "None", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("Or1"), py::arg("S2"), py::arg("I2"), py::arg("PC2"), py::arg("Sref2"), py::arg("PCref2"), py::arg("Decroch2"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP"), py::arg("RecS"), py::arg("RecRst"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("SimulSurf", [](ChFi3d_ChBuilder &self, opencascade::handle<ChFiDS_SurfData> & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<BRepAdaptor_HCurve2d> & PC1, const opencascade::handle<BRepAdaptor_HSurface> & Sref1, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref1, Standard_Boolean & Decroch1, const TopAbs_Orientation Or1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const opencascade::handle<BRepAdaptor_HCurve2d> & PC2, const opencascade::handle<BRepAdaptor_HSurface> & Sref2, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref2, Standard_Boolean & Decroch2, const TopAbs_Orientation Or2, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP1, const Standard_Boolean RecRst1, const Standard_Boolean RecP2, const Standard_Boolean RecRst2, const math_Vector & Soldep){ self.SimulSurf(Data, Guide, Spine, Choix, S1, I1, PC1, Sref1, PCref1, Decroch1, Or1, S2, I2, PC2, Sref2, PCref2, Decroch2, Or2, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP1, RecRst1, RecP2, RecRst2, Soldep); return std::tuple<Standard_Boolean &, Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch1, Decroch2, First, Last); }, "None", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("PC1"), py::arg("Sref1"), py::arg("PCref1"), py::arg("Decroch1"), py::arg("Or1"), py::arg("S2"), py::arg("I2"), py::arg("PC2"), py::arg("Sref2"), py::arg("PCref2"), py::arg("Decroch2"), py::arg("Or2"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP1"), py::arg("RecRst1"), py::arg("RecP2"), py::arg("RecRst2"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("PerformSurf", [](ChFi3d_ChBuilder &self, ChFiDS_SequenceOfSurfData & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const Standard_Real MaxStep, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecOnS1, const Standard_Boolean RecOnS2, const math_Vector & Soldep, Standard_Integer & Intf, Standard_Integer & Intl){ Standard_Boolean rv = self.PerformSurf(Data, Guide, Spine, Choix, S1, I1, S2, I2, MaxStep, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecOnS1, RecOnS2, Soldep, Intf, Intl); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &, Standard_Integer &, Standard_Integer &>(rv, First, Last, Intf, Intl); }, "Methode, implemented in inheritants, calculates the elements of construction of the surface (fillet or chamfer).", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("S2"), py::arg("I2"), py::arg("MaxStep"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecOnS1"), py::arg("RecOnS2"), py::arg("Soldep"), py::arg("Intf"), py::arg("Intl"));
cls_ChFi3d_ChBuilder.def("PerformSurf", [](ChFi3d_ChBuilder &self, ChFiDS_SequenceOfSurfData & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<BRepAdaptor_HCurve2d> & PC1, const opencascade::handle<BRepAdaptor_HSurface> & Sref1, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref1, Standard_Boolean & Decroch1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const TopAbs_Orientation Or2, const Standard_Real MaxStep, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP, const Standard_Boolean RecS, const Standard_Boolean RecRst, const math_Vector & Soldep){ self.PerformSurf(Data, Guide, Spine, Choix, S1, I1, PC1, Sref1, PCref1, Decroch1, S2, I2, Or2, MaxStep, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP, RecS, RecRst, Soldep); return std::tuple<Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch1, First, Last); }, "Method, implemented in the inheritants, calculates the elements of construction of the surface (fillet or chamfer) contact edge/face.", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("PC1"), py::arg("Sref1"), py::arg("PCref1"), py::arg("Decroch1"), py::arg("S2"), py::arg("I2"), py::arg("Or2"), py::arg("MaxStep"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP"), py::arg("RecS"), py::arg("RecRst"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("PerformSurf", [](ChFi3d_ChBuilder &self, ChFiDS_SequenceOfSurfData & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const TopAbs_Orientation Or1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const opencascade::handle<BRepAdaptor_HCurve2d> & PC2, const opencascade::handle<BRepAdaptor_HSurface> & Sref2, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref2, Standard_Boolean & Decroch2, const Standard_Real MaxStep, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP, const Standard_Boolean RecS, const Standard_Boolean RecRst, const math_Vector & Soldep){ self.PerformSurf(Data, Guide, Spine, Choix, S1, I1, Or1, S2, I2, PC2, Sref2, PCref2, Decroch2, MaxStep, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP, RecS, RecRst, Soldep); return std::tuple<Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch2, First, Last); }, "Method, implemented in inheritants, calculates the elements of construction of the surface (fillet or chamfer) contact edge/face.", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("Or1"), py::arg("S2"), py::arg("I2"), py::arg("PC2"), py::arg("Sref2"), py::arg("PCref2"), py::arg("Decroch2"), py::arg("MaxStep"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP"), py::arg("RecS"), py::arg("RecRst"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("PerformSurf", [](ChFi3d_ChBuilder &self, ChFiDS_SequenceOfSurfData & Data, const opencascade::handle<ChFiDS_HElSpine> & Guide, const opencascade::handle<ChFiDS_Spine> & Spine, const Standard_Integer Choix, const opencascade::handle<BRepAdaptor_HSurface> & S1, const opencascade::handle<Adaptor3d_TopolTool> & I1, const opencascade::handle<BRepAdaptor_HCurve2d> & PC1, const opencascade::handle<BRepAdaptor_HSurface> & Sref1, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref1, Standard_Boolean & Decroch1, const TopAbs_Orientation Or1, const opencascade::handle<BRepAdaptor_HSurface> & S2, const opencascade::handle<Adaptor3d_TopolTool> & I2, const opencascade::handle<BRepAdaptor_HCurve2d> & PC2, const opencascade::handle<BRepAdaptor_HSurface> & Sref2, const opencascade::handle<BRepAdaptor_HCurve2d> & PCref2, Standard_Boolean & Decroch2, const TopAbs_Orientation Or2, const Standard_Real MaxStep, const Standard_Real Fleche, const Standard_Real TolGuide, Standard_Real & First, Standard_Real & Last, const Standard_Boolean Inside, const Standard_Boolean Appro, const Standard_Boolean Forward, const Standard_Boolean RecP1, const Standard_Boolean RecRst1, const Standard_Boolean RecP2, const Standard_Boolean RecRst2, const math_Vector & Soldep){ self.PerformSurf(Data, Guide, Spine, Choix, S1, I1, PC1, Sref1, PCref1, Decroch1, Or1, S2, I2, PC2, Sref2, PCref2, Decroch2, Or2, MaxStep, Fleche, TolGuide, First, Last, Inside, Appro, Forward, RecP1, RecRst1, RecP2, RecRst2, Soldep); return std::tuple<Standard_Boolean &, Standard_Boolean &, Standard_Real &, Standard_Real &>(Decroch1, Decroch2, First, Last); }, "Method, implemented in inheritants, calculates the elements of construction of the surface (fillet or chamfer) contact edge/edge.", py::arg("Data"), py::arg("Guide"), py::arg("Spine"), py::arg("Choix"), py::arg("S1"), py::arg("I1"), py::arg("PC1"), py::arg("Sref1"), py::arg("PCref1"), py::arg("Decroch1"), py::arg("Or1"), py::arg("S2"), py::arg("I2"), py::arg("PC2"), py::arg("Sref2"), py::arg("PCref2"), py::arg("Decroch2"), py::arg("Or2"), py::arg("MaxStep"), py::arg("Fleche"), py::arg("TolGuide"), py::arg("First"), py::arg("Last"), py::arg("Inside"), py::arg("Appro"), py::arg("Forward"), py::arg("RecP1"), py::arg("RecRst1"), py::arg("RecP2"), py::arg("RecRst2"), py::arg("Soldep"));
cls_ChFi3d_ChBuilder.def("FindChoiceDistAngle", (Standard_Integer (ChFi3d_ChBuilder::*)(const Standard_Integer, const Standard_Boolean) const) &ChFi3d_ChBuilder::FindChoiceDistAngle, "None", py::arg("Choice"), py::arg("DisOnF1"));

// CLASS: CHFI3D_FILBUILDER
py::class_<ChFi3d_FilBuilder, ChFi3d_Builder> cls_ChFi3d_FilBuilder(mod, "ChFi3d_FilBuilder", "Tool of construction of fillets 3d on edges (on a solid).");

// Constructors
cls_ChFi3d_FilBuilder.def(py::init<const TopoDS_Shape &>(), py::arg("S"));
cls_ChFi3d_FilBuilder.def(py::init<const TopoDS_Shape &, const ChFi3d_FilletShape>(), py::arg("S"), py::arg("FShape"));
cls_ChFi3d_FilBuilder.def(py::init<const TopoDS_Shape &, const ChFi3d_FilletShape, const Standard_Real>(), py::arg("S"), py::arg("FShape"), py::arg("Ta"));

// Methods
// cls_ChFi3d_FilBuilder.def_static("operator new_", (void * (*)(size_t)) &ChFi3d_FilBuilder::operator new, "None", py::arg("theSize"));
// cls_ChFi3d_FilBuilder.def_static("operator delete_", (void (*)(void *)) &ChFi3d_FilBuilder::operator delete, "None", py::arg("theAddress"));
// cls_ChFi3d_FilBuilder.def_static("operator new[]_", (void * (*)(size_t)) &ChFi3d_FilBuilder::operator new[], "None", py::arg("theSize"));
// cls_ChFi3d_FilBuilder.def_static("operator delete[]_", (void (*)(void *)) &ChFi3d_FilBuilder::operator delete[], "None", py::arg("theAddress"));
// cls_ChFi3d_FilBuilder.def_static("operator new_", (void * (*)(size_t, void *)) &ChFi3d_FilBuilder::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ChFi3d_FilBuilder.def_static("operator delete_", (void (*)(void *, void *)) &ChFi3d_FilBuilder::operator delete, "None", py::arg(""), py::arg(""));
cls_ChFi3d_FilBuilder.def("SetFilletShape", (void (ChFi3d_FilBuilder::*)(const ChFi3d_FilletShape)) &ChFi3d_FilBuilder::SetFilletShape, "Sets the type of fillet surface.", py::arg("FShape"));
cls_ChFi3d_FilBuilder.def("GetFilletShape", (ChFi3d_FilletShape (ChFi3d_FilBuilder::*)() const) &ChFi3d_FilBuilder::GetFilletShape, "Returns the type of fillet surface.");
cls_ChFi3d_FilBuilder.def("Add", (void (ChFi3d_FilBuilder::*)(const TopoDS_Edge &)) &ChFi3d_FilBuilder::Add, "initialisation of a contour with the first edge (the following are found by propagation). Attention, you need to start with SetRadius.", py::arg("E"));
cls_ChFi3d_FilBuilder.def("Add", (void (ChFi3d_FilBuilder::*)(const Standard_Real, const TopoDS_Edge &)) &ChFi3d_FilBuilder::Add, "initialisation of the constant vector the corresponding 1st edge.", py::arg("Radius"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("SetRadius", (void (ChFi3d_FilBuilder::*)(const opencascade::handle<Law_Function> &, const Standard_Integer, const Standard_Integer)) &ChFi3d_FilBuilder::SetRadius, "Set the radius of the contour of index IC.", py::arg("C"), py::arg("IC"), py::arg("IinC"));
cls_ChFi3d_FilBuilder.def("IsConstant", (Standard_Boolean (ChFi3d_FilBuilder::*)(const Standard_Integer)) &ChFi3d_FilBuilder::IsConstant, "Returns true the contour is flaged as edge constant.", py::arg("IC"));
cls_ChFi3d_FilBuilder.def("Radius", (Standard_Real (ChFi3d_FilBuilder::*)(const Standard_Integer)) &ChFi3d_FilBuilder::Radius, "Returns the vector if the contour is flagged as edge constant.", py::arg("IC"));
cls_ChFi3d_FilBuilder.def("ResetContour", (void (ChFi3d_FilBuilder::*)(const Standard_Integer)) &ChFi3d_FilBuilder::ResetContour, "Reset all vectors of contour IC.", py::arg("IC"));
cls_ChFi3d_FilBuilder.def("SetRadius", (void (ChFi3d_FilBuilder::*)(const Standard_Real, const Standard_Integer, const TopoDS_Edge &)) &ChFi3d_FilBuilder::SetRadius, "Set a constant on edge E of the contour of index IC. Since then E is flagged as constant.", py::arg("Radius"), py::arg("IC"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("UnSet", (void (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Edge &)) &ChFi3d_FilBuilder::UnSet, "Extracts the flag constant and the vector of edge E.", py::arg("IC"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("SetRadius", (void (ChFi3d_FilBuilder::*)(const Standard_Real, const Standard_Integer, const TopoDS_Vertex &)) &ChFi3d_FilBuilder::SetRadius, "Set a vector on vertex V of the contour of index IC.", py::arg("Radius"), py::arg("IC"), py::arg("V"));
cls_ChFi3d_FilBuilder.def("UnSet", (void (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Vertex &)) &ChFi3d_FilBuilder::UnSet, "Extracts the vector of the vertex V.", py::arg("IC"), py::arg("V"));
cls_ChFi3d_FilBuilder.def("SetRadius", (void (ChFi3d_FilBuilder::*)(const gp_XY &, const Standard_Integer, const Standard_Integer)) &ChFi3d_FilBuilder::SetRadius, "Set a vertex on the point of parametre U in the edge IinC of the contour of index IC", py::arg("UandR"), py::arg("IC"), py::arg("IinC"));
cls_ChFi3d_FilBuilder.def("IsConstant", (Standard_Boolean (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Edge &)) &ChFi3d_FilBuilder::IsConstant, "Returns true E is flagged as edge constant.", py::arg("IC"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("Radius", (Standard_Real (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Edge &)) &ChFi3d_FilBuilder::Radius, "Returns the vector if E is flagged as edge constant.", py::arg("IC"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("GetBounds", [](ChFi3d_FilBuilder &self, const Standard_Integer IC, const TopoDS_Edge & E, Standard_Real & First, Standard_Real & Last){ Standard_Boolean rv = self.GetBounds(IC, E, First, Last); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, First, Last); }, "Returns in First and Last les extremities of the part of variable vector framing E, returns False if E is flagged as edge constant.", py::arg("IC"), py::arg("E"), py::arg("First"), py::arg("Last"));
cls_ChFi3d_FilBuilder.def("GetLaw", (opencascade::handle<Law_Function> (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Edge &)) &ChFi3d_FilBuilder::GetLaw, "Returns the rule of elementary evolution of the part to variable vector framing E, returns a rule zero if E is flagged as edge constant.", py::arg("IC"), py::arg("E"));
cls_ChFi3d_FilBuilder.def("SetLaw", (void (ChFi3d_FilBuilder::*)(const Standard_Integer, const TopoDS_Edge &, const opencascade::handle<Law_Function> &)) &ChFi3d_FilBuilder::SetLaw, "Sets the rule of elementary evolution of the part to variable vector framing E.", py::arg("IC"), py::arg("E"), py::arg("L"));
cls_ChFi3d_FilBuilder.def("Simulate", (void (ChFi3d_FilBuilder::*)(const Standard_Integer)) &ChFi3d_FilBuilder::Simulate, "None", py::arg("IC"));
cls_ChFi3d_FilBuilder.def("NbSurf", (Standard_Integer (ChFi3d_FilBuilder::*)(const Standard_Integer) const) &ChFi3d_FilBuilder::NbSurf, "None", py::arg("IC"));
cls_ChFi3d_FilBuilder.def("Sect", (opencascade::handle<ChFiDS_SecHArray1> (ChFi3d_FilBuilder::*)(const Standard_Integer, const Standard_Integer) const) &ChFi3d_FilBuilder::Sect, "None", py::arg("IC"), py::arg("IS"));

// CLASS: CHFI3D
py::class_<ChFi3d> cls_ChFi3d(mod, "ChFi3d", "creation of spatial fillets on a solid.");

// Methods
// cls_ChFi3d.def_static("operator new_", (void * (*)(size_t)) &ChFi3d::operator new, "None", py::arg("theSize"));
// cls_ChFi3d.def_static("operator delete_", (void (*)(void *)) &ChFi3d::operator delete, "None", py::arg("theAddress"));
// cls_ChFi3d.def_static("operator new[]_", (void * (*)(size_t)) &ChFi3d::operator new[], "None", py::arg("theSize"));
// cls_ChFi3d.def_static("operator delete[]_", (void (*)(void *)) &ChFi3d::operator delete[], "None", py::arg("theAddress"));
// cls_ChFi3d.def_static("operator new_", (void * (*)(size_t, void *)) &ChFi3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ChFi3d.def_static("operator delete_", (void (*)(void *, void *)) &ChFi3d::operator delete, "None", py::arg(""), py::arg(""));
cls_ChFi3d.def_static("ConcaveSide_", (Standard_Integer (*)(const BRepAdaptor_Surface &, const BRepAdaptor_Surface &, const TopoDS_Edge &, TopAbs_Orientation &, TopAbs_Orientation &)) &ChFi3d::ConcaveSide, "Returns Reversed in Or1 and(or) Or2 if the concave edge defined by the interior of faces F1 and F2, in the neighbourhood of their boundary E is of the edge opposite to the normal of their surface support. The orientation of faces is not taken into consideration in the calculation. The function returns 0 if the calculation fails (tangence), if not, it returns the number of choice of the fillet or chamfer corresponding to the orientations calculated and to the tangent to the guide line read in E.", py::arg("S1"), py::arg("S2"), py::arg("E"), py::arg("Or1"), py::arg("Or2"));
cls_ChFi3d.def_static("NextSide_", (Standard_Integer (*)(TopAbs_Orientation &, TopAbs_Orientation &, const TopAbs_Orientation, const TopAbs_Orientation, const Standard_Integer)) &ChFi3d::NextSide, "Same as ConcaveSide, but the orientations are logically deduced from the result of the call of ConcaveSide on the first pair of faces of the fillet or chamnfer.", py::arg("Or1"), py::arg("Or2"), py::arg("OrSave1"), py::arg("OrSave2"), py::arg("ChoixSauv"));
cls_ChFi3d.def_static("NextSide_", (void (*)(TopAbs_Orientation &, const TopAbs_Orientation, const TopAbs_Orientation)) &ChFi3d::NextSide, "Same as the other NextSide, but the calculation is done on an edge only.", py::arg("Or"), py::arg("OrSave"), py::arg("OrFace"));
cls_ChFi3d.def_static("SameSide_", (Standard_Boolean (*)(const TopAbs_Orientation, const TopAbs_Orientation, const TopAbs_Orientation, const TopAbs_Orientation, const TopAbs_Orientation)) &ChFi3d::SameSide, "Enables to determine while processing an angle, if two fillets or chamfers constituting a face have identic or opposed concave edges.", py::arg("Or"), py::arg("OrSave1"), py::arg("OrSave2"), py::arg("OrFace1"), py::arg("OrFace2"));

// CLASS: CHFI3D_SEARCHSING
py::class_<ChFi3d_SearchSing, math_FunctionWithDerivative> cls_ChFi3d_SearchSing(mod, "ChFi3d_SearchSing", "Searches singularities on fillet. F(t) = (C1(t) - C2(t)).(C1'(t) - C2'(t));");

// Constructors
cls_ChFi3d_SearchSing.def(py::init<const opencascade::handle<Geom_Curve> &, const opencascade::handle<Geom_Curve> &>(), py::arg("C1"), py::arg("C2"));

// Methods
// cls_ChFi3d_SearchSing.def_static("operator new_", (void * (*)(size_t)) &ChFi3d_SearchSing::operator new, "None", py::arg("theSize"));
// cls_ChFi3d_SearchSing.def_static("operator delete_", (void (*)(void *)) &ChFi3d_SearchSing::operator delete, "None", py::arg("theAddress"));
// cls_ChFi3d_SearchSing.def_static("operator new[]_", (void * (*)(size_t)) &ChFi3d_SearchSing::operator new[], "None", py::arg("theSize"));
// cls_ChFi3d_SearchSing.def_static("operator delete[]_", (void (*)(void *)) &ChFi3d_SearchSing::operator delete[], "None", py::arg("theAddress"));
// cls_ChFi3d_SearchSing.def_static("operator new_", (void * (*)(size_t, void *)) &ChFi3d_SearchSing::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ChFi3d_SearchSing.def_static("operator delete_", (void (*)(void *, void *)) &ChFi3d_SearchSing::operator delete, "None", py::arg(""), py::arg(""));
cls_ChFi3d_SearchSing.def("Value", [](ChFi3d_SearchSing &self, const Standard_Real X, Standard_Real & F){ Standard_Boolean rv = self.Value(X, F); return std::tuple<Standard_Boolean, Standard_Real &>(rv, F); }, "computes the value of the function <F> for the variable <X>. returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_ChFi3d_SearchSing.def("Derivative", [](ChFi3d_SearchSing &self, const Standard_Real X, Standard_Real & D){ Standard_Boolean rv = self.Derivative(X, D); return std::tuple<Standard_Boolean, Standard_Real &>(rv, D); }, "computes the derivative <D> of the function for the variable <X>. Returns True if the calculation were successfully done, False otherwise.", py::arg("X"), py::arg("D"));
cls_ChFi3d_SearchSing.def("Values", [](ChFi3d_SearchSing &self, const Standard_Real X, Standard_Real & F, Standard_Real & D){ Standard_Boolean rv = self.Values(X, F, D); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, F, D); }, "computes the value <F> and the derivative <D> of the function for the variable <X>. Returns True if the calculation were successfully done, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));


}
