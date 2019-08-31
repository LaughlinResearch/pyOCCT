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
#include <Convert_ParameterisationType.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <gp_Pnt2d.hxx>
#include <Standard_Handle.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <Convert_ConicToBSplineCurve.hxx>
#include <gp_Circ2d.hxx>
#include <Convert_CircleToBSplineCurve.hxx>
#include <TColgp_SequenceOfArray1OfPnt2d.hxx>
#include <Convert_SequenceOfArray1OfPoles2d.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <TColStd_SequenceOfInteger.hxx>
#include <Convert_CompBezierCurves2dToBSplineCurve2d.hxx>
#include <NCollection_Sequence.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <Convert_SequenceOfArray1OfPoles.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <Convert_CompBezierCurvesToBSplineCurve.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <Convert_CompPolynomialToPoles.hxx>
#include <gp_Pnt.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <Convert_ElementarySurfaceToBSplineSurface.hxx>
#include <gp_Cone.hxx>
#include <Convert_ConeToBSplineSurface.hxx>
#include <Convert_CosAndSinEvalFunction.hxx>
#include <gp_Cylinder.hxx>
#include <Convert_CylinderToBSplineSurface.hxx>
#include <gp_Elips2d.hxx>
#include <Convert_EllipseToBSplineCurve.hxx>
#include <TColStd_HArray2OfInteger.hxx>
#include <TColgp_HArray2OfPnt.hxx>
#include <Convert_GridPolynomialToPoles.hxx>
#include <gp_Hypr2d.hxx>
#include <Convert_HyperbolaToBSplineCurve.hxx>
#include <gp_Parab2d.hxx>
#include <Convert_ParabolaToBSplineCurve.hxx>
#include <gp_Sphere.hxx>
#include <Convert_SphereToBSplineSurface.hxx>
#include <gp_Torus.hxx>
#include <Convert_TorusToBSplineSurface.hxx>
#include <bind_NCollection_Sequence.hxx>

PYBIND11_MODULE(Convert, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.gp");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.NCollection");

// ENUM: CONVERT_PARAMETERISATIONTYPE
py::enum_<Convert_ParameterisationType>(mod, "Convert_ParameterisationType", "Identifies a type of parameterization of a circle or ellipse represented as a BSpline curve. For a circle with a center C and a radius R (for example a Geom2d_Circle or a Geom_Circle), the natural parameterization is angular. It uses the angle Theta made by the vector CM with the 'X Axis' of the circle's local coordinate system as parameter for the current point M. The coordinates of the point M are as follows: X = R *cos ( Theta ) y = R * sin ( Theta ) Similarly, for an ellipse with a center C, a major radius R and a minor radius r, the circle Circ with center C and radius R (and located in the same plane as the ellipse) lends its natural angular parameterization to the ellipse. This is achieved by an affine transformation in the plane of the ellipse, in the ratio r / R, about the 'X Axis' of its local coordinate system. The coordinates of the current point M are as follows: X = R * cos ( Theta ) y = r * sin ( Theta ) The process of converting a circle or an ellipse into a rational or non-rational BSpline curve transforms the Theta angular parameter into a parameter t. This ensures the rational or polynomial parameterization of the resulting BSpline curve. Several types of parametric transformations are available. TgtThetaOver2 The most usual method is Convert_TgtThetaOver2 where the parameter t on the BSpline curve is obtained by means of transformation of the following type: t = tan ( Theta / 2 ) The result of this definition is: cos ( Theta ) = ( 1. - t**2 ) / ( 1. + t**2 ) sin ( Theta ) = 2. * t / ( 1. + t**2 ) which ensures the rational parameterization of the circle or the ellipse. However, this is not the most suitable parameterization method where the arc of the circle or ellipse has a large opening angle. In such cases, the curve will be represented by a BSpline with intermediate knots. Each span, i.e. each portion of curve between two different knot values, will use parameterization of this type. The number of spans is calculated using the following rule: ( 1.2 * Delta / Pi ) + 1 where Delta is equal to the opening angle (in radians) of the arc of the circle (Delta is equal to 2.* Pi in the case of a complete circle). The resulting BSpline curve is 'exact', i.e. computing any point of parameter t on the BSpline curve gives an exact point on the circle or the ellipse. TgtThetaOver2_N Where N is equal to 1, 2, 3 or 4, this ensures the same type of parameterization as Convert_TgtThetaOver2 but sets the number of spans in the resulting BSpline curve to N rather than allowing the algorithm to make this calculation. However, the opening angle Delta (parametric angle, given in radians) of the arc of the circle (or of the ellipse) must comply with the following: - Delta <= 0.9999 * Pi for the Convert_TgtThetaOver2_1 method, or - Delta <= 1.9999 * Pi for the Convert_TgtThetaOver2_2 method. QuasiAngular The Convert_QuasiAngular method of parameterization uses a different type of rational parameterization. This method ensures that the parameter t along the resulting BSpline curve is very close to the natural parameterization angle Theta of the circle or ellipse (i.e. which uses the functions sin ( Theta ) and cos ( Theta ). The resulting BSpline curve is 'exact', i.e. computing any point of parameter t on the BSpline curve gives an exact point on the circle or the ellipse. RationalC1 The Convert_RationalC1 method of parameterization uses a further type of rational parameterization. This method ensures that the equation relating to the resulting BSpline curve has a 'C1' continuous denominator, which is not the case with the above methods. RationalC1 enhances the degree of continuity at the junction point of the different spans of the curve. The resulting BSpline curve is 'exact', i.e. computing any point of parameter t on the BSpline curve gives an exact point on the circle or the ellipse. Polynomial The Convert_Polynomial method is used to produce polynomial (i.e. non-rational) parameterization of the resulting BSpline curve with 8 poles (i.e. a polynomial degree equal to 7). However, the result is an approximation of the circle or ellipse (i.e. computing the point of parameter t on the BSpline curve does not give an exact point on the circle or the ellipse).")
	.value("Convert_TgtThetaOver2", Convert_ParameterisationType::Convert_TgtThetaOver2)
	.value("Convert_TgtThetaOver2_1", Convert_ParameterisationType::Convert_TgtThetaOver2_1)
	.value("Convert_TgtThetaOver2_2", Convert_ParameterisationType::Convert_TgtThetaOver2_2)
	.value("Convert_TgtThetaOver2_3", Convert_ParameterisationType::Convert_TgtThetaOver2_3)
	.value("Convert_TgtThetaOver2_4", Convert_ParameterisationType::Convert_TgtThetaOver2_4)
	.value("Convert_QuasiAngular", Convert_ParameterisationType::Convert_QuasiAngular)
	.value("Convert_RationalC1", Convert_ParameterisationType::Convert_RationalC1)
	.value("Convert_Polynomial", Convert_ParameterisationType::Convert_Polynomial)
	.export_values();


// CLASS: CONVERT_CONICTOBSPLINECURVE
py::class_<Convert_ConicToBSplineCurve> cls_Convert_ConicToBSplineCurve(mod, "Convert_ConicToBSplineCurve", "Root class for algorithms which convert a conic curve into a BSpline curve (CircleToBSplineCurve, EllipseToBSplineCurve, HyperbolaToBSplineCurve, ParabolaToBSplineCurve). These algorithms all work on 2D curves from the gp package and compute all the data needed to construct a BSpline curve equivalent to the conic curve. This data consists of: - the degree of the curve, - the periodic characteristics of the curve, - a poles table with associated weights, - a knots table with associated multiplicities. The abstract class ConicToBSplineCurve provides a framework for storing and consulting this computed data. The data may then be used to construct a Geom2d_BSplineCurve curvSuper class of the following classes : This abstract class implements the methods to get the geometric representation of the B-spline curve equivalent to the conic. The B-spline is computed at the creation time in the sub classes. The B-spline curve is defined with its degree, its control points (Poles), its weights, its knots and their multiplicity. All the geometric entities used in this package are defined in 2D space. KeyWords : Convert, Conic, BSplineCurve, 2D.");

// Methods
// cls_Convert_ConicToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_ConicToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_ConicToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_ConicToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_ConicToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_ConicToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_ConicToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_ConicToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_ConicToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_ConicToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_ConicToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_ConicToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_ConicToBSplineCurve.def("Degree", (Standard_Integer (Convert_ConicToBSplineCurve::*)() const) &Convert_ConicToBSplineCurve::Degree, "Returns the degree of the BSpline curve whose data is computed in this framework.");
cls_Convert_ConicToBSplineCurve.def("NbPoles", (Standard_Integer (Convert_ConicToBSplineCurve::*)() const) &Convert_ConicToBSplineCurve::NbPoles, "Returns the number of poles of the BSpline curve whose data is computed in this framework.");
cls_Convert_ConicToBSplineCurve.def("NbKnots", (Standard_Integer (Convert_ConicToBSplineCurve::*)() const) &Convert_ConicToBSplineCurve::NbKnots, "Returns the number of knots of the BSpline curve whose data is computed in this framework.");
cls_Convert_ConicToBSplineCurve.def("IsPeriodic", (Standard_Boolean (Convert_ConicToBSplineCurve::*)() const) &Convert_ConicToBSplineCurve::IsPeriodic, "Returns true if the BSpline curve whose data is computed in this framework is periodic.");
cls_Convert_ConicToBSplineCurve.def("Pole", (gp_Pnt2d (Convert_ConicToBSplineCurve::*)(const Standard_Integer) const) &Convert_ConicToBSplineCurve::Pole, "Returns the pole of index Index to the poles table of the BSpline curve whose data is computed in this framework. Exceptions Standard_OutOfRange if Index is outside the bounds of the poles table of the BSpline curve whose data is computed in this framework.", py::arg("Index"));
cls_Convert_ConicToBSplineCurve.def("Weight", (Standard_Real (Convert_ConicToBSplineCurve::*)(const Standard_Integer) const) &Convert_ConicToBSplineCurve::Weight, "Returns the weight of the pole of index Index to the poles table of the BSpline curve whose data is computed in this framework. Exceptions Standard_OutOfRange if Index is outside the bounds of the poles table of the BSpline curve whose data is computed in this framework.", py::arg("Index"));
cls_Convert_ConicToBSplineCurve.def("Knot", (Standard_Real (Convert_ConicToBSplineCurve::*)(const Standard_Integer) const) &Convert_ConicToBSplineCurve::Knot, "Returns the knot of index Index to the knots table of the BSpline curve whose data is computed in this framework. Exceptions Standard_OutOfRange if Index is outside the bounds of the knots table of the BSpline curve whose data is computed in this framework.", py::arg("Index"));
cls_Convert_ConicToBSplineCurve.def("Multiplicity", (Standard_Integer (Convert_ConicToBSplineCurve::*)(const Standard_Integer) const) &Convert_ConicToBSplineCurve::Multiplicity, "Returns the multiplicity of the knot of index Index to the knots table of the BSpline curve whose data is computed in this framework. Exceptions Standard_OutOfRange if Index is outside the bounds of the knots table of the BSpline curve whose data is computed in this framework.", py::arg("Index"));
cls_Convert_ConicToBSplineCurve.def("BuildCosAndSin", [](Convert_ConicToBSplineCurve &self, const Convert_ParameterisationType Parametrisation, opencascade::handle<TColStd_HArray1OfReal> & CosNumerator, opencascade::handle<TColStd_HArray1OfReal> & SinNumerator, opencascade::handle<TColStd_HArray1OfReal> & Denominator, Standard_Integer & Degree, opencascade::handle<TColStd_HArray1OfReal> & Knots, opencascade::handle<TColStd_HArray1OfInteger> & Mults){ self.BuildCosAndSin(Parametrisation, CosNumerator, SinNumerator, Denominator, Degree, Knots, Mults); return Degree; }, "None", py::arg("Parametrisation"), py::arg("CosNumerator"), py::arg("SinNumerator"), py::arg("Denominator"), py::arg("Degree"), py::arg("Knots"), py::arg("Mults"));
cls_Convert_ConicToBSplineCurve.def("BuildCosAndSin", [](Convert_ConicToBSplineCurve &self, const Convert_ParameterisationType Parametrisation, const Standard_Real UFirst, const Standard_Real ULast, opencascade::handle<TColStd_HArray1OfReal> & CosNumerator, opencascade::handle<TColStd_HArray1OfReal> & SinNumerator, opencascade::handle<TColStd_HArray1OfReal> & Denominator, Standard_Integer & Degree, opencascade::handle<TColStd_HArray1OfReal> & Knots, opencascade::handle<TColStd_HArray1OfInteger> & Mults){ self.BuildCosAndSin(Parametrisation, UFirst, ULast, CosNumerator, SinNumerator, Denominator, Degree, Knots, Mults); return Degree; }, "None", py::arg("Parametrisation"), py::arg("UFirst"), py::arg("ULast"), py::arg("CosNumerator"), py::arg("SinNumerator"), py::arg("Denominator"), py::arg("Degree"), py::arg("Knots"), py::arg("Mults"));

// CLASS: CONVERT_CIRCLETOBSPLINECURVE
py::class_<Convert_CircleToBSplineCurve, Convert_ConicToBSplineCurve> cls_Convert_CircleToBSplineCurve(mod, "Convert_CircleToBSplineCurve", "This algorithm converts a circle into a rational B-spline curve. The circle is a Circ2d from package gp and its parametrization is : P (U) = Loc + R * (Cos(U) * Xdir + Sin(U) * YDir) where Loc is the center of the circle Xdir and Ydir are the normalized directions of the local cartesian coordinate system of the circle. The parametrization range for the circle is U [0, 2Pi].");

// Constructors
cls_Convert_CircleToBSplineCurve.def(py::init<const gp_Circ2d &>(), py::arg("C"));
cls_Convert_CircleToBSplineCurve.def(py::init<const gp_Circ2d &, const Convert_ParameterisationType>(), py::arg("C"), py::arg("Parameterisation"));
cls_Convert_CircleToBSplineCurve.def(py::init<const gp_Circ2d &, const Standard_Real, const Standard_Real>(), py::arg("C"), py::arg("U1"), py::arg("U2"));
cls_Convert_CircleToBSplineCurve.def(py::init<const gp_Circ2d &, const Standard_Real, const Standard_Real, const Convert_ParameterisationType>(), py::arg("C"), py::arg("U1"), py::arg("U2"), py::arg("Parameterisation"));

// Methods
// cls_Convert_CircleToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_CircleToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_CircleToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_CircleToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_CircleToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_CircleToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_CircleToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_CircleToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_CircleToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_CircleToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_CircleToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_CircleToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));

// TYPEDEF: CONVERT_SEQUENCEOFARRAY1OFPOLES2D
bind_NCollection_Sequence<opencascade::handle<TColgp_HArray1OfPnt2d> >(mod, "Convert_SequenceOfArray1OfPoles2d", py::module_local());

// CLASS: CONVERT_COMPBEZIERCURVES2DTOBSPLINECURVE2D
py::class_<Convert_CompBezierCurves2dToBSplineCurve2d> cls_Convert_CompBezierCurves2dToBSplineCurve2d(mod, "Convert_CompBezierCurves2dToBSplineCurve2d", "Converts a list of connecting Bezier Curves 2d to a BSplineCurve 2d. if possible, the continuity of the BSpline will be increased to more than C0.");

// Constructors
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def(py::init<>());
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def(py::init<const Standard_Real>(), py::arg("AngularTolerance"));

// Methods
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator new_", (void * (*)(size_t)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator new, "None", py::arg("theSize"));
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator delete_", (void (*)(void *)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator delete, "None", py::arg("theAddress"));
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator new[]_", (void * (*)(size_t)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator new[], "None", py::arg("theSize"));
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator delete[]_", (void (*)(void *)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_CompBezierCurves2dToBSplineCurve2d.def_static("operator delete_", (void (*)(void *, void *)) &Convert_CompBezierCurves2dToBSplineCurve2d::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("AddCurve", (void (Convert_CompBezierCurves2dToBSplineCurve2d::*)(const TColgp_Array1OfPnt2d &)) &Convert_CompBezierCurves2dToBSplineCurve2d::AddCurve, "Adds the Bezier curve defined by the table of poles Poles, to the sequence (still contained in this framework) of adjacent Bezier curves to be converted into a BSpline curve. Only polynomial (i.e. non-rational) Bezier curves are converted using this framework. If this is not the first call to the function (i.e. if this framework still contains data in its sequence of Bezier curves), the degree of continuity of the BSpline curve will be increased at the time of computation at the first point of the added Bezier curve (i.e. the first point of the Poles table). This will be the case if the tangent vector of the curve at this point is parallel to the tangent vector at the end point of the preceding Bezier curve in the sequence of Bezier curves still contained in this framework. An angular tolerance given at the time of construction of this framework, will be used to check the parallelism of the two tangent vectors. This checking procedure, and all the relative computations will be performed by the function Perform. When the sequence of adjacent Bezier curves is complete, use the following functions: - Perform to compute the data needed to build the BSpline curve, - and the available consultation functions to access the computed data. This data may be used to construct the BSpline curve. Warning The sequence of Bezier curves treated by this framework is automatically initialized with the first Bezier curve when the function is first called. During subsequent use of this function, ensure that the first point of the added Bezier curve (i.e. the first point of the Poles table) is coincident with the last point of the sequence (i.e. the last point of the preceding Bezier curve in the sequence) of Bezier curves still contained in this framework. An error may occur at the time of computation if this condition is not satisfied. Particular care must be taken with respect to the above, as this condition is not checked either when defining the sequence of Bezier curves or at the time of computation.", py::arg("Poles"));
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("Perform", (void (Convert_CompBezierCurves2dToBSplineCurve2d::*)()) &Convert_CompBezierCurves2dToBSplineCurve2d::Perform, "Computes all the data needed to build a BSpline curve equivalent to the sequence of adjacent Bezier curves still contained in this framework. A knot is inserted on the computed BSpline curve at the junction point of two consecutive Bezier curves. The degree of continuity of the BSpline curve will be increased at the junction point of two consecutive Bezier curves if their tangent vectors at this point are parallel. An angular tolerance given at the time of construction of this framework is used to check the parallelism of the two tangent vectors. Use the available consultation functions to access the computed data. This data may then be used to construct the BSpline curve. Warning Ensure that the curves in the sequence of Bezier curves contained in this framework are adjacent. An error may occur at the time of computation if this condition is not satisfied. Particular care must be taken with respect to the above as this condition is not checked, either when defining the Bezier curve sequence or at the time of computation.");
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("Degree", (Standard_Integer (Convert_CompBezierCurves2dToBSplineCurve2d::*)() const) &Convert_CompBezierCurves2dToBSplineCurve2d::Degree, "Returns the degree of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("NbPoles", (Standard_Integer (Convert_CompBezierCurves2dToBSplineCurve2d::*)() const) &Convert_CompBezierCurves2dToBSplineCurve2d::NbPoles, "Returns the number of poles of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("Poles", (void (Convert_CompBezierCurves2dToBSplineCurve2d::*)(TColgp_Array1OfPnt2d &) const) &Convert_CompBezierCurves2dToBSplineCurve2d::Poles, "Loads the Poles table with the poles of the BSpline curve whose data is computed in this framework. Warning - Do not use this function before the computation is performed (Perform function). - The length of the Poles array must be equal to the number of poles of the BSpline curve whose data is computed in this framework. Particular care must be taken with respect to the above, as these conditions are not checked, and an error may occur.", py::arg("Poles"));
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("NbKnots", (Standard_Integer (Convert_CompBezierCurves2dToBSplineCurve2d::*)() const) &Convert_CompBezierCurves2dToBSplineCurve2d::NbKnots, "Returns the number of knots of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurves2dToBSplineCurve2d.def("KnotsAndMults", (void (Convert_CompBezierCurves2dToBSplineCurve2d::*)(TColStd_Array1OfReal &, TColStd_Array1OfInteger &) const) &Convert_CompBezierCurves2dToBSplineCurve2d::KnotsAndMults, "Loads the Knots table with the knots and the Mults table with the corresponding multiplicities of the BSpline curve whose data is computed in this framework. Warning - Do not use this function before the computation is performed (Perform function). - The length of the Knots and Mults arrays must be equal to the number of knots in the BSpline curve whose data is computed in this framework. Particular care must be taken with respect to the above as these conditions are not checked, and an error may occur.", py::arg("Knots"), py::arg("Mults"));

// TYPEDEF: CONVERT_SEQUENCEOFARRAY1OFPOLES
bind_NCollection_Sequence<opencascade::handle<TColgp_HArray1OfPnt> >(mod, "Convert_SequenceOfArray1OfPoles", py::module_local(false));

// CLASS: CONVERT_COMPBEZIERCURVESTOBSPLINECURVE
py::class_<Convert_CompBezierCurvesToBSplineCurve> cls_Convert_CompBezierCurvesToBSplineCurve(mod, "Convert_CompBezierCurvesToBSplineCurve", "An algorithm to convert a sequence of adjacent non-rational Bezier curves into a BSpline curve. A CompBezierCurvesToBSplineCurve object provides a framework for: - defining the sequence of adjacent non-rational Bezier curves to be converted into a BSpline curve, - implementing the computation algorithm, and - consulting the results. Warning Do not attempt to convert rational Bezier curves using this type of algorithm.");

// Constructors
cls_Convert_CompBezierCurvesToBSplineCurve.def(py::init<>());
cls_Convert_CompBezierCurvesToBSplineCurve.def(py::init<const Standard_Real>(), py::arg("AngularTolerance"));

// Methods
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_CompBezierCurvesToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_CompBezierCurvesToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_CompBezierCurvesToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_CompBezierCurvesToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_CompBezierCurvesToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_CompBezierCurvesToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_CompBezierCurvesToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_CompBezierCurvesToBSplineCurve.def("AddCurve", (void (Convert_CompBezierCurvesToBSplineCurve::*)(const TColgp_Array1OfPnt &)) &Convert_CompBezierCurvesToBSplineCurve::AddCurve, "Adds the Bezier curve defined by the table of poles Poles, to the sequence (still contained in this framework) of adjacent Bezier curves to be converted into a BSpline curve. Only polynomial (i.e. non-rational) Bezier curves are converted using this framework. If this is not the first call to the function (i.e. if this framework still contains data in its Bezier curve sequence), the degree of continuity of the BSpline curve will be increased at the time of computation at the first point of the added Bezier curve (i.e. the first point of the Poles table). This will be the case if the tangent vector of the curve at this point is parallel to the tangent vector at the end point of the preceding Bezier curve in the Bezier curve sequence still contained in this framework. An angular tolerance given at the time of construction of this framework will be used to check the parallelism of the two tangent vectors. This checking procedure and all related computations will be performed by the Perform function. When the adjacent Bezier curve sequence is complete, use the following functions: - Perform to compute the data needed to build the BSpline curve, - and the available consultation functions to access the computed data. This data may be used to construct the BSpline curve. Warning The Bezier curve sequence treated by this framework is automatically initialized with the first Bezier curve when the function is first called. During subsequent use of this function, ensure that the first point of the added Bezier curve (i.e. the first point of the Poles table) is coincident with the last point of the Bezier curve sequence (i.e. the last point of the preceding Bezier curve in the sequence) still contained in this framework. An error may occur at the time of computation if this condition is not satisfied. Particular care must be taken with respect to the above, as this condition is not checked either when defining the Bezier curve sequence or at the time of computation.", py::arg("Poles"));
cls_Convert_CompBezierCurvesToBSplineCurve.def("Perform", (void (Convert_CompBezierCurvesToBSplineCurve::*)()) &Convert_CompBezierCurvesToBSplineCurve::Perform, "Computes all the data needed to build a BSpline curve equivalent to the adjacent Bezier curve sequence still contained in this framework. A knot is inserted on the computed BSpline curve at the junction point of two consecutive Bezier curves. The degree of continuity of the BSpline curve will be increased at the junction point of two consecutive Bezier curves if their tangent vectors at this point are parallel. An angular tolerance given at the time of construction of this framework is used to check the parallelism of the two tangent vectors. Use the available consultation functions to access the computed data. This data may then be used to construct the BSpline curve. Warning Make sure that the curves in the Bezier curve sequence contained in this framework are adjacent. An error may occur at the time of computation if this condition is not satisfied. Particular care must be taken with respect to the above as this condition is not checked, either when defining the Bezier curve sequence or at the time of computation.");
cls_Convert_CompBezierCurvesToBSplineCurve.def("Degree", (Standard_Integer (Convert_CompBezierCurvesToBSplineCurve::*)() const) &Convert_CompBezierCurvesToBSplineCurve::Degree, "Returns the degree of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurvesToBSplineCurve.def("NbPoles", (Standard_Integer (Convert_CompBezierCurvesToBSplineCurve::*)() const) &Convert_CompBezierCurvesToBSplineCurve::NbPoles, "Returns the number of poles of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurvesToBSplineCurve.def("Poles", (void (Convert_CompBezierCurvesToBSplineCurve::*)(TColgp_Array1OfPnt &) const) &Convert_CompBezierCurvesToBSplineCurve::Poles, "Loads the Poles table with the poles of the BSpline curve whose data is computed in this framework. Warning - Do not use this function before the computation is performed (Perform function). - The length of the Poles array must be equal to the number of poles of the BSpline curve whose data is computed in this framework. Particular care must be taken with respect to the above, as these conditions are not checked, and an error may occur.", py::arg("Poles"));
cls_Convert_CompBezierCurvesToBSplineCurve.def("NbKnots", (Standard_Integer (Convert_CompBezierCurvesToBSplineCurve::*)() const) &Convert_CompBezierCurvesToBSplineCurve::NbKnots, "Returns the number of knots of the BSpline curve whose data is computed in this framework. Warning Take particular care not to use this function before the computation is performed (Perform function), as this condition is not checked and an error may therefore occur.");
cls_Convert_CompBezierCurvesToBSplineCurve.def("KnotsAndMults", (void (Convert_CompBezierCurvesToBSplineCurve::*)(TColStd_Array1OfReal &, TColStd_Array1OfInteger &) const) &Convert_CompBezierCurvesToBSplineCurve::KnotsAndMults, "- loads the Knots table with the knots, - and loads the Mults table with the corresponding multiplicities of the BSpline curve whose data is computed in this framework. Warning - Do not use this function before the computation is performed (Perform function). - The length of the Knots and Mults arrays must be equal to the number of knots in the BSpline curve whose data is computed in this framework. Particular care must be taken with respect to the above as these conditions are not checked, and an error may occur.", py::arg("Knots"), py::arg("Mults"));

// CLASS: CONVERT_COMPPOLYNOMIALTOPOLES
py::class_<Convert_CompPolynomialToPoles> cls_Convert_CompPolynomialToPoles(mod, "Convert_CompPolynomialToPoles", "Convert a serie of Polynomial N-Dimensional Curves that are have continuity CM to an N-Dimensional Bspline Curve that has continuity CM. (to convert an function (curve) polynomial by span in a BSpline) This class uses the following arguments : NumCurves : the number of Polynomial Curves Continuity: the requested continuity for the n-dimensional Spline Dimension : the dimension of the Spline MaxDegree : maximum allowed degree for each composite polynomial segment. NumCoeffPerCurve : the number of coefficient per segments = degree - 1 Coefficients : the coefficients organized in the following way [1..<myNumPolynomials>][1..myMaxDegree +1][1..myDimension] that is : index [n,d,i] is at slot (n-1) * (myMaxDegree + 1) * myDimension + (d-1) * myDimension + i PolynomialIntervals : nth polynomial represents a polynomial between myPolynomialIntervals->Value(n,0) and myPolynomialIntervals->Value(n,1) TrueIntervals : the nth polynomial has to be mapped linearly to be defined on the following interval : myTrueIntervals->Value(n) and myTrueIntervals->Value(n+1) so that it represent adequatly the function with the required continuity");

// Constructors
cls_Convert_CompPolynomialToPoles.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray2OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &>(), py::arg("NumCurves"), py::arg("Continuity"), py::arg("Dimension"), py::arg("MaxDegree"), py::arg("NumCoeffPerCurve"), py::arg("Coefficients"), py::arg("PolynomialIntervals"), py::arg("TrueIntervals"));
cls_Convert_CompPolynomialToPoles.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const TColStd_Array1OfInteger &, const TColStd_Array1OfInteger &, const TColStd_Array1OfReal &, const TColStd_Array2OfReal &, const TColStd_Array1OfReal &>(), py::arg("NumCurves"), py::arg("Dimension"), py::arg("MaxDegree"), py::arg("Continuity"), py::arg("NumCoeffPerCurve"), py::arg("Coefficients"), py::arg("PolynomialIntervals"), py::arg("TrueIntervals"));
cls_Convert_CompPolynomialToPoles.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const TColStd_Array1OfReal &, const TColStd_Array1OfReal &, const TColStd_Array1OfReal &>(), py::arg("Dimension"), py::arg("MaxDegree"), py::arg("Degree"), py::arg("Coefficients"), py::arg("PolynomialIntervals"), py::arg("TrueIntervals"));

// Methods
// cls_Convert_CompPolynomialToPoles.def_static("operator new_", (void * (*)(size_t)) &Convert_CompPolynomialToPoles::operator new, "None", py::arg("theSize"));
// cls_Convert_CompPolynomialToPoles.def_static("operator delete_", (void (*)(void *)) &Convert_CompPolynomialToPoles::operator delete, "None", py::arg("theAddress"));
// cls_Convert_CompPolynomialToPoles.def_static("operator new[]_", (void * (*)(size_t)) &Convert_CompPolynomialToPoles::operator new[], "None", py::arg("theSize"));
// cls_Convert_CompPolynomialToPoles.def_static("operator delete[]_", (void (*)(void *)) &Convert_CompPolynomialToPoles::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_CompPolynomialToPoles.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_CompPolynomialToPoles::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_CompPolynomialToPoles.def_static("operator delete_", (void (*)(void *, void *)) &Convert_CompPolynomialToPoles::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_CompPolynomialToPoles.def("NbPoles", (Standard_Integer (Convert_CompPolynomialToPoles::*)() const) &Convert_CompPolynomialToPoles::NbPoles, "number of poles of the n-dimensional BSpline");
cls_Convert_CompPolynomialToPoles.def("Poles", (void (Convert_CompPolynomialToPoles::*)(opencascade::handle<TColStd_HArray2OfReal> &) const) &Convert_CompPolynomialToPoles::Poles, "returns the poles of the n-dimensional BSpline in the following format : [1..NumPoles][1..Dimension]", py::arg("Poles"));
cls_Convert_CompPolynomialToPoles.def("Degree", (Standard_Integer (Convert_CompPolynomialToPoles::*)() const) &Convert_CompPolynomialToPoles::Degree, "None");
cls_Convert_CompPolynomialToPoles.def("NbKnots", (Standard_Integer (Convert_CompPolynomialToPoles::*)() const) &Convert_CompPolynomialToPoles::NbKnots, "Degree of the n-dimensional Bspline");
cls_Convert_CompPolynomialToPoles.def("Knots", (void (Convert_CompPolynomialToPoles::*)(opencascade::handle<TColStd_HArray1OfReal> &) const) &Convert_CompPolynomialToPoles::Knots, "Knots of the n-dimensional Bspline", py::arg("K"));
cls_Convert_CompPolynomialToPoles.def("Multiplicities", (void (Convert_CompPolynomialToPoles::*)(opencascade::handle<TColStd_HArray1OfInteger> &) const) &Convert_CompPolynomialToPoles::Multiplicities, "Multiplicities of the knots in the BSpline", py::arg("M"));
cls_Convert_CompPolynomialToPoles.def("IsDone", (Standard_Boolean (Convert_CompPolynomialToPoles::*)() const) &Convert_CompPolynomialToPoles::IsDone, "None");

// CLASS: CONVERT_ELEMENTARYSURFACETOBSPLINESURFACE
py::class_<Convert_ElementarySurfaceToBSplineSurface> cls_Convert_ElementarySurfaceToBSplineSurface(mod, "Convert_ElementarySurfaceToBSplineSurface", "Root class for algorithms which convert an elementary surface (cylinder, cone, sphere or torus) into a BSpline surface (CylinderToBSplineSurface, ConeToBSplineSurface, SphereToBSplineSurface, TorusToBSplineSurface). These algorithms all work on elementary surfaces from the gp package and compute all the data needed to construct a BSpline surface equivalent to the cylinder, cone, sphere or torus. This data consists of the following: - degrees in the u and v parametric directions, - periodic characteristics in the u and v parametric directions, - a poles table with associated weights, - a knots table (for the u and v parametric directions) with associated multiplicities. The abstract class ElementarySurfaceToBSplineSurface provides a framework for storing and consulting this computed data. This data may then be used to construct a Geom_BSplineSurface surface, for example. All those classes define algorithmes to convert an ElementarySurface into a B-spline surface. This abstract class implements the methods to get the geometric representation of the B-spline surface. The B-spline representation is computed at the creation time in the sub classes. The B-spline surface is defined with its degree in the parametric U and V directions, its control points (Poles), its weights, its knots and their multiplicity. KeyWords : Convert, ElementarySurface, BSplineSurface.");

// Methods
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &Convert_ElementarySurfaceToBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator delete_", (void (*)(void *)) &Convert_ElementarySurfaceToBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &Convert_ElementarySurfaceToBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &Convert_ElementarySurfaceToBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_ElementarySurfaceToBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_ElementarySurfaceToBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &Convert_ElementarySurfaceToBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_ElementarySurfaceToBSplineSurface.def("UDegree", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::UDegree, "None");
cls_Convert_ElementarySurfaceToBSplineSurface.def("VDegree", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::VDegree, "Returns the degree for the u or v parametric direction of the BSpline surface whose data is computed in this framework.");
cls_Convert_ElementarySurfaceToBSplineSurface.def("NbUPoles", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::NbUPoles, "None");
cls_Convert_ElementarySurfaceToBSplineSurface.def("NbVPoles", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::NbVPoles, "Returns the number of poles for the u or v parametric direction of the BSpline surface whose data is computed in this framework.");
cls_Convert_ElementarySurfaceToBSplineSurface.def("NbUKnots", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::NbUKnots, "None");
cls_Convert_ElementarySurfaceToBSplineSurface.def("NbVKnots", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::NbVKnots, "Returns the number of knots for the u or v parametric direction of the BSpline surface whose data is computed in this framework .");
cls_Convert_ElementarySurfaceToBSplineSurface.def("IsUPeriodic", (Standard_Boolean (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::IsUPeriodic, "None");
cls_Convert_ElementarySurfaceToBSplineSurface.def("IsVPeriodic", (Standard_Boolean (Convert_ElementarySurfaceToBSplineSurface::*)() const) &Convert_ElementarySurfaceToBSplineSurface::IsVPeriodic, "Returns true if the BSpline surface whose data is computed in this framework is periodic in the u or v parametric direction.");
cls_Convert_ElementarySurfaceToBSplineSurface.def("Pole", (gp_Pnt (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::Pole, "Returns the pole of index (UIndex,VIndex) to the poles table of the BSpline surface whose data is computed in this framework. Exceptions Standard_OutOfRange if, for the BSpline surface whose data is computed in this framework: - UIndex is outside the bounds of the poles table in the u parametric direction, or - VIndex is outside the bounds of the poles table in the v parametric direction.", py::arg("UIndex"), py::arg("VIndex"));
cls_Convert_ElementarySurfaceToBSplineSurface.def("Weight", (Standard_Real (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::Weight, "Returns the weight of the pole of index (UIndex,VIndex) to the poles table of the BSpline surface whose data is computed in this framework. Exceptions Standard_OutOfRange if, for the BSpline surface whose data is computed in this framework: - UIndex is outside the bounds of the poles table in the u parametric direction, or - VIndex is outside the bounds of the poles table in the v parametric direction.", py::arg("UIndex"), py::arg("VIndex"));
cls_Convert_ElementarySurfaceToBSplineSurface.def("UKnot", (Standard_Real (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::UKnot, "Returns the U-knot of range UIndex. Raised if UIndex < 1 or UIndex > NbUKnots.", py::arg("UIndex"));
cls_Convert_ElementarySurfaceToBSplineSurface.def("VKnot", (Standard_Real (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::VKnot, "Returns the V-knot of range VIndex. Raised if VIndex < 1 or VIndex > NbVKnots.", py::arg("UIndex"));
cls_Convert_ElementarySurfaceToBSplineSurface.def("UMultiplicity", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::UMultiplicity, "Returns the multiplicity of the U-knot of range UIndex. Raised if UIndex < 1 or UIndex > NbUKnots.", py::arg("UIndex"));
cls_Convert_ElementarySurfaceToBSplineSurface.def("VMultiplicity", (Standard_Integer (Convert_ElementarySurfaceToBSplineSurface::*)(const Standard_Integer) const) &Convert_ElementarySurfaceToBSplineSurface::VMultiplicity, "Returns the multiplicity of the V-knot of range VIndex. Raised if VIndex < 1 or VIndex > NbVKnots.", py::arg("VIndex"));

// CLASS: CONVERT_CONETOBSPLINESURFACE
py::class_<Convert_ConeToBSplineSurface, Convert_ElementarySurfaceToBSplineSurface> cls_Convert_ConeToBSplineSurface(mod, "Convert_ConeToBSplineSurface", "This algorithm converts a bounded Cone into a rational B-spline surface. The cone a Cone from package gp. Its parametrization is : P (U, V) = Loc + V * Zdir + (R + V*Tan(Ang)) * (Cos(U)*Xdir + Sin(U)*Ydir) where Loc is the location point of the cone, Xdir, Ydir and Zdir are the normalized directions of the local cartesian coordinate system of the cone (Zdir is the direction of the Cone's axis) , Ang is the cone semi-angle. The U parametrization range is [0, 2PI]. KeyWords : Convert, Cone, BSplineSurface.");

// Constructors
cls_Convert_ConeToBSplineSurface.def(py::init<const gp_Cone &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("C"), py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_Convert_ConeToBSplineSurface.def(py::init<const gp_Cone &, const Standard_Real, const Standard_Real>(), py::arg("C"), py::arg("V1"), py::arg("V2"));

// Methods
// cls_Convert_ConeToBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &Convert_ConeToBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_Convert_ConeToBSplineSurface.def_static("operator delete_", (void (*)(void *)) &Convert_ConeToBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_Convert_ConeToBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &Convert_ConeToBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_Convert_ConeToBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &Convert_ConeToBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_ConeToBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_ConeToBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_ConeToBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &Convert_ConeToBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));

// TYPEDEF: CONVERT_COSANDSINEVALFUNCTION

// CLASS: CONVERT_CYLINDERTOBSPLINESURFACE
py::class_<Convert_CylinderToBSplineSurface, Convert_ElementarySurfaceToBSplineSurface> cls_Convert_CylinderToBSplineSurface(mod, "Convert_CylinderToBSplineSurface", "This algorithm converts a bounded cylinder into a rational B-spline surface. The cylinder is a Cylinder from package gp. The parametrization of the cylinder is : P (U, V) = Loc + V * Zdir + Radius * (Xdir*Cos(U) + Ydir*Sin(U)) where Loc is the location point of the cylinder, Xdir, Ydir and Zdir are the normalized directions of the local cartesian coordinate system of the cylinder (Zdir is the direction of the cylinder's axis). The U parametrization range is U [0, 2PI]. KeyWords : Convert, Cylinder, BSplineSurface.");

// Constructors
cls_Convert_CylinderToBSplineSurface.def(py::init<const gp_Cylinder &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Cyl"), py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_Convert_CylinderToBSplineSurface.def(py::init<const gp_Cylinder &, const Standard_Real, const Standard_Real>(), py::arg("Cyl"), py::arg("V1"), py::arg("V2"));

// Methods
// cls_Convert_CylinderToBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &Convert_CylinderToBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_Convert_CylinderToBSplineSurface.def_static("operator delete_", (void (*)(void *)) &Convert_CylinderToBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_Convert_CylinderToBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &Convert_CylinderToBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_Convert_CylinderToBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &Convert_CylinderToBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_CylinderToBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_CylinderToBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_CylinderToBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &Convert_CylinderToBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));

// CLASS: CONVERT_ELLIPSETOBSPLINECURVE
py::class_<Convert_EllipseToBSplineCurve, Convert_ConicToBSplineCurve> cls_Convert_EllipseToBSplineCurve(mod, "Convert_EllipseToBSplineCurve", "This algorithm converts a ellipse into a rational B-spline curve. The ellipse is represented an Elips2d from package gp with the parametrization : P (U) = Loc + (MajorRadius * Cos(U) * Xdir + MinorRadius * Sin(U) * Ydir) where Loc is the center of the ellipse, Xdir and Ydir are the normalized directions of the local cartesian coordinate system of the ellipse. The parametrization range is U [0, 2PI]. KeyWords : Convert, Ellipse, BSplineCurve, 2D .");

// Constructors
cls_Convert_EllipseToBSplineCurve.def(py::init<const gp_Elips2d &>(), py::arg("E"));
cls_Convert_EllipseToBSplineCurve.def(py::init<const gp_Elips2d &, const Convert_ParameterisationType>(), py::arg("E"), py::arg("Parameterisation"));
cls_Convert_EllipseToBSplineCurve.def(py::init<const gp_Elips2d &, const Standard_Real, const Standard_Real>(), py::arg("E"), py::arg("U1"), py::arg("U2"));
cls_Convert_EllipseToBSplineCurve.def(py::init<const gp_Elips2d &, const Standard_Real, const Standard_Real, const Convert_ParameterisationType>(), py::arg("E"), py::arg("U1"), py::arg("U2"), py::arg("Parameterisation"));

// Methods
// cls_Convert_EllipseToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_EllipseToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_EllipseToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_EllipseToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_EllipseToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_EllipseToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_EllipseToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_EllipseToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_EllipseToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_EllipseToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_EllipseToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_EllipseToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));

// CLASS: CONVERT_GRIDPOLYNOMIALTOPOLES
py::class_<Convert_GridPolynomialToPoles> cls_Convert_GridPolynomialToPoles(mod, "Convert_GridPolynomialToPoles", "Convert a grid of Polynomial Surfaces that are have continuity CM to an Bspline Surface that has continuity CM");

// Constructors
cls_Convert_GridPolynomialToPoles.def(py::init<const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &>(), py::arg("MaxUDegree"), py::arg("MaxVDegree"), py::arg("NumCoeff"), py::arg("Coefficients"), py::arg("PolynomialUIntervals"), py::arg("PolynomialVIntervals"));
cls_Convert_GridPolynomialToPoles.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray2OfInteger> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &>(), py::arg("NbUSurfaces"), py::arg("NBVSurfaces"), py::arg("UContinuity"), py::arg("VContinuity"), py::arg("MaxUDegree"), py::arg("MaxVDegree"), py::arg("NumCoeffPerSurface"), py::arg("Coefficients"), py::arg("PolynomialUIntervals"), py::arg("PolynomialVIntervals"), py::arg("TrueUIntervals"), py::arg("TrueVIntervals"));

// Methods
// cls_Convert_GridPolynomialToPoles.def_static("operator new_", (void * (*)(size_t)) &Convert_GridPolynomialToPoles::operator new, "None", py::arg("theSize"));
// cls_Convert_GridPolynomialToPoles.def_static("operator delete_", (void (*)(void *)) &Convert_GridPolynomialToPoles::operator delete, "None", py::arg("theAddress"));
// cls_Convert_GridPolynomialToPoles.def_static("operator new[]_", (void * (*)(size_t)) &Convert_GridPolynomialToPoles::operator new[], "None", py::arg("theSize"));
// cls_Convert_GridPolynomialToPoles.def_static("operator delete[]_", (void (*)(void *)) &Convert_GridPolynomialToPoles::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_GridPolynomialToPoles.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_GridPolynomialToPoles::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_GridPolynomialToPoles.def_static("operator delete_", (void (*)(void *, void *)) &Convert_GridPolynomialToPoles::operator delete, "None", py::arg(""), py::arg(""));
cls_Convert_GridPolynomialToPoles.def("Perform", (void (Convert_GridPolynomialToPoles::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray2OfInteger> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &)) &Convert_GridPolynomialToPoles::Perform, "None", py::arg("UContinuity"), py::arg("VContinuity"), py::arg("MaxUDegree"), py::arg("MaxVDegree"), py::arg("NumCoeffPerSurface"), py::arg("Coefficients"), py::arg("PolynomialUIntervals"), py::arg("PolynomialVIntervals"), py::arg("TrueUIntervals"), py::arg("TrueVIntervals"));
cls_Convert_GridPolynomialToPoles.def("NbUPoles", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::NbUPoles, "None");
cls_Convert_GridPolynomialToPoles.def("NbVPoles", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::NbVPoles, "None");
cls_Convert_GridPolynomialToPoles.def("Poles", (const opencascade::handle<TColgp_HArray2OfPnt> & (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::Poles, "returns the poles of the BSpline Surface");
cls_Convert_GridPolynomialToPoles.def("UDegree", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::UDegree, "None");
cls_Convert_GridPolynomialToPoles.def("VDegree", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::VDegree, "None");
cls_Convert_GridPolynomialToPoles.def("NbUKnots", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::NbUKnots, "None");
cls_Convert_GridPolynomialToPoles.def("NbVKnots", (Standard_Integer (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::NbVKnots, "None");
cls_Convert_GridPolynomialToPoles.def("UKnots", (const opencascade::handle<TColStd_HArray1OfReal> & (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::UKnots, "Knots in the U direction");
cls_Convert_GridPolynomialToPoles.def("VKnots", (const opencascade::handle<TColStd_HArray1OfReal> & (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::VKnots, "Knots in the V direction");
cls_Convert_GridPolynomialToPoles.def("UMultiplicities", (const opencascade::handle<TColStd_HArray1OfInteger> & (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::UMultiplicities, "Multiplicities of the knots in the U direction");
cls_Convert_GridPolynomialToPoles.def("VMultiplicities", (const opencascade::handle<TColStd_HArray1OfInteger> & (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::VMultiplicities, "Multiplicities of the knots in the V direction");
cls_Convert_GridPolynomialToPoles.def("IsDone", (Standard_Boolean (Convert_GridPolynomialToPoles::*)() const) &Convert_GridPolynomialToPoles::IsDone, "None");

// CLASS: CONVERT_HYPERBOLATOBSPLINECURVE
py::class_<Convert_HyperbolaToBSplineCurve, Convert_ConicToBSplineCurve> cls_Convert_HyperbolaToBSplineCurve(mod, "Convert_HyperbolaToBSplineCurve", "This algorithm converts a hyperbola into a rational B-spline curve. The hyperbola is an Hypr2d from package gp with the parametrization : P (U) = Loc + (MajorRadius * Cosh(U) * Xdir + MinorRadius * Sinh(U) * Ydir) where Loc is the location point of the hyperbola, Xdir and Ydir are the normalized directions of the local cartesian coordinate system of the hyperbola. KeyWords : Convert, Hyperbola, BSplineCurve, 2D .");

// Constructors
cls_Convert_HyperbolaToBSplineCurve.def(py::init<const gp_Hypr2d &, const Standard_Real, const Standard_Real>(), py::arg("H"), py::arg("U1"), py::arg("U2"));

// Methods
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_HyperbolaToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_HyperbolaToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_HyperbolaToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_HyperbolaToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_HyperbolaToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_HyperbolaToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_HyperbolaToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));

// CLASS: CONVERT_PARABOLATOBSPLINECURVE
py::class_<Convert_ParabolaToBSplineCurve, Convert_ConicToBSplineCurve> cls_Convert_ParabolaToBSplineCurve(mod, "Convert_ParabolaToBSplineCurve", "This algorithm converts a parabola into a non rational B-spline curve. The parabola is a Parab2d from package gp with the parametrization P (U) = Loc + F * (U*U * Xdir + 2 * U * Ydir) where Loc is the apex of the parabola, Xdir is the normalized direction of the symmetry axis of the parabola, Ydir is the normalized direction of the directrix and F is the focal length. KeyWords : Convert, Parabola, BSplineCurve, 2D .");

// Constructors
cls_Convert_ParabolaToBSplineCurve.def(py::init<const gp_Parab2d &, const Standard_Real, const Standard_Real>(), py::arg("Prb"), py::arg("U1"), py::arg("U2"));

// Methods
// cls_Convert_ParabolaToBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &Convert_ParabolaToBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_Convert_ParabolaToBSplineCurve.def_static("operator delete_", (void (*)(void *)) &Convert_ParabolaToBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_Convert_ParabolaToBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &Convert_ParabolaToBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_Convert_ParabolaToBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &Convert_ParabolaToBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_ParabolaToBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_ParabolaToBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_ParabolaToBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &Convert_ParabolaToBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));

// CLASS: CONVERT_SPHERETOBSPLINESURFACE
py::class_<Convert_SphereToBSplineSurface, Convert_ElementarySurfaceToBSplineSurface> cls_Convert_SphereToBSplineSurface(mod, "Convert_SphereToBSplineSurface", "This algorithm converts a bounded Sphere into a rational B-spline surface. The sphere is a Sphere from package gp. The parametrization of the sphere is P (U, V) = Loc + Radius * Sin(V) * Zdir + Radius * Cos(V) * (Cos(U)*Xdir + Sin(U)*Ydir) where Loc is the center of the sphere Xdir, Ydir and Zdir are the normalized directions of the local cartesian coordinate system of the sphere. The parametrization range is U [0, 2PI] and V [-PI/2, PI/2]. KeyWords : Convert, Sphere, BSplineSurface.");

// Constructors
cls_Convert_SphereToBSplineSurface.def(py::init<const gp_Sphere &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Sph"), py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_Convert_SphereToBSplineSurface.def(py::init<const gp_Sphere &, const Standard_Real, const Standard_Real>(), py::arg("Sph"), py::arg("Param1"), py::arg("Param2"));
cls_Convert_SphereToBSplineSurface.def(py::init<const gp_Sphere &, const Standard_Real, const Standard_Real, const Standard_Boolean>(), py::arg("Sph"), py::arg("Param1"), py::arg("Param2"), py::arg("UTrim"));
cls_Convert_SphereToBSplineSurface.def(py::init<const gp_Sphere &>(), py::arg("Sph"));

// Methods
// cls_Convert_SphereToBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &Convert_SphereToBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_Convert_SphereToBSplineSurface.def_static("operator delete_", (void (*)(void *)) &Convert_SphereToBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_Convert_SphereToBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &Convert_SphereToBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_Convert_SphereToBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &Convert_SphereToBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_SphereToBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_SphereToBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_SphereToBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &Convert_SphereToBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));

// CLASS: CONVERT_TORUSTOBSPLINESURFACE
py::class_<Convert_TorusToBSplineSurface, Convert_ElementarySurfaceToBSplineSurface> cls_Convert_TorusToBSplineSurface(mod, "Convert_TorusToBSplineSurface", "This algorithm converts a bounded Torus into a rational B-spline surface. The torus is a Torus from package gp. The parametrization of the torus is : P (U, V) = Loc + MinorRadius * Sin(V) * Zdir + (MajorRadius+MinorRadius*Cos(V)) * (Cos(U)*Xdir + Sin(U)*Ydir) where Loc is the center of the torus, Xdir, Ydir and Zdir are the normalized directions of the local cartesian coordinate system of the Torus. The parametrization range is U [0, 2PI], V [0, 2PI]. KeyWords : Convert, Torus, BSplineSurface.");

// Constructors
cls_Convert_TorusToBSplineSurface.def(py::init<const gp_Torus &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("T"), py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_Convert_TorusToBSplineSurface.def(py::init<const gp_Torus &, const Standard_Real, const Standard_Real>(), py::arg("T"), py::arg("Param1"), py::arg("Param2"));
cls_Convert_TorusToBSplineSurface.def(py::init<const gp_Torus &, const Standard_Real, const Standard_Real, const Standard_Boolean>(), py::arg("T"), py::arg("Param1"), py::arg("Param2"), py::arg("UTrim"));
cls_Convert_TorusToBSplineSurface.def(py::init<const gp_Torus &>(), py::arg("T"));

// Methods
// cls_Convert_TorusToBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &Convert_TorusToBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_Convert_TorusToBSplineSurface.def_static("operator delete_", (void (*)(void *)) &Convert_TorusToBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_Convert_TorusToBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &Convert_TorusToBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_Convert_TorusToBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &Convert_TorusToBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_Convert_TorusToBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &Convert_TorusToBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Convert_TorusToBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &Convert_TorusToBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));


}
