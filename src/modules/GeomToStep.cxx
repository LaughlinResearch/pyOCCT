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
#include <Standard_TypeDef.hxx>
#include <GeomToStep_Root.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2d.hxx>
#include <Standard_Handle.hxx>
#include <Geom_Axis1Placement.hxx>
#include <Geom2d_AxisPlacement.hxx>
#include <StepGeom_Axis1Placement.hxx>
#include <GeomToStep_MakeAxis1Placement.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax22d.hxx>
#include <StepGeom_Axis2Placement2d.hxx>
#include <GeomToStep_MakeAxis2Placement2d.hxx>
#include <gp_Ax3.hxx>
#include <gp_Trsf.hxx>
#include <Geom_Axis2Placement.hxx>
#include <StepGeom_Axis2Placement3d.hxx>
#include <GeomToStep_MakeAxis2Placement3d.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <StepGeom_BoundedCurve.hxx>
#include <GeomToStep_MakeBoundedCurve.hxx>
#include <Geom_BoundedSurface.hxx>
#include <StepGeom_BoundedSurface.hxx>
#include <GeomToStep_MakeBoundedSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <StepGeom_BSplineCurveWithKnots.hxx>
#include <GeomToStep_MakeBSplineCurveWithKnots.hxx>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hxx>
#include <GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <StepGeom_BSplineSurfaceWithKnots.hxx>
#include <GeomToStep_MakeBSplineSurfaceWithKnots.hxx>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hxx>
#include <GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <GeomToStep_MakeCartesianPoint.hxx>
#include <gp_Circ.hxx>
#include <Geom_Circle.hxx>
#include <Geom2d_Circle.hxx>
#include <StepGeom_Circle.hxx>
#include <GeomToStep_MakeCircle.hxx>
#include <Geom_Conic.hxx>
#include <Geom2d_Conic.hxx>
#include <StepGeom_Conic.hxx>
#include <GeomToStep_MakeConic.hxx>
#include <Geom_ConicalSurface.hxx>
#include <StepGeom_ConicalSurface.hxx>
#include <GeomToStep_MakeConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <StepGeom_Curve.hxx>
#include <GeomToStep_MakeCurve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <StepGeom_CylindricalSurface.hxx>
#include <GeomToStep_MakeCylindricalSurface.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <Geom_Direction.hxx>
#include <Geom2d_Direction.hxx>
#include <StepGeom_Direction.hxx>
#include <GeomToStep_MakeDirection.hxx>
#include <Geom_ElementarySurface.hxx>
#include <StepGeom_ElementarySurface.hxx>
#include <GeomToStep_MakeElementarySurface.hxx>
#include <gp_Elips.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom2d_Ellipse.hxx>
#include <StepGeom_Ellipse.hxx>
#include <GeomToStep_MakeEllipse.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom_Hyperbola.hxx>
#include <StepGeom_Hyperbola.hxx>
#include <GeomToStep_MakeHyperbola.hxx>
#include <gp_Lin.hxx>
#include <gp_Lin2d.hxx>
#include <Geom_Line.hxx>
#include <Geom2d_Line.hxx>
#include <StepGeom_Line.hxx>
#include <GeomToStep_MakeLine.hxx>
#include <Geom2d_Parabola.hxx>
#include <Geom_Parabola.hxx>
#include <StepGeom_Parabola.hxx>
#include <GeomToStep_MakeParabola.hxx>
#include <gp_Pln.hxx>
#include <Geom_Plane.hxx>
#include <StepGeom_Plane.hxx>
#include <GeomToStep_MakePlane.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <StepGeom_Polyline.hxx>
#include <GeomToStep_MakePolyline.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <StepGeom_RectangularTrimmedSurface.hxx>
#include <GeomToStep_MakeRectangularTrimmedSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <StepGeom_SphericalSurface.hxx>
#include <GeomToStep_MakeSphericalSurface.hxx>
#include <Geom_Surface.hxx>
#include <StepGeom_Surface.hxx>
#include <GeomToStep_MakeSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <StepGeom_SurfaceOfLinearExtrusion.hxx>
#include <GeomToStep_MakeSurfaceOfLinearExtrusion.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <StepGeom_SurfaceOfRevolution.hxx>
#include <GeomToStep_MakeSurfaceOfRevolution.hxx>
#include <Geom_SweptSurface.hxx>
#include <StepGeom_SweptSurface.hxx>
#include <GeomToStep_MakeSweptSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <StepGeom_ToroidalSurface.hxx>
#include <GeomToStep_MakeToroidalSurface.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <Geom_Vector.hxx>
#include <Geom2d_Vector.hxx>
#include <StepGeom_Vector.hxx>
#include <GeomToStep_MakeVector.hxx>

PYBIND11_MODULE(GeomToStep, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.gp");
py::module::import("OCCT.Geom");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.StepGeom");
py::module::import("OCCT.TColgp");

// CLASS: GEOMTOSTEP_ROOT
py::class_<GeomToStep_Root> cls_GeomToStep_Root(mod, "GeomToStep_Root", "This class implements the common services for all classes of GeomToStep which report error.");

// Methods
// cls_GeomToStep_Root.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_Root::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_Root.def_static("operator delete_", (void (*)(void *)) &GeomToStep_Root::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_Root.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_Root::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_Root.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_Root::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_Root.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_Root::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_Root.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_Root::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_Root.def("IsDone", (Standard_Boolean (GeomToStep_Root::*)() const) &GeomToStep_Root::IsDone, "None");

// CLASS: GEOMTOSTEP_MAKEAXIS1PLACEMENT
py::class_<GeomToStep_MakeAxis1Placement, GeomToStep_Root> cls_GeomToStep_MakeAxis1Placement(mod, "GeomToStep_MakeAxis1Placement", "This class implements the mapping between classes Axis1Placement from Geom and Ax1 from gp, and the class Axis1Placement from StepGeom which describes an Axis1Placement from Prostep.");

// Constructors
cls_GeomToStep_MakeAxis1Placement.def(py::init<const gp_Ax1 &>(), py::arg("A"));
cls_GeomToStep_MakeAxis1Placement.def(py::init<const gp_Ax2d &>(), py::arg("A"));
cls_GeomToStep_MakeAxis1Placement.def(py::init<const opencascade::handle<Geom_Axis1Placement> &>(), py::arg("A"));
cls_GeomToStep_MakeAxis1Placement.def(py::init<const opencascade::handle<Geom2d_AxisPlacement> &>(), py::arg("A"));

// Methods
// cls_GeomToStep_MakeAxis1Placement.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeAxis1Placement::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis1Placement.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeAxis1Placement::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis1Placement.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeAxis1Placement::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis1Placement.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeAxis1Placement::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis1Placement.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeAxis1Placement::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeAxis1Placement.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeAxis1Placement::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeAxis1Placement.def("Value", (const opencascade::handle<StepGeom_Axis1Placement> & (GeomToStep_MakeAxis1Placement::*)() const) &GeomToStep_MakeAxis1Placement::Value, "None");

// CLASS: GEOMTOSTEP_MAKEAXIS2PLACEMENT2D
py::class_<GeomToStep_MakeAxis2Placement2d, GeomToStep_Root> cls_GeomToStep_MakeAxis2Placement2d(mod, "GeomToStep_MakeAxis2Placement2d", "This class implements the mapping between classes Axis2Placement from Geom and Ax2, Ax22d from gp, and the class Axis2Placement2d from StepGeom which describes an axis2_placement_2d from Prostep.");

// Constructors
cls_GeomToStep_MakeAxis2Placement2d.def(py::init<const gp_Ax2 &>(), py::arg("A"));
cls_GeomToStep_MakeAxis2Placement2d.def(py::init<const gp_Ax22d &>(), py::arg("A"));

// Methods
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeAxis2Placement2d::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeAxis2Placement2d::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeAxis2Placement2d::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeAxis2Placement2d::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeAxis2Placement2d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement2d.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeAxis2Placement2d::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeAxis2Placement2d.def("Value", (const opencascade::handle<StepGeom_Axis2Placement2d> & (GeomToStep_MakeAxis2Placement2d::*)() const) &GeomToStep_MakeAxis2Placement2d::Value, "None");

// CLASS: GEOMTOSTEP_MAKEAXIS2PLACEMENT3D
py::class_<GeomToStep_MakeAxis2Placement3d, GeomToStep_Root> cls_GeomToStep_MakeAxis2Placement3d(mod, "GeomToStep_MakeAxis2Placement3d", "This class implements the mapping between classes Axis2Placement from Geom and Ax2, Ax3 from gp, and the class Axis2Placement3d from StepGeom which describes an axis2_placement_3d from Prostep.");

// Constructors
cls_GeomToStep_MakeAxis2Placement3d.def(py::init<>());
cls_GeomToStep_MakeAxis2Placement3d.def(py::init<const gp_Ax2 &>(), py::arg("A"));
cls_GeomToStep_MakeAxis2Placement3d.def(py::init<const gp_Ax3 &>(), py::arg("A"));
cls_GeomToStep_MakeAxis2Placement3d.def(py::init<const gp_Trsf &>(), py::arg("T"));
cls_GeomToStep_MakeAxis2Placement3d.def(py::init<const opencascade::handle<Geom_Axis2Placement> &>(), py::arg("A"));

// Methods
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeAxis2Placement3d::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeAxis2Placement3d::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeAxis2Placement3d::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeAxis2Placement3d::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeAxis2Placement3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeAxis2Placement3d.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeAxis2Placement3d::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeAxis2Placement3d.def("Value", (const opencascade::handle<StepGeom_Axis2Placement3d> & (GeomToStep_MakeAxis2Placement3d::*)() const) &GeomToStep_MakeAxis2Placement3d::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBOUNDEDCURVE
py::class_<GeomToStep_MakeBoundedCurve, GeomToStep_Root> cls_GeomToStep_MakeBoundedCurve(mod, "GeomToStep_MakeBoundedCurve", "This class implements the mapping between classes BoundedCurve from Geom, Geom2d and the class BoundedCurve from StepGeom which describes a BoundedCurve from prostep. As BoundedCurve is an abstract BoundedCurve this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeBoundedCurve.def(py::init<const opencascade::handle<Geom_BoundedCurve> &>(), py::arg("C"));
cls_GeomToStep_MakeBoundedCurve.def(py::init<const opencascade::handle<Geom2d_BoundedCurve> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeBoundedCurve.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBoundedCurve::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBoundedCurve.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBoundedCurve::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedCurve.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBoundedCurve::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBoundedCurve.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBoundedCurve::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedCurve.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBoundedCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedCurve.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBoundedCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBoundedCurve.def("Value", (const opencascade::handle<StepGeom_BoundedCurve> & (GeomToStep_MakeBoundedCurve::*)() const) &GeomToStep_MakeBoundedCurve::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBOUNDEDSURFACE
py::class_<GeomToStep_MakeBoundedSurface, GeomToStep_Root> cls_GeomToStep_MakeBoundedSurface(mod, "GeomToStep_MakeBoundedSurface", "This class implements the mapping between classes BoundedSurface from Geom and the class BoundedSurface from StepGeom which describes a BoundedSurface from prostep. As BoundedSurface is an abstract BoundedSurface this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeBoundedSurface.def(py::init<const opencascade::handle<Geom_BoundedSurface> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeBoundedSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBoundedSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBoundedSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBoundedSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBoundedSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBoundedSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBoundedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBoundedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBoundedSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBoundedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBoundedSurface.def("Value", (const opencascade::handle<StepGeom_BoundedSurface> & (GeomToStep_MakeBoundedSurface::*)() const) &GeomToStep_MakeBoundedSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBSPLINECURVEWITHKNOTS
py::class_<GeomToStep_MakeBSplineCurveWithKnots, GeomToStep_Root> cls_GeomToStep_MakeBSplineCurveWithKnots(mod, "GeomToStep_MakeBSplineCurveWithKnots", "This class implements the mapping between classes BSplineCurve from Geom, Geom2d and the class BSplineCurveWithKnots from StepGeom which describes a bspline_curve_with_knots from Prostep");

// Constructors
cls_GeomToStep_MakeBSplineCurveWithKnots.def(py::init<const opencascade::handle<Geom_BSplineCurve> &>(), py::arg("Bsplin"));
cls_GeomToStep_MakeBSplineCurveWithKnots.def(py::init<const opencascade::handle<Geom2d_BSplineCurve> &>(), py::arg("Bsplin"));

// Methods
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBSplineCurveWithKnots::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBSplineCurveWithKnots::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBSplineCurveWithKnots::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBSplineCurveWithKnots::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBSplineCurveWithKnots::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnots.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBSplineCurveWithKnots::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBSplineCurveWithKnots.def("Value", (const opencascade::handle<StepGeom_BSplineCurveWithKnots> & (GeomToStep_MakeBSplineCurveWithKnots::*)() const) &GeomToStep_MakeBSplineCurveWithKnots::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBSPLINECURVEWITHKNOTSANDRATIONALBSPLINECURVE
py::class_<GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve, GeomToStep_Root> cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve(mod, "GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve", "This class implements the mapping between classes BSplineCurve from Geom, Geom2d and the class BSplineCurveWithKnotsAndRationalBSplineCurve from StepGeom which describes a rational_bspline_curve_with_knots from Prostep");

// Constructors
cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def(py::init<const opencascade::handle<Geom_BSplineCurve> &>(), py::arg("Bsplin"));
cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def(py::init<const opencascade::handle<Geom2d_BSplineCurve> &>(), py::arg("Bsplin"));

// Methods
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.def("Value", (const opencascade::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> & (GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::*)() const) &GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBSPLINESURFACEWITHKNOTS
py::class_<GeomToStep_MakeBSplineSurfaceWithKnots, GeomToStep_Root> cls_GeomToStep_MakeBSplineSurfaceWithKnots(mod, "GeomToStep_MakeBSplineSurfaceWithKnots", "This class implements the mapping between class BSplineSurface from Geom and the class BSplineSurfaceWithKnots from StepGeom which describes a bspline_Surface_with_knots from Prostep");

// Constructors
cls_GeomToStep_MakeBSplineSurfaceWithKnots.def(py::init<const opencascade::handle<Geom_BSplineSurface> &>(), py::arg("Bsplin"));

// Methods
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnots.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBSplineSurfaceWithKnots::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBSplineSurfaceWithKnots.def("Value", (const opencascade::handle<StepGeom_BSplineSurfaceWithKnots> & (GeomToStep_MakeBSplineSurfaceWithKnots::*)() const) &GeomToStep_MakeBSplineSurfaceWithKnots::Value, "None");

// CLASS: GEOMTOSTEP_MAKEBSPLINESURFACEWITHKNOTSANDRATIONALBSPLINESURFACE
py::class_<GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface, GeomToStep_Root> cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface(mod, "GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface", "This class implements the mapping between class BSplineSurface from Geom and the class BSplineSurfaceWithKnotsAndRationalBSplineSurface from StepGeom which describes a rational_bspline_Surface_with_knots from Prostep");

// Constructors
cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def(py::init<const opencascade::handle<Geom_BSplineSurface> &>(), py::arg("Bsplin"));

// Methods
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.def("Value", (const opencascade::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> & (GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::*)() const) &GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKECARTESIANPOINT
py::class_<GeomToStep_MakeCartesianPoint, GeomToStep_Root> cls_GeomToStep_MakeCartesianPoint(mod, "GeomToStep_MakeCartesianPoint", "This class implements the mapping between classes CartesianPoint from Geom and Pnt from gp, and the class CartesianPoint from StepGeom which describes a point from Prostep.");

// Constructors
cls_GeomToStep_MakeCartesianPoint.def(py::init<const gp_Pnt &>(), py::arg("P"));
cls_GeomToStep_MakeCartesianPoint.def(py::init<const gp_Pnt2d &>(), py::arg("P"));
cls_GeomToStep_MakeCartesianPoint.def(py::init<const opencascade::handle<Geom_CartesianPoint> &>(), py::arg("P"));
cls_GeomToStep_MakeCartesianPoint.def(py::init<const opencascade::handle<Geom2d_CartesianPoint> &>(), py::arg("P"));

// Methods
// cls_GeomToStep_MakeCartesianPoint.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeCartesianPoint::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeCartesianPoint.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeCartesianPoint::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCartesianPoint.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeCartesianPoint::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeCartesianPoint.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeCartesianPoint::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCartesianPoint.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeCartesianPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeCartesianPoint.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeCartesianPoint::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeCartesianPoint.def("Value", (const opencascade::handle<StepGeom_CartesianPoint> & (GeomToStep_MakeCartesianPoint::*)() const) &GeomToStep_MakeCartesianPoint::Value, "None");

// CLASS: GEOMTOSTEP_MAKECIRCLE
py::class_<GeomToStep_MakeCircle, GeomToStep_Root> cls_GeomToStep_MakeCircle(mod, "GeomToStep_MakeCircle", "This class implements the mapping between classes Circle from Geom, and Circ from gp, and the class Circle from StepGeom which describes a circle from Prostep.");

// Constructors
cls_GeomToStep_MakeCircle.def(py::init<const gp_Circ &>(), py::arg("C"));
cls_GeomToStep_MakeCircle.def(py::init<const opencascade::handle<Geom_Circle> &>(), py::arg("C"));
cls_GeomToStep_MakeCircle.def(py::init<const opencascade::handle<Geom2d_Circle> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeCircle.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeCircle::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeCircle.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeCircle::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCircle.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeCircle::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeCircle.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeCircle::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCircle.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeCircle::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeCircle.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeCircle::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeCircle.def("Value", (const opencascade::handle<StepGeom_Circle> & (GeomToStep_MakeCircle::*)() const) &GeomToStep_MakeCircle::Value, "None");

// CLASS: GEOMTOSTEP_MAKECONIC
py::class_<GeomToStep_MakeConic, GeomToStep_Root> cls_GeomToStep_MakeConic(mod, "GeomToStep_MakeConic", "This class implements the mapping between classes Conic from Geom and the class Conic from StepGeom which describes a Conic from prostep. As Conic is an abstract Conic this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeConic.def(py::init<const opencascade::handle<Geom_Conic> &>(), py::arg("C"));
cls_GeomToStep_MakeConic.def(py::init<const opencascade::handle<Geom2d_Conic> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeConic.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeConic::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeConic.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeConic::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeConic.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeConic::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeConic.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeConic::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeConic.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeConic::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeConic.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeConic::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeConic.def("Value", (const opencascade::handle<StepGeom_Conic> & (GeomToStep_MakeConic::*)() const) &GeomToStep_MakeConic::Value, "None");

// CLASS: GEOMTOSTEP_MAKECONICALSURFACE
py::class_<GeomToStep_MakeConicalSurface, GeomToStep_Root> cls_GeomToStep_MakeConicalSurface(mod, "GeomToStep_MakeConicalSurface", "This class implements the mapping between class ConicalSurface from Geom and the class ConicalSurface from StepGeom which describes a conical_surface from Prostep");

// Constructors
cls_GeomToStep_MakeConicalSurface.def(py::init<const opencascade::handle<Geom_ConicalSurface> &>(), py::arg("CSurf"));

// Methods
// cls_GeomToStep_MakeConicalSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeConicalSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeConicalSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeConicalSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeConicalSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeConicalSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeConicalSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeConicalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeConicalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeConicalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeConicalSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeConicalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeConicalSurface.def("Value", (const opencascade::handle<StepGeom_ConicalSurface> & (GeomToStep_MakeConicalSurface::*)() const) &GeomToStep_MakeConicalSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKECURVE
py::class_<GeomToStep_MakeCurve, GeomToStep_Root> cls_GeomToStep_MakeCurve(mod, "GeomToStep_MakeCurve", "This class implements the mapping between classes Curve from Geom and the class Curve from StepGeom which describes a Curve from prostep. As Curve is an abstract curve this class an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeCurve.def(py::init<const opencascade::handle<Geom_Curve> &>(), py::arg("C"));
cls_GeomToStep_MakeCurve.def(py::init<const opencascade::handle<Geom2d_Curve> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeCurve.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeCurve::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeCurve.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeCurve::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCurve.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeCurve::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeCurve.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeCurve::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCurve.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeCurve.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeCurve.def("Value", (const opencascade::handle<StepGeom_Curve> & (GeomToStep_MakeCurve::*)() const) &GeomToStep_MakeCurve::Value, "None");

// CLASS: GEOMTOSTEP_MAKECYLINDRICALSURFACE
py::class_<GeomToStep_MakeCylindricalSurface, GeomToStep_Root> cls_GeomToStep_MakeCylindricalSurface(mod, "GeomToStep_MakeCylindricalSurface", "This class implements the mapping between class CylindricalSurface from Geom and the class CylindricalSurface from StepGeom which describes a cylindrical_surface from Prostep");

// Constructors
cls_GeomToStep_MakeCylindricalSurface.def(py::init<const opencascade::handle<Geom_CylindricalSurface> &>(), py::arg("CSurf"));

// Methods
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeCylindricalSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeCylindricalSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeCylindricalSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeCylindricalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeCylindricalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeCylindricalSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeCylindricalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeCylindricalSurface.def("Value", (const opencascade::handle<StepGeom_CylindricalSurface> & (GeomToStep_MakeCylindricalSurface::*)() const) &GeomToStep_MakeCylindricalSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKEDIRECTION
py::class_<GeomToStep_MakeDirection, GeomToStep_Root> cls_GeomToStep_MakeDirection(mod, "GeomToStep_MakeDirection", "This class implements the mapping between classes Direction from Geom, Geom2d and Dir, Dir2d from gp, and the class Direction from StepGeom which describes a direction from Prostep.");

// Constructors
cls_GeomToStep_MakeDirection.def(py::init<const gp_Dir &>(), py::arg("D"));
cls_GeomToStep_MakeDirection.def(py::init<const gp_Dir2d &>(), py::arg("D"));
cls_GeomToStep_MakeDirection.def(py::init<const opencascade::handle<Geom_Direction> &>(), py::arg("D"));
cls_GeomToStep_MakeDirection.def(py::init<const opencascade::handle<Geom2d_Direction> &>(), py::arg("D"));

// Methods
// cls_GeomToStep_MakeDirection.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeDirection::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeDirection.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeDirection::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeDirection.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeDirection::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeDirection.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeDirection::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeDirection.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeDirection::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeDirection.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeDirection::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeDirection.def("Value", (const opencascade::handle<StepGeom_Direction> & (GeomToStep_MakeDirection::*)() const) &GeomToStep_MakeDirection::Value, "None");

// CLASS: GEOMTOSTEP_MAKEELEMENTARYSURFACE
py::class_<GeomToStep_MakeElementarySurface, GeomToStep_Root> cls_GeomToStep_MakeElementarySurface(mod, "GeomToStep_MakeElementarySurface", "This class implements the mapping between classes ElementarySurface from Geom and the class ElementarySurface from StepGeom which describes a ElementarySurface from prostep. As ElementarySurface is an abstract Surface this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeElementarySurface.def(py::init<const opencascade::handle<Geom_ElementarySurface> &>(), py::arg("S"));

// Methods
// cls_GeomToStep_MakeElementarySurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeElementarySurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeElementarySurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeElementarySurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeElementarySurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeElementarySurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeElementarySurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeElementarySurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeElementarySurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeElementarySurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeElementarySurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeElementarySurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeElementarySurface.def("Value", (const opencascade::handle<StepGeom_ElementarySurface> & (GeomToStep_MakeElementarySurface::*)() const) &GeomToStep_MakeElementarySurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKEELLIPSE
py::class_<GeomToStep_MakeEllipse, GeomToStep_Root> cls_GeomToStep_MakeEllipse(mod, "GeomToStep_MakeEllipse", "This class implements the mapping between classes Ellipse from Geom, and Circ from gp, and the class Ellipse from StepGeom which describes a Ellipse from Prostep.");

// Constructors
cls_GeomToStep_MakeEllipse.def(py::init<const gp_Elips &>(), py::arg("C"));
cls_GeomToStep_MakeEllipse.def(py::init<const opencascade::handle<Geom_Ellipse> &>(), py::arg("C"));
cls_GeomToStep_MakeEllipse.def(py::init<const opencascade::handle<Geom2d_Ellipse> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeEllipse.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeEllipse::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeEllipse.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeEllipse::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeEllipse.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeEllipse::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeEllipse.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeEllipse::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeEllipse.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeEllipse::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeEllipse.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeEllipse::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeEllipse.def("Value", (const opencascade::handle<StepGeom_Ellipse> & (GeomToStep_MakeEllipse::*)() const) &GeomToStep_MakeEllipse::Value, "None");

// CLASS: GEOMTOSTEP_MAKEHYPERBOLA
py::class_<GeomToStep_MakeHyperbola, GeomToStep_Root> cls_GeomToStep_MakeHyperbola(mod, "GeomToStep_MakeHyperbola", "This class implements the mapping between the class Hyperbola from Geom and the class Hyperbola from StepGeom which describes a Hyperbola from ProSTEP");

// Constructors
cls_GeomToStep_MakeHyperbola.def(py::init<const opencascade::handle<Geom2d_Hyperbola> &>(), py::arg("C"));
cls_GeomToStep_MakeHyperbola.def(py::init<const opencascade::handle<Geom_Hyperbola> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeHyperbola.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeHyperbola::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeHyperbola.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeHyperbola::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeHyperbola.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeHyperbola::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeHyperbola.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeHyperbola::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeHyperbola.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeHyperbola::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeHyperbola.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeHyperbola::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeHyperbola.def("Value", (const opencascade::handle<StepGeom_Hyperbola> & (GeomToStep_MakeHyperbola::*)() const) &GeomToStep_MakeHyperbola::Value, "None");

// CLASS: GEOMTOSTEP_MAKELINE
py::class_<GeomToStep_MakeLine, GeomToStep_Root> cls_GeomToStep_MakeLine(mod, "GeomToStep_MakeLine", "This class implements the mapping between classes Line from Geom and Lin from gp, and the class Line from StepGeom which describes a line from Prostep.");

// Constructors
cls_GeomToStep_MakeLine.def(py::init<const gp_Lin &>(), py::arg("L"));
cls_GeomToStep_MakeLine.def(py::init<const gp_Lin2d &>(), py::arg("L"));
cls_GeomToStep_MakeLine.def(py::init<const opencascade::handle<Geom_Line> &>(), py::arg("C"));
cls_GeomToStep_MakeLine.def(py::init<const opencascade::handle<Geom2d_Line> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeLine.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeLine::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeLine.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeLine::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeLine.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeLine::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeLine.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeLine::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeLine.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeLine::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeLine.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeLine::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeLine.def("Value", (const opencascade::handle<StepGeom_Line> & (GeomToStep_MakeLine::*)() const) &GeomToStep_MakeLine::Value, "None");

// CLASS: GEOMTOSTEP_MAKEPARABOLA
py::class_<GeomToStep_MakeParabola, GeomToStep_Root> cls_GeomToStep_MakeParabola(mod, "GeomToStep_MakeParabola", "This class implements the mapping between the class Parabola from Geom and the class Parabola from StepGeom which describes a Parabola from ProSTEP");

// Constructors
cls_GeomToStep_MakeParabola.def(py::init<const opencascade::handle<Geom2d_Parabola> &>(), py::arg("C"));
cls_GeomToStep_MakeParabola.def(py::init<const opencascade::handle<Geom_Parabola> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeParabola.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeParabola::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeParabola.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeParabola::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeParabola.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeParabola::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeParabola.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeParabola::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeParabola.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeParabola::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeParabola.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeParabola::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeParabola.def("Value", (const opencascade::handle<StepGeom_Parabola> & (GeomToStep_MakeParabola::*)() const) &GeomToStep_MakeParabola::Value, "None");

// CLASS: GEOMTOSTEP_MAKEPLANE
py::class_<GeomToStep_MakePlane, GeomToStep_Root> cls_GeomToStep_MakePlane(mod, "GeomToStep_MakePlane", "This class implements the mapping between classes Plane from Geom and Pln from gp, and the class Plane from StepGeom which describes a plane from Prostep.");

// Constructors
cls_GeomToStep_MakePlane.def(py::init<const gp_Pln &>(), py::arg("P"));
cls_GeomToStep_MakePlane.def(py::init<const opencascade::handle<Geom_Plane> &>(), py::arg("P"));

// Methods
// cls_GeomToStep_MakePlane.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakePlane::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakePlane.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakePlane::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakePlane.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakePlane::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakePlane.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakePlane::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakePlane.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakePlane::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakePlane.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakePlane::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakePlane.def("Value", (const opencascade::handle<StepGeom_Plane> & (GeomToStep_MakePlane::*)() const) &GeomToStep_MakePlane::Value, "None");

// CLASS: GEOMTOSTEP_MAKEPOLYLINE
py::class_<GeomToStep_MakePolyline, GeomToStep_Root> cls_GeomToStep_MakePolyline(mod, "GeomToStep_MakePolyline", "This class implements the mapping between an Array1 of points from gp and a Polyline from StepGeom.");

// Constructors
cls_GeomToStep_MakePolyline.def(py::init<const TColgp_Array1OfPnt &>(), py::arg("P"));
cls_GeomToStep_MakePolyline.def(py::init<const TColgp_Array1OfPnt2d &>(), py::arg("P"));

// Methods
// cls_GeomToStep_MakePolyline.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakePolyline::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakePolyline.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakePolyline::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakePolyline.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakePolyline::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakePolyline.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakePolyline::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakePolyline.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakePolyline::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakePolyline.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakePolyline::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakePolyline.def("Value", (const opencascade::handle<StepGeom_Polyline> & (GeomToStep_MakePolyline::*)() const) &GeomToStep_MakePolyline::Value, "None");

// CLASS: GEOMTOSTEP_MAKERECTANGULARTRIMMEDSURFACE
py::class_<GeomToStep_MakeRectangularTrimmedSurface, GeomToStep_Root> cls_GeomToStep_MakeRectangularTrimmedSurface(mod, "GeomToStep_MakeRectangularTrimmedSurface", "This class implements the mapping between class RectangularTrimmedSurface from Geom and the class RectangularTrimmedSurface from StepGeom which describes a rectangular_trimmed_surface from ISO-IS 10303-42");

// Constructors
cls_GeomToStep_MakeRectangularTrimmedSurface.def(py::init<const opencascade::handle<Geom_RectangularTrimmedSurface> &>(), py::arg("RTSurf"));

// Methods
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeRectangularTrimmedSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeRectangularTrimmedSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeRectangularTrimmedSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeRectangularTrimmedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeRectangularTrimmedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeRectangularTrimmedSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeRectangularTrimmedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeRectangularTrimmedSurface.def("Value", (const opencascade::handle<StepGeom_RectangularTrimmedSurface> & (GeomToStep_MakeRectangularTrimmedSurface::*)() const) &GeomToStep_MakeRectangularTrimmedSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKESPHERICALSURFACE
py::class_<GeomToStep_MakeSphericalSurface, GeomToStep_Root> cls_GeomToStep_MakeSphericalSurface(mod, "GeomToStep_MakeSphericalSurface", "This class implements the mapping between class SphericalSurface from Geom and the class SphericalSurface from StepGeom which describes a spherical_surface from Prostep");

// Constructors
cls_GeomToStep_MakeSphericalSurface.def(py::init<const opencascade::handle<Geom_SphericalSurface> &>(), py::arg("CSurf"));

// Methods
// cls_GeomToStep_MakeSphericalSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeSphericalSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeSphericalSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeSphericalSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSphericalSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeSphericalSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeSphericalSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeSphericalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSphericalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeSphericalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeSphericalSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeSphericalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeSphericalSurface.def("Value", (const opencascade::handle<StepGeom_SphericalSurface> & (GeomToStep_MakeSphericalSurface::*)() const) &GeomToStep_MakeSphericalSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKESURFACE
py::class_<GeomToStep_MakeSurface, GeomToStep_Root> cls_GeomToStep_MakeSurface(mod, "GeomToStep_MakeSurface", "This class implements the mapping between classes Surface from Geom and the class Surface from StepGeom which describes a Surface from prostep. As Surface is an abstract Surface this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeSurface.def(py::init<const opencascade::handle<Geom_Surface> &>(), py::arg("C"));

// Methods
// cls_GeomToStep_MakeSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeSurface.def("Value", (const opencascade::handle<StepGeom_Surface> & (GeomToStep_MakeSurface::*)() const) &GeomToStep_MakeSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKESURFACEOFLINEAREXTRUSION
py::class_<GeomToStep_MakeSurfaceOfLinearExtrusion, GeomToStep_Root> cls_GeomToStep_MakeSurfaceOfLinearExtrusion(mod, "GeomToStep_MakeSurfaceOfLinearExtrusion", "This class implements the mapping between class SurfaceOfLinearExtrusion from Geom and the class SurfaceOfLinearExtrusion from StepGeom which describes a surface_of_linear_extrusion from Prostep");

// Constructors
cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def(py::init<const opencascade::handle<Geom_SurfaceOfLinearExtrusion> &>(), py::arg("CSurf"));

// Methods
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeSurfaceOfLinearExtrusion::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeSurfaceOfLinearExtrusion.def("Value", (const opencascade::handle<StepGeom_SurfaceOfLinearExtrusion> & (GeomToStep_MakeSurfaceOfLinearExtrusion::*)() const) &GeomToStep_MakeSurfaceOfLinearExtrusion::Value, "None");

// CLASS: GEOMTOSTEP_MAKESURFACEOFREVOLUTION
py::class_<GeomToStep_MakeSurfaceOfRevolution, GeomToStep_Root> cls_GeomToStep_MakeSurfaceOfRevolution(mod, "GeomToStep_MakeSurfaceOfRevolution", "This class implements the mapping between class SurfaceOfRevolution from Geom and the class SurfaceOfRevolution from StepGeom which describes a surface_of_revolution from Prostep");

// Constructors
cls_GeomToStep_MakeSurfaceOfRevolution.def(py::init<const opencascade::handle<Geom_SurfaceOfRevolution> &>(), py::arg("RevSurf"));

// Methods
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeSurfaceOfRevolution::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeSurfaceOfRevolution::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeSurfaceOfRevolution::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeSurfaceOfRevolution::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeSurfaceOfRevolution::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeSurfaceOfRevolution::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeSurfaceOfRevolution.def("Value", (const opencascade::handle<StepGeom_SurfaceOfRevolution> & (GeomToStep_MakeSurfaceOfRevolution::*)() const) &GeomToStep_MakeSurfaceOfRevolution::Value, "None");

// CLASS: GEOMTOSTEP_MAKESWEPTSURFACE
py::class_<GeomToStep_MakeSweptSurface, GeomToStep_Root> cls_GeomToStep_MakeSweptSurface(mod, "GeomToStep_MakeSweptSurface", "This class implements the mapping between classes SweptSurface from Geom and the class SweptSurface from StepGeom which describes a SweptSurface from prostep. As SweptSurface is an abstract SweptSurface this class is an access to the sub-class required.");

// Constructors
cls_GeomToStep_MakeSweptSurface.def(py::init<const opencascade::handle<Geom_SweptSurface> &>(), py::arg("S"));

// Methods
// cls_GeomToStep_MakeSweptSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeSweptSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeSweptSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeSweptSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSweptSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeSweptSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeSweptSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeSweptSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeSweptSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeSweptSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeSweptSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeSweptSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeSweptSurface.def("Value", (const opencascade::handle<StepGeom_SweptSurface> & (GeomToStep_MakeSweptSurface::*)() const) &GeomToStep_MakeSweptSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKETOROIDALSURFACE
py::class_<GeomToStep_MakeToroidalSurface, GeomToStep_Root> cls_GeomToStep_MakeToroidalSurface(mod, "GeomToStep_MakeToroidalSurface", "This class implements the mapping between class ToroidalSurface from Geom and the class ToroidalSurface from StepGeom which describes a toroidal_surface from Prostep");

// Constructors
cls_GeomToStep_MakeToroidalSurface.def(py::init<const opencascade::handle<Geom_ToroidalSurface> &>(), py::arg("TorSurf"));

// Methods
// cls_GeomToStep_MakeToroidalSurface.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeToroidalSurface::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeToroidalSurface.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeToroidalSurface::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeToroidalSurface.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeToroidalSurface::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeToroidalSurface.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeToroidalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeToroidalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeToroidalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeToroidalSurface.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeToroidalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeToroidalSurface.def("Value", (const opencascade::handle<StepGeom_ToroidalSurface> & (GeomToStep_MakeToroidalSurface::*)() const) &GeomToStep_MakeToroidalSurface::Value, "None");

// CLASS: GEOMTOSTEP_MAKEVECTOR
py::class_<GeomToStep_MakeVector, GeomToStep_Root> cls_GeomToStep_MakeVector(mod, "GeomToStep_MakeVector", "This class implements the mapping between classes Vector from Geom, Geom2d and Vec, Vec2d from gp, and the class Vector from StepGeom which describes a Vector from Prostep.");

// Constructors
cls_GeomToStep_MakeVector.def(py::init<const gp_Vec &>(), py::arg("V"));
cls_GeomToStep_MakeVector.def(py::init<const gp_Vec2d &>(), py::arg("V"));
cls_GeomToStep_MakeVector.def(py::init<const opencascade::handle<Geom_Vector> &>(), py::arg("V"));
cls_GeomToStep_MakeVector.def(py::init<const opencascade::handle<Geom2d_Vector> &>(), py::arg("V"));

// Methods
// cls_GeomToStep_MakeVector.def_static("operator new_", (void * (*)(size_t)) &GeomToStep_MakeVector::operator new, "None", py::arg("theSize"));
// cls_GeomToStep_MakeVector.def_static("operator delete_", (void (*)(void *)) &GeomToStep_MakeVector::operator delete, "None", py::arg("theAddress"));
// cls_GeomToStep_MakeVector.def_static("operator new[]_", (void * (*)(size_t)) &GeomToStep_MakeVector::operator new[], "None", py::arg("theSize"));
// cls_GeomToStep_MakeVector.def_static("operator delete[]_", (void (*)(void *)) &GeomToStep_MakeVector::operator delete[], "None", py::arg("theAddress"));
// cls_GeomToStep_MakeVector.def_static("operator new_", (void * (*)(size_t, void *)) &GeomToStep_MakeVector::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GeomToStep_MakeVector.def_static("operator delete_", (void (*)(void *, void *)) &GeomToStep_MakeVector::operator delete, "None", py::arg(""), py::arg(""));
cls_GeomToStep_MakeVector.def("Value", (const opencascade::handle<StepGeom_Vector> & (GeomToStep_MakeVector::*)() const) &GeomToStep_MakeVector::Value, "None");


}
