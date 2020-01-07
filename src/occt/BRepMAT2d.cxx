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
#include <BRepMAT2d_Explorer.hxx>
#include <Standard_TypeDef.hxx>
#include <MAT_Side.hxx>
#include <GeomAbs_JoinType.hxx>
#include <Standard_Handle.hxx>
#include <MAT_Graph.hxx>
#include <MAT_BasicElt.hxx>
#include <Geom2d_Geometry.hxx>
#include <gp_Pnt2d.hxx>
#include <MAT_Node.hxx>
#include <Bisector_Bisec.hxx>
#include <MAT_Arc.hxx>
#include <MAT_DataMapOfIntegerBasicElt.hxx>
#include <MAT2d_Tool2d.hxx>
#include <MAT2d_DataMapOfBiIntInteger.hxx>
#include <BRepMAT2d_BisectingLocus.hxx>
#include <NCollection_DataMap.hxx>
#include <TopoDS_Shape.hxx>
#include <MAT_SequenceOfBasicElt.hxx>
#include <TopTools_ShapeMapHasher.hxx>
#include <BRepMAT2d_DataMapOfShapeSequenceOfBasicElt.hxx>
#include <TColStd_MapTransientHasher.hxx>
#include <BRepMAT2d_DataMapOfBasicEltShape.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepMAT2d_LinkTopoBilo.hxx>
#include <TopoDS_Face.hxx>
#include <Geom2d_Curve.hxx>
#include <TColGeom2d_SequenceOfCurve.hxx>
#include <TColStd_SequenceOfBoolean.hxx>
#include <MAT2d_SequenceOfSequenceOfCurve.hxx>
#include <TopTools_IndexedDataMapOfShapeShape.hxx>
#include <bind_NCollection_DataMap.hxx>

PYBIND11_MODULE(BRepMAT2d, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.MAT");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.gp");
py::module::import("OCCT.Bisector");
py::module::import("OCCT.MAT2d");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.TopTools");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.TColGeom2d");

// CLASS: BREPMAT2D_BISECTINGLOCUS
py::class_<BRepMAT2d_BisectingLocus> cls_BRepMAT2d_BisectingLocus(mod, "BRepMAT2d_BisectingLocus", "BisectingLocus generates and contains the Bisecting_Locus of a set of lines from Geom2d, defined by <ExploSet>.");

// Constructors
cls_BRepMAT2d_BisectingLocus.def(py::init<>());

// Methods
// cls_BRepMAT2d_BisectingLocus.def_static("operator new_", (void * (*)(size_t)) &BRepMAT2d_BisectingLocus::operator new, "None", py::arg("theSize"));
// cls_BRepMAT2d_BisectingLocus.def_static("operator delete_", (void (*)(void *)) &BRepMAT2d_BisectingLocus::operator delete, "None", py::arg("theAddress"));
// cls_BRepMAT2d_BisectingLocus.def_static("operator new[]_", (void * (*)(size_t)) &BRepMAT2d_BisectingLocus::operator new[], "None", py::arg("theSize"));
// cls_BRepMAT2d_BisectingLocus.def_static("operator delete[]_", (void (*)(void *)) &BRepMAT2d_BisectingLocus::operator delete[], "None", py::arg("theAddress"));
// cls_BRepMAT2d_BisectingLocus.def_static("operator new_", (void * (*)(size_t, void *)) &BRepMAT2d_BisectingLocus::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepMAT2d_BisectingLocus.def_static("operator delete_", (void (*)(void *, void *)) &BRepMAT2d_BisectingLocus::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepMAT2d_BisectingLocus.def("Compute", [](BRepMAT2d_BisectingLocus &self, BRepMAT2d_Explorer & a0) -> void { return self.Compute(a0); });
cls_BRepMAT2d_BisectingLocus.def("Compute", [](BRepMAT2d_BisectingLocus &self, BRepMAT2d_Explorer & a0, const Standard_Integer a1) -> void { return self.Compute(a0, a1); });
cls_BRepMAT2d_BisectingLocus.def("Compute", [](BRepMAT2d_BisectingLocus &self, BRepMAT2d_Explorer & a0, const Standard_Integer a1, const MAT_Side a2) -> void { return self.Compute(a0, a1, a2); });
cls_BRepMAT2d_BisectingLocus.def("Compute", [](BRepMAT2d_BisectingLocus &self, BRepMAT2d_Explorer & a0, const Standard_Integer a1, const MAT_Side a2, const GeomAbs_JoinType a3) -> void { return self.Compute(a0, a1, a2, a3); });
cls_BRepMAT2d_BisectingLocus.def("Compute", (void (BRepMAT2d_BisectingLocus::*)(BRepMAT2d_Explorer &, const Standard_Integer, const MAT_Side, const GeomAbs_JoinType, const Standard_Boolean)) &BRepMAT2d_BisectingLocus::Compute, "Computation of the Bisector_Locus in a set of Lines defined in <anExplo>. The bisecting locus are computed on the side <aSide> from the line <LineIndex> in <anExplo>.", py::arg("anExplo"), py::arg("LineIndex"), py::arg("aSide"), py::arg("aJoinType"), py::arg("IsOpenResult"));
cls_BRepMAT2d_BisectingLocus.def("IsDone", (Standard_Boolean (BRepMAT2d_BisectingLocus::*)() const) &BRepMAT2d_BisectingLocus::IsDone, "Returns True if Compute has succeeded.");
cls_BRepMAT2d_BisectingLocus.def("Graph", (opencascade::handle<MAT_Graph> (BRepMAT2d_BisectingLocus::*)() const) &BRepMAT2d_BisectingLocus::Graph, "Returns <theGraph> of <me>.");
cls_BRepMAT2d_BisectingLocus.def("NumberOfContours", (Standard_Integer (BRepMAT2d_BisectingLocus::*)() const) &BRepMAT2d_BisectingLocus::NumberOfContours, "Returns the number of contours.");
cls_BRepMAT2d_BisectingLocus.def("NumberOfElts", (Standard_Integer (BRepMAT2d_BisectingLocus::*)(const Standard_Integer) const) &BRepMAT2d_BisectingLocus::NumberOfElts, "Returns the number of BasicElts on the line <IndLine>.", py::arg("IndLine"));
cls_BRepMAT2d_BisectingLocus.def("NumberOfSections", (Standard_Integer (BRepMAT2d_BisectingLocus::*)(const Standard_Integer, const Standard_Integer) const) &BRepMAT2d_BisectingLocus::NumberOfSections, "Returns the number of sections of a curve. this curve is the Indexth curve in the IndLineth contour given by anExplo.", py::arg("IndLine"), py::arg("Index"));
cls_BRepMAT2d_BisectingLocus.def("BasicElt", (opencascade::handle<MAT_BasicElt> (BRepMAT2d_BisectingLocus::*)(const Standard_Integer, const Standard_Integer) const) &BRepMAT2d_BisectingLocus::BasicElt, "Returns the BasicElts located at the position <Index> on the contour designed by <IndLine>. Remark: the BasicElts on a contour are sorted.", py::arg("IndLine"), py::arg("Index"));
cls_BRepMAT2d_BisectingLocus.def("GeomElt", (opencascade::handle<Geom2d_Geometry> (BRepMAT2d_BisectingLocus::*)(const opencascade::handle<MAT_BasicElt> &) const) &BRepMAT2d_BisectingLocus::GeomElt, "Returns the geometry linked to the <BasicElt>.", py::arg("aBasicElt"));
cls_BRepMAT2d_BisectingLocus.def("GeomElt", (gp_Pnt2d (BRepMAT2d_BisectingLocus::*)(const opencascade::handle<MAT_Node> &) const) &BRepMAT2d_BisectingLocus::GeomElt, "Returns the geometry of type <gp> linked to the <Node>.", py::arg("aNode"));
cls_BRepMAT2d_BisectingLocus.def("GeomBis", [](BRepMAT2d_BisectingLocus &self, const opencascade::handle<MAT_Arc> & anArc, Standard_Boolean & Reverse){ Bisector_Bisec rv = self.GeomBis(anArc, Reverse); return std::tuple<Bisector_Bisec, Standard_Boolean &>(rv, Reverse); }, "Returns the geometry of type <Bissec> linked to the arc <ARC>. <Reverse> is False when the FirstNode of <anArc> correspond to the first point of geometry.", py::arg("anArc"), py::arg("Reverse"));

// TYPEDEF: BREPMAT2D_DATAMAPOFSHAPESEQUENCEOFBASICELT
bind_NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<opencascade::handle<MAT_BasicElt> >, TopTools_ShapeMapHasher>(mod, "BRepMAT2d_DataMapOfShapeSequenceOfBasicElt", py::module_local(false));

// TYPEDEF: BREPMAT2D_DATAMAPITERATOROFDATAMAPOFSHAPESEQUENCEOFBASICELT

// TYPEDEF: BREPMAT2D_DATAMAPOFBASICELTSHAPE
bind_NCollection_DataMap<opencascade::handle<MAT_BasicElt>, TopoDS_Shape, NCollection_DefaultHasher<opencascade::handle<Standard_Transient> > >(mod, "BRepMAT2d_DataMapOfBasicEltShape", py::module_local(false));

// TYPEDEF: BREPMAT2D_DATAMAPITERATOROFDATAMAPOFBASICELTSHAPE

// CLASS: BREPMAT2D_LINKTOPOBILO
py::class_<BRepMAT2d_LinkTopoBilo> cls_BRepMAT2d_LinkTopoBilo(mod, "BRepMAT2d_LinkTopoBilo", "Constucts links between the Wire or the Face of the explorer and the BasicElts contained in the bisecting locus.");

// Constructors
cls_BRepMAT2d_LinkTopoBilo.def(py::init<>());
cls_BRepMAT2d_LinkTopoBilo.def(py::init<const BRepMAT2d_Explorer &, const BRepMAT2d_BisectingLocus &>(), py::arg("Explo"), py::arg("BiLo"));

// Methods
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator new_", (void * (*)(size_t)) &BRepMAT2d_LinkTopoBilo::operator new, "None", py::arg("theSize"));
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator delete_", (void (*)(void *)) &BRepMAT2d_LinkTopoBilo::operator delete, "None", py::arg("theAddress"));
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator new[]_", (void * (*)(size_t)) &BRepMAT2d_LinkTopoBilo::operator new[], "None", py::arg("theSize"));
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator delete[]_", (void (*)(void *)) &BRepMAT2d_LinkTopoBilo::operator delete[], "None", py::arg("theAddress"));
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator new_", (void * (*)(size_t, void *)) &BRepMAT2d_LinkTopoBilo::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepMAT2d_LinkTopoBilo.def_static("operator delete_", (void (*)(void *, void *)) &BRepMAT2d_LinkTopoBilo::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepMAT2d_LinkTopoBilo.def("Perform", (void (BRepMAT2d_LinkTopoBilo::*)(const BRepMAT2d_Explorer &, const BRepMAT2d_BisectingLocus &)) &BRepMAT2d_LinkTopoBilo::Perform, "Constructs the links Between S and BiLo.", py::arg("Explo"), py::arg("BiLo"));
cls_BRepMAT2d_LinkTopoBilo.def("Init", (void (BRepMAT2d_LinkTopoBilo::*)(const TopoDS_Shape &)) &BRepMAT2d_LinkTopoBilo::Init, "Initialise the Iterator on <S> <S> is an edge or a vertex of the initial wire or face. raises if <S> is not an edge or a vertex.", py::arg("S"));
cls_BRepMAT2d_LinkTopoBilo.def("More", (Standard_Boolean (BRepMAT2d_LinkTopoBilo::*)()) &BRepMAT2d_LinkTopoBilo::More, "Returns True if there is a current BasicElt.");
cls_BRepMAT2d_LinkTopoBilo.def("Next", (void (BRepMAT2d_LinkTopoBilo::*)()) &BRepMAT2d_LinkTopoBilo::Next, "Proceed to the next BasicElt.");
cls_BRepMAT2d_LinkTopoBilo.def("Value", (opencascade::handle<MAT_BasicElt> (BRepMAT2d_LinkTopoBilo::*)() const) &BRepMAT2d_LinkTopoBilo::Value, "Returns the current BasicElt.");
cls_BRepMAT2d_LinkTopoBilo.def("GeneratingShape", (TopoDS_Shape (BRepMAT2d_LinkTopoBilo::*)(const opencascade::handle<MAT_BasicElt> &) const) &BRepMAT2d_LinkTopoBilo::GeneratingShape, "Returns the Shape linked to <aBE>.", py::arg("aBE"));

// CLASS: BREPMAT2D_EXPLORER
py::class_<BRepMAT2d_Explorer> cls_BRepMAT2d_Explorer(mod, "BRepMAT2d_Explorer", "Construct an explorer from wires, face, set of curves from Geom2d to compute the bisecting Locus.");

// Constructors
cls_BRepMAT2d_Explorer.def(py::init<>());
cls_BRepMAT2d_Explorer.def(py::init<const TopoDS_Face &>(), py::arg("aFace"));

// Methods
// cls_BRepMAT2d_Explorer.def_static("operator new_", (void * (*)(size_t)) &BRepMAT2d_Explorer::operator new, "None", py::arg("theSize"));
// cls_BRepMAT2d_Explorer.def_static("operator delete_", (void (*)(void *)) &BRepMAT2d_Explorer::operator delete, "None", py::arg("theAddress"));
// cls_BRepMAT2d_Explorer.def_static("operator new[]_", (void * (*)(size_t)) &BRepMAT2d_Explorer::operator new[], "None", py::arg("theSize"));
// cls_BRepMAT2d_Explorer.def_static("operator delete[]_", (void (*)(void *)) &BRepMAT2d_Explorer::operator delete[], "None", py::arg("theAddress"));
// cls_BRepMAT2d_Explorer.def_static("operator new_", (void * (*)(size_t, void *)) &BRepMAT2d_Explorer::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepMAT2d_Explorer.def_static("operator delete_", (void (*)(void *, void *)) &BRepMAT2d_Explorer::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepMAT2d_Explorer.def("Clear", (void (BRepMAT2d_Explorer::*)()) &BRepMAT2d_Explorer::Clear, "Clear the contents of <me>.");
cls_BRepMAT2d_Explorer.def("Perform", (void (BRepMAT2d_Explorer::*)(const TopoDS_Face &)) &BRepMAT2d_Explorer::Perform, "None", py::arg("aFace"));
cls_BRepMAT2d_Explorer.def("NumberOfContours", (Standard_Integer (BRepMAT2d_Explorer::*)() const) &BRepMAT2d_Explorer::NumberOfContours, "Returns the Number of contours.");
cls_BRepMAT2d_Explorer.def("NumberOfCurves", (Standard_Integer (BRepMAT2d_Explorer::*)(const Standard_Integer) const) &BRepMAT2d_Explorer::NumberOfCurves, "Returns the Number of Curves in the Contour number <IndexContour>.", py::arg("IndexContour"));
cls_BRepMAT2d_Explorer.def("Init", (void (BRepMAT2d_Explorer::*)(const Standard_Integer)) &BRepMAT2d_Explorer::Init, "Initialisation of an Iterator on the curves of the Contour number <IndexContour>.", py::arg("IndexContour"));
cls_BRepMAT2d_Explorer.def("More", (Standard_Boolean (BRepMAT2d_Explorer::*)() const) &BRepMAT2d_Explorer::More, "Return False if there is no more curves on the Contour initialised by the method Init.");
cls_BRepMAT2d_Explorer.def("Next", (void (BRepMAT2d_Explorer::*)()) &BRepMAT2d_Explorer::Next, "Move to the next curve of the current Contour.");
cls_BRepMAT2d_Explorer.def("Value", (opencascade::handle<Geom2d_Curve> (BRepMAT2d_Explorer::*)() const) &BRepMAT2d_Explorer::Value, "Returns the current curve on the current Contour.");
cls_BRepMAT2d_Explorer.def("Shape", (TopoDS_Shape (BRepMAT2d_Explorer::*)() const) &BRepMAT2d_Explorer::Shape, "None");
cls_BRepMAT2d_Explorer.def("Contour", (const TColGeom2d_SequenceOfCurve & (BRepMAT2d_Explorer::*)(const Standard_Integer) const) &BRepMAT2d_Explorer::Contour, "None", py::arg("IndexContour"));
cls_BRepMAT2d_Explorer.def("IsModified", (Standard_Boolean (BRepMAT2d_Explorer::*)(const TopoDS_Shape &) const) &BRepMAT2d_Explorer::IsModified, "None", py::arg("aShape"));
cls_BRepMAT2d_Explorer.def("ModifiedShape", (TopoDS_Shape (BRepMAT2d_Explorer::*)(const TopoDS_Shape &) const) &BRepMAT2d_Explorer::ModifiedShape, "If the shape is not modified, returns the shape itself.", py::arg("aShape"));
cls_BRepMAT2d_Explorer.def("GetIsClosed", (const TColStd_SequenceOfBoolean & (BRepMAT2d_Explorer::*)() const) &BRepMAT2d_Explorer::GetIsClosed, "None");


}
