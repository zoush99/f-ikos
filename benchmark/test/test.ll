; ModuleID = '/tmp/test-356580.ll'
source_filename = "/tmp/test-356580.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.STATICS1 = type <{ [4 x i8] }>

@.STATICS1 = internal global %struct.STATICS1 <{ [4 x i8] c"\00\00\80?" }>, align 16

define float @div_() !dbg !5 {
L.entry:
  %b_331 = alloca float, align 4
  %c_332 = alloca float, align 4
  %div_329 = alloca float, align 4
  br label %L.LB1_335

L.LB1_335:                                        ; preds = %L.entry
  %0 = bitcast %struct.STATICS1* @.STATICS1 to float*, !dbg !9
  %1 = load float, float* %0, align 4, !dbg !9
  store float %1, float* %b_331, align 4, !dbg !9
  %2 = load float, float* %b_331, align 4, !dbg !10
  %3 = bitcast %struct.STATICS1* @.STATICS1 to float*, !dbg !10
  %4 = load float, float* %3, align 4, !dbg !10
  %5 = fsub float %2, %4, !dbg !10
  store float %5, float* %c_332, align 4, !dbg !10
  %6 = bitcast %struct.STATICS1* @.STATICS1 to float*, !dbg !11
  %7 = load float, float* %6, align 4, !dbg !11
  %8 = load float, float* %c_332, align 4, !dbg !11
  %9 = fdiv float %7, %8, !dbg !11
  %10 = bitcast %struct.STATICS1* @.STATICS1 to float*, !dbg !11
  store float %9, float* %10, align 4, !dbg !11
  %11 = load float, float* %b_331, align 4, !dbg !12
  %12 = load float, float* %c_332, align 4, !dbg !12
  %13 = fadd float %11, %12, !dbg !12
  store float %13, float* %b_331, align 4, !dbg !12
  %14 = bitcast %struct.STATICS1* @.STATICS1 to float*, !dbg !13
  %15 = load float, float* %14, align 4, !dbg !13
  store float %15, float* %div_329, align 4, !dbg !13
  %16 = load float, float* %div_329, align 4, !dbg !14
  ret float %16, !dbg !14
}

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c test.f90 -o test.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "test.f90", directory: "/home/zou/Documents/f-ikos/benchmark/test")
!4 = !{}
!5 = distinct !DISubprogram(name: "div", scope: !2, file: !3, line: 24, type: !6, scopeLine: 24, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 30, column: 1, scope: !5)
!10 = !DILocation(line: 31, column: 1, scope: !5)
!11 = !DILocation(line: 32, column: 1, scope: !5)
!12 = !DILocation(line: 33, column: 1, scope: !5)
!13 = !DILocation(line: 35, column: 1, scope: !5)
!14 = !DILocation(line: 36, column: 1, scope: !5)
