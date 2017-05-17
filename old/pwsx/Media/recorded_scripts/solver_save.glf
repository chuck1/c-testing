# Pointwise V17.0 Journal file - Fri Jun  7 11:26:15 2013

package require PWI_Glyph 2.17.0

pw::Application setUndoMaximumLevels 5

pw::Application setCAESolver {ANSYS FLUENT} 3
pw::Application markUndoLevel {Select Solver}

pw::Application save {/nfs/stak/students/r/rymalc/cpp/pointwise_script/pw_files/pointwisefile.pw}

set _BL(1) [pw::GridEntity getByName "blk-1"]
set _BL(2) [pw::GridEntity getByName "blk-2"]
set _BL(3) [pw::GridEntity getByName "blk-3"]
set _BL(4) [pw::GridEntity getByName "blk-4"]
set _BL(5) [pw::GridEntity getByName "blk-5"]
set _BL(6) [pw::GridEntity getByName "blk-6"]
set _BL(7) [pw::GridEntity getByName "blk-7"]
set _BL(8) [pw::GridEntity getByName "blk-8"]
set _BL(9) [pw::GridEntity getByName "blk-9"]
set _BL(10) [pw::GridEntity getByName "blk-10"]
set _BL(11) [pw::GridEntity getByName "blk-11"]
set _BL(12) [pw::GridEntity getByName "blk-12"]
set _BL(13) [pw::GridEntity getByName "blk-13"]
set _BL(14) [pw::GridEntity getByName "blk-14"]
set _BL(15) [pw::GridEntity getByName "blk-15"]
set _BL(16) [pw::GridEntity getByName "blk-16"]
set _BL(17) [pw::GridEntity getByName "blk-17"]
set _BL(18) [pw::GridEntity getByName "blk-18"]
set _BL(19) [pw::GridEntity getByName "blk-19"]
set _BL(20) [pw::GridEntity getByName "blk-20"]
set _BL(21) [pw::GridEntity getByName "blk-21"]
set _BL(22) [pw::GridEntity getByName "blk-22"]
set _BL(23) [pw::GridEntity getByName "blk-23"]
set _BL(24) [pw::GridEntity getByName "blk-24"]
set _BL(25) [pw::GridEntity getByName "blk-25"]
set _BL(26) [pw::GridEntity getByName "blk-26"]
set _BL(27) [pw::GridEntity getByName "blk-27"]
set _BL(28) [pw::GridEntity getByName "blk-28"]
set _BL(29) [pw::GridEntity getByName "blk-29"]
set _BL(30) [pw::GridEntity getByName "blk-30"]
set _BL(31) [pw::GridEntity getByName "blk-31"]
set _BL(32) [pw::GridEntity getByName "blk-32"]
set _BL(33) [pw::GridEntity getByName "blk-33"]
set _BL(34) [pw::GridEntity getByName "blk-34"]
set _BL(35) [pw::GridEntity getByName "blk-35"]
set _BL(36) [pw::GridEntity getByName "blk-36"]
set _BL(37) [pw::GridEntity getByName "blk-37"]
set _BL(38) [pw::GridEntity getByName "blk-38"]
set _BL(39) [pw::GridEntity getByName "blk-39"]
set _BL(40) [pw::GridEntity getByName "blk-40"]
set _BL(41) [pw::GridEntity getByName "blk-41"]
set _BL(42) [pw::GridEntity getByName "blk-42"]
set _BL(43) [pw::GridEntity getByName "blk-43"]
set _BL(44) [pw::GridEntity getByName "blk-44"]
set _BL(45) [pw::GridEntity getByName "blk-45"]
set _BL(46) [pw::GridEntity getByName "blk-46"]
set _BL(47) [pw::GridEntity getByName "blk-47"]
set _BL(48) [pw::GridEntity getByName "blk-48"]
set _BL(49) [pw::GridEntity getByName "blk-49"]
set _BL(50) [pw::GridEntity getByName "blk-50"]
set _BL(51) [pw::GridEntity getByName "blk-51"]
set _BL(52) [pw::GridEntity getByName "blk-52"]
set _BL(53) [pw::GridEntity getByName "blk-53"]
set _BL(54) [pw::GridEntity getByName "blk-54"]
set _BL(55) [pw::GridEntity getByName "blk-55"]
set _BL(56) [pw::GridEntity getByName "blk-56"]
set _BL(57) [pw::GridEntity getByName "blk-57"]
set _BL(58) [pw::GridEntity getByName "blk-58"]
set _BL(59) [pw::GridEntity getByName "blk-59"]
set _BL(60) [pw::GridEntity getByName "blk-60"]
set _BL(61) [pw::GridEntity getByName "blk-61"]
set _BL(62) [pw::GridEntity getByName "blk-62"]
set _BL(63) [pw::GridEntity getByName "blk-63"]
set _BL(64) [pw::GridEntity getByName "blk-64"]
set _BL(65) [pw::GridEntity getByName "blk-65"]
set _BL(66) [pw::GridEntity getByName "blk-66"]
set _BL(67) [pw::GridEntity getByName "blk-67"]
set _BL(68) [pw::GridEntity getByName "blk-68"]
set _BL(69) [pw::GridEntity getByName "blk-69"]
set _BL(70) [pw::GridEntity getByName "blk-70"]
set _BL(71) [pw::GridEntity getByName "blk-71"]
set _BL(72) [pw::GridEntity getByName "blk-72"]
set _BL(73) [pw::GridEntity getByName "blk-73"]
set _BL(74) [pw::GridEntity getByName "blk-74"]
set _BL(75) [pw::GridEntity getByName "blk-75"]
set _BL(76) [pw::GridEntity getByName "blk-76"]
set _BL(77) [pw::GridEntity getByName "blk-77"]
set _BL(78) [pw::GridEntity getByName "blk-78"]
set _BL(79) [pw::GridEntity getByName "blk-79"]
set _BL(80) [pw::GridEntity getByName "blk-80"]
set _BL(81) [pw::GridEntity getByName "blk-81"]
set _BL(82) [pw::GridEntity getByName "blk-82"]
set _BL(83) [pw::GridEntity getByName "blk-83"]


set _TMP(mode_453) [pw::Application begin CaeExport [pw::Entity sort [list
 $_BL(1) $_BL(2) $_BL(3) $_BL(4) $_BL(5) $_BL(6) $_BL(7) $_BL(8) $_BL(9) $_BL(10) $_BL(11) $_BL(12) $_BL(13) $_BL(14) $_BL(15) $_BL(16) $_BL(17) $_BL(18) $_BL(19) $_BL(20) $_BL(21) $_BL(22) $_BL(23) $_BL(24) $_BL(25) $_BL(26) $_BL(27) $_BL(28) $_BL(29) $_BL(30) $_BL(31) $_BL(32) $_BL(33) $_BL(34) $_BL(35) $_BL(36) $_BL(37) $_BL(38) $_BL(39) $_BL(40) $_BL(41) $_BL(42) $_BL(43) $_BL(44) $_BL(45) $_BL(46) $_BL(47)]]]
  $_TMP(453) initialize -type CAE {/nfs/mohr/sva/work/rymalc/bin/sunshot/pointwise/script_generator/files/casefile.cas}
  if {![$_TMP(453) verify]} {
    error "Data verification failed"
  }
  $_TMP(453) write
$_TMP(453) end
unset _TMP(453)


set _TMP(mode_10) [pw::Application begin CaeExport [pw::Entity sort [list $_BL(1) $_BL(2) $_BL(3) $_BL(4) $_BL(5) $_BL(6) $_BL(7) $_BL(8) $_BL(9) $_BL(10) $_BL(11) $_BL(12) $_BL(13) $_BL(14) $_BL(15) $_BL(16) $_BL(17) $_BL(18) $_BL(19) $_BL(20) $_BL(21) $_BL(22) $_BL(23) $_BL(24) $_BL(25) $_BL(26) $_BL(27) $_BL(28) $_BL(29) $_BL(30) $_BL(31) $_BL(32) $_BL(33) $_BL(34) $_BL(35) $_BL(36) $_BL(37) $_BL(38) $_BL(39) $_BL(40) $_BL(41) $_BL(42) $_BL(43) $_BL(44) $_BL(45) $_BL(46) $_BL(47) $_BL(48) $_BL(49) $_BL(50) $_BL(51) $_BL(52) $_BL(53) $_BL(54) $_BL(55) $_BL(56) $_BL(57) $_BL(58) $_BL(59) $_BL(60) $_BL(61) $_BL(62) $_BL(63) $_BL(64) $_BL(65) $_BL(66) $_BL(67) $_BL(68) $_BL(69) $_BL(70) $_BL(71) $_BL(72) $_BL(73) $_BL(74) $_BL(75) $_BL(76) $_BL(77) $_BL(78) $_BL(79) $_BL(80) $_BL(81) $_BL(82) $_BL(83)]]]
  $_TMP(mode_10) initialize -type CAE {/nfs/stak/students/r/rymalc/cpp/pointwise_script/pw_files/casefile.cas}
  if {![$_TMP(mode_10) verify]} {
    error "Data verification failed"
  }
  $_TMP(mode_10) write
$_TMP(mode_10) end
unset _TMP(mode_10)
