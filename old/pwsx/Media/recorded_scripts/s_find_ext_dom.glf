# Pointwise V17.0 Journal file - Fri Jun  7 10:34:59 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5
pw::Application reset
pw::Application markUndoLevel {Journal Reset}

pw::Application clearModified

set _TMP(mode_2) [pw::Application begin Create]
  set _TMP(PW_2) [pw::SegmentSpline create]
  $_TMP(PW_2) addPoint {0 0 0}
  $_TMP(PW_2) addPoint {10 0 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_2)
  unset _TMP(PW_2)
  $_TMP(con_1) calculateDimension
$_TMP(mode_2) end
unset _TMP(mode_2)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_3) [pw::Application begin Create]
  set _TMP(PW_3) [pw::SegmentSpline create]
  $_TMP(PW_3) addPoint {10 0 0}
  $_TMP(PW_3) addPoint {10 10 0}
  unset _TMP(con_1)
  set _TMP(con_2) [pw::Connector create]
  $_TMP(con_2) addSegment $_TMP(PW_3)
  unset _TMP(PW_3)
  $_TMP(con_2) calculateDimension
$_TMP(mode_3) end
unset _TMP(mode_3)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_4) [pw::Application begin Create]
  set _TMP(PW_4) [pw::SegmentSpline create]
  $_TMP(PW_4) addPoint {10 10 0}
  $_TMP(PW_4) addPoint {0 10 0}
  unset _TMP(con_2)
  set _TMP(con_3) [pw::Connector create]
  $_TMP(con_3) addSegment $_TMP(PW_4)
  unset _TMP(PW_4)
  $_TMP(con_3) calculateDimension
$_TMP(mode_4) end
unset _TMP(mode_4)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_5) [pw::Application begin Create]
  set _TMP(PW_5) [pw::SegmentSpline create]
  $_TMP(PW_5) addPoint {0 10 0}
  $_TMP(PW_5) addPoint {0 0 0}
  unset _TMP(con_3)
  set _TMP(con_4) [pw::Connector create]
  $_TMP(con_4) addSegment $_TMP(PW_5)
  unset _TMP(PW_5)
  $_TMP(con_4) calculateDimension
$_TMP(mode_5) end
unset _TMP(mode_5)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_6) [pw::Application begin Create]
  set _TMP(PW_6) [pw::SegmentSpline create]
  $_TMP(PW_6) delete
  unset _TMP(PW_6)
$_TMP(mode_6) abort
unset _TMP(mode_6)
unset _TMP(con_4)
set _CN(1) [pw::GridEntity getByName "con-3"]
set _CN(2) [pw::GridEntity getByName "con-4"]
set _CN(3) [pw::GridEntity getByName "con-1"]
set _CN(4) [pw::GridEntity getByName "con-2"]
set _TMP(PW_7) [pw::Collection create]
$_TMP(PW_7) set [list $_CN(1) $_CN(2) $_CN(3) $_CN(4)]
$_TMP(PW_7) do setDimension 10
$_TMP(PW_7) delete
unset _TMP(PW_7)
pw::Application markUndoLevel {Dimension}

set _TMP(PW_8) [pw::DomainStructured createFromConnectors -reject _TMP(unusedCons) -solid [list $_CN(1) $_CN(2) $_CN(3) $_CN(4)]]
unset _TMP(unusedCons)
unset _TMP(PW_8)
pw::Application markUndoLevel {Assemble Domains}

set _TMP(mode_7) [pw::Application begin Create]
  set _DM(1) [pw::GridEntity getByName "dom-1"]
  set _TMP(PW_9) [pw::FaceStructured createFromDomains [list $_DM(1)]]
  set _TMP(face_1) [lindex $_TMP(PW_9) 0]
  unset _TMP(PW_9)
  set _TMP(extStrBlock_1) [pw::BlockStructured create]
  $_TMP(extStrBlock_1) addFace $_TMP(face_1)
$_TMP(mode_7) end
unset _TMP(mode_7)
set _TMP(mode_8) [pw::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1)]]
  $_TMP(mode_8) setKeepFailingStep true
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  set _BL(1) [pw::GridEntity getByName "blk-1"]
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {0 0 1}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 1
  $_TMP(mode_8) run 10
  $_TMP(mode_8) run Restart
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {0 0 1}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 10
  $_TMP(mode_8) run 10
$_TMP(mode_8) end
unset _TMP(mode_8)
unset _TMP(extStrBlock_1)
unset _TMP(face_1)
pw::Application markUndoLevel {Extrude, Translate}

set _TMP(mode_9) [pw::Application begin Create]
  set _DM(2) [pw::GridEntity getByName "dom-3"]
  set _TMP(PW_10) [pw::FaceStructured createFromDomains [list $_DM(2)]]
  set _TMP(face_2) [lindex $_TMP(PW_10) 0]
  unset _TMP(PW_10)
  set _TMP(extStrBlock_1) [pw::BlockStructured create]
  $_TMP(extStrBlock_1) addFace $_TMP(face_2)
$_TMP(mode_9) end
unset _TMP(mode_9)
set _TMP(mode_10) [pw::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1)]]
  $_TMP(mode_10) setKeepFailingStep true
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  set _BL(2) [pw::GridEntity getByName "blk-2"]
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 10
  $_TMP(mode_10) run 10
$_TMP(mode_10) end
unset _TMP(mode_10)
unset _TMP(extStrBlock_1)
unset _TMP(face_2)
pw::Application markUndoLevel {Extrude, Translate}

set _TMP(PW_11) [pw::BoundaryCondition getByName "Unspecified"]
set _DM(3) [pw::GridEntity getByName "dom-2"]
set _DM(4) [pw::GridEntity getByName "dom-4"]
set _DM(5) [pw::GridEntity getByName "dom-5"]
set _DM(6) [pw::GridEntity getByName "dom-6"]
set _DM(7) [pw::GridEntity getByName "dom-7"]
set _DM(8) [pw::GridEntity getByName "dom-8"]
set _DM(9) [pw::GridEntity getByName "dom-9"]
set _DM(10) [pw::GridEntity getByName "dom-10"]
set _DM(11) [pw::GridEntity getByName "dom-11"]
set _TMP(PW_12) [pw::BoundaryCondition create]
pw::Application markUndoLevel {Create BC}

set _TMP(PW_13) [pw::BoundaryCondition getByName "bc-2"]
unset _TMP(PW_12)
unset _TMP(PW_11)
unset _TMP(PW_13)
pw::Application reset -keep [list Clipboard]
pw::Display resetView -Z
pw::Display resetRotationPoint
pw::Application markUndoLevel {New}

pw::Application clearModified
