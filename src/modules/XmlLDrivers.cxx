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
#include <PCDM_RetrievalDriver.hxx>
#include <Standard_Handle.hxx>
#include <CDM_Document.hxx>
#include <TCollection_ExtendedString.hxx>
#include <CDM_Application.hxx>
#include <Standard_IStream.hxx>
#include <Storage_Data.hxx>
#include <XmlMDF_ADriverTable.hxx>
#include <Message_Messenger.hxx>
#include <Standard_Std.hxx>
#include <XmlLDrivers_DocumentRetrievalDriver.hxx>
#include <Standard_Type.hxx>
#include <XmlObjMgt_Element.hxx>
#include <Standard_TypeDef.hxx>
#include <XmlMDF_ADriver.hxx>
#include <XmlObjMgt_RRelocationTable.hxx>
#include <Standard.hxx>
#include <TCollection_AsciiString.hxx>
#include <XmlLDrivers_NamespaceDef.hxx>
#include <NCollection_Sequence.hxx>
#include <XmlLDrivers_SequenceOfNamespaceDef.hxx>
#include <PCDM_StorageDriver.hxx>
#include <Standard_OStream.hxx>
#include <XmlLDrivers_DocumentStorageDriver.hxx>
#include <XmlObjMgt_SRelocationTable.hxx>
#include <Standard_Transient.hxx>
#include <Standard_GUID.hxx>
#include <TDocStd_Application.hxx>
#include <XmlLDrivers.hxx>
#include <bind_NCollection_Sequence.hxx>

PYBIND11_MODULE(XmlLDrivers, mod) {

py::module::import("OCCT.PCDM");
py::module::import("OCCT.Standard");
py::module::import("OCCT.CDM");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.Storage");
py::module::import("OCCT.XmlMDF");
py::module::import("OCCT.Message");
py::module::import("OCCT.XmlObjMgt");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TDocStd");

// CLASS: XMLLDRIVERS_DOCUMENTRETRIEVALDRIVER
py::class_<XmlLDrivers_DocumentRetrievalDriver, opencascade::handle<XmlLDrivers_DocumentRetrievalDriver>, PCDM_RetrievalDriver> cls_XmlLDrivers_DocumentRetrievalDriver(mod, "XmlLDrivers_DocumentRetrievalDriver", "None");

// Constructors
cls_XmlLDrivers_DocumentRetrievalDriver.def(py::init<>());

// Methods
cls_XmlLDrivers_DocumentRetrievalDriver.def("CreateDocument", (opencascade::handle<CDM_Document> (XmlLDrivers_DocumentRetrievalDriver::*)()) &XmlLDrivers_DocumentRetrievalDriver::CreateDocument, "None");
cls_XmlLDrivers_DocumentRetrievalDriver.def("Read", (void (XmlLDrivers_DocumentRetrievalDriver::*)(const TCollection_ExtendedString &, const opencascade::handle<CDM_Document> &, const opencascade::handle<CDM_Application> &)) &XmlLDrivers_DocumentRetrievalDriver::Read, "None", py::arg("theFileName"), py::arg("theNewDocument"), py::arg("theApplication"));
cls_XmlLDrivers_DocumentRetrievalDriver.def("Read", (void (XmlLDrivers_DocumentRetrievalDriver::*)(Standard_IStream &, const opencascade::handle<Storage_Data> &, const opencascade::handle<CDM_Document> &, const opencascade::handle<CDM_Application> &)) &XmlLDrivers_DocumentRetrievalDriver::Read, "None", py::arg("theIStream"), py::arg("theStorageData"), py::arg("theDoc"), py::arg("theApplication"));
cls_XmlLDrivers_DocumentRetrievalDriver.def("AttributeDrivers", (opencascade::handle<XmlMDF_ADriverTable> (XmlLDrivers_DocumentRetrievalDriver::*)(const opencascade::handle<Message_Messenger> &)) &XmlLDrivers_DocumentRetrievalDriver::AttributeDrivers, "None", py::arg("theMsgDriver"));
cls_XmlLDrivers_DocumentRetrievalDriver.def_static("get_type_name_", (const char * (*)()) &XmlLDrivers_DocumentRetrievalDriver::get_type_name, "None");
cls_XmlLDrivers_DocumentRetrievalDriver.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XmlLDrivers_DocumentRetrievalDriver::get_type_descriptor, "None");
cls_XmlLDrivers_DocumentRetrievalDriver.def("DynamicType", (const opencascade::handle<Standard_Type> & (XmlLDrivers_DocumentRetrievalDriver::*)() const) &XmlLDrivers_DocumentRetrievalDriver::DynamicType, "None");

// CLASS: XMLLDRIVERS_NAMESPACEDEF
py::class_<XmlLDrivers_NamespaceDef> cls_XmlLDrivers_NamespaceDef(mod, "XmlLDrivers_NamespaceDef", "None");

// Constructors
cls_XmlLDrivers_NamespaceDef.def(py::init<>());
cls_XmlLDrivers_NamespaceDef.def(py::init<const TCollection_AsciiString &, const TCollection_AsciiString &>(), py::arg("thePrefix"), py::arg("theURI"));

// Methods
// cls_XmlLDrivers_NamespaceDef.def_static("operator new_", (void * (*)(size_t)) &XmlLDrivers_NamespaceDef::operator new, "None", py::arg("theSize"));
// cls_XmlLDrivers_NamespaceDef.def_static("operator delete_", (void (*)(void *)) &XmlLDrivers_NamespaceDef::operator delete, "None", py::arg("theAddress"));
// cls_XmlLDrivers_NamespaceDef.def_static("operator new[]_", (void * (*)(size_t)) &XmlLDrivers_NamespaceDef::operator new[], "None", py::arg("theSize"));
// cls_XmlLDrivers_NamespaceDef.def_static("operator delete[]_", (void (*)(void *)) &XmlLDrivers_NamespaceDef::operator delete[], "None", py::arg("theAddress"));
// cls_XmlLDrivers_NamespaceDef.def_static("operator new_", (void * (*)(size_t, void *)) &XmlLDrivers_NamespaceDef::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XmlLDrivers_NamespaceDef.def_static("operator delete_", (void (*)(void *, void *)) &XmlLDrivers_NamespaceDef::operator delete, "None", py::arg(""), py::arg(""));
cls_XmlLDrivers_NamespaceDef.def("Prefix", (const TCollection_AsciiString & (XmlLDrivers_NamespaceDef::*)() const) &XmlLDrivers_NamespaceDef::Prefix, "None");
cls_XmlLDrivers_NamespaceDef.def("URI", (const TCollection_AsciiString & (XmlLDrivers_NamespaceDef::*)() const) &XmlLDrivers_NamespaceDef::URI, "None");

// TYPEDEF: XMLLDRIVERS_SEQUENCEOFNAMESPACEDEF
bind_NCollection_Sequence<XmlLDrivers_NamespaceDef>(mod, "XmlLDrivers_SequenceOfNamespaceDef", py::module_local(false));

// CLASS: XMLLDRIVERS_DOCUMENTSTORAGEDRIVER
py::class_<XmlLDrivers_DocumentStorageDriver, opencascade::handle<XmlLDrivers_DocumentStorageDriver>, PCDM_StorageDriver> cls_XmlLDrivers_DocumentStorageDriver(mod, "XmlLDrivers_DocumentStorageDriver", "None");

// Constructors
cls_XmlLDrivers_DocumentStorageDriver.def(py::init<const TCollection_ExtendedString &>(), py::arg("theCopyright"));

// Methods
cls_XmlLDrivers_DocumentStorageDriver.def("Write", (void (XmlLDrivers_DocumentStorageDriver::*)(const opencascade::handle<CDM_Document> &, const TCollection_ExtendedString &)) &XmlLDrivers_DocumentStorageDriver::Write, "None", py::arg("theDocument"), py::arg("theFileName"));
cls_XmlLDrivers_DocumentStorageDriver.def("Write", (void (XmlLDrivers_DocumentStorageDriver::*)(const opencascade::handle<CDM_Document> &, Standard_OStream &)) &XmlLDrivers_DocumentStorageDriver::Write, "None", py::arg("theDocument"), py::arg("theOStream"));
cls_XmlLDrivers_DocumentStorageDriver.def("AttributeDrivers", (opencascade::handle<XmlMDF_ADriverTable> (XmlLDrivers_DocumentStorageDriver::*)(const opencascade::handle<Message_Messenger> &)) &XmlLDrivers_DocumentStorageDriver::AttributeDrivers, "None", py::arg("theMsgDriver"));
cls_XmlLDrivers_DocumentStorageDriver.def_static("get_type_name_", (const char * (*)()) &XmlLDrivers_DocumentStorageDriver::get_type_name, "None");
cls_XmlLDrivers_DocumentStorageDriver.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XmlLDrivers_DocumentStorageDriver::get_type_descriptor, "None");
cls_XmlLDrivers_DocumentStorageDriver.def("DynamicType", (const opencascade::handle<Standard_Type> & (XmlLDrivers_DocumentStorageDriver::*)() const) &XmlLDrivers_DocumentStorageDriver::DynamicType, "None");

// CLASS: XMLLDRIVERS
py::class_<XmlLDrivers> cls_XmlLDrivers(mod, "XmlLDrivers", "None");

// Methods
cls_XmlLDrivers.def_static("Factory_", (const opencascade::handle<Standard_Transient> & (*)(const Standard_GUID &)) &XmlLDrivers::Factory, "None", py::arg("theGUID"));
cls_XmlLDrivers.def_static("CreationDate_", (TCollection_AsciiString (*)()) &XmlLDrivers::CreationDate, "None");
cls_XmlLDrivers.def_static("DefineFormat_", (void (*)(const opencascade::handle<TDocStd_Application> &)) &XmlLDrivers::DefineFormat, "Defines format 'XmlLOcaf' and registers its read and write drivers in the specified application", py::arg("theApp"));
cls_XmlLDrivers.def_static("AttributeDrivers_", (opencascade::handle<XmlMDF_ADriverTable> (*)(const opencascade::handle<Message_Messenger> &)) &XmlLDrivers::AttributeDrivers, "None", py::arg("theMsgDriver"));
cls_XmlLDrivers.def_static("StorageVersion_", (int (*)()) &XmlLDrivers::StorageVersion, "None");


}
