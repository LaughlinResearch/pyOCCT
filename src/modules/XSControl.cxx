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
#include <XSControl_WorkSession.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <Interface_InterfaceModel.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <Standard_Transient.hxx>
#include <TopoDS_Shape.hxx>
#include <IFSelect_PrintCount.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TColStd_SequenceOfTransient.hxx>
#include <XSControl_Reader.hxx>
#include <XSControl_Controller.hxx>
#include <Interface_Protocol.hxx>
#include <IFSelect_WorkLibrary.hxx>
#include <Transfer_ActorOfTransientProcess.hxx>
#include <Transfer_ActorOfFinderProcess.hxx>
#include <Transfer_FinderProcess.hxx>
#include <NCollection_DataMap.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_Std.hxx>
#include <Standard_Type.hxx>
#include <NCollection_Vector.hxx>
#include <Interface_HArray1OfHAsciiString.hxx>
#include <Interface_CheckIterator.hxx>
#include <XSControl_TransferWriter.hxx>
#include <IFSelect_WorkSession.hxx>
#include <Message_Messenger.hxx>
#include <XSControl_TransferReader.hxx>
#include <Transfer_TransientProcess.hxx>
#include <XSControl_Vars.hxx>
#include <IFSelect_SelectExtract.hxx>
#include <XSControl_SelectForTransfer.hxx>
#include <IFSelect_SessionPilot.hxx>
#include <XSControl_SignTransferStatus.hxx>
#include <XSControl_ConnectedShapes.hxx>
#include <XSControl_Writer.hxx>
#include <XSControl_Functions.hxx>
#include <XSControl_FuncShape.hxx>
#include <XSControl_Utils.hxx>
#include <XSControl.hxx>
#include <IFSelect_SelectExplore.hxx>
#include <Interface_Graph.hxx>
#include <Interface_EntityIterator.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <IFSelect_Signature.hxx>
#include <Interface_HGraph.hxx>
#include <Transfer_ResultFromModel.hxx>
#include <Interface_CheckStatus.hxx>
#include <TColStd_DataMapOfIntegerTransient.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TCollection_HExtendedString.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TColStd_HSequenceOfHAsciiString.hxx>
#include <TColStd_HSequenceOfHExtendedString.hxx>
#include <TColStd_HSequenceOfInteger.hxx>
#include <Geom_Geometry.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

PYBIND11_MODULE(XSControl, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.IFSelect");
py::module::import("OCCT.Interface");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.TopTools");
py::module::import("OCCT.Transfer");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.TCollection");
py::module::import("OCCT.Message");
py::module::import("OCCT.TopAbs");
py::module::import("OCCT.Geom");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.gp");

// CLASS: XSCONTROL_READER
py::class_<XSControl_Reader> cls_XSControl_Reader(mod, "XSControl_Reader", "A groundwork to convert a shape to data which complies with a particular norm. This data can be that of a whole model or that of a specific list of entities in the model. You specify the list using a single selection or a combination of selections. A selection is an operator which computes a list of entities from a list given in input. To specify the input, you can use: - A predefined selection such as 'xst-transferrable-roots' - A filter based on a signature. A signature is an operator which returns a string from an entity according to its type. For example: - 'xst-type' (CDL) - 'iges-level' - 'step-type'. A filter can be based on a signature by giving a value to be matched by the string returned. For example, 'xst-type(Curve)'. If no list is specified, the selection computes its list of entities from the whole model. To use this class, you have to initialize the transfer norm first, as shown in the example below. Example: Control_Reader reader; IFSelect_ReturnStatus status = reader.ReadFile (filename.); When using IGESControl_Reader or STEPControl_Reader - as the above example shows - the reader initializes the norm directly. Note that loading the file only stores the data. It does not translate this data. Shapes are accumulated by successive transfers. The last shape is cleared by: - ClearShapes which allows you to handle a new batch - TransferRoots which restarts the list of shapes from scratch.");

// Constructors
cls_XSControl_Reader.def(py::init<>());
cls_XSControl_Reader.def(py::init<const Standard_CString>(), py::arg("norm"));
cls_XSControl_Reader.def(py::init<const opencascade::handle<XSControl_WorkSession> &>(), py::arg("WS"));
cls_XSControl_Reader.def(py::init<const opencascade::handle<XSControl_WorkSession> &, const Standard_Boolean>(), py::arg("WS"), py::arg("scratch"));

// Methods
// cls_XSControl_Reader.def_static("operator new_", (void * (*)(size_t)) &XSControl_Reader::operator new, "None", py::arg("theSize"));
// cls_XSControl_Reader.def_static("operator delete_", (void (*)(void *)) &XSControl_Reader::operator delete, "None", py::arg("theAddress"));
// cls_XSControl_Reader.def_static("operator new[]_", (void * (*)(size_t)) &XSControl_Reader::operator new[], "None", py::arg("theSize"));
// cls_XSControl_Reader.def_static("operator delete[]_", (void (*)(void *)) &XSControl_Reader::operator delete[], "None", py::arg("theAddress"));
// cls_XSControl_Reader.def_static("operator new_", (void * (*)(size_t, void *)) &XSControl_Reader::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XSControl_Reader.def_static("operator delete_", (void (*)(void *, void *)) &XSControl_Reader::operator delete, "None", py::arg(""), py::arg(""));
cls_XSControl_Reader.def("SetNorm", (Standard_Boolean (XSControl_Reader::*)(const Standard_CString)) &XSControl_Reader::SetNorm, "Sets a specific norm to <me> Returns True if done, False if <norm> is not available", py::arg("norm"));
cls_XSControl_Reader.def("SetWS", [](XSControl_Reader &self, const opencascade::handle<XSControl_WorkSession> & a0) -> void { return self.SetWS(a0); });
cls_XSControl_Reader.def("SetWS", (void (XSControl_Reader::*)(const opencascade::handle<XSControl_WorkSession> &, const Standard_Boolean)) &XSControl_Reader::SetWS, "Sets a specific session to <me>", py::arg("WS"), py::arg("scratch"));
cls_XSControl_Reader.def("WS", (opencascade::handle<XSControl_WorkSession> (XSControl_Reader::*)() const) &XSControl_Reader::WS, "Returns the session used in <me>");
cls_XSControl_Reader.def("ReadFile", (IFSelect_ReturnStatus (XSControl_Reader::*)(const Standard_CString)) &XSControl_Reader::ReadFile, "Loads a file and returns the read status Zero for a Model which compies with the Controller", py::arg("filename"));
cls_XSControl_Reader.def("Model", (opencascade::handle<Interface_InterfaceModel> (XSControl_Reader::*)() const) &XSControl_Reader::Model, "Returns the model. It can then be consulted (header, product)");
cls_XSControl_Reader.def("GiveList", [](XSControl_Reader &self) -> opencascade::handle<TColStd_HSequenceOfTransient> { return self.GiveList(); });
cls_XSControl_Reader.def("GiveList", [](XSControl_Reader &self, const Standard_CString a0) -> opencascade::handle<TColStd_HSequenceOfTransient> { return self.GiveList(a0); });
cls_XSControl_Reader.def("GiveList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_Reader::*)(const Standard_CString, const Standard_CString)) &XSControl_Reader::GiveList, "Returns a list of entities from the IGES or STEP file according to the following rules: - if first and second are empty strings, the whole file is selected. - if first is an entity number or label, the entity referred to is selected. - if first is a list of entity numbers/labels separated by commas, the entities referred to are selected, - if first is the name of a selection in the worksession and second is not defined, the list contains the standard output for that selection. - if first is the name of a selection and second is defined, the criterion defined by second is applied to the result of the first selection. A selection is an operator which computes a list of entities from a list given in input according to its type. If no list is specified, the selection computes its list of entities from the whole model. A selection can be: - A predefined selection (xst-transferrable-mode) - A filter based on a signature A Signature is an operator which returns a string from an entity according to its type. For example: - 'xst-type' (CDL) - 'iges-level' - 'step-type'. For example, if you wanted to select only the advanced_faces in a STEP file you would use the following code: Example Reader.GiveList('xst-transferrable-roots','step-type(ADVANCED_FACE)'); Warning If the value given to second is incorrect, it will simply be ignored.", py::arg("first"), py::arg("second"));
cls_XSControl_Reader.def("GiveList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_Reader::*)(const Standard_CString, const opencascade::handle<Standard_Transient> &)) &XSControl_Reader::GiveList, "Computes a List of entities from the model as follows <first> beeing a Selection, <ent> beeing an entity or a list of entities (as a HSequenceOfTransient) : the standard result of this selection applied to this list if <first> is erroneous, a null handle is returned", py::arg("first"), py::arg("ent"));
cls_XSControl_Reader.def("NbRootsForTransfer", (Standard_Integer (XSControl_Reader::*)()) &XSControl_Reader::NbRootsForTransfer, "Determines the list of root entities which are candidate for a transfer to a Shape, and returns the number of entities in the list");
cls_XSControl_Reader.def("RootForTransfer", [](XSControl_Reader &self) -> opencascade::handle<Standard_Transient> { return self.RootForTransfer(); });
cls_XSControl_Reader.def("RootForTransfer", (opencascade::handle<Standard_Transient> (XSControl_Reader::*)(const Standard_Integer)) &XSControl_Reader::RootForTransfer, "Returns an IGES or STEP root entity for translation. The entity is identified by its rank in a list.", py::arg("num"));
cls_XSControl_Reader.def("TransferOneRoot", [](XSControl_Reader &self) -> Standard_Boolean { return self.TransferOneRoot(); });
cls_XSControl_Reader.def("TransferOneRoot", (Standard_Boolean (XSControl_Reader::*)(const Standard_Integer)) &XSControl_Reader::TransferOneRoot, "Translates a root identified by the rank num in the model. false is returned if no shape is produced.", py::arg("num"));
cls_XSControl_Reader.def("TransferOne", (Standard_Boolean (XSControl_Reader::*)(const Standard_Integer)) &XSControl_Reader::TransferOne, "Translates an IGES or STEP entity identified by the rank num in the model. false is returned if no shape is produced.", py::arg("num"));
cls_XSControl_Reader.def("TransferEntity", (Standard_Boolean (XSControl_Reader::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_Reader::TransferEntity, "Translates an IGES or STEP entity in the model. true is returned if a shape is produced; otherwise, false is returned.", py::arg("start"));
cls_XSControl_Reader.def("TransferList", (Standard_Integer (XSControl_Reader::*)(const opencascade::handle<TColStd_HSequenceOfTransient> &)) &XSControl_Reader::TransferList, "Translates a list of entities. Returns the number of IGES or STEP entities that were successfully translated. The list can be produced with GiveList. Warning - This function does not clear the existing output shapes.", py::arg("list"));
cls_XSControl_Reader.def("TransferRoots", (Standard_Integer (XSControl_Reader::*)()) &XSControl_Reader::TransferRoots, "Translates all translatable roots and returns the number of successful translations. Warning - This function clears existing output shapes first.");
cls_XSControl_Reader.def("ClearShapes", (void (XSControl_Reader::*)()) &XSControl_Reader::ClearShapes, "Clears the list of shapes that may have accumulated in calls to TransferOne or TransferRoot.C");
cls_XSControl_Reader.def("NbShapes", (Standard_Integer (XSControl_Reader::*)() const) &XSControl_Reader::NbShapes, "Returns the number of shapes produced by translation.");
cls_XSControl_Reader.def("Shape", [](XSControl_Reader &self) -> TopoDS_Shape { return self.Shape(); });
cls_XSControl_Reader.def("Shape", (TopoDS_Shape (XSControl_Reader::*)(const Standard_Integer) const) &XSControl_Reader::Shape, "Returns the shape resulting from a translation and identified by the rank num. num equals 1 by default. In other words, the first shape resulting from the translation is returned.", py::arg("num"));
cls_XSControl_Reader.def("OneShape", (TopoDS_Shape (XSControl_Reader::*)() const) &XSControl_Reader::OneShape, "Returns all of the results in a single shape which is: - a null shape if there are no results, - a shape if there is one result, - a compound containing the resulting shapes if there are more than one.");
cls_XSControl_Reader.def("PrintCheckLoad", (void (XSControl_Reader::*)(const Standard_Boolean, const IFSelect_PrintCount) const) &XSControl_Reader::PrintCheckLoad, "Prints the check list attached to loaded data, on the Standard Trace File (starts at std::cout) All messages or fails only, according to <failsonly> mode = 0 : per entity, prints messages mode = 1 : per message, just gives count of entities per check mode = 2 : also gives entity numbers", py::arg("failsonly"), py::arg("mode"));
cls_XSControl_Reader.def("PrintCheckTransfer", (void (XSControl_Reader::*)(const Standard_Boolean, const IFSelect_PrintCount) const) &XSControl_Reader::PrintCheckTransfer, "Displays check results for the last translation of IGES or STEP entities to Open CASCADE entities. Only fail messages are displayed if failsonly is true. All messages are displayed if failsonly is false. mode determines the contents and the order of the messages according to the terms of the IFSelect_PrintCount enumeration.", py::arg("failsonly"), py::arg("mode"));
cls_XSControl_Reader.def("PrintStatsTransfer", [](XSControl_Reader &self, const Standard_Integer a0) -> void { return self.PrintStatsTransfer(a0); });
cls_XSControl_Reader.def("PrintStatsTransfer", (void (XSControl_Reader::*)(const Standard_Integer, const Standard_Integer) const) &XSControl_Reader::PrintStatsTransfer, "Displays the statistics for the last translation. what defines the kind of statistics that are displayed as follows: - 0 gives general statistics (number of translated roots, number of warnings, number of fail messages), - 1 gives root results, - 2 gives statistics for all checked entities, - 3 gives the list of translated entities, - 4 gives warning and fail messages, - 5 gives fail messages only. The use of mode depends on the value of what. If what is 0, mode is ignored. If what is 1, 2 or 3, mode defines the following: - 0 lists the numbers of IGES or STEP entities in the respective model - 1 gives the number, identifier, type and result type for each IGES or STEP entity and/or its status (fail, warning, etc.) - 2 gives maximum information for each IGES or STEP entity (i.e. checks) - 3 gives the number of entities per type of IGES or STEP entity - 4 gives the number of IGES or STEP entities per result type and/or status - 5 gives the number of pairs (IGES or STEP or result type and status) - 6 gives the number of pairs (IGES or STEP or result type and status) AND the list of entity numbers in the IGES or STEP model. If what is 4 or 5, mode defines the warning and fail messages as follows: - if mode is 0 all warnings and checks per entity are returned - if mode is 2 the list of entities per warning is returned. If mode is not set, only the list of all entities per warning is given.", py::arg("what"), py::arg("mode"));
cls_XSControl_Reader.def("GetStatsTransfer", [](XSControl_Reader &self, const opencascade::handle<TColStd_HSequenceOfTransient> & list, Standard_Integer & nbMapped, Standard_Integer & nbWithResult, Standard_Integer & nbWithFail){ self.GetStatsTransfer(list, nbMapped, nbWithResult, nbWithFail); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &>(nbMapped, nbWithResult, nbWithFail); }, "Gives statistics about Transfer", py::arg("list"), py::arg("nbMapped"), py::arg("nbWithResult"), py::arg("nbWithFail"));

// CLASS: XSCONTROL_CONTROLLER
py::class_<XSControl_Controller, opencascade::handle<XSControl_Controller>, Standard_Transient> cls_XSControl_Controller(mod, "XSControl_Controller", "This class allows a general X-STEP engine to run generic functions on any interface norm, in the same way. It includes the transfer operations. I.e. it gathers the already available general modules, the engine has just to know it");

// Methods
cls_XSControl_Controller.def("SetNames", (void (XSControl_Controller::*)(const Standard_CString, const Standard_CString)) &XSControl_Controller::SetNames, "Changes names if a name is empty, the formerly set one remains Remark : Does not call Record or AutoRecord", py::arg("theLongName"), py::arg("theShortName"));
cls_XSControl_Controller.def("AutoRecord", (void (XSControl_Controller::*)() const) &XSControl_Controller::AutoRecord, "Records <me> is a general dictionary under Short and Long Names (see method Name)");
cls_XSControl_Controller.def("Record", (void (XSControl_Controller::*)(const Standard_CString) const) &XSControl_Controller::Record, "Records <me> in a general dictionary under a name Error if <name> already used for another one", py::arg("name"));
cls_XSControl_Controller.def_static("Recorded_", (opencascade::handle<XSControl_Controller> (*)(const Standard_CString)) &XSControl_Controller::Recorded, "Returns the Controller attached to a given name Returns a Null Handle if <name> is unknown", py::arg("name"));
cls_XSControl_Controller.def("Name", [](XSControl_Controller &self) -> Standard_CString { return self.Name(); });
cls_XSControl_Controller.def("Name", (Standard_CString (XSControl_Controller::*)(const Standard_Boolean) const) &XSControl_Controller::Name, "Returns a name, as given when initializing : rsc = False (D) : True Name attached to the Norm (long name) rsc = True : Name of the ressource set (i.e. short name)", py::arg("rsc"));
cls_XSControl_Controller.def("Protocol", (const opencascade::handle<Interface_Protocol> & (XSControl_Controller::*)() const) &XSControl_Controller::Protocol, "Returns the Protocol attached to the Norm (from field)");
cls_XSControl_Controller.def("WorkLibrary", (const opencascade::handle<IFSelect_WorkLibrary> & (XSControl_Controller::*)() const) &XSControl_Controller::WorkLibrary, "Returns the WorkLibrary attached to the Norm. Remark that it has to be in phase with the Protocol (read from field)");
cls_XSControl_Controller.def("NewModel", (opencascade::handle<Interface_InterfaceModel> (XSControl_Controller::*)() const) &XSControl_Controller::NewModel, "Creates a new empty Model ready to receive data of the Norm Used to write data from Imagine to an interface file");
cls_XSControl_Controller.def("ActorRead", (opencascade::handle<Transfer_ActorOfTransientProcess> (XSControl_Controller::*)(const opencascade::handle<Interface_InterfaceModel> &) const) &XSControl_Controller::ActorRead, "Returns the Actor for Read attached to the pair (norm,appli) It can be adapted for data of the input Model, as required Can be read from field then adapted with Model as required", py::arg("model"));
cls_XSControl_Controller.def("ActorWrite", (opencascade::handle<Transfer_ActorOfFinderProcess> (XSControl_Controller::*)() const) &XSControl_Controller::ActorWrite, "Returns the Actor for Write attached to the pair (norm,appli) Read from field. Can be redefined");
cls_XSControl_Controller.def("SetModeWrite", [](XSControl_Controller &self, const Standard_Integer a0, const Standard_Integer a1) -> void { return self.SetModeWrite(a0, a1); });
cls_XSControl_Controller.def("SetModeWrite", (void (XSControl_Controller::*)(const Standard_Integer, const Standard_Integer, const Standard_Boolean)) &XSControl_Controller::SetModeWrite, "Sets mininum and maximum values for modetrans (write) Erases formerly recorded bounds and values Actually only for shape Then, for each value a little help can be attached", py::arg("modemin"), py::arg("modemax"), py::arg("shape"));
cls_XSControl_Controller.def("SetModeWriteHelp", [](XSControl_Controller &self, const Standard_Integer a0, const Standard_CString a1) -> void { return self.SetModeWriteHelp(a0, a1); });
cls_XSControl_Controller.def("SetModeWriteHelp", (void (XSControl_Controller::*)(const Standard_Integer, const Standard_CString, const Standard_Boolean)) &XSControl_Controller::SetModeWriteHelp, "Attaches a short line of help to a value of modetrans (write)", py::arg("modetrans"), py::arg("help"), py::arg("shape"));
cls_XSControl_Controller.def("ModeWriteBounds", [](XSControl_Controller &self, Standard_Integer & modemin, Standard_Integer & modemax, const Standard_Boolean shape){ Standard_Boolean rv = self.ModeWriteBounds(modemin, modemax, shape); return std::tuple<Standard_Boolean, Standard_Integer &, Standard_Integer &>(rv, modemin, modemax); }, "Returns recorded min and max values for modetrans (write) Actually only for shapes Returns True if bounds are set, False else (then, free value)", py::arg("modemin"), py::arg("modemax"), py::arg("shape"));
cls_XSControl_Controller.def("IsModeWrite", [](XSControl_Controller &self, const Standard_Integer a0) -> Standard_Boolean { return self.IsModeWrite(a0); });
cls_XSControl_Controller.def("IsModeWrite", (Standard_Boolean (XSControl_Controller::*)(const Standard_Integer, const Standard_Boolean) const) &XSControl_Controller::IsModeWrite, "Tells if a value of <modetrans> is a good value(within bounds) Actually only for shapes", py::arg("modetrans"), py::arg("shape"));
cls_XSControl_Controller.def("ModeWriteHelp", [](XSControl_Controller &self, const Standard_Integer a0) -> Standard_CString { return self.ModeWriteHelp(a0); });
cls_XSControl_Controller.def("ModeWriteHelp", (Standard_CString (XSControl_Controller::*)(const Standard_Integer, const Standard_Boolean) const) &XSControl_Controller::ModeWriteHelp, "Returns the help line recorded for a value of modetrans empty if help not defined or not within bounds or if values are free", py::arg("modetrans"), py::arg("shape"));
cls_XSControl_Controller.def("RecognizeWriteTransient", [](XSControl_Controller &self, const opencascade::handle<Standard_Transient> & a0) -> Standard_Boolean { return self.RecognizeWriteTransient(a0); });
cls_XSControl_Controller.def("RecognizeWriteTransient", (Standard_Boolean (XSControl_Controller::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_Controller::RecognizeWriteTransient, "Tells if <obj> (an application object) is a valid candidate for a transfer to a Model. By default, asks the ActorWrite if known (through a TransientMapper). Can be redefined", py::arg("obj"), py::arg("modetrans"));
cls_XSControl_Controller.def("TransferWriteTransient", [](XSControl_Controller &self, const opencascade::handle<Standard_Transient> & a0, const opencascade::handle<Transfer_FinderProcess> & a1, const opencascade::handle<Interface_InterfaceModel> & a2) -> IFSelect_ReturnStatus { return self.TransferWriteTransient(a0, a1, a2); });
cls_XSControl_Controller.def("TransferWriteTransient", (IFSelect_ReturnStatus (XSControl_Controller::*)(const opencascade::handle<Standard_Transient> &, const opencascade::handle<Transfer_FinderProcess> &, const opencascade::handle<Interface_InterfaceModel> &, const Standard_Integer) const) &XSControl_Controller::TransferWriteTransient, "Takes one Transient Object and transfers it to an InterfaceModel (already created, e.g. by NewModel) (result is recorded in the model by AddWithRefs) FP records produced results and checks", py::arg("obj"), py::arg("FP"), py::arg("model"), py::arg("modetrans"));
cls_XSControl_Controller.def("RecognizeWriteShape", [](XSControl_Controller &self, const TopoDS_Shape & a0) -> Standard_Boolean { return self.RecognizeWriteShape(a0); });
cls_XSControl_Controller.def("RecognizeWriteShape", (Standard_Boolean (XSControl_Controller::*)(const TopoDS_Shape &, const Standard_Integer) const) &XSControl_Controller::RecognizeWriteShape, "Tells if a shape is valid for a transfer to a model Asks the ActorWrite (through a ShapeMapper)", py::arg("shape"), py::arg("modetrans"));
cls_XSControl_Controller.def("TransferWriteShape", [](XSControl_Controller &self, const TopoDS_Shape & a0, const opencascade::handle<Transfer_FinderProcess> & a1, const opencascade::handle<Interface_InterfaceModel> & a2) -> IFSelect_ReturnStatus { return self.TransferWriteShape(a0, a1, a2); });
cls_XSControl_Controller.def("TransferWriteShape", (IFSelect_ReturnStatus (XSControl_Controller::*)(const TopoDS_Shape &, const opencascade::handle<Transfer_FinderProcess> &, const opencascade::handle<Interface_InterfaceModel> &, const Standard_Integer) const) &XSControl_Controller::TransferWriteShape, "Takes one Shape and transfers it to an InterfaceModel (already created, e.g. by NewModel) Default uses ActorWrite; can be redefined as necessary Returned value is a status, as follows : Done OK , Void : No Result , Fail : Fail (e.g. exception) Error : bad conditions , bad model or null model", py::arg("shape"), py::arg("FP"), py::arg("model"), py::arg("modetrans"));
cls_XSControl_Controller.def("AddSessionItem", [](XSControl_Controller &self, const opencascade::handle<Standard_Transient> & a0, const Standard_CString a1) -> void { return self.AddSessionItem(a0, a1); });
cls_XSControl_Controller.def("AddSessionItem", (void (XSControl_Controller::*)(const opencascade::handle<Standard_Transient> &, const Standard_CString, const Standard_Boolean)) &XSControl_Controller::AddSessionItem, "Records a Session Item, to be added for customisation of the Work Session. It must have a specific name. <setapplied> is used if <item> is a GeneralModifier, to decide If set to true, <item> will be applied to the hook list 'send'. Else, it is not applied to any hook list. Remark : this method is to be called at Create time, the recorded items will be used by Customise Warning : if <name> conflicts, the last recorded item is kept", py::arg("theItem"), py::arg("theName"), py::arg("toApply"));
cls_XSControl_Controller.def("SessionItem", (opencascade::handle<Standard_Transient> (XSControl_Controller::*)(const Standard_CString) const) &XSControl_Controller::SessionItem, "Returns an item given its name to record in a Session If <name> is unknown, returns a Null Handle", py::arg("theName"));
cls_XSControl_Controller.def("Customise", (void (XSControl_Controller::*)(opencascade::handle<XSControl_WorkSession> &)) &XSControl_Controller::Customise, "Customises a WorkSession, by adding to it the recorded items (by AddSessionItem)", py::arg("WS"));
cls_XSControl_Controller.def("AdaptorSession", (const NCollection_DataMap<TCollection_AsciiString, opencascade::handle<Standard_Transient> > & (XSControl_Controller::*)() const) &XSControl_Controller::AdaptorSession, "None");
cls_XSControl_Controller.def_static("get_type_name_", (const char * (*)()) &XSControl_Controller::get_type_name, "None");
cls_XSControl_Controller.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_Controller::get_type_descriptor, "None");
cls_XSControl_Controller.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_Controller::*)() const) &XSControl_Controller::DynamicType, "None");

// CLASS: XSCONTROL_TRANSFERWRITER
py::class_<XSControl_TransferWriter, opencascade::handle<XSControl_TransferWriter>, Standard_Transient> cls_XSControl_TransferWriter(mod, "XSControl_TransferWriter", "TransferWriter gives help to control transfer to write a file after having converted data from Cascade/Imagine");

// Constructors
cls_XSControl_TransferWriter.def(py::init<>());

// Methods
cls_XSControl_TransferWriter.def("FinderProcess", (const opencascade::handle<Transfer_FinderProcess> & (XSControl_TransferWriter::*)() const) &XSControl_TransferWriter::FinderProcess, "Returns the FinderProcess itself");
cls_XSControl_TransferWriter.def("SetFinderProcess", (void (XSControl_TransferWriter::*)(const opencascade::handle<Transfer_FinderProcess> &)) &XSControl_TransferWriter::SetFinderProcess, "Sets a new FinderProcess and forgets the former one", py::arg("theFP"));
cls_XSControl_TransferWriter.def("Controller", (const opencascade::handle<XSControl_Controller> & (XSControl_TransferWriter::*)() const) &XSControl_TransferWriter::Controller, "Returns the currently used Controller");
cls_XSControl_TransferWriter.def("SetController", (void (XSControl_TransferWriter::*)(const opencascade::handle<XSControl_Controller> &)) &XSControl_TransferWriter::SetController, "Sets a new Controller, also sets a new FinderProcess", py::arg("theCtl"));
cls_XSControl_TransferWriter.def("Clear", (void (XSControl_TransferWriter::*)(const Standard_Integer)) &XSControl_TransferWriter::Clear, "Clears recorded data according a mode 0 clears FinderProcess (results, checks) -1 create a new FinderProcess", py::arg("theMode"));
cls_XSControl_TransferWriter.def("TransferMode", (Standard_Integer (XSControl_TransferWriter::*)() const) &XSControl_TransferWriter::TransferMode, "Returns the current Transfer Mode (an Integer) It will be interpreted by the Controller to run Transfers This call form could be later replaced by more specific ones (parameters suited for each norm / transfer case)");
cls_XSControl_TransferWriter.def("SetTransferMode", (void (XSControl_TransferWriter::*)(const Standard_Integer)) &XSControl_TransferWriter::SetTransferMode, "Changes the Transfer Mode", py::arg("theMode"));
cls_XSControl_TransferWriter.def("PrintStats", [](XSControl_TransferWriter &self, const Standard_Integer a0) -> void { return self.PrintStats(a0); });
cls_XSControl_TransferWriter.def("PrintStats", (void (XSControl_TransferWriter::*)(const Standard_Integer, const Standard_Integer) const) &XSControl_TransferWriter::PrintStats, "Prints statistics on current Trace File, according what,mode See PrintStatsProcess for details", py::arg("theWhat"), py::arg("theMode"));
cls_XSControl_TransferWriter.def("RecognizeTransient", (Standard_Boolean (XSControl_TransferWriter::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_TransferWriter::RecognizeTransient, "Tells if a transient object (from an application) is a valid candidate for a transfer to a model Asks the Controller (RecognizeWriteTransient) If <obj> is a HShape, calls RecognizeShape", py::arg("theObj"));
cls_XSControl_TransferWriter.def("TransferWriteTransient", (IFSelect_ReturnStatus (XSControl_TransferWriter::*)(const opencascade::handle<Interface_InterfaceModel> &, const opencascade::handle<Standard_Transient> &)) &XSControl_TransferWriter::TransferWriteTransient, "Transfers a Transient object (from an application) to a model of current norm, according to the last call to SetTransferMode Works by calling the Controller Returns status : =0 if OK, >0 if error during transfer, <0 if transfer badly initialised", py::arg("theModel"), py::arg("theObj"));
cls_XSControl_TransferWriter.def("RecognizeShape", (Standard_Boolean (XSControl_TransferWriter::*)(const TopoDS_Shape &)) &XSControl_TransferWriter::RecognizeShape, "Tells if a Shape is valid for a transfer to a model Asks the Controller (RecognizeWriteShape)", py::arg("theShape"));
cls_XSControl_TransferWriter.def("TransferWriteShape", (IFSelect_ReturnStatus (XSControl_TransferWriter::*)(const opencascade::handle<Interface_InterfaceModel> &, const TopoDS_Shape &)) &XSControl_TransferWriter::TransferWriteShape, "Transfers a Shape from CasCade to a model of current norm, according to the last call to SetTransferMode Works by calling the Controller Returns status : =0 if OK, >0 if error during transfer, <0 if transfer badly initialised", py::arg("theModel"), py::arg("theShape"));
cls_XSControl_TransferWriter.def("CheckList", (Interface_CheckIterator (XSControl_TransferWriter::*)() const) &XSControl_TransferWriter::CheckList, "Returns the check-list of last transfer (write), i.e. the check-list currently recorded in the FinderProcess");
cls_XSControl_TransferWriter.def("ResultCheckList", (Interface_CheckIterator (XSControl_TransferWriter::*)(const opencascade::handle<Interface_InterfaceModel> &) const) &XSControl_TransferWriter::ResultCheckList, "Returns the check-list of last transfer (write), but tries to bind to each check, the resulting entity in the model instead of keeping the original Mapper, whenever known", py::arg("theModel"));
cls_XSControl_TransferWriter.def_static("get_type_name_", (const char * (*)()) &XSControl_TransferWriter::get_type_name, "None");
cls_XSControl_TransferWriter.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_TransferWriter::get_type_descriptor, "None");
cls_XSControl_TransferWriter.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_TransferWriter::*)() const) &XSControl_TransferWriter::DynamicType, "None");

// CLASS: XSCONTROL_WORKSESSION
py::class_<XSControl_WorkSession, opencascade::handle<XSControl_WorkSession>, IFSelect_WorkSession> cls_XSControl_WorkSession(mod, "XSControl_WorkSession", "This WorkSession completes the basic one, by adding : - use of Controller, with norm selection... - management of transfers (both ways) with auxiliary classes TransferReader and TransferWriter -> these transfers may work with a Context List : its items are given by the user, according to the transfer to be i.e. it is interpreted by the Actors Each item is accessed by a Name");

// Constructors
cls_XSControl_WorkSession.def(py::init<>());

// Methods
cls_XSControl_WorkSession.def("ClearData", (void (XSControl_WorkSession::*)(const Standard_Integer)) &XSControl_WorkSession::ClearData, "In addition to basic ClearData, clears Transfer and Management for interactive use, for mode = 0,1,2 and over 4 Plus : mode = 5 to clear Transfers (both ways) only mode = 6 to clear enforced results mode = 7 to clear transfers, results", py::arg("theMode"));
cls_XSControl_WorkSession.def("SelectNorm", (Standard_Boolean (XSControl_WorkSession::*)(const Standard_CString)) &XSControl_WorkSession::SelectNorm, "Selects a Norm defined by its name. A Norm is described and handled by a Controller Returns True if done, False if <normname> is unknown", py::arg("theNormName"));
cls_XSControl_WorkSession.def("SetController", (void (XSControl_WorkSession::*)(const opencascade::handle<XSControl_Controller> &)) &XSControl_WorkSession::SetController, "Selects a Norm defined by its Controller itself", py::arg("theCtl"));
cls_XSControl_WorkSession.def("SelectedNorm", [](XSControl_WorkSession &self) -> Standard_CString { return self.SelectedNorm(); });
cls_XSControl_WorkSession.def("SelectedNorm", (Standard_CString (XSControl_WorkSession::*)(const Standard_Boolean) const) &XSControl_WorkSession::SelectedNorm, "Returns the name of the last Selected Norm. If none is defined, returns an empty string By default, returns the complete name of the norm If <rsc> is True, returns the short name used for resource", py::arg("theRsc"));
cls_XSControl_WorkSession.def("NormAdaptor", (const opencascade::handle<XSControl_Controller> & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::NormAdaptor, "Returns the norm controller itself");
cls_XSControl_WorkSession.def("Context", (const NCollection_DataMap<TCollection_AsciiString, opencascade::handle<Standard_Transient> > & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::Context, "Returns the current Context List, Null if not defined The Context is given to the TransientProcess for TransferRead");
cls_XSControl_WorkSession.def("SetAllContext", (void (XSControl_WorkSession::*)(const NCollection_DataMap<TCollection_AsciiString, opencascade::handle<Standard_Transient> > &)) &XSControl_WorkSession::SetAllContext, "Sets the current Context List, as a whole Sets it to the TransferReader", py::arg("theContext"));
cls_XSControl_WorkSession.def("ClearContext", (void (XSControl_WorkSession::*)()) &XSControl_WorkSession::ClearContext, "Clears the whole current Context (nullifies it)");
cls_XSControl_WorkSession.def("PrintTransferStatus", (Standard_Boolean (XSControl_WorkSession::*)(const Standard_Integer, const Standard_Boolean, const opencascade::handle<Message_Messenger> &) const) &XSControl_WorkSession::PrintTransferStatus, "Prints the transfer status of a transferred item, as beeing the Mapped n0 <num>, from MapWriter if <wri> is True, or from MapReader if <wri> is False Returns True when done, False else (i.e. num out of range)", py::arg("theNum"), py::arg("theWri"), py::arg("theS"));
cls_XSControl_WorkSession.def("InitTransferReader", (void (XSControl_WorkSession::*)(const Standard_Integer)) &XSControl_WorkSession::InitTransferReader, "Sets a Transfer Reader, by internal ways, according mode : 0 recreates it clear, 1 clears it (does not recreate) 2 aligns Roots of TransientProcess from final Results 3 aligns final Results from Roots of TransientProcess 4 begins a new transfer (by BeginTransfer) 5 recreates TransferReader then begins a new transfer", py::arg("theMode"));
cls_XSControl_WorkSession.def("SetTransferReader", (void (XSControl_WorkSession::*)(const opencascade::handle<XSControl_TransferReader> &)) &XSControl_WorkSession::SetTransferReader, "Sets a Transfer Reader, which manages transfers on reading", py::arg("theTR"));
cls_XSControl_WorkSession.def("TransferReader", (const opencascade::handle<XSControl_TransferReader> & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::TransferReader, "Returns the Transfer Reader, Null if not set");
cls_XSControl_WorkSession.def("MapReader", (opencascade::handle<Transfer_TransientProcess> (XSControl_WorkSession::*)() const) &XSControl_WorkSession::MapReader, "Returns the TransientProcess(internal data for TransferReader)");
cls_XSControl_WorkSession.def("SetMapReader", (Standard_Boolean (XSControl_WorkSession::*)(const opencascade::handle<Transfer_TransientProcess> &)) &XSControl_WorkSession::SetMapReader, "Changes the Map Reader, i.e. considers that the new one defines the relevant read results (forgets the former ones) Returns True when done, False in case of bad definition, i.e. if Model from TP differs from that of Session", py::arg("theTP"));
cls_XSControl_WorkSession.def("Result", (opencascade::handle<Standard_Transient> (XSControl_WorkSession::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_WorkSession::Result, "Returns the result attached to a starting entity If <mode> = 0, returns Final Result If <mode> = 1, considers Last Result If <mode> = 2, considers Final, else if absent, Last returns it as Transient, if result is not transient returns the Binder <mode> = 10,11,12 idem but returns the Binder itself (if it is not, e.g. Shape, returns the Binder) <mode> = 20, returns the ResultFromModel", py::arg("theEnt"), py::arg("theMode"));
cls_XSControl_WorkSession.def("TransferReadOne", (Standard_Integer (XSControl_WorkSession::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_WorkSession::TransferReadOne, "Commands the transfer of, either one entity, or a list I.E. calls the TransferReader after having analysed <ents> It is cumulated from the last BeginTransfer <ents> is processed by GiveList, hence : - <ents> a Selection : its SelectionResult - <ents> a HSequenceOfTransient : this list - <ents> the Model : in this specific case, all the roots, with no cumulation of former transfers (TransferReadRoots)", py::arg("theEnts"));
cls_XSControl_WorkSession.def("TransferReadRoots", (Standard_Integer (XSControl_WorkSession::*)()) &XSControl_WorkSession::TransferReadRoots, "Commands the transfer of all the root entities of the model i.e. calls TransferRoot from the TransferReader with the Graph No cumulation with former calls to TransferReadOne");
cls_XSControl_WorkSession.def("NewModel", (opencascade::handle<Interface_InterfaceModel> (XSControl_WorkSession::*)()) &XSControl_WorkSession::NewModel, "produces and returns a new Model well conditionned It is produced by the Norm Controller It can be Null (if this function is not implemented)");
cls_XSControl_WorkSession.def("TransferWriter", (const opencascade::handle<XSControl_TransferWriter> & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::TransferWriter, "Returns the Transfer Reader, Null if not set");
cls_XSControl_WorkSession.def("SetMapWriter", (Standard_Boolean (XSControl_WorkSession::*)(const opencascade::handle<Transfer_FinderProcess> &)) &XSControl_WorkSession::SetMapWriter, "Changes the Map Reader, i.e. considers that the new one defines the relevant read results (forgets the former ones) Returns True when done, False if <FP> is Null", py::arg("theFP"));
cls_XSControl_WorkSession.def("TransferWriteShape", [](XSControl_WorkSession &self, const TopoDS_Shape & a0) -> IFSelect_ReturnStatus { return self.TransferWriteShape(a0); });
cls_XSControl_WorkSession.def("TransferWriteShape", (IFSelect_ReturnStatus (XSControl_WorkSession::*)(const TopoDS_Shape &, const Standard_Boolean)) &XSControl_WorkSession::TransferWriteShape, "Transfers a Shape from CasCade to a model of current norm, according to the last call to SetModeWriteShape Returns status :Done if OK, Fail if error during transfer, Error if transfer badly initialised", py::arg("theShape"), py::arg("theCompGraph"));
cls_XSControl_WorkSession.def("TransferWriteCheckList", (Interface_CheckIterator (XSControl_WorkSession::*)() const) &XSControl_WorkSession::TransferWriteCheckList, "Returns the check-list of last transfer (write) It is recorded in the FinderProcess, but it must be bound with resulting entities (in the resulting file model) rather than with original objects (in fact, their mappers)");
cls_XSControl_WorkSession.def("Vars", (const opencascade::handle<XSControl_Vars> & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::Vars, "None");
cls_XSControl_WorkSession.def("SetVars", (void (XSControl_WorkSession::*)(const opencascade::handle<XSControl_Vars> &)) &XSControl_WorkSession::SetVars, "None", py::arg("theVars"));
cls_XSControl_WorkSession.def_static("get_type_name_", (const char * (*)()) &XSControl_WorkSession::get_type_name, "None");
cls_XSControl_WorkSession.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_WorkSession::get_type_descriptor, "None");
cls_XSControl_WorkSession.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_WorkSession::*)() const) &XSControl_WorkSession::DynamicType, "None");

// CLASS: XSCONTROL_SELECTFORTRANSFER
py::class_<XSControl_SelectForTransfer, opencascade::handle<XSControl_SelectForTransfer>, IFSelect_SelectExtract> cls_XSControl_SelectForTransfer(mod, "XSControl_SelectForTransfer", "This selection selects the entities which are recognised for transfer by an Actor for Read : current one or another one.");

// Constructors
cls_XSControl_SelectForTransfer.def(py::init<>());
cls_XSControl_SelectForTransfer.def(py::init<const opencascade::handle<XSControl_TransferReader> &>(), py::arg("TR"));

// Methods
cls_XSControl_SelectForTransfer.def("SetReader", (void (XSControl_SelectForTransfer::*)(const opencascade::handle<XSControl_TransferReader> &)) &XSControl_SelectForTransfer::SetReader, "Sets a TransferReader to sort entities : it brings the Actor, which may change, while the TransferReader does not", py::arg("TR"));
cls_XSControl_SelectForTransfer.def("SetActor", (void (XSControl_SelectForTransfer::*)(const opencascade::handle<Transfer_ActorOfTransientProcess> &)) &XSControl_SelectForTransfer::SetActor, "Sets a precise actor to sort entities This definition oversedes the creation with a TransferReader", py::arg("act"));
cls_XSControl_SelectForTransfer.def("Actor", (opencascade::handle<Transfer_ActorOfTransientProcess> (XSControl_SelectForTransfer::*)() const) &XSControl_SelectForTransfer::Actor, "Returns the Actor used as precised one. Returns a Null Handle for a creation from a TransferReader without any further setting");
cls_XSControl_SelectForTransfer.def("Reader", (opencascade::handle<XSControl_TransferReader> (XSControl_SelectForTransfer::*)() const) &XSControl_SelectForTransfer::Reader, "Returns the Reader (if created with a Reader) Returns a Null Handle if not created with a Reader");
cls_XSControl_SelectForTransfer.def("Sort", (Standard_Boolean (XSControl_SelectForTransfer::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const opencascade::handle<Interface_InterfaceModel> &) const) &XSControl_SelectForTransfer::Sort, "Returns True for an Entity which is recognized by the Actor, either the precised one, or the one defined by TransferReader", py::arg("rank"), py::arg("ent"), py::arg("model"));
cls_XSControl_SelectForTransfer.def("ExtractLabel", (TCollection_AsciiString (XSControl_SelectForTransfer::*)() const) &XSControl_SelectForTransfer::ExtractLabel, "Returns a text defining the criterium : 'Recognized for Transfer [(current actor)]'");
cls_XSControl_SelectForTransfer.def_static("get_type_name_", (const char * (*)()) &XSControl_SelectForTransfer::get_type_name, "None");
cls_XSControl_SelectForTransfer.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_SelectForTransfer::get_type_descriptor, "None");
cls_XSControl_SelectForTransfer.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_SelectForTransfer::*)() const) &XSControl_SelectForTransfer::DynamicType, "None");

// CLASS: XSCONTROL
py::class_<XSControl> cls_XSControl(mod, "XSControl", "This package provides complements to IFSelect & Co for control of a session");

// Methods
// cls_XSControl.def_static("operator new_", (void * (*)(size_t)) &XSControl::operator new, "None", py::arg("theSize"));
// cls_XSControl.def_static("operator delete_", (void (*)(void *)) &XSControl::operator delete, "None", py::arg("theAddress"));
// cls_XSControl.def_static("operator new[]_", (void * (*)(size_t)) &XSControl::operator new[], "None", py::arg("theSize"));
// cls_XSControl.def_static("operator delete[]_", (void (*)(void *)) &XSControl::operator delete[], "None", py::arg("theAddress"));
// cls_XSControl.def_static("operator new_", (void * (*)(size_t, void *)) &XSControl::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XSControl.def_static("operator delete_", (void (*)(void *, void *)) &XSControl::operator delete, "None", py::arg(""), py::arg(""));
cls_XSControl.def_static("Session_", (opencascade::handle<XSControl_WorkSession> (*)(const opencascade::handle<IFSelect_SessionPilot> &)) &XSControl::Session, "Returns the WorkSession of a SessionPilot, but casts it as from XSControl : it then gives access to Control & Transfers", py::arg("pilot"));
cls_XSControl.def_static("Vars_", (opencascade::handle<XSControl_Vars> (*)(const opencascade::handle<IFSelect_SessionPilot> &)) &XSControl::Vars, "Returns the Vars of a SessionPilot, it is brought by Session it provides access to external variables", py::arg("pilot"));

// CLASS: XSCONTROL_CONNECTEDSHAPES
py::class_<XSControl_ConnectedShapes, opencascade::handle<XSControl_ConnectedShapes>, IFSelect_SelectExplore> cls_XSControl_ConnectedShapes(mod, "XSControl_ConnectedShapes", "From a TopoDS_Shape, or from the entity which has produced it, searches for the shapes, and the entities which have produced them in last transfer, which are adjacent to it by VERTICES");

// Constructors
cls_XSControl_ConnectedShapes.def(py::init<>());
cls_XSControl_ConnectedShapes.def(py::init<const opencascade::handle<XSControl_TransferReader> &>(), py::arg("TR"));

// Methods
cls_XSControl_ConnectedShapes.def("SetReader", (void (XSControl_ConnectedShapes::*)(const opencascade::handle<XSControl_TransferReader> &)) &XSControl_ConnectedShapes::SetReader, "Sets a TransferReader to sort entities : it brings the TransferProcess which may change, while the TransferReader does not", py::arg("TR"));
cls_XSControl_ConnectedShapes.def("Explore", (Standard_Boolean (XSControl_ConnectedShapes::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_Graph &, Interface_EntityIterator &) const) &XSControl_ConnectedShapes::Explore, "Explores an entity : entities from which are connected to that produced by this entity, including itself", py::arg("level"), py::arg("ent"), py::arg("G"), py::arg("explored"));
cls_XSControl_ConnectedShapes.def("ExploreLabel", (TCollection_AsciiString (XSControl_ConnectedShapes::*)() const) &XSControl_ConnectedShapes::ExploreLabel, "Returns a text defining the criterium. 'Connected Entities through produced Shapes'");
cls_XSControl_ConnectedShapes.def_static("AdjacentEntities_", (opencascade::handle<TColStd_HSequenceOfTransient> (*)(const TopoDS_Shape &, const opencascade::handle<Transfer_TransientProcess> &, const TopAbs_ShapeEnum)) &XSControl_ConnectedShapes::AdjacentEntities, "This functions considers a shape from a transfer and performs the search function explained above", py::arg("ashape"), py::arg("TP"), py::arg("type"));
cls_XSControl_ConnectedShapes.def_static("get_type_name_", (const char * (*)()) &XSControl_ConnectedShapes::get_type_name, "None");
cls_XSControl_ConnectedShapes.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_ConnectedShapes::get_type_descriptor, "None");
cls_XSControl_ConnectedShapes.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_ConnectedShapes::*)() const) &XSControl_ConnectedShapes::DynamicType, "None");

// CLASS: XSCONTROL_FUNCSHAPE
py::class_<XSControl_FuncShape> cls_XSControl_FuncShape(mod, "XSControl_FuncShape", "Defines additionnal commands for XSControl to : - control of initialisation (xinit, xnorm, newmodel) - analyse of the result of a transfer (recorded in a TransientProcess for Read, FinderProcess for Write) : statistics, various lists (roots,complete,abnormal), what about one specific entity, producing a model with the abnormal result");

// Methods
// cls_XSControl_FuncShape.def_static("operator new_", (void * (*)(size_t)) &XSControl_FuncShape::operator new, "None", py::arg("theSize"));
// cls_XSControl_FuncShape.def_static("operator delete_", (void (*)(void *)) &XSControl_FuncShape::operator delete, "None", py::arg("theAddress"));
// cls_XSControl_FuncShape.def_static("operator new[]_", (void * (*)(size_t)) &XSControl_FuncShape::operator new[], "None", py::arg("theSize"));
// cls_XSControl_FuncShape.def_static("operator delete[]_", (void (*)(void *)) &XSControl_FuncShape::operator delete[], "None", py::arg("theAddress"));
// cls_XSControl_FuncShape.def_static("operator new_", (void * (*)(size_t, void *)) &XSControl_FuncShape::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XSControl_FuncShape.def_static("operator delete_", (void (*)(void *, void *)) &XSControl_FuncShape::operator delete, "None", py::arg(""), py::arg(""));
cls_XSControl_FuncShape.def_static("Init_", (void (*)()) &XSControl_FuncShape::Init, "Defines and loads all functions which work on shapes for XSControl (as ActFunc)");
cls_XSControl_FuncShape.def_static("MoreShapes_", (Standard_Integer (*)(const opencascade::handle<XSControl_WorkSession> &, opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_CString)) &XSControl_FuncShape::MoreShapes, "Analyses a name as designating Shapes from a Vars or from XSTEP transfer (last Transfer on Reading). <name> can be : '*' : all the root shapes produced by last Transfer (Read) i.e. considers roots of the TransientProcess a name : a name of a variable DRAW", py::arg("session"), py::arg("list"), py::arg("name"));
cls_XSControl_FuncShape.def_static("FileAndVar_", (Standard_Boolean (*)(const opencascade::handle<XSControl_WorkSession> &, const Standard_CString, const Standard_CString, const Standard_CString, TCollection_AsciiString &, TCollection_AsciiString &)) &XSControl_FuncShape::FileAndVar, "Analyses given file name and variable name, with a default name for variables. Returns resulting file name and variable name plus status 'file to read'(True) or 'already read'(False) In the latter case, empty resfile means no file available", py::arg("session"), py::arg("file"), py::arg("var"), py::arg("def"), py::arg("resfile"), py::arg("resvar"));

// CLASS: XSCONTROL_FUNCTIONS
py::class_<XSControl_Functions> cls_XSControl_Functions(mod, "XSControl_Functions", "Functions from XSControl gives access to actions which can be commanded with the resources provided by XSControl: especially Controller and Transfer");

// Methods
cls_XSControl_Functions.def_static("Init_", (void (*)()) &XSControl_Functions::Init, "Defines and loads all functions for XSControl (as ActFunc)");

// CLASS: XSCONTROL_SIGNTRANSFERSTATUS
py::class_<XSControl_SignTransferStatus, opencascade::handle<XSControl_SignTransferStatus>, IFSelect_Signature> cls_XSControl_SignTransferStatus(mod, "XSControl_SignTransferStatus", "This Signatures gives the Transfer Status of an entity, as recorded in a TransferProcess. It can be : - Void : not recorded, or recorded as void with no message (attributes are not taken into account) - Warning : no result, warning message(s), no fail - Fail : no result, fail messages (with or without warning) - Result.. : result, no message (neither warning nor fail) Result.. i.e. Result:TypeName of the result - Result../Warning : result, with warning but no fail - Result../Fail : result, with fail (.e. bad result) - Fail on run : no result yet recorded, no message, but an exception occurred while recording the result (this should not appear and indicates a programming error)");

// Constructors
cls_XSControl_SignTransferStatus.def(py::init<>());
cls_XSControl_SignTransferStatus.def(py::init<const opencascade::handle<XSControl_TransferReader> &>(), py::arg("TR"));

// Methods
cls_XSControl_SignTransferStatus.def("SetReader", (void (XSControl_SignTransferStatus::*)(const opencascade::handle<XSControl_TransferReader> &)) &XSControl_SignTransferStatus::SetReader, "Sets a TransferReader to work", py::arg("TR"));
cls_XSControl_SignTransferStatus.def("SetMap", (void (XSControl_SignTransferStatus::*)(const opencascade::handle<Transfer_TransientProcess> &)) &XSControl_SignTransferStatus::SetMap, "Sets a precise map to sign entities This definition oversedes the creation with a TransferReader", py::arg("TP"));
cls_XSControl_SignTransferStatus.def("Map", (opencascade::handle<Transfer_TransientProcess> (XSControl_SignTransferStatus::*)() const) &XSControl_SignTransferStatus::Map, "Returns the TransientProcess used as precised one Returns a Null Handle for a creation from a TransferReader without any further setting");
cls_XSControl_SignTransferStatus.def("Reader", (opencascade::handle<XSControl_TransferReader> (XSControl_SignTransferStatus::*)() const) &XSControl_SignTransferStatus::Reader, "Returns the Reader (if created with a Reader) Returns a Null Handle if not created with a Reader");
cls_XSControl_SignTransferStatus.def("Value", (Standard_CString (XSControl_SignTransferStatus::*)(const opencascade::handle<Standard_Transient> &, const opencascade::handle<Interface_InterfaceModel> &) const) &XSControl_SignTransferStatus::Value, "Returns the Signature for a Transient object, as its transfer status", py::arg("ent"), py::arg("model"));
cls_XSControl_SignTransferStatus.def_static("get_type_name_", (const char * (*)()) &XSControl_SignTransferStatus::get_type_name, "None");
cls_XSControl_SignTransferStatus.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_SignTransferStatus::get_type_descriptor, "None");
cls_XSControl_SignTransferStatus.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_SignTransferStatus::*)() const) &XSControl_SignTransferStatus::DynamicType, "None");

// CLASS: XSCONTROL_TRANSFERREADER
py::class_<XSControl_TransferReader, opencascade::handle<XSControl_TransferReader>, Standard_Transient> cls_XSControl_TransferReader(mod, "XSControl_TransferReader", "A TransferReader performs, manages, handles results of, transfers done when reading a file (i.e. from entities of an InterfaceModel, to objects for Imagine)");

// Constructors
cls_XSControl_TransferReader.def(py::init<>());

// Methods
cls_XSControl_TransferReader.def("SetController", (void (XSControl_TransferReader::*)(const opencascade::handle<XSControl_Controller> &)) &XSControl_TransferReader::SetController, "Sets a Controller. It is required to generate the Actor. Elsewhere, the Actor must be provided directly", py::arg("theControl"));
cls_XSControl_TransferReader.def("SetActor", (void (XSControl_TransferReader::*)(const opencascade::handle<Transfer_ActorOfTransientProcess> &)) &XSControl_TransferReader::SetActor, "Sets the Actor directly : this value will be used if the Controller is not set", py::arg("theActor"));
cls_XSControl_TransferReader.def("Actor", (opencascade::handle<Transfer_ActorOfTransientProcess> (XSControl_TransferReader::*)()) &XSControl_TransferReader::Actor, "Returns the Actor, determined by the Controller, or if this one is unknown, directly set. Once it has been defined, it can then be edited.");
cls_XSControl_TransferReader.def("SetModel", (void (XSControl_TransferReader::*)(const opencascade::handle<Interface_InterfaceModel> &)) &XSControl_TransferReader::SetModel, "Sets an InterfaceModel. This causes former results, computed from another one, to be lost (see also Clear)", py::arg("theModel"));
cls_XSControl_TransferReader.def("SetGraph", (void (XSControl_TransferReader::*)(const opencascade::handle<Interface_HGraph> &)) &XSControl_TransferReader::SetGraph, "Sets a Graph and its InterfaceModel (calls SetModel)", py::arg("theGraph"));
cls_XSControl_TransferReader.def("Model", (const opencascade::handle<Interface_InterfaceModel> & (XSControl_TransferReader::*)() const) &XSControl_TransferReader::Model, "Returns the currently set InterfaceModel");
cls_XSControl_TransferReader.def("SetContext", (void (XSControl_TransferReader::*)(const Standard_CString, const opencascade::handle<Standard_Transient> &)) &XSControl_TransferReader::SetContext, "Sets a Context : according to receiving appli, to be interpreted by the Actor", py::arg("theName"), py::arg("theCtx"));
cls_XSControl_TransferReader.def("GetContext", (Standard_Boolean (XSControl_TransferReader::*)(const Standard_CString, const opencascade::handle<Standard_Type> &, opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::GetContext, "Returns the Context attached to a name, if set and if it is Kind of the type, else a Null Handle Returns True if OK, False if no Context", py::arg("theName"), py::arg("theType"), py::arg("theCtx"));
cls_XSControl_TransferReader.def("Context", (NCollection_DataMap<TCollection_AsciiString, opencascade::handle<Standard_Transient> > & (XSControl_TransferReader::*)()) &XSControl_TransferReader::Context, "Returns (modifiable) the whole definition of Context Rather for internal use (ex.: preparing and setting in once)");
cls_XSControl_TransferReader.def("SetFileName", (void (XSControl_TransferReader::*)(const Standard_CString)) &XSControl_TransferReader::SetFileName, "Sets a new value for (loaded) file name", py::arg("theName"));
cls_XSControl_TransferReader.def("FileName", (Standard_CString (XSControl_TransferReader::*)() const) &XSControl_TransferReader::FileName, "Returns actual value of file name");
cls_XSControl_TransferReader.def("Clear", (void (XSControl_TransferReader::*)(const Standard_Integer)) &XSControl_TransferReader::Clear, "Clears data, according mode : -1 all 0 nothing done +1 final results +2 working data (model, context, transfer process)", py::arg("theMode"));
cls_XSControl_TransferReader.def("TransientProcess", (const opencascade::handle<Transfer_TransientProcess> & (XSControl_TransferReader::*)() const) &XSControl_TransferReader::TransientProcess, "Returns the currently used TransientProcess It is computed from the model by TransferReadRoots, or by BeginTransferRead");
cls_XSControl_TransferReader.def("SetTransientProcess", (void (XSControl_TransferReader::*)(const opencascade::handle<Transfer_TransientProcess> &)) &XSControl_TransferReader::SetTransientProcess, "Forces the TransientProcess Remark : it also changes the Model and the Actor, from those recorded in the new TransientProcess", py::arg("theTP"));
cls_XSControl_TransferReader.def("RecordResult", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_TransferReader::RecordResult, "Records a final result of transferring an entity This result is recorded as a ResultFromModel, taken from the TransientProcess Returns True if a result is available, False else", py::arg("theEnt"));
cls_XSControl_TransferReader.def("IsRecorded", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::IsRecorded, "Returns True if a final result is recorded for an entity Remark that it can bring no effective result if transfer has completely failed (FinalResult brings only fail messages ...)", py::arg("theEnt"));
cls_XSControl_TransferReader.def("HasResult", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::HasResult, "Returns True if a final result is recorded AND BRINGS AN EFFECTIVE RESULT (else, it brings only fail messages)", py::arg("theEnt"));
cls_XSControl_TransferReader.def("RecordedList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_TransferReader::*)() const) &XSControl_TransferReader::RecordedList, "Returns the list of entities to which a final result is attached (i.e. processed by RecordResult)");
cls_XSControl_TransferReader.def("Skip", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_TransferReader::Skip, "Note that an entity has been required for transfer but no result at all is available (typically : case not implemented) It is not an error, but it gives a specific status : Skipped Returns True if done, False if <ent> is not in starting model", py::arg("theEnt"));
cls_XSControl_TransferReader.def("IsSkipped", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::IsSkipped, "Returns True if an entity is noted as skipped", py::arg("theEnt"));
cls_XSControl_TransferReader.def("IsMarked", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::IsMarked, "Returns True if an entity has been asked for transfert, hence it is marked, as : Recorded (a computation has ran, with or without an effective result), or Skipped (case ignored)", py::arg("theEnt"));
cls_XSControl_TransferReader.def("FinalResult", (opencascade::handle<Transfer_ResultFromModel> (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::FinalResult, "Returns the final result recorded for an entity, as such", py::arg("theEnt"));
cls_XSControl_TransferReader.def("FinalEntityLabel", (Standard_CString (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::FinalEntityLabel, "Returns the label attached to an entity recorded for final, or an empty string if not recorded", py::arg("theEnt"));
cls_XSControl_TransferReader.def("FinalEntityNumber", (Standard_Integer (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::FinalEntityNumber, "Returns the number attached to the entity recorded for final, or zero if not recorded (looks in the ResultFromModel)", py::arg("theEnt"));
cls_XSControl_TransferReader.def("ResultFromNumber", (opencascade::handle<Transfer_ResultFromModel> (XSControl_TransferReader::*)(const Standard_Integer) const) &XSControl_TransferReader::ResultFromNumber, "Returns the final result recorded for a NUMBER of entity (internal use). Null if out of range", py::arg("theNum"));
cls_XSControl_TransferReader.def("TransientResult", (opencascade::handle<Standard_Transient> (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::TransientResult, "Returns the resulting object as a Transient Null Handle if no result or result not transient", py::arg("theEnt"));
cls_XSControl_TransferReader.def("ShapeResult", (TopoDS_Shape (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_TransferReader::ShapeResult, "Returns the resulting object as a Shape Null Shape if no result or result not a shape", py::arg("theEnt"));
cls_XSControl_TransferReader.def("ClearResult", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer)) &XSControl_TransferReader::ClearResult, "Clears recorded result for an entity, according mode <mode> = -1 : true, complete, clearing (erasing result) <mode> >= 0 : simple 'stripping', see ResultFromModel, in particular, 0 for simple internal strip, 10 for all but final result, 11 for all : just label, status and filename are kept Returns True when done, False if nothing was to clear", py::arg("theEnt"), py::arg("theMode"));
cls_XSControl_TransferReader.def("EntityFromResult", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0) -> opencascade::handle<Standard_Transient> { return self.EntityFromResult(a0); });
cls_XSControl_TransferReader.def("EntityFromResult", (opencascade::handle<Standard_Transient> (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_TransferReader::EntityFromResult, "Returns an entity from which a given result was produced. If <mode> = 0 (D), searches in last root transfers If <mode> = 1, searches in last (root & sub) transfers If <mode> = 2, searches in root recorded results If <mode> = 3, searches in all (root & sub) recordeds <res> can be, either a transient object (result itself) or a binder. For a binder of shape, calls EntityFromShapeResult Returns a Null Handle if <res> not recorded", py::arg("theRes"), py::arg("theMode"));
cls_XSControl_TransferReader.def("EntityFromShapeResult", [](XSControl_TransferReader &self, const TopoDS_Shape & a0) -> opencascade::handle<Standard_Transient> { return self.EntityFromShapeResult(a0); });
cls_XSControl_TransferReader.def("EntityFromShapeResult", (opencascade::handle<Standard_Transient> (XSControl_TransferReader::*)(const TopoDS_Shape &, const Standard_Integer) const) &XSControl_TransferReader::EntityFromShapeResult, "Returns an entity from which a given shape result was produced Returns a Null Handle if <res> not recorded or not a Shape", py::arg("theRes"), py::arg("theMode"));
cls_XSControl_TransferReader.def("EntitiesFromShapeList", [](XSControl_TransferReader &self, const opencascade::handle<TopTools_HSequenceOfShape> & a0) -> opencascade::handle<TColStd_HSequenceOfTransient> { return self.EntitiesFromShapeList(a0); });
cls_XSControl_TransferReader.def("EntitiesFromShapeList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_TransferReader::*)(const opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Integer) const) &XSControl_TransferReader::EntitiesFromShapeList, "Returns the list of entities from which some shapes were produced : it corresponds to a loop on EntityFromShapeResult, but is optimised", py::arg("theRes"), py::arg("theMode"));
cls_XSControl_TransferReader.def("CheckList", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0) -> Interface_CheckIterator { return self.CheckList(a0); });
cls_XSControl_TransferReader.def("CheckList", (Interface_CheckIterator (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_TransferReader::CheckList, "Returns the CheckList resulting from transferring <ent>, i.e. stored in its recorded form ResultFromModel (empty if transfer successful or not recorded ...)", py::arg("theEnt"), py::arg("theLevel"));
cls_XSControl_TransferReader.def("HasChecks", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Boolean) const) &XSControl_TransferReader::HasChecks, "Returns True if an entity (with a final result) has checks : - failsonly = False : any kind of check message - failsonly = True : fails only Returns False if <ent> is not recorded", py::arg("theEnt"), py::arg("FailsOnly"));
cls_XSControl_TransferReader.def("CheckedList", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0) -> opencascade::handle<TColStd_HSequenceOfTransient> { return self.CheckedList(a0); });
cls_XSControl_TransferReader.def("CheckedList", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0, const Interface_CheckStatus a1) -> opencascade::handle<TColStd_HSequenceOfTransient> { return self.CheckedList(a0, a1); });
cls_XSControl_TransferReader.def("CheckedList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Interface_CheckStatus, const Standard_Boolean) const) &XSControl_TransferReader::CheckedList, "Returns the list of starting entities to which a given check status is attached, IN FINAL RESULTS <ent> can be an entity, or the model to query all entities Below, 'entities' are, either <ent> plus its sub-transferred, or all the entities of the model", py::arg("theEnt"), py::arg("WithCheck"), py::arg("theResult"));
cls_XSControl_TransferReader.def("BeginTransfer", (Standard_Boolean (XSControl_TransferReader::*)()) &XSControl_TransferReader::BeginTransfer, "Defines a new TransferProcess for reading transfer Returns True if done, False if data are not properly defined (the Model, the Actor for Read)");
cls_XSControl_TransferReader.def("Recognize", (Standard_Boolean (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &)) &XSControl_TransferReader::Recognize, "Tells if an entity is recognized as a valid candidate for Transfer. Calls method Recognize from the Actor (if known)", py::arg("theEnt"));
cls_XSControl_TransferReader.def("TransferOne", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0) -> Standard_Integer { return self.TransferOne(a0); });
cls_XSControl_TransferReader.def("TransferOne", (Standard_Integer (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Boolean)) &XSControl_TransferReader::TransferOne, "Commands the transfer on reading for an entity to data for Imagine, using the selected Actor for Read Returns count of transferred entities, ok or with fails (0/1) If <rec> is True (D), the result is recorded by RecordResult", py::arg("theEnt"), py::arg("theRec"));
cls_XSControl_TransferReader.def("TransferList", [](XSControl_TransferReader &self, const opencascade::handle<TColStd_HSequenceOfTransient> & a0) -> Standard_Integer { return self.TransferList(a0); });
cls_XSControl_TransferReader.def("TransferList", (Standard_Integer (XSControl_TransferReader::*)(const opencascade::handle<TColStd_HSequenceOfTransient> &, const Standard_Boolean)) &XSControl_TransferReader::TransferList, "Commands the transfer on reading for a list of entities to data for Imagine, using the selected Actor for Read Returns count of transferred entities, ok or with fails (0/1) If <rec> is True (D), the results are recorded by RecordResult", py::arg("theList"), py::arg("theRec"));
cls_XSControl_TransferReader.def("TransferRoots", (Standard_Integer (XSControl_TransferReader::*)(const Interface_Graph &)) &XSControl_TransferReader::TransferRoots, "Transfers the content of the current Interface Model to data handled by Imagine, starting from its Roots (determined by the Graph <G>), using the selected Actor for Read Returns the count of performed root transfers (i.e. 0 if none) or -1 if no actor is defined", py::arg("theGraph"));
cls_XSControl_TransferReader.def("TransferClear", [](XSControl_TransferReader &self, const opencascade::handle<Standard_Transient> & a0) -> void { return self.TransferClear(a0); });
cls_XSControl_TransferReader.def("TransferClear", (void (XSControl_TransferReader::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer)) &XSControl_TransferReader::TransferClear, "Clears the results attached to an entity if <ents> equates the starting model, clears all results", py::arg("theEnt"), py::arg("theLevel"));
cls_XSControl_TransferReader.def("PrintStats", [](XSControl_TransferReader &self, const Standard_Integer a0) -> void { return self.PrintStats(a0); });
cls_XSControl_TransferReader.def("PrintStats", (void (XSControl_TransferReader::*)(const Standard_Integer, const Standard_Integer) const) &XSControl_TransferReader::PrintStats, "Prints statistics on current Trace File, according <what> and <mode>. See PrintStatsProcess for details", py::arg("theWhat"), py::arg("theMode"));
cls_XSControl_TransferReader.def("LastCheckList", (Interface_CheckIterator (XSControl_TransferReader::*)() const) &XSControl_TransferReader::LastCheckList, "Returns the CheckList resulting from last TransferRead i.e. from TransientProcess itself, recorded from last Clear");
cls_XSControl_TransferReader.def("LastTransferList", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_TransferReader::*)(const Standard_Boolean) const) &XSControl_TransferReader::LastTransferList, "Returns the list of entities recorded as lastly transferred i.e. from TransientProcess itself, recorded from last Clear If <roots> is True , considers only roots of transfer If <roots> is False, considers all entities bound with result", py::arg("theRoots"));
cls_XSControl_TransferReader.def("ShapeResultList", (const opencascade::handle<TopTools_HSequenceOfShape> & (XSControl_TransferReader::*)(const Standard_Boolean)) &XSControl_TransferReader::ShapeResultList, "Returns a list of result Shapes If <rec> is True , sees RecordedList If <rec> is False, sees LastTransferList (last ROOT transfers) For each one, if it is a Shape, it is cumulated to the list If no Shape is found, returns an empty Sequence", py::arg("theRec"));
cls_XSControl_TransferReader.def_static("PrintStatsProcess_", [](const opencascade::handle<Transfer_TransientProcess> & a0, const Standard_Integer a1) -> void { return XSControl_TransferReader::PrintStatsProcess(a0, a1); });
cls_XSControl_TransferReader.def_static("PrintStatsProcess_", (void (*)(const opencascade::handle<Transfer_TransientProcess> &, const Standard_Integer, const Standard_Integer)) &XSControl_TransferReader::PrintStatsProcess, "This routines prints statistics about a TransientProcess It can be called, by a TransferReader, or isolately Prints are done on the default trace file <what> defines what kind of statistics are to be printed : 0 : basic figures 1 : root results 2 : all recorded (roots, intermediate, checked entities) 3 : abnormal records 4 : check messages (warnings and fails) 5 : fail messages", py::arg("theTP"), py::arg("theWhat"), py::arg("theMode"));
cls_XSControl_TransferReader.def_static("PrintStatsOnList_", [](const opencascade::handle<Transfer_TransientProcess> & a0, const opencascade::handle<TColStd_HSequenceOfTransient> & a1, const Standard_Integer a2) -> void { return XSControl_TransferReader::PrintStatsOnList(a0, a1, a2); });
cls_XSControl_TransferReader.def_static("PrintStatsOnList_", (void (*)(const opencascade::handle<Transfer_TransientProcess> &, const opencascade::handle<TColStd_HSequenceOfTransient> &, const Standard_Integer, const Standard_Integer)) &XSControl_TransferReader::PrintStatsOnList, "Works as PrintStatsProcess, but displays data only on the entities which are in <list> (filter)", py::arg("theTP"), py::arg("theList"), py::arg("theWhat"), py::arg("theMode"));
cls_XSControl_TransferReader.def_static("get_type_name_", (const char * (*)()) &XSControl_TransferReader::get_type_name, "None");
cls_XSControl_TransferReader.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_TransferReader::get_type_descriptor, "None");
cls_XSControl_TransferReader.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_TransferReader::*)() const) &XSControl_TransferReader::DynamicType, "None");

// CLASS: XSCONTROL_UTILS
py::class_<XSControl_Utils> cls_XSControl_Utils(mod, "XSControl_Utils", "This class provides various useful utility routines, to facilitate handling of most common data structures : transients (type, type name ...), strings (ascii or extended, pointed or handled or ...), shapes (reading, writing, testing ...), sequences & arrays (of strings, of transients, of shapes ...), ...");

// Constructors
cls_XSControl_Utils.def(py::init<>());

// Methods
// cls_XSControl_Utils.def_static("operator new_", (void * (*)(size_t)) &XSControl_Utils::operator new, "None", py::arg("theSize"));
// cls_XSControl_Utils.def_static("operator delete_", (void (*)(void *)) &XSControl_Utils::operator delete, "None", py::arg("theAddress"));
// cls_XSControl_Utils.def_static("operator new[]_", (void * (*)(size_t)) &XSControl_Utils::operator new[], "None", py::arg("theSize"));
// cls_XSControl_Utils.def_static("operator delete[]_", (void (*)(void *)) &XSControl_Utils::operator delete[], "None", py::arg("theAddress"));
// cls_XSControl_Utils.def_static("operator new_", (void * (*)(size_t, void *)) &XSControl_Utils::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XSControl_Utils.def_static("operator delete_", (void (*)(void *, void *)) &XSControl_Utils::operator delete, "None", py::arg(""), py::arg(""));
cls_XSControl_Utils.def("TraceLine", (void (XSControl_Utils::*)(const Standard_CString) const) &XSControl_Utils::TraceLine, "Just prints a line into the current Trace File. This allows to better characterise the various trace outputs, as desired.", py::arg("line"));
cls_XSControl_Utils.def("TraceLines", (void (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_Utils::TraceLines, "Just prints a line or a set of lines into the current Trace File. <lines> can be a HAscii/ExtendedString (produces a print without ending line) or a HSequence or HArray1 Of .. (one new line per item)", py::arg("lines"));
cls_XSControl_Utils.def("IsKind", (Standard_Boolean (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const opencascade::handle<Standard_Type> &) const) &XSControl_Utils::IsKind, "None", py::arg("item"), py::arg("what"));
cls_XSControl_Utils.def("TypeName", [](XSControl_Utils &self, const opencascade::handle<Standard_Transient> & a0) -> Standard_CString { return self.TypeName(a0); });
cls_XSControl_Utils.def("TypeName", (Standard_CString (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const Standard_Boolean) const) &XSControl_Utils::TypeName, "Returns the name of the dynamic type of an object, i.e. : If it is a Type, its Name If it is a object not a type, the Name of its DynamicType If it is Null, an empty string If <nopk> is False (D), gives complete name If <nopk> is True, returns class name without package", py::arg("item"), py::arg("nopk"));
cls_XSControl_Utils.def("TraValue", (opencascade::handle<Standard_Transient> (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_Utils::TraValue, "None", py::arg("list"), py::arg("num"));
cls_XSControl_Utils.def("NewSeqTra", (opencascade::handle<TColStd_HSequenceOfTransient> (XSControl_Utils::*)() const) &XSControl_Utils::NewSeqTra, "None");
cls_XSControl_Utils.def("AppendTra", (void (XSControl_Utils::*)(const opencascade::handle<TColStd_HSequenceOfTransient> &, const opencascade::handle<Standard_Transient> &) const) &XSControl_Utils::AppendTra, "None", py::arg("seqval"), py::arg("traval"));
cls_XSControl_Utils.def("DateString", (Standard_CString (XSControl_Utils::*)(const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer) const) &XSControl_Utils::DateString, "None", py::arg("yy"), py::arg("mm"), py::arg("dd"), py::arg("hh"), py::arg("mn"), py::arg("ss"));
cls_XSControl_Utils.def("DateValues", [](XSControl_Utils &self, const Standard_CString text, Standard_Integer & yy, Standard_Integer & mm, Standard_Integer & dd, Standard_Integer & hh, Standard_Integer & mn, Standard_Integer & ss){ self.DateValues(text, yy, mm, dd, hh, mn, ss); return std::tuple<Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &, Standard_Integer &>(yy, mm, dd, hh, mn, ss); }, "None", py::arg("text"), py::arg("yy"), py::arg("mm"), py::arg("dd"), py::arg("hh"), py::arg("mn"), py::arg("ss"));
cls_XSControl_Utils.def("ToCString", (Standard_CString (XSControl_Utils::*)(const opencascade::handle<TCollection_HAsciiString> &) const) &XSControl_Utils::ToCString, "None", py::arg("strval"));
cls_XSControl_Utils.def("ToCString", (Standard_CString (XSControl_Utils::*)(const TCollection_AsciiString &) const) &XSControl_Utils::ToCString, "None", py::arg("strval"));
cls_XSControl_Utils.def("ToHString", (opencascade::handle<TCollection_HAsciiString> (XSControl_Utils::*)(const Standard_CString) const) &XSControl_Utils::ToHString, "None", py::arg("strcon"));
cls_XSControl_Utils.def("ToAString", (TCollection_AsciiString (XSControl_Utils::*)(const Standard_CString) const) &XSControl_Utils::ToAString, "None", py::arg("strcon"));
cls_XSControl_Utils.def("ToEString", (Standard_ExtString (XSControl_Utils::*)(const opencascade::handle<TCollection_HExtendedString> &) const) &XSControl_Utils::ToEString, "None", py::arg("strval"));
cls_XSControl_Utils.def("ToEString", (Standard_ExtString (XSControl_Utils::*)(const TCollection_ExtendedString &) const) &XSControl_Utils::ToEString, "None", py::arg("strval"));
cls_XSControl_Utils.def("ToHString", (opencascade::handle<TCollection_HExtendedString> (XSControl_Utils::*)(const Standard_ExtString) const) &XSControl_Utils::ToHString, "None", py::arg("strcon"));
cls_XSControl_Utils.def("ToXString", (TCollection_ExtendedString (XSControl_Utils::*)(const Standard_ExtString) const) &XSControl_Utils::ToXString, "None", py::arg("strcon"));
cls_XSControl_Utils.def("AsciiToExtended", (Standard_ExtString (XSControl_Utils::*)(const Standard_CString) const) &XSControl_Utils::AsciiToExtended, "None", py::arg("str"));
cls_XSControl_Utils.def("IsAscii", (Standard_Boolean (XSControl_Utils::*)(const Standard_ExtString) const) &XSControl_Utils::IsAscii, "None", py::arg("str"));
cls_XSControl_Utils.def("ExtendedToAscii", (Standard_CString (XSControl_Utils::*)(const Standard_ExtString) const) &XSControl_Utils::ExtendedToAscii, "None", py::arg("str"));
cls_XSControl_Utils.def("CStrValue", (Standard_CString (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_Utils::CStrValue, "None", py::arg("list"), py::arg("num"));
cls_XSControl_Utils.def("EStrValue", (Standard_ExtString (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_Utils::EStrValue, "None", py::arg("list"), py::arg("num"));
cls_XSControl_Utils.def("NewSeqCStr", (opencascade::handle<TColStd_HSequenceOfHAsciiString> (XSControl_Utils::*)() const) &XSControl_Utils::NewSeqCStr, "None");
cls_XSControl_Utils.def("AppendCStr", (void (XSControl_Utils::*)(const opencascade::handle<TColStd_HSequenceOfHAsciiString> &, const Standard_CString) const) &XSControl_Utils::AppendCStr, "None", py::arg("seqval"), py::arg("strval"));
cls_XSControl_Utils.def("NewSeqEStr", (opencascade::handle<TColStd_HSequenceOfHExtendedString> (XSControl_Utils::*)() const) &XSControl_Utils::NewSeqEStr, "None");
cls_XSControl_Utils.def("AppendEStr", (void (XSControl_Utils::*)(const opencascade::handle<TColStd_HSequenceOfHExtendedString> &, const Standard_ExtString) const) &XSControl_Utils::AppendEStr, "None", py::arg("seqval"), py::arg("strval"));
cls_XSControl_Utils.def("CompoundFromSeq", (TopoDS_Shape (XSControl_Utils::*)(const opencascade::handle<TopTools_HSequenceOfShape> &) const) &XSControl_Utils::CompoundFromSeq, "Converts a list of Shapes to a Compound (a kind of Shape)", py::arg("seqval"));
cls_XSControl_Utils.def("ShapeType", (TopAbs_ShapeEnum (XSControl_Utils::*)(const TopoDS_Shape &, const Standard_Boolean) const) &XSControl_Utils::ShapeType, "Returns the type of a Shape : true type if <compound> is False If <compound> is True and <shape> is a Compound, iterates on its items. If all are of the same type, returns this type. Else, returns COMPOUND. If it is empty, returns SHAPE For a Null Shape, returns SHAPE", py::arg("shape"), py::arg("compound"));
cls_XSControl_Utils.def("SortedCompound", (TopoDS_Shape (XSControl_Utils::*)(const TopoDS_Shape &, const TopAbs_ShapeEnum, const Standard_Boolean, const Standard_Boolean) const) &XSControl_Utils::SortedCompound, "From a Shape, builds a Compound as follows : explores it level by level If <explore> is False, only COMPOUND items. Else, all items Adds to the result, shapes which comply to <type> + if <type> is WIRE, considers free edges (and makes wires) + if <type> is SHELL, considers free faces (and makes shells) If <compound> is True, gathers items in compounds which correspond to starting COMPOUND,SOLID or SHELL containers, or items directly contained in a Compound", py::arg("shape"), py::arg("type"), py::arg("explore"), py::arg("compound"));
cls_XSControl_Utils.def("ShapeValue", (TopoDS_Shape (XSControl_Utils::*)(const opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Integer) const) &XSControl_Utils::ShapeValue, "None", py::arg("seqv"), py::arg("num"));
cls_XSControl_Utils.def("NewSeqShape", (opencascade::handle<TopTools_HSequenceOfShape> (XSControl_Utils::*)() const) &XSControl_Utils::NewSeqShape, "None");
cls_XSControl_Utils.def("AppendShape", (void (XSControl_Utils::*)(const opencascade::handle<TopTools_HSequenceOfShape> &, const TopoDS_Shape &) const) &XSControl_Utils::AppendShape, "None", py::arg("seqv"), py::arg("shape"));
cls_XSControl_Utils.def("ShapeBinder", [](XSControl_Utils &self, const TopoDS_Shape & a0) -> opencascade::handle<Standard_Transient> { return self.ShapeBinder(a0); });
cls_XSControl_Utils.def("ShapeBinder", (opencascade::handle<Standard_Transient> (XSControl_Utils::*)(const TopoDS_Shape &, const Standard_Boolean) const) &XSControl_Utils::ShapeBinder, "Creates a Transient Object from a Shape : it is either a Binder (used by functions which require a Transient but can process a Shape, such as viewing functions) or a HShape (according to hs) Default is a HShape", py::arg("shape"), py::arg("hs"));
cls_XSControl_Utils.def("BinderShape", (TopoDS_Shape (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_Utils::BinderShape, "From a Transient, returns a Shape. In fact, recognizes ShapeBinder ShapeMapper and HShape", py::arg("tr"));
cls_XSControl_Utils.def("SeqLength", (Standard_Integer (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_Utils::SeqLength, "None", py::arg("list"));
cls_XSControl_Utils.def("SeqToArr", [](XSControl_Utils &self, const opencascade::handle<Standard_Transient> & a0) -> opencascade::handle<Standard_Transient> { return self.SeqToArr(a0); });
cls_XSControl_Utils.def("SeqToArr", (opencascade::handle<Standard_Transient> (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &, const Standard_Integer) const) &XSControl_Utils::SeqToArr, "None", py::arg("seq"), py::arg("first"));
cls_XSControl_Utils.def("ArrToSeq", (opencascade::handle<Standard_Transient> (XSControl_Utils::*)(const opencascade::handle<Standard_Transient> &) const) &XSControl_Utils::ArrToSeq, "None", py::arg("arr"));
cls_XSControl_Utils.def("SeqIntValue", (Standard_Integer (XSControl_Utils::*)(const opencascade::handle<TColStd_HSequenceOfInteger> &, const Standard_Integer) const) &XSControl_Utils::SeqIntValue, "None", py::arg("list"), py::arg("num"));

// CLASS: XSCONTROL_VARS
py::class_<XSControl_Vars, opencascade::handle<XSControl_Vars>, Standard_Transient> cls_XSControl_Vars(mod, "XSControl_Vars", "Defines a receptacle for externally defined variables, each one has a name");

// Constructors
cls_XSControl_Vars.def(py::init<>());

// Methods
cls_XSControl_Vars.def("Set", (void (XSControl_Vars::*)(const Standard_CString, const opencascade::handle<Standard_Transient> &)) &XSControl_Vars::Set, "None", py::arg("name"), py::arg("val"));
// cls_XSControl_Vars.def("Get", [](XSControl_Vars &self, Standard_CString & name){ opencascade::handle<Standard_Transient> rv = self.Get(name); return std::tuple<opencascade::handle<Standard_Transient>, Standard_CString &>(rv, name); }, "None", py::arg("name"));
// cls_XSControl_Vars.def("GetGeom", [](XSControl_Vars &self, Standard_CString & name){ opencascade::handle<Geom_Geometry> rv = self.GetGeom(name); return std::tuple<opencascade::handle<Geom_Geometry>, Standard_CString &>(rv, name); }, "None", py::arg("name"));
// cls_XSControl_Vars.def("GetCurve2d", [](XSControl_Vars &self, Standard_CString & name){ opencascade::handle<Geom2d_Curve> rv = self.GetCurve2d(name); return std::tuple<opencascade::handle<Geom2d_Curve>, Standard_CString &>(rv, name); }, "None", py::arg("name"));
// cls_XSControl_Vars.def("GetCurve", [](XSControl_Vars &self, Standard_CString & name){ opencascade::handle<Geom_Curve> rv = self.GetCurve(name); return std::tuple<opencascade::handle<Geom_Curve>, Standard_CString &>(rv, name); }, "None", py::arg("name"));
// cls_XSControl_Vars.def("GetSurface", [](XSControl_Vars &self, Standard_CString & name){ opencascade::handle<Geom_Surface> rv = self.GetSurface(name); return std::tuple<opencascade::handle<Geom_Surface>, Standard_CString &>(rv, name); }, "None", py::arg("name"));
cls_XSControl_Vars.def("SetPoint", (void (XSControl_Vars::*)(const Standard_CString, const gp_Pnt &)) &XSControl_Vars::SetPoint, "None", py::arg("name"), py::arg("val"));
cls_XSControl_Vars.def("SetPoint2d", (void (XSControl_Vars::*)(const Standard_CString, const gp_Pnt2d &)) &XSControl_Vars::SetPoint2d, "None", py::arg("name"), py::arg("val"));
// cls_XSControl_Vars.def("GetPoint", [](XSControl_Vars &self, Standard_CString & name, gp_Pnt & pnt){ Standard_Boolean rv = self.GetPoint(name, pnt); return std::tuple<Standard_Boolean, Standard_CString &>(rv, name); }, "None", py::arg("name"), py::arg("pnt"));
// cls_XSControl_Vars.def("GetPoint2d", [](XSControl_Vars &self, Standard_CString & name, gp_Pnt2d & pnt){ Standard_Boolean rv = self.GetPoint2d(name, pnt); return std::tuple<Standard_Boolean, Standard_CString &>(rv, name); }, "None", py::arg("name"), py::arg("pnt"));
cls_XSControl_Vars.def("SetShape", (void (XSControl_Vars::*)(const Standard_CString, const TopoDS_Shape &)) &XSControl_Vars::SetShape, "None", py::arg("name"), py::arg("val"));
// cls_XSControl_Vars.def("GetShape", [](XSControl_Vars &self, Standard_CString & name){ TopoDS_Shape rv = self.GetShape(name); return std::tuple<TopoDS_Shape, Standard_CString &>(rv, name); }, "None", py::arg("name"));
cls_XSControl_Vars.def_static("get_type_name_", (const char * (*)()) &XSControl_Vars::get_type_name, "None");
cls_XSControl_Vars.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &XSControl_Vars::get_type_descriptor, "None");
cls_XSControl_Vars.def("DynamicType", (const opencascade::handle<Standard_Type> & (XSControl_Vars::*)() const) &XSControl_Vars::DynamicType, "None");

// CLASS: XSCONTROL_WRITER
py::class_<XSControl_Writer> cls_XSControl_Writer(mod, "XSControl_Writer", "This class gives a simple way to create then write a Model compliant to a given norm, from a Shape The model can then be edited by tools by other appropriate tools");

// Constructors
cls_XSControl_Writer.def(py::init<>());
cls_XSControl_Writer.def(py::init<const Standard_CString>(), py::arg("norm"));
cls_XSControl_Writer.def(py::init<const opencascade::handle<XSControl_WorkSession> &>(), py::arg("WS"));
cls_XSControl_Writer.def(py::init<const opencascade::handle<XSControl_WorkSession> &, const Standard_Boolean>(), py::arg("WS"), py::arg("scratch"));

// Methods
// cls_XSControl_Writer.def_static("operator new_", (void * (*)(size_t)) &XSControl_Writer::operator new, "None", py::arg("theSize"));
// cls_XSControl_Writer.def_static("operator delete_", (void (*)(void *)) &XSControl_Writer::operator delete, "None", py::arg("theAddress"));
// cls_XSControl_Writer.def_static("operator new[]_", (void * (*)(size_t)) &XSControl_Writer::operator new[], "None", py::arg("theSize"));
// cls_XSControl_Writer.def_static("operator delete[]_", (void (*)(void *)) &XSControl_Writer::operator delete[], "None", py::arg("theAddress"));
// cls_XSControl_Writer.def_static("operator new_", (void * (*)(size_t, void *)) &XSControl_Writer::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_XSControl_Writer.def_static("operator delete_", (void (*)(void *, void *)) &XSControl_Writer::operator delete, "None", py::arg(""), py::arg(""));
cls_XSControl_Writer.def("SetNorm", (Standard_Boolean (XSControl_Writer::*)(const Standard_CString)) &XSControl_Writer::SetNorm, "Sets a specific norm to <me> Returns True if done, False if <norm> is not available", py::arg("norm"));
cls_XSControl_Writer.def("SetWS", [](XSControl_Writer &self, const opencascade::handle<XSControl_WorkSession> & a0) -> void { return self.SetWS(a0); });
cls_XSControl_Writer.def("SetWS", (void (XSControl_Writer::*)(const opencascade::handle<XSControl_WorkSession> &, const Standard_Boolean)) &XSControl_Writer::SetWS, "Sets a specific session to <me>", py::arg("WS"), py::arg("scratch"));
cls_XSControl_Writer.def("WS", (opencascade::handle<XSControl_WorkSession> (XSControl_Writer::*)() const) &XSControl_Writer::WS, "Returns the session used in <me>");
cls_XSControl_Writer.def("Model", [](XSControl_Writer &self) -> opencascade::handle<Interface_InterfaceModel> { return self.Model(); });
cls_XSControl_Writer.def("Model", (opencascade::handle<Interface_InterfaceModel> (XSControl_Writer::*)(const Standard_Boolean)) &XSControl_Writer::Model, "Returns the produced model. Produces a new one if not yet done or if <newone> is True This method allows for instance to edit product or header data before writing", py::arg("newone"));
cls_XSControl_Writer.def("TransferShape", [](XSControl_Writer &self, const TopoDS_Shape & a0) -> IFSelect_ReturnStatus { return self.TransferShape(a0); });
cls_XSControl_Writer.def("TransferShape", (IFSelect_ReturnStatus (XSControl_Writer::*)(const TopoDS_Shape &, const Standard_Integer)) &XSControl_Writer::TransferShape, "Transfers a Shape according to the mode", py::arg("sh"), py::arg("mode"));
cls_XSControl_Writer.def("WriteFile", (IFSelect_ReturnStatus (XSControl_Writer::*)(const Standard_CString)) &XSControl_Writer::WriteFile, "Writes the produced model", py::arg("filename"));
cls_XSControl_Writer.def("PrintStatsTransfer", [](XSControl_Writer &self, const Standard_Integer a0) -> void { return self.PrintStatsTransfer(a0); });
cls_XSControl_Writer.def("PrintStatsTransfer", (void (XSControl_Writer::*)(const Standard_Integer, const Standard_Integer) const) &XSControl_Writer::PrintStatsTransfer, "Prints Statistics about Transfer", py::arg("what"), py::arg("mode"));


}
