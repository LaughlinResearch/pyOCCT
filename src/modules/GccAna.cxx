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
#include <GccEnt_QualifiedCirc.hxx>
#include <gp_Lin2d.hxx>
#include <Standard_TypeDef.hxx>
#include <GccEnt_QualifiedLin.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Circ2d.hxx>
#include <GccEnt_Position.hxx>
#include <TColgp_Array1OfCirc2d.hxx>
#include <GccEnt_Array1OfPosition.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <GccAna_Circ2d2TanOn.hxx>
#include <GccAna_Circ2d2TanRad.hxx>
#include <GccAna_Circ2d3Tan.hxx>
#include <Standard_Handle.hxx>
#include <GccInt_Bisec.hxx>
#include <GccAna_Circ2dBisec.hxx>
#include <GccAna_Circ2dTanCen.hxx>
#include <GccAna_Circ2dTanOnRad.hxx>
#include <GccAna_CircLin2dBisec.hxx>
#include <GccAna_CircPnt2dBisec.hxx>
#include <TColgp_Array1OfLin2d.hxx>
#include <GccAna_Lin2d2Tan.hxx>
#include <GccAna_Lin2dBisec.hxx>
#include <GccAna_Lin2dTanObl.hxx>
#include <GccAna_Lin2dTanPar.hxx>
#include <GccAna_Lin2dTanPer.hxx>
#include <GccAna_LinPnt2dBisec.hxx>
#include <Standard_Failure.hxx>
#include <GccAna_NoSolution.hxx>
#include <Standard_SStream.hxx>
#include <Standard_Std.hxx>
#include <Standard_Type.hxx>
#include <GccAna_Pnt2dBisec.hxx>

PYBIND11_MODULE(GccAna, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.GccEnt");
py::module::import("OCCT.gp");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.GccInt");

// CLASS: GCCANA_CIRC2D2TANON
py::class_<GccAna_Circ2d2TanOn> cls_GccAna_Circ2d2TanOn(mod, "GccAna_Circ2d2TanOn", "Describes functions for building a 2D circle - tangential to 2 curves, or - tangential to a curve and passing through a point, or - passing through 2 points, and with its center on a curve. For these analytic algorithms, curves are circles or lines. A Circ2d2TanOn object provides a framework for: - defining the construction of 2D circles(s), - implementing the construction algorithm, and - consulting the result(s).");

// Constructors
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedLin &, const gp_Pnt2d &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &, const gp_Lin2d &, const Standard_Real>(), py::arg("Point1"), py::arg("Point2"), py::arg("OnLine"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const gp_Circ2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnCirc"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const gp_Circ2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnCirc"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const gp_Circ2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("OnCirc"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const gp_Circ2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("OnCirc"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const GccEnt_QualifiedLin &, const gp_Pnt2d &, const gp_Circ2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("OnCirc"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanOn.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &, const gp_Circ2d &, const Standard_Real>(), py::arg("Point1"), py::arg("Point2"), py::arg("OnCirc"), py::arg("Tolerance"));

// Methods
// cls_GccAna_Circ2d2TanOn.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2d2TanOn::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2d2TanOn.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2d2TanOn::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2d2TanOn.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2d2TanOn::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2d2TanOn.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2d2TanOn::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2d2TanOn.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2d2TanOn::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2d2TanOn.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2d2TanOn::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2d2TanOn.def("IsDone", (Standard_Boolean (GccAna_Circ2d2TanOn::*)() const) &GccAna_Circ2d2TanOn::IsDone, "Returns true if the construction algorithm does not fail (even if it finds no solution). Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Circ2d2TanOn.def("NbSolutions", (Standard_Integer (GccAna_Circ2d2TanOn::*)() const) &GccAna_Circ2d2TanOn::NbSolutions, "Returns the number of circles, representing solutions computed by this algorithm. Exceptions StdFail_NotDone if the construction fails.");
cls_GccAna_Circ2d2TanOn.def("ThisSolution", (gp_Circ2d (GccAna_Circ2d2TanOn::*)(const Standard_Integer) const) &GccAna_Circ2d2TanOn::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be careful: the Index is only a way to get all the solutions, but is not associated to those outside the context of the algorithm-object. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"));
cls_GccAna_Circ2d2TanOn.def("WhichQualifier", (void (GccAna_Circ2d2TanOn::*)(const Standard_Integer, GccEnt_Position &, GccEnt_Position &) const) &GccAna_Circ2d2TanOn::WhichQualifier, "Returns the qualifiers Qualif1 and Qualif2 of the tangency arguments for the solution of index Index computed by this algorithm. The returned qualifiers are: - those specified at the start of construction when the solutions are defined as enclosed, enclosing or outside with respect to the arguments, or - those computed during construction (i.e. enclosed, enclosing or outside) when the solutions are defined as unqualified with respect to the arguments, or - GccEnt_noqualifier if the tangency argument is a point. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("Qualif1"), py::arg("Qualif2"));
cls_GccAna_Circ2d2TanOn.def("Tangency1", [](GccAna_Circ2d2TanOn &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns the informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution ParArg is the intrinsic parameter of the point PntSol on the first argument. Raises OutOfRange if Index is greater than the number of solutions and NotDone if IsDone returns false.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d2TanOn.def("Tangency2", [](GccAna_Circ2d2TanOn &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns the informations about the tangency point between the result number Index and the second argument. ParSol is the intrinsic parameter of the point PntSol on the solution. ParArg is the intrinsic parameter of the point PntSol on the second argument. Raises OutOfRange if Index is greater than the number of solutions and NotDone if IsDone returns false.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d2TanOn.def("CenterOn3", [](GccAna_Circ2d2TanOn &self, const Standard_Integer Index, Standard_Real & ParArg, gp_Pnt2d & PntArg){ self.CenterOn3(Index, ParArg, PntArg); return ParArg; }, "Returns the informations about the center (on the curv) of the result number Index and the third argument. ParArg is the intrinsic parameter of the point PntArg on the third argument. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("ParArg"), py::arg("PntArg"));
cls_GccAna_Circ2d2TanOn.def("IsTheSame1", (Standard_Boolean (GccAna_Circ2d2TanOn::*)(const Standard_Integer) const) &GccAna_Circ2d2TanOn::IsTheSame1, "True if the solution and the first argument are the same (2 circles). If R1 is the radius of the first argument and Rsol the radius of the solution and dist the distance between the two centers, we concider the two circles are identical if R1+dist-Rsol is less than Tolerance. False in the other cases. Raises OutOfRange if Index is greater than the number of solutions and NotDone if IsDone returns false.", py::arg("Index"));
cls_GccAna_Circ2d2TanOn.def("IsTheSame2", (Standard_Boolean (GccAna_Circ2d2TanOn::*)(const Standard_Integer) const) &GccAna_Circ2d2TanOn::IsTheSame2, "True if the solution and the second argument are the same (2 circles). If R2 is the radius of the second argument and Rsol the radius of the solution and dist the distance between the two centers, we concider the two circles are identical if R2+dist-Rsol is less than Tolerance. False in the other cases. Raises OutOfRange if Index is greater than the number of solutions and NotDone if IsDone returns false.", py::arg("Index"));

// CLASS: GCCANA_CIRC2D2TANRAD
py::class_<GccAna_Circ2d2TanRad> cls_GccAna_Circ2d2TanRad(mod, "GccAna_Circ2d2TanRad", "This class implements the algorithms used to create 2d circles tangent to 2 points/lines/circles and with a given radius. For each construction methods arguments are: - Two Qualified elements for tangency constraints. (for example EnclosedCirc if we want the solution inside the argument EnclosedCirc). - Two Reals. One (Radius) for the radius and the other (Tolerance) for the tolerance. Tolerance is only used for the limit cases. For example : We want to create a circle inside a circle C1 and inside a circle C2 with a radius Radius and a tolerance Tolerance. If we do not use Tolerance it is impossible to find a solution in the following case : C2 is inside C1 and there is no intersection point between the two circles. With Tolerance it gives a solution if the lowest distance between C1 and C2 is lower than or equal Tolerance.");

// Constructors
cls_GccAna_Circ2d2TanRad.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanRad.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanRad.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanRad.def(py::init<const GccEnt_QualifiedLin &, const gp_Pnt2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanRad.def(py::init<const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2d2TanRad.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real, const Standard_Real>(), py::arg("Point1"), py::arg("Point2"), py::arg("Radius"), py::arg("Tolerance"));

// Methods
// cls_GccAna_Circ2d2TanRad.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2d2TanRad::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2d2TanRad.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2d2TanRad::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2d2TanRad.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2d2TanRad::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2d2TanRad.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2d2TanRad::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2d2TanRad.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2d2TanRad::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2d2TanRad.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2d2TanRad::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2d2TanRad.def("IsDone", (Standard_Boolean (GccAna_Circ2d2TanRad::*)() const) &GccAna_Circ2d2TanRad::IsDone, "This method returns True if the algorithm succeeded. Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Circ2d2TanRad.def("NbSolutions", (Standard_Integer (GccAna_Circ2d2TanRad::*)() const) &GccAna_Circ2d2TanRad::NbSolutions, "This method returns the number of circles, representing solutions computed by this algorithm. Exceptions StdFail_NotDone if the construction fails. of solutions.");
cls_GccAna_Circ2d2TanRad.def("ThisSolution", (gp_Circ2d (GccAna_Circ2d2TanRad::*)(const Standard_Integer) const) &GccAna_Circ2d2TanRad::ThisSolution, "Returns the solution number Index. Be careful: the Index is only a way to get all the solutions, but is not associated to those outside the context of the algorithm-object. Raises OutOfRange exception if Index is greater than the number of solutions. It raises NotDone if the construction algorithm did not succeed.", py::arg("Index"));
cls_GccAna_Circ2d2TanRad.def("WhichQualifier", (void (GccAna_Circ2d2TanRad::*)(const Standard_Integer, GccEnt_Position &, GccEnt_Position &) const) &GccAna_Circ2d2TanRad::WhichQualifier, "Returns the information about the qualifiers of the tangency arguments concerning the solution number Index. It returns the real qualifiers (the qualifiers given to the constructor method in case of enclosed, enclosing and outside and the qualifiers computedin case of unqualified).", py::arg("Index"), py::arg("Qualif1"), py::arg("Qualif2"));
cls_GccAna_Circ2d2TanRad.def("Tangency1", [](GccAna_Circ2d2TanRad &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns information about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution. ParArg is the intrinsic parameter of the point PntSol on the first argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the construction algorithm did not succeed", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d2TanRad.def("Tangency2", [](GccAna_Circ2d2TanRad &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns information about the tangency point between the result number Index and the second argument. ParSol is the intrinsic parameter of the point PntSol on the solution. ParArg is the intrinsic parameter of the point PntArg on the second argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the construction algorithm did not succeed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d2TanRad.def("IsTheSame1", (Standard_Boolean (GccAna_Circ2d2TanRad::*)(const Standard_Integer) const) &GccAna_Circ2d2TanRad::IsTheSame1, "Returns True if the solution number Index is equal to the first argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the construction algorithm did not succeed.", py::arg("Index"));
cls_GccAna_Circ2d2TanRad.def("IsTheSame2", (Standard_Boolean (GccAna_Circ2d2TanRad::*)(const Standard_Integer) const) &GccAna_Circ2d2TanRad::IsTheSame2, "Returns True if the solution number Index is equal to the second argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the construction algorithm did not succeed.", py::arg("Index"));

// CLASS: GCCANA_CIRC2D3TAN
py::class_<GccAna_Circ2d3Tan> cls_GccAna_Circ2d3Tan(mod, "GccAna_Circ2d3Tan", "This class implements the algorithms used to create 2d circles tangent to 3 points/lines/circles. The arguments of all construction methods are : - The three qualified elements for the tangency constraints (QualifiedCirc, QualifiedLine, Points). - A real Tolerance. Tolerance is only used in the limit cases. For example : We want to create a circle tangent to an UnqualifiedCirc C1 and an UnqualifiedCirc C2 and an UnqualifiedCirc C3 with a tolerance Tolerance. If we do not use Tolerance it is impossible to find a solution in the following case : C2 is inside C1 and there is no intersection point between the two circles, and C3 is completly outside C1. With Tolerance we will find a solution if the lowest distance between C1 and C2 is lower than or equal Tolerance.");

// Constructors
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Qualified3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Qualified3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Qualified3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Qualified3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Point3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedLin &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Point3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedLin &, const GccEnt_QualifiedLin &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Point3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("Point3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const GccEnt_QualifiedLin &, const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Point2"), py::arg("Point3"), py::arg("Tolerance"));
cls_GccAna_Circ2d3Tan.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Point1"), py::arg("Point2"), py::arg("Point3"), py::arg("Tolerance"));

// Methods
// cls_GccAna_Circ2d3Tan.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2d3Tan::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2d3Tan.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2d3Tan::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2d3Tan.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2d3Tan::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2d3Tan.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2d3Tan::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2d3Tan.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2d3Tan::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2d3Tan.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2d3Tan::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2d3Tan.def("IsDone", (Standard_Boolean (GccAna_Circ2d3Tan::*)() const) &GccAna_Circ2d3Tan::IsDone, "This method returns True if the construction algorithm succeeded. Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Circ2d3Tan.def("NbSolutions", (Standard_Integer (GccAna_Circ2d3Tan::*)() const) &GccAna_Circ2d3Tan::NbSolutions, "This method returns the number of solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Circ2d3Tan.def("ThisSolution", (gp_Circ2d (GccAna_Circ2d3Tan::*)(const Standard_Integer) const) &GccAna_Circ2d3Tan::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be careful: the Index is only a way to get all the solutions, but is not associated to those outside the context of the algorithm-object. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"));
cls_GccAna_Circ2d3Tan.def("WhichQualifier", (void (GccAna_Circ2d3Tan::*)(const Standard_Integer, GccEnt_Position &, GccEnt_Position &, GccEnt_Position &) const) &GccAna_Circ2d3Tan::WhichQualifier, "Returns the informations about the qualifiers of the tangency arguments concerning the solution number Index. It returns the real qualifiers (the qualifiers given to the constructor method in case of enclosed, enclosing and outside and the qualifiers computedin case of unqualified).", py::arg("Index"), py::arg("Qualif1"), py::arg("Qualif2"), py::arg("Qualif3"));
cls_GccAna_Circ2d3Tan.def("Tangency1", [](GccAna_Circ2d3Tan &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution curv. ParArg is the intrinsic parameter of the point PntArg on the argument curv. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d3Tan.def("Tangency2", [](GccAna_Circ2d3Tan &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution curv. ParArg is the intrinsic parameter of the point Pntsol on the argument curv. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d3Tan.def("Tangency3", [](GccAna_Circ2d3Tan &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency3(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution curv. ParArg is the intrinsic parameter of the point Pntsol on the argument curv. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2d3Tan.def("IsTheSame1", (Standard_Boolean (GccAna_Circ2d3Tan::*)(const Standard_Integer) const) &GccAna_Circ2d3Tan::IsTheSame1, "Returns True if the solution number Index is equal to the first argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"));
cls_GccAna_Circ2d3Tan.def("IsTheSame2", (Standard_Boolean (GccAna_Circ2d3Tan::*)(const Standard_Integer) const) &GccAna_Circ2d3Tan::IsTheSame2, "Returns True if the solution number Index is equal to the second argument. Raises OutOfRange Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"));
cls_GccAna_Circ2d3Tan.def("IsTheSame3", (Standard_Boolean (GccAna_Circ2d3Tan::*)(const Standard_Integer) const) &GccAna_Circ2d3Tan::IsTheSame3, "Returns True if the solution number Index is equal to the third argument. Raises OutOfRange if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"));

// CLASS: GCCANA_CIRC2DBISEC
py::class_<GccAna_Circ2dBisec> cls_GccAna_Circ2dBisec(mod, "GccAna_Circ2dBisec", "This class describes functions for building bisecting curves between two 2D circles. A bisecting curve between two circles is a curve such that each of its points is at the same distance from the two circles. It can be an ellipse, hyperbola, circle or line, depending on the relative position of the two circles. The algorithm computes all the elementary curves which are solutions. There is no solution if the two circles are coincident. A Circ2dBisec object provides a framework for: - defining the construction of the bisecting curves, - implementing the construction algorithm, and consulting the result.");

// Constructors
cls_GccAna_Circ2dBisec.def(py::init<const gp_Circ2d &, const gp_Circ2d &>(), py::arg("Circ1"), py::arg("Circ2"));

// Methods
// cls_GccAna_Circ2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2dBisec.def("IsDone", (Standard_Boolean (GccAna_Circ2dBisec::*)() const) &GccAna_Circ2dBisec::IsDone, "This method returns True if the construction algorithm succeeded.");
cls_GccAna_Circ2dBisec.def("NbSolutions", (Standard_Integer (GccAna_Circ2dBisec::*)() const) &GccAna_Circ2dBisec::NbSolutions, "This method returns the number of solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Circ2dBisec.def("ThisSolution", (opencascade::handle<GccInt_Bisec> (GccAna_Circ2dBisec::*)(const Standard_Integer) const) &GccAna_Circ2dBisec::ThisSolution, "Returns the solution number Index Raises OutOfRange exception if Index is greater than the number of solutions. It raises NotDone if the construction algorithm didn't succeed.", py::arg("Index"));

// CLASS: GCCANA_CIRC2DTANCEN
py::class_<GccAna_Circ2dTanCen> cls_GccAna_Circ2dTanCen(mod, "GccAna_Circ2dTanCen", "This class implements the algorithms used to create 2d circles tangent to an entity and centered on a point. The arguments of all construction methods are : - The qualified element for the tangency constrains (QualifiedCirc, Line, Point). - The center point Pcenter. - A real Tolerance. Tolerance is only used in the limits cases. For example : We want to create a circle tangent to an EnclosedCirc C1 with a tolerance Tolerance. If we did not used Tolerance it is impossible to find a solution in the the following case : Pcenter is outside C1. With Tolerance we will give a solution if the distance between C1 and Pcenter is lower than or equal Tolerance.");

// Constructors
cls_GccAna_Circ2dTanCen.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Pcenter"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanCen.def(py::init<const gp_Lin2d &, const gp_Pnt2d &>(), py::arg("Linetan"), py::arg("Pcenter"));
cls_GccAna_Circ2dTanCen.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &>(), py::arg("Point1"), py::arg("Pcenter"));

// Methods
// cls_GccAna_Circ2dTanCen.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2dTanCen::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2dTanCen.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2dTanCen::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2dTanCen.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2dTanCen::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2dTanCen.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2dTanCen::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2dTanCen.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2dTanCen::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2dTanCen.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2dTanCen::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2dTanCen.def("IsDone", (Standard_Boolean (GccAna_Circ2dTanCen::*)() const) &GccAna_Circ2dTanCen::IsDone, "This method returns True if the construction algorithm succeeded. Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Circ2dTanCen.def("NbSolutions", (Standard_Integer (GccAna_Circ2dTanCen::*)() const) &GccAna_Circ2dTanCen::NbSolutions, "Returns the number of circles, representing solutions computed by this algorithm and raises NotDone exception if the algorithm didn't succeed.");
cls_GccAna_Circ2dTanCen.def("ThisSolution", (gp_Circ2d (GccAna_Circ2dTanCen::*)(const Standard_Integer) const) &GccAna_Circ2dTanCen::ThisSolution, "Returns the circle, representing the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be carefull: the Index is only a way to get all the solutions, but is not associated to theses outside the context of the algorithm-object. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions or less than zer", py::arg("Index"));
cls_GccAna_Circ2dTanCen.def("WhichQualifier", (void (GccAna_Circ2dTanCen::*)(const Standard_Integer, GccEnt_Position &) const) &GccAna_Circ2dTanCen::WhichQualifier, "Returns the qualifier Qualif1 of the tangency argument for the solution of index Index computed by this algorithm. The returned qualifier is: - that specified at the start of construction when the solutions are defined as enclosed, enclosing or It returns the real qualifiers (the qualifiers given to the constructor method in case of enclosed, enclosing and outside and the qualifiers computedin case of unqualified).", py::arg("Index"), py::arg("Qualif1"));
cls_GccAna_Circ2dTanCen.def("Tangency1", [](GccAna_Circ2dTanCen &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution curv. ParArg is the intrinsic parameter of the point PntArg on the argument curv. It raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions or less than zero.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2dTanCen.def("IsTheSame1", (Standard_Boolean (GccAna_Circ2dTanCen::*)(const Standard_Integer) const) &GccAna_Circ2dTanCen::IsTheSame1, "Returns True if the solution number Index is equal to the first argument. It raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions or less than zero.", py::arg("Index"));

// CLASS: GCCANA_CIRC2DTANONRAD
py::class_<GccAna_Circ2dTanOnRad> cls_GccAna_Circ2dTanOnRad(mod, "GccAna_Circ2dTanOnRad", "This class implements the algorithms used to create a 2d circle tangent to a 2d entity, centered on a curv and with a given radius. The arguments of all construction methods are : - The qualified element for the tangency constrains (QualifiedCirc, QualifiedLin, Points). - The Center element (circle, line). - A real Tolerance. Tolerance is only used in the limits cases. For example : We want to create a circle tangent to an OutsideCirc C1 centered on a line OnLine with a radius Radius and with a tolerance Tolerance. If we did not use Tolerance it is impossible to find a solution in the the following case : OnLine is outside C1. There is no intersection point between C1 and OnLine. The distance between the line and the circle is greater than Radius. With Tolerance we will give a solution if the distance between C1 and OnLine is lower than or equal Tolerance.");

// Constructors
cls_GccAna_Circ2dTanOnRad.def(py::init<const GccEnt_QualifiedCirc &, const gp_Lin2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("OnLine"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanOnRad.def(py::init<const GccEnt_QualifiedLin &, const gp_Lin2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("OnLine"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanOnRad.def(py::init<const gp_Pnt2d &, const gp_Lin2d &, const Standard_Real, const Standard_Real>(), py::arg("Point1"), py::arg("OnLine"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanOnRad.def(py::init<const GccEnt_QualifiedCirc &, const gp_Circ2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("OnCirc"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanOnRad.def(py::init<const GccEnt_QualifiedLin &, const gp_Circ2d &, const Standard_Real, const Standard_Real>(), py::arg("Qualified1"), py::arg("OnCirc"), py::arg("Radius"), py::arg("Tolerance"));
cls_GccAna_Circ2dTanOnRad.def(py::init<const gp_Pnt2d &, const gp_Circ2d &, const Standard_Real, const Standard_Real>(), py::arg("Point1"), py::arg("OnCirc"), py::arg("Radius"), py::arg("Tolerance"));

// Methods
// cls_GccAna_Circ2dTanOnRad.def_static("operator new_", (void * (*)(size_t)) &GccAna_Circ2dTanOnRad::operator new, "None", py::arg("theSize"));
// cls_GccAna_Circ2dTanOnRad.def_static("operator delete_", (void (*)(void *)) &GccAna_Circ2dTanOnRad::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Circ2dTanOnRad.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Circ2dTanOnRad::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Circ2dTanOnRad.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Circ2dTanOnRad::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Circ2dTanOnRad.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Circ2dTanOnRad::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Circ2dTanOnRad.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Circ2dTanOnRad::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Circ2dTanOnRad.def("IsDone", (Standard_Boolean (GccAna_Circ2dTanOnRad::*)() const) &GccAna_Circ2dTanOnRad::IsDone, "Returns true if the construction algorithm does not fail (even if it finds no solution). Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Circ2dTanOnRad.def("NbSolutions", (Standard_Integer (GccAna_Circ2dTanOnRad::*)() const) &GccAna_Circ2dTanOnRad::NbSolutions, "This method returns the number of circles, representing solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Circ2dTanOnRad.def("ThisSolution", (gp_Circ2d (GccAna_Circ2dTanOnRad::*)(const Standard_Integer) const) &GccAna_Circ2dTanOnRad::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be careful: the Index is only a way to get all the solutions, but is not associated to theses outside the context of the algorithm-object. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions", py::arg("Index"));
cls_GccAna_Circ2dTanOnRad.def("WhichQualifier", (void (GccAna_Circ2dTanOnRad::*)(const Standard_Integer, GccEnt_Position &) const) &GccAna_Circ2dTanOnRad::WhichQualifier, "Returns the qualifier Qualif1 of the tangency argument for the solution of index Index computed by this algorithm. The returned qualifier is: - that specified at the start of construction when the solutions are defined as enclosed, enclosing or outside with respect to the argument, or - that computed during construction (i.e. enclosed, enclosing or outside) when the solutions are defined as unqualified with respect to the argument, or - GccEnt_noqualifier if the tangency argument is a point. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("Qualif1"));
cls_GccAna_Circ2dTanOnRad.def("Tangency1", [](GccAna_Circ2dTanOnRad &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point on the solution curv. ParArg is the intrinsic parameter of the point on the argument curv. PntSol is the tangency point on the solution curv. PntArg is the tangency point on the argument curv. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2dTanOnRad.def("CenterOn3", [](GccAna_Circ2dTanOnRad &self, const Standard_Integer Index, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.CenterOn3(Index, ParArg, PntSol); return ParArg; }, "Returns informations about the center (on the curv) of the result. ParArg is the intrinsic parameter of the point on the argument curv. PntSol is the center point of the solution curv. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Circ2dTanOnRad.def("IsTheSame1", (Standard_Boolean (GccAna_Circ2dTanOnRad::*)(const Standard_Integer) const) &GccAna_Circ2dTanOnRad::IsTheSame1, "Returns True if the solution number Index is equal to the first argument and False in the other cases. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"));

// CLASS: GCCANA_CIRCLIN2DBISEC
py::class_<GccAna_CircLin2dBisec> cls_GccAna_CircLin2dBisec(mod, "GccAna_CircLin2dBisec", "Describes functions for building bisecting curves between a 2D line and a 2D circle. A bisecting curve between a circle and a line is a curve such that each of its points is at the same distance from the circle and the line. It can be a parabola or a line, depending of the relative position of the line and the circle. The algorithm computes all the elementary curves which are solutions. A CircLin2dBisec object provides a framework for: - defining the construction of the bisecting curves, - implementing the construction algorithm, and - consulting the result.");

// Constructors
cls_GccAna_CircLin2dBisec.def(py::init<const gp_Circ2d &, const gp_Lin2d &>(), py::arg("Circle"), py::arg("Line"));

// Methods
// cls_GccAna_CircLin2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_CircLin2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_CircLin2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_CircLin2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_CircLin2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_CircLin2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_CircLin2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_CircLin2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_CircLin2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_CircLin2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_CircLin2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_CircLin2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_CircLin2dBisec.def("IsDone", (Standard_Boolean (GccAna_CircLin2dBisec::*)() const) &GccAna_CircLin2dBisec::IsDone, "Returns true (this construction algorithm never fails).");
cls_GccAna_CircLin2dBisec.def("NbSolutions", (Standard_Integer (GccAna_CircLin2dBisec::*)() const) &GccAna_CircLin2dBisec::NbSolutions, "Returns the number of curves, representing solutions computed by this algorithm.");
cls_GccAna_CircLin2dBisec.def("ThisSolution", (opencascade::handle<GccInt_Bisec> (GccAna_CircLin2dBisec::*)(const Standard_Integer) const) &GccAna_CircLin2dBisec::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm.", py::arg("Index"));

// CLASS: GCCANA_CIRCPNT2DBISEC
py::class_<GccAna_CircPnt2dBisec> cls_GccAna_CircPnt2dBisec(mod, "GccAna_CircPnt2dBisec", "Describes functions for building a bisecting curve between a 2D circle and a point. A bisecting curve between a circle and a point is such a curve that each of its points is at the same distance from the circle and the point. It can be an ellipse, hyperbola, circle or line, depending on the relative position of the point and the circle. The algorithm computes all the elementary curves which are solutions. A CircPnt2dBisec object provides a framework for: - defining the construction of the bisecting curves, - implementing the construction algorithm, and - consulting the result.");

// Constructors
cls_GccAna_CircPnt2dBisec.def(py::init<const gp_Circ2d &, const gp_Pnt2d &>(), py::arg("Circle1"), py::arg("Point2"));
cls_GccAna_CircPnt2dBisec.def(py::init<const gp_Circ2d &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Circle1"), py::arg("Point2"), py::arg("Tolerance"));

// Methods
// cls_GccAna_CircPnt2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_CircPnt2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_CircPnt2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_CircPnt2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_CircPnt2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_CircPnt2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_CircPnt2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_CircPnt2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_CircPnt2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_CircPnt2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_CircPnt2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_CircPnt2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_CircPnt2dBisec.def("IsDone", (Standard_Boolean (GccAna_CircPnt2dBisec::*)() const) &GccAna_CircPnt2dBisec::IsDone, "Returns true (this construction algorithm never fails).");
cls_GccAna_CircPnt2dBisec.def("NbSolutions", (Standard_Integer (GccAna_CircPnt2dBisec::*)() const) &GccAna_CircPnt2dBisec::NbSolutions, "Returns the number of curves, representing solutions computed by this algorithm.");
cls_GccAna_CircPnt2dBisec.def("ThisSolution", (opencascade::handle<GccInt_Bisec> (GccAna_CircPnt2dBisec::*)(const Standard_Integer) const) &GccAna_CircPnt2dBisec::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm.", py::arg("Index"));

// CLASS: GCCANA_LIN2D2TAN
py::class_<GccAna_Lin2d2Tan> cls_GccAna_Lin2d2Tan(mod, "GccAna_Lin2d2Tan", "This class implements the algorithms used to create 2d lines tangent to 2 other elements which can be circles or points. Describes functions for building a 2D line: - tangential to 2 circles, or - tangential to a circle and passing through a point, or - passing through 2 points. A Lin2d2Tan object provides a framework for: - defining the construction of 2D line(s), - implementing the construction algorithm, and consulting the result(s). Some constructors may check the type of the qualified argument and raise BadQualifier Error in case of incorrect couple (qualifier, curv). For example: 'EnclosedCirc'.");

// Constructors
cls_GccAna_Lin2d2Tan.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real>(), py::arg("ThePoint1"), py::arg("ThePoint2"), py::arg("Tolerance"));
cls_GccAna_Lin2d2Tan.def(py::init<const GccEnt_QualifiedCirc &, const gp_Pnt2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("ThePoint"), py::arg("Tolerance"));
cls_GccAna_Lin2d2Tan.def(py::init<const GccEnt_QualifiedCirc &, const GccEnt_QualifiedCirc &, const Standard_Real>(), py::arg("Qualified1"), py::arg("Qualified2"), py::arg("Tolerance"));

// Methods
// cls_GccAna_Lin2d2Tan.def_static("operator new_", (void * (*)(size_t)) &GccAna_Lin2d2Tan::operator new, "None", py::arg("theSize"));
// cls_GccAna_Lin2d2Tan.def_static("operator delete_", (void (*)(void *)) &GccAna_Lin2d2Tan::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Lin2d2Tan.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Lin2d2Tan::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Lin2d2Tan.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Lin2d2Tan::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Lin2d2Tan.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Lin2d2Tan::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Lin2d2Tan.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Lin2d2Tan::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Lin2d2Tan.def("IsDone", (Standard_Boolean (GccAna_Lin2d2Tan::*)() const) &GccAna_Lin2d2Tan::IsDone, "This method returns true when there is a solution and false in the other cases.");
cls_GccAna_Lin2d2Tan.def("NbSolutions", (Standard_Integer (GccAna_Lin2d2Tan::*)() const) &GccAna_Lin2d2Tan::NbSolutions, "This method returns the number of solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Lin2d2Tan.def("ThisSolution", (gp_Lin2d (GccAna_Lin2d2Tan::*)(const Standard_Integer) const) &GccAna_Lin2d2Tan::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be carefull: the Index is only a way to get all the solutions, but is not associated to theses outside the context of the algorithm-object. Raises OutOfRange is raised if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"));
cls_GccAna_Lin2d2Tan.def("WhichQualifier", (void (GccAna_Lin2d2Tan::*)(const Standard_Integer, GccEnt_Position &, GccEnt_Position &) const) &GccAna_Lin2d2Tan::WhichQualifier, "Returns the qualifiers Qualif1 and Qualif2 of the tangency arguments for the solution of index Index computed by this algorithm. The returned qualifiers are: - those specified at the start of construction when the solutions are defined as enclosing or outside with respect to the arguments, or - those computed during construction (i.e. enclosing or outside) when the solutions are defined as unqualified with respect to the arguments, or - GccEnt_noqualifier if the tangency argument is a point. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("Qualif1"), py::arg("Qualif2"));
cls_GccAna_Lin2d2Tan.def("Tangency1", [](GccAna_Lin2d2Tan &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point PntSol on the solution curv. ParArg is the intrinsic parameter of the point PntSol on the argument curv. Raises OutOfRange is raised if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Lin2d2Tan.def("Tangency2", [](GccAna_Lin2d2Tan &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the second argument. ParSol is the intrinsic parameter of the point ParSol on the solution curv. ParArg is the intrinsic parameter of the point PntSol on the argument curv. Raises OutOfRange is raised if Index is greater than the number of solutions. It raises NotDone if the algorithm failed.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));

// CLASS: GCCANA_LIN2DBISEC
py::class_<GccAna_Lin2dBisec> cls_GccAna_Lin2dBisec(mod, "GccAna_Lin2dBisec", "Describes functions for building bisecting lines between two 2D lines. A bisecting line between two lines is such that each of its points is at the same distance from the two lines. If the two lines are secant, there are two orthogonal bisecting lines which share the angles made by the two straight lines in two equal parts. If D1 and D2 are the unit vectors of the two straight lines, those of the two bisecting lines are collinear with the following vectors: - D1 + D2 for the 'internal' bisecting line, - D1 - D2 for the 'external' bisecting line. If the two lines are parallel, the (unique) bisecting line is the straight line equidistant from the two straight lines. If the two straight lines are coincident, the algorithm returns the first straight line as the solution. A Lin2dTanObl object provides a framework for: - defining the construction of the bisecting lines, - implementing the construction algorithm, and - consulting the result.");

// Constructors
cls_GccAna_Lin2dBisec.def(py::init<const gp_Lin2d &, const gp_Lin2d &>(), py::arg("Lin1"), py::arg("Lin2"));

// Methods
// cls_GccAna_Lin2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_Lin2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_Lin2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_Lin2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Lin2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Lin2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Lin2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Lin2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Lin2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Lin2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Lin2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Lin2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Lin2dBisec.def("IsDone", (Standard_Boolean (GccAna_Lin2dBisec::*)() const) &GccAna_Lin2dBisec::IsDone, "Returns True when the algorithm succeded.");
cls_GccAna_Lin2dBisec.def("NbSolutions", (Standard_Integer (GccAna_Lin2dBisec::*)() const) &GccAna_Lin2dBisec::NbSolutions, "Returns the number of solutions and raise NotDone if the constructor wasn't called before.");
cls_GccAna_Lin2dBisec.def("ThisSolution", (gp_Lin2d (GccAna_Lin2dBisec::*)(const Standard_Integer) const) &GccAna_Lin2dBisec::ThisSolution, "Returns the solution number Index . The first solution is the inside one and the second is the outside one. For the first solution the direction is D1+D2 (D1 is the direction of the first argument and D2 the direction of the second argument). For the second solution the direction is D1-D2. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"));
cls_GccAna_Lin2dBisec.def("Intersection1", [](GccAna_Lin2dBisec &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Intersection1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the intersection point between the result number Index and the first argument. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Lin2dBisec.def("Intersection2", [](GccAna_Lin2dBisec &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Intersection2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the intersection point between the result number Index and the second argument. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));

// CLASS: GCCANA_LIN2DTANOBL
py::class_<GccAna_Lin2dTanObl> cls_GccAna_Lin2dTanObl(mod, "GccAna_Lin2dTanObl", "This class implements the algorithms used to create 2d line tangent to a circle or a point and making an angle with a line. The angle is in radians. The origin of the solution is the tangency point with the first argument. Its direction is making an angle Angle with the second argument.");

// Constructors
cls_GccAna_Lin2dTanObl.def(py::init<const gp_Pnt2d &, const gp_Lin2d &, const Standard_Real>(), py::arg("ThePoint"), py::arg("TheLine"), py::arg("TheAngle"));
cls_GccAna_Lin2dTanObl.def(py::init<const GccEnt_QualifiedCirc &, const gp_Lin2d &, const Standard_Real>(), py::arg("Qualified1"), py::arg("TheLine"), py::arg("TheAngle"));

// Methods
// cls_GccAna_Lin2dTanObl.def_static("operator new_", (void * (*)(size_t)) &GccAna_Lin2dTanObl::operator new, "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanObl.def_static("operator delete_", (void (*)(void *)) &GccAna_Lin2dTanObl::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanObl.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Lin2dTanObl::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanObl.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Lin2dTanObl::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanObl.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Lin2dTanObl::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Lin2dTanObl.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Lin2dTanObl::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Lin2dTanObl.def("IsDone", (Standard_Boolean (GccAna_Lin2dTanObl::*)() const) &GccAna_Lin2dTanObl::IsDone, "Returns True if the algorithm succeeded. Note: IsDone protects against a failure arising from a more internal intersection algorithm, which has reached its numeric limits.");
cls_GccAna_Lin2dTanObl.def("NbSolutions", (Standard_Integer (GccAna_Lin2dTanObl::*)() const) &GccAna_Lin2dTanObl::NbSolutions, "Returns the number of of lines, representing solutions computed by this algorithm. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Lin2dTanObl.def("ThisSolution", (gp_Lin2d (GccAna_Lin2dTanObl::*)(const Standard_Integer) const) &GccAna_Lin2dTanObl::ThisSolution, "Returns the solution number Index. Be careful: the Index is only a way to get all the solutions, but is not associated to theses outside the context of the algorithm-object. raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"));
cls_GccAna_Lin2dTanObl.def("WhichQualifier", (void (GccAna_Lin2dTanObl::*)(const Standard_Integer, GccEnt_Position &) const) &GccAna_Lin2dTanObl::WhichQualifier, "Returns the qualifier Qualif1 of the tangency argument for the solution of index Index computed by this algorithm. The returned qualifier is: - that specified at the start of construction when the solutions are defined as enclosing or outside with respect to the argument, or - that computed during construction (i.e. enclosing or outside) when the solutions are defined as unqualified with respect to the argument, or - GccEnt_noqualifier if the tangency argument is a point. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("Qualif1"));
cls_GccAna_Lin2dTanObl.def("Tangency1", [](GccAna_Lin2dTanObl &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Tangency1(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point ParSol on the solution curv. ParArg is the intrinsic parameter of the point ParArg on the argument curv. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));
cls_GccAna_Lin2dTanObl.def("Intersection2", [](GccAna_Lin2dTanObl &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Intersection2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the intersection between the result number Index and the third argument. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));

// CLASS: GCCANA_LIN2DTANPAR
py::class_<GccAna_Lin2dTanPar> cls_GccAna_Lin2dTanPar(mod, "GccAna_Lin2dTanPar", "This class implements the algorithms used to create 2d line tangent to a circle or a point and parallel to another line. The solution has the same orientation as the second argument. Describes functions for building a 2D line parallel to a line and: - tangential to a circle, or - passing through a point. A Lin2dTanPar object provides a framework for: - defining the construction of 2D line(s), - implementing the construction algorithm, and consulting the result(s).");

// Constructors
cls_GccAna_Lin2dTanPar.def(py::init<const gp_Pnt2d &, const gp_Lin2d &>(), py::arg("ThePoint"), py::arg("Lin1"));
cls_GccAna_Lin2dTanPar.def(py::init<const GccEnt_QualifiedCirc &, const gp_Lin2d &>(), py::arg("Qualified1"), py::arg("Lin1"));

// Methods
// cls_GccAna_Lin2dTanPar.def_static("operator new_", (void * (*)(size_t)) &GccAna_Lin2dTanPar::operator new, "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanPar.def_static("operator delete_", (void (*)(void *)) &GccAna_Lin2dTanPar::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanPar.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Lin2dTanPar::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanPar.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Lin2dTanPar::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanPar.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Lin2dTanPar::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Lin2dTanPar.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Lin2dTanPar::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Lin2dTanPar.def("IsDone", (Standard_Boolean (GccAna_Lin2dTanPar::*)() const) &GccAna_Lin2dTanPar::IsDone, "Returns True if the algorithm succeeded.");
cls_GccAna_Lin2dTanPar.def("NbSolutions", (Standard_Integer (GccAna_Lin2dTanPar::*)() const) &GccAna_Lin2dTanPar::NbSolutions, "Returns the number of solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Lin2dTanPar.def("ThisSolution", (gp_Lin2d (GccAna_Lin2dTanPar::*)(const Standard_Integer) const) &GccAna_Lin2dTanPar::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be careful: the Index is only a way to get all the solutions, but is not associated to those outside the context of the algorithm-object. raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"));
cls_GccAna_Lin2dTanPar.def("WhichQualifier", (void (GccAna_Lin2dTanPar::*)(const Standard_Integer, GccEnt_Position &) const) &GccAna_Lin2dTanPar::WhichQualifier, "Returns the informations about the qualifiers of the tangency arguments concerning the solution number Index. It returns the real qualifiers (the qualifiers given to the constructor method in case of enclosed, enclosing and outside and the qualifiers computed in case of unqualified). Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("Qualif1"));
cls_GccAna_Lin2dTanPar.def("Tangency1", [](GccAna_Lin2dTanPar &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & Pnt){ self.Tangency1(Index, ParSol, ParArg, Pnt); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point on the solution curv. ParArg is the intrinsic parameter of the point on the argument curv. ParArg is equal 0 when the solution is passing thrue a point. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("Pnt"));

// CLASS: GCCANA_LIN2DTANPER
py::class_<GccAna_Lin2dTanPer> cls_GccAna_Lin2dTanPer(mod, "GccAna_Lin2dTanPer", "This class implements the algorithms used to create 2d lines tangent to a circle or a point and perpendicular to a line or a circle. Describes functions for building a 2D line perpendicular to a line and: - tangential to a circle, or - passing through a point. A Lin2dTanPer object provides a framework for: - defining the construction of 2D line(s), - implementing the construction algorithm, and - consulting the result(s).");

// Constructors
cls_GccAna_Lin2dTanPer.def(py::init<const gp_Pnt2d &, const gp_Lin2d &>(), py::arg("ThePnt"), py::arg("TheLin"));
cls_GccAna_Lin2dTanPer.def(py::init<const gp_Pnt2d &, const gp_Circ2d &>(), py::arg("ThePnt"), py::arg("TheCircle"));
cls_GccAna_Lin2dTanPer.def(py::init<const GccEnt_QualifiedCirc &, const gp_Lin2d &>(), py::arg("Qualified1"), py::arg("TheLin"));
cls_GccAna_Lin2dTanPer.def(py::init<const GccEnt_QualifiedCirc &, const gp_Circ2d &>(), py::arg("Qualified1"), py::arg("TheCircle"));

// Methods
// cls_GccAna_Lin2dTanPer.def_static("operator new_", (void * (*)(size_t)) &GccAna_Lin2dTanPer::operator new, "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanPer.def_static("operator delete_", (void (*)(void *)) &GccAna_Lin2dTanPer::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanPer.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Lin2dTanPer::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Lin2dTanPer.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Lin2dTanPer::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Lin2dTanPer.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Lin2dTanPer::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Lin2dTanPer.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Lin2dTanPer::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Lin2dTanPer.def("IsDone", (Standard_Boolean (GccAna_Lin2dTanPer::*)() const) &GccAna_Lin2dTanPer::IsDone, "Returns True if the algorithm succeeded.");
cls_GccAna_Lin2dTanPer.def("NbSolutions", (Standard_Integer (GccAna_Lin2dTanPer::*)() const) &GccAna_Lin2dTanPer::NbSolutions, "Returns the number of solutions. Raises NotDone if the construction algorithm didn't succeed.");
cls_GccAna_Lin2dTanPer.def("WhichQualifier", (void (GccAna_Lin2dTanPer::*)(const Standard_Integer, GccEnt_Position &) const) &GccAna_Lin2dTanPer::WhichQualifier, "Returns the qualifier Qualif1 of the tangency argument for the solution of index Index computed by this algorithm. The returned qualifier is: - that specified at the start of construction when the solutions are defined as enclosing or outside with respect to the argument, or - that computed during construction (i.e. enclosing or outside) when the solutions are defined as unqualified with respect to the argument, or - GccEnt_noqualifier if the tangency argument is a point. Exceptions Standard_OutOfRange if Index is less than zero or greater than the number of solutions computed by this algorithm. StdFail_NotDone if the construction fails.", py::arg("Index"), py::arg("Qualif1"));
cls_GccAna_Lin2dTanPer.def("ThisSolution", (gp_Lin2d (GccAna_Lin2dTanPer::*)(const Standard_Integer) const) &GccAna_Lin2dTanPer::ThisSolution, "Returns the solution number Index and raises OutOfRange exception if Index is greater than the number of solutions. Be careful: the Index is only a way to get all the solutions, but is not associated to those outside the context of the algorithm-object. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"));
cls_GccAna_Lin2dTanPer.def("Tangency1", [](GccAna_Lin2dTanPer &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & Pnt){ self.Tangency1(Index, ParSol, ParArg, Pnt); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the tangency point between the result number Index and the first argument. ParSol is the intrinsic parameter of the point on the solution curv. ParArg is the intrinsic parameter of the point on the argument curv. If the first argument is a point ParArg is equal zero. raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("Pnt"));
cls_GccAna_Lin2dTanPer.def("Intersection2", [](GccAna_Lin2dTanPer &self, const Standard_Integer Index, Standard_Real & ParSol, Standard_Real & ParArg, gp_Pnt2d & PntSol){ self.Intersection2(Index, ParSol, ParArg, PntSol); return std::tuple<Standard_Real &, Standard_Real &>(ParSol, ParArg); }, "Returns informations about the intersection between the solution number Index and the second argument. It returns the first intersection in a case of Lin2dTanPer which is perpendicular to a circle . ParSol is the intrinsic parameter of the point on the solution curv. ParArg is the intrinsic parameter of the point on the argument curv. Raises NotDone if the construction algorithm didn't succeed. It raises OutOfRange if Index is greater than the number of solutions.", py::arg("Index"), py::arg("ParSol"), py::arg("ParArg"), py::arg("PntSol"));

// CLASS: GCCANA_LINPNT2DBISEC
py::class_<GccAna_LinPnt2dBisec> cls_GccAna_LinPnt2dBisec(mod, "GccAna_LinPnt2dBisec", "Describes functions for building bisecting curves between a 2D line and a point. A bisecting curve between a line and a point is such a curve that each of its points is at the same distance from the circle and the point. It can be a parabola or a line, depending on the relative position of the line and the circle. There is always one unique solution. A LinPnt2dBisec object provides a framework for: - defining the construction of the bisecting curve, - implementing the construction algorithm, and - consulting the result.");

// Constructors
cls_GccAna_LinPnt2dBisec.def(py::init<const gp_Lin2d &, const gp_Pnt2d &>(), py::arg("Line1"), py::arg("Point2"));

// Methods
// cls_GccAna_LinPnt2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_LinPnt2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_LinPnt2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_LinPnt2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_LinPnt2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_LinPnt2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_LinPnt2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_LinPnt2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_LinPnt2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_LinPnt2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_LinPnt2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_LinPnt2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_LinPnt2dBisec.def("IsDone", (Standard_Boolean (GccAna_LinPnt2dBisec::*)() const) &GccAna_LinPnt2dBisec::IsDone, "Returns True if the algorithm succeeded.");
cls_GccAna_LinPnt2dBisec.def("ThisSolution", (opencascade::handle<GccInt_Bisec> (GccAna_LinPnt2dBisec::*)() const) &GccAna_LinPnt2dBisec::ThisSolution, "Returns the number of solutions. It raises NotDone if the construction algorithm didn't succeed.");

// CLASS: GCCANA_NOSOLUTION
py::class_<GccAna_NoSolution, opencascade::handle<GccAna_NoSolution>, Standard_Failure> cls_GccAna_NoSolution(mod, "GccAna_NoSolution", "None");

// Constructors
cls_GccAna_NoSolution.def(py::init<>());
cls_GccAna_NoSolution.def(py::init<const Standard_CString>(), py::arg("theMessage"));

// Methods
cls_GccAna_NoSolution.def_static("Raise_", (void (*)(const Standard_CString)) &GccAna_NoSolution::Raise, "None", py::arg("theMessage"));
cls_GccAna_NoSolution.def_static("Raise_", (void (*)(Standard_SStream &)) &GccAna_NoSolution::Raise, "None", py::arg("theMessage"));
cls_GccAna_NoSolution.def_static("NewInstance_", (opencascade::handle<GccAna_NoSolution> (*)(const Standard_CString)) &GccAna_NoSolution::NewInstance, "None", py::arg("theMessage"));
cls_GccAna_NoSolution.def_static("get_type_name_", (const char * (*)()) &GccAna_NoSolution::get_type_name, "None");
cls_GccAna_NoSolution.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &GccAna_NoSolution::get_type_descriptor, "None");
cls_GccAna_NoSolution.def("DynamicType", (const opencascade::handle<Standard_Type> & (GccAna_NoSolution::*)() const) &GccAna_NoSolution::DynamicType, "None");

// CLASS: GCCANA_PNT2DBISEC
py::class_<GccAna_Pnt2dBisec> cls_GccAna_Pnt2dBisec(mod, "GccAna_Pnt2dBisec", "This class implements the algorithms used to create the bisecting line between two 2d points Describes functions for building a bisecting line between two 2D points. The bisecting line between two points is the bisector of the segment which joins the two points, if these are not coincident. The algorithm does not find a solution if the two points are coincident. A Pnt2dBisec object provides a framework for: - defining the construction of the bisecting line, - implementing the construction algorithm, and consulting the result.");

// Constructors
cls_GccAna_Pnt2dBisec.def(py::init<const gp_Pnt2d &, const gp_Pnt2d &>(), py::arg("Point1"), py::arg("Point2"));

// Methods
// cls_GccAna_Pnt2dBisec.def_static("operator new_", (void * (*)(size_t)) &GccAna_Pnt2dBisec::operator new, "None", py::arg("theSize"));
// cls_GccAna_Pnt2dBisec.def_static("operator delete_", (void (*)(void *)) &GccAna_Pnt2dBisec::operator delete, "None", py::arg("theAddress"));
// cls_GccAna_Pnt2dBisec.def_static("operator new[]_", (void * (*)(size_t)) &GccAna_Pnt2dBisec::operator new[], "None", py::arg("theSize"));
// cls_GccAna_Pnt2dBisec.def_static("operator delete[]_", (void (*)(void *)) &GccAna_Pnt2dBisec::operator delete[], "None", py::arg("theAddress"));
// cls_GccAna_Pnt2dBisec.def_static("operator new_", (void * (*)(size_t, void *)) &GccAna_Pnt2dBisec::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_GccAna_Pnt2dBisec.def_static("operator delete_", (void (*)(void *, void *)) &GccAna_Pnt2dBisec::operator delete, "None", py::arg(""), py::arg(""));
cls_GccAna_Pnt2dBisec.def("IsDone", (Standard_Boolean (GccAna_Pnt2dBisec::*)() const) &GccAna_Pnt2dBisec::IsDone, "Returns true (this construction algorithm never fails).");
cls_GccAna_Pnt2dBisec.def("HasSolution", (Standard_Boolean (GccAna_Pnt2dBisec::*)() const) &GccAna_Pnt2dBisec::HasSolution, "Returns true if this algorithm has a solution, i.e. if the two points are not coincident.");
cls_GccAna_Pnt2dBisec.def("ThisSolution", (gp_Lin2d (GccAna_Pnt2dBisec::*)() const) &GccAna_Pnt2dBisec::ThisSolution, "Returns a line, representing the solution computed by this algorithm.");


}
