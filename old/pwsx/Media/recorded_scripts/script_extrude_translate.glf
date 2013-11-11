# Pointwise V17.0 Journal file - Thu Jun  6 23:41:08 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5

set _TMP(mode_5) [pw::Application begin Create]
  set _DM(1) [pw::GridEntity getByName "dom-316"]
  set _TMP(PW_5) [pw::FaceStructured createFromDomains [list $_DM(1)]]
  set _TMP(face_3) [lindex $_TMP(PW_5) 0]
  unset _TMP(PW_5)
  set _TMP(extStrBlock_1) [pw::BlockStructured create]
  $_TMP(extStrBlock_1) addFace $_TMP(face_3)
$_TMP(mode_5) end
unset _TMP(mode_5)
set _TMP(mode_6) [pw::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1)]]
  $_TMP(mode_6) setKeepFailingStep true
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  set _BL(1) [pw::GridEntity getByName "blk-84"]
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run 20
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {-1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run 1
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {-1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run -1
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {-1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run -2
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {-1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run 1
  set _DM(2) [pw::GridEntity getByName "dom-313"]
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {-1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_6) run -2
$_TMP(mode_6) abort
unset _TMP(mode_6)
$_TMP(extStrBlock_1) delete
unset _TMP(face_3)
unset _TMP(extStrBlock_1)




set _TMP(mode_7) [pw::Application begin Create]
  set _TMP(PW_6) [pw::FaceStructured createFromDomains [list $_DM(1)]]
  set _TMP(face_4) [lindex $_TMP(PW_6) 0]
  unset _TMP(PW_6)
  set _TMP(extStrBlock_1) [pw::BlockStructured create]
  $_TMP(extStrBlock_1) addFace $_TMP(face_4)
$_TMP(mode_7) end
unset _TMP(mode_7)
set _TMP(mode_8) [pw::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1)]]
  $_TMP(mode_8) setKeepFailingStep true
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {1 0 0}
  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance 0.005
  $_TMP(mode_8) run 2
$_TMP(mode_8) end
unset _TMP(mode_8)
unset _TMP(extStrBlock_1)
unset _TMP(face_4)
pw::Application markUndoLevel {Extrude, Translate}

set _BL(1) [pw::GridEntity getByName "blk-84"]
