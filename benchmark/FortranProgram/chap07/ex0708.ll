; ModuleID = '/tmp/ex0708-0de71b.ll'
source_filename = "/tmp/ex0708-0de71b.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.BSS1 = type <{ [16 x i8] }>
%struct.STATICS1 = type <{ [32 x i8] }>

@.BSS1 = internal global %struct.BSS1 zeroinitializer, align 32
@.STATICS1 = internal global %struct.STATICS1 <{ [32 x i8] c"\04\00\00\00\04\00\00\00\04\00\00\00\04\00\00\00\01\00\00\00\01\00\00\00\01\00\00\00\01\00\00\00" }>, align 16
@.C351_MAIN_ = internal constant i32 25
@.C330_MAIN_ = internal constant i32 2
@.C343_MAIN_ = internal constant i32 6
@.C344_MAIN_ = internal constant [15 x i8] c"(I3,I3,/,I3,I3)"
@.C311_MAIN_ = internal constant i32 1
@.C346_MAIN_ = internal constant i32 14
@.C340_MAIN_ = internal constant [10 x i8] c"ex0708.f90"
@.C342_MAIN_ = internal constant i32 11
@.C310_MAIN_ = internal constant i64 0
@.C333_MAIN_ = internal constant i64 2
@.C312_MAIN_ = internal constant i64 1
@.C309_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %.dY0001_361 = alloca i64, align 8
  %"i$a_355" = alloca i64, align 8
  %.dY0002_364 = alloca i64, align 8
  %"i$b_356" = alloca i64, align 8
  %z__io_347 = alloca i32, align 4
  %.dY0003_367 = alloca i32, align 4
  %j_339 = alloca i32, align 4
  %.dY0004_370 = alloca i32, align 4
  %i_338 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_372

L.LB1_372:                                        ; preds = %L.entry
  store i64 2, i64* %.dY0001_361, align 8, !dbg !8
  store i64 1, i64* %"i$a_355", align 8, !dbg !8
  br label %L.LB1_359

L.LB1_359:                                        ; preds = %L.LB1_405, %L.LB1_372
  store i64 2, i64* %.dY0002_364, align 8, !dbg !8
  store i64 1, i64* %"i$b_356", align 8, !dbg !8
  br label %L.LB1_362

L.LB1_362:                                        ; preds = %L.LB1_362, %L.LB1_359
  %2 = load i64, i64* %"i$b_356", align 8, !dbg !8
  %3 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %4 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %5 = add nsw i64 %3, %4, !dbg !8
  %6 = add nsw i64 %2, %5, !dbg !8
  %7 = bitcast %struct.STATICS1* @.STATICS1 to i8*, !dbg !8
  %8 = getelementptr i8, i8* %7, i64 -12, !dbg !8
  %9 = bitcast i8* %8 to i32*, !dbg !8
  %10 = getelementptr i32, i32* %9, i64 %6, !dbg !8
  %11 = load i32, i32* %10, align 4, !dbg !8
  %12 = load i64, i64* %"i$b_356", align 8, !dbg !8
  %13 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %14 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %15 = add nsw i64 %13, %14, !dbg !8
  %16 = add nsw i64 %12, %15, !dbg !8
  %17 = bitcast %struct.STATICS1* @.STATICS1 to i8*, !dbg !8
  %18 = getelementptr i8, i8* %17, i64 4, !dbg !8
  %19 = bitcast i8* %18 to i32*, !dbg !8
  %20 = getelementptr i32, i32* %19, i64 %16, !dbg !8
  %21 = load i32, i32* %20, align 4, !dbg !8
  %22 = add nsw i32 %11, %21, !dbg !8
  %23 = load i64, i64* %"i$b_356", align 8, !dbg !8
  %24 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %25 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %26 = add nsw i64 %24, %25, !dbg !8
  %27 = add nsw i64 %23, %26, !dbg !8
  %28 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !8
  %29 = getelementptr i8, i8* %28, i64 -12, !dbg !8
  %30 = bitcast i8* %29 to i32*, !dbg !8
  %31 = getelementptr i32, i32* %30, i64 %27, !dbg !8
  store i32 %22, i32* %31, align 4, !dbg !8
  %32 = load i64, i64* %"i$b_356", align 8, !dbg !8
  %33 = add nsw i64 %32, 1, !dbg !8
  store i64 %33, i64* %"i$b_356", align 8, !dbg !8
  %34 = load i64, i64* %.dY0002_364, align 8, !dbg !8
  %35 = sub nsw i64 %34, 1, !dbg !8
  store i64 %35, i64* %.dY0002_364, align 8, !dbg !8
  %36 = load i64, i64* %.dY0002_364, align 8, !dbg !8
  %37 = icmp sgt i64 %36, 0, !dbg !8
  br i1 %37, label %L.LB1_362, label %L.LB1_405, !dbg !8, !llvm.loop !9

L.LB1_405:                                        ; preds = %L.LB1_362
  %38 = load i64, i64* %"i$a_355", align 8, !dbg !8
  %39 = add nsw i64 %38, 1, !dbg !8
  store i64 %39, i64* %"i$a_355", align 8, !dbg !8
  %40 = load i64, i64* %.dY0001_361, align 8, !dbg !8
  %41 = sub nsw i64 %40, 1, !dbg !8
  store i64 %41, i64* %.dY0001_361, align 8, !dbg !8
  %42 = load i64, i64* %.dY0001_361, align 8, !dbg !8
  %43 = icmp sgt i64 %42, 0, !dbg !8
  br i1 %43, label %L.LB1_359, label %L.LB1_406, !dbg !8, !llvm.loop !10

L.LB1_406:                                        ; preds = %L.LB1_405
  %44 = bitcast i32* @.C342_MAIN_ to i8*, !dbg !11
  %45 = bitcast [10 x i8]* @.C340_MAIN_ to i8*, !dbg !11
  %46 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !11
  call void (i8*, i8*, i64, ...) %46(i8* %44, i8* %45, i64 10), !dbg !11
  %47 = bitcast i32* @.C346_MAIN_ to i8*, !dbg !11
  %48 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !11
  %49 = bitcast [15 x i8]* @.C344_MAIN_ to i8*, !dbg !11
  %50 = bitcast i32 (...)* @f90io_encode_fmta to i32 (i8*, i8*, i8*, i64, ...)*, !dbg !11
  %51 = call i32 (i8*, i8*, i8*, i64, ...) %50(i8* %47, i8* %48, i8* %49, i64 15), !dbg !11
  store i32 %51, i32* %z__io_347, align 4, !dbg !11
  %52 = bitcast i32* @.C343_MAIN_ to i8*, !dbg !11
  %53 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !11
  %54 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !11
  %55 = bitcast i32 (...)* @f90io_fmtw_inita to i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...)*, !dbg !11
  %56 = call i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...) %55(i8* %52, i8* null, i8* %53, i8* %54, i8* null, i8* null, i64 0), !dbg !11
  store i32 %56, i32* %z__io_347, align 4, !dbg !11
  store i32 2, i32* %.dY0003_367, align 4, !dbg !11
  store i32 1, i32* %j_339, align 4, !dbg !11
  br label %L.LB1_365

L.LB1_365:                                        ; preds = %L.LB1_407, %L.LB1_406
  store i32 2, i32* %.dY0004_370, align 4, !dbg !11
  store i32 1, i32* %i_338, align 4, !dbg !11
  br label %L.LB1_368

L.LB1_368:                                        ; preds = %L.LB1_368, %L.LB1_365
  %57 = load i32, i32* %i_338, align 4, !dbg !11
  %58 = sext i32 %57 to i64, !dbg !11
  %59 = load i32, i32* %j_339, align 4, !dbg !11
  %60 = sext i32 %59 to i64, !dbg !11
  %61 = load i32, i32* %j_339, align 4, !dbg !11
  %62 = sext i32 %61 to i64, !dbg !11
  %63 = add nsw i64 %60, %62, !dbg !11
  %64 = add nsw i64 %58, %63, !dbg !11
  %65 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !11
  %66 = getelementptr i8, i8* %65, i64 -12, !dbg !11
  %67 = bitcast i8* %66 to i32*, !dbg !11
  %68 = getelementptr i32, i32* %67, i64 %64, !dbg !11
  %69 = load i32, i32* %68, align 4, !dbg !11
  %70 = bitcast i32 (...)* @f90io_sc_i_fmt_write to i32 (i32, i32, ...)*, !dbg !11
  %71 = call i32 (i32, i32, ...) %70(i32 %69, i32 25), !dbg !11
  store i32 %71, i32* %z__io_347, align 4, !dbg !11
  %72 = load i32, i32* %i_338, align 4, !dbg !11
  %73 = add nsw i32 %72, 1, !dbg !11
  store i32 %73, i32* %i_338, align 4, !dbg !11
  %74 = load i32, i32* %.dY0004_370, align 4, !dbg !11
  %75 = sub nsw i32 %74, 1, !dbg !11
  store i32 %75, i32* %.dY0004_370, align 4, !dbg !11
  %76 = load i32, i32* %.dY0004_370, align 4, !dbg !11
  %77 = icmp sgt i32 %76, 0, !dbg !11
  br i1 %77, label %L.LB1_368, label %L.LB1_407, !dbg !11, !llvm.loop !12

L.LB1_407:                                        ; preds = %L.LB1_368
  %78 = load i32, i32* %j_339, align 4, !dbg !11
  %79 = add nsw i32 %78, 1, !dbg !11
  store i32 %79, i32* %j_339, align 4, !dbg !11
  %80 = load i32, i32* %.dY0003_367, align 4, !dbg !11
  %81 = sub nsw i32 %80, 1, !dbg !11
  store i32 %81, i32* %.dY0003_367, align 4, !dbg !11
  %82 = load i32, i32* %.dY0003_367, align 4, !dbg !11
  %83 = icmp sgt i32 %82, 0, !dbg !11
  br i1 %83, label %L.LB1_365, label %L.LB1_408, !dbg !11, !llvm.loop !13

L.LB1_408:                                        ; preds = %L.LB1_407
  %84 = call i32 (...) @f90io_fmtw_end(), !dbg !11
  store i32 %84, i32* %z__io_347, align 4, !dbg !11
  %85 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !14
  %86 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !14
  call void (i8*, i8*, i64, ...) %86(i8* %85, i8* null, i64 0), !dbg !14
  ret void, !dbg !15
}

declare void @f90_stop08a(...)

declare signext i32 @f90io_fmtw_end(...)

declare signext i32 @f90io_sc_i_fmt_write(...)

declare signext i32 @f90io_fmtw_inita(...)

declare signext i32 @f90io_encode_fmta(...)

declare void @f90io_src_info03a(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm ex0708.f90 -S -o ex0708.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "ex0708.f90", directory: "/home/zou/Downloads/FortranProgram/chap07")
!4 = !{}
!5 = distinct !DISubprogram(name: "ex0708", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 10, column: 1, scope: !5)
!9 = distinct !{!9, !8, !8}
!10 = distinct !{!10, !8, !8}
!11 = !DILocation(line: 11, column: 1, scope: !5)
!12 = distinct !{!12, !11, !11}
!13 = distinct !{!13, !11, !11}
!14 = !DILocation(line: 13, column: 1, scope: !5)
!15 = !DILocation(line: 14, column: 1, scope: !5)
