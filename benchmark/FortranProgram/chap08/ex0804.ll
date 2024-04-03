; ModuleID = '/tmp/ex0804-4fa112.ll'
source_filename = "/tmp/ex0804-4fa112.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C310_MAIN_ = internal constant i64 0
@.C315_MAIN_ = internal constant float 2.000000e+00
@.C314_MAIN_ = internal constant float 1.000000e+00
@.C309_MAIN_ = internal constant i32 0
@.C333_add_ = internal constant float 3.000000e+00
@.C334_adds_ = internal constant float 3.000000e+00

define void @MAIN_() !dbg !5 {
L.entry:
  %first_329 = alloca float, align 4
  %second_330 = alloca float, align 4
  %r_332 = alloca float, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_339

L.LB1_339:                                        ; preds = %L.entry
  store float 1.000000e+00, float* %first_329, align 4, !dbg !8
  store float 2.000000e+00, float* %second_330, align 4, !dbg !9
  %2 = bitcast float* %first_329 to i64*, !dbg !10
  %3 = bitcast float* %second_330 to i64*, !dbg !10
  call void @add_(i64* %2, i64* %3), !dbg !10
  %4 = bitcast float* %first_329 to i64*, !dbg !11
  %5 = bitcast float* %second_330 to i64*, !dbg !11
  %6 = call float @adds_(i64* %4, i64* %5), !dbg !11
  store float %6, float* %r_332, align 4, !dbg !11
  %7 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !12
  %8 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !12
  call void (i8*, i8*, i64, ...) %8(i8* %7, i8* null, i64 0), !dbg !12
  ret void, !dbg !13
}

define void @add_(i64* %first, i64* %second) !dbg !14 {
L.entry:
  %c_331 = alloca float, align 4
  %d_332 = alloca float, align 4
  br label %L.LB2_338

L.LB2_338:                                        ; preds = %L.entry
  store float 3.000000e+00, float* %c_331, align 4, !dbg !18
  %0 = load float, float* %c_331, align 4, !dbg !19
  store float %0, float* %d_332, align 4, !dbg !19
  %1 = load float, float* %c_331, align 4, !dbg !20
  %2 = load float, float* %c_331, align 4, !dbg !20
  %3 = load float, float* %d_332, align 4, !dbg !20
  %4 = fsub float %2, %3, !dbg !20
  %5 = fdiv float %1, %4, !dbg !20
  %6 = bitcast i64* %first to float*, !dbg !20
  store float %5, float* %6, align 4, !dbg !20
  br label %L.LB2_334, !dbg !21

L.LB2_334:                                        ; preds = %L.LB2_338
  ret void, !dbg !22
}

define float @adds_(i64* %a, i64* %b) !dbg !23 {
L.entry:
  %c_332 = alloca float, align 4
  %d_333 = alloca float, align 4
  %r_331 = alloca float, align 4
  br label %L.LB3_339

L.LB3_339:                                        ; preds = %L.entry
  store float 3.000000e+00, float* %c_332, align 4, !dbg !26
  store float 3.000000e+00, float* %d_333, align 4, !dbg !27
  %0 = load float, float* %c_332, align 4, !dbg !28
  %1 = load float, float* %c_332, align 4, !dbg !28
  %2 = load float, float* %d_333, align 4, !dbg !28
  %3 = fsub float %1, %2, !dbg !28
  %4 = fdiv float %0, %3, !dbg !28
  store float %4, float* %r_331, align 4, !dbg !28
  br label %L.LB3_335, !dbg !29

L.LB3_335:                                        ; preds = %L.LB3_339
  %5 = load float, float* %r_331, align 4, !dbg !30
  ret float %5, !dbg !30
}

declare void @f90_stop08a(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c ex0804.f90 -o ex0804.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "ex0804.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProgram/chap08")
!4 = !{}
!5 = distinct !DISubprogram(name: "ex0804", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 6, column: 1, scope: !5)
!9 = !DILocation(line: 7, column: 1, scope: !5)
!10 = !DILocation(line: 8, column: 1, scope: !5)
!11 = !DILocation(line: 10, column: 1, scope: !5)
!12 = !DILocation(line: 11, column: 1, scope: !5)
!13 = !DILocation(line: 12, column: 1, scope: !5)
!14 = distinct !DISubprogram(name: "add", scope: !2, file: !3, line: 14, type: !15, scopeLine: 14, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!15 = !DISubroutineType(types: !16)
!16 = !{null, !17, !17}
!17 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!18 = !DILocation(line: 18, column: 1, scope: !14)
!19 = !DILocation(line: 19, column: 1, scope: !14)
!20 = !DILocation(line: 20, column: 1, scope: !14)
!21 = !DILocation(line: 21, column: 1, scope: !14)
!22 = !DILocation(line: 22, column: 1, scope: !14)
!23 = distinct !DISubprogram(name: "adds", scope: !2, file: !3, line: 24, type: !24, scopeLine: 24, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!24 = !DISubroutineType(types: !25)
!25 = !{!17, !17, !17}
!26 = !DILocation(line: 29, column: 1, scope: !23)
!27 = !DILocation(line: 30, column: 1, scope: !23)
!28 = !DILocation(line: 31, column: 1, scope: !23)
!29 = !DILocation(line: 32, column: 1, scope: !23)
!30 = !DILocation(line: 33, column: 1, scope: !23)
