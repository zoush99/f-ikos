; ModuleID = 'test_expr.c'
source_filename = "test_expr.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata double* %2, metadata !15, metadata !DIExpression()), !dbg !17
  call void @llvm.dbg.declare(metadata double* %3, metadata !18, metadata !DIExpression()), !dbg !19
  call void @llvm.dbg.declare(metadata double* %4, metadata !20, metadata !DIExpression()), !dbg !21
  store double 1.000000e-01, double* %2, align 8, !dbg !22
  %5 = load double, double* %2, align 8, !dbg !23
  %6 = load double, double* %2, align 8, !dbg !24
  %7 = fmul double %5, %6, !dbg !25
  %8 = load double, double* %2, align 8, !dbg !26
  %9 = load double, double* %2, align 8, !dbg !27
  %10 = fmul double 2.000000e+00, %9, !dbg !28
  %11 = call double @llvm.fmuladd.f64(double %7, double %8, double %10), !dbg !29
  %12 = fadd double %11, 1.000000e+00, !dbg !30
  store double %12, double* %3, align 8, !dbg !31
  %13 = load double, double* %2, align 8, !dbg !32
  %14 = load double, double* %3, align 8, !dbg !33
  %15 = fmul double %13, %14, !dbg !34
  store double %15, double* %4, align 8, !dbg !35
  %16 = load double, double* %4, align 8, !dbg !36
  %17 = fptosi double %16 to i32, !dbg !36
  ret i32 %17, !dbg !37
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare double @llvm.fmuladd.f64(double, double, double) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test_expr.c", directory: "/home/zou/Documents/f-ikos/benchmark", checksumkind: CSK_MD5, checksum: "6aed32be744aa5533b81d05362ca2d8d")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.6"}
!10 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 2, type: !11, scopeLine: 2, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !{}
!15 = !DILocalVariable(name: "x", scope: !10, file: !1, line: 3, type: !16)
!16 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!17 = !DILocation(line: 3, column: 13, scope: !10)
!18 = !DILocalVariable(name: "y", scope: !10, file: !1, line: 3, type: !16)
!19 = !DILocation(line: 3, column: 15, scope: !10)
!20 = !DILocalVariable(name: "z", scope: !10, file: !1, line: 4, type: !16)
!21 = !DILocation(line: 4, column: 13, scope: !10)
!22 = !DILocation(line: 5, column: 7, scope: !10)
!23 = !DILocation(line: 6, column: 8, scope: !10)
!24 = !DILocation(line: 6, column: 10, scope: !10)
!25 = !DILocation(line: 6, column: 9, scope: !10)
!26 = !DILocation(line: 6, column: 12, scope: !10)
!27 = !DILocation(line: 6, column: 16, scope: !10)
!28 = !DILocation(line: 6, column: 15, scope: !10)
!29 = !DILocation(line: 6, column: 13, scope: !10)
!30 = !DILocation(line: 6, column: 17, scope: !10)
!31 = !DILocation(line: 6, column: 7, scope: !10)
!32 = !DILocation(line: 7, column: 8, scope: !10)
!33 = !DILocation(line: 7, column: 10, scope: !10)
!34 = !DILocation(line: 7, column: 9, scope: !10)
!35 = !DILocation(line: 7, column: 7, scope: !10)
!36 = !DILocation(line: 8, column: 13, scope: !10)
!37 = !DILocation(line: 8, column: 6, scope: !10)
