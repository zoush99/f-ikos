; ModuleID = '/tmp/ex0405-219508.ll'
source_filename = "/tmp/ex0405-219508.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C314_div_ = internal constant float 1.000000e+00
@.C334_div_ = internal constant float 3.000000e+00
@.C333_div_ = internal constant float 7.000000e+00

define float @div_() !dbg !5 {
L.entry:
  %a_330 = alloca float, align 4
  %b_331 = alloca float, align 4
  %c_332 = alloca float, align 4
  %div_329 = alloca float, align 4
  br label %L.LB1_337

L.LB1_337:                                        ; preds = %L.entry
  store float 7.000000e+00, float* %a_330, align 4, !dbg !9
  store float 3.000000e+00, float* %b_331, align 4, !dbg !10
  store float 1.000000e+00, float* %c_332, align 4, !dbg !11
  %0 = load float, float* %a_330, align 4, !dbg !12
  %1 = load float, float* %c_332, align 4, !dbg !12
  %2 = fsub float %1, 1.000000e+00, !dbg !12
  %3 = fdiv float %0, %2, !dbg !12
  store float %3, float* %a_330, align 4, !dbg !12
  %4 = load float, float* %a_330, align 4, !dbg !13
  store float %4, float* %div_329, align 4, !dbg !13
  %5 = load float, float* %div_329, align 4, !dbg !14
  ret float %5, !dbg !14
}

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c ex0405.f90 -o ex0405.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "ex0405.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProgram/chap04")
!4 = !{}
!5 = distinct !DISubprogram(name: "div", scope: !2, file: !3, line: 13, type: !6, scopeLine: 13, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 18, column: 1, scope: !5)
!10 = !DILocation(line: 19, column: 1, scope: !5)
!11 = !DILocation(line: 20, column: 1, scope: !5)
!12 = !DILocation(line: 21, column: 1, scope: !5)
!13 = !DILocation(line: 22, column: 1, scope: !5)
!14 = !DILocation(line: 23, column: 1, scope: !5)
