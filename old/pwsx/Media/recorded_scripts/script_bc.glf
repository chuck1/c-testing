# Pointwise V17.0 Journal file - Wed Jun  5 21:30:49 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5

set _TMP(PW_3) [pw::BoundaryCondition getByName "Unspecified"]
set _DM(1) [pw::GridEntity getByName "dom-1"]
set _DM(2) [pw::GridEntity getByName "dom-2"]
set _DM(3) [pw::GridEntity getByName "dom-3"]
set _DM(4) [pw::GridEntity getByName "dom-4"]
set _DM(5) [pw::GridEntity getByName "dom-5"]
set _DM(6) [pw::GridEntity getByName "dom-6"]
set _BL(1) [pw::GridEntity getByName "blk-1"]


set _TMP(PW_4) [pw::BoundaryCondition create]
  pw::Application markUndoLevel {Create BC}
unset _TMP(PW_4)

set _TMP(PW_5) [pw::BoundaryCondition getByName "bc-2"]
  $_TMP(PW_5) setName "inflow"
  pw::Application markUndoLevel {Name BC}

  $_TMP(PW_5) setPhysicalType {Inflow}
  pw::Application markUndoLevel {Change BC Type}

  $_TMP(PW_5) apply [list [list $_BL(1) $_DM(3)]]
  pw::Application markUndoLevel {Set BC}
unset _TMP(PW_5)


unset _TMP(PW_3)

set _TMP(PW_6) [pw::BoundaryCondition getByName "Unspecified"]
unset _TMP(PW_6)
set _TMP(PW_7) [pw::BoundaryCondition getByName "inflow"]
unset _TMP(PW_7)

set _TMP(PW_8) [pw::VolumeCondition create]
  pw::Application markUndoLevel {Create VC}

  $_TMP(PW_8) setName "fluid"
  pw::Application markUndoLevel {Name VC}

  $_TMP(PW_8) setPhysicalType {Fluid}
  pw::Application markUndoLevel {Change VC Type}

  $_TMP(PW_8) apply [list $_BL(1)]
  pw::Application markUndoLevel {Set VC}

unset _TMP(PW_8)
