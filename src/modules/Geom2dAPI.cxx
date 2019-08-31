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
#include <Geom2d_Curve.hxx>
#include <Standard_TypeDef.hxx>
#include <gp_Pnt2d.hxx>
#include <Extrema_ExtCC2d.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2dAPI_ExtremaCurveCurve.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <gp_Vec2d.hxx>
#include <TColgp_Array1OfVec2d.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_HArray1OfVec2d.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <GeomAbs_Shape.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <Approx_ParametrizationType.hxx>
#include <Geom2dAPI_PointsToBSpline.hxx>
#include <Extrema_ExtPC2d.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

PYBIND11_MODULE(Geom2dAPI, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.gp");
py::module::import("OCCT.Extrema");
py::module::import("OCCT.Geom2dAdaptor");
py::module::import("OCCT.Geom2dInt");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.Approx");

// CLASS: GEOM2DAPI_EXTREMACURVECURVE
py::class_<Geom2dAPI_ExtremaCurveCurve> cls_Geom2dAPI_ExtremaCurveCurve(mod, "Geom2dAPI_ExtremaCurveCurve", "Describes functions for computing all the extrema between two 2D curves. An ExtremaCurveCurve algorithm minimizes or maximizes the distance between a point on the first curve and a point on the second curve. Thus, it computes the start point and end point of perpendiculars common to the two curves (an intersection point is not an extremum except where the two curves are tangential at this point). Solutions consist of pairs of points, and an extremum is considered to be a segment joining the two points of a solution. An ExtremaCurveCurve object provides a framework for: - defining the construction of the extrema, - implementing the construction algorithm, and - consulting the results. Warning In some cases, the nearest points between two curves do not correspond to one of the computed extrema. Instead, they may be given by: - a limit point of one curve and one of the following: - its orthogonal projection on the other curve, - a limit point of the other curve; or - an intersection point between the two curves.");

// Constructors
cls_Geom2dAPI_ExtremaCurveCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &, const opencascade::handle<Geom2d_Curve> &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("C1"), py::arg("C2"), py::arg("U1min"), py::arg("U1max"), py::arg("U2min"), py::arg("U2max"));

// Methods
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator new_", (void * (*)(size_t)) &Geom2dAPI_ExtremaCurveCurve::operator new, "None", py::arg("theSize"));
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator delete_", (void (*)(void *)) &Geom2dAPI_ExtremaCurveCurve::operator delete, "None", py::arg("theAddress"));
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator new[]_", (void * (*)(size_t)) &Geom2dAPI_ExtremaCurveCurve::operator new[], "None", py::arg("theSize"));
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator delete[]_", (void (*)(void *)) &Geom2dAPI_ExtremaCurveCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Geom2dAPI_ExtremaCurveCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Geom2dAPI_ExtremaCurveCurve.def_static("operator delete_", (void (*)(void *, void *)) &Geom2dAPI_ExtremaCurveCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_Geom2dAPI_ExtremaCurveCurve.def("NbExtrema", (Standard_Integer (Geom2dAPI_ExtremaCurveCurve::*)() const) &Geom2dAPI_ExtremaCurveCurve::NbExtrema, "Returns the number of extrema computed by this algorithm. Note: if this algorithm fails, NbExtrema returns 0.");
cls_Geom2dAPI_ExtremaCurveCurve.def("Points", (void (Geom2dAPI_ExtremaCurveCurve::*)(const Standard_Integer, gp_Pnt2d &, gp_Pnt2d &) const) &Geom2dAPI_ExtremaCurveCurve::Points, "Returns the points P1 on the first curve and P2 on the second curve, which are the ends of the extremum of index Index computed by this algorithm. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbExtrema ], where NbExtrema is the number of extrema computed by this algorithm.", py::arg("Index"), py::arg("P1"), py::arg("P2"));
cls_Geom2dAPI_ExtremaCurveCurve.def("Parameters", [](Geom2dAPI_ExtremaCurveCurve &self, const Standard_Integer Index, Standard_Real & U1, Standard_Real & U2){ self.Parameters(Index, U1, U2); return std::tuple<Standard_Real &, Standard_Real &>(U1, U2); }, "Returns the parameters U1 of the point on the first curve and U2 of the point on the second curve, which are the ends of the extremum of index Index computed by this algorithm. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbExtrema ], where NbExtrema is the number of extrema computed by this algorithm.", py::arg("Index"), py::arg("U1"), py::arg("U2"));
cls_Geom2dAPI_ExtremaCurveCurve.def("Distance", (Standard_Real (Geom2dAPI_ExtremaCurveCurve::*)(const Standard_Integer) const) &Geom2dAPI_ExtremaCurveCurve::Distance, "Computes the distance between the end points of the extremum of index Index computed by this algorithm. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbExtrema ], where NbExtrema is the number of extrema computed by this algorithm.", py::arg("Index"));
cls_Geom2dAPI_ExtremaCurveCurve.def("NearestPoints", (void (Geom2dAPI_ExtremaCurveCurve::*)(gp_Pnt2d &, gp_Pnt2d &) const) &Geom2dAPI_ExtremaCurveCurve::NearestPoints, "Returns the points P1 on the first curve and P2 on the second curve, which are the ends of the shortest extremum computed by this algorithm. Exceptions StdFail_NotDone if this algorithm fails.", py::arg("P1"), py::arg("P2"));
cls_Geom2dAPI_ExtremaCurveCurve.def("LowerDistanceParameters", [](Geom2dAPI_ExtremaCurveCurve &self, Standard_Real & U1, Standard_Real & U2){ self.LowerDistanceParameters(U1, U2); return std::tuple<Standard_Real &, Standard_Real &>(U1, U2); }, "Returns the parameters U1 of the point on the first curve and U2 of the point on the second curve, which are the ends of the shortest extremum computed by this algorithm. Exceptions StdFail_NotDone if this algorithm fails.", py::arg("U1"), py::arg("U2"));
cls_Geom2dAPI_ExtremaCurveCurve.def("LowerDistance", (Standard_Real (Geom2dAPI_ExtremaCurveCurve::*)() const) &Geom2dAPI_ExtremaCurveCurve::LowerDistance, "Computes the distance between the end points of the shortest extremum computed by this algorithm. Exceptions - StdFail_NotDone if this algorithm fails.");
cls_Geom2dAPI_ExtremaCurveCurve.def("Extrema", (const Extrema_ExtCC2d & (Geom2dAPI_ExtremaCurveCurve::*)() const) &Geom2dAPI_ExtremaCurveCurve::Extrema, "None");

// CLASS: GEOM2DAPI_INTERCURVECURVE
py::class_<Geom2dAPI_InterCurveCurve> cls_Geom2dAPI_InterCurveCurve(mod, "Geom2dAPI_InterCurveCurve", "This class implements methods for computing - the intersections between two 2D curves, - the self-intersections of a 2D curve. Using the InterCurveCurve algorithm allows to get the following results: - intersection points in the case of cross intersections, - intersection segments in the case of tangential intersections, - nothing in the case of no intersections.");

// Constructors
cls_Geom2dAPI_InterCurveCurve.def(py::init<>());
cls_Geom2dAPI_InterCurveCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &, const opencascade::handle<Geom2d_Curve> &>(), py::arg("C1"), py::arg("C2"));
cls_Geom2dAPI_InterCurveCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &, const opencascade::handle<Geom2d_Curve> &, const Standard_Real>(), py::arg("C1"), py::arg("C2"), py::arg("Tol"));
cls_Geom2dAPI_InterCurveCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &>(), py::arg("C1"));
cls_Geom2dAPI_InterCurveCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &, const Standard_Real>(), py::arg("C1"), py::arg("Tol"));

// Methods
// cls_Geom2dAPI_InterCurveCurve.def_static("operator new_", (void * (*)(size_t)) &Geom2dAPI_InterCurveCurve::operator new, "None", py::arg("theSize"));
// cls_Geom2dAPI_InterCurveCurve.def_static("operator delete_", (void (*)(void *)) &Geom2dAPI_InterCurveCurve::operator delete, "None", py::arg("theAddress"));
// cls_Geom2dAPI_InterCurveCurve.def_static("operator new[]_", (void * (*)(size_t)) &Geom2dAPI_InterCurveCurve::operator new[], "None", py::arg("theSize"));
// cls_Geom2dAPI_InterCurveCurve.def_static("operator delete[]_", (void (*)(void *)) &Geom2dAPI_InterCurveCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Geom2dAPI_InterCurveCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Geom2dAPI_InterCurveCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Geom2dAPI_InterCurveCurve.def_static("operator delete_", (void (*)(void *, void *)) &Geom2dAPI_InterCurveCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_Geom2dAPI_InterCurveCurve.def("Init", [](Geom2dAPI_InterCurveCurve &self, const opencascade::handle<Geom2d_Curve> & a0, const opencascade::handle<Geom2d_Curve> & a1) -> void { return self.Init(a0, a1); });
cls_Geom2dAPI_InterCurveCurve.def("Init", (void (Geom2dAPI_InterCurveCurve::*)(const opencascade::handle<Geom2d_Curve> &, const opencascade::handle<Geom2d_Curve> &, const Standard_Real)) &Geom2dAPI_InterCurveCurve::Init, "Initializes an algorithm with the given arguments and computes the intersections between the curves C1. and C2.", py::arg("C1"), py::arg("C2"), py::arg("Tol"));
cls_Geom2dAPI_InterCurveCurve.def("Init", [](Geom2dAPI_InterCurveCurve &self, const opencascade::handle<Geom2d_Curve> & a0) -> void { return self.Init(a0); });
cls_Geom2dAPI_InterCurveCurve.def("Init", (void (Geom2dAPI_InterCurveCurve::*)(const opencascade::handle<Geom2d_Curve> &, const Standard_Real)) &Geom2dAPI_InterCurveCurve::Init, "Initializes an algorithm with the given arguments and computes the self-intersections of the curve C1. Tolerance value Tol, defaulted to 1.0e-6, defines the precision of computing the intersection points. In case of a tangential intersection, Tol also defines the size of intersection segments (limited portions of the curves) where the distance between all points from two curves (or a curve in case of self-intersection) is less than Tol. Warning Use functions NbPoints and NbSegments to obtain the number of solutions. If the algorithm finds no intersections NbPoints and NbSegments return 0.", py::arg("C1"), py::arg("Tol"));
cls_Geom2dAPI_InterCurveCurve.def("NbPoints", (Standard_Integer (Geom2dAPI_InterCurveCurve::*)() const) &Geom2dAPI_InterCurveCurve::NbPoints, "Returns the number of intersection-points in case of cross intersections. NbPoints returns 0 if no intersections were found.");
cls_Geom2dAPI_InterCurveCurve.def("Point", (gp_Pnt2d (Geom2dAPI_InterCurveCurve::*)(const Standard_Integer) const) &Geom2dAPI_InterCurveCurve::Point, "Returns the intersection point of index Index. Intersection points are computed in case of cross intersections with a precision equal to the tolerance value assigned at the time of construction or in the function Init (this value is defaulted to 1.0e-6). Exceptions Standard_OutOfRange if index is not in the range [ 1,NbPoints ], where NbPoints is the number of computed intersection points", py::arg("Index"));
cls_Geom2dAPI_InterCurveCurve.def("NbSegments", (Standard_Integer (Geom2dAPI_InterCurveCurve::*)() const) &Geom2dAPI_InterCurveCurve::NbSegments, "Returns the number of tangential intersections. NbSegments returns 0 if no intersections were found");
cls_Geom2dAPI_InterCurveCurve.def("Segment", (void (Geom2dAPI_InterCurveCurve::*)(const Standard_Integer, opencascade::handle<Geom2d_Curve> &, opencascade::handle<Geom2d_Curve> &) const) &Geom2dAPI_InterCurveCurve::Segment, "Use this syntax only to get solutions of tangential intersection between two curves. Output values Curve1 and Curve2 are the intersection segments on the first curve and on the second curve accordingly. Parameter Index defines a number of computed solution. An intersection segment is a portion of an initial curve limited by two points. The distance from each point of this segment to the other curve is less or equal to the tolerance value assigned at the time of construction or in function Init (this value is defaulted to 1.0e-6). Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbSegments ], where NbSegments is the number of computed tangential intersections. Standard_NullObject if the algorithm is initialized for the computing of self-intersections on a curve.", py::arg("Index"), py::arg("Curve1"), py::arg("Curve2"));
cls_Geom2dAPI_InterCurveCurve.def("Intersector", (const Geom2dInt_GInter & (Geom2dAPI_InterCurveCurve::*)() const) &Geom2dAPI_InterCurveCurve::Intersector, "return the algorithmic object from Intersection.");

// CLASS: GEOM2DAPI_INTERPOLATE
py::class_<Geom2dAPI_Interpolate> cls_Geom2dAPI_Interpolate(mod, "Geom2dAPI_Interpolate", "This class is used to interpolate a BsplineCurve passing through an array of points, with a C2 Continuity if tangency is not requested at the point. If tangency is requested at the point the continuity will be C1. If Perodicity is requested the curve will be closed and the junction will be the first point given. The curve will than be only C1 The curve is defined by a table of points through which it passes, and if required by a parallel table of reals which gives the value of the parameter of each point through which the resulting BSpline curve passes, and by vectors tangential to these points. An Interpolate object provides a framework for: defining the constraints of the BSpline curve, - implementing the interpolation algorithm, and consulting the results.");

// Constructors
cls_Geom2dAPI_Interpolate.def(py::init<const opencascade::handle<TColgp_HArray1OfPnt2d> &, const Standard_Boolean, const Standard_Real>(), py::arg("Points"), py::arg("PeriodicFlag"), py::arg("Tolerance"));
cls_Geom2dAPI_Interpolate.def(py::init<const opencascade::handle<TColgp_HArray1OfPnt2d> &, const opencascade::handle<TColStd_HArray1OfReal> &, const Standard_Boolean, const Standard_Real>(), py::arg("Points"), py::arg("Parameters"), py::arg("PeriodicFlag"), py::arg("Tolerance"));

// Methods
// cls_Geom2dAPI_Interpolate.def_static("operator new_", (void * (*)(size_t)) &Geom2dAPI_Interpolate::operator new, "None", py::arg("theSize"));
// cls_Geom2dAPI_Interpolate.def_static("operator delete_", (void (*)(void *)) &Geom2dAPI_Interpolate::operator delete, "None", py::arg("theAddress"));
// cls_Geom2dAPI_Interpolate.def_static("operator new[]_", (void * (*)(size_t)) &Geom2dAPI_Interpolate::operator new[], "None", py::arg("theSize"));
// cls_Geom2dAPI_Interpolate.def_static("operator delete[]_", (void (*)(void *)) &Geom2dAPI_Interpolate::operator delete[], "None", py::arg("theAddress"));
// cls_Geom2dAPI_Interpolate.def_static("operator new_", (void * (*)(size_t, void *)) &Geom2dAPI_Interpolate::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Geom2dAPI_Interpolate.def_static("operator delete_", (void (*)(void *, void *)) &Geom2dAPI_Interpolate::operator delete, "None", py::arg(""), py::arg(""));
cls_Geom2dAPI_Interpolate.def("Load", [](Geom2dAPI_Interpolate &self, const gp_Vec2d & a0, const gp_Vec2d & a1) -> void { return self.Load(a0, a1); });
cls_Geom2dAPI_Interpolate.def("Load", (void (Geom2dAPI_Interpolate::*)(const gp_Vec2d &, const gp_Vec2d &, const Standard_Boolean)) &Geom2dAPI_Interpolate::Load, "Assigns this constrained BSpline curve to be tangential to vectors InitialTangent and FinalTangent at its first and last points respectively (i.e. the first and last points of the table of points through which the curve passes, as defined at the time of initialization). <Scale> - boolean flag defining whether tangent vectors are to be scaled according to derivatives of lagrange interpolation.", py::arg("InitialTangent"), py::arg("FinalTangent"), py::arg("Scale"));
cls_Geom2dAPI_Interpolate.def("Load", [](Geom2dAPI_Interpolate &self, const TColgp_Array1OfVec2d & a0, const opencascade::handle<TColStd_HArray1OfBoolean> & a1) -> void { return self.Load(a0, a1); });
cls_Geom2dAPI_Interpolate.def("Load", (void (Geom2dAPI_Interpolate::*)(const TColgp_Array1OfVec2d &, const opencascade::handle<TColStd_HArray1OfBoolean> &, const Standard_Boolean)) &Geom2dAPI_Interpolate::Load, "Assigns this constrained BSpline curve to be tangential to vectors defined in the table Tangents, which is parallel to the table of points through which the curve passes, as defined at the time of initialization. Vectors in the table Tangents are defined only if the flag given in the parallel table TangentFlags is true: only these vectors are set as tangency constraints. <Scale> - boolean flag defining whether tangent vectors are to be scaled according to derivatives of lagrange interpolation.", py::arg("Tangents"), py::arg("TangentFlags"), py::arg("Scale"));
// cls_Geom2dAPI_Interpolate.def("ClearTangents", (void (Geom2dAPI_Interpolate::*)()) &Geom2dAPI_Interpolate::ClearTangents, "Clears all tangency constraints on this constrained BSpline curve (as initialized by the function Load).");
cls_Geom2dAPI_Interpolate.def("Perform", (void (Geom2dAPI_Interpolate::*)()) &Geom2dAPI_Interpolate::Perform, "Computes the constrained BSpline curve. Use the function IsDone to verify that the computation is successful, and then the function Curve to obtain the result.");
cls_Geom2dAPI_Interpolate.def("Curve", (const opencascade::handle<Geom2d_BSplineCurve> & (Geom2dAPI_Interpolate::*)() const) &Geom2dAPI_Interpolate::Curve, "Returns the computed BSpline curve. Raises StdFail_NotDone if the interpolation fails.");
cls_Geom2dAPI_Interpolate.def("IsDone", (Standard_Boolean (Geom2dAPI_Interpolate::*)() const) &Geom2dAPI_Interpolate::IsDone, "Returns true if the constrained BSpline curve is successfully constructed. Note: in this case, the result is given by the function Curve.");

// CLASS: GEOM2DAPI_POINTSTOBSPLINE
py::class_<Geom2dAPI_PointsToBSpline> cls_Geom2dAPI_PointsToBSpline(mod, "Geom2dAPI_PointsToBSpline", "This class is used to approximate a BsplineCurve passing through an array of points, with a given Continuity. Describes functions for building a 2D BSpline curve which approximates a set of points. A PointsToBSpline object provides a framework for: - defining the data of the BSpline curve to be built, - implementing the approximation algorithm, and - consulting the results");

// Constructors
cls_Geom2dAPI_PointsToBSpline.def(py::init<>());
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &>(), py::arg("Points"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Integer>(), py::arg("Points"), py::arg("DegMin"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Integer, const Standard_Integer>(), py::arg("Points"), py::arg("DegMin"), py::arg("DegMax"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape>(), py::arg("Points"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real>(), py::arg("Points"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real>(), py::arg("YValues"), py::arg("X0"), py::arg("DX"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real, const Standard_Integer>(), py::arg("YValues"), py::arg("X0"), py::arg("DX"), py::arg("DegMin"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer>(), py::arg("YValues"), py::arg("X0"), py::arg("DX"), py::arg("DegMin"), py::arg("DegMax"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape>(), py::arg("YValues"), py::arg("X0"), py::arg("DX"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real>(), py::arg("YValues"), py::arg("X0"), py::arg("DX"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType>(), py::arg("Points"), py::arg("ParType"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType, const Standard_Integer>(), py::arg("Points"), py::arg("ParType"), py::arg("DegMin"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType, const Standard_Integer, const Standard_Integer>(), py::arg("Points"), py::arg("ParType"), py::arg("DegMin"), py::arg("DegMax"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape>(), py::arg("Points"), py::arg("ParType"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real>(), py::arg("Points"), py::arg("ParType"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &>(), py::arg("Points"), py::arg("Parameters"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &, const Standard_Integer>(), py::arg("Points"), py::arg("Parameters"), py::arg("DegMin"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &, const Standard_Integer, const Standard_Integer>(), py::arg("Points"), py::arg("Parameters"), py::arg("DegMin"), py::arg("DegMax"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape>(), py::arg("Points"), py::arg("Parameters"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real>(), py::arg("Points"), py::arg("Parameters"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Points"), py::arg("Weight1"), py::arg("Weight2"), py::arg("Weight3"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer>(), py::arg("Points"), py::arg("Weight1"), py::arg("Weight2"), py::arg("Weight3"), py::arg("DegMax"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const GeomAbs_Shape>(), py::arg("Points"), py::arg("Weight1"), py::arg("Weight2"), py::arg("Weight3"), py::arg("DegMax"), py::arg("Continuity"));
cls_Geom2dAPI_PointsToBSpline.def(py::init<const TColgp_Array1OfPnt2d &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const GeomAbs_Shape, const Standard_Real>(), py::arg("Points"), py::arg("Weight1"), py::arg("Weight2"), py::arg("Weight3"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol3D"));

// Methods
// cls_Geom2dAPI_PointsToBSpline.def_static("operator new_", (void * (*)(size_t)) &Geom2dAPI_PointsToBSpline::operator new, "None", py::arg("theSize"));
// cls_Geom2dAPI_PointsToBSpline.def_static("operator delete_", (void (*)(void *)) &Geom2dAPI_PointsToBSpline::operator delete, "None", py::arg("theAddress"));
// cls_Geom2dAPI_PointsToBSpline.def_static("operator new[]_", (void * (*)(size_t)) &Geom2dAPI_PointsToBSpline::operator new[], "None", py::arg("theSize"));
// cls_Geom2dAPI_PointsToBSpline.def_static("operator delete[]_", (void (*)(void *)) &Geom2dAPI_PointsToBSpline::operator delete[], "None", py::arg("theAddress"));
// cls_Geom2dAPI_PointsToBSpline.def_static("operator new_", (void * (*)(size_t, void *)) &Geom2dAPI_PointsToBSpline::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Geom2dAPI_PointsToBSpline.def_static("operator delete_", (void (*)(void *, void *)) &Geom2dAPI_PointsToBSpline::operator delete, "None", py::arg(""), py::arg(""));
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0) -> void { return self.Init(a0); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Integer a1) -> void { return self.Init(a0, a1); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Integer a1, const Standard_Integer a2) -> void { return self.Init(a0, a1, a2); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Integer a1, const Standard_Integer a2, const GeomAbs_Shape a3) -> void { return self.Init(a0, a1, a2, a3); });
cls_Geom2dAPI_PointsToBSpline.def("Init", (void (Geom2dAPI_PointsToBSpline::*)(const TColgp_Array1OfPnt2d &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real)) &Geom2dAPI_PointsToBSpline::Init, "Approximate a BSpline Curve passing through an array of Point. The resulting BSpline will have the following properties: 1- his degree will be in the range [Degmin,Degmax] 2- his continuity will be at least <Continuity> 3- the distance from the point <Points> to the BSpline will be lower to Tol2D", py::arg("Points"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColStd_Array1OfReal & a0, const Standard_Real a1, const Standard_Real a2) -> void { return self.Init(a0, a1, a2); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColStd_Array1OfReal & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Integer a3) -> void { return self.Init(a0, a1, a2, a3); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColStd_Array1OfReal & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Integer a3, const Standard_Integer a4) -> void { return self.Init(a0, a1, a2, a3, a4); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColStd_Array1OfReal & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Integer a3, const Standard_Integer a4, const GeomAbs_Shape a5) -> void { return self.Init(a0, a1, a2, a3, a4, a5); });
cls_Geom2dAPI_PointsToBSpline.def("Init", (void (Geom2dAPI_PointsToBSpline::*)(const TColStd_Array1OfReal &, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real)) &Geom2dAPI_PointsToBSpline::Init, "Approximate a BSpline Curve passing through an array of Point. Of coordinates :", py::arg("YValues"), py::arg("X0"), py::arg("DX"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Approx_ParametrizationType a1) -> void { return self.Init(a0, a1); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Approx_ParametrizationType a1, const Standard_Integer a2) -> void { return self.Init(a0, a1, a2); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Approx_ParametrizationType a1, const Standard_Integer a2, const Standard_Integer a3) -> void { return self.Init(a0, a1, a2, a3); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Approx_ParametrizationType a1, const Standard_Integer a2, const Standard_Integer a3, const GeomAbs_Shape a4) -> void { return self.Init(a0, a1, a2, a3, a4); });
cls_Geom2dAPI_PointsToBSpline.def("Init", (void (Geom2dAPI_PointsToBSpline::*)(const TColgp_Array1OfPnt2d &, const Approx_ParametrizationType, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real)) &Geom2dAPI_PointsToBSpline::Init, "Approximate a BSpline Curve passing through an array of Point. The resulting BSpline will have the following properties: 1- his degree will be in the range [Degmin,Degmax] 2- his continuity will be at least <Continuity> 3- the distance from the point <Points> to the BSpline will be lower to Tol2D", py::arg("Points"), py::arg("ParType"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const TColStd_Array1OfReal & a1) -> void { return self.Init(a0, a1); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const TColStd_Array1OfReal & a1, const Standard_Integer a2) -> void { return self.Init(a0, a1, a2); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const TColStd_Array1OfReal & a1, const Standard_Integer a2, const Standard_Integer a3) -> void { return self.Init(a0, a1, a2, a3); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const TColStd_Array1OfReal & a1, const Standard_Integer a2, const Standard_Integer a3, const GeomAbs_Shape a4) -> void { return self.Init(a0, a1, a2, a3, a4); });
cls_Geom2dAPI_PointsToBSpline.def("Init", (void (Geom2dAPI_PointsToBSpline::*)(const TColgp_Array1OfPnt2d &, const TColStd_Array1OfReal &, const Standard_Integer, const Standard_Integer, const GeomAbs_Shape, const Standard_Real)) &Geom2dAPI_PointsToBSpline::Init, "Approximate a BSpline Curve passing through an array of Point, which parameters are given by the array <Parameters>. The resulting BSpline will have the following properties: 1- his degree will be in the range [Degmin,Degmax] 2- his continuity will be at least <Continuity> 3- the distance from the point <Points> to the BSpline will be lower to Tol2D", py::arg("Points"), py::arg("Parameters"), py::arg("DegMin"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Real a3) -> void { return self.Init(a0, a1, a2, a3); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Real a3, const Standard_Integer a4) -> void { return self.Init(a0, a1, a2, a3, a4); });
cls_Geom2dAPI_PointsToBSpline.def("Init", [](Geom2dAPI_PointsToBSpline &self, const TColgp_Array1OfPnt2d & a0, const Standard_Real a1, const Standard_Real a2, const Standard_Real a3, const Standard_Integer a4, const GeomAbs_Shape a5) -> void { return self.Init(a0, a1, a2, a3, a4, a5); });
cls_Geom2dAPI_PointsToBSpline.def("Init", (void (Geom2dAPI_PointsToBSpline::*)(const TColgp_Array1OfPnt2d &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Integer, const GeomAbs_Shape, const Standard_Real)) &Geom2dAPI_PointsToBSpline::Init, "Approximate a BSpline Curve passing through an array of Point using variational smoothing algorithm, which tries to minimize additional criterium: Weight1*CurveLength + Weight2*Curvature + Weight3*Torsion", py::arg("Points"), py::arg("Weight1"), py::arg("Weight2"), py::arg("Weight3"), py::arg("DegMax"), py::arg("Continuity"), py::arg("Tol2D"));
cls_Geom2dAPI_PointsToBSpline.def("Curve", (const opencascade::handle<Geom2d_BSplineCurve> & (Geom2dAPI_PointsToBSpline::*)() const) &Geom2dAPI_PointsToBSpline::Curve, "Returns the approximate BSpline Curve");
cls_Geom2dAPI_PointsToBSpline.def("IsDone", (Standard_Boolean (Geom2dAPI_PointsToBSpline::*)() const) &Geom2dAPI_PointsToBSpline::IsDone, "None");

// CLASS: GEOM2DAPI_PROJECTPOINTONCURVE
py::class_<Geom2dAPI_ProjectPointOnCurve> cls_Geom2dAPI_ProjectPointOnCurve(mod, "Geom2dAPI_ProjectPointOnCurve", "This class implements methods for computing all the orthogonal projections of a 2D point onto a 2D curve.");

// Constructors
cls_Geom2dAPI_ProjectPointOnCurve.def(py::init<>());
cls_Geom2dAPI_ProjectPointOnCurve.def(py::init<const gp_Pnt2d &, const opencascade::handle<Geom2d_Curve> &>(), py::arg("P"), py::arg("Curve"));
cls_Geom2dAPI_ProjectPointOnCurve.def(py::init<const gp_Pnt2d &, const opencascade::handle<Geom2d_Curve> &, const Standard_Real, const Standard_Real>(), py::arg("P"), py::arg("Curve"), py::arg("Umin"), py::arg("Usup"));

// Methods
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator new_", (void * (*)(size_t)) &Geom2dAPI_ProjectPointOnCurve::operator new, "None", py::arg("theSize"));
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator delete_", (void (*)(void *)) &Geom2dAPI_ProjectPointOnCurve::operator delete, "None", py::arg("theAddress"));
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator new[]_", (void * (*)(size_t)) &Geom2dAPI_ProjectPointOnCurve::operator new[], "None", py::arg("theSize"));
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator delete[]_", (void (*)(void *)) &Geom2dAPI_ProjectPointOnCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Geom2dAPI_ProjectPointOnCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Geom2dAPI_ProjectPointOnCurve.def_static("operator delete_", (void (*)(void *, void *)) &Geom2dAPI_ProjectPointOnCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_Geom2dAPI_ProjectPointOnCurve.def("Init", (void (Geom2dAPI_ProjectPointOnCurve::*)(const gp_Pnt2d &, const opencascade::handle<Geom2d_Curve> &)) &Geom2dAPI_ProjectPointOnCurve::Init, "Initializes this algorithm with the given arguments, and computes the orthogonal projections of a point <P> on a curve <Curve>", py::arg("P"), py::arg("Curve"));
cls_Geom2dAPI_ProjectPointOnCurve.def("Init", (void (Geom2dAPI_ProjectPointOnCurve::*)(const gp_Pnt2d &, const opencascade::handle<Geom2d_Curve> &, const Standard_Real, const Standard_Real)) &Geom2dAPI_ProjectPointOnCurve::Init, "Initializes this algorithm with the given arguments, and computes the orthogonal projections of the point P onto the portion of the curve Curve limited by the two points of parameter Umin and Usup.", py::arg("P"), py::arg("Curve"), py::arg("Umin"), py::arg("Usup"));
cls_Geom2dAPI_ProjectPointOnCurve.def("NbPoints", (Standard_Integer (Geom2dAPI_ProjectPointOnCurve::*)() const) &Geom2dAPI_ProjectPointOnCurve::NbPoints, "return the number of of computed orthogonal projectionn points.");
cls_Geom2dAPI_ProjectPointOnCurve.def("Point", (gp_Pnt2d (Geom2dAPI_ProjectPointOnCurve::*)(const Standard_Integer) const) &Geom2dAPI_ProjectPointOnCurve::Point, "Returns the orthogonal projection on the curve. Index is a number of a computed point. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where NbPoints is the number of solution points.", py::arg("Index"));
cls_Geom2dAPI_ProjectPointOnCurve.def("Parameter", (Standard_Real (Geom2dAPI_ProjectPointOnCurve::*)(const Standard_Integer) const) &Geom2dAPI_ProjectPointOnCurve::Parameter, "Returns the parameter on the curve of a point which is the orthogonal projection. Index is a number of a computed projected point. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where NbPoints is the number of solution points.", py::arg("Index"));
cls_Geom2dAPI_ProjectPointOnCurve.def("Parameter", [](Geom2dAPI_ProjectPointOnCurve &self, const Standard_Integer Index, Standard_Real & U){ self.Parameter(Index, U); return U; }, "Returns the parameter on the curve of a point which is the orthogonal projection. Index is a number of a computed projected point. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where NbPoints is the number of solution points", py::arg("Index"), py::arg("U"));
cls_Geom2dAPI_ProjectPointOnCurve.def("Distance", (Standard_Real (Geom2dAPI_ProjectPointOnCurve::*)(const Standard_Integer) const) &Geom2dAPI_ProjectPointOnCurve::Distance, "Computes the distance between the point and its computed orthogonal projection on the curve. Index is a number of computed projected point. Exceptions Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where NbPoints is the number of solution points.", py::arg("Index"));
cls_Geom2dAPI_ProjectPointOnCurve.def("NearestPoint", (gp_Pnt2d (Geom2dAPI_ProjectPointOnCurve::*)() const) &Geom2dAPI_ProjectPointOnCurve::NearestPoint, "Returns the nearest orthogonal projection of the point on the curve. Exceptions StdFail_NotDone if this algorithm fails.");
cls_Geom2dAPI_ProjectPointOnCurve.def("LowerDistanceParameter", (Standard_Real (Geom2dAPI_ProjectPointOnCurve::*)() const) &Geom2dAPI_ProjectPointOnCurve::LowerDistanceParameter, "Returns the parameter on the curve of the nearest orthogonal projection of the point. Exceptions StdFail_NotDone if this algorithm fails.");
cls_Geom2dAPI_ProjectPointOnCurve.def("LowerDistance", (Standard_Real (Geom2dAPI_ProjectPointOnCurve::*)() const) &Geom2dAPI_ProjectPointOnCurve::LowerDistance, "Computes the distance between the point and its nearest orthogonal projection on the curve. Exceptions StdFail_NotDone if this algorithm fails.");
cls_Geom2dAPI_ProjectPointOnCurve.def("Extrema", (const Extrema_ExtPC2d & (Geom2dAPI_ProjectPointOnCurve::*)() const) &Geom2dAPI_ProjectPointOnCurve::Extrema, "return the algorithmic object from Extrema");


}
