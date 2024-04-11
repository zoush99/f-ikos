; ModuleID = '/tmp/angle-4a7228.ll'
source_filename = "/tmp/angle-4a7228.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.BSS1 = type <{ [20 x i8] }>
%struct.STATICS1 = type <{ [52 x i8] }>

@.BSS1 = internal global %struct.BSS1 zeroinitializer, align 32
@.STATICS1 = internal global %struct.STATICS1 <{ [52 x i8] c"\00\00\C8A\00\00\A0A\00\00\A8A\00\00\D8A\00\00\B0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\F0A\00\004B\00\00\0CB\00\00HB\00\00 B" }>, align 16
@.C350_MAIN_ = internal constant i32 27
@.C348_MAIN_ = internal constant i32 25
@.C310_MAIN_ = internal constant i64 0
@.C340_MAIN_ = internal constant i32 6
@.C341_MAIN_ = internal constant [24 x i8] c"('Player ',I1,' =',F8.2)"
@.C343_MAIN_ = internal constant i32 14
@.C337_MAIN_ = internal constant [9 x i8] c"angle.f90"
@.C339_MAIN_ = internal constant i32 11
@.C330_MAIN_ = internal constant i32 5
@.C311_MAIN_ = internal constant i32 1
@.C309_MAIN_ = internal constant i32 0
@.C333_angle_to_rad_ = internal constant float 1.800000e+02
@.C332_angle_to_rad_ = internal constant float 0x400921FA00000000
@.C335_get_distance_ = internal constant float 0x40239EB860000000
@.C315_get_distance_ = internal constant float 2.000000e+00

define void @MAIN_() !dbg !5 {
L.entry:
  %.dY0001_358 = alloca i32, align 4
  %i_335 = alloca i32, align 4
  %z__io_344 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_360

L.LB1_360:                                        ; preds = %L.entry
  store i32 5, i32* %.dY0001_358, align 4, !dbg !8
  store i32 1, i32* %i_335, align 4, !dbg !8
  br label %L.LB1_356

L.LB1_356:                                        ; preds = %L.LB1_356, %L.LB1_360
  %2 = bitcast %struct.STATICS1* @.STATICS1 to i8*, !dbg !9
  %3 = getelementptr i8, i8* %2, i64 28, !dbg !9
  %4 = load i32, i32* %i_335, align 4, !dbg !9
  %5 = sext i32 %4 to i64, !dbg !9
  %6 = mul nsw i64 %5, 4, !dbg !9
  %7 = getelementptr i8, i8* %3, i64 %6, !dbg !9
  %8 = bitcast i8* %7 to i64*, !dbg !9
  %9 = bitcast %struct.STATICS1* @.STATICS1 to i8*, !dbg !9
  %10 = getelementptr i8, i8* %9, i64 -4, !dbg !9
  %11 = load i32, i32* %i_335, align 4, !dbg !9
  %12 = sext i32 %11 to i64, !dbg !9
  %13 = mul nsw i64 %12, 4, !dbg !9
  %14 = getelementptr i8, i8* %10, i64 %13, !dbg !9
  %15 = bitcast i8* %14 to i64*, !dbg !9
  %16 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !9
  %17 = getelementptr i8, i8* %16, i64 -4, !dbg !9
  %18 = load i32, i32* %i_335, align 4, !dbg !9
  %19 = sext i32 %18 to i64, !dbg !9
  %20 = mul nsw i64 %19, 4, !dbg !9
  %21 = getelementptr i8, i8* %17, i64 %20, !dbg !9
  %22 = bitcast i8* %21 to i64*, !dbg !9
  call void @get_distance_(i64* %8, i64* %15, i64* %22), !dbg !9
  %23 = bitcast i32* @.C339_MAIN_ to i8*, !dbg !10
  %24 = bitcast [9 x i8]* @.C337_MAIN_ to i8*, !dbg !10
  %25 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !10
  call void (i8*, i8*, i64, ...) %25(i8* %23, i8* %24, i64 9), !dbg !10
  %26 = bitcast i32* @.C343_MAIN_ to i8*, !dbg !10
  %27 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !10
  %28 = bitcast [24 x i8]* @.C341_MAIN_ to i8*, !dbg !10
  %29 = bitcast i32 (...)* @f90io_encode_fmta to i32 (i8*, i8*, i8*, i64, ...)*, !dbg !10
  %30 = call i32 (i8*, i8*, i8*, i64, ...) %29(i8* %26, i8* %27, i8* %28, i64 24), !dbg !10
  store i32 %30, i32* %z__io_344, align 4, !dbg !10
  %31 = bitcast i32* @.C340_MAIN_ to i8*, !dbg !10
  %32 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !10
  %33 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !10
  %34 = bitcast i32 (...)* @f90io_fmtw_inita to i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...)*, !dbg !10
  %35 = call i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...) %34(i8* %31, i8* null, i8* %32, i8* %33, i8* null, i8* null, i64 0), !dbg !10
  store i32 %35, i32* %z__io_344, align 4, !dbg !10
  %36 = load i32, i32* %i_335, align 4, !dbg !10
  %37 = bitcast i32 (...)* @f90io_sc_i_fmt_write to i32 (i32, i32, ...)*, !dbg !10
  %38 = call i32 (i32, i32, ...) %37(i32 %36, i32 25), !dbg !10
  store i32 %38, i32* %z__io_344, align 4, !dbg !10
  %39 = load i32, i32* %i_335, align 4, !dbg !10
  %40 = sext i32 %39 to i64, !dbg !10
  %41 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !10
  %42 = getelementptr i8, i8* %41, i64 -4, !dbg !10
  %43 = bitcast i8* %42 to float*, !dbg !10
  %44 = getelementptr float, float* %43, i64 %40, !dbg !10
  %45 = load float, float* %44, align 4, !dbg !10
  %46 = bitcast i32 (...)* @f90io_sc_f_fmt_write to i32 (float, i32, ...)*, !dbg !10
  %47 = call i32 (float, i32, ...) %46(float %45, i32 27), !dbg !10
  store i32 %47, i32* %z__io_344, align 4, !dbg !10
  %48 = call i32 (...) @f90io_fmtw_end(), !dbg !10
  store i32 %48, i32* %z__io_344, align 4, !dbg !10
  %49 = load i32, i32* %i_335, align 4, !dbg !11
  %50 = add nsw i32 %49, 1, !dbg !11
  store i32 %50, i32* %i_335, align 4, !dbg !11
  %51 = load i32, i32* %.dY0001_358, align 4, !dbg !11
  %52 = sub nsw i32 %51, 1, !dbg !11
  store i32 %52, i32* %.dY0001_358, align 4, !dbg !11
  %53 = load i32, i32* %.dY0001_358, align 4, !dbg !11
  %54 = icmp sgt i32 %53, 0, !dbg !11
  br i1 %54, label %L.LB1_356, label %L.LB1_387, !dbg !11, !llvm.loop !12

L.LB1_387:                                        ; preds = %L.LB1_356
  %55 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !13
  %56 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !13
  call void (i8*, i8*, i64, ...) %56(i8* %55, i8* null, i64 0), !dbg !13
  ret void, !dbg !14
}

define void @angle_to_rad_(i64* %angle, i64* %rad) !dbg !15 {
L.entry:
  br label %L.LB2_338

L.LB2_338:                                        ; preds = %L.entry
  %0 = bitcast i64* %angle to float*, !dbg !19
  %1 = load float, float* %0, align 4, !dbg !19
  %2 = fmul float %1, 0x400921FA00000000, !dbg !19
  %3 = fdiv float %2, 1.800000e+02, !dbg !19
  %4 = bitcast i64* %rad to float*, !dbg !19
  store float %3, float* %4, align 4, !dbg !19
  br label %L.LB2_334, !dbg !20

L.LB2_334:                                        ; preds = %L.LB2_338
  ret void, !dbg !21
}

define void @get_distance_(i64* %angle, i64* %speed, i64* %distance) !dbg !22 {
L.entry:
  %rad_332 = alloca float, align 4
  %vx_333 = alloca float, align 4
  %time_337 = alloca float, align 4
  br label %L.LB3_343

L.LB3_343:                                        ; preds = %L.entry
  %0 = bitcast float* %rad_332 to i64*, !dbg !25
  call void @angle_to_rad_(i64* %angle, i64* %0), !dbg !25
  %1 = load float, float* %rad_332, align 4, !dbg !26
  %2 = call float @__ps_cos_1(float %1), !dbg !26
  %3 = bitcast i64* %speed to float*, !dbg !26
  %4 = load float, float* %3, align 4, !dbg !26
  %5 = fmul float %2, %4, !dbg !26
  store float %5, float* %vx_333, align 4, !dbg !26
  %6 = load float, float* %rad_332, align 4, !dbg !27
  %7 = call float @__ps_sin_1(float %6), !dbg !27
  %8 = bitcast i64* %speed to float*, !dbg !27
  %9 = load float, float* %8, align 4, !dbg !27
  %10 = fmul float %9, 2.000000e+00, !dbg !27
  %11 = fmul float %7, %10, !dbg !27
  %12 = fdiv float %11, 0x40239EB860000000, !dbg !27
  store float %12, float* %time_337, align 4, !dbg !27
  %13 = load float, float* %time_337, align 4, !dbg !28
  %14 = load float, float* %vx_333, align 4, !dbg !28
  %15 = fmul float %13, %14, !dbg !28
  %16 = bitcast i64* %distance to float*, !dbg !28
  store float %15, float* %16, align 4, !dbg !28
  br label %L.LB3_338, !dbg !29

L.LB3_338:                                        ; preds = %L.LB3_343
  ret void, !dbg !30
}

; Function Attrs: nounwind readnone willreturn
declare float @__ps_sin_1(float) #0

; Function Attrs: nounwind readnone willreturn
declare float @__ps_cos_1(float) #0

; Function Attrs: nounwind readnone willreturn
declare <{ float, float }> @__ps_sincos_1(float) #0

declare void @f90_stop08a(...)

declare signext i32 @f90io_fmtw_end(...)

declare signext i32 @f90io_sc_f_fmt_write(...)

declare signext i32 @f90io_sc_i_fmt_write(...)

declare signext i32 @f90io_fmtw_inita(...)

declare signext i32 @f90io_encode_fmta(...)

declare void @f90io_src_info03a(...)

declare void @fort_init(...)

attributes #0 = { nounwind readnone willreturn }

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c angle.f90 -o angle.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "angle.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProByzou/Fortran 95\E7\A8\8B\E5\BA\8F\E8\AE\BE\E8\AE\A1")
!4 = !{}
!5 = distinct !DISubprogram(name: "ex0806", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 9, column: 1, scope: !5)
!9 = !DILocation(line: 10, column: 1, scope: !5)
!10 = !DILocation(line: 11, column: 1, scope: !5)
!11 = !DILocation(line: 12, column: 1, scope: !5)
!12 = distinct !{!12, !8, !11}
!13 = !DILocation(line: 14, column: 1, scope: !5)
!14 = !DILocation(line: 15, column: 1, scope: !5)
!15 = distinct !DISubprogram(name: "angle_to_rad", scope: !2, file: !3, line: 17, type: !16, scopeLine: 17, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!16 = !DISubroutineType(types: !17)
!17 = !{null, !18, !18}
!18 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!19 = !DILocation(line: 22, column: 1, scope: !15)
!20 = !DILocation(line: 24, column: 1, scope: !15)
!21 = !DILocation(line: 25, column: 1, scope: !15)
!22 = distinct !DISubprogram(name: "get_distance", scope: !2, file: !3, line: 27, type: !23, scopeLine: 27, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!23 = !DISubroutineType(types: !24)
!24 = !{null, !18, !18, !18}
!25 = !DILocation(line: 34, column: 1, scope: !22)
!26 = !DILocation(line: 35, column: 1, scope: !22)
!27 = !DILocation(line: 36, column: 1, scope: !22)
!28 = !DILocation(line: 37, column: 1, scope: !22)
!29 = !DILocation(line: 39, column: 1, scope: !22)
!30 = !DILocation(line: 40, column: 1, scope: !22)
