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
#include <IGESGeom_Protocol.hxx>
#include <IGESGeom_CircularArc.hxx>
#include <IGESGeom_CompositeCurve.hxx>
#include <IGESGeom_ConicArc.hxx>
#include <IGESGeom_CopiousData.hxx>
#include <IGESGeom_Plane.hxx>
#include <IGESGeom_Line.hxx>
#include <IGESGeom_SplineCurve.hxx>
#include <IGESGeom_SplineSurface.hxx>
#include <IGESGeom_Point.hxx>
#include <IGESGeom_RuledSurface.hxx>
#include <IGESGeom_SurfaceOfRevolution.hxx>
#include <IGESGeom_TabulatedCylinder.hxx>
#include <IGESGeom_Direction.hxx>
#include <IGESGeom_TransformationMatrix.hxx>
#include <IGESGeom_Flash.hxx>
#include <IGESGeom_BSplineCurve.hxx>
#include <IGESGeom_BSplineSurface.hxx>
#include <IGESGeom_OffsetCurve.hxx>
#include <IGESGeom_OffsetSurface.hxx>
#include <IGESGeom_Boundary.hxx>
#include <IGESGeom_CurveOnSurface.hxx>
#include <IGESGeom_BoundedSurface.hxx>
#include <IGESGeom_TrimmedSurface.hxx>
#include <IGESGeom_ToolCircularArc.hxx>
#include <IGESGeom_ToolCompositeCurve.hxx>
#include <IGESGeom_ToolConicArc.hxx>
#include <IGESGeom_ToolCopiousData.hxx>
#include <IGESGeom_ToolPlane.hxx>
#include <IGESGeom_ToolLine.hxx>
#include <IGESGeom_ToolSplineCurve.hxx>
#include <IGESGeom_ToolSplineSurface.hxx>
#include <IGESGeom_ToolPoint.hxx>
#include <IGESGeom_ToolRuledSurface.hxx>
#include <IGESGeom_ToolSurfaceOfRevolution.hxx>
#include <IGESGeom_ToolTabulatedCylinder.hxx>
#include <IGESGeom_ToolDirection.hxx>
#include <IGESGeom_ToolTransformationMatrix.hxx>
#include <IGESGeom_ToolFlash.hxx>
#include <IGESGeom_ToolBSplineCurve.hxx>
#include <IGESGeom_ToolBSplineSurface.hxx>
#include <IGESGeom_ToolOffsetCurve.hxx>
#include <IGESGeom_ToolOffsetSurface.hxx>
#include <IGESGeom_ToolBoundary.hxx>
#include <IGESGeom_ToolCurveOnSurface.hxx>
#include <IGESGeom_ToolBoundedSurface.hxx>
#include <IGESGeom_ToolTrimmedSurface.hxx>
#include <IGESGeom_ReadWriteModule.hxx>
#include <IGESGeom_GeneralModule.hxx>
#include <IGESGeom_SpecificModule.hxx>
#include <IGESGeom.hxx>
#include <IGESData_IGESEntity.hxx>
#include <Standard_TypeDef.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESBasic_HArray1OfHArray1OfIGESEntity.hxx>
#include <Standard_Std.hxx>
#include <Standard_Type.hxx>
#include <NCollection_Array1.hxx>
#include <IGESGeom_Array1OfBoundary.hxx>
#include <IGESGeom_Array1OfCurveOnSurface.hxx>
#include <IGESData_TransfEntity.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <gp_GTrsf.hxx>
#include <IGESGeom_Array1OfTransformationMatrix.hxx>
#include <Standard_Transient.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <IGESGeom_HArray1OfBoundary.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColgp_HArray1OfXYZ.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <TColgp_HArray2OfXYZ.hxx>
#include <gp_XY.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <IGESData_GeneralModule.hxx>
#include <Interface_EntityIterator.hxx>
#include <IGESData_DirChecker.hxx>
#include <Interface_ShareTool.hxx>
#include <Interface_Check.hxx>
#include <Interface_CopyTool.hxx>
#include <IGESGeom_HArray1OfCurveOnSurface.hxx>
#include <IGESGeom_HArray1OfTransformationMatrix.hxx>
#include <IGESBasic_SubfigureDef.hxx>
#include <IGESData_Protocol.hxx>
#include <Interface_Protocol.hxx>
#include <IGESData_ReadWriteModule.hxx>
#include <IGESData_IGESReaderData.hxx>
#include <IGESData_ParamReader.hxx>
#include <IGESData_IGESWriter.hxx>
#include <IGESData_SpecificModule.hxx>
#include <IGESData_IGESDumper.hxx>
#include <Message_Messenger.hxx>
#include <IGESBasic_HArray2OfHArray1OfReal.hxx>
#include <bind_NCollection_Array1.hxx>

PYBIND11_MODULE(IGESGeom, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.IGESData");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.IGESBasic");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.gp");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.Interface");
py::module::import("OCCT.Message");

// CLASS: IGESGEOM
py::class_<IGESGeom> cls_IGESGeom(mod, "IGESGeom", "This package consists of B-Rep and CSG Solid entities");

// Constructors
cls_IGESGeom.def(py::init<>());

// Methods
// cls_IGESGeom.def_static("operator new_", (void * (*)(size_t)) &IGESGeom::operator new, "None", py::arg("theSize"));
// cls_IGESGeom.def_static("operator delete_", (void (*)(void *)) &IGESGeom::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom.def_static("Init_", (void (*)()) &IGESGeom::Init, "Prepares dymanic data (Protocol, Modules) for this package");
cls_IGESGeom.def_static("Protocol_", (opencascade::handle<IGESGeom_Protocol> (*)()) &IGESGeom::Protocol, "Returns the Protocol for this Package");

// CLASS: IGESGEOM_BOUNDARY
py::class_<IGESGeom_Boundary, opencascade::handle<IGESGeom_Boundary>, IGESData_IGESEntity> cls_IGESGeom_Boundary(mod, "IGESGeom_Boundary", "defines IGESBoundary, Type <141> Form <0> in package IGESGeom A boundary entity identifies a surface boundary consisting of a set of curves lying on the surface");

// Constructors
cls_IGESGeom_Boundary.def(py::init<>());

// Methods
cls_IGESGeom_Boundary.def("Init", (void (IGESGeom_Boundary::*)(const Standard_Integer, const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_HArray1OfIGESEntity> &, const opencascade::handle<TColStd_HArray1OfInteger> &, const opencascade::handle<IGESBasic_HArray1OfHArray1OfIGESEntity> &)) &IGESGeom_Boundary::Init, "This method is used to set the fields of the class Boundary - aType : Type of bounded surface representation - aPreference : Preferred representation of Trimming Curve - aSurface : Untrimmed surface to be bounded - allModelCurves : Model Space Curves - allSenses : Orientation flags of all Model Space Curves - allParameterCurves : Parameter Space Curves raises exception if allSenses, allModelCurves and allParameterCurves do not have same dimensions", py::arg("aType"), py::arg("aPreference"), py::arg("aSurface"), py::arg("allModelCurves"), py::arg("allSenses"), py::arg("allParameterCurves"));
cls_IGESGeom_Boundary.def("BoundaryType", (Standard_Integer (IGESGeom_Boundary::*)() const) &IGESGeom_Boundary::BoundaryType, "returns type of bounded surface representation 0 = Boundary entities may only reference model space trimming curves. Associated surface representation may be parametric 1 = Boundary entities must reference model space curves and associated parameter space curve collections. Associated surface must be a parametric representation");
cls_IGESGeom_Boundary.def("PreferenceType", (Standard_Integer (IGESGeom_Boundary::*)() const) &IGESGeom_Boundary::PreferenceType, "returns preferred representation of trimming curves 0 = Unspecified 1 = Model space 2 = Parameter space 3 = Representations are of equal preference");
cls_IGESGeom_Boundary.def("Surface", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_Boundary::*)() const) &IGESGeom_Boundary::Surface, "returns the surface to be bounded");
cls_IGESGeom_Boundary.def("NbModelSpaceCurves", (Standard_Integer (IGESGeom_Boundary::*)() const) &IGESGeom_Boundary::NbModelSpaceCurves, "returns the number of model space curves");
cls_IGESGeom_Boundary.def("ModelSpaceCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_Boundary::*)(const Standard_Integer) const) &IGESGeom_Boundary::ModelSpaceCurve, "returns Model Space Curve raises exception if Index <= 0 or Index > NbModelSpaceCurves()", py::arg("Index"));
cls_IGESGeom_Boundary.def("Sense", (Standard_Integer (IGESGeom_Boundary::*)(const Standard_Integer) const) &IGESGeom_Boundary::Sense, "returns the sense of a particular model space curve 1 = model curve direction does not need reversal 2 = model curve direction needs to be reversed raises exception if Index <= 0 or Index > NbModelSpaceCurves()", py::arg("Index"));
cls_IGESGeom_Boundary.def("NbParameterCurves", (Standard_Integer (IGESGeom_Boundary::*)(const Standard_Integer) const) &IGESGeom_Boundary::NbParameterCurves, "returns the number of parameter curves associated with one model space curve referred to by Index raises exception if Index <= 0 or Index > NbModelSpaceCurves()", py::arg("Index"));
cls_IGESGeom_Boundary.def("ParameterCurves", (opencascade::handle<IGESData_HArray1OfIGESEntity> (IGESGeom_Boundary::*)(const Standard_Integer) const) &IGESGeom_Boundary::ParameterCurves, "returns an array of parameter space curves associated with a model space curve referred to by the Index raises exception if Index <= 0 or Index > NbModelSpaceCurves()", py::arg("Index"));
cls_IGESGeom_Boundary.def("ParameterCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_Boundary::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_Boundary::ParameterCurve, "returns an individual parameter curve raises exception if Index or Num is out of range", py::arg("Index"), py::arg("Num"));
cls_IGESGeom_Boundary.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Boundary::get_type_name, "None");
cls_IGESGeom_Boundary.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Boundary::get_type_descriptor, "None");
cls_IGESGeom_Boundary.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Boundary::*)() const) &IGESGeom_Boundary::DynamicType, "None");

// TYPEDEF: IGESGEOM_ARRAY1OFBOUNDARY
bind_NCollection_Array1<opencascade::handle<IGESGeom_Boundary> >(mod, "IGESGeom_Array1OfBoundary", py::module_local(false));

// CLASS: IGESGEOM_CURVEONSURFACE
py::class_<IGESGeom_CurveOnSurface, opencascade::handle<IGESGeom_CurveOnSurface>, IGESData_IGESEntity> cls_IGESGeom_CurveOnSurface(mod, "IGESGeom_CurveOnSurface", "defines IGESCurveOnSurface, Type <142> Form <0> in package IGESGeom A curve on a parametric surface entity associates a given curve with a surface and identifies the curve as lying on the surface.");

// Constructors
cls_IGESGeom_CurveOnSurface.def(py::init<>());

// Methods
cls_IGESGeom_CurveOnSurface.def("Init", (void (IGESGeom_CurveOnSurface::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer)) &IGESGeom_CurveOnSurface::Init, "This method is used to set the fields of the class CurveOnSurface - aMode : Way the curve on the surface has been created - aSurface : Surface on which the curve lies - aCurveUV : Curve S (UV) - aCurve3D : Curve C (3D) - aPreference : 0 = Unspecified 1 = S o B is preferred 2 = C is preferred 3 = C and S o B are equally preferred", py::arg("aMode"), py::arg("aSurface"), py::arg("aCurveUV"), py::arg("aCurve3D"), py::arg("aPreference"));
cls_IGESGeom_CurveOnSurface.def("CreationMode", (Standard_Integer (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::CreationMode, "returns the mode in which the curve is created on the surface 0 = Unspecified 1 = Projection of a given curve on the surface 2 = Intersection of two surfaces 3 = Isoparametric curve, i.e:- either a `u` parametric or a `v` parametric curve");
cls_IGESGeom_CurveOnSurface.def("Surface", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::Surface, "returns the surface on which the curve lies");
cls_IGESGeom_CurveOnSurface.def("CurveUV", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::CurveUV, "returns curve S");
cls_IGESGeom_CurveOnSurface.def("Curve3D", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::Curve3D, "returns curve C");
cls_IGESGeom_CurveOnSurface.def("PreferenceMode", (Standard_Integer (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::PreferenceMode, "returns preference mode 0 = Unspecified 1 = S o B is preferred 2 = C is preferred 3 = C and S o B are equally preferred");
cls_IGESGeom_CurveOnSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_CurveOnSurface::get_type_name, "None");
cls_IGESGeom_CurveOnSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_CurveOnSurface::get_type_descriptor, "None");
cls_IGESGeom_CurveOnSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_CurveOnSurface::*)() const) &IGESGeom_CurveOnSurface::DynamicType, "None");

// TYPEDEF: IGESGEOM_ARRAY1OFCURVEONSURFACE
bind_NCollection_Array1<opencascade::handle<IGESGeom_CurveOnSurface> >(mod, "IGESGeom_Array1OfCurveOnSurface", py::module_local(false));

// CLASS: IGESGEOM_TRANSFORMATIONMATRIX
py::class_<IGESGeom_TransformationMatrix, opencascade::handle<IGESGeom_TransformationMatrix>, IGESData_TransfEntity> cls_IGESGeom_TransformationMatrix(mod, "IGESGeom_TransformationMatrix", "defines IGESTransformationMatrix, Type <124> Form <0> in package IGESGeom The transformation matrix entity transforms three-row column vectors by means of matrix multiplication and then a vector addition. This entity can be considered as an 'operator' entity in that it starts with the input vector, operates on it as described above, and produces the output vector.");

// Constructors
cls_IGESGeom_TransformationMatrix.def(py::init<>());

// Methods
cls_IGESGeom_TransformationMatrix.def("Init", (void (IGESGeom_TransformationMatrix::*)(const opencascade::handle<TColStd_HArray2OfReal> &)) &IGESGeom_TransformationMatrix::Init, "This method is used to set the fields of the class TransformationMatrix - aMatrix : 3 x 4 array containing elements of the transformation matrix raises exception if aMatrix is not 3 x 4 array", py::arg("aMatrix"));
cls_IGESGeom_TransformationMatrix.def("SetFormNumber", (void (IGESGeom_TransformationMatrix::*)(const Standard_Integer)) &IGESGeom_TransformationMatrix::SetFormNumber, "Changes FormNumber (indicates the Type of Transf : Transformation 0-1 or Coordinate System 10-11-12) Error if not in ranges [0-1] or [10-12]", py::arg("form"));
cls_IGESGeom_TransformationMatrix.def("Data", (Standard_Real (IGESGeom_TransformationMatrix::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_TransformationMatrix::Data, "returns individual Data Errro if I not in [1-3] or J not in [1-4]", py::arg("I"), py::arg("J"));
cls_IGESGeom_TransformationMatrix.def("Value", (gp_GTrsf (IGESGeom_TransformationMatrix::*)() const) &IGESGeom_TransformationMatrix::Value, "returns the transformation matrix 4th row elements of GTrsf will always be 0, 0, 0, 1 (not defined)");
cls_IGESGeom_TransformationMatrix.def_static("get_type_name_", (const char * (*)()) &IGESGeom_TransformationMatrix::get_type_name, "None");
cls_IGESGeom_TransformationMatrix.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_TransformationMatrix::get_type_descriptor, "None");
cls_IGESGeom_TransformationMatrix.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_TransformationMatrix::*)() const) &IGESGeom_TransformationMatrix::DynamicType, "None");

// TYPEDEF: IGESGEOM_ARRAY1OFTRANSFORMATIONMATRIX
bind_NCollection_Array1<opencascade::handle<IGESGeom_TransformationMatrix> >(mod, "IGESGeom_Array1OfTransformationMatrix", py::module_local(false));

// CLASS: IGESGEOM_HARRAY1OFBOUNDARY
py::class_<IGESGeom_HArray1OfBoundary, opencascade::handle<IGESGeom_HArray1OfBoundary>, Standard_Transient> cls_IGESGeom_HArray1OfBoundary(mod, "IGESGeom_HArray1OfBoundary", "None", py::multiple_inheritance());

// Constructors
cls_IGESGeom_HArray1OfBoundary.def(py::init<>());
cls_IGESGeom_HArray1OfBoundary.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESGeom_HArray1OfBoundary.def(py::init<const Standard_Integer, const Standard_Integer, const IGESGeom_Array1OfBoundary::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESGeom_HArray1OfBoundary.def(py::init<const IGESGeom_Array1OfBoundary &>(), py::arg("theOther"));

// Methods
// cls_IGESGeom_HArray1OfBoundary.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_HArray1OfBoundary::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator delete_", (void (*)(void *)) &IGESGeom_HArray1OfBoundary::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_HArray1OfBoundary::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_HArray1OfBoundary::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_HArray1OfBoundary::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_HArray1OfBoundary::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfBoundary::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESGeom_HArray1OfBoundary.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfBoundary::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESGeom_HArray1OfBoundary.def("Array1", (const IGESGeom_Array1OfBoundary & (IGESGeom_HArray1OfBoundary::*)() const) &IGESGeom_HArray1OfBoundary::Array1, "None");
cls_IGESGeom_HArray1OfBoundary.def("ChangeArray1", (IGESGeom_Array1OfBoundary & (IGESGeom_HArray1OfBoundary::*)()) &IGESGeom_HArray1OfBoundary::ChangeArray1, "None");
cls_IGESGeom_HArray1OfBoundary.def_static("get_type_name_", (const char * (*)()) &IGESGeom_HArray1OfBoundary::get_type_name, "None");
cls_IGESGeom_HArray1OfBoundary.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_HArray1OfBoundary::get_type_descriptor, "None");
cls_IGESGeom_HArray1OfBoundary.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_HArray1OfBoundary::*)() const) &IGESGeom_HArray1OfBoundary::DynamicType, "None");

// CLASS: IGESGEOM_BOUNDEDSURFACE
py::class_<IGESGeom_BoundedSurface, opencascade::handle<IGESGeom_BoundedSurface>, IGESData_IGESEntity> cls_IGESGeom_BoundedSurface(mod, "IGESGeom_BoundedSurface", "defines BoundedSurface, Type <143> Form <0> in package IGESGeom A bounded surface is used to communicate trimmed surfaces. The surface and trimming curves are assumed to be represented parametrically.");

// Constructors
cls_IGESGeom_BoundedSurface.def(py::init<>());

// Methods
cls_IGESGeom_BoundedSurface.def("Init", (void (IGESGeom_BoundedSurface::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESGeom_HArray1OfBoundary> &)) &IGESGeom_BoundedSurface::Init, "This method is used to set the fields of the class BoundedSurface - aType : Type of bounded surface representation - aSurface : Surface entity to be bounded - allBounds : Array of boundary entities", py::arg("aType"), py::arg("aSurface"), py::arg("allBounds"));
cls_IGESGeom_BoundedSurface.def("RepresentationType", (Standard_Integer (IGESGeom_BoundedSurface::*)() const) &IGESGeom_BoundedSurface::RepresentationType, "returns the type of Bounded surface representation 0 = The boundary entities may only reference model space curves 1 = The boundary entities may reference both model space curves and associated parameter space curve representations");
cls_IGESGeom_BoundedSurface.def("Surface", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_BoundedSurface::*)() const) &IGESGeom_BoundedSurface::Surface, "returns the bounded surface");
cls_IGESGeom_BoundedSurface.def("NbBoundaries", (Standard_Integer (IGESGeom_BoundedSurface::*)() const) &IGESGeom_BoundedSurface::NbBoundaries, "returns the number of boundaries");
cls_IGESGeom_BoundedSurface.def("Boundary", (opencascade::handle<IGESGeom_Boundary> (IGESGeom_BoundedSurface::*)(const Standard_Integer) const) &IGESGeom_BoundedSurface::Boundary, "returns boundary entity raises exception if Index <= 0 or Index > NbBoundaries()", py::arg("Index"));
cls_IGESGeom_BoundedSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_BoundedSurface::get_type_name, "None");
cls_IGESGeom_BoundedSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_BoundedSurface::get_type_descriptor, "None");
cls_IGESGeom_BoundedSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_BoundedSurface::*)() const) &IGESGeom_BoundedSurface::DynamicType, "None");

// CLASS: IGESGEOM_BSPLINECURVE
py::class_<IGESGeom_BSplineCurve, opencascade::handle<IGESGeom_BSplineCurve>, IGESData_IGESEntity> cls_IGESGeom_BSplineCurve(mod, "IGESGeom_BSplineCurve", "defines IGESBSplineCurve, Type <126> Form <0-5> in package IGESGeom A parametric equation obtained by dividing two summations involving weights (which are real numbers), the control points, and B-Spline basis functions");

// Constructors
cls_IGESGeom_BSplineCurve.def(py::init<>());

// Methods
cls_IGESGeom_BSplineCurve.def("Init", (void (IGESGeom_BSplineCurve::*)(const Standard_Integer, const Standard_Integer, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColgp_HArray1OfXYZ> &, const Standard_Real, const Standard_Real, const gp_XYZ &)) &IGESGeom_BSplineCurve::Init, "This method is used to set the fields of the class BSplineCurve. Beware about indexation of arrays - anIndex : Upper index of the sum - aDegree : Degree of basis functions - aPlanar : 0 = nonplanar curve, 1 = planar curve - aClosed : 0 = open curve, 1 = closed curve - aPolynom : 0 = rational, 1 = polynomial - aPeriodic : 0 = nonperiodic, 1 = periodic - allKnots : Knot sequence values [-Degree,Index+1] - allWeights : Array of weights [0,Index] - allPoles : X, Y, Z coordinates of all control points [0,Index] - aUmin, aUmax : Starting and ending parameter values - aNorm : Unit normal (if the curve is planar) raises exception if allWeights & allPoles are not of same size.", py::arg("anIndex"), py::arg("aDegree"), py::arg("aPlanar"), py::arg("aClosed"), py::arg("aPolynom"), py::arg("aPeriodic"), py::arg("allKnots"), py::arg("allWeights"), py::arg("allPoles"), py::arg("aUmin"), py::arg("aUmax"), py::arg("aNorm"));
cls_IGESGeom_BSplineCurve.def("SetFormNumber", (void (IGESGeom_BSplineCurve::*)(const Standard_Integer)) &IGESGeom_BSplineCurve::SetFormNumber, "Changes FormNumber (indicates the Shape of the Curve) Error if not in range [0-5]", py::arg("form"));
cls_IGESGeom_BSplineCurve.def("UpperIndex", (Standard_Integer (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::UpperIndex, "returns the upper index of the sum (see Knots,Poles)");
cls_IGESGeom_BSplineCurve.def("Degree", (Standard_Integer (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::Degree, "returns the degree of basis functions");
cls_IGESGeom_BSplineCurve.def("IsPlanar", (Standard_Boolean (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::IsPlanar, "returns True if the curve is Planar, False if non-planar");
cls_IGESGeom_BSplineCurve.def("IsClosed", (Standard_Boolean (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::IsClosed, "returns True if the curve is closed, False if open");
cls_IGESGeom_BSplineCurve.def("IsPolynomial", [](IGESGeom_BSplineCurve &self) -> Standard_Boolean { return self.IsPolynomial(); });
cls_IGESGeom_BSplineCurve.def("IsPolynomial", (Standard_Boolean (IGESGeom_BSplineCurve::*)(const Standard_Boolean) const) &IGESGeom_BSplineCurve::IsPolynomial, "returns True if the curve is polynomial, False if rational <flag> False (D) : computed from the list of weights (all must be equal) <flag> True : as recorded", py::arg("flag"));
cls_IGESGeom_BSplineCurve.def("IsPeriodic", (Standard_Boolean (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::IsPeriodic, "returns True if the curve is periodic, False otherwise");
cls_IGESGeom_BSplineCurve.def("NbKnots", (Standard_Integer (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::NbKnots, "returns the number of knots (i.e. Degree + UpperIndex + 2)");
cls_IGESGeom_BSplineCurve.def("Knot", (Standard_Real (IGESGeom_BSplineCurve::*)(const Standard_Integer) const) &IGESGeom_BSplineCurve::Knot, "returns the knot referred to by anIndex, inside the range [-Degree,UpperIndex+1] raises exception if anIndex < -Degree() or anIndex > (NbKnots() - Degree()) Note : Knots are numbered from -Degree (not from 1)", py::arg("anIndex"));
cls_IGESGeom_BSplineCurve.def("NbPoles", (Standard_Integer (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::NbPoles, "returns number of poles (i.e. UpperIndex + 1)");
cls_IGESGeom_BSplineCurve.def("Weight", (Standard_Real (IGESGeom_BSplineCurve::*)(const Standard_Integer) const) &IGESGeom_BSplineCurve::Weight, "returns the weight referred to by anIndex, in [0,UpperIndex] raises exception if anIndex < 0 or anIndex > UpperIndex()", py::arg("anIndex"));
cls_IGESGeom_BSplineCurve.def("Pole", (gp_Pnt (IGESGeom_BSplineCurve::*)(const Standard_Integer) const) &IGESGeom_BSplineCurve::Pole, "returns the pole referred to by anIndex, in [0,UpperIndex] raises exception if anIndex < 0 or anIndex > UpperIndex()", py::arg("anIndex"));
cls_IGESGeom_BSplineCurve.def("TransformedPole", (gp_Pnt (IGESGeom_BSplineCurve::*)(const Standard_Integer) const) &IGESGeom_BSplineCurve::TransformedPole, "returns the anIndex'th pole after applying Transf. Matrix raises exception if an Index < 0 or an Index > UpperIndex()", py::arg("anIndex"));
cls_IGESGeom_BSplineCurve.def("UMin", (Standard_Real (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::UMin, "returns starting parameter value");
cls_IGESGeom_BSplineCurve.def("UMax", (Standard_Real (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::UMax, "returns ending parameter value");
cls_IGESGeom_BSplineCurve.def("Normal", (gp_XYZ (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::Normal, "if the curve is nonplanar then (0, 0, 0) is returned");
cls_IGESGeom_BSplineCurve.def_static("get_type_name_", (const char * (*)()) &IGESGeom_BSplineCurve::get_type_name, "None");
cls_IGESGeom_BSplineCurve.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_BSplineCurve::get_type_descriptor, "None");
cls_IGESGeom_BSplineCurve.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_BSplineCurve::*)() const) &IGESGeom_BSplineCurve::DynamicType, "None");

// CLASS: IGESGEOM_BSPLINESURFACE
py::class_<IGESGeom_BSplineSurface, opencascade::handle<IGESGeom_BSplineSurface>, IGESData_IGESEntity> cls_IGESGeom_BSplineSurface(mod, "IGESGeom_BSplineSurface", "defines IGESBSplineSurface, Type <128> Form <0-9> in package IGESGeom A parametric equation obtained by dividing two summations involving weights (which are real numbers), the control points, and B-Spline basis functions");

// Constructors
cls_IGESGeom_BSplineSurface.def(py::init<>());

// Methods
cls_IGESGeom_BSplineSurface.def("Init", (void (IGESGeom_BSplineSurface::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray2OfReal> &, const opencascade::handle<TColgp_HArray2OfXYZ> &, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &IGESGeom_BSplineSurface::Init, "This method is used to set the fields of the class BSplineSurface - anIndexU : Upper index of first sum - anIndexV : Upper index of second sum - aDegU, aDegV : Degrees of first and second sets of basis functions - aCloseU, aCloseV : 1 = Closed in U, V directions 0 = open in U, V directions - aPolynom : 0 = Rational, 1 = polynomial - aPeriodU, aPeriodV : 0 = Non periodic in U or V direction 1 = Periodic in U or V direction - allKnotsU, allKnotsV : Knots in U and V directions - allWeights : Array of weights - allPoles : XYZ coordinates of all control points - aUmin : Starting value of U direction - aUmax : Ending value of U direction - aVmin : Starting value of V direction - aVmax : Ending value of V direction raises exception if allWeights & allPoles are not of same size.", py::arg("anIndexU"), py::arg("anIndexV"), py::arg("aDegU"), py::arg("aDegV"), py::arg("aCloseU"), py::arg("aCloseV"), py::arg("aPolynom"), py::arg("aPeriodU"), py::arg("aPeriodV"), py::arg("allKnotsU"), py::arg("allKnotsV"), py::arg("allWeights"), py::arg("allPoles"), py::arg("aUmin"), py::arg("aUmax"), py::arg("aVmin"), py::arg("aVmax"));
cls_IGESGeom_BSplineSurface.def("SetFormNumber", (void (IGESGeom_BSplineSurface::*)(const Standard_Integer)) &IGESGeom_BSplineSurface::SetFormNumber, "Changes FormNumber (indicates the Shape of the Surface) Error if not in range [0-9]", py::arg("form"));
cls_IGESGeom_BSplineSurface.def("UpperIndexU", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::UpperIndexU, "returns the upper index of the first sum (U)");
cls_IGESGeom_BSplineSurface.def("UpperIndexV", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::UpperIndexV, "returns the upper index of the second sum (V)");
cls_IGESGeom_BSplineSurface.def("DegreeU", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::DegreeU, "returns degree of first set of basis functions");
cls_IGESGeom_BSplineSurface.def("DegreeV", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::DegreeV, "returns degree of second set of basis functions");
cls_IGESGeom_BSplineSurface.def("IsClosedU", (Standard_Boolean (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::IsClosedU, "True if closed in U direction else False");
cls_IGESGeom_BSplineSurface.def("IsClosedV", (Standard_Boolean (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::IsClosedV, "True if closed in V direction else False");
cls_IGESGeom_BSplineSurface.def("IsPolynomial", [](IGESGeom_BSplineSurface &self) -> Standard_Boolean { return self.IsPolynomial(); });
cls_IGESGeom_BSplineSurface.def("IsPolynomial", (Standard_Boolean (IGESGeom_BSplineSurface::*)(const Standard_Boolean) const) &IGESGeom_BSplineSurface::IsPolynomial, "True if polynomial, False if rational <flag> False (D) : computed from Weights <flag> True : recorded", py::arg("flag"));
cls_IGESGeom_BSplineSurface.def("IsPeriodicU", (Standard_Boolean (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::IsPeriodicU, "True if periodic in U direction else False");
cls_IGESGeom_BSplineSurface.def("IsPeriodicV", (Standard_Boolean (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::IsPeriodicV, "True if periodic in V direction else False");
cls_IGESGeom_BSplineSurface.def("NbKnotsU", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::NbKnotsU, "returns number of knots in U direction KnotsU are numbered from -DegreeU");
cls_IGESGeom_BSplineSurface.def("NbKnotsV", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::NbKnotsV, "returns number of knots in V direction KnotsV are numbered from -DegreeV");
cls_IGESGeom_BSplineSurface.def("KnotU", (Standard_Real (IGESGeom_BSplineSurface::*)(const Standard_Integer) const) &IGESGeom_BSplineSurface::KnotU, "returns the value of knot referred to by anIndex in U direction raises exception if anIndex < -DegreeU() or anIndex > (NbKnotsU() - DegreeU())", py::arg("anIndex"));
cls_IGESGeom_BSplineSurface.def("KnotV", (Standard_Real (IGESGeom_BSplineSurface::*)(const Standard_Integer) const) &IGESGeom_BSplineSurface::KnotV, "returns the value of knot referred to by anIndex in V direction raises exception if anIndex < -DegreeV() or anIndex > (NbKnotsV() - DegreeV())", py::arg("anIndex"));
cls_IGESGeom_BSplineSurface.def("NbPolesU", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::NbPolesU, "returns number of poles in U direction");
cls_IGESGeom_BSplineSurface.def("NbPolesV", (Standard_Integer (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::NbPolesV, "returns number of poles in V direction");
cls_IGESGeom_BSplineSurface.def("Weight", (Standard_Real (IGESGeom_BSplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_BSplineSurface::Weight, "returns the weight referred to by anIndex1, anIndex2 raises exception if anIndex1 <= 0 or anIndex1 > NbPolesU() or if anIndex2 <= 0 or anIndex2 > NbPolesV()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_BSplineSurface.def("Pole", (gp_Pnt (IGESGeom_BSplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_BSplineSurface::Pole, "returns the control point referenced by anIndex1, anIndex2 raises exception if anIndex1 <= 0 or anIndex1 > NbPolesU() or if anIndex2 <= 0 or anIndex2 > NbPolesV()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_BSplineSurface.def("TransformedPole", (gp_Pnt (IGESGeom_BSplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_BSplineSurface::TransformedPole, "returns the control point referenced by anIndex1, anIndex2 after applying the Transf.Matrix raises exception if anIndex1 <= 0 or anIndex1 > NbPolesU() or if anIndex2 <= 0 or anIndex2 > NbPolesV()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_BSplineSurface.def("UMin", (Standard_Real (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::UMin, "returns starting value in the U direction");
cls_IGESGeom_BSplineSurface.def("UMax", (Standard_Real (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::UMax, "returns ending value in the U direction");
cls_IGESGeom_BSplineSurface.def("VMin", (Standard_Real (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::VMin, "returns starting value in the V direction");
cls_IGESGeom_BSplineSurface.def("VMax", (Standard_Real (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::VMax, "returns ending value in the V direction");
cls_IGESGeom_BSplineSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_BSplineSurface::get_type_name, "None");
cls_IGESGeom_BSplineSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_BSplineSurface::get_type_descriptor, "None");
cls_IGESGeom_BSplineSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_BSplineSurface::*)() const) &IGESGeom_BSplineSurface::DynamicType, "None");

// CLASS: IGESGEOM_CIRCULARARC
py::class_<IGESGeom_CircularArc, opencascade::handle<IGESGeom_CircularArc>, IGESData_IGESEntity> cls_IGESGeom_CircularArc(mod, "IGESGeom_CircularArc", "defines IGESCircularArc, Type <100> Form <0> in package IGESGeom A circular arc is a connected portion of a parent circle which consists of more than one point. The definition space coordinate system is always chosen so that the circular arc remains in a plane either coincident with or parallel to the XT, YT plane.");

// Constructors
cls_IGESGeom_CircularArc.def(py::init<>());

// Methods
cls_IGESGeom_CircularArc.def("Init", (void (IGESGeom_CircularArc::*)(const Standard_Real, const gp_XY &, const gp_XY &, const gp_XY &)) &IGESGeom_CircularArc::Init, "This method is used to set the fields of the class CircularArc - aZT : Shift above the Z plane - aCenter : Center of the circle of which the arc forms a part - aStart : Starting point of the circular arc - anEnd : Ending point of the circular arc", py::arg("aZT"), py::arg("aCenter"), py::arg("aStart"), py::arg("anEnd"));
cls_IGESGeom_CircularArc.def("Center", (gp_Pnt2d (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::Center, "returns the center of the circle of which arc forms a part");
cls_IGESGeom_CircularArc.def("TransformedCenter", (gp_Pnt (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::TransformedCenter, "returns the center of the circle of which arc forms a part after applying Transf. Matrix");
cls_IGESGeom_CircularArc.def("StartPoint", (gp_Pnt2d (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::StartPoint, "returns the start point of the arc");
cls_IGESGeom_CircularArc.def("TransformedStartPoint", (gp_Pnt (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::TransformedStartPoint, "returns the start point of the arc after applying Transf. Matrix");
cls_IGESGeom_CircularArc.def("ZPlane", (Standard_Real (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::ZPlane, "returns the parallel displacement of the plane containing the arc from the XT, YT plane");
cls_IGESGeom_CircularArc.def("EndPoint", (gp_Pnt2d (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::EndPoint, "returns the end point of the arc");
cls_IGESGeom_CircularArc.def("TransformedEndPoint", (gp_Pnt (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::TransformedEndPoint, "returns the end point of the arc after applying Transf. Matrix");
cls_IGESGeom_CircularArc.def("Radius", (Standard_Real (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::Radius, "returns the radius of the circle of which arc forms a part");
cls_IGESGeom_CircularArc.def("Angle", (Standard_Real (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::Angle, "returns the angle subtended by the arc at the center in radians");
cls_IGESGeom_CircularArc.def("Axis", (gp_Dir (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::Axis, "Z-Axis of circle (i.e. [0,0,1])");
cls_IGESGeom_CircularArc.def("TransformedAxis", (gp_Dir (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::TransformedAxis, "Z-Axis after applying Trans. Matrix");
cls_IGESGeom_CircularArc.def("IsClosed", (Standard_Boolean (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::IsClosed, "True if StartPoint = EndPoint");
cls_IGESGeom_CircularArc.def_static("get_type_name_", (const char * (*)()) &IGESGeom_CircularArc::get_type_name, "None");
cls_IGESGeom_CircularArc.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_CircularArc::get_type_descriptor, "None");
cls_IGESGeom_CircularArc.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_CircularArc::*)() const) &IGESGeom_CircularArc::DynamicType, "None");

// CLASS: IGESGEOM_COMPOSITECURVE
py::class_<IGESGeom_CompositeCurve, opencascade::handle<IGESGeom_CompositeCurve>, IGESData_IGESEntity> cls_IGESGeom_CompositeCurve(mod, "IGESGeom_CompositeCurve", "defines IGESCompositeCurve, Type <102> Form <0> in package IGESGeom A composite curve is defined as an ordered list of entities consisting of a point, connect point and parametrised curve entities (excluding the CompositeCurve entity).");

// Constructors
cls_IGESGeom_CompositeCurve.def(py::init<>());

// Methods
cls_IGESGeom_CompositeCurve.def("Init", (void (IGESGeom_CompositeCurve::*)(const opencascade::handle<IGESData_HArray1OfIGESEntity> &)) &IGESGeom_CompositeCurve::Init, "This method is used to set the fields of the class CompositeCurve - allEntities : Constituent Entities of the composite curve", py::arg("allEntities"));
cls_IGESGeom_CompositeCurve.def("NbCurves", (Standard_Integer (IGESGeom_CompositeCurve::*)() const) &IGESGeom_CompositeCurve::NbCurves, "returns the number of curves contained in the CompositeCurve");
cls_IGESGeom_CompositeCurve.def("Curve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_CompositeCurve::*)(const Standard_Integer) const) &IGESGeom_CompositeCurve::Curve, "returns Component of the CompositeCurve (a curve or a point) raises exception if Index <= 0 or Index > NbCurves()", py::arg("Index"));
cls_IGESGeom_CompositeCurve.def_static("get_type_name_", (const char * (*)()) &IGESGeom_CompositeCurve::get_type_name, "None");
cls_IGESGeom_CompositeCurve.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_CompositeCurve::get_type_descriptor, "None");
cls_IGESGeom_CompositeCurve.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_CompositeCurve::*)() const) &IGESGeom_CompositeCurve::DynamicType, "None");

// CLASS: IGESGEOM_CONICARC
py::class_<IGESGeom_ConicArc, opencascade::handle<IGESGeom_ConicArc>, IGESData_IGESEntity> cls_IGESGeom_ConicArc(mod, "IGESGeom_ConicArc", "defines IGESConicArc, Type <104> Form <0-3> in package IGESGeom A conic arc is a bounded connected portion of a parent conic curve which consists of more than one point. The parent conic curve is either an ellipse, a parabola, or a hyperbola. The definition space coordinate system is always chosen so that the conic arc lies in a plane either coincident with or parallel to XT, YT plane. Within such a plane a conic is defined by the six coefficients in the following equation. A*XT^2 + B*XT*YT + C*YT^2 + D*XT + E*YT + F = 0");

// Constructors
cls_IGESGeom_ConicArc.def(py::init<>());

// Methods
cls_IGESGeom_ConicArc.def("Init", (void (IGESGeom_ConicArc::*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_XY &, const gp_XY &)) &IGESGeom_ConicArc::Init, "This method is used to set the fields of the class ConicalArc - A, B, C, D, E, F : Coefficients of the equation defining conic arc - ZT : Parallel ZT displacement of the arc from XT, YT plane. - aStart : Starting point of the conic arc - anEnd : End point of the conic arc", py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"), py::arg("E"), py::arg("F"), py::arg("ZT"), py::arg("aStart"), py::arg("anEnd"));
cls_IGESGeom_ConicArc.def("OwnCorrect", (Standard_Boolean (IGESGeom_ConicArc::*)()) &IGESGeom_ConicArc::OwnCorrect, "sets the Form Number equal to ComputedFormNumber, returns True if changed");
cls_IGESGeom_ConicArc.def("ComputedFormNumber", (Standard_Integer (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::ComputedFormNumber, "Computes the Form Number according to the equation 1 for Ellipse, 2 for Hyperbola, 3 for Parabola");
cls_IGESGeom_ConicArc.def("Equation", [](IGESGeom_ConicArc &self, Standard_Real & A, Standard_Real & B, Standard_Real & C, Standard_Real & D, Standard_Real & E, Standard_Real & F){ self.Equation(A, B, C, D, E, F); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(A, B, C, D, E, F); }, "None", py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"), py::arg("E"), py::arg("F"));
cls_IGESGeom_ConicArc.def("ZPlane", (Standard_Real (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::ZPlane, "returns the Z displacement of the arc from XT, YT plane");
cls_IGESGeom_ConicArc.def("StartPoint", (gp_Pnt2d (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::StartPoint, "returns the starting point of the arc");
cls_IGESGeom_ConicArc.def("TransformedStartPoint", (gp_Pnt (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::TransformedStartPoint, "returns the starting point of the arc after applying Transf. Matrix");
cls_IGESGeom_ConicArc.def("EndPoint", (gp_Pnt2d (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::EndPoint, "returns the end point of the arc");
cls_IGESGeom_ConicArc.def("TransformedEndPoint", (gp_Pnt (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::TransformedEndPoint, "returns the end point of the arc after applying Transf. Matrix");
cls_IGESGeom_ConicArc.def("IsFromEllipse", (Standard_Boolean (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::IsFromEllipse, "returns True if parent conic curve is an ellipse");
cls_IGESGeom_ConicArc.def("IsFromParabola", (Standard_Boolean (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::IsFromParabola, "returns True if parent conic curve is a parabola");
cls_IGESGeom_ConicArc.def("IsFromHyperbola", (Standard_Boolean (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::IsFromHyperbola, "returns True if parent conic curve is a hyperbola");
cls_IGESGeom_ConicArc.def("IsClosed", (Standard_Boolean (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::IsClosed, "returns True if StartPoint = EndPoint");
cls_IGESGeom_ConicArc.def("Axis", (gp_Dir (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::Axis, "Z-Axis of conic (i.e. [0,0,1])");
cls_IGESGeom_ConicArc.def("TransformedAxis", (gp_Dir (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::TransformedAxis, "Z-Axis after applying Trans. Matrix");
cls_IGESGeom_ConicArc.def("Definition", [](IGESGeom_ConicArc &self, gp_Pnt & Center, gp_Dir & MainAxis, Standard_Real & rmin, Standard_Real & rmax){ self.Definition(Center, MainAxis, rmin, rmax); return std::tuple<Standard_Real &, Standard_Real &>(rmin, rmax); }, "Returns a Definition computed from equation, easier to use <Center> : the center of the the conic (meaningless for a parabola) (defined with Z displacement) <MainAxis> : the Main Axis of the conic (for a Circle, arbitrary the X Axis) <Rmin,Rmax> : Minor and Major Radii of the conic For a Circle, Rmin = Rmax, For a Parabola, Rmin = Rmax = the Focal Warning : the basic definition (by equation) is not very stable, limit cases may be approximative", py::arg("Center"), py::arg("MainAxis"), py::arg("rmin"), py::arg("rmax"));
cls_IGESGeom_ConicArc.def("TransformedDefinition", [](IGESGeom_ConicArc &self, gp_Pnt & Center, gp_Dir & MainAxis, Standard_Real & rmin, Standard_Real & rmax){ self.TransformedDefinition(Center, MainAxis, rmin, rmax); return std::tuple<Standard_Real &, Standard_Real &>(rmin, rmax); }, "Same as Definition, but the Location is applied on the Center and the MainAxis", py::arg("Center"), py::arg("MainAxis"), py::arg("rmin"), py::arg("rmax"));
cls_IGESGeom_ConicArc.def("ComputedDefinition", [](IGESGeom_ConicArc &self, Standard_Real & Xcen, Standard_Real & Ycen, Standard_Real & Xax, Standard_Real & Yax, Standard_Real & Rmin, Standard_Real & Rmax){ self.ComputedDefinition(Xcen, Ycen, Xax, Yax, Rmin, Rmax); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(Xcen, Ycen, Xax, Yax, Rmin, Rmax); }, "Computes and returns the coordinates of the definition of a comic from its equation. Used by Definition & TransformedDefinition, or may be called directly if needed", py::arg("Xcen"), py::arg("Ycen"), py::arg("Xax"), py::arg("Yax"), py::arg("Rmin"), py::arg("Rmax"));
cls_IGESGeom_ConicArc.def_static("get_type_name_", (const char * (*)()) &IGESGeom_ConicArc::get_type_name, "None");
cls_IGESGeom_ConicArc.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_ConicArc::get_type_descriptor, "None");
cls_IGESGeom_ConicArc.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_ConicArc::*)() const) &IGESGeom_ConicArc::DynamicType, "None");

// CLASS: IGESGEOM_COPIOUSDATA
py::class_<IGESGeom_CopiousData, opencascade::handle<IGESGeom_CopiousData>, IGESData_IGESEntity> cls_IGESGeom_CopiousData(mod, "IGESGeom_CopiousData", "defines IGESCopiousData, Type <106> Form <1-3,11-13,63> in package IGESGeom This entity stores data points in the form of pairs, triples, or sextuples. An interpretation flag value signifies which of these forms is being used.");

// Constructors
cls_IGESGeom_CopiousData.def(py::init<>());

// Methods
cls_IGESGeom_CopiousData.def("Init", (void (IGESGeom_CopiousData::*)(const Standard_Integer, const Standard_Real, const opencascade::handle<TColStd_HArray1OfReal> &)) &IGESGeom_CopiousData::Init, "This method is used to set the fields of the class CopiousData - aDataType : Specifies whether data is a pair or a triple or a sextuple. - aZPlane : Common Z value for all points if datatype = 1 - allData : Data to be read in groups of 2, 3 or 6", py::arg("aDataType"), py::arg("aZPlane"), py::arg("allData"));
cls_IGESGeom_CopiousData.def("SetPolyline", (void (IGESGeom_CopiousData::*)(const Standard_Boolean)) &IGESGeom_CopiousData::SetPolyline, "Sets Copious Data to be a Polyline if <mode> is True (Form = 11-12-13) or a Set of Points else (Form 1-2-3)", py::arg("mode"));
cls_IGESGeom_CopiousData.def("SetClosedPath2D", (void (IGESGeom_CopiousData::*)()) &IGESGeom_CopiousData::SetClosedPath2D, "Sets Copious Data to be a Closed Path 2D (Form 63) Warning : DataType is not checked and must be set to ONE by Init");
cls_IGESGeom_CopiousData.def("IsPointSet", (Standard_Boolean (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::IsPointSet, "Returns True if <me> is a Set of Points (Form 1-2-3)");
cls_IGESGeom_CopiousData.def("IsPolyline", (Standard_Boolean (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::IsPolyline, "Returns True if <me> is a Polyline (Form 11-12-13)");
cls_IGESGeom_CopiousData.def("IsClosedPath2D", (Standard_Boolean (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::IsClosedPath2D, "Returns True if <me> is a Closed Path 2D (Form 63)");
cls_IGESGeom_CopiousData.def("DataType", (Standard_Integer (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::DataType, "returns data type 1 = XY ( with common Z given by plane) 2 = XYZ ( point) 3 = XYZ + Vec(XYZ) (point + normal vector)");
cls_IGESGeom_CopiousData.def("NbPoints", (Standard_Integer (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::NbPoints, "returns the number of tuples");
cls_IGESGeom_CopiousData.def("Data", (Standard_Real (IGESGeom_CopiousData::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_CopiousData::Data, "Returns an individual Data, given the N0 of the Point and the B0 of the Coordinate (according DataType)", py::arg("NumPoint"), py::arg("NumData"));
cls_IGESGeom_CopiousData.def("ZPlane", (Standard_Real (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::ZPlane, "If datatype = 1, then returns common z value for all data else returns 0");
cls_IGESGeom_CopiousData.def("Point", (gp_Pnt (IGESGeom_CopiousData::*)(const Standard_Integer) const) &IGESGeom_CopiousData::Point, "returns the coordinates of the point specified by the anIndex raises exception if anIndex <= 0 or anIndex > NbPoints()", py::arg("anIndex"));
cls_IGESGeom_CopiousData.def("TransformedPoint", (gp_Pnt (IGESGeom_CopiousData::*)(const Standard_Integer) const) &IGESGeom_CopiousData::TransformedPoint, "returns the coordinates of the point specified by the anIndex after applying Transf. Matrix raises exception if anIndex <= 0 or anIndex > NbPoints()", py::arg("anIndex"));
cls_IGESGeom_CopiousData.def("Vector", (gp_Vec (IGESGeom_CopiousData::*)(const Standard_Integer) const) &IGESGeom_CopiousData::Vector, "returns i, j, k values if 3-tuple else returns (0, 0, 0) raises exception if anIndex <= 0 or anIndex > NbPoints()", py::arg("anIndex"));
cls_IGESGeom_CopiousData.def("TransformedVector", (gp_Vec (IGESGeom_CopiousData::*)(const Standard_Integer) const) &IGESGeom_CopiousData::TransformedVector, "returns transformed vector if 3-tuple else returns (0, 0, 0) raises exception if anIndex <= 0 or anIndex > NbPoints()", py::arg("anIndex"));
cls_IGESGeom_CopiousData.def_static("get_type_name_", (const char * (*)()) &IGESGeom_CopiousData::get_type_name, "None");
cls_IGESGeom_CopiousData.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_CopiousData::get_type_descriptor, "None");
cls_IGESGeom_CopiousData.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_CopiousData::*)() const) &IGESGeom_CopiousData::DynamicType, "None");

// CLASS: IGESGEOM_DIRECTION
py::class_<IGESGeom_Direction, opencascade::handle<IGESGeom_Direction>, IGESData_IGESEntity> cls_IGESGeom_Direction(mod, "IGESGeom_Direction", "defines IGESDirection, Type <123> Form <0> in package IGESGeom A direction entity is a non-zero vector in Euclidean 3-space that is defined by its three components (direction ratios) with respect to the coordinate axes. If x, y, z are the direction ratios then (x^2 + y^2 + z^2) > 0");

// Constructors
cls_IGESGeom_Direction.def(py::init<>());

// Methods
cls_IGESGeom_Direction.def("Init", (void (IGESGeom_Direction::*)(const gp_XYZ &)) &IGESGeom_Direction::Init, "This method is used to set the fields of the class Direction - aDirection : Direction ratios, Z is 0 by default", py::arg("aDirection"));
cls_IGESGeom_Direction.def("Value", (gp_Vec (IGESGeom_Direction::*)() const) &IGESGeom_Direction::Value, "None");
cls_IGESGeom_Direction.def("TransformedValue", (gp_Vec (IGESGeom_Direction::*)() const) &IGESGeom_Direction::TransformedValue, "returns the Direction value after applying Transformation matrix");
cls_IGESGeom_Direction.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Direction::get_type_name, "None");
cls_IGESGeom_Direction.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Direction::get_type_descriptor, "None");
cls_IGESGeom_Direction.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Direction::*)() const) &IGESGeom_Direction::DynamicType, "None");

// CLASS: IGESGEOM_FLASH
py::class_<IGESGeom_Flash, opencascade::handle<IGESGeom_Flash>, IGESData_IGESEntity> cls_IGESGeom_Flash(mod, "IGESGeom_Flash", "defines IGESFlash, Type <125> Form <0 - 4> in package IGESGeom A flash entity is a point in the ZT=0 plane that locates a particular closed area. That closed area can be defined in one of two ways. First, it can be an arbitrary closed area defined by any entity capable of defining a closed area. The points of this entity must all lie in the ZT=0 plane. Second, it can be a member of a predefined set of flash shapes.");

// Constructors
cls_IGESGeom_Flash.def(py::init<>());

// Methods
cls_IGESGeom_Flash.def("Init", (void (IGESGeom_Flash::*)(const gp_XY &, const Standard_Real, const Standard_Real, const Standard_Real, const opencascade::handle<IGESData_IGESEntity> &)) &IGESGeom_Flash::Init, "This method is used to set the fields of the class Flash - aPoint : Reference of flash - aDim : First flash sizing parameter - anotherDim : Second flash sizing parameter - aRotation : Rotation of flash about reference point in radians - aReference : Pointer to the referenced entity or Null", py::arg("aPoint"), py::arg("aDim"), py::arg("anotherDim"), py::arg("aRotation"), py::arg("aReference"));
cls_IGESGeom_Flash.def("SetFormNumber", (void (IGESGeom_Flash::*)(const Standard_Integer)) &IGESGeom_Flash::SetFormNumber, "Changes FormNumber (indicates the Nature of the Flash : 0 Unspecified, then given by Reference, 1->4 various Specialisations (Circle,Rectangle, etc...) ) Error if not in range [0-4]", py::arg("form"));
cls_IGESGeom_Flash.def("ReferencePoint", (gp_Pnt2d (IGESGeom_Flash::*)() const) &IGESGeom_Flash::ReferencePoint, "returns the referenced point, Z = 0 always");
cls_IGESGeom_Flash.def("TransformedReferencePoint", (gp_Pnt (IGESGeom_Flash::*)() const) &IGESGeom_Flash::TransformedReferencePoint, "returns the referenced point after applying Transf. Matrix");
cls_IGESGeom_Flash.def("Dimension1", (Standard_Real (IGESGeom_Flash::*)() const) &IGESGeom_Flash::Dimension1, "returns first flash sizing parameter");
cls_IGESGeom_Flash.def("Dimension2", (Standard_Real (IGESGeom_Flash::*)() const) &IGESGeom_Flash::Dimension2, "returns second flash sizing parameter");
cls_IGESGeom_Flash.def("Rotation", (Standard_Real (IGESGeom_Flash::*)() const) &IGESGeom_Flash::Rotation, "returns the angle in radians of the rotation of flash about the reference point");
cls_IGESGeom_Flash.def("ReferenceEntity", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_Flash::*)() const) &IGESGeom_Flash::ReferenceEntity, "returns the referenced entity or Null handle.");
cls_IGESGeom_Flash.def("HasReferenceEntity", (Standard_Boolean (IGESGeom_Flash::*)() const) &IGESGeom_Flash::HasReferenceEntity, "returns True if referenced entity is present.");
cls_IGESGeom_Flash.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Flash::get_type_name, "None");
cls_IGESGeom_Flash.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Flash::get_type_descriptor, "None");
cls_IGESGeom_Flash.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Flash::*)() const) &IGESGeom_Flash::DynamicType, "None");

// CLASS: IGESGEOM_GENERALMODULE
py::class_<IGESGeom_GeneralModule, opencascade::handle<IGESGeom_GeneralModule>, IGESData_GeneralModule> cls_IGESGeom_GeneralModule(mod, "IGESGeom_GeneralModule", "Definition of General Services for IGESGeom (specific part) This Services comprise : Shared & Implied Lists, Copy, Check");

// Constructors
cls_IGESGeom_GeneralModule.def(py::init<>());

// Methods
cls_IGESGeom_GeneralModule.def("OwnSharedCase", (void (IGESGeom_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, Interface_EntityIterator &) const) &IGESGeom_GeneralModule::OwnSharedCase, "Lists the Entities shared by a given IGESEntity <ent>, from its specific parameters : specific for each type", py::arg("CN"), py::arg("ent"), py::arg("iter"));
cls_IGESGeom_GeneralModule.def("DirChecker", (IGESData_DirChecker (IGESGeom_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESGeom_GeneralModule::DirChecker, "Returns a DirChecker, specific for each type of Entity (identified by its Case Number) : this DirChecker defines constraints which must be respected by the DirectoryPart", py::arg("CN"), py::arg("ent"));
cls_IGESGeom_GeneralModule.def("OwnCheckCase", (void (IGESGeom_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_GeneralModule::OwnCheckCase, "Performs Specific Semantic Check for each type of Entity", py::arg("CN"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_GeneralModule.def("NewVoid", (Standard_Boolean (IGESGeom_GeneralModule::*)(const Standard_Integer, opencascade::handle<Standard_Transient> &) const) &IGESGeom_GeneralModule::NewVoid, "Specific creation of a new void entity", py::arg("CN"), py::arg("entto"));
cls_IGESGeom_GeneralModule.def("OwnCopyCase", (void (IGESGeom_GeneralModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, Interface_CopyTool &) const) &IGESGeom_GeneralModule::OwnCopyCase, "Copies parameters which are specific of each Type of Entity", py::arg("CN"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_GeneralModule.def("CategoryNumber", (Standard_Integer (IGESGeom_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &) const) &IGESGeom_GeneralModule::CategoryNumber, "Returns a category number which characterizes an entity Shape for all, but Drawing for : Flash; Point with a symbol; Plane with a symbol", py::arg("CN"), py::arg("ent"), py::arg("shares"));
cls_IGESGeom_GeneralModule.def_static("get_type_name_", (const char * (*)()) &IGESGeom_GeneralModule::get_type_name, "None");
cls_IGESGeom_GeneralModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_GeneralModule::get_type_descriptor, "None");
cls_IGESGeom_GeneralModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_GeneralModule::*)() const) &IGESGeom_GeneralModule::DynamicType, "None");

// CLASS: IGESGEOM_HARRAY1OFCURVEONSURFACE
py::class_<IGESGeom_HArray1OfCurveOnSurface, opencascade::handle<IGESGeom_HArray1OfCurveOnSurface>, Standard_Transient> cls_IGESGeom_HArray1OfCurveOnSurface(mod, "IGESGeom_HArray1OfCurveOnSurface", "None", py::multiple_inheritance());

// Constructors
cls_IGESGeom_HArray1OfCurveOnSurface.def(py::init<>());
cls_IGESGeom_HArray1OfCurveOnSurface.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESGeom_HArray1OfCurveOnSurface.def(py::init<const Standard_Integer, const Standard_Integer, const IGESGeom_Array1OfCurveOnSurface::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESGeom_HArray1OfCurveOnSurface.def(py::init<const IGESGeom_Array1OfCurveOnSurface &>(), py::arg("theOther"));

// Methods
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_HArray1OfCurveOnSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_HArray1OfCurveOnSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_HArray1OfCurveOnSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_HArray1OfCurveOnSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_HArray1OfCurveOnSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_HArray1OfCurveOnSurface::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfCurveOnSurface::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESGeom_HArray1OfCurveOnSurface.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfCurveOnSurface::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESGeom_HArray1OfCurveOnSurface.def("Array1", (const IGESGeom_Array1OfCurveOnSurface & (IGESGeom_HArray1OfCurveOnSurface::*)() const) &IGESGeom_HArray1OfCurveOnSurface::Array1, "None");
cls_IGESGeom_HArray1OfCurveOnSurface.def("ChangeArray1", (IGESGeom_Array1OfCurveOnSurface & (IGESGeom_HArray1OfCurveOnSurface::*)()) &IGESGeom_HArray1OfCurveOnSurface::ChangeArray1, "None");
cls_IGESGeom_HArray1OfCurveOnSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_HArray1OfCurveOnSurface::get_type_name, "None");
cls_IGESGeom_HArray1OfCurveOnSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_HArray1OfCurveOnSurface::get_type_descriptor, "None");
cls_IGESGeom_HArray1OfCurveOnSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_HArray1OfCurveOnSurface::*)() const) &IGESGeom_HArray1OfCurveOnSurface::DynamicType, "None");

// CLASS: IGESGEOM_HARRAY1OFTRANSFORMATIONMATRIX
py::class_<IGESGeom_HArray1OfTransformationMatrix, opencascade::handle<IGESGeom_HArray1OfTransformationMatrix>, Standard_Transient> cls_IGESGeom_HArray1OfTransformationMatrix(mod, "IGESGeom_HArray1OfTransformationMatrix", "None", py::multiple_inheritance());

// Constructors
cls_IGESGeom_HArray1OfTransformationMatrix.def(py::init<>());
cls_IGESGeom_HArray1OfTransformationMatrix.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_IGESGeom_HArray1OfTransformationMatrix.def(py::init<const Standard_Integer, const Standard_Integer, const IGESGeom_Array1OfTransformationMatrix::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_IGESGeom_HArray1OfTransformationMatrix.def(py::init<const IGESGeom_Array1OfTransformationMatrix &>(), py::arg("theOther"));

// Methods
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_HArray1OfTransformationMatrix::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator delete_", (void (*)(void *)) &IGESGeom_HArray1OfTransformationMatrix::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_HArray1OfTransformationMatrix::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_HArray1OfTransformationMatrix::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_HArray1OfTransformationMatrix::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_HArray1OfTransformationMatrix::operator delete, "None", py::arg(""), py::arg(""));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfTransformationMatrix::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_IGESGeom_HArray1OfTransformationMatrix.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &IGESGeom_HArray1OfTransformationMatrix::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_IGESGeom_HArray1OfTransformationMatrix.def("Array1", (const IGESGeom_Array1OfTransformationMatrix & (IGESGeom_HArray1OfTransformationMatrix::*)() const) &IGESGeom_HArray1OfTransformationMatrix::Array1, "None");
cls_IGESGeom_HArray1OfTransformationMatrix.def("ChangeArray1", (IGESGeom_Array1OfTransformationMatrix & (IGESGeom_HArray1OfTransformationMatrix::*)()) &IGESGeom_HArray1OfTransformationMatrix::ChangeArray1, "None");
cls_IGESGeom_HArray1OfTransformationMatrix.def_static("get_type_name_", (const char * (*)()) &IGESGeom_HArray1OfTransformationMatrix::get_type_name, "None");
cls_IGESGeom_HArray1OfTransformationMatrix.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_HArray1OfTransformationMatrix::get_type_descriptor, "None");
cls_IGESGeom_HArray1OfTransformationMatrix.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_HArray1OfTransformationMatrix::*)() const) &IGESGeom_HArray1OfTransformationMatrix::DynamicType, "None");

// CLASS: IGESGEOM_LINE
py::class_<IGESGeom_Line, opencascade::handle<IGESGeom_Line>, IGESData_IGESEntity> cls_IGESGeom_Line(mod, "IGESGeom_Line", "defines IGESLine, Type <110> Form <0> in package IGESGeom A line is a bounded, connected portion of a parent straight line which consists of more than one point. A line is defined by its end points.");

// Constructors
cls_IGESGeom_Line.def(py::init<>());

// Methods
cls_IGESGeom_Line.def("Init", (void (IGESGeom_Line::*)(const gp_XYZ &, const gp_XYZ &)) &IGESGeom_Line::Init, "This method is used to set the fields of the class Line - aStart : Start point of the line - anEnd : End point of the line", py::arg("aStart"), py::arg("anEnd"));
cls_IGESGeom_Line.def("Infinite", (Standard_Integer (IGESGeom_Line::*)() const) &IGESGeom_Line::Infinite, "Returns the Infinite status i.e. the Form Number : 0 1 2");
cls_IGESGeom_Line.def("SetInfinite", (void (IGESGeom_Line::*)(const Standard_Integer)) &IGESGeom_Line::SetInfinite, "Sets the Infinite status Does nothing if <status> is not 0 1 or 2", py::arg("status"));
cls_IGESGeom_Line.def("StartPoint", (gp_Pnt (IGESGeom_Line::*)() const) &IGESGeom_Line::StartPoint, "returns the start point of the line");
cls_IGESGeom_Line.def("TransformedStartPoint", (gp_Pnt (IGESGeom_Line::*)() const) &IGESGeom_Line::TransformedStartPoint, "returns the start point of the line after applying Transf. Matrix");
cls_IGESGeom_Line.def("EndPoint", (gp_Pnt (IGESGeom_Line::*)() const) &IGESGeom_Line::EndPoint, "returns the end point of the line");
cls_IGESGeom_Line.def("TransformedEndPoint", (gp_Pnt (IGESGeom_Line::*)() const) &IGESGeom_Line::TransformedEndPoint, "returns the end point of the line after applying Transf. Matrix");
cls_IGESGeom_Line.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Line::get_type_name, "None");
cls_IGESGeom_Line.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Line::get_type_descriptor, "None");
cls_IGESGeom_Line.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Line::*)() const) &IGESGeom_Line::DynamicType, "None");

// CLASS: IGESGEOM_OFFSETCURVE
py::class_<IGESGeom_OffsetCurve, opencascade::handle<IGESGeom_OffsetCurve>, IGESData_IGESEntity> cls_IGESGeom_OffsetCurve(mod, "IGESGeom_OffsetCurve", "defines IGESOffsetCurve, Type <130> Form <0> in package IGESGeom An OffsetCurve entity contains the data necessary to determine the offset of a given curve C. This entity points to the base curve to be offset and contains offset distance and other pertinent information.");

// Constructors
cls_IGESGeom_OffsetCurve.def(py::init<>());

// Methods
cls_IGESGeom_OffsetCurve.def("Init", (void (IGESGeom_OffsetCurve::*)(const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const Standard_Integer, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const gp_XYZ &, const Standard_Real, const Standard_Real)) &IGESGeom_OffsetCurve::Init, "This method is used to set the fields of the class OffsetCurve - aBaseCurve : The curve entity to be offset - anOffsetType : Offset distance flag 1 = Single value, uniform distance 2 = Varying linearly 3 = As a specified function - aFunction : Curve entity, one coordinate of which describes offset as a function of its parameter (0 unless OffsetType = 3) - aFunctionCoord : Particular coordinate of curve describing offset as function of its parameters. (used if OffsetType = 3) - aTaperedOffsetType : Tapered offset type flag 1 = Function of arc length 2 = Function of parameter (Only used if OffsetType = 2 or 3) - offDistance1 : First offset distance (Only used if OffsetType = 1 or 2) - arcLength1 : Arc length or parameter value of first offset distance (Only used if OffsetType = 2) - offDistance2 : Second offset distance - arcLength2 : Arc length or parameter value of second offset distance (Only used if OffsetType = 2) - aNormalVec : Unit vector normal to plane containing curve to be offset - anOffsetParam : Start parameter value of offset curve - anotherOffsetParam : End parameter value of offset curve", py::arg("aBaseCurve"), py::arg("anOffsetType"), py::arg("aFunction"), py::arg("aFunctionCoord"), py::arg("aTaperedOffsetType"), py::arg("offDistance1"), py::arg("arcLength1"), py::arg("offDistance2"), py::arg("arcLength2"), py::arg("aNormalVec"), py::arg("anOffsetParam"), py::arg("anotherOffsetParam"));
cls_IGESGeom_OffsetCurve.def("BaseCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::BaseCurve, "returns the curve to be offset");
cls_IGESGeom_OffsetCurve.def("OffsetType", (Standard_Integer (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::OffsetType, "returns the offset distance flag 1 = Single value offset (uniform distance) 2 = Offset distance varying linearly 3 = Offset distance specified as a function");
cls_IGESGeom_OffsetCurve.def("Function", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::Function, "returns the function defining the offset if at all the offset is described as a function or Null Handle.");
cls_IGESGeom_OffsetCurve.def("HasFunction", (Standard_Boolean (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::HasFunction, "returns True if function defining the offset is present.");
cls_IGESGeom_OffsetCurve.def("FunctionParameter", (Standard_Integer (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::FunctionParameter, "returns particular coordinate of the curve which describes offset as a function of its parameters. (only used if OffsetType() = 3)");
cls_IGESGeom_OffsetCurve.def("TaperedOffsetType", (Standard_Integer (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::TaperedOffsetType, "returns tapered offset type flag (only used if OffsetType() = 2 or 3) 1 = Function of arc length 2 = Function of parameter");
cls_IGESGeom_OffsetCurve.def("FirstOffsetDistance", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::FirstOffsetDistance, "returns first offset distance (only used if OffsetType() = 1 or 2)");
cls_IGESGeom_OffsetCurve.def("ArcLength1", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::ArcLength1, "returns arc length or parameter value (depending on value of offset distance flag) of first offset distance (only used if OffsetType() = 2)");
cls_IGESGeom_OffsetCurve.def("SecondOffsetDistance", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::SecondOffsetDistance, "returns the second offset distance");
cls_IGESGeom_OffsetCurve.def("ArcLength2", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::ArcLength2, "returns arc length or parameter value (depending on value of offset distance flag) of second offset distance (only used if OffsetType() = 2)");
cls_IGESGeom_OffsetCurve.def("NormalVector", (gp_Vec (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::NormalVector, "returns unit vector normal to plane containing curve to be offset");
cls_IGESGeom_OffsetCurve.def("TransformedNormalVector", (gp_Vec (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::TransformedNormalVector, "returns unit vector normal to plane containing curve to be offset after applying Transf. Matrix");
cls_IGESGeom_OffsetCurve.def("Parameters", [](IGESGeom_OffsetCurve &self, Standard_Real & StartParam, Standard_Real & EndParam){ self.Parameters(StartParam, EndParam); return std::tuple<Standard_Real &, Standard_Real &>(StartParam, EndParam); }, "None", py::arg("StartParam"), py::arg("EndParam"));
cls_IGESGeom_OffsetCurve.def("StartParameter", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::StartParameter, "returns Start Parameter value of the offset curve");
cls_IGESGeom_OffsetCurve.def("EndParameter", (Standard_Real (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::EndParameter, "returns End Parameter value of the offset curve");
cls_IGESGeom_OffsetCurve.def_static("get_type_name_", (const char * (*)()) &IGESGeom_OffsetCurve::get_type_name, "None");
cls_IGESGeom_OffsetCurve.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_OffsetCurve::get_type_descriptor, "None");
cls_IGESGeom_OffsetCurve.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_OffsetCurve::*)() const) &IGESGeom_OffsetCurve::DynamicType, "None");

// CLASS: IGESGEOM_OFFSETSURFACE
py::class_<IGESGeom_OffsetSurface, opencascade::handle<IGESGeom_OffsetSurface>, IGESData_IGESEntity> cls_IGESGeom_OffsetSurface(mod, "IGESGeom_OffsetSurface", "defines IGESOffsetSurface, Type <140> Form <0> in package IGESGeom An offset surface is a surface defined in terms of an already existing surface.If S(u, v) is a parametrised regular surface and N(u, v) is a differential field of unit normal vectors defined on the whole surface, and 'd' a fixed non zero real number, then offset surface to S is a parametrised surface S(u, v) given by O(u, v) = S(u, v) + d * N(u, v); u1 <= u <= u2; v1 <= v <= v2;");

// Constructors
cls_IGESGeom_OffsetSurface.def(py::init<>());

// Methods
cls_IGESGeom_OffsetSurface.def("Init", (void (IGESGeom_OffsetSurface::*)(const gp_XYZ &, const Standard_Real, const opencascade::handle<IGESData_IGESEntity> &)) &IGESGeom_OffsetSurface::Init, "This method is used to set the fields of the class OffsetSurface - anIndicator : Offset indicator - aDistance : Offset distance - aSurface : Surface that is offset", py::arg("anIndicatoR"), py::arg("aDistance"), py::arg("aSurface"));
cls_IGESGeom_OffsetSurface.def("OffsetIndicator", (gp_Vec (IGESGeom_OffsetSurface::*)() const) &IGESGeom_OffsetSurface::OffsetIndicator, "returns the offset indicator");
cls_IGESGeom_OffsetSurface.def("TransformedOffsetIndicator", (gp_Vec (IGESGeom_OffsetSurface::*)() const) &IGESGeom_OffsetSurface::TransformedOffsetIndicator, "returns the offset indicator after applying Transf. Matrix");
cls_IGESGeom_OffsetSurface.def("Distance", (Standard_Real (IGESGeom_OffsetSurface::*)() const) &IGESGeom_OffsetSurface::Distance, "returns the distance by which surface is offset");
cls_IGESGeom_OffsetSurface.def("Surface", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_OffsetSurface::*)() const) &IGESGeom_OffsetSurface::Surface, "returns the surface that has been offset");
cls_IGESGeom_OffsetSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_OffsetSurface::get_type_name, "None");
cls_IGESGeom_OffsetSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_OffsetSurface::get_type_descriptor, "None");
cls_IGESGeom_OffsetSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_OffsetSurface::*)() const) &IGESGeom_OffsetSurface::DynamicType, "None");

// CLASS: IGESGEOM_PLANE
py::class_<IGESGeom_Plane, opencascade::handle<IGESGeom_Plane>, IGESData_IGESEntity> cls_IGESGeom_Plane(mod, "IGESGeom_Plane", "defines IGESPlane, Type <108> Form <-1,0,1> in package IGESGeom A plane entity can be used to represent unbounded plane, as well as bounded portion of a plane. In either of the above cases the plane is defined within definition space by means of coefficients A, B, C, D where at least one of A, B, C is non-zero and A * XT + B * YT + C * ZT = D");

// Constructors
cls_IGESGeom_Plane.def(py::init<>());

// Methods
cls_IGESGeom_Plane.def("Init", (void (IGESGeom_Plane::*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const opencascade::handle<IGESData_IGESEntity> &, const gp_XYZ &, const Standard_Real)) &IGESGeom_Plane::Init, "None", py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"), py::arg("aCurve"), py::arg("attach"), py::arg("aSize"));
cls_IGESGeom_Plane.def("SetFormNumber", (void (IGESGeom_Plane::*)(const Standard_Integer)) &IGESGeom_Plane::SetFormNumber, "Changes FormNumber (indicates the Type of Bound : 0 no Bound, 1 (External) Bound, -1 Hole) Remark that Init keeps this Value and must be consistent : aCurve Null if FormNumber = 0, Non-Null else Error if not in ranges [0-1] or [10-12]", py::arg("form"));
cls_IGESGeom_Plane.def("Equation", [](IGESGeom_Plane &self, Standard_Real & A, Standard_Real & B, Standard_Real & C, Standard_Real & D){ self.Equation(A, B, C, D); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(A, B, C, D); }, "None", py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"));
cls_IGESGeom_Plane.def("TransformedEquation", [](IGESGeom_Plane &self, Standard_Real & A, Standard_Real & B, Standard_Real & C, Standard_Real & D){ self.TransformedEquation(A, B, C, D); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(A, B, C, D); }, "None", py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"));
cls_IGESGeom_Plane.def("HasBoundingCurve", (Standard_Boolean (IGESGeom_Plane::*)() const) &IGESGeom_Plane::HasBoundingCurve, "returns True if there exists a bounding curve");
cls_IGESGeom_Plane.def("HasBoundingCurveHole", (Standard_Boolean (IGESGeom_Plane::*)() const) &IGESGeom_Plane::HasBoundingCurveHole, "returns True if bounding curve exists and bounded portion is negative");
cls_IGESGeom_Plane.def("BoundingCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_Plane::*)() const) &IGESGeom_Plane::BoundingCurve, "returns Optional Bounding Curve, can be positive (normal clipping) or negative (hole) according to Form Number");
cls_IGESGeom_Plane.def("HasSymbolAttach", (Standard_Boolean (IGESGeom_Plane::*)() const) &IGESGeom_Plane::HasSymbolAttach, "returns True if SymbolSize() > 0, False if SymbolSize() = 0");
cls_IGESGeom_Plane.def("SymbolAttach", (gp_Pnt (IGESGeom_Plane::*)() const) &IGESGeom_Plane::SymbolAttach, "returns (X, Y, Z) if symbol exists else returns (0, 0, 0)");
cls_IGESGeom_Plane.def("TransformedSymbolAttach", (gp_Pnt (IGESGeom_Plane::*)() const) &IGESGeom_Plane::TransformedSymbolAttach, "returns (X, Y, Z) if symbol exists after applying Transf. Matrix else returns (0, 0, 0)");
cls_IGESGeom_Plane.def("SymbolSize", (Standard_Real (IGESGeom_Plane::*)() const) &IGESGeom_Plane::SymbolSize, "Size of optional display symbol");
cls_IGESGeom_Plane.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Plane::get_type_name, "None");
cls_IGESGeom_Plane.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Plane::get_type_descriptor, "None");
cls_IGESGeom_Plane.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Plane::*)() const) &IGESGeom_Plane::DynamicType, "None");

// CLASS: IGESGEOM_POINT
py::class_<IGESGeom_Point, opencascade::handle<IGESGeom_Point>, IGESData_IGESEntity> cls_IGESGeom_Point(mod, "IGESGeom_Point", "defines IGESPoint, Type <116> Form <0> in package IGESGeom");

// Constructors
cls_IGESGeom_Point.def(py::init<>());

// Methods
cls_IGESGeom_Point.def("Init", (void (IGESGeom_Point::*)(const gp_XYZ &, const opencascade::handle<IGESBasic_SubfigureDef> &)) &IGESGeom_Point::Init, "This method is used to set the fields of the class Point - aPoint : Coordinates of point - aSymbol : SubfigureDefinition entity specifying the display symbol if there exists one, or zero", py::arg("aPoint"), py::arg("aSymbol"));
cls_IGESGeom_Point.def("Value", (gp_Pnt (IGESGeom_Point::*)() const) &IGESGeom_Point::Value, "returns co-ordinates of the point");
cls_IGESGeom_Point.def("TransformedValue", (gp_Pnt (IGESGeom_Point::*)() const) &IGESGeom_Point::TransformedValue, "returns co-ordinates of the point after applying Transf. Matrix");
cls_IGESGeom_Point.def("HasDisplaySymbol", (Standard_Boolean (IGESGeom_Point::*)() const) &IGESGeom_Point::HasDisplaySymbol, "returns True if symbol exists");
cls_IGESGeom_Point.def("DisplaySymbol", (opencascade::handle<IGESBasic_SubfigureDef> (IGESGeom_Point::*)() const) &IGESGeom_Point::DisplaySymbol, "returns display symbol entity if it exists");
cls_IGESGeom_Point.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Point::get_type_name, "None");
cls_IGESGeom_Point.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Point::get_type_descriptor, "None");
cls_IGESGeom_Point.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Point::*)() const) &IGESGeom_Point::DynamicType, "None");

// CLASS: IGESGEOM_PROTOCOL
py::class_<IGESGeom_Protocol, opencascade::handle<IGESGeom_Protocol>, IGESData_Protocol> cls_IGESGeom_Protocol(mod, "IGESGeom_Protocol", "Description of Protocol for IGESGeom");

// Constructors
cls_IGESGeom_Protocol.def(py::init<>());

// Methods
cls_IGESGeom_Protocol.def("NbResources", (Standard_Integer (IGESGeom_Protocol::*)() const) &IGESGeom_Protocol::NbResources, "Gives the count of Resource Protocol. Here, one (Protocol from IGESBasic)");
cls_IGESGeom_Protocol.def("Resource", (opencascade::handle<Interface_Protocol> (IGESGeom_Protocol::*)(const Standard_Integer) const) &IGESGeom_Protocol::Resource, "Returns a Resource, given a rank.", py::arg("num"));
cls_IGESGeom_Protocol.def("TypeNumber", (Standard_Integer (IGESGeom_Protocol::*)(const opencascade::handle<Standard_Type> &) const) &IGESGeom_Protocol::TypeNumber, "Returns a Case Number, specific of each recognized Type This Case Number is then used in Libraries : the various Modules attached to this class of Protocol must use them in accordance (for a given value of TypeNumber, they must consider the same Type as the Protocol defines)", py::arg("atype"));
cls_IGESGeom_Protocol.def_static("get_type_name_", (const char * (*)()) &IGESGeom_Protocol::get_type_name, "None");
cls_IGESGeom_Protocol.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_Protocol::get_type_descriptor, "None");
cls_IGESGeom_Protocol.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_Protocol::*)() const) &IGESGeom_Protocol::DynamicType, "None");

// CLASS: IGESGEOM_READWRITEMODULE
py::class_<IGESGeom_ReadWriteModule, opencascade::handle<IGESGeom_ReadWriteModule>, IGESData_ReadWriteModule> cls_IGESGeom_ReadWriteModule(mod, "IGESGeom_ReadWriteModule", "Defines Geom File Access Module for IGESGeom (specific parts) Specific actions concern : Read and Write Own Parameters of an IGESEntity.");

// Constructors
cls_IGESGeom_ReadWriteModule.def(py::init<>());

// Methods
cls_IGESGeom_ReadWriteModule.def("CaseIGES", (Standard_Integer (IGESGeom_ReadWriteModule::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_ReadWriteModule::CaseIGES, "Defines Case Numbers for Entities of IGESGeom", py::arg("typenum"), py::arg("formnum"));
cls_IGESGeom_ReadWriteModule.def("ReadOwnParams", (void (IGESGeom_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ReadWriteModule::ReadOwnParams, "Reads own parameters from file for an Entity of IGESGeom", py::arg("CN"), py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ReadWriteModule.def("WriteOwnParams", (void (IGESGeom_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, IGESData_IGESWriter &) const) &IGESGeom_ReadWriteModule::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("CN"), py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ReadWriteModule.def_static("get_type_name_", (const char * (*)()) &IGESGeom_ReadWriteModule::get_type_name, "None");
cls_IGESGeom_ReadWriteModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_ReadWriteModule::get_type_descriptor, "None");
cls_IGESGeom_ReadWriteModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_ReadWriteModule::*)() const) &IGESGeom_ReadWriteModule::DynamicType, "None");

// CLASS: IGESGEOM_RULEDSURFACE
py::class_<IGESGeom_RuledSurface, opencascade::handle<IGESGeom_RuledSurface>, IGESData_IGESEntity> cls_IGESGeom_RuledSurface(mod, "IGESGeom_RuledSurface", "defines IGESRuledSurface, Type <118> Form <0-1> in package IGESGeom A ruled surface is formed by moving a line connecting points of equal relative arc length or equal relative parametric value on two parametric curves from a start point to a terminate point on the curves. The parametric curves may be points, lines, circles, conics, rational B-splines, parametric splines or any parametric curve defined in the IGES specification.");

// Constructors
cls_IGESGeom_RuledSurface.def(py::init<>());

// Methods
cls_IGESGeom_RuledSurface.def("Init", (void (IGESGeom_RuledSurface::*)(const opencascade::handle<IGESData_IGESEntity> &, const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const Standard_Integer)) &IGESGeom_RuledSurface::Init, "This method is used to set the fields of the class RuledSurface - aCurve : First parametric curve - anotherCurve : Second parametric curve - aDirFlag : Direction Flag 0 = Join first to first, last to last 1 = Join first to last, last to first - aDevFlag : Developable Surface Flag 1 = Developable 0 = Possibly not", py::arg("aCurve"), py::arg("anotherCurve"), py::arg("aDirFlag"), py::arg("aDevFlag"));
cls_IGESGeom_RuledSurface.def("SetRuledByParameter", (void (IGESGeom_RuledSurface::*)(const Standard_Boolean)) &IGESGeom_RuledSurface::SetRuledByParameter, "Sets <me> to be Ruled by Parameter (Form 1) if <mode> is True, or Ruled by Length (Form 0) else", py::arg("mode"));
cls_IGESGeom_RuledSurface.def("IsRuledByParameter", (Standard_Boolean (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::IsRuledByParameter, "Returns True if Form is 1");
cls_IGESGeom_RuledSurface.def("FirstCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::FirstCurve, "returns the first curve");
cls_IGESGeom_RuledSurface.def("SecondCurve", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::SecondCurve, "returns the second curve");
cls_IGESGeom_RuledSurface.def("DirectionFlag", (Standard_Integer (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::DirectionFlag, "return the sense of direction 0 = Join first to first, last to last 1 = Join first to last, last to first");
cls_IGESGeom_RuledSurface.def("IsDevelopable", (Standard_Boolean (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::IsDevelopable, "returns True if developable else False");
cls_IGESGeom_RuledSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_RuledSurface::get_type_name, "None");
cls_IGESGeom_RuledSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_RuledSurface::get_type_descriptor, "None");
cls_IGESGeom_RuledSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_RuledSurface::*)() const) &IGESGeom_RuledSurface::DynamicType, "None");

// CLASS: IGESGEOM_SPECIFICMODULE
py::class_<IGESGeom_SpecificModule, opencascade::handle<IGESGeom_SpecificModule>, IGESData_SpecificModule> cls_IGESGeom_SpecificModule(mod, "IGESGeom_SpecificModule", "Defines Services attached to IGES Entities : Dump & OwnCorrect, for IGESGeom");

// Constructors
cls_IGESGeom_SpecificModule.def(py::init<>());

// Methods
cls_IGESGeom_SpecificModule.def("OwnDump", (void (IGESGeom_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_SpecificModule::OwnDump, "Specific Dump (own parameters) for IGESGeom", py::arg("CN"), py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));
cls_IGESGeom_SpecificModule.def("OwnCorrect", (Standard_Boolean (IGESGeom_SpecificModule::*)(const Standard_Integer, const opencascade::handle<IGESData_IGESEntity> &) const) &IGESGeom_SpecificModule::OwnCorrect, "Performs non-ambiguous Correction on Entities which support them (Boundary,ConicArc,Flash,OffsetCurve,TransformationMatrix)", py::arg("CN"), py::arg("ent"));
cls_IGESGeom_SpecificModule.def_static("get_type_name_", (const char * (*)()) &IGESGeom_SpecificModule::get_type_name, "None");
cls_IGESGeom_SpecificModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_SpecificModule::get_type_descriptor, "None");
cls_IGESGeom_SpecificModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_SpecificModule::*)() const) &IGESGeom_SpecificModule::DynamicType, "None");

// CLASS: IGESGEOM_SPLINECURVE
py::class_<IGESGeom_SplineCurve, opencascade::handle<IGESGeom_SplineCurve>, IGESData_IGESEntity> cls_IGESGeom_SplineCurve(mod, "IGESGeom_SplineCurve", "Defines IGESSplineCurve, Type <112> Form <0> in package IGESGeom The parametric spline is a sequence of parametric polynomial segments. The curve could be of the type Linear, Quadratic, Cubic, Wilson-Fowler, Modified Wilson-Fowler, B-Spline. The N polynomial segments are delimited by the break points T(1), T(2), T(3), ..., T(N+1).");

// Constructors
cls_IGESGeom_SplineCurve.def(py::init<>());

// Methods
cls_IGESGeom_SplineCurve.def("Init", (void (IGESGeom_SplineCurve::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray2OfReal> &, const opencascade::handle<TColStd_HArray2OfReal> &, const opencascade::handle<TColStd_HArray2OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &)) &IGESGeom_SplineCurve::Init, "This method is used to set the fields of the class SplineCurve - aType : Spline Type 1 = Linear 2 = Quadratic 3 = Cubic 4 = Wilson-Fowler 5 = Modified Wilson-Fowler 6 = B Spline - aDegree : Degree of continuity w.r.t. arc length - nbDimensions : Number of dimensions 2 = Planar 3 = Non-planar - allBreakPoints : Array of break points - allXPolynomials : X coordinate polynomials of segments - allYPolynomials : Y coordinate polynomials of segments - allZPolynomials : Z coordinate polynomials of segments - allXValues : Values of 1st, 2nd, 3rd derivatives of X polynomials at the terminate point and values of X at terminate point - allYValues : Values of 1st, 2nd, 3rd derivatives of Y polynomials at the terminate point and values of Y at terminate point - allZvalues : Values of 1st, 2nd, 3rd derivatives of Z polynomials at the terminate point and values of Z at terminate point raises exception if allXPolynomials, allYPolynomials & allZPolynomials are not of same size OR allXValues, allYValues & allZValues are not of size 4", py::arg("aType"), py::arg("aDegree"), py::arg("nbDimensions"), py::arg("allBreakPoints"), py::arg("allXPolynomials"), py::arg("allYPolynomials"), py::arg("allZPolynomials"), py::arg("allXvalues"), py::arg("allYvalues"), py::arg("allZvalues"));
cls_IGESGeom_SplineCurve.def("SplineType", (Standard_Integer (IGESGeom_SplineCurve::*)() const) &IGESGeom_SplineCurve::SplineType, "returns the type of Spline curve");
cls_IGESGeom_SplineCurve.def("Degree", (Standard_Integer (IGESGeom_SplineCurve::*)() const) &IGESGeom_SplineCurve::Degree, "returns the degree of the curve");
cls_IGESGeom_SplineCurve.def("NbDimensions", (Standard_Integer (IGESGeom_SplineCurve::*)() const) &IGESGeom_SplineCurve::NbDimensions, "returns the number of dimensions 2 = Planar 3 = Non-planar");
cls_IGESGeom_SplineCurve.def("NbSegments", (Standard_Integer (IGESGeom_SplineCurve::*)() const) &IGESGeom_SplineCurve::NbSegments, "returns the number of segments");
cls_IGESGeom_SplineCurve.def("BreakPoint", (Standard_Real (IGESGeom_SplineCurve::*)(const Standard_Integer) const) &IGESGeom_SplineCurve::BreakPoint, "returns breakpoint of piecewise polynomial raises exception if Index <= 0 or Index > NbSegments() + 1", py::arg("Index"));
cls_IGESGeom_SplineCurve.def("XCoordPolynomial", [](IGESGeom_SplineCurve &self, const Standard_Integer Index, Standard_Real & AX, Standard_Real & BX, Standard_Real & CX, Standard_Real & DX){ self.XCoordPolynomial(Index, AX, BX, CX, DX); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(AX, BX, CX, DX); }, "returns X coordinate polynomial for segment referred to by Index raises exception if Index <= 0 or Index > NbSegments()", py::arg("Index"), py::arg("AX"), py::arg("BX"), py::arg("CX"), py::arg("DX"));
cls_IGESGeom_SplineCurve.def("YCoordPolynomial", [](IGESGeom_SplineCurve &self, const Standard_Integer Index, Standard_Real & AY, Standard_Real & BY, Standard_Real & CY, Standard_Real & DY){ self.YCoordPolynomial(Index, AY, BY, CY, DY); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(AY, BY, CY, DY); }, "returns Y coordinate polynomial for segment referred to by Index raises exception if Index <= 0 or Index > NbSegments()", py::arg("Index"), py::arg("AY"), py::arg("BY"), py::arg("CY"), py::arg("DY"));
cls_IGESGeom_SplineCurve.def("ZCoordPolynomial", [](IGESGeom_SplineCurve &self, const Standard_Integer Index, Standard_Real & AZ, Standard_Real & BZ, Standard_Real & CZ, Standard_Real & DZ){ self.ZCoordPolynomial(Index, AZ, BZ, CZ, DZ); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(AZ, BZ, CZ, DZ); }, "returns Z coordinate polynomial for segment referred to by Index raises exception if Index <= 0 or Index > NbSegments()", py::arg("Index"), py::arg("AZ"), py::arg("BZ"), py::arg("CZ"), py::arg("DZ"));
cls_IGESGeom_SplineCurve.def("XValues", [](IGESGeom_SplineCurve &self, Standard_Real & TPX0, Standard_Real & TPX1, Standard_Real & TPX2, Standard_Real & TPX3){ self.XValues(TPX0, TPX1, TPX2, TPX3); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(TPX0, TPX1, TPX2, TPX3); }, "returns the value of X polynomial, the values of 1st, 2nd and 3rd derivatives of the X polynomial at the terminate point", py::arg("TPX0"), py::arg("TPX1"), py::arg("TPX2"), py::arg("TPX3"));
cls_IGESGeom_SplineCurve.def("YValues", [](IGESGeom_SplineCurve &self, Standard_Real & TPY0, Standard_Real & TPY1, Standard_Real & TPY2, Standard_Real & TPY3){ self.YValues(TPY0, TPY1, TPY2, TPY3); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(TPY0, TPY1, TPY2, TPY3); }, "returns the value of Y polynomial, the values of 1st, 2nd and 3rd derivatives of the Y polynomial at the termminate point", py::arg("TPY0"), py::arg("TPY1"), py::arg("TPY2"), py::arg("TPY3"));
cls_IGESGeom_SplineCurve.def("ZValues", [](IGESGeom_SplineCurve &self, Standard_Real & TPZ0, Standard_Real & TPZ1, Standard_Real & TPZ2, Standard_Real & TPZ3){ self.ZValues(TPZ0, TPZ1, TPZ2, TPZ3); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(TPZ0, TPZ1, TPZ2, TPZ3); }, "returns the value of Z polynomial, the values of 1st, 2nd and 3rd derivatives of the Z polynomial at the termminate point", py::arg("TPZ0"), py::arg("TPZ1"), py::arg("TPZ2"), py::arg("TPZ3"));
cls_IGESGeom_SplineCurve.def_static("get_type_name_", (const char * (*)()) &IGESGeom_SplineCurve::get_type_name, "None");
cls_IGESGeom_SplineCurve.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_SplineCurve::get_type_descriptor, "None");
cls_IGESGeom_SplineCurve.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_SplineCurve::*)() const) &IGESGeom_SplineCurve::DynamicType, "None");

// CLASS: IGESGEOM_SPLINESURFACE
py::class_<IGESGeom_SplineSurface, opencascade::handle<IGESGeom_SplineSurface>, IGESData_IGESEntity> cls_IGESGeom_SplineSurface(mod, "IGESGeom_SplineSurface", "defines IGESSplineSurface, Type <114> Form <0> in package IGESGeom A parametric spline surface is a grid of polynomial patches. Patch could be of the type Linear, Quadratic, Cubic, Wilson-Fowler, Modified Wilson-Fowler, B-Spline The M * N grid of patches is defined by the 'u' break points TU(1), TU(2), ..., TU(M+1) and the 'v' break points TV(1), TV(2), TV(3) ..., TV(N+1).");

// Constructors
cls_IGESGeom_SplineSurface.def(py::init<>());

// Methods
cls_IGESGeom_SplineSurface.def("Init", (void (IGESGeom_SplineSurface::*)(const Standard_Integer, const Standard_Integer, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<TColStd_HArray1OfReal> &, const opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &, const opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &, const opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &)) &IGESGeom_SplineSurface::Init, "This method is used to set the fields of the class SplineSurface - aBoundaryType : Type of Spline boundary 1 = Linear 2 = Quadratic 3 = Cubic 4 = Wilson-Fowler 5 = Modified Wilson-Fowler 6 = B-spline - aPatchType : Type of patch contained in the grid 1 = Cartesian Product 0 = Unspecified - allUBreakpoints : u values of grid lines - allVBreakpoints : v values of grid lines - allXCoeffs : X coefficients of M x N patches - allYCoeffs : Y coefficients of M x N patches - allZCoeffs : Z coefficients of M x N patches raises exception if allXCoeffs, allYCoeffs & allZCoeffs are not of the same size. or if the size of each element of the double array is not 16", py::arg("aBoundaryType"), py::arg("aPatchType"), py::arg("allUBreakpoints"), py::arg("allVBreakpoints"), py::arg("allXCoeffs"), py::arg("allYCoeffs"), py::arg("allZCoeffs"));
cls_IGESGeom_SplineSurface.def("NbUSegments", (Standard_Integer (IGESGeom_SplineSurface::*)() const) &IGESGeom_SplineSurface::NbUSegments, "returns the number of U segments");
cls_IGESGeom_SplineSurface.def("NbVSegments", (Standard_Integer (IGESGeom_SplineSurface::*)() const) &IGESGeom_SplineSurface::NbVSegments, "returns the number of V segments");
cls_IGESGeom_SplineSurface.def("BoundaryType", (Standard_Integer (IGESGeom_SplineSurface::*)() const) &IGESGeom_SplineSurface::BoundaryType, "returns boundary type");
cls_IGESGeom_SplineSurface.def("PatchType", (Standard_Integer (IGESGeom_SplineSurface::*)() const) &IGESGeom_SplineSurface::PatchType, "returns patch type");
cls_IGESGeom_SplineSurface.def("UBreakPoint", (Standard_Real (IGESGeom_SplineSurface::*)(const Standard_Integer) const) &IGESGeom_SplineSurface::UBreakPoint, "returns U break point of the grid line referred to by anIndex raises exception if anIndex <= 0 or anIndex > NbUSegments() + 1", py::arg("anIndex"));
cls_IGESGeom_SplineSurface.def("VBreakPoint", (Standard_Real (IGESGeom_SplineSurface::*)(const Standard_Integer) const) &IGESGeom_SplineSurface::VBreakPoint, "returns V break point of the grid line referred to by anIndex raises exception if anIndex <= 0 or anIndex > NbVSegments() + 1", py::arg("anIndex"));
cls_IGESGeom_SplineSurface.def("XPolynomial", (opencascade::handle<TColStd_HArray1OfReal> (IGESGeom_SplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_SplineSurface::XPolynomial, "returns X polynomial of patch referred to by anIndex1, anIndex2 raises exception if anIndex1 <= 0 or anIndex1 > NbUSegments() or anIndex2 <= 0 or anIndex2 > NbVSegments()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_SplineSurface.def("YPolynomial", (opencascade::handle<TColStd_HArray1OfReal> (IGESGeom_SplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_SplineSurface::YPolynomial, "returns Y polynomial of patch referred to by anIndex1, anIndex2 raises exception if anIndex1 <= 0 or anIndex1 > NbUSegments() or anIndex2 <= 0 or anIndex2 > NbVSegments()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_SplineSurface.def("ZPolynomial", (opencascade::handle<TColStd_HArray1OfReal> (IGESGeom_SplineSurface::*)(const Standard_Integer, const Standard_Integer) const) &IGESGeom_SplineSurface::ZPolynomial, "returns Z polynomial of patch referred to by anIndex1, anIndex2 raises exception if anIndex1 <= 0 or anIndex1 > NbUSegments() or anIndex2 <= 0 or anIndex2 > NbVSegments()", py::arg("anIndex1"), py::arg("anIndex2"));
cls_IGESGeom_SplineSurface.def("Polynomials", (void (IGESGeom_SplineSurface::*)(opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &, opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &, opencascade::handle<IGESBasic_HArray2OfHArray1OfReal> &) const) &IGESGeom_SplineSurface::Polynomials, "returns in one all the polynomial values 'in bulk' usefull for massive treatements", py::arg("XCoef"), py::arg("YCoef"), py::arg("ZCoef"));
cls_IGESGeom_SplineSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_SplineSurface::get_type_name, "None");
cls_IGESGeom_SplineSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_SplineSurface::get_type_descriptor, "None");
cls_IGESGeom_SplineSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_SplineSurface::*)() const) &IGESGeom_SplineSurface::DynamicType, "None");

// CLASS: IGESGEOM_SURFACEOFREVOLUTION
py::class_<IGESGeom_SurfaceOfRevolution, opencascade::handle<IGESGeom_SurfaceOfRevolution>, IGESData_IGESEntity> cls_IGESGeom_SurfaceOfRevolution(mod, "IGESGeom_SurfaceOfRevolution", "defines IGESSurfaceOfRevolution, Type <120> Form <0> in package IGESGeom A surface of revolution is defined by an axis of rotation a generatrix, and start and terminate rotation angles. The surface is created by rotating the generatrix about the axis of rotation through the start and terminate rotation angles.");

// Constructors
cls_IGESGeom_SurfaceOfRevolution.def(py::init<>());

// Methods
cls_IGESGeom_SurfaceOfRevolution.def("Init", (void (IGESGeom_SurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_Line> &, const opencascade::handle<IGESData_IGESEntity> &, const Standard_Real, const Standard_Real)) &IGESGeom_SurfaceOfRevolution::Init, "This method is used to set the fields of the class Line - anAxis : Axis of revolution - aGeneratrix : The curve which is revolved about the axis - aStartAngle : Start angle of the surface of revolution - anEndAngle : End angle of the surface of revolution", py::arg("anAxis"), py::arg("aGeneratrix"), py::arg("aStartAngle"), py::arg("anEndAngle"));
cls_IGESGeom_SurfaceOfRevolution.def("AxisOfRevolution", (opencascade::handle<IGESGeom_Line> (IGESGeom_SurfaceOfRevolution::*)() const) &IGESGeom_SurfaceOfRevolution::AxisOfRevolution, "returns the axis of revolution");
cls_IGESGeom_SurfaceOfRevolution.def("Generatrix", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_SurfaceOfRevolution::*)() const) &IGESGeom_SurfaceOfRevolution::Generatrix, "returns the curve which is revolved about the axis");
cls_IGESGeom_SurfaceOfRevolution.def("StartAngle", (Standard_Real (IGESGeom_SurfaceOfRevolution::*)() const) &IGESGeom_SurfaceOfRevolution::StartAngle, "returns start angle of revolution");
cls_IGESGeom_SurfaceOfRevolution.def("EndAngle", (Standard_Real (IGESGeom_SurfaceOfRevolution::*)() const) &IGESGeom_SurfaceOfRevolution::EndAngle, "returns end angle of revolution");
cls_IGESGeom_SurfaceOfRevolution.def_static("get_type_name_", (const char * (*)()) &IGESGeom_SurfaceOfRevolution::get_type_name, "None");
cls_IGESGeom_SurfaceOfRevolution.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_SurfaceOfRevolution::get_type_descriptor, "None");
cls_IGESGeom_SurfaceOfRevolution.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_SurfaceOfRevolution::*)() const) &IGESGeom_SurfaceOfRevolution::DynamicType, "None");

// CLASS: IGESGEOM_TABULATEDCYLINDER
py::class_<IGESGeom_TabulatedCylinder, opencascade::handle<IGESGeom_TabulatedCylinder>, IGESData_IGESEntity> cls_IGESGeom_TabulatedCylinder(mod, "IGESGeom_TabulatedCylinder", "defines IGESTabulatedCylinder, Type <122> Form <0> in package IGESGeom A tabulated cylinder is a surface formed by moving a line segment called generatrix parallel to itself along a curve called directrix. The curve may be a line, circular arc, conic arc, parametric spline curve, rational B-spline curve or composite curve.");

// Constructors
cls_IGESGeom_TabulatedCylinder.def(py::init<>());

// Methods
cls_IGESGeom_TabulatedCylinder.def("Init", (void (IGESGeom_TabulatedCylinder::*)(const opencascade::handle<IGESData_IGESEntity> &, const gp_XYZ &)) &IGESGeom_TabulatedCylinder::Init, "This method is used to set the fields of the class TabulatedCylinder - aDirectrix : Directrix Curve of the tabulated cylinder - anEnd : Coordinates of the terminate point of the generatrix The start point of the directrix is identical to the start point of the generatrix", py::arg("aDirectrix"), py::arg("anEnd"));
cls_IGESGeom_TabulatedCylinder.def("Directrix", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_TabulatedCylinder::*)() const) &IGESGeom_TabulatedCylinder::Directrix, "returns the directrix curve of the tabulated cylinder");
cls_IGESGeom_TabulatedCylinder.def("EndPoint", (gp_Pnt (IGESGeom_TabulatedCylinder::*)() const) &IGESGeom_TabulatedCylinder::EndPoint, "returns end point of generatrix of the tabulated cylinder");
cls_IGESGeom_TabulatedCylinder.def("TransformedEndPoint", (gp_Pnt (IGESGeom_TabulatedCylinder::*)() const) &IGESGeom_TabulatedCylinder::TransformedEndPoint, "returns end point of generatrix of the tabulated cylinder after applying Transf. Matrix");
cls_IGESGeom_TabulatedCylinder.def_static("get_type_name_", (const char * (*)()) &IGESGeom_TabulatedCylinder::get_type_name, "None");
cls_IGESGeom_TabulatedCylinder.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_TabulatedCylinder::get_type_descriptor, "None");
cls_IGESGeom_TabulatedCylinder.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_TabulatedCylinder::*)() const) &IGESGeom_TabulatedCylinder::DynamicType, "None");

// CLASS: IGESGEOM_TOOLBOUNDARY
py::class_<IGESGeom_ToolBoundary> cls_IGESGeom_ToolBoundary(mod, "IGESGeom_ToolBoundary", "Tool to work on a Boundary. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolBoundary.def(py::init<>());

// Methods
// cls_IGESGeom_ToolBoundary.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolBoundary::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolBoundary.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolBoundary::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBoundary.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolBoundary::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolBoundary.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolBoundary::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBoundary.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolBoundary::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolBoundary.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolBoundary::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolBoundary.def("ReadOwnParams", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolBoundary::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolBoundary.def("WriteOwnParams", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, IGESData_IGESWriter &) const) &IGESGeom_ToolBoundary::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolBoundary.def("OwnShared", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, Interface_EntityIterator &) const) &IGESGeom_ToolBoundary::OwnShared, "Lists the Entities shared by a Boundary <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolBoundary.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &) const) &IGESGeom_ToolBoundary::OwnCorrect, "Sets automatic unambiguous Correction on a Boundary (if BoundaryType = 0, Nullify all ParameterCurves)", py::arg("ent"));
cls_IGESGeom_ToolBoundary.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &) const) &IGESGeom_ToolBoundary::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolBoundary.def("OwnCheck", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolBoundary::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolBoundary.def("OwnCopy", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, const opencascade::handle<IGESGeom_Boundary> &, Interface_CopyTool &) const) &IGESGeom_ToolBoundary::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolBoundary.def("OwnDump", (void (IGESGeom_ToolBoundary::*)(const opencascade::handle<IGESGeom_Boundary> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolBoundary::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLBOUNDEDSURFACE
py::class_<IGESGeom_ToolBoundedSurface> cls_IGESGeom_ToolBoundedSurface(mod, "IGESGeom_ToolBoundedSurface", "Tool to work on a BoundedSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolBoundedSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolBoundedSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolBoundedSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolBoundedSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolBoundedSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBoundedSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolBoundedSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolBoundedSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolBoundedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBoundedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolBoundedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolBoundedSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolBoundedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolBoundedSurface.def("ReadOwnParams", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolBoundedSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolBoundedSurface.def("WriteOwnParams", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolBoundedSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolBoundedSurface.def("OwnShared", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolBoundedSurface::OwnShared, "Lists the Entities shared by a BoundedSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolBoundedSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &) const) &IGESGeom_ToolBoundedSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolBoundedSurface.def("OwnCheck", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolBoundedSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolBoundedSurface.def("OwnCopy", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, const opencascade::handle<IGESGeom_BoundedSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolBoundedSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolBoundedSurface.def("OwnDump", (void (IGESGeom_ToolBoundedSurface::*)(const opencascade::handle<IGESGeom_BoundedSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolBoundedSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLBSPLINECURVE
py::class_<IGESGeom_ToolBSplineCurve> cls_IGESGeom_ToolBSplineCurve(mod, "IGESGeom_ToolBSplineCurve", "Tool to work on a BSplineCurve. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolBSplineCurve.def(py::init<>());

// Methods
// cls_IGESGeom_ToolBSplineCurve.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolBSplineCurve::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolBSplineCurve.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolBSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolBSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolBSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolBSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolBSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolBSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolBSplineCurve.def("ReadOwnParams", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolBSplineCurve::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolBSplineCurve.def("WriteOwnParams", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, IGESData_IGESWriter &) const) &IGESGeom_ToolBSplineCurve::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolBSplineCurve.def("OwnShared", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, Interface_EntityIterator &) const) &IGESGeom_ToolBSplineCurve::OwnShared, "Lists the Entities shared by a BSplineCurve <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolBSplineCurve.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &) const) &IGESGeom_ToolBSplineCurve::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolBSplineCurve.def("OwnCheck", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolBSplineCurve::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolBSplineCurve.def("OwnCopy", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, const opencascade::handle<IGESGeom_BSplineCurve> &, Interface_CopyTool &) const) &IGESGeom_ToolBSplineCurve::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolBSplineCurve.def("OwnDump", (void (IGESGeom_ToolBSplineCurve::*)(const opencascade::handle<IGESGeom_BSplineCurve> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolBSplineCurve::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLBSPLINESURFACE
py::class_<IGESGeom_ToolBSplineSurface> cls_IGESGeom_ToolBSplineSurface(mod, "IGESGeom_ToolBSplineSurface", "Tool to work on a BSplineSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolBSplineSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolBSplineSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolBSplineSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolBSplineSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolBSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolBSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolBSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolBSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolBSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolBSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolBSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolBSplineSurface.def("ReadOwnParams", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolBSplineSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolBSplineSurface.def("WriteOwnParams", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolBSplineSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolBSplineSurface.def("OwnShared", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolBSplineSurface::OwnShared, "Lists the Entities shared by a BSplineSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolBSplineSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &) const) &IGESGeom_ToolBSplineSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolBSplineSurface.def("OwnCheck", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolBSplineSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolBSplineSurface.def("OwnCopy", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, const opencascade::handle<IGESGeom_BSplineSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolBSplineSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolBSplineSurface.def("OwnDump", (void (IGESGeom_ToolBSplineSurface::*)(const opencascade::handle<IGESGeom_BSplineSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolBSplineSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLCIRCULARARC
py::class_<IGESGeom_ToolCircularArc> cls_IGESGeom_ToolCircularArc(mod, "IGESGeom_ToolCircularArc", "Tool to work on a CircularArc. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolCircularArc.def(py::init<>());

// Methods
// cls_IGESGeom_ToolCircularArc.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolCircularArc::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolCircularArc.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolCircularArc::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCircularArc.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolCircularArc::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolCircularArc.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolCircularArc::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCircularArc.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolCircularArc::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolCircularArc.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolCircularArc::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolCircularArc.def("ReadOwnParams", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolCircularArc::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolCircularArc.def("WriteOwnParams", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, IGESData_IGESWriter &) const) &IGESGeom_ToolCircularArc::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolCircularArc.def("OwnShared", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, Interface_EntityIterator &) const) &IGESGeom_ToolCircularArc::OwnShared, "Lists the Entities shared by a CircularArc <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolCircularArc.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &) const) &IGESGeom_ToolCircularArc::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolCircularArc.def("OwnCheck", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolCircularArc::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolCircularArc.def("OwnCopy", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, const opencascade::handle<IGESGeom_CircularArc> &, Interface_CopyTool &) const) &IGESGeom_ToolCircularArc::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolCircularArc.def("OwnDump", (void (IGESGeom_ToolCircularArc::*)(const opencascade::handle<IGESGeom_CircularArc> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolCircularArc::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLCOMPOSITECURVE
py::class_<IGESGeom_ToolCompositeCurve> cls_IGESGeom_ToolCompositeCurve(mod, "IGESGeom_ToolCompositeCurve", "Tool to work on a CompositeCurve. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolCompositeCurve.def(py::init<>());

// Methods
// cls_IGESGeom_ToolCompositeCurve.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolCompositeCurve::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolCompositeCurve.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolCompositeCurve::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCompositeCurve.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolCompositeCurve::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolCompositeCurve.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolCompositeCurve::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCompositeCurve.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolCompositeCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolCompositeCurve.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolCompositeCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolCompositeCurve.def("ReadOwnParams", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolCompositeCurve::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolCompositeCurve.def("WriteOwnParams", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, IGESData_IGESWriter &) const) &IGESGeom_ToolCompositeCurve::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolCompositeCurve.def("OwnShared", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, Interface_EntityIterator &) const) &IGESGeom_ToolCompositeCurve::OwnShared, "Lists the Entities shared by a CompositeCurve <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolCompositeCurve.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &) const) &IGESGeom_ToolCompositeCurve::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolCompositeCurve.def("OwnCheck", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolCompositeCurve::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolCompositeCurve.def("OwnCopy", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, const opencascade::handle<IGESGeom_CompositeCurve> &, Interface_CopyTool &) const) &IGESGeom_ToolCompositeCurve::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolCompositeCurve.def("OwnDump", (void (IGESGeom_ToolCompositeCurve::*)(const opencascade::handle<IGESGeom_CompositeCurve> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolCompositeCurve::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLCONICARC
py::class_<IGESGeom_ToolConicArc> cls_IGESGeom_ToolConicArc(mod, "IGESGeom_ToolConicArc", "Tool to work on a ConicArc. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolConicArc.def(py::init<>());

// Methods
// cls_IGESGeom_ToolConicArc.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolConicArc::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolConicArc.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolConicArc::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolConicArc.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolConicArc::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolConicArc.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolConicArc::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolConicArc.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolConicArc::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolConicArc.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolConicArc::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolConicArc.def("ReadOwnParams", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolConicArc::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolConicArc.def("WriteOwnParams", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, IGESData_IGESWriter &) const) &IGESGeom_ToolConicArc::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolConicArc.def("OwnShared", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, Interface_EntityIterator &) const) &IGESGeom_ToolConicArc::OwnShared, "Lists the Entities shared by a ConicArc <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolConicArc.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &) const) &IGESGeom_ToolConicArc::OwnCorrect, "Sets automatic unambiguous Correction on a ConicArc (FormNumber recomputed according case Ellips-Parab-Hyperb)", py::arg("ent"));
cls_IGESGeom_ToolConicArc.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &) const) &IGESGeom_ToolConicArc::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolConicArc.def("OwnCheck", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolConicArc::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolConicArc.def("OwnCopy", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, const opencascade::handle<IGESGeom_ConicArc> &, Interface_CopyTool &) const) &IGESGeom_ToolConicArc::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolConicArc.def("OwnDump", (void (IGESGeom_ToolConicArc::*)(const opencascade::handle<IGESGeom_ConicArc> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolConicArc::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLCOPIOUSDATA
py::class_<IGESGeom_ToolCopiousData> cls_IGESGeom_ToolCopiousData(mod, "IGESGeom_ToolCopiousData", "Tool to work on a CopiousData. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolCopiousData.def(py::init<>());

// Methods
// cls_IGESGeom_ToolCopiousData.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolCopiousData::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolCopiousData.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolCopiousData::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCopiousData.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolCopiousData::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolCopiousData.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolCopiousData::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCopiousData.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolCopiousData::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolCopiousData.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolCopiousData::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolCopiousData.def("ReadOwnParams", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolCopiousData::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolCopiousData.def("WriteOwnParams", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, IGESData_IGESWriter &) const) &IGESGeom_ToolCopiousData::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolCopiousData.def("OwnShared", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, Interface_EntityIterator &) const) &IGESGeom_ToolCopiousData::OwnShared, "Lists the Entities shared by a CopiousData <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolCopiousData.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &) const) &IGESGeom_ToolCopiousData::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolCopiousData.def("OwnCheck", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolCopiousData::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolCopiousData.def("OwnCopy", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, const opencascade::handle<IGESGeom_CopiousData> &, Interface_CopyTool &) const) &IGESGeom_ToolCopiousData::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolCopiousData.def("OwnDump", (void (IGESGeom_ToolCopiousData::*)(const opencascade::handle<IGESGeom_CopiousData> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolCopiousData::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLCURVEONSURFACE
py::class_<IGESGeom_ToolCurveOnSurface> cls_IGESGeom_ToolCurveOnSurface(mod, "IGESGeom_ToolCurveOnSurface", "Tool to work on a CurveOnSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolCurveOnSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolCurveOnSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolCurveOnSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolCurveOnSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolCurveOnSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolCurveOnSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolCurveOnSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolCurveOnSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolCurveOnSurface.def("ReadOwnParams", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolCurveOnSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolCurveOnSurface.def("WriteOwnParams", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolCurveOnSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolCurveOnSurface.def("OwnShared", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolCurveOnSurface::OwnShared, "Lists the Entities shared by a CurveOnSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolCurveOnSurface.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &) const) &IGESGeom_ToolCurveOnSurface::OwnCorrect, "Sets automatic unambiguous Correction on a CurveOnSurface (its CurveUV must have UseFlag at 5)", py::arg("ent"));
cls_IGESGeom_ToolCurveOnSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &) const) &IGESGeom_ToolCurveOnSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolCurveOnSurface.def("OwnCheck", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolCurveOnSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolCurveOnSurface.def("OwnCopy", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, const opencascade::handle<IGESGeom_CurveOnSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolCurveOnSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolCurveOnSurface.def("OwnDump", (void (IGESGeom_ToolCurveOnSurface::*)(const opencascade::handle<IGESGeom_CurveOnSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolCurveOnSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLDIRECTION
py::class_<IGESGeom_ToolDirection> cls_IGESGeom_ToolDirection(mod, "IGESGeom_ToolDirection", "Tool to work on a Direction. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolDirection.def(py::init<>());

// Methods
// cls_IGESGeom_ToolDirection.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolDirection::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolDirection.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolDirection::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolDirection.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolDirection::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolDirection.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolDirection::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolDirection.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolDirection::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolDirection.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolDirection::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolDirection.def("ReadOwnParams", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolDirection::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolDirection.def("WriteOwnParams", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, IGESData_IGESWriter &) const) &IGESGeom_ToolDirection::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolDirection.def("OwnShared", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, Interface_EntityIterator &) const) &IGESGeom_ToolDirection::OwnShared, "Lists the Entities shared by a Direction <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolDirection.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &) const) &IGESGeom_ToolDirection::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolDirection.def("OwnCheck", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolDirection::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolDirection.def("OwnCopy", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, const opencascade::handle<IGESGeom_Direction> &, Interface_CopyTool &) const) &IGESGeom_ToolDirection::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolDirection.def("OwnDump", (void (IGESGeom_ToolDirection::*)(const opencascade::handle<IGESGeom_Direction> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolDirection::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLFLASH
py::class_<IGESGeom_ToolFlash> cls_IGESGeom_ToolFlash(mod, "IGESGeom_ToolFlash", "Tool to work on a Flash. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolFlash.def(py::init<>());

// Methods
// cls_IGESGeom_ToolFlash.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolFlash::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolFlash.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolFlash::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolFlash.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolFlash::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolFlash.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolFlash::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolFlash.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolFlash::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolFlash.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolFlash::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolFlash.def("ReadOwnParams", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolFlash::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolFlash.def("WriteOwnParams", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, IGESData_IGESWriter &) const) &IGESGeom_ToolFlash::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolFlash.def("OwnShared", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, Interface_EntityIterator &) const) &IGESGeom_ToolFlash::OwnShared, "Lists the Entities shared by a Flash <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolFlash.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &) const) &IGESGeom_ToolFlash::OwnCorrect, "Sets automatic unambiguous Correction on a Flash (LineFont in Directory Entry forced to Rank = 1)", py::arg("ent"));
cls_IGESGeom_ToolFlash.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &) const) &IGESGeom_ToolFlash::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolFlash.def("OwnCheck", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolFlash::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolFlash.def("OwnCopy", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, const opencascade::handle<IGESGeom_Flash> &, Interface_CopyTool &) const) &IGESGeom_ToolFlash::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolFlash.def("OwnDump", (void (IGESGeom_ToolFlash::*)(const opencascade::handle<IGESGeom_Flash> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolFlash::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLLINE
py::class_<IGESGeom_ToolLine> cls_IGESGeom_ToolLine(mod, "IGESGeom_ToolLine", "Tool to work on a Line. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolLine.def(py::init<>());

// Methods
// cls_IGESGeom_ToolLine.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolLine::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolLine.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolLine::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolLine.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolLine::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolLine.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolLine::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolLine.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolLine::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolLine.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolLine::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolLine.def("ReadOwnParams", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolLine::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolLine.def("WriteOwnParams", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, IGESData_IGESWriter &) const) &IGESGeom_ToolLine::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolLine.def("OwnShared", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, Interface_EntityIterator &) const) &IGESGeom_ToolLine::OwnShared, "Lists the Entities shared by a Line <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolLine.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &) const) &IGESGeom_ToolLine::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolLine.def("OwnCheck", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolLine::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolLine.def("OwnCopy", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, const opencascade::handle<IGESGeom_Line> &, Interface_CopyTool &) const) &IGESGeom_ToolLine::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolLine.def("OwnDump", (void (IGESGeom_ToolLine::*)(const opencascade::handle<IGESGeom_Line> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolLine::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLOFFSETCURVE
py::class_<IGESGeom_ToolOffsetCurve> cls_IGESGeom_ToolOffsetCurve(mod, "IGESGeom_ToolOffsetCurve", "Tool to work on a OffsetCurve. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolOffsetCurve.def(py::init<>());

// Methods
// cls_IGESGeom_ToolOffsetCurve.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolOffsetCurve::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolOffsetCurve.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolOffsetCurve::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetCurve.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolOffsetCurve::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolOffsetCurve.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolOffsetCurve::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetCurve.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolOffsetCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetCurve.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolOffsetCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolOffsetCurve.def("ReadOwnParams", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolOffsetCurve::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolOffsetCurve.def("WriteOwnParams", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, IGESData_IGESWriter &) const) &IGESGeom_ToolOffsetCurve::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolOffsetCurve.def("OwnShared", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, Interface_EntityIterator &) const) &IGESGeom_ToolOffsetCurve::OwnShared, "Lists the Entities shared by a OffsetCurve <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolOffsetCurve.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &) const) &IGESGeom_ToolOffsetCurve::OwnCorrect, "Sets automatic unambiguous Correction on a OffsetCurve (if OffsetType is not 3, OffsetFunction is cleared)", py::arg("ent"));
cls_IGESGeom_ToolOffsetCurve.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &) const) &IGESGeom_ToolOffsetCurve::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolOffsetCurve.def("OwnCheck", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolOffsetCurve::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolOffsetCurve.def("OwnCopy", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, const opencascade::handle<IGESGeom_OffsetCurve> &, Interface_CopyTool &) const) &IGESGeom_ToolOffsetCurve::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolOffsetCurve.def("OwnDump", (void (IGESGeom_ToolOffsetCurve::*)(const opencascade::handle<IGESGeom_OffsetCurve> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolOffsetCurve::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLOFFSETSURFACE
py::class_<IGESGeom_ToolOffsetSurface> cls_IGESGeom_ToolOffsetSurface(mod, "IGESGeom_ToolOffsetSurface", "Tool to work on a OffsetSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolOffsetSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolOffsetSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolOffsetSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolOffsetSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolOffsetSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolOffsetSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolOffsetSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolOffsetSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolOffsetSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolOffsetSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolOffsetSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolOffsetSurface.def("ReadOwnParams", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolOffsetSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolOffsetSurface.def("WriteOwnParams", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolOffsetSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolOffsetSurface.def("OwnShared", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolOffsetSurface::OwnShared, "Lists the Entities shared by a OffsetSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolOffsetSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &) const) &IGESGeom_ToolOffsetSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolOffsetSurface.def("OwnCheck", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolOffsetSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolOffsetSurface.def("OwnCopy", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, const opencascade::handle<IGESGeom_OffsetSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolOffsetSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolOffsetSurface.def("OwnDump", (void (IGESGeom_ToolOffsetSurface::*)(const opencascade::handle<IGESGeom_OffsetSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolOffsetSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLPLANE
py::class_<IGESGeom_ToolPlane> cls_IGESGeom_ToolPlane(mod, "IGESGeom_ToolPlane", "Tool to work on a Plane. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolPlane.def(py::init<>());

// Methods
// cls_IGESGeom_ToolPlane.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolPlane::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolPlane.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolPlane::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolPlane.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolPlane::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolPlane.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolPlane::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolPlane.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolPlane::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolPlane.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolPlane::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolPlane.def("ReadOwnParams", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolPlane::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolPlane.def("WriteOwnParams", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, IGESData_IGESWriter &) const) &IGESGeom_ToolPlane::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolPlane.def("OwnShared", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, Interface_EntityIterator &) const) &IGESGeom_ToolPlane::OwnShared, "Lists the Entities shared by a Plane <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolPlane.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &) const) &IGESGeom_ToolPlane::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolPlane.def("OwnCheck", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolPlane::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolPlane.def("OwnCopy", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, const opencascade::handle<IGESGeom_Plane> &, Interface_CopyTool &) const) &IGESGeom_ToolPlane::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolPlane.def("OwnDump", (void (IGESGeom_ToolPlane::*)(const opencascade::handle<IGESGeom_Plane> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolPlane::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLPOINT
py::class_<IGESGeom_ToolPoint> cls_IGESGeom_ToolPoint(mod, "IGESGeom_ToolPoint", "Tool to work on a Point. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolPoint.def(py::init<>());

// Methods
// cls_IGESGeom_ToolPoint.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolPoint::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolPoint.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolPoint::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolPoint.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolPoint::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolPoint.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolPoint::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolPoint.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolPoint::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolPoint.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolPoint::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolPoint.def("ReadOwnParams", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolPoint::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolPoint.def("WriteOwnParams", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, IGESData_IGESWriter &) const) &IGESGeom_ToolPoint::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolPoint.def("OwnShared", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, Interface_EntityIterator &) const) &IGESGeom_ToolPoint::OwnShared, "Lists the Entities shared by a Point <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolPoint.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &) const) &IGESGeom_ToolPoint::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolPoint.def("OwnCheck", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolPoint::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolPoint.def("OwnCopy", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, const opencascade::handle<IGESGeom_Point> &, Interface_CopyTool &) const) &IGESGeom_ToolPoint::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolPoint.def("OwnDump", (void (IGESGeom_ToolPoint::*)(const opencascade::handle<IGESGeom_Point> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolPoint::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLRULEDSURFACE
py::class_<IGESGeom_ToolRuledSurface> cls_IGESGeom_ToolRuledSurface(mod, "IGESGeom_ToolRuledSurface", "Tool to work on a RuledSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolRuledSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolRuledSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolRuledSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolRuledSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolRuledSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolRuledSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolRuledSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolRuledSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolRuledSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolRuledSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolRuledSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolRuledSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolRuledSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolRuledSurface.def("ReadOwnParams", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolRuledSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolRuledSurface.def("WriteOwnParams", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolRuledSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolRuledSurface.def("OwnShared", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolRuledSurface::OwnShared, "Lists the Entities shared by a RuledSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolRuledSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &) const) &IGESGeom_ToolRuledSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolRuledSurface.def("OwnCheck", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolRuledSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolRuledSurface.def("OwnCopy", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, const opencascade::handle<IGESGeom_RuledSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolRuledSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolRuledSurface.def("OwnDump", (void (IGESGeom_ToolRuledSurface::*)(const opencascade::handle<IGESGeom_RuledSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolRuledSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLSPLINECURVE
py::class_<IGESGeom_ToolSplineCurve> cls_IGESGeom_ToolSplineCurve(mod, "IGESGeom_ToolSplineCurve", "Tool to work on a SplineCurve. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolSplineCurve.def(py::init<>());

// Methods
// cls_IGESGeom_ToolSplineCurve.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolSplineCurve::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolSplineCurve.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolSplineCurve::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSplineCurve.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolSplineCurve::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolSplineCurve.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolSplineCurve::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSplineCurve.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolSplineCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolSplineCurve.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolSplineCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolSplineCurve.def("ReadOwnParams", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolSplineCurve::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolSplineCurve.def("WriteOwnParams", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, IGESData_IGESWriter &) const) &IGESGeom_ToolSplineCurve::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolSplineCurve.def("OwnShared", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, Interface_EntityIterator &) const) &IGESGeom_ToolSplineCurve::OwnShared, "Lists the Entities shared by a SplineCurve <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolSplineCurve.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &) const) &IGESGeom_ToolSplineCurve::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolSplineCurve.def("OwnCheck", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolSplineCurve::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolSplineCurve.def("OwnCopy", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, const opencascade::handle<IGESGeom_SplineCurve> &, Interface_CopyTool &) const) &IGESGeom_ToolSplineCurve::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolSplineCurve.def("OwnDump", (void (IGESGeom_ToolSplineCurve::*)(const opencascade::handle<IGESGeom_SplineCurve> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolSplineCurve::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLSPLINESURFACE
py::class_<IGESGeom_ToolSplineSurface> cls_IGESGeom_ToolSplineSurface(mod, "IGESGeom_ToolSplineSurface", "Tool to work on a SplineSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolSplineSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolSplineSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolSplineSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolSplineSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolSplineSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSplineSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolSplineSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolSplineSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolSplineSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSplineSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolSplineSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolSplineSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolSplineSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolSplineSurface.def("ReadOwnParams", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolSplineSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolSplineSurface.def("WriteOwnParams", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolSplineSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolSplineSurface.def("OwnShared", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolSplineSurface::OwnShared, "Lists the Entities shared by a SplineSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolSplineSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &) const) &IGESGeom_ToolSplineSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolSplineSurface.def("OwnCheck", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolSplineSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolSplineSurface.def("OwnCopy", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, const opencascade::handle<IGESGeom_SplineSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolSplineSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolSplineSurface.def("OwnDump", (void (IGESGeom_ToolSplineSurface::*)(const opencascade::handle<IGESGeom_SplineSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolSplineSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLSURFACEOFREVOLUTION
py::class_<IGESGeom_ToolSurfaceOfRevolution> cls_IGESGeom_ToolSurfaceOfRevolution(mod, "IGESGeom_ToolSurfaceOfRevolution", "Tool to work on a SurfaceOfRevolution. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolSurfaceOfRevolution.def(py::init<>());

// Methods
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolSurfaceOfRevolution::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolSurfaceOfRevolution::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolSurfaceOfRevolution::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolSurfaceOfRevolution::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolSurfaceOfRevolution::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolSurfaceOfRevolution.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolSurfaceOfRevolution::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolSurfaceOfRevolution.def("ReadOwnParams", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolSurfaceOfRevolution::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("WriteOwnParams", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, IGESData_IGESWriter &) const) &IGESGeom_ToolSurfaceOfRevolution::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("OwnShared", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, Interface_EntityIterator &) const) &IGESGeom_ToolSurfaceOfRevolution::OwnShared, "Lists the Entities shared by a SurfaceOfRevolution <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &) const) &IGESGeom_ToolSurfaceOfRevolution::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("OwnCheck", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolSurfaceOfRevolution::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("OwnCopy", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, Interface_CopyTool &) const) &IGESGeom_ToolSurfaceOfRevolution::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolSurfaceOfRevolution.def("OwnDump", (void (IGESGeom_ToolSurfaceOfRevolution::*)(const opencascade::handle<IGESGeom_SurfaceOfRevolution> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolSurfaceOfRevolution::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLTABULATEDCYLINDER
py::class_<IGESGeom_ToolTabulatedCylinder> cls_IGESGeom_ToolTabulatedCylinder(mod, "IGESGeom_ToolTabulatedCylinder", "Tool to work on a TabulatedCylinder. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolTabulatedCylinder.def(py::init<>());

// Methods
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolTabulatedCylinder::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolTabulatedCylinder::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolTabulatedCylinder::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolTabulatedCylinder::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolTabulatedCylinder::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolTabulatedCylinder.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolTabulatedCylinder::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolTabulatedCylinder.def("ReadOwnParams", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolTabulatedCylinder::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolTabulatedCylinder.def("WriteOwnParams", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, IGESData_IGESWriter &) const) &IGESGeom_ToolTabulatedCylinder::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolTabulatedCylinder.def("OwnShared", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, Interface_EntityIterator &) const) &IGESGeom_ToolTabulatedCylinder::OwnShared, "Lists the Entities shared by a TabulatedCylinder <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolTabulatedCylinder.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &) const) &IGESGeom_ToolTabulatedCylinder::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolTabulatedCylinder.def("OwnCheck", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolTabulatedCylinder::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolTabulatedCylinder.def("OwnCopy", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, const opencascade::handle<IGESGeom_TabulatedCylinder> &, Interface_CopyTool &) const) &IGESGeom_ToolTabulatedCylinder::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolTabulatedCylinder.def("OwnDump", (void (IGESGeom_ToolTabulatedCylinder::*)(const opencascade::handle<IGESGeom_TabulatedCylinder> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolTabulatedCylinder::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLTRANSFORMATIONMATRIX
py::class_<IGESGeom_ToolTransformationMatrix> cls_IGESGeom_ToolTransformationMatrix(mod, "IGESGeom_ToolTransformationMatrix", "Tool to work on a TransformationMatrix. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolTransformationMatrix.def(py::init<>());

// Methods
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolTransformationMatrix::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolTransformationMatrix::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolTransformationMatrix::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolTransformationMatrix::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolTransformationMatrix::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolTransformationMatrix.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolTransformationMatrix::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolTransformationMatrix.def("ReadOwnParams", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolTransformationMatrix::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolTransformationMatrix.def("WriteOwnParams", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, IGESData_IGESWriter &) const) &IGESGeom_ToolTransformationMatrix::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolTransformationMatrix.def("OwnShared", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, Interface_EntityIterator &) const) &IGESGeom_ToolTransformationMatrix::OwnShared, "Lists the Entities shared by a TransformationMatrix <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolTransformationMatrix.def("OwnCorrect", (Standard_Boolean (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &) const) &IGESGeom_ToolTransformationMatrix::OwnCorrect, "Sets automatic unambiguous Correction on a TransformationMatrix (FormNumber if 0 or 1, recomputed according Positive/Negative)", py::arg("ent"));
cls_IGESGeom_ToolTransformationMatrix.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &) const) &IGESGeom_ToolTransformationMatrix::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolTransformationMatrix.def("OwnCheck", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolTransformationMatrix::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolTransformationMatrix.def("OwnCopy", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, const opencascade::handle<IGESGeom_TransformationMatrix> &, Interface_CopyTool &) const) &IGESGeom_ToolTransformationMatrix::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolTransformationMatrix.def("OwnDump", (void (IGESGeom_ToolTransformationMatrix::*)(const opencascade::handle<IGESGeom_TransformationMatrix> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolTransformationMatrix::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TOOLTRIMMEDSURFACE
py::class_<IGESGeom_ToolTrimmedSurface> cls_IGESGeom_ToolTrimmedSurface(mod, "IGESGeom_ToolTrimmedSurface", "Tool to work on a TrimmedSurface. Called by various Modules (ReadWriteModule, GeneralModule, SpecificModule)");

// Constructors
cls_IGESGeom_ToolTrimmedSurface.def(py::init<>());

// Methods
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator new_", (void * (*)(size_t)) &IGESGeom_ToolTrimmedSurface::operator new, "None", py::arg("theSize"));
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator delete_", (void (*)(void *)) &IGESGeom_ToolTrimmedSurface::operator delete, "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator new[]_", (void * (*)(size_t)) &IGESGeom_ToolTrimmedSurface::operator new[], "None", py::arg("theSize"));
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator delete[]_", (void (*)(void *)) &IGESGeom_ToolTrimmedSurface::operator delete[], "None", py::arg("theAddress"));
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator new_", (void * (*)(size_t, void *)) &IGESGeom_ToolTrimmedSurface::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_IGESGeom_ToolTrimmedSurface.def_static("operator delete_", (void (*)(void *, void *)) &IGESGeom_ToolTrimmedSurface::operator delete, "None", py::arg(""), py::arg(""));
cls_IGESGeom_ToolTrimmedSurface.def("ReadOwnParams", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, const opencascade::handle<IGESData_IGESReaderData> &, IGESData_ParamReader &) const) &IGESGeom_ToolTrimmedSurface::ReadOwnParams, "Reads own parameters from file. <PR> gives access to them, <IR> detains parameter types and values", py::arg("ent"), py::arg("IR"), py::arg("PR"));
cls_IGESGeom_ToolTrimmedSurface.def("WriteOwnParams", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, IGESData_IGESWriter &) const) &IGESGeom_ToolTrimmedSurface::WriteOwnParams, "Writes own parameters to IGESWriter", py::arg("ent"), py::arg("IW"));
cls_IGESGeom_ToolTrimmedSurface.def("OwnShared", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, Interface_EntityIterator &) const) &IGESGeom_ToolTrimmedSurface::OwnShared, "Lists the Entities shared by a TrimmedSurface <ent>, from its specific (own) parameters", py::arg("ent"), py::arg("iter"));
cls_IGESGeom_ToolTrimmedSurface.def("DirChecker", (IGESData_DirChecker (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &) const) &IGESGeom_ToolTrimmedSurface::DirChecker, "Returns specific DirChecker", py::arg("ent"));
cls_IGESGeom_ToolTrimmedSurface.def("OwnCheck", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &IGESGeom_ToolTrimmedSurface::OwnCheck, "Performs Specific Semantic Check", py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_IGESGeom_ToolTrimmedSurface.def("OwnCopy", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, const opencascade::handle<IGESGeom_TrimmedSurface> &, Interface_CopyTool &) const) &IGESGeom_ToolTrimmedSurface::OwnCopy, "Copies Specific Parameters", py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_IGESGeom_ToolTrimmedSurface.def("OwnDump", (void (IGESGeom_ToolTrimmedSurface::*)(const opencascade::handle<IGESGeom_TrimmedSurface> &, const IGESData_IGESDumper &, const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &IGESGeom_ToolTrimmedSurface::OwnDump, "Dump of Specific Parameters", py::arg("ent"), py::arg("dumper"), py::arg("S"), py::arg("own"));

// CLASS: IGESGEOM_TRIMMEDSURFACE
py::class_<IGESGeom_TrimmedSurface, opencascade::handle<IGESGeom_TrimmedSurface>, IGESData_IGESEntity> cls_IGESGeom_TrimmedSurface(mod, "IGESGeom_TrimmedSurface", "defines IGESTrimmedSurface, Type <144> Form <0> in package IGESGeom A simple closed curve in Euclidean plane divides the plane in to two disjoint, open connected components; one bounded, one unbounded. The bounded one is called the interior region to the curve. Unbounded component is called exterior region to the curve. The domain of the trimmed surface is defined as the interior of the outer boundaries and exterior of the inner boundaries and includes the boundary curves.");

// Constructors
cls_IGESGeom_TrimmedSurface.def(py::init<>());

// Methods
cls_IGESGeom_TrimmedSurface.def("Init", (void (IGESGeom_TrimmedSurface::*)(const opencascade::handle<IGESData_IGESEntity> &, const Standard_Integer, const opencascade::handle<IGESGeom_CurveOnSurface> &, const opencascade::handle<IGESGeom_HArray1OfCurveOnSurface> &)) &IGESGeom_TrimmedSurface::Init, "This method is used to set the fields of the class TrimmedSurface - aSurface : Surface to be trimmed - aFlag : Outer boundary type False = The outer boundary is the boundary of rectangle D which is the domain of the surface to be trimmed True = otherwise - anOuter : Closed curve which constitutes outer boundary - allInners : Array of closed curves which constitute the inner boundary", py::arg("aSurface"), py::arg("aFlag"), py::arg("anOuter"), py::arg("allInners"));
cls_IGESGeom_TrimmedSurface.def("Surface", (opencascade::handle<IGESData_IGESEntity> (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::Surface, "returns the surface to be trimmed");
cls_IGESGeom_TrimmedSurface.def("HasOuterContour", (Standard_Boolean (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::HasOuterContour, "returns True if outer contour exists");
cls_IGESGeom_TrimmedSurface.def("OuterContour", (opencascade::handle<IGESGeom_CurveOnSurface> (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::OuterContour, "returns the outer contour of the trimmed surface");
cls_IGESGeom_TrimmedSurface.def("OuterBoundaryType", (Standard_Integer (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::OuterBoundaryType, "returns the outer contour type of the trimmed surface 0 : The outer boundary is the boundary of D 1 : otherwise");
cls_IGESGeom_TrimmedSurface.def("NbInnerContours", (Standard_Integer (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::NbInnerContours, "returns the number of inner boundaries");
cls_IGESGeom_TrimmedSurface.def("InnerContour", (opencascade::handle<IGESGeom_CurveOnSurface> (IGESGeom_TrimmedSurface::*)(const Standard_Integer) const) &IGESGeom_TrimmedSurface::InnerContour, "returns the Index'th inner contour raises exception if Index <= 0 or Index > NbInnerContours()", py::arg("Index"));
cls_IGESGeom_TrimmedSurface.def_static("get_type_name_", (const char * (*)()) &IGESGeom_TrimmedSurface::get_type_name, "None");
cls_IGESGeom_TrimmedSurface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &IGESGeom_TrimmedSurface::get_type_descriptor, "None");
cls_IGESGeom_TrimmedSurface.def("DynamicType", (const opencascade::handle<Standard_Type> & (IGESGeom_TrimmedSurface::*)() const) &IGESGeom_TrimmedSurface::DynamicType, "None");


}
