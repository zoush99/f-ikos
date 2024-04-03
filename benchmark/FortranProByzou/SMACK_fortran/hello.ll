; ModuleID = '/tmp/hello-b1f3f0.ll'
source_filename = "/tmp/hello-b1f3f0.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C340_fikos_assert_ = internal constant i32 14
@.C337_fikos_assert_ = internal constant [17 x i8] c"Assertion failed!"
@.C309_fikos_assert_ = internal constant i32 0
@.C310_fikos_assert_ = internal constant i64 0
@.C334_fikos_assert_ = internal constant i32 6
@.C331_fikos_assert_ = internal constant [9 x i8] c"hello.f90"
@.C333_fikos_assert_ = internal constant i32 11
@.C336_MAIN_ = internal constant i32 -1
@.C309_MAIN_ = internal constant i32 0

; Function Attrs: noinline
define float @fikos_() #0 {
.L.entry:
  ret float undef
}

define void @fikos_assert_(i64* %condition) !dbg !5 {
L.entry:
  %z__io_336 = alloca i32, align 4
  br label %L.LB2_347

L.LB2_347:                                        ; preds = %L.entry
  %0 = bitcast i64* %condition to i32*, !dbg !10
  %1 = load i32, i32* %0, align 4, !dbg !10
  %2 = and i32 %1, 1, !dbg !10
  %3 = icmp ne i32 %2, 0, !dbg !10
  br i1 %3, label %L.LB2_345, label %L.LB2_362, !dbg !10

L.LB2_362:                                        ; preds = %L.LB2_347
  %4 = bitcast i32* @.C333_fikos_assert_ to i8*, !dbg !11
  %5 = bitcast [9 x i8]* @.C331_fikos_assert_ to i8*, !dbg !11
  %6 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !11
  call void (i8*, i8*, i64, ...) %6(i8* %4, i8* %5, i64 9), !dbg !11
  %7 = bitcast i32* @.C334_fikos_assert_ to i8*, !dbg !11
  %8 = bitcast i32* @.C309_fikos_assert_ to i8*, !dbg !11
  %9 = bitcast i32* @.C309_fikos_assert_ to i8*, !dbg !11
  %10 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !11
  %11 = call i32 (i8*, i8*, i8*, i8*, ...) %10(i8* %7, i8* null, i8* %8, i8* %9), !dbg !11
  store i32 %11, i32* %z__io_336, align 4, !dbg !11
  %12 = bitcast [17 x i8]* @.C337_fikos_assert_ to i8*, !dbg !11
  %13 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !11
  %14 = call i32 (i8*, i32, i64, ...) %13(i8* %12, i32 14, i64 17), !dbg !11
  store i32 %14, i32* %z__io_336, align 4, !dbg !11
  %15 = call i32 (...) @f90io_ldw_end(), !dbg !11
  store i32 %15, i32* %z__io_336, align 4, !dbg !11
  %16 = bitcast i32* @.C309_fikos_assert_ to i8*, !dbg !12
  %17 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !12
  call void (i8*, i8*, i64, ...) %17(i8* %16, i8* null, i64 0), !dbg !12
  br label %L.LB2_345

L.LB2_345:                                        ; preds = %L.LB2_362, %L.LB2_347
  ret void, !dbg !13
}

define void @MAIN_() !dbg !14 {
L.entry:
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB3_338

L.LB3_338:                                        ; preds = %L.entry
  %2 = bitcast i32* @.C336_MAIN_ to i64*, !dbg !17
  call void @fikos_assert_(i64* %2), !dbg !17
  ret void, !dbg !18
}

declare void @fort_init(...)

declare void @f90_stop08a(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

attributes #0 = { noinline }

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c hello.f90 -o hello.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "hello.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProByzou/SMACK_fortran")
!4 = !{}
!5 = distinct !DISubprogram(name: "assert", scope: !6, file: !3, line: 7, type: !7, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DIModule(scope: !2, name: "fikos", file: !3)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9}
!9 = !DIBasicType(name: "logical", size: 32, align: 32, encoding: DW_ATE_boolean)
!10 = !DILocation(line: 10, column: 1, scope: !5)
!11 = !DILocation(line: 11, column: 1, scope: !5)
!12 = !DILocation(line: 12, column: 1, scope: !5)
!13 = !DILocation(line: 14, column: 1, scope: !5)
!14 = distinct !DISubprogram(name: "hello", scope: !2, file: !3, line: 17, type: !15, scopeLine: 17, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!15 = !DISubroutineType(cc: DW_CC_program, types: !16)
!16 = !{null}
!17 = !DILocation(line: 20, column: 1, scope: !14)
!18 = !DILocation(line: 21, column: 1, scope: !14)
