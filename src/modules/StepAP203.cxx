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
#include <StepData_SelectType.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>
#include <StepBasic_ProductDefinitionFormation.hxx>
#include <StepBasic_ProductDefinition.hxx>
#include <StepRepr_ConfigurationEffectivity.hxx>
#include <StepRepr_ConfigurationItem.hxx>
#include <StepBasic_SecurityClassification.hxx>
#include <StepAP203_ChangeRequest.hxx>
#include <StepAP203_Change.hxx>
#include <StepAP203_StartRequest.hxx>
#include <StepAP203_StartWork.hxx>
#include <StepBasic_Certification.hxx>
#include <StepBasic_Contract.hxx>
#include <StepAP203_ApprovedItem.hxx>
#include <NCollection_Array1.hxx>
#include <StepAP203_Array1OfApprovedItem.hxx>
#include <StepRepr_SuppliedPartRelationship.hxx>
#include <StepAP203_CertifiedItem.hxx>
#include <StepAP203_Array1OfCertifiedItem.hxx>
#include <StepAP203_ChangeRequestItem.hxx>
#include <StepAP203_Array1OfChangeRequestItem.hxx>
#include <StepRepr_AssemblyComponentUsage.hxx>
#include <StepAP203_ClassifiedItem.hxx>
#include <StepAP203_Array1OfClassifiedItem.hxx>
#include <StepAP203_ContractedItem.hxx>
#include <StepAP203_Array1OfContractedItem.hxx>
#include <StepBasic_ApprovalPersonOrganization.hxx>
#include <StepAP203_DateTimeItem.hxx>
#include <StepAP203_Array1OfDateTimeItem.hxx>
#include <StepBasic_Product.hxx>
#include <StepAP203_PersonOrganizationItem.hxx>
#include <StepAP203_Array1OfPersonOrganizationItem.hxx>
#include <StepRepr_ShapeAspect.hxx>
#include <StepAP203_SpecifiedItem.hxx>
#include <StepAP203_Array1OfSpecifiedItem.hxx>
#include <StepAP203_StartRequestItem.hxx>
#include <StepAP203_Array1OfStartRequestItem.hxx>
#include <StepAP203_WorkItem.hxx>
#include <StepAP203_Array1OfWorkItem.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <Standard_Std.hxx>
#include <StepAP203_HArray1OfApprovedItem.hxx>
#include <Standard_Type.hxx>
#include <StepBasic_ApprovalAssignment.hxx>
#include <StepBasic_Approval.hxx>
#include <StepAP203_CcDesignApproval.hxx>
#include <StepAP203_HArray1OfCertifiedItem.hxx>
#include <StepBasic_CertificationAssignment.hxx>
#include <StepAP203_CcDesignCertification.hxx>
#include <StepAP203_HArray1OfContractedItem.hxx>
#include <StepBasic_ContractAssignment.hxx>
#include <StepAP203_CcDesignContract.hxx>
#include <StepAP203_HArray1OfDateTimeItem.hxx>
#include <StepBasic_DateAndTimeAssignment.hxx>
#include <StepBasic_DateAndTime.hxx>
#include <StepBasic_DateTimeRole.hxx>
#include <StepAP203_CcDesignDateAndTimeAssignment.hxx>
#include <StepAP203_HArray1OfPersonOrganizationItem.hxx>
#include <StepBasic_PersonAndOrganizationAssignment.hxx>
#include <StepBasic_PersonAndOrganization.hxx>
#include <StepBasic_PersonAndOrganizationRole.hxx>
#include <StepAP203_CcDesignPersonAndOrganizationAssignment.hxx>
#include <StepAP203_HArray1OfClassifiedItem.hxx>
#include <StepBasic_SecurityClassificationAssignment.hxx>
#include <StepAP203_CcDesignSecurityClassification.hxx>
#include <StepAP203_HArray1OfSpecifiedItem.hxx>
#include <StepBasic_DocumentReference.hxx>
#include <StepBasic_Document.hxx>
#include <TCollection_HAsciiString.hxx>
#include <StepAP203_CcDesignSpecificationReference.hxx>
#include <StepAP203_HArray1OfWorkItem.hxx>
#include <StepBasic_ActionAssignment.hxx>
#include <StepBasic_Action.hxx>
#include <StepAP203_HArray1OfChangeRequestItem.hxx>
#include <StepBasic_ActionRequestAssignment.hxx>
#include <StepBasic_VersionedActionRequest.hxx>
#include <StepAP203_HArray1OfStartRequestItem.hxx>
#include <bind_NCollection_Array1.hxx>

PYBIND11_MODULE(StepAP203, mod) {

py::module::import("OCCT.StepData");
py::module::import("OCCT.Standard");
py::module::import("OCCT.StepBasic");
py::module::import("OCCT.StepRepr");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TCollection");

// CLASS: STEPAP203_APPROVEDITEM
py::class_<StepAP203_ApprovedItem, StepData_SelectType> cls_StepAP203_ApprovedItem(mod, "StepAP203_ApprovedItem", "Representation of STEP SELECT type ApprovedItem");

// Constructors
cls_StepAP203_ApprovedItem.def(py::init<>());

// Methods
// cls_StepAP203_ApprovedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_ApprovedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_ApprovedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_ApprovedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_ApprovedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_ApprovedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_ApprovedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_ApprovedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_ApprovedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_ApprovedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_ApprovedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_ApprovedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_ApprovedItem.def("CaseNum", (Standard_Integer (StepAP203_ApprovedItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_ApprovedItem::CaseNum, "Recognizes a kind of ApprovedItem select type 1 -> ProductDefinitionFormation from StepBasic 2 -> ProductDefinition from StepBasic 3 -> ConfigurationEffectivity from StepRepr 4 -> ConfigurationItem from StepRepr 5 -> SecurityClassification from StepBasic 6 -> ChangeRequest from StepAP203 7 -> Change from StepAP203 8 -> StartRequest from StepAP203 9 -> StartWork from StepAP203 10 -> Certification from StepBasic 11 -> Contract from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_ApprovedItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");
cls_StepAP203_ApprovedItem.def("ProductDefinition", (opencascade::handle<StepBasic_ProductDefinition> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::ProductDefinition, "Returns Value as ProductDefinition (or Null if another type)");
cls_StepAP203_ApprovedItem.def("ConfigurationEffectivity", (opencascade::handle<StepRepr_ConfigurationEffectivity> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::ConfigurationEffectivity, "Returns Value as ConfigurationEffectivity (or Null if another type)");
cls_StepAP203_ApprovedItem.def("ConfigurationItem", (opencascade::handle<StepRepr_ConfigurationItem> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::ConfigurationItem, "Returns Value as ConfigurationItem (or Null if another type)");
cls_StepAP203_ApprovedItem.def("SecurityClassification", (opencascade::handle<StepBasic_SecurityClassification> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::SecurityClassification, "Returns Value as SecurityClassification (or Null if another type)");
cls_StepAP203_ApprovedItem.def("ChangeRequest", (opencascade::handle<StepAP203_ChangeRequest> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::ChangeRequest, "Returns Value as ChangeRequest (or Null if another type)");
cls_StepAP203_ApprovedItem.def("Change", (opencascade::handle<StepAP203_Change> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::Change, "Returns Value as Change (or Null if another type)");
cls_StepAP203_ApprovedItem.def("StartRequest", (opencascade::handle<StepAP203_StartRequest> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::StartRequest, "Returns Value as StartRequest (or Null if another type)");
cls_StepAP203_ApprovedItem.def("StartWork", (opencascade::handle<StepAP203_StartWork> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::StartWork, "Returns Value as StartWork (or Null if another type)");
cls_StepAP203_ApprovedItem.def("Certification", (opencascade::handle<StepBasic_Certification> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::Certification, "Returns Value as Certification (or Null if another type)");
cls_StepAP203_ApprovedItem.def("Contract", (opencascade::handle<StepBasic_Contract> (StepAP203_ApprovedItem::*)() const) &StepAP203_ApprovedItem::Contract, "Returns Value as Contract (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFAPPROVEDITEM
bind_NCollection_Array1<StepAP203_ApprovedItem>(mod, "StepAP203_Array1OfApprovedItem", py::module_local(false));

// CLASS: STEPAP203_CERTIFIEDITEM
py::class_<StepAP203_CertifiedItem, StepData_SelectType> cls_StepAP203_CertifiedItem(mod, "StepAP203_CertifiedItem", "Representation of STEP SELECT type CertifiedItem");

// Constructors
cls_StepAP203_CertifiedItem.def(py::init<>());

// Methods
// cls_StepAP203_CertifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_CertifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_CertifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_CertifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_CertifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_CertifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_CertifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_CertifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_CertifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_CertifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_CertifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_CertifiedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_CertifiedItem.def("CaseNum", (Standard_Integer (StepAP203_CertifiedItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_CertifiedItem::CaseNum, "Recognizes a kind of CertifiedItem select type 1 -> SuppliedPartRelationship from StepRepr 0 else", py::arg("ent"));
cls_StepAP203_CertifiedItem.def("SuppliedPartRelationship", (opencascade::handle<StepRepr_SuppliedPartRelationship> (StepAP203_CertifiedItem::*)() const) &StepAP203_CertifiedItem::SuppliedPartRelationship, "Returns Value as SuppliedPartRelationship (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFCERTIFIEDITEM
bind_NCollection_Array1<StepAP203_CertifiedItem>(mod, "StepAP203_Array1OfCertifiedItem", py::module_local(false));

// CLASS: STEPAP203_CHANGEREQUESTITEM
py::class_<StepAP203_ChangeRequestItem, StepData_SelectType> cls_StepAP203_ChangeRequestItem(mod, "StepAP203_ChangeRequestItem", "Representation of STEP SELECT type ChangeRequestItem");

// Constructors
cls_StepAP203_ChangeRequestItem.def(py::init<>());

// Methods
// cls_StepAP203_ChangeRequestItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_ChangeRequestItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_ChangeRequestItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_ChangeRequestItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_ChangeRequestItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_ChangeRequestItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_ChangeRequestItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_ChangeRequestItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_ChangeRequestItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_ChangeRequestItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_ChangeRequestItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_ChangeRequestItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_ChangeRequestItem.def("CaseNum", (Standard_Integer (StepAP203_ChangeRequestItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_ChangeRequestItem::CaseNum, "Recognizes a kind of ChangeRequestItem select type 1 -> ProductDefinitionFormation from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_ChangeRequestItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_ChangeRequestItem::*)() const) &StepAP203_ChangeRequestItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFCHANGEREQUESTITEM
bind_NCollection_Array1<StepAP203_ChangeRequestItem>(mod, "StepAP203_Array1OfChangeRequestItem", py::module_local(false));

// CLASS: STEPAP203_CLASSIFIEDITEM
py::class_<StepAP203_ClassifiedItem, StepData_SelectType> cls_StepAP203_ClassifiedItem(mod, "StepAP203_ClassifiedItem", "Representation of STEP SELECT type ClassifiedItem");

// Constructors
cls_StepAP203_ClassifiedItem.def(py::init<>());

// Methods
// cls_StepAP203_ClassifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_ClassifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_ClassifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_ClassifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_ClassifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_ClassifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_ClassifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_ClassifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_ClassifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_ClassifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_ClassifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_ClassifiedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_ClassifiedItem.def("CaseNum", (Standard_Integer (StepAP203_ClassifiedItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_ClassifiedItem::CaseNum, "Recognizes a kind of ClassifiedItem select type 1 -> ProductDefinitionFormation from StepBasic 2 -> AssemblyComponentUsage from StepRepr 0 else", py::arg("ent"));
cls_StepAP203_ClassifiedItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_ClassifiedItem::*)() const) &StepAP203_ClassifiedItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");
cls_StepAP203_ClassifiedItem.def("AssemblyComponentUsage", (opencascade::handle<StepRepr_AssemblyComponentUsage> (StepAP203_ClassifiedItem::*)() const) &StepAP203_ClassifiedItem::AssemblyComponentUsage, "Returns Value as AssemblyComponentUsage (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFCLASSIFIEDITEM
bind_NCollection_Array1<StepAP203_ClassifiedItem>(mod, "StepAP203_Array1OfClassifiedItem", py::module_local(false));

// CLASS: STEPAP203_CONTRACTEDITEM
py::class_<StepAP203_ContractedItem, StepData_SelectType> cls_StepAP203_ContractedItem(mod, "StepAP203_ContractedItem", "Representation of STEP SELECT type ContractedItem");

// Constructors
cls_StepAP203_ContractedItem.def(py::init<>());

// Methods
// cls_StepAP203_ContractedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_ContractedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_ContractedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_ContractedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_ContractedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_ContractedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_ContractedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_ContractedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_ContractedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_ContractedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_ContractedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_ContractedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_ContractedItem.def("CaseNum", (Standard_Integer (StepAP203_ContractedItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_ContractedItem::CaseNum, "Recognizes a kind of ContractedItem select type 1 -> ProductDefinitionFormation from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_ContractedItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_ContractedItem::*)() const) &StepAP203_ContractedItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFCONTRACTEDITEM
bind_NCollection_Array1<StepAP203_ContractedItem>(mod, "StepAP203_Array1OfContractedItem", py::module_local(false));

// CLASS: STEPAP203_DATETIMEITEM
py::class_<StepAP203_DateTimeItem, StepData_SelectType> cls_StepAP203_DateTimeItem(mod, "StepAP203_DateTimeItem", "Representation of STEP SELECT type DateTimeItem");

// Constructors
cls_StepAP203_DateTimeItem.def(py::init<>());

// Methods
// cls_StepAP203_DateTimeItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_DateTimeItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_DateTimeItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_DateTimeItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_DateTimeItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_DateTimeItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_DateTimeItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_DateTimeItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_DateTimeItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_DateTimeItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_DateTimeItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_DateTimeItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_DateTimeItem.def("CaseNum", (Standard_Integer (StepAP203_DateTimeItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_DateTimeItem::CaseNum, "Recognizes a kind of DateTimeItem select type 1 -> ProductDefinition from StepBasic 2 -> ChangeRequest from StepAP203 3 -> StartRequest from StepAP203 4 -> Change from StepAP203 5 -> StartWork from StepAP203 6 -> ApprovalPersonOrganization from StepBasic 7 -> Contract from StepBasic 8 -> SecurityClassification from StepBasic 9 -> Certification from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_DateTimeItem.def("ProductDefinition", (opencascade::handle<StepBasic_ProductDefinition> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::ProductDefinition, "Returns Value as ProductDefinition (or Null if another type)");
cls_StepAP203_DateTimeItem.def("ChangeRequest", (opencascade::handle<StepAP203_ChangeRequest> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::ChangeRequest, "Returns Value as ChangeRequest (or Null if another type)");
cls_StepAP203_DateTimeItem.def("StartRequest", (opencascade::handle<StepAP203_StartRequest> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::StartRequest, "Returns Value as StartRequest (or Null if another type)");
cls_StepAP203_DateTimeItem.def("Change", (opencascade::handle<StepAP203_Change> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::Change, "Returns Value as Change (or Null if another type)");
cls_StepAP203_DateTimeItem.def("StartWork", (opencascade::handle<StepAP203_StartWork> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::StartWork, "Returns Value as StartWork (or Null if another type)");
cls_StepAP203_DateTimeItem.def("ApprovalPersonOrganization", (opencascade::handle<StepBasic_ApprovalPersonOrganization> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::ApprovalPersonOrganization, "Returns Value as ApprovalPersonOrganization (or Null if another type)");
cls_StepAP203_DateTimeItem.def("Contract", (opencascade::handle<StepBasic_Contract> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::Contract, "Returns Value as Contract (or Null if another type)");
cls_StepAP203_DateTimeItem.def("SecurityClassification", (opencascade::handle<StepBasic_SecurityClassification> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::SecurityClassification, "Returns Value as SecurityClassification (or Null if another type)");
cls_StepAP203_DateTimeItem.def("Certification", (opencascade::handle<StepBasic_Certification> (StepAP203_DateTimeItem::*)() const) &StepAP203_DateTimeItem::Certification, "Returns Value as Certification (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFDATETIMEITEM
bind_NCollection_Array1<StepAP203_DateTimeItem>(mod, "StepAP203_Array1OfDateTimeItem", py::module_local(false));

// CLASS: STEPAP203_PERSONORGANIZATIONITEM
py::class_<StepAP203_PersonOrganizationItem, StepData_SelectType> cls_StepAP203_PersonOrganizationItem(mod, "StepAP203_PersonOrganizationItem", "Representation of STEP SELECT type PersonOrganizationItem");

// Constructors
cls_StepAP203_PersonOrganizationItem.def(py::init<>());

// Methods
// cls_StepAP203_PersonOrganizationItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_PersonOrganizationItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_PersonOrganizationItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_PersonOrganizationItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_PersonOrganizationItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_PersonOrganizationItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_PersonOrganizationItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_PersonOrganizationItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_PersonOrganizationItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_PersonOrganizationItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_PersonOrganizationItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_PersonOrganizationItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_PersonOrganizationItem.def("CaseNum", (Standard_Integer (StepAP203_PersonOrganizationItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_PersonOrganizationItem::CaseNum, "Recognizes a kind of PersonOrganizationItem select type 1 -> Change from StepAP203 2 -> StartWork from StepAP203 3 -> ChangeRequest from StepAP203 4 -> StartRequest from StepAP203 5 -> ConfigurationItem from StepRepr 6 -> Product from StepBasic 7 -> ProductDefinitionFormation from StepBasic 8 -> ProductDefinition from StepBasic 9 -> Contract from StepBasic 10 -> SecurityClassification from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_PersonOrganizationItem.def("Change", (opencascade::handle<StepAP203_Change> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::Change, "Returns Value as Change (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("StartWork", (opencascade::handle<StepAP203_StartWork> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::StartWork, "Returns Value as StartWork (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("ChangeRequest", (opencascade::handle<StepAP203_ChangeRequest> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::ChangeRequest, "Returns Value as ChangeRequest (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("StartRequest", (opencascade::handle<StepAP203_StartRequest> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::StartRequest, "Returns Value as StartRequest (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("ConfigurationItem", (opencascade::handle<StepRepr_ConfigurationItem> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::ConfigurationItem, "Returns Value as ConfigurationItem (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("Product", (opencascade::handle<StepBasic_Product> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::Product, "Returns Value as Product (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("ProductDefinition", (opencascade::handle<StepBasic_ProductDefinition> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::ProductDefinition, "Returns Value as ProductDefinition (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("Contract", (opencascade::handle<StepBasic_Contract> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::Contract, "Returns Value as Contract (or Null if another type)");
cls_StepAP203_PersonOrganizationItem.def("SecurityClassification", (opencascade::handle<StepBasic_SecurityClassification> (StepAP203_PersonOrganizationItem::*)() const) &StepAP203_PersonOrganizationItem::SecurityClassification, "Returns Value as SecurityClassification (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFPERSONORGANIZATIONITEM
bind_NCollection_Array1<StepAP203_PersonOrganizationItem>(mod, "StepAP203_Array1OfPersonOrganizationItem", py::module_local(false));

// CLASS: STEPAP203_SPECIFIEDITEM
py::class_<StepAP203_SpecifiedItem, StepData_SelectType> cls_StepAP203_SpecifiedItem(mod, "StepAP203_SpecifiedItem", "Representation of STEP SELECT type SpecifiedItem");

// Constructors
cls_StepAP203_SpecifiedItem.def(py::init<>());

// Methods
// cls_StepAP203_SpecifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_SpecifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_SpecifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_SpecifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_SpecifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_SpecifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_SpecifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_SpecifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_SpecifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_SpecifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_SpecifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_SpecifiedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_SpecifiedItem.def("CaseNum", (Standard_Integer (StepAP203_SpecifiedItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_SpecifiedItem::CaseNum, "Recognizes a kind of SpecifiedItem select type 1 -> ProductDefinition from StepBasic 2 -> ShapeAspect from StepRepr 0 else", py::arg("ent"));
cls_StepAP203_SpecifiedItem.def("ProductDefinition", (opencascade::handle<StepBasic_ProductDefinition> (StepAP203_SpecifiedItem::*)() const) &StepAP203_SpecifiedItem::ProductDefinition, "Returns Value as ProductDefinition (or Null if another type)");
cls_StepAP203_SpecifiedItem.def("ShapeAspect", (opencascade::handle<StepRepr_ShapeAspect> (StepAP203_SpecifiedItem::*)() const) &StepAP203_SpecifiedItem::ShapeAspect, "Returns Value as ShapeAspect (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFSPECIFIEDITEM
bind_NCollection_Array1<StepAP203_SpecifiedItem>(mod, "StepAP203_Array1OfSpecifiedItem", py::module_local(false));

// CLASS: STEPAP203_STARTREQUESTITEM
py::class_<StepAP203_StartRequestItem, StepData_SelectType> cls_StepAP203_StartRequestItem(mod, "StepAP203_StartRequestItem", "Representation of STEP SELECT type StartRequestItem");

// Constructors
cls_StepAP203_StartRequestItem.def(py::init<>());

// Methods
// cls_StepAP203_StartRequestItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_StartRequestItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_StartRequestItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_StartRequestItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_StartRequestItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_StartRequestItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_StartRequestItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_StartRequestItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_StartRequestItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_StartRequestItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_StartRequestItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_StartRequestItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_StartRequestItem.def("CaseNum", (Standard_Integer (StepAP203_StartRequestItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_StartRequestItem::CaseNum, "Recognizes a kind of StartRequestItem select type 1 -> ProductDefinitionFormation from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_StartRequestItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_StartRequestItem::*)() const) &StepAP203_StartRequestItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFSTARTREQUESTITEM
bind_NCollection_Array1<StepAP203_StartRequestItem>(mod, "StepAP203_Array1OfStartRequestItem", py::module_local(false));

// CLASS: STEPAP203_WORKITEM
py::class_<StepAP203_WorkItem, StepData_SelectType> cls_StepAP203_WorkItem(mod, "StepAP203_WorkItem", "Representation of STEP SELECT type WorkItem");

// Constructors
cls_StepAP203_WorkItem.def(py::init<>());

// Methods
// cls_StepAP203_WorkItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_WorkItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_WorkItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_WorkItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_WorkItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_WorkItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_WorkItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_WorkItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_WorkItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_WorkItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_WorkItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_WorkItem::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP203_WorkItem.def("CaseNum", (Standard_Integer (StepAP203_WorkItem::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP203_WorkItem::CaseNum, "Recognizes a kind of WorkItem select type 1 -> ProductDefinitionFormation from StepBasic 0 else", py::arg("ent"));
cls_StepAP203_WorkItem.def("ProductDefinitionFormation", (opencascade::handle<StepBasic_ProductDefinitionFormation> (StepAP203_WorkItem::*)() const) &StepAP203_WorkItem::ProductDefinitionFormation, "Returns Value as ProductDefinitionFormation (or Null if another type)");

// TYPEDEF: STEPAP203_ARRAY1OFWORKITEM
bind_NCollection_Array1<StepAP203_WorkItem>(mod, "StepAP203_Array1OfWorkItem", py::module_local(false));

// CLASS: STEPAP203_HARRAY1OFAPPROVEDITEM
py::class_<StepAP203_HArray1OfApprovedItem, opencascade::handle<StepAP203_HArray1OfApprovedItem>, Standard_Transient> cls_StepAP203_HArray1OfApprovedItem(mod, "StepAP203_HArray1OfApprovedItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfApprovedItem.def(py::init<>());
cls_StepAP203_HArray1OfApprovedItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfApprovedItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfApprovedItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfApprovedItem.def(py::init<const StepAP203_Array1OfApprovedItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfApprovedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfApprovedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfApprovedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfApprovedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfApprovedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfApprovedItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfApprovedItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfApprovedItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfApprovedItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfApprovedItem.def("Array1", (const StepAP203_Array1OfApprovedItem & (StepAP203_HArray1OfApprovedItem::*)() const) &StepAP203_HArray1OfApprovedItem::Array1, "None");
cls_StepAP203_HArray1OfApprovedItem.def("ChangeArray1", (StepAP203_Array1OfApprovedItem & (StepAP203_HArray1OfApprovedItem::*)()) &StepAP203_HArray1OfApprovedItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfApprovedItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfApprovedItem::get_type_name, "None");
cls_StepAP203_HArray1OfApprovedItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfApprovedItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfApprovedItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfApprovedItem::*)() const) &StepAP203_HArray1OfApprovedItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNAPPROVAL
py::class_<StepAP203_CcDesignApproval, opencascade::handle<StepAP203_CcDesignApproval>, StepBasic_ApprovalAssignment> cls_StepAP203_CcDesignApproval(mod, "StepAP203_CcDesignApproval", "Representation of STEP entity CcDesignApproval");

// Constructors
cls_StepAP203_CcDesignApproval.def(py::init<>());

// Methods
cls_StepAP203_CcDesignApproval.def("Init", (void (StepAP203_CcDesignApproval::*)(const opencascade::handle<StepBasic_Approval> &, const opencascade::handle<StepAP203_HArray1OfApprovedItem> &)) &StepAP203_CcDesignApproval::Init, "Initialize all fields (own and inherited)", py::arg("aApprovalAssignment_AssignedApproval"), py::arg("aItems"));
cls_StepAP203_CcDesignApproval.def("Items", (opencascade::handle<StepAP203_HArray1OfApprovedItem> (StepAP203_CcDesignApproval::*)() const) &StepAP203_CcDesignApproval::Items, "Returns field Items");
cls_StepAP203_CcDesignApproval.def("SetItems", (void (StepAP203_CcDesignApproval::*)(const opencascade::handle<StepAP203_HArray1OfApprovedItem> &)) &StepAP203_CcDesignApproval::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignApproval.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignApproval::get_type_name, "None");
cls_StepAP203_CcDesignApproval.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignApproval::get_type_descriptor, "None");
cls_StepAP203_CcDesignApproval.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignApproval::*)() const) &StepAP203_CcDesignApproval::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFCERTIFIEDITEM
py::class_<StepAP203_HArray1OfCertifiedItem, opencascade::handle<StepAP203_HArray1OfCertifiedItem>, Standard_Transient> cls_StepAP203_HArray1OfCertifiedItem(mod, "StepAP203_HArray1OfCertifiedItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfCertifiedItem.def(py::init<>());
cls_StepAP203_HArray1OfCertifiedItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfCertifiedItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfCertifiedItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfCertifiedItem.def(py::init<const StepAP203_Array1OfCertifiedItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfCertifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfCertifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfCertifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfCertifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfCertifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfCertifiedItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfCertifiedItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfCertifiedItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfCertifiedItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfCertifiedItem.def("Array1", (const StepAP203_Array1OfCertifiedItem & (StepAP203_HArray1OfCertifiedItem::*)() const) &StepAP203_HArray1OfCertifiedItem::Array1, "None");
cls_StepAP203_HArray1OfCertifiedItem.def("ChangeArray1", (StepAP203_Array1OfCertifiedItem & (StepAP203_HArray1OfCertifiedItem::*)()) &StepAP203_HArray1OfCertifiedItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfCertifiedItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfCertifiedItem::get_type_name, "None");
cls_StepAP203_HArray1OfCertifiedItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfCertifiedItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfCertifiedItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfCertifiedItem::*)() const) &StepAP203_HArray1OfCertifiedItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNCERTIFICATION
py::class_<StepAP203_CcDesignCertification, opencascade::handle<StepAP203_CcDesignCertification>, StepBasic_CertificationAssignment> cls_StepAP203_CcDesignCertification(mod, "StepAP203_CcDesignCertification", "Representation of STEP entity CcDesignCertification");

// Constructors
cls_StepAP203_CcDesignCertification.def(py::init<>());

// Methods
cls_StepAP203_CcDesignCertification.def("Init", (void (StepAP203_CcDesignCertification::*)(const opencascade::handle<StepBasic_Certification> &, const opencascade::handle<StepAP203_HArray1OfCertifiedItem> &)) &StepAP203_CcDesignCertification::Init, "Initialize all fields (own and inherited)", py::arg("aCertificationAssignment_AssignedCertification"), py::arg("aItems"));
cls_StepAP203_CcDesignCertification.def("Items", (opencascade::handle<StepAP203_HArray1OfCertifiedItem> (StepAP203_CcDesignCertification::*)() const) &StepAP203_CcDesignCertification::Items, "Returns field Items");
cls_StepAP203_CcDesignCertification.def("SetItems", (void (StepAP203_CcDesignCertification::*)(const opencascade::handle<StepAP203_HArray1OfCertifiedItem> &)) &StepAP203_CcDesignCertification::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignCertification.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignCertification::get_type_name, "None");
cls_StepAP203_CcDesignCertification.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignCertification::get_type_descriptor, "None");
cls_StepAP203_CcDesignCertification.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignCertification::*)() const) &StepAP203_CcDesignCertification::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFCONTRACTEDITEM
py::class_<StepAP203_HArray1OfContractedItem, opencascade::handle<StepAP203_HArray1OfContractedItem>, Standard_Transient> cls_StepAP203_HArray1OfContractedItem(mod, "StepAP203_HArray1OfContractedItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfContractedItem.def(py::init<>());
cls_StepAP203_HArray1OfContractedItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfContractedItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfContractedItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfContractedItem.def(py::init<const StepAP203_Array1OfContractedItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfContractedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfContractedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfContractedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfContractedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfContractedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfContractedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfContractedItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfContractedItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfContractedItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfContractedItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfContractedItem.def("Array1", (const StepAP203_Array1OfContractedItem & (StepAP203_HArray1OfContractedItem::*)() const) &StepAP203_HArray1OfContractedItem::Array1, "None");
cls_StepAP203_HArray1OfContractedItem.def("ChangeArray1", (StepAP203_Array1OfContractedItem & (StepAP203_HArray1OfContractedItem::*)()) &StepAP203_HArray1OfContractedItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfContractedItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfContractedItem::get_type_name, "None");
cls_StepAP203_HArray1OfContractedItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfContractedItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfContractedItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfContractedItem::*)() const) &StepAP203_HArray1OfContractedItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNCONTRACT
py::class_<StepAP203_CcDesignContract, opencascade::handle<StepAP203_CcDesignContract>, StepBasic_ContractAssignment> cls_StepAP203_CcDesignContract(mod, "StepAP203_CcDesignContract", "Representation of STEP entity CcDesignContract");

// Constructors
cls_StepAP203_CcDesignContract.def(py::init<>());

// Methods
cls_StepAP203_CcDesignContract.def("Init", (void (StepAP203_CcDesignContract::*)(const opencascade::handle<StepBasic_Contract> &, const opencascade::handle<StepAP203_HArray1OfContractedItem> &)) &StepAP203_CcDesignContract::Init, "Initialize all fields (own and inherited)", py::arg("aContractAssignment_AssignedContract"), py::arg("aItems"));
cls_StepAP203_CcDesignContract.def("Items", (opencascade::handle<StepAP203_HArray1OfContractedItem> (StepAP203_CcDesignContract::*)() const) &StepAP203_CcDesignContract::Items, "Returns field Items");
cls_StepAP203_CcDesignContract.def("SetItems", (void (StepAP203_CcDesignContract::*)(const opencascade::handle<StepAP203_HArray1OfContractedItem> &)) &StepAP203_CcDesignContract::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignContract.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignContract::get_type_name, "None");
cls_StepAP203_CcDesignContract.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignContract::get_type_descriptor, "None");
cls_StepAP203_CcDesignContract.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignContract::*)() const) &StepAP203_CcDesignContract::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFDATETIMEITEM
py::class_<StepAP203_HArray1OfDateTimeItem, opencascade::handle<StepAP203_HArray1OfDateTimeItem>, Standard_Transient> cls_StepAP203_HArray1OfDateTimeItem(mod, "StepAP203_HArray1OfDateTimeItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfDateTimeItem.def(py::init<>());
cls_StepAP203_HArray1OfDateTimeItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfDateTimeItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfDateTimeItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfDateTimeItem.def(py::init<const StepAP203_Array1OfDateTimeItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfDateTimeItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfDateTimeItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfDateTimeItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfDateTimeItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfDateTimeItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfDateTimeItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfDateTimeItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfDateTimeItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfDateTimeItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfDateTimeItem.def("Array1", (const StepAP203_Array1OfDateTimeItem & (StepAP203_HArray1OfDateTimeItem::*)() const) &StepAP203_HArray1OfDateTimeItem::Array1, "None");
cls_StepAP203_HArray1OfDateTimeItem.def("ChangeArray1", (StepAP203_Array1OfDateTimeItem & (StepAP203_HArray1OfDateTimeItem::*)()) &StepAP203_HArray1OfDateTimeItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfDateTimeItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfDateTimeItem::get_type_name, "None");
cls_StepAP203_HArray1OfDateTimeItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfDateTimeItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfDateTimeItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfDateTimeItem::*)() const) &StepAP203_HArray1OfDateTimeItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNDATEANDTIMEASSIGNMENT
py::class_<StepAP203_CcDesignDateAndTimeAssignment, opencascade::handle<StepAP203_CcDesignDateAndTimeAssignment>, StepBasic_DateAndTimeAssignment> cls_StepAP203_CcDesignDateAndTimeAssignment(mod, "StepAP203_CcDesignDateAndTimeAssignment", "Representation of STEP entity CcDesignDateAndTimeAssignment");

// Constructors
cls_StepAP203_CcDesignDateAndTimeAssignment.def(py::init<>());

// Methods
cls_StepAP203_CcDesignDateAndTimeAssignment.def("Init", (void (StepAP203_CcDesignDateAndTimeAssignment::*)(const opencascade::handle<StepBasic_DateAndTime> &, const opencascade::handle<StepBasic_DateTimeRole> &, const opencascade::handle<StepAP203_HArray1OfDateTimeItem> &)) &StepAP203_CcDesignDateAndTimeAssignment::Init, "Initialize all fields (own and inherited)", py::arg("aDateAndTimeAssignment_AssignedDateAndTime"), py::arg("aDateAndTimeAssignment_Role"), py::arg("aItems"));
cls_StepAP203_CcDesignDateAndTimeAssignment.def("Items", (opencascade::handle<StepAP203_HArray1OfDateTimeItem> (StepAP203_CcDesignDateAndTimeAssignment::*)() const) &StepAP203_CcDesignDateAndTimeAssignment::Items, "Returns field Items");
cls_StepAP203_CcDesignDateAndTimeAssignment.def("SetItems", (void (StepAP203_CcDesignDateAndTimeAssignment::*)(const opencascade::handle<StepAP203_HArray1OfDateTimeItem> &)) &StepAP203_CcDesignDateAndTimeAssignment::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignDateAndTimeAssignment.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignDateAndTimeAssignment::get_type_name, "None");
cls_StepAP203_CcDesignDateAndTimeAssignment.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignDateAndTimeAssignment::get_type_descriptor, "None");
cls_StepAP203_CcDesignDateAndTimeAssignment.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignDateAndTimeAssignment::*)() const) &StepAP203_CcDesignDateAndTimeAssignment::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFPERSONORGANIZATIONITEM
py::class_<StepAP203_HArray1OfPersonOrganizationItem, opencascade::handle<StepAP203_HArray1OfPersonOrganizationItem>, Standard_Transient> cls_StepAP203_HArray1OfPersonOrganizationItem(mod, "StepAP203_HArray1OfPersonOrganizationItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfPersonOrganizationItem.def(py::init<>());
cls_StepAP203_HArray1OfPersonOrganizationItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfPersonOrganizationItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfPersonOrganizationItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfPersonOrganizationItem.def(py::init<const StepAP203_Array1OfPersonOrganizationItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfPersonOrganizationItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfPersonOrganizationItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfPersonOrganizationItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfPersonOrganizationItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfPersonOrganizationItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfPersonOrganizationItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfPersonOrganizationItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfPersonOrganizationItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfPersonOrganizationItem.def("Array1", (const StepAP203_Array1OfPersonOrganizationItem & (StepAP203_HArray1OfPersonOrganizationItem::*)() const) &StepAP203_HArray1OfPersonOrganizationItem::Array1, "None");
cls_StepAP203_HArray1OfPersonOrganizationItem.def("ChangeArray1", (StepAP203_Array1OfPersonOrganizationItem & (StepAP203_HArray1OfPersonOrganizationItem::*)()) &StepAP203_HArray1OfPersonOrganizationItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfPersonOrganizationItem::get_type_name, "None");
cls_StepAP203_HArray1OfPersonOrganizationItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfPersonOrganizationItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfPersonOrganizationItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfPersonOrganizationItem::*)() const) &StepAP203_HArray1OfPersonOrganizationItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNPERSONANDORGANIZATIONASSIGNMENT
py::class_<StepAP203_CcDesignPersonAndOrganizationAssignment, opencascade::handle<StepAP203_CcDesignPersonAndOrganizationAssignment>, StepBasic_PersonAndOrganizationAssignment> cls_StepAP203_CcDesignPersonAndOrganizationAssignment(mod, "StepAP203_CcDesignPersonAndOrganizationAssignment", "Representation of STEP entity CcDesignPersonAndOrganizationAssignment");

// Constructors
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def(py::init<>());

// Methods
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def("Init", (void (StepAP203_CcDesignPersonAndOrganizationAssignment::*)(const opencascade::handle<StepBasic_PersonAndOrganization> &, const opencascade::handle<StepBasic_PersonAndOrganizationRole> &, const opencascade::handle<StepAP203_HArray1OfPersonOrganizationItem> &)) &StepAP203_CcDesignPersonAndOrganizationAssignment::Init, "Initialize all fields (own and inherited)", py::arg("aPersonAndOrganizationAssignment_AssignedPersonAndOrganization"), py::arg("aPersonAndOrganizationAssignment_Role"), py::arg("aItems"));
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def("Items", (opencascade::handle<StepAP203_HArray1OfPersonOrganizationItem> (StepAP203_CcDesignPersonAndOrganizationAssignment::*)() const) &StepAP203_CcDesignPersonAndOrganizationAssignment::Items, "Returns field Items");
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def("SetItems", (void (StepAP203_CcDesignPersonAndOrganizationAssignment::*)(const opencascade::handle<StepAP203_HArray1OfPersonOrganizationItem> &)) &StepAP203_CcDesignPersonAndOrganizationAssignment::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignPersonAndOrganizationAssignment::get_type_name, "None");
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignPersonAndOrganizationAssignment::get_type_descriptor, "None");
cls_StepAP203_CcDesignPersonAndOrganizationAssignment.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignPersonAndOrganizationAssignment::*)() const) &StepAP203_CcDesignPersonAndOrganizationAssignment::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFCLASSIFIEDITEM
py::class_<StepAP203_HArray1OfClassifiedItem, opencascade::handle<StepAP203_HArray1OfClassifiedItem>, Standard_Transient> cls_StepAP203_HArray1OfClassifiedItem(mod, "StepAP203_HArray1OfClassifiedItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfClassifiedItem.def(py::init<>());
cls_StepAP203_HArray1OfClassifiedItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfClassifiedItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfClassifiedItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfClassifiedItem.def(py::init<const StepAP203_Array1OfClassifiedItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfClassifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfClassifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfClassifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfClassifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfClassifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfClassifiedItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfClassifiedItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfClassifiedItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfClassifiedItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfClassifiedItem.def("Array1", (const StepAP203_Array1OfClassifiedItem & (StepAP203_HArray1OfClassifiedItem::*)() const) &StepAP203_HArray1OfClassifiedItem::Array1, "None");
cls_StepAP203_HArray1OfClassifiedItem.def("ChangeArray1", (StepAP203_Array1OfClassifiedItem & (StepAP203_HArray1OfClassifiedItem::*)()) &StepAP203_HArray1OfClassifiedItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfClassifiedItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfClassifiedItem::get_type_name, "None");
cls_StepAP203_HArray1OfClassifiedItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfClassifiedItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfClassifiedItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfClassifiedItem::*)() const) &StepAP203_HArray1OfClassifiedItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNSECURITYCLASSIFICATION
py::class_<StepAP203_CcDesignSecurityClassification, opencascade::handle<StepAP203_CcDesignSecurityClassification>, StepBasic_SecurityClassificationAssignment> cls_StepAP203_CcDesignSecurityClassification(mod, "StepAP203_CcDesignSecurityClassification", "Representation of STEP entity CcDesignSecurityClassification");

// Constructors
cls_StepAP203_CcDesignSecurityClassification.def(py::init<>());

// Methods
cls_StepAP203_CcDesignSecurityClassification.def("Init", (void (StepAP203_CcDesignSecurityClassification::*)(const opencascade::handle<StepBasic_SecurityClassification> &, const opencascade::handle<StepAP203_HArray1OfClassifiedItem> &)) &StepAP203_CcDesignSecurityClassification::Init, "Initialize all fields (own and inherited)", py::arg("aSecurityClassificationAssignment_AssignedSecurityClassification"), py::arg("aItems"));
cls_StepAP203_CcDesignSecurityClassification.def("Items", (opencascade::handle<StepAP203_HArray1OfClassifiedItem> (StepAP203_CcDesignSecurityClassification::*)() const) &StepAP203_CcDesignSecurityClassification::Items, "Returns field Items");
cls_StepAP203_CcDesignSecurityClassification.def("SetItems", (void (StepAP203_CcDesignSecurityClassification::*)(const opencascade::handle<StepAP203_HArray1OfClassifiedItem> &)) &StepAP203_CcDesignSecurityClassification::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignSecurityClassification.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignSecurityClassification::get_type_name, "None");
cls_StepAP203_CcDesignSecurityClassification.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignSecurityClassification::get_type_descriptor, "None");
cls_StepAP203_CcDesignSecurityClassification.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignSecurityClassification::*)() const) &StepAP203_CcDesignSecurityClassification::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFSPECIFIEDITEM
py::class_<StepAP203_HArray1OfSpecifiedItem, opencascade::handle<StepAP203_HArray1OfSpecifiedItem>, Standard_Transient> cls_StepAP203_HArray1OfSpecifiedItem(mod, "StepAP203_HArray1OfSpecifiedItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfSpecifiedItem.def(py::init<>());
cls_StepAP203_HArray1OfSpecifiedItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfSpecifiedItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfSpecifiedItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfSpecifiedItem.def(py::init<const StepAP203_Array1OfSpecifiedItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfSpecifiedItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfSpecifiedItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfSpecifiedItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfSpecifiedItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfSpecifiedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfSpecifiedItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfSpecifiedItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfSpecifiedItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfSpecifiedItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfSpecifiedItem.def("Array1", (const StepAP203_Array1OfSpecifiedItem & (StepAP203_HArray1OfSpecifiedItem::*)() const) &StepAP203_HArray1OfSpecifiedItem::Array1, "None");
cls_StepAP203_HArray1OfSpecifiedItem.def("ChangeArray1", (StepAP203_Array1OfSpecifiedItem & (StepAP203_HArray1OfSpecifiedItem::*)()) &StepAP203_HArray1OfSpecifiedItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfSpecifiedItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfSpecifiedItem::get_type_name, "None");
cls_StepAP203_HArray1OfSpecifiedItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfSpecifiedItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfSpecifiedItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfSpecifiedItem::*)() const) &StepAP203_HArray1OfSpecifiedItem::DynamicType, "None");

// CLASS: STEPAP203_CCDESIGNSPECIFICATIONREFERENCE
py::class_<StepAP203_CcDesignSpecificationReference, opencascade::handle<StepAP203_CcDesignSpecificationReference>, StepBasic_DocumentReference> cls_StepAP203_CcDesignSpecificationReference(mod, "StepAP203_CcDesignSpecificationReference", "Representation of STEP entity CcDesignSpecificationReference");

// Constructors
cls_StepAP203_CcDesignSpecificationReference.def(py::init<>());

// Methods
cls_StepAP203_CcDesignSpecificationReference.def("Init", (void (StepAP203_CcDesignSpecificationReference::*)(const opencascade::handle<StepBasic_Document> &, const opencascade::handle<TCollection_HAsciiString> &, const opencascade::handle<StepAP203_HArray1OfSpecifiedItem> &)) &StepAP203_CcDesignSpecificationReference::Init, "Initialize all fields (own and inherited)", py::arg("aDocumentReference_AssignedDocument"), py::arg("aDocumentReference_Source"), py::arg("aItems"));
cls_StepAP203_CcDesignSpecificationReference.def("Items", (opencascade::handle<StepAP203_HArray1OfSpecifiedItem> (StepAP203_CcDesignSpecificationReference::*)() const) &StepAP203_CcDesignSpecificationReference::Items, "Returns field Items");
cls_StepAP203_CcDesignSpecificationReference.def("SetItems", (void (StepAP203_CcDesignSpecificationReference::*)(const opencascade::handle<StepAP203_HArray1OfSpecifiedItem> &)) &StepAP203_CcDesignSpecificationReference::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_CcDesignSpecificationReference.def_static("get_type_name_", (const char * (*)()) &StepAP203_CcDesignSpecificationReference::get_type_name, "None");
cls_StepAP203_CcDesignSpecificationReference.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_CcDesignSpecificationReference::get_type_descriptor, "None");
cls_StepAP203_CcDesignSpecificationReference.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_CcDesignSpecificationReference::*)() const) &StepAP203_CcDesignSpecificationReference::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFWORKITEM
py::class_<StepAP203_HArray1OfWorkItem, opencascade::handle<StepAP203_HArray1OfWorkItem>, Standard_Transient> cls_StepAP203_HArray1OfWorkItem(mod, "StepAP203_HArray1OfWorkItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfWorkItem.def(py::init<>());
cls_StepAP203_HArray1OfWorkItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfWorkItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfWorkItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfWorkItem.def(py::init<const StepAP203_Array1OfWorkItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfWorkItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfWorkItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfWorkItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfWorkItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfWorkItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfWorkItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfWorkItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfWorkItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfWorkItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfWorkItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfWorkItem.def("Array1", (const StepAP203_Array1OfWorkItem & (StepAP203_HArray1OfWorkItem::*)() const) &StepAP203_HArray1OfWorkItem::Array1, "None");
cls_StepAP203_HArray1OfWorkItem.def("ChangeArray1", (StepAP203_Array1OfWorkItem & (StepAP203_HArray1OfWorkItem::*)()) &StepAP203_HArray1OfWorkItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfWorkItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfWorkItem::get_type_name, "None");
cls_StepAP203_HArray1OfWorkItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfWorkItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfWorkItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfWorkItem::*)() const) &StepAP203_HArray1OfWorkItem::DynamicType, "None");

// CLASS: STEPAP203_CHANGE
py::class_<StepAP203_Change, opencascade::handle<StepAP203_Change>, StepBasic_ActionAssignment> cls_StepAP203_Change(mod, "StepAP203_Change", "Representation of STEP entity Change");

// Constructors
cls_StepAP203_Change.def(py::init<>());

// Methods
cls_StepAP203_Change.def("Init", (void (StepAP203_Change::*)(const opencascade::handle<StepBasic_Action> &, const opencascade::handle<StepAP203_HArray1OfWorkItem> &)) &StepAP203_Change::Init, "Initialize all fields (own and inherited)", py::arg("aActionAssignment_AssignedAction"), py::arg("aItems"));
cls_StepAP203_Change.def("Items", (opencascade::handle<StepAP203_HArray1OfWorkItem> (StepAP203_Change::*)() const) &StepAP203_Change::Items, "Returns field Items");
cls_StepAP203_Change.def("SetItems", (void (StepAP203_Change::*)(const opencascade::handle<StepAP203_HArray1OfWorkItem> &)) &StepAP203_Change::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_Change.def_static("get_type_name_", (const char * (*)()) &StepAP203_Change::get_type_name, "None");
cls_StepAP203_Change.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_Change::get_type_descriptor, "None");
cls_StepAP203_Change.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_Change::*)() const) &StepAP203_Change::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFCHANGEREQUESTITEM
py::class_<StepAP203_HArray1OfChangeRequestItem, opencascade::handle<StepAP203_HArray1OfChangeRequestItem>, Standard_Transient> cls_StepAP203_HArray1OfChangeRequestItem(mod, "StepAP203_HArray1OfChangeRequestItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfChangeRequestItem.def(py::init<>());
cls_StepAP203_HArray1OfChangeRequestItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfChangeRequestItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfChangeRequestItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfChangeRequestItem.def(py::init<const StepAP203_Array1OfChangeRequestItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfChangeRequestItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfChangeRequestItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfChangeRequestItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfChangeRequestItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfChangeRequestItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfChangeRequestItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfChangeRequestItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfChangeRequestItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfChangeRequestItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfChangeRequestItem.def("Array1", (const StepAP203_Array1OfChangeRequestItem & (StepAP203_HArray1OfChangeRequestItem::*)() const) &StepAP203_HArray1OfChangeRequestItem::Array1, "None");
cls_StepAP203_HArray1OfChangeRequestItem.def("ChangeArray1", (StepAP203_Array1OfChangeRequestItem & (StepAP203_HArray1OfChangeRequestItem::*)()) &StepAP203_HArray1OfChangeRequestItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfChangeRequestItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfChangeRequestItem::get_type_name, "None");
cls_StepAP203_HArray1OfChangeRequestItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfChangeRequestItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfChangeRequestItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfChangeRequestItem::*)() const) &StepAP203_HArray1OfChangeRequestItem::DynamicType, "None");

// CLASS: STEPAP203_CHANGEREQUEST
py::class_<StepAP203_ChangeRequest, opencascade::handle<StepAP203_ChangeRequest>, StepBasic_ActionRequestAssignment> cls_StepAP203_ChangeRequest(mod, "StepAP203_ChangeRequest", "Representation of STEP entity ChangeRequest");

// Constructors
cls_StepAP203_ChangeRequest.def(py::init<>());

// Methods
cls_StepAP203_ChangeRequest.def("Init", (void (StepAP203_ChangeRequest::*)(const opencascade::handle<StepBasic_VersionedActionRequest> &, const opencascade::handle<StepAP203_HArray1OfChangeRequestItem> &)) &StepAP203_ChangeRequest::Init, "Initialize all fields (own and inherited)", py::arg("aActionRequestAssignment_AssignedActionRequest"), py::arg("aItems"));
cls_StepAP203_ChangeRequest.def("Items", (opencascade::handle<StepAP203_HArray1OfChangeRequestItem> (StepAP203_ChangeRequest::*)() const) &StepAP203_ChangeRequest::Items, "Returns field Items");
cls_StepAP203_ChangeRequest.def("SetItems", (void (StepAP203_ChangeRequest::*)(const opencascade::handle<StepAP203_HArray1OfChangeRequestItem> &)) &StepAP203_ChangeRequest::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_ChangeRequest.def_static("get_type_name_", (const char * (*)()) &StepAP203_ChangeRequest::get_type_name, "None");
cls_StepAP203_ChangeRequest.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_ChangeRequest::get_type_descriptor, "None");
cls_StepAP203_ChangeRequest.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_ChangeRequest::*)() const) &StepAP203_ChangeRequest::DynamicType, "None");

// CLASS: STEPAP203_HARRAY1OFSTARTREQUESTITEM
py::class_<StepAP203_HArray1OfStartRequestItem, opencascade::handle<StepAP203_HArray1OfStartRequestItem>, Standard_Transient> cls_StepAP203_HArray1OfStartRequestItem(mod, "StepAP203_HArray1OfStartRequestItem", "None", py::multiple_inheritance());

// Constructors
cls_StepAP203_HArray1OfStartRequestItem.def(py::init<>());
cls_StepAP203_HArray1OfStartRequestItem.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_StepAP203_HArray1OfStartRequestItem.def(py::init<const Standard_Integer, const Standard_Integer, const StepAP203_Array1OfStartRequestItem::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_StepAP203_HArray1OfStartRequestItem.def(py::init<const StepAP203_Array1OfStartRequestItem &>(), py::arg("theOther"));

// Methods
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator new_", (void * (*)(size_t)) &StepAP203_HArray1OfStartRequestItem::operator new, "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator delete_", (void (*)(void *)) &StepAP203_HArray1OfStartRequestItem::operator delete, "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator new[]_", (void * (*)(size_t)) &StepAP203_HArray1OfStartRequestItem::operator new[], "None", py::arg("theSize"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator delete[]_", (void (*)(void *)) &StepAP203_HArray1OfStartRequestItem::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP203_HArray1OfStartRequestItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator delete_", (void (*)(void *, void *)) &StepAP203_HArray1OfStartRequestItem::operator delete, "None", py::arg(""), py::arg(""));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfStartRequestItem::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_StepAP203_HArray1OfStartRequestItem.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &StepAP203_HArray1OfStartRequestItem::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_StepAP203_HArray1OfStartRequestItem.def("Array1", (const StepAP203_Array1OfStartRequestItem & (StepAP203_HArray1OfStartRequestItem::*)() const) &StepAP203_HArray1OfStartRequestItem::Array1, "None");
cls_StepAP203_HArray1OfStartRequestItem.def("ChangeArray1", (StepAP203_Array1OfStartRequestItem & (StepAP203_HArray1OfStartRequestItem::*)()) &StepAP203_HArray1OfStartRequestItem::ChangeArray1, "None");
cls_StepAP203_HArray1OfStartRequestItem.def_static("get_type_name_", (const char * (*)()) &StepAP203_HArray1OfStartRequestItem::get_type_name, "None");
cls_StepAP203_HArray1OfStartRequestItem.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_HArray1OfStartRequestItem::get_type_descriptor, "None");
cls_StepAP203_HArray1OfStartRequestItem.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_HArray1OfStartRequestItem::*)() const) &StepAP203_HArray1OfStartRequestItem::DynamicType, "None");

// CLASS: STEPAP203_STARTREQUEST
py::class_<StepAP203_StartRequest, opencascade::handle<StepAP203_StartRequest>, StepBasic_ActionRequestAssignment> cls_StepAP203_StartRequest(mod, "StepAP203_StartRequest", "Representation of STEP entity StartRequest");

// Constructors
cls_StepAP203_StartRequest.def(py::init<>());

// Methods
cls_StepAP203_StartRequest.def("Init", (void (StepAP203_StartRequest::*)(const opencascade::handle<StepBasic_VersionedActionRequest> &, const opencascade::handle<StepAP203_HArray1OfStartRequestItem> &)) &StepAP203_StartRequest::Init, "Initialize all fields (own and inherited)", py::arg("aActionRequestAssignment_AssignedActionRequest"), py::arg("aItems"));
cls_StepAP203_StartRequest.def("Items", (opencascade::handle<StepAP203_HArray1OfStartRequestItem> (StepAP203_StartRequest::*)() const) &StepAP203_StartRequest::Items, "Returns field Items");
cls_StepAP203_StartRequest.def("SetItems", (void (StepAP203_StartRequest::*)(const opencascade::handle<StepAP203_HArray1OfStartRequestItem> &)) &StepAP203_StartRequest::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_StartRequest.def_static("get_type_name_", (const char * (*)()) &StepAP203_StartRequest::get_type_name, "None");
cls_StepAP203_StartRequest.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_StartRequest::get_type_descriptor, "None");
cls_StepAP203_StartRequest.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_StartRequest::*)() const) &StepAP203_StartRequest::DynamicType, "None");

// CLASS: STEPAP203_STARTWORK
py::class_<StepAP203_StartWork, opencascade::handle<StepAP203_StartWork>, StepBasic_ActionAssignment> cls_StepAP203_StartWork(mod, "StepAP203_StartWork", "Representation of STEP entity StartWork");

// Constructors
cls_StepAP203_StartWork.def(py::init<>());

// Methods
cls_StepAP203_StartWork.def("Init", (void (StepAP203_StartWork::*)(const opencascade::handle<StepBasic_Action> &, const opencascade::handle<StepAP203_HArray1OfWorkItem> &)) &StepAP203_StartWork::Init, "Initialize all fields (own and inherited)", py::arg("aActionAssignment_AssignedAction"), py::arg("aItems"));
cls_StepAP203_StartWork.def("Items", (opencascade::handle<StepAP203_HArray1OfWorkItem> (StepAP203_StartWork::*)() const) &StepAP203_StartWork::Items, "Returns field Items");
cls_StepAP203_StartWork.def("SetItems", (void (StepAP203_StartWork::*)(const opencascade::handle<StepAP203_HArray1OfWorkItem> &)) &StepAP203_StartWork::SetItems, "Set field Items", py::arg("Items"));
cls_StepAP203_StartWork.def_static("get_type_name_", (const char * (*)()) &StepAP203_StartWork::get_type_name, "None");
cls_StepAP203_StartWork.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepAP203_StartWork::get_type_descriptor, "None");
cls_StepAP203_StartWork.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepAP203_StartWork::*)() const) &StepAP203_StartWork::DynamicType, "None");


}
