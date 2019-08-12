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
#include <gp_Pnt.hxx>
#include <gp_Lin.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Hypr.hxx>
#include <gp_Parab.hxx>
#include <gp_Vec.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Elips2d.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Parab2d.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Ax22d.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <ElCLib.hxx>

void bind_ElCLib(py::module &mod){

py::class_<ElCLib, std::unique_ptr<ElCLib, Deleter<ElCLib>>> cls_ElCLib(mod, "ElCLib", "Provides functions for basic geometric computations on elementary curves such as conics and lines in 2D and 3D space. This includes: - calculation of a point or derived vector on a 2D or 3D curve where: - the curve is provided by the gp package, or defined in reference form (as in the gp package), and - the point is defined by a parameter, - evaluation of the parameter corresponding to a point on a 2D or 3D curve from gp, - various elementary computations which allow you to position parameterized values within the period of a curve. Notes: - ElCLib stands for Elementary Curves Library. - If the curves provided by the gp package are not explicitly parameterized, they still have an implicit parameterization, analogous to that which they infer for the equivalent Geom or Geom2d curves.");

// Constructors

// Fields

// Methods
// cls_ElCLib.def_static("operator new_", (void * (*)(size_t)) &ElCLib::operator new, "None", py::arg("theSize"));
// cls_ElCLib.def_static("operator delete_", (void (*)(void *)) &ElCLib::operator delete, "None", py::arg("theAddress"));
// cls_ElCLib.def_static("operator new[]_", (void * (*)(size_t)) &ElCLib::operator new[], "None", py::arg("theSize"));
// cls_ElCLib.def_static("operator delete[]_", (void (*)(void *)) &ElCLib::operator delete[], "None", py::arg("theAddress"));
// cls_ElCLib.def_static("operator new_", (void * (*)(size_t, void *)) &ElCLib::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ElCLib.def_static("operator delete_", (void (*)(void *, void *)) &ElCLib::operator delete, "None", py::arg(""), py::arg(""));
cls_ElCLib.def_static("InPeriod_", (Standard_Real (*)(const Standard_Real, const Standard_Real, const Standard_Real)) &ElCLib::InPeriod, "Return a value in the range <UFirst, ULast> by adding or removing the period <ULast - UFirst> to <U>. ATTENTION!!! It is expected but not checked that (ULast > UFirst)", py::arg("U"), py::arg("UFirst"), py::arg("ULast"));
cls_ElCLib.def_static("AdjustPeriodic_", [](const Standard_Real UFirst, const Standard_Real ULast, const Standard_Real Precision, Standard_Real & U1, Standard_Real & U2){ ElCLib::AdjustPeriodic(UFirst, ULast, Precision, U1, U2); return std::tuple<Standard_Real &, Standard_Real &>(U1, U2); }, "Adjust U1 and U2 in the parametric range UFirst Ulast of a periodic curve, where ULast - UFirst is its period. To do this, this function: - sets U1 in the range [ UFirst, ULast ] by adding/removing the period to/from the value U1, then - sets U2 in the range [ U1, U1 + period ] by adding/removing the period to/from the value U2. Precision is used to test the equalities.", py::arg("UFirst"), py::arg("ULast"), py::arg("Precision"), py::arg("U1"), py::arg("U2"));
cls_ElCLib.def_static("Value_", (gp_Pnt (*)(const Standard_Real, const gp_Lin &)) &ElCLib::Value, "For elementary curves (lines, circles and conics) from the gp package, computes the point of parameter U. The result is either: - a gp_Pnt point for a curve in 3D space, or - a gp_Pnt2d point for a curve in 2D space.", py::arg("U"), py::arg("L"));
cls_ElCLib.def_static("Value_", (gp_Pnt (*)(const Standard_Real, const gp_Circ &)) &ElCLib::Value, "None", py::arg("U"), py::arg("C"));
cls_ElCLib.def_static("Value_", (gp_Pnt (*)(const Standard_Real, const gp_Elips &)) &ElCLib::Value, "None", py::arg("U"), py::arg("E"));
cls_ElCLib.def_static("Value_", (gp_Pnt (*)(const Standard_Real, const gp_Hypr &)) &ElCLib::Value, "None", py::arg("U"), py::arg("H"));
cls_ElCLib.def_static("Value_", (gp_Pnt (*)(const Standard_Real, const gp_Parab &)) &ElCLib::Value, "None", py::arg("U"), py::arg("Prb"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Lin &, gp_Pnt &, gp_Vec &)) &ElCLib::D1, "For elementary curves (lines, circles and conics) from the gp package, computes: - the point P of parameter U, and - the first derivative vector V1 at this point. The results P and V1 are either: - a gp_Pnt point and a gp_Vec vector, for a curve in 3D space, or - a gp_Pnt2d point and a gp_Vec2d vector, for a curve in 2D space.", py::arg("U"), py::arg("L"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Circ &, gp_Pnt &, gp_Vec &)) &ElCLib::D1, "None", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Elips &, gp_Pnt &, gp_Vec &)) &ElCLib::D1, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Hypr &, gp_Pnt &, gp_Vec &)) &ElCLib::D1, "None", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Parab &, gp_Pnt &, gp_Vec &)) &ElCLib::D1, "None", py::arg("U"), py::arg("Prb"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Circ &, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::D2, "For elementary curves (circles and conics) from the gp package, computes: - the point P of parameter U, and - the first and second derivative vectors V1 and V2 at this point. The results, P, V1 and V2, are either: - a gp_Pnt point and two gp_Vec vectors, for a curve in 3D space, or - a gp_Pnt2d point and two gp_Vec2d vectors, for a curve in 2D space.", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Elips &, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::D2, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Hypr &, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::D2, "None", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Parab &, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::D2, "None", py::arg("U"), py::arg("Prb"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Circ &, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::D3, "For elementary curves (circles, ellipses and hyperbolae) from the gp package, computes: - the point P of parameter U, and - the first, second and third derivative vectors V1, V2 and V3 at this point. The results, P, V1, V2 and V3, are either: - a gp_Pnt point and three gp_Vec vectors, for a curve in 3D space, or - a gp_Pnt2d point and three gp_Vec2d vectors, for a curve in 2D space.", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Elips &, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::D3, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Hypr &, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::D3, "None", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("DN_", (gp_Vec (*)(const Standard_Real, const gp_Lin &, const Standard_Integer)) &ElCLib::DN, "For elementary curves (lines, circles and conics) from the gp package, computes the vector corresponding to the Nth derivative at the point of parameter U. The result is either: - a gp_Vec vector for a curve in 3D space, or - a gp_Vec2d vector for a curve in 2D space. In the following functions N is the order of derivation and should be greater than 0", py::arg("U"), py::arg("L"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec (*)(const Standard_Real, const gp_Circ &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("C"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec (*)(const Standard_Real, const gp_Elips &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("E"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec (*)(const Standard_Real, const gp_Hypr &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("H"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec (*)(const Standard_Real, const gp_Parab &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("Prb"), py::arg("N"));
cls_ElCLib.def_static("Value_", (gp_Pnt2d (*)(const Standard_Real, const gp_Lin2d &)) &ElCLib::Value, "None", py::arg("U"), py::arg("L"));
cls_ElCLib.def_static("Value_", (gp_Pnt2d (*)(const Standard_Real, const gp_Circ2d &)) &ElCLib::Value, "None", py::arg("U"), py::arg("C"));
cls_ElCLib.def_static("Value_", (gp_Pnt2d (*)(const Standard_Real, const gp_Elips2d &)) &ElCLib::Value, "None", py::arg("U"), py::arg("E"));
cls_ElCLib.def_static("Value_", (gp_Pnt2d (*)(const Standard_Real, const gp_Hypr2d &)) &ElCLib::Value, "None", py::arg("U"), py::arg("H"));
cls_ElCLib.def_static("Value_", (gp_Pnt2d (*)(const Standard_Real, const gp_Parab2d &)) &ElCLib::Value, "None", py::arg("U"), py::arg("Prb"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Lin2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::D1, "None", py::arg("U"), py::arg("L"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Circ2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::D1, "None", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Elips2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::D1, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Hypr2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::D1, "None", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D1_", (void (*)(const Standard_Real, const gp_Parab2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::D1, "None", py::arg("U"), py::arg("Prb"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Circ2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D2, "None", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Elips2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D2, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Hypr2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D2, "None", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D2_", (void (*)(const Standard_Real, const gp_Parab2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D2, "None", py::arg("U"), py::arg("Prb"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Circ2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D3, "None", py::arg("U"), py::arg("C"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Elips2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D3, "None", py::arg("U"), py::arg("E"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("D3_", (void (*)(const Standard_Real, const gp_Hypr2d &, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::D3, "In the following functions N is the order of derivation and should be greater than 0", py::arg("U"), py::arg("H"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("DN_", (gp_Vec2d (*)(const Standard_Real, const gp_Lin2d &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("L"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec2d (*)(const Standard_Real, const gp_Circ2d &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("C"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec2d (*)(const Standard_Real, const gp_Elips2d &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("E"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec2d (*)(const Standard_Real, const gp_Hypr2d &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("H"), py::arg("N"));
cls_ElCLib.def_static("DN_", (gp_Vec2d (*)(const Standard_Real, const gp_Parab2d &, const Standard_Integer)) &ElCLib::DN, "None", py::arg("U"), py::arg("Prb"), py::arg("N"));
cls_ElCLib.def_static("LineValue_", (gp_Pnt (*)(const Standard_Real, const gp_Ax1 &)) &ElCLib::LineValue, "Curve evaluation The following basis functions compute the derivatives on elementary curves defined by their geometric characteristics. These functions can be called without constructing a conic from package gp. They are called by the previous functions. Example : A circle is defined by its position and its radius.", py::arg("U"), py::arg("Pos"));
cls_ElCLib.def_static("CircleValue_", (gp_Pnt (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real)) &ElCLib::CircleValue, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"));
cls_ElCLib.def_static("EllipseValue_", (gp_Pnt (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real)) &ElCLib::EllipseValue, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"));
cls_ElCLib.def_static("HyperbolaValue_", (gp_Pnt (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real)) &ElCLib::HyperbolaValue, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"));
cls_ElCLib.def_static("ParabolaValue_", (gp_Pnt (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real)) &ElCLib::ParabolaValue, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"));
cls_ElCLib.def_static("LineD1_", (void (*)(const Standard_Real, const gp_Ax1 &, gp_Pnt &, gp_Vec &)) &ElCLib::LineD1, "None", py::arg("U"), py::arg("Pos"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("CircleD1_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, gp_Pnt &, gp_Vec &)) &ElCLib::CircleD1, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("EllipseD1_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &)) &ElCLib::EllipseD1, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("HyperbolaD1_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &)) &ElCLib::HyperbolaD1, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("ParabolaD1_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, gp_Pnt &, gp_Vec &)) &ElCLib::ParabolaD1, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("CircleD2_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::CircleD2, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("EllipseD2_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::EllipseD2, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("HyperbolaD2_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::HyperbolaD2, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("ParabolaD2_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &)) &ElCLib::ParabolaD2, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("CircleD3_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::CircleD3, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("EllipseD3_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::EllipseD3, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("HyperbolaD3_", (void (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &ElCLib::HyperbolaD3, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("LineDN_", (gp_Vec (*)(const Standard_Real, const gp_Ax1 &, const Standard_Integer)) &ElCLib::LineDN, "In the following functions N is the order of derivation and should be greater than 0", py::arg("U"), py::arg("Pos"), py::arg("N"));
cls_ElCLib.def_static("CircleDN_", (gp_Vec (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Integer)) &ElCLib::CircleDN, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("N"));
cls_ElCLib.def_static("EllipseDN_", (gp_Vec (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, const Standard_Integer)) &ElCLib::EllipseDN, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("N"));
cls_ElCLib.def_static("HyperbolaDN_", (gp_Vec (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Real, const Standard_Integer)) &ElCLib::HyperbolaDN, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("N"));
cls_ElCLib.def_static("ParabolaDN_", (gp_Vec (*)(const Standard_Real, const gp_Ax2 &, const Standard_Real, const Standard_Integer)) &ElCLib::ParabolaDN, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("N"));
cls_ElCLib.def_static("LineValue_", (gp_Pnt2d (*)(const Standard_Real, const gp_Ax2d &)) &ElCLib::LineValue, "None", py::arg("U"), py::arg("Pos"));
cls_ElCLib.def_static("CircleValue_", (gp_Pnt2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real)) &ElCLib::CircleValue, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"));
cls_ElCLib.def_static("EllipseValue_", (gp_Pnt2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real)) &ElCLib::EllipseValue, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"));
cls_ElCLib.def_static("HyperbolaValue_", (gp_Pnt2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real)) &ElCLib::HyperbolaValue, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"));
cls_ElCLib.def_static("ParabolaValue_", (gp_Pnt2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real)) &ElCLib::ParabolaValue, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"));
cls_ElCLib.def_static("LineD1_", (void (*)(const Standard_Real, const gp_Ax2d &, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::LineD1, "None", py::arg("U"), py::arg("Pos"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("CircleD1_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::CircleD1, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("EllipseD1_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::EllipseD1, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("HyperbolaD1_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::HyperbolaD1, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("ParabolaD1_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, gp_Pnt2d &, gp_Vec2d &)) &ElCLib::ParabolaD1, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("P"), py::arg("V1"));
cls_ElCLib.def_static("CircleD2_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::CircleD2, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("EllipseD2_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::EllipseD2, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("HyperbolaD2_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::HyperbolaD2, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("ParabolaD2_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::ParabolaD2, "None", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_ElCLib.def_static("CircleD3_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::CircleD3, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("EllipseD3_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::EllipseD3, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("HyperbolaD3_", (void (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, gp_Pnt2d &, gp_Vec2d &, gp_Vec2d &, gp_Vec2d &)) &ElCLib::HyperbolaD3, "In the following functions N is the order of derivation and should be greater than 0", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_ElCLib.def_static("LineDN_", (gp_Vec2d (*)(const Standard_Real, const gp_Ax2d &, const Standard_Integer)) &ElCLib::LineDN, "None", py::arg("U"), py::arg("Pos"), py::arg("N"));
cls_ElCLib.def_static("CircleDN_", (gp_Vec2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Integer)) &ElCLib::CircleDN, "None", py::arg("U"), py::arg("Pos"), py::arg("Radius"), py::arg("N"));
cls_ElCLib.def_static("EllipseDN_", (gp_Vec2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, const Standard_Integer)) &ElCLib::EllipseDN, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("N"));
cls_ElCLib.def_static("HyperbolaDN_", (gp_Vec2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Real, const Standard_Integer)) &ElCLib::HyperbolaDN, "None", py::arg("U"), py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("N"));
cls_ElCLib.def_static("ParabolaDN_", (gp_Vec2d (*)(const Standard_Real, const gp_Ax22d &, const Standard_Real, const Standard_Integer)) &ElCLib::ParabolaDN, "The following functions compute the parametric value corresponding to a given point on a elementary curve. The point should be on the curve.", py::arg("U"), py::arg("Pos"), py::arg("Focal"), py::arg("N"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Lin &, const gp_Pnt &)) &ElCLib::Parameter, "Computes the parameter value of the point P on the given curve. Note: In its local coordinate system, the parametric equation of the curve is given by the following: - for the line L: P(U) = Po + U*Vo where Po is the origin and Vo the unit vector of its positioning axis. - for the circle C: X(U) = Radius*Cos(U), Y(U) = Radius*Sin(U) - for the ellipse E: X(U) = MajorRadius*Cos(U). Y(U) = MinorRadius*Sin(U) - for the hyperbola H: X(U) = MajorRadius*Ch(U), Y(U) = MinorRadius*Sh(U) - for the parabola Prb: X(U) = U**2 / (2*p) Y(U) = U where p is the distance between the focus and the directrix. Warning The point P must be on the curve. These functions are not protected, however, and if point P is not on the curve, an exception may be raised.", py::arg("L"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Lin2d &, const gp_Pnt2d &)) &ElCLib::Parameter, "parametrization P (U) = L.Location() + U * L.Direction()", py::arg("L"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Circ &, const gp_Pnt &)) &ElCLib::Parameter, "None", py::arg("C"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Circ2d &, const gp_Pnt2d &)) &ElCLib::Parameter, "parametrization In the local coordinate system of the circle X (U) = Radius * Cos (U) Y (U) = Radius * Sin (U)", py::arg("C"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Elips &, const gp_Pnt &)) &ElCLib::Parameter, "None", py::arg("E"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Elips2d &, const gp_Pnt2d &)) &ElCLib::Parameter, "parametrization In the local coordinate system of the Ellipse X (U) = MajorRadius * Cos (U) Y (U) = MinorRadius * Sin (U)", py::arg("E"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Hypr &, const gp_Pnt &)) &ElCLib::Parameter, "None", py::arg("H"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Hypr2d &, const gp_Pnt2d &)) &ElCLib::Parameter, "parametrization In the local coordinate system of the Hyperbola X (U) = MajorRadius * Ch (U) Y (U) = MinorRadius * Sh (U)", py::arg("H"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Parab &, const gp_Pnt &)) &ElCLib::Parameter, "None", py::arg("Prb"), py::arg("P"));
cls_ElCLib.def_static("Parameter_", (Standard_Real (*)(const gp_Parab2d &, const gp_Pnt2d &)) &ElCLib::Parameter, "parametrization In the local coordinate system of the parabola Y**2 = (2*P) * X where P is the distance between the focus and the directrix.", py::arg("Prb"), py::arg("P"));
cls_ElCLib.def_static("LineParameter_", (Standard_Real (*)(const gp_Ax1 &, const gp_Pnt &)) &ElCLib::LineParameter, "None", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("LineParameter_", (Standard_Real (*)(const gp_Ax2d &, const gp_Pnt2d &)) &ElCLib::LineParameter, "parametrization P (U) = L.Location() + U * L.Direction()", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("CircleParameter_", (Standard_Real (*)(const gp_Ax2 &, const gp_Pnt &)) &ElCLib::CircleParameter, "None", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("CircleParameter_", (Standard_Real (*)(const gp_Ax22d &, const gp_Pnt2d &)) &ElCLib::CircleParameter, "Pos is the Axis of the Circle parametrization In the local coordinate system of the circle X (U) = Radius * Cos (U) Y (U) = Radius * Sin (U)", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("EllipseParameter_", (Standard_Real (*)(const gp_Ax2 &, const Standard_Real, const Standard_Real, const gp_Pnt &)) &ElCLib::EllipseParameter, "None", py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"));
cls_ElCLib.def_static("EllipseParameter_", (Standard_Real (*)(const gp_Ax22d &, const Standard_Real, const Standard_Real, const gp_Pnt2d &)) &ElCLib::EllipseParameter, "Pos is the Axis of the Ellipse parametrization In the local coordinate system of the Ellipse X (U) = MajorRadius * Cos (U) Y (U) = MinorRadius * Sin (U)", py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"));
cls_ElCLib.def_static("HyperbolaParameter_", (Standard_Real (*)(const gp_Ax2 &, const Standard_Real, const Standard_Real, const gp_Pnt &)) &ElCLib::HyperbolaParameter, "None", py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"));
cls_ElCLib.def_static("HyperbolaParameter_", (Standard_Real (*)(const gp_Ax22d &, const Standard_Real, const Standard_Real, const gp_Pnt2d &)) &ElCLib::HyperbolaParameter, "Pos is the Axis of the Hyperbola parametrization In the local coordinate system of the Hyperbola X (U) = MajorRadius * Ch (U) Y (U) = MinorRadius * Sh (U)", py::arg("Pos"), py::arg("MajorRadius"), py::arg("MinorRadius"), py::arg("P"));
cls_ElCLib.def_static("ParabolaParameter_", (Standard_Real (*)(const gp_Ax2 &, const gp_Pnt &)) &ElCLib::ParabolaParameter, "None", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("ParabolaParameter_", (Standard_Real (*)(const gp_Ax22d &, const gp_Pnt2d &)) &ElCLib::ParabolaParameter, "Pos is the mirror axis of the parabola parametrization In the local coordinate system of the parabola Y**2 = (2*P) * X where P is the distance between the focus and the directrix. The following functions build a 3d curve from a 2d curve at a given position defined with an Ax2.", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("To3d_", (gp_Pnt (*)(const gp_Ax2 &, const gp_Pnt2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("P"));
cls_ElCLib.def_static("To3d_", (gp_Vec (*)(const gp_Ax2 &, const gp_Vec2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("V"));
cls_ElCLib.def_static("To3d_", (gp_Dir (*)(const gp_Ax2 &, const gp_Dir2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("V"));
cls_ElCLib.def_static("To3d_", (gp_Ax1 (*)(const gp_Ax2 &, const gp_Ax2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("A"));
cls_ElCLib.def_static("To3d_", (gp_Ax2 (*)(const gp_Ax2 &, const gp_Ax22d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("A"));
cls_ElCLib.def_static("To3d_", (gp_Lin (*)(const gp_Ax2 &, const gp_Lin2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("L"));
cls_ElCLib.def_static("To3d_", (gp_Circ (*)(const gp_Ax2 &, const gp_Circ2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("C"));
cls_ElCLib.def_static("To3d_", (gp_Elips (*)(const gp_Ax2 &, const gp_Elips2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("E"));
cls_ElCLib.def_static("To3d_", (gp_Hypr (*)(const gp_Ax2 &, const gp_Hypr2d &)) &ElCLib::To3d, "None", py::arg("Pos"), py::arg("H"));
cls_ElCLib.def_static("To3d_", (gp_Parab (*)(const gp_Ax2 &, const gp_Parab2d &)) &ElCLib::To3d, "These functions build a 3D geometric entity from a 2D geometric entity. The 'X Axis' and the 'Y Axis' of the global coordinate system (i.e. 2D space) are lined up respectively with the 'X Axis' and 'Y Axis' of the 3D coordinate system, Pos.", py::arg("Pos"), py::arg("Prb"));

// Enums

}