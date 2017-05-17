# Pointwise V17.0 Journal file - Sun Jun 16 23:19:42 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5
pw::Application reset
pw::Application markUndoLevel {Journal Reset}

pw::Application clearModified

pw::Connector setDefault Dimension 10
set _TMP(mode_3) [pw::Application begin Create]
  set _TMP(PW_3) [pw::SegmentSpline create]
  $_TMP(PW_3) addPoint {10 0 0}
  $_TMP(PW_3) addPoint {0 0 0}
  set _TMP(con_2) [pw::Connector create]
  $_TMP(con_2) addSegment $_TMP(PW_3)
  unset _TMP(PW_3)
  $_TMP(con_2) calculateDimension
$_TMP(mode_3) end
unset _TMP(mode_3)
pw::Application markUndoLevel {Create 2 Point Connector}

set _TMP(mode_4) [pw::Application begin Create]
  set _TMP(PW_4) [pw::SegmentSpline create]
  $_TMP(PW_4) delete
  unset _TMP(PW_4)
$_TMP(mode_4) abort
unset _TMP(mode_4)
unset _TMP(con_2)
set _CN(1) [pw::GridEntity getByName "con-1"]
set _TMP(mode_5) [pw::Application begin Modify [list $_CN(1)]]
  set _TMP(PW_5) [$_CN(1) getDistribution 1]
  $_TMP(PW_5) setEndSpacing 20
  unset _TMP(PW_5)
$_TMP(mode_5) end
unset _TMP(mode_5)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_6) [pw::Application begin Modify [list $_CN(1)]]
  set _TMP(PW_6) [$_CN(1) getDistribution 1]
  $_TMP(PW_6) setBeginSpacing 40
  unset _TMP(PW_6)
$_TMP(mode_6) end
unset _TMP(mode_6)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(mode_7) [pw::Application begin Modify [list $_CN(1)]]
  set _TMP(PW_7) [$_CN(1) getDistribution 1]
  $_TMP(PW_7) setEndSpacing 12
  unset _TMP(PW_7)
$_TMP(mode_7) end
unset _TMP(mode_7)
pw::Application markUndoLevel {Change Spacing(s)}

set _TMP(PW_8) [pw::Collection create]
$_TMP(PW_8) set [list $_CN(1)]
$_TMP(PW_8) do setRenderAttribute PointMode All
$_TMP(PW_8) delete
unset _TMP(PW_8)
pw::Application markUndoLevel {Modify Entity Display}

