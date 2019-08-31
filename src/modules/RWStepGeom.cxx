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
#include <StepData_StepReaderData.hxx>
#include <Standard_TypeDef.hxx>
#include <Interface_Check.hxx>
#include <StepGeom_Axis1Placement.hxx>
#include <StepData_StepWriter.hxx>
#include <Interface_EntityIterator.hxx>
#include <RWStepGeom_RWAxis1Placement.hxx>
#include <StepGeom_Axis2Placement2d.hxx>
#include <RWStepGeom_RWAxis2Placement2d.hxx>
#include <StepGeom_Axis2Placement3d.hxx>
#include <RWStepGeom_RWAxis2Placement3d.hxx>
#include <StepGeom_BezierCurve.hxx>
#include <RWStepGeom_RWBezierCurve.hxx>
#include <StepGeom_BezierCurveAndRationalBSplineCurve.hxx>
#include <RWStepGeom_RWBezierCurveAndRationalBSplineCurve.hxx>
#include <StepGeom_BezierSurface.hxx>
#include <RWStepGeom_RWBezierSurface.hxx>
#include <StepGeom_BezierSurfaceAndRationalBSplineSurface.hxx>
#include <RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.hxx>
#include <StepGeom_BoundaryCurve.hxx>
#include <RWStepGeom_RWBoundaryCurve.hxx>
#include <StepGeom_BoundedCurve.hxx>
#include <RWStepGeom_RWBoundedCurve.hxx>
#include <StepGeom_BoundedSurface.hxx>
#include <RWStepGeom_RWBoundedSurface.hxx>
#include <StepGeom_BSplineCurve.hxx>
#include <RWStepGeom_RWBSplineCurve.hxx>
#include <StepGeom_BSplineCurveWithKnots.hxx>
#include <Interface_ShareTool.hxx>
#include <RWStepGeom_RWBSplineCurveWithKnots.hxx>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hxx>
#include <RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.hxx>
#include <StepGeom_BSplineSurface.hxx>
#include <RWStepGeom_RWBSplineSurface.hxx>
#include <StepGeom_BSplineSurfaceWithKnots.hxx>
#include <RWStepGeom_RWBSplineSurfaceWithKnots.hxx>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hxx>
#include <RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <RWStepGeom_RWCartesianPoint.hxx>
#include <StepGeom_CartesianTransformationOperator.hxx>
#include <RWStepGeom_RWCartesianTransformationOperator.hxx>
#include <StepGeom_CartesianTransformationOperator3d.hxx>
#include <RWStepGeom_RWCartesianTransformationOperator3d.hxx>
#include <StepGeom_Circle.hxx>
#include <RWStepGeom_RWCircle.hxx>
#include <StepGeom_CompositeCurve.hxx>
#include <RWStepGeom_RWCompositeCurve.hxx>
#include <StepGeom_CompositeCurveOnSurface.hxx>
#include <RWStepGeom_RWCompositeCurveOnSurface.hxx>
#include <StepGeom_CompositeCurveSegment.hxx>
#include <RWStepGeom_RWCompositeCurveSegment.hxx>
#include <StepGeom_Conic.hxx>
#include <RWStepGeom_RWConic.hxx>
#include <StepGeom_ConicalSurface.hxx>
#include <RWStepGeom_RWConicalSurface.hxx>
#include <StepGeom_Curve.hxx>
#include <RWStepGeom_RWCurve.hxx>
#include <StepGeom_CurveBoundedSurface.hxx>
#include <RWStepGeom_RWCurveBoundedSurface.hxx>
#include <StepGeom_CurveReplica.hxx>
#include <RWStepGeom_RWCurveReplica.hxx>
#include <StepGeom_CylindricalSurface.hxx>
#include <RWStepGeom_RWCylindricalSurface.hxx>
#include <StepGeom_DegeneratePcurve.hxx>
#include <RWStepGeom_RWDegeneratePcurve.hxx>
#include <StepGeom_DegenerateToroidalSurface.hxx>
#include <RWStepGeom_RWDegenerateToroidalSurface.hxx>
#include <StepGeom_Direction.hxx>
#include <RWStepGeom_RWDirection.hxx>
#include <StepGeom_ElementarySurface.hxx>
#include <RWStepGeom_RWElementarySurface.hxx>
#include <StepGeom_Ellipse.hxx>
#include <RWStepGeom_RWEllipse.hxx>
#include <StepGeom_EvaluatedDegeneratePcurve.hxx>
#include <RWStepGeom_RWEvaluatedDegeneratePcurve.hxx>
#include <StepGeom_GeometricRepresentationContext.hxx>
#include <RWStepGeom_RWGeometricRepresentationContext.hxx>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hxx>
#include <RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.hxx>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hxx>
#include <RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.hxx>
#include <StepGeom_GeometricRepresentationItem.hxx>
#include <RWStepGeom_RWGeometricRepresentationItem.hxx>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hxx>
#include <RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hxx>
#include <StepGeom_Hyperbola.hxx>
#include <RWStepGeom_RWHyperbola.hxx>
#include <StepGeom_IntersectionCurve.hxx>
#include <RWStepGeom_RWIntersectionCurve.hxx>
#include <StepGeom_Line.hxx>
#include <RWStepGeom_RWLine.hxx>
#include <StepGeom_OffsetCurve3d.hxx>
#include <RWStepGeom_RWOffsetCurve3d.hxx>
#include <StepGeom_OffsetSurface.hxx>
#include <RWStepGeom_RWOffsetSurface.hxx>
#include <StepGeom_OrientedSurface.hxx>
#include <RWStepGeom_RWOrientedSurface.hxx>
#include <StepGeom_OuterBoundaryCurve.hxx>
#include <RWStepGeom_RWOuterBoundaryCurve.hxx>
#include <StepGeom_Parabola.hxx>
#include <RWStepGeom_RWParabola.hxx>
#include <StepGeom_Pcurve.hxx>
#include <RWStepGeom_RWPcurve.hxx>
#include <StepGeom_Placement.hxx>
#include <RWStepGeom_RWPlacement.hxx>
#include <StepGeom_Plane.hxx>
#include <RWStepGeom_RWPlane.hxx>
#include <StepGeom_Point.hxx>
#include <RWStepGeom_RWPoint.hxx>
#include <StepGeom_PointOnCurve.hxx>
#include <RWStepGeom_RWPointOnCurve.hxx>
#include <StepGeom_PointOnSurface.hxx>
#include <RWStepGeom_RWPointOnSurface.hxx>
#include <StepGeom_PointReplica.hxx>
#include <RWStepGeom_RWPointReplica.hxx>
#include <StepGeom_Polyline.hxx>
#include <RWStepGeom_RWPolyline.hxx>
#include <StepGeom_QuasiUniformCurve.hxx>
#include <RWStepGeom_RWQuasiUniformCurve.hxx>
#include <StepGeom_QuasiUniformCurveAndRationalBSplineCurve.hxx>
#include <RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.hxx>
#include <StepGeom_QuasiUniformSurface.hxx>
#include <RWStepGeom_RWQuasiUniformSurface.hxx>
#include <StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface.hxx>
#include <RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.hxx>
#include <StepGeom_RationalBSplineCurve.hxx>
#include <RWStepGeom_RWRationalBSplineCurve.hxx>
#include <StepGeom_RationalBSplineSurface.hxx>
#include <RWStepGeom_RWRationalBSplineSurface.hxx>
#include <StepGeom_RectangularCompositeSurface.hxx>
#include <RWStepGeom_RWRectangularCompositeSurface.hxx>
#include <StepGeom_RectangularTrimmedSurface.hxx>
#include <RWStepGeom_RWRectangularTrimmedSurface.hxx>
#include <StepGeom_ReparametrisedCompositeCurveSegment.hxx>
#include <RWStepGeom_RWReparametrisedCompositeCurveSegment.hxx>
#include <StepGeom_SeamCurve.hxx>
#include <RWStepGeom_RWSeamCurve.hxx>
#include <StepGeom_SphericalSurface.hxx>
#include <RWStepGeom_RWSphericalSurface.hxx>
#include <StepGeom_Surface.hxx>
#include <RWStepGeom_RWSurface.hxx>
#include <StepGeom_SurfaceCurve.hxx>
#include <RWStepGeom_RWSurfaceCurve.hxx>
#include <StepGeom_SurfaceCurveAndBoundedCurve.hxx>
#include <RWStepGeom_RWSurfaceCurveAndBoundedCurve.hxx>
#include <StepGeom_SurfaceOfLinearExtrusion.hxx>
#include <RWStepGeom_RWSurfaceOfLinearExtrusion.hxx>
#include <StepGeom_SurfaceOfRevolution.hxx>
#include <RWStepGeom_RWSurfaceOfRevolution.hxx>
#include <StepGeom_SurfacePatch.hxx>
#include <RWStepGeom_RWSurfacePatch.hxx>
#include <StepGeom_SurfaceReplica.hxx>
#include <RWStepGeom_RWSurfaceReplica.hxx>
#include <StepGeom_SweptSurface.hxx>
#include <RWStepGeom_RWSweptSurface.hxx>
#include <StepGeom_ToroidalSurface.hxx>
#include <RWStepGeom_RWToroidalSurface.hxx>
#include <StepGeom_TrimmedCurve.hxx>
#include <RWStepGeom_RWTrimmedCurve.hxx>
#include <StepGeom_UniformCurve.hxx>
#include <RWStepGeom_RWUniformCurve.hxx>
#include <StepGeom_UniformCurveAndRationalBSplineCurve.hxx>
#include <RWStepGeom_RWUniformCurveAndRationalBSplineCurve.hxx>
#include <StepGeom_UniformSurface.hxx>
#include <RWStepGeom_RWUniformSurface.hxx>
#include <StepGeom_UniformSurfaceAndRationalBSplineSurface.hxx>
#include <RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.hxx>
#include <StepGeom_Vector.hxx>
#include <RWStepGeom_RWVector.hxx>

PYBIND11_MODULE(RWStepGeom, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.StepData");
py::module::import("OCCT.Interface");
py::module::import("OCCT.StepGeom");

// CLASS: RWSTEPGEOM_RWAXIS1PLACEMENT
py::class_<RWStepGeom_RWAxis1Placement> cls_RWStepGeom_RWAxis1Placement(mod, "RWStepGeom_RWAxis1Placement", "Read & Write Module for Axis1Placement");

// Constructors
cls_RWStepGeom_RWAxis1Placement.def(py::init<>());

// Methods
// cls_RWStepGeom_RWAxis1Placement.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWAxis1Placement::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis1Placement.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWAxis1Placement::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis1Placement.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWAxis1Placement::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis1Placement.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWAxis1Placement::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis1Placement.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWAxis1Placement::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWAxis1Placement.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWAxis1Placement::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWAxis1Placement.def("ReadStep", (void (RWStepGeom_RWAxis1Placement::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Axis1Placement> &) const) &RWStepGeom_RWAxis1Placement::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWAxis1Placement.def("WriteStep", (void (RWStepGeom_RWAxis1Placement::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Axis1Placement> &) const) &RWStepGeom_RWAxis1Placement::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWAxis1Placement.def("Share", (void (RWStepGeom_RWAxis1Placement::*)(const opencascade::handle<StepGeom_Axis1Placement> &, Interface_EntityIterator &) const) &RWStepGeom_RWAxis1Placement::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWAXIS2PLACEMENT2D
py::class_<RWStepGeom_RWAxis2Placement2d> cls_RWStepGeom_RWAxis2Placement2d(mod, "RWStepGeom_RWAxis2Placement2d", "Read & Write Module for Axis2Placement2d");

// Constructors
cls_RWStepGeom_RWAxis2Placement2d.def(py::init<>());

// Methods
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWAxis2Placement2d::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWAxis2Placement2d::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWAxis2Placement2d::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWAxis2Placement2d::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWAxis2Placement2d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement2d.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWAxis2Placement2d::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWAxis2Placement2d.def("ReadStep", (void (RWStepGeom_RWAxis2Placement2d::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Axis2Placement2d> &) const) &RWStepGeom_RWAxis2Placement2d::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWAxis2Placement2d.def("WriteStep", (void (RWStepGeom_RWAxis2Placement2d::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Axis2Placement2d> &) const) &RWStepGeom_RWAxis2Placement2d::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWAxis2Placement2d.def("Share", (void (RWStepGeom_RWAxis2Placement2d::*)(const opencascade::handle<StepGeom_Axis2Placement2d> &, Interface_EntityIterator &) const) &RWStepGeom_RWAxis2Placement2d::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWAXIS2PLACEMENT3D
py::class_<RWStepGeom_RWAxis2Placement3d> cls_RWStepGeom_RWAxis2Placement3d(mod, "RWStepGeom_RWAxis2Placement3d", "Read & Write Module for Axis2Placement3d");

// Constructors
cls_RWStepGeom_RWAxis2Placement3d.def(py::init<>());

// Methods
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWAxis2Placement3d::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWAxis2Placement3d::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWAxis2Placement3d::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWAxis2Placement3d::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWAxis2Placement3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWAxis2Placement3d.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWAxis2Placement3d::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWAxis2Placement3d.def("ReadStep", (void (RWStepGeom_RWAxis2Placement3d::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Axis2Placement3d> &) const) &RWStepGeom_RWAxis2Placement3d::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWAxis2Placement3d.def("WriteStep", (void (RWStepGeom_RWAxis2Placement3d::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Axis2Placement3d> &) const) &RWStepGeom_RWAxis2Placement3d::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWAxis2Placement3d.def("Share", (void (RWStepGeom_RWAxis2Placement3d::*)(const opencascade::handle<StepGeom_Axis2Placement3d> &, Interface_EntityIterator &) const) &RWStepGeom_RWAxis2Placement3d::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBEZIERCURVE
py::class_<RWStepGeom_RWBezierCurve> cls_RWStepGeom_RWBezierCurve(mod, "RWStepGeom_RWBezierCurve", "Read & Write Module for BezierCurve");

// Constructors
cls_RWStepGeom_RWBezierCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBezierCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBezierCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBezierCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBezierCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBezierCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBezierCurve.def("ReadStep", (void (RWStepGeom_RWBezierCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BezierCurve> &) const) &RWStepGeom_RWBezierCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurve.def("WriteStep", (void (RWStepGeom_RWBezierCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BezierCurve> &) const) &RWStepGeom_RWBezierCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurve.def("Share", (void (RWStepGeom_RWBezierCurve::*)(const opencascade::handle<StepGeom_BezierCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBezierCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBEZIERCURVEANDRATIONALBSPLINECURVE
py::class_<RWStepGeom_RWBezierCurveAndRationalBSplineCurve> cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve(mod, "RWStepGeom_RWBezierCurveAndRationalBSplineCurve", "Read & Write Module for BezierCurveAndRationalBSplineCurve");

// Constructors
cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def("ReadStep", (void (RWStepGeom_RWBezierCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BezierCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def("WriteStep", (void (RWStepGeom_RWBezierCurveAndRationalBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BezierCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurveAndRationalBSplineCurve.def("Share", (void (RWStepGeom_RWBezierCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepGeom_BezierCurveAndRationalBSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBezierCurveAndRationalBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBEZIERSURFACE
py::class_<RWStepGeom_RWBezierSurface> cls_RWStepGeom_RWBezierSurface(mod, "RWStepGeom_RWBezierSurface", "Read & Write Module for BezierSurface");

// Constructors
cls_RWStepGeom_RWBezierSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBezierSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBezierSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBezierSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBezierSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBezierSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBezierSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBezierSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBezierSurface.def("ReadStep", (void (RWStepGeom_RWBezierSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BezierSurface> &) const) &RWStepGeom_RWBezierSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBezierSurface.def("WriteStep", (void (RWStepGeom_RWBezierSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BezierSurface> &) const) &RWStepGeom_RWBezierSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBezierSurface.def("Share", (void (RWStepGeom_RWBezierSurface::*)(const opencascade::handle<StepGeom_BezierSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWBezierSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBEZIERSURFACEANDRATIONALBSPLINESURFACE
py::class_<RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface> cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface(mod, "RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface", "Read & Write Module for BezierSurfaceAndRationalBSplineSurface");

// Constructors
cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def("ReadStep", (void (RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def("WriteStep", (void (RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.def("Share", (void (RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBOUNDARYCURVE
py::class_<RWStepGeom_RWBoundaryCurve> cls_RWStepGeom_RWBoundaryCurve(mod, "RWStepGeom_RWBoundaryCurve", "Read & Write Module for BoundaryCurve");

// Constructors
cls_RWStepGeom_RWBoundaryCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBoundaryCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBoundaryCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBoundaryCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBoundaryCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBoundaryCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBoundaryCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBoundaryCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBoundaryCurve.def("ReadStep", (void (RWStepGeom_RWBoundaryCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BoundaryCurve> &) const) &RWStepGeom_RWBoundaryCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBoundaryCurve.def("WriteStep", (void (RWStepGeom_RWBoundaryCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BoundaryCurve> &) const) &RWStepGeom_RWBoundaryCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBoundaryCurve.def("Share", (void (RWStepGeom_RWBoundaryCurve::*)(const opencascade::handle<StepGeom_BoundaryCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBoundaryCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBOUNDEDCURVE
py::class_<RWStepGeom_RWBoundedCurve> cls_RWStepGeom_RWBoundedCurve(mod, "RWStepGeom_RWBoundedCurve", "Read & Write Module for BoundedCurve");

// Constructors
cls_RWStepGeom_RWBoundedCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBoundedCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBoundedCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundedCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBoundedCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBoundedCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundedCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBoundedCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBoundedCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBoundedCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBoundedCurve.def("ReadStep", (void (RWStepGeom_RWBoundedCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BoundedCurve> &) const) &RWStepGeom_RWBoundedCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBoundedCurve.def("WriteStep", (void (RWStepGeom_RWBoundedCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BoundedCurve> &) const) &RWStepGeom_RWBoundedCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWBOUNDEDSURFACE
py::class_<RWStepGeom_RWBoundedSurface> cls_RWStepGeom_RWBoundedSurface(mod, "RWStepGeom_RWBoundedSurface", "Read & Write Module for BoundedSurface");

// Constructors
cls_RWStepGeom_RWBoundedSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBoundedSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBoundedSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundedSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBoundedSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBoundedSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBoundedSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBoundedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBoundedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBoundedSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBoundedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBoundedSurface.def("ReadStep", (void (RWStepGeom_RWBoundedSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BoundedSurface> &) const) &RWStepGeom_RWBoundedSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBoundedSurface.def("WriteStep", (void (RWStepGeom_RWBoundedSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BoundedSurface> &) const) &RWStepGeom_RWBoundedSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWBSPLINECURVE
py::class_<RWStepGeom_RWBSplineCurve> cls_RWStepGeom_RWBSplineCurve(mod, "RWStepGeom_RWBSplineCurve", "Read & Write Module for BSplineCurve");

// Constructors
cls_RWStepGeom_RWBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineCurve.def("ReadStep", (void (RWStepGeom_RWBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineCurve> &) const) &RWStepGeom_RWBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurve.def("WriteStep", (void (RWStepGeom_RWBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineCurve> &) const) &RWStepGeom_RWBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurve.def("Share", (void (RWStepGeom_RWBSplineCurve::*)(const opencascade::handle<StepGeom_BSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBSPLINECURVEWITHKNOTS
py::class_<RWStepGeom_RWBSplineCurveWithKnots> cls_RWStepGeom_RWBSplineCurveWithKnots(mod, "RWStepGeom_RWBSplineCurveWithKnots", "Read & Write Module for BSplineCurveWithKnots Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWBSplineCurveWithKnots.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurveWithKnots::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineCurveWithKnots::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurveWithKnots::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineCurveWithKnots::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineCurveWithKnots::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnots.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineCurveWithKnots::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineCurveWithKnots.def("ReadStep", (void (RWStepGeom_RWBSplineCurveWithKnots::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineCurveWithKnots> &) const) &RWStepGeom_RWBSplineCurveWithKnots::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurveWithKnots.def("WriteStep", (void (RWStepGeom_RWBSplineCurveWithKnots::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineCurveWithKnots> &) const) &RWStepGeom_RWBSplineCurveWithKnots::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurveWithKnots.def("Share", (void (RWStepGeom_RWBSplineCurveWithKnots::*)(const opencascade::handle<StepGeom_BSplineCurveWithKnots> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineCurveWithKnots::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWBSplineCurveWithKnots.def("Check", (void (RWStepGeom_RWBSplineCurveWithKnots::*)(const opencascade::handle<StepGeom_BSplineCurveWithKnots> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWBSplineCurveWithKnots::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWBSPLINECURVEWITHKNOTSANDRATIONALBSPLINECURVE
py::class_<RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve> cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve(mod, "RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve", "Read & Write Module for BSplineCurveWithKnotsAndRationalBSplineCurve Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def("ReadStep", (void (RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> &) const) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def("WriteStep", (void (RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> &) const) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def("Share", (void (RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::*)(const opencascade::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.def("Check", (void (RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::*)(const opencascade::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWBSPLINESURFACE
py::class_<RWStepGeom_RWBSplineSurface> cls_RWStepGeom_RWBSplineSurface(mod, "RWStepGeom_RWBSplineSurface", "Read & Write Module for BSplineSurface");

// Constructors
cls_RWStepGeom_RWBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineSurface.def("ReadStep", (void (RWStepGeom_RWBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineSurface> &) const) &RWStepGeom_RWBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurface.def("WriteStep", (void (RWStepGeom_RWBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineSurface> &) const) &RWStepGeom_RWBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurface.def("Share", (void (RWStepGeom_RWBSplineSurface::*)(const opencascade::handle<StepGeom_BSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWBSPLINESURFACEWITHKNOTS
py::class_<RWStepGeom_RWBSplineSurfaceWithKnots> cls_RWStepGeom_RWBSplineSurfaceWithKnots(mod, "RWStepGeom_RWBSplineSurfaceWithKnots", "Read & Write Module for BSplineSurfaceWithKnots Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWBSplineSurfaceWithKnots.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnots.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineSurfaceWithKnots::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineSurfaceWithKnots.def("ReadStep", (void (RWStepGeom_RWBSplineSurfaceWithKnots::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineSurfaceWithKnots> &) const) &RWStepGeom_RWBSplineSurfaceWithKnots::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurfaceWithKnots.def("WriteStep", (void (RWStepGeom_RWBSplineSurfaceWithKnots::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineSurfaceWithKnots> &) const) &RWStepGeom_RWBSplineSurfaceWithKnots::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurfaceWithKnots.def("Share", (void (RWStepGeom_RWBSplineSurfaceWithKnots::*)(const opencascade::handle<StepGeom_BSplineSurfaceWithKnots> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineSurfaceWithKnots::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWBSplineSurfaceWithKnots.def("Check", (void (RWStepGeom_RWBSplineSurfaceWithKnots::*)(const opencascade::handle<StepGeom_BSplineSurfaceWithKnots> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWBSplineSurfaceWithKnots::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWBSPLINESURFACEWITHKNOTSANDRATIONALBSPLINESURFACE
py::class_<RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface> cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface(mod, "RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface", "Read & Write Module for BSplineSurfaceWithKnotsAndRationalBSplineSurface Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def("ReadStep", (void (RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> &) const) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def("WriteStep", (void (RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> &) const) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def("Share", (void (RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::*)(const opencascade::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.def("Check", (void (RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::*)(const opencascade::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWCARTESIANPOINT
py::class_<RWStepGeom_RWCartesianPoint> cls_RWStepGeom_RWCartesianPoint(mod, "RWStepGeom_RWCartesianPoint", "Read & Write Module for CartesianPoint");

// Constructors
cls_RWStepGeom_RWCartesianPoint.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCartesianPoint.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCartesianPoint::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianPoint.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCartesianPoint::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianPoint.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCartesianPoint::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianPoint.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCartesianPoint::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianPoint.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCartesianPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianPoint.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCartesianPoint::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCartesianPoint.def("ReadStep", (void (RWStepGeom_RWCartesianPoint::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CartesianPoint> &) const) &RWStepGeom_RWCartesianPoint::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCartesianPoint.def("WriteStep", (void (RWStepGeom_RWCartesianPoint::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CartesianPoint> &) const) &RWStepGeom_RWCartesianPoint::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWCARTESIANTRANSFORMATIONOPERATOR
py::class_<RWStepGeom_RWCartesianTransformationOperator> cls_RWStepGeom_RWCartesianTransformationOperator(mod, "RWStepGeom_RWCartesianTransformationOperator", "Read & Write Module for CartesianTransformationOperator");

// Constructors
cls_RWStepGeom_RWCartesianTransformationOperator.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCartesianTransformationOperator::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCartesianTransformationOperator::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCartesianTransformationOperator::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCartesianTransformationOperator::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCartesianTransformationOperator::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCartesianTransformationOperator::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCartesianTransformationOperator.def("ReadStep", (void (RWStepGeom_RWCartesianTransformationOperator::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CartesianTransformationOperator> &) const) &RWStepGeom_RWCartesianTransformationOperator::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCartesianTransformationOperator.def("WriteStep", (void (RWStepGeom_RWCartesianTransformationOperator::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CartesianTransformationOperator> &) const) &RWStepGeom_RWCartesianTransformationOperator::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCartesianTransformationOperator.def("Share", (void (RWStepGeom_RWCartesianTransformationOperator::*)(const opencascade::handle<StepGeom_CartesianTransformationOperator> &, Interface_EntityIterator &) const) &RWStepGeom_RWCartesianTransformationOperator::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCARTESIANTRANSFORMATIONOPERATOR3D
py::class_<RWStepGeom_RWCartesianTransformationOperator3d> cls_RWStepGeom_RWCartesianTransformationOperator3d(mod, "RWStepGeom_RWCartesianTransformationOperator3d", "Read & Write Module for CartesianTransformationOperator3d");

// Constructors
cls_RWStepGeom_RWCartesianTransformationOperator3d.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCartesianTransformationOperator3d::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCartesianTransformationOperator3d::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCartesianTransformationOperator3d::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCartesianTransformationOperator3d::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCartesianTransformationOperator3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCartesianTransformationOperator3d.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCartesianTransformationOperator3d::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCartesianTransformationOperator3d.def("ReadStep", (void (RWStepGeom_RWCartesianTransformationOperator3d::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CartesianTransformationOperator3d> &) const) &RWStepGeom_RWCartesianTransformationOperator3d::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCartesianTransformationOperator3d.def("WriteStep", (void (RWStepGeom_RWCartesianTransformationOperator3d::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CartesianTransformationOperator3d> &) const) &RWStepGeom_RWCartesianTransformationOperator3d::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCartesianTransformationOperator3d.def("Share", (void (RWStepGeom_RWCartesianTransformationOperator3d::*)(const opencascade::handle<StepGeom_CartesianTransformationOperator3d> &, Interface_EntityIterator &) const) &RWStepGeom_RWCartesianTransformationOperator3d::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCIRCLE
py::class_<RWStepGeom_RWCircle> cls_RWStepGeom_RWCircle(mod, "RWStepGeom_RWCircle", "Read & Write Module for Circle");

// Constructors
cls_RWStepGeom_RWCircle.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCircle.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCircle::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCircle.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCircle::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCircle.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCircle::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCircle.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCircle::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCircle.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCircle::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCircle.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCircle::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCircle.def("ReadStep", (void (RWStepGeom_RWCircle::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Circle> &) const) &RWStepGeom_RWCircle::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCircle.def("WriteStep", (void (RWStepGeom_RWCircle::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Circle> &) const) &RWStepGeom_RWCircle::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCircle.def("Share", (void (RWStepGeom_RWCircle::*)(const opencascade::handle<StepGeom_Circle> &, Interface_EntityIterator &) const) &RWStepGeom_RWCircle::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCOMPOSITECURVE
py::class_<RWStepGeom_RWCompositeCurve> cls_RWStepGeom_RWCompositeCurve(mod, "RWStepGeom_RWCompositeCurve", "Read & Write Module for CompositeCurve");

// Constructors
cls_RWStepGeom_RWCompositeCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCompositeCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCompositeCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCompositeCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCompositeCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCompositeCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCompositeCurve.def("ReadStep", (void (RWStepGeom_RWCompositeCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CompositeCurve> &) const) &RWStepGeom_RWCompositeCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurve.def("WriteStep", (void (RWStepGeom_RWCompositeCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CompositeCurve> &) const) &RWStepGeom_RWCompositeCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurve.def("Share", (void (RWStepGeom_RWCompositeCurve::*)(const opencascade::handle<StepGeom_CompositeCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWCompositeCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCOMPOSITECURVEONSURFACE
py::class_<RWStepGeom_RWCompositeCurveOnSurface> cls_RWStepGeom_RWCompositeCurveOnSurface(mod, "RWStepGeom_RWCompositeCurveOnSurface", "Read & Write Module for CompositeCurveOnSurface");

// Constructors
cls_RWStepGeom_RWCompositeCurveOnSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurveOnSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCompositeCurveOnSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurveOnSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCompositeCurveOnSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCompositeCurveOnSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveOnSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCompositeCurveOnSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCompositeCurveOnSurface.def("ReadStep", (void (RWStepGeom_RWCompositeCurveOnSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CompositeCurveOnSurface> &) const) &RWStepGeom_RWCompositeCurveOnSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurveOnSurface.def("WriteStep", (void (RWStepGeom_RWCompositeCurveOnSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CompositeCurveOnSurface> &) const) &RWStepGeom_RWCompositeCurveOnSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurveOnSurface.def("Share", (void (RWStepGeom_RWCompositeCurveOnSurface::*)(const opencascade::handle<StepGeom_CompositeCurveOnSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWCompositeCurveOnSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCOMPOSITECURVESEGMENT
py::class_<RWStepGeom_RWCompositeCurveSegment> cls_RWStepGeom_RWCompositeCurveSegment(mod, "RWStepGeom_RWCompositeCurveSegment", "Read & Write Module for CompositeCurveSegment");

// Constructors
cls_RWStepGeom_RWCompositeCurveSegment.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurveSegment::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCompositeCurveSegment::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCompositeCurveSegment::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCompositeCurveSegment::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCompositeCurveSegment::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCompositeCurveSegment.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCompositeCurveSegment::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCompositeCurveSegment.def("ReadStep", (void (RWStepGeom_RWCompositeCurveSegment::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CompositeCurveSegment> &) const) &RWStepGeom_RWCompositeCurveSegment::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurveSegment.def("WriteStep", (void (RWStepGeom_RWCompositeCurveSegment::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CompositeCurveSegment> &) const) &RWStepGeom_RWCompositeCurveSegment::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCompositeCurveSegment.def("Share", (void (RWStepGeom_RWCompositeCurveSegment::*)(const opencascade::handle<StepGeom_CompositeCurveSegment> &, Interface_EntityIterator &) const) &RWStepGeom_RWCompositeCurveSegment::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCONIC
py::class_<RWStepGeom_RWConic> cls_RWStepGeom_RWConic(mod, "RWStepGeom_RWConic", "Read & Write Module for Conic");

// Constructors
cls_RWStepGeom_RWConic.def(py::init<>());

// Methods
// cls_RWStepGeom_RWConic.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWConic::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWConic.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWConic::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWConic.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWConic::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWConic.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWConic::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWConic.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWConic::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWConic.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWConic::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWConic.def("ReadStep", (void (RWStepGeom_RWConic::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Conic> &) const) &RWStepGeom_RWConic::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWConic.def("WriteStep", (void (RWStepGeom_RWConic::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Conic> &) const) &RWStepGeom_RWConic::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWConic.def("Share", (void (RWStepGeom_RWConic::*)(const opencascade::handle<StepGeom_Conic> &, Interface_EntityIterator &) const) &RWStepGeom_RWConic::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCONICALSURFACE
py::class_<RWStepGeom_RWConicalSurface> cls_RWStepGeom_RWConicalSurface(mod, "RWStepGeom_RWConicalSurface", "Read & Write Module for ConicalSurface");

// Constructors
cls_RWStepGeom_RWConicalSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWConicalSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWConicalSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWConicalSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWConicalSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWConicalSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWConicalSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWConicalSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWConicalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWConicalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWConicalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWConicalSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWConicalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWConicalSurface.def("ReadStep", (void (RWStepGeom_RWConicalSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_ConicalSurface> &) const) &RWStepGeom_RWConicalSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWConicalSurface.def("WriteStep", (void (RWStepGeom_RWConicalSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_ConicalSurface> &) const) &RWStepGeom_RWConicalSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWConicalSurface.def("Share", (void (RWStepGeom_RWConicalSurface::*)(const opencascade::handle<StepGeom_ConicalSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWConicalSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCURVE
py::class_<RWStepGeom_RWCurve> cls_RWStepGeom_RWCurve(mod, "RWStepGeom_RWCurve", "Read & Write Module for Curve");

// Constructors
cls_RWStepGeom_RWCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCurve.def("ReadStep", (void (RWStepGeom_RWCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Curve> &) const) &RWStepGeom_RWCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCurve.def("WriteStep", (void (RWStepGeom_RWCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Curve> &) const) &RWStepGeom_RWCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWCURVEBOUNDEDSURFACE
py::class_<RWStepGeom_RWCurveBoundedSurface> cls_RWStepGeom_RWCurveBoundedSurface(mod, "RWStepGeom_RWCurveBoundedSurface", "Read & Write tool for CurveBoundedSurface");

// Constructors
cls_RWStepGeom_RWCurveBoundedSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCurveBoundedSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCurveBoundedSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCurveBoundedSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCurveBoundedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCurveBoundedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCurveBoundedSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCurveBoundedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCurveBoundedSurface.def("ReadStep", (void (RWStepGeom_RWCurveBoundedSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CurveBoundedSurface> &) const) &RWStepGeom_RWCurveBoundedSurface::ReadStep, "Reads CurveBoundedSurface", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCurveBoundedSurface.def("WriteStep", (void (RWStepGeom_RWCurveBoundedSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CurveBoundedSurface> &) const) &RWStepGeom_RWCurveBoundedSurface::WriteStep, "Writes CurveBoundedSurface", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCurveBoundedSurface.def("Share", (void (RWStepGeom_RWCurveBoundedSurface::*)(const opencascade::handle<StepGeom_CurveBoundedSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWCurveBoundedSurface::Share, "Fills data for graph (shared items)", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCURVEREPLICA
py::class_<RWStepGeom_RWCurveReplica> cls_RWStepGeom_RWCurveReplica(mod, "RWStepGeom_RWCurveReplica", "Read & Write Module for CurveReplica");

// Constructors
cls_RWStepGeom_RWCurveReplica.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCurveReplica.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCurveReplica::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurveReplica.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCurveReplica::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurveReplica.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCurveReplica::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCurveReplica.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCurveReplica::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCurveReplica.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCurveReplica::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCurveReplica.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCurveReplica::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCurveReplica.def("ReadStep", (void (RWStepGeom_RWCurveReplica::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CurveReplica> &) const) &RWStepGeom_RWCurveReplica::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCurveReplica.def("WriteStep", (void (RWStepGeom_RWCurveReplica::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CurveReplica> &) const) &RWStepGeom_RWCurveReplica::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCurveReplica.def("Share", (void (RWStepGeom_RWCurveReplica::*)(const opencascade::handle<StepGeom_CurveReplica> &, Interface_EntityIterator &) const) &RWStepGeom_RWCurveReplica::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWCYLINDRICALSURFACE
py::class_<RWStepGeom_RWCylindricalSurface> cls_RWStepGeom_RWCylindricalSurface(mod, "RWStepGeom_RWCylindricalSurface", "Read & Write Module for CylindricalSurface");

// Constructors
cls_RWStepGeom_RWCylindricalSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWCylindricalSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWCylindricalSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWCylindricalSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWCylindricalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWCylindricalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWCylindricalSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWCylindricalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWCylindricalSurface.def("ReadStep", (void (RWStepGeom_RWCylindricalSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_CylindricalSurface> &) const) &RWStepGeom_RWCylindricalSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWCylindricalSurface.def("WriteStep", (void (RWStepGeom_RWCylindricalSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_CylindricalSurface> &) const) &RWStepGeom_RWCylindricalSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWCylindricalSurface.def("Share", (void (RWStepGeom_RWCylindricalSurface::*)(const opencascade::handle<StepGeom_CylindricalSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWCylindricalSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWDEGENERATEPCURVE
py::class_<RWStepGeom_RWDegeneratePcurve> cls_RWStepGeom_RWDegeneratePcurve(mod, "RWStepGeom_RWDegeneratePcurve", "Read & Write Module for DegeneratePcurve");

// Constructors
cls_RWStepGeom_RWDegeneratePcurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWDegeneratePcurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWDegeneratePcurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWDegeneratePcurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWDegeneratePcurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWDegeneratePcurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWDegeneratePcurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWDegeneratePcurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWDegeneratePcurve.def("ReadStep", (void (RWStepGeom_RWDegeneratePcurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_DegeneratePcurve> &) const) &RWStepGeom_RWDegeneratePcurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWDegeneratePcurve.def("WriteStep", (void (RWStepGeom_RWDegeneratePcurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_DegeneratePcurve> &) const) &RWStepGeom_RWDegeneratePcurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWDegeneratePcurve.def("Share", (void (RWStepGeom_RWDegeneratePcurve::*)(const opencascade::handle<StepGeom_DegeneratePcurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWDegeneratePcurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWDEGENERATETOROIDALSURFACE
py::class_<RWStepGeom_RWDegenerateToroidalSurface> cls_RWStepGeom_RWDegenerateToroidalSurface(mod, "RWStepGeom_RWDegenerateToroidalSurface", "Read & Write Module for DegenerateToroidalSurface");

// Constructors
cls_RWStepGeom_RWDegenerateToroidalSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWDegenerateToroidalSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWDegenerateToroidalSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWDegenerateToroidalSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWDegenerateToroidalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWDegenerateToroidalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWDegenerateToroidalSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWDegenerateToroidalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWDegenerateToroidalSurface.def("ReadStep", (void (RWStepGeom_RWDegenerateToroidalSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_DegenerateToroidalSurface> &) const) &RWStepGeom_RWDegenerateToroidalSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWDegenerateToroidalSurface.def("WriteStep", (void (RWStepGeom_RWDegenerateToroidalSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_DegenerateToroidalSurface> &) const) &RWStepGeom_RWDegenerateToroidalSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWDegenerateToroidalSurface.def("Share", (void (RWStepGeom_RWDegenerateToroidalSurface::*)(const opencascade::handle<StepGeom_DegenerateToroidalSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWDegenerateToroidalSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWDIRECTION
py::class_<RWStepGeom_RWDirection> cls_RWStepGeom_RWDirection(mod, "RWStepGeom_RWDirection", "Read & Write Module for Direction Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWDirection.def(py::init<>());

// Methods
// cls_RWStepGeom_RWDirection.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWDirection::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWDirection.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWDirection::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDirection.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWDirection::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWDirection.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWDirection::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWDirection.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWDirection::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWDirection.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWDirection::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWDirection.def("ReadStep", (void (RWStepGeom_RWDirection::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Direction> &) const) &RWStepGeom_RWDirection::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWDirection.def("WriteStep", (void (RWStepGeom_RWDirection::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Direction> &) const) &RWStepGeom_RWDirection::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWDirection.def("Check", (void (RWStepGeom_RWDirection::*)(const opencascade::handle<StepGeom_Direction> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWDirection::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWELEMENTARYSURFACE
py::class_<RWStepGeom_RWElementarySurface> cls_RWStepGeom_RWElementarySurface(mod, "RWStepGeom_RWElementarySurface", "Read & Write Module for ElementarySurface");

// Constructors
cls_RWStepGeom_RWElementarySurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWElementarySurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWElementarySurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWElementarySurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWElementarySurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWElementarySurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWElementarySurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWElementarySurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWElementarySurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWElementarySurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWElementarySurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWElementarySurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWElementarySurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWElementarySurface.def("ReadStep", (void (RWStepGeom_RWElementarySurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_ElementarySurface> &) const) &RWStepGeom_RWElementarySurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWElementarySurface.def("WriteStep", (void (RWStepGeom_RWElementarySurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_ElementarySurface> &) const) &RWStepGeom_RWElementarySurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWElementarySurface.def("Share", (void (RWStepGeom_RWElementarySurface::*)(const opencascade::handle<StepGeom_ElementarySurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWElementarySurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWELLIPSE
py::class_<RWStepGeom_RWEllipse> cls_RWStepGeom_RWEllipse(mod, "RWStepGeom_RWEllipse", "Read & Write Module for Ellipse Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWEllipse.def(py::init<>());

// Methods
// cls_RWStepGeom_RWEllipse.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWEllipse::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWEllipse.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWEllipse::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWEllipse.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWEllipse::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWEllipse.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWEllipse::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWEllipse.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWEllipse::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWEllipse.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWEllipse::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWEllipse.def("ReadStep", (void (RWStepGeom_RWEllipse::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Ellipse> &) const) &RWStepGeom_RWEllipse::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWEllipse.def("WriteStep", (void (RWStepGeom_RWEllipse::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Ellipse> &) const) &RWStepGeom_RWEllipse::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWEllipse.def("Share", (void (RWStepGeom_RWEllipse::*)(const opencascade::handle<StepGeom_Ellipse> &, Interface_EntityIterator &) const) &RWStepGeom_RWEllipse::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWEllipse.def("Check", (void (RWStepGeom_RWEllipse::*)(const opencascade::handle<StepGeom_Ellipse> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWEllipse::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWEVALUATEDDEGENERATEPCURVE
py::class_<RWStepGeom_RWEvaluatedDegeneratePcurve> cls_RWStepGeom_RWEvaluatedDegeneratePcurve(mod, "RWStepGeom_RWEvaluatedDegeneratePcurve", "Read & Write Module for EvaluatedDegeneratePcurve");

// Constructors
cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWEvaluatedDegeneratePcurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def("ReadStep", (void (RWStepGeom_RWEvaluatedDegeneratePcurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_EvaluatedDegeneratePcurve> &) const) &RWStepGeom_RWEvaluatedDegeneratePcurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def("WriteStep", (void (RWStepGeom_RWEvaluatedDegeneratePcurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_EvaluatedDegeneratePcurve> &) const) &RWStepGeom_RWEvaluatedDegeneratePcurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWEvaluatedDegeneratePcurve.def("Share", (void (RWStepGeom_RWEvaluatedDegeneratePcurve::*)(const opencascade::handle<StepGeom_EvaluatedDegeneratePcurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWEvaluatedDegeneratePcurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWGEOMETRICREPRESENTATIONCONTEXT
py::class_<RWStepGeom_RWGeometricRepresentationContext> cls_RWStepGeom_RWGeometricRepresentationContext(mod, "RWStepGeom_RWGeometricRepresentationContext", "Read & Write Module for GeometricRepresentationContext");

// Constructors
cls_RWStepGeom_RWGeometricRepresentationContext.def(py::init<>());

// Methods
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContext::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContext::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContext::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContext::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWGeometricRepresentationContext::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContext.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWGeometricRepresentationContext::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWGeometricRepresentationContext.def("ReadStep", (void (RWStepGeom_RWGeometricRepresentationContext::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_GeometricRepresentationContext> &) const) &RWStepGeom_RWGeometricRepresentationContext::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationContext.def("WriteStep", (void (RWStepGeom_RWGeometricRepresentationContext::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_GeometricRepresentationContext> &) const) &RWStepGeom_RWGeometricRepresentationContext::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWGEOMETRICREPRESENTATIONCONTEXTANDGLOBALUNITASSIGNEDCONTEXT
py::class_<RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext> cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext(mod, "RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext", "Read & Write Module for GeometricRepresentationContextAndGlobalUnitAssignedContext");

// Constructors
cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def(py::init<>());

// Methods
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def("ReadStep", (void (RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext> &) const) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def("WriteStep", (void (RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext> &) const) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.def("Share", (void (RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::*)(const opencascade::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext> &, Interface_EntityIterator &) const) &RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWGEOMETRICREPRESENTATIONCONTEXTANDPARAMETRICREPRESENTATIONCONTEXT
py::class_<RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext> cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext(mod, "RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext", "Read & Write Module for GeometricRepresentationContextAndParametricRepresentationContext");

// Constructors
cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def(py::init<>());

// Methods
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def("ReadStep", (void (RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext> &) const) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def("WriteStep", (void (RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext> &) const) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.def("Share", (void (RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::*)(const opencascade::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext> &, Interface_EntityIterator &) const) &RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWGEOMETRICREPRESENTATIONITEM
py::class_<RWStepGeom_RWGeometricRepresentationItem> cls_RWStepGeom_RWGeometricRepresentationItem(mod, "RWStepGeom_RWGeometricRepresentationItem", "Read & Write Module for GeometricRepresentationItem");

// Constructors
cls_RWStepGeom_RWGeometricRepresentationItem.def(py::init<>());

// Methods
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationItem::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationItem::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWGeometricRepresentationItem::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWGeometricRepresentationItem::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWGeometricRepresentationItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWGeometricRepresentationItem.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWGeometricRepresentationItem::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWGeometricRepresentationItem.def("ReadStep", (void (RWStepGeom_RWGeometricRepresentationItem::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_GeometricRepresentationItem> &) const) &RWStepGeom_RWGeometricRepresentationItem::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWGeometricRepresentationItem.def("WriteStep", (void (RWStepGeom_RWGeometricRepresentationItem::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_GeometricRepresentationItem> &) const) &RWStepGeom_RWGeometricRepresentationItem::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWGEOMREPCONTEXTANDGLOBUNITASSCTXANDGLOBUNCERTAINTYASSCTX
py::class_<RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx(mod, "RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx", "Read & Write Module for GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx");

// Constructors
cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def(py::init<>());

// Methods
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def("ReadStep", (void (RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> &) const) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def("WriteStep", (void (RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> &) const) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.def("Share", (void (RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::*)(const opencascade::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> &, Interface_EntityIterator &) const) &RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWHYPERBOLA
py::class_<RWStepGeom_RWHyperbola> cls_RWStepGeom_RWHyperbola(mod, "RWStepGeom_RWHyperbola", "Read & Write Module for Hyperbola");

// Constructors
cls_RWStepGeom_RWHyperbola.def(py::init<>());

// Methods
// cls_RWStepGeom_RWHyperbola.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWHyperbola::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWHyperbola.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWHyperbola::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWHyperbola.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWHyperbola::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWHyperbola.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWHyperbola::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWHyperbola.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWHyperbola::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWHyperbola.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWHyperbola::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWHyperbola.def("ReadStep", (void (RWStepGeom_RWHyperbola::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Hyperbola> &) const) &RWStepGeom_RWHyperbola::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWHyperbola.def("WriteStep", (void (RWStepGeom_RWHyperbola::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Hyperbola> &) const) &RWStepGeom_RWHyperbola::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWHyperbola.def("Share", (void (RWStepGeom_RWHyperbola::*)(const opencascade::handle<StepGeom_Hyperbola> &, Interface_EntityIterator &) const) &RWStepGeom_RWHyperbola::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWINTERSECTIONCURVE
py::class_<RWStepGeom_RWIntersectionCurve> cls_RWStepGeom_RWIntersectionCurve(mod, "RWStepGeom_RWIntersectionCurve", "Read & Write Module for IntersectionCurve");

// Constructors
cls_RWStepGeom_RWIntersectionCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWIntersectionCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWIntersectionCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWIntersectionCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWIntersectionCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWIntersectionCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWIntersectionCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWIntersectionCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWIntersectionCurve.def("ReadStep", (void (RWStepGeom_RWIntersectionCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_IntersectionCurve> &) const) &RWStepGeom_RWIntersectionCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWIntersectionCurve.def("WriteStep", (void (RWStepGeom_RWIntersectionCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_IntersectionCurve> &) const) &RWStepGeom_RWIntersectionCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWIntersectionCurve.def("Share", (void (RWStepGeom_RWIntersectionCurve::*)(const opencascade::handle<StepGeom_IntersectionCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWIntersectionCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWLINE
py::class_<RWStepGeom_RWLine> cls_RWStepGeom_RWLine(mod, "RWStepGeom_RWLine", "Read & Write Module for Line");

// Constructors
cls_RWStepGeom_RWLine.def(py::init<>());

// Methods
// cls_RWStepGeom_RWLine.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWLine::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWLine.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWLine::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWLine.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWLine::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWLine.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWLine::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWLine.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWLine::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWLine.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWLine::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWLine.def("ReadStep", (void (RWStepGeom_RWLine::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Line> &) const) &RWStepGeom_RWLine::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWLine.def("WriteStep", (void (RWStepGeom_RWLine::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Line> &) const) &RWStepGeom_RWLine::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWLine.def("Share", (void (RWStepGeom_RWLine::*)(const opencascade::handle<StepGeom_Line> &, Interface_EntityIterator &) const) &RWStepGeom_RWLine::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWOFFSETCURVE3D
py::class_<RWStepGeom_RWOffsetCurve3d> cls_RWStepGeom_RWOffsetCurve3d(mod, "RWStepGeom_RWOffsetCurve3d", "Read & Write Module for OffsetCurve3d");

// Constructors
cls_RWStepGeom_RWOffsetCurve3d.def(py::init<>());

// Methods
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWOffsetCurve3d::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWOffsetCurve3d::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWOffsetCurve3d::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWOffsetCurve3d::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWOffsetCurve3d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetCurve3d.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWOffsetCurve3d::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWOffsetCurve3d.def("ReadStep", (void (RWStepGeom_RWOffsetCurve3d::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_OffsetCurve3d> &) const) &RWStepGeom_RWOffsetCurve3d::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWOffsetCurve3d.def("WriteStep", (void (RWStepGeom_RWOffsetCurve3d::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_OffsetCurve3d> &) const) &RWStepGeom_RWOffsetCurve3d::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWOffsetCurve3d.def("Share", (void (RWStepGeom_RWOffsetCurve3d::*)(const opencascade::handle<StepGeom_OffsetCurve3d> &, Interface_EntityIterator &) const) &RWStepGeom_RWOffsetCurve3d::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWOFFSETSURFACE
py::class_<RWStepGeom_RWOffsetSurface> cls_RWStepGeom_RWOffsetSurface(mod, "RWStepGeom_RWOffsetSurface", "Read & Write Module for OffsetSurface");

// Constructors
cls_RWStepGeom_RWOffsetSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWOffsetSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWOffsetSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWOffsetSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWOffsetSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWOffsetSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWOffsetSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWOffsetSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWOffsetSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWOffsetSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWOffsetSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWOffsetSurface.def("ReadStep", (void (RWStepGeom_RWOffsetSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_OffsetSurface> &) const) &RWStepGeom_RWOffsetSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWOffsetSurface.def("WriteStep", (void (RWStepGeom_RWOffsetSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_OffsetSurface> &) const) &RWStepGeom_RWOffsetSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWOffsetSurface.def("Share", (void (RWStepGeom_RWOffsetSurface::*)(const opencascade::handle<StepGeom_OffsetSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWOffsetSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWORIENTEDSURFACE
py::class_<RWStepGeom_RWOrientedSurface> cls_RWStepGeom_RWOrientedSurface(mod, "RWStepGeom_RWOrientedSurface", "Read & Write tool for OrientedSurface");

// Constructors
cls_RWStepGeom_RWOrientedSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWOrientedSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWOrientedSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWOrientedSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWOrientedSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOrientedSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWOrientedSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWOrientedSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWOrientedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOrientedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWOrientedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWOrientedSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWOrientedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWOrientedSurface.def("ReadStep", (void (RWStepGeom_RWOrientedSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_OrientedSurface> &) const) &RWStepGeom_RWOrientedSurface::ReadStep, "Reads OrientedSurface", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWOrientedSurface.def("WriteStep", (void (RWStepGeom_RWOrientedSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_OrientedSurface> &) const) &RWStepGeom_RWOrientedSurface::WriteStep, "Writes OrientedSurface", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWOrientedSurface.def("Share", (void (RWStepGeom_RWOrientedSurface::*)(const opencascade::handle<StepGeom_OrientedSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWOrientedSurface::Share, "Fills data for graph (shared items)", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWOUTERBOUNDARYCURVE
py::class_<RWStepGeom_RWOuterBoundaryCurve> cls_RWStepGeom_RWOuterBoundaryCurve(mod, "RWStepGeom_RWOuterBoundaryCurve", "Read & Write Module for OuterBoundaryCurve");

// Constructors
cls_RWStepGeom_RWOuterBoundaryCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWOuterBoundaryCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWOuterBoundaryCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWOuterBoundaryCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWOuterBoundaryCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWOuterBoundaryCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWOuterBoundaryCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWOuterBoundaryCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWOuterBoundaryCurve.def("ReadStep", (void (RWStepGeom_RWOuterBoundaryCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_OuterBoundaryCurve> &) const) &RWStepGeom_RWOuterBoundaryCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWOuterBoundaryCurve.def("WriteStep", (void (RWStepGeom_RWOuterBoundaryCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_OuterBoundaryCurve> &) const) &RWStepGeom_RWOuterBoundaryCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWOuterBoundaryCurve.def("Share", (void (RWStepGeom_RWOuterBoundaryCurve::*)(const opencascade::handle<StepGeom_OuterBoundaryCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWOuterBoundaryCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPARABOLA
py::class_<RWStepGeom_RWParabola> cls_RWStepGeom_RWParabola(mod, "RWStepGeom_RWParabola", "Read & Write Module for Parabola");

// Constructors
cls_RWStepGeom_RWParabola.def(py::init<>());

// Methods
// cls_RWStepGeom_RWParabola.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWParabola::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWParabola.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWParabola::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWParabola.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWParabola::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWParabola.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWParabola::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWParabola.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWParabola::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWParabola.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWParabola::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWParabola.def("ReadStep", (void (RWStepGeom_RWParabola::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Parabola> &) const) &RWStepGeom_RWParabola::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWParabola.def("WriteStep", (void (RWStepGeom_RWParabola::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Parabola> &) const) &RWStepGeom_RWParabola::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWParabola.def("Share", (void (RWStepGeom_RWParabola::*)(const opencascade::handle<StepGeom_Parabola> &, Interface_EntityIterator &) const) &RWStepGeom_RWParabola::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPCURVE
py::class_<RWStepGeom_RWPcurve> cls_RWStepGeom_RWPcurve(mod, "RWStepGeom_RWPcurve", "Read & Write Module for Pcurve");

// Constructors
cls_RWStepGeom_RWPcurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPcurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPcurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPcurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPcurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPcurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPcurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPcurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPcurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPcurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPcurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPcurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPcurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPcurve.def("ReadStep", (void (RWStepGeom_RWPcurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Pcurve> &) const) &RWStepGeom_RWPcurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPcurve.def("WriteStep", (void (RWStepGeom_RWPcurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Pcurve> &) const) &RWStepGeom_RWPcurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPcurve.def("Share", (void (RWStepGeom_RWPcurve::*)(const opencascade::handle<StepGeom_Pcurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWPcurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPLACEMENT
py::class_<RWStepGeom_RWPlacement> cls_RWStepGeom_RWPlacement(mod, "RWStepGeom_RWPlacement", "Read & Write Module for Placement");

// Constructors
cls_RWStepGeom_RWPlacement.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPlacement.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPlacement::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPlacement.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPlacement::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPlacement.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPlacement::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPlacement.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPlacement::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPlacement.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPlacement::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPlacement.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPlacement::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPlacement.def("ReadStep", (void (RWStepGeom_RWPlacement::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Placement> &) const) &RWStepGeom_RWPlacement::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPlacement.def("WriteStep", (void (RWStepGeom_RWPlacement::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Placement> &) const) &RWStepGeom_RWPlacement::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPlacement.def("Share", (void (RWStepGeom_RWPlacement::*)(const opencascade::handle<StepGeom_Placement> &, Interface_EntityIterator &) const) &RWStepGeom_RWPlacement::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPLANE
py::class_<RWStepGeom_RWPlane> cls_RWStepGeom_RWPlane(mod, "RWStepGeom_RWPlane", "Read & Write Module for Plane");

// Constructors
cls_RWStepGeom_RWPlane.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPlane.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPlane::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPlane.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPlane::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPlane.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPlane::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPlane.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPlane::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPlane.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPlane::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPlane.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPlane::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPlane.def("ReadStep", (void (RWStepGeom_RWPlane::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Plane> &) const) &RWStepGeom_RWPlane::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPlane.def("WriteStep", (void (RWStepGeom_RWPlane::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Plane> &) const) &RWStepGeom_RWPlane::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPlane.def("Share", (void (RWStepGeom_RWPlane::*)(const opencascade::handle<StepGeom_Plane> &, Interface_EntityIterator &) const) &RWStepGeom_RWPlane::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPOINT
py::class_<RWStepGeom_RWPoint> cls_RWStepGeom_RWPoint(mod, "RWStepGeom_RWPoint", "Read & Write Module for Point");

// Constructors
cls_RWStepGeom_RWPoint.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPoint.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPoint::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPoint.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPoint::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPoint.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPoint::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPoint.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPoint::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPoint.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPoint.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPoint::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPoint.def("ReadStep", (void (RWStepGeom_RWPoint::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Point> &) const) &RWStepGeom_RWPoint::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPoint.def("WriteStep", (void (RWStepGeom_RWPoint::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Point> &) const) &RWStepGeom_RWPoint::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWPOINTONCURVE
py::class_<RWStepGeom_RWPointOnCurve> cls_RWStepGeom_RWPointOnCurve(mod, "RWStepGeom_RWPointOnCurve", "Read & Write Module for PointOnCurve");

// Constructors
cls_RWStepGeom_RWPointOnCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPointOnCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPointOnCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointOnCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPointOnCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPointOnCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointOnCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPointOnCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPointOnCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPointOnCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPointOnCurve.def("ReadStep", (void (RWStepGeom_RWPointOnCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_PointOnCurve> &) const) &RWStepGeom_RWPointOnCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPointOnCurve.def("WriteStep", (void (RWStepGeom_RWPointOnCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_PointOnCurve> &) const) &RWStepGeom_RWPointOnCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPointOnCurve.def("Share", (void (RWStepGeom_RWPointOnCurve::*)(const opencascade::handle<StepGeom_PointOnCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWPointOnCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPOINTONSURFACE
py::class_<RWStepGeom_RWPointOnSurface> cls_RWStepGeom_RWPointOnSurface(mod, "RWStepGeom_RWPointOnSurface", "Read & Write Module for PointOnSurface");

// Constructors
cls_RWStepGeom_RWPointOnSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPointOnSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPointOnSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointOnSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPointOnSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPointOnSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointOnSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPointOnSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPointOnSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPointOnSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPointOnSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPointOnSurface.def("ReadStep", (void (RWStepGeom_RWPointOnSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_PointOnSurface> &) const) &RWStepGeom_RWPointOnSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPointOnSurface.def("WriteStep", (void (RWStepGeom_RWPointOnSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_PointOnSurface> &) const) &RWStepGeom_RWPointOnSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPointOnSurface.def("Share", (void (RWStepGeom_RWPointOnSurface::*)(const opencascade::handle<StepGeom_PointOnSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWPointOnSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPOINTREPLICA
py::class_<RWStepGeom_RWPointReplica> cls_RWStepGeom_RWPointReplica(mod, "RWStepGeom_RWPointReplica", "Read & Write Module for PointReplica");

// Constructors
cls_RWStepGeom_RWPointReplica.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPointReplica.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPointReplica::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointReplica.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPointReplica::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointReplica.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPointReplica::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPointReplica.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPointReplica::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPointReplica.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPointReplica::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPointReplica.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPointReplica::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPointReplica.def("ReadStep", (void (RWStepGeom_RWPointReplica::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_PointReplica> &) const) &RWStepGeom_RWPointReplica::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPointReplica.def("WriteStep", (void (RWStepGeom_RWPointReplica::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_PointReplica> &) const) &RWStepGeom_RWPointReplica::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPointReplica.def("Share", (void (RWStepGeom_RWPointReplica::*)(const opencascade::handle<StepGeom_PointReplica> &, Interface_EntityIterator &) const) &RWStepGeom_RWPointReplica::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWPOLYLINE
py::class_<RWStepGeom_RWPolyline> cls_RWStepGeom_RWPolyline(mod, "RWStepGeom_RWPolyline", "Read & Write Module for Polyline");

// Constructors
cls_RWStepGeom_RWPolyline.def(py::init<>());

// Methods
// cls_RWStepGeom_RWPolyline.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWPolyline::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWPolyline.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWPolyline::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPolyline.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWPolyline::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWPolyline.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWPolyline::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWPolyline.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWPolyline::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWPolyline.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWPolyline::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWPolyline.def("ReadStep", (void (RWStepGeom_RWPolyline::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Polyline> &) const) &RWStepGeom_RWPolyline::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWPolyline.def("WriteStep", (void (RWStepGeom_RWPolyline::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Polyline> &) const) &RWStepGeom_RWPolyline::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWPolyline.def("Share", (void (RWStepGeom_RWPolyline::*)(const opencascade::handle<StepGeom_Polyline> &, Interface_EntityIterator &) const) &RWStepGeom_RWPolyline::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWQUASIUNIFORMCURVE
py::class_<RWStepGeom_RWQuasiUniformCurve> cls_RWStepGeom_RWQuasiUniformCurve(mod, "RWStepGeom_RWQuasiUniformCurve", "Read & Write Module for QuasiUniformCurve");

// Constructors
cls_RWStepGeom_RWQuasiUniformCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWQuasiUniformCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWQuasiUniformCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWQuasiUniformCurve.def("ReadStep", (void (RWStepGeom_RWQuasiUniformCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_QuasiUniformCurve> &) const) &RWStepGeom_RWQuasiUniformCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformCurve.def("WriteStep", (void (RWStepGeom_RWQuasiUniformCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_QuasiUniformCurve> &) const) &RWStepGeom_RWQuasiUniformCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformCurve.def("Share", (void (RWStepGeom_RWQuasiUniformCurve::*)(const opencascade::handle<StepGeom_QuasiUniformCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWQuasiUniformCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWQUASIUNIFORMCURVEANDRATIONALBSPLINECURVE
py::class_<RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve> cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve(mod, "RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve", "Read & Write Module for QuasiUniformCurveAndRationalBSplineCurve");

// Constructors
cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def("ReadStep", (void (RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def("WriteStep", (void (RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.def("Share", (void (RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWQUASIUNIFORMSURFACE
py::class_<RWStepGeom_RWQuasiUniformSurface> cls_RWStepGeom_RWQuasiUniformSurface(mod, "RWStepGeom_RWQuasiUniformSurface", "Read & Write Module for QuasiUniformSurface");

// Constructors
cls_RWStepGeom_RWQuasiUniformSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWQuasiUniformSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWQuasiUniformSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWQuasiUniformSurface.def("ReadStep", (void (RWStepGeom_RWQuasiUniformSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_QuasiUniformSurface> &) const) &RWStepGeom_RWQuasiUniformSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformSurface.def("WriteStep", (void (RWStepGeom_RWQuasiUniformSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_QuasiUniformSurface> &) const) &RWStepGeom_RWQuasiUniformSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformSurface.def("Share", (void (RWStepGeom_RWQuasiUniformSurface::*)(const opencascade::handle<StepGeom_QuasiUniformSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWQuasiUniformSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWQUASIUNIFORMSURFACEANDRATIONALBSPLINESURFACE
py::class_<RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface> cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface(mod, "RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface", "Read & Write Module for QuasiUniformSurfaceAndRationalBSplineSurface");

// Constructors
cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def("ReadStep", (void (RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def("WriteStep", (void (RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.def("Share", (void (RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWRATIONALBSPLINECURVE
py::class_<RWStepGeom_RWRationalBSplineCurve> cls_RWStepGeom_RWRationalBSplineCurve(mod, "RWStepGeom_RWRationalBSplineCurve", "Read & Write Module for RationalBSplineCurve Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWRationalBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWRationalBSplineCurve.def("ReadStep", (void (RWStepGeom_RWRationalBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_RationalBSplineCurve> &) const) &RWStepGeom_RWRationalBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWRationalBSplineCurve.def("WriteStep", (void (RWStepGeom_RWRationalBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_RationalBSplineCurve> &) const) &RWStepGeom_RWRationalBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWRationalBSplineCurve.def("Share", (void (RWStepGeom_RWRationalBSplineCurve::*)(const opencascade::handle<StepGeom_RationalBSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWRationalBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWRationalBSplineCurve.def("Check", (void (RWStepGeom_RWRationalBSplineCurve::*)(const opencascade::handle<StepGeom_RationalBSplineCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWRationalBSplineCurve::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWRATIONALBSPLINESURFACE
py::class_<RWStepGeom_RWRationalBSplineSurface> cls_RWStepGeom_RWRationalBSplineSurface(mod, "RWStepGeom_RWRationalBSplineSurface", "Read & Write Module for RationalBSplineSurface Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWRationalBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWRationalBSplineSurface.def("ReadStep", (void (RWStepGeom_RWRationalBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_RationalBSplineSurface> &) const) &RWStepGeom_RWRationalBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWRationalBSplineSurface.def("WriteStep", (void (RWStepGeom_RWRationalBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_RationalBSplineSurface> &) const) &RWStepGeom_RWRationalBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWRationalBSplineSurface.def("Share", (void (RWStepGeom_RWRationalBSplineSurface::*)(const opencascade::handle<StepGeom_RationalBSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWRationalBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWRationalBSplineSurface.def("Check", (void (RWStepGeom_RWRationalBSplineSurface::*)(const opencascade::handle<StepGeom_RationalBSplineSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWRationalBSplineSurface::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWRECTANGULARCOMPOSITESURFACE
py::class_<RWStepGeom_RWRectangularCompositeSurface> cls_RWStepGeom_RWRectangularCompositeSurface(mod, "RWStepGeom_RWRectangularCompositeSurface", "Read & Write Module for RectangularCompositeSurface");

// Constructors
cls_RWStepGeom_RWRectangularCompositeSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWRectangularCompositeSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWRectangularCompositeSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWRectangularCompositeSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWRectangularCompositeSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWRectangularCompositeSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularCompositeSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWRectangularCompositeSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWRectangularCompositeSurface.def("ReadStep", (void (RWStepGeom_RWRectangularCompositeSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_RectangularCompositeSurface> &) const) &RWStepGeom_RWRectangularCompositeSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWRectangularCompositeSurface.def("WriteStep", (void (RWStepGeom_RWRectangularCompositeSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_RectangularCompositeSurface> &) const) &RWStepGeom_RWRectangularCompositeSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWRectangularCompositeSurface.def("Share", (void (RWStepGeom_RWRectangularCompositeSurface::*)(const opencascade::handle<StepGeom_RectangularCompositeSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWRectangularCompositeSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWRECTANGULARTRIMMEDSURFACE
py::class_<RWStepGeom_RWRectangularTrimmedSurface> cls_RWStepGeom_RWRectangularTrimmedSurface(mod, "RWStepGeom_RWRectangularTrimmedSurface", "Read & Write Module for RectangularTrimmedSurface");

// Constructors
cls_RWStepGeom_RWRectangularTrimmedSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWRectangularTrimmedSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWRectangularTrimmedSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWRectangularTrimmedSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWRectangularTrimmedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWRectangularTrimmedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWRectangularTrimmedSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWRectangularTrimmedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWRectangularTrimmedSurface.def("ReadStep", (void (RWStepGeom_RWRectangularTrimmedSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_RectangularTrimmedSurface> &) const) &RWStepGeom_RWRectangularTrimmedSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWRectangularTrimmedSurface.def("WriteStep", (void (RWStepGeom_RWRectangularTrimmedSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_RectangularTrimmedSurface> &) const) &RWStepGeom_RWRectangularTrimmedSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWRectangularTrimmedSurface.def("Share", (void (RWStepGeom_RWRectangularTrimmedSurface::*)(const opencascade::handle<StepGeom_RectangularTrimmedSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWRectangularTrimmedSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWREPARAMETRISEDCOMPOSITECURVESEGMENT
py::class_<RWStepGeom_RWReparametrisedCompositeCurveSegment> cls_RWStepGeom_RWReparametrisedCompositeCurveSegment(mod, "RWStepGeom_RWReparametrisedCompositeCurveSegment", "Read & Write Module for ReparametrisedCompositeCurveSegment");

// Constructors
cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def(py::init<>());

// Methods
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWReparametrisedCompositeCurveSegment::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def("ReadStep", (void (RWStepGeom_RWReparametrisedCompositeCurveSegment::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_ReparametrisedCompositeCurveSegment> &) const) &RWStepGeom_RWReparametrisedCompositeCurveSegment::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def("WriteStep", (void (RWStepGeom_RWReparametrisedCompositeCurveSegment::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_ReparametrisedCompositeCurveSegment> &) const) &RWStepGeom_RWReparametrisedCompositeCurveSegment::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWReparametrisedCompositeCurveSegment.def("Share", (void (RWStepGeom_RWReparametrisedCompositeCurveSegment::*)(const opencascade::handle<StepGeom_ReparametrisedCompositeCurveSegment> &, Interface_EntityIterator &) const) &RWStepGeom_RWReparametrisedCompositeCurveSegment::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSEAMCURVE
py::class_<RWStepGeom_RWSeamCurve> cls_RWStepGeom_RWSeamCurve(mod, "RWStepGeom_RWSeamCurve", "Read & Write Module for SeamCurve");

// Constructors
cls_RWStepGeom_RWSeamCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSeamCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSeamCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSeamCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSeamCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSeamCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSeamCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSeamCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSeamCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSeamCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSeamCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSeamCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSeamCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSeamCurve.def("ReadStep", (void (RWStepGeom_RWSeamCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SeamCurve> &) const) &RWStepGeom_RWSeamCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSeamCurve.def("WriteStep", (void (RWStepGeom_RWSeamCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SeamCurve> &) const) &RWStepGeom_RWSeamCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSeamCurve.def("Share", (void (RWStepGeom_RWSeamCurve::*)(const opencascade::handle<StepGeom_SeamCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWSeamCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSPHERICALSURFACE
py::class_<RWStepGeom_RWSphericalSurface> cls_RWStepGeom_RWSphericalSurface(mod, "RWStepGeom_RWSphericalSurface", "Read & Write Module for SphericalSurface");

// Constructors
cls_RWStepGeom_RWSphericalSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSphericalSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSphericalSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSphericalSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSphericalSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSphericalSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSphericalSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSphericalSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSphericalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSphericalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSphericalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSphericalSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSphericalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSphericalSurface.def("ReadStep", (void (RWStepGeom_RWSphericalSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SphericalSurface> &) const) &RWStepGeom_RWSphericalSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSphericalSurface.def("WriteStep", (void (RWStepGeom_RWSphericalSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SphericalSurface> &) const) &RWStepGeom_RWSphericalSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSphericalSurface.def("Share", (void (RWStepGeom_RWSphericalSurface::*)(const opencascade::handle<StepGeom_SphericalSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWSphericalSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACE
py::class_<RWStepGeom_RWSurface> cls_RWStepGeom_RWSurface(mod, "RWStepGeom_RWSurface", "Read & Write Module for Surface");

// Constructors
cls_RWStepGeom_RWSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurface.def("ReadStep", (void (RWStepGeom_RWSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Surface> &) const) &RWStepGeom_RWSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurface.def("WriteStep", (void (RWStepGeom_RWSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Surface> &) const) &RWStepGeom_RWSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));

// CLASS: RWSTEPGEOM_RWSURFACECURVE
py::class_<RWStepGeom_RWSurfaceCurve> cls_RWStepGeom_RWSurfaceCurve(mod, "RWStepGeom_RWSurfaceCurve", "Read & Write Module for SurfaceCurve");

// Constructors
cls_RWStepGeom_RWSurfaceCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfaceCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfaceCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfaceCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfaceCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfaceCurve.def("ReadStep", (void (RWStepGeom_RWSurfaceCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfaceCurve> &) const) &RWStepGeom_RWSurfaceCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceCurve.def("WriteStep", (void (RWStepGeom_RWSurfaceCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfaceCurve> &) const) &RWStepGeom_RWSurfaceCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceCurve.def("Share", (void (RWStepGeom_RWSurfaceCurve::*)(const opencascade::handle<StepGeom_SurfaceCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfaceCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACECURVEANDBOUNDEDCURVE
py::class_<RWStepGeom_RWSurfaceCurveAndBoundedCurve> cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve(mod, "RWStepGeom_RWSurfaceCurveAndBoundedCurve", "Read StepGeom_SurfaceCurveAndBoundedCurve");

// Constructors
cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def("ReadStep", (void (RWStepGeom_RWSurfaceCurveAndBoundedCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfaceCurveAndBoundedCurve> &) const) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def("WriteStep", (void (RWStepGeom_RWSurfaceCurveAndBoundedCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfaceCurveAndBoundedCurve> &) const) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceCurveAndBoundedCurve.def("Share", (void (RWStepGeom_RWSurfaceCurveAndBoundedCurve::*)(const opencascade::handle<StepGeom_SurfaceCurveAndBoundedCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfaceCurveAndBoundedCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACEOFLINEAREXTRUSION
py::class_<RWStepGeom_RWSurfaceOfLinearExtrusion> cls_RWStepGeom_RWSurfaceOfLinearExtrusion(mod, "RWStepGeom_RWSurfaceOfLinearExtrusion", "Read & Write Module for SurfaceOfLinearExtrusion");

// Constructors
cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfaceOfLinearExtrusion::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def("ReadStep", (void (RWStepGeom_RWSurfaceOfLinearExtrusion::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfaceOfLinearExtrusion> &) const) &RWStepGeom_RWSurfaceOfLinearExtrusion::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def("WriteStep", (void (RWStepGeom_RWSurfaceOfLinearExtrusion::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfaceOfLinearExtrusion> &) const) &RWStepGeom_RWSurfaceOfLinearExtrusion::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceOfLinearExtrusion.def("Share", (void (RWStepGeom_RWSurfaceOfLinearExtrusion::*)(const opencascade::handle<StepGeom_SurfaceOfLinearExtrusion> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfaceOfLinearExtrusion::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACEOFREVOLUTION
py::class_<RWStepGeom_RWSurfaceOfRevolution> cls_RWStepGeom_RWSurfaceOfRevolution(mod, "RWStepGeom_RWSurfaceOfRevolution", "Read & Write Module for SurfaceOfRevolution");

// Constructors
cls_RWStepGeom_RWSurfaceOfRevolution.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceOfRevolution::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfaceOfRevolution::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceOfRevolution::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfaceOfRevolution::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfaceOfRevolution::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfaceOfRevolution::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfaceOfRevolution.def("ReadStep", (void (RWStepGeom_RWSurfaceOfRevolution::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfaceOfRevolution> &) const) &RWStepGeom_RWSurfaceOfRevolution::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceOfRevolution.def("WriteStep", (void (RWStepGeom_RWSurfaceOfRevolution::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfaceOfRevolution> &) const) &RWStepGeom_RWSurfaceOfRevolution::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceOfRevolution.def("Share", (void (RWStepGeom_RWSurfaceOfRevolution::*)(const opencascade::handle<StepGeom_SurfaceOfRevolution> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfaceOfRevolution::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACEPATCH
py::class_<RWStepGeom_RWSurfacePatch> cls_RWStepGeom_RWSurfacePatch(mod, "RWStepGeom_RWSurfacePatch", "Read & Write Module for SurfacePatch");

// Constructors
cls_RWStepGeom_RWSurfacePatch.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfacePatch.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfacePatch::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfacePatch.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfacePatch::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfacePatch.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfacePatch::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfacePatch.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfacePatch::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfacePatch.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfacePatch::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfacePatch.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfacePatch::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfacePatch.def("ReadStep", (void (RWStepGeom_RWSurfacePatch::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfacePatch> &) const) &RWStepGeom_RWSurfacePatch::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfacePatch.def("WriteStep", (void (RWStepGeom_RWSurfacePatch::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfacePatch> &) const) &RWStepGeom_RWSurfacePatch::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfacePatch.def("Share", (void (RWStepGeom_RWSurfacePatch::*)(const opencascade::handle<StepGeom_SurfacePatch> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfacePatch::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSURFACEREPLICA
py::class_<RWStepGeom_RWSurfaceReplica> cls_RWStepGeom_RWSurfaceReplica(mod, "RWStepGeom_RWSurfaceReplica", "Read & Write Module for SurfaceReplica");

// Constructors
cls_RWStepGeom_RWSurfaceReplica.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceReplica::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSurfaceReplica::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSurfaceReplica::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSurfaceReplica::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSurfaceReplica::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSurfaceReplica.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSurfaceReplica::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSurfaceReplica.def("ReadStep", (void (RWStepGeom_RWSurfaceReplica::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SurfaceReplica> &) const) &RWStepGeom_RWSurfaceReplica::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceReplica.def("WriteStep", (void (RWStepGeom_RWSurfaceReplica::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SurfaceReplica> &) const) &RWStepGeom_RWSurfaceReplica::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSurfaceReplica.def("Share", (void (RWStepGeom_RWSurfaceReplica::*)(const opencascade::handle<StepGeom_SurfaceReplica> &, Interface_EntityIterator &) const) &RWStepGeom_RWSurfaceReplica::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWSWEPTSURFACE
py::class_<RWStepGeom_RWSweptSurface> cls_RWStepGeom_RWSweptSurface(mod, "RWStepGeom_RWSweptSurface", "Read & Write Module for SweptSurface");

// Constructors
cls_RWStepGeom_RWSweptSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWSweptSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWSweptSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWSweptSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWSweptSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSweptSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWSweptSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWSweptSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWSweptSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWSweptSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWSweptSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWSweptSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWSweptSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWSweptSurface.def("ReadStep", (void (RWStepGeom_RWSweptSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_SweptSurface> &) const) &RWStepGeom_RWSweptSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWSweptSurface.def("WriteStep", (void (RWStepGeom_RWSweptSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_SweptSurface> &) const) &RWStepGeom_RWSweptSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWSweptSurface.def("Share", (void (RWStepGeom_RWSweptSurface::*)(const opencascade::handle<StepGeom_SweptSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWSweptSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWTOROIDALSURFACE
py::class_<RWStepGeom_RWToroidalSurface> cls_RWStepGeom_RWToroidalSurface(mod, "RWStepGeom_RWToroidalSurface", "Read & Write Module for ToroidalSurface Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWToroidalSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWToroidalSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWToroidalSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWToroidalSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWToroidalSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWToroidalSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWToroidalSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWToroidalSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWToroidalSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWToroidalSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWToroidalSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWToroidalSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWToroidalSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWToroidalSurface.def("ReadStep", (void (RWStepGeom_RWToroidalSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_ToroidalSurface> &) const) &RWStepGeom_RWToroidalSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWToroidalSurface.def("WriteStep", (void (RWStepGeom_RWToroidalSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_ToroidalSurface> &) const) &RWStepGeom_RWToroidalSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWToroidalSurface.def("Share", (void (RWStepGeom_RWToroidalSurface::*)(const opencascade::handle<StepGeom_ToroidalSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWToroidalSurface::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWToroidalSurface.def("Check", (void (RWStepGeom_RWToroidalSurface::*)(const opencascade::handle<StepGeom_ToroidalSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWToroidalSurface::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));

// CLASS: RWSTEPGEOM_RWTRIMMEDCURVE
py::class_<RWStepGeom_RWTrimmedCurve> cls_RWStepGeom_RWTrimmedCurve(mod, "RWStepGeom_RWTrimmedCurve", "Read & Write Module for TrimmedCurve");

// Constructors
cls_RWStepGeom_RWTrimmedCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWTrimmedCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWTrimmedCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWTrimmedCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWTrimmedCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWTrimmedCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWTrimmedCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWTrimmedCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWTrimmedCurve.def("ReadStep", (void (RWStepGeom_RWTrimmedCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_TrimmedCurve> &) const) &RWStepGeom_RWTrimmedCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWTrimmedCurve.def("WriteStep", (void (RWStepGeom_RWTrimmedCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_TrimmedCurve> &) const) &RWStepGeom_RWTrimmedCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWTrimmedCurve.def("Share", (void (RWStepGeom_RWTrimmedCurve::*)(const opencascade::handle<StepGeom_TrimmedCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWTrimmedCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWUNIFORMCURVE
py::class_<RWStepGeom_RWUniformCurve> cls_RWStepGeom_RWUniformCurve(mod, "RWStepGeom_RWUniformCurve", "Read & Write Module for UniformCurve");

// Constructors
cls_RWStepGeom_RWUniformCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWUniformCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWUniformCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWUniformCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWUniformCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWUniformCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWUniformCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWUniformCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWUniformCurve.def("ReadStep", (void (RWStepGeom_RWUniformCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_UniformCurve> &) const) &RWStepGeom_RWUniformCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWUniformCurve.def("WriteStep", (void (RWStepGeom_RWUniformCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_UniformCurve> &) const) &RWStepGeom_RWUniformCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWUniformCurve.def("Share", (void (RWStepGeom_RWUniformCurve::*)(const opencascade::handle<StepGeom_UniformCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWUniformCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWUNIFORMCURVEANDRATIONALBSPLINECURVE
py::class_<RWStepGeom_RWUniformCurveAndRationalBSplineCurve> cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve(mod, "RWStepGeom_RWUniformCurveAndRationalBSplineCurve", "Read & Write Module for UniformCurveAndRationalBSplineCurve");

// Constructors
cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def(py::init<>());

// Methods
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def("ReadStep", (void (RWStepGeom_RWUniformCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_UniformCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def("WriteStep", (void (RWStepGeom_RWUniformCurveAndRationalBSplineCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_UniformCurveAndRationalBSplineCurve> &) const) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWUniformCurveAndRationalBSplineCurve.def("Share", (void (RWStepGeom_RWUniformCurveAndRationalBSplineCurve::*)(const opencascade::handle<StepGeom_UniformCurveAndRationalBSplineCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWUniformCurveAndRationalBSplineCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWUNIFORMSURFACE
py::class_<RWStepGeom_RWUniformSurface> cls_RWStepGeom_RWUniformSurface(mod, "RWStepGeom_RWUniformSurface", "Read & Write Module for UniformSurface");

// Constructors
cls_RWStepGeom_RWUniformSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWUniformSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWUniformSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWUniformSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWUniformSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWUniformSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWUniformSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWUniformSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWUniformSurface.def("ReadStep", (void (RWStepGeom_RWUniformSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_UniformSurface> &) const) &RWStepGeom_RWUniformSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWUniformSurface.def("WriteStep", (void (RWStepGeom_RWUniformSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_UniformSurface> &) const) &RWStepGeom_RWUniformSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWUniformSurface.def("Share", (void (RWStepGeom_RWUniformSurface::*)(const opencascade::handle<StepGeom_UniformSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWUniformSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWUNIFORMSURFACEANDRATIONALBSPLINESURFACE
py::class_<RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface> cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface(mod, "RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface", "Read & Write Module for UniformSurfaceAndRationalBSplineSurface");

// Constructors
cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def(py::init<>());

// Methods
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def("ReadStep", (void (RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_UniformSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def("WriteStep", (void (RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_UniformSurfaceAndRationalBSplineSurface> &) const) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.def("Share", (void (RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::*)(const opencascade::handle<StepGeom_UniformSurfaceAndRationalBSplineSurface> &, Interface_EntityIterator &) const) &RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface::Share, "None", py::arg("ent"), py::arg("iter"));

// CLASS: RWSTEPGEOM_RWVECTOR
py::class_<RWStepGeom_RWVector> cls_RWStepGeom_RWVector(mod, "RWStepGeom_RWVector", "Read & Write Module for Vector Check added by CKY , 7-OCT-1996");

// Constructors
cls_RWStepGeom_RWVector.def(py::init<>());

// Methods
// cls_RWStepGeom_RWVector.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWVector::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWVector.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWVector::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWVector.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWVector::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWVector.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWVector::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWVector.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWVector::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWVector.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWVector::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWVector.def("ReadStep", (void (RWStepGeom_RWVector::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_Vector> &) const) &RWStepGeom_RWVector::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWVector.def("WriteStep", (void (RWStepGeom_RWVector::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_Vector> &) const) &RWStepGeom_RWVector::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWVector.def("Share", (void (RWStepGeom_RWVector::*)(const opencascade::handle<StepGeom_Vector> &, Interface_EntityIterator &) const) &RWStepGeom_RWVector::Share, "None", py::arg("ent"), py::arg("iter"));
cls_RWStepGeom_RWVector.def("Check", (void (RWStepGeom_RWVector::*)(const opencascade::handle<StepGeom_Vector> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &RWStepGeom_RWVector::Check, "None", py::arg("ent"), py::arg("shares"), py::arg("ach"));


}
