# Pointwise V17.0 Journal file - Sat Jun  8 11:47:48 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5

set _DM(1349) [pw::GridEntity getByName "dom-2136"]
set _DM(1350) [pw::GridEntity getByName "dom-2137"]
set _DM(1358) [pw::GridEntity getByName "dom-2153"]


set _TMP(PW_9) [pw::BoundaryCondition getByName "Unspecified"]
set _TMP(PW_10) [pw::BoundaryCondition getByName "inlet"]
set _TMP(PW_11) [pw::BoundaryCondition getByName "outlet"]
set _TMP(PW_12) [pw::BoundaryCondition getByName "symmetry"]


set _DM(1359) [pw::GridEntity getByName "dom-1"]
set _DM(1360) [pw::GridEntity getByName "dom-2"]
set _DM(1363) [pw::GridEntity getByName "dom-5"]
set _BL(522) [pw::GridEntity getByName "blk-573"]
set _BL(523) [pw::GridEntity getByName "blk-586"]
set _BL(524) [pw::GridEntity getByName "blk-587"]


set _TMP(PW_14) [pw::BoundaryCondition create]
  pw::Application markUndoLevel {Create BC}

  $_TMP(PW_14) setName "interior wall"
  pw::Application markUndoLevel {Name BC}

  $_TMP(PW_14) setPhysicalType {Wall}
  pw::Application markUndoLevel {Change BC Type}

  $_TMP(PW_14) apply [list [list $_BL(17) $_DM(1) Same] [list $_BL(523) $_DM(1) Opposite]]
  pw::Application markUndoLevel {Set BC}

unset _TMP(PW_14)

