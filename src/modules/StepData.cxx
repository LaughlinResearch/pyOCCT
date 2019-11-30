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
#include <StepData_Logical.hxx>
#include <Interface_Protocol.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>
#include <Interface_InterfaceModel.hxx>
#include <StepData_EDescr.hxx>
#include <StepData_ESDescr.hxx>
#include <StepData_ECDescr.hxx>
#include <TColStd_SequenceOfAsciiString.hxx>
#include <StepData_PDescr.hxx>
#include <Standard_Std.hxx>
#include <StepData_Protocol.hxx>
#include <Interface_DataMapOfTransientInteger.hxx>
#include <NCollection_DataMap.hxx>
#include <TCollection_AsciiString.hxx>
#include <Interface_GeneralModule.hxx>
#include <Interface_EntityIterator.hxx>
#include <Interface_ShareTool.hxx>
#include <Interface_Check.hxx>
#include <Interface_CopyTool.hxx>
#include <StepData_GeneralModule.hxx>
#include <Interface_ReaderModule.hxx>
#include <Interface_FileReaderData.hxx>
#include <StepData_StepReaderData.hxx>
#include <StepData_StepWriter.hxx>
#include <StepData_ReadWriteModule.hxx>
#include <Interface_ParamType.hxx>
#include <StepData_SelectMember.hxx>
#include <StepData_Field.hxx>
#include <StepData_FieldList.hxx>
#include <StepData_SelectType.hxx>
#include <TCollection_HAsciiString.hxx>
#include <StepData_EnumTool.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Interface_IndexedMapOfAsciiString.hxx>
#include <TColStd_DataMapOfIntegerInteger.hxx>
#include <Standard.hxx>
#include <StepData_SelectReal.hxx>
#include <StepData_SelectInt.hxx>
#include <StepData_StepModel.hxx>
#include <StepData_UndefinedEntity.hxx>
#include <StepData_SelectNamed.hxx>
#include <StepData_SelectArrReal.hxx>
#include <StepData_FieldList1.hxx>
#include <StepData_FieldListN.hxx>
#include <StepData_FieldListD.hxx>
#include <StepData_Described.hxx>
#include <StepData_Simple.hxx>
#include <StepData_Plex.hxx>
#include <StepData_FreeFormEntity.hxx>
#include <StepData_FileRecognizer.hxx>
#include <StepData_FileProtocol.hxx>
#include <StepData_StepReaderTool.hxx>
#include <StepData_StepDumper.hxx>
#include <StepData_WriterLib.hxx>
#include <StepData_DefaultGeneral.hxx>
#include <StepData_GlobalNodeOfWriterLib.hxx>
#include <StepData_NodeOfWriterLib.hxx>
#include <StepData.hxx>
#include <NCollection_Array1.hxx>
#include <StepData_Array1OfField.hxx>
#include <TColStd_HSequenceOfAsciiString.hxx>
#include <TColStd_SequenceOfTransient.hxx>
#include <TColStd_HArray1OfTransient.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <StepData_HArray1OfField.hxx>
#include <Interface_Graph.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <Interface_FloatWriter.hxx>
#include <Interface_CheckIterator.hxx>
#include <Standard_OStream.hxx>
#include <TColStd_HSequenceOfHAsciiString.hxx>
#include <Interface_LineBuffer.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <Message_Messenger.hxx>
#include <Interface_GeneralLib.hxx>
#include <Interface_EntityList.hxx>
#include <Interface_FileReaderTool.hxx>
#include <Interface_ReaderLib.hxx>
#include <Interface_UndefinedContent.hxx>
#include <bind_NCollection_Array1.hxx>

PYBIND11_MODULE(StepData, mod) {

py::module::import("OCCT.Interface");
py::module::import("OCCT.Standard");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.Message");

// ENUM: STEPDATA_LOGICAL
py::enum_<StepData_Logical>(mod, "StepData_Logical", "A Standard Definition for STEP (which knows Boolean too)")
	.value("StepData_LFalse", StepData_Logical::StepData_LFalse)
	.value("StepData_LTrue", StepData_Logical::StepData_LTrue)
	.value("StepData_LUnknown", StepData_Logical::StepData_LUnknown)
	.export_values();


// CLASS: STEPDATA_PROTOCOL
py::class_<StepData_Protocol, opencascade::handle<StepData_Protocol>, Interface_Protocol> cls_StepData_Protocol(mod, "StepData_Protocol", "Description of Basic Protocol for Step The class Protocol from StepData itself describes a default Protocol, which recognizes only UnknownEntities. Sub-classes will redefine CaseNumber and, if necessary, NbResources and Resources.");

// Constructors
cls_StepData_Protocol.def(py::init<>());

// Methods
cls_StepData_Protocol.def("NbResources", (Standard_Integer (StepData_Protocol::*)() const) &StepData_Protocol::NbResources, "Gives the count of Protocols used as Resource (can be zero) Here, No resource");
cls_StepData_Protocol.def("Resource", (opencascade::handle<Interface_Protocol> (StepData_Protocol::*)(const Standard_Integer) const) &StepData_Protocol::Resource, "Returns a Resource, given a rank. Here, none", py::arg("num"));
cls_StepData_Protocol.def("CaseNumber", (Standard_Integer (StepData_Protocol::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_Protocol::CaseNumber, "Returns a unique positive number for any recognized entity Redefined to work by calling both TypeNumber and, for a Described Entity (late binding) DescrNumber", py::arg("obj"));
cls_StepData_Protocol.def("TypeNumber", (Standard_Integer (StepData_Protocol::*)(const opencascade::handle<Standard_Type> &) const) &StepData_Protocol::TypeNumber, "Returns a Case Number, specific of each recognized Type Here, only Unknown Entity is recognized", py::arg("atype"));
cls_StepData_Protocol.def("SchemaName", (Standard_CString (StepData_Protocol::*)() const) &StepData_Protocol::SchemaName, "Returns the Schema Name attached to each class of Protocol To be redefined by each sub-class Here, SchemaName returns '(DEFAULT)' was C++ : return const");
cls_StepData_Protocol.def("NewModel", (opencascade::handle<Interface_InterfaceModel> (StepData_Protocol::*)() const) &StepData_Protocol::NewModel, "Creates an empty Model for Step Norm");
cls_StepData_Protocol.def("IsSuitableModel", (Standard_Boolean (StepData_Protocol::*)(const opencascade::handle<Interface_InterfaceModel> &) const) &StepData_Protocol::IsSuitableModel, "Returns True if <model> is a Model of Step Norm", py::arg("model"));
cls_StepData_Protocol.def("UnknownEntity", (opencascade::handle<Standard_Transient> (StepData_Protocol::*)() const) &StepData_Protocol::UnknownEntity, "Creates a new Unknown Entity for Step (UndefinedEntity)");
cls_StepData_Protocol.def("IsUnknownEntity", (Standard_Boolean (StepData_Protocol::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_Protocol::IsUnknownEntity, "Returns True if <ent> is an Unknown Entity for the Norm, i.e. Type UndefinedEntity, status Unknown", py::arg("ent"));
cls_StepData_Protocol.def("DescrNumber", (Standard_Integer (StepData_Protocol::*)(const opencascade::handle<StepData_EDescr> &) const) &StepData_Protocol::DescrNumber, "Returns a unique positive CaseNumber for types described by an EDescr (late binding) Warning : TypeNumber and DescrNumber must give together a unique positive case number for each distinct case, type or descr", py::arg("adescr"));
cls_StepData_Protocol.def("AddDescr", (void (StepData_Protocol::*)(const opencascade::handle<StepData_EDescr> &, const Standard_Integer)) &StepData_Protocol::AddDescr, "Records an EDescr with its case number Also records its name for an ESDescr (simple type): an ESDescr is then used, for case number, or for type name", py::arg("adescr"), py::arg("CN"));
cls_StepData_Protocol.def("HasDescr", (Standard_Boolean (StepData_Protocol::*)() const) &StepData_Protocol::HasDescr, "Tells if a Protocol brings at least one ESDescr, i.e. if it defines at least one entity description by ESDescr mechanism");
cls_StepData_Protocol.def("Descr", (opencascade::handle<StepData_EDescr> (StepData_Protocol::*)(const Standard_Integer) const) &StepData_Protocol::Descr, "Returns the description attached to a case number, or null", py::arg("num"));
cls_StepData_Protocol.def("Descr", [](StepData_Protocol &self, const Standard_CString a0) -> opencascade::handle<StepData_EDescr> { return self.Descr(a0); });
cls_StepData_Protocol.def("Descr", (opencascade::handle<StepData_EDescr> (StepData_Protocol::*)(const Standard_CString, const Standard_Boolean) const) &StepData_Protocol::Descr, "Returns a description according to its name <anylevel> True (D) : for <me> and its resources <anylevel> False : for <me> only", py::arg("name"), py::arg("anylevel"));
cls_StepData_Protocol.def("ESDescr", [](StepData_Protocol &self, const Standard_CString a0) -> opencascade::handle<StepData_ESDescr> { return self.ESDescr(a0); });
cls_StepData_Protocol.def("ESDescr", (opencascade::handle<StepData_ESDescr> (StepData_Protocol::*)(const Standard_CString, const Standard_Boolean) const) &StepData_Protocol::ESDescr, "Idem as Descr but cast to simple description", py::arg("name"), py::arg("anylevel"));
cls_StepData_Protocol.def("ECDescr", [](StepData_Protocol &self, const TColStd_SequenceOfAsciiString & a0) -> opencascade::handle<StepData_ECDescr> { return self.ECDescr(a0); });
cls_StepData_Protocol.def("ECDescr", (opencascade::handle<StepData_ECDescr> (StepData_Protocol::*)(const TColStd_SequenceOfAsciiString &, const Standard_Boolean) const) &StepData_Protocol::ECDescr, "Returns a complex description according to list of names <anylevel> True (D) : for <me> and its resources <anylevel> False : for <me> only", py::arg("names"), py::arg("anylevel"));
cls_StepData_Protocol.def("AddPDescr", (void (StepData_Protocol::*)(const opencascade::handle<StepData_PDescr> &)) &StepData_Protocol::AddPDescr, "Records an PDescr", py::arg("pdescr"));
cls_StepData_Protocol.def("PDescr", [](StepData_Protocol &self, const Standard_CString a0) -> opencascade::handle<StepData_PDescr> { return self.PDescr(a0); });
cls_StepData_Protocol.def("PDescr", (opencascade::handle<StepData_PDescr> (StepData_Protocol::*)(const Standard_CString, const Standard_Boolean) const) &StepData_Protocol::PDescr, "Returns a parameter description according to its name <anylevel> True (D) : for <me> and its resources <anylevel> False : for <me> only", py::arg("name"), py::arg("anylevel"));
cls_StepData_Protocol.def("AddBasicDescr", (void (StepData_Protocol::*)(const opencascade::handle<StepData_ESDescr> &)) &StepData_Protocol::AddBasicDescr, "Records an ESDescr, intended to build complex descriptions", py::arg("esdescr"));
cls_StepData_Protocol.def("BasicDescr", [](StepData_Protocol &self, const Standard_CString a0) -> opencascade::handle<StepData_EDescr> { return self.BasicDescr(a0); });
cls_StepData_Protocol.def("BasicDescr", (opencascade::handle<StepData_EDescr> (StepData_Protocol::*)(const Standard_CString, const Standard_Boolean) const) &StepData_Protocol::BasicDescr, "Returns a basic description according to its name <anylevel> True (D) : for <me> and its resources <anylevel> False : for <me> only", py::arg("name"), py::arg("anylevel"));
cls_StepData_Protocol.def_static("get_type_name_", (const char * (*)()) &StepData_Protocol::get_type_name, "None");
cls_StepData_Protocol.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_Protocol::get_type_descriptor, "None");
cls_StepData_Protocol.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_Protocol::*)() const) &StepData_Protocol::DynamicType, "None");

// CLASS: STEPDATA_GENERALMODULE
py::class_<StepData_GeneralModule, opencascade::handle<StepData_GeneralModule>, Interface_GeneralModule> cls_StepData_GeneralModule(mod, "StepData_GeneralModule", "Specific features for General Services adapted to STEP");

// Methods
cls_StepData_GeneralModule.def("FillSharedCase", (void (StepData_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, Interface_EntityIterator &) const) &StepData_GeneralModule::FillSharedCase, "Specific filling of the list of Entities shared by an Entity <ent>. Can use the internal utility method Share, below", py::arg("casenum"), py::arg("ent"), py::arg("iter"));
cls_StepData_GeneralModule.def("CheckCase", (void (StepData_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &StepData_GeneralModule::CheckCase, "Specific Checking of an Entity <ent>", py::arg("casenum"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_StepData_GeneralModule.def("CopyCase", (void (StepData_GeneralModule::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const opencascade::handle<Standard_Transient> &, Interface_CopyTool &) const) &StepData_GeneralModule::CopyCase, "Specific Copy ('Deep') from <entfrom> to <entto> (same type) by using a TransferControl which provides its working Map. Use method Transferred from TransferControl to work Specific Copying of Implied References A Default is provided which does nothing (must current case !) Already copied references (by CopyFrom) must remain unchanged Use method Search from TransferControl to work", py::arg("casenum"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_StepData_GeneralModule.def_static("get_type_name_", (const char * (*)()) &StepData_GeneralModule::get_type_name, "None");
cls_StepData_GeneralModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_GeneralModule::get_type_descriptor, "None");
cls_StepData_GeneralModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_GeneralModule::*)() const) &StepData_GeneralModule::DynamicType, "None");

// CLASS: STEPDATA_READWRITEMODULE
py::class_<StepData_ReadWriteModule, opencascade::handle<StepData_ReadWriteModule>, Interface_ReaderModule> cls_StepData_ReadWriteModule(mod, "StepData_ReadWriteModule", "Defines basic File Access Module (Recognize, Read, Write) That is : ReaderModule (Recognize & Read) + Write for StepWriter (for a more centralized description) Warning : A sub-class of ReadWriteModule, which belongs to a particular Protocol, must use the same definition for Case Numbers (give the same Value for a StepType defined as a String from a File as the Protocol does for the corresponding Entity)");

// Methods
cls_StepData_ReadWriteModule.def("CaseNum", (Standard_Integer (StepData_ReadWriteModule::*)(const opencascade::handle<Interface_FileReaderData> &, const Standard_Integer) const) &StepData_ReadWriteModule::CaseNum, "Translate the Type of record <num> in <data> to a positive Case Number, or 0 if failed. Works with a StepReaderData, in which the Type of an Entity is defined as a String : Reads the RecordType <num> then calls CaseNum (this type) Warning : The methods CaseStep, StepType and Recognize, must be in phase (triplets CaseNum-StepType-Type of Object)", py::arg("data"), py::arg("num"));
cls_StepData_ReadWriteModule.def("CaseStep", (Standard_Integer (StepData_ReadWriteModule::*)(const TCollection_AsciiString &) const) &StepData_ReadWriteModule::CaseStep, "Defines Case Numbers corresponding to the recognized Types Called by CaseNum (data,num) above for a Simple Type Entity Warning : CaseStep must give the same Value as Protocol does for the Entity type which corresponds to this Type given as a String", py::arg("atype"));
cls_StepData_ReadWriteModule.def("CaseStep", (Standard_Integer (StepData_ReadWriteModule::*)(const TColStd_SequenceOfAsciiString &) const) &StepData_ReadWriteModule::CaseStep, "Same a above but for a Complex Type Entity ('Plex') The provided Default recognizes nothing", py::arg("types"));
cls_StepData_ReadWriteModule.def("IsComplex", (Standard_Boolean (StepData_ReadWriteModule::*)(const Standard_Integer) const) &StepData_ReadWriteModule::IsComplex, "Returns True if the Case Number corresponds to a Complex Type ('Plex'). Remember that all possible combinations must be aknowledged to be processed Default is False for all cases. For a Protocol which defines possible Plexes, this method must be redefined.", py::arg("CN"));
cls_StepData_ReadWriteModule.def("StepType", (const TCollection_AsciiString & (StepData_ReadWriteModule::*)(const Standard_Integer) const) &StepData_ReadWriteModule::StepType, "Function specific to STEP, which delivers the StepType as it is recorded in and read from a File compliant with STEP. This method is symmetric to the method CaseStep. StepType can be different from Dynamic Type's name, but belongs to the same class of Object. Returns an empty String if <CN> is zero. Warning : For a Complex Type Entity, returns an Empty String (Complex Type must be managed by users)", py::arg("CN"));
cls_StepData_ReadWriteModule.def("ShortType", (TCollection_AsciiString (StepData_ReadWriteModule::*)(const Standard_Integer) const) &StepData_ReadWriteModule::ShortType, "Function specific to STEP. Some STEP Types have a short form This method can be redefined to fill it By default, returns an empty string, which is then interpreted to take normal form from StepType", py::arg("CN"));
cls_StepData_ReadWriteModule.def("ComplexType", (Standard_Boolean (StepData_ReadWriteModule::*)(const Standard_Integer, TColStd_SequenceOfAsciiString &) const) &StepData_ReadWriteModule::ComplexType, "Function specific to STEP, which delivers the list of types which corresponds to a complex type. If <CN> is not for a complex type, this method returns False. Else it returns True and fills the list in alphabetic order. The default returns False. To be redefined as required.", py::arg("CN"), py::arg("types"));
cls_StepData_ReadWriteModule.def("Read", (void (StepData_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<Interface_FileReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<Standard_Transient> &) const) &StepData_ReadWriteModule::Read, "General Read Function, calls ReadStep", py::arg("CN"), py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_StepData_ReadWriteModule.def("ReadStep", (void (StepData_ReadWriteModule::*)(const Standard_Integer, const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<Standard_Transient> &) const) &StepData_ReadWriteModule::ReadStep, "Specific Read Function. Works with StepReaderData", py::arg("CN"), py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_StepData_ReadWriteModule.def("WriteStep", (void (StepData_ReadWriteModule::*)(const Standard_Integer, StepData_StepWriter &, const opencascade::handle<Standard_Transient> &) const) &StepData_ReadWriteModule::WriteStep, "Write Function, switched by CaseNum", py::arg("CN"), py::arg("SW"), py::arg("ent"));
cls_StepData_ReadWriteModule.def_static("get_type_name_", (const char * (*)()) &StepData_ReadWriteModule::get_type_name, "None");
cls_StepData_ReadWriteModule.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_ReadWriteModule::get_type_descriptor, "None");
cls_StepData_ReadWriteModule.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_ReadWriteModule::*)() const) &StepData_ReadWriteModule::DynamicType, "None");

// CLASS: STEPDATA_STEPREADERDATA
py::class_<StepData_StepReaderData, opencascade::handle<StepData_StepReaderData>, Interface_FileReaderData> cls_StepData_StepReaderData(mod, "StepData_StepReaderData", "Specific FileReaderData for Step Contains litteral description of entities (for each one : type as a string, ident, parameter list) provides references evaluation, plus access to litteral data and specific access methods (Boolean, XY, XYZ)");

// Constructors
cls_StepData_StepReaderData.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer>(), py::arg("nbheader"), py::arg("nbtotal"), py::arg("nbpar"));

// Methods
cls_StepData_StepReaderData.def("SetRecord", (void (StepData_StepReaderData::*)(const Standard_Integer, const Standard_CString, const Standard_CString, const Standard_Integer)) &StepData_StepReaderData::SetRecord, "Fills the fields of a record", py::arg("num"), py::arg("ident"), py::arg("type"), py::arg("nbpar"));
cls_StepData_StepReaderData.def("AddStepParam", [](StepData_StepReaderData &self, const Standard_Integer a0, const Standard_CString a1, const Interface_ParamType a2) -> void { return self.AddStepParam(a0, a1, a2); });
cls_StepData_StepReaderData.def("AddStepParam", (void (StepData_StepReaderData::*)(const Standard_Integer, const Standard_CString, const Interface_ParamType, const Standard_Integer)) &StepData_StepReaderData::AddStepParam, "Fills the fields of a parameter of a record. This is a variant of AddParam, Adapted to STEP (optimized for specific values)", py::arg("num"), py::arg("aval"), py::arg("atype"), py::arg("nument"));
cls_StepData_StepReaderData.def("RecordType", (const TCollection_AsciiString & (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::RecordType, "Returns Record Type", py::arg("num"));
cls_StepData_StepReaderData.def("CType", (Standard_CString (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::CType, "Returns Record Type as a CString was C++ : return const", py::arg("num"));
cls_StepData_StepReaderData.def("RecordIdent", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::RecordIdent, "Returns record identifier (Positive number) If returned ident is not positive : Sub-List or Scope mark", py::arg("num"));
cls_StepData_StepReaderData.def("SubListNumber", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_Boolean) const) &StepData_StepReaderData::SubListNumber, "Returns SubList numero designated by a parameter (nump) in a record (num), or zero if the parameter does not exist or is not a SubList address. Zero too If aslast is True and nump is not for the last parameter", py::arg("num"), py::arg("nump"), py::arg("aslast"));
cls_StepData_StepReaderData.def("IsComplex", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::IsComplex, "Returns True if <num> corresponds to a Complex Type Entity (as can be defined by ANDOR Express clause)", py::arg("num"));
cls_StepData_StepReaderData.def("ComplexType", (void (StepData_StepReaderData::*)(const Standard_Integer, TColStd_SequenceOfAsciiString &) const) &StepData_StepReaderData::ComplexType, "Returns the List of Types which correspond to a Complex Type Entity. If not Complex, there is just one Type in it For a SubList or a Scope mark, <types> remains empty", py::arg("num"), py::arg("types"));
cls_StepData_StepReaderData.def("NextForComplex", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::NextForComplex, "Returns the Next 'Componant' for a Complex Type Entity, of which <num> is already a Componant (the first one or a next one) Returns 0 for a Simple Type or for the last Componant", py::arg("num"));
cls_StepData_StepReaderData.def("NamedForComplex", [](StepData_StepReaderData &self, const Standard_CString name, const Standard_Integer num0, Standard_Integer & num, opencascade::handle<Interface_Check> & ach){ Standard_Boolean rv = self.NamedForComplex(name, num0, num, ach); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, num); }, "Determines the first component which brings a given name, for a Complex Type Entity <num0> is the very first record of this entity <num> is given the last NextNamedForComplex, starts at zero it is returned as the newly found number Hence, in the normal case, NextNamedForComplex starts by num0 if <num> is zero, else by NextForComplex(num) If the alphabetic order is not respected, it restarts from num0 and loops on NextForComplex until finding <name> In case of 'non-alphabetic order', <ach> is filled with a Warning for this name In case of 'not-found at all', <ach> is filled with a Fail, and <num> is returned as zero", py::arg("name"), py::arg("num0"), py::arg("num"), py::arg("ach"));
cls_StepData_StepReaderData.def("NamedForComplex", [](StepData_StepReaderData &self, const Standard_CString theName, const Standard_CString theShortName, const Standard_Integer num0, Standard_Integer & num, opencascade::handle<Interface_Check> & ach){ Standard_Boolean rv = self.NamedForComplex(theName, theShortName, num0, num, ach); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, num); }, "Determines the first component which brings a given name, or short name for a Complex Type Entity <num0> is the very first record of this entity <num> is given the last NextNamedForComplex, starts at zero it is returned as the newly found number Hence, in the normal case, NextNamedForComplex starts by num0 if <num> is zero, else by NextForComplex(num) If the alphabetic order is not respected, it restarts from num0 and loops on NextForComplex until finding <name> In case of 'non-alphabetic order', <ach> is filled with a Warning for this name In case of 'not-found at all', <ach> is filled with a Fail, and <num> is returned as zero", py::arg("theName"), py::arg("theShortName"), py::arg("num0"), py::arg("num"), py::arg("ach"));
cls_StepData_StepReaderData.def("CheckNbParams", [](StepData_StepReaderData &self, const Standard_Integer a0, const Standard_Integer a1, opencascade::handle<Interface_Check> & a2) -> Standard_Boolean { return self.CheckNbParams(a0, a1, a2); });
cls_StepData_StepReaderData.def("CheckNbParams", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, opencascade::handle<Interface_Check> &, const Standard_CString) const) &StepData_StepReaderData::CheckNbParams, "Checks Count of Parameters of record <num> to equate <nbreq> If this Check is successful, returns True Else, fills <ach> with an Error Message then returns False <mess> is included in the Error message if given non empty", py::arg("num"), py::arg("nbreq"), py::arg("ach"), py::arg("mess"));
cls_StepData_StepReaderData.def("ReadSubList", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Integer & numsub, const Standard_Boolean optional, const Standard_Integer lenmin, const Standard_Integer lenmax){ Standard_Boolean rv = self.ReadSubList(num, nump, mess, ach, numsub, optional, lenmin, lenmax); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, numsub); }, "reads parameter <nump> of record <num> as a sub-list (may be typed, see ReadTypedParameter in this case) Returns True if OK. Else (not a LIST), returns false and feeds Check with appropriate check If <optional> is True and Param is not defined, returns True with <ach> not filled and <numsub> returned as 0 Works with SubListNumber with <aslast> false (no specific case for last parameter)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("numsub"), py::arg("optional"), py::arg("lenmin"), py::arg("lenmax"));
cls_StepData_StepReaderData.def("ReadSub", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, const opencascade::handle<StepData_PDescr> &, opencascade::handle<Standard_Transient> &) const) &StepData_StepReaderData::ReadSub, "reads the content of a sub-list into a transient : SelectNamed, or HArray1 of Integer,Real,String,Transient ... recursive call if list of list ... If a sub-list has mixed types, an HArray1OfTransient is produced, it may contain SelectMember Intended to be called by ReadField The returned status is : negative if failed, 0 if empty. Else the kind to be recorded in the field", py::arg("numsub"), py::arg("mess"), py::arg("ach"), py::arg("descr"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadMember", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, opencascade::handle<StepData_SelectMember> &) const) &StepData_StepReaderData::ReadMember, "Reads parameter <nump> of record <num> into a SelectMember, self-sufficient (no Description needed) If <val> is already created, it will be filled, as possible And if reading does not match its own description, the result will be False If <val> is not it not yet created, it will be (SelectNamed) Usefull if a field is defined as a SelectMember, directly (SELECT with no Entity as member) But SelectType also manages SelectMember (for SELECT with some members as Entity, some other not)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadField", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, const opencascade::handle<StepData_PDescr> &, StepData_Field &) const) &StepData_StepReaderData::ReadField, "reads parameter <nump> of record <num> into a Field, controlled by a Parameter Descriptor (PDescr), which controls its allowed type(s) and value <ach> is filled if the read parameter does not match its description (but the field is read anyway) If the description is not defined, no control is done Returns True when done", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("descr"), py::arg("fild"));
cls_StepData_StepReaderData.def("ReadList", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepData_ESDescr> &, StepData_FieldList &) const) &StepData_StepReaderData::ReadList, "reads a list of fields controlled by an ESDescr", py::arg("num"), py::arg("ach"), py::arg("descr"), py::arg("list"));
cls_StepData_StepReaderData.def("ReadAny", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, const opencascade::handle<StepData_PDescr> &, opencascade::handle<Standard_Transient> &) const) &StepData_StepReaderData::ReadAny, "Reads parameter <nump> of record <num> into a Transient Value according to the type of the parameter : Named for Integer,Boolean,Logical,Enum,Real : SelectNamed Immediate Integer,Boolean,Logical,Enum,Real : SelectInt/Real Text : HAsciiString Ident : the referenced Entity Sub-List not processed, see ReadSub This value is controlled by a Parameter Descriptor (PDescr), which controls its allowed type and value <ach> is filled if the read parameter does not match its description (the select is nevertheless created if possible)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("descr"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadXY", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Real & X, Standard_Real & Y){ Standard_Boolean rv = self.ReadXY(num, nump, mess, ach, X, Y); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, X, Y); }, "reads parameter <nump> of record <num> as a sub-list of two Reals X,Y. Returns True if OK. Else, returns false and feeds Check with appropriate Fails (parameter not a sub-list, not two Reals in the sub-list) composed with 'mess' which gives the name of the parameter", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("X"), py::arg("Y"));
cls_StepData_StepReaderData.def("ReadXYZ", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Real & X, Standard_Real & Y, Standard_Real & Z){ Standard_Boolean rv = self.ReadXYZ(num, nump, mess, ach, X, Y, Z); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &, Standard_Real &>(rv, X, Y, Z); }, "reads parameter <nump> of record <num> as a sub-list of three Reals X,Y,Z. Return value and Check managed as by ReadXY (demands a sub-list of three Reals)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("X"), py::arg("Y"), py::arg("Z"));
cls_StepData_StepReaderData.def("ReadReal", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Real & val){ Standard_Boolean rv = self.ReadReal(num, nump, mess, ach, val); return std::tuple<Standard_Boolean, Standard_Real &>(rv, val); }, "reads parameter <nump> of record <num> as a single Real value. Return value and Check managed as by ReadXY (demands a Real)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadEntity", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, const opencascade::handle<Standard_Type> &, opencascade::handle<Standard_Transient> &) const) &StepData_StepReaderData::ReadEntity, "Reads parameter <nump> of record <num> as a single Entity. Return value and Check managed as by ReadReal (demands a reference to an Entity). In Addition, demands read Entity to be Kind of a required Type <atype>. Remark that returned status is False and <ent> is Null if parameter is not an Entity, <ent> remains Not Null is parameter is an Entity but is not Kind of required type", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("atype"), py::arg("ent"));
cls_StepData_StepReaderData.def("ReadEntity", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, StepData_SelectType &) const) &StepData_StepReaderData::ReadEntity, "Same as above, but a SelectType checks Type Matching, and records the read Entity (see method Value from SelectType)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("sel"));
cls_StepData_StepReaderData.def("ReadInteger", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Integer & val){ Standard_Boolean rv = self.ReadInteger(num, nump, mess, ach, val); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, val); }, "reads parameter <nump> of record <num> as a single Integer. Return value & Check managed as by ReadXY (demands an Integer)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadBoolean", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Boolean & flag){ Standard_Boolean rv = self.ReadBoolean(num, nump, mess, ach, flag); return std::tuple<Standard_Boolean, Standard_Boolean &>(rv, flag); }, "reads parameter <nump> of record <num> as a Boolean Return value and Check managed as by ReadReal (demands a Boolean enum, i.e. text '.T.' for True or '.F.' for False)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("flag"));
cls_StepData_StepReaderData.def("ReadLogical", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, StepData_Logical &) const) &StepData_StepReaderData::ReadLogical, "reads parameter <nump> of record <num> as a Logical Return value and Check managed as by ReadBoolean (demands a Logical enum, i.e. text '.T.', '.F.', or '.U.')", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("flag"));
cls_StepData_StepReaderData.def("ReadString", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, opencascade::handle<TCollection_HAsciiString> &) const) &StepData_StepReaderData::ReadString, "reads parameter <nump> of record <num> as a String (text between quotes, quotes are removed by the Read operation) Return value and Check managed as by ReadXY (demands a String)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("val"));
// cls_StepData_StepReaderData.def("ReadEnumParam", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_CString & text){ Standard_Boolean rv = self.ReadEnumParam(num, nump, mess, ach, text); return std::tuple<Standard_Boolean, Standard_CString &>(rv, text); }, "None", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("text"));
cls_StepData_StepReaderData.def("FailEnumValue", (void (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &) const) &StepData_StepReaderData::FailEnumValue, "Fills a check with a fail message if enumeration value does match parameter definition Just a help to centralize message definitions", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"));
cls_StepData_StepReaderData.def("ReadEnum", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, const StepData_EnumTool & enumtool, Standard_Integer & val){ Standard_Boolean rv = self.ReadEnum(num, nump, mess, ach, enumtool, val); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, val); }, "Reads parameter <nump> of record <num> as an Enumeration (text between dots) and converts it to an integer value, by an EnumTool. Returns True if OK, false if : this parameter is not enumeration, or is not recognized by the EnumTool (with fail)", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("enumtool"), py::arg("val"));
cls_StepData_StepReaderData.def("ReadTypedParam", [](StepData_StepReaderData &self, const Standard_Integer num, const Standard_Integer nump, const Standard_Boolean mustbetyped, const Standard_CString mess, opencascade::handle<Interface_Check> & ach, Standard_Integer & numr, Standard_Integer & numrp, TCollection_AsciiString & typ){ Standard_Boolean rv = self.ReadTypedParam(num, nump, mustbetyped, mess, ach, numr, numrp, typ); return std::tuple<Standard_Boolean, Standard_Integer &, Standard_Integer &>(rv, numr, numrp); }, "Resolves a parameter which can be enclosed in a type def., as TYPE(val). The parameter must then be read normally according its type. Parameter to be resolved is <nump> of record <num> <mustbetyped> True demands a typed parameter <mustbetyped> False accepts a non-typed parameter as option mess and ach as usual <numr>,<numrp> are the resolved record and parameter numbers = num,nump if no type, else numrp=1 <typ> returns the recorded type, or empty string Remark : a non-typed list is considered as 'non-typed'", py::arg("num"), py::arg("nump"), py::arg("mustbetyped"), py::arg("mess"), py::arg("ach"), py::arg("numr"), py::arg("numrp"), py::arg("typ"));
cls_StepData_StepReaderData.def("CheckDerived", [](StepData_StepReaderData &self, const Standard_Integer a0, const Standard_Integer a1, const Standard_CString a2, opencascade::handle<Interface_Check> & a3) -> Standard_Boolean { return self.CheckDerived(a0, a1, a2, a3); });
cls_StepData_StepReaderData.def("CheckDerived", (Standard_Boolean (StepData_StepReaderData::*)(const Standard_Integer, const Standard_Integer, const Standard_CString, opencascade::handle<Interface_Check> &, const Standard_Boolean) const) &StepData_StepReaderData::CheckDerived, "Checks if parameter <nump> of record <num> is given as Derived If this Check is successful (i.e. Param = '*'), returns True Else, fills <ach> with a Message which contains <mess> and returns False. According to <errstat>, this message is Warning if errstat is False (Default), Fail if errstat is True", py::arg("num"), py::arg("nump"), py::arg("mess"), py::arg("ach"), py::arg("errstat"));
cls_StepData_StepReaderData.def("NbEntities", (Standard_Integer (StepData_StepReaderData::*)() const) &StepData_StepReaderData::NbEntities, "Returns total count of Entities (including Header)");
cls_StepData_StepReaderData.def("FindNextRecord", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::FindNextRecord, "determines the first suitable record following a given one that is, skips SCOPE,ENDSCOPE and SUBLIST records Note : skips Header records, which are accessed separately", py::arg("num"));
cls_StepData_StepReaderData.def("SetEntityNumbers", [](StepData_StepReaderData &self) -> void { return self.SetEntityNumbers(); });
cls_StepData_StepReaderData.def("SetEntityNumbers", (void (StepData_StepReaderData::*)(const Standard_Boolean)) &StepData_StepReaderData::SetEntityNumbers, "determines reference numbers in EntityNumber fields called by Prepare from StepReaderTool to prepare later using by a StepModel. This method is attached to StepReaderData because it needs a massive amount of data accesses to work", py::arg("withmap"));
cls_StepData_StepReaderData.def("FindNextHeaderRecord", (Standard_Integer (StepData_StepReaderData::*)(const Standard_Integer) const) &StepData_StepReaderData::FindNextHeaderRecord, "determine first suitable record of Header works as FindNextRecord, but treats only Header records", py::arg("num"));
cls_StepData_StepReaderData.def("PrepareHeader", (void (StepData_StepReaderData::*)()) &StepData_StepReaderData::PrepareHeader, "Works as SetEntityNumbers but for Header : more simple because there are no Reference, only Sub-Lists");
cls_StepData_StepReaderData.def("GlobalCheck", (const opencascade::handle<Interface_Check> (StepData_StepReaderData::*)() const) &StepData_StepReaderData::GlobalCheck, "Returns the Global Check. It can record Fail messages about Undefined References (detected by SetEntityNumbers)");
cls_StepData_StepReaderData.def_static("get_type_name_", (const char * (*)()) &StepData_StepReaderData::get_type_name, "None");
cls_StepData_StepReaderData.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_StepReaderData::get_type_descriptor, "None");
cls_StepData_StepReaderData.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_StepReaderData::*)() const) &StepData_StepReaderData::DynamicType, "None");

// CLASS: STEPDATA_SELECTTYPE
py::class_<StepData_SelectType> cls_StepData_SelectType(mod, "StepData_SelectType", "SelectType is the basis used for SELECT_TYPE definitions from the EXPRESS form. A SELECT_TYPE in EXPRESS is an enumeration of Types, it corresponds in a way to a Super-Type, but with no specific Methods, and no exclusivity (a given Type can be member of several SELECT_TYPES, plus be itself a SUB_TYPE).");

// Methods
// cls_StepData_SelectType.def_static("operator new_", (void * (*)(size_t)) &StepData_SelectType::operator new, "None", py::arg("theSize"));
// cls_StepData_SelectType.def_static("operator delete_", (void (*)(void *)) &StepData_SelectType::operator delete, "None", py::arg("theAddress"));
// cls_StepData_SelectType.def_static("operator new[]_", (void * (*)(size_t)) &StepData_SelectType::operator new[], "None", py::arg("theSize"));
// cls_StepData_SelectType.def_static("operator delete[]_", (void (*)(void *)) &StepData_SelectType::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_SelectType.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_SelectType::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_SelectType.def_static("operator delete_", (void (*)(void *, void *)) &StepData_SelectType::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_SelectType.def("CaseNum", (Standard_Integer (StepData_SelectType::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_SelectType::CaseNum, "Recognizes the Type of an Entity. Returns a positive Number which identifies the Type in the definition List of the SelectType. Returns Zero if its Type in not in this List.", py::arg("ent"));
cls_StepData_SelectType.def("Matches", (Standard_Boolean (StepData_SelectType::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_SelectType::Matches, "Returns True if the Type of an Entity complies with the definition list of the SelectType. Also checks for a SelectMember Default Implementation looks for CaseNum or CaseMem positive", py::arg("ent"));
cls_StepData_SelectType.def("SetValue", (void (StepData_SelectType::*)(const opencascade::handle<Standard_Transient> &)) &StepData_SelectType::SetValue, "Stores an Entity. This allows to define a specific SelectType class with one read method per member Type, which returns the Value casted with the good Type.", py::arg("ent"));
cls_StepData_SelectType.def("Nullify", (void (StepData_SelectType::*)()) &StepData_SelectType::Nullify, "Nullifies the Stored Entity");
cls_StepData_SelectType.def("Value", (const opencascade::handle<Standard_Transient> & (StepData_SelectType::*)() const) &StepData_SelectType::Value, "Returns the Stored Entity. Can be used to define specific read methods (see above)");
cls_StepData_SelectType.def("IsNull", (Standard_Boolean (StepData_SelectType::*)() const) &StepData_SelectType::IsNull, "Returns True if there is no Stored Entity (i.e. it is Null)");
cls_StepData_SelectType.def("Type", (opencascade::handle<Standard_Type> (StepData_SelectType::*)() const) &StepData_SelectType::Type, "Returns the Effective (Dynamic) Type of the Stored Entity If it is Null, returns TYPE(Transient)");
cls_StepData_SelectType.def("CaseNumber", (Standard_Integer (StepData_SelectType::*)() const) &StepData_SelectType::CaseNumber, "Recognizes the Type of the stored Entity, or zero if it is Null or SelectMember. Calls the first method CaseNum on Value");
cls_StepData_SelectType.def("Description", (opencascade::handle<StepData_PDescr> (StepData_SelectType::*)() const) &StepData_SelectType::Description, "Returns the Description which corresponds to <me> Null if no specific description to give. This description is used to control reading an check validity. Default returns a Null Handle, i.e. undefined description It can suffice if CaseNum and CaseMem give enough control");
cls_StepData_SelectType.def("NewMember", (opencascade::handle<StepData_SelectMember> (StepData_SelectType::*)() const) &StepData_SelectType::NewMember, "Returns a preferred SelectMember. Default returns a Null By default, a SelectMember can be set according to data type and Name : it is a SelectNamed if Name is defined");
cls_StepData_SelectType.def("CaseMem", (Standard_Integer (StepData_SelectType::*)(const opencascade::handle<StepData_SelectMember> &) const) &StepData_SelectType::CaseMem, "Recognize a SelectMember (kind, name). Returns a positive value which identifies the case in the List of immediate cases (distinct from the List of Entity Types). Zero if not recognizes Default returns 0, saying that no immediate value is allowed", py::arg("ent"));
cls_StepData_SelectType.def("CaseMember", (Standard_Integer (StepData_SelectType::*)() const) &StepData_SelectType::CaseMember, "Returns the Type of the stored SelectMember, or zero if it is Null or Entity. Calls the method CaseMem on Value");
cls_StepData_SelectType.def("Member", (opencascade::handle<StepData_SelectMember> (StepData_SelectType::*)() const) &StepData_SelectType::Member, "Returns Value as a SelectMember. Null if not a SelectMember");
cls_StepData_SelectType.def("SelectName", (Standard_CString (StepData_SelectType::*)() const) &StepData_SelectType::SelectName, "Returns the type name of SelectMember. If no SelectMember or with no type name, returns an empty string To change it, pass through the SelectMember itself");
cls_StepData_SelectType.def("Int", (Standard_Integer (StepData_SelectType::*)() const) &StepData_SelectType::Int, "This internal method gives access to a value implemented by an Integer (to read it)");
cls_StepData_SelectType.def("SetInt", (void (StepData_SelectType::*)(const Standard_Integer)) &StepData_SelectType::SetInt, "This internal method gives access to a value implemented by an Integer (to set it) : a SelectMember MUST ALREADY BE THERE !", py::arg("val"));
cls_StepData_SelectType.def("Integer", (Standard_Integer (StepData_SelectType::*)() const) &StepData_SelectType::Integer, "Gets the value as an Integer");
cls_StepData_SelectType.def("SetInteger", [](StepData_SelectType &self, const Standard_Integer a0) -> void { return self.SetInteger(a0); });
cls_StepData_SelectType.def("SetInteger", (void (StepData_SelectType::*)(const Standard_Integer, const Standard_CString)) &StepData_SelectType::SetInteger, "Sets a new Integer value, with an optional type name Warning : If a SelectMember is already set, works on it : value and name must then be accepted by this SelectMember", py::arg("val"), py::arg("name"));
cls_StepData_SelectType.def("Boolean", (Standard_Boolean (StepData_SelectType::*)() const) &StepData_SelectType::Boolean, "None");
cls_StepData_SelectType.def("SetBoolean", [](StepData_SelectType &self, const Standard_Boolean a0) -> void { return self.SetBoolean(a0); });
cls_StepData_SelectType.def("SetBoolean", (void (StepData_SelectType::*)(const Standard_Boolean, const Standard_CString)) &StepData_SelectType::SetBoolean, "None", py::arg("val"), py::arg("name"));
cls_StepData_SelectType.def("Logical", (StepData_Logical (StepData_SelectType::*)() const) &StepData_SelectType::Logical, "None");
cls_StepData_SelectType.def("SetLogical", [](StepData_SelectType &self, const StepData_Logical a0) -> void { return self.SetLogical(a0); });
cls_StepData_SelectType.def("SetLogical", (void (StepData_SelectType::*)(const StepData_Logical, const Standard_CString)) &StepData_SelectType::SetLogical, "None", py::arg("val"), py::arg("name"));
cls_StepData_SelectType.def("Real", (Standard_Real (StepData_SelectType::*)() const) &StepData_SelectType::Real, "None");
cls_StepData_SelectType.def("SetReal", [](StepData_SelectType &self, const Standard_Real a0) -> void { return self.SetReal(a0); });
cls_StepData_SelectType.def("SetReal", (void (StepData_SelectType::*)(const Standard_Real, const Standard_CString)) &StepData_SelectType::SetReal, "None", py::arg("val"), py::arg("name"));

// CLASS: STEPDATA_SELECTMEMBER
py::class_<StepData_SelectMember, opencascade::handle<StepData_SelectMember>, Standard_Transient> cls_StepData_SelectMember(mod, "StepData_SelectMember", "The general form for a Select Member. A Select Member can, either define a value of a basic type (such as an integer) with an additional information : a name or list of names which precise the meaning of this value or be an alternate value in a select, which also accepts an entity (in this case, the name is not mandatory)");

// Constructors
cls_StepData_SelectMember.def(py::init<>());

// Methods
cls_StepData_SelectMember.def("HasName", (Standard_Boolean (StepData_SelectMember::*)() const) &StepData_SelectMember::HasName, "Tells if a SelectMember has a name. Default is False");
cls_StepData_SelectMember.def("Name", (Standard_CString (StepData_SelectMember::*)() const) &StepData_SelectMember::Name, "Returns the name of a SelectMember. Default is empty");
cls_StepData_SelectMember.def("SetName", (Standard_Boolean (StepData_SelectMember::*)(const Standard_CString)) &StepData_SelectMember::SetName, "Sets the name of a SelectMember, returns True if done, False if no name is allowed Default does nothing and returns False", py::arg("name"));
cls_StepData_SelectMember.def("Matches", (Standard_Boolean (StepData_SelectMember::*)(const Standard_CString) const) &StepData_SelectMember::Matches, "Tells if the name of a SelectMember matches a given one By default, compares the strings, can be redefined (optimised)", py::arg("name"));
cls_StepData_SelectMember.def("Kind", (Standard_Integer (StepData_SelectMember::*)() const) &StepData_SelectMember::Kind, "None");
cls_StepData_SelectMember.def("SetKind", (void (StepData_SelectMember::*)(const Standard_Integer)) &StepData_SelectMember::SetKind, "None", py::arg("kind"));
cls_StepData_SelectMember.def("ParamType", (Interface_ParamType (StepData_SelectMember::*)() const) &StepData_SelectMember::ParamType, "Returns the Kind of the SelectMember, under the form of an enum ParamType");
cls_StepData_SelectMember.def("Int", (Standard_Integer (StepData_SelectMember::*)() const) &StepData_SelectMember::Int, "This internal method gives access to a value implemented by an Integer (to read it)");
cls_StepData_SelectMember.def("SetInt", (void (StepData_SelectMember::*)(const Standard_Integer)) &StepData_SelectMember::SetInt, "This internal method gives access to a value implemented by an Integer (to set it)", py::arg("val"));
cls_StepData_SelectMember.def("Integer", (Standard_Integer (StepData_SelectMember::*)() const) &StepData_SelectMember::Integer, "Gets the value as an Integer");
cls_StepData_SelectMember.def("SetInteger", (void (StepData_SelectMember::*)(const Standard_Integer)) &StepData_SelectMember::SetInteger, "None", py::arg("val"));
cls_StepData_SelectMember.def("Boolean", (Standard_Boolean (StepData_SelectMember::*)() const) &StepData_SelectMember::Boolean, "None");
cls_StepData_SelectMember.def("SetBoolean", (void (StepData_SelectMember::*)(const Standard_Boolean)) &StepData_SelectMember::SetBoolean, "None", py::arg("val"));
cls_StepData_SelectMember.def("Logical", (StepData_Logical (StepData_SelectMember::*)() const) &StepData_SelectMember::Logical, "None");
cls_StepData_SelectMember.def("SetLogical", (void (StepData_SelectMember::*)(const StepData_Logical)) &StepData_SelectMember::SetLogical, "None", py::arg("val"));
cls_StepData_SelectMember.def("Real", (Standard_Real (StepData_SelectMember::*)() const) &StepData_SelectMember::Real, "None");
cls_StepData_SelectMember.def("SetReal", (void (StepData_SelectMember::*)(const Standard_Real)) &StepData_SelectMember::SetReal, "None", py::arg("val"));
cls_StepData_SelectMember.def("String", (Standard_CString (StepData_SelectMember::*)() const) &StepData_SelectMember::String, "None");
cls_StepData_SelectMember.def("SetString", (void (StepData_SelectMember::*)(const Standard_CString)) &StepData_SelectMember::SetString, "None", py::arg("val"));
cls_StepData_SelectMember.def("Enum", (Standard_Integer (StepData_SelectMember::*)() const) &StepData_SelectMember::Enum, "None");
cls_StepData_SelectMember.def("EnumText", (Standard_CString (StepData_SelectMember::*)() const) &StepData_SelectMember::EnumText, "None");
cls_StepData_SelectMember.def("SetEnum", [](StepData_SelectMember &self, const Standard_Integer a0) -> void { return self.SetEnum(a0); });
cls_StepData_SelectMember.def("SetEnum", (void (StepData_SelectMember::*)(const Standard_Integer, const Standard_CString)) &StepData_SelectMember::SetEnum, "None", py::arg("val"), py::arg("text"));
cls_StepData_SelectMember.def("SetEnumText", (void (StepData_SelectMember::*)(const Standard_Integer, const Standard_CString)) &StepData_SelectMember::SetEnumText, "None", py::arg("val"), py::arg("text"));
cls_StepData_SelectMember.def_static("get_type_name_", (const char * (*)()) &StepData_SelectMember::get_type_name, "None");
cls_StepData_SelectMember.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_SelectMember::get_type_descriptor, "None");
cls_StepData_SelectMember.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_SelectMember::*)() const) &StepData_SelectMember::DynamicType, "None");

// CLASS: STEPDATA_SELECTREAL
py::class_<StepData_SelectReal, opencascade::handle<StepData_SelectReal>, StepData_SelectMember> cls_StepData_SelectReal(mod, "StepData_SelectReal", "A SelectReal is a SelectMember specialised for a basic real type in a select which also accepts entities : this one has NO NAME For a named select, see SelectNamed");

// Constructors
cls_StepData_SelectReal.def(py::init<>());

// Methods
cls_StepData_SelectReal.def("Kind", (Standard_Integer (StepData_SelectReal::*)() const) &StepData_SelectReal::Kind, "None");
cls_StepData_SelectReal.def("Real", (Standard_Real (StepData_SelectReal::*)() const) &StepData_SelectReal::Real, "None");
cls_StepData_SelectReal.def("SetReal", (void (StepData_SelectReal::*)(const Standard_Real)) &StepData_SelectReal::SetReal, "None", py::arg("val"));
cls_StepData_SelectReal.def_static("get_type_name_", (const char * (*)()) &StepData_SelectReal::get_type_name, "None");
cls_StepData_SelectReal.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_SelectReal::get_type_descriptor, "None");
cls_StepData_SelectReal.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_SelectReal::*)() const) &StepData_SelectReal::DynamicType, "None");

// CLASS: STEPDATA_SELECTINT
py::class_<StepData_SelectInt, opencascade::handle<StepData_SelectInt>, StepData_SelectMember> cls_StepData_SelectInt(mod, "StepData_SelectInt", "A SelectInt is a SelectMember specialised for a basic integer type in a select which also accepts entities : this one has NO NAME. For a named select, see SelectNamed");

// Constructors
cls_StepData_SelectInt.def(py::init<>());

// Methods
cls_StepData_SelectInt.def("Kind", (Standard_Integer (StepData_SelectInt::*)() const) &StepData_SelectInt::Kind, "None");
cls_StepData_SelectInt.def("SetKind", (void (StepData_SelectInt::*)(const Standard_Integer)) &StepData_SelectInt::SetKind, "None", py::arg("kind"));
cls_StepData_SelectInt.def("Int", (Standard_Integer (StepData_SelectInt::*)() const) &StepData_SelectInt::Int, "None");
cls_StepData_SelectInt.def("SetInt", (void (StepData_SelectInt::*)(const Standard_Integer)) &StepData_SelectInt::SetInt, "None", py::arg("val"));
cls_StepData_SelectInt.def_static("get_type_name_", (const char * (*)()) &StepData_SelectInt::get_type_name, "None");
cls_StepData_SelectInt.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_SelectInt::get_type_descriptor, "None");
cls_StepData_SelectInt.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_SelectInt::*)() const) &StepData_SelectInt::DynamicType, "None");

// CLASS: STEPDATA
py::class_<StepData> cls_StepData(mod, "StepData", "Gives basic data definition for Step Interface. Any class of a data model described in EXPRESS Language is candidate to be managed by a Step Interface");

// Constructors
cls_StepData.def(py::init<>());

// Methods
// cls_StepData.def_static("operator new_", (void * (*)(size_t)) &StepData::operator new, "None", py::arg("theSize"));
// cls_StepData.def_static("operator delete_", (void (*)(void *)) &StepData::operator delete, "None", py::arg("theAddress"));
// cls_StepData.def_static("operator new[]_", (void * (*)(size_t)) &StepData::operator new[], "None", py::arg("theSize"));
// cls_StepData.def_static("operator delete[]_", (void (*)(void *)) &StepData::operator delete[], "None", py::arg("theAddress"));
// cls_StepData.def_static("operator new_", (void * (*)(size_t, void *)) &StepData::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData.def_static("operator delete_", (void (*)(void *, void *)) &StepData::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData.def_static("HeaderProtocol_", (opencascade::handle<StepData_Protocol> (*)()) &StepData::HeaderProtocol, "Returns the recorded HeaderProtocol, which can be : - a Null Handle if no Header Protocol was yet defined - a simple Protocol if only one was defined - a FileProtocol if more than one Protocol was yet defined");
cls_StepData.def_static("AddHeaderProtocol_", (void (*)(const opencascade::handle<StepData_Protocol> &)) &StepData::AddHeaderProtocol, "Adds a new Header Protocol to the Header Definition", py::arg("headerproto"));
cls_StepData.def_static("Init_", (void (*)()) &StepData::Init, "Prepares General Data required to work with this package, which are the Protocol and Modules to be loaded into Libraries");
cls_StepData.def_static("Protocol_", (opencascade::handle<StepData_Protocol> (*)()) &StepData::Protocol, "Returns a Protocol from StepData (avoids to create it)");

// CLASS: STEPDATA_FIELD
py::class_<StepData_Field> cls_StepData_Field(mod, "StepData_Field", "Defines a generally defined Field for STEP data : can be used either in any kind of entity to implement it or in free format entities in a 'late-binding' mode A field can have : no value (or derived), a single value of any kind, a list of value : single or double list");

// Constructors
cls_StepData_Field.def(py::init<>());
cls_StepData_Field.def(py::init<const StepData_Field &>(), py::arg("other"));
cls_StepData_Field.def(py::init<const StepData_Field &, const Standard_Boolean>(), py::arg("other"), py::arg("copy"));

// Methods
// cls_StepData_Field.def_static("operator new_", (void * (*)(size_t)) &StepData_Field::operator new, "None", py::arg("theSize"));
// cls_StepData_Field.def_static("operator delete_", (void (*)(void *)) &StepData_Field::operator delete, "None", py::arg("theAddress"));
// cls_StepData_Field.def_static("operator new[]_", (void * (*)(size_t)) &StepData_Field::operator new[], "None", py::arg("theSize"));
// cls_StepData_Field.def_static("operator delete[]_", (void (*)(void *)) &StepData_Field::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_Field.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_Field::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_Field.def_static("operator delete_", (void (*)(void *, void *)) &StepData_Field::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_Field.def("CopyFrom", (void (StepData_Field::*)(const StepData_Field &)) &StepData_Field::CopyFrom, "Gets the copy of the values of another field", py::arg("other"));
cls_StepData_Field.def("Clear", [](StepData_Field &self) -> void { return self.Clear(); });
cls_StepData_Field.def("Clear", (void (StepData_Field::*)(const Standard_Integer)) &StepData_Field::Clear, "Clears the field, to set it as 'no value defined' Just before SetList, predeclares it as 'any' A Kind can be directly set here to declare a type", py::arg("kind"));
cls_StepData_Field.def("SetDerived", (void (StepData_Field::*)()) &StepData_Field::SetDerived, "Codes a Field as derived (no proper value)");
cls_StepData_Field.def("SetInt", (void (StepData_Field::*)(const Standard_Integer)) &StepData_Field::SetInt, "Directly sets the Integer value, if its Kind matches Integer, Boolean, Logical, or Enum (does not change Kind)", py::arg("val"));
cls_StepData_Field.def("SetInteger", [](StepData_Field &self) -> void { return self.SetInteger(); });
cls_StepData_Field.def("SetInteger", (void (StepData_Field::*)(const Standard_Integer)) &StepData_Field::SetInteger, "Sets an Integer value (before SetList* declares it as Integer)", py::arg("val"));
cls_StepData_Field.def("SetBoolean", [](StepData_Field &self) -> void { return self.SetBoolean(); });
cls_StepData_Field.def("SetBoolean", (void (StepData_Field::*)(const Standard_Boolean)) &StepData_Field::SetBoolean, "Sets a Boolean value (or predeclares a list as boolean)", py::arg("val"));
cls_StepData_Field.def("SetLogical", [](StepData_Field &self) -> void { return self.SetLogical(); });
cls_StepData_Field.def("SetLogical", (void (StepData_Field::*)(const StepData_Logical)) &StepData_Field::SetLogical, "Sets a Logical Value (or predeclares a list as logical)", py::arg("val"));
cls_StepData_Field.def("SetReal", [](StepData_Field &self) -> void { return self.SetReal(); });
cls_StepData_Field.def("SetReal", (void (StepData_Field::*)(const Standard_Real)) &StepData_Field::SetReal, "Sets a Real Value (or predeclares a list as Real);", py::arg("val"));
cls_StepData_Field.def("SetString", [](StepData_Field &self) -> void { return self.SetString(); });
cls_StepData_Field.def("SetString", (void (StepData_Field::*)(const Standard_CString)) &StepData_Field::SetString, "Sets a String Value (or predeclares a list as String) Does not redefine the Kind if it is alread String or Enum", py::arg("val"));
cls_StepData_Field.def("SetEnum", [](StepData_Field &self) -> void { return self.SetEnum(); });
cls_StepData_Field.def("SetEnum", [](StepData_Field &self, const Standard_Integer a0) -> void { return self.SetEnum(a0); });
cls_StepData_Field.def("SetEnum", (void (StepData_Field::*)(const Standard_Integer, const Standard_CString)) &StepData_Field::SetEnum, "Sets an Enum Value (as its integer counterpart) (or predeclares a list as Enum) If <text> is given , also sets its textual expression <val> negative means unknown (known values begin at 0)", py::arg("val"), py::arg("text"));
cls_StepData_Field.def("SetSelectMember", (void (StepData_Field::*)(const opencascade::handle<StepData_SelectMember> &)) &StepData_Field::SetSelectMember, "Sets a SelectMember (for Integer,Boolean,Enum,Real,Logical) Hence, the value of the field is accessed through this member", py::arg("val"));
cls_StepData_Field.def("SetEntity", (void (StepData_Field::*)(const opencascade::handle<Standard_Transient> &)) &StepData_Field::SetEntity, "Sets an Entity Value", py::arg("val"));
cls_StepData_Field.def("SetEntity", (void (StepData_Field::*)()) &StepData_Field::SetEntity, "Predeclares a list as of entity");
cls_StepData_Field.def("SetList", [](StepData_Field &self, const Standard_Integer a0) -> void { return self.SetList(a0); });
cls_StepData_Field.def("SetList", (void (StepData_Field::*)(const Standard_Integer, const Standard_Integer)) &StepData_Field::SetList, "Declares a field as a list, with an initial size Initial lower is defaulted as 1, can be defined The list starts empty, typed by the last Set* If no Set* before, sets it as 'any' (transient/select)", py::arg("size"), py::arg("first"));
cls_StepData_Field.def("SetList2", [](StepData_Field &self, const Standard_Integer a0, const Standard_Integer a1) -> void { return self.SetList2(a0, a1); });
cls_StepData_Field.def("SetList2", [](StepData_Field &self, const Standard_Integer a0, const Standard_Integer a1, const Standard_Integer a2) -> void { return self.SetList2(a0, a1, a2); });
cls_StepData_Field.def("SetList2", (void (StepData_Field::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer)) &StepData_Field::SetList2, "Declares a field as an homogeneous square list, with initial sizes, and initial lowers", py::arg("siz1"), py::arg("siz2"), py::arg("f1"), py::arg("f2"));
cls_StepData_Field.def("Set", (void (StepData_Field::*)(const opencascade::handle<Standard_Transient> &)) &StepData_Field::Set, "Sets an undetermined value : can be String, SelectMember, HArray(1-2) ... else, an Entity In case of an HArray, determines and records its size(s)", py::arg("val"));
cls_StepData_Field.def("ClearItem", (void (StepData_Field::*)(const Standard_Integer)) &StepData_Field::ClearItem, "Declares an item of the list as undefined (ignored if list not defined as String,Entity or Any)", py::arg("num"));
cls_StepData_Field.def("SetInt", (void (StepData_Field::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer)) &StepData_Field::SetInt, "Internal access to an Integer Value for a list, plus its kind", py::arg("num"), py::arg("val"), py::arg("kind"));
cls_StepData_Field.def("SetInteger", (void (StepData_Field::*)(const Standard_Integer, const Standard_Integer)) &StepData_Field::SetInteger, "Sets an Integer Value for a list (rank num) (recognizes a SelectMember)", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("SetBoolean", (void (StepData_Field::*)(const Standard_Integer, const Standard_Boolean)) &StepData_Field::SetBoolean, "None", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("SetLogical", (void (StepData_Field::*)(const Standard_Integer, const StepData_Logical)) &StepData_Field::SetLogical, "None", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("SetEnum", [](StepData_Field &self, const Standard_Integer a0, const Standard_Integer a1) -> void { return self.SetEnum(a0, a1); });
cls_StepData_Field.def("SetEnum", (void (StepData_Field::*)(const Standard_Integer, const Standard_Integer, const Standard_CString)) &StepData_Field::SetEnum, "Sets an Enum Value (Integer counterpart), also its text expression if known (if list has been set as 'any')", py::arg("num"), py::arg("val"), py::arg("text"));
cls_StepData_Field.def("SetReal", (void (StepData_Field::*)(const Standard_Integer, const Standard_Real)) &StepData_Field::SetReal, "None", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("SetString", (void (StepData_Field::*)(const Standard_Integer, const Standard_CString)) &StepData_Field::SetString, "None", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("SetEntity", (void (StepData_Field::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &)) &StepData_Field::SetEntity, "None", py::arg("num"), py::arg("val"));
cls_StepData_Field.def("IsSet", [](StepData_Field &self) -> Standard_Boolean { return self.IsSet(); });
cls_StepData_Field.def("IsSet", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Boolean { return self.IsSet(a0); });
cls_StepData_Field.def("IsSet", (Standard_Boolean (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::IsSet, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("ItemKind", [](StepData_Field &self) -> Standard_Integer { return self.ItemKind(); });
cls_StepData_Field.def("ItemKind", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Integer { return self.ItemKind(a0); });
cls_StepData_Field.def("ItemKind", (Standard_Integer (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::ItemKind, "Returns the kind of an item in a list or double list It is the kind of the list, except if it is 'Any', in such a case the true kind is determined and returned", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Kind", [](StepData_Field &self) -> Standard_Integer { return self.Kind(); });
cls_StepData_Field.def("Kind", (Standard_Integer (StepData_Field::*)(const Standard_Boolean) const) &StepData_Field::Kind, "Returns the kind of the field <type> True (D) : returns only the type itself else, returns the complete kind", py::arg("type"));
cls_StepData_Field.def("Arity", (Standard_Integer (StepData_Field::*)() const) &StepData_Field::Arity, "None");
cls_StepData_Field.def("Length", [](StepData_Field &self) -> Standard_Integer { return self.Length(); });
cls_StepData_Field.def("Length", (Standard_Integer (StepData_Field::*)(const Standard_Integer) const) &StepData_Field::Length, "None", py::arg("index"));
cls_StepData_Field.def("Lower", [](StepData_Field &self) -> Standard_Integer { return self.Lower(); });
cls_StepData_Field.def("Lower", (Standard_Integer (StepData_Field::*)(const Standard_Integer) const) &StepData_Field::Lower, "None", py::arg("index"));
cls_StepData_Field.def("Int", (Standard_Integer (StepData_Field::*)() const) &StepData_Field::Int, "None");
cls_StepData_Field.def("Integer", [](StepData_Field &self) -> Standard_Integer { return self.Integer(); });
cls_StepData_Field.def("Integer", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Integer { return self.Integer(a0); });
cls_StepData_Field.def("Integer", (Standard_Integer (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Integer, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Boolean", [](StepData_Field &self) -> Standard_Boolean { return self.Boolean(); });
cls_StepData_Field.def("Boolean", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Boolean { return self.Boolean(a0); });
cls_StepData_Field.def("Boolean", (Standard_Boolean (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Boolean, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Logical", [](StepData_Field &self) -> StepData_Logical { return self.Logical(); });
cls_StepData_Field.def("Logical", [](StepData_Field &self, const Standard_Integer a0) -> StepData_Logical { return self.Logical(a0); });
cls_StepData_Field.def("Logical", (StepData_Logical (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Logical, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Real", [](StepData_Field &self) -> Standard_Real { return self.Real(); });
cls_StepData_Field.def("Real", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Real { return self.Real(a0); });
cls_StepData_Field.def("Real", (Standard_Real (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Real, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("String", [](StepData_Field &self) -> Standard_CString { return self.String(); });
cls_StepData_Field.def("String", [](StepData_Field &self, const Standard_Integer a0) -> Standard_CString { return self.String(a0); });
cls_StepData_Field.def("String", (Standard_CString (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::String, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Enum", [](StepData_Field &self) -> Standard_Integer { return self.Enum(); });
cls_StepData_Field.def("Enum", [](StepData_Field &self, const Standard_Integer a0) -> Standard_Integer { return self.Enum(a0); });
cls_StepData_Field.def("Enum", (Standard_Integer (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Enum, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("EnumText", [](StepData_Field &self) -> Standard_CString { return self.EnumText(); });
cls_StepData_Field.def("EnumText", [](StepData_Field &self, const Standard_Integer a0) -> Standard_CString { return self.EnumText(a0); });
cls_StepData_Field.def("EnumText", (Standard_CString (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::EnumText, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Entity", [](StepData_Field &self) -> opencascade::handle<Standard_Transient> { return self.Entity(); });
cls_StepData_Field.def("Entity", [](StepData_Field &self, const Standard_Integer a0) -> opencascade::handle<Standard_Transient> { return self.Entity(a0); });
cls_StepData_Field.def("Entity", (opencascade::handle<Standard_Transient> (StepData_Field::*)(const Standard_Integer, const Standard_Integer) const) &StepData_Field::Entity, "None", py::arg("n1"), py::arg("n2"));
cls_StepData_Field.def("Transient", (opencascade::handle<Standard_Transient> (StepData_Field::*)() const) &StepData_Field::Transient, "None");

// TYPEDEF: STEPDATA_ARRAY1OFFIELD
bind_NCollection_Array1<StepData_Field>(mod, "StepData_Array1OfField", py::module_local(false));

// CLASS: STEPDATA_DEFAULTGENERAL
py::class_<StepData_DefaultGeneral, opencascade::handle<StepData_DefaultGeneral>, StepData_GeneralModule> cls_StepData_DefaultGeneral(mod, "StepData_DefaultGeneral", "DefaultGeneral defines a GeneralModule which processes Unknown Entity from StepData only");

// Constructors
cls_StepData_DefaultGeneral.def(py::init<>());

// Methods
cls_StepData_DefaultGeneral.def("FillSharedCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, Interface_EntityIterator &) const) &StepData_DefaultGeneral::FillSharedCase, "Specific filling of the list of Entities shared by an Entity <ent>, which is an UnknownEntity from StepData.", py::arg("casenum"), py::arg("ent"), py::arg("iter"));
cls_StepData_DefaultGeneral.def("CheckCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &StepData_DefaultGeneral::CheckCase, "Specific Checking of an Entity <ent>", py::arg("casenum"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_StepData_DefaultGeneral.def("NewVoid", (Standard_Boolean (StepData_DefaultGeneral::*)(const Standard_Integer, opencascade::handle<Standard_Transient> &) const) &StepData_DefaultGeneral::NewVoid, "Specific creation of a new void entity", py::arg("CN"), py::arg("entto"));
cls_StepData_DefaultGeneral.def("CopyCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const opencascade::handle<Standard_Transient> &, Interface_CopyTool &) const) &StepData_DefaultGeneral::CopyCase, "Specific Copy ('Deep') from <entfrom> to <entto> (same type) by using a CopyTool which provides its working Map. Use method Transferred from TransferControl to work", py::arg("casenum"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_StepData_DefaultGeneral.def_static("get_type_name_", (const char * (*)()) &StepData_DefaultGeneral::get_type_name, "None");
cls_StepData_DefaultGeneral.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_DefaultGeneral::get_type_descriptor, "None");
cls_StepData_DefaultGeneral.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_DefaultGeneral::*)() const) &StepData_DefaultGeneral::DynamicType, "None");

// CLASS: STEPDATA_DESCRIBED
py::class_<StepData_Described, opencascade::handle<StepData_Described>, Standard_Transient> cls_StepData_Described(mod, "StepData_Described", "General frame to describe entities with Description (Simple or Complex)");

// Methods
cls_StepData_Described.def("Description", (opencascade::handle<StepData_EDescr> (StepData_Described::*)() const) &StepData_Described::Description, "Returns the Description used to define this entity");
cls_StepData_Described.def("IsComplex", (Standard_Boolean (StepData_Described::*)() const) &StepData_Described::IsComplex, "Tells if a described entity is complex");
cls_StepData_Described.def("Matches", (Standard_Boolean (StepData_Described::*)(const Standard_CString) const) &StepData_Described::Matches, "Tells if a step type is matched by <me> For a Simple Entity : own type or super type For a Complex Entity : one of the members", py::arg("steptype"));
cls_StepData_Described.def("As", (opencascade::handle<StepData_Simple> (StepData_Described::*)(const Standard_CString) const) &StepData_Described::As, "Returns a Simple Entity which matches with a Type in <me> : For a Simple Entity : me if it matches, else a null handle For a Complex Entity : the member which matches, else null", py::arg("steptype"));
cls_StepData_Described.def("HasField", (Standard_Boolean (StepData_Described::*)(const Standard_CString) const) &StepData_Described::HasField, "Tells if a Field brings a given name", py::arg("name"));
cls_StepData_Described.def("Field", (const StepData_Field & (StepData_Described::*)(const Standard_CString) const) &StepData_Described::Field, "Returns a Field from its name; read-only", py::arg("name"));
cls_StepData_Described.def("CField", (StepData_Field & (StepData_Described::*)(const Standard_CString)) &StepData_Described::CField, "Returns a Field from its name; read or write", py::arg("name"));
cls_StepData_Described.def("Check", (void (StepData_Described::*)(opencascade::handle<Interface_Check> &) const) &StepData_Described::Check, "Fills a Check by using its Description", py::arg("ach"));
cls_StepData_Described.def("Shared", (void (StepData_Described::*)(Interface_EntityIterator &) const) &StepData_Described::Shared, "Fills an EntityIterator with entities shared by <me>", py::arg("list"));
cls_StepData_Described.def_static("get_type_name_", (const char * (*)()) &StepData_Described::get_type_name, "None");
cls_StepData_Described.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_Described::get_type_descriptor, "None");
cls_StepData_Described.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_Described::*)() const) &StepData_Described::DynamicType, "None");

// CLASS: STEPDATA_EDESCR
py::class_<StepData_EDescr, opencascade::handle<StepData_EDescr>, Standard_Transient> cls_StepData_EDescr(mod, "StepData_EDescr", "This class is intended to describe the authorized form for an entity, either Simple or Plex");

// Methods
cls_StepData_EDescr.def("Matches", (Standard_Boolean (StepData_EDescr::*)(const Standard_CString) const) &StepData_EDescr::Matches, "Tells if a ESDescr matches a step type : exact or super type", py::arg("steptype"));
cls_StepData_EDescr.def("IsComplex", (Standard_Boolean (StepData_EDescr::*)() const) &StepData_EDescr::IsComplex, "Tells if a EDescr is complex (ECDescr) or simple (ESDescr)");
cls_StepData_EDescr.def("NewEntity", (opencascade::handle<StepData_Described> (StepData_EDescr::*)() const) &StepData_EDescr::NewEntity, "Creates a described entity (i.e. a simple one)");
cls_StepData_EDescr.def_static("get_type_name_", (const char * (*)()) &StepData_EDescr::get_type_name, "None");
cls_StepData_EDescr.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_EDescr::get_type_descriptor, "None");
cls_StepData_EDescr.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_EDescr::*)() const) &StepData_EDescr::DynamicType, "None");

// CLASS: STEPDATA_ECDESCR
py::class_<StepData_ECDescr, opencascade::handle<StepData_ECDescr>, StepData_EDescr> cls_StepData_ECDescr(mod, "StepData_ECDescr", "Describes a Complex Entity (Plex) as a list of Simple ones");

// Constructors
cls_StepData_ECDescr.def(py::init<>());

// Methods
cls_StepData_ECDescr.def("Add", (void (StepData_ECDescr::*)(const opencascade::handle<StepData_ESDescr> &)) &StepData_ECDescr::Add, "Adds a member Warning : members are added in alphabetic order", py::arg("member"));
cls_StepData_ECDescr.def("NbMembers", (Standard_Integer (StepData_ECDescr::*)() const) &StepData_ECDescr::NbMembers, "Returns the count of members");
cls_StepData_ECDescr.def("Member", (opencascade::handle<StepData_ESDescr> (StepData_ECDescr::*)(const Standard_Integer) const) &StepData_ECDescr::Member, "Returns a Member from its rank", py::arg("num"));
cls_StepData_ECDescr.def("TypeList", (opencascade::handle<TColStd_HSequenceOfAsciiString> (StepData_ECDescr::*)() const) &StepData_ECDescr::TypeList, "Returns the ordered list of types");
cls_StepData_ECDescr.def("Matches", (Standard_Boolean (StepData_ECDescr::*)(const Standard_CString) const) &StepData_ECDescr::Matches, "Tells if a ESDescr matches a step type : exact or super type", py::arg("steptype"));
cls_StepData_ECDescr.def("IsComplex", (Standard_Boolean (StepData_ECDescr::*)() const) &StepData_ECDescr::IsComplex, "Returns True");
cls_StepData_ECDescr.def("NewEntity", (opencascade::handle<StepData_Described> (StepData_ECDescr::*)() const) &StepData_ECDescr::NewEntity, "Creates a described entity (i.e. a complex one, made of one simple entity per member)");
cls_StepData_ECDescr.def_static("get_type_name_", (const char * (*)()) &StepData_ECDescr::get_type_name, "None");
cls_StepData_ECDescr.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_ECDescr::get_type_descriptor, "None");
cls_StepData_ECDescr.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_ECDescr::*)() const) &StepData_ECDescr::DynamicType, "None");

// CLASS: STEPDATA_ENUMTOOL
py::class_<StepData_EnumTool> cls_StepData_EnumTool(mod, "StepData_EnumTool", "This class gives a way of conversion between the value of an enumeration and its representation in STEP An enumeration corresponds to an integer with reserved values, which begin to 0 In STEP, it is represented by a name in capital letter and limited by two dots, e.g. .UNKNOWN.");

// Constructors
cls_StepData_EnumTool.def(py::init<>());
cls_StepData_EnumTool.def(py::init<const Standard_CString>(), py::arg("e0"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"), py::arg("e35"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"), py::arg("e35"), py::arg("e36"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"), py::arg("e35"), py::arg("e36"), py::arg("e37"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"), py::arg("e35"), py::arg("e36"), py::arg("e37"), py::arg("e38"));
cls_StepData_EnumTool.def(py::init<const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString, const Standard_CString>(), py::arg("e0"), py::arg("e1"), py::arg("e2"), py::arg("e3"), py::arg("e4"), py::arg("e5"), py::arg("e6"), py::arg("e7"), py::arg("e8"), py::arg("e9"), py::arg("e10"), py::arg("e11"), py::arg("e12"), py::arg("e13"), py::arg("e14"), py::arg("e15"), py::arg("e16"), py::arg("e17"), py::arg("e18"), py::arg("e19"), py::arg("e20"), py::arg("e21"), py::arg("e22"), py::arg("e23"), py::arg("e24"), py::arg("e25"), py::arg("e26"), py::arg("e27"), py::arg("e28"), py::arg("e29"), py::arg("e30"), py::arg("e31"), py::arg("e32"), py::arg("e33"), py::arg("e34"), py::arg("e35"), py::arg("e36"), py::arg("e37"), py::arg("e38"), py::arg("e39"));

// Methods
// cls_StepData_EnumTool.def_static("operator new_", (void * (*)(size_t)) &StepData_EnumTool::operator new, "None", py::arg("theSize"));
// cls_StepData_EnumTool.def_static("operator delete_", (void (*)(void *)) &StepData_EnumTool::operator delete, "None", py::arg("theAddress"));
// cls_StepData_EnumTool.def_static("operator new[]_", (void * (*)(size_t)) &StepData_EnumTool::operator new[], "None", py::arg("theSize"));
// cls_StepData_EnumTool.def_static("operator delete[]_", (void (*)(void *)) &StepData_EnumTool::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_EnumTool.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_EnumTool::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_EnumTool.def_static("operator delete_", (void (*)(void *, void *)) &StepData_EnumTool::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_EnumTool.def("AddDefinition", (void (StepData_EnumTool::*)(const Standard_CString)) &StepData_EnumTool::AddDefinition, "Processes a definition, splits it according blanks if any empty definitions are ignored A null definition can be input by given '$' :the corresponding position is attached to 'null/undefined' value (as one particular item of the enumeration list) See also IsSet", py::arg("term"));
cls_StepData_EnumTool.def("IsSet", (Standard_Boolean (StepData_EnumTool::*)() const) &StepData_EnumTool::IsSet, "Returns True if at least one definition has been entered after creation time (i.e. by AddDefinition only)");
cls_StepData_EnumTool.def("MaxValue", (Standard_Integer (StepData_EnumTool::*)() const) &StepData_EnumTool::MaxValue, "Returns the maximum integer for a suitable value Remark : while values begin at zero, MaxValue is the count of recorded values minus one");
cls_StepData_EnumTool.def("Optional", (void (StepData_EnumTool::*)(const Standard_Boolean)) &StepData_EnumTool::Optional, "Sets or Unsets the EnumTool to accept undefined value (for optional field). Ignored if no null value is defined (by '$') Can be changed during execution (to read each field), Default is True (if a null value is defined)", py::arg("mode"));
cls_StepData_EnumTool.def("NullValue", (Standard_Integer (StepData_EnumTool::*)() const) &StepData_EnumTool::NullValue, "Returns the value attached to 'null/undefined value' If none is specified or if Optional has been set to False, returns -1 Null Value has been specified by definition '$'");
cls_StepData_EnumTool.def("Text", (const TCollection_AsciiString & (StepData_EnumTool::*)(const Standard_Integer) const) &StepData_EnumTool::Text, "Returns the text which corresponds to a given numeric value It is limited by dots If num is out of range, returns an empty string", py::arg("num"));
cls_StepData_EnumTool.def("Value", (Standard_Integer (StepData_EnumTool::*)(const Standard_CString) const) &StepData_EnumTool::Value, "Returns the numeric value found for a text The text must be in capitals and limited by dots A non-suitable text gives a negative value to be returned", py::arg("txt"));
cls_StepData_EnumTool.def("Value", (Standard_Integer (StepData_EnumTool::*)(const TCollection_AsciiString &) const) &StepData_EnumTool::Value, "Same as above but works on an AsciiString", py::arg("txt"));

// CLASS: STEPDATA_ESDESCR
py::class_<StepData_ESDescr, opencascade::handle<StepData_ESDescr>, StepData_EDescr> cls_StepData_ESDescr(mod, "StepData_ESDescr", "This class is intended to describe the authorized form for a Simple (not Plex) Entity, as a list of fields");

// Constructors
cls_StepData_ESDescr.def(py::init<const Standard_CString>(), py::arg("name"));

// Methods
cls_StepData_ESDescr.def("SetNbFields", (void (StepData_ESDescr::*)(const Standard_Integer)) &StepData_ESDescr::SetNbFields, "Sets a new count of fields Each one is described by a PDescr", py::arg("nb"));
cls_StepData_ESDescr.def("SetField", (void (StepData_ESDescr::*)(const Standard_Integer, const Standard_CString, const opencascade::handle<StepData_PDescr> &)) &StepData_ESDescr::SetField, "Sets a PDescr to describe a field A Field is designated by its rank and name", py::arg("num"), py::arg("name"), py::arg("descr"));
cls_StepData_ESDescr.def("SetBase", (void (StepData_ESDescr::*)(const opencascade::handle<StepData_ESDescr> &)) &StepData_ESDescr::SetBase, "Sets an ESDescr as based on another one Hence, if there are inherited fields, the derived ESDescr cumulates all them, while the base just records its own ones", py::arg("base"));
cls_StepData_ESDescr.def("SetSuper", (void (StepData_ESDescr::*)(const opencascade::handle<StepData_ESDescr> &)) &StepData_ESDescr::SetSuper, "Sets an ESDescr as 'super-type'. Applies an a base (non derived) ESDescr", py::arg("super"));
cls_StepData_ESDescr.def("TypeName", (Standard_CString (StepData_ESDescr::*)() const) &StepData_ESDescr::TypeName, "Returns the type name given at creation time");
cls_StepData_ESDescr.def("StepType", (const TCollection_AsciiString & (StepData_ESDescr::*)() const) &StepData_ESDescr::StepType, "Returns the type name as an AsciiString");
cls_StepData_ESDescr.def("Base", (opencascade::handle<StepData_ESDescr> (StepData_ESDescr::*)() const) &StepData_ESDescr::Base, "Returns the basic ESDescr, null if <me> is not derived");
cls_StepData_ESDescr.def("Super", (opencascade::handle<StepData_ESDescr> (StepData_ESDescr::*)() const) &StepData_ESDescr::Super, "Returns the super-type ESDescr, null if <me> is root");
cls_StepData_ESDescr.def("IsSub", (Standard_Boolean (StepData_ESDescr::*)(const opencascade::handle<StepData_ESDescr> &) const) &StepData_ESDescr::IsSub, "Tells if <me> is sub-type of (or equal to) another one", py::arg("other"));
cls_StepData_ESDescr.def("NbFields", (Standard_Integer (StepData_ESDescr::*)() const) &StepData_ESDescr::NbFields, "Returns the count of fields");
cls_StepData_ESDescr.def("Rank", (Standard_Integer (StepData_ESDescr::*)(const Standard_CString) const) &StepData_ESDescr::Rank, "Returns the rank of a field from its name. 0 if unknown", py::arg("name"));
cls_StepData_ESDescr.def("Name", (Standard_CString (StepData_ESDescr::*)(const Standard_Integer) const) &StepData_ESDescr::Name, "Returns the name of a field from its rank. empty if outofrange", py::arg("num"));
cls_StepData_ESDescr.def("Field", (opencascade::handle<StepData_PDescr> (StepData_ESDescr::*)(const Standard_Integer) const) &StepData_ESDescr::Field, "Returns the PDescr for the field <num> (or Null)", py::arg("num"));
cls_StepData_ESDescr.def("NamedField", (opencascade::handle<StepData_PDescr> (StepData_ESDescr::*)(const Standard_CString) const) &StepData_ESDescr::NamedField, "Returns the PDescr for the field named <name> (or Null)", py::arg("name"));
cls_StepData_ESDescr.def("Matches", (Standard_Boolean (StepData_ESDescr::*)(const Standard_CString) const) &StepData_ESDescr::Matches, "Tells if a ESDescr matches a step type : exact or super type", py::arg("steptype"));
cls_StepData_ESDescr.def("IsComplex", (Standard_Boolean (StepData_ESDescr::*)() const) &StepData_ESDescr::IsComplex, "Returns False");
cls_StepData_ESDescr.def("NewEntity", (opencascade::handle<StepData_Described> (StepData_ESDescr::*)() const) &StepData_ESDescr::NewEntity, "Creates a described entity (i.e. a simple one)");
cls_StepData_ESDescr.def_static("get_type_name_", (const char * (*)()) &StepData_ESDescr::get_type_name, "None");
cls_StepData_ESDescr.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_ESDescr::get_type_descriptor, "None");
cls_StepData_ESDescr.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_ESDescr::*)() const) &StepData_ESDescr::DynamicType, "None");

// CLASS: STEPDATA_FIELDLIST
py::class_<StepData_FieldList> cls_StepData_FieldList(mod, "StepData_FieldList", "Describes a list of fields, in a general way This basic class is for a null size list Subclasses are for 1, N (fixed) or Dynamic sizes");

// Constructors
cls_StepData_FieldList.def(py::init<>());

// Methods
// cls_StepData_FieldList.def_static("operator new_", (void * (*)(size_t)) &StepData_FieldList::operator new, "None", py::arg("theSize"));
// cls_StepData_FieldList.def_static("operator delete_", (void (*)(void *)) &StepData_FieldList::operator delete, "None", py::arg("theAddress"));
// cls_StepData_FieldList.def_static("operator new[]_", (void * (*)(size_t)) &StepData_FieldList::operator new[], "None", py::arg("theSize"));
// cls_StepData_FieldList.def_static("operator delete[]_", (void (*)(void *)) &StepData_FieldList::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_FieldList.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_FieldList::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_FieldList.def_static("operator delete_", (void (*)(void *, void *)) &StepData_FieldList::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_FieldList.def("NbFields", (Standard_Integer (StepData_FieldList::*)() const) &StepData_FieldList::NbFields, "Returns the count of fields. Here, returns 0");
cls_StepData_FieldList.def("Field", (const StepData_Field & (StepData_FieldList::*)(const Standard_Integer) const) &StepData_FieldList::Field, "Returns the field n0 <num> between 1 and NbFields (read only)", py::arg("num"));
cls_StepData_FieldList.def("CField", (StepData_Field & (StepData_FieldList::*)(const Standard_Integer)) &StepData_FieldList::CField, "Returns the field n0 <num> between 1 and NbFields, in order to modify its content", py::arg("num"));
cls_StepData_FieldList.def("FillShared", (void (StepData_FieldList::*)(Interface_EntityIterator &) const) &StepData_FieldList::FillShared, "Fills an iterator with the entities shared by <me>", py::arg("iter"));

// CLASS: STEPDATA_FIELDLIST1
py::class_<StepData_FieldList1, StepData_FieldList> cls_StepData_FieldList1(mod, "StepData_FieldList1", "Describes a list of ONE field");

// Constructors
cls_StepData_FieldList1.def(py::init<>());

// Methods
// cls_StepData_FieldList1.def_static("operator new_", (void * (*)(size_t)) &StepData_FieldList1::operator new, "None", py::arg("theSize"));
// cls_StepData_FieldList1.def_static("operator delete_", (void (*)(void *)) &StepData_FieldList1::operator delete, "None", py::arg("theAddress"));
// cls_StepData_FieldList1.def_static("operator new[]_", (void * (*)(size_t)) &StepData_FieldList1::operator new[], "None", py::arg("theSize"));
// cls_StepData_FieldList1.def_static("operator delete[]_", (void (*)(void *)) &StepData_FieldList1::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_FieldList1.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_FieldList1::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_FieldList1.def_static("operator delete_", (void (*)(void *, void *)) &StepData_FieldList1::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_FieldList1.def("NbFields", (Standard_Integer (StepData_FieldList1::*)() const) &StepData_FieldList1::NbFields, "Returns the count of fields. Here, returns 1");
cls_StepData_FieldList1.def("Field", (const StepData_Field & (StepData_FieldList1::*)(const Standard_Integer) const) &StepData_FieldList1::Field, "Returns the field n0 <num> between 1 and NbFields (read only)", py::arg("num"));
cls_StepData_FieldList1.def("CField", (StepData_Field & (StepData_FieldList1::*)(const Standard_Integer)) &StepData_FieldList1::CField, "Returns the field n0 <num> between 1 and NbFields, in order to modify its content", py::arg("num"));

// CLASS: STEPDATA_HARRAY1OFFIELD
py::class_<StepData_HArray1OfField, opencascade::handle<StepData_HArray1OfField>, Standard_Transient> cls_StepData_HArray1OfField(mod, "StepData_HArray1OfField", "None", py::multiple_inheritance());

// Constructors
cls_StepData_HArray1OfField.def(py::init<>());
cls_StepData_HArray1OfField.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepData_HArray1OfField.def(py::init<const Standard_Integer, const Standard_Integer, const StepData_Array1OfField::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepData_HArray1OfField.def(py::init<const StepData_Array1OfField &>(), py::arg("theOther"));

// Methods
// cls_StepData_HArray1OfField.def_static("operator new_", (void * (*)(size_t)) &StepData_HArray1OfField::operator new, "None", py::arg("theSize"));
// cls_StepData_HArray1OfField.def_static("operator delete_", (void (*)(void *)) &StepData_HArray1OfField::operator delete, "None", py::arg("theAddress"));
// cls_StepData_HArray1OfField.def_static("operator new[]_", (void * (*)(size_t)) &StepData_HArray1OfField::operator new[], "None", py::arg("theSize"));
// cls_StepData_HArray1OfField.def_static("operator delete[]_", (void (*)(void *)) &StepData_HArray1OfField::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_HArray1OfField.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_HArray1OfField::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_HArray1OfField.def_static("operator delete_", (void (*)(void *, void *)) &StepData_HArray1OfField::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepData_HArray1OfField.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepData_HArray1OfField::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepData_HArray1OfField.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepData_HArray1OfField::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepData_HArray1OfField.def("Array1", (const StepData_Array1OfField & (StepData_HArray1OfField::*)() const) &StepData_HArray1OfField::Array1, "None");
cls_StepData_HArray1OfField.def("ChangeArray1", (StepData_Array1OfField & (StepData_HArray1OfField::*)()) &StepData_HArray1OfField::ChangeArray1, "None");
cls_StepData_HArray1OfField.def_static("get_type_name_", (const char * (*)()) &StepData_HArray1OfField::get_type_name, "None");
cls_StepData_HArray1OfField.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_HArray1OfField::get_type_descriptor, "None");
cls_StepData_HArray1OfField.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_HArray1OfField::*)() const) &StepData_HArray1OfField::DynamicType, "None");

// CLASS: STEPDATA_FIELDLISTD
py::class_<StepData_FieldListD, StepData_FieldList> cls_StepData_FieldListD(mod, "StepData_FieldListD", "Describes a list of fields, in a general way This basic class is for a null size list Subclasses are for 1, N (fixed) or Dynamic sizes");

// Constructors
cls_StepData_FieldListD.def(py::init<const Standard_Integer>(), py::arg("nb"));

// Methods
// cls_StepData_FieldListD.def_static("operator new_", (void * (*)(size_t)) &StepData_FieldListD::operator new, "None", py::arg("theSize"));
// cls_StepData_FieldListD.def_static("operator delete_", (void (*)(void *)) &StepData_FieldListD::operator delete, "None", py::arg("theAddress"));
// cls_StepData_FieldListD.def_static("operator new[]_", (void * (*)(size_t)) &StepData_FieldListD::operator new[], "None", py::arg("theSize"));
// cls_StepData_FieldListD.def_static("operator delete[]_", (void (*)(void *)) &StepData_FieldListD::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_FieldListD.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_FieldListD::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_FieldListD.def_static("operator delete_", (void (*)(void *, void *)) &StepData_FieldListD::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_FieldListD.def("SetNb", (void (StepData_FieldListD::*)(const Standard_Integer)) &StepData_FieldListD::SetNb, "Sets a new count of Fields. Former contents are lost", py::arg("nb"));
cls_StepData_FieldListD.def("NbFields", (Standard_Integer (StepData_FieldListD::*)() const) &StepData_FieldListD::NbFields, "Returns the count of fields. Here, returns starting <nb>");
cls_StepData_FieldListD.def("Field", (const StepData_Field & (StepData_FieldListD::*)(const Standard_Integer) const) &StepData_FieldListD::Field, "Returns the field n0 <num> between 1 and NbFields (read only)", py::arg("num"));
cls_StepData_FieldListD.def("CField", (StepData_Field & (StepData_FieldListD::*)(const Standard_Integer)) &StepData_FieldListD::CField, "Returns the field n0 <num> between 1 and NbFields, in order to modify its content", py::arg("num"));

// CLASS: STEPDATA_FIELDLISTN
py::class_<StepData_FieldListN, StepData_FieldList> cls_StepData_FieldListN(mod, "StepData_FieldListN", "Describes a list of fields, in a general way This basic class is for a null size list Subclasses are for 1, N (fixed) or Dynamic sizes");

// Constructors
cls_StepData_FieldListN.def(py::init<const Standard_Integer>(), py::arg("nb"));

// Methods
// cls_StepData_FieldListN.def_static("operator new_", (void * (*)(size_t)) &StepData_FieldListN::operator new, "None", py::arg("theSize"));
// cls_StepData_FieldListN.def_static("operator delete_", (void (*)(void *)) &StepData_FieldListN::operator delete, "None", py::arg("theAddress"));
// cls_StepData_FieldListN.def_static("operator new[]_", (void * (*)(size_t)) &StepData_FieldListN::operator new[], "None", py::arg("theSize"));
// cls_StepData_FieldListN.def_static("operator delete[]_", (void (*)(void *)) &StepData_FieldListN::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_FieldListN.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_FieldListN::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_FieldListN.def_static("operator delete_", (void (*)(void *, void *)) &StepData_FieldListN::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_FieldListN.def("NbFields", (Standard_Integer (StepData_FieldListN::*)() const) &StepData_FieldListN::NbFields, "Returns the count of fields. Here, returns starting <nb>");
cls_StepData_FieldListN.def("Field", (const StepData_Field & (StepData_FieldListN::*)(const Standard_Integer) const) &StepData_FieldListN::Field, "Returns the field n0 <num> between 1 and NbFields (read only)", py::arg("num"));
cls_StepData_FieldListN.def("CField", (StepData_Field & (StepData_FieldListN::*)(const Standard_Integer)) &StepData_FieldListN::CField, "Returns the field n0 <num> between 1 and NbFields, in order to modify its content", py::arg("num"));

// CLASS: STEPDATA_FILEPROTOCOL
py::class_<StepData_FileProtocol, opencascade::handle<StepData_FileProtocol>, StepData_Protocol> cls_StepData_FileProtocol(mod, "StepData_FileProtocol", "A FileProtocol is defined as the addition of several already existing Protocols. It corresponds to the definition of a SchemaName with several Names, each one being attached to a specific Protocol. Thus, a File defined with a compound Schema is processed as any other one, once built the equivalent compound Protocol, a FileProtocol");

// Constructors
cls_StepData_FileProtocol.def(py::init<>());

// Methods
cls_StepData_FileProtocol.def("Add", (void (StepData_FileProtocol::*)(const opencascade::handle<StepData_Protocol> &)) &StepData_FileProtocol::Add, "Adds a Protocol to the definition list of the FileProtocol But ensures that each class of Protocol is present only once in this list", py::arg("protocol"));
cls_StepData_FileProtocol.def("NbResources", (Standard_Integer (StepData_FileProtocol::*)() const) &StepData_FileProtocol::NbResources, "Gives the count of Protocols used as Resource (can be zero) i.e. the count of Protocol recorded by calling the method Add");
cls_StepData_FileProtocol.def("Resource", (opencascade::handle<Interface_Protocol> (StepData_FileProtocol::*)(const Standard_Integer) const) &StepData_FileProtocol::Resource, "Returns a Resource, given a rank. Here, rank of calling Add", py::arg("num"));
cls_StepData_FileProtocol.def("TypeNumber", (Standard_Integer (StepData_FileProtocol::*)(const opencascade::handle<Standard_Type> &) const) &StepData_FileProtocol::TypeNumber, "Returns a Case Number, specific of each recognized Type Here, NO Type at all is recognized properly : all Types are recognized by the resources", py::arg("atype"));
cls_StepData_FileProtocol.def("GlobalCheck", (Standard_Boolean (StepData_FileProtocol::*)(const Interface_Graph &, opencascade::handle<Interface_Check> &) const) &StepData_FileProtocol::GlobalCheck, "Calls GlobalCheck for each of its recorded ressources", py::arg("G"), py::arg("ach"));
cls_StepData_FileProtocol.def("SchemaName", (Standard_CString (StepData_FileProtocol::*)() const) &StepData_FileProtocol::SchemaName, "Returns the Schema Name attached to each class of Protocol To be redefined by each sub-class Here, SchemaName returns '' (empty String) was C++ : return const");
cls_StepData_FileProtocol.def_static("get_type_name_", (const char * (*)()) &StepData_FileProtocol::get_type_name, "None");
cls_StepData_FileProtocol.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_FileProtocol::get_type_descriptor, "None");
cls_StepData_FileProtocol.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_FileProtocol::*)() const) &StepData_FileProtocol::DynamicType, "None");

// CLASS: STEPDATA_FILERECOGNIZER
py::class_<StepData_FileRecognizer, opencascade::handle<StepData_FileRecognizer>, Standard_Transient> cls_StepData_FileRecognizer(mod, "StepData_FileRecognizer", "None");

// Methods
cls_StepData_FileRecognizer.def("Evaluate", (Standard_Boolean (StepData_FileRecognizer::*)(const TCollection_AsciiString &, opencascade::handle<Standard_Transient> &)) &StepData_FileRecognizer::Evaluate, "Evaluates if recognition has a result, returns it if yes In case of success, Returns True and puts result in 'res' In case of Failure, simply Returns False Works by calling deferred method Eval, and in case of failure, looks for Added Recognizers to work", py::arg("akey"), py::arg("res"));
cls_StepData_FileRecognizer.def("Result", (opencascade::handle<Standard_Transient> (StepData_FileRecognizer::*)() const) &StepData_FileRecognizer::Result, "Returns result of last recognition (call of Evaluate)");
cls_StepData_FileRecognizer.def("Add", (void (StepData_FileRecognizer::*)(const opencascade::handle<StepData_FileRecognizer> &)) &StepData_FileRecognizer::Add, "Adds a new Recognizer to the Compound, at the end Several calls to Add work by adding in the order of calls : Hence, when Eval has failed to recognize, Evaluate will call Evaluate from the first added Recognizer if there is one, and to the second if there is still no result, and so on", py::arg("reco"));
cls_StepData_FileRecognizer.def_static("get_type_name_", (const char * (*)()) &StepData_FileRecognizer::get_type_name, "None");
cls_StepData_FileRecognizer.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_FileRecognizer::get_type_descriptor, "None");
cls_StepData_FileRecognizer.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_FileRecognizer::*)() const) &StepData_FileRecognizer::DynamicType, "None");

// CLASS: STEPDATA_FREEFORMENTITY
py::class_<StepData_FreeFormEntity, opencascade::handle<StepData_FreeFormEntity>, Standard_Transient> cls_StepData_FreeFormEntity(mod, "StepData_FreeFormEntity", "A Free Form Entity allows to record any kind of STEP parameters, in any way of typing It is implemented with an array of fields A Complex entity can be defined, as a chain of FreeFormEntity (see Next and As)");

// Constructors
// cls_StepData_FreeFormEntity.def(py::init<>());

// Methods
cls_StepData_FreeFormEntity.def("SetStepType", (void (StepData_FreeFormEntity::*)(const Standard_CString)) &StepData_FreeFormEntity::SetStepType, "Sets the type of an entity For a complex one, the type of this member", py::arg("typenam"));
cls_StepData_FreeFormEntity.def("StepType", (Standard_CString (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::StepType, "Returns the recorded StepType For a complex one, the type of this member");
cls_StepData_FreeFormEntity.def("SetNext", [](StepData_FreeFormEntity &self, const opencascade::handle<StepData_FreeFormEntity> & a0) -> void { return self.SetNext(a0); });
cls_StepData_FreeFormEntity.def("SetNext", (void (StepData_FreeFormEntity::*)(const opencascade::handle<StepData_FreeFormEntity> &, const Standard_Boolean)) &StepData_FreeFormEntity::SetNext, "Sets a next member, in order to define or complete a Complex entity If <last> is True (D), this next will be set as last of list Else, it is inserted just as next of <me> If <next> is Null, Next is cleared", py::arg("next"), py::arg("last"));
cls_StepData_FreeFormEntity.def("Next", (opencascade::handle<StepData_FreeFormEntity> (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::Next, "Returns the next member of a Complex entity (remark : the last member has none)");
cls_StepData_FreeFormEntity.def("IsComplex", (Standard_Boolean (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::IsComplex, "Returns True if a FreeFormEntity is Complex (i.e. has Next)");
cls_StepData_FreeFormEntity.def("Typed", (opencascade::handle<StepData_FreeFormEntity> (StepData_FreeFormEntity::*)(const Standard_CString) const) &StepData_FreeFormEntity::Typed, "Returns the member of a FreeFormEntity of which the type name is given (exact match, no sub-type)", py::arg("typenam"));
cls_StepData_FreeFormEntity.def("TypeList", (opencascade::handle<TColStd_HSequenceOfAsciiString> (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::TypeList, "Returns the list of types (one type for a simple entity), as is (non reordered)");
cls_StepData_FreeFormEntity.def_static("Reorder_", (Standard_Boolean (*)(opencascade::handle<StepData_FreeFormEntity> &)) &StepData_FreeFormEntity::Reorder, "Reorders a Complex entity if required, i.e. if member types are not in alphabetic order Returns False if nothing done (order was OK or simple entity), True plus modified <ent> if <ent> has been reordered", py::arg("ent"));
cls_StepData_FreeFormEntity.def("SetNbFields", (void (StepData_FreeFormEntity::*)(const Standard_Integer)) &StepData_FreeFormEntity::SetNbFields, "Sets a count of Fields, from scratch", py::arg("nb"));
cls_StepData_FreeFormEntity.def("NbFields", (Standard_Integer (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::NbFields, "Returns the count of fields");
cls_StepData_FreeFormEntity.def("Field", (const StepData_Field & (StepData_FreeFormEntity::*)(const Standard_Integer) const) &StepData_FreeFormEntity::Field, "Returns a field from its rank, for read-only use", py::arg("num"));
cls_StepData_FreeFormEntity.def("CField", (StepData_Field & (StepData_FreeFormEntity::*)(const Standard_Integer)) &StepData_FreeFormEntity::CField, "Returns a field from its rank, in order to modify it", py::arg("num"));
cls_StepData_FreeFormEntity.def_static("get_type_name_", (const char * (*)()) &StepData_FreeFormEntity::get_type_name, "None");
cls_StepData_FreeFormEntity.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_FreeFormEntity::get_type_descriptor, "None");
cls_StepData_FreeFormEntity.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_FreeFormEntity::*)() const) &StepData_FreeFormEntity::DynamicType, "None");

// CLASS: STEPDATA_GLOBALNODEOFWRITERLIB
py::class_<StepData_GlobalNodeOfWriterLib, opencascade::handle<StepData_GlobalNodeOfWriterLib>, Standard_Transient> cls_StepData_GlobalNodeOfWriterLib(mod, "StepData_GlobalNodeOfWriterLib", "None");

// Constructors
cls_StepData_GlobalNodeOfWriterLib.def(py::init<>());

// Methods
cls_StepData_GlobalNodeOfWriterLib.def("Add", (void (StepData_GlobalNodeOfWriterLib::*)(const opencascade::handle<StepData_ReadWriteModule> &, const opencascade::handle<StepData_Protocol> &)) &StepData_GlobalNodeOfWriterLib::Add, "Adds a Module bound with a Protocol to the list : does nothing if already in the list, THAT IS, Same Type (exact match) and Same State (that is, IsEqual is not required) Once added, stores its attached Protocol in correspondance", py::arg("amodule"), py::arg("aprotocol"));
cls_StepData_GlobalNodeOfWriterLib.def("Module", (const opencascade::handle<StepData_ReadWriteModule> & (StepData_GlobalNodeOfWriterLib::*)() const) &StepData_GlobalNodeOfWriterLib::Module, "Returns the Module stored in a given GlobalNode");
cls_StepData_GlobalNodeOfWriterLib.def("Protocol", (const opencascade::handle<StepData_Protocol> & (StepData_GlobalNodeOfWriterLib::*)() const) &StepData_GlobalNodeOfWriterLib::Protocol, "Returns the attached Protocol stored in a given GlobalNode");
cls_StepData_GlobalNodeOfWriterLib.def("Next", (const opencascade::handle<StepData_GlobalNodeOfWriterLib> & (StepData_GlobalNodeOfWriterLib::*)() const) &StepData_GlobalNodeOfWriterLib::Next, "Returns the Next GlobalNode. If none is defined, returned value is a Null Handle");
cls_StepData_GlobalNodeOfWriterLib.def_static("get_type_name_", (const char * (*)()) &StepData_GlobalNodeOfWriterLib::get_type_name, "None");
cls_StepData_GlobalNodeOfWriterLib.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_GlobalNodeOfWriterLib::get_type_descriptor, "None");
cls_StepData_GlobalNodeOfWriterLib.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_GlobalNodeOfWriterLib::*)() const) &StepData_GlobalNodeOfWriterLib::DynamicType, "None");

// CLASS: STEPDATA_NODEOFWRITERLIB
py::class_<StepData_NodeOfWriterLib, opencascade::handle<StepData_NodeOfWriterLib>, Standard_Transient> cls_StepData_NodeOfWriterLib(mod, "StepData_NodeOfWriterLib", "None");

// Constructors
cls_StepData_NodeOfWriterLib.def(py::init<>());

// Methods
cls_StepData_NodeOfWriterLib.def("AddNode", (void (StepData_NodeOfWriterLib::*)(const opencascade::handle<StepData_GlobalNodeOfWriterLib> &)) &StepData_NodeOfWriterLib::AddNode, "Adds a couple (Module,Protocol), that is, stores it into itself if not yet done, else creates a Next Node to do it", py::arg("anode"));
cls_StepData_NodeOfWriterLib.def("Module", (const opencascade::handle<StepData_ReadWriteModule> & (StepData_NodeOfWriterLib::*)() const) &StepData_NodeOfWriterLib::Module, "Returns the Module designated by a precise Node");
cls_StepData_NodeOfWriterLib.def("Protocol", (const opencascade::handle<StepData_Protocol> & (StepData_NodeOfWriterLib::*)() const) &StepData_NodeOfWriterLib::Protocol, "Returns the Protocol designated by a precise Node");
cls_StepData_NodeOfWriterLib.def("Next", (const opencascade::handle<StepData_NodeOfWriterLib> & (StepData_NodeOfWriterLib::*)() const) &StepData_NodeOfWriterLib::Next, "Returns the Next Node. If none was defined, returned value is a Null Handle");
cls_StepData_NodeOfWriterLib.def_static("get_type_name_", (const char * (*)()) &StepData_NodeOfWriterLib::get_type_name, "None");
cls_StepData_NodeOfWriterLib.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_NodeOfWriterLib::get_type_descriptor, "None");
cls_StepData_NodeOfWriterLib.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_NodeOfWriterLib::*)() const) &StepData_NodeOfWriterLib::DynamicType, "None");

// CLASS: STEPDATA_PDESCR
py::class_<StepData_PDescr, opencascade::handle<StepData_PDescr>, Standard_Transient> cls_StepData_PDescr(mod, "StepData_PDescr", "This class is intended to describe the authorized form for a parameter, as a type or a value for a field");

// Constructors
cls_StepData_PDescr.def(py::init<>());

// Methods
cls_StepData_PDescr.def("SetName", (void (StepData_PDescr::*)(const Standard_CString)) &StepData_PDescr::SetName, "None", py::arg("name"));
cls_StepData_PDescr.def("Name", (Standard_CString (StepData_PDescr::*)() const) &StepData_PDescr::Name, "None");
cls_StepData_PDescr.def("SetSelect", (void (StepData_PDescr::*)()) &StepData_PDescr::SetSelect, "Declares this PDescr to be a Select, hence to have members <me> itself can be the first member");
cls_StepData_PDescr.def("AddMember", (void (StepData_PDescr::*)(const opencascade::handle<StepData_PDescr> &)) &StepData_PDescr::AddMember, "Adds a member to a SELECT description", py::arg("member"));
cls_StepData_PDescr.def("SetMemberName", (void (StepData_PDescr::*)(const Standard_CString)) &StepData_PDescr::SetMemberName, "Sets a name for SELECT member. To be used if a member is for an immediate type", py::arg("memname"));
cls_StepData_PDescr.def("SetInteger", (void (StepData_PDescr::*)()) &StepData_PDescr::SetInteger, "Sets <me> for an Integer value");
cls_StepData_PDescr.def("SetReal", (void (StepData_PDescr::*)()) &StepData_PDescr::SetReal, "Sets <me> for a Real value");
cls_StepData_PDescr.def("SetString", (void (StepData_PDescr::*)()) &StepData_PDescr::SetString, "Sets <me> for a String value");
cls_StepData_PDescr.def("SetBoolean", (void (StepData_PDescr::*)()) &StepData_PDescr::SetBoolean, "Sets <me> for a Boolean value (false,true)");
cls_StepData_PDescr.def("SetLogical", (void (StepData_PDescr::*)()) &StepData_PDescr::SetLogical, "Sets <me> for a Logical value (false,true,unknown)");
cls_StepData_PDescr.def("SetEnum", (void (StepData_PDescr::*)()) &StepData_PDescr::SetEnum, "Sets <me> for an Enum value Then, call AddEnumDef ordered from the first one (value 0)");
cls_StepData_PDescr.def("AddEnumDef", (void (StepData_PDescr::*)(const Standard_CString)) &StepData_PDescr::AddEnumDef, "Adds an enum value as a string", py::arg("enumdef"));
cls_StepData_PDescr.def("SetType", (void (StepData_PDescr::*)(const opencascade::handle<Standard_Type> &)) &StepData_PDescr::SetType, "Sets <me> for an Entity which must match a Type (early-bound)", py::arg("atype"));
cls_StepData_PDescr.def("SetDescr", (void (StepData_PDescr::*)(const Standard_CString)) &StepData_PDescr::SetDescr, "Sets <me> for a Described Entity, whose Description must match the type name <dscnam>", py::arg("dscnam"));
cls_StepData_PDescr.def("AddArity", [](StepData_PDescr &self) -> void { return self.AddArity(); });
cls_StepData_PDescr.def("AddArity", (void (StepData_PDescr::*)(const Standard_Integer)) &StepData_PDescr::AddArity, "Adds an arity count to <me>, by default 1 1 : a simple field passes to a LIST/ARRAY etc or a LIST to a LIST OF LIST 2 : a simple field passes to a LIST OF LIST", py::arg("arity"));
cls_StepData_PDescr.def("SetArity", [](StepData_PDescr &self) -> void { return self.SetArity(); });
cls_StepData_PDescr.def("SetArity", (void (StepData_PDescr::*)(const Standard_Integer)) &StepData_PDescr::SetArity, "Directly sets the arity count 0 : simple field 1 : LIST or ARRAY etc 2 : LIST OF LIST", py::arg("arity"));
cls_StepData_PDescr.def("SetFrom", (void (StepData_PDescr::*)(const opencascade::handle<StepData_PDescr> &)) &StepData_PDescr::SetFrom, "Sets <me> as <other> but duplicated Hence, some definition may be changed", py::arg("other"));
cls_StepData_PDescr.def("SetOptional", [](StepData_PDescr &self) -> void { return self.SetOptional(); });
cls_StepData_PDescr.def("SetOptional", (void (StepData_PDescr::*)(const Standard_Boolean)) &StepData_PDescr::SetOptional, "Sets/Unsets <me> to accept undefined values", py::arg("opt"));
cls_StepData_PDescr.def("SetDerived", [](StepData_PDescr &self) -> void { return self.SetDerived(); });
cls_StepData_PDescr.def("SetDerived", (void (StepData_PDescr::*)(const Standard_Boolean)) &StepData_PDescr::SetDerived, "Sets/Unsets <me> to be for a derived field", py::arg("der"));
cls_StepData_PDescr.def("SetField", (void (StepData_PDescr::*)(const Standard_CString, const Standard_Integer)) &StepData_PDescr::SetField, "Sets <me> to describe a field of an entity With a name and a rank", py::arg("name"), py::arg("rank"));
cls_StepData_PDescr.def("IsSelect", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsSelect, "Tells if <me> is for a SELECT");
cls_StepData_PDescr.def("Member", (opencascade::handle<StepData_PDescr> (StepData_PDescr::*)(const Standard_CString) const) &StepData_PDescr::Member, "For a SELECT, returns the member whose name matches <name> To this member, the following question can then be asked Null Handle if <name> not matched or <me> not a SELECT", py::arg("name"));
cls_StepData_PDescr.def("IsInteger", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsInteger, "Tells if <me> is for an Integer");
cls_StepData_PDescr.def("IsReal", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsReal, "Tells if <me> is for a Real value");
cls_StepData_PDescr.def("IsString", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsString, "Tells if <me> is for a String value");
cls_StepData_PDescr.def("IsBoolean", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsBoolean, "Tells if <me> is for a Boolean value (false,true)");
cls_StepData_PDescr.def("IsLogical", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsLogical, "Tells if <me> is for a Logical value (false,true,unknown)");
cls_StepData_PDescr.def("IsEnum", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsEnum, "Tells if <me> is for an Enum value Then, call AddEnumDef ordered from the first one (value 0) Managed by an EnumTool");
cls_StepData_PDescr.def("EnumMax", (Standard_Integer (StepData_PDescr::*)() const) &StepData_PDescr::EnumMax, "Returns the maximum integer for a suitable value (count - 1)");
cls_StepData_PDescr.def("EnumValue", (Standard_Integer (StepData_PDescr::*)(const Standard_CString) const) &StepData_PDescr::EnumValue, "Returns the numeric value found for an enum text The text must be in capitals and limited by dots A non-suitable text gives a negative value to be returned", py::arg("name"));
cls_StepData_PDescr.def("EnumText", (Standard_CString (StepData_PDescr::*)(const Standard_Integer) const) &StepData_PDescr::EnumText, "Returns the text which corresponds to a numeric value, between 0 and EnumMax. It is limited by dots", py::arg("val"));
cls_StepData_PDescr.def("IsEntity", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsEntity, "Tells if <me> is for an Entity, either Described or CDL Type");
cls_StepData_PDescr.def("IsType", (Standard_Boolean (StepData_PDescr::*)(const opencascade::handle<Standard_Type> &) const) &StepData_PDescr::IsType, "Tells if <me> is for an entity of a given CDL type (early-bnd) (works for <me> + nexts if <me> is a Select)", py::arg("atype"));
cls_StepData_PDescr.def("Type", (opencascade::handle<Standard_Type> (StepData_PDescr::*)() const) &StepData_PDescr::Type, "Returns the type to match (IsKind), for a CDL Entity (else, null handle)");
cls_StepData_PDescr.def("IsDescr", (Standard_Boolean (StepData_PDescr::*)(const opencascade::handle<StepData_EDescr> &) const) &StepData_PDescr::IsDescr, "Tells if <me> is for a Described entity of a given EDescr (does this EDescr match description name ?). For late-bnd (works for <me> + nexts if <me> is a Select)", py::arg("descr"));
cls_StepData_PDescr.def("DescrName", (Standard_CString (StepData_PDescr::*)() const) &StepData_PDescr::DescrName, "Returns the description (type name) to match, for a Described (else, empty string)");
cls_StepData_PDescr.def("Arity", (Standard_Integer (StepData_PDescr::*)() const) &StepData_PDescr::Arity, "Returns the arity of <me>");
cls_StepData_PDescr.def("Simple", (opencascade::handle<StepData_PDescr> (StepData_PDescr::*)() const) &StepData_PDescr::Simple, "For a LIST or LIST OF LIST, Returns the PDescr for the simpler PDescr. Else, returns <me> This allows to have different attributes for Optional for instance, on a field, and on the parameter of a LIST : [OPTIONAL] LIST OF [OPTIONAL] ...");
cls_StepData_PDescr.def("IsOptional", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsOptional, "Tells if <me> is Optional");
cls_StepData_PDescr.def("IsDerived", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsDerived, "Tells if <me> is Derived");
cls_StepData_PDescr.def("IsField", (Standard_Boolean (StepData_PDescr::*)() const) &StepData_PDescr::IsField, "Tells if <me> is a Field. Else it is a Type");
cls_StepData_PDescr.def("FieldName", (Standard_CString (StepData_PDescr::*)() const) &StepData_PDescr::FieldName, "None");
cls_StepData_PDescr.def("FieldRank", (Standard_Integer (StepData_PDescr::*)() const) &StepData_PDescr::FieldRank, "None");
cls_StepData_PDescr.def("Check", (void (StepData_PDescr::*)(const StepData_Field &, opencascade::handle<Interface_Check> &) const) &StepData_PDescr::Check, "Semantic Check of a Field : does it complies with the given description ?", py::arg("afild"), py::arg("ach"));
cls_StepData_PDescr.def_static("get_type_name_", (const char * (*)()) &StepData_PDescr::get_type_name, "None");
cls_StepData_PDescr.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_PDescr::get_type_descriptor, "None");
cls_StepData_PDescr.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_PDescr::*)() const) &StepData_PDescr::DynamicType, "None");

// CLASS: STEPDATA_PLEX
py::class_<StepData_Plex, opencascade::handle<StepData_Plex>, StepData_Described> cls_StepData_Plex(mod, "StepData_Plex", "A Plex (for Complex) Entity is defined as a list of Simple Members ('external mapping') The types of these members must be in alphabetic order");

// Constructors
cls_StepData_Plex.def(py::init<const opencascade::handle<StepData_ECDescr> &>(), py::arg("descr"));

// Methods
cls_StepData_Plex.def("Add", (void (StepData_Plex::*)(const opencascade::handle<StepData_Simple> &)) &StepData_Plex::Add, "Adds a member to <me>", py::arg("member"));
cls_StepData_Plex.def("ECDescr", (opencascade::handle<StepData_ECDescr> (StepData_Plex::*)() const) &StepData_Plex::ECDescr, "Returns the Description as for a Plex");
cls_StepData_Plex.def("IsComplex", (Standard_Boolean (StepData_Plex::*)() const) &StepData_Plex::IsComplex, "Returns False");
cls_StepData_Plex.def("Matches", (Standard_Boolean (StepData_Plex::*)(const Standard_CString) const) &StepData_Plex::Matches, "Tells if a step type is matched by <me> For a Simple Entity : own type or super type For a Complex Entity : one of the members", py::arg("steptype"));
cls_StepData_Plex.def("As", (opencascade::handle<StepData_Simple> (StepData_Plex::*)(const Standard_CString) const) &StepData_Plex::As, "Returns a Simple Entity which matches with a Type in <me> : For a Simple Entity : me if it matches, else a null handle For a Complex Entity : the member which matches, else null", py::arg("steptype"));
cls_StepData_Plex.def("HasField", (Standard_Boolean (StepData_Plex::*)(const Standard_CString) const) &StepData_Plex::HasField, "Tells if a Field brings a given name", py::arg("name"));
cls_StepData_Plex.def("Field", (const StepData_Field & (StepData_Plex::*)(const Standard_CString) const) &StepData_Plex::Field, "Returns a Field from its name; read-only", py::arg("name"));
cls_StepData_Plex.def("CField", (StepData_Field & (StepData_Plex::*)(const Standard_CString)) &StepData_Plex::CField, "Returns a Field from its name; read or write", py::arg("name"));
cls_StepData_Plex.def("NbMembers", (Standard_Integer (StepData_Plex::*)() const) &StepData_Plex::NbMembers, "Returns the count of simple members");
cls_StepData_Plex.def("Member", (opencascade::handle<StepData_Simple> (StepData_Plex::*)(const Standard_Integer) const) &StepData_Plex::Member, "Returns a simple member from its rank", py::arg("num"));
cls_StepData_Plex.def("TypeList", (opencascade::handle<TColStd_HSequenceOfAsciiString> (StepData_Plex::*)() const) &StepData_Plex::TypeList, "Returns the actual list of members types");
cls_StepData_Plex.def("Check", (void (StepData_Plex::*)(opencascade::handle<Interface_Check> &) const) &StepData_Plex::Check, "Fills a Check by using its Description", py::arg("ach"));
cls_StepData_Plex.def("Shared", (void (StepData_Plex::*)(Interface_EntityIterator &) const) &StepData_Plex::Shared, "Fills an EntityIterator with entities shared by <me>", py::arg("list"));
cls_StepData_Plex.def_static("get_type_name_", (const char * (*)()) &StepData_Plex::get_type_name, "None");
cls_StepData_Plex.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_Plex::get_type_descriptor, "None");
cls_StepData_Plex.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_Plex::*)() const) &StepData_Plex::DynamicType, "None");

// CLASS: STEPDATA_SELECTNAMED
py::class_<StepData_SelectNamed, opencascade::handle<StepData_SelectNamed>, StepData_SelectMember> cls_StepData_SelectNamed(mod, "StepData_SelectNamed", "This select member can be of any kind, and be named But its takes more memory than some specialised ones This class allows one name for the instance");

// Constructors
cls_StepData_SelectNamed.def(py::init<>());

// Methods
cls_StepData_SelectNamed.def("HasName", (Standard_Boolean (StepData_SelectNamed::*)() const) &StepData_SelectNamed::HasName, "None");
cls_StepData_SelectNamed.def("Name", (Standard_CString (StepData_SelectNamed::*)() const) &StepData_SelectNamed::Name, "None");
cls_StepData_SelectNamed.def("SetName", (Standard_Boolean (StepData_SelectNamed::*)(const Standard_CString)) &StepData_SelectNamed::SetName, "None", py::arg("name"));
cls_StepData_SelectNamed.def("Field", (const StepData_Field & (StepData_SelectNamed::*)() const) &StepData_SelectNamed::Field, "None");
cls_StepData_SelectNamed.def("CField", (StepData_Field & (StepData_SelectNamed::*)()) &StepData_SelectNamed::CField, "None");
cls_StepData_SelectNamed.def("Kind", (Standard_Integer (StepData_SelectNamed::*)() const) &StepData_SelectNamed::Kind, "None");
cls_StepData_SelectNamed.def("SetKind", (void (StepData_SelectNamed::*)(const Standard_Integer)) &StepData_SelectNamed::SetKind, "None", py::arg("kind"));
cls_StepData_SelectNamed.def("Int", (Standard_Integer (StepData_SelectNamed::*)() const) &StepData_SelectNamed::Int, "This internal method gives access to a value implemented by an Integer (to read it)");
cls_StepData_SelectNamed.def("SetInt", (void (StepData_SelectNamed::*)(const Standard_Integer)) &StepData_SelectNamed::SetInt, "This internal method gives access to a value implemented by an Integer (to set it)", py::arg("val"));
cls_StepData_SelectNamed.def("Real", (Standard_Real (StepData_SelectNamed::*)() const) &StepData_SelectNamed::Real, "None");
cls_StepData_SelectNamed.def("SetReal", (void (StepData_SelectNamed::*)(const Standard_Real)) &StepData_SelectNamed::SetReal, "None", py::arg("val"));
cls_StepData_SelectNamed.def("String", (Standard_CString (StepData_SelectNamed::*)() const) &StepData_SelectNamed::String, "None");
cls_StepData_SelectNamed.def("SetString", (void (StepData_SelectNamed::*)(const Standard_CString)) &StepData_SelectNamed::SetString, "None", py::arg("val"));
cls_StepData_SelectNamed.def_static("get_type_name_", (const char * (*)()) &StepData_SelectNamed::get_type_name, "None");
cls_StepData_SelectNamed.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_SelectNamed::get_type_descriptor, "None");
cls_StepData_SelectNamed.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_SelectNamed::*)() const) &StepData_SelectNamed::DynamicType, "None");

// CLASS: STEPDATA_SELECTARRREAL
py::class_<StepData_SelectArrReal, opencascade::handle<StepData_SelectArrReal>, StepData_SelectNamed> cls_StepData_SelectArrReal(mod, "StepData_SelectArrReal", "None");

// Constructors
cls_StepData_SelectArrReal.def(py::init<>());

// Methods
cls_StepData_SelectArrReal.def("Kind", (Standard_Integer (StepData_SelectArrReal::*)() const) &StepData_SelectArrReal::Kind, "None");
cls_StepData_SelectArrReal.def("ArrReal", (opencascade::handle<TColStd_HArray1OfReal> (StepData_SelectArrReal::*)() const) &StepData_SelectArrReal::ArrReal, "None");
cls_StepData_SelectArrReal.def("SetArrReal", (void (StepData_SelectArrReal::*)(const opencascade::handle<TColStd_HArray1OfReal> &)) &StepData_SelectArrReal::SetArrReal, "None", py::arg("arr"));
cls_StepData_SelectArrReal.def_static("get_type_name_", (const char * (*)()) &StepData_SelectArrReal::get_type_name, "None");
cls_StepData_SelectArrReal.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_SelectArrReal::get_type_descriptor, "None");
cls_StepData_SelectArrReal.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_SelectArrReal::*)() const) &StepData_SelectArrReal::DynamicType, "None");

// CLASS: STEPDATA_SIMPLE
py::class_<StepData_Simple, opencascade::handle<StepData_Simple>, StepData_Described> cls_StepData_Simple(mod, "StepData_Simple", "A Simple Entity is defined by a type (which can heve super types) and a list of parameters");

// Constructors
cls_StepData_Simple.def(py::init<const opencascade::handle<StepData_ESDescr> &>(), py::arg("descr"));

// Methods
cls_StepData_Simple.def("ESDescr", (opencascade::handle<StepData_ESDescr> (StepData_Simple::*)() const) &StepData_Simple::ESDescr, "Returns description, as for simple");
cls_StepData_Simple.def("StepType", (Standard_CString (StepData_Simple::*)() const) &StepData_Simple::StepType, "Returns the recorded StepType (TypeName of its ESDescr)");
cls_StepData_Simple.def("IsComplex", (Standard_Boolean (StepData_Simple::*)() const) &StepData_Simple::IsComplex, "Returns False");
cls_StepData_Simple.def("Matches", (Standard_Boolean (StepData_Simple::*)(const Standard_CString) const) &StepData_Simple::Matches, "Tells if a step type is matched by <me> For a Simple Entity : own type or super type For a Complex Entity : one of the members", py::arg("steptype"));
cls_StepData_Simple.def("As", (opencascade::handle<StepData_Simple> (StepData_Simple::*)(const Standard_CString) const) &StepData_Simple::As, "Returns a Simple Entity which matches with a Type in <me> : For a Simple Entity : me if it matches, else a null handle For a Complex Entity : the member which matches, else null", py::arg("steptype"));
cls_StepData_Simple.def("HasField", (Standard_Boolean (StepData_Simple::*)(const Standard_CString) const) &StepData_Simple::HasField, "Tells if a Field brings a given name", py::arg("name"));
cls_StepData_Simple.def("Field", (const StepData_Field & (StepData_Simple::*)(const Standard_CString) const) &StepData_Simple::Field, "Returns a Field from its name; read-only", py::arg("name"));
cls_StepData_Simple.def("CField", (StepData_Field & (StepData_Simple::*)(const Standard_CString)) &StepData_Simple::CField, "Returns a Field from its name; read or write", py::arg("name"));
cls_StepData_Simple.def("NbFields", (Standard_Integer (StepData_Simple::*)() const) &StepData_Simple::NbFields, "Returns the count of fields");
cls_StepData_Simple.def("FieldNum", (const StepData_Field & (StepData_Simple::*)(const Standard_Integer) const) &StepData_Simple::FieldNum, "Returns a field from its rank, for read-only use", py::arg("num"));
cls_StepData_Simple.def("CFieldNum", (StepData_Field & (StepData_Simple::*)(const Standard_Integer)) &StepData_Simple::CFieldNum, "Returns a field from its rank, in order to modify it", py::arg("num"));
cls_StepData_Simple.def("Fields", (const StepData_FieldListN & (StepData_Simple::*)() const) &StepData_Simple::Fields, "Returns the entire field list, read-only");
cls_StepData_Simple.def("CFields", (StepData_FieldListN & (StepData_Simple::*)()) &StepData_Simple::CFields, "Returns the entire field list, read or write");
cls_StepData_Simple.def("Check", (void (StepData_Simple::*)(opencascade::handle<Interface_Check> &) const) &StepData_Simple::Check, "Fills a Check by using its Description", py::arg("ach"));
cls_StepData_Simple.def("Shared", (void (StepData_Simple::*)(Interface_EntityIterator &) const) &StepData_Simple::Shared, "Fills an EntityIterator with entities shared by <me>", py::arg("list"));
cls_StepData_Simple.def_static("get_type_name_", (const char * (*)()) &StepData_Simple::get_type_name, "None");
cls_StepData_Simple.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_Simple::get_type_descriptor, "None");
cls_StepData_Simple.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_Simple::*)() const) &StepData_Simple::DynamicType, "None");

// CLASS: STEPDATA_WRITERLIB
py::class_<StepData_WriterLib> cls_StepData_WriterLib(mod, "StepData_WriterLib", "None");

// Constructors
cls_StepData_WriterLib.def(py::init<const opencascade::handle<StepData_Protocol> &>(), py::arg("aprotocol"));
cls_StepData_WriterLib.def(py::init<>());

// Methods
// cls_StepData_WriterLib.def_static("operator new_", (void * (*)(size_t)) &StepData_WriterLib::operator new, "None", py::arg("theSize"));
// cls_StepData_WriterLib.def_static("operator delete_", (void (*)(void *)) &StepData_WriterLib::operator delete, "None", py::arg("theAddress"));
// cls_StepData_WriterLib.def_static("operator new[]_", (void * (*)(size_t)) &StepData_WriterLib::operator new[], "None", py::arg("theSize"));
// cls_StepData_WriterLib.def_static("operator delete[]_", (void (*)(void *)) &StepData_WriterLib::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_WriterLib.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_WriterLib::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_WriterLib.def_static("operator delete_", (void (*)(void *, void *)) &StepData_WriterLib::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_WriterLib.def_static("SetGlobal_", (void (*)(const opencascade::handle<StepData_ReadWriteModule> &, const opencascade::handle<StepData_Protocol> &)) &StepData_WriterLib::SetGlobal, "Adds a couple (Module-Protocol) into the global definition set for this class of Library.", py::arg("amodule"), py::arg("aprotocol"));
cls_StepData_WriterLib.def("AddProtocol", (void (StepData_WriterLib::*)(const opencascade::handle<Standard_Transient> &)) &StepData_WriterLib::AddProtocol, "Adds a couple (Module-Protocol) to the Library, given the class of a Protocol. Takes Resources into account. (if <aprotocol> is not of type TheProtocol, it is not added)", py::arg("aprotocol"));
cls_StepData_WriterLib.def("Clear", (void (StepData_WriterLib::*)()) &StepData_WriterLib::Clear, "Clears the list of Modules of a library (can be used to redefine the order of Modules before action : Clear then refill the Library by calls to AddProtocol)");
cls_StepData_WriterLib.def("SetComplete", (void (StepData_WriterLib::*)()) &StepData_WriterLib::SetComplete, "Sets a library to be defined with the complete Global list (all the couples Protocol/Modules recorded in it)");
cls_StepData_WriterLib.def("Select", [](StepData_WriterLib &self, const opencascade::handle<Standard_Transient> & obj, opencascade::handle<StepData_ReadWriteModule> & module, Standard_Integer & CN){ Standard_Boolean rv = self.Select(obj, module, CN); return std::tuple<Standard_Boolean, Standard_Integer &>(rv, CN); }, "Selects a Module from the Library, given an Object. Returns True if Select has succeeded, False else. Also Returns (as arguments) the selected Module and the Case Number determined by the associated Protocol. If Select has failed, <module> is Null Handle and CN is zero. (Select can work on any criterium, such as Object DynamicType)", py::arg("obj"), py::arg("module"), py::arg("CN"));
cls_StepData_WriterLib.def("Start", (void (StepData_WriterLib::*)()) &StepData_WriterLib::Start, "Starts Iteration on the Modules (sets it on the first one)");
cls_StepData_WriterLib.def("More", (Standard_Boolean (StepData_WriterLib::*)() const) &StepData_WriterLib::More, "Returns True if there are more Modules to iterate on");
cls_StepData_WriterLib.def("Next", (void (StepData_WriterLib::*)()) &StepData_WriterLib::Next, "Iterates by getting the next Module in the list If there is none, the exception will be raised by Value");
cls_StepData_WriterLib.def("Module", (const opencascade::handle<StepData_ReadWriteModule> & (StepData_WriterLib::*)() const) &StepData_WriterLib::Module, "Returns the current Module in the Iteration");
cls_StepData_WriterLib.def("Protocol", (const opencascade::handle<StepData_Protocol> & (StepData_WriterLib::*)() const) &StepData_WriterLib::Protocol, "Returns the current Protocol in the Iteration");

// CLASS: STEPDATA_STEPWRITER
py::class_<StepData_StepWriter> cls_StepData_StepWriter(mod, "StepData_StepWriter", "manages atomic file writing, under control of StepModel (for general organisation of file) and each class of Transient (for its own parameters) : prepares text to be written then writes it A stream cannot be used because Step limits line length at 72 In more, a specific object offers more appropriate functions");

// Constructors
cls_StepData_StepWriter.def(py::init<const opencascade::handle<StepData_StepModel> &>(), py::arg("amodel"));

// Methods
// cls_StepData_StepWriter.def_static("operator new_", (void * (*)(size_t)) &StepData_StepWriter::operator new, "None", py::arg("theSize"));
// cls_StepData_StepWriter.def_static("operator delete_", (void (*)(void *)) &StepData_StepWriter::operator delete, "None", py::arg("theAddress"));
// cls_StepData_StepWriter.def_static("operator new[]_", (void * (*)(size_t)) &StepData_StepWriter::operator new[], "None", py::arg("theSize"));
// cls_StepData_StepWriter.def_static("operator delete[]_", (void (*)(void *)) &StepData_StepWriter::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_StepWriter.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_StepWriter::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_StepWriter.def_static("operator delete_", (void (*)(void *, void *)) &StepData_StepWriter::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_StepWriter.def("LabelMode", (Standard_Integer & (StepData_StepWriter::*)()) &StepData_StepWriter::LabelMode, "ModeLabel controls how to display entity ids : 0 (D) gives entity number in the model 1 gives the already recorded label (else, its number) Warning : conflicts are not controlled");
cls_StepData_StepWriter.def("TypeMode", (Standard_Integer & (StepData_StepWriter::*)()) &StepData_StepWriter::TypeMode, "TypeMode controls the type form to use : 0 (D) for normal long form 1 for short form (if a type name has no short form, normal long form is then used)");
cls_StepData_StepWriter.def("FloatWriter", (Interface_FloatWriter & (StepData_StepWriter::*)()) &StepData_StepWriter::FloatWriter, "Returns the embedded FloatWriter, which controls sending Reals Use this method to access FloatWriter in order to consult or change its options (MainFormat, FormatForRange,ZeroSuppress), because it is returned as the address of its field");
cls_StepData_StepWriter.def("SetScope", (void (StepData_StepWriter::*)(const Standard_Integer, const Standard_Integer)) &StepData_StepWriter::SetScope, "Declares the Entity Number <numscope> to correspond to a Scope which contains the Entity Number <numin>. Several calls to the same <numscope> add Entities in this Scope, in this order. Error if <numin> is already declared in the Scope Warning : the declaration of the Scopes is assumed to be consistent, i.e. <numin> is not referenced from outside this Scope (not checked here)", py::arg("numscope"), py::arg("numin"));
cls_StepData_StepWriter.def("IsInScope", (Standard_Boolean (StepData_StepWriter::*)(const Standard_Integer) const) &StepData_StepWriter::IsInScope, "Returns True if an Entity identified by its Number is in a Scope", py::arg("num"));
cls_StepData_StepWriter.def("SendModel", [](StepData_StepWriter &self, const opencascade::handle<StepData_Protocol> & a0) -> void { return self.SendModel(a0); });
cls_StepData_StepWriter.def("SendModel", (void (StepData_StepWriter::*)(const opencascade::handle<StepData_Protocol> &, const Standard_Boolean)) &StepData_StepWriter::SendModel, "Sends the complete Model, included HEADER and DATA Sections Works with a WriterLib defined through a Protocol If <headeronly> is given True, only the HEADER Section is sent (used to Dump the Header of a StepModel)", py::arg("protocol"), py::arg("headeronly"));
cls_StepData_StepWriter.def("SendHeader", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendHeader, "Begins model header");
cls_StepData_StepWriter.def("SendData", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendData, "Begins data section; error if EndSec was not set");
cls_StepData_StepWriter.def("SendEntity", (void (StepData_StepWriter::*)(const Standard_Integer, const StepData_WriterLib &)) &StepData_StepWriter::SendEntity, "Send an Entity of the Data Section. If it corresponds to a Scope, also Sends the Scope informations and contained Items", py::arg("nument"), py::arg("lib"));
cls_StepData_StepWriter.def("EndSec", (void (StepData_StepWriter::*)()) &StepData_StepWriter::EndSec, "sets end of section; to be done before passing to next one");
cls_StepData_StepWriter.def("EndFile", (void (StepData_StepWriter::*)()) &StepData_StepWriter::EndFile, "sets end of file; error is EndSec was not set");
cls_StepData_StepWriter.def("NewLine", (void (StepData_StepWriter::*)(const Standard_Boolean)) &StepData_StepWriter::NewLine, "flushes current line; if empty, flushes it (defines a new empty line) if evenempty is True; else, skips it", py::arg("evenempty"));
cls_StepData_StepWriter.def("JoinLast", (void (StepData_StepWriter::*)(const Standard_Boolean)) &StepData_StepWriter::JoinLast, "joins current line to last one, only if new length is 72 max if newline is True, a new current line begins; else, current line is set to the last line (once joined) itself an can be completed", py::arg("newline"));
cls_StepData_StepWriter.def("Indent", (void (StepData_StepWriter::*)(const Standard_Boolean)) &StepData_StepWriter::Indent, "asks that further indentations will begin at position of entity first opening bracket; else they begin at zero (def) for each sublist level, two more blancks are added at beginning (except for text continuation, which must begin at true zero)", py::arg("onent"));
cls_StepData_StepWriter.def("SendIdent", (void (StepData_StepWriter::*)(const Standard_Integer)) &StepData_StepWriter::SendIdent, "begins an entity with an ident plus '=' (at beginning of line) entity ident is its Number given by the containing Model Warning : <ident> must be, either Number or Label, according LabelMode", py::arg("ident"));
cls_StepData_StepWriter.def("SendScope", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendScope, "sets a begin of Scope (ends this line)");
cls_StepData_StepWriter.def("SendEndscope", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendEndscope, "sets an end of Scope (on a separate line)");
cls_StepData_StepWriter.def("Comment", (void (StepData_StepWriter::*)(const Standard_Boolean)) &StepData_StepWriter::Comment, "sets a comment mark : if mode is True, begins Comment zone, if mode is False, ends Comment zone (if one is begun)", py::arg("mode"));
cls_StepData_StepWriter.def("SendComment", (void (StepData_StepWriter::*)(const opencascade::handle<TCollection_HAsciiString> &)) &StepData_StepWriter::SendComment, "sends a comment. Error if we are not inside a comment zone", py::arg("text"));
cls_StepData_StepWriter.def("SendComment", (void (StepData_StepWriter::*)(const Standard_CString)) &StepData_StepWriter::SendComment, "same as above but accepts a CString (ex.: '...' directly)", py::arg("text"));
cls_StepData_StepWriter.def("StartEntity", (void (StepData_StepWriter::*)(const TCollection_AsciiString &)) &StepData_StepWriter::StartEntity, "sets entity's StepType, opens brakets, starts param no to 0 params are separated by comma Remark : for a Multiple Type Entity (see Express ANDOR clause) StartComplex must be called before sending componants, then each 'Componant' must be send separately (one call to StartEntity for each one) : the Type which preceeds is then automaticaly closed. Once all the componants have been sent, EndComplex must be called, then and only then EndEntity", py::arg("atype"));
cls_StepData_StepWriter.def("StartComplex", (void (StepData_StepWriter::*)()) &StepData_StepWriter::StartComplex, "sends the start of a complex entity, which is a simple open bracket (without increasing braket level) It must be called JUST AFTER SendEntity and BEFORE sending componants, each one begins by StartEntity");
cls_StepData_StepWriter.def("EndComplex", (void (StepData_StepWriter::*)()) &StepData_StepWriter::EndComplex, "sends the end of a complex entity : a simple closed bracket It must be called AFTER sending all the componants and BEFORE the final call to EndEntity");
cls_StepData_StepWriter.def("SendField", (void (StepData_StepWriter::*)(const StepData_Field &, const opencascade::handle<StepData_PDescr> &)) &StepData_StepWriter::SendField, "Sends the content of a field, controlled by its descriptor If the descriptor is not defined, follows the description detained by the field itself", py::arg("fild"), py::arg("descr"));
cls_StepData_StepWriter.def("SendSelect", (void (StepData_StepWriter::*)(const opencascade::handle<StepData_SelectMember> &, const opencascade::handle<StepData_PDescr> &)) &StepData_StepWriter::SendSelect, "Sends a SelectMember, which cab be named or not", py::arg("sm"), py::arg("descr"));
cls_StepData_StepWriter.def("SendList", (void (StepData_StepWriter::*)(const StepData_FieldList &, const opencascade::handle<StepData_ESDescr> &)) &StepData_StepWriter::SendList, "Send the content of an entity as being a FieldList controlled by its descriptor. This includes start and end brackets but not the entity type", py::arg("list"), py::arg("descr"));
cls_StepData_StepWriter.def("OpenSub", (void (StepData_StepWriter::*)()) &StepData_StepWriter::OpenSub, "open a sublist by a '('");
cls_StepData_StepWriter.def("OpenTypedSub", (void (StepData_StepWriter::*)(const Standard_CString)) &StepData_StepWriter::OpenTypedSub, "open a sublist with its type then a '('", py::arg("subtype"));
cls_StepData_StepWriter.def("CloseSub", (void (StepData_StepWriter::*)()) &StepData_StepWriter::CloseSub, "closes a sublist by a ')'");
cls_StepData_StepWriter.def("AddParam", (void (StepData_StepWriter::*)()) &StepData_StepWriter::AddParam, "prepares adding a parameter (that is, adds ',' except for first one); normally for internal use; can be used to send a totally empty parameter (with no litteral value)");
cls_StepData_StepWriter.def("Send", (void (StepData_StepWriter::*)(const Standard_Integer)) &StepData_StepWriter::Send, "sends an integer parameter", py::arg("val"));
cls_StepData_StepWriter.def("Send", (void (StepData_StepWriter::*)(const Standard_Real)) &StepData_StepWriter::Send, "sends a real parameter (wroks with FloatWriter)", py::arg("val"));
cls_StepData_StepWriter.def("Send", (void (StepData_StepWriter::*)(const TCollection_AsciiString &)) &StepData_StepWriter::Send, "sends a text given as string (it will be set between '...')", py::arg("val"));
cls_StepData_StepWriter.def("Send", (void (StepData_StepWriter::*)(const opencascade::handle<Standard_Transient> &)) &StepData_StepWriter::Send, "sends a reference to an entity (its identifier with '#') REMARK 1 : a Null <val> is interpreted as 'Undefined' REMARK 2 : for an HAsciiString which is not recorded in the Model, it is send as its String Content, between quotes", py::arg("val"));
cls_StepData_StepWriter.def("SendBoolean", (void (StepData_StepWriter::*)(const Standard_Boolean)) &StepData_StepWriter::SendBoolean, "sends a Boolean as .T. for True or .F. for False (it is an useful case of Enum, which is built-in)", py::arg("val"));
cls_StepData_StepWriter.def("SendLogical", (void (StepData_StepWriter::*)(const StepData_Logical)) &StepData_StepWriter::SendLogical, "sends a Logical as .T. or .F. or .U. according its Value (it is a standard case of Enum for Step, and is built-in)", py::arg("val"));
cls_StepData_StepWriter.def("SendString", (void (StepData_StepWriter::*)(const TCollection_AsciiString &)) &StepData_StepWriter::SendString, "sends a string exactly as it is given", py::arg("val"));
cls_StepData_StepWriter.def("SendString", (void (StepData_StepWriter::*)(const Standard_CString)) &StepData_StepWriter::SendString, "sends a string exactly as it is given", py::arg("val"));
cls_StepData_StepWriter.def("SendEnum", (void (StepData_StepWriter::*)(const TCollection_AsciiString &)) &StepData_StepWriter::SendEnum, "sends an enum given by String (litteral expression) adds '.' around it if not done Remark : val can be computed by class EnumTool from StepData: StepWriter.SendEnum (myenum.Text(enumval));", py::arg("val"));
cls_StepData_StepWriter.def("SendEnum", (void (StepData_StepWriter::*)(const Standard_CString)) &StepData_StepWriter::SendEnum, "sends an enum given by String (litteral expression) adds '.' around it if not done", py::arg("val"));
cls_StepData_StepWriter.def("SendArrReal", (void (StepData_StepWriter::*)(const opencascade::handle<TColStd_HArray1OfReal> &)) &StepData_StepWriter::SendArrReal, "sends an array of real", py::arg("anArr"));
cls_StepData_StepWriter.def("SendUndef", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendUndef, "sends an undefined (optionnal absent) parameter (by '$')");
cls_StepData_StepWriter.def("SendDerived", (void (StepData_StepWriter::*)()) &StepData_StepWriter::SendDerived, "sends a 'Derived' parameter (by '*'). A Derived Parameter has been inherited from a Super-Type then redefined as being computed by a function. Hence its value in file is senseless.");
cls_StepData_StepWriter.def("EndEntity", (void (StepData_StepWriter::*)()) &StepData_StepWriter::EndEntity, "sends end of entity (closing bracket plus ';') Error if count of opened-closed brackets is not null");
cls_StepData_StepWriter.def("CheckList", (Interface_CheckIterator (StepData_StepWriter::*)() const) &StepData_StepWriter::CheckList, "Returns the check-list, which has received possible checks : for unknown entities, badly loaded ones, null or unknown references");
cls_StepData_StepWriter.def("NbLines", (Standard_Integer (StepData_StepWriter::*)() const) &StepData_StepWriter::NbLines, "Returns count of Lines");
cls_StepData_StepWriter.def("Line", (opencascade::handle<TCollection_HAsciiString> (StepData_StepWriter::*)(const Standard_Integer) const) &StepData_StepWriter::Line, "Returns a Line given its rank in the File", py::arg("num"));
cls_StepData_StepWriter.def("Print", (Standard_Boolean (StepData_StepWriter::*)(Standard_OStream &)) &StepData_StepWriter::Print, "writes result on an output defined as an OStream then clears it", py::arg("S"));

// CLASS: STEPDATA_STEPDUMPER
py::class_<StepData_StepDumper> cls_StepData_StepDumper(mod, "StepData_StepDumper", "Provides a way to dump entities processed through STEP, with these features : - same form as for writing a STEP File (because it is clear and compact enough, even if the names of the fields do not appear) : thus, no additionnal resource is required - possibility to look for an entity itself (only its Type or with its content), an entity and it shared items (one level) or all the entities its refers to, directly or recursively.");

// Constructors
cls_StepData_StepDumper.def(py::init<const opencascade::handle<StepData_StepModel> &, const opencascade::handle<StepData_Protocol> &>(), py::arg("amodel"), py::arg("protocol"));
cls_StepData_StepDumper.def(py::init<const opencascade::handle<StepData_StepModel> &, const opencascade::handle<StepData_Protocol> &, const Standard_Integer>(), py::arg("amodel"), py::arg("protocol"), py::arg("mode"));

// Methods
// cls_StepData_StepDumper.def_static("operator new_", (void * (*)(size_t)) &StepData_StepDumper::operator new, "None", py::arg("theSize"));
// cls_StepData_StepDumper.def_static("operator delete_", (void (*)(void *)) &StepData_StepDumper::operator delete, "None", py::arg("theAddress"));
// cls_StepData_StepDumper.def_static("operator new[]_", (void * (*)(size_t)) &StepData_StepDumper::operator new[], "None", py::arg("theSize"));
// cls_StepData_StepDumper.def_static("operator delete[]_", (void (*)(void *)) &StepData_StepDumper::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_StepDumper.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_StepDumper::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_StepDumper.def_static("operator delete_", (void (*)(void *, void *)) &StepData_StepDumper::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_StepDumper.def("StepWriter", (StepData_StepWriter & (StepData_StepDumper::*)()) &StepData_StepDumper::StepWriter, "Gives an access to the tool which is used to work : this allow to acts on some parameters : Floating Format, Scopes ...");
cls_StepData_StepDumper.def("Dump", (Standard_Boolean (StepData_StepDumper::*)(const opencascade::handle<Message_Messenger> &, const opencascade::handle<Standard_Transient> &, const Standard_Integer)) &StepData_StepDumper::Dump, "Dumps a Entity on an Messenger. Returns True if sucess, False, if the entity to dump has not been recognized by the Protocol. <level> can have one of these values : - 0 : prints the TYPE only, as known in STEP Files (StepType) If <ent> has not been regognized by the Protocol, or if its type is Complex, the StepType is replaced by the display of the cdl type. Complex Type are well processed by level 1. - 1 : dumps the entity, completely (whatever it has simple or complex type) but alone. - 2 : dumps the entity completely, plus the item its refers to at first level (a header message designates the starting entity of the dump) <Lists Shared and Implied> - 3 : dumps the entity and its refered items at any levels", py::arg("S"), py::arg("ent"), py::arg("level"));
cls_StepData_StepDumper.def("Dump", (Standard_Boolean (StepData_StepDumper::*)(const opencascade::handle<Message_Messenger> &, const Standard_Integer, const Standard_Integer)) &StepData_StepDumper::Dump, "Works as Dump with a Transient, but directly takes the entity designated by its number in the Model Returns False, also if <num> is out of range", py::arg("S"), py::arg("num"), py::arg("level"));

// CLASS: STEPDATA_STEPMODEL
py::class_<StepData_StepModel, opencascade::handle<StepData_StepModel>, Interface_InterfaceModel> cls_StepData_StepModel(mod, "StepData_StepModel", "Gives access to - entities in a STEP file, - the STEP file header.");

// Constructors
cls_StepData_StepModel.def(py::init<>());

// Methods
cls_StepData_StepModel.def("Entity", (opencascade::handle<Standard_Transient> (StepData_StepModel::*)(const Standard_Integer) const) &StepData_StepModel::Entity, "returns entity given its rank. Same as InterfaceEntity, but with a shorter name", py::arg("num"));
cls_StepData_StepModel.def("GetFromAnother", (void (StepData_StepModel::*)(const opencascade::handle<Interface_InterfaceModel> &)) &StepData_StepModel::GetFromAnother, "gets header from another Model (uses Header Protocol)", py::arg("other"));
cls_StepData_StepModel.def("NewEmptyModel", (opencascade::handle<Interface_InterfaceModel> (StepData_StepModel::*)() const) &StepData_StepModel::NewEmptyModel, "Returns a New Empty Model, same type as <me>, i.e. StepModel");
cls_StepData_StepModel.def("Header", (Interface_EntityIterator (StepData_StepModel::*)() const) &StepData_StepModel::Header, "returns Header entities under the form of an iterator");
cls_StepData_StepModel.def("HasHeaderEntity", (Standard_Boolean (StepData_StepModel::*)(const opencascade::handle<Standard_Type> &) const) &StepData_StepModel::HasHeaderEntity, "says if a Header entity has a specifed type", py::arg("atype"));
cls_StepData_StepModel.def("HeaderEntity", (opencascade::handle<Standard_Transient> (StepData_StepModel::*)(const opencascade::handle<Standard_Type> &) const) &StepData_StepModel::HeaderEntity, "Returns Header entity with specified type, if there is", py::arg("atype"));
cls_StepData_StepModel.def("ClearHeader", (void (StepData_StepModel::*)()) &StepData_StepModel::ClearHeader, "Clears the Header");
cls_StepData_StepModel.def("AddHeaderEntity", (void (StepData_StepModel::*)(const opencascade::handle<Standard_Transient> &)) &StepData_StepModel::AddHeaderEntity, "Adds an Entity to the Header", py::arg("ent"));
cls_StepData_StepModel.def("VerifyCheck", (void (StepData_StepModel::*)(opencascade::handle<Interface_Check> &) const) &StepData_StepModel::VerifyCheck, "Specific Check, checks Header Items with HeaderProtocol", py::arg("ach"));
cls_StepData_StepModel.def("DumpHeader", [](StepData_StepModel &self, const opencascade::handle<Message_Messenger> & a0) -> void { return self.DumpHeader(a0); });
cls_StepData_StepModel.def("DumpHeader", (void (StepData_StepModel::*)(const opencascade::handle<Message_Messenger> &, const Standard_Integer) const) &StepData_StepModel::DumpHeader, "Dumps the Header, with the Header Protocol of StepData. If the Header Protocol is not defined, for each Header Entity, prints its Type. Else sends the Header under the form of HEADER Section of an Ascii Step File <level> is not used because Header is not so big", py::arg("S"), py::arg("level"));
cls_StepData_StepModel.def("ClearLabels", (void (StepData_StepModel::*)()) &StepData_StepModel::ClearLabels, "erases specific labels, i.e. clears the map (entity-ident)");
cls_StepData_StepModel.def("SetIdentLabel", (void (StepData_StepModel::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer)) &StepData_StepModel::SetIdentLabel, "Attaches an ident to an entity to produce a label (does nothing if <ent> is not in <me>)", py::arg("ent"), py::arg("ident"));
cls_StepData_StepModel.def("IdentLabel", (Standard_Integer (StepData_StepModel::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_StepModel::IdentLabel, "returns the label ident attached to an entity, 0 if not in me", py::arg("ent"));
cls_StepData_StepModel.def("PrintLabel", (void (StepData_StepModel::*)(const opencascade::handle<Standard_Transient> &, const opencascade::handle<Message_Messenger> &) const) &StepData_StepModel::PrintLabel, "Prints label specific to STEP norm for a given entity, i.e. if a LabelIdent has been recorded, its value with '#', else the number in the model with '#' and between ()", py::arg("ent"), py::arg("S"));
cls_StepData_StepModel.def("StringLabel", (opencascade::handle<TCollection_HAsciiString> (StepData_StepModel::*)(const opencascade::handle<Standard_Transient> &) const) &StepData_StepModel::StringLabel, "Returns a string with the label attached to a given entity, same form as for PrintLabel", py::arg("ent"));
cls_StepData_StepModel.def_static("get_type_name_", (const char * (*)()) &StepData_StepModel::get_type_name, "None");
cls_StepData_StepModel.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_StepModel::get_type_descriptor, "None");
cls_StepData_StepModel.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_StepModel::*)() const) &StepData_StepModel::DynamicType, "None");

// CLASS: STEPDATA_STEPREADERTOOL
py::class_<StepData_StepReaderTool, Interface_FileReaderTool> cls_StepData_StepReaderTool(mod, "StepData_StepReaderTool", "Specific FileReaderTool for Step; works with FileReaderData provides references evaluation, plus access to litteral data and specific methods defined by FileReaderTool Remarks : works with a ReaderLib to load Entities");

// Constructors
cls_StepData_StepReaderTool.def(py::init<const opencascade::handle<StepData_StepReaderData> &, const opencascade::handle<StepData_Protocol> &>(), py::arg("reader"), py::arg("protocol"));

// Methods
// cls_StepData_StepReaderTool.def_static("operator new_", (void * (*)(size_t)) &StepData_StepReaderTool::operator new, "None", py::arg("theSize"));
// cls_StepData_StepReaderTool.def_static("operator delete_", (void (*)(void *)) &StepData_StepReaderTool::operator delete, "None", py::arg("theAddress"));
// cls_StepData_StepReaderTool.def_static("operator new[]_", (void * (*)(size_t)) &StepData_StepReaderTool::operator new[], "None", py::arg("theSize"));
// cls_StepData_StepReaderTool.def_static("operator delete[]_", (void (*)(void *)) &StepData_StepReaderTool::operator delete[], "None", py::arg("theAddress"));
// cls_StepData_StepReaderTool.def_static("operator new_", (void * (*)(size_t, void *)) &StepData_StepReaderTool::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepData_StepReaderTool.def_static("operator delete_", (void (*)(void *, void *)) &StepData_StepReaderTool::operator delete, "None", py::arg(""), py::arg(""));
cls_StepData_StepReaderTool.def("Prepare", [](StepData_StepReaderTool &self) -> void { return self.Prepare(); });
cls_StepData_StepReaderTool.def("Prepare", (void (StepData_StepReaderTool::*)(const Standard_Boolean)) &StepData_StepReaderTool::Prepare, "Bounds empty entities to records, uses default Recognition provided by ReaderLib and ReaderModule. Also calls computation of references (SetEntityNumbers from StepReaderData) Works only on data entities (skips header) <optimize> given False allows to test some internal algorithms which are normally avoided (see also StepReaderData)", py::arg("optimize"));
cls_StepData_StepReaderTool.def("Prepare", [](StepData_StepReaderTool &self, const opencascade::handle<StepData_FileRecognizer> & a0) -> void { return self.Prepare(a0); });
cls_StepData_StepReaderTool.def("Prepare", (void (StepData_StepReaderTool::*)(const opencascade::handle<StepData_FileRecognizer> &, const Standard_Boolean)) &StepData_StepReaderTool::Prepare, "Bounds empty entities to records, works with a specific FileRecognizer, stored and later used in Recognize Works only on data entities (skips header) <optimize : same as above", py::arg("reco"), py::arg("optimize"));
cls_StepData_StepReaderTool.def("Recognize", (Standard_Boolean (StepData_StepReaderTool::*)(const Standard_Integer, opencascade::handle<Interface_Check> &, opencascade::handle<Standard_Transient> &)) &StepData_StepReaderTool::Recognize, "recognizes records, by asking either ReaderLib (default) or FileRecognizer (if defined) to do so. <ach> is to call RecognizeByLib", py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_StepData_StepReaderTool.def("PrepareHeader", (void (StepData_StepReaderTool::*)(const opencascade::handle<StepData_FileRecognizer> &)) &StepData_StepReaderTool::PrepareHeader, "bounds empty entities and sub-lists to header records works like Prepare + SetEntityNumbers, but for header (N.B.: in Header, no Ident and no reference) FileRecognizer is to specify Entities which are allowed to be defined in the Header (not every type can be)", py::arg("reco"));
cls_StepData_StepReaderTool.def("BeginRead", (void (StepData_StepReaderTool::*)(const opencascade::handle<Interface_InterfaceModel> &)) &StepData_StepReaderTool::BeginRead, "fills model's header; that is, gives to it Header entities and commands their loading. Also fills StepModel's Global Check from StepReaderData's GlobalCheck", py::arg("amodel"));
cls_StepData_StepReaderTool.def("AnalyseRecord", (Standard_Boolean (StepData_StepReaderTool::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, opencascade::handle<Interface_Check> &)) &StepData_StepReaderTool::AnalyseRecord, "fills an entity, given record no; works by using a ReaderLib to load each entity, which must be a Transient Actually, returned value is True if no fail, False else", py::arg("num"), py::arg("anent"), py::arg("acheck"));
cls_StepData_StepReaderTool.def("EndRead", (void (StepData_StepReaderTool::*)(const opencascade::handle<Interface_InterfaceModel> &)) &StepData_StepReaderTool::EndRead, "Ends file reading after reading all the entities Here, it binds in the model, Idents to Entities (for checks)", py::arg("amodel"));

// CLASS: STEPDATA_UNDEFINEDENTITY
py::class_<StepData_UndefinedEntity, opencascade::handle<StepData_UndefinedEntity>, Standard_Transient> cls_StepData_UndefinedEntity(mod, "StepData_UndefinedEntity", "Undefined entity specific to Step Interface, in which StepType is defined at each instance, or is a SubList of another one Uses an UndefinedContent, that from Interface is suitable. Also an Entity defined by STEP can be 'Complex Type' (see ANDOR clause in Express).");

// Constructors
cls_StepData_UndefinedEntity.def(py::init<>());
cls_StepData_UndefinedEntity.def(py::init<const Standard_Boolean>(), py::arg("issub"));

// Methods
cls_StepData_UndefinedEntity.def("UndefinedContent", (opencascade::handle<Interface_UndefinedContent> (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::UndefinedContent, "Returns the UndefinedContent which brings the Parameters");
cls_StepData_UndefinedEntity.def("IsSub", (Standard_Boolean (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::IsSub, "Returns True if an Unndefined Entity is SubPart of another one");
// cls_StepData_UndefinedEntity.def("Super", (opencascade::handle<StepData_UndefinedEntity> (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::Super, "Returns the 'super-entity' of a sub-part");
cls_StepData_UndefinedEntity.def("IsComplex", (Standard_Boolean (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::IsComplex, "Returns True if <me> defines a Multiple Type Entity (see ANDOR)");
cls_StepData_UndefinedEntity.def("Next", (opencascade::handle<StepData_UndefinedEntity> (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::Next, "For a Multiple Type Entity, returns the Next 'Componant' For more than two Types, iterative definition (Next->Next...) Returns a Null Handle for the end of the List");
cls_StepData_UndefinedEntity.def("StepType", (Standard_CString (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::StepType, "gives entity type, read from file For a Complex Type Entity, gives the first Type read, each 'Next' gives its 'partial' type was C++ : return const");
cls_StepData_UndefinedEntity.def("ReadRecord", (void (StepData_UndefinedEntity::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &)) &StepData_UndefinedEntity::ReadRecord, "reads data from StepReaderData (i.e. from file), by filling StepType and parameters stored in the UndefinedContent", py::arg("SR"), py::arg("num"), py::arg("ach"));
cls_StepData_UndefinedEntity.def("WriteParams", (void (StepData_UndefinedEntity::*)(StepData_StepWriter &) const) &StepData_UndefinedEntity::WriteParams, "write data to StepWriter, taken from UndefinedContent", py::arg("SW"));
cls_StepData_UndefinedEntity.def("GetFromAnother", (void (StepData_UndefinedEntity::*)(const opencascade::handle<StepData_UndefinedEntity> &, Interface_CopyTool &)) &StepData_UndefinedEntity::GetFromAnother, "reads another UndefinedEntity from StepData", py::arg("other"), py::arg("TC"));
cls_StepData_UndefinedEntity.def("FillShared", (void (StepData_UndefinedEntity::*)(Interface_EntityIterator &) const) &StepData_UndefinedEntity::FillShared, "Fills the list of shared entities", py::arg("list"));
cls_StepData_UndefinedEntity.def_static("get_type_name_", (const char * (*)()) &StepData_UndefinedEntity::get_type_name, "None");
cls_StepData_UndefinedEntity.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_UndefinedEntity::get_type_descriptor, "None");
cls_StepData_UndefinedEntity.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_UndefinedEntity::*)() const) &StepData_UndefinedEntity::DynamicType, "None");


}
