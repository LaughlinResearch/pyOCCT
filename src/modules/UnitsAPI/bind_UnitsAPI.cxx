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
#include <Standard_Handle.hxx>
#include <Units_Dimensions.hxx>
#include <UnitsAPI_SystemUnits.hxx>
#include <UnitsAPI.hxx>

void bind_UnitsAPI(py::module &mod){

py::class_<UnitsAPI, std::unique_ptr<UnitsAPI, Deleter<UnitsAPI>>> cls_UnitsAPI(mod, "UnitsAPI", "The UnitsAPI global functions are used to convert a value from any unit into another unit. Principles Conversion is executed among three unit systems: - the SI System - the user's Local System - the user's Current System. The SI System is the standard international unit system. It is indicated by SI in the synopses of the UnitsAPI functions. The MDTV System corresponds to the SI international standard but the length unit and all its derivatives use millimeters instead of the meters. Both systems are proposed by Open CASCADE; the SI System is the standard option. By selecting one of these two systems, the user defines his Local System through the SetLocalSystem function. The Local System is indicated by LS in the synopses of the UnitsAPI functions. The user's Local System units can be modified in the working environment. The user defines his Current System by modifying its units through the SetCurrentUnit function. The Current System is indicated by Current in the synopses of the UnitsAPI functions.");

// Constructors

// Fields

// Methods
// cls_UnitsAPI.def_static("operator new_", (void * (*)(size_t)) &UnitsAPI::operator new, "None", py::arg("theSize"));
// cls_UnitsAPI.def_static("operator delete_", (void (*)(void *)) &UnitsAPI::operator delete, "None", py::arg("theAddress"));
// cls_UnitsAPI.def_static("operator new[]_", (void * (*)(size_t)) &UnitsAPI::operator new[], "None", py::arg("theSize"));
// cls_UnitsAPI.def_static("operator delete[]_", (void (*)(void *)) &UnitsAPI::operator delete[], "None", py::arg("theAddress"));
// cls_UnitsAPI.def_static("operator new_", (void * (*)(size_t, void *)) &UnitsAPI::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_UnitsAPI.def_static("operator delete_", (void (*)(void *, void *)) &UnitsAPI::operator delete, "None", py::arg(""), py::arg(""));
cls_UnitsAPI.def_static("CurrentToLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::CurrentToLS, "Converts the current unit value to the local system units value. Example: CurrentToLS(1.,'LENGTH') returns 1000. if the current length unit is meter and LocalSystem is MDTV.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("CurrentToSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::CurrentToSI, "Converts the current unit value to the SI system units value. Example: CurrentToSI(1.,'LENGTH') returns 0.001 if current length unit is millimeter.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("CurrentFromLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::CurrentFromLS, "Converts the local system units value to the current unit value. Example: CurrentFromLS(1000.,'LENGTH') returns 1. if current length unit is meter and LocalSystem is MDTV.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("CurrentFromSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::CurrentFromSI, "Converts the SI system units value to the current unit value. Example: CurrentFromSI(0.001,'LENGTH') returns 1 if current length unit is millimeter.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("AnyToLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::AnyToLS, "Converts the local unit value to the local system units value. Example: AnyToLS(1.,'in.') returns 25.4 if the LocalSystem is MDTV.", py::arg("aData"), py::arg("aUnit"));
cls_UnitsAPI.def_static("AnyToLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString, opencascade::handle<Units_Dimensions> &)) &UnitsAPI::AnyToLS, "Converts the local unit value to the local system units value. and gives the associated dimension of the unit", py::arg("aData"), py::arg("aUnit"), py::arg("aDim"));
cls_UnitsAPI.def_static("AnyToSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::AnyToSI, "Converts the local unit value to the SI system units value. Example: AnyToSI(1.,'in.') returns 0.0254", py::arg("aData"), py::arg("aUnit"));
cls_UnitsAPI.def_static("AnyToSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString, opencascade::handle<Units_Dimensions> &)) &UnitsAPI::AnyToSI, "Converts the local unit value to the SI system units value. and gives the associated dimension of the unit", py::arg("aData"), py::arg("aUnit"), py::arg("aDim"));
cls_UnitsAPI.def_static("AnyFromLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::AnyFromLS, "Converts the local system units value to the local unit value. Example: AnyFromLS(25.4,'in.') returns 1. if the LocalSystem is MDTV. Note: aUnit is also used to identify the type of physical quantity to convert.", py::arg("aData"), py::arg("aUnit"));
cls_UnitsAPI.def_static("AnyFromSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::AnyFromSI, "Converts the SI system units value to the local unit value. Example: AnyFromSI(0.0254,'in.') returns 0.001 Note: aUnit is also used to identify the type of physical quantity to convert.", py::arg("aData"), py::arg("aUnit"));
cls_UnitsAPI.def_static("CurrentToAny_", (Standard_Real (*)(const Standard_Real, const Standard_CString, const Standard_CString)) &UnitsAPI::CurrentToAny, "Converts the aData value expressed in the current unit for the working environment, as defined for the physical quantity aQuantity by the last call to the SetCurrentUnit function, into the unit aUnit.", py::arg("aData"), py::arg("aQuantity"), py::arg("aUnit"));
cls_UnitsAPI.def_static("CurrentFromAny_", (Standard_Real (*)(const Standard_Real, const Standard_CString, const Standard_CString)) &UnitsAPI::CurrentFromAny, "Converts the aData value expressed in the unit aUnit, into the current unit for the working environment, as defined for the physical quantity aQuantity by the last call to the SetCurrentUnit function.", py::arg("aData"), py::arg("aQuantity"), py::arg("aUnit"));
cls_UnitsAPI.def_static("AnyToAny_", (Standard_Real (*)(const Standard_Real, const Standard_CString, const Standard_CString)) &UnitsAPI::AnyToAny, "Converts the local unit value to another local unit value. Example: AnyToAny(0.0254,'in.','millimeter') returns 1. ;", py::arg("aData"), py::arg("aUnit1"), py::arg("aUnit2"));
cls_UnitsAPI.def_static("LSToSI_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::LSToSI, "Converts the local system units value to the SI system unit value. Example: LSToSI(1.,'LENGTH') returns 0.001 if the local system length unit is millimeter.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("SIToLS_", (Standard_Real (*)(const Standard_Real, const Standard_CString)) &UnitsAPI::SIToLS, "Converts the SI system unit value to the local system units value. Example: SIToLS(1.,'LENGTH') returns 1000. if the local system length unit is millimeter.", py::arg("aData"), py::arg("aQuantity"));
cls_UnitsAPI.def_static("SetLocalSystem_", []() -> void { return UnitsAPI::SetLocalSystem(); });
cls_UnitsAPI.def_static("SetLocalSystem_", (void (*)(const UnitsAPI_SystemUnits)) &UnitsAPI::SetLocalSystem, "Sets the local system units. Example: SetLocalSystem(UnitsAPI_MDTV)", py::arg("aSystemUnit"));
cls_UnitsAPI.def_static("LocalSystem_", (UnitsAPI_SystemUnits (*)()) &UnitsAPI::LocalSystem, "Returns the current local system units.");
cls_UnitsAPI.def_static("SetCurrentUnit_", (void (*)(const Standard_CString, const Standard_CString)) &UnitsAPI::SetCurrentUnit, "Sets the current unit dimension <aUnit> to the unit quantity <aQuantity>. Example: SetCurrentUnit('LENGTH','millimeter')", py::arg("aQuantity"), py::arg("aUnit"));
cls_UnitsAPI.def_static("CurrentUnit_", (Standard_CString (*)(const Standard_CString)) &UnitsAPI::CurrentUnit, "Returns the current unit dimension <aUnit> from the unit quantity <aQuantity>.", py::arg("aQuantity"));
cls_UnitsAPI.def_static("Save_", (void (*)()) &UnitsAPI::Save, "saves the units in the file .CurrentUnits of the directory pointed by the CSF_CurrentUnitsUserDefaults environment variable.");
cls_UnitsAPI.def_static("Reload_", (void (*)()) &UnitsAPI::Reload, "None");
cls_UnitsAPI.def_static("Dimensions_", (opencascade::handle<Units_Dimensions> (*)(const Standard_CString)) &UnitsAPI::Dimensions, "return the dimension associated to the quantity", py::arg("aQuantity"));
cls_UnitsAPI.def_static("DimensionLess_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionLess, "None");
cls_UnitsAPI.def_static("DimensionMass_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionMass, "None");
cls_UnitsAPI.def_static("DimensionLength_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionLength, "None");
cls_UnitsAPI.def_static("DimensionTime_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionTime, "None");
cls_UnitsAPI.def_static("DimensionElectricCurrent_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionElectricCurrent, "None");
cls_UnitsAPI.def_static("DimensionThermodynamicTemperature_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionThermodynamicTemperature, "None");
cls_UnitsAPI.def_static("DimensionAmountOfSubstance_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionAmountOfSubstance, "None");
cls_UnitsAPI.def_static("DimensionLuminousIntensity_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionLuminousIntensity, "None");
cls_UnitsAPI.def_static("DimensionPlaneAngle_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionPlaneAngle, "None");
cls_UnitsAPI.def_static("DimensionSolidAngle_", (opencascade::handle<Units_Dimensions> (*)()) &UnitsAPI::DimensionSolidAngle, "Returns the basic dimensions.");
cls_UnitsAPI.def_static("Check_", (Standard_Boolean (*)(const Standard_CString, const Standard_CString)) &UnitsAPI::Check, "Checks the coherence between the quantity <aQuantity> and the unit <aUnits> in the current system and returns FALSE when it's WRONG.", py::arg("aQuantity"), py::arg("aUnit"));

// Enums

}