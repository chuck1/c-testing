# Pointwise V17.0 Journal file - Wed Jun 12 17:45:25 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5
pw::Application reset
pw::Application markUndoLevel {Journal Reset}

pw::Application clearModified

set _TMP(mode_1) [pw::Application begin Create]
  set _TMP(PW_1) [pw::SegmentSpline create]
  $_TMP(PW_1) addPoint {0 0 0}
  $_TMP(PW_1) addPoint {5 0 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_1)
  unset _TMP(PW_1)
  $_TMP(con_1) calculateDimension
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_2) [pw::Application begin Create]
  set _TMP(PW_2) [pw::SegmentSpline create]
  $_TMP(PW_2) delete
  unset _TMP(PW_2)
$_TMP(mode_2) abort
unset _TMP(mode_2)
unset _TMP(con_1)
set _CN(1) [pw::GridEntity getByName "con-1"]
set _TMP(PW_3) [pw::Collection create]
$_TMP(PW_3) set [list $_CN(1)]
$_TMP(PW_3) do setDimension 10
$_TMP(PW_3) delete
unset _TMP(PW_3)
pw::Application markUndoLevel {Dimension}

set _TMP(mode_3) [pw::Application begin Create]
  set _TMP(PW_4) [pw::Edge createFromConnectors [list $_CN(1)]]
  set _TMP(edge_1) [lindex $_TMP(PW_4) 0]
  unset _TMP(PW_4)
  set _TMP(dom_1) [pw::DomainStructured create]
  $_TMP(dom_1) addEdge $_TMP(edge_1)
$_TMP(mode_3) end
unset _TMP(mode_3)
set _TMP(mode_4) [pw::Application begin ExtrusionSolver [list $_TMP(dom_1)]]
  $_TMP(mode_4) setKeepFailingStep true
  $_TMP(dom_1) setExtrusionSolverAttribute Mode Rotate
  set _DM(1) [pw::GridEntity getByName "dom-1"]
  $_TMP(dom_1) setExtrusionSolverAttribute RotateAxisStart {0 0 0}
  $_TMP(dom_1) setExtrusionSolverAttribute RotateAxisEnd [pwu::Vector3 add {0 0 0} {1 0 0}]
  $_TMP(dom_1) setExtrusionSolverAttribute RotateAxisStart {0 0 0}
  $_TMP(dom_1) setExtrusionSolverAttribute RotateAxisEnd [pwu::Vector3 add {0 0 0} {0 0 1}]
  $_TMP(dom_1) setExtrusionSolverAttribute RotateAngle 180
  $_TMP(mode_4) run 10
  pw::Display resetView -Z
$_TMP(mode_4) end
unset _TMP(mode_4)
unset _TMP(dom_1)
unset _TMP(edge_1)
pw::Application markUndoLevel {Extrude, Rotate}

set _TMP(mode_5) [pw::Application begin Create]
  set _TMP(PW_5) [pw::SegmentSpline create]
  $_TMP(PW_5) addPoint {5 0 0}
  $_TMP(PW_5) addPoint {6 0 0}
  set _TMP(con_2) [pw::Connector create]
  $_TMP(con_2) addSegment $_TMP(PW_5)
  unset _TMP(PW_5)
  $_TMP(con_2) calculateDimension
$_TMP(mode_5) end
unset _TMP(mode_5)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_6) [pw::Application begin Create]
  set _TMP(PW_6) [pw::SegmentSpline create]
  $_TMP(PW_6) addPoint {6 0 0}
  $_TMP(PW_6) addPoint {6 5 0}
  unset _TMP(con_2)
  set _TMP(con_3) [pw::Connector create]
  $_TMP(con_3) addSegment $_TMP(PW_6)
  unset _TMP(PW_6)
  $_TMP(con_3) calculateDimension
$_TMP(mode_6) end
unset _TMP(mode_6)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_7) [pw::Application begin Create]
  set _TMP(PW_7) [pw::SegmentSpline create]
  $_TMP(PW_7) delete
  unset _TMP(PW_7)
$_TMP(mode_7) abort
unset _TMP(mode_7)
unset _TMP(con_3)
set _CN(2) [pw::GridEntity getByName "con-6"]
pw::Entity delete [list $_CN(2)]
pw::Application markUndoLevel {Delete}

set _TMP(mode_8) [pw::Application begin Create]
  set _TMP(PW_8) [pw::SegmentSpline create]
  $_TMP(PW_8) addPoint {6 6 0}
  $_TMP(PW_8) addPoint {6 0 0}
  set _TMP(con_4) [pw::Connector create]
  $_TMP(con_4) addSegment $_TMP(PW_8)
  unset _TMP(PW_8)
  $_TMP(con_4) calculateDimension
$_TMP(mode_8) end
unset _TMP(mode_8)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_9) [pw::Application begin Create]
  set _TMP(PW_9) [pw::SegmentSpline create]
  $_TMP(PW_9) addPoint {6 6 0}
  $_TMP(PW_9) addPoint {-6 6 0}
  unset _TMP(con_4)
  set _TMP(con_5) [pw::Connector create]
  $_TMP(con_5) addSegment $_TMP(PW_9)
  unset _TMP(PW_9)
  $_TMP(con_5) calculateDimension
$_TMP(mode_9) end
unset _TMP(mode_9)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_10) [pw::Application begin Create]
  set _TMP(PW_10) [pw::SegmentSpline create]
  $_TMP(PW_10) addPoint {-6 6 0}
  $_TMP(PW_10) addPoint {-6 0 0}
  unset _TMP(con_5)
  set _TMP(con_6) [pw::Connector create]
  $_TMP(con_6) addSegment $_TMP(PW_10)
  unset _TMP(PW_10)
  $_TMP(con_6) calculateDimension
$_TMP(mode_10) end
unset _TMP(mode_10)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_10) [pw::Application begin Create]
  set _TMP(PW_11) [pw::SegmentSpline create]
  $_TMP(PW_11) addPoint {-6 0 0}
  $_TMP(PW_11) addPoint {-5 0 0}
  unset _TMP(con_6)
  set _TMP(con_7) [pw::Connector create]
  $_TMP(con_7) addSegment $_TMP(PW_11)
  unset _TMP(PW_11)
  $_TMP(con_7) calculateDimension
$_TMP(mode_10) end
unset _TMP(mode_10)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_10) [pw::Application begin Create]
  set _TMP(PW_12) [pw::SegmentSpline create]
  $_TMP(PW_12) delete
  unset _TMP(PW_12)
$_TMP(mode_10) abort
unset _TMP(mode_10)
unset _TMP(con_7)
set _CN(3) [pw::GridEntity getByName "con-8"]
set _CN(4) [pw::GridEntity getByName "con-9"]
set _CN(5) [pw::GridEntity getByName "con-6"]
set _CN(6) [pw::GridEntity getByName "con-7"]
set _CN(7) [pw::GridEntity getByName "con-5"]
set _TMP(PW_13) [pw::Collection create]
$_TMP(PW_13) set [list $_CN(3) $_CN(4) $_CN(5) $_CN(6) $_CN(7)]
$_TMP(PW_13) do setDimension 10
$_TMP(PW_13) delete
unset _TMP(PW_13)
pw::Application markUndoLevel {Dimension}

set _TMP(PW_14) [pw::Collection create]
$_TMP(PW_14) set [list $_CN(4) $_CN(7)]
$_TMP(PW_14) do setDimension 4
$_TMP(PW_14) delete
unset _TMP(PW_14)
pw::Application markUndoLevel {Dimension}

set _CN(8) [pw::GridEntity getByName "con-2"]
set _CN(9) [pw::GridEntity getByName "con-4"]
set _TMP(PW_15) [pw::DomainStructured createFromConnectors -reject _TMP(unusedCons) -solid [list $_CN(3) $_CN(4) $_CN(5) $_CN(8) $_CN(9) $_CN(6) $_CN(7)]]
unset _TMP(unusedCons)
unset _TMP(PW_15)
pw::Application markUndoLevel {Assemble Domains}

pw::Application setGridPreference Unstructured
set _TMP(PW_16) [pw::DomainUnstructured createFromConnectors -reject _TMP(unusedCons)  [list $_CN(3) $_CN(4) $_CN(5) $_CN(8) $_CN(9) $_CN(6) $_CN(7)]]
unset _TMP(unusedCons)
unset _TMP(PW_16)
pw::Application markUndoLevel {Assemble Domains}

set _TMP(mode_10) [pw::Application begin Create]
  set _DM(2) [pw::GridEntity getByName "dom-2"]
  set _TMP(PW_17) [pw::FaceUnstructured createFromDomains [list $_DM(2)]]
  set _TMP(face_1) [lindex $_TMP(PW_17) 0]
  unset _TMP(PW_17)
  set _TMP(PW_18) [pw::FaceStructured createFromDomains [list $_DM(1)]]
  set _TMP(face_2) [lindex $_TMP(PW_18) 0]
  unset _TMP(PW_18)
  set _TMP(extStrBlock_1) [pw::BlockStructured create]
  $_TMP(extStrBlock_1) addFace $_TMP(face_2)
  set _TMP(extExtBlock_1) [pw::BlockExtruded create]
  $_TMP(extExtBlock_1) addFace $_TMP(face_1)
$_TMP(mode_10) end
unset _TMP(mode_10)
set _TMP(mode_10) [pw::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1) $_TMP(extExtBlock_1)]]
  $_TMP(mode_10) setKeepFailingStep true
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extExtBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  $_TMP(extExtBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  set _BL(1) [pw::GridEntity getByName "blk-1"]
  set _BL(2) [pw::GridEntity getByName "blk-2"]
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {0 0 1}
  $_TMP(extExtBlock_1) setExtrusionSolverAttribute TranslateDirection {0 0 1}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 10
  $_TMP(extExtBlock_1) setExtrusionSolverAttribute TranslateDistance 10
  $_TMP(mode_10) run 10
$_TMP(mode_10) end
unset _TMP(mode_10)
unset _TMP(extExtBlock_1)
unset _TMP(extStrBlock_1)
unset _TMP(face_1)
unset _TMP(face_2)
pw::Application markUndoLevel {Extrude, Translate}

pw::Application setCAESolver {ANSYS FLUENT} 3
pw::Application markUndoLevel {Select Solver}

set _TMP(mode_10) [pw::Application begin CaeExport [pw::Entity sort [list $_BL(1) $_BL(2)]]]
  $_TMP(mode_10) initialize -type CAE {/nfs/stak/students/r/rymalc/casefile_test_1.cas}
  if {![$_TMP(mode_10) verify]} {
    error "Data verification failed"
  }
  $_TMP(mode_10) write
$_TMP(mode_10) end
unset _TMP(mode_10)
set _TMP(PW_19) [pw::VolumeCondition create]
pw::Application markUndoLevel {Create VC}

set _TMP(PW_20) [pw::VolumeCondition create]
pw::Application markUndoLevel {Create VC}

$_TMP(PW_19) setPhysicalType {Fluid}
pw::Application markUndoLevel {Change VC Type}

$_TMP(PW_20) setPhysicalType {Solid}
pw::Application markUndoLevel {Change VC Type}

$_TMP(PW_19) apply [list $_BL(2)]
pw::Application markUndoLevel {Set VC}

$_TMP(PW_20) apply [list $_BL(1)]
pw::Application markUndoLevel {Set VC}

unset _TMP(PW_19)
unset _TMP(PW_20)
set _TMP(mode_10) [pw::Application begin CaeExport [pw::Entity sort [list $_BL(1) $_BL(2)]]]
  $_TMP(mode_10) initialize -type CAE {/nfs/stak/students/r/rymalc/casefile_test_2.cas}
  if {![$_TMP(mode_10) verify]} {
    error "Data verification failed"
  }
  $_TMP(mode_10) write
$_TMP(mode_10) end
unset _TMP(mode_10)
set _DM(3) [pw::GridEntity getByName "dom-4"]
set _TMP(PW_21) [pw::BoundaryCondition getByName "Unspecified"]
set _DM(4) [pw::GridEntity getByName "dom-3"]
set _DM(5) [pw::GridEntity getByName "dom-5"]
set _DM(6) [pw::GridEntity getByName "dom-6"]
set _DM(7) [pw::GridEntity getByName "dom-7"]
set _DM(8) [pw::GridEntity getByName "dom-9"]
set _DM(9) [pw::GridEntity getByName "dom-10"]
set _DM(10) [pw::GridEntity getByName "dom-11"]
set _DM(11) [pw::GridEntity getByName "dom-12"]
set _DM(12) [pw::GridEntity getByName "dom-13"]
set _DM(13) [pw::GridEntity getByName "dom-14"]
set _TMP(PW_22) [pw::BoundaryCondition create]
pw::Application markUndoLevel {Create BC}

set _TMP(PW_23) [pw::BoundaryCondition getByName "bc-2"]
unset _TMP(PW_22)
$_TMP(PW_23) setPhysicalType {Interface}
pw::Application markUndoLevel {Change BC Type}

$_TMP(PW_23) apply [list [list $_BL(1) $_DM(3) Opposite] [list $_BL(2) $_DM(3) Same]]
pw::Application markUndoLevel {Set BC}

unset _TMP(PW_21)
unset _TMP(PW_23)
set _TMP(mode_10) [pw::Application begin CaeExport [pw::Entity sort [list $_BL(1) $_BL(2)]]]
  $_TMP(mode_10) initialize -type CAE {/nfs/stak/students/r/rymalc/casefile_test_3.cas}
  if {![$_TMP(mode_10) verify]} {
    error "Data verification failed"
  }
  $_TMP(mode_10) write
$_TMP(mode_10) abort
unset _TMP(mode_10)
set _TMP(mode_10) [pw::Application begin CaeExport [pw::Entity sort [list $_BL(1) $_BL(2)]]]
  $_TMP(mode_10) initialize -type CAE {/nfs/stak/students/r/rymalc/casefile_test_3.cas}
  if {![$_TMP(mode_10) verify]} {
    error "Data verification failed"
  }
  $_TMP(mode_10) write
$_TMP(mode_10) abort
unset _TMP(mode_10)
set _TMP(PW_24) [pw::BoundaryCondition getByName "Unspecified"]
set _TMP(PW_25) [pw::BoundaryCondition getByName "bc-2"]
$_TMP(PW_24) apply [list [list $_BL(2) $_DM(3) Same]]
pw::Application markUndoLevel {Set BC}

$_TMP(PW_24) apply [list [list $_BL(2) $_DM(3) Same]]
pw::Application markUndoLevel {Set BC}

unset _TMP(PW_24)
unset _TMP(PW_25)
