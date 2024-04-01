; ModuleID = '/tmp/test1-e7b4ca.ll'
source_filename = "/tmp/test1-e7b4ca.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C330_MAIN_ = internal constant i32 2
@.C344_MAIN_ = internal constant i32 -1
@.C339_MAIN_ = internal constant [7 x i8] c"Fortran"
@.C338_MAIN_ = internal constant <{ float, float }> <{ float 1.000000e+00, float 2.000000e+00 }>
@.C318_MAIN_ = internal constant double 1.000000e+00
@.C337_MAIN_ = internal constant i32 10
@.C309_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %i1_329 = alloca i32, align 4
  %r1_333 = alloca double, align 8
  %c1_334 = alloca <{ float, float }>, align 4
  %s1_335 = alloca [20 x i8], align 16
  %l1_336 = alloca i32, align 4
  %i2_331 = alloca i16, align 2
  %i3_332 = alloca i8, align 1
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_346

L.LB1_346:                                        ; preds = %L.entry
  store i32 10, i32* %i1_329, align 4, !dbg !8
  store double 1.000000e+00, double* %r1_333, align 8, !dbg !9
  store <{ float, float }> <{ float 1.000000e+00, float 2.000000e+00 }>, <{ float, float }>* %c1_334, align 4, !dbg !10
  %2 = bitcast [20 x i8]* %s1_335 to i8*, !dbg !11
  %3 = bitcast [7 x i8]* @.C339_MAIN_ to i8*, !dbg !11
  %4 = bitcast i32 (...)* @f90_str_cpy1 to i32 (i8*, i64, i8*, i64, ...)*, !dbg !11
  %5 = call i32 (i8*, i64, i8*, i64, ...) %4(i8* %2, i64 20, i8* %3, i64 7), !dbg !11
  store i32 -1, i32* %l1_336, align 4, !dbg !12
  %6 = load i32, i32* %i1_329, align 4, !dbg !13
  %7 = load i16, i16* %i2_331, align 2, !dbg !13
  %8 = sext i16 %7 to i32, !dbg !13
  %9 = mul nsw i32 %8, 2, !dbg !13
  %10 = sdiv i32 %6, %9, !dbg !13
  %11 = shl nsw i32 %10, 24, !dbg !13
  %12 = ashr i32 %11, 24, !dbg !13
  %13 = trunc i32 %12 to i8, !dbg !13
  store i8 %13, i8* %i3_332, align 1, !dbg !13
  ret void, !dbg !14
}

declare signext i32 @f90_str_cpy1(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c test1.f90 -o test1.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "test1.f90", directory: "/home/zou/Downloads/FortranProgram/chap02")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 12, column: 1, scope: !5)
!9 = !DILocation(line: 13, column: 1, scope: !5)
!10 = !DILocation(line: 14, column: 1, scope: !5)
!11 = !DILocation(line: 15, column: 1, scope: !5)
!12 = !DILocation(line: 16, column: 1, scope: !5)
!13 = !DILocation(line: 17, column: 1, scope: !5)
!14 = !DILocation(line: 19, column: 1, scope: !5)
