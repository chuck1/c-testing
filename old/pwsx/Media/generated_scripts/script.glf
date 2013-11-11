package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5
pw::Application reset
pw::Application markUndoLevel {Journal Reset}

pw::Application clearModified

pw::Connector setCalculateDimensionMethod Spacing
pw::Connector setCalculateDimensionSpacing 1

set _TMP(mode_1) [pw::Application begin Create]
  set _TMP(PW_1) [pw::SegmentSpline create]
  $_TMP(PW_1) addPoint {0 0 0}
  $_TMP(PW_1) addPoint {10 0 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_1)
  unset _TMP(PW_1)
  $_TMP(con_1) calculateDimension
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_2) [pw::Application begin Create]
  set _TMP(PW_2) [pw::SegmentSpline create]
  $_TMP(PW_2) addPoint {0 0 10}
  $_TMP(PW_2) addPoint {10 0 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_2)
  unset _TMP(PW_2)
  $_TMP(con_1) calculateDimension
$_TMP(mode_2) end
unset _TMP(mode_2)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_3) [pw::Application begin Create]
  set _TMP(PW_3) [pw::SegmentSpline create]
  $_TMP(PW_3) addPoint {0 10 0}
  $_TMP(PW_3) addPoint {10 10 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_3)
  unset _TMP(PW_3)
  $_TMP(con_1) calculateDimension
$_TMP(mode_3) end
unset _TMP(mode_3)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_4) [pw::Application begin Create]
  set _TMP(PW_4) [pw::SegmentSpline create]
  $_TMP(PW_4) addPoint {0 10 10}
  $_TMP(PW_4) addPoint {10 10 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_4)
  unset _TMP(PW_4)
  $_TMP(con_1) calculateDimension
$_TMP(mode_4) end
unset _TMP(mode_4)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_5) [pw::Application begin Create]
  set _TMP(PW_5) [pw::SegmentSpline create]
  $_TMP(PW_5) addPoint {0 0 0}
  $_TMP(PW_5) addPoint {0 10 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_5)
  unset _TMP(PW_5)
  $_TMP(con_1) calculateDimension
$_TMP(mode_5) end
unset _TMP(mode_5)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_6) [pw::Application begin Create]
  set _TMP(PW_6) [pw::SegmentSpline create]
  $_TMP(PW_6) addPoint {0 0 10}
  $_TMP(PW_6) addPoint {0 10 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_6)
  unset _TMP(PW_6)
  $_TMP(con_1) calculateDimension
$_TMP(mode_6) end
unset _TMP(mode_6)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_7) [pw::Application begin Create]
  set _TMP(PW_7) [pw::SegmentSpline create]
  $_TMP(PW_7) addPoint {10 0 0}
  $_TMP(PW_7) addPoint {10 10 0}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_7)
  unset _TMP(PW_7)
  $_TMP(con_1) calculateDimension
$_TMP(mode_7) end
unset _TMP(mode_7)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_8) [pw::Application begin Create]
  set _TMP(PW_8) [pw::SegmentSpline create]
  $_TMP(PW_8) addPoint {10 0 10}
  $_TMP(PW_8) addPoint {10 10 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_8)
  unset _TMP(PW_8)
  $_TMP(con_1) calculateDimension
$_TMP(mode_8) end
unset _TMP(mode_8)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_9) [pw::Application begin Create]
  set _TMP(PW_9) [pw::SegmentSpline create]
  $_TMP(PW_9) addPoint {0 0 0}
  $_TMP(PW_9) addPoint {0 0 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_9)
  unset _TMP(PW_9)
  $_TMP(con_1) calculateDimension
$_TMP(mode_9) end
unset _TMP(mode_9)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_10) [pw::Application begin Create]
  set _TMP(PW_10) [pw::SegmentSpline create]
  $_TMP(PW_10) addPoint {0 10 0}
  $_TMP(PW_10) addPoint {0 10 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_10)
  unset _TMP(PW_10)
  $_TMP(con_1) calculateDimension
$_TMP(mode_10) end
unset _TMP(mode_10)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_11) [pw::Application begin Create]
  set _TMP(PW_11) [pw::SegmentSpline create]
  $_TMP(PW_11) addPoint {10 0 0}
  $_TMP(PW_11) addPoint {10 0 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_11)
  unset _TMP(PW_11)
  $_TMP(con_1) calculateDimension
$_TMP(mode_11) end
unset _TMP(mode_11)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)


set _TMP(mode_12) [pw::Application begin Create]
  set _TMP(PW_12) [pw::SegmentSpline create]
  $_TMP(PW_12) addPoint {10 10 0}
  $_TMP(PW_12) addPoint {10 10 10}
  set _TMP(con_1) [pw::Connector create]
  $_TMP(con_1) addSegment $_TMP(PW_12)
  unset _TMP(PW_12)
  $_TMP(con_1) calculateDimension
$_TMP(mode_12) end
unset _TMP(mode_12)
pw::Application markUndoLevel {Create 2 Point Connector}
unset _TMP(con_1)

set _CN(1) [pw::GridEntity getByName "con-1"]
set _CN(2) [pw::GridEntity getByName "con-2"]
set _CN(3) [pw::GridEntity getByName "con-3"]
set _CN(4) [pw::GridEntity getByName "con-4"]
set _CN(5) [pw::GridEntity getByName "con-5"]
set _CN(6) [pw::GridEntity getByName "con-6"]
set _CN(7) [pw::GridEntity getByName "con-7"]
set _CN(8) [pw::GridEntity getByName "con-8"]
set _CN(9) [pw::GridEntity getByName "con-9"]
set _CN(10) [pw::GridEntity getByName "con-10"]
set _CN(11) [pw::GridEntity getByName "con-11"]
set _CN(12) [pw::GridEntity getByName "con-12"]

set _TMP(mode_13) [pw::Application begin Modify [list $_CN(1)]]
  set _TMP(PW_13) [$_CN(1) getDistribution 1]
  $_TMP(PW_13) setBeginSpacing 0.1
  unset _TMP(PW_13)
$_TMP(mode_13) end
unset _TMP(mode_13)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_13) [pw::Application begin Modify [list $_CN(1)]]
  set _TMP(PW_14) [$_CN(1) getDistribution 1]
  $_TMP(PW_14) setEndSpacing 0.1
  unset _TMP(PW_14)
$_TMP(mode_13) end
unset _TMP(mode_13)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_14) [pw::Application begin Modify [list $_CN(2)]]
  set _TMP(PW_15) [$_CN(2) getDistribution 1]
  $_TMP(PW_15) setBeginSpacing 0.1
  unset _TMP(PW_15)
$_TMP(mode_14) end
unset _TMP(mode_14)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_14) [pw::Application begin Modify [list $_CN(2)]]
  set _TMP(PW_16) [$_CN(2) getDistribution 1]
  $_TMP(PW_16) setEndSpacing 0.1
  unset _TMP(PW_16)
$_TMP(mode_14) end
unset _TMP(mode_14)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_15) [pw::Application begin Modify [list $_CN(3)]]
  set _TMP(PW_17) [$_CN(3) getDistribution 1]
  $_TMP(PW_17) setBeginSpacing 0.1
  unset _TMP(PW_17)
$_TMP(mode_15) end
unset _TMP(mode_15)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_15) [pw::Application begin Modify [list $_CN(3)]]
  set _TMP(PW_18) [$_CN(3) getDistribution 1]
  $_TMP(PW_18) setEndSpacing 0.1
  unset _TMP(PW_18)
$_TMP(mode_15) end
unset _TMP(mode_15)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_16) [pw::Application begin Modify [list $_CN(4)]]
  set _TMP(PW_19) [$_CN(4) getDistribution 1]
  $_TMP(PW_19) setBeginSpacing 0.1
  unset _TMP(PW_19)
$_TMP(mode_16) end
unset _TMP(mode_16)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_16) [pw::Application begin Modify [list $_CN(4)]]
  set _TMP(PW_20) [$_CN(4) getDistribution 1]
  $_TMP(PW_20) setEndSpacing 0.1
  unset _TMP(PW_20)
$_TMP(mode_16) end
unset _TMP(mode_16)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_17) [pw::Application begin Modify [list $_CN(5)]]
  set _TMP(PW_21) [$_CN(5) getDistribution 1]
  $_TMP(PW_21) setBeginSpacing 0.1
  unset _TMP(PW_21)
$_TMP(mode_17) end
unset _TMP(mode_17)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_17) [pw::Application begin Modify [list $_CN(5)]]
  set _TMP(PW_22) [$_CN(5) getDistribution 1]
  $_TMP(PW_22) setEndSpacing 0.1
  unset _TMP(PW_22)
$_TMP(mode_17) end
unset _TMP(mode_17)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_18) [pw::Application begin Modify [list $_CN(6)]]
  set _TMP(PW_23) [$_CN(6) getDistribution 1]
  $_TMP(PW_23) setBeginSpacing 0.1
  unset _TMP(PW_23)
$_TMP(mode_18) end
unset _TMP(mode_18)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_18) [pw::Application begin Modify [list $_CN(6)]]
  set _TMP(PW_24) [$_CN(6) getDistribution 1]
  $_TMP(PW_24) setEndSpacing 0.1
  unset _TMP(PW_24)
$_TMP(mode_18) end
unset _TMP(mode_18)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_19) [pw::Application begin Modify [list $_CN(7)]]
  set _TMP(PW_25) [$_CN(7) getDistribution 1]
  $_TMP(PW_25) setBeginSpacing 0.1
  unset _TMP(PW_25)
$_TMP(mode_19) end
unset _TMP(mode_19)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_19) [pw::Application begin Modify [list $_CN(7)]]
  set _TMP(PW_26) [$_CN(7) getDistribution 1]
  $_TMP(PW_26) setEndSpacing 0.1
  unset _TMP(PW_26)
$_TMP(mode_19) end
unset _TMP(mode_19)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_20) [pw::Application begin Modify [list $_CN(8)]]
  set _TMP(PW_27) [$_CN(8) getDistribution 1]
  $_TMP(PW_27) setBeginSpacing 0.1
  unset _TMP(PW_27)
$_TMP(mode_20) end
unset _TMP(mode_20)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_20) [pw::Application begin Modify [list $_CN(8)]]
  set _TMP(PW_28) [$_CN(8) getDistribution 1]
  $_TMP(PW_28) setEndSpacing 0.1
  unset _TMP(PW_28)
$_TMP(mode_20) end
unset _TMP(mode_20)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_21) [pw::Application begin Modify [list $_CN(9)]]
  set _TMP(PW_29) [$_CN(9) getDistribution 1]
  $_TMP(PW_29) setBeginSpacing 0.1
  unset _TMP(PW_29)
$_TMP(mode_21) end
unset _TMP(mode_21)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_21) [pw::Application begin Modify [list $_CN(9)]]
  set _TMP(PW_30) [$_CN(9) getDistribution 1]
  $_TMP(PW_30) setEndSpacing 0.1
  unset _TMP(PW_30)
$_TMP(mode_21) end
unset _TMP(mode_21)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_22) [pw::Application begin Modify [list $_CN(10)]]
  set _TMP(PW_31) [$_CN(10) getDistribution 1]
  $_TMP(PW_31) setBeginSpacing 0.1
  unset _TMP(PW_31)
$_TMP(mode_22) end
unset _TMP(mode_22)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_22) [pw::Application begin Modify [list $_CN(10)]]
  set _TMP(PW_32) [$_CN(10) getDistribution 1]
  $_TMP(PW_32) setEndSpacing 0.1
  unset _TMP(PW_32)
$_TMP(mode_22) end
unset _TMP(mode_22)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_23) [pw::Application begin Modify [list $_CN(11)]]
  set _TMP(PW_33) [$_CN(11) getDistribution 1]
  $_TMP(PW_33) setBeginSpacing 0.1
  unset _TMP(PW_33)
$_TMP(mode_23) end
unset _TMP(mode_23)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_23) [pw::Application begin Modify [list $_CN(11)]]
  set _TMP(PW_34) [$_CN(11) getDistribution 1]
  $_TMP(PW_34) setEndSpacing 0.1
  unset _TMP(PW_34)
$_TMP(mode_23) end
unset _TMP(mode_23)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_24) [pw::Application begin Modify [list $_CN(12)]]
  set _TMP(PW_35) [$_CN(12) getDistribution 1]
  $_TMP(PW_35) setBeginSpacing 0.1
  unset _TMP(PW_35)
$_TMP(mode_24) end
unset _TMP(mode_24)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_24) [pw::Application begin Modify [list $_CN(12)]]
  set _TMP(PW_36) [$_CN(12) getDistribution 1]
  $_TMP(PW_36) setEndSpacing 0.1
  unset _TMP(PW_36)
$_TMP(mode_24) end
unset _TMP(mode_24)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(PW_37) [pw::DomainStructured createFromConnectors -reject _TMP(unusedCons) -solid [list $_CN(1) $_CN(3) $_CN(2) $_CN(4) $_CN(5) $_CN(7) $_CN(6) $_CN(8) $_CN(9) $_CN(11) $_CN(10) $_CN(12)]]
unset _TMP(unusedCons)
unset _TMP(PW_37)
pw::Application markUndoLevel {Assemble Blocks}
