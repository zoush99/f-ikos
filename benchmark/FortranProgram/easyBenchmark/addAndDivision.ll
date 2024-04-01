; ModuleID = '/tmp/addAndDivision-7ff73c.ll'
source_filename = "/tmp/addAndDivision-7ff73c.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C344_add_ = internal constant i32 27
@.C342_add_ = internal constant i32 14
@.C337_add_ = internal constant [12 x i8] c"2.5+3.0/2.0="
@.C309_add_ = internal constant i32 0
@.C310_add_ = internal constant i64 0
@.C336_add_ = internal constant i32 6
@.C333_add_ = internal constant [18 x i8] c"addAndDivision.f90"
@.C335_add_ = internal constant i32 8
@.C332_add_ = internal constant float 3.500000e+00
@.C313_add_ = internal constant float 0.000000e+00

define float @add_(i64* %a) !dbg !5 {
L.entry:
  %b_331 = alloca float, align 4
  %z__io_339 = alloca i32, align 4
  %add_330 = alloca float, align 4
  br label %L.LB1_349

L.LB1_349:                                        ; preds = %L.entry
  store float 0.000000e+00, float* %b_331, align 4, !dbg !9
  %0 = bitcast i64* %a to float*, !dbg !10
  store float 3.500000e+00, float* %0, align 4, !dbg !10
  %1 = bitcast i32* @.C335_add_ to i8*, !dbg !11
  %2 = bitcast [18 x i8]* @.C333_add_ to i8*, !dbg !11
  %3 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !11
  call void (i8*, i8*, i64, ...) %3(i8* %1, i8* %2, i64 18), !dbg !11
  %4 = bitcast i32* @.C336_add_ to i8*, !dbg !11
  %5 = bitcast i32* @.C309_add_ to i8*, !dbg !11
  %6 = bitcast i32* @.C309_add_ to i8*, !dbg !11
  %7 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !11
  %8 = call i32 (i8*, i8*, i8*, i8*, ...) %7(i8* %4, i8* null, i8* %5, i8* %6), !dbg !11
  store i32 %8, i32* %z__io_339, align 4, !dbg !11
  %9 = bitcast [12 x i8]* @.C337_add_ to i8*, !dbg !11
  %10 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !11
  %11 = call i32 (i8*, i32, i64, ...) %10(i8* %9, i32 14, i64 12), !dbg !11
  store i32 %11, i32* %z__io_339, align 4, !dbg !11
  %12 = bitcast i64* %a to float*, !dbg !11
  %13 = load float, float* %12, align 4, !dbg !11
  %14 = bitcast i32 (...)* @f90io_sc_f_ldw to i32 (float, i32, ...)*, !dbg !11
  %15 = call i32 (float, i32, ...) %14(float %13, i32 27), !dbg !11
  store i32 %15, i32* %z__io_339, align 4, !dbg !11
  %16 = call i32 (...) @f90io_ldw_end(), !dbg !11
  store i32 %16, i32* %z__io_339, align 4, !dbg !11
  %17 = bitcast i64* %a to float*, !dbg !12
  %18 = load float, float* %17, align 4, !dbg !12
  %19 = load float, float* %b_331, align 4, !dbg !12
  %20 = fdiv float %18, %19, !dbg !12
  %21 = bitcast i64* %a to float*, !dbg !12
  store float %20, float* %21, align 4, !dbg !12
  %22 = load float, float* %add_330, align 4, !dbg !13
  ret float %22, !dbg !13
}

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_f_ldw(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S addAndDivision.f90 -o addAndDivision.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "addAndDivision.f90", directory: "/home/zou/Downloads/FortranProgram/easyBenchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "add", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8, !8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 6, column: 1, scope: !5)
!10 = !DILocation(line: 7, column: 1, scope: !5)
!11 = !DILocation(line: 8, column: 1, scope: !5)
!12 = !DILocation(line: 9, column: 1, scope: !5)
!13 = !DILocation(line: 10, column: 1, scope: !5)
