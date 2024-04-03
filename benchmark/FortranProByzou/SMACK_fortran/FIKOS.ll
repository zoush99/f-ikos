; ModuleID = '/tmp/FIKOS-b76cbf.ll'
source_filename = "/tmp/FIKOS-b76cbf.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct_fikos_1_ = type <{ [100 x i8] }>

@.C310_fikos_assert_ = internal constant i64 0
@.C309_fikos_assert_ = internal constant i32 0
@.C341_fikos_print_error_ = internal constant i32 14
@.C338_fikos_print_error_ = internal constant [18 x i8] c"Assertion failed: "
@.C309_fikos_print_error_ = internal constant i32 0
@.C310_fikos_print_error_ = internal constant i64 0
@.C335_fikos_print_error_ = internal constant i32 6
@.C332_fikos_print_error_ = internal constant [9 x i8] c"FIKOS.f90"
@.C334_fikos_print_error_ = internal constant i32 20
@_fikos_1_ = common global %struct_fikos_1_ zeroinitializer, align 64

; Function Attrs: noinline
define float @fikos_() #0 {
.L.entry:
  ret float undef
}

define void @fikos_assert_(i64* %condition, i64* %message, i64 %.U0001.arg) !dbg !5 {
L.entry:
  %.U0001.addr = alloca i64, align 8
  store i64 %.U0001.arg, i64* %.U0001.addr, align 8
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
  %6 = load i64, i64* %.U0001.addr, align 8, !dbg !12
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
  %1 = bitcast [9 x i8]* @.C332_fikos_print_error_ to i8*, !dbg !19
  %2 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !19
  call void (i8*, i8*, i64, ...) %2(i8* %0, i8* %1, i64 9), !dbg !19
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
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S FIKOS.f90 -o FIKOS.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "FIKOS.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProByzou/SMACK_fortran")
!4 = !{}
!5 = distinct !DISubprogram(name: "assert", scope: !6, file: !3, line: 8, type: !7, scopeLine: 8, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DIModule(scope: !2, name: "fikos", file: !3)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9, !10}
!9 = !DIBasicType(name: "logical", size: 32, align: 32, encoding: DW_ATE_boolean)
!10 = !DIStringType(name: "character(*)!1", size: 32)
!11 = !DILocation(line: 12, column: 1, scope: !5)
!12 = !DILocation(line: 13, column: 1, scope: !5)
!13 = !DILocation(line: 14, column: 1, scope: !5)
!14 = !DILocation(line: 15, column: 1, scope: !5)
!15 = !DILocation(line: 17, column: 1, scope: !5)
!16 = distinct !DISubprogram(name: "print_error", scope: !6, file: !3, line: 19, type: !17, scopeLine: 19, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!17 = !DISubroutineType(types: !18)
!18 = !{null}
!19 = !DILocation(line: 20, column: 1, scope: !16)
!20 = !DILocation(line: 21, column: 1, scope: !16)
