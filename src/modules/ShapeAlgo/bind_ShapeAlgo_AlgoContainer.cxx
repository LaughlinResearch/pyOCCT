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
#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>
#include <ShapeAlgo_ToolContainer.hxx>
#include <Standard_TypeDef.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeExtend_WireData.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColGeom_SequenceOfCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColGeom2d_SequenceOfCurve.hxx>
#include <TColGeom_HSequenceOfBoundedCurve.hxx>
#include <TColGeom2d_HSequenceOfBoundedCurve.hxx>
#include <TopoDS_Shape.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Surface.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <Geom_Curve.hxx>
#include <GeomAbs_Shape.hxx>
#include <ShapeAlgo_AlgoContainer.hxx>
#include <Standard_Type.hxx>

void bind_ShapeAlgo_AlgoContainer(py::module &mod){

py::class_<ShapeAlgo_AlgoContainer, opencascade::handle<ShapeAlgo_AlgoContainer>, Standard_Transient> cls_ShapeAlgo_AlgoContainer(mod, "ShapeAlgo_AlgoContainer", "None");

// Constructors
cls_ShapeAlgo_AlgoContainer.def(py::init<>());

// Fields

// Methods
cls_ShapeAlgo_AlgoContainer.def("SetToolContainer", (void (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<ShapeAlgo_ToolContainer> &)) &ShapeAlgo_AlgoContainer::SetToolContainer, "Sets ToolContainer", py::arg("TC"));
cls_ShapeAlgo_AlgoContainer.def("ToolContainer", (opencascade::handle<ShapeAlgo_ToolContainer> (ShapeAlgo_AlgoContainer::*)() const) &ShapeAlgo_AlgoContainer::ToolContainer, "Returns ToolContainer");
cls_ShapeAlgo_AlgoContainer.def("ConnectNextWire", [](ShapeAlgo_AlgoContainer &self, const opencascade::handle<ShapeAnalysis_Wire> & saw, const opencascade::handle<ShapeExtend_WireData> & nextsewd, const Standard_Real maxtol, Standard_Real & distmin, Standard_Boolean & revsewd, Standard_Boolean & revnextsewd){ Standard_Boolean rv = self.ConnectNextWire(saw, nextsewd, maxtol, distmin, revsewd, revnextsewd); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Boolean &, Standard_Boolean &>(rv, distmin, revsewd, revnextsewd); }, "Finds the best way to connect and connects <nextsewd> to already built <sewd> (in <saw>). Returns False if <nextsewd> cannot be connected, otherwise - True. <maxtol> specifies the maximum tolerance with which <nextsewd> can be added. <distmin> is used to receive the minimum distance between <nextsewd> and <sewd>. <revsewd> is True if <sewd> has been reversed before connecting. <revnextwd> is True if <nextsewd> has been reversed before connecting. Uses functionality of ShapeAnalysis_Wire.", py::arg("saw"), py::arg("nextsewd"), py::arg("maxtol"), py::arg("distmin"), py::arg("revsewd"), py::arg("revnextsewd"));
cls_ShapeAlgo_AlgoContainer.def("ApproxBSplineCurve", (void (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom_BSplineCurve> &, TColGeom_SequenceOfCurve &) const) &ShapeAlgo_AlgoContainer::ApproxBSplineCurve, "None", py::arg("bspline"), py::arg("seq"));
cls_ShapeAlgo_AlgoContainer.def("ApproxBSplineCurve", (void (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom2d_BSplineCurve> &, TColGeom2d_SequenceOfCurve &) const) &ShapeAlgo_AlgoContainer::ApproxBSplineCurve, "None", py::arg("bspline"), py::arg("seq"));
cls_ShapeAlgo_AlgoContainer.def("C0BSplineToSequenceOfC1BSplineCurve", (Standard_Boolean (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom_BSplineCurve> &, opencascade::handle<TColGeom_HSequenceOfBoundedCurve> &) const) &ShapeAlgo_AlgoContainer::C0BSplineToSequenceOfC1BSplineCurve, "None", py::arg("BS"), py::arg("seqBS"));
cls_ShapeAlgo_AlgoContainer.def("C0BSplineToSequenceOfC1BSplineCurve", (Standard_Boolean (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom2d_BSplineCurve> &, opencascade::handle<TColGeom2d_HSequenceOfBoundedCurve> &) const) &ShapeAlgo_AlgoContainer::C0BSplineToSequenceOfC1BSplineCurve, "Converts C0 B-Spline curve into sequence of C1 B-Spline curves. Calls ShapeUpgrade::C0BSplineToSequenceOfC1BSplineCurve.", py::arg("BS"), py::arg("seqBS"));
cls_ShapeAlgo_AlgoContainer.def("C0ShapeToC1Shape", (TopoDS_Shape (ShapeAlgo_AlgoContainer::*)(const TopoDS_Shape &, const Standard_Real) const) &ShapeAlgo_AlgoContainer::C0ShapeToC1Shape, "Converts a shape on C0 geometry into the shape on C1 geometry.", py::arg("shape"), py::arg("tol"));
cls_ShapeAlgo_AlgoContainer.def("ConvertSurfaceToBSpline", (opencascade::handle<Geom_BSplineSurface> (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom_Surface> &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real) const) &ShapeAlgo_AlgoContainer::ConvertSurfaceToBSpline, "Converts a surface to B-Spline. Uses ShapeConstruct.", py::arg("surf"), py::arg("UF"), py::arg("UL"), py::arg("VF"), py::arg("VL"));
cls_ShapeAlgo_AlgoContainer.def("HomoWires", (Standard_Boolean (ShapeAlgo_AlgoContainer::*)(const TopoDS_Wire &, const TopoDS_Wire &, TopoDS_Wire &, TopoDS_Wire &, const Standard_Boolean) const) &ShapeAlgo_AlgoContainer::HomoWires, "Return 2 wires with the same number of edges. The both Edges number i of these wires have got the same ratio between theirs parameter lengths and their wire parameter lengths.", py::arg("wireIn1"), py::arg("wireIn2"), py::arg("wireOut1"), py::arg("wireOut2"), py::arg("byParam"));
cls_ShapeAlgo_AlgoContainer.def("OuterWire", (TopoDS_Wire (ShapeAlgo_AlgoContainer::*)(const TopoDS_Face &) const) &ShapeAlgo_AlgoContainer::OuterWire, "Returns the outer wire on the face <Face>.", py::arg("face"));
cls_ShapeAlgo_AlgoContainer.def("ConvertToPeriodic", (opencascade::handle<Geom_Surface> (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom_Surface> &) const) &ShapeAlgo_AlgoContainer::ConvertToPeriodic, "Converts surface to periodic form. Calls ShapeCustom_Surface.", py::arg("surf"));
cls_ShapeAlgo_AlgoContainer.def("GetFaceUVBounds", [](ShapeAlgo_AlgoContainer &self, const TopoDS_Face & F, Standard_Real & Umin, Standard_Real & Umax, Standard_Real & Vmin, Standard_Real & Vmax){ self.GetFaceUVBounds(F, Umin, Umax, Vmin, Vmax); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(Umin, Umax, Vmin, Vmax); }, "Computes exact UV bounds of all wires on the face", py::arg("F"), py::arg("Umin"), py::arg("Umax"), py::arg("Vmin"), py::arg("Vmax"));
cls_ShapeAlgo_AlgoContainer.def("ConvertCurveToBSpline", (opencascade::handle<Geom_BSplineCurve> (ShapeAlgo_AlgoContainer::*)(const opencascade::handle<Geom_Curve> &, const Standard_Real, const Standard_Real, const Standard_Real, const GeomAbs_Shape, const Standard_Integer, const Standard_Integer) const) &ShapeAlgo_AlgoContainer::ConvertCurveToBSpline, "Convert Geom_Curve to Geom_BSplineCurve", py::arg("C3D"), py::arg("First"), py::arg("Last"), py::arg("Tol3d"), py::arg("Continuity"), py::arg("MaxSegments"), py::arg("MaxDegree"));
cls_ShapeAlgo_AlgoContainer.def_static("get_type_name_", (const char * (*)()) &ShapeAlgo_AlgoContainer::get_type_name, "None");
cls_ShapeAlgo_AlgoContainer.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAlgo_AlgoContainer::get_type_descriptor, "None");
cls_ShapeAlgo_AlgoContainer.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAlgo_AlgoContainer::*)() const) &ShapeAlgo_AlgoContainer::DynamicType, "None");

// Enums

}