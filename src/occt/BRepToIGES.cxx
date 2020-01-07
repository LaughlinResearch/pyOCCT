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
#include <IGESData_IGESModel.hxx>
#include <Standard_TypeDef.hxx>
#include <Transfer_FinderProcess.hxx>
#include <IGESData_IGESEntity.hxx>
#include <TopoDS_Shape.hxx>
#include <Standard_Transient.hxx>
#include <BRepToIGES_BREntity.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Face.hxx>
#include <BRepToIGES_BRShell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Compound.hxx>
#include <BRepToIGES_BRSolid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <Geom_Surface.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Pnt2d.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepToIGES_BRWire.hxx>

PYBIND11_MODULE(BRepToIGES, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.IGESData");
py::module::import("OCCT.Transfer");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.Geom");
py::module::import("OCCT.TopLoc");
py::module::import("OCCT.gp");

// CLASS: BREPTOIGES_BRENTITY
py::class_<BRepToIGES_BREntity> cls_BRepToIGES_BREntity(mod, "BRepToIGES_BREntity", "provides methods to transfer BRep entity from CASCADE to IGES.");

// Constructors
cls_BRepToIGES_BREntity.def(py::init<>());

// Methods
// cls_BRepToIGES_BREntity.def_static("operator new_", (void * (*)(size_t)) &BRepToIGES_BREntity::operator new, "None", py::arg("theSize"));
// cls_BRepToIGES_BREntity.def_static("operator delete_", (void (*)(void *)) &BRepToIGES_BREntity::operator delete, "None", py::arg("theAddress"));
// cls_BRepToIGES_BREntity.def_static("operator new[]_", (void * (*)(size_t)) &BRepToIGES_BREntity::operator new[], "None", py::arg("theSize"));
// cls_BRepToIGES_BREntity.def_static("operator delete[]_", (void (*)(void *)) &BRepToIGES_BREntity::operator delete[], "None", py::arg("theAddress"));
// cls_BRepToIGES_BREntity.def_static("operator new_", (void * (*)(size_t, void *)) &BRepToIGES_BREntity::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepToIGES_BREntity.def_static("operator delete_", (void (*)(void *, void *)) &BRepToIGES_BREntity::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepToIGES_BREntity.def("Init", (void (BRepToIGES_BREntity::*)()) &BRepToIGES_BREntity::Init, "Initializes the field of the tool BREntity with default creating values.");
cls_BRepToIGES_BREntity.def("SetModel", (void (BRepToIGES_BREntity::*)(const opencascade::handle<IGESData_IGESModel> &)) &BRepToIGES_BREntity::SetModel, "Set the value of 'TheModel'", py::arg("model"));
cls_BRepToIGES_BREntity.def("GetModel", (opencascade::handle<IGESData_IGESModel> (BRepToIGES_BREntity::*)() const) &BRepToIGES_BREntity::GetModel, "Returns the value of 'TheModel'");
cls_BRepToIGES_BREntity.def("GetUnit", (Standard_Real (BRepToIGES_BREntity::*)() const) &BRepToIGES_BREntity::GetUnit, "Returns the value of the UnitFlag of the header of the model in meters.");
cls_BRepToIGES_BREntity.def("SetTransferProcess", (void (BRepToIGES_BREntity::*)(const opencascade::handle<Transfer_FinderProcess> &)) &BRepToIGES_BREntity::SetTransferProcess, "Set the value of 'TheMap'", py::arg("TP"));
cls_BRepToIGES_BREntity.def("GetTransferProcess", (opencascade::handle<Transfer_FinderProcess> (BRepToIGES_BREntity::*)() const) &BRepToIGES_BREntity::GetTransferProcess, "Returns the value of 'TheMap'");
cls_BRepToIGES_BREntity.def("TransferShape", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BREntity::*)(const TopoDS_Shape &)) &BRepToIGES_BREntity::TransferShape, "Returns the result of the transfert of any Shape If the transfer has failed, this member return a NullEntity.", py::arg("start"));
cls_BRepToIGES_BREntity.def("AddFail", (void (BRepToIGES_BREntity::*)(const TopoDS_Shape &, const Standard_CString)) &BRepToIGES_BREntity::AddFail, "Records a new Fail message", py::arg("start"), py::arg("amess"));
cls_BRepToIGES_BREntity.def("AddWarning", (void (BRepToIGES_BREntity::*)(const TopoDS_Shape &, const Standard_CString)) &BRepToIGES_BREntity::AddWarning, "Records a new Warning message", py::arg("start"), py::arg("amess"));
cls_BRepToIGES_BREntity.def("AddFail", (void (BRepToIGES_BREntity::*)(const opencascade::handle<Standard_Transient> &, const Standard_CString)) &BRepToIGES_BREntity::AddFail, "Records a new Fail message", py::arg("start"), py::arg("amess"));
cls_BRepToIGES_BREntity.def("AddWarning", (void (BRepToIGES_BREntity::*)(const opencascade::handle<Standard_Transient> &, const Standard_CString)) &BRepToIGES_BREntity::AddWarning, "Records a new Warning message", py::arg("start"), py::arg("amess"));
cls_BRepToIGES_BREntity.def("HasShapeResult", (Standard_Boolean (BRepToIGES_BREntity::*)(const TopoDS_Shape &) const) &BRepToIGES_BREntity::HasShapeResult, "Returns True if start was already treated and has a result in 'TheMap' else returns False.", py::arg("start"));
cls_BRepToIGES_BREntity.def("GetShapeResult", (opencascade::handle<Standard_Transient> (BRepToIGES_BREntity::*)(const TopoDS_Shape &) const) &BRepToIGES_BREntity::GetShapeResult, "Returns the result of the transfer of the Shape 'start' contained in 'TheMap' . (if HasShapeResult is True).", py::arg("start"));
cls_BRepToIGES_BREntity.def("SetShapeResult", (void (BRepToIGES_BREntity::*)(const TopoDS_Shape &, const opencascade::handle<Standard_Transient> &)) &BRepToIGES_BREntity::SetShapeResult, "set in 'TheMap' the result of the transfer of the Shape 'start'.", py::arg("start"), py::arg("result"));
cls_BRepToIGES_BREntity.def("HasShapeResult", (Standard_Boolean (BRepToIGES_BREntity::*)(const opencascade::handle<Standard_Transient> &) const) &BRepToIGES_BREntity::HasShapeResult, "Returns True if start was already treated and has a result in 'TheMap' else returns False.", py::arg("start"));
cls_BRepToIGES_BREntity.def("GetShapeResult", (opencascade::handle<Standard_Transient> (BRepToIGES_BREntity::*)(const opencascade::handle<Standard_Transient> &) const) &BRepToIGES_BREntity::GetShapeResult, "Returns the result of the transfer of the Transient 'start' contained in 'TheMap' . (if HasShapeResult is True).", py::arg("start"));
cls_BRepToIGES_BREntity.def("SetShapeResult", (void (BRepToIGES_BREntity::*)(const opencascade::handle<Standard_Transient> &, const opencascade::handle<Standard_Transient> &)) &BRepToIGES_BREntity::SetShapeResult, "set in 'TheMap' the result of the transfer of the Transient 'start'.", py::arg("start"), py::arg("result"));
cls_BRepToIGES_BREntity.def("GetConvertSurfaceMode", (Standard_Boolean (BRepToIGES_BREntity::*)() const) &BRepToIGES_BREntity::GetConvertSurfaceMode, "Returns mode for conversion of surfaces (value of parameter write.convertsurface.mode)");
cls_BRepToIGES_BREntity.def("GetPCurveMode", (Standard_Boolean (BRepToIGES_BREntity::*)() const) &BRepToIGES_BREntity::GetPCurveMode, "Returns mode for writing pcurves (value of parameter write.surfacecurve.mode)");

// CLASS: BREPTOIGES_BRSHELL
py::class_<BRepToIGES_BRShell, BRepToIGES_BREntity> cls_BRepToIGES_BRShell(mod, "BRepToIGES_BRShell", "This class implements the transfer of Shape Entities from Geom To IGES. These can be : . Vertex . Edge . Wire");

// Constructors
cls_BRepToIGES_BRShell.def(py::init<>());
cls_BRepToIGES_BRShell.def(py::init<const BRepToIGES_BREntity &>(), py::arg("BR"));

// Methods
// cls_BRepToIGES_BRShell.def_static("operator new_", (void * (*)(size_t)) &BRepToIGES_BRShell::operator new, "None", py::arg("theSize"));
// cls_BRepToIGES_BRShell.def_static("operator delete_", (void (*)(void *)) &BRepToIGES_BRShell::operator delete, "None", py::arg("theAddress"));
// cls_BRepToIGES_BRShell.def_static("operator new[]_", (void * (*)(size_t)) &BRepToIGES_BRShell::operator new[], "None", py::arg("theSize"));
// cls_BRepToIGES_BRShell.def_static("operator delete[]_", (void (*)(void *)) &BRepToIGES_BRShell::operator delete[], "None", py::arg("theAddress"));
// cls_BRepToIGES_BRShell.def_static("operator new_", (void * (*)(size_t, void *)) &BRepToIGES_BRShell::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepToIGES_BRShell.def_static("operator delete_", (void (*)(void *, void *)) &BRepToIGES_BRShell::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepToIGES_BRShell.def("TransferShell", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRShell::*)(const TopoDS_Shape &)) &BRepToIGES_BRShell::TransferShell, "Transfert an Shape entity from TopoDS to IGES This entity must be a Face or a Shell. If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRShell.def("TransferShell", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRShell::*)(const TopoDS_Shell &)) &BRepToIGES_BRShell::TransferShell, "Transfert an Shell entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRShell.def("TransferFace", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRShell::*)(const TopoDS_Face &)) &BRepToIGES_BRShell::TransferFace, "Transfert a Face entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));

// CLASS: BREPTOIGES_BRSOLID
py::class_<BRepToIGES_BRSolid, BRepToIGES_BREntity> cls_BRepToIGES_BRSolid(mod, "BRepToIGES_BRSolid", "This class implements the transfer of Shape Entities from Geom To IGES. These can be : . Vertex . Edge . Wire");

// Constructors
cls_BRepToIGES_BRSolid.def(py::init<>());
cls_BRepToIGES_BRSolid.def(py::init<const BRepToIGES_BREntity &>(), py::arg("BR"));

// Methods
// cls_BRepToIGES_BRSolid.def_static("operator new_", (void * (*)(size_t)) &BRepToIGES_BRSolid::operator new, "None", py::arg("theSize"));
// cls_BRepToIGES_BRSolid.def_static("operator delete_", (void (*)(void *)) &BRepToIGES_BRSolid::operator delete, "None", py::arg("theAddress"));
// cls_BRepToIGES_BRSolid.def_static("operator new[]_", (void * (*)(size_t)) &BRepToIGES_BRSolid::operator new[], "None", py::arg("theSize"));
// cls_BRepToIGES_BRSolid.def_static("operator delete[]_", (void (*)(void *)) &BRepToIGES_BRSolid::operator delete[], "None", py::arg("theAddress"));
// cls_BRepToIGES_BRSolid.def_static("operator new_", (void * (*)(size_t, void *)) &BRepToIGES_BRSolid::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepToIGES_BRSolid.def_static("operator delete_", (void (*)(void *, void *)) &BRepToIGES_BRSolid::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepToIGES_BRSolid.def("TransferSolid", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRSolid::*)(const TopoDS_Shape &)) &BRepToIGES_BRSolid::TransferSolid, "Transfert a Shape entity from TopoDS to IGES this entity must be a Solid or a CompSolid or a Compound. If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRSolid.def("TransferSolid", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRSolid::*)(const TopoDS_Solid &)) &BRepToIGES_BRSolid::TransferSolid, "Transfert a Solid entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRSolid.def("TransferCompSolid", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRSolid::*)(const TopoDS_CompSolid &)) &BRepToIGES_BRSolid::TransferCompSolid, "Transfert an CompSolid entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRSolid.def("TransferCompound", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRSolid::*)(const TopoDS_Compound &)) &BRepToIGES_BRSolid::TransferCompound, "Transfert a Compound entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));

// CLASS: BREPTOIGES_BRWIRE
py::class_<BRepToIGES_BRWire, BRepToIGES_BREntity> cls_BRepToIGES_BRWire(mod, "BRepToIGES_BRWire", "This class implements the transfer of Shape Entities from Geom To IGES. These can be : . Vertex . Edge . Wire");

// Constructors
cls_BRepToIGES_BRWire.def(py::init<>());
cls_BRepToIGES_BRWire.def(py::init<const BRepToIGES_BREntity &>(), py::arg("BR"));

// Methods
// cls_BRepToIGES_BRWire.def_static("operator new_", (void * (*)(size_t)) &BRepToIGES_BRWire::operator new, "None", py::arg("theSize"));
// cls_BRepToIGES_BRWire.def_static("operator delete_", (void (*)(void *)) &BRepToIGES_BRWire::operator delete, "None", py::arg("theAddress"));
// cls_BRepToIGES_BRWire.def_static("operator new[]_", (void * (*)(size_t)) &BRepToIGES_BRWire::operator new[], "None", py::arg("theSize"));
// cls_BRepToIGES_BRWire.def_static("operator delete[]_", (void (*)(void *)) &BRepToIGES_BRWire::operator delete[], "None", py::arg("theAddress"));
// cls_BRepToIGES_BRWire.def_static("operator new_", (void * (*)(size_t, void *)) &BRepToIGES_BRWire::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepToIGES_BRWire.def_static("operator delete_", (void (*)(void *, void *)) &BRepToIGES_BRWire::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepToIGES_BRWire.def("TransferWire", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Shape &)) &BRepToIGES_BRWire::TransferWire, "Transfert a Shape entity from TopoDS to IGES this entity must be a Vertex or an Edge or a Wire. If this Entity could not be converted, this member returns a NullEntity.", py::arg("start"));
cls_BRepToIGES_BRWire.def("TransferVertex", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Vertex &)) &BRepToIGES_BRWire::TransferVertex, "Transfert a Vertex entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("myvertex"));
cls_BRepToIGES_BRWire.def("TransferVertex", [](BRepToIGES_BRWire &self, const TopoDS_Vertex & myvertex, const TopoDS_Edge & myedge, Standard_Real & parameter){ opencascade::handle<IGESData_IGESEntity> rv = self.TransferVertex(myvertex, myedge, parameter); return std::tuple<opencascade::handle<IGESData_IGESEntity>, Standard_Real &>(rv, parameter); }, "Transfert a Vertex entity on an Edge from TopoDS to IGES Returns the parameter of myvertex on myedge. If this Entity could not be converted, this member returns a NullEntity.", py::arg("myvertex"), py::arg("myedge"), py::arg("parameter"));
cls_BRepToIGES_BRWire.def("TransferVertex", [](BRepToIGES_BRWire &self, const TopoDS_Vertex & myvertex, const TopoDS_Edge & myedge, const TopoDS_Face & myface, Standard_Real & parameter){ opencascade::handle<IGESData_IGESEntity> rv = self.TransferVertex(myvertex, myedge, myface, parameter); return std::tuple<opencascade::handle<IGESData_IGESEntity>, Standard_Real &>(rv, parameter); }, "Transfert a Vertex entity of an edge on a Face from TopoDS to IGES Returns the parameter of myvertex on the pcurve of myedge on myface If this Entity could not be converted, this member returns a NullEntity.", py::arg("myvertex"), py::arg("myedge"), py::arg("myface"), py::arg("parameter"));
cls_BRepToIGES_BRWire.def("TransferVertex", [](BRepToIGES_BRWire &self, const TopoDS_Vertex & myvertex, const TopoDS_Edge & myedge, const opencascade::handle<Geom_Surface> & mysurface, const TopLoc_Location & myloc, Standard_Real & parameter){ opencascade::handle<IGESData_IGESEntity> rv = self.TransferVertex(myvertex, myedge, mysurface, myloc, parameter); return std::tuple<opencascade::handle<IGESData_IGESEntity>, Standard_Real &>(rv, parameter); }, "Transfert a Vertex entity of an edge on a Surface from TopoDS to IGES Returns the parameter of myvertex on the pcurve of myedge on mysurface If this Entity could not be converted, this member returns a NullEntity.", py::arg("myvertex"), py::arg("myedge"), py::arg("mysurface"), py::arg("myloc"), py::arg("parameter"));
cls_BRepToIGES_BRWire.def("TransferVertex", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Vertex &, const TopoDS_Face &, gp_Pnt2d &)) &BRepToIGES_BRWire::TransferVertex, "Transfert a Vertex entity on a Face from TopoDS to IGES Returns the parameters of myvertex on myface If this Entity could not be converted, this member returns a NullEntity.", py::arg("myvertex"), py::arg("myface"), py::arg("mypoint"));
cls_BRepToIGES_BRWire.def("TransferEdge", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Edge &, const Standard_Boolean)) &BRepToIGES_BRWire::TransferEdge, "Transfert an Edge entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity. isBRepMode indicates if write mode is BRep (True when called from BRepToIGESBRep and False when from BRepToIGES) If edge is REVERSED and isBRepMode is False 3D edge curve is reversed, otherwise, not.", py::arg("myedge"), py::arg("isBRepMode"));
cls_BRepToIGES_BRWire.def("TransferEdge", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Edge &, const TopoDS_Face &, const Standard_Real, const Standard_Boolean)) &BRepToIGES_BRWire::TransferEdge, "Transfert an Edge entity on a Face from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity. isBRepMode indicates if write mode is BRep (True when called from BRepToIGESBRep and False when from BRepToIGES) passing into Transform2dCurve()", py::arg("myedge"), py::arg("myface"), py::arg("length"), py::arg("isBRepMode"));
cls_BRepToIGES_BRWire.def("TransferWire", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Wire &)) &BRepToIGES_BRWire::TransferWire, "Transfert a Wire entity from TopoDS to IGES If this Entity could not be converted, this member returns a NullEntity.", py::arg("mywire"));
cls_BRepToIGES_BRWire.def("TransferWire", (opencascade::handle<IGESData_IGESEntity> (BRepToIGES_BRWire::*)(const TopoDS_Wire &, const TopoDS_Face &, opencascade::handle<IGESData_IGESEntity> &, const Standard_Real)) &BRepToIGES_BRWire::TransferWire, "Transfert a Wire entity from TopoDS to IGES. Returns the curve associated to mywire in the parametric space of myface. If this Entity could not be converted, this member returns a NullEntity. Parameter IsRevol is not used anymore", py::arg("mywire"), py::arg("myface"), py::arg("mycurve2d"), py::arg("length"));


}
