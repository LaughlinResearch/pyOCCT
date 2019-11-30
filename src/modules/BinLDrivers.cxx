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
#include <BinLDrivers_Marker.hxx>
#include <Standard.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>
#include <BinLDrivers_DocumentSection.hxx>
#include <Standard_IStream.hxx>
#include <NCollection_Vector.hxx>
#include <BinLDrivers_VectorOfDocumentSection.hxx>
#include <PCDM_RetrievalDriver.hxx>
#include <Standard_Handle.hxx>
#include <CDM_Document.hxx>
#include <TCollection_ExtendedString.hxx>
#include <CDM_Application.hxx>
#include <Storage_Data.hxx>
#include <BinMDF_ADriverTable.hxx>
#include <Message_Messenger.hxx>
#include <Standard_Std.hxx>
#include <BinLDrivers_DocumentRetrievalDriver.hxx>
#include <Standard_Type.hxx>
#include <TDF_Label.hxx>
#include <Storage_Position.hxx>
#include <BinObjMgt_RRelocationTable.hxx>
#include <BinObjMgt_Persistent.hxx>
#include <TColStd_MapOfInteger.hxx>
#include <PCDM_StorageDriver.hxx>
#include <BinLDrivers_DocumentStorageDriver.hxx>
#include <BinObjMgt_SRelocationTable.hxx>
#include <TDF_LabelList.hxx>
#include <TColStd_MapOfTransient.hxx>
#include <TColStd_IndexedMapOfTransient.hxx>
#include <Standard_Transient.hxx>
#include <Standard_GUID.hxx>
#include <TDocStd_Application.hxx>
#include <BinLDrivers.hxx>
#include <bind_NCollection_Vector.hxx>

PYBIND11_MODULE(BinLDrivers, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.PCDM");
py::module::import("OCCT.CDM");
py::module::import("OCCT.Storage");
py::module::import("OCCT.BinMDF");
py::module::import("OCCT.Message");
py::module::import("OCCT.TDF");
py::module::import("OCCT.BinObjMgt");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.TDocStd");

// ENUM: BINLDRIVERS_MARKER
py::enum_<BinLDrivers_Marker>(mod, "BinLDrivers_Marker", "None")
	.value("BinLDrivers_ENDATTRLIST", BinLDrivers_Marker::BinLDrivers_ENDATTRLIST)
	.value("BinLDrivers_ENDLABEL", BinLDrivers_Marker::BinLDrivers_ENDLABEL)
	.export_values();


// CLASS: BINLDRIVERS_DOCUMENTSECTION
py::class_<BinLDrivers_DocumentSection> cls_BinLDrivers_DocumentSection(mod, "BinLDrivers_DocumentSection", "More or less independent part of the saved/restored document that is distinct from OCAF data themselves but may be referred by them.");

// Constructors
cls_BinLDrivers_DocumentSection.def(py::init<>());
cls_BinLDrivers_DocumentSection.def(py::init<const TCollection_AsciiString &, const Standard_Boolean>(), py::arg("theName"), py::arg("isPostRead"));

// Methods
// cls_BinLDrivers_DocumentSection.def_static("operator new_", (void * (*)(size_t)) &BinLDrivers_DocumentSection::operator new, "None", py::arg("theSize"));
// cls_BinLDrivers_DocumentSection.def_static("operator delete_", (void (*)(void *)) &BinLDrivers_DocumentSection::operator delete, "None", py::arg("theAddress"));
// cls_BinLDrivers_DocumentSection.def_static("operator new[]_", (void * (*)(size_t)) &BinLDrivers_DocumentSection::operator new[], "None", py::arg("theSize"));
// cls_BinLDrivers_DocumentSection.def_static("operator delete[]_", (void (*)(void *)) &BinLDrivers_DocumentSection::operator delete[], "None", py::arg("theAddress"));
// cls_BinLDrivers_DocumentSection.def_static("operator new_", (void * (*)(size_t, void *)) &BinLDrivers_DocumentSection::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BinLDrivers_DocumentSection.def_static("operator delete_", (void (*)(void *, void *)) &BinLDrivers_DocumentSection::operator delete, "None", py::arg(""), py::arg(""));
cls_BinLDrivers_DocumentSection.def("Name", (const TCollection_AsciiString & (BinLDrivers_DocumentSection::*)() const) &BinLDrivers_DocumentSection::Name, "Query the name of the section.");
cls_BinLDrivers_DocumentSection.def("IsPostRead", (Standard_Boolean (BinLDrivers_DocumentSection::*)() const) &BinLDrivers_DocumentSection::IsPostRead, "Query the status: if the Section should be read after OCAF; False means that the Section is read before starting to read OCAF data.");
cls_BinLDrivers_DocumentSection.def("Offset", (uint64_t (BinLDrivers_DocumentSection::*)() const) &BinLDrivers_DocumentSection::Offset, "Query the offset of the section in the persistent file");
cls_BinLDrivers_DocumentSection.def("SetOffset", (void (BinLDrivers_DocumentSection::*)(const uint64_t)) &BinLDrivers_DocumentSection::SetOffset, "Set the offset of the section in the persistent file", py::arg("theOffset"));
cls_BinLDrivers_DocumentSection.def("Length", (uint64_t (BinLDrivers_DocumentSection::*)() const) &BinLDrivers_DocumentSection::Length, "Query the length of the section in the persistent file");
cls_BinLDrivers_DocumentSection.def("SetLength", (void (BinLDrivers_DocumentSection::*)(const uint64_t)) &BinLDrivers_DocumentSection::SetLength, "Set the length of the section in the persistent file", py::arg("theLength"));
cls_BinLDrivers_DocumentSection.def("WriteTOC", (void (BinLDrivers_DocumentSection::*)(Standard_OStream &)) &BinLDrivers_DocumentSection::WriteTOC, "Create a Section entry in the Document TOC (list of sections)", py::arg("theOS"));
cls_BinLDrivers_DocumentSection.def("Write", (void (BinLDrivers_DocumentSection::*)(Standard_OStream &, const uint64_t)) &BinLDrivers_DocumentSection::Write, "Save Offset and Length data into the Section entry in the Document TOC (list of sections)", py::arg("theOS"), py::arg("theOffset"));
cls_BinLDrivers_DocumentSection.def_static("ReadTOC_", (void (*)(BinLDrivers_DocumentSection &, Standard_IStream &, const Standard_Integer)) &BinLDrivers_DocumentSection::ReadTOC, "Fill a DocumentSection instance from the data that are read from TOC.", py::arg("theSection"), py::arg("theIS"), py::arg("theDocFormatVersion"));

// TYPEDEF: BINLDRIVERS_VECTOROFDOCUMENTSECTION
bind_NCollection_Vector<BinLDrivers_DocumentSection>(mod, "BinLDrivers_VectorOfDocumentSection", py::module_local(false));

// CLASS: BINLDRIVERS_DOCUMENTRETRIEVALDRIVER
py::class_<BinLDrivers_DocumentRetrievalDriver, opencascade::handle<BinLDrivers_DocumentRetrievalDriver>, PCDM_RetrievalDriver> cls_BinLDrivers_DocumentRetrievalDriver(mod, "BinLDrivers_DocumentRetrievalDriver", "None");

// Constructors
cls_BinLDrivers_DocumentRetrievalDriver.def(py::init<>());

// Methods
cls_BinLDrivers_DocumentRetrievalDriver.def("CreateDocument", (opencascade::handle<CDM_Document> (BinLDrivers_DocumentRetrievalDriver::*)()) &BinLDrivers_DocumentRetrievalDriver::CreateDocument, "pure virtual method definition");
cls_BinLDrivers_DocumentRetrievalDriver.def("Read", (void (BinLDrivers_DocumentRetrievalDriver::*)(const TCollection_ExtendedString &, const opencascade::handle<CDM_Document> &, const opencascade::handle<CDM_Application> &)) &BinLDrivers_DocumentRetrievalDriver::Read, "retrieves the content of the file into a new Document.", py::arg("theFileName"), py::arg("theNewDocument"), py::arg("theApplication"));
cls_BinLDrivers_DocumentRetrievalDriver.def("Read", (void (BinLDrivers_DocumentRetrievalDriver::*)(Standard_IStream &, const opencascade::handle<Storage_Data> &, const opencascade::handle<CDM_Document> &, const opencascade::handle<CDM_Application> &)) &BinLDrivers_DocumentRetrievalDriver::Read, "None", py::arg("theIStream"), py::arg("theStorageData"), py::arg("theDoc"), py::arg("theApplication"));
cls_BinLDrivers_DocumentRetrievalDriver.def("AttributeDrivers", (opencascade::handle<BinMDF_ADriverTable> (BinLDrivers_DocumentRetrievalDriver::*)(const opencascade::handle<Message_Messenger> &)) &BinLDrivers_DocumentRetrievalDriver::AttributeDrivers, "None", py::arg("theMsgDriver"));
cls_BinLDrivers_DocumentRetrievalDriver.def_static("get_type_name_", (const char * (*)()) &BinLDrivers_DocumentRetrievalDriver::get_type_name, "None");
cls_BinLDrivers_DocumentRetrievalDriver.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &BinLDrivers_DocumentRetrievalDriver::get_type_descriptor, "None");
cls_BinLDrivers_DocumentRetrievalDriver.def("DynamicType", (const opencascade::handle<Standard_Type> & (BinLDrivers_DocumentRetrievalDriver::*)() const) &BinLDrivers_DocumentRetrievalDriver::DynamicType, "None");

// CLASS: BINLDRIVERS_DOCUMENTSTORAGEDRIVER
py::class_<BinLDrivers_DocumentStorageDriver, opencascade::handle<BinLDrivers_DocumentStorageDriver>, PCDM_StorageDriver> cls_BinLDrivers_DocumentStorageDriver(mod, "BinLDrivers_DocumentStorageDriver", "persistent implemention of storage a document in a binary file");

// Constructors
cls_BinLDrivers_DocumentStorageDriver.def(py::init<>());

// Methods
cls_BinLDrivers_DocumentStorageDriver.def("Write", (void (BinLDrivers_DocumentStorageDriver::*)(const opencascade::handle<CDM_Document> &, const TCollection_ExtendedString &)) &BinLDrivers_DocumentStorageDriver::Write, "Write <theDocument> to the binary file <theFileName>", py::arg("theDocument"), py::arg("theFileName"));
cls_BinLDrivers_DocumentStorageDriver.def("Write", (void (BinLDrivers_DocumentStorageDriver::*)(const opencascade::handle<CDM_Document> &, Standard_OStream &)) &BinLDrivers_DocumentStorageDriver::Write, "Write <theDocument> to theOStream", py::arg("theDocument"), py::arg("theOStream"));
cls_BinLDrivers_DocumentStorageDriver.def("AttributeDrivers", (opencascade::handle<BinMDF_ADriverTable> (BinLDrivers_DocumentStorageDriver::*)(const opencascade::handle<Message_Messenger> &)) &BinLDrivers_DocumentStorageDriver::AttributeDrivers, "None", py::arg("theMsgDriver"));
cls_BinLDrivers_DocumentStorageDriver.def("AddSection", [](BinLDrivers_DocumentStorageDriver &self, const TCollection_AsciiString & a0) -> void { return self.AddSection(a0); });
cls_BinLDrivers_DocumentStorageDriver.def("AddSection", (void (BinLDrivers_DocumentStorageDriver::*)(const TCollection_AsciiString &, const Standard_Boolean)) &BinLDrivers_DocumentStorageDriver::AddSection, "Create a section that should be written after the OCAF data", py::arg("theName"), py::arg("isPostRead"));
cls_BinLDrivers_DocumentStorageDriver.def_static("get_type_name_", (const char * (*)()) &BinLDrivers_DocumentStorageDriver::get_type_name, "None");
cls_BinLDrivers_DocumentStorageDriver.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &BinLDrivers_DocumentStorageDriver::get_type_descriptor, "None");
cls_BinLDrivers_DocumentStorageDriver.def("DynamicType", (const opencascade::handle<Standard_Type> & (BinLDrivers_DocumentStorageDriver::*)() const) &BinLDrivers_DocumentStorageDriver::DynamicType, "None");

// CLASS: BINLDRIVERS
py::class_<BinLDrivers> cls_BinLDrivers(mod, "BinLDrivers", "None");

// Methods
cls_BinLDrivers.def_static("Factory_", (const opencascade::handle<Standard_Transient> & (*)(const Standard_GUID &)) &BinLDrivers::Factory, "None", py::arg("theGUID"));
cls_BinLDrivers.def_static("DefineFormat_", (void (*)(const opencascade::handle<TDocStd_Application> &)) &BinLDrivers::DefineFormat, "Defines format 'BinLOcaf' and registers its read and write drivers in the specified application", py::arg("theApp"));
cls_BinLDrivers.def_static("AttributeDrivers_", (opencascade::handle<BinMDF_ADriverTable> (*)(const opencascade::handle<Message_Messenger> &)) &BinLDrivers::AttributeDrivers, "Creates a table of the supported drivers' types", py::arg("MsgDrv"));
cls_BinLDrivers.def_static("StorageVersion_", (TCollection_AsciiString (*)()) &BinLDrivers::StorageVersion, "returns last storage version");


}
