; ModuleID = '/tmp/addAndMul-5f789a.ll'
source_filename = "/tmp/addAndMul-5f789a.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C342_MAIN_ = internal constant i32 27
@.C340_MAIN_ = internal constant i32 14
@.C335_MAIN_ = internal constant [6 x i8] c"2.5*3="
@.C310_MAIN_ = internal constant i64 0
@.C334_MAIN_ = internal constant i32 6
@.C332_MAIN_ = internal constant [13 x i8] c"addAndMul.f90"
@.C329_MAIN_ = internal constant i32 4
@.C331_MAIN_ = internal constant float 7.500000e+00
@.C309_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %a_330 = alloca float, align 4
  %z__io_337 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_349

L.LB1_349:                                        ; preds = %L.entry
  store float 7.500000e+00, float* %a_330, align 4, !dbg !8
  %2 = bitcast i32* @.C329_MAIN_ to i8*, !dbg !9
  %3 = bitcast [13 x i8]* @.C332_MAIN_ to i8*, !dbg !9
  %4 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !9
  call void (i8*, i8*, i64, ...) %4(i8* %2, i8* %3, i64 13), !dbg !9
  %5 = bitcast i32* @.C334_MAIN_ to i8*, !dbg !9
  %6 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !9
  %7 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !9
  %8 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !9
  %9 = call i32 (i8*, i8*, i8*, i8*, ...) %8(i8* %5, i8* null, i8* %6, i8* %7), !dbg !9
  store i32 %9, i32* %z__io_337, align 4, !dbg !9
  %10 = bitcast [6 x i8]* @.C335_MAIN_ to i8*, !dbg !9
  %11 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !9
  %12 = call i32 (i8*, i32, i64, ...) %11(i8* %10, i32 14, i64 6), !dbg !9
  store i32 %12, i32* %z__io_337, align 4, !dbg !9
  %13 = load float, float* %a_330, align 4, !dbg !9
  %14 = bitcast i32 (...)* @f90io_sc_f_ldw to i32 (float, i32, ...)*, !dbg !9
  %15 = call i32 (float, i32, ...) %14(float %13, i32 27), !dbg !9
  store i32 %15, i32* %z__io_337, align 4, !dbg !9
  %16 = call i32 (...) @f90io_ldw_end(), !dbg !9
  store i32 %16, i32* %z__io_337, align 4, !dbg !9
  %17 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !10
  %18 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !10
  call void (i8*, i8*, i64, ...) %18(i8* %17, i8* null, i64 0), !dbg !10
  ret void, !dbg !11
}

declare void @f90_stop08a(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_f_ldw(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -S -emit-llvm addAndMul.f90 -o addAndMul.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "addAndMul.f90", directory: "/home/zou/Downloads/FortranProgram/easyBenchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "ex0405", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 3, column: 1, scope: !5)
!9 = !DILocation(line: 4, column: 1, scope: !5)
!10 = !DILocation(line: 5, column: 1, scope: !5)
!11 = !DILocation(line: 6, column: 1, scope: !5)
