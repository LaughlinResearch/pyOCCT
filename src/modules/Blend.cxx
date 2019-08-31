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
#include <Blend_DecrochStatus.hxx>
#include <Blend_Status.hxx>
#include <math_FunctionSetWithDerivatives.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <math_Vector.hxx>
#include <math_Matrix.hxx>
#include <gp_Pnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <GeomAbs_Shape.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Blend_Point.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_Array1OfVec2d.hxx>
#include <Blend_AppFunction.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <Blend_Function.hxx>
#include <Standard_Handle.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <Blend_FuncInv.hxx>
#include <gp_Pnt2d.hxx>
#include <Blend_CSFunction.hxx>
#include <Blend_CurvPointFuncInv.hxx>
#include <Blend_RstRstFunction.hxx>
#include <NCollection_Sequence.hxx>
#include <Blend_SequenceOfPoint.hxx>
#include <Blend_SurfCurvFuncInv.hxx>
#include <Blend_SurfPointFuncInv.hxx>
#include <Blend_SurfRstFunction.hxx>
#include <bind_NCollection_Sequence.hxx>

PYBIND11_MODULE(Blend, mod) {

py::module::import("OCCT.math");
py::module::import("OCCT.Standard");
py::module::import("OCCT.gp");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.Adaptor2d");
py::module::import("OCCT.NCollection");

// ENUM: BLEND_DECROCHSTATUS
py::enum_<Blend_DecrochStatus>(mod, "Blend_DecrochStatus", "None")
	.value("Blend_NoDecroch", Blend_DecrochStatus::Blend_NoDecroch)
	.value("Blend_DecrochRst1", Blend_DecrochStatus::Blend_DecrochRst1)
	.value("Blend_DecrochRst2", Blend_DecrochStatus::Blend_DecrochRst2)
	.value("Blend_DecrochBoth", Blend_DecrochStatus::Blend_DecrochBoth)
	.export_values();


// ENUM: BLEND_STATUS
py::enum_<Blend_Status>(mod, "Blend_Status", "None")
	.value("Blend_StepTooLarge", Blend_Status::Blend_StepTooLarge)
	.value("Blend_StepTooSmall", Blend_Status::Blend_StepTooSmall)
	.value("Blend_Backward", Blend_Status::Blend_Backward)
	.value("Blend_SamePoints", Blend_Status::Blend_SamePoints)
	.value("Blend_OnRst1", Blend_Status::Blend_OnRst1)
	.value("Blend_OnRst2", Blend_Status::Blend_OnRst2)
	.value("Blend_OnRst12", Blend_Status::Blend_OnRst12)
	.value("Blend_OK", Blend_Status::Blend_OK)
	.export_values();


// CLASS: BLEND_APPFUNCTION
py::class_<Blend_AppFunction, math_FunctionSetWithDerivatives> cls_Blend_AppFunction(mod, "Blend_AppFunction", "Deferred class for a function used to compute a blending surface between two surfaces, using a guide line. The vector <X> used in Value, Values and Derivatives methods has to be the vector of the parametric coordinates U1,V1, U2,V2, of the extremities of a section on the first and second surface.");

// Methods
// cls_Blend_AppFunction.def_static("operator new_", (void * (*)(size_t)) &Blend_AppFunction::operator new, "None", py::arg("theSize"));
// cls_Blend_AppFunction.def_static("operator delete_", (void (*)(void *)) &Blend_AppFunction::operator delete, "None", py::arg("theAddress"));
// cls_Blend_AppFunction.def_static("operator new[]_", (void * (*)(size_t)) &Blend_AppFunction::operator new[], "None", py::arg("theSize"));
// cls_Blend_AppFunction.def_static("operator delete[]_", (void (*)(void *)) &Blend_AppFunction::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_AppFunction.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_AppFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_AppFunction.def_static("operator delete_", (void (*)(void *, void *)) &Blend_AppFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_AppFunction.def("NbVariables", (Standard_Integer (Blend_AppFunction::*)() const) &Blend_AppFunction::NbVariables, "returns the number of variables of the function.");
cls_Blend_AppFunction.def("NbEquations", (Standard_Integer (Blend_AppFunction::*)() const) &Blend_AppFunction::NbEquations, "returns the number of equations of the function.");
cls_Blend_AppFunction.def("Value", (Standard_Boolean (Blend_AppFunction::*)(const math_Vector &, math_Vector &)) &Blend_AppFunction::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_AppFunction.def("Derivatives", (Standard_Boolean (Blend_AppFunction::*)(const math_Vector &, math_Matrix &)) &Blend_AppFunction::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_AppFunction.def("Values", (Standard_Boolean (Blend_AppFunction::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_AppFunction::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_AppFunction.def("Set", (void (Blend_AppFunction::*)(const Standard_Real)) &Blend_AppFunction::Set, "Sets the value of the parameter along the guide line. This determines the plane in which the solution has to be found.", py::arg("Param"));
cls_Blend_AppFunction.def("Set", (void (Blend_AppFunction::*)(const Standard_Real, const Standard_Real)) &Blend_AppFunction::Set, "Sets the bounds of the parametric interval on the guide line. This determines the derivatives in these values if the function is not Cn.", py::arg("First"), py::arg("Last"));
cls_Blend_AppFunction.def("GetTolerance", (void (Blend_AppFunction::*)(math_Vector &, const Standard_Real) const) &Blend_AppFunction::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 4 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_AppFunction.def("GetBounds", (void (Blend_AppFunction::*)(math_Vector &, math_Vector &) const) &Blend_AppFunction::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 4 variables. Returns in the vector SupBound the greatest values allowed for each of the 4 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_AppFunction.def("IsSolution", (Standard_Boolean (Blend_AppFunction::*)(const math_Vector &, const Standard_Real)) &Blend_AppFunction::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space. The computation is made at the current value of the parameter on the guide line.", py::arg("Sol"), py::arg("Tol"));
cls_Blend_AppFunction.def("GetMinimalDistance", (Standard_Real (Blend_AppFunction::*)() const) &Blend_AppFunction::GetMinimalDistance, "Returns the minimal Distance beetween two extremitys of calculed sections.");
cls_Blend_AppFunction.def("Pnt1", (const gp_Pnt & (Blend_AppFunction::*)() const) &Blend_AppFunction::Pnt1, "Returns the point on the first support.");
cls_Blend_AppFunction.def("Pnt2", (const gp_Pnt & (Blend_AppFunction::*)() const) &Blend_AppFunction::Pnt2, "Returns the point on the first support.");
cls_Blend_AppFunction.def("IsRational", (Standard_Boolean (Blend_AppFunction::*)() const) &Blend_AppFunction::IsRational, "Returns if the section is rationnal");
cls_Blend_AppFunction.def("GetSectionSize", (Standard_Real (Blend_AppFunction::*)() const) &Blend_AppFunction::GetSectionSize, "Returns the length of the maximum section");
cls_Blend_AppFunction.def("GetMinimalWeight", (void (Blend_AppFunction::*)(TColStd_Array1OfReal &) const) &Blend_AppFunction::GetMinimalWeight, "Compute the minimal value of weight for each poles of all sections.", py::arg("Weigths"));
cls_Blend_AppFunction.def("NbIntervals", (Standard_Integer (Blend_AppFunction::*)(const GeomAbs_Shape) const) &Blend_AppFunction::NbIntervals, "Returns the number of intervals for continuity <S>. May be one if Continuity(me) >= <S>", py::arg("S"));
cls_Blend_AppFunction.def("Intervals", (void (Blend_AppFunction::*)(TColStd_Array1OfReal &, const GeomAbs_Shape) const) &Blend_AppFunction::Intervals, "Stores in <T> the parameters bounding the intervals of continuity <S>.", py::arg("T"), py::arg("S"));
cls_Blend_AppFunction.def("GetShape", [](Blend_AppFunction &self, Standard_Integer & NbPoles, Standard_Integer & NbKnots, Standard_Integer & Degree, Standard_Integer & NbPoles2d){ self.GetShape(NbPoles, NbKnots, Degree, NbPoles2d); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(NbPoles, NbKnots, Degree, NbPoles2d); }, "None", py::arg("NbPoles"), py::arg("NbKnots"), py::arg("Degree"), py::arg("NbPoles2d"));
cls_Blend_AppFunction.def("GetTolerance", (void (Blend_AppFunction::*)(const Standard_Real, const Standard_Real, const Standard_Real, math_Vector &, math_Vector &) const) &Blend_AppFunction::GetTolerance, "Returns the tolerance to reach in approximation to respecte BoundTol error at the Boundary AngleTol tangent error at the Boundary SurfTol error inside the surface.", py::arg("BoundTol"), py::arg("SurfTol"), py::arg("AngleTol"), py::arg("Tol3d"), py::arg("Tol1D"));
cls_Blend_AppFunction.def("Knots", (void (Blend_AppFunction::*)(TColStd_Array1OfReal &)) &Blend_AppFunction::Knots, "None", py::arg("TKnots"));
cls_Blend_AppFunction.def("Mults", (void (Blend_AppFunction::*)(TColStd_Array1OfInteger &)) &Blend_AppFunction::Mults, "None", py::arg("TMults"));
cls_Blend_AppFunction.def("Section", (Standard_Boolean (Blend_AppFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_AppFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("Weigths"), py::arg("DWeigths"));
cls_Blend_AppFunction.def("Section", (void (Blend_AppFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfPnt2d &, TColStd_Array1OfReal &)) &Blend_AppFunction::Section, "None", py::arg("P"), py::arg("Poles"), py::arg("Poles2d"), py::arg("Weigths"));
cls_Blend_AppFunction.def("Section", (Standard_Boolean (Blend_AppFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_AppFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("D2Poles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("D2Poles2d"), py::arg("Weigths"), py::arg("DWeigths"), py::arg("D2Weigths"));
cls_Blend_AppFunction.def("Resolution", [](Blend_AppFunction &self, const Standard_Integer IC2d, const Standard_Real Tol, Standard_Real & TolU, Standard_Real & TolV){ self.Resolution(IC2d, Tol, TolU, TolV); return std::tuple<Standard_Real &, Standard_Real &>(TolU, TolV); }, "None", py::arg("IC2d"), py::arg("Tol"), py::arg("TolU"), py::arg("TolV"));
cls_Blend_AppFunction.def("Parameter", (Standard_Real (Blend_AppFunction::*)(const Blend_Point &) const) &Blend_AppFunction::Parameter, "Returns the parameter of the point P. Used to impose the parameters in the approximation.", py::arg("P"));

// CLASS: BLEND_FUNCTION
py::class_<Blend_Function, Blend_AppFunction> cls_Blend_Function(mod, "Blend_Function", "Deferred class for a function used to compute a blending surface between two surfaces, using a guide line. The vector <X> used in Value, Values and Derivatives methods has to be the vector of the parametric coordinates U1,V1, U2,V2, of the extremities of a section on the first and second surface.");

// Methods
// cls_Blend_Function.def_static("operator new_", (void * (*)(size_t)) &Blend_Function::operator new, "None", py::arg("theSize"));
// cls_Blend_Function.def_static("operator delete_", (void (*)(void *)) &Blend_Function::operator delete, "None", py::arg("theAddress"));
// cls_Blend_Function.def_static("operator new[]_", (void * (*)(size_t)) &Blend_Function::operator new[], "None", py::arg("theSize"));
// cls_Blend_Function.def_static("operator delete[]_", (void (*)(void *)) &Blend_Function::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_Function.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_Function::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_Function.def_static("operator delete_", (void (*)(void *, void *)) &Blend_Function::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_Function.def("NbVariables", (Standard_Integer (Blend_Function::*)() const) &Blend_Function::NbVariables, "Returns 4.");
cls_Blend_Function.def("NbEquations", (Standard_Integer (Blend_Function::*)() const) &Blend_Function::NbEquations, "returns the number of equations of the function.");
cls_Blend_Function.def("Value", (Standard_Boolean (Blend_Function::*)(const math_Vector &, math_Vector &)) &Blend_Function::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_Function.def("Derivatives", (Standard_Boolean (Blend_Function::*)(const math_Vector &, math_Matrix &)) &Blend_Function::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_Function.def("Values", (Standard_Boolean (Blend_Function::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_Function::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_Function.def("Set", (void (Blend_Function::*)(const Standard_Real)) &Blend_Function::Set, "Sets the value of the parameter along the guide line. This determines the plane in which the solution has to be found.", py::arg("Param"));
cls_Blend_Function.def("Set", (void (Blend_Function::*)(const Standard_Real, const Standard_Real)) &Blend_Function::Set, "Sets the bounds of the parametric interval on the guide line. This determines the derivatives in these values if the function is not Cn.", py::arg("First"), py::arg("Last"));
cls_Blend_Function.def("GetTolerance", (void (Blend_Function::*)(math_Vector &, const Standard_Real) const) &Blend_Function::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 4 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_Function.def("GetBounds", (void (Blend_Function::*)(math_Vector &, math_Vector &) const) &Blend_Function::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 4 variables. Returns in the vector SupBound the greatest values allowed for each of the 4 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_Function.def("IsSolution", (Standard_Boolean (Blend_Function::*)(const math_Vector &, const Standard_Real)) &Blend_Function::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space. The computation is made at the current value of the parameter on the guide line.", py::arg("Sol"), py::arg("Tol"));
cls_Blend_Function.def("Pnt1", (const gp_Pnt & (Blend_Function::*)() const) &Blend_Function::Pnt1, "Returns the point on the first support.");
cls_Blend_Function.def("Pnt2", (const gp_Pnt & (Blend_Function::*)() const) &Blend_Function::Pnt2, "Returns the point on the seconde support.");
cls_Blend_Function.def("PointOnS1", (const gp_Pnt & (Blend_Function::*)() const) &Blend_Function::PointOnS1, "Returns the point on the first surface, at parameter Sol(1),Sol(2) (Sol is the vector used in the call of IsSolution.");
cls_Blend_Function.def("PointOnS2", (const gp_Pnt & (Blend_Function::*)() const) &Blend_Function::PointOnS2, "Returns the point on the second surface, at parameter Sol(3),Sol(4) (Sol is the vector used in the call of IsSolution.");
cls_Blend_Function.def("IsTangencyPoint", (Standard_Boolean (Blend_Function::*)() const) &Blend_Function::IsTangencyPoint, "Returns True when it is not possible to compute the tangent vectors at PointOnS1 and/or PointOnS2.");
cls_Blend_Function.def("TangentOnS1", (const gp_Vec & (Blend_Function::*)() const) &Blend_Function::TangentOnS1, "Returns the tangent vector at PointOnS1, in 3d space.");
cls_Blend_Function.def("Tangent2dOnS1", (const gp_Vec2d & (Blend_Function::*)() const) &Blend_Function::Tangent2dOnS1, "Returns the tangent vector at PointOnS1, in the parametric space of the first surface.");
cls_Blend_Function.def("TangentOnS2", (const gp_Vec & (Blend_Function::*)() const) &Blend_Function::TangentOnS2, "Returns the tangent vector at PointOnS2, in 3d space.");
cls_Blend_Function.def("Tangent2dOnS2", (const gp_Vec2d & (Blend_Function::*)() const) &Blend_Function::Tangent2dOnS2, "Returns the tangent vector at PointOnS2, in the parametric space of the second surface.");
cls_Blend_Function.def("Tangent", (void (Blend_Function::*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, gp_Vec &, gp_Vec &, gp_Vec &, gp_Vec &) const) &Blend_Function::Tangent, "Returns the tangent vector at the section, at the beginning and the end of the section, and returns the normal (of the surfaces) at these points.", py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("TgFirst"), py::arg("TgLast"), py::arg("NormFirst"), py::arg("NormLast"));
cls_Blend_Function.def("TwistOnS1", (Standard_Boolean (Blend_Function::*)() const) &Blend_Function::TwistOnS1, "None");
cls_Blend_Function.def("TwistOnS2", (Standard_Boolean (Blend_Function::*)() const) &Blend_Function::TwistOnS2, "None");
cls_Blend_Function.def("GetShape", [](Blend_Function &self, Standard_Integer & NbPoles, Standard_Integer & NbKnots, Standard_Integer & Degree, Standard_Integer & NbPoles2d){ self.GetShape(NbPoles, NbKnots, Degree, NbPoles2d); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(NbPoles, NbKnots, Degree, NbPoles2d); }, "None", py::arg("NbPoles"), py::arg("NbKnots"), py::arg("Degree"), py::arg("NbPoles2d"));
cls_Blend_Function.def("GetTolerance", (void (Blend_Function::*)(const Standard_Real, const Standard_Real, const Standard_Real, math_Vector &, math_Vector &) const) &Blend_Function::GetTolerance, "Returns the tolerance to reach in approximation to respecte BoundTol error at the Boundary AngleTol tangent error at the Boundary SurfTol error inside the surface.", py::arg("BoundTol"), py::arg("SurfTol"), py::arg("AngleTol"), py::arg("Tol3d"), py::arg("Tol1D"));
cls_Blend_Function.def("Knots", (void (Blend_Function::*)(TColStd_Array1OfReal &)) &Blend_Function::Knots, "None", py::arg("TKnots"));
cls_Blend_Function.def("Mults", (void (Blend_Function::*)(TColStd_Array1OfInteger &)) &Blend_Function::Mults, "None", py::arg("TMults"));
cls_Blend_Function.def("Section", (Standard_Boolean (Blend_Function::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_Function::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("Weigths"), py::arg("DWeigths"));
cls_Blend_Function.def("Section", (void (Blend_Function::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfPnt2d &, TColStd_Array1OfReal &)) &Blend_Function::Section, "None", py::arg("P"), py::arg("Poles"), py::arg("Poles2d"), py::arg("Weigths"));
cls_Blend_Function.def("Section", (Standard_Boolean (Blend_Function::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_Function::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("D2Poles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("D2Poles2d"), py::arg("Weigths"), py::arg("DWeigths"), py::arg("D2Weigths"));

// CLASS: BLEND_FUNCINV
py::class_<Blend_FuncInv, math_FunctionSetWithDerivatives> cls_Blend_FuncInv(mod, "Blend_FuncInv", "Deferred class for a function used to compute a blending surface between two surfaces, using a guide line. This function is used to find a solution on a restriction of one of the surface. The vector <X> used in Value, Values and Derivatives methods has to be the vector of the parametric coordinates t,w,U,V where t is the parameter on the curve on surface, w is the parameter on the guide line, U,V are the parametric coordinates of a point on the partner surface.");

// Methods
// cls_Blend_FuncInv.def_static("operator new_", (void * (*)(size_t)) &Blend_FuncInv::operator new, "None", py::arg("theSize"));
// cls_Blend_FuncInv.def_static("operator delete_", (void (*)(void *)) &Blend_FuncInv::operator delete, "None", py::arg("theAddress"));
// cls_Blend_FuncInv.def_static("operator new[]_", (void * (*)(size_t)) &Blend_FuncInv::operator new[], "None", py::arg("theSize"));
// cls_Blend_FuncInv.def_static("operator delete[]_", (void (*)(void *)) &Blend_FuncInv::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_FuncInv.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_FuncInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_FuncInv.def_static("operator delete_", (void (*)(void *, void *)) &Blend_FuncInv::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_FuncInv.def("NbVariables", (Standard_Integer (Blend_FuncInv::*)() const) &Blend_FuncInv::NbVariables, "Returns 4.");
cls_Blend_FuncInv.def("NbEquations", (Standard_Integer (Blend_FuncInv::*)() const) &Blend_FuncInv::NbEquations, "returns the number of equations of the function.");
cls_Blend_FuncInv.def("Value", (Standard_Boolean (Blend_FuncInv::*)(const math_Vector &, math_Vector &)) &Blend_FuncInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_FuncInv.def("Derivatives", (Standard_Boolean (Blend_FuncInv::*)(const math_Vector &, math_Matrix &)) &Blend_FuncInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_FuncInv.def("Values", (Standard_Boolean (Blend_FuncInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_FuncInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_FuncInv.def("Set", (void (Blend_FuncInv::*)(const Standard_Boolean, const opencascade::handle<Adaptor2d_HCurve2d> &)) &Blend_FuncInv::Set, "Sets the CurveOnSurface on which a solution has to be found. If <OnFirst> is set to Standard_True, the curve will be on the first surface, otherwise the curve is on the second one.", py::arg("OnFirst"), py::arg("COnSurf"));
cls_Blend_FuncInv.def("GetTolerance", (void (Blend_FuncInv::*)(math_Vector &, const Standard_Real) const) &Blend_FuncInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 4 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_FuncInv.def("GetBounds", (void (Blend_FuncInv::*)(math_Vector &, math_Vector &) const) &Blend_FuncInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 4 variables. Returns in the vector SupBound the greatest values allowed for each of the 4 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_FuncInv.def("IsSolution", (Standard_Boolean (Blend_FuncInv::*)(const math_Vector &, const Standard_Real)) &Blend_FuncInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// CLASS: BLEND_CSFUNCTION
py::class_<Blend_CSFunction, Blend_AppFunction> cls_Blend_CSFunction(mod, "Blend_CSFunction", "Deferred class for a function used to compute a blending surface between a surface and a curve, using a guide line. The vector <X> used in Value, Values and Derivatives methods may be the vector of the parametric coordinates U,V, W of the extremities of a section on the surface and the curve.");

// Methods
// cls_Blend_CSFunction.def_static("operator new_", (void * (*)(size_t)) &Blend_CSFunction::operator new, "None", py::arg("theSize"));
// cls_Blend_CSFunction.def_static("operator delete_", (void (*)(void *)) &Blend_CSFunction::operator delete, "None", py::arg("theAddress"));
// cls_Blend_CSFunction.def_static("operator new[]_", (void * (*)(size_t)) &Blend_CSFunction::operator new[], "None", py::arg("theSize"));
// cls_Blend_CSFunction.def_static("operator delete[]_", (void (*)(void *)) &Blend_CSFunction::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_CSFunction.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_CSFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_CSFunction.def_static("operator delete_", (void (*)(void *, void *)) &Blend_CSFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_CSFunction.def("NbVariables", (Standard_Integer (Blend_CSFunction::*)() const) &Blend_CSFunction::NbVariables, "Returns 3 (default value). Can be redefined.");
cls_Blend_CSFunction.def("NbEquations", (Standard_Integer (Blend_CSFunction::*)() const) &Blend_CSFunction::NbEquations, "returns the number of equations of the function.");
cls_Blend_CSFunction.def("Value", (Standard_Boolean (Blend_CSFunction::*)(const math_Vector &, math_Vector &)) &Blend_CSFunction::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_CSFunction.def("Derivatives", (Standard_Boolean (Blend_CSFunction::*)(const math_Vector &, math_Matrix &)) &Blend_CSFunction::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_CSFunction.def("Values", (Standard_Boolean (Blend_CSFunction::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_CSFunction::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_CSFunction.def("Set", (void (Blend_CSFunction::*)(const Standard_Real)) &Blend_CSFunction::Set, "Sets the value of the parameter along the guide line. This determines the plane in which the solution has to be found.", py::arg("Param"));
cls_Blend_CSFunction.def("Set", (void (Blend_CSFunction::*)(const Standard_Real, const Standard_Real)) &Blend_CSFunction::Set, "Sets the bounds of the parametric interval on the guide line. This determines the derivatives in these values if the function is not Cn.", py::arg("First"), py::arg("Last"));
cls_Blend_CSFunction.def("GetTolerance", (void (Blend_CSFunction::*)(math_Vector &, const Standard_Real) const) &Blend_CSFunction::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_CSFunction.def("GetBounds", (void (Blend_CSFunction::*)(math_Vector &, math_Vector &) const) &Blend_CSFunction::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_CSFunction.def("IsSolution", (Standard_Boolean (Blend_CSFunction::*)(const math_Vector &, const Standard_Real)) &Blend_CSFunction::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space. The computation is made at the current value of the parameter on the guide line.", py::arg("Sol"), py::arg("Tol"));
cls_Blend_CSFunction.def("GetMinimalDistance", (Standard_Real (Blend_CSFunction::*)() const) &Blend_CSFunction::GetMinimalDistance, "Returns the minimal Distance beetween two extremitys of calculed sections.");
cls_Blend_CSFunction.def("Pnt1", (const gp_Pnt & (Blend_CSFunction::*)() const) &Blend_CSFunction::Pnt1, "Returns the point on the first support.");
cls_Blend_CSFunction.def("Pnt2", (const gp_Pnt & (Blend_CSFunction::*)() const) &Blend_CSFunction::Pnt2, "Returns the point on the seconde support.");
cls_Blend_CSFunction.def("PointOnS", (const gp_Pnt & (Blend_CSFunction::*)() const) &Blend_CSFunction::PointOnS, "Returns the point on the surface.");
cls_Blend_CSFunction.def("PointOnC", (const gp_Pnt & (Blend_CSFunction::*)() const) &Blend_CSFunction::PointOnC, "Returns the point on the curve.");
cls_Blend_CSFunction.def("Pnt2d", (const gp_Pnt2d & (Blend_CSFunction::*)() const) &Blend_CSFunction::Pnt2d, "Returns U,V coordinates of the point on the surface.");
cls_Blend_CSFunction.def("ParameterOnC", (Standard_Real (Blend_CSFunction::*)() const) &Blend_CSFunction::ParameterOnC, "Returns parameter of the point on the curve.");
cls_Blend_CSFunction.def("IsTangencyPoint", (Standard_Boolean (Blend_CSFunction::*)() const) &Blend_CSFunction::IsTangencyPoint, "Returns True when it is not possible to compute the tangent vectors at PointOnS and/or PointOnC.");
cls_Blend_CSFunction.def("TangentOnS", (const gp_Vec & (Blend_CSFunction::*)() const) &Blend_CSFunction::TangentOnS, "Returns the tangent vector at PointOnS, in 3d space.");
cls_Blend_CSFunction.def("Tangent2d", (const gp_Vec2d & (Blend_CSFunction::*)() const) &Blend_CSFunction::Tangent2d, "Returns the tangent vector at PointOnS, in the parametric space of the first surface.");
cls_Blend_CSFunction.def("TangentOnC", (const gp_Vec & (Blend_CSFunction::*)() const) &Blend_CSFunction::TangentOnC, "Returns the tangent vector at PointOnC, in 3d space.");
cls_Blend_CSFunction.def("Tangent", (void (Blend_CSFunction::*)(const Standard_Real, const Standard_Real, gp_Vec &, gp_Vec &) const) &Blend_CSFunction::Tangent, "Returns the tangent vector at the section, at the beginning and the end of the section, and returns the normal (of the surfaces) at these points.", py::arg("U"), py::arg("V"), py::arg("TgS"), py::arg("NormS"));
cls_Blend_CSFunction.def("GetShape", [](Blend_CSFunction &self, Standard_Integer & NbPoles, Standard_Integer & NbKnots, Standard_Integer & Degree, Standard_Integer & NbPoles2d){ self.GetShape(NbPoles, NbKnots, Degree, NbPoles2d); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(NbPoles, NbKnots, Degree, NbPoles2d); }, "None", py::arg("NbPoles"), py::arg("NbKnots"), py::arg("Degree"), py::arg("NbPoles2d"));
cls_Blend_CSFunction.def("GetTolerance", (void (Blend_CSFunction::*)(const Standard_Real, const Standard_Real, const Standard_Real, math_Vector &, math_Vector &) const) &Blend_CSFunction::GetTolerance, "Returns the tolerance to reach in approximation to respecte BoundTol error at the Boundary AngleTol tangent error at the Boundary SurfTol error inside the surface.", py::arg("BoundTol"), py::arg("SurfTol"), py::arg("AngleTol"), py::arg("Tol3d"), py::arg("Tol1D"));
cls_Blend_CSFunction.def("Knots", (void (Blend_CSFunction::*)(TColStd_Array1OfReal &)) &Blend_CSFunction::Knots, "None", py::arg("TKnots"));
cls_Blend_CSFunction.def("Mults", (void (Blend_CSFunction::*)(TColStd_Array1OfInteger &)) &Blend_CSFunction::Mults, "None", py::arg("TMults"));
cls_Blend_CSFunction.def("Section", (Standard_Boolean (Blend_CSFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_CSFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("Weigths"), py::arg("DWeigths"));
cls_Blend_CSFunction.def("Section", (void (Blend_CSFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfPnt2d &, TColStd_Array1OfReal &)) &Blend_CSFunction::Section, "None", py::arg("P"), py::arg("Poles"), py::arg("Poles2d"), py::arg("Weigths"));
cls_Blend_CSFunction.def("Section", (Standard_Boolean (Blend_CSFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_CSFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("D2Poles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("D2Poles2d"), py::arg("Weigths"), py::arg("DWeigths"), py::arg("D2Weigths"));

// CLASS: BLEND_CURVPOINTFUNCINV
py::class_<Blend_CurvPointFuncInv, math_FunctionSetWithDerivatives> cls_Blend_CurvPointFuncInv(mod, "Blend_CurvPointFuncInv", "Deferred class for a function used to compute a blending surface between a surface and a curve, using a guide line. This function is used to find a solution on a done point of the curve. The vector <X> used in Value, Values and Derivatives methods has to be the vector of the parametric coordinates w, U, V where w is the parameter on the guide line, U,V are the parametric coordinates of a point on the partner surface.");

// Methods
// cls_Blend_CurvPointFuncInv.def_static("operator new_", (void * (*)(size_t)) &Blend_CurvPointFuncInv::operator new, "None", py::arg("theSize"));
// cls_Blend_CurvPointFuncInv.def_static("operator delete_", (void (*)(void *)) &Blend_CurvPointFuncInv::operator delete, "None", py::arg("theAddress"));
// cls_Blend_CurvPointFuncInv.def_static("operator new[]_", (void * (*)(size_t)) &Blend_CurvPointFuncInv::operator new[], "None", py::arg("theSize"));
// cls_Blend_CurvPointFuncInv.def_static("operator delete[]_", (void (*)(void *)) &Blend_CurvPointFuncInv::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_CurvPointFuncInv.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_CurvPointFuncInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_CurvPointFuncInv.def_static("operator delete_", (void (*)(void *, void *)) &Blend_CurvPointFuncInv::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_CurvPointFuncInv.def("NbVariables", (Standard_Integer (Blend_CurvPointFuncInv::*)() const) &Blend_CurvPointFuncInv::NbVariables, "Returns 3.");
cls_Blend_CurvPointFuncInv.def("NbEquations", (Standard_Integer (Blend_CurvPointFuncInv::*)() const) &Blend_CurvPointFuncInv::NbEquations, "returns the number of equations of the function.");
cls_Blend_CurvPointFuncInv.def("Value", (Standard_Boolean (Blend_CurvPointFuncInv::*)(const math_Vector &, math_Vector &)) &Blend_CurvPointFuncInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_CurvPointFuncInv.def("Derivatives", (Standard_Boolean (Blend_CurvPointFuncInv::*)(const math_Vector &, math_Matrix &)) &Blend_CurvPointFuncInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_CurvPointFuncInv.def("Values", (Standard_Boolean (Blend_CurvPointFuncInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_CurvPointFuncInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_CurvPointFuncInv.def("Set", (void (Blend_CurvPointFuncInv::*)(const gp_Pnt &)) &Blend_CurvPointFuncInv::Set, "Set the Point on which a solution has to be found.", py::arg("P"));
cls_Blend_CurvPointFuncInv.def("GetTolerance", (void (Blend_CurvPointFuncInv::*)(math_Vector &, const Standard_Real) const) &Blend_CurvPointFuncInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_CurvPointFuncInv.def("GetBounds", (void (Blend_CurvPointFuncInv::*)(math_Vector &, math_Vector &) const) &Blend_CurvPointFuncInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_CurvPointFuncInv.def("IsSolution", (Standard_Boolean (Blend_CurvPointFuncInv::*)(const math_Vector &, const Standard_Real)) &Blend_CurvPointFuncInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// CLASS: BLEND_POINT
py::class_<Blend_Point> cls_Blend_Point(mod, "Blend_Point", "None");

// Constructors
cls_Blend_Point.def(py::init<>());
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &>(), py::arg("Pts"), py::arg("Ptc"), py::arg("Param"), py::arg("U"), py::arg("V"), py::arg("W"), py::arg("Tgs"), py::arg("Tgc"), py::arg("Tg2d"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pts"), py::arg("Ptc"), py::arg("Param"), py::arg("U"), py::arg("V"), py::arg("W"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC1"), py::arg("PC2"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def(py::init<const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC1"), py::arg("PC2"));

// Methods
// cls_Blend_Point.def_static("operator new_", (void * (*)(size_t)) &Blend_Point::operator new, "None", py::arg("theSize"));
// cls_Blend_Point.def_static("operator delete_", (void (*)(void *)) &Blend_Point::operator delete, "None", py::arg("theAddress"));
// cls_Blend_Point.def_static("operator new[]_", (void * (*)(size_t)) &Blend_Point::operator new[], "None", py::arg("theSize"));
// cls_Blend_Point.def_static("operator delete[]_", (void (*)(void *)) &Blend_Point::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_Point.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_Point::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_Point.def_static("operator delete_", (void (*)(void *, void *)) &Blend_Point::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &)) &Blend_Point::SetValue, "Set the values for a point on 2 surfaces, with tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &Blend_Point::SetValue, "Set the values for a point on 2 surfaces, without tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &)) &Blend_Point::SetValue, "Set the values for a point on a surface and a curve, with tangents.", py::arg("Pts"), py::arg("Ptc"), py::arg("Param"), py::arg("U"), py::arg("V"), py::arg("W"), py::arg("Tgs"), py::arg("Tgc"), py::arg("Tg2d"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &Blend_Point::SetValue, "Set the values for a point on a surface and a curve, without tangents.", py::arg("Pts"), py::arg("Ptc"), py::arg("Param"), py::arg("U"), py::arg("V"), py::arg("W"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &)) &Blend_Point::SetValue, "Creates a point on a surface and a curve on surface, with tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &Blend_Point::SetValue, "Creates a point on a surface and a curve on surface, without tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_Vec &, const gp_Vec &, const gp_Vec2d &, const gp_Vec2d &)) &Blend_Point::SetValue, "Creates a point on two curves on surfaces, with tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC1"), py::arg("PC2"), py::arg("Tg1"), py::arg("Tg2"), py::arg("Tg12d"), py::arg("Tg22d"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &Blend_Point::SetValue, "Creates a point on two curves on surfaces, without tangents.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("U1"), py::arg("V1"), py::arg("U2"), py::arg("V2"), py::arg("PC1"), py::arg("PC2"));
cls_Blend_Point.def("SetValue", (void (Blend_Point::*)(const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Real, const Standard_Real)) &Blend_Point::SetValue, "Creates a point on two curves.", py::arg("Pt1"), py::arg("Pt2"), py::arg("Param"), py::arg("PC1"), py::arg("PC2"));
cls_Blend_Point.def("SetParameter", (void (Blend_Point::*)(const Standard_Real)) &Blend_Point::SetParameter, "Changes parameter on existing point", py::arg("Param"));
cls_Blend_Point.def("Parameter", (Standard_Real (Blend_Point::*)() const) &Blend_Point::Parameter, "None");
cls_Blend_Point.def("IsTangencyPoint", (Standard_Boolean (Blend_Point::*)() const) &Blend_Point::IsTangencyPoint, "Returns Standard_True if it was not possible to compute the tangent vectors at PointOnS1 and/or PointOnS2.");
cls_Blend_Point.def("PointOnS1", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnS1, "None");
cls_Blend_Point.def("PointOnS2", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnS2, "None");
cls_Blend_Point.def("ParametersOnS1", [](Blend_Point &self, Standard_Real & U, Standard_Real & V){ self.ParametersOnS1(U, V); return std::tuple<Standard_Real &, Standard_Real &>(U, V); }, "None", py::arg("U"), py::arg("V"));
cls_Blend_Point.def("ParametersOnS2", [](Blend_Point &self, Standard_Real & U, Standard_Real & V){ self.ParametersOnS2(U, V); return std::tuple<Standard_Real &, Standard_Real &>(U, V); }, "None", py::arg("U"), py::arg("V"));
cls_Blend_Point.def("TangentOnS1", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnS1, "None");
cls_Blend_Point.def("TangentOnS2", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnS2, "None");
cls_Blend_Point.def("Tangent2dOnS1", (gp_Vec2d (Blend_Point::*)() const) &Blend_Point::Tangent2dOnS1, "None");
cls_Blend_Point.def("Tangent2dOnS2", (gp_Vec2d (Blend_Point::*)() const) &Blend_Point::Tangent2dOnS2, "None");
cls_Blend_Point.def("PointOnS", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnS, "None");
cls_Blend_Point.def("PointOnC", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnC, "None");
cls_Blend_Point.def("ParametersOnS", [](Blend_Point &self, Standard_Real & U, Standard_Real & V){ self.ParametersOnS(U, V); return std::tuple<Standard_Real &, Standard_Real &>(U, V); }, "None", py::arg("U"), py::arg("V"));
cls_Blend_Point.def("ParameterOnC", (Standard_Real (Blend_Point::*)() const) &Blend_Point::ParameterOnC, "None");
cls_Blend_Point.def("TangentOnS", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnS, "None");
cls_Blend_Point.def("TangentOnC", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnC, "None");
cls_Blend_Point.def("Tangent2d", (gp_Vec2d (Blend_Point::*)() const) &Blend_Point::Tangent2d, "None");
cls_Blend_Point.def("PointOnC1", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnC1, "None");
cls_Blend_Point.def("PointOnC2", (const gp_Pnt & (Blend_Point::*)() const) &Blend_Point::PointOnC2, "None");
cls_Blend_Point.def("ParameterOnC1", (Standard_Real (Blend_Point::*)() const) &Blend_Point::ParameterOnC1, "None");
cls_Blend_Point.def("ParameterOnC2", (Standard_Real (Blend_Point::*)() const) &Blend_Point::ParameterOnC2, "None");
cls_Blend_Point.def("TangentOnC1", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnC1, "None");
cls_Blend_Point.def("TangentOnC2", (const gp_Vec & (Blend_Point::*)() const) &Blend_Point::TangentOnC2, "None");

// CLASS: BLEND_RSTRSTFUNCTION
py::class_<Blend_RstRstFunction, Blend_AppFunction> cls_Blend_RstRstFunction(mod, "Blend_RstRstFunction", "Deferred class for a function used to compute a blending surface between a surface and a pcurve on an other Surface, using a guide line. The vector <X> used in Value, Values and Derivatives methods may be the vector of the parametric coordinates U,V, W of the extremities of a section on the surface and the curve.");

// Methods
// cls_Blend_RstRstFunction.def_static("operator new_", (void * (*)(size_t)) &Blend_RstRstFunction::operator new, "None", py::arg("theSize"));
// cls_Blend_RstRstFunction.def_static("operator delete_", (void (*)(void *)) &Blend_RstRstFunction::operator delete, "None", py::arg("theAddress"));
// cls_Blend_RstRstFunction.def_static("operator new[]_", (void * (*)(size_t)) &Blend_RstRstFunction::operator new[], "None", py::arg("theSize"));
// cls_Blend_RstRstFunction.def_static("operator delete[]_", (void (*)(void *)) &Blend_RstRstFunction::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_RstRstFunction.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_RstRstFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_RstRstFunction.def_static("operator delete_", (void (*)(void *, void *)) &Blend_RstRstFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_RstRstFunction.def("NbVariables", (Standard_Integer (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::NbVariables, "Returns 2 (default value). Can be redefined.");
cls_Blend_RstRstFunction.def("NbEquations", (Standard_Integer (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::NbEquations, "returns the number of equations of the function.");
cls_Blend_RstRstFunction.def("Value", (Standard_Boolean (Blend_RstRstFunction::*)(const math_Vector &, math_Vector &)) &Blend_RstRstFunction::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_RstRstFunction.def("Derivatives", (Standard_Boolean (Blend_RstRstFunction::*)(const math_Vector &, math_Matrix &)) &Blend_RstRstFunction::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_RstRstFunction.def("Values", (Standard_Boolean (Blend_RstRstFunction::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_RstRstFunction::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_RstRstFunction.def("Set", (void (Blend_RstRstFunction::*)(const Standard_Real)) &Blend_RstRstFunction::Set, "Sets the value of the parameter along the guide line. This determines the plane in which the solution has to be found.", py::arg("Param"));
cls_Blend_RstRstFunction.def("Set", (void (Blend_RstRstFunction::*)(const Standard_Real, const Standard_Real)) &Blend_RstRstFunction::Set, "Sets the bounds of the parametric interval on the guide line. This determines the derivatives in these values if the function is not Cn.", py::arg("First"), py::arg("Last"));
cls_Blend_RstRstFunction.def("GetTolerance", (void (Blend_RstRstFunction::*)(math_Vector &, const Standard_Real) const) &Blend_RstRstFunction::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each variable; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_RstRstFunction.def("GetBounds", (void (Blend_RstRstFunction::*)(math_Vector &, math_Vector &) const) &Blend_RstRstFunction::GetBounds, "Returns in the vector InfBound the lowest values allowed for each variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_RstRstFunction.def("IsSolution", (Standard_Boolean (Blend_RstRstFunction::*)(const math_Vector &, const Standard_Real)) &Blend_RstRstFunction::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space. The computation is made at the current value of the parameter on the guide line.", py::arg("Sol"), py::arg("Tol"));
cls_Blend_RstRstFunction.def("GetMinimalDistance", (Standard_Real (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::GetMinimalDistance, "Returns the minimal Distance beetween two extremitys of calculed sections.");
cls_Blend_RstRstFunction.def("Pnt1", (const gp_Pnt & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Pnt1, "Returns the point on the first support.");
cls_Blend_RstRstFunction.def("Pnt2", (const gp_Pnt & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Pnt2, "Returns the point on the seconde support.");
cls_Blend_RstRstFunction.def("PointOnRst1", (const gp_Pnt & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::PointOnRst1, "Returns the point on the surface.");
cls_Blend_RstRstFunction.def("PointOnRst2", (const gp_Pnt & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::PointOnRst2, "Returns the point on the curve.");
cls_Blend_RstRstFunction.def("Pnt2dOnRst1", (const gp_Pnt2d & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Pnt2dOnRst1, "Returns U,V coordinates of the point on the surface.");
cls_Blend_RstRstFunction.def("Pnt2dOnRst2", (const gp_Pnt2d & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Pnt2dOnRst2, "Returns U,V coordinates of the point on the curve on surface.");
cls_Blend_RstRstFunction.def("ParameterOnRst1", (Standard_Real (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::ParameterOnRst1, "Returns parameter of the point on the curve.");
cls_Blend_RstRstFunction.def("ParameterOnRst2", (Standard_Real (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::ParameterOnRst2, "Returns parameter of the point on the curve.");
cls_Blend_RstRstFunction.def("IsTangencyPoint", (Standard_Boolean (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::IsTangencyPoint, "Returns True when it is not possible to compute the tangent vectors at PointOnS and/or PointOnRst.");
cls_Blend_RstRstFunction.def("TangentOnRst1", (const gp_Vec & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::TangentOnRst1, "Returns the tangent vector at PointOnS, in 3d space.");
cls_Blend_RstRstFunction.def("Tangent2dOnRst1", (const gp_Vec2d & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Tangent2dOnRst1, "Returns the tangent vector at PointOnS, in the parametric space of the first surface.");
cls_Blend_RstRstFunction.def("TangentOnRst2", (const gp_Vec & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::TangentOnRst2, "Returns the tangent vector at PointOnC, in 3d space.");
cls_Blend_RstRstFunction.def("Tangent2dOnRst2", (const gp_Vec2d & (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::Tangent2dOnRst2, "Returns the tangent vector at PointOnRst, in the parametric space of the second surface.");
cls_Blend_RstRstFunction.def("Decroch", (Blend_DecrochStatus (Blend_RstRstFunction::*)(const math_Vector &, gp_Vec &, gp_Vec &, gp_Vec &, gp_Vec &) const) &Blend_RstRstFunction::Decroch, "Enables to implement a criterion of decrochage specific to the function. Warning: Can be called without previous call of issolution but the values calculated can be senseless.", py::arg("Sol"), py::arg("NRst1"), py::arg("TgRst1"), py::arg("NRst2"), py::arg("TgRst2"));
cls_Blend_RstRstFunction.def("IsRational", (Standard_Boolean (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::IsRational, "Returns if the section is rationnal");
cls_Blend_RstRstFunction.def("GetSectionSize", (Standard_Real (Blend_RstRstFunction::*)() const) &Blend_RstRstFunction::GetSectionSize, "Returns the length of the maximum section");
cls_Blend_RstRstFunction.def("GetMinimalWeight", (void (Blend_RstRstFunction::*)(TColStd_Array1OfReal &) const) &Blend_RstRstFunction::GetMinimalWeight, "Compute the minimal value of weight for each poles of all sections.", py::arg("Weigths"));
cls_Blend_RstRstFunction.def("NbIntervals", (Standard_Integer (Blend_RstRstFunction::*)(const GeomAbs_Shape) const) &Blend_RstRstFunction::NbIntervals, "Returns the number of intervals for continuity <S>. May be one if Continuity(me) >= <S>", py::arg("S"));
cls_Blend_RstRstFunction.def("Intervals", (void (Blend_RstRstFunction::*)(TColStd_Array1OfReal &, const GeomAbs_Shape) const) &Blend_RstRstFunction::Intervals, "Stores in <T> the parameters bounding the intervals of continuity <S>.", py::arg("T"), py::arg("S"));
cls_Blend_RstRstFunction.def("GetShape", [](Blend_RstRstFunction &self, Standard_Integer & NbPoles, Standard_Integer & NbKnots, Standard_Integer & Degree, Standard_Integer & NbPoles2d){ self.GetShape(NbPoles, NbKnots, Degree, NbPoles2d); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(NbPoles, NbKnots, Degree, NbPoles2d); }, "None", py::arg("NbPoles"), py::arg("NbKnots"), py::arg("Degree"), py::arg("NbPoles2d"));
cls_Blend_RstRstFunction.def("GetTolerance", (void (Blend_RstRstFunction::*)(const Standard_Real, const Standard_Real, const Standard_Real, math_Vector &, math_Vector &) const) &Blend_RstRstFunction::GetTolerance, "Returns the tolerance to reach in approximation to respecte BoundTol error at the Boundary AngleTol tangent error at the Boundary SurfTol error inside the surface.", py::arg("BoundTol"), py::arg("SurfTol"), py::arg("AngleTol"), py::arg("Tol3d"), py::arg("Tol1D"));
cls_Blend_RstRstFunction.def("Knots", (void (Blend_RstRstFunction::*)(TColStd_Array1OfReal &)) &Blend_RstRstFunction::Knots, "None", py::arg("TKnots"));
cls_Blend_RstRstFunction.def("Mults", (void (Blend_RstRstFunction::*)(TColStd_Array1OfInteger &)) &Blend_RstRstFunction::Mults, "None", py::arg("TMults"));
cls_Blend_RstRstFunction.def("Section", (void (Blend_RstRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfPnt2d &, TColStd_Array1OfReal &)) &Blend_RstRstFunction::Section, "None", py::arg("P"), py::arg("Poles"), py::arg("Poles2d"), py::arg("Weigths"));
cls_Blend_RstRstFunction.def("Section", (Standard_Boolean (Blend_RstRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_RstRstFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("Weigths"), py::arg("DWeigths"));
cls_Blend_RstRstFunction.def("Section", (Standard_Boolean (Blend_RstRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_RstRstFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("D2Poles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("D2Poles2d"), py::arg("Weigths"), py::arg("DWeigths"), py::arg("D2Weigths"));

// TYPEDEF: BLEND_SEQUENCEOFPOINT
bind_NCollection_Sequence<Blend_Point>(mod, "Blend_SequenceOfPoint", py::module_local(false));

// CLASS: BLEND_SURFCURVFUNCINV
py::class_<Blend_SurfCurvFuncInv, math_FunctionSetWithDerivatives> cls_Blend_SurfCurvFuncInv(mod, "Blend_SurfCurvFuncInv", "Deferred class for a function used to compute a blending surface between a surface and a curve, using a guide line. This function is used to find a solution on a done restriction of the surface.");

// Methods
// cls_Blend_SurfCurvFuncInv.def_static("operator new_", (void * (*)(size_t)) &Blend_SurfCurvFuncInv::operator new, "None", py::arg("theSize"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete_", (void (*)(void *)) &Blend_SurfCurvFuncInv::operator delete, "None", py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator new[]_", (void * (*)(size_t)) &Blend_SurfCurvFuncInv::operator new[], "None", py::arg("theSize"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete[]_", (void (*)(void *)) &Blend_SurfCurvFuncInv::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_SurfCurvFuncInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete_", (void (*)(void *, void *)) &Blend_SurfCurvFuncInv::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_SurfCurvFuncInv.def("NbVariables", (Standard_Integer (Blend_SurfCurvFuncInv::*)() const) &Blend_SurfCurvFuncInv::NbVariables, "Returns 3.");
cls_Blend_SurfCurvFuncInv.def("NbEquations", (Standard_Integer (Blend_SurfCurvFuncInv::*)() const) &Blend_SurfCurvFuncInv::NbEquations, "returns the number of equations of the function.");
cls_Blend_SurfCurvFuncInv.def("Value", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Vector &)) &Blend_SurfCurvFuncInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_SurfCurvFuncInv.def("Derivatives", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Matrix &)) &Blend_SurfCurvFuncInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_SurfCurvFuncInv.def("Values", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_SurfCurvFuncInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_SurfCurvFuncInv.def("Set", (void (Blend_SurfCurvFuncInv::*)(const opencascade::handle<Adaptor2d_HCurve2d> &)) &Blend_SurfCurvFuncInv::Set, "Set the Point on which a solution has to be found.", py::arg("Rst"));
cls_Blend_SurfCurvFuncInv.def("GetTolerance", (void (Blend_SurfCurvFuncInv::*)(math_Vector &, const Standard_Real) const) &Blend_SurfCurvFuncInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_SurfCurvFuncInv.def("GetBounds", (void (Blend_SurfCurvFuncInv::*)(math_Vector &, math_Vector &) const) &Blend_SurfCurvFuncInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_SurfCurvFuncInv.def("IsSolution", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, const Standard_Real)) &Blend_SurfCurvFuncInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// CLASS: BLEND_SURFPOINTFUNCINV
py::class_<Blend_SurfPointFuncInv, math_FunctionSetWithDerivatives> cls_Blend_SurfPointFuncInv(mod, "Blend_SurfPointFuncInv", "Deferred class for a function used to compute a blending surface between a surface and a curve, using a guide line. This function is used to find a solution on a done point of the curve.");

// Methods
// cls_Blend_SurfPointFuncInv.def_static("operator new_", (void * (*)(size_t)) &Blend_SurfPointFuncInv::operator new, "None", py::arg("theSize"));
// cls_Blend_SurfPointFuncInv.def_static("operator delete_", (void (*)(void *)) &Blend_SurfPointFuncInv::operator delete, "None", py::arg("theAddress"));
// cls_Blend_SurfPointFuncInv.def_static("operator new[]_", (void * (*)(size_t)) &Blend_SurfPointFuncInv::operator new[], "None", py::arg("theSize"));
// cls_Blend_SurfPointFuncInv.def_static("operator delete[]_", (void (*)(void *)) &Blend_SurfPointFuncInv::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_SurfPointFuncInv.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_SurfPointFuncInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_SurfPointFuncInv.def_static("operator delete_", (void (*)(void *, void *)) &Blend_SurfPointFuncInv::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_SurfPointFuncInv.def("NbVariables", (Standard_Integer (Blend_SurfPointFuncInv::*)() const) &Blend_SurfPointFuncInv::NbVariables, "Returns 3.");
cls_Blend_SurfPointFuncInv.def("NbEquations", (Standard_Integer (Blend_SurfPointFuncInv::*)() const) &Blend_SurfPointFuncInv::NbEquations, "returns the number of equations of the function.");
cls_Blend_SurfPointFuncInv.def("Value", (Standard_Boolean (Blend_SurfPointFuncInv::*)(const math_Vector &, math_Vector &)) &Blend_SurfPointFuncInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_SurfPointFuncInv.def("Derivatives", (Standard_Boolean (Blend_SurfPointFuncInv::*)(const math_Vector &, math_Matrix &)) &Blend_SurfPointFuncInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_SurfPointFuncInv.def("Values", (Standard_Boolean (Blend_SurfPointFuncInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_SurfPointFuncInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_SurfPointFuncInv.def("Set", (void (Blend_SurfPointFuncInv::*)(const gp_Pnt &)) &Blend_SurfPointFuncInv::Set, "Set the Point on which a solution has to be found.", py::arg("P"));
cls_Blend_SurfPointFuncInv.def("GetTolerance", (void (Blend_SurfPointFuncInv::*)(math_Vector &, const Standard_Real) const) &Blend_SurfPointFuncInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_SurfPointFuncInv.def("GetBounds", (void (Blend_SurfPointFuncInv::*)(math_Vector &, math_Vector &) const) &Blend_SurfPointFuncInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_SurfPointFuncInv.def("IsSolution", (Standard_Boolean (Blend_SurfPointFuncInv::*)(const math_Vector &, const Standard_Real)) &Blend_SurfPointFuncInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// CLASS: BLEND_SURFRSTFUNCTION
py::class_<Blend_SurfRstFunction, Blend_AppFunction> cls_Blend_SurfRstFunction(mod, "Blend_SurfRstFunction", "Deferred class for a function used to compute a blending surface between a surface and a pcurve on an other Surface, using a guide line. The vector <X> used in Value, Values and Derivatives methods may be the vector of the parametric coordinates U,V, W of the extremities of a section on the surface and the curve.");

// Methods
// cls_Blend_SurfRstFunction.def_static("operator new_", (void * (*)(size_t)) &Blend_SurfRstFunction::operator new, "None", py::arg("theSize"));
// cls_Blend_SurfRstFunction.def_static("operator delete_", (void (*)(void *)) &Blend_SurfRstFunction::operator delete, "None", py::arg("theAddress"));
// cls_Blend_SurfRstFunction.def_static("operator new[]_", (void * (*)(size_t)) &Blend_SurfRstFunction::operator new[], "None", py::arg("theSize"));
// cls_Blend_SurfRstFunction.def_static("operator delete[]_", (void (*)(void *)) &Blend_SurfRstFunction::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_SurfRstFunction.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_SurfRstFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_SurfRstFunction.def_static("operator delete_", (void (*)(void *, void *)) &Blend_SurfRstFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_SurfRstFunction.def("NbVariables", (Standard_Integer (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::NbVariables, "Returns 3 (default value). Can be redefined.");
cls_Blend_SurfRstFunction.def("NbEquations", (Standard_Integer (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::NbEquations, "returns the number of equations of the function.");
cls_Blend_SurfRstFunction.def("Value", (Standard_Boolean (Blend_SurfRstFunction::*)(const math_Vector &, math_Vector &)) &Blend_SurfRstFunction::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_SurfRstFunction.def("Derivatives", (Standard_Boolean (Blend_SurfRstFunction::*)(const math_Vector &, math_Matrix &)) &Blend_SurfRstFunction::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_SurfRstFunction.def("Values", (Standard_Boolean (Blend_SurfRstFunction::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_SurfRstFunction::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_SurfRstFunction.def("Set", (void (Blend_SurfRstFunction::*)(const Standard_Real)) &Blend_SurfRstFunction::Set, "Sets the value of the parameter along the guide line. This determines the plane in which the solution has to be found.", py::arg("Param"));
cls_Blend_SurfRstFunction.def("Set", (void (Blend_SurfRstFunction::*)(const Standard_Real, const Standard_Real)) &Blend_SurfRstFunction::Set, "Sets the bounds of the parametric interval on the guide line. This determines the derivatives in these values if the function is not Cn.", py::arg("First"), py::arg("Last"));
cls_Blend_SurfRstFunction.def("GetTolerance", (void (Blend_SurfRstFunction::*)(math_Vector &, const Standard_Real) const) &Blend_SurfRstFunction::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each variable; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_SurfRstFunction.def("GetBounds", (void (Blend_SurfRstFunction::*)(math_Vector &, math_Vector &) const) &Blend_SurfRstFunction::GetBounds, "Returns in the vector InfBound the lowest values allowed for each variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_SurfRstFunction.def("IsSolution", (Standard_Boolean (Blend_SurfRstFunction::*)(const math_Vector &, const Standard_Real)) &Blend_SurfRstFunction::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space. The computation is made at the current value of the parameter on the guide line.", py::arg("Sol"), py::arg("Tol"));
cls_Blend_SurfRstFunction.def("GetMinimalDistance", (Standard_Real (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::GetMinimalDistance, "Returns the minimal Distance beetween two extremitys of calculed sections.");
cls_Blend_SurfRstFunction.def("Pnt1", (const gp_Pnt & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Pnt1, "Returns the point on the first support.");
cls_Blend_SurfRstFunction.def("Pnt2", (const gp_Pnt & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Pnt2, "Returns the point on the seconde support.");
cls_Blend_SurfRstFunction.def("PointOnS", (const gp_Pnt & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::PointOnS, "Returns the point on the surface.");
cls_Blend_SurfRstFunction.def("PointOnRst", (const gp_Pnt & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::PointOnRst, "Returns the point on the curve.");
cls_Blend_SurfRstFunction.def("Pnt2dOnS", (const gp_Pnt2d & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Pnt2dOnS, "Returns U,V coordinates of the point on the surface.");
cls_Blend_SurfRstFunction.def("Pnt2dOnRst", (const gp_Pnt2d & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Pnt2dOnRst, "Returns U,V coordinates of the point on the curve on surface.");
cls_Blend_SurfRstFunction.def("ParameterOnRst", (Standard_Real (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::ParameterOnRst, "Returns parameter of the point on the curve.");
cls_Blend_SurfRstFunction.def("IsTangencyPoint", (Standard_Boolean (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::IsTangencyPoint, "Returns True when it is not possible to compute the tangent vectors at PointOnS and/or PointOnRst.");
cls_Blend_SurfRstFunction.def("TangentOnS", (const gp_Vec & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::TangentOnS, "Returns the tangent vector at PointOnS, in 3d space.");
cls_Blend_SurfRstFunction.def("Tangent2dOnS", (const gp_Vec2d & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Tangent2dOnS, "Returns the tangent vector at PointOnS, in the parametric space of the first surface.");
cls_Blend_SurfRstFunction.def("TangentOnRst", (const gp_Vec & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::TangentOnRst, "Returns the tangent vector at PointOnC, in 3d space.");
cls_Blend_SurfRstFunction.def("Tangent2dOnRst", (const gp_Vec2d & (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::Tangent2dOnRst, "Returns the tangent vector at PointOnRst, in the parametric space of the second surface.");
cls_Blend_SurfRstFunction.def("Decroch", (Standard_Boolean (Blend_SurfRstFunction::*)(const math_Vector &, gp_Vec &, gp_Vec &) const) &Blend_SurfRstFunction::Decroch, "Enables implementation of a criterion of decrochage specific to the function.", py::arg("Sol"), py::arg("NS"), py::arg("TgS"));
cls_Blend_SurfRstFunction.def("IsRational", (Standard_Boolean (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::IsRational, "Returns if the section is rationnal");
cls_Blend_SurfRstFunction.def("GetSectionSize", (Standard_Real (Blend_SurfRstFunction::*)() const) &Blend_SurfRstFunction::GetSectionSize, "Returns the length of the maximum section");
cls_Blend_SurfRstFunction.def("GetMinimalWeight", (void (Blend_SurfRstFunction::*)(TColStd_Array1OfReal &) const) &Blend_SurfRstFunction::GetMinimalWeight, "Compute the minimal value of weight for each poles of all sections.", py::arg("Weigths"));
cls_Blend_SurfRstFunction.def("NbIntervals", (Standard_Integer (Blend_SurfRstFunction::*)(const GeomAbs_Shape) const) &Blend_SurfRstFunction::NbIntervals, "Returns the number of intervals for continuity <S>. May be one if Continuity(me) >= <S>", py::arg("S"));
cls_Blend_SurfRstFunction.def("Intervals", (void (Blend_SurfRstFunction::*)(TColStd_Array1OfReal &, const GeomAbs_Shape) const) &Blend_SurfRstFunction::Intervals, "Stores in <T> the parameters bounding the intervals of continuity <S>.", py::arg("T"), py::arg("S"));
cls_Blend_SurfRstFunction.def("GetShape", [](Blend_SurfRstFunction &self, Standard_Integer & NbPoles, Standard_Integer & NbKnots, Standard_Integer & Degree, Standard_Integer & NbPoles2d){ self.GetShape(NbPoles, NbKnots, Degree, NbPoles2d); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(NbPoles, NbKnots, Degree, NbPoles2d); }, "None", py::arg("NbPoles"), py::arg("NbKnots"), py::arg("Degree"), py::arg("NbPoles2d"));
cls_Blend_SurfRstFunction.def("GetTolerance", (void (Blend_SurfRstFunction::*)(const Standard_Real, const Standard_Real, const Standard_Real, math_Vector &, math_Vector &) const) &Blend_SurfRstFunction::GetTolerance, "Returns the tolerance to reach in approximation to respecte BoundTol error at the Boundary AngleTol tangent error at the Boundary SurfTol error inside the surface.", py::arg("BoundTol"), py::arg("SurfTol"), py::arg("AngleTol"), py::arg("Tol3d"), py::arg("Tol1D"));
cls_Blend_SurfRstFunction.def("Knots", (void (Blend_SurfRstFunction::*)(TColStd_Array1OfReal &)) &Blend_SurfRstFunction::Knots, "None", py::arg("TKnots"));
cls_Blend_SurfRstFunction.def("Mults", (void (Blend_SurfRstFunction::*)(TColStd_Array1OfInteger &)) &Blend_SurfRstFunction::Mults, "None", py::arg("TMults"));
cls_Blend_SurfRstFunction.def("Section", (Standard_Boolean (Blend_SurfRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_SurfRstFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("Weigths"), py::arg("DWeigths"));
cls_Blend_SurfRstFunction.def("Section", (Standard_Boolean (Blend_SurfRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfVec &, TColgp_Array1OfVec &, TColgp_Array1OfPnt2d &, TColgp_Array1OfVec2d &, TColgp_Array1OfVec2d &, TColStd_Array1OfReal &, TColStd_Array1OfReal &, TColStd_Array1OfReal &)) &Blend_SurfRstFunction::Section, "Used for the first and last section The method returns Standard_True if the derivatives are computed, otherwise it returns Standard_False.", py::arg("P"), py::arg("Poles"), py::arg("DPoles"), py::arg("D2Poles"), py::arg("Poles2d"), py::arg("DPoles2d"), py::arg("D2Poles2d"), py::arg("Weigths"), py::arg("DWeigths"), py::arg("D2Weigths"));
cls_Blend_SurfRstFunction.def("Section", (void (Blend_SurfRstFunction::*)(const Blend_Point &, TColgp_Array1OfPnt &, TColgp_Array1OfPnt2d &, TColStd_Array1OfReal &)) &Blend_SurfRstFunction::Section, "None", py::arg("P"), py::arg("Poles"), py::arg("Poles2d"), py::arg("Weigths"));


}
