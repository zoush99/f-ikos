; ModuleID = '/tmp/type-f11534.ll'
source_filename = "/tmp/type-f11534.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.BSS4 = type <{ [4 x i8] }>
%structmain_location_td_ = type <{ [8 x i64], [6 x i8*], [16 x i8] }>
%struct_fikos_1_ = type <{ [100 x i8] }>

@.C310_fikos_assert_ = internal constant i64 0
@.C309_fikos_assert_ = internal constant i32 0
@.C341_fikos_print_error_ = internal constant i32 14
@.C338_fikos_print_error_ = internal constant [18 x i8] c"Assertion failed: "
@.C309_fikos_print_error_ = internal constant i32 0
@.C310_fikos_print_error_ = internal constant i64 0
@.C335_fikos_print_error_ = internal constant i32 6
@.C332_fikos_print_error_ = internal constant [8 x i8] c"type.f90"
@.C334_fikos_print_error_ = internal constant i32 21
@.BSS4 = internal global %struct.BSS4 zeroinitializer, align 32
@.C340_MAIN_ = internal constant [4 x i8] c"fail"
@.C339_MAIN_ = internal constant i32 3
@.C309_MAIN_ = internal constant i32 0
@main_location_td_ = global %structmain_location_td_ <{ [8 x i64] [i64 43, i64 33, i64 0, i64 4, i64 0, i64 0, i64 0, i64 0], [6 x i8*] [i8* null, i8* bitcast (%structmain_location_td_* @main_location_td_ to i8*), i8* null, i8* null, i8* null, i8* null], [16 x i8] c"main$location$td" }>
@_fikos_1_ = common global %struct_fikos_1_ zeroinitializer, align 64

; Function Attrs: noinline
define float @fikos_() #0 {
.L.entry:
  ret float undef
}

define void @fikos_assert_(i64* %condition, i64* %message, i64 %.U0002.arg) !dbg !5 {
L.entry:
  %.U0002.addr = alloca i64, align 8
  store i64 %.U0002.arg, i64* %.U0002.addr, align 8
  br label %L.LB2_344

L.LB2_344:                                        ; preds = %L.entry
  %0 = bitcast i64* %condition to i32*, !dbg !11
  %1 = load i32, i32* %0, align 4, !dbg !11
  %2 = and i32 %1, 1, !dbg !11
  %3 = icmp ne i32 %2, 0, !dbg !11
  br i1 %3, label %L.LB2_339, label %L.LB2_357, !dbg !11

L.LB2_357:                                        ; preds = %L.LB2_344
  %4 = bitcast %struct_fikos_1_* @_fikos_1_ to i8*, !dbg !12
  %5 = bitcast i64* %message to i8*, !dbg !12
  %6 = load i64, i64* %.U0002.addr, align 8, !dbg !12
  %7 = bitcast i32 (...)* @f90_str_copy_klen to i32 (i32, i8*, i64, i8*, i64, ...)*, !dbg !12
  %8 = call i32 (i32, i8*, i64, i8*, i64, ...) %7(i32 1, i8* %4, i64 100, i8* %5, i64 %6), !dbg !12
  call void @fikos_print_error_(), !dbg !13
  %9 = bitcast i32* @.C309_fikos_assert_ to i8*, !dbg !14
  %10 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !14
  call void (i8*, i8*, i64, ...) %10(i8* %9, i8* null, i64 0), !dbg !14
  br label %L.LB2_339

L.LB2_339:                                        ; preds = %L.LB2_357, %L.LB2_344
  ret void, !dbg !15
}

define void @fikos_print_error_() !dbg !16 {
L.entry:
  %z__io_337 = alloca i32, align 4
  br label %L.LB3_345

L.LB3_345:                                        ; preds = %L.entry
  %0 = bitcast i32* @.C334_fikos_print_error_ to i8*, !dbg !19
  %1 = bitcast [8 x i8]* @.C332_fikos_print_error_ to i8*, !dbg !19
  %2 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !19
  call void (i8*, i8*, i64, ...) %2(i8* %0, i8* %1, i64 8), !dbg !19
  %3 = bitcast i32* @.C335_fikos_print_error_ to i8*, !dbg !19
  %4 = bitcast i32* @.C309_fikos_print_error_ to i8*, !dbg !19
  %5 = bitcast i32* @.C309_fikos_print_error_ to i8*, !dbg !19
  %6 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !19
  %7 = call i32 (i8*, i8*, i8*, i8*, ...) %6(i8* %3, i8* null, i8* %4, i8* %5), !dbg !19
  store i32 %7, i32* %z__io_337, align 4, !dbg !19
  %8 = bitcast [18 x i8]* @.C338_fikos_print_error_ to i8*, !dbg !19
  %9 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !19
  %10 = call i32 (i8*, i32, i64, ...) %9(i8* %8, i32 14, i64 18), !dbg !19
  store i32 %10, i32* %z__io_337, align 4, !dbg !19
  %11 = bitcast %struct_fikos_1_* @_fikos_1_ to i8*, !dbg !19
  %12 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !19
  %13 = call i32 (i8*, i32, i64, ...) %12(i8* %11, i32 14, i64 100), !dbg !19
  store i32 %13, i32* %z__io_337, align 4, !dbg !19
  %14 = call i32 (...) @f90io_ldw_end(), !dbg !19
  store i32 %14, i32* %z__io_337, align 4, !dbg !19
  ret void, !dbg !20
}

define void @MAIN_() !dbg !21 {
L.entry:
  %.D0000_351 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB4_346

L.LB4_346:                                        ; preds = %L.entry
  %2 = bitcast %struct.BSS4* @.BSS4 to i32*, !dbg !23
  store i32 3, i32* %2, align 4, !dbg !23
  %3 = bitcast %struct.BSS4* @.BSS4 to i32*, !dbg !24
  %4 = load i32, i32* %3, align 4, !dbg !24
  %5 = icmp eq i32 %4, 3, !dbg !24
  %6 = sext i1 %5 to i32, !dbg !24
  store i32 %6, i32* %.D0000_351, align 4, !dbg !24
  %7 = bitcast i32* %.D0000_351 to i64*, !dbg !24
  %8 = bitcast [4 x i8]* @.C340_MAIN_ to i64*, !dbg !24
  call void @fikos_assert_(i64* %7, i64* %8, i64 4), !dbg !24
  ret void, !dbg !25
}

declare void @fort_init(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

declare void @f90_stop08a(...)

declare signext i32 @f90_str_copy_klen(...)

attributes #0 = { noinline }

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c type.f90 -o hello.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "type.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProByzou/SMACK_fortran/other")
!4 = !{}
!5 = distinct !DISubprogram(name: "assert", scope: !6, file: !3, line: 9, type: !7, scopeLine: 9, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DIModule(scope: !2, name: "fikos", file: !3)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9, !10}
!9 = !DIBasicType(name: "logical", size: 32, align: 32, encoding: DW_ATE_boolean)
!10 = !DIStringType(name: "character(*)!1", size: 32)
!11 = !DILocation(line: 13, column: 1, scope: !5)
!12 = !DILocation(line: 14, column: 1, scope: !5)
!13 = !DILocation(line: 15, column: 1, scope: !5)
!14 = !DILocation(line: 16, column: 1, scope: !5)
!15 = !DILocation(line: 18, column: 1, scope: !5)
!16 = distinct !DISubprogram(name: "print_error", scope: !6, file: !3, line: 20, type: !17, scopeLine: 20, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!17 = !DISubroutineType(types: !18)
!18 = !{null}
!19 = !DILocation(line: 21, column: 1, scope: !16)
!20 = !DILocation(line: 22, column: 1, scope: !16)
!21 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 26, type: !22, scopeLine: 26, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!22 = !DISubroutineType(cc: DW_CC_program, types: !18)
!23 = !DILocation(line: 34, column: 1, scope: !21)
!24 = !DILocation(line: 36, column: 1, scope: !21)
!25 = !DILocation(line: 37, column: 1, scope: !21)
