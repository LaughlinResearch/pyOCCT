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
#include <BRepGProp_Face.hxx>
#include <BRepGProp_Domain.hxx>
#include <Standard.hxx>
#include <TopoDS_Shape.hxx>
#include <GProp_GProps.hxx>
#include <Standard_TypeDef.hxx>
#include <gp_Pln.hxx>
#include <BRepGProp_EdgeTool.hxx>
#include <BRepGProp_Cinert.hxx>
#include <BRepGProp_Sinert.hxx>
#include <BRepGProp_Vinert.hxx>
#include <BRepGProp_VinertGK.hxx>
#include <BRepGProp_UFunction.hxx>
#include <BRepGProp_TFunction.hxx>
#include <BRepGProp.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <gp_Vec.hxx>
#include <GeomAbs_Shape.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <GeomAbs_IsoType.hxx>
#include <Standard_Handle.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <NCollection_Handle.hxx>
#include <NCollection_Array1.hxx>
#include <BRepGProp_Gauss.hxx>
#include <gp_Mat.hxx>
#include <math_Vector.hxx>
#include <math_Function.hxx>
#include <GProp_ValueType.hxx>
#include <gp_XYZ.hxx>

PYBIND11_MODULE(BRepGProp, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.GProp");
py::module::import("OCCT.gp");
py::module::import("OCCT.BRepAdaptor");
py::module::import("OCCT.TopExp");
py::module::import("OCCT.GeomAbs");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.Geom2dAdaptor");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.math");

// CLASS: BREPGPROP
py::class_<BRepGProp> cls_BRepGProp(mod, "BRepGProp", "Provides global functions to compute a shape's global properties for lines, surfaces or volumes, and bring them together with the global properties already computed for a geometric system. The global properties computed for a system are : - its mass, - its center of mass, - its matrix of inertia, - its moment about an axis, - its radius of gyration about an axis, - and its principal properties of inertia such as principal axis, principal moments, principal radius of gyration.");

// Methods
// cls_BRepGProp.def_static("operator new_", (void * (*)(size_t)) &BRepGProp::operator new, "None", py::arg("theSize"));
// cls_BRepGProp.def_static("operator delete_", (void (*)(void *)) &BRepGProp::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp.def_static("LinearProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1) -> void { return BRepGProp::LinearProperties(a0, a1); });
cls_BRepGProp.def_static("LinearProperties_", (void (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Boolean)) &BRepGProp::LinearProperties, "Computes the linear global properties of the shape S, i.e. the global properties induced by each edge of the shape S, and brings them together with the global properties still retained by the framework LProps. If the current system of LProps was empty, its global properties become equal to the linear global properties of S. For this computation no linear density is attached to the edges. So, for example, the added mass corresponds to the sum of the lengths of the edges of S. The density of the composed systems, i.e. that of each component of the current system of LProps, and that of S which is considered to be equal to 1, must be coherent. Note that this coherence cannot be checked. You are advised to use a separate framework for each density, and then to bring these frameworks together into a global one. The point relative to which the inertia of the system is computed is the reference point of the framework LProps. Note: if your programming ensures that the framework LProps retains only linear global properties (brought together for example, by the function LinearProperties) for objects the density of which is equal to 1 (or is not defined), the function Mass will return the total length of edges of the system analysed by LProps. Warning No check is performed to verify that the shape S retains truly linear properties. If S is simply a vertex, it is not considered to present any additional global properties. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, edges, shared by two or more faces, are taken into calculation only once. If we have cube with sizes 1, 1, 1, its linear properties = 12 for SkipEdges = true and 24 for SkipEdges = false.", py::arg("S"), py::arg("LProps"), py::arg("SkipShared"));
cls_BRepGProp.def_static("SurfaceProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1) -> void { return BRepGProp::SurfaceProperties(a0, a1); });
cls_BRepGProp.def_static("SurfaceProperties_", (void (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Boolean)) &BRepGProp::SurfaceProperties, "Computes the surface global properties of the shape S, i.e. the global properties induced by each face of the shape S, and brings them together with the global properties still retained by the framework SProps. If the current system of SProps was empty, its global properties become equal to the surface global properties of S. For this computation, no surface density is attached to the faces. Consequently, the added mass corresponds to the sum of the areas of the faces of S. The density of the component systems, i.e. that of each component of the current system of SProps, and that of S which is considered to be equal to 1, must be coherent. Note that this coherence cannot be checked. You are advised to use a framework for each different value of density, and then to bring these frameworks together into a global one. The point relative to which the inertia of the system is computed is the reference point of the framework SProps. Note : if your programming ensures that the framework SProps retains only surface global properties, brought together, for example, by the function SurfaceProperties, for objects the density of which is equal to 1 (or is not defined), the function Mass will return the total area of faces of the system analysed by SProps. Warning No check is performed to verify that the shape S retains truly surface properties. If S is simply a vertex, an edge or a wire, it is not considered to present any additional global properties. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, faces, shared by two or more shells, are taken into calculation only once.", py::arg("S"), py::arg("SProps"), py::arg("SkipShared"));
cls_BRepGProp.def_static("SurfaceProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2) -> Standard_Real { return BRepGProp::SurfaceProperties(a0, a1, a2); });
cls_BRepGProp.def_static("SurfaceProperties_", (Standard_Real (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Real, const Standard_Boolean)) &BRepGProp::SurfaceProperties, "Updates <SProps> with the shape <S>, that contains its pricipal properties. The surface properties of all the faces in <S> are computed. Adaptive 2D Gauss integration is used. Parameter Eps sets maximal relative error of computed mass (area) for each face. Error is calculated as Abs((M(i+1)-M(i))/M(i+1)), M(i+1) and M(i) are values for two successive steps of adaptive integration. Method returns estimation of relative error reached for whole shape. WARNING: if Eps > 0.001 algorithm performs non-adaptive integration. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, faces, shared by two or more shells, are taken into calculation only once.", py::arg("S"), py::arg("SProps"), py::arg("Eps"), py::arg("SkipShared"));
cls_BRepGProp.def_static("VolumeProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1) -> void { return BRepGProp::VolumeProperties(a0, a1); });
cls_BRepGProp.def_static("VolumeProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Boolean a2) -> void { return BRepGProp::VolumeProperties(a0, a1, a2); });
cls_BRepGProp.def_static("VolumeProperties_", (void (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Boolean, const Standard_Boolean)) &BRepGProp::VolumeProperties, "Computes the global volume properties of the solid S, and brings them together with the global properties still retained by the framework VProps. If the current system of VProps was empty, its global properties become equal to the global properties of S for volume. For this computation, no volume density is attached to the solid. Consequently, the added mass corresponds to the volume of S. The density of the component systems, i.e. that of each component of the current system of VProps, and that of S which is considered to be equal to 1, must be coherent to each other. Note that this coherence cannot be checked. You are advised to use a separate framework for each density, and then to bring these frameworks together into a global one. The point relative to which the inertia of the system is computed is the reference point of the framework VProps. Note: if your programming ensures that the framework VProps retains only global properties of volume (brought together for example, by the function VolumeProperties) for objects the density of which is equal to 1 (or is not defined), the function Mass will return the total volume of the solids of the system analysed by VProps. Warning The shape S must represent an object whose global volume properties can be computed. It may be a finite solid, or a series of finite solids all oriented in a coherent way. Nonetheless, S must be exempt of any free boundary. Note that these conditions of coherence are not checked by this algorithm, and results will be false if they are not respected. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, the volumes formed by the equal (the same TShape, location and orientation) faces are taken into calculation only once.", py::arg("S"), py::arg("VProps"), py::arg("OnlyClosed"), py::arg("SkipShared"));
cls_BRepGProp.def_static("VolumeProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2) -> Standard_Real { return BRepGProp::VolumeProperties(a0, a1, a2); });
cls_BRepGProp.def_static("VolumeProperties_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2, const Standard_Boolean a3) -> Standard_Real { return BRepGProp::VolumeProperties(a0, a1, a2, a3); });
cls_BRepGProp.def_static("VolumeProperties_", (Standard_Real (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp::VolumeProperties, "Updates <VProps> with the shape <S>, that contains its pricipal properties. The volume properties of all the FORWARD and REVERSED faces in <S> are computed. If OnlyClosed is True then computed faces must belong to closed Shells. Adaptive 2D Gauss integration is used. Parameter Eps sets maximal relative error of computed mass (volume) for each face. Error is calculated as Abs((M(i+1)-M(i))/M(i+1)), M(i+1) and M(i) are values for two successive steps of adaptive integration. Method returns estimation of relative error reached for whole shape. WARNING: if Eps > 0.001 algorithm performs non-adaptive integration. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, the volumes formed by the equal (the same TShape, location and orientation) faces are taken into calculation only once.", py::arg("S"), py::arg("VProps"), py::arg("Eps"), py::arg("OnlyClosed"), py::arg("SkipShared"));
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2, const Standard_Boolean a3) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2, const Standard_Boolean a3, const Standard_Boolean a4) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2, const Standard_Boolean a3, const Standard_Boolean a4, const Standard_Boolean a5) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4, a5); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const Standard_Real a2, const Standard_Boolean a3, const Standard_Boolean a4, const Standard_Boolean a5, const Standard_Boolean a6) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4, a5, a6); });
cls_BRepGProp.def_static("VolumePropertiesGK_", (Standard_Real (*)(const TopoDS_Shape &, GProp_GProps &, const Standard_Real, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean)) &BRepGProp::VolumePropertiesGK, "Updates <VProps> with the shape <S>, that contains its pricipal properties. The volume properties of all the FORWARD and REVERSED faces in <S> are computed. If OnlyClosed is True then computed faces must belong to closed Shells. Adaptive 2D Gauss integration is used. Parameter IsUseSpan says if it is necessary to define spans on a face. This option has an effect only for BSpline faces. Parameter Eps sets maximal relative error of computed property for each face. Error is delivered by the adaptive Gauss-Kronrod method of integral computation that is used for properties computation. Method returns estimation of relative error reached for whole shape. Returns negative value if the computation is failed. SkipShared is special flag, which allows to take in calculation shared topological entities or not For ex., if SkipShared = True, the volumes formed by the equal (the same TShape, location and orientation) faces are taken into calculation only once.", py::arg("S"), py::arg("VProps"), py::arg("Eps"), py::arg("OnlyClosed"), py::arg("IsUseSpan"), py::arg("CGFlag"), py::arg("IFlag"), py::arg("SkipShared"));
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2, const Standard_Real a3) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2, const Standard_Real a3, const Standard_Boolean a4) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2, const Standard_Real a3, const Standard_Boolean a4, const Standard_Boolean a5) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4, a5); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2, const Standard_Real a3, const Standard_Boolean a4, const Standard_Boolean a5, const Standard_Boolean a6) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4, a5, a6); });
cls_BRepGProp.def_static("VolumePropertiesGK_", [](const TopoDS_Shape & a0, GProp_GProps & a1, const gp_Pln & a2, const Standard_Real a3, const Standard_Boolean a4, const Standard_Boolean a5, const Standard_Boolean a6, const Standard_Boolean a7) -> Standard_Real { return BRepGProp::VolumePropertiesGK(a0, a1, a2, a3, a4, a5, a6, a7); });
cls_BRepGProp.def_static("VolumePropertiesGK_", (Standard_Real (*)(const TopoDS_Shape &, GProp_GProps &, const gp_Pln &, const Standard_Real, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean)) &BRepGProp::VolumePropertiesGK, "None", py::arg("S"), py::arg("VProps"), py::arg("thePln"), py::arg("Eps"), py::arg("OnlyClosed"), py::arg("IsUseSpan"), py::arg("CGFlag"), py::arg("IFlag"), py::arg("SkipShared"));

// CLASS: BREPGPROP_CINERT
py::class_<BRepGProp_Cinert, GProp_GProps> cls_BRepGProp_Cinert(mod, "BRepGProp_Cinert", "Computes the global properties of bounded curves in 3D space. The curve must have at least a continuity C1. It can be a curve as defined in the template CurveTool from package GProp. This template gives the minimum of methods required to evaluate the global properties of a curve 3D with the algorithmes of GProp.");

// Constructors
cls_BRepGProp_Cinert.def(py::init<>());
cls_BRepGProp_Cinert.def(py::init<const BRepAdaptor_Curve &, const gp_Pnt &>(), py::arg("C"), py::arg("CLocation"));

// Methods
// cls_BRepGProp_Cinert.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_Cinert::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_Cinert.def_static("operator delete_", (void (*)(void *)) &BRepGProp_Cinert::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_Cinert.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_Cinert::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_Cinert.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_Cinert::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_Cinert.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_Cinert::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_Cinert.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_Cinert::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_Cinert.def("SetLocation", (void (BRepGProp_Cinert::*)(const gp_Pnt &)) &BRepGProp_Cinert::SetLocation, "None", py::arg("CLocation"));
cls_BRepGProp_Cinert.def("Perform", (void (BRepGProp_Cinert::*)(const BRepAdaptor_Curve &)) &BRepGProp_Cinert::Perform, "None", py::arg("C"));

// CLASS: BREPGPROP_DOMAIN
py::class_<BRepGProp_Domain> cls_BRepGProp_Domain(mod, "BRepGProp_Domain", "Arc iterator. Returns only Forward and Reversed edges from the face in an undigested order.");

// Constructors
cls_BRepGProp_Domain.def(py::init<>());
cls_BRepGProp_Domain.def(py::init<const TopoDS_Face &>(), py::arg("F"));

// Methods
// cls_BRepGProp_Domain.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_Domain::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_Domain.def_static("operator delete_", (void (*)(void *)) &BRepGProp_Domain::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_Domain.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_Domain::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_Domain.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_Domain::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_Domain.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_Domain::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_Domain.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_Domain::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_Domain.def("Init", (void (BRepGProp_Domain::*)(const TopoDS_Face &)) &BRepGProp_Domain::Init, "Initializes the domain with the face.", py::arg("F"));
cls_BRepGProp_Domain.def("More", (Standard_Boolean (BRepGProp_Domain::*)()) &BRepGProp_Domain::More, "Returns True if there is another arc of curve in the list.");
cls_BRepGProp_Domain.def("Init", (void (BRepGProp_Domain::*)()) &BRepGProp_Domain::Init, "Initializes the exploration with the face already set.");
cls_BRepGProp_Domain.def("Value", (const TopoDS_Edge & (BRepGProp_Domain::*)()) &BRepGProp_Domain::Value, "Returns the current edge.");
cls_BRepGProp_Domain.def("Next", (void (BRepGProp_Domain::*)()) &BRepGProp_Domain::Next, "Sets the index of the arc iterator to the next arc of curve.");

// CLASS: BREPGPROP_EDGETOOL
py::class_<BRepGProp_EdgeTool> cls_BRepGProp_EdgeTool(mod, "BRepGProp_EdgeTool", "Provides the required methods to instantiate CGProps from GProp with a Curve from BRepAdaptor.");

// Methods
// cls_BRepGProp_EdgeTool.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_EdgeTool::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_EdgeTool.def_static("operator delete_", (void (*)(void *)) &BRepGProp_EdgeTool::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_EdgeTool.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_EdgeTool::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_EdgeTool.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_EdgeTool::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_EdgeTool.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_EdgeTool::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_EdgeTool.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_EdgeTool::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_EdgeTool.def_static("FirstParameter_", (Standard_Real (*)(const BRepAdaptor_Curve &)) &BRepGProp_EdgeTool::FirstParameter, "Returns the parametric value of the start point of the curve. The curve is oriented from the start point to the end point.", py::arg("C"));
cls_BRepGProp_EdgeTool.def_static("LastParameter_", (Standard_Real (*)(const BRepAdaptor_Curve &)) &BRepGProp_EdgeTool::LastParameter, "Returns the parametric value of the end point of the curve. The curve is oriented from the start point to the end point.", py::arg("C"));
cls_BRepGProp_EdgeTool.def_static("IntegrationOrder_", (Standard_Integer (*)(const BRepAdaptor_Curve &)) &BRepGProp_EdgeTool::IntegrationOrder, "Returns the number of Gauss points required to do the integration with a good accuracy using the Gauss method. For a polynomial curve of degree n the maxima of accuracy is obtained with an order of integration equal to 2*n-1.", py::arg("C"));
cls_BRepGProp_EdgeTool.def_static("Value_", (gp_Pnt (*)(const BRepAdaptor_Curve &, const Standard_Real)) &BRepGProp_EdgeTool::Value, "Returns the point of parameter U on the loaded curve.", py::arg("C"), py::arg("U"));
cls_BRepGProp_EdgeTool.def_static("D1_", (void (*)(const BRepAdaptor_Curve &, const Standard_Real, gp_Pnt &, gp_Vec &)) &BRepGProp_EdgeTool::D1, "Returns the point of parameter U and the first derivative at this point.", py::arg("C"), py::arg("U"), py::arg("P"), py::arg("V1"));
cls_BRepGProp_EdgeTool.def_static("NbIntervals_", (Standard_Integer (*)(const BRepAdaptor_Curve &, const GeomAbs_Shape)) &BRepGProp_EdgeTool::NbIntervals, "Returns the number of intervals for continuity <S>. May be one if Continuity(me) >= <S>", py::arg("C"), py::arg("S"));
cls_BRepGProp_EdgeTool.def_static("Intervals_", (void (*)(const BRepAdaptor_Curve &, TColStd_Array1OfReal &, const GeomAbs_Shape)) &BRepGProp_EdgeTool::Intervals, "Stores in <T> the parameters bounding the intervals of continuity <S>.", py::arg("C"), py::arg("T"), py::arg("S"));

// CLASS: BREPGPROP_FACE
py::class_<BRepGProp_Face> cls_BRepGProp_Face(mod, "BRepGProp_Face", "None");

// Constructors
cls_BRepGProp_Face.def(py::init<>());
cls_BRepGProp_Face.def(py::init<const Standard_Boolean>(), py::arg("IsUseSpan"));
cls_BRepGProp_Face.def(py::init<const TopoDS_Face &>(), py::arg("F"));
cls_BRepGProp_Face.def(py::init<const TopoDS_Face &, const Standard_Boolean>(), py::arg("F"), py::arg("IsUseSpan"));

// Methods
// cls_BRepGProp_Face.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_Face::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_Face.def_static("operator delete_", (void (*)(void *)) &BRepGProp_Face::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_Face.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_Face::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_Face.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_Face::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_Face.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_Face::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_Face.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_Face::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_Face.def("Load", (void (BRepGProp_Face::*)(const TopoDS_Face &)) &BRepGProp_Face::Load, "None", py::arg("F"));
cls_BRepGProp_Face.def("VIntegrationOrder", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::VIntegrationOrder, "None");
cls_BRepGProp_Face.def("NaturalRestriction", (Standard_Boolean (BRepGProp_Face::*)() const) &BRepGProp_Face::NaturalRestriction, "Returns Standard_True if the face is not trimmed.");
cls_BRepGProp_Face.def("GetFace", (const TopoDS_Face & (BRepGProp_Face::*)() const) &BRepGProp_Face::GetFace, "Returns the TopoDS face.");
cls_BRepGProp_Face.def("Value2d", (gp_Pnt2d (BRepGProp_Face::*)(const Standard_Real) const) &BRepGProp_Face::Value2d, "Returns the value of the boundary curve of the face.", py::arg("U"));
cls_BRepGProp_Face.def("SIntOrder", (Standard_Integer (BRepGProp_Face::*)(const Standard_Real) const) &BRepGProp_Face::SIntOrder, "None", py::arg("Eps"));
cls_BRepGProp_Face.def("SVIntSubs", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::SVIntSubs, "None");
cls_BRepGProp_Face.def("SUIntSubs", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::SUIntSubs, "None");
cls_BRepGProp_Face.def("UKnots", (void (BRepGProp_Face::*)(TColStd_Array1OfReal &) const) &BRepGProp_Face::UKnots, "None", py::arg("Knots"));
cls_BRepGProp_Face.def("VKnots", (void (BRepGProp_Face::*)(TColStd_Array1OfReal &) const) &BRepGProp_Face::VKnots, "None", py::arg("Knots"));
cls_BRepGProp_Face.def("LIntOrder", (Standard_Integer (BRepGProp_Face::*)(const Standard_Real) const) &BRepGProp_Face::LIntOrder, "None", py::arg("Eps"));
cls_BRepGProp_Face.def("LIntSubs", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::LIntSubs, "None");
cls_BRepGProp_Face.def("LKnots", (void (BRepGProp_Face::*)(TColStd_Array1OfReal &) const) &BRepGProp_Face::LKnots, "None", py::arg("Knots"));
cls_BRepGProp_Face.def("UIntegrationOrder", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::UIntegrationOrder, "Returns the number of points required to do the integration in the U parametric direction with a good accuracy.");
cls_BRepGProp_Face.def("Bounds", [](BRepGProp_Face &self, Standard_Real & U1, Standard_Real & U2, Standard_Real & V1, Standard_Real & V2){ self.Bounds(U1, U2, V1, V2); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(U1, U2, V1, V2); }, "Returns the parametric bounds of the Face.", py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_BRepGProp_Face.def("Normal", (void (BRepGProp_Face::*)(const Standard_Real, const Standard_Real, gp_Pnt &, gp_Vec &) const) &BRepGProp_Face::Normal, "Computes the point of parameter U, V on the Face <S> and the normal to the face at this point.", py::arg("U"), py::arg("V"), py::arg("P"), py::arg("VNor"));
cls_BRepGProp_Face.def("Load", (void (BRepGProp_Face::*)(const TopoDS_Edge &)) &BRepGProp_Face::Load, "Loading the boundary arc.", py::arg("E"));
cls_BRepGProp_Face.def("FirstParameter", (Standard_Real (BRepGProp_Face::*)() const) &BRepGProp_Face::FirstParameter, "Returns the parametric value of the start point of the current arc of curve.");
cls_BRepGProp_Face.def("LastParameter", (Standard_Real (BRepGProp_Face::*)() const) &BRepGProp_Face::LastParameter, "Returns the parametric value of the end point of the current arc of curve.");
cls_BRepGProp_Face.def("IntegrationOrder", (Standard_Integer (BRepGProp_Face::*)() const) &BRepGProp_Face::IntegrationOrder, "Returns the number of points required to do the integration along the parameter of curve.");
cls_BRepGProp_Face.def("D12d", (void (BRepGProp_Face::*)(const Standard_Real, gp_Pnt2d &, gp_Vec2d &) const) &BRepGProp_Face::D12d, "Returns the point of parameter U and the first derivative at this point of a boundary curve.", py::arg("U"), py::arg("P"), py::arg("V1"));
cls_BRepGProp_Face.def("Load", (void (BRepGProp_Face::*)(const Standard_Boolean, const GeomAbs_IsoType)) &BRepGProp_Face::Load, "Loading the boundary arc. This arc is either a top, bottom, left or right bound of a UV rectangle in which the parameters of surface are defined. If IsFirstParam is equal to Standard_True, the face is initialized by either left of bottom bound. Otherwise it is initialized by the top or right one. If theIsoType is equal to GeomAbs_IsoU, the face is initialized with either left or right bound. Otherwise - with either top or bottom one.", py::arg("IsFirstParam"), py::arg("theIsoType"));
cls_BRepGProp_Face.def("GetUKnots", (void (BRepGProp_Face::*)(const Standard_Real, const Standard_Real, opencascade::handle<TColStd_HArray1OfReal> &) const) &BRepGProp_Face::GetUKnots, "Returns an array of U knots of the face. The first and last elements of the array will be theUMin and theUMax. The middle elements will be the U Knots of the face greater then theUMin and lower then theUMax in increasing order. If the face is not a BSpline, the array initialized with theUMin and theUMax only.", py::arg("theUMin"), py::arg("theUMax"), py::arg("theUKnots"));
cls_BRepGProp_Face.def("GetTKnots", (void (BRepGProp_Face::*)(const Standard_Real, const Standard_Real, opencascade::handle<TColStd_HArray1OfReal> &) const) &BRepGProp_Face::GetTKnots, "Returns an array of combination of T knots of the arc and V knots of the face. The first and last elements of the array will be theTMin and theTMax. The middle elements will be the Knots of the arc and the values of parameters of arc on which the value points have V coordinates close to V knots of face. All the parameter will be greater then theTMin and lower then theTMax in increasing order. If the face is not a BSpline, the array initialized with theTMin and theTMax only.", py::arg("theTMin"), py::arg("theTMax"), py::arg("theTKnots"));

// CLASS: BREPGPROP_GAUSS
py::class_<BRepGProp_Gauss> cls_BRepGProp_Gauss(mod, "BRepGProp_Gauss", "Class performs computing of the global inertia properties of geometric object in 3D space by adaptive and non-adaptive 2D Gauss integration algorithms.");

// Constructors
cls_BRepGProp_Gauss.def(py::init<const BRepGProp_Gauss::BRepGProp_GaussType>(), py::arg("theType"));

// Methods
// cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, const BRepGProp_Face & theSurface, const gp_Pnt & theLocation, const Standard_Real [] theCoeff, const Standard_Boolean theIsByPoint, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ self.Compute(theSurface, theLocation, theCoeff, theIsByPoint, theOutMass, theOutGravityCenter, theOutInertia); return theOutMass; }, "Computes the global properties of a solid region of 3D space which can be delimited by the surface and point or surface and plane. Surface can be closed. The method is quick and its precision is enough for many cases of analytical surfaces. Non-adaptive 2D Gauss integration with predefined numbers of Gauss points is used. Numbers of points depend on types of surfaces and curves. Error of the computation is not calculated.", py::arg("theSurface"), py::arg("theLocation"), py::arg("theCoeff"), py::arg("theIsByPoint"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));
cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, const BRepGProp_Face & theSurface, const gp_Pnt & theLocation, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ self.Compute(theSurface, theLocation, theOutMass, theOutGravityCenter, theOutInertia); return theOutMass; }, "Computes the global properties of a surface. Surface can be closed. The method is quick and its precision is enough for many cases of analytical surfaces. Non-adaptive 2D Gauss integration with predefined numbers of Gauss points is used. Numbers of points depend on types of surfaces and curves. Error of the computation is not calculated.", py::arg("theSurface"), py::arg("theLocation"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));
// cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, BRepGProp_Face & theSurface, BRepGProp_Domain & theDomain, const gp_Pnt & theLocation, const Standard_Real [] theCoeff, const Standard_Boolean theIsByPoint, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ self.Compute(theSurface, theDomain, theLocation, theCoeff, theIsByPoint, theOutMass, theOutGravityCenter, theOutInertia); return theOutMass; }, "Computes the global properties of a region of 3D space which can be delimited by the surface and point or surface and plane. Surface can be closed. The method is quick and its precision is enough for many cases of analytical surfaces. Non-adaptive 2D Gauss integration with predefined numbers of Gauss points is used. Numbers of points depend on types of surfaces and curves. Error of the computation is not calculated.", py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theCoeff"), py::arg("theIsByPoint"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));
cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, BRepGProp_Face & theSurface, BRepGProp_Domain & theDomain, const gp_Pnt & theLocation, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ self.Compute(theSurface, theDomain, theLocation, theOutMass, theOutGravityCenter, theOutInertia); return theOutMass; }, "Computes the global properties of a surface. Surface can be closed. The method is quick and its precision is enough for many cases of analytical surfaces. Non-adaptive 2D Gauss integration with predefined numbers of Gauss points is used. Numbers of points depend on types of surfaces and curves. Error of the computation is not calculated.", py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));
// cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, BRepGProp_Face & theSurface, BRepGProp_Domain & theDomain, const gp_Pnt & theLocation, const Standard_Real theEps, const Standard_Real [] theCoeff, const Standard_Boolean theByPoint, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ Standard_Real rv = self.Compute(theSurface, theDomain, theLocation, theEps, theCoeff, theByPoint, theOutMass, theOutGravityCenter, theOutInertia); return std::tuple<Standard_Real, Standard_Real &>(rv, theOutMass); }, "Computes the global properties of the region of 3D space which can be delimited by the surface and point or surface and plane. Adaptive 2D Gauss integration is used. If Epsilon more than 0.001 then algorithm performs non-adaptive integration.", py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theEps"), py::arg("theCoeff"), py::arg("theByPoint"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));
cls_BRepGProp_Gauss.def("Compute", [](BRepGProp_Gauss &self, BRepGProp_Face & theSurface, BRepGProp_Domain & theDomain, const gp_Pnt & theLocation, const Standard_Real theEps, Standard_Real & theOutMass, gp_Pnt & theOutGravityCenter, gp_Mat & theOutInertia){ Standard_Real rv = self.Compute(theSurface, theDomain, theLocation, theEps, theOutMass, theOutGravityCenter, theOutInertia); return std::tuple<Standard_Real, Standard_Real &>(rv, theOutMass); }, "Computes the global properties of the face. Adaptive 2D Gauss integration is used. If Epsilon more than 0.001 then algorithm performs non-adaptive integration.", py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theEps"), py::arg("theOutMass"), py::arg("theOutGravityCenter"), py::arg("theOutInertia"));

// Enums
py::enum_<BRepGProp_Gauss::BRepGProp_GaussType>(cls_BRepGProp_Gauss, "BRepGProp_Gauss_BRepGProp_GaussType", "Describes types of geometric objects. - Vinert is 3D closed region of space delimited with: -- Surface; -- Point and Surface; -- Plane and Surface. - Sinert is face in 3D space.")
	.value("Vinert", BRepGProp_Gauss::BRepGProp_GaussType::Vinert)
	.value("Sinert", BRepGProp_Gauss::BRepGProp_GaussType::Sinert)
	.export_values();

// CLASS: BREPGPROP_SINERT
py::class_<BRepGProp_Sinert, GProp_GProps> cls_BRepGProp_Sinert(mod, "BRepGProp_Sinert", "Computes the global properties of a face in 3D space. The face 's requirements to evaluate the global properties are defined in the template FaceTool from package GProp.");

// Constructors
cls_BRepGProp_Sinert.def(py::init<>());
cls_BRepGProp_Sinert.def(py::init<const BRepGProp_Face &, const gp_Pnt &>(), py::arg("S"), py::arg("SLocation"));
cls_BRepGProp_Sinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &>(), py::arg("S"), py::arg("D"), py::arg("SLocation"));
cls_BRepGProp_Sinert.def(py::init<BRepGProp_Face &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("SLocation"), py::arg("Eps"));
cls_BRepGProp_Sinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("D"), py::arg("SLocation"), py::arg("Eps"));

// Methods
// cls_BRepGProp_Sinert.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_Sinert::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_Sinert.def_static("operator delete_", (void (*)(void *)) &BRepGProp_Sinert::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_Sinert.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_Sinert::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_Sinert.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_Sinert::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_Sinert.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_Sinert::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_Sinert.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_Sinert::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_Sinert.def("SetLocation", (void (BRepGProp_Sinert::*)(const gp_Pnt &)) &BRepGProp_Sinert::SetLocation, "None", py::arg("SLocation"));
cls_BRepGProp_Sinert.def("Perform", (void (BRepGProp_Sinert::*)(const BRepGProp_Face &)) &BRepGProp_Sinert::Perform, "None", py::arg("S"));
cls_BRepGProp_Sinert.def("Perform", (void (BRepGProp_Sinert::*)(BRepGProp_Face &, BRepGProp_Domain &)) &BRepGProp_Sinert::Perform, "None", py::arg("S"), py::arg("D"));
cls_BRepGProp_Sinert.def("Perform", (Standard_Real (BRepGProp_Sinert::*)(BRepGProp_Face &, const Standard_Real)) &BRepGProp_Sinert::Perform, "None", py::arg("S"), py::arg("Eps"));
cls_BRepGProp_Sinert.def("Perform", (Standard_Real (BRepGProp_Sinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const Standard_Real)) &BRepGProp_Sinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("Eps"));
cls_BRepGProp_Sinert.def("GetEpsilon", (Standard_Real (BRepGProp_Sinert::*)()) &BRepGProp_Sinert::GetEpsilon, "If previously used method contained Eps parameter get actual relative error of the computation, else return 1.0.");

// CLASS: BREPGPROP_UFUNCTION
py::class_<BRepGProp_UFunction, math_Function> cls_BRepGProp_UFunction(mod, "BRepGProp_UFunction", "This class represents the integrand function for computation of an inner integral. The returned value depends on the value type and the flag IsByPoint.");

// Constructors
cls_BRepGProp_UFunction.def(py::init<const BRepGProp_Face &, const gp_Pnt &, const Standard_Boolean, const Standard_Address>(), py::arg("theSurface"), py::arg("theVertex"), py::arg("IsByPoint"), py::arg("theCoeffs"));

// Methods
// cls_BRepGProp_UFunction.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_UFunction::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_UFunction.def_static("operator delete_", (void (*)(void *)) &BRepGProp_UFunction::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_UFunction.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_UFunction::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_UFunction.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_UFunction::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_UFunction.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_UFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_UFunction.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_UFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_UFunction.def("SetValueType", (void (BRepGProp_UFunction::*)(const GProp_ValueType)) &BRepGProp_UFunction::SetValueType, "Setting the type of the value to be returned.", py::arg("theType"));
cls_BRepGProp_UFunction.def("SetVParam", (void (BRepGProp_UFunction::*)(const Standard_Real)) &BRepGProp_UFunction::SetVParam, "Setting the V parameter that is constant during the integral computation.", py::arg("theVParam"));
cls_BRepGProp_UFunction.def("Value", [](BRepGProp_UFunction &self, const Standard_Real X, Standard_Real & F){ Standard_Boolean rv = self.Value(X, F); return std::tuple<Standard_Boolean, Standard_Real &>(rv, F); }, "Returns a value of the function.", py::arg("X"), py::arg("F"));

// CLASS: BREPGPROP_TFUNCTION
py::class_<BRepGProp_TFunction, math_Function> cls_BRepGProp_TFunction(mod, "BRepGProp_TFunction", "This class represents the integrand function for the outer integral computation. The returned value represents the integral of UFunction. It depends on the value type and the flag IsByPoint.");

// Constructors
cls_BRepGProp_TFunction.def(py::init<const BRepGProp_Face &, const gp_Pnt &, const Standard_Boolean, const Standard_Address, const Standard_Real, const Standard_Real>(), py::arg("theSurface"), py::arg("theVertex"), py::arg("IsByPoint"), py::arg("theCoeffs"), py::arg("theUMin"), py::arg("theTolerance"));

// Methods
// cls_BRepGProp_TFunction.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_TFunction::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_TFunction.def_static("operator delete_", (void (*)(void *)) &BRepGProp_TFunction::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_TFunction.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_TFunction::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_TFunction.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_TFunction::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_TFunction.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_TFunction::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_TFunction.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_TFunction::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_TFunction.def("Init", (void (BRepGProp_TFunction::*)()) &BRepGProp_TFunction::Init, "None");
cls_BRepGProp_TFunction.def("SetNbKronrodPoints", (void (BRepGProp_TFunction::*)(const Standard_Integer)) &BRepGProp_TFunction::SetNbKronrodPoints, "Setting the expected number of Kronrod points for the outer integral computation. This number is required for computation of a value of tolerance for inner integral computation. After GetStateNumber method call, this number is recomputed by the same law as in math_KronrodSingleIntegration, i.e. next number of points is equal to the current number plus a square root of the current number. If the law in math_KronrodSingleIntegration is changed, the modification algo should be modified accordingly.", py::arg("theNbPoints"));
cls_BRepGProp_TFunction.def("SetValueType", (void (BRepGProp_TFunction::*)(const GProp_ValueType)) &BRepGProp_TFunction::SetValueType, "Setting the type of the value to be returned. This parameter is directly passed to the UFunction.", py::arg("aType"));
cls_BRepGProp_TFunction.def("SetTolerance", (void (BRepGProp_TFunction::*)(const Standard_Real)) &BRepGProp_TFunction::SetTolerance, "Setting the tolerance for inner integration", py::arg("aTol"));
cls_BRepGProp_TFunction.def("ErrorReached", (Standard_Real (BRepGProp_TFunction::*)() const) &BRepGProp_TFunction::ErrorReached, "Returns the relative reached error of all values computation since the last call of GetStateNumber method.");
cls_BRepGProp_TFunction.def("AbsolutError", (Standard_Real (BRepGProp_TFunction::*)() const) &BRepGProp_TFunction::AbsolutError, "Returns the absolut reached error of all values computation since the last call of GetStateNumber method.");
cls_BRepGProp_TFunction.def("Value", [](BRepGProp_TFunction &self, const Standard_Real X, Standard_Real & F){ Standard_Boolean rv = self.Value(X, F); return std::tuple<Standard_Boolean, Standard_Real &>(rv, F); }, "Returns a value of the function. The value represents an integral of UFunction. It is computed with the predefined tolerance using the adaptive Gauss-Kronrod method.", py::arg("X"), py::arg("F"));
cls_BRepGProp_TFunction.def("GetStateNumber", (Standard_Integer (BRepGProp_TFunction::*)()) &BRepGProp_TFunction::GetStateNumber, "Redefined method. Remembers the error reached during computation of integral values since the object creation or the last call of GetStateNumber. It is invoked in each algorithm from the package math. Particularly in the algorithm math_KronrodSingleIntegration that is used to compute the integral of TFunction.");

// CLASS: BREPGPROP_VINERT
py::class_<BRepGProp_Vinert, GProp_GProps> cls_BRepGProp_Vinert(mod, "BRepGProp_Vinert", "Computes the global properties of a geometric solid (3D closed region of space) delimited with : . a surface . a point and a surface . a plane and a surface");

// Constructors
cls_BRepGProp_Vinert.def(py::init<>());
cls_BRepGProp_Vinert.def(py::init<const BRepGProp_Face &, const gp_Pnt &>(), py::arg("S"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("VLocation"), py::arg("Eps"));
cls_BRepGProp_Vinert.def(py::init<const BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &>(), py::arg("S"), py::arg("O"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("O"), py::arg("VLocation"), py::arg("Eps"));
cls_BRepGProp_Vinert.def(py::init<const BRepGProp_Face &, const gp_Pln &, const gp_Pnt &>(), py::arg("S"), py::arg("Pl"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, const gp_Pln &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("Pl"), py::arg("VLocation"), py::arg("Eps"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &>(), py::arg("S"), py::arg("D"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("D"), py::arg("VLocation"), py::arg("Eps"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &>(), py::arg("S"), py::arg("D"), py::arg("O"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("D"), py::arg("O"), py::arg("VLocation"), py::arg("Eps"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &>(), py::arg("S"), py::arg("D"), py::arg("Pl"), py::arg("VLocation"));
cls_BRepGProp_Vinert.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &, const Standard_Real>(), py::arg("S"), py::arg("D"), py::arg("Pl"), py::arg("VLocation"), py::arg("Eps"));

// Methods
// cls_BRepGProp_Vinert.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_Vinert::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_Vinert.def_static("operator delete_", (void (*)(void *)) &BRepGProp_Vinert::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_Vinert.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_Vinert::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_Vinert.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_Vinert::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_Vinert.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_Vinert::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_Vinert.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_Vinert::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_Vinert.def("SetLocation", (void (BRepGProp_Vinert::*)(const gp_Pnt &)) &BRepGProp_Vinert::SetLocation, "None", py::arg("VLocation"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(const BRepGProp_Face &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(const BRepGProp_Face &, const gp_Pnt &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("O"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, const gp_Pnt &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("O"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(const BRepGProp_Face &, const gp_Pln &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("Pl"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, const gp_Pln &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("Pl"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("O"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("O"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("Perform", (void (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("Pl"));
cls_BRepGProp_Vinert.def("Perform", (Standard_Real (BRepGProp_Vinert::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const Standard_Real)) &BRepGProp_Vinert::Perform, "None", py::arg("S"), py::arg("D"), py::arg("Pl"), py::arg("Eps"));
cls_BRepGProp_Vinert.def("GetEpsilon", (Standard_Real (BRepGProp_Vinert::*)()) &BRepGProp_Vinert::GetEpsilon, "If previously used methods containe Eps parameter gets actual relative error of the computation, else returns 1.0.");

// CLASS: BREPGPROP_VINERTGK
py::class_<BRepGProp_VinertGK, GProp_GProps> cls_BRepGProp_VinertGK(mod, "BRepGProp_VinertGK", "Computes the global properties of a geometric solid (3D closed region of space) delimited with : - a point and a surface - a plane and a surface");

// Constructors
cls_BRepGProp_VinertGK.def(py::init<>());
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("thePoint"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePoint"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePoint"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pln &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("thePlane"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pln &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pln &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, const gp_Pln &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePlane"), py::arg("theLocation"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &, const Standard_Real>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &, const Standard_Real, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"));
cls_BRepGProp_VinertGK.def(py::init<BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("theSurface"), py::arg("theDomain"), py::arg("thePlane"), py::arg("theLocation"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));

// Methods
// cls_BRepGProp_VinertGK.def_static("operator new_", (void * (*)(size_t)) &BRepGProp_VinertGK::operator new, "None", py::arg("theSize"));
// cls_BRepGProp_VinertGK.def_static("operator delete_", (void (*)(void *)) &BRepGProp_VinertGK::operator delete, "None", py::arg("theAddress"));
// cls_BRepGProp_VinertGK.def_static("operator new[]_", (void * (*)(size_t)) &BRepGProp_VinertGK::operator new[], "None", py::arg("theSize"));
// cls_BRepGProp_VinertGK.def_static("operator delete[]_", (void (*)(void *)) &BRepGProp_VinertGK::operator delete[], "None", py::arg("theAddress"));
// cls_BRepGProp_VinertGK.def_static("operator new_", (void * (*)(size_t, void *)) &BRepGProp_VinertGK::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepGProp_VinertGK.def_static("operator delete_", (void (*)(void *, void *)) &BRepGProp_VinertGK::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepGProp_VinertGK.def("SetLocation", (void (BRepGProp_VinertGK::*)(const gp_Pnt &)) &BRepGProp_VinertGK::SetLocation, "Sets the vertex that delimit 3D closed region of space.", py::arg("theLocation"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0) -> Standard_Real { return self.Perform(a0); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const Standard_Real a1) -> Standard_Real { return self.Perform(a0, a1); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const Standard_Real a1, const Standard_Boolean a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the naturally restricted surface and the point VLocation.", py::arg("theSurface"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pnt & a1) -> Standard_Real { return self.Perform(a0, a1); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pnt & a1, const Standard_Real a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pnt & a1, const Standard_Real a2, const Standard_Boolean a3) -> Standard_Real { return self.Perform(a0, a1, a2, a3); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the naturally restricted surface and the point VLocation. The inertia is computed with respect to thePoint.", py::arg("theSurface"), py::arg("thePoint"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1) -> Standard_Real { return self.Perform(a0, a1); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const Standard_Real a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const Standard_Real a2, const Standard_Boolean a3) -> Standard_Real { return self.Perform(a0, a1, a2, a3); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, BRepGProp_Domain &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the surface bounded by the domain and the point VLocation.", py::arg("theSurface"), py::arg("theDomain"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pnt & a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pnt & a2, const Standard_Real a3) -> Standard_Real { return self.Perform(a0, a1, a2, a3); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pnt & a2, const Standard_Real a3, const Standard_Boolean a4) -> Standard_Real { return self.Perform(a0, a1, a2, a3, a4); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pnt &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the surface bounded by the domain and the point VLocation. The inertia is computed with respect to thePoint.", py::arg("theSurface"), py::arg("theDomain"), py::arg("thePoint"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pln & a1) -> Standard_Real { return self.Perform(a0, a1); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pln & a1, const Standard_Real a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, const gp_Pln & a1, const Standard_Real a2, const Standard_Boolean a3) -> Standard_Real { return self.Perform(a0, a1, a2, a3); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, const gp_Pln &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the naturally restricted surface and the plane.", py::arg("theSurface"), py::arg("thePlane"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pln & a2) -> Standard_Real { return self.Perform(a0, a1, a2); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pln & a2, const Standard_Real a3) -> Standard_Real { return self.Perform(a0, a1, a2, a3); });
cls_BRepGProp_VinertGK.def("Perform", [](BRepGProp_VinertGK &self, BRepGProp_Face & a0, BRepGProp_Domain & a1, const gp_Pln & a2, const Standard_Real a3, const Standard_Boolean a4) -> Standard_Real { return self.Perform(a0, a1, a2, a3, a4); });
cls_BRepGProp_VinertGK.def("Perform", (Standard_Real (BRepGProp_VinertGK::*)(BRepGProp_Face &, BRepGProp_Domain &, const gp_Pln &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &BRepGProp_VinertGK::Perform, "Computes the global properties of a region of 3D space delimited with the surface bounded by the domain and the plane.", py::arg("theSurface"), py::arg("theDomain"), py::arg("thePlane"), py::arg("theTolerance"), py::arg("theCGFlag"), py::arg("theIFlag"));
cls_BRepGProp_VinertGK.def("GetErrorReached", (Standard_Real (BRepGProp_VinertGK::*)() const) &BRepGProp_VinertGK::GetErrorReached, "Returns the relative reached computation error.");
// cls_BRepGProp_VinertGK.def("GetAbsolutError", (Standard_Real (BRepGProp_VinertGK::*)() const) &BRepGProp_VinertGK::GetAbsolutError, "Returns the absolut reached computation error.");


}
