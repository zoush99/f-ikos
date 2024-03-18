; ModuleID = '/tmp/ikos-g3hgjo5b/test_expr.pp.bc'
source_filename = "test_expr.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !10 {
  call void @llvm.dbg.value(metadata double 1.000000e-01, metadata !15, metadata !DIExpression()), !dbg !17
  %1 = fmul double 1.000000e-01, 1.000000e-01, !dbg !18
  %2 = fmul double 2.000000e+00, 1.000000e-01, !dbg !19
  %3 = call double @llvm.fmuladd.f64(double %1, double 1.000000e-01, double %2), !dbg !20
  %4 = fadd double %3, 1.000000e+00, !dbg !21
  call void @llvm.dbg.value(metadata double %4, metadata !22, metadata !DIExpression()), !dbg !17
  %5 = fmul double 1.000000e-01, %4, !dbg !23
  call void @llvm.dbg.value(metadata double %5, metadata !24, metadata !DIExpression()), !dbg !17
  %6 = fptosi double %5 to i32, !dbg !25
  ret i32 %6, !dbg !26
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare double @llvm.fmuladd.f64(double, double, double) #1

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

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
!17 = !DILocation(line: 0, scope: !10)
!18 = !DILocation(line: 6, column: 9, scope: !10)
!19 = !DILocation(line: 6, column: 15, scope: !10)
!20 = !DILocation(line: 6, column: 13, scope: !10)
!21 = !DILocation(line: 6, column: 17, scope: !10)
!22 = !DILocalVariable(name: "y", scope: !10, file: !1, line: 3, type: !16)
!23 = !DILocation(line: 7, column: 9, scope: !10)
!24 = !DILocalVariable(name: "z", scope: !10, file: !1, line: 4, type: !16)
!25 = !DILocation(line: 8, column: 13, scope: !10)
!26 = !DILocation(line: 8, column: 6, scope: !10)
