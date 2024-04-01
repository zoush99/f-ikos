; ModuleID = '/tmp/Fort_add-546239.ll'
source_filename = "/tmp/Fort_add-546239.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C314_add_ = internal constant float 1.000000e+00
@.C315_add_ = internal constant float 2.000000e+00
@.C333_add_ = internal constant float 0x3FB99999A0000000

define float @add_(i64* %x) !dbg !5 {
L.entry:
  %y_331 = alloca float, align 4
  %z_332 = alloca float, align 4
  %add_330 = alloca float, align 4
  br label %L.LB1_337

L.LB1_337:                                        ; preds = %L.entry
  %0 = bitcast i64* %x to float*, !dbg !9
  store float 0x3FB99999A0000000, float* %0, align 4, !dbg !9
  %1 = bitcast i64* %x to float*, !dbg !10
  %2 = load float, float* %1, align 4, !dbg !10
  %3 = fmul float %2, 2.000000e+00, !dbg !10
  %4 = bitcast i64* %x to float*, !dbg !10
  %5 = load float, float* %4, align 4, !dbg !10
  %6 = bitcast i64* %x to float*, !dbg !10
  %7 = load float, float* %6, align 4, !dbg !10
  %8 = bitcast i64* %x to float*, !dbg !10
  %9 = load float, float* %8, align 4, !dbg !10
  %10 = fmul float %7, %9, !dbg !10
  %11 = fmul float %5, %10, !dbg !10
  %12 = fadd float %3, %11, !dbg !10
  %13 = fadd float %12, 1.000000e+00, !dbg !10
  store float %13, float* %y_331, align 4, !dbg !10
  %14 = bitcast i64* %x to float*, !dbg !11
  %15 = load float, float* %14, align 4, !dbg !11
  %16 = load float, float* %y_331, align 4, !dbg !11
  %17 = fmul float %15, %16, !dbg !11
  store float %17, float* %z_332, align 4, !dbg !11
  %18 = load float, float* %add_330, align 4, !dbg !12
  ret float %18, !dbg !12
}

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm Fort_add.f90 -S -c -o Fort_add.ll -std=4'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "Fort_add.f90", directory: "/home/zou/Documents/f-ikos/benchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "add", scope: !2, file: !3, line: 3, type: !6, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8, !8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 8, column: 1, scope: !5)
!10 = !DILocation(line: 9, column: 1, scope: !5)
!11 = !DILocation(line: 10, column: 1, scope: !5)
!12 = !DILocation(line: 11, column: 1, scope: !5)
