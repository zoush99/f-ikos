; this block is definition that is related to sourcefile
; ModuleID = '/tmp/defineVariabl-775d8e.ll'
source_filename = "/tmp/defineVariabl-775d8e.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C310_MAIN_ = internal constant i64 0
@.C311_MAIN_ = internal constant i32 1
@.C309_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %a_329 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_335

L.LB1_335:                                        ; preds = %L.entry
  store i32 1, i32* %a_329, align 4, !dbg !8
  %2 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !9
  %3 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !9
  call void (i8*, i8*, i64, ...) %3(i8* %2, i8* null, i64 0), !dbg !9
  ret void, !dbg !10
}

declare void @f90_stop08a(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S defineVariabl.f90 -o defineVariable.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "defineVariabl.f90", directory: "/home/zou/Downloads/FortranProgram/easyBenchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 4, column: 1, scope: !5)
!9 = !DILocation(line: 5, column: 1, scope: !5)
!10 = !DILocation(line: 6, column: 1, scope: !5)
